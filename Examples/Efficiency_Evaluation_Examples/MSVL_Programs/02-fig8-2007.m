//#Safe
//@ ltl invariant positive: [](AP(set != 0) ==> <> AP(unset!= 0));
</
  define p: set!=0;
  define q: unset!=0;
  alw(p->som(q))
/>
function PPMakeDeviceName(int a, int b, int c, int d, int RValue) 
{
	RValue:=0
}
function IoCreateDevice(int a, int RValue) 
{ 
	RValue:=2
}
function ExFreePool(int a) 
{
	skip
}
function PPBlockInits() 
{
	skip
}
function PPUnblockInits()
{
	skip
}
function RtlInitUnicodeString(int a)
{
	skip
}

function main() 
{
frame(break_1,loc_continue,tmp) and
(
  int break_1<==0 and int loc_continue<==0 and and int tmp skip;
  set := 1; 
  set := 0; 
  PPBlockInits();
  while (i < Pdolen AND !break_1 AND !loc_continue) 
  { 
	DName:=PPMakeDeviceName(lptNamei, PdoType, dcIdi, num); 
	if (!DName)then { break_1<==1 and skip}; 	
	if (!break_1)then
	{  
	RtlInitUnicodeString(DName); 	
    status := IoCreateDevice(Pdoi);
	 pc := 1; 
	 pc := 0;
     if ( status!= 1) then{ 
         Pdoi := 0; 
         if ( status=2 ) 
		 then{ 
			ExFreePool(DName); 
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
     num := 0;  
     unset:= 1; 
	 unset:=0;
	 PPUnblockInits()
  };
  tmp:=10000000;
	while(tmp>0)
	{
		tmp:=tmp-1
	}
 )
};

frame(pc,i,Pdolen, num,DName,lptNamei,dcIdi,Pdoi,PdoType,status,set,unset)and
(
int pc and
int i and int Pdolen and int num and int DName and
int lptNamei and 
int dcIdi and 
int Pdoi and 
int PdoType and int status and
int set <== 0 and int unset <== 0 skip;
main()
)

