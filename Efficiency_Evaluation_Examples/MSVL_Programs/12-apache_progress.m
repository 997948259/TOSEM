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

//@ ltl invariant positive: []((<>AP(lr>0) || <>AP(status!=7)) || AP(do_ACCEPT!=1));

</
define p: lr>0;
define q: status!=7;
define r: do_ACCEPT!=1;
alw(som(p)or som(q) or r)
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
uuu,ddd,
tmp
)
and
(
int do_ACCEPT and

int  ap_accept_lock_mech and
int  ap_listeners and
int  ap_lock_fname and
int  ap_max_mem_free and
int  ap_max_requests_per_child and
int  ap_scoreboard_image and
int  conn_rec and
int  current_conn and
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

int ap_my_pid and 
int parent_pid and
int my_child_num and
int ap_my_generation<==0 and
int tpf_child <== 0 and
char *tpf_server_name and 
void *csd and
int yyy2 and
  child_num_arg <== 2  
  and
  int numdesc<==-1 and
 void *pdesc and
 
 int loc_return<==0 and
 
 int loc_continueA<==0 and
 
 int break_1<==0 and
 
 int loc_continueB<==0 and
 int uuu and
 int ddd and
 int tmp and

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
  ap_listeners <== 2
  and
  skip;
  main()
);

//static void child_main(int child_num_arg)
function main()
{
    mpm_state := 9; 
    my_child_num := child_num_arg;
    ap_my_pid := 1;
    requests_this_child := 0;
    status :=5;
    if (status != 7) then{
		skip
    };

    num_listensocks :=10;
	lr := ap_listeners;
	i := num_listensocks;
	while(i)
	{
        i:=i-1;  
        pfd := 0;

        pfd_desc_type:= 6;
        pfd_desc_s := 1; 
        pfd_reqevents := 5;
        pfd_client_data := lr
    };

    mpm_state := 8;
    bucket_alloc := 0；

    while (!die_now) then
	{
        if ((ap_max_requests_per_child > 0
             AND requests_this_child >= ap_max_requests_per_child)) {
            skip
        };
		requests_this_child:=requests_this_child+1;

	   do_ACCEPT:=1; do_ACCEPT:=0;

        if (num_listensocks = 1) then{
            /* There is only one listener record, so refer to that one. */
            lr := ap_listeners
        }
        else {
            /* multiple listening sockets - need to poll */
            if(!break_1) then
			{	    
                status := 3;
                if (status != 7) then
				{
                    if (1) then
					{                         
						if (one_process AND shutdown_pending) then
						{
			               loc_return:=1
                        };
						if(!loc_return)then
                        {
						 loc_continueA:=1
						}
                    }
                };
				
				if(!loc_return AND !loc_continueA) then
				{
					if (last_poll_idx >= numdesc)then
					{ 
						last_poll_idx := 0
					};
                lr := 1; 
		        break_1:=1
				};
				if(!break_1)then
				{
					if(!loc_return)then
					{ 
						yyy2:=yyy2
					}
				}
            }
        };
		 
		if(!loc_return)then
        {		
        status :=5;

        if (status = 4) then{
			skip
        }
        else 
		{
		  if (status != 7) then
		  {
	          loc_continueB:=1
           }
		};

       if(!loc_continueB)then
	   {
			current_conn :=0;
			if (current_conn) then 
			{
				skip
			};
			if (1 == 7) then 
			{
				die_now := 1
			}
			else 
			{
				if (ap_my_generation != 0) then{
				die_now := 1
				}	
			}
		
		};
        uuu:=uuu
        }		
    };
	tmp:=10000000;
    while(tmp>0) 
    {
	  tmp:=tmp-1
    }
}

