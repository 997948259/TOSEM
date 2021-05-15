//Unsafe

//AP(c > 5) ==> <>AP(resp > 5)
</
 define p: c>5;
 define q: resp>5;
 p->som(q)
/>
frame(c,servers,resp,curr_serv,tmp) and
(
int c and
int servers and
int resp and
int curr_serv and
int tmp and skip;

c:=6;   
servers := 4 and
resp := 0 and
curr_serv := servers;

  while(curr_serv > 0) {
	if(1) then
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