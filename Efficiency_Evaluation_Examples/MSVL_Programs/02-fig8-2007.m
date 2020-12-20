//#Safe
//@ ltl invariant positive: [](AP(set != 0) ==> <> AP(unset!= 0));
</
  define p: set!=0;
  define q: unset!=0;
  alw(p->som(q))
/>
function main() 
{
frame(break_1,loc_continue) and
(
  int break_1<==0 and int loc_continue<==0 and
  set <== 1 and skip; 
  set <== 0 and skip; 
  while (i < Pdolen AND !break_1 AND !loc_continue) 
  { 
    ((DName <==1 and skip) or (DName <==0 and skip));
     if (!DName)then { break_1<==1 and skip}; 	
    if (!break_1)then{   
     ((status <== 1 and skip) or (status<==2 and skip) or (status<==3 and skip)); 
	 pc <== 1 and skip; 
	 pc <== 0 and skip;
     if ( status!= 1) then{ 
         Pdoi <== 0 and skip; 
         if ( status=2 ) 
		 then{ 
	        num:=num+1; 
	        loc_continue<==1 and skip 
          } ;
       break_1<==1 and skip
      }
     else { 
       i:=i+1
       } 
	}
  };
  if(!loc_continue)then
  {
     num <== 0 and skip;  
     unset <== 1 and skip; unset <== 0 and skip
  }
 )
};

frame(pc,i,Pdolen, num,DName,lptNamei,dcIdi,Pdoi,PdoType,status,set,unset)and
(
int pc and
int i and int Pdolen and int num and int DName and
int lptNamei and //[5];
int dcIdi and // [5];
int Pdoi and //[5];
int PdoType and int status and
int set <== 0 and int unset <== 0 and skip;
main()
)

