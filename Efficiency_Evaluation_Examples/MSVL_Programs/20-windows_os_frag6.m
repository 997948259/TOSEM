//#Safe
//@ ltl invariant positive: <>[]AP(WItemsNum >= 1 );
</
   define p: WItemsNum >= 1;
   som(alw(p))
/>

frame(WItemsNum,loop)
and
(
int WItemsNum and int loop and skip;
WItemsNum := 3;//__VERIFIER_nondet_int();
main()
);

//void callback1() {}
//void callback2() {}
//#define MoreWItems() __VERIFIER_nondet_int()

function main() {
    WItemsNum := -1;//__VERIFIER_nondet_int();
    if(1)then {
		loop:=0;
        while(WItemsNum<=5 OR loop) {
               if (WItemsNum<=5) then{
                  // callback1();
                   WItemsNum:=WItemsNum+1
    
               } else {
                   WItemsNum:=WItemsNum+1
               }
        };
    
        while(WItemsNum>2) {
            // callback2();
             WItemsNum:=WItemsNum-1
        }
    }
  //  while(1) {}
}
