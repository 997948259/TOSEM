//#Safe
// ****************************************************
//
//     Making Prophecies with Decision Predicates
//
//              Byron Cook * Eric Koskinen
//                     July 2010
//
// ****************************************************

//@ ltl invariant positive: [](AP(a != 0) ==> <> AP(r!= 0));

extern void __VERIFIER_error() __attribute__ ((__noreturn__));
extern void __VERIFIER_assume();
extern int __VERIFIER_nondet_int();

int a = 0;
int r = 0;

int main() {
   int n;
   int tmp;
   tmp=10;
  while(tmp>0) {
    a = 1;
    a = 0;
    n = 1;
    while(n>0) {
      n--;
    }
    r = 1;
    r = 0;
	tmp=tmp-1;
  }
  tmp=10000000;
  while (tmp>0) {tmp=tmp-1;}
  return 0;
}
