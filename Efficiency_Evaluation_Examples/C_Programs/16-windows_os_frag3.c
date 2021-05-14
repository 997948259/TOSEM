//#Safe
// ****************************************************
//
//     Making Prophecies with Decision Predicates
//
//              Byron Cook * Eric Koskinen
//                     July 2010
//
// ****************************************************

//@ ltl invariant positive: <>[]AP( Stored == 0 );

extern void __VERIFIER_error() __attribute__ ((__noreturn__));
extern void __VERIFIER_assume();
extern int __VERIFIER_nondet_int();

int Stored;
void init() { Stored = 0; }
int tmp;
void main() {
	init();
	tmp=10;
    while(tmp>0) {
           if (1) {
               
           } else {
               Stored = 1;
               break;
           }
		   tmp--;
    }
    // Lower Irql and process
    if (Stored==1) {
        Stored = 0;
    }
	tmp=10000000;
	while (tmp>0) {tmp=tmp-1;}
}