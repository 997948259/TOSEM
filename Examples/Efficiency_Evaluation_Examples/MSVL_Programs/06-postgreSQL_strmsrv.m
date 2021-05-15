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
break_1,
break_2,
loc_continue, tmp
)
and 
(
	int closed and
	int MaxBackends and
	int family and
	int hostName and
	char *unixSocketName and
	int MaxListen and
	int fd and
	int err and
	int maxconn and
	int one and
	int service and
	int hint and
	int listen_index and
	int added and
	int addr_ai_family and
	int addr and
	int MAXADDR and
	int ListenSocket_OF_listen_index and
	int ret and
	int sock_path and
	int addrs and
	int tmp and
	int break_1 and
	int break_2 and 
	int loc_continue and skip;

	one := 1;
	listen_index := 0; 
	added := 0; 
	MAXADDR :=5; 
	addrs := 0;
	MaxBackends :=6; 
	ret := 0; 

	if (family = 3) then
	{
		service := sock_path
	}
	else
	{
		service := 1
	};

	ret :=1;
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
	addr := addrs;
	while(addr < MAXADDR AND !break_1)
	{
		if(0) then
		{
			loc_continue:=1
		};
				
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

				fd:=1;
		        if (fd)then
		        {
			       loc_continue:=1
		        }
				else
				{				
		           if(!loc_continue)then
				   {
				         closed:=1;
			         	 loc_continue:=1;
						 if(!loc_continue)then
						 {
		                      err:=-1;
	                          if (err < 0)then
	          	              {
		        	             closed:=1;
		                       	 loc_continue:=1
	                          };
							  if(!loc_continue)then
							  {
		                          if (addr_ai_family = 3)then
		                          {
									if(0!=1) then
									{
										closed:=1;
										break_1:=1
									}
		                          };
								  if(!break_1)then
								  {
	                              	 maxconn := MaxBackends * 2;
		                             if (maxconn > 10)then
									 {
			                            maxconn := 10;
		                                err:=-1;
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
		ret := 0;
		tmp:=10000000;
		while(tmp>0) then
		{
			tmp:=tmp-1
		}
	}
	else
	{	
    	ret := 1;
		tmp:=10000000;
		while(tmp>0)
		{
			tmp:=tmp-1
		}
	}
	

)
