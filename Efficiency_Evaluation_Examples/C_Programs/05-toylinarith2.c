//#Safe
// ****************************************************
//
//     Making Prophecies with Decision Predicates
//
//              Byron Cook * Eric Koskinen
//                     July 2010
//
// ****************************************************

//@ ltl invariant positive: AP(c > (servers / 2)) ==> <>AP(resp > (servers / 2));

extern void __VERIFIER_error() __attribute__ ((__noreturn__));
extern void __VERIFIER_assume();
extern int __VERIFIER_nondet_int();

unsigned int c;
int servers;
int resp;
int curr_serv;
int serversdiv2;

c = 2;
servers = 4; 
serversdiv2 = 2;
  
int main() {

	resp = 0;
	curr_serv = servers;
  
	while(curr_serv > 0) {
		if(1) {
			c--; curr_serv--;
			resp++;
		} else {
			curr_serv--;
		}
	}
	tmp=10000000;
    while (tmp>0) {tmp=tmp-1;}
}
