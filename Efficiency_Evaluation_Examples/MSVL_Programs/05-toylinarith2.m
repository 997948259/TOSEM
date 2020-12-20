//#Safe
//@ ltl invariant positive: AP(c > (servers / 2)) ==> <>AP(resp > (servers / 2));
</
  define p: c>(servers/2);
  define q: resp>(servers/2);  
  p->som(q)
/>

frame(c,servers,resp,curr_serv,serversdiv2,ddd) and
(
unsigned int c and int ddd and
int servers and
int resp and
int curr_serv and
int serversdiv2 and skip;
((c:=2 and //c = __VERIFIER_nondet_int();
servers:=4 and //servers = __VERIFIER_nondet_int(); 
serversdiv2:=2)//serversdiv2 = __VERIFIER_nondet_int();
or
(
 c:=2 and 
 servers:=5 and
 serversdiv2:=2
))
;

if(servers>0 AND c > 0)then //__VERIFIER_assume(servers>0 && c > 0); 
{
	/*if(__VERIFIER_nondet_int())
		__VERIFIER_assume(serversdiv2+serversdiv2==servers);
	else
		__VERIFIER_assume(serversdiv2+serversdiv2+1==servers);*/
	resp <== 0 and skip;
	curr_serv <== servers and skip;
  
	if(curr_serv > 0)then {
		(
			c:=c-1; 
			curr_serv:=curr_serv-1;
			resp:=resp+1
		)
		or
		(
			if(c<curr_serv)then//__VERIFIER_assume(c < curr_serv);
			{curr_serv:=curr_serv-1}
		)
	}
}
)
