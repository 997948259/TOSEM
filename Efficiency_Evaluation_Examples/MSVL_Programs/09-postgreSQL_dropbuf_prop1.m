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
tmp
)
and
(
int family and
char *hostName and
char *unixSocketName and
int MaxListen and
int fd, err and
int maxconn and
int one and
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
int *bufHdr and
int bufHdr_tag_blockNum and
int bufHdr_tag_rnode and
int bufHdr_tag_rnode_spcNode and
int bufHdr_tag_rnode_dbNode and
int bufHdr_tag_rnode_relNode and
int bufHdr_flags and
int bufHdr_cntxDirty and
int LocalRefCount_i and
int LocalBufferDescriptors_i and
int NLocBuffer and
int i and
int NBuffers and
int bufHdr_refcount and
int tmp and skip;

istemp := 0; 
A := 0;
RELEASE := 0;
NLocBuffer := 5;
NBuffers := 5;
main_1()
);
function main_1() {
frame(cond,my_exit,recheck)
and(
int cond and 
int my_exit<==0 and 
int recheck<==1 and skip;
	if (istemp=1)then
	{
	    i:=0;
		while(i < NLocBuffer)
		{
			bufHdr := &LocalBufferDescriptors_i;
			if (bufHdr_tag_blockNum >= firstDelBlock) then
			{
				if (LocalRefCount_i != 0) then
				{
					skip
				};
				bufHdr_flags := 0;
				bufHdr_cntxDirty := 0;
				bufHdr_tag_rnode_relNode := 1
			};
			i:=i+1
		};
		my_exit:=1
	};
	
	if(!my_exit)then
	{
	  A := 1; 
	  A := 0;
	  i:=1;
	  while(i <= NBuffers)
	  {
		bufHdr :=0;
        while(recheck)
		{
		   recheck:=0;
		   if (bufHdr_tag_blockNum >= firstDelBlock) then
		   {
			   if (bufHdr_flags)then
			   {
				 recheck:=1
			   };

			   if(!recheck)then
			   {
			       if (bufHdr_refcount != 0) then
				   {
					 skip
				   };
			        bufHdr_flags := 0;
			        bufHdr_cntxDirty := 0	   
			   }
		   }
		};
		i:=i+1
	   };

	   RELEASE := 1; RELEASE := 0
	 };
	tmp:=10000000;
    while(tmp>0)
    {
	  tmp:=tmp-1
    }
)
}
