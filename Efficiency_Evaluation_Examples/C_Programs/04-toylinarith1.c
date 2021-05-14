//#Unsafe
// ****************************************************
//
//     Making Prophecies with Decision Predicates
//
//              Byron Cook * Eric Koskinen
//                     July 2010
//
// ****************************************************

//@ ltl invariant positive: AP(c > 5) ==> <>AP(resp > 5);

extern void __VERIFIER_error() __attribute__ ((__noreturn__));
extern void __VERIFIER_assume();
extern int __VERIFIER_nondet_int();

int c;
int servers ;
int resp;
int curr_serv;


c = 6; 
servers = 4;
resp = 0;
curr_serv = servers;


int main() {
	int tmp;
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

