#include <pthread.h>
#include<Windows.h>
#include <atomic>  
#pragma comment(lib, "pthreadVC2.lib")  //����������
#define THREADNUMBER 5//�궨���߳���Ŀ
#define MULTIPATHNUM 5//�궨���·��ʱ�����߳���
#define MULTIMAXPATHNUM 50//�궨���·��ʱһ��ʼ�̳߳صĴ�С����Ϊ������ܻ�䣬���������������һЩ����������ò�����ô��


/* Ҫִ�е��������� */
typedef struct tpool_work {
	void*               (*routine)(void*);       /* ������ */
	void                *arg;                    /* �����������Ĳ��� */
	struct tpool_work   *next;
}tpool_work_t;

typedef struct tpool {
	int             shutdown;                    /* �̳߳��Ƿ����� */
	int             max_thr_num;                /* ����߳��� */
	pthread_t       *thr_id;                    /* �߳�ID���� */
	tpool_work_t    *queue_head;                /* �߳����� */
	pthread_mutex_t queue_lock;
	pthread_cond_t  queue_ready;
	int queue_cur_num;                //���е�ǰ��job����
	std::atomic_int cur_working_job_num;		//��ǰ����ִ�е��̵߳ĸ���
	std::atomic_int cur_max_thr_num;			//��ǰ���������߳���
	std::atomic_int addWorkNum;			//�����̳߳��е�������
	std::atomic_int completeWorkNum;		//�̳߳��Ѿ���ɵ�������

}tpool_t;

/*
* @brief     �����̳߳�
* @param     max_thr_num ����߳���
* @return     0: �ɹ� ����: ʧ��
*/
int
tpool_create(int thread_index, int max_thr_num);

/*
* @brief     �����̳߳�
*/
void
tpool_destroy(int thread_index);

/*
* @brief     ���̳߳����������
* @param    routine ������ָ��
* @param     arg ����������
* @return     0: �ɹ� ����:ʧ��
*/
int
tpool_add_work(int thread_index, void*(*routine)(void*), void *arg);

void tpool_await(int thread_index);

void tpool_adjust(int thread_index, int poolSize);