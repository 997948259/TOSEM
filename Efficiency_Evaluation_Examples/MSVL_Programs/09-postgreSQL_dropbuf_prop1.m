//#Unsafe

//@ ltl invariant positive: AP(istemp==0) ==> [](AP(A!=1));
</
  define p: istemp=0;
  define q: A!=1;
  p->alw(q)
/>

frame(
family,
hostName,
portNumber,
unixSocketName,MaxListen,fd, err,
maxconn, one,ret,service,
hint,listen_index,
added, addr_ai_family,addr,MAXADDR,
ListenSocket_OF_listen_index,sock_path,
addrs,rnode,istemp,firstDelBlock,
A,RELEASE,bufHdr,bufHdr_tag_blockNum,
bufHdr_tag_rnode, bufHdr_tag_rnode_spcNode,
bufHdr_tag_rnode_dbNode,
bufHdr_flags,
bufHdr_cntxDirty,
bufHdr_tag_rnode_relNode,
LocalRefCount_i,
LocalBufferDescriptors_i,
NLocBuffer,
i,
NBuffers,
bufHdr_refcount,
BM_DIRTY,
BM_JUST_DIRTIED,
BM_IO_IN_PROGRESS
)
and
(
int family and
char *hostName and
//unsigned short portNumber and
char *unixSocketName and
int MaxListen and
int fd, err and
int maxconn and
int one and
//int ret and
char *service and
int hint and
int listen_index and
int added and
int addr_ai_family and
int addr and
int MAXADDR and
int ListenSocket_OF_listen_index and
int ret and
char *sock_path and
int addrs and
int rnode and
int istemp and
int firstDelBlock and
int A and int RELEASE and
///char *bufHdr and
int *bufHdr and
int bufHdr_tag_blockNum and
//int bufHdr_tag_blockNum and
int bufHdr_tag_rnode and
int bufHdr_tag_rnode_spcNode and
int bufHdr_tag_rnode_dbNode and
int bufHdr_tag_rnode_relNode and
int bufHdr_flags and
int bufHdr_cntxDirty and
//int bufHdr_tag_rnode_relNode and
int LocalRefCount_i and
int LocalBufferDescriptors_i and
int NLocBuffer and
int i and
int NBuffers and
int bufHdr_refcount and
int BM_DIRTY<==1 and 
int BM_JUST_DIRTIED<==2 and 
int BM_IO_IN_PROGRESS<==3 and
skip;

//void StrategyInvalidateBuffer(int bufHdr) {}
//void WaitIO(int a) {}
/*int RelFileNodeEquals(int a, int b) 
{ 
	return __VERIFIER_nondet_int(); 
}*/

istemp <== 0//__VERIFIER_nondet_int() 
and
A <== 0 and
RELEASE <== 0 and
NLocBuffer <== 5//__VERIFIER_nondet_int()
and
NBuffers <== 5//__VERIFIER_nondet_int() 
and skip;
main_1()
);
function main_1() {
frame(yyy, cond,my_exit,recheck)
and(
int yyy and 
int cond and 
int my_exit<==0 and 
int recheck<==1 and skip;
	//DD: If NBuffers is not larger than 1, the property is trivially not satisfied. So I added the following line:
	//__VERIFIER_assume(NBuffers>1);
	//end
	if (istemp=1)then
	{
	    i:=0;
		while(i < NLocBuffer)
		{
			bufHdr := &LocalBufferDescriptors_i;
			//if (RelFileNodeEquals(bufHdr_tag_rnode, rnode) && bufHdr_tag_blockNum >= firstDelBlock)
			(cond:=1 or cond:=0);
			if(cond)then
			{
				//if (LocalRefCount_i != 0) ;

				//DD: replaced the line
				//bufHdr_flags &= ~(BM_DIRTY | BM_JUST_DIRTIED);
				//with this
				bufHdr_flags := 0;
				//because x = 0 & ... is always 0 				
				//end
				bufHdr_cntxDirty := 0;
				bufHdr_tag_rnode_relNode := 1 // InvalidOid;
			};
			i:=i+1
		};
		my_exit:=1
	};
	
	if(!my_exit)then
	{

	  A := 1; 
	  A := 0; // LWLockAcquire(BufMgrLock, LW_EXCLUSIVE);

	  i:=1;
	  while( i <= NBuffers)
	  {
		bufHdr :=0;// __VERIFIER_nondet_int(); // &BufferDescriptors[i - 1];
		
        while(recheck)
		{
		   recheck:=0;
		   //if (RelFileNodeEquals(bufHdr_tag_rnode, rnode) && bufHdr_tag_blockNum >= firstDelBlock)
		   (cond:=0 or cond:=1);
		   if(cond)then
		   {
		       //DD: replaced the line
			   //if (bufHdr_flags & BM_IO_IN_PROGRESS)
			   //with this
			   if (bufHdr_flags)then
			   {
				//WaitIO(bufHdr);
				 recheck:=1
			   };

			   if(!recheck)then
			   {
			       //if (bufHdr_refcount != 0);

			       //DD: replaced the line
			       //bufHdr_flags &= ~(BM_DIRTY | BM_JUST_DIRTIED);
			       //with this
			        bufHdr_flags := 0;
			       //because x = 0 & ... is always 0 
			        //end
			        bufHdr_cntxDirty := 0

			       //StrategyInvalidateBuffer(bufHdr);			   
			   }
		   }
		};
		
		i:=i+1
	   };

	   RELEASE := 1; RELEASE := 0 //LWLockRelease(BufMgrLock);
	 }
	
)
}
