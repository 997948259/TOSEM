//Unsafe

//AP(c > 5) ==> <>AP(resp > 5)
</
 define p: c>5;
 define q: resp>5;
 p->som(q)
/>
frame(c,servers,resp,curr_serv,ddd) and
(
int c and
int servers and
int resp and
int curr_serv and
int ddd and

c<==6 and   //c>0 的任意值
servers<== 4 and
resp <== 0 and
curr_serv <== 4 and skip;

  while(curr_serv > 0) {
   (
      c:=c-1;
      curr_serv:=curr_serv-1;
      resp:=resp+1)
     or
	 (
	   if(c<curr_serv)then ///__VERIFIER_assume(c < curr_serv);
	   {
	     curr_serv:=curr_serv-1
	   }
	 )
  }
)