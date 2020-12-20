//#UnSafe
//@ ltl invariant positive: ([] AP(die_now == 0)) ==> ([]<>AP(do_ACCEPT != 0));
</
define p: die_now=0;
define q: do_ACCEPT!=0;
alw(p)->alw(som(q))
/>


frame(
do_ACCEPT,
ap_accept_lock_mech,
ap_listeners,
ap_lock_fname,
ap_max_mem_free,
ap_max_requests_per_child,
ap_scoreboard_image,
conn_rec,
current_conn,
numdesc,
shutdown_pending,
pfd_desc_type,
pfd_desc_s,
pfd_reqevents,
pfd_client_data,
die_now,
requests_this_child,
num_listensocks,
ptrans,
allocator,
status,
i,
lr,
pollset,
sbh,
bucket_alloc,
last_poll_idx,
child_num_arg,
ap_threads_per_child,        
accept_mutex,
ap_daemons_to_start,
ap_daemons_min_free,
ap_daemons_max_free,
ap_daemons_limit,    
server_limit,
first_server_limit,
changed_limit_at_restart,
mpm_state,
pod,
ap_max_daemons_limit,
ap_server_conf,
one_process,
pconf,   
pchild, 

ap_my_pid,
parent_pid,
my_child_num,
ap_my_generation,
tpf_child,
tpf_server_name,
pfd,
csd,
yyy2,
pdesc,
loc_return,
loc_continueA,
break_1,
loc_continueB, 
uuu,ddd
)
and
(
int do_ACCEPT and

//int accept_mutex_off() { }
//int unixd_setup_child() { }
//int APR_STATUS_IS_EINTR(int a) { }
//int accept_mutex_on() { }
//int SAFE_ACCEPT(int a) { }
//int clean_child_exit(int a) { }

//#define AP_MPMQ_STARTING 9
int  ap_accept_lock_mech and
int  ap_listeners and
int  ap_lock_fname and
int  ap_max_mem_free and
int  ap_max_requests_per_child and
int  ap_scoreboard_image and
int  conn_rec and
int  current_conn and
//int  numdesc and
int  pfd and
int  shutdown_pending and
int  pfd_desc_type and
int  pfd_desc_s  and
int  pfd_reqevents and
int  pfd_client_data and

int die_now and
int requests_this_child and
int num_listensocks<== 0 and

void *ptrans and
void *allocator and
int status and
int i and
int lr and
void *pollset and
void *sbh and
void *bucket_alloc and
int last_poll_idx and
int child_num_arg and
int ap_threads_per_child and         /* Worker threads per child */
void *accept_mutex and
int ap_daemons_to_start<==0 and
int ap_daemons_min_free<==0 and
int ap_daemons_max_free<==0 and
int ap_daemons_limit<==0 and     /* MaxClients */
int server_limit <== 256 and
int first_server_limit <== 0 and
int changed_limit_at_restart and
int mpm_state <== 1 and //AP_MPMQ_STARTING;
void *pod and
int ap_max_daemons_limit <== -1 and
void *ap_server_conf and
int one_process <== 0 and
void *pconf and               /* Pool for config stuff */
void *pchild and            /* Pool for httpd child stuff */

int ap_my_pid and /* it seems silly to call getpid all the time */
int parent_pid and
int my_child_num and
int ap_my_generation<==0 and
int tpf_child <== 0 and
char *tpf_server_name and // [256+1]; // INETD_SERVNAME_LENGTH+1];

//int pfd and

//int current_conn and
        void *csd and
int yyy2 and
  child_num_arg <== 2 //__VERIFIER_nondet_int() 
  and
  
  int numdesc<==-1 and
 void *pdesc and
 
 int loc_return<==0 and
 
 int loc_continueA<==0 and
 
 int break_1<==0 and
 
 int loc_continueB<==0 and
 int uuu and
 int ddd and

  do_ACCEPT <== 0 and
  die_now <== 0 and
  last_poll_idx <== 0 and
  ap_threads_per_child <== 0 and
  ap_daemons_to_start<==0 and
  ap_daemons_min_free<==0 and
  ap_daemons_max_free<==0 and
  ap_daemons_limit<==0 and     /* MaxClients */
  server_limit <== 256 and
  first_server_limit <== 0 and
  ap_listeners <== 2 //__VERIFIER_nondet_int() 
  and
  skip;
  main()
);



/*****************************************************************
 * Child process main loop.
 * The following vars are static to avoid getting clobbered by longjmp();
 * they are really private to child_main.
 */
//int getpid() { return __VERIFIER_nondet_int(); }
//void ap_fatal_signal_child_setup(int ap_server_conf) {}
//void apr_allocator_create(int *allocator) {}
//void apr_allocator_max_free_set(int allocator, int ap_max_mem_free) {}
//void apr_pool_create_ex(int *pchild, int pconf, int NL, int allocator) {}
//void apr_allocator_owner_set(int allocator, int pchild) {}
//void apr_pool_create(int *ptrans, int pchild) {}
//void apr_pool_tag(int ptrans, char *asdf) {}
//void ap_reopen_scoreboard(int pchild, int NL, int z) {}
//int apr_proc_mutex_child_init(int *accept_mutex, int ap_lock_fname, int pchild) { return __VERIFIER_nondet_int(); }
//void ap_log_error(int APm, int APe, int status, int ap_server_conf, int a, int b, int c) {}
//void ap_log_error5(int APm, int APe, int status, int ap_server_conf, int a) {}
//void ap_run_child_init(int pchild, int ap_server_conf) {}
//void ap_create_sb_handle(int *sbh, int pchild, int my_child_num, int z) {}
//void ap_update_child_status(int sbh, int SER, int NL) {}
//void apr_pollset_create(int *pollset, int num_listensocks, int pchild, int z) {}
//void apr_pollset_add(int pollset, int *pfd) {}
//void *apr_bucket_alloc_create(int pchild) {}
//void apr_pool_clear(int ptrans) {}
//int apr_pollset_poll(int pollset, int a, int *numdesc, int *pdesc) {}
//int ap_run_create_connection(int ptrans, int ap_server_conf, int csd, int my_child_num, int sbh, int bucket_alloc) {}
//void ap_process_connection(int current_conn, int csd) {}
//void ap_lingering_close(int current_conn) {}
//int ap_mpm_pod_check(int a) { return __VERIFIER_nondet_int(); }

