//#Safe
//@ ltl invariant positive: [](AP(added>0) ==> <>[]AP(ret==1));

</
 define p: added>=0;
 alw(p)
/>

frame(closed,MaxBackends,family,hostName,portNumber,unixSocketName,
MaxListen,
fd, err,
maxconn,
one,
service,
hint,
listen_index,
added,
addr_ai_family,
addr,
MAXADDR,
ListenSocket_OF_listen_index,
ret,
sock_path,
addrs,
rrr,
ddd,
break_1,
break_2,
loc_continue
)
and 
(

int closed and
int MaxBackends and
int family and
int hostName<==0 and
//unsigned short portNumber 
//and
char *unixSocketName 
and
int MaxListen<==5 
and
int fd 
and
int err 
and
int maxconn 
and
int one 
and
//int ret 
//and
int service 
and
int hint 
and
int listen_index 
and
int added 
and
int addr_ai_family<==1 
and
int addr 
and
int MAXADDR 
and
int ListenSocket_OF_listen_index 
and
int ret 
and
int sock_path<==0 
and
int addrs 
and
int rrr 
and 
int ddd 
and
int break_1<==0 
and
int break_2<==0 
and 
int loc_continue<==0 
and

one <== 1 
and
listen_index <== 0 
and
added <== 0 
and
MAXADDR <==5// __VERIFIER_nondet_int() 
and
addrs <== 0//__VERIFIER_nondet_int() 
and
MaxBackends <==6 //__VERIFIER_nondet_int() 
and
ret <== 0 
and
skip;

((family<==3 and skip) or (family<==2 and skip));

if(addrs>=0 AND MaxBackends>0)then
{	
   //__VERIFIER_assume(addrs>=0);
	//__VERIFIER_assume(MaxBackends>0);

	if (family = 3)
	then
	{
		service <== sock_path and skip
	}
	else
	{
		skip;
		service <== 1 and skip
	};

	ret <==1 and skip;
	if (ret OR !addrs)then
	{
		if (hostName)then
		{
			skip
		} 
		else 
		{
		  skip
		}
	};
	addr <== addrs and skip;
	if( addr < MAXADDR AND !break_1)then
	{
		(loc_continue:=1 or loc_continue:=0);
				
		if(!loc_continue)then
		{
		   while(listen_index < MaxListen AND !break_2)
		   {
			 if (ListenSocket_OF_listen_index = -1)then
			 { 
			    break_2:=1
			 }
			 else
			 {
			   listen_index:=listen_index+1
			 }
		   };
		   if (listen_index >= MaxListen)then
		   {
			  break_1:=1
		   }
		   else
		   {
		       if(addr_ai_family=1) then 
	           {
			     skip
		       } 
		       else
               {	
        	       if(addr_ai_family=2)then
	               {
		        	   skip
		           } 
		           else 
			       {
			          if(addr_ai_family=3)then
		              {
			            skip
		              }
		              else 
		              {
			             skip
		              }
		            }
		        };

				(fd:=-1 or fd:=0 or fd:=1);
		        if (fd)then
		        {
			       loc_continue:=1
		        }
				else
				{				

				   (loc_continue:=1 or loc_continue:=0);
		           if(!loc_continue)then
				   {
				         (skip or
				         (closed:=1;
			         	 loc_continue:=1));
						 if(!loc_continue)then
						 {
		           
		                      (err := 0 
							  or err:=-1);
	                          if (err < 0)then
	          	              {
		        	             closed:=1;
		                       	 loc_continue:=1
	                          };
							  if(!loc_continue)then
							  {

		                          if (addr_ai_family = 3)then
		                          {
			                         (skip or
									 (
				                       closed:=1;
				                       break_1:=1
			                          ))
		                          };
								  if(!break_1)then
								  {
		
	                              	 maxconn := MaxBackends * 2;
		                             if (maxconn > 10)then
									 {
			                            maxconn := 10;

		                                (err := 0 or err:=-1);
		                                if (err < 0)then
	                                   	{
			                               closed:=1;
			                               loc_continue:=1
		                                };
										if(!loc_continue)then
										{
		
		                                 ListenSocket_OF_listen_index := fd;
		                                 added:=added+1
		                                }
		                              }
		                          }
		                      }
		                  }
		           }
		       }
		   }
		};

		if(!break_1)then
		{		
	       addr:=addr+1
		}
		
	};

	if (!added)then
	{
		ret := 0
	}
	else
	{	
    	ret := 0
	}
	
}

)
