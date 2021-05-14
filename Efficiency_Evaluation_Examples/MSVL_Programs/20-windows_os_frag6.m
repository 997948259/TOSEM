//#Safe
//@ ltl invariant positive: <>[]AP(WItemsNum >= 1 );
</
   define p: WItemsNum >= 1;
   som(alw(p))
/>

frame(WItemsNum,tmp)
and
(
int WItemsNum and int tmp and skip;
main()
);

function main() {
    WItemsNum := -1;
	tmp:=10;
    while(tmp>0){
        while(WItemsNum<=5) {
               if (WItemsNum<=5) then{
                   WItemsNum:=WItemsNum+1
               } else {
                   WItemsNum:=WItemsNum+1
               }
        };
        while(WItemsNum>2) {
             WItemsNum:=WItemsNum-1
        };
		tmp:=tmp-1
    };
	tmp:=10000000;
    while(tmp>0)
    {
	  tmp:=tmp-1
    }
}