//static void child_main(int child_num_arg)
function main()
{
//  __VERIFIER_assume(child_num_arg > 0);
//__VERIFIER_assume(ap_listeners > 0);

    mpm_state := 9; /* for benefit of any hooks that run as this
                                   * child initializes
                                   */

    my_child_num := child_num_arg;
    ap_my_pid := 1;//getpid();
    requests_this_child := 0;

   // ap_fatal_signal_child_setup(ap_server_conf);

    /* Get a sub context for global allocations in this child, so that
     * we can have cleanups occur when the child exits.
     */
    //apr_allocator_create(&allocator);
    //apr_allocator_max_free_set(allocator, ap_max_mem_free);
   // apr_pool_create_ex(&pchild, pconf, 0, allocator);
    //apr_allocator_owner_set(allocator, pchild);

    //apr_pool_create(&ptrans, pchild);
    //apr_pool_tag(ptrans, "transaction");

    /* needs to be done before we switch UIDs so we have permissions */
    //ap_reopen_scoreboard(pchild, 0, 0);
    status :=5;// apr_proc_mutex_child_init(&accept_mutex, ap_lock_fname, pchild);
    if (status != 7) then{
        //ap_log_error(3, 1, status, ap_server_conf,
       //              "Couldn't initialize cross-process lock in child "
         //            "(%s) (%d)", ap_lock_fname, ap_accept_lock_mech);
        //clean_child_exit(APEXIT_CHILDFATAL);
		skip
    };

   // if (unixd_setup_child()) {
        //clean_child_exit(APEXIT_CHILDFATAL);
  //  }

   // ap_run_child_init(pchild, ap_server_conf);

   // ap_create_sb_handle(&sbh, pchild, my_child_num, 0);

   // ap_update_child_status(sbh, 1, 0);

    /* Set up the pollfd array */
    /* ### check the status */
    //(void) apr_pollset_create(&pollset, num_listensocks, pchild, 0);

    num_listensocks :=10; //__VERIFIER_nondet_int(); //__VERIFIER_assume(num_listensocks>0);

	lr := ap_listeners;
	i := num_listensocks;
	while(i)
	{
        i:=i-1;  
        pfd := 0;

        pfd_desc_type:= 6;
        pfd_desc_s := 1; // lr->sd;
        pfd_reqevents := 5;
        pfd_client_data := lr

        /* ### check the status */
        //(void) apr_pollset_add(pollset, &pfd);
    };

    mpm_state := 8;

    bucket_alloc := 1;//apr_bucket_alloc_create(pchild);

    if (!die_now) then
	{
        

        /*
         * (Re)initialize this child to a pre-connection state.
         */

        //apr_pool_clear(ptrans);

       /* if ((ap_max_requests_per_child > 0
             && requests_this_child++ >= ap_max_requests_per_child)) {
            //clean_child_exit(0);
        }*/

       // (void) ap_update_child_status(sbh, 1, 0);

        /*
         * Wait for an acceptable connection to arrive.
         */

        /* Lock around "accept", if necessary */
        //SAFE_ACCEPT(accept_mutex_on());
	   do_ACCEPT:=1; do_ACCEPT:=0;

        if (num_listensocks = 1) then{
            /* There is only one listener record, so refer to that one. */
            lr := ap_listeners
        }
        else {
            /* multiple listening sockets - need to poll */
            if(!break_1) then
			{	    
                /* timeout == -1 == wait forever */
                status := 3;//apr_pollset_poll(pollset, -1, &numdesc, &pdesc);
                if (status != 7) then
				{
                    //if (APR_STATUS_IS_EINTR(status)) 
					//then{                     
					    
						if (one_process AND shutdown_pending) 
						then{
			               loc_return:=1
                        };
						if(!loc_return)then
                        {
						 loc_continueA:=1
						}
						
						
                    //}
                    /* Single Unix documents select as returning errnos
                     * EBADF, EINTR, and EINVAL... and in none of those
                     * cases does it make sense to continue.  In fact
                     * on Linux 2.0.x we seem to end up with EFAULT
                     * occasionally, and we'd loop forever due to it.
                     */
                    //ap_log_error5(3, 2, status,
                      //           ap_server_conf, "apr_pollset_poll: (listen)");
                    //clean_child_exit(1);
                };
				
				if(!loc_return AND !loc_continueA) then
				{
                /* We can always use pdesc[0], but sockets at position N
                 * could end up completely starved of attention in a very
                 * busy server. Therefore, we round-robin across the
                 * returned set of descriptors. While it is possible that
                 * the returned set of descriptors might flip around and
                 * continue to starve some sockets, we happen to know the
                 * internal pollset implementation retains ordering
                 * stability of the sockets. Thus, the round-robin should
                 * ensure that a socket will eventually be serviced.
                 */
                if (last_poll_idx >= numdesc)then
                   { last_poll_idx := 0};

                /* Grab a listener record from the client_data of the poll
                 * descriptor, and advance our saved index to round-robin
                 * the next fetch.
                 *
                 * ### hmm... this descriptor might have POLLERR rather
                 * ### than POLLIN
                 */
                lr := 1; //pdesc[last_poll_idx++].client_data;
		        break_1:=1
				};
				if(!break_1)then
				{
				  if(!loc_return)then
                  { yyy2:=yyy2}
				 }
            }
        };
        /* if we accept() something we don't want to die, so we have to
         * defer the exit
         */
		 
		if(!loc_return)then
        {		
        status :=5; //__VERIFIER_nondet_int(); // lr->accept_func(&csd, lr, ptrans);

        //SAFE_ACCEPT(accept_mutex_off());      /* unlock after "accept" */

        if (status = 4) then{
            /* resource shortage or should-not-occur occured */
            //clean_child_exit(1);
			skip
        }
        else 
		{
		  if (status != 7) then{
	          loc_continueB:=1
           }
		};

        /*
         * We now have a connection, so set it up with the appropriate
         * socket options, file descriptors, and read/write buffers.
         */
       if(!loc_continueB)then
	   {
        current_conn :=0// ap_run_create_connection(ptrans, ap_server_conf, csd, my_child_num, sbh, bucket_alloc);
        //if (current_conn) {
           // ap_process_connection(current_conn, csd);
            //ap_lingering_close(current_conn);
		//	skip
       // }

        /* Check the pod and the generation number after processing a
         * connection so that we'll go away if a graceful restart occurred
         * while we were processing the connection or we are the lucky
         * idle server process that gets to die.
         */
        //if (ap_mpm_pod_check(pod) == 7) { /* selected as idle? */
        //    die_now = 1;
        //}
       // else if (ap_my_generation != __VERIFIER_nondet_int()) {
	    //ap_scoreboard_image->global->running_generation) { /* restart? */
            /* yeah, this could be non-graceful restart, in which case the
             * parent will kill us soon enough, but why bother checking?
             */
        //    die_now = 1;
        //}
		};
        uuu:=uuu
        }		
    }
}
