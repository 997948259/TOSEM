//#Unsafe
// ****************************************************
//
//     Making Prophecies with Decision Predicates
//
//              Byron Cook * Eric Koskinen
//                     July 2010
//
// ****************************************************
 
//@ ltl invariant positive: AP(istemp==0) ==> [](AP(A!=1));

extern void __VERIFIER_error() __attribute__ ((__noreturn__));
extern void __VERIFIER_assume();
extern int __VERIFIER_nondet_int();

#include <stdio.h>
#define AF_INET 1
#define AF_INET6 2
#define AF_UNIX 3
#define __builtin___snprintf_chk(a,b,c,d,e,f) {}
#define __builtin___object_size(a,b) __VERIFIER_nondet_int()
#define BM_DIRTY 1
#define BM_JUST_DIRTIED 2
#define BM_IO_IN_PROGRESS 3

int family;
char *hostName;
char *unixSocketName;
int MaxListen;
int fd, err;
int maxconn;
int one;
char *service;
int hint;
int listen_index;
int added;
int addr_ai_family;
int addr;
int MAXADDR;
int ListenSocket_OF_listen_index;
int ret;
char *sock_path;
int addrs;
int rnode;
int istemp;
int firstDelBlock;
int A; int RELEASE;
char *bufHdr;
int bufHdr_tag_blockNum;
int bufHdr_tag_rnode;
int bufHdr_tag_rnode_spcNode;
int bufHdr_tag_rnode_dbNode;
int bufHdr_tag_rnode_relNode;
int bufHdr_flags;
int bufHdr_cntxDirty;
int bufHdr_tag_rnode_relNode;
int LocalRefCount_i;
int LocalBufferDescriptors_i;
int NLocBuffer;
int i;
int NBuffers;
int bufHdr_refcount;
int tmp;

istemp = 0;
A = 0;
RELEASE = 0;
NLocBuffer = 5;
NBuffers = 5;

void main() {
	if (istemp==1)
	{
		for (i = 0; i < NLocBuffer; i++)
		{
			bufHdr = &LocalBufferDescriptors_i;
			if ( bufHdr_tag_blockNum >= firstDelBlock)
			{
				if (LocalRefCount_i != 0) ;
				bufHdr_flags = 0;
				bufHdr_cntxDirty = 0;
				bufHdr_tag_rnode_relNode = 1;
			}
		}
		goto my_exit;
	}

	A = 1; A = 0;

	for (i = 1; i <= NBuffers; i++)
	{
		bufHdr = 0; 
recheck:
		if ( bufHdr_tag_blockNum >= firstDelBlock)
		{
			if (bufHdr_flags)
			{
				goto recheck;
			}

			if (bufHdr_refcount != 0);
			bufHdr_flags = 0;
			bufHdr_cntxDirty = 0;
		}
	}

	RELEASE = 1; RELEASE = 0; 
my_exit:
	tmp=10000000;
	while (tmp>0) {tmp=tmp-1;}
}
