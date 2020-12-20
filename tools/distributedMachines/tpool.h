#include <pthread.h>
#include<Windows.h>
#include <atomic>  
#pragma comment(lib, "pthreadVC2.lib")  //必须加上这句
#define THREADNUMBER 5//宏定义线程数目
#define MULTIPATHNUM 5//宏定义多路径时最大的线程数
#define MULTIMAXPATHNUM 50//宏定义多路径时一开始线程池的大小，因为后面可能会变，所以这个数尽量大一些，后面可以用不了这么多


/* 要执行的任务链表 */
typedef struct tpool_work {
	void*               (*routine)(void*);       /* 任务函数 */
	void                *arg;                    /* 传入任务函数的参数 */
	struct tpool_work   *next;
}tpool_work_t;

typedef struct tpool {
	int             shutdown;                    /* 线程池是否销毁 */
	int             max_thr_num;                /* 最大线程数 */
	pthread_t       *thr_id;                    /* 线程ID数组 */
	tpool_work_t    *queue_head;                /* 线程链表 */
	pthread_mutex_t queue_lock;
	pthread_cond_t  queue_ready;
	int queue_cur_num;                //队列当前的job个数
	std::atomic_int cur_working_job_num;		//当前正在执行的线程的个数
	std::atomic_int cur_max_thr_num;			//当前允许的最大线程数
	std::atomic_int addWorkNum;			//加入线程池中的任务数
	std::atomic_int completeWorkNum;		//线程池已经完成的任务数

}tpool_t;

/*
* @brief     创建线程池
* @param     max_thr_num 最大线程数
* @return     0: 成功 其他: 失败
*/
int
tpool_create(int thread_index, int max_thr_num);

/*
* @brief     销毁线程池
*/
void
tpool_destroy(int thread_index);

/*
* @brief     向线程池中添加任务
* @param    routine 任务函数指针
* @param     arg 任务函数参数
* @return     0: 成功 其他:失败
*/
int
tpool_add_work(int thread_index, void*(*routine)(void*), void *arg);

void tpool_await(int thread_index);

void tpool_adjust(int thread_index, int poolSize);