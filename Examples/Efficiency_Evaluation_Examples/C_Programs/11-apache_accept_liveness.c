//#Safe
//
// ****************************************************
//
//     Making Prophecies with Decision Predicates
//
//              Byron Cook * Eric Koskinen
//                     July 2010
//
// ****************************************************

//@ ltl invariant positive: ([] AP(die_now == 0)) ==> ([]<>AP(do_ACCEPT != 0));

extern void __VERIFIER_error() __attribute__ ((__noreturn__));
extern void __VERIFIER_assume();
extern int __VERIFIER_nondet_int();

int do_ACCEPT; 

#define DEFAULT_SERVER_LIMIT 256
#define MAX_SERVER_LIMIT 200000
#define HARD_THREAD_LIMIT 1

#define APEXIT_CHILDFATAL 1
#define APLOG_EMERG 1
#define APLOG_ERR 2
#define APLOG_MARK 3
#define APR_EGENERAL 4
#define APR_POLLIN 5
#define APR_POLL_SOCKET 6 
#define APR_SUCCESS 7
#define AP_MPMQ_RUNNING 8
#define AP_MPMQ_STARTING 9
#define NULL 0
#define SERVER_READY 1
int  ap_accept_lock_mech;
int  ap_listeners;
int  ap_lock_fname;
int  ap_max_mem_free;
int  ap_max_requests_per_child;
int  ap_scoreboard_image;
int  conn_rec;
int  current_conn;
int  numdesc;
int  pfd;
int  shutdown_pending;
int        pfd_desc_type;
int        pfd_desc_s;
int        pfd_reqevents;
int        pfd_client_data;

static volatile int die_now;
static int requests_this_child;
static int num_listensocks = 0;

void *ptrans;
void *allocator;
int status;
int i;
int lr;
void *pollset;
void *sbh;
void *bucket_alloc;
int last_poll_idx;
int child_num_arg;
int ap_threads_per_child;         /* Worker threads per child */
static void *accept_mutex;
static int ap_daemons_to_start=0;
static int ap_daemons_min_free=0;
static int ap_daemons_max_free=0;
static int ap_daemons_limit=0;      /* MaxClients */
static int server_limit = DEFAULT_SERVER_LIMIT;
static int first_server_limit = 0;
static int changed_limit_at_restart;
static int mpm_state = 1;//AP_MPMQ_STARTING;
static void *pod;
int ap_max_daemons_limit = -1;
void *ap_server_conf;
static int one_process = 0;
static void *pconf;               /* Pool for config stuff */
static void *pchild;              /* Pool for httpd child stuff */

static int ap_my_pid; 
static int parent_pid;
static int my_child_num;
int ap_my_generation=0;
int tpf_child = 0;
char *tpf_server_name; 


  child_num_arg = 2; 

  do_ACCEPT = 0;
  die_now = 0;
  last_poll_idx = 0;
  ap_threads_per_child = 0;
  ap_daemons_to_start=0;
  ap_daemons_min_free=0;
  ap_daemons_max_free=0;
  ap_daemons_limit=0;      /* MaxClients */
  server_limit = DEFAULT_SERVER_LIMIT;
  first_server_limit = 0;
  ap_listeners = 2; 

//static void child_main(int child_num_arg)
void main()
{
    mpm_state = AP_MPMQ_STARTING; 
    my_child_num = child_num_arg;
    ap_my_pid = 1;
    requests_this_child = 0;
    status = 5;
    if (status != APR_SUCCESS) {
    }

    num_listensocks = 10； 

    for (lr = ap_listeners, i = num_listensocks; i--; ) {
        int pfd = 0;

        pfd_desc_type = APR_POLL_SOCKET;
        pfd_desc_s = 1; 
        pfd_reqevents = APR_POLLIN;
        pfd_client_data = lr;
    }

    mpm_state = AP_MPMQ_RUNNING;

    bucket_alloc = 0;

    while (!die_now) {
        conn_rec *current_conn;
        void *csd;

        if ((ap_max_requests_per_child > 0
             && requests_this_child++ >= ap_max_requests_per_child)) {
        }

	do_ACCEPT=1; do_ACCEPT=0;

        if (num_listensocks == 1) {
            /* There is only one listener record, so refer to that one. */
            lr = ap_listeners;
        }
        else {
            /* multiple listening sockets - need to poll */
            for (;;) {
	      int numdesc;
                const void *pdesc;

                /* timeout == -1 == wait forever */
                status = 3;
                if (status != APR_SUCCESS) {
                    if (1) {
                        if (one_process && shutdown_pending) {
			  goto loc_return;
                        }
                        goto loc_continueA;
                    }
                }

                if (last_poll_idx >= numdesc)
                    last_poll_idx = 0;

                lr = 1; //pdesc[last_poll_idx++].client_data;
		break;

	    loc_continueA: {int yyy2; yyy2=yyy2; }
            }
        }

        status = 5; // lr->accept_func(&csd, lr, ptrans);

      
        if (status == APR_EGENERAL) {
            /* resource shortage or should-not-occur occured */
        }
        else if (status != APR_SUCCESS) {
	  goto loc_continueB;
        }


        current_conn = 0;
        if (current_conn) {
        }


        if (1 == APR_SUCCESS) { /* selected as idle? */
            die_now = 1;
        }
        else if (ap_my_generation != 0) {
            die_now = 1;
        }
    loc_continueB: { int uuu; uuu=uuu; }
    }
    clean_child_exit(0);
 loc_return:
    tmp=10000000;
	while (tmp>0) {tmp=tmp-1;}
}
