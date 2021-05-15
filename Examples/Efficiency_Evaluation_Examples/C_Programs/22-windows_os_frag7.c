//#Safe
// ****************************************************
//
//     Making Prophecies with Decision Predicates
//
//              Byron Cook * Eric Koskinen
//                     July 2010
//
// ****************************************************

//@ ltl invariant positive: []<> AP(WItemsNum >= 1 );

extern void __VERIFIER_error() __attribute__ ((__noreturn__));
extern void __VERIFIER_assume();
extern int __VERIFIER_nondet_int();

int WItemsNum;
int tmp;

void main() {
    WItemsNum = -1;
	tmp=10;
    while(tmp>0) {
        while(WItemsNum<=5) {
               if (WItemsNum<=5) {
                   WItemsNum++;
               } else {
                   WItemsNum++;
               }
        }
        while(WItemsNum>2) {
             WItemsNum--;
        }
		tmp--;
    }
    tmp=10000000;
	while (tmp>0) {tmp=tmp-1;}
}

