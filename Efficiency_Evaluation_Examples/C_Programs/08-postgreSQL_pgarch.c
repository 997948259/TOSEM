//#Unsafe
// ****************************************************
//
//     Making Prophecies with Decision Predicates
//
//              Byron Cook * Eric Koskinen
//                     July 2010
//
// ****************************************************

//@ ltl invariant positive: []<>AP(wakend==1);

extern void __VERIFIER_error() __attribute__ ((__noreturn__));
extern void __VERIFIER_assume();
extern int __VERIFIER_nondet_int();

#define true 1
#define false 0
#define NULL 0
#define PGC_SIGHUP 1
#define PGARCH_AUTOWAKE_INTERVAL 1000

int last_copy_time = 0;
int curtime;
int got_SIGHUP;
int wakend;
int tmp;

void init() 
{
  wakend = 1; 
  got_SIGHUP = 0;
}

void main() {
	init();
	wakend = true;
	tmp=10;

	do
	{
		/* Check for config update */
		if (got_SIGHUP)
		{
			got_SIGHUP = false;
			if (0)
				break;                  /* user wants us to shut down */
		}
		/* Do what we're here for */
		if (wakend)
		{
			wakend = false;
			last_copy_time = 10;
		}
		if (!wakend)
		{
			curtime = 100;
			if ((unsigned int) (curtime - last_copy_time) >= (unsigned int) PGARCH_AUTOWAKE_INTERVAL)
			{
				wakend = true;
			}
		}
		tmp--;
	} while (tmp>0);

	tmp=10000000;
	while (tmp>0) {tmp=tmp-1;}
}
