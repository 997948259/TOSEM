//#Safe
//@ ltl invariant positive: AP(c > (servers / 2)) ==> <>AP(resp > (servers / 2));
</
  define p: c>(servers/2);
  define q: resp>(servers/2);  
  p->som(q)
/>

frame(c,servers,resp,curr_serv,serversdiv2,tmp) and
(
	unsigned int c and
	int servers and
	int resp and
	int curr_serv and
	int serversdiv2 and int tmp skip;
	c:=2; 
	servers:=4; 
	serversdiv2:=2;

	resp := 0;
	curr_serv := servers;
	while(curr_serv > 0)
	{
		if(1)then 
		{
			c:=c-1; 
			curr_serv:=curr_serv-1;
			resp:=resp+1
		}
		else
		{
			curr_serv:=curr_serv-1
		}
	};
	tmp:=10000000;
	while(tmp>0)
	{
		tmp:=tmp-1
	}
)
