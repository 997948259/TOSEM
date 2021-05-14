//#Unsafe
//@ ltl invariant positive: []<>AP(wakend==1);
</
  define p: wakend=1;
  alw(som(p))
/>

function init() 
{
  wakend := 1; 
  got_SIGHUP :=0 
};


function main() {
	init();
	wakend := 1;
	tmp:=10;
	
	while (tmp>0 AND !break_1)
	{
		/* Check for config update */
		if (got_SIGHUP)then
		{
			got_SIGHUP := 0;
			if(0) then
			{
				break_1:=1
			}
		};
		if(!break_1)then
		{
		   /* Do what we're here for */
	 	   if (wakend)then
		   {
			   wakend := 0;			
			   last_copy_time := 10
		   };
		    if (!wakend)then
		    {
			    curtime := 100;
			    if ((unsigned int) (curtime - last_copy_time) >= 1000)then
			    {
				    wakend := 1
			    }
		     };
			 tmp:=tmp-1
		}
	};
	tmp:=10000000;
    while(tmp>0)
    {
	  tmp:=tmp-1
    }
};


frame(last_copy_time,
curtime,
got_SIGHUP,
wakend,
ddd,
loop,
break_1,tmp)
and
(
int last_copy_time <== 0 and
int curtime and 
int got_SIGHUP and
int wakend and 
int ddd and 
int loop and 
int break_1 and int tmp skip;
main()
)


