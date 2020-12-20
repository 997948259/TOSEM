//#Unsafe
//@ ltl invariant positive: []<>AP(wakend==1);
</
  define p: wakend=1;
  alw(som(p))
/>

function init() 
{
  wakend <== 1 and skip; 
  got_SIGHUP <==0 and skip //__VERIFIER_nondet_int();
};


function main() {
	init();
	/*
	 * We run the copy loop immediately upon entry, in case there are
	 * unarchived files left over from a previous database run (or maybe
	 * the archiver died unexpectedly).  After that we wait for a signal
	 * or timeout before doing more.
	 */
	wakend := 1;
	
	while (loop AND !break_1)
	{
		/* Check for config update */
		if (got_SIGHUP)then
		{
			got_SIGHUP := 0;
			(skip or 
			break_1:=1)                  /* user wants us to shut down */
		};
		if(!break_1)then
		{
		   /* Do what we're here for */
	 	   if (wakend)then
		   {
			   wakend := 0;			
			   last_copy_time := 10//time(0);
		   };
		   /*
		    * There shouldn't be anything for the archiver to do except to
	    	* wait for a signal, ... however, the archiver exists to
		    * protect our data, so she wakes up occasionally to allow
		    * herself to be proactive. In particular this avoids getting
		    * stuck if a signal arrives just before we sleep.
		    */
		    if (!wakend)then
		    {
			    curtime := 100;//time(0);
			    if ((unsigned int) (curtime - last_copy_time) >= 1000)then
			    {
				    wakend := 1
			    }
		     };
			 (loop:=0 or loop:=1)
		}
		
	}
};


frame(last_copy_time,
curtime,
got_SIGHUP,
wakend,
ddd,
loop,
break_1)
and
(
int last_copy_time <== 0 and
int curtime and 
int got_SIGHUP and
int wakend and 
int ddd and 
int loop<==1 and 
int break_1<==0 and skip;
main()
)


