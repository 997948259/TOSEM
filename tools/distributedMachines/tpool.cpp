#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "tpool.h"
#include <iostream>
using namespace std;
extern tpool_t *tpool[THREADNUMBER];
/* 工作者线程函数, 从任务链表中取出任务并执行 */
static void*
thread_routine(void *arg)
{
	tpool_work_t *work;
	int thread_index = (int)arg;
	while (1) {
		/* 如果线程池没有被销毁且没有任务要执行，则等待 */
		pthread_mutex_lock(&tpool[thread_index]->queue_lock);  //线程调用该函数让互斥锁上锁，如果该互斥锁已被另一个线程锁定和拥有，则调用该线程将阻塞，直到该互斥锁变为可用为止。
		while (!tpool[thread_index]->queue_head && !tpool[thread_index]->shutdown) {
			pthread_cond_wait(&tpool[thread_index]->queue_ready, &tpool[thread_index]->queue_lock);
		}

		if (tpool[thread_index]->queue_head != NULL
			&& tpool[thread_index]->cur_working_job_num <= tpool[thread_index]->cur_max_thr_num){

			tpool[thread_index]->queue_cur_num--;
			tpool[thread_index]->cur_working_job_num++;
			work = tpool[thread_index]->queue_head;
			tpool[thread_index]->queue_head = tpool[thread_index]->queue_head->next;
			pthread_mutex_unlock(&tpool[thread_index]->queue_lock);

			work->routine(work->arg);
			tpool[thread_index]->cur_working_job_num--;
			tpool[thread_index]->completeWorkNum++;
			free(work);
		}
		else if (tpool[thread_index]->shutdown) {
			pthread_mutex_unlock(&tpool[thread_index]->queue_lock);
			pthread_exit(NULL);
		}
		else
		{
			pthread_mutex_unlock(&tpool[thread_index]->queue_lock);
		}

	}

	return NULL;
}
//可以通过pthread_join()函数来使主线程阻塞等待其他线程退 出，这样主线程可以清理其他线程的环境。但是还有一些线程，更喜欢自己来清理退出的状态，他们也不愿意主线程调用pthread_join来等待他们。
/*
* 创建线程池
*/
int
tpool_create(int thread_index, int max_thr_num)
{
	int i;

	tpool[thread_index] = (tpool_t *)malloc(sizeof(tpool_t));
	if (!tpool[thread_index]) {
		printf("calloc failed\n");
		exit(1);
	}

	/* 初始化 */
	tpool[thread_index]->max_thr_num = max_thr_num;
	tpool[thread_index]->shutdown = 0;
	tpool[thread_index]->queue_head = NULL;
	tpool[thread_index]->queue_cur_num = 0;
	tpool[thread_index]->cur_working_job_num = 0;
	tpool[thread_index]->addWorkNum = 0;
	tpool[thread_index]->completeWorkNum = 0;
	tpool[thread_index]->cur_max_thr_num = 0;
	if (pthread_mutex_init(&tpool[thread_index]->queue_lock, NULL) != 0) {
		printf("pthread_mutex_init failed\n");
		exit(1);
	}
	if (pthread_cond_init(&tpool[thread_index]->queue_ready, NULL) != 0) {
		printf("%s: pthread_cond_init failed\n");
		exit(1);
	}

	/* 创建工作者线程 */
	tpool[thread_index]->thr_id = (pthread_t*)malloc(sizeof(pthread_t)*max_thr_num);
	if (!tpool[thread_index]->thr_id) {
		printf("calloc failed\n");
		exit(1);
	}
	for (i = 0; i < max_thr_num; ++i) {
		if (pthread_create(&tpool[thread_index]->thr_id[i], NULL, thread_routine, (void *)thread_index) != 0){
			printf("pthread_create failed, errno\n");
			exit(1);
		}
	}

	return 0;
}

void tpool_adjust(int thread_index, int poolSize)//每次调整线程池大小
{
	//cout << "poolSize:" << poolSize << endl;
	tpool[thread_index]->cur_max_thr_num = poolSize;
}

void tpool_await(int thread_index)//等待线程池中所有线程结束
{
	while (tpool[thread_index]->addWorkNum != tpool[thread_index]->completeWorkNum)
	{
		//cout << "addWorkNum:" << tpool[thread_index]->addWorkNum << "completeWorkNum" << tpool[thread_index]->completeWorkNum << endl;
		Sleep(1);
	}
}

/* 销毁线程池 */
void
tpool_destroy(int thread_index)
{
	int i;
	tpool_work_t *member;

	/*if (tpool[thread_index]->shutdown) {
		return;
	}
	tpool[thread_index]->shutdown = 1;

	pthread_mutex_lock(&tpool[thread_index]->queue_lock);
	pthread_cond_broadcast(&tpool[thread_index]->queue_ready);
	pthread_mutex_unlock(&tpool[thread_index]->queue_lock);

	for (i = 0; i < tpool[thread_index]->max_thr_num; ++i) {
		pthread_join(tpool[thread_index]->thr_id[i], NULL);//可以通过pthread_join()函数来使主线程阻塞等待其他线程退 出，
		//这样主线程可以清理其他线程的环境。但是还有一些线程，更喜欢自己来清理退出的状态，他们也不愿意主线程调用pthread_join来等待他们。
	}
	*/

	free(tpool[thread_index]->thr_id);

	while (tpool[thread_index]->queue_head) {
		member = tpool[thread_index]->queue_head;
		tpool[thread_index]->queue_head = tpool[thread_index]->queue_head->next;
		free(member);
	}

	pthread_mutex_destroy(&tpool[thread_index]->queue_lock);
	pthread_cond_destroy(&tpool[thread_index]->queue_ready);

	free(tpool[thread_index]);
}

/* 向线程池添加任务 */
int tpool_add_work(int thread_index, void*(*routine)(void*), void *arg)
{
	tpool_work_t *work, *member;

	if (!routine){
		printf("Invalid argument\n");
		return -1;
	}
	work = (tpool_work_t *)malloc(sizeof(tpool_work_t));
	if (!work) {
		printf("malloc failed\n");
		return -1;
	}
	work->routine = routine;
	work->arg = arg;
	work->next = NULL;

	pthread_mutex_lock(&tpool[thread_index]->queue_lock);
	tpool[thread_index]->addWorkNum++;
	member = tpool[thread_index]->queue_head;
	if (!member) {
		tpool[thread_index]->queue_head = work;
	}
	else {
		while (member->next) {
			member = member->next;
		}
		member->next = work;
	}
	tpool[thread_index]->queue_cur_num++;
	//cout << "队列线程个数:" << tpool[thread_index]->queue_cur_num << endl;
	/* 通知工作者线程，有新任务添加 */
	pthread_cond_signal(&tpool[thread_index]->queue_ready);
	pthread_mutex_unlock(&tpool[thread_index]->queue_lock);

	return 0;
}
