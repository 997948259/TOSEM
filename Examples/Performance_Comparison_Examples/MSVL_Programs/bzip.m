/*</
define p:main_level<=11;
alw(p)
/>*/
/*</
define p:main_level>0;
som(p)
/>*/
/*</
define p:module_1=1;
define q:module_4=1;
alw(p->som(q))
/>*/
</
define p1:module_1=1;
define p2:module_2=1;
define p3:module_3=1;
define p4:module_4=1;
som(p1;(p2;p3)#)
/>
frame(temp_i,temp_j,syf,bytesIn,bytesOut,verbosity,keepInputFiles,smallMode,testFailsExist,globalCrc,numFileNames,numFilesProcessed,opMode,srcMode,longestFileName,inName,outName,progName,progNameReally,outputHandleJustInCase,block,quadrant,zptr,szptr,ftab,ll16,ll4,tt,ll8,unzftab,last,origPtr,blockSize100k,workFactor,workDone,workLimit,blockRandomised,firstAttempt,nBlocksRandomised,inUse,nInUse,seqToUnseq,unseqToSeq,selector,selectorMtf,nMTF,mtfFreq,len$,limit,base,perm,minLens,code,rfreq,crc32Table,bsBuff,bsLive,bsStream,bsWriting,incs,rNums,dbglvl,spec_fd,seedi,main_level,module_1,module_2,module_3,module_4) and (
 int module_1<==1 and skip;
 int module_2<==0 and skip;
 int module_3<==0 and skip;
 int module_4<==0 and skip;
 int syf<==0 and skip;
 int main_level<==0 and skip;
 int temp_i<==0 and skip;
 int temp_j<==0 and skip;
 function ERROR_IF_EOF ( int i )
 {
     if((i)=(-1)) then 
     {
         ioError()
     }
     else 
     {
          skip 
     }
     
 };
 function ERROR_IF_NOT_ZERO ( int i )
 {
     if(i!=0) then 
     {
         ioError()
     }
     else 
     {
          skip 
     }
     
 };
 function ERROR_IF_MINUS_ONE ( int i )
 {
     if((i)=(-1)) then 
     {
         ioError()
     }
     else 
     {
          skip 
     }
     
 };
 int bytesIn,bytesOut and skip;
 int verbosity and skip;
 unsigned char keepInputFiles,smallMode,testFailsExist and skip;
 int globalCrc and skip;
 int numFileNames<==0,numFilesProcessed<==0 and skip;
 int opMode and skip;
 int srcMode and skip;
 int longestFileName and skip;
 char inName[1024] and skip;
 char outName[1024] and skip;
 char *progName and skip;
 char progNameReally[1024] and skip;
 int outputHandleJustInCase and skip;
 unsigned char *block and skip;
 int *quadrant and skip;
 int *zptr and skip;
 int *szptr and skip;
 int *ftab and skip;
 int *ll16 and skip;
 unsigned char *ll4 and skip;
 int *tt and skip;
 unsigned char *ll8 and skip;
 int unzftab[256] and skip;
 int last and skip;
 int origPtr and skip;
 int blockSize100k and skip;
 int workFactor and skip;
 int workDone and skip;
 int workLimit and skip;
 unsigned char blockRandomised and skip;
 unsigned char firstAttempt and skip;
 int nBlocksRandomised and skip;
 unsigned char inUse[256] and skip;
 int nInUse and skip;
 unsigned char seqToUnseq[256] and skip;
 unsigned char unseqToSeq[256] and skip;
 unsigned char selector[(2+(900000/ 50))] and skip;
 unsigned char selectorMtf[(2+(900000/ 50))] and skip;
 int nMTF and skip;
 int mtfFreq[258] and skip;
 unsigned char len$[6,258] and skip;
 int limit[6,258] and skip;
 int base[6,258] and skip;
 int perm[6,258] and skip;
 int minLens[6] and skip;
 int code[6,258] and skip;
 int rfreq[6,258] and skip;
 int crc32Table[256]<=={0x00000000,0x04c11db7,0x09823b6e,0x0d4326d9,0x130476dc,0x17c56b6b,0x1a864db2,0x1e475005,0x2608edb8,0x22c9f00f,0x2f8ad6d6,0x2b4bcb61,0x350c9b64,0x31cd86d3,0x3c8ea00a,0x384fbdbd,0x4c11db70,0x48d0c6c7,0x4593e01e,0x4152fda9,0x5f15adac,0x5bd4b01b,0x569796c2,0x52568b75,0x6a1936c8,0x6ed82b7f,0x639b0da6,0x675a1011,0x791d4014,0x7ddc5da3,0x709f7b7a,0x745e66cd,0x9823b6e0,0x9ce2ab57,0x91a18d8e,0x95609039,0x8b27c03c,0x8fe6dd8b,0x82a5fb52,0x8664e6e5,0xbe2b5b58,0xbaea46ef,0xb7a96036,0xb3687d81,0xad2f2d84,0xa9ee3033,0xa4ad16ea,0xa06c0b5d,0xd4326d90,0xd0f37027,0xddb056fe,0xd9714b49,0xc7361b4c,0xc3f706fb,0xceb42022,0xca753d95,0xf23a8028,0xf6fb9d9f,0xfbb8bb46,0xff79a6f1,0xe13ef6f4,0xe5ffeb43,0xe8bccd9a,0xec7dd02d,0x34867077,0x30476dc0,0x3d044b19,0x39c556ae,0x278206ab,0x23431b1c,0x2e003dc5,0x2ac12072,0x128e9dcf,0x164f8078,0x1b0ca6a1,0x1fcdbb16,0x018aeb13,0x054bf6a4,0x0808d07d,0x0cc9cdca,0x7897ab07,0x7c56b6b0,0x71159069,0x75d48dde,0x6b93dddb,0x6f52c06c,0x6211e6b5,0x66d0fb02,0x5e9f46bf,0x5a5e5b08,0x571d7dd1,0x53dc6066,0x4d9b3063,0x495a2dd4,0x44190b0d,0x40d816ba,0xaca5c697,0xa864db20,0xa527fdf9,0xa1e6e04e,0xbfa1b04b,0xbb60adfc,0xb6238b25,0xb2e29692,0x8aad2b2f,0x8e6c3698,0x832f1041,0x87ee0df6,0x99a95df3,0x9d684044,0x902b669d,0x94ea7b2a,0xe0b41de7,0xe4750050,0xe9362689,0xedf73b3e,0xf3b06b3b,0xf771768c,0xfa325055,0xfef34de2,0xc6bcf05f,0xc27dede8,0xcf3ecb31,0xcbffd686,0xd5b88683,0xd1799b34,0xdc3abded,0xd8fba05a,0x690ce0ee,0x6dcdfd59,0x608edb80,0x644fc637,0x7a089632,0x7ec98b85,0x738aad5c,0x774bb0eb,0x4f040d56,0x4bc510e1,0x46863638,0x42472b8f,0x5c007b8a,0x58c1663d,0x558240e4,0x51435d53,0x251d3b9e,0x21dc2629,0x2c9f00f0,0x285e1d47,0x36194d42,0x32d850f5,0x3f9b762c,0x3b5a6b9b,0x0315d626,0x07d4cb91,0x0a97ed48,0x0e56f0ff,0x1011a0fa,0x14d0bd4d,0x19939b94,0x1d528623,0xf12f560e,0xf5ee4bb9,0xf8ad6d60,0xfc6c70d7,0xe22b20d2,0xe6ea3d65,0xeba91bbc,0xef68060b,0xd727bbb6,0xd3e6a601,0xdea580d8,0xda649d6f,0xc423cd6a,0xc0e2d0dd,0xcda1f604,0xc960ebb3,0xbd3e8d7e,0xb9ff90c9,0xb4bcb610,0xb07daba7,0xae3afba2,0xaafbe615,0xa7b8c0cc,0xa379dd7b,0x9b3660c6,0x9ff77d71,0x92b45ba8,0x9675461f,0x8832161a,0x8cf30bad,0x81b02d74,0x857130c3,0x5d8a9099,0x594b8d2e,0x5408abf7,0x50c9b640,0x4e8ee645,0x4a4ffbf2,0x470cdd2b,0x43cdc09c,0x7b827d21,0x7f436096,0x7200464f,0x76c15bf8,0x68860bfd,0x6c47164a,0x61043093,0x65c52d24,0x119b4be9,0x155a565e,0x18197087,0x1cd86d30,0x029f3d35,0x065e2082,0x0b1d065b,0x0fdc1bec,0x3793a651,0x3352bbe6,0x3e119d3f,0x3ad08088,0x2497d08d,0x2056cd3a,0x2d15ebe3,0x29d4f654,0xc5a92679,0xc1683bce,0xcc2b1d17,0xc8ea00a0,0xd6ad50a5,0xd26c4d12,0xdf2f6bcb,0xdbee767c,0xe3a1cbc1,0xe760d676,0xea23f0af,0xeee2ed18,0xf0a5bd1d,0xf464a0aa,0xf9278673,0xfde69bc4,0x89b8fd09,0x8d79e0be,0x803ac667,0x84fbdbd0,0x9abc8bd5,0x9e7d9662,0x933eb0bb,0x97ffad0c,0xafb010b1,0xab710d06,0xa6322bdf,0xa2f33668,0xbcb4666d,0xb8757bda,0xb5365d03,0xb1f740b4} and skip;
 function initialiseCRC (  )
 {
     globalCrc:=0xffffffff
     
 };
 function getFinalCRC ( int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and RValue:=~globalCrc;
     skip
     )
     }; 
  function getGlobalCRC ( int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and RValue:=globalCrc;
     skip
     )
     }; 
  function setGlobalCRC ( int newCrc )
 {
     globalCrc:=newCrc
     
 };
 int bsBuff and skip;
 int bsLive and skip;
 int bsStream and skip;
 unsigned char bsWriting and skip;
 function bsSetStream ( int f,unsigned char wr )
 {
     bsStream:=f;
     bsLive:=0;
     bsBuff:=0;
     bytesOut:=0;
     bytesIn:=0;
     bsWriting:=wr
     
 };
 function bsFinishedWithStream (  )
 {
     if(bsWriting) then 
     {
         while(bsLive>0)
         {
             spec_putc((unsigned char)(bsBuff>>24),bsStream,RValue);
             bsBuff:=bsBuff<< (8 );
             bsLive:=bsLive-8;
             bytesOut:=bytesOut+1
         }
     }
     else 
     {
          skip 
     };
     bsStream:=0
     
 };
 function bsR ( int n,int RValue )
 {
     frame(bsR_v,bsR_1_zzi,return) and ( 
     int return<==0 and skip;
     int bsR_v and skip;
     while(bsLive<n)
     {
         int bsR_1_zzi and skip;
         bsR_1_zzi:=spec_getc(bsStream,RValue);
         if((bsR_1_zzi)=(-1)) then 
         {
             compressedStreamEOF()
         }
         else 
         {
              skip 
         };
         bsBuff:=(bsBuff<<8) | (bsR_1_zzi & 255);
         bsLive:=bsLive+8
     };
     bsR_v:=(bsBuff>>(bsLive-n)) & ((1<<n)-1);
     bsLive:=bsLive-n;
     return<==1 and RValue:=bsR_v;
     skip
     )
     }; 
  function bsW ( int n,int v )
 {
     while(bsLive>=8)
     {
         spec_putc((unsigned char)(bsBuff>>24),bsStream,RValue);
         bsBuff:=bsBuff<< (8 );
         bsLive:=bsLive-8;
         bytesOut:=bytesOut+1
     };
     bsBuff:=bsBuff| (v<<(32-bsLive-n));
     bsLive:=bsLive+n
     
 };
 function bsGetUChar ( unsigned char RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and RValue:=(unsigned char)bsR(8,RValue);
     skip
     )
     }; 
  function bsPutUChar ( unsigned char c )
 {
     bsW(8,(unsigned int)c)
     
 };
 function bsGetUInt32 ( int RValue )
 {
     frame(bsGetUInt32_u,return) and ( 
     int return<==0 and skip;
     int bsGetUInt32_u and skip;
     bsGetUInt32_u:=0;
     bsGetUInt32_u:=(bsGetUInt32_u<<8) | bsR(8,RValue);
     bsGetUInt32_u:=(bsGetUInt32_u<<8) | bsR(8,RValue);
     bsGetUInt32_u:=(bsGetUInt32_u<<8) | bsR(8,RValue);
     bsGetUInt32_u:=(bsGetUInt32_u<<8) | bsR(8,RValue);
     return<==1 and RValue:=bsGetUInt32_u;
     skip
     )
     }; 
  function bsGetIntVS ( int numBits,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and RValue:=(unsigned int)bsR(numBits,RValue);
     skip
     )
     }; 
  function bsGetInt32 ( int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and RValue:=(int)bsGetUInt32(RValue);
     skip
     )
     }; 
  function bsPutUInt32 ( int u )
 {
     bsW(8,(u>>24) & 255);
     bsW(8,(u>>16) & 255);
     bsW(8,(u>>8) & 255);
     bsW(8,u & 255)
     
 };
 function bsPutInt32 ( int c )
 {
     bsPutUInt32((unsigned int)c)
     
 };
 function bsPutIntVS ( int numBits,int c )
 {
     bsW(numBits,c)
     
 };
 function hbMakeCodeLengths ( unsigned char *len$,int *freq,int alphaSize,int maxLen )
 {
     frame(hbMakeCodeLengths_nNodes,hbMakeCodeLengths_nHeap,hbMakeCodeLengths_n1,hbMakeCodeLengths_n2,hbMakeCodeLengths_i,hbMakeCodeLengths_j,hbMakeCodeLengths_k,hbMakeCodeLengths_tooLong,hbMakeCodeLengths_heap,hbMakeCodeLengths_weight,hbMakeCodeLengths_parent,hbMakeCodeLengths_2_zz,hbMakeCodeLengths_2_tmp,hbMakeCodeLengths_2_5_zz,hbMakeCodeLengths_2_5_yy,hbMakeCodeLengths_2_5_tmp,break$$) and ( 
     int break$$<==0 and skip;
     int hbMakeCodeLengths_nNodes,hbMakeCodeLengths_nHeap,hbMakeCodeLengths_n1,hbMakeCodeLengths_n2,hbMakeCodeLengths_i,hbMakeCodeLengths_j,hbMakeCodeLengths_k and skip;
     unsigned char hbMakeCodeLengths_tooLong and skip;
     int hbMakeCodeLengths_heap[258+2] and skip;
     int hbMakeCodeLengths_weight[258*2] and skip;
     int hbMakeCodeLengths_parent[258*2] and skip;
     hbMakeCodeLengths_i:=0;
     
     while(hbMakeCodeLengths_i<alphaSize)
     {
         hbMakeCodeLengths_weight[hbMakeCodeLengths_i+1]:=(( if(freq[hbMakeCodeLengths_i]=0) then 1 else freq[hbMakeCodeLengths_i]))<<8;
         hbMakeCodeLengths_i:=hbMakeCodeLengths_i+1
         
     };
     break$$<==0 and skip;
     while( break$$=0 AND 1)
     {
         hbMakeCodeLengths_nNodes:=alphaSize;
         hbMakeCodeLengths_nHeap:=0;
         hbMakeCodeLengths_heap[0]:=0;
         hbMakeCodeLengths_weight[0]:=0;
         hbMakeCodeLengths_parent[0]:=-2;
         hbMakeCodeLengths_i:=1;
         
         while(hbMakeCodeLengths_i<=alphaSize)
         {
             hbMakeCodeLengths_parent[hbMakeCodeLengths_i]:=-1;
             hbMakeCodeLengths_nHeap:=hbMakeCodeLengths_nHeap+1;
             hbMakeCodeLengths_heap[hbMakeCodeLengths_nHeap]:=hbMakeCodeLengths_i;
             int hbMakeCodeLengths_2_zz,hbMakeCodeLengths_2_tmp and skip;
             hbMakeCodeLengths_2_zz:=hbMakeCodeLengths_nHeap;
             hbMakeCodeLengths_2_tmp:=hbMakeCodeLengths_heap[hbMakeCodeLengths_2_zz];
             while(hbMakeCodeLengths_weight[hbMakeCodeLengths_2_tmp]<hbMakeCodeLengths_weight[hbMakeCodeLengths_heap[hbMakeCodeLengths_2_zz>>1]])
             {
                 hbMakeCodeLengths_heap[hbMakeCodeLengths_2_zz]:=hbMakeCodeLengths_heap[hbMakeCodeLengths_2_zz>>1];
                 hbMakeCodeLengths_2_zz:=hbMakeCodeLengths_2_zz>> (1 )
             };
             hbMakeCodeLengths_heap[hbMakeCodeLengths_2_zz]:=hbMakeCodeLengths_2_tmp;
             hbMakeCodeLengths_i:=hbMakeCodeLengths_i+1
             
         };
         if(!(hbMakeCodeLengths_nHeap<(258+2))) then 
         {
             panic("hbMakeCodeLengths(1)")
         }
         else 
         {
              skip 
         };
         while(hbMakeCodeLengths_nHeap>1)
         {
             hbMakeCodeLengths_n1:=hbMakeCodeLengths_heap[1];
             hbMakeCodeLengths_heap[1]:=hbMakeCodeLengths_heap[hbMakeCodeLengths_nHeap];
             hbMakeCodeLengths_nHeap:=hbMakeCodeLengths_nHeap-1;
             int hbMakeCodeLengths_2_5_zz,hbMakeCodeLengths_2_5_yy,hbMakeCodeLengths_2_5_tmp and skip;
             hbMakeCodeLengths_2_5_zz:=1;
             hbMakeCodeLengths_2_5_tmp:=hbMakeCodeLengths_heap[hbMakeCodeLengths_2_5_zz];
             break$$<==0 and skip;
             while( break$$=0 AND  1)
             {
                 hbMakeCodeLengths_2_5_yy:=hbMakeCodeLengths_2_5_zz<<1;
                 if(hbMakeCodeLengths_2_5_yy>hbMakeCodeLengths_nHeap) then 
                 {
                     break$$<==1 and skip
                  }
                 else 
                 {
                      skip 
                 };
                 if(break$$=0)   then
                 {
                     if(hbMakeCodeLengths_2_5_yy<hbMakeCodeLengths_nHeap AND hbMakeCodeLengths_weight[hbMakeCodeLengths_heap[hbMakeCodeLengths_2_5_yy+1]]<hbMakeCodeLengths_weight[hbMakeCodeLengths_heap[hbMakeCodeLengths_2_5_yy]]) then 
                     {
                         hbMakeCodeLengths_2_5_yy:=hbMakeCodeLengths_2_5_yy+1
                     }
                     else 
                     {
                          skip 
                     };
                     if(hbMakeCodeLengths_weight[hbMakeCodeLengths_2_5_tmp]<hbMakeCodeLengths_weight[hbMakeCodeLengths_heap[hbMakeCodeLengths_2_5_yy]]) then 
                     {
                         break$$<==1 and skip
                      }
                     else 
                     {
                          skip 
                     };
                     if(break$$=0)   then
                     {
                         hbMakeCodeLengths_heap[hbMakeCodeLengths_2_5_zz]:=hbMakeCodeLengths_heap[hbMakeCodeLengths_2_5_yy];
                         hbMakeCodeLengths_2_5_zz:=hbMakeCodeLengths_2_5_yy
                     }
                     else
                     {
                         skip
                     }
                 }
                 else
                 {
                     skip
                 }
             };
             break$$<==0 and skip;
             hbMakeCodeLengths_heap[hbMakeCodeLengths_2_5_zz]:=hbMakeCodeLengths_2_5_tmp;
             hbMakeCodeLengths_n2:=hbMakeCodeLengths_heap[1];
             hbMakeCodeLengths_heap[1]:=hbMakeCodeLengths_heap[hbMakeCodeLengths_nHeap];
             hbMakeCodeLengths_nHeap:=hbMakeCodeLengths_nHeap-1;
             hbMakeCodeLengths_2_5_zz:=1;
             hbMakeCodeLengths_2_5_tmp:=hbMakeCodeLengths_heap[hbMakeCodeLengths_2_5_zz];
             break$$<==0 and skip;
             while( break$$=0 AND  1)
             {
                 hbMakeCodeLengths_2_5_yy:=hbMakeCodeLengths_2_5_zz<<1;
                 if(hbMakeCodeLengths_2_5_yy>hbMakeCodeLengths_nHeap) then 
                 {
                     break$$<==1 and skip
                  }
                 else 
                 {
                      skip 
                 };
                 if(break$$=0)   then
                 {
                     if(hbMakeCodeLengths_2_5_yy<hbMakeCodeLengths_nHeap AND hbMakeCodeLengths_weight[hbMakeCodeLengths_heap[hbMakeCodeLengths_2_5_yy+1]]<hbMakeCodeLengths_weight[hbMakeCodeLengths_heap[hbMakeCodeLengths_2_5_yy]]) then 
                     {
                         hbMakeCodeLengths_2_5_yy:=hbMakeCodeLengths_2_5_yy+1
                     }
                     else 
                     {
                          skip 
                     };
                     if(hbMakeCodeLengths_weight[hbMakeCodeLengths_2_5_tmp]<hbMakeCodeLengths_weight[hbMakeCodeLengths_heap[hbMakeCodeLengths_2_5_yy]]) then 
                     {
                         break$$<==1 and skip
                      }
                     else 
                     {
                          skip 
                     };
                     if(break$$=0)   then
                     {
                         hbMakeCodeLengths_heap[hbMakeCodeLengths_2_5_zz]:=hbMakeCodeLengths_heap[hbMakeCodeLengths_2_5_yy];
                         hbMakeCodeLengths_2_5_zz:=hbMakeCodeLengths_2_5_yy
                     }
                     else
                     {
                         skip
                     }
                 }
                 else
                 {
                     skip
                 }
             };
             break$$<==0 and skip;
             hbMakeCodeLengths_heap[hbMakeCodeLengths_2_5_zz]:=hbMakeCodeLengths_2_5_tmp;
             hbMakeCodeLengths_nNodes:=hbMakeCodeLengths_nNodes+1;
             hbMakeCodeLengths_parent[hbMakeCodeLengths_n2]<==hbMakeCodeLengths_nNodes and hbMakeCodeLengths_parent[hbMakeCodeLengths_n1]<==hbMakeCodeLengths_parent[hbMakeCodeLengths_n2] and skip;
             hbMakeCodeLengths_weight[hbMakeCodeLengths_nNodes]:=(((hbMakeCodeLengths_weight[hbMakeCodeLengths_n1]) & 0xffffff00)+((hbMakeCodeLengths_weight[hbMakeCodeLengths_n2]) & 0xffffff00)) | (( if(1+(((hbMakeCodeLengths_weight[hbMakeCodeLengths_n1]) & 0x000000ff))>((hbMakeCodeLengths_weight[hbMakeCodeLengths_n2]) & 0x000000ff)) then ((hbMakeCodeLengths_weight[hbMakeCodeLengths_n1]) & 0x000000ff) else ((hbMakeCodeLengths_weight[hbMakeCodeLengths_n2]) & 0x000000ff)));
             hbMakeCodeLengths_parent[hbMakeCodeLengths_nNodes]:=-1;
             hbMakeCodeLengths_nHeap:=hbMakeCodeLengths_nHeap+1;
             hbMakeCodeLengths_heap[hbMakeCodeLengths_nHeap]:=hbMakeCodeLengths_nNodes;
             hbMakeCodeLengths_2_5_zz:=hbMakeCodeLengths_nHeap;
             hbMakeCodeLengths_2_5_tmp:=hbMakeCodeLengths_heap[hbMakeCodeLengths_2_5_zz];
             while(hbMakeCodeLengths_weight[hbMakeCodeLengths_2_5_tmp]<hbMakeCodeLengths_weight[hbMakeCodeLengths_heap[hbMakeCodeLengths_2_5_zz>>1]])
             {
                 hbMakeCodeLengths_heap[hbMakeCodeLengths_2_5_zz]:=hbMakeCodeLengths_heap[hbMakeCodeLengths_2_5_zz>>1];
                 hbMakeCodeLengths_2_5_zz:=hbMakeCodeLengths_2_5_zz>> (1 )
             };
             hbMakeCodeLengths_heap[hbMakeCodeLengths_2_5_zz]:=hbMakeCodeLengths_2_5_tmp
         };
         if(!(hbMakeCodeLengths_nNodes<(258*2))) then 
         {
             panic("hbMakeCodeLengths(2)")
         }
         else 
         {
              skip 
         };
         hbMakeCodeLengths_tooLong:=0;
         hbMakeCodeLengths_i:=1;
         
         while(hbMakeCodeLengths_i<=alphaSize)
         {
             hbMakeCodeLengths_j:=0;
             hbMakeCodeLengths_k:=hbMakeCodeLengths_i;
             while(hbMakeCodeLengths_parent[hbMakeCodeLengths_k]>=0)
             {
                 hbMakeCodeLengths_k:=hbMakeCodeLengths_parent[hbMakeCodeLengths_k];
                 hbMakeCodeLengths_j:=hbMakeCodeLengths_j+1
             };
             len$[hbMakeCodeLengths_i-1]:=hbMakeCodeLengths_j;
             if(hbMakeCodeLengths_j>maxLen) then 
             {
                 hbMakeCodeLengths_tooLong:=1
             }
             else 
             {
                  skip 
             };
             hbMakeCodeLengths_i:=hbMakeCodeLengths_i+1
             
         };
         if(!hbMakeCodeLengths_tooLong) then 
         {
             break$$<==1 and skip
          }
         else 
         {
              skip 
         };
         if(break$$=0)   then
         {
             hbMakeCodeLengths_i:=1;
             
             while(hbMakeCodeLengths_i<alphaSize)
             {
                 hbMakeCodeLengths_j:=hbMakeCodeLengths_weight[hbMakeCodeLengths_i]>>8;
                 hbMakeCodeLengths_j:=1+(hbMakeCodeLengths_j/ 2);
                 hbMakeCodeLengths_weight[hbMakeCodeLengths_i]:=hbMakeCodeLengths_j<<8;
                 hbMakeCodeLengths_i:=hbMakeCodeLengths_i+1
                 
             }
         }
         else
         {
             skip
         }
     };
     break$$<==0 and skip
     )
     }; 
  function hbAssignCodes ( int *code,unsigned char *length,int minLen,int maxLen,int alphaSize )
 {
     frame(hbAssignCodes_n,hbAssignCodes_vec,hbAssignCodes_i) and ( 
     int hbAssignCodes_n,hbAssignCodes_vec,hbAssignCodes_i and skip;
     hbAssignCodes_vec:=0;
     hbAssignCodes_n:=minLen;
     
     while(hbAssignCodes_n<=maxLen)
     {
         hbAssignCodes_i:=0;
         
         while(hbAssignCodes_i<alphaSize)
         {
             if(length[hbAssignCodes_i]=hbAssignCodes_n) then 
             {
                 code[hbAssignCodes_i]:=hbAssignCodes_vec;
                 hbAssignCodes_vec:=hbAssignCodes_vec+1
                 
             }
             else 
             {
                  skip 
             };
             hbAssignCodes_i:=hbAssignCodes_i+1
             
         };
         hbAssignCodes_vec:=hbAssignCodes_vec<< (1 );
         hbAssignCodes_n:=hbAssignCodes_n+1
         
     }
     )
     }; 
  function hbCreateDecodeTables ( int *limit,int *base,int *perm,unsigned char *length,int minLen,int maxLen,int alphaSize )
 {
     frame(hbCreateDecodeTables_pp,hbCreateDecodeTables_i,hbCreateDecodeTables_j,hbCreateDecodeTables_vec) and ( 
     int hbCreateDecodeTables_pp,hbCreateDecodeTables_i,hbCreateDecodeTables_j,hbCreateDecodeTables_vec and skip;
     hbCreateDecodeTables_pp:=0;
     hbCreateDecodeTables_i:=minLen;
     
     while(hbCreateDecodeTables_i<=maxLen)
     {
         hbCreateDecodeTables_j:=0;
         
         while(hbCreateDecodeTables_j<alphaSize)
         {
             if(length[hbCreateDecodeTables_j]=hbCreateDecodeTables_i) then 
             {
                 perm[hbCreateDecodeTables_pp]:=hbCreateDecodeTables_j;
                 hbCreateDecodeTables_pp:=hbCreateDecodeTables_pp+1
                 
             }
             else 
             {
                  skip 
             };
             hbCreateDecodeTables_j:=hbCreateDecodeTables_j+1
             
         };
         hbCreateDecodeTables_i:=hbCreateDecodeTables_i+1
         
     };
     hbCreateDecodeTables_i:=0;
     
     while(hbCreateDecodeTables_i<23)
     {
         base[hbCreateDecodeTables_i]:=0;
         hbCreateDecodeTables_i:=hbCreateDecodeTables_i+1
         
     };
     hbCreateDecodeTables_i:=0;
     
     while(hbCreateDecodeTables_i<alphaSize)
     {
         base[length[hbCreateDecodeTables_i]+1]:=base[length[hbCreateDecodeTables_i]+1]+1;
         hbCreateDecodeTables_i:=hbCreateDecodeTables_i+1
         
     };
     hbCreateDecodeTables_i:=1;
     
     while(hbCreateDecodeTables_i<23)
     {
         base[hbCreateDecodeTables_i]:=base[hbCreateDecodeTables_i]+base[hbCreateDecodeTables_i-1];
         hbCreateDecodeTables_i:=hbCreateDecodeTables_i+1
         
     };
     hbCreateDecodeTables_i:=0;
     
     while(hbCreateDecodeTables_i<23)
     {
         limit[hbCreateDecodeTables_i]:=0;
         hbCreateDecodeTables_i:=hbCreateDecodeTables_i+1
         
     };
     hbCreateDecodeTables_vec:=0;
     hbCreateDecodeTables_i:=minLen;
     
     while(hbCreateDecodeTables_i<=maxLen)
     {
         hbCreateDecodeTables_vec:=hbCreateDecodeTables_vec+(base[hbCreateDecodeTables_i+1]-base[hbCreateDecodeTables_i]);
         limit[hbCreateDecodeTables_i]:=hbCreateDecodeTables_vec-1;
         hbCreateDecodeTables_vec:=hbCreateDecodeTables_vec<< (1 );
         hbCreateDecodeTables_i:=hbCreateDecodeTables_i+1
         
     };
     hbCreateDecodeTables_i:=minLen+1;
     
     while(hbCreateDecodeTables_i<=maxLen)
     {
         base[hbCreateDecodeTables_i]:=((limit[hbCreateDecodeTables_i-1]+1)<<1)-base[hbCreateDecodeTables_i];
         hbCreateDecodeTables_i:=hbCreateDecodeTables_i+1
         
     }
     )
     }; 
  function SET_LL4 (int i ,int n )
 {
     if((i & 1)=0) then 
     {
         ll4[i>>1]:=(ll4[i>>1] & 240) | n
     }
     else
     {
         ll4[i>>1]:=(ll4[i>>1] & 15) | (n<<4)
     }
     
 };
 function allocateCompressStructures (  )
 {
     frame(allocateCompressStructures_n,allocateCompressStructures_1_totalDraw) and ( 
     int allocateCompressStructures_n<==100000*blockSize100k and skip;
	 //output("yubin0\n") and skip;
     block:=malloc((allocateCompressStructures_n+1+20)*sizeof(unsigned char));
	 //output("yubin1\n") and skip;
     quadrant:=malloc((allocateCompressStructures_n+20)*4);
	 //output("yubin2\n") and skip;
     zptr:=malloc(allocateCompressStructures_n*sizeof(int));
	 //output("yubin3\n") and skip;
     ftab:=malloc(65537*sizeof(int));
     if(block=NULL OR quadrant=NULL OR zptr=NULL OR ftab=NULL) then 
     {
         int allocateCompressStructures_1_totalDraw<==(allocateCompressStructures_n+1+20)*1+(allocateCompressStructures_n+20)*4+allocateCompressStructures_n*4+65537*4 and skip;
         compressOutOfMemory(allocateCompressStructures_1_totalDraw,allocateCompressStructures_n)
         
     }
     else 
     {
          skip 
     };
     block:=block+1;
     szptr:=(int *)zptr
     )
     }; 
  function setDecompressStructureSizes ( int newSize100k )
 {
     frame(setDecompressStructureSizes_8_n,setDecompressStructureSizes_8_9_totalDraw,setDecompressStructureSizes_10_n,setDecompressStructureSizes_10_11_int,return) and ( 
     int return<==0 and skip;
     if(!(0<=newSize100k AND newSize100k<=9 AND 0<=blockSize100k AND blockSize100k<=9)) then 
     {
         panic("setDecompressStructureSizes")
     }
     else 
     {
          skip 
     };
     if(newSize100k=blockSize100k) then 
     {
          return<==1 and skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         blockSize100k:=newSize100k;
         if(ll16!=NULL) then 
         {
             free(ll16) and skip
         }
         else 
         {
              skip 
         };
         if(ll4!=NULL) then 
         {
             free(ll4) and skip
         }
         else 
         {
              skip 
         };
         if(ll8!=NULL) then 
         {
             free(ll8) and skip
         }
         else 
         {
              skip 
         };
         if(tt!=NULL) then 
         {
             free(tt) and skip
         }
         else 
         {
              skip 
         };
         if(newSize100k=0) then 
         {
              return<==1 and skip
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             if(smallMode) then 
             {
                 int setDecompressStructureSizes_8_n<==100000*newSize100k and skip;
				 //output("yubin4\n") and skip;
                 ll16:=malloc(setDecompressStructureSizes_8_n*sizeof(unsigned int));
				 //output("yubin5\n") and skip;
                 ll4:=malloc(((setDecompressStructureSizes_8_n+1)>>1)*sizeof(unsigned char));
                 if(ll4=NULL OR ll16=NULL) then 
                 {
                     int setDecompressStructureSizes_8_9_totalDraw<==setDecompressStructureSizes_8_n*4+((setDecompressStructureSizes_8_n+1)>>1)*1 and skip;
                     uncompressOutOfMemory(setDecompressStructureSizes_8_9_totalDraw,setDecompressStructureSizes_8_n)
                     
                 }
                 else 
                 {
                      skip 
                 }
             }
             else
             {
                 int setDecompressStructureSizes_10_n<==100000*newSize100k and skip;
				 //output("yubin6\n") and skip;
                 ll8:=malloc(setDecompressStructureSizes_10_n*sizeof(unsigned char));
				 //output("yubin7\n") and skip;
                 tt:=malloc(setDecompressStructureSizes_10_n*sizeof(int));
				 //output("yubin7555\n") and skip;
				 
                 if(ll8=NULL OR tt=NULL) then 
                 {
                     int setDecompressStructureSizes_10_11_totalDraw<==setDecompressStructureSizes_10_n*1+setDecompressStructureSizes_10_n*sizeof(unsigned int) and skip;
                     uncompressOutOfMemory(setDecompressStructureSizes_10_11_totalDraw,setDecompressStructureSizes_10_n)
                     
                 }
                 else 
                 {
                      skip 
                 }
             }
         }
         else
         {
             skip
         }
     }
     else
     {
         skip
     }
     )
     }; 
  function makeMaps (  )
 {
     frame(makeMaps_i) and ( 
     int makeMaps_i and skip;
     nInUse:=0;
     makeMaps_i:=0;
     
     while(makeMaps_i<256)
     {
         if(inUse[makeMaps_i]) then 
         {
             seqToUnseq[nInUse]:=makeMaps_i;
             unseqToSeq[makeMaps_i]:=nInUse;
             nInUse:=nInUse+1
             
         }
         else 
         {
              skip 
         };
         makeMaps_i:=makeMaps_i+1
         
     }
     )
     }; 
  function generateMTFValues (  )
 {
     frame(generateMTFValues_yy,generateMTFValues_i,generateMTFValues_j,generateMTFValues_tmp,generateMTFValues_tmp2,generateMTFValues_zPend,generateMTFValues_wr,generateMTFValues_EOB,generateMTFValues_ll_i,nm_1$,break$$$,switch$,nm_2$,return,break$$) and ( 
     int break$$<==0 and skip;
     int return<==0 and skip;
     unsigned char generateMTFValues_yy[256] and skip;
     int generateMTFValues_i,generateMTFValues_j and skip;
     unsigned char generateMTFValues_tmp and skip;
     unsigned char generateMTFValues_tmp2 and skip;
     int generateMTFValues_zPend and skip;
     int generateMTFValues_wr and skip;
     int generateMTFValues_EOB and skip;
     makeMaps();
     generateMTFValues_EOB:=nInUse+1;
     generateMTFValues_i:=0;
     
     while(generateMTFValues_i<=generateMTFValues_EOB)
     {
         mtfFreq[generateMTFValues_i]:=0;
         generateMTFValues_i:=generateMTFValues_i+1
         
     };
     generateMTFValues_wr:=0;
     generateMTFValues_zPend:=0;
     generateMTFValues_i:=0;
     
     while(generateMTFValues_i<nInUse)
     {
         generateMTFValues_yy[generateMTFValues_i]:=(unsigned char)generateMTFValues_i;
         generateMTFValues_i:=generateMTFValues_i+1
         
     };
     generateMTFValues_i:=0;
     
     while(generateMTFValues_i<=last)
     {
         unsigned char generateMTFValues_ll_i and skip;
         generateMTFValues_ll_i:=unseqToSeq[block[zptr[generateMTFValues_i]-1]];
         generateMTFValues_j:=0;
         generateMTFValues_tmp:=generateMTFValues_yy[generateMTFValues_j];
         while(generateMTFValues_ll_i!=generateMTFValues_tmp)
         {
             generateMTFValues_j:=generateMTFValues_j+1;
             generateMTFValues_tmp2:=generateMTFValues_tmp;
             generateMTFValues_tmp:=generateMTFValues_yy[generateMTFValues_j];
             generateMTFValues_yy[generateMTFValues_j]:=generateMTFValues_tmp2
         };
         generateMTFValues_yy[0]:=generateMTFValues_tmp;
         if(generateMTFValues_j=0) then 
         {
             generateMTFValues_zPend:=generateMTFValues_zPend+1
             
         }
         else
         {
             if(generateMTFValues_zPend>0) then 
             {
                 generateMTFValues_zPend:=generateMTFValues_zPend-1;
                 break$$<==0 and skip;
                 while( break$$=0 AND  1)
                 {
                     int switch$ and skip;
                     int break$$$ and skip;
                     break$$$<==0 and skip;
                      switch$<==0 and skip;
                      int nm_1$ and skip;
                     nm_1$ := generateMTFValues_zPend % 2;
                     if (nm_1$=0 OR (switch$=1 AND break$$$=0 AND return=0) ) then 
                     {
                         switch$<==1 and skip;
                         szptr[generateMTFValues_wr]:=0;
                         generateMTFValues_wr:=generateMTFValues_wr+1;
                         mtfFreq[0]:=mtfFreq[0]+1;
                         break$$$<==1 and skip
                          
                     }
                     else
                     {
                         skip
                     };
                     if (nm_1$=1 OR (switch$=1 AND break$$$=0 AND return=0) ) then 
                     {
                         switch$<==1 and skip;
                         szptr[generateMTFValues_wr]:=1;
                         generateMTFValues_wr:=generateMTFValues_wr+1;
                         mtfFreq[1]:=mtfFreq[1]+1;
                         break$$$<==1 and skip
                          
                     }
                     else
                     {
                         skip
                     };
                     if(generateMTFValues_zPend<2) then 
                     {
                         break$$<==1 and skip
                      }
                     else 
                     {
                          skip 
                     };
                     if(break$$=0)   then
                     {
                         generateMTFValues_zPend:=(generateMTFValues_zPend-2)/ 2
                     }
                     else
                     {
                         skip
                     }
                 };
                 break$$<==0 and skip;
                 generateMTFValues_zPend:=0
                 
             }
             else 
             {
                  skip 
             };
             szptr[generateMTFValues_wr]:=generateMTFValues_j+1;
             generateMTFValues_wr:=generateMTFValues_wr+1;
             mtfFreq[generateMTFValues_j+1]:=mtfFreq[generateMTFValues_j+1]+1
         };
         generateMTFValues_i:=generateMTFValues_i+1
         
     };
     if(generateMTFValues_zPend>0) then 
     {
         generateMTFValues_zPend:=generateMTFValues_zPend-1;
         break$$<==0 and skip;
         while( break$$=0 AND 1)
         {
             break$$$<==0 and skip;
              switch$<==0 and skip;
              int nm_2$ and skip;
             nm_2$ := generateMTFValues_zPend % 2;
             if (nm_2$=0 OR (switch$=1 AND break$$$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 szptr[generateMTFValues_wr]:=0;
                 generateMTFValues_wr:=generateMTFValues_wr+1;
                 mtfFreq[0]:=mtfFreq[0]+1;
                 break$$$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             if (nm_2$=1 OR (switch$=1 AND break$$$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 szptr[generateMTFValues_wr]:=1;
                 generateMTFValues_wr:=generateMTFValues_wr+1;
                 mtfFreq[1]:=mtfFreq[1]+1;
                 break$$$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             if(generateMTFValues_zPend<2) then 
             {
                 break$$<==1 and skip
              }
             else 
             {
                  skip 
             };
             if(break$$=0)   then
             {
                 generateMTFValues_zPend:=(generateMTFValues_zPend-2)/ 2
             }
             else
             {
                 skip
             }
         };
         break$$<==0 and skip
         
     }
     else 
     {
          skip 
     };
     szptr[generateMTFValues_wr]:=generateMTFValues_EOB;
     generateMTFValues_wr:=generateMTFValues_wr+1;
     mtfFreq[generateMTFValues_EOB]:=mtfFreq[generateMTFValues_EOB]+1;
     nMTF:=generateMTFValues_wr
     )
     }; 
  function sendMTFValues (  )
 {
     frame(sendMTFValues_v,sendMTFValues_t,sendMTFValues_i,sendMTFValues_j,sendMTFValues_gs,sendMTFValues_ge,sendMTFValues_totc,sendMTFValues_bt,sendMTFValues_bc,sendMTFValues_iter,sendMTFValues_nSelectors,sendMTFValues_alphaSize,sendMTFValues_minLen,sendMTFValues_maxLen,sendMTFValues_selCtr,sendMTFValues_nGroups,sendMTFValues_nBytes,sendMTFValues_cost,sendMTFValues_fave,sendMTFValues_nPart,sendMTFValues_remF,sendMTFValues_tFreq,sendMTFValues_aFreq,sendMTFValues_19_23_cost0,sendMTFValues_19_23_cost1,sendMTFValues_19_23_cost2,sendMTFValues_19_23_cost3,sendMTFValues_19_23_cost4,sendMTFValues_19_23_cost5,sendMTFValues_19_23_icv,sendMTFValues_19_24_icv,sendMTFValues_pos,sendMTFValues_ll_i,sendMTFValues_tmp2,sendMTFValues_tmp,sendMTFValues_inUse16,sendMTFValues_curr,break$$) and ( 
     int break$$<==0 and skip;
     int sendMTFValues_v,sendMTFValues_t,sendMTFValues_i,sendMTFValues_j,sendMTFValues_gs,sendMTFValues_ge,sendMTFValues_totc,sendMTFValues_bt,sendMTFValues_bc,sendMTFValues_iter and skip;
     int sendMTFValues_nSelectors,sendMTFValues_alphaSize,sendMTFValues_minLen,sendMTFValues_maxLen,sendMTFValues_selCtr and skip;
     int sendMTFValues_nGroups,sendMTFValues_nBytes and skip;
     int sendMTFValues_cost[6] and skip;
     int sendMTFValues_fave[6] and skip;
     if(verbosity>=3) then 
     {
         fprintf(stdout,"      %d in block, %d after MTF & 1-2 coding, %d+2 syms in use\n",last+1,nMTF,nInUse,RValue) and skip
     }
     else 
     {
          skip 
     };
     sendMTFValues_alphaSize:=nInUse+2;
     sendMTFValues_t:=0;
     
     while(sendMTFValues_t<6)
     {
         sendMTFValues_v:=0;
         
         while(sendMTFValues_v<sendMTFValues_alphaSize)
         {
             len$[sendMTFValues_t,sendMTFValues_v]:=15;
             sendMTFValues_v:=sendMTFValues_v+1
             
         };
         sendMTFValues_t:=sendMTFValues_t+1
         
     };
     if(nMTF<=0) then 
     {
         panic("sendMTFValues(0)")
     }
     else 
     {
          skip 
     };
     if(nMTF<200) then 
     {
         sendMTFValues_nGroups:=2
     }
     else
     {
         if(nMTF<800) then 
         {
             sendMTFValues_nGroups:=4
         }
         else
         {
             sendMTFValues_nGroups:=6
         }
     };
     int sendMTFValues_nPart,sendMTFValues_remF,sendMTFValues_tFreq,sendMTFValues_aFreq and skip;
     sendMTFValues_nPart:=sendMTFValues_nGroups;
     sendMTFValues_remF:=nMTF;
     sendMTFValues_gs:=0;
     while(sendMTFValues_nPart>0)
     {
         sendMTFValues_tFreq:=sendMTFValues_remF/ sendMTFValues_nPart;
         sendMTFValues_ge:=sendMTFValues_gs-1;
         sendMTFValues_aFreq:=0;
         while(sendMTFValues_aFreq<sendMTFValues_tFreq AND sendMTFValues_ge<sendMTFValues_alphaSize-1)
         {
             sendMTFValues_ge:=sendMTFValues_ge+1;
             sendMTFValues_aFreq:=sendMTFValues_aFreq+mtfFreq[sendMTFValues_ge]
         };
         if(sendMTFValues_ge>sendMTFValues_gs AND sendMTFValues_nPart!=sendMTFValues_nGroups AND sendMTFValues_nPart!=1 AND ((sendMTFValues_nGroups-sendMTFValues_nPart) % 2=1)) then 
         {
             sendMTFValues_aFreq:=sendMTFValues_aFreq-mtfFreq[sendMTFValues_ge];
             sendMTFValues_ge:=sendMTFValues_ge-1
             
         }
         else 
         {
              skip 
         };
         if(verbosity>=3) then 
         {
             fprintf(stdout,"      initial group %d, [%d .. %d], has %d syms (%4.1f%%)\n",sendMTFValues_nPart,sendMTFValues_gs,sendMTFValues_ge,sendMTFValues_aFreq,(100.0*(float)sendMTFValues_aFreq)/ (float)nMTF,RValue) and skip
         }
         else 
         {
              skip 
         };
         sendMTFValues_v:=0;
         
         while(sendMTFValues_v<sendMTFValues_alphaSize)
         {
             if(sendMTFValues_v>=sendMTFValues_gs AND sendMTFValues_v<=sendMTFValues_ge) then 
             {
                 len$[sendMTFValues_nPart-1,sendMTFValues_v]:=0
             }
             else
             {
                 len$[sendMTFValues_nPart-1,sendMTFValues_v]:=15
             };
             sendMTFValues_v:=sendMTFValues_v+1
             
         };
         sendMTFValues_nPart:=sendMTFValues_nPart-1;
         sendMTFValues_gs:=sendMTFValues_ge+1;
         sendMTFValues_remF:=sendMTFValues_remF-sendMTFValues_aFreq
     };
     sendMTFValues_iter:=0;
     
     while(sendMTFValues_iter<4)
     {
         sendMTFValues_t:=0;
         
         while(sendMTFValues_t<sendMTFValues_nGroups)
         {
             sendMTFValues_fave[sendMTFValues_t]:=0;
             sendMTFValues_t:=sendMTFValues_t+1
             
         };
         sendMTFValues_t:=0;
         
         while(sendMTFValues_t<sendMTFValues_nGroups)
         {
             sendMTFValues_v:=0;
             
             while(sendMTFValues_v<sendMTFValues_alphaSize)
             {
                 rfreq[sendMTFValues_t,sendMTFValues_v]:=0;
                 sendMTFValues_v:=sendMTFValues_v+1
                 
             };
             sendMTFValues_t:=sendMTFValues_t+1
             
         };
         sendMTFValues_nSelectors:=0;
         sendMTFValues_totc:=0;
         sendMTFValues_gs:=0;
         break$$<==0 and skip;
         while( break$$=0 AND  1)
         {
             if(sendMTFValues_gs>=nMTF) then 
             {
                 break$$<==1 and skip
              }
             else 
             {
                  skip 
             };
             if(break$$=0)   then
             {
                 sendMTFValues_ge:=sendMTFValues_gs+50-1;
                 if(sendMTFValues_ge>=nMTF) then 
                 {
                     sendMTFValues_ge:=nMTF-1
                 }
                 else 
                 {
                      skip 
                 };
                 sendMTFValues_t:=0;
                 
                 while(sendMTFValues_t<sendMTFValues_nGroups)
                 {
                     sendMTFValues_cost[sendMTFValues_t]:=0;
                     sendMTFValues_t:=sendMTFValues_t+1
                     
                 };
                 if(sendMTFValues_nGroups=6) then 
                 {
                     int sendMTFValues_19_23_cost0,sendMTFValues_19_23_cost1,sendMTFValues_19_23_cost2,sendMTFValues_19_23_cost3,sendMTFValues_19_23_cost4,sendMTFValues_19_23_cost5 and skip;
                     sendMTFValues_19_23_cost5<==0 and sendMTFValues_19_23_cost4<==sendMTFValues_19_23_cost5 and sendMTFValues_19_23_cost3<==sendMTFValues_19_23_cost4 and sendMTFValues_19_23_cost2<==sendMTFValues_19_23_cost3 and sendMTFValues_19_23_cost1<==sendMTFValues_19_23_cost2 and sendMTFValues_19_23_cost0<==sendMTFValues_19_23_cost1 and skip;
                     sendMTFValues_i:=sendMTFValues_gs;
                     
                     while(sendMTFValues_i<=sendMTFValues_ge)
                     {
                         int sendMTFValues_19_23_icv<==szptr[sendMTFValues_i] and skip;
                         sendMTFValues_19_23_cost0:=sendMTFValues_19_23_cost0+len$[0,sendMTFValues_19_23_icv];
                         sendMTFValues_19_23_cost1:=sendMTFValues_19_23_cost1+len$[1,sendMTFValues_19_23_icv];
                         sendMTFValues_19_23_cost2:=sendMTFValues_19_23_cost2+len$[2,sendMTFValues_19_23_icv];
                         sendMTFValues_19_23_cost3:=sendMTFValues_19_23_cost3+len$[3,sendMTFValues_19_23_icv];
                         sendMTFValues_19_23_cost4:=sendMTFValues_19_23_cost4+len$[4,sendMTFValues_19_23_icv];
                         sendMTFValues_19_23_cost5:=sendMTFValues_19_23_cost5+len$[5,sendMTFValues_19_23_icv];
                         sendMTFValues_i:=sendMTFValues_i+1
                         
                     };
                     sendMTFValues_cost[0]:=sendMTFValues_19_23_cost0;
                     sendMTFValues_cost[1]:=sendMTFValues_19_23_cost1;
                     sendMTFValues_cost[2]:=sendMTFValues_19_23_cost2;
                     sendMTFValues_cost[3]:=sendMTFValues_19_23_cost3;
                     sendMTFValues_cost[4]:=sendMTFValues_19_23_cost4;
                     sendMTFValues_cost[5]:=sendMTFValues_19_23_cost5
                     
                 }
                 else
                 {
                     sendMTFValues_i:=sendMTFValues_gs;
                     
                     while(sendMTFValues_i<=sendMTFValues_ge)
                     {
                         int sendMTFValues_19_24_icv<==szptr[sendMTFValues_i] and skip;
                         sendMTFValues_t:=0;
                         
                         while(sendMTFValues_t<sendMTFValues_nGroups)
                         {
                             sendMTFValues_cost[sendMTFValues_t]:=sendMTFValues_cost[sendMTFValues_t]+len$[sendMTFValues_t,sendMTFValues_19_24_icv];
                             sendMTFValues_t:=sendMTFValues_t+1
                             
                         };
                         sendMTFValues_i:=sendMTFValues_i+1
                         
                     }
                 };
                 sendMTFValues_bc:=999999999;
                 sendMTFValues_bt:=-1;
                 sendMTFValues_t:=0;
                 
                 while(sendMTFValues_t<sendMTFValues_nGroups)
                 {
                     if(sendMTFValues_cost[sendMTFValues_t]<sendMTFValues_bc) then 
                     {
                         sendMTFValues_bc:=sendMTFValues_cost[sendMTFValues_t];
                         sendMTFValues_bt:=sendMTFValues_t
                         
                     }
                     else 
                     {
                          skip 
                     };
                     sendMTFValues_t:=sendMTFValues_t+1
                     
                 };
                 sendMTFValues_totc:=sendMTFValues_totc+sendMTFValues_bc;
                 sendMTFValues_fave[sendMTFValues_bt]:=sendMTFValues_fave[sendMTFValues_bt]+1;
                 selector[sendMTFValues_nSelectors]:=sendMTFValues_bt;
                 sendMTFValues_nSelectors:=sendMTFValues_nSelectors+1;
                 sendMTFValues_i:=sendMTFValues_gs;
                 
                 while(sendMTFValues_i<=sendMTFValues_ge)
                 {
                     rfreq[sendMTFValues_bt,szptr[sendMTFValues_i]]:=rfreq[sendMTFValues_bt,szptr[sendMTFValues_i]]+1;
                     sendMTFValues_i:=sendMTFValues_i+1
                     
                 };
                 sendMTFValues_gs:=sendMTFValues_ge+1
             }
             else
             {
                 skip
             }
         };
         break$$<==0 and skip;
         if(verbosity>=3) then 
         {
             fprintf(stdout,"      pass %d: size is %d, grp uses are ",sendMTFValues_iter+1,sendMTFValues_totc/ 8,RValue) and skip;
             sendMTFValues_t:=0;
             
             while(sendMTFValues_t<sendMTFValues_nGroups)
             {
                 fprintf(stdout,"%d ",sendMTFValues_fave[sendMTFValues_t],RValue) and skip;
                 sendMTFValues_t:=sendMTFValues_t+1
                 
             };
             fprintf(stdout,"\n",RValue) and skip
             
         }
         else 
         {
              skip 
         };
         sendMTFValues_t:=0;
         
         while(sendMTFValues_t<sendMTFValues_nGroups)
         {
             hbMakeCodeLengths(&len$[sendMTFValues_t,0],&rfreq[sendMTFValues_t,0],sendMTFValues_alphaSize,20);
             sendMTFValues_t:=sendMTFValues_t+1
             
         };
         sendMTFValues_iter:=sendMTFValues_iter+1
         
     };
     if(!(sendMTFValues_nGroups<8)) then 
     {
         panic("sendMTFValues(1)")
     }
     else 
     {
          skip 
     };
     if(!(sendMTFValues_nSelectors<32768 AND sendMTFValues_nSelectors<=(2+(900000/ 50)))) then 
     {
         panic("sendMTFValues(2)")
     }
     else 
     {
          skip 
     };
     unsigned char sendMTFValues_pos[6],sendMTFValues_ll_i,sendMTFValues_tmp2,sendMTFValues_tmp and skip;
     sendMTFValues_i:=0;
     
     while(sendMTFValues_i<sendMTFValues_nGroups)
     {
         sendMTFValues_pos[sendMTFValues_i]:=sendMTFValues_i;
         sendMTFValues_i:=sendMTFValues_i+1
         
     };
     sendMTFValues_i:=0;
     
     while(sendMTFValues_i<sendMTFValues_nSelectors)
     {
         sendMTFValues_ll_i:=selector[sendMTFValues_i];
         sendMTFValues_j:=0;
         sendMTFValues_tmp:=sendMTFValues_pos[sendMTFValues_j];
         while(sendMTFValues_ll_i!=sendMTFValues_tmp)
         {
             sendMTFValues_j:=sendMTFValues_j+1;
             sendMTFValues_tmp2:=sendMTFValues_tmp;
             sendMTFValues_tmp:=sendMTFValues_pos[sendMTFValues_j];
             sendMTFValues_pos[sendMTFValues_j]:=sendMTFValues_tmp2
         };
         sendMTFValues_pos[0]:=sendMTFValues_tmp;
         selectorMtf[sendMTFValues_i]:=sendMTFValues_j;
         sendMTFValues_i:=sendMTFValues_i+1
         
     };
     sendMTFValues_t:=0;
     
     while(sendMTFValues_t<sendMTFValues_nGroups)
     {
         sendMTFValues_minLen:=32;
         sendMTFValues_maxLen:=0;
         sendMTFValues_i:=0;
         
         while(sendMTFValues_i<sendMTFValues_alphaSize)
         {
             if(len$[sendMTFValues_t,sendMTFValues_i]>sendMTFValues_maxLen) then 
             {
                 sendMTFValues_maxLen:=len$[sendMTFValues_t,sendMTFValues_i]
             }
             else 
             {
                  skip 
             };
             if(len$[sendMTFValues_t,sendMTFValues_i]<sendMTFValues_minLen) then 
             {
                 sendMTFValues_minLen:=len$[sendMTFValues_t,sendMTFValues_i]
             }
             else 
             {
                  skip 
             };
             sendMTFValues_i:=sendMTFValues_i+1
             
         };
         if(sendMTFValues_maxLen>20) then 
         {
             panic("sendMTFValues(3)")
         }
         else 
         {
              skip 
         };
         if(sendMTFValues_minLen<1) then 
         {
             panic("sendMTFValues(4)")
         }
         else 
         {
              skip 
         };
         hbAssignCodes(&code[sendMTFValues_t,0],&len$[sendMTFValues_t,0],sendMTFValues_minLen,sendMTFValues_maxLen,sendMTFValues_alphaSize);
         sendMTFValues_t:=sendMTFValues_t+1
         
     };
     unsigned char sendMTFValues_inUse16[16] and skip;
     sendMTFValues_i:=0;
     
     while(sendMTFValues_i<16)
     {
         sendMTFValues_inUse16[sendMTFValues_i]:=0;
         sendMTFValues_j:=0;
         
         while(sendMTFValues_j<16)
         {
             if(inUse[sendMTFValues_i*16+sendMTFValues_j]) then 
             {
                 sendMTFValues_inUse16[sendMTFValues_i]:=1
             }
             else 
             {
                  skip 
             };
             sendMTFValues_j:=sendMTFValues_j+1
             
         };
         sendMTFValues_i:=sendMTFValues_i+1
         
     };
     sendMTFValues_nBytes:=bytesOut;
     sendMTFValues_i:=0;
     
     while(sendMTFValues_i<16)
     {
         if(sendMTFValues_inUse16[sendMTFValues_i]) then 
         {
             bsW(1,1)
         }
         else
         {
             bsW(1,0)
         };
         sendMTFValues_i:=sendMTFValues_i+1
         
     };
     sendMTFValues_i:=0;
     
     while(sendMTFValues_i<16)
     {
         if(sendMTFValues_inUse16[sendMTFValues_i]) then 
         {
             sendMTFValues_j:=0;
             
             while(sendMTFValues_j<16)
             {
                 if(inUse[sendMTFValues_i*16+sendMTFValues_j]) then 
                 {
                     bsW(1,1)
                     
                 }
                 else
                 {
                     bsW(1,0)
                 };
                 sendMTFValues_j:=sendMTFValues_j+1
                 
             }
             
         }
         else 
         {
              skip 
         };
         sendMTFValues_i:=sendMTFValues_i+1
         
     };
     if(verbosity>=3) then 
     {
         fprintf(stdout,"      bytes: mapping %d, ",bytesOut-sendMTFValues_nBytes,RValue) and skip
     }
     else 
     {
          skip 
     };
     sendMTFValues_nBytes:=bytesOut;
     bsW(3,sendMTFValues_nGroups);
     bsW(15,sendMTFValues_nSelectors);
     sendMTFValues_i:=0;
     
     while(sendMTFValues_i<sendMTFValues_nSelectors)
     {
         sendMTFValues_j:=0;
         
         while(sendMTFValues_j<selectorMtf[sendMTFValues_i])
         {
             bsW(1,1);
             sendMTFValues_j:=sendMTFValues_j+1
             
         };
         bsW(1,0);
         sendMTFValues_i:=sendMTFValues_i+1
         
     };
     if(verbosity>=3) then 
     {
         fprintf(stdout,"selectors %d, ",bytesOut-sendMTFValues_nBytes,RValue) and skip
     }
     else 
     {
          skip 
     };
     sendMTFValues_nBytes:=bytesOut;
     sendMTFValues_t:=0;
     
     while(sendMTFValues_t<sendMTFValues_nGroups)
     {
         int sendMTFValues_curr<==len$[sendMTFValues_t,0] and skip;
         bsW(5,sendMTFValues_curr);
         sendMTFValues_i:=0;
         
         while(sendMTFValues_i<sendMTFValues_alphaSize)
         {
             while(sendMTFValues_curr<len$[sendMTFValues_t,sendMTFValues_i])
             {
                 bsW(2,2);
                 sendMTFValues_curr:=sendMTFValues_curr+1
             };
             while(sendMTFValues_curr>len$[sendMTFValues_t,sendMTFValues_i])
             {
                 bsW(2,3);
                 sendMTFValues_curr:=sendMTFValues_curr-1
             };
             bsW(1,0);
             sendMTFValues_i:=sendMTFValues_i+1
             
         };
         sendMTFValues_t:=sendMTFValues_t+1
         
     };
     if(verbosity>=3) then 
     {
         fprintf(stdout,"code lengths %d, ",bytesOut-sendMTFValues_nBytes,RValue) and skip
     }
     else 
     {
          skip 
     };
     sendMTFValues_nBytes:=bytesOut;
     sendMTFValues_selCtr:=0;
     sendMTFValues_gs:=0;
     break$$<==0 and skip;
     while( break$$=0 AND  1)
     {
         if(sendMTFValues_gs>=nMTF) then 
         {
             break$$<==1 and skip
          }
         else 
         {
              skip 
         };
         if(break$$=0)   then
         {
             sendMTFValues_ge:=sendMTFValues_gs+50-1;
             if(sendMTFValues_ge>=nMTF) then 
             {
                 sendMTFValues_ge:=nMTF-1
             }
             else 
             {
                  skip 
             };
             sendMTFValues_i:=sendMTFValues_gs;
             
             while(sendMTFValues_i<=sendMTFValues_ge)
             {
                 bsW(len$[selector[sendMTFValues_selCtr],szptr[sendMTFValues_i]],code[selector[sendMTFValues_selCtr],szptr[sendMTFValues_i]]);
                 sendMTFValues_i:=sendMTFValues_i+1
                 
             };
             sendMTFValues_gs:=sendMTFValues_ge+1;
             sendMTFValues_selCtr:=sendMTFValues_selCtr+1
         }
         else
         {
             skip
         }
     };
     break$$<==0 and skip;
     if(!(sendMTFValues_selCtr=sendMTFValues_nSelectors)) then 
     {
         panic("sendMTFValues(5)")
     }
     else 
     {
          skip 
     };
     if(verbosity>=3) then 
     {
         fprintf(stdout,"codes %d\n",bytesOut-sendMTFValues_nBytes,RValue) and skip
     }
     else 
     {
          skip 
     }
     )
     }; 
  function moveToFrontCodeAndSend (  )
 {
     bsPutIntVS(24,origPtr);
     generateMTFValues();
     sendMTFValues()
     
 };
 function recvDecodingTables (  )
 {
     frame(recvDecodingTables_i,recvDecodingTables_j,recvDecodingTables_t,recvDecodingTables_nGroups,recvDecodingTables_nSelectors,recvDecodingTables_alphaSize,recvDecodingTables_minLen,recvDecodingTables_maxLen,recvDecodingTables_inUse16,recvDecodingTables_pos,recvDecodingTables_tmp,recvDecodingTables_v,recvDecodingTables_curr) and ( 
     int recvDecodingTables_i,recvDecodingTables_j,recvDecodingTables_t,recvDecodingTables_nGroups,recvDecodingTables_nSelectors,recvDecodingTables_alphaSize and skip;
     int recvDecodingTables_minLen,recvDecodingTables_maxLen and skip;
     unsigned char recvDecodingTables_inUse16[16] and skip;
     recvDecodingTables_i:=0;
     
     while(recvDecodingTables_i<16)
     {
         if(extern bsR(1,RValue)=1) then 
         {
             recvDecodingTables_inUse16[recvDecodingTables_i]:=1
         }
         else
         {
             recvDecodingTables_inUse16[recvDecodingTables_i]:=0
         };
         recvDecodingTables_i:=recvDecodingTables_i+1
         
     };
     recvDecodingTables_i:=0;
     
     while(recvDecodingTables_i<256)
     {
         inUse[recvDecodingTables_i]:=0;
         recvDecodingTables_i:=recvDecodingTables_i+1
         
     };
     recvDecodingTables_i:=0;
     
     while(recvDecodingTables_i<16)
     {
         if(recvDecodingTables_inUse16[recvDecodingTables_i]) then 
         {
             recvDecodingTables_j:=0;
             
             while(recvDecodingTables_j<16)
             {
                 if(extern bsR(1,RValue)=1) then 
                 {
                     inUse[recvDecodingTables_i*16+recvDecodingTables_j]:=1
                 }
                 else 
                 {
                      skip 
                 };
                 recvDecodingTables_j:=recvDecodingTables_j+1
                 
             }
         }
         else 
         {
              skip 
         };
         recvDecodingTables_i:=recvDecodingTables_i+1
         
     };
     makeMaps();
     recvDecodingTables_alphaSize:=nInUse+2;
     recvDecodingTables_nGroups:=bsR(3,RValue);
     recvDecodingTables_nSelectors:=bsR(15,RValue);
     recvDecodingTables_i:=0;
     
     while(recvDecodingTables_i<recvDecodingTables_nSelectors)
     {
         recvDecodingTables_j:=0;
         while(extern bsR(1,RValue)=1)
         {
             recvDecodingTables_j:=recvDecodingTables_j+1
         };
         selectorMtf[recvDecodingTables_i]:=recvDecodingTables_j;
         recvDecodingTables_i:=recvDecodingTables_i+1
         
     };
     unsigned char recvDecodingTables_pos[6],recvDecodingTables_tmp,recvDecodingTables_v and skip;
     recvDecodingTables_v:=0;
     
     while(recvDecodingTables_v<recvDecodingTables_nGroups)
     {
         recvDecodingTables_pos[recvDecodingTables_v]:=recvDecodingTables_v;
         recvDecodingTables_v:=recvDecodingTables_v+1
         
     };
     recvDecodingTables_i:=0;
     
     while(recvDecodingTables_i<recvDecodingTables_nSelectors)
     {
         recvDecodingTables_v:=selectorMtf[recvDecodingTables_i];
         recvDecodingTables_tmp:=recvDecodingTables_pos[recvDecodingTables_v];
         while(recvDecodingTables_v>0)
         {
             recvDecodingTables_pos[recvDecodingTables_v]:=recvDecodingTables_pos[recvDecodingTables_v-1];
             recvDecodingTables_v:=recvDecodingTables_v-1
         };
         recvDecodingTables_pos[0]:=recvDecodingTables_tmp;
         selector[recvDecodingTables_i]:=recvDecodingTables_tmp;
         recvDecodingTables_i:=recvDecodingTables_i+1
         
     };
     recvDecodingTables_t:=0;
     
     while(recvDecodingTables_t<recvDecodingTables_nGroups)
     {
         int recvDecodingTables_curr and skip;
         recvDecodingTables_curr:=bsR(5,RValue);
         recvDecodingTables_i:=0;
         
         while(recvDecodingTables_i<recvDecodingTables_alphaSize)
         {
             while(extern bsR(1,RValue)=1)
             {
                 if(extern bsR(1,RValue)=0) then 
                 {
                     recvDecodingTables_curr:=recvDecodingTables_curr+1
                 }
                 else
                 {
                     recvDecodingTables_curr:=recvDecodingTables_curr-1
                 }
             };
             len$[recvDecodingTables_t,recvDecodingTables_i]:=recvDecodingTables_curr;
             recvDecodingTables_i:=recvDecodingTables_i+1
             
         };
         recvDecodingTables_t:=recvDecodingTables_t+1
         
     };
     recvDecodingTables_t:=0;
     
     while(recvDecodingTables_t<recvDecodingTables_nGroups)
     {
         recvDecodingTables_minLen:=32;
         recvDecodingTables_maxLen:=0;
         recvDecodingTables_i:=0;
         
         while(recvDecodingTables_i<recvDecodingTables_alphaSize)
         {
             if(len$[recvDecodingTables_t,recvDecodingTables_i]>recvDecodingTables_maxLen) then 
             {
                 recvDecodingTables_maxLen:=len$[recvDecodingTables_t,recvDecodingTables_i]
             }
             else 
             {
                  skip 
             };
             if(len$[recvDecodingTables_t,recvDecodingTables_i]<recvDecodingTables_minLen) then 
             {
                 recvDecodingTables_minLen:=len$[recvDecodingTables_t,recvDecodingTables_i]
             }
             else 
             {
                  skip 
             };
             recvDecodingTables_i:=recvDecodingTables_i+1
             
         };
         hbCreateDecodeTables(&limit[recvDecodingTables_t,0],&base[recvDecodingTables_t,0],&perm[recvDecodingTables_t,0],&len$[recvDecodingTables_t,0],recvDecodingTables_minLen,recvDecodingTables_maxLen,recvDecodingTables_alphaSize);
         minLens[recvDecodingTables_t]:=recvDecodingTables_minLen;
         recvDecodingTables_t:=recvDecodingTables_t+1
         
     }
     )
     }; 
  function getAndMoveToFrontDecode (  )
 {
     frame(getAndMoveToFrontDecode_yy,getAndMoveToFrontDecode_i,getAndMoveToFrontDecode_j,getAndMoveToFrontDecode_nextSym,getAndMoveToFrontDecode_limitLast,getAndMoveToFrontDecode_EOB,getAndMoveToFrontDecode_groupNo,getAndMoveToFrontDecode_groupPos,getAndMoveToFrontDecode_zt,getAndMoveToFrontDecode_zn,getAndMoveToFrontDecode_zvec,getAndMoveToFrontDecode_zj,getAndMoveToFrontDecode_4_5_zzi,getAndMoveToFrontDecode_7_9_ch,getAndMoveToFrontDecode_7_9_s,getAndMoveToFrontDecode_7_9_N,getAndMoveToFrontDecode_7_9_10_zt,getAndMoveToFrontDecode_7_9_10_zn,getAndMoveToFrontDecode_7_9_10_zvec,getAndMoveToFrontDecode_7_9_10_zj,getAndMoveToFrontDecode_7_9_10_15_16_zzi,count$,getAndMoveToFrontDecode_7_23_tmp,getAndMoveToFrontDecode_7_23_zt,getAndMoveToFrontDecode_7_23_zn,getAndMoveToFrontDecode_7_23_zvec,getAndMoveToFrontDecode_7_23_zj,getAndMoveToFrontDecode_7_23_29_30_zzi,break$$,continue) and ( 
     int continue<==0 and skip;
     int break$$<==0 and skip;
     unsigned char getAndMoveToFrontDecode_yy[256] and skip;
     int getAndMoveToFrontDecode_i,getAndMoveToFrontDecode_j,getAndMoveToFrontDecode_nextSym,getAndMoveToFrontDecode_limitLast and skip;
     int getAndMoveToFrontDecode_EOB,getAndMoveToFrontDecode_groupNo,getAndMoveToFrontDecode_groupPos and skip;
     getAndMoveToFrontDecode_limitLast:=100000*blockSize100k;
     origPtr:=bsGetIntVS(24,RValue);
     recvDecodingTables();
     getAndMoveToFrontDecode_EOB:=nInUse+1;
     getAndMoveToFrontDecode_groupNo:=-1;
     getAndMoveToFrontDecode_groupPos:=0;
     getAndMoveToFrontDecode_i:=0;
     
     while(getAndMoveToFrontDecode_i<=255)
     {
         unzftab[getAndMoveToFrontDecode_i]:=0;
         getAndMoveToFrontDecode_i:=getAndMoveToFrontDecode_i+1
         
     };
     getAndMoveToFrontDecode_i:=0;
     
     while(getAndMoveToFrontDecode_i<=255)
     {
         getAndMoveToFrontDecode_yy[getAndMoveToFrontDecode_i]:=(unsigned char)getAndMoveToFrontDecode_i;
         getAndMoveToFrontDecode_i:=getAndMoveToFrontDecode_i+1
         
     };
     last:=-1;
     int getAndMoveToFrontDecode_zt,getAndMoveToFrontDecode_zn,getAndMoveToFrontDecode_zvec,getAndMoveToFrontDecode_zj and skip;
     if(getAndMoveToFrontDecode_groupPos=0) then 
     {
         getAndMoveToFrontDecode_groupNo:=getAndMoveToFrontDecode_groupNo+1;
         getAndMoveToFrontDecode_groupPos:=50
         
     }
     else 
     {
          skip 
     };
     getAndMoveToFrontDecode_groupPos:=getAndMoveToFrontDecode_groupPos-1;
     getAndMoveToFrontDecode_zt:=selector[getAndMoveToFrontDecode_groupNo];
     getAndMoveToFrontDecode_zn:=minLens[getAndMoveToFrontDecode_zt];
     getAndMoveToFrontDecode_zvec:=bsR(getAndMoveToFrontDecode_zn,RValue);
     while(getAndMoveToFrontDecode_zvec>limit[getAndMoveToFrontDecode_zt,getAndMoveToFrontDecode_zn])
     {
         getAndMoveToFrontDecode_zn:=getAndMoveToFrontDecode_zn+1;
         while(bsLive<1)
         {
             int getAndMoveToFrontDecode_4_5_zzi and skip;
             getAndMoveToFrontDecode_4_5_zzi:=spec_getc(bsStream,RValue);
             if((getAndMoveToFrontDecode_4_5_zzi)=(-1)) then 
             {
                 compressedStreamEOF()
             }
             else 
             {
                  skip 
             };
             bsBuff:=(bsBuff<<8) | (getAndMoveToFrontDecode_4_5_zzi & 255);
             bsLive:=bsLive+8
         };
         getAndMoveToFrontDecode_zj:=(bsBuff>>(bsLive-1)) & 1;
         bsLive:=bsLive-1;
         getAndMoveToFrontDecode_zvec:=(getAndMoveToFrontDecode_zvec<<1) | getAndMoveToFrontDecode_zj
     };
     getAndMoveToFrontDecode_nextSym:=perm[getAndMoveToFrontDecode_zt,getAndMoveToFrontDecode_zvec-base[getAndMoveToFrontDecode_zt,getAndMoveToFrontDecode_zn]];
     break$$<==0 and skip;
     while( break$$=0 AND 1)
     {
         continue<==0 and skip;
         if(getAndMoveToFrontDecode_nextSym=getAndMoveToFrontDecode_EOB) then 
         {
             break$$<==1 and skip
          }
         else 
         {
              skip 
         };
         if(break$$=0)   then
         {
             if(getAndMoveToFrontDecode_nextSym=0 OR getAndMoveToFrontDecode_nextSym=1) then 
             {
                 unsigned char getAndMoveToFrontDecode_7_9_ch and skip;
                 int getAndMoveToFrontDecode_7_9_s<==-1 and skip;
                 int getAndMoveToFrontDecode_7_9_N<==1 and skip;
                 int count$<==0 and skip;
                 while( ( count$=0 OR getAndMoveToFrontDecode_nextSym=0 OR getAndMoveToFrontDecode_nextSym=1))
                 {
                     count$:=count$+1;
                     if(getAndMoveToFrontDecode_nextSym=0) then 
                     {
                         getAndMoveToFrontDecode_7_9_s:=getAndMoveToFrontDecode_7_9_s+(0+1)*getAndMoveToFrontDecode_7_9_N
                     }
                     else
                     {
                         if(getAndMoveToFrontDecode_nextSym=1) then 
                         {
                             getAndMoveToFrontDecode_7_9_s:=getAndMoveToFrontDecode_7_9_s+(1+1)*getAndMoveToFrontDecode_7_9_N
                         }
                         else 
                         {
                              skip 
                         }
                     };
                     getAndMoveToFrontDecode_7_9_N:=getAndMoveToFrontDecode_7_9_N*2;
                     int getAndMoveToFrontDecode_7_9_10_zt,getAndMoveToFrontDecode_7_9_10_zn,getAndMoveToFrontDecode_7_9_10_zvec,getAndMoveToFrontDecode_7_9_10_zj and skip;
                     if(getAndMoveToFrontDecode_groupPos=0) then 
                     {
                         getAndMoveToFrontDecode_groupNo:=getAndMoveToFrontDecode_groupNo+1;
                         getAndMoveToFrontDecode_groupPos:=50
                         
                     }
                     else 
                     {
                          skip 
                     };
                     getAndMoveToFrontDecode_groupPos:=getAndMoveToFrontDecode_groupPos-1;
                     getAndMoveToFrontDecode_7_9_10_zt:=selector[getAndMoveToFrontDecode_groupNo];
                     getAndMoveToFrontDecode_7_9_10_zn:=minLens[getAndMoveToFrontDecode_7_9_10_zt];
                     getAndMoveToFrontDecode_7_9_10_zvec:=bsR(getAndMoveToFrontDecode_7_9_10_zn,RValue);
                     while(getAndMoveToFrontDecode_7_9_10_zvec>limit[getAndMoveToFrontDecode_7_9_10_zt,getAndMoveToFrontDecode_7_9_10_zn])
                     {
                         getAndMoveToFrontDecode_7_9_10_zn:=getAndMoveToFrontDecode_7_9_10_zn+1;
                         while(bsLive<1)
                         {
                             int getAndMoveToFrontDecode_7_9_10_15_16_zzi and skip;
                             getAndMoveToFrontDecode_7_9_10_15_16_zzi:=spec_getc(bsStream,RValue);
                             if((getAndMoveToFrontDecode_7_9_10_15_16_zzi)=(-1)) then 
                             {
                                 compressedStreamEOF()
                             }
                             else 
                             {
                                  skip 
                             };
                             bsBuff:=(bsBuff<<8) | (getAndMoveToFrontDecode_7_9_10_15_16_zzi & 255);
                             bsLive:=bsLive+8
                         };
                         getAndMoveToFrontDecode_7_9_10_zj:=(bsBuff>>(bsLive-1)) & 1;
                         bsLive:=bsLive-1;
                         getAndMoveToFrontDecode_7_9_10_zvec:=(getAndMoveToFrontDecode_7_9_10_zvec<<1) | getAndMoveToFrontDecode_7_9_10_zj
                     };
                     getAndMoveToFrontDecode_nextSym:=perm[getAndMoveToFrontDecode_7_9_10_zt,getAndMoveToFrontDecode_7_9_10_zvec-base[getAndMoveToFrontDecode_7_9_10_zt,getAndMoveToFrontDecode_7_9_10_zn]]
                 };
                 getAndMoveToFrontDecode_7_9_s:=getAndMoveToFrontDecode_7_9_s+1;
                 getAndMoveToFrontDecode_7_9_ch:=seqToUnseq[getAndMoveToFrontDecode_yy[0]];
                 unzftab[getAndMoveToFrontDecode_7_9_ch]:=unzftab[getAndMoveToFrontDecode_7_9_ch]+getAndMoveToFrontDecode_7_9_s;
                 if(smallMode) then 
                 {
                     while(getAndMoveToFrontDecode_7_9_s>0)
                     {
                         last:=last+1;
                         ll16[last]:=getAndMoveToFrontDecode_7_9_ch;
                         getAndMoveToFrontDecode_7_9_s:=getAndMoveToFrontDecode_7_9_s-1
                     }
                 }
                 else
                 {
                     while(getAndMoveToFrontDecode_7_9_s>0)
                     {
                         last:=last+1;
                         ll8[last]:=getAndMoveToFrontDecode_7_9_ch;
                         getAndMoveToFrontDecode_7_9_s:=getAndMoveToFrontDecode_7_9_s-1
                     }
                 };
                 if(last>=getAndMoveToFrontDecode_limitLast) then 
                 {
                     blockOverrun()
                 }
                 else 
                 {
                      skip 
                 };
                 continue<==1 and skip
              }
             else
             {
                 unsigned char getAndMoveToFrontDecode_7_23_tmp and skip;
                 last:=last+1;
                 if(last>=getAndMoveToFrontDecode_limitLast) then 
                 {
                     blockOverrun()
                 }
                 else 
                 {
                      skip 
                 };
                 getAndMoveToFrontDecode_7_23_tmp:=getAndMoveToFrontDecode_yy[getAndMoveToFrontDecode_nextSym-1];
                 unzftab[seqToUnseq[getAndMoveToFrontDecode_7_23_tmp]]:=unzftab[seqToUnseq[getAndMoveToFrontDecode_7_23_tmp]]+1;
                 if(smallMode) then 
                 {
                     ll16[last]:=seqToUnseq[getAndMoveToFrontDecode_7_23_tmp]
                 }
                 else
                 {
                     ll8[last]:=seqToUnseq[getAndMoveToFrontDecode_7_23_tmp]
                 };
                 getAndMoveToFrontDecode_j:=getAndMoveToFrontDecode_nextSym-1;
                 while(getAndMoveToFrontDecode_j>3)
                 {
                     getAndMoveToFrontDecode_yy[getAndMoveToFrontDecode_j]:=getAndMoveToFrontDecode_yy[getAndMoveToFrontDecode_j-1];
                     getAndMoveToFrontDecode_yy[getAndMoveToFrontDecode_j-1]:=getAndMoveToFrontDecode_yy[getAndMoveToFrontDecode_j-2];
                     getAndMoveToFrontDecode_yy[getAndMoveToFrontDecode_j-2]:=getAndMoveToFrontDecode_yy[getAndMoveToFrontDecode_j-3];
                     getAndMoveToFrontDecode_yy[getAndMoveToFrontDecode_j-3]:=getAndMoveToFrontDecode_yy[getAndMoveToFrontDecode_j-4];
                     getAndMoveToFrontDecode_j:=getAndMoveToFrontDecode_j-4
                     
                 };
                 while(getAndMoveToFrontDecode_j>0)
                 {
                     getAndMoveToFrontDecode_yy[getAndMoveToFrontDecode_j]:=getAndMoveToFrontDecode_yy[getAndMoveToFrontDecode_j-1];
                     getAndMoveToFrontDecode_j:=getAndMoveToFrontDecode_j-1
                     
                 };
                 getAndMoveToFrontDecode_yy[0]:=getAndMoveToFrontDecode_7_23_tmp;
                 int getAndMoveToFrontDecode_7_23_zt,getAndMoveToFrontDecode_7_23_zn,getAndMoveToFrontDecode_7_23_zvec,getAndMoveToFrontDecode_7_23_zj and skip;
                 if(getAndMoveToFrontDecode_groupPos=0) then 
                 {
                     getAndMoveToFrontDecode_groupNo:=getAndMoveToFrontDecode_groupNo+1;
                     getAndMoveToFrontDecode_groupPos:=50
                     
                 }
                 else 
                 {
                      skip 
                 };
                 getAndMoveToFrontDecode_groupPos:=getAndMoveToFrontDecode_groupPos-1;
                 getAndMoveToFrontDecode_7_23_zt:=selector[getAndMoveToFrontDecode_groupNo];
                 getAndMoveToFrontDecode_7_23_zn:=minLens[getAndMoveToFrontDecode_7_23_zt];
                 getAndMoveToFrontDecode_7_23_zvec:=bsR(getAndMoveToFrontDecode_7_23_zn,RValue);
                 while(getAndMoveToFrontDecode_7_23_zvec>limit[getAndMoveToFrontDecode_7_23_zt,getAndMoveToFrontDecode_7_23_zn])
                 {
                     getAndMoveToFrontDecode_7_23_zn:=getAndMoveToFrontDecode_7_23_zn+1;
                     while(bsLive<1)
                     {
                         int getAndMoveToFrontDecode_7_23_29_30_zzi and skip;
                         getAndMoveToFrontDecode_7_23_29_30_zzi:=spec_getc(bsStream,RValue);
                         if((getAndMoveToFrontDecode_7_23_29_30_zzi)=(-1)) then 
                         {
                             compressedStreamEOF()
                         }
                         else 
                         {
                              skip 
                         };
                         bsBuff:=(bsBuff<<8) | (getAndMoveToFrontDecode_7_23_29_30_zzi & 255);
                         bsLive:=bsLive+8
                     };
                     getAndMoveToFrontDecode_7_23_zj:=(bsBuff>>(bsLive-1)) & 1;
                     bsLive:=bsLive-1;
                     getAndMoveToFrontDecode_7_23_zvec:=(getAndMoveToFrontDecode_7_23_zvec<<1) | getAndMoveToFrontDecode_7_23_zj
                 };
                 getAndMoveToFrontDecode_nextSym:=perm[getAndMoveToFrontDecode_7_23_zt,getAndMoveToFrontDecode_7_23_zvec-base[getAndMoveToFrontDecode_7_23_zt,getAndMoveToFrontDecode_7_23_zn]];
                 continue<==1 and skip
              }
         }
         else
         {
             skip
         }
     };
     break$$<==0 and skip;
     continue<==0 and skip
     )
     }; 
 function fullGtU ( int i1,int i2,unsigned char RValue )
 {
     frame(fullGtU_k,fullGtU_i,fullGtU_c1,fullGtU_c2,fullGtU_s1,fullGtU_s2,count$,return) and ( 
     int return<==0 and skip;
     int fullGtU_k,fullGtU_i and skip;
     unsigned char fullGtU_c1,fullGtU_c2 and skip;
     int fullGtU_s1,fullGtU_s2 and skip;
     fullGtU_i:=0;
	 
     while( return=0 AND  fullGtU_i<6)
     {
         fullGtU_c1:=block[i1];
		 
         fullGtU_c2:=block[i2];
         if(fullGtU_c1!=fullGtU_c2) then 
         {
             return<==1 and RValue:=(fullGtU_c1>fullGtU_c2);
             skip
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             i1:=i1+1;
             i2:=i2+1;
             fullGtU_i:=fullGtU_i+1
         }
         else
         {
             skip
         }
     };
     if(return=0)   then 
     {
         fullGtU_k:=last+1;
         int count$<==0 and skip;
         while( return=0 AND  ( count$=0 OR fullGtU_k>=0))
         {
             count$:=count$+1;
             fullGtU_i:=0;
             while( return=0 AND  fullGtU_i<4)
             {
                 fullGtU_c1:=block[i1];
                 fullGtU_c2:=block[i2];
                 if(fullGtU_c1!=fullGtU_c2) then 
                 {
                     return<==1 and RValue:=(fullGtU_c1>fullGtU_c2);
                     skip
                 }
                 else 
                 {
                      skip 
                 };
                 if(return=0)   then 
                 {
                     fullGtU_s1:=quadrant[i1];
                     fullGtU_s2:=quadrant[i2];
                     if(fullGtU_s1!=fullGtU_s2) then 
                     {
                         return<==1 and RValue:=(fullGtU_s1>fullGtU_s2);
                         skip
                     }
                     else 
                     {
                          skip 
                     };
                     if(return=0)   then 
                     {
                         i1:=i1+1;
                         i2:=i2+1;
                         fullGtU_i:=fullGtU_i+1
                     }
                     else
                     {
                         skip
                     }
                 }
                 else
                 {
                     skip
                 }
             };
             if(return=0)   then 
             {
                 if(i1>last) then 
                 {
                     i1:=i1-last;
                     i1:=i1-1
                     
                 }
                 else 
                 {
                      skip 
                 };
                 if(i2>last) then 
                 {
                     i2:=i2-last;
                     i2:=i2-1
                     
                 }
                 else 
                 {
                      skip 
                 };
                 fullGtU_k:=fullGtU_k-4;
                 workDone:=workDone+1
             }
             else
             {
                 skip
             }
         };
         if(return=0)   then 
         {
             return<==1 and RValue:=0;
             skip
         }
         else
         {
             skip
         }
     }
     else
     {
         skip
     }
     )
     }; 
      int incs[14]<=={1,4,13,40,121,364,1093,3280,9841,29524,88573,265720,797161,2391484} and skip;
 function simpleSort ( int lo,int hi,int d )
 {
     frame(yk,temp,simpleSort_i,simpleSort_j,simpleSort_h,simpleSort_bigN,simpleSort_hp,simpleSort_v,return,break$$) and ( 
     int yk<==0 and skip;
	 int break$$<==0 and skip;
	 unsigned char temp and skip;
     int return<==0 and skip;
     int simpleSort_i,simpleSort_j,simpleSort_h,simpleSort_bigN,simpleSort_hp and skip;
     int simpleSort_v and skip;
     simpleSort_bigN:=hi-lo+1;
     if(simpleSort_bigN<2) then 
     {
          return<==1 and skip
     }
     else 
     {
          skip 
     };
	 
     if(return=0)   then 
     {
         simpleSort_hp:=0;
         while(incs[simpleSort_hp]<simpleSort_bigN)
         {
             simpleSort_hp:=simpleSort_hp+1
         };
         simpleSort_hp:=simpleSort_hp-1;
		 
         while( return=0 AND  simpleSort_hp>=0)
         {
             simpleSort_h:=incs[simpleSort_hp];
			 
             if(verbosity>=5) then 
             {
                 fprintf(stdout,"          shell increment %d\n",simpleSort_h,RValue) and skip
             }
             else 
             {
                  skip 
             };
             simpleSort_i:=lo+simpleSort_h;
             break$$<==0 and skip;
             while( return=0 AND   break$$=0 )
             {
                 if(simpleSort_i>hi) then 
                 {
                     break$$<==1 and skip
                  }
                 else 
                 {
                      skip 
                 };
                 if(break$$=0)   then
                 {
                     simpleSort_v:=zptr[simpleSort_i];
				
                     simpleSort_j:=simpleSort_i;
                    
					
				
                     while( break$$=0 AND ( extern  fullGtU(zptr[simpleSort_j-simpleSort_h]+d,simpleSort_v+d,RValue))  )
                     {
                         zptr[simpleSort_j]:=zptr[simpleSort_j-simpleSort_h];
                         simpleSort_j:=simpleSort_j-simpleSort_h;
                         if(simpleSort_j<=(lo+simpleSort_h-1)) then 
                         {
                             break$$<==1 and skip
                          }
                         else 
                         {
                              skip 
                         }
                     };
					
                     break$$<==0 and skip;
                     zptr[simpleSort_j]:=simpleSort_v;
                     simpleSort_i:=simpleSort_i+1;
                     if(simpleSort_i>hi) then 
                     {
                         break$$<==1 and skip
                      }
                     else 
                     {
                          skip 
                     };
                     if(break$$=0)   then
                     {
                         simpleSort_v:=zptr[simpleSort_i];
                         simpleSort_j:=simpleSort_i;
                         break$$<==0 and skip;

						 

                         while( break$$=0 AND (extern fullGtU(zptr[simpleSort_j-simpleSort_h]+d,simpleSort_v+d,RValue)) )
                         {
                             zptr[simpleSort_j]:=zptr[simpleSort_j-simpleSort_h];
                             simpleSort_j:=simpleSort_j-simpleSort_h; 
                             if(simpleSort_j<=(lo+simpleSort_h-1)) then 
                             {
                                 break$$<==1 and skip
                              }
                             else 
                             {
                                  skip 
                             }
                         };
                         break$$<==0 and skip;
                         zptr[simpleSort_j]:=simpleSort_v;
                         simpleSort_i:=simpleSort_i+1;
                         if(simpleSort_i>hi) then 
                         {
                             break$$<==1 and skip
                          }
                         else 
                         {
                              skip 
                         };
                         if(break$$=0)   then
                         {
                             simpleSort_v:=zptr[simpleSort_i];
                             simpleSort_j:=simpleSort_i;
                             break$$<==0 and skip;


							  /*yk:=fullGtU(zptr[simpleSort_j-simpleSort_h]+d,simpleSort_v+d,RValue);

					      if(temp_j=3) then{output(yk, " ") and skip} else{skip};*/

                             while(break$$=0 AND extern  fullGtU(zptr[simpleSort_j-simpleSort_h]+d,simpleSort_v+d,RValue) )
                             {
                                 zptr[simpleSort_j]:=zptr[simpleSort_j-simpleSort_h];
                                 simpleSort_j:=simpleSort_j-simpleSort_h;
                                 if(simpleSort_j<=(lo+simpleSort_h-1)) then 
                                 {
                                     break$$<==1 and skip
                                  }
                                 else 
                                 {
                                      skip 
                                 }
                             };
                             break$$<==0 and skip;
                             zptr[simpleSort_j]:=simpleSort_v;
                             simpleSort_i:=simpleSort_i+1;
                             if(workDone>workLimit AND firstAttempt) then 
                             {
                                  return<==1 and skip
                             }
                             else 
                             {
                                  skip 
                             }
                         }
                         else
                         {
                             skip
                         }
                     }
                     else
                     {
                         skip
                     }
                 }
                 else
                 {
                     skip
                 }
             };
			 
             break$$<==0 and skip;
             if(return=0)   then 
             {
                 simpleSort_hp:=simpleSort_hp-1
             }
             else
             {
                 skip
             }
             
         }
     }
     else
     {
         skip
     }
     )
     }; 
  function vswap ( int p1,int p2,int n )
 {
     frame(vswap_1_tmp) and ( 
     while(n>0)
     {
         int vswap_1_tmp<==zptr[p1] and skip;
         zptr[p1]:=zptr[p2];
         zptr[p2]:=vswap_1_tmp;
         p1:=p1+1;
         p2:=p2+1;
         n:=n-1
     }
     )
     }; 
  function med3 ( unsigned char a,unsigned char b,unsigned char c,unsigned char RValue )
 {
     frame(med3_t,return) and ( 
     int return<==0 and skip;
     unsigned char med3_t and skip;
     if(a>b) then 
     {
         med3_t:=a;
         a:=b;
         b:=med3_t
         
     }
     else 
     {
          skip 
     };
     if(b>c) then 
     {
         med3_t:=b;
         b:=c;
         c:=med3_t
         
     }
     else 
     {
          skip 
     };
     if(a>b) then 
     {
         b:=a
     }
     else 
     {
          skip 
     };
     return<==1 and RValue:=b;
     skip
     )
     }; 
      struct StackElem {
     int ll and 
     int hh and 
     int dd 
 };
 function qSort3 ( int loSt,int hiSt,int dSt )
 {
     frame(qSort3_unLo,qSort3_unHi,qSort3_ltLo,qSort3_gtHi,qSort3_med,qSort3_n,qSort3_m,qSort3_sp,qSort3_lo,qSort3_hi,qSort3_d,qSort3_stack,qSort3_1_5_6_8_tmp,qSort3_1_5_10_12_tmp,qSort3_1_5_tmp,return,break$$,continue) and ( 
     int continue<==0 and skip;
     int break$$<==0 and skip;
     int return<==0 and skip;
     int qSort3_unLo,qSort3_unHi,qSort3_ltLo,qSort3_gtHi,qSort3_med,qSort3_n,qSort3_m and skip;
     int qSort3_sp,qSort3_lo,qSort3_hi,qSort3_d and skip;
     StackElem qSort3_stack[1000] and skip;
     qSort3_sp:=0;
     qSort3_stack[qSort3_sp].ll:=loSt;
     qSort3_stack[qSort3_sp].hh:=hiSt;
     qSort3_stack[qSort3_sp].dd:=dSt;
     qSort3_sp:=qSort3_sp+1;
     while( return=0 AND  qSort3_sp>0)
     {
         continue<==0 and skip;
         if(qSort3_sp>=1000) then 
         {
             panic("stack overflow in qSort3")
         }
         else 
         {
              skip 
         };
         qSort3_sp:=qSort3_sp-1;
         qSort3_lo:=qSort3_stack[qSort3_sp].ll;
         qSort3_hi:=qSort3_stack[qSort3_sp].hh;
         qSort3_d:=qSort3_stack[qSort3_sp].dd;
         if(qSort3_hi-qSort3_lo<20 OR qSort3_d>10) then 
         {
		    if(syf=255) then{temp_j:=temp_j+1} else{skip};
	

            simpleSort(qSort3_lo,qSort3_hi,qSort3_d);
	
			 if(workDone>workLimit AND firstAttempt) then 
             {
                  return<==1 and skip
             }
             else 
             {
                  skip 
             };
             if(return=0)   then 
             {
                 continue<==1 and skip
              }
             else
             {
                 skip
             }
             
         }
         else 
         {
              skip 
         };
         if(continue=0)   then 
         {
             if(return=0)  then
             {
				 qSort3_med:=med3(block[zptr[qSort3_lo]+qSort3_d],block[zptr[qSort3_hi]+qSort3_d],block[zptr[(qSort3_lo+qSort3_hi)>>1]+qSort3_d],RValue);
                
				 
				 
				 qSort3_ltLo<==qSort3_lo and qSort3_unLo<==qSort3_ltLo and skip;
                 qSort3_gtHi<==qSort3_hi and qSort3_unHi<==qSort3_gtHi and skip;
                 break$$<==0 and skip;
                 while( break$$=0 AND  1)
                 {
                     break$$<==0 and skip;
                     while( break$$=0 AND  1)
                     {
                         continue<==0 and skip;
                         if(qSort3_unLo>qSort3_unHi) then 
                         {
                             break$$<==1 and skip
                          }
                         else 
                         {
                              skip 
                         };
                         if(break$$=0)   then
                         {
                             qSort3_n:=((int)block[zptr[qSort3_unLo]+qSort3_d])-qSort3_med;
                             if(qSort3_n=0) then 
                             {
                                 int qSort3_1_5_6_8_tmp<==zptr[qSort3_unLo] and skip;
                                 zptr[qSort3_unLo]:=zptr[qSort3_ltLo];
                                 zptr[qSort3_ltLo]:=qSort3_1_5_6_8_tmp;
                                 qSort3_ltLo:=qSort3_ltLo+1;
                                 qSort3_unLo:=qSort3_unLo+1;
                                 continue<==1 and skip
                                  
                             }
                             else 
                             {
                                  skip 
                             };
                             if(continue=0)   then 
                             {
                                 if(qSort3_n>0) then 
                                 {
                                     break$$<==1 and skip
                                  }
                                 else 
                                 {
                                      skip 
                                 };
                                 if(break$$=0)   then
                                 {
                                     qSort3_unLo:=qSort3_unLo+1
                                 }
                                 else
                                 {
                                     skip
                                 }
                             }
                             else
                             {
                                 skip
                             }
                         }
                         else
                         {
                             skip
                         }
                     };
                     break$$<==0 and skip;
                     continue<==0 and skip;
                     break$$<==0 and skip;
                     while( break$$=0 AND  1)
                     {
                         continue<==0 and skip;
                         if(qSort3_unLo>qSort3_unHi) then 
                         {
                             break$$<==1 and skip
                          }
                         else 
                         {
                              skip 
                         };
                         if(break$$=0)   then
                         {
                             qSort3_n:=((int)block[zptr[qSort3_unHi]+qSort3_d])-qSort3_med;
                             if(qSort3_n=0) then 
                             {
                                 int qSort3_1_5_10_12_tmp<==zptr[qSort3_unHi] and skip;
                                 zptr[qSort3_unHi]:=zptr[qSort3_gtHi];
                                 zptr[qSort3_gtHi]:=qSort3_1_5_10_12_tmp;
                                 qSort3_gtHi:=qSort3_gtHi-1;
                                 qSort3_unHi:=qSort3_unHi-1;
                                 continue<==1 and skip
                                  
                             }
                             else 
                             {
                                  skip 
                             };
                             if(continue=0)   then 
                             {
                                 if(qSort3_n<0) then 
                                 {
                                     break$$<==1 and skip
                                  }
                                 else 
                                 {
                                      skip 
                                 };
                                 if(break$$=0)   then
                                 {
                                     qSort3_unHi:=qSort3_unHi-1
                                 }
                                 else
                                 {
                                     skip
                                 }
                             }
                             else
                             {
                                 skip
                             }
                         }
                         else
                         {
                             skip
                         }
                     };
                     break$$<==0 and skip;
                     continue<==0 and skip;
                     if(qSort3_unLo>qSort3_unHi) then 
                     {
                         break$$<==1 and skip
                      }
                     else 
                     {
                          skip 
                     };
                     if(break$$=0)   then
                     {
                         int qSort3_1_5_tmp<==zptr[qSort3_unLo] and skip;
                         zptr[qSort3_unLo]:=zptr[qSort3_unHi];
                         zptr[qSort3_unHi]:=qSort3_1_5_tmp;
                         qSort3_unLo:=qSort3_unLo+1;
                         qSort3_unHi:=qSort3_unHi-1
                     }
                     else
                     {
                         skip
                     }
                 };

                 break$$<==0 and skip;
                 if(qSort3_gtHi<qSort3_ltLo) then 
                 {
                     qSort3_stack[qSort3_sp].ll:=qSort3_lo;
                     qSort3_stack[qSort3_sp].hh:=qSort3_hi;
                     qSort3_stack[qSort3_sp].dd:=qSort3_d+1;
                     qSort3_sp:=qSort3_sp+1;
                     continue<==1 and skip
                      
                 }
                 else 
                 {
                      skip 
                 };
                 if(continue=0)   then 
                 {
                     qSort3_n:=( if(((qSort3_ltLo-qSort3_lo)<(qSort3_unLo-qSort3_ltLo))) then (qSort3_ltLo-qSort3_lo) else (qSort3_unLo-qSort3_ltLo));
                     vswap(qSort3_lo,qSort3_unLo-qSort3_n,qSort3_n);
                     qSort3_m:=( if(((qSort3_hi-qSort3_gtHi)<(qSort3_gtHi-qSort3_unHi))) then (qSort3_hi-qSort3_gtHi) else (qSort3_gtHi-qSort3_unHi));
                     vswap(qSort3_unLo,qSort3_hi-qSort3_m+1,qSort3_m);

                     qSort3_n:=qSort3_lo+qSort3_unLo-qSort3_ltLo-1;
                     qSort3_m:=qSort3_hi-(qSort3_gtHi-qSort3_unHi)+1;
                     qSort3_stack[qSort3_sp].ll:=qSort3_lo;
                     qSort3_stack[qSort3_sp].hh:=qSort3_n;
                     qSort3_stack[qSort3_sp].dd:=qSort3_d;
                     qSort3_sp:=qSort3_sp+1;
                     qSort3_stack[qSort3_sp].ll:=qSort3_n+1;
                     qSort3_stack[qSort3_sp].hh:=qSort3_m-1;
                     qSort3_stack[qSort3_sp].dd:=qSort3_d+1;
                     qSort3_sp:=qSort3_sp+1;
                     qSort3_stack[qSort3_sp].ll:=qSort3_m;
                     qSort3_stack[qSort3_sp].hh:=qSort3_hi;
                     qSort3_stack[qSort3_sp].dd:=qSort3_d;
                     qSort3_sp:=qSort3_sp+1
                 }
                 else
                 {
                     skip
                 }
             }
             else
             {
                 skip
             }
         }
         else
         {
             skip
         }
     };
     continue<==0 and skip
     )
     }; 
  function sortIt (  )
 {
     frame(sortIt_i,sortIt_j,sortIt_ss,sortIt_sb,sortIt_runningOrder,sortIt_copy,sortIt_bigDone,sortIt_c1,sortIt_c2,sortIt_numQSorted,sortIt_8_vv,sortIt_8_h,count$,goto$,sortIt_8_18_lo,sortIt_8_18_hi,sortIt_8_22_bbStart,sortIt_8_22_bbSize,sortIt_8_22_shifts,sortIt_8_22_a2update,return) and ( 
     int return<==0 and skip;
	 int goto$<==0 and skip;
     int sortIt_i,sortIt_j,sortIt_ss,sortIt_sb and skip;
     int sortIt_runningOrder[256] and skip;
     int sortIt_copy[256] and skip;
     unsigned char sortIt_bigDone[256] and skip;
     unsigned char sortIt_c1,sortIt_c2 and skip;
     int sortIt_numQSorted and skip;
     if(verbosity>=4) then 
     {
         fprintf(stdout,"        sort initialise ...\n",RValue) and skip
     }
     else 
     {
          skip 
     };
     sortIt_i:=0;
     while(sortIt_i<20)
     {
         block[last+sortIt_i+1]:=block[sortIt_i % (last+1)];
         sortIt_i:=sortIt_i+1
         
     };
     sortIt_i:=0;
	
     while(sortIt_i<=last+20)
     {
         quadrant[sortIt_i]:=0;
         sortIt_i:=sortIt_i+1
         
     };
     block[-1]:=block[last];
     if(last<4000) then 
     {
         if(verbosity>=4) then 
         {
             fprintf(stdout,"        simpleSort ...\n",RValue) and skip
         }
         else 
         {
              skip 
         };
         sortIt_i:=0;
         
         while(sortIt_i<=last)
         {
             zptr[sortIt_i]:=sortIt_i;
             sortIt_i:=sortIt_i+1
             
         };
         firstAttempt:=0;
         workLimit<==0 and workDone<==workLimit and skip;
		 
         simpleSort(0,last,0);
         if(verbosity>=4) then 
         {
             fprintf(stdout,"        simpleSort done.\n",RValue) and skip
         }
         else 
         {
              skip 
         }
     }
     else
     {
         sortIt_numQSorted:=0;
         sortIt_i:=0;
       
         while(sortIt_i<=255)
         {
             sortIt_bigDone[sortIt_i]:=0;
             sortIt_i:=sortIt_i+1
             
         };
         if(verbosity>=4) then 
         {
             fprintf(stdout,"        bucket sorting ...\n",RValue) and skip
         }
         else 
         {
              skip 
         };
         sortIt_i:=0;
         
         while(sortIt_i<=65536)
         {
             ftab[sortIt_i]:=0;
             sortIt_i:=sortIt_i+1
             
         };
         sortIt_c1:=block[-1];
         sortIt_i:=0;
         while(sortIt_i<=last)
         {
             sortIt_c2:=block[sortIt_i];
             ftab[(sortIt_c1<<8)+sortIt_c2]:=ftab[(sortIt_c1<<8)+sortIt_c2]+1;
             sortIt_c1:=sortIt_c2;
             sortIt_i:=sortIt_i+1
             
         };
         sortIt_i:=1;
         while(sortIt_i<=65536)
         {
             ftab[sortIt_i]:=ftab[sortIt_i]+ftab[sortIt_i-1];
             sortIt_i:=sortIt_i+1
             
         };
         sortIt_c1:=block[0];
         sortIt_i:=0;
	 
         while(sortIt_i<last)
         {
             sortIt_c2:=block[sortIt_i+1];
             sortIt_j:=(sortIt_c1<<8)+sortIt_c2;
             sortIt_c1:=sortIt_c2;
             ftab[sortIt_j]:=ftab[sortIt_j]-1;
             zptr[ftab[sortIt_j]]:=sortIt_i;
             sortIt_i:=sortIt_i+1
             
         };

         sortIt_j:=(block[last]<<8)+block[0];
         ftab[sortIt_j]:=ftab[sortIt_j]-1;
         zptr[ftab[sortIt_j]]:=last;
         sortIt_i:=0;
         
         while(sortIt_i<=255)
         {
             sortIt_runningOrder[sortIt_i]:=sortIt_i;
             sortIt_i:=sortIt_i+1
             
         };
         int sortIt_8_vv and skip;
         int sortIt_8_h<==1 and skip;
         int count$<==0 and skip;
         while( ( count$=0 OR sortIt_8_h<=256))
         {
             count$:=count$+1;
             sortIt_8_h:=3*sortIt_8_h+1
         };
         count$<==0 and skip;
         while( ( count$=0 OR sortIt_8_h!=1))
         {
             count$:=count$+1;
             sortIt_8_h:=sortIt_8_h/ 3;
             sortIt_i:=sortIt_8_h;
             
             while(sortIt_i<=255)
             {
                 sortIt_8_vv:=sortIt_runningOrder[sortIt_i];
                 sortIt_j:=sortIt_i;
                 while(goto$=0 AND (ftab[((sortIt_runningOrder[sortIt_j-sortIt_8_h])+1)<<8]-ftab[(sortIt_runningOrder[sortIt_j-sortIt_8_h])<<8])>(ftab[(sortIt_8_vv+1)<<8]-ftab[sortIt_8_vv<<8]))
                 {
                     sortIt_runningOrder[sortIt_j]:=sortIt_runningOrder[sortIt_j-sortIt_8_h];
                     sortIt_j:=sortIt_j-sortIt_8_h;
                     if(sortIt_j<=(sortIt_8_h-1)) then 
                     {
                         goto$<==1 and skip
                     }
                     else 
                     {
                          skip 
                     }
                 };
                     sortIt_runningOrder[sortIt_j]:=sortIt_8_vv;
                     sortIt_i:=sortIt_i+1;
					 goto$<==0 and skip
                 
             }
          };
		  
		  goto$<==0 and skip;
             if(goto$=0)   then 
             {
                 sortIt_i:=0;
                 while( return=0 AND  sortIt_i<=255)
                 {
                     sortIt_ss:=sortIt_runningOrder[sortIt_i];
                     sortIt_j:=0;
                     while( return=0 AND  sortIt_j<=255)
                     {
                         sortIt_sb:=(sortIt_ss<<8)+sortIt_j;
                         if(!(ftab[sortIt_sb] & (1<<21))) then 
                         {
                             int sortIt_8_18_lo<==ftab[sortIt_sb] & (~(1<<21)) and skip;
                             int sortIt_8_18_hi<==(ftab[sortIt_sb+1] & (~(1<<21)))-1 and skip;
							 
                             if(sortIt_8_18_hi>sortIt_8_18_lo) then 
                             {
                                 if(verbosity>=4) then 
                                 {
                                     fprintf(stdout,"        qsort [0x%x, 0x%x]   done %d   this %d\n",sortIt_ss,sortIt_j,sortIt_numQSorted,sortIt_8_18_hi-sortIt_8_18_lo+1,RValue)and skip
                                 }
                                 else 
                                 {
                                      skip 
                                 };
								 syf<==sortIt_i and skip;

								
                                 qSort3(sortIt_8_18_lo,sortIt_8_18_hi,2);
								 
                                 sortIt_numQSorted:=sortIt_numQSorted+(sortIt_8_18_hi-sortIt_8_18_lo+1);
                                 if(workDone>workLimit AND firstAttempt) then 
                                 {
                                      return<==1 and skip
                                 }
                                 else 
                                 {
                                      skip 
                                 }
                                 
                             }
                             else 
                             {
                                  skip 
                             };
                             if(return=0)  then
                             {
                                 ftab[sortIt_sb]:=ftab[sortIt_sb]| (1<<21)
                             }
                             else
                             {
                                 skip
                             }
                             
                         }
                         else 
                         {
                              skip 
                         };
                         if(return=0)  then
                         {
                             sortIt_j:=sortIt_j+1
                         }
                         else
                         {
                             skip
                         }
                         
                     };
                     if(return=0)   then 
                     {
                         sortIt_bigDone[sortIt_ss]:=1;
                         if(sortIt_i<255) then 
                         {
                             int sortIt_8_22_bbStart<==ftab[sortIt_ss<<8] & (~(1<<21)) and skip;
                             int sortIt_8_22_bbSize<==(ftab[(sortIt_ss+1)<<8] & (~(1<<21)))-sortIt_8_22_bbStart and skip;
                             int sortIt_8_22_shifts<==0 and skip;
							 
                             while((sortIt_8_22_bbSize>>sortIt_8_22_shifts)>65534)
                             {
                                 sortIt_8_22_shifts:=sortIt_8_22_shifts+1
                             };
                             sortIt_j:=0;
                             
                             while(sortIt_j<sortIt_8_22_bbSize)
                             {
                                 int sortIt_8_22_a2update<==zptr[sortIt_8_22_bbStart+sortIt_j] and skip;
                                 int sortIt_8_22_qVal<==(unsigned int)(sortIt_j>>sortIt_8_22_shifts) and skip;
                                 quadrant[sortIt_8_22_a2update]:=sortIt_8_22_qVal;
                                 if(sortIt_8_22_a2update<20) then 
                                 {
                                     quadrant[sortIt_8_22_a2update+last+1]:=sortIt_8_22_qVal
                                 }
                                 else 
                                 {
                                      skip 
                                 };
                                 sortIt_j:=sortIt_j+1
                                 
                             };
                             if(!(((sortIt_8_22_bbSize-1)>>sortIt_8_22_shifts)<=65535)) then 
                             {
                                 panic("sortIt")

                             }
                             else 
                             {
                                  skip 
                             }
                             
                         }
                         else 
                         {
                              skip 
                         };
                         sortIt_j:=0;
                         
                         while(sortIt_j<=255)
                         {
                             sortIt_copy[sortIt_j]:=ftab[(sortIt_j<<8)+sortIt_ss] & (~(1<<21));
                             sortIt_j:=sortIt_j+1
                             
                         };
                         sortIt_j:=ftab[sortIt_ss<<8] & (~(1<<21));
        
                         while(sortIt_j<(ftab[(sortIt_ss+1)<<8] & (~(1<<21))))
                         {
                             sortIt_c1:=block[zptr[sortIt_j]-1];
                             if(!sortIt_bigDone[sortIt_c1]) then 
                             {
                                 zptr[sortIt_copy[sortIt_c1]]:=( if(zptr[sortIt_j]=0) then last else (zptr[sortIt_j]-1));
                                 sortIt_copy[sortIt_c1]:=sortIt_copy[sortIt_c1]+1
                                 
                             }
                             else 
                             {
                                  skip 
                             };
                             sortIt_j:=sortIt_j+1
                             
                         };
                         sortIt_j:=0;
                         
                         while(sortIt_j<=255)
                         {
                             ftab[(sortIt_j<<8)+sortIt_ss]:=ftab[(sortIt_j<<8)+sortIt_ss]| (1<<21);
                             sortIt_j:=sortIt_j+1
                             
                         };
                         sortIt_i:=sortIt_i+1
                     }
                     else
                     {
                         skip
                     }
                     
                 };
                 if(return=0)   then 
                 {
                     if(verbosity>=4) then 
                     {
                         fprintf(stdout,"        %d pointers, %d sorted, %d scanned\n",last+1,sortIt_numQSorted,(last+1)-sortIt_numQSorted,RValue) and skip
                     }
                     else 
                     {
                          skip 
                     }
                 }
                 else
                 {
                     skip
                 }
             }
             else
             {
                 skip
             }
         }
         )
         }; 
        int rNums[512]<=={619,720,127,481,931,816,813,233,566,247,985,724,205,454,863,491,741,242,949,214,733,859,335,708,621,574,73,654,730,472,419,436,278,496,867,210,399,680,480,51,878,465,811,169,869,675,611,697,867,561,862,687,507,283,482,129,807,591,733,623,150,238,59,379,684,877,625,169,643,105,170,607,520,932,727,476,693,425,174,647,73,122,335,530,442,853,695,249,445,515,909,545,703,919,874,474,882,500,594,612,641,801,220,162,819,984,589,513,495,799,161,604,958,533,221,400,386,867,600,782,382,596,414,171,516,375,682,485,911,276,98,553,163,354,666,933,424,341,533,870,227,730,475,186,263,647,537,686,600,224,469,68,770,919,190,373,294,822,808,206,184,943,795,384,383,461,404,758,839,887,715,67,618,276,204,918,873,777,604,560,951,160,578,722,79,804,96,409,713,940,652,934,970,447,318,353,859,672,112,785,645,863,803,350,139,93,354,99,820,908,609,772,154,274,580,184,79,626,630,742,653,282,762,623,680,81,927,626,789,125,411,521,938,300,821,78,343,175,128,250,170,774,972,275,999,639,495,78,352,126,857,956,358,619,580,124,737,594,701,612,669,112,134,694,363,992,809,743,168,974,944,375,748,52,600,747,642,182,862,81,344,805,988,739,511,655,814,334,249,515,897,955,664,981,649,113,974,459,893,228,433,837,553,268,926,240,102,654,459,51,686,754,806,760,493,403,415,394,687,700,946,670,656,610,738,392,760,799,887,653,978,321,576,617,626,502,894,679,243,440,680,879,194,572,640,724,926,56,204,700,707,151,457,449,797,195,791,558,945,679,297,59,87,824,713,663,412,693,342,606,134,108,571,364,631,212,174,643,304,329,343,97,430,751,497,314,983,374,822,928,140,206,73,263,980,736,876,478,430,305,170,514,364,692,829,82,855,953,676,246,369,970,294,750,807,827,150,790,288,923,804,378,215,828,592,281,565,555,710,82,896,831,547,261,524,462,293,465,502,56,661,821,976,991,658,869,905,758,745,193,768,550,608,933,378,286,215,979,792,961,61,688,793,644,986,403,106,366,905,644,372,567,466,434,645,210,389,550,919,135,780,773,635,389,707,100,626,958,165,504,920,176,193,713,857,265,203,50,668,108,645,990,626,197,510,357,358,850,858,364,936,638} and skip;
 function randomiseBlock (  )
 {
     frame(randomiseBlock_i,randomiseBlock_rNToGo,randomiseBlock_rTPos) and ( 
     int randomiseBlock_i and skip;
     int randomiseBlock_rNToGo<==0 and skip;
     int randomiseBlock_rTPos<==0 and skip;
     randomiseBlock_i:=0;
     while(randomiseBlock_i<256)
     {
         inUse[randomiseBlock_i]:=0;
         randomiseBlock_i:=randomiseBlock_i+1
         
     };
     randomiseBlock_i:=0;
     
     while(randomiseBlock_i<=last)
     {
         if(randomiseBlock_rNToGo=0) then 
         {
             randomiseBlock_rNToGo:=rNums[randomiseBlock_rTPos];
             randomiseBlock_rTPos:=randomiseBlock_rTPos+1;
             if(randomiseBlock_rTPos=512) then 
             {
                 randomiseBlock_rTPos:=0
             }
             else 
             {
                  skip 
             }
             
         }
         else 
         {
              skip 
         };
         randomiseBlock_rNToGo:=randomiseBlock_rNToGo-1;
         block[randomiseBlock_i]:=block[randomiseBlock_i]^ (( if((randomiseBlock_rNToGo=1)) then 1 else 0));
         inUse[block[randomiseBlock_i]]:=1;
         randomiseBlock_i:=randomiseBlock_i+1
         
     }
     )
     }; 
  function doReversibleTransformation (  )
 {
     frame(doReversibleTransformation_i,break$$) and ( 
     int break$$<==0 and skip;
     int doReversibleTransformation_i and skip;
     if(verbosity>=2) then 
     {
         fprintf(stdout,"\n",RValue) and skip
     }
     else 
     {
          skip 
     };
     workLimit:=workFactor*last;
     workDone:=0;
     blockRandomised:=0;
     firstAttempt:=1;
     sortIt();
     if(verbosity>=3) then 
     {
         fprintf(stdout,"      %d work, %d block, ratio %5.2f\n",workDone,last,(float)workDone/ (float)last,RValue) and skip
     }
     else 
     {
          skip 
     };
     if(workDone>workLimit AND firstAttempt) then 
     {
         if(verbosity>=2) then 
         {
             fprintf(stdout,"    sorting aborted; randomising block\n",RValue) and skip
         }
         else 
         {
              skip 
         };
         randomiseBlock();
         workDone<==0 and workLimit<==workDone and skip;
         blockRandomised:=1;
         firstAttempt:=0;
         sortIt();
         if(verbosity>=3) then 
         {
             fprintf(stdout,"      %d work, %d block, ratio %f\n",workDone,last,(float)workDone/ (float)last,RValue) and skip
         }
         else 
         {
              skip 
         }
         
     }
     else 
     {
          skip 
     };
     origPtr:=-1;
     break$$<==0 and skip;
     doReversibleTransformation_i:=0;
     
     while( break$$=0 AND  doReversibleTransformation_i<=last)
     {
         if(zptr[doReversibleTransformation_i]=0) then 
         {
             origPtr:=doReversibleTransformation_i;
             break$$<==1 and skip
              
         }
         else 
         {
              skip 
         };
         if(break$$=0)   then
         {
             doReversibleTransformation_i:=doReversibleTransformation_i+1
         }
         else
         {
             skip
         }
         
     };
     break$$<==0 and skip;
     if(origPtr=-1) then 
     {
         panic("doReversibleTransformation")
     }
     else 
     {
          skip 
     }
     )
     }; 
  function indexIntoF ( int indx,int *cftab,int RValue )
 {
     frame(indexIntoF_nb,indexIntoF_na,indexIntoF_mid,count$,return) and ( 
     int return<==0 and skip;
     int indexIntoF_nb,indexIntoF_na,indexIntoF_mid and skip;
     indexIntoF_nb:=0;
     indexIntoF_na:=256;
     int count$<==0 and skip;
     while( ( count$=0 OR indexIntoF_na-indexIntoF_nb!=1))
     {
         count$:=count$+1;
         indexIntoF_mid:=(indexIntoF_nb+indexIntoF_na)>>1;
         if(indx>=cftab[indexIntoF_mid]) then 
         {
             indexIntoF_nb:=indexIntoF_mid
         }
         else
         {
             indexIntoF_na:=indexIntoF_mid
         }
     };
     return<==1 and RValue:=indexIntoF_nb;
     skip
     )
     }; 
  function undoReversibleTransformation_small ( int dst )
 {
     frame(undoReversibleTransformation_small_cftab,undoReversibleTransformation_small_cftabAlso,undoReversibleTransformation_small_i,undoReversibleTransformation_small_j,undoReversibleTransformation_small_tmp,undoReversibleTransformation_small_tPos,undoReversibleTransformation_small_ch,count$,undoReversibleTransformation_small_retVal,undoReversibleTransformation_small_i2,undoReversibleTransformation_small_count,undoReversibleTransformation_small_chPrev,undoReversibleTransformation_small_ch2,undoReversibleTransformation_small_localCrc,undoReversibleTransformation_small_rNToGo,undoReversibleTransformation_small_rTPos,undoReversibleTransformation_small_5_11_12_j2,undoReversibleTransformation_small_5_11_12_z) and ( 
     int undoReversibleTransformation_small_cftab[257],undoReversibleTransformation_small_cftabAlso[257] and skip;
     int undoReversibleTransformation_small_i,undoReversibleTransformation_small_j,undoReversibleTransformation_small_tmp,undoReversibleTransformation_small_tPos and skip;
     unsigned char undoReversibleTransformation_small_ch and skip;
     undoReversibleTransformation_small_cftab[0]:=0;
     undoReversibleTransformation_small_i:=1;
     
     while(undoReversibleTransformation_small_i<=256)
     {
         undoReversibleTransformation_small_cftab[undoReversibleTransformation_small_i]:=unzftab[undoReversibleTransformation_small_i-1];
         undoReversibleTransformation_small_i:=undoReversibleTransformation_small_i+1
         
     };
     undoReversibleTransformation_small_i:=1;
     
     while(undoReversibleTransformation_small_i<=256)
     {
         undoReversibleTransformation_small_cftab[undoReversibleTransformation_small_i]:=undoReversibleTransformation_small_cftab[undoReversibleTransformation_small_i]+undoReversibleTransformation_small_cftab[undoReversibleTransformation_small_i-1];
         undoReversibleTransformation_small_i:=undoReversibleTransformation_small_i+1
         
     };
     undoReversibleTransformation_small_i:=0;
     
     while(undoReversibleTransformation_small_i<=256)
     {
         undoReversibleTransformation_small_cftabAlso[undoReversibleTransformation_small_i]:=undoReversibleTransformation_small_cftab[undoReversibleTransformation_small_i];
         undoReversibleTransformation_small_i:=undoReversibleTransformation_small_i+1
         
     };
     undoReversibleTransformation_small_i:=0;
     
     while(undoReversibleTransformation_small_i<=last)
     {
         undoReversibleTransformation_small_ch:=(unsigned char)ll16[undoReversibleTransformation_small_i];
         ll16[undoReversibleTransformation_small_i]:=(unsigned int)(undoReversibleTransformation_small_cftabAlso[undoReversibleTransformation_small_ch] & 0x0000ffff);
         SET_LL4(undoReversibleTransformation_small_i,undoReversibleTransformation_small_cftabAlso[undoReversibleTransformation_small_ch]>>16);
         ll16[undoReversibleTransformation_small_i]:=(unsigned int)(undoReversibleTransformation_small_cftabAlso[undoReversibleTransformation_small_ch] & 0x0000ffff);
         SET_LL4(undoReversibleTransformation_small_i,undoReversibleTransformation_small_cftabAlso[undoReversibleTransformation_small_ch]>>16);
         undoReversibleTransformation_small_cftabAlso[undoReversibleTransformation_small_ch]:=undoReversibleTransformation_small_cftabAlso[undoReversibleTransformation_small_ch]+1;
         undoReversibleTransformation_small_i:=undoReversibleTransformation_small_i+1
         
     };
     undoReversibleTransformation_small_i:=origPtr;
     undoReversibleTransformation_small_j:=(((unsigned int)ll16[undoReversibleTransformation_small_i]) | ((((unsigned int)(ll4[undoReversibleTransformation_small_i>>1]))>>((undoReversibleTransformation_small_i<<2) & 4) & 15)<<16));
     int count$<==0 and skip;
     while( ( count$=0 OR undoReversibleTransformation_small_i!=origPtr))
     {
         count$:=count$+1;
         undoReversibleTransformation_small_tmp:=(((unsigned int)ll16[undoReversibleTransformation_small_j]) | ((((unsigned int)(ll4[undoReversibleTransformation_small_j>>1]))>>((undoReversibleTransformation_small_j<<2) & 4) & 15)<<16));
         ll16[undoReversibleTransformation_small_j]:=(unsigned int)(undoReversibleTransformation_small_i & 0x0000ffff);
         SET_LL4(undoReversibleTransformation_small_j,undoReversibleTransformation_small_i>>16);
         ll16[undoReversibleTransformation_small_j]:=(unsigned int)(undoReversibleTransformation_small_i & 0x0000ffff);
         SET_LL4(undoReversibleTransformation_small_j,undoReversibleTransformation_small_i>>16);
         undoReversibleTransformation_small_i:=undoReversibleTransformation_small_j;
         undoReversibleTransformation_small_j:=undoReversibleTransformation_small_tmp
     };
     undoReversibleTransformation_small_tPos:=origPtr;
     int undoReversibleTransformation_small_retVal and skip;
     int undoReversibleTransformation_small_i2,undoReversibleTransformation_small_count,undoReversibleTransformation_small_chPrev,undoReversibleTransformation_small_ch2 and skip;
     int undoReversibleTransformation_small_localCrc and skip;
     undoReversibleTransformation_small_count:=0;
     undoReversibleTransformation_small_i2:=0;
     undoReversibleTransformation_small_ch2:=256;
     undoReversibleTransformation_small_localCrc:=getGlobalCRC(RValue);
     int undoReversibleTransformation_small_rNToGo<==0 and skip;
     int undoReversibleTransformation_small_rTPos<==0 and skip;
     while(undoReversibleTransformation_small_i2<=last)
     {
         undoReversibleTransformation_small_chPrev:=undoReversibleTransformation_small_ch2;
         undoReversibleTransformation_small_ch2:=indexIntoF(undoReversibleTransformation_small_tPos,undoReversibleTransformation_small_cftab,RValue);
         undoReversibleTransformation_small_tPos:=(((unsigned int)ll16[undoReversibleTransformation_small_tPos]) | ((((unsigned int)(ll4[undoReversibleTransformation_small_tPos>>1]))>>((undoReversibleTransformation_small_tPos<<2) & 4) & 15)<<16));
         if(blockRandomised) then 
         {
             if(undoReversibleTransformation_small_rNToGo=0) then 
             {
                 undoReversibleTransformation_small_rNToGo:=rNums[undoReversibleTransformation_small_rTPos];
                 undoReversibleTransformation_small_rTPos:=undoReversibleTransformation_small_rTPos+1;
                 if(undoReversibleTransformation_small_rTPos=512) then 
                 {
                     undoReversibleTransformation_small_rTPos:=0
                 }
                 else 
                 {
                      skip 
                 }
                 
             }
             else 
             {
                  skip 
             };
             undoReversibleTransformation_small_rNToGo:=undoReversibleTransformation_small_rNToGo-1;
             undoReversibleTransformation_small_ch2:=undoReversibleTransformation_small_ch2^ ((unsigned int)(( if((undoReversibleTransformation_small_rNToGo=1)) then 1 else 0)))
             
         }
         else 
         {
              skip 
         };
         undoReversibleTransformation_small_i2:=undoReversibleTransformation_small_i2+1;
         if(dst) then 
         {
             undoReversibleTransformation_small_retVal:=spec_putc(undoReversibleTransformation_small_ch2,dst,RValue)
         }
         else 
         {
              skip 
         };
         undoReversibleTransformation_small_localCrc:=(undoReversibleTransformation_small_localCrc<<8) ^ crc32Table[(undoReversibleTransformation_small_localCrc>>24) ^ ((unsigned char)undoReversibleTransformation_small_ch2)];
         if(undoReversibleTransformation_small_ch2!=undoReversibleTransformation_small_chPrev) then 
         {
             undoReversibleTransformation_small_count:=1
         }
         else
         {
             undoReversibleTransformation_small_count:=undoReversibleTransformation_small_count+1;
             if(undoReversibleTransformation_small_count>=4) then 
             {
                 int undoReversibleTransformation_small_5_11_12_j2 and skip;
                 unsigned char undoReversibleTransformation_small_5_11_12_z and skip;
                 undoReversibleTransformation_small_5_11_12_z:=indexIntoF(undoReversibleTransformation_small_tPos,undoReversibleTransformation_small_cftab,RValue);
                 undoReversibleTransformation_small_tPos:=(((unsigned int)ll16[undoReversibleTransformation_small_tPos]) | ((((unsigned int)(ll4[undoReversibleTransformation_small_tPos>>1]))>>((undoReversibleTransformation_small_tPos<<2) & 4) & 15)<<16));
                 if(blockRandomised) then 
                 {
                     if(undoReversibleTransformation_small_rNToGo=0) then 
                     {
                         undoReversibleTransformation_small_rNToGo:=rNums[undoReversibleTransformation_small_rTPos];
                         undoReversibleTransformation_small_rTPos:=undoReversibleTransformation_small_rTPos+1;
                         if(undoReversibleTransformation_small_rTPos=512) then 
                         {
                             undoReversibleTransformation_small_rTPos:=0
                         }
                         else 
                         {
                              skip 
                         }
                         
                     }
                     else 
                     {
                          skip 
                     };
                     undoReversibleTransformation_small_rNToGo:=undoReversibleTransformation_small_rNToGo-1;
                     undoReversibleTransformation_small_5_11_12_z:=undoReversibleTransformation_small_5_11_12_z^ (( if((undoReversibleTransformation_small_rNToGo=1)) then 1 else 0))
                     
                 }
                 else 
                 {
                      skip 
                 };
                 undoReversibleTransformation_small_5_11_12_j2:=0;
                 
                 while(undoReversibleTransformation_small_5_11_12_j2<(int)undoReversibleTransformation_small_5_11_12_z)
                 {
                     if(dst) then 
                     {
                         undoReversibleTransformation_small_retVal:=spec_putc(undoReversibleTransformation_small_ch2,dst,RValue)
                     }
                     else 
                     {
                          skip 
                     };
                     undoReversibleTransformation_small_localCrc:=(undoReversibleTransformation_small_localCrc<<8) ^ crc32Table[(undoReversibleTransformation_small_localCrc>>24) ^ ((unsigned char)undoReversibleTransformation_small_ch2)];
                     undoReversibleTransformation_small_5_11_12_j2:=undoReversibleTransformation_small_5_11_12_j2+1
                     
                 };
                 undoReversibleTransformation_small_i2:=undoReversibleTransformation_small_i2+1;
                 undoReversibleTransformation_small_count:=0
                 
             }
             else 
             {
                  skip 
             }
         }
     };
     setGlobalCRC(undoReversibleTransformation_small_localCrc)
     )
     }; 
  function undoReversibleTransformation_fast ( int dst )
 {
     frame(undoReversibleTransformation_fast_cftab,undoReversibleTransformation_fast_i,undoReversibleTransformation_fast_tPos,undoReversibleTransformation_fast_ch,undoReversibleTransformation_fast_retVal,undoReversibleTransformation_fast_i2,undoReversibleTransformation_fast_count,undoReversibleTransformation_fast_chPrev,undoReversibleTransformation_fast_ch2,undoReversibleTransformation_fast_localCrc,undoReversibleTransformation_fast_3_rNToGo,undoReversibleTransformation_fast_3_rTPos,undoReversibleTransformation_fast_3_4_8_9_j2,undoReversibleTransformation_fast_3_4_8_9_z,undoReversibleTransformation_fast_12_13_15_16_j2,undoReversibleTransformation_fast_12_13_15_16_z) and ( 
     int undoReversibleTransformation_fast_cftab[257] and skip;
     int undoReversibleTransformation_fast_i,undoReversibleTransformation_fast_tPos and skip;
     unsigned char undoReversibleTransformation_fast_ch and skip;
     undoReversibleTransformation_fast_cftab[0]:=0;
     undoReversibleTransformation_fast_i:=1;
     
     while(undoReversibleTransformation_fast_i<=256)
     {
         undoReversibleTransformation_fast_cftab[undoReversibleTransformation_fast_i]:=unzftab[undoReversibleTransformation_fast_i-1];
         undoReversibleTransformation_fast_i:=undoReversibleTransformation_fast_i+1
         
     };
     undoReversibleTransformation_fast_i:=1;
     
     while(undoReversibleTransformation_fast_i<=256)
     {
         undoReversibleTransformation_fast_cftab[undoReversibleTransformation_fast_i]:=undoReversibleTransformation_fast_cftab[undoReversibleTransformation_fast_i]+undoReversibleTransformation_fast_cftab[undoReversibleTransformation_fast_i-1];
         undoReversibleTransformation_fast_i:=undoReversibleTransformation_fast_i+1
         
     };
     undoReversibleTransformation_fast_i:=0;
     
     while(undoReversibleTransformation_fast_i<=last)
     {
         undoReversibleTransformation_fast_ch:=(unsigned char)ll8[undoReversibleTransformation_fast_i];
         tt[undoReversibleTransformation_fast_cftab[undoReversibleTransformation_fast_ch]]:=undoReversibleTransformation_fast_i;
         undoReversibleTransformation_fast_cftab[undoReversibleTransformation_fast_ch]:=undoReversibleTransformation_fast_cftab[undoReversibleTransformation_fast_ch]+1;
         undoReversibleTransformation_fast_i:=undoReversibleTransformation_fast_i+1
         
     };
     undoReversibleTransformation_fast_tPos:=tt[origPtr];
     int undoReversibleTransformation_fast_retVal and skip;
     int undoReversibleTransformation_fast_i2,undoReversibleTransformation_fast_count,undoReversibleTransformation_fast_chPrev,undoReversibleTransformation_fast_ch2 and skip;
     int undoReversibleTransformation_fast_localCrc and skip;
     undoReversibleTransformation_fast_count:=0;
     undoReversibleTransformation_fast_i2:=0;
     undoReversibleTransformation_fast_ch2:=256;
     undoReversibleTransformation_fast_localCrc:=getGlobalCRC(RValue);
     if(blockRandomised) then 
     {
         int undoReversibleTransformation_fast_3_rNToGo<==0 and skip;
         int undoReversibleTransformation_fast_3_rTPos<==0 and skip;
         while(undoReversibleTransformation_fast_i2<=last)
         {
             undoReversibleTransformation_fast_chPrev:=undoReversibleTransformation_fast_ch2;
             undoReversibleTransformation_fast_ch2:=ll8[undoReversibleTransformation_fast_tPos];
             undoReversibleTransformation_fast_tPos:=tt[undoReversibleTransformation_fast_tPos];
             if(undoReversibleTransformation_fast_3_rNToGo=0) then 
             {
                 undoReversibleTransformation_fast_3_rNToGo:=rNums[undoReversibleTransformation_fast_3_rTPos];
                 undoReversibleTransformation_fast_3_rTPos:=undoReversibleTransformation_fast_3_rTPos+1;
                 if(undoReversibleTransformation_fast_3_rTPos=512) then 
                 {
                     undoReversibleTransformation_fast_3_rTPos:=0
                 }
                 else 
                 {
                      skip 
                 }
                 
             }
             else 
             {
                  skip 
             };
             undoReversibleTransformation_fast_3_rNToGo:=undoReversibleTransformation_fast_3_rNToGo-1;
             undoReversibleTransformation_fast_ch2:=undoReversibleTransformation_fast_ch2^ ((unsigned int)(( if((undoReversibleTransformation_fast_3_rNToGo=1)) then 1 else 0)));
             undoReversibleTransformation_fast_i2:=undoReversibleTransformation_fast_i2+1;
             undoReversibleTransformation_fast_retVal:=spec_putc(undoReversibleTransformation_fast_ch2,dst,RValue);
             undoReversibleTransformation_fast_localCrc:=(undoReversibleTransformation_fast_localCrc<<8) ^ crc32Table[(undoReversibleTransformation_fast_localCrc>>24) ^ ((unsigned char)undoReversibleTransformation_fast_ch2)];
             if(undoReversibleTransformation_fast_ch2!=undoReversibleTransformation_fast_chPrev) then 
             {
                 undoReversibleTransformation_fast_count:=1
             }
             else
             {
                 undoReversibleTransformation_fast_count:=undoReversibleTransformation_fast_count+1;
                 if(undoReversibleTransformation_fast_count>=4) then 
                 {
                     int undoReversibleTransformation_fast_3_4_8_9_j2 and skip;
                     unsigned char undoReversibleTransformation_fast_3_4_8_9_z and skip;
                     undoReversibleTransformation_fast_3_4_8_9_z:=ll8[undoReversibleTransformation_fast_tPos];
                     undoReversibleTransformation_fast_tPos:=tt[undoReversibleTransformation_fast_tPos];
                     if(undoReversibleTransformation_fast_3_rNToGo=0) then 
                     {
                         undoReversibleTransformation_fast_3_rNToGo:=rNums[undoReversibleTransformation_fast_3_rTPos];
                         undoReversibleTransformation_fast_3_rTPos:=undoReversibleTransformation_fast_3_rTPos+1;
                         if(undoReversibleTransformation_fast_3_rTPos=512) then 
                         {
                             undoReversibleTransformation_fast_3_rTPos:=0
                         }
                         else 
                         {
                              skip 
                         }
                         
                     }
                     else 
                     {
                          skip 
                     };
                     undoReversibleTransformation_fast_3_rNToGo:=undoReversibleTransformation_fast_3_rNToGo-1;
                     undoReversibleTransformation_fast_3_4_8_9_z:=undoReversibleTransformation_fast_3_4_8_9_z^ (( if((undoReversibleTransformation_fast_3_rNToGo=1)) then 1 else 0));
                     undoReversibleTransformation_fast_3_4_8_9_j2:=0;
                     
                     while(undoReversibleTransformation_fast_3_4_8_9_j2<(int)undoReversibleTransformation_fast_3_4_8_9_z)
                     {
                         undoReversibleTransformation_fast_retVal:=spec_putc(undoReversibleTransformation_fast_ch2,dst,RValue);
                         undoReversibleTransformation_fast_localCrc:=(undoReversibleTransformation_fast_localCrc<<8) ^ crc32Table[(undoReversibleTransformation_fast_localCrc>>24) ^ ((unsigned char)undoReversibleTransformation_fast_ch2)];
                         undoReversibleTransformation_fast_3_4_8_9_j2:=undoReversibleTransformation_fast_3_4_8_9_j2+1
                         
                     };
                     undoReversibleTransformation_fast_i2:=undoReversibleTransformation_fast_i2+1;
                     undoReversibleTransformation_fast_count:=0
                     
                 }
                 else 
                 {
                      skip 
                 }
             }
         }
         
     }
     else
     {
         while(undoReversibleTransformation_fast_i2<=last)
         {
             undoReversibleTransformation_fast_chPrev:=undoReversibleTransformation_fast_ch2;
             undoReversibleTransformation_fast_ch2:=ll8[undoReversibleTransformation_fast_tPos];
             undoReversibleTransformation_fast_tPos:=tt[undoReversibleTransformation_fast_tPos];
             undoReversibleTransformation_fast_i2:=undoReversibleTransformation_fast_i2+1;
             undoReversibleTransformation_fast_retVal:=spec_putc(undoReversibleTransformation_fast_ch2,dst,RValue);
             undoReversibleTransformation_fast_localCrc:=(undoReversibleTransformation_fast_localCrc<<8) ^ crc32Table[(undoReversibleTransformation_fast_localCrc>>24) ^ ((unsigned char)undoReversibleTransformation_fast_ch2)];
             if(undoReversibleTransformation_fast_ch2!=undoReversibleTransformation_fast_chPrev) then 
             {
                 undoReversibleTransformation_fast_count:=1
             }
             else
             {
                 undoReversibleTransformation_fast_count:=undoReversibleTransformation_fast_count+1;
                 if(undoReversibleTransformation_fast_count>=4) then 
                 {
                     int undoReversibleTransformation_fast_12_13_15_16_j2 and skip;
                     unsigned char undoReversibleTransformation_fast_12_13_15_16_z and skip;
                     undoReversibleTransformation_fast_12_13_15_16_z:=ll8[undoReversibleTransformation_fast_tPos];
                     undoReversibleTransformation_fast_tPos:=tt[undoReversibleTransformation_fast_tPos];
                     undoReversibleTransformation_fast_12_13_15_16_j2:=0;
                     
                     while(undoReversibleTransformation_fast_12_13_15_16_j2<(int)undoReversibleTransformation_fast_12_13_15_16_z)
                     {
                         undoReversibleTransformation_fast_retVal:=spec_putc(undoReversibleTransformation_fast_ch2,dst,RValue);
                         undoReversibleTransformation_fast_localCrc:=(undoReversibleTransformation_fast_localCrc<<8) ^ crc32Table[(undoReversibleTransformation_fast_localCrc>>24) ^ ((unsigned char)undoReversibleTransformation_fast_ch2)];
                         undoReversibleTransformation_fast_12_13_15_16_j2:=undoReversibleTransformation_fast_12_13_15_16_j2+1
                         
                     };
                     undoReversibleTransformation_fast_i2:=undoReversibleTransformation_fast_i2+1;
                     undoReversibleTransformation_fast_count:=0
                     
                 }
                 else 
                 {
                      skip 
                 }
             }
         }
     };
     setGlobalCRC(undoReversibleTransformation_fast_localCrc)
     )
     }; 
  function getRLEpair ( int src,int RValue )
 {
     frame(getRLEpair_runLength,getRLEpair_ch,getRLEpair_chLatest,count$,getRLEpair_7_i,return) and ( 
     int return<==0 and skip;
     int getRLEpair_runLength and skip;
     int getRLEpair_ch,getRLEpair_chLatest and skip;
     getRLEpair_ch:=spec_getc(src,RValue);
     if((getRLEpair_ch)=(-1)) then 
     {
         ERROR_IF_NOT_ZERO(0);
         return<==1 and RValue:=(1<<16) | 257;
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         getRLEpair_runLength:=0;
         int count$<==0 and skip;
         while( ( count$=0 OR getRLEpair_ch=getRLEpair_chLatest AND getRLEpair_runLength<255))
         {
             count$:=count$+1;
             getRLEpair_chLatest:=spec_getc(src,RValue);
             getRLEpair_runLength:=getRLEpair_runLength+1;
             bytesIn:=bytesIn+1
         };
         if((getRLEpair_chLatest)!=(-1)) then 
         {
             if(((extern spec_ungetc(getRLEpair_chLatest,src,RValue)))=(-1)) then 
             {
                 panic("getRLEpair: ungetc failed")
             }
             else 
             {
                  skip 
             }
             
         }
         else
         {
             ERROR_IF_NOT_ZERO(0)
         };
         if(getRLEpair_runLength=1) then 
         {
             globalCrc:=(globalCrc<<8) ^ crc32Table[(globalCrc>>24) ^ ((unsigned char)getRLEpair_ch)];
             return<==1 and RValue:=(1<<16) | getRLEpair_ch;
             skip
         }
         else
         {
             int getRLEpair_7_i and skip;
             getRLEpair_7_i:=1;
             
             while(getRLEpair_7_i<=getRLEpair_runLength)
             {
                 globalCrc:=(globalCrc<<8) ^ crc32Table[(globalCrc>>24) ^ ((unsigned char)getRLEpair_ch)];
                 getRLEpair_7_i:=getRLEpair_7_i+1
                 
             };
             return<==1 and RValue:=(getRLEpair_runLength<<16) | getRLEpair_ch;
             skip
         }
     }
     else
     {
         skip
     }
     )
     }; 
  function loadAndRLEsource ( int src )
 {
     frame(loadAndRLEsource_ch,loadAndRLEsource_allowableBlockSize,loadAndRLEsource_i,loadAndRLEsource_2_rlePair,loadAndRLEsource_2_runLen,nm_3$,break$$$,switch$,return) and ( 
     int return<==0 and skip;
     int loadAndRLEsource_ch,loadAndRLEsource_allowableBlockSize,loadAndRLEsource_i and skip;
     last:=-1;
     loadAndRLEsource_ch:=0;
     loadAndRLEsource_i:=0;
     
     while(loadAndRLEsource_i<256)
     {
         inUse[loadAndRLEsource_i]:=0;
         loadAndRLEsource_i:=loadAndRLEsource_i+1
         
     };
     loadAndRLEsource_allowableBlockSize:=100000*blockSize100k-20;
     while(last<loadAndRLEsource_allowableBlockSize AND loadAndRLEsource_ch!=257)
     {
         int loadAndRLEsource_2_rlePair,loadAndRLEsource_2_runLen and skip;
         loadAndRLEsource_2_rlePair:=getRLEpair(src,RValue);
         loadAndRLEsource_ch:=loadAndRLEsource_2_rlePair & 65535;
         loadAndRLEsource_2_runLen:=(unsigned int)loadAndRLEsource_2_rlePair>>16;
         if(loadAndRLEsource_ch!=257) then 
         {
             inUse[loadAndRLEsource_ch]:=1;
             int switch$ and skip;
             int break$$$ and skip;
             break$$$<==0 and skip;
              switch$<==0 and skip;
              int nm_3$ and skip;
             nm_3$ := loadAndRLEsource_2_runLen;
             if (nm_3$=1 OR (switch$=1 AND break$$$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 last:=last+1;
                 block[last]:=(unsigned char)loadAndRLEsource_ch;
                 break$$$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             if (nm_3$=2 OR (switch$=1 AND break$$$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 last:=last+1;
                 block[last]:=(unsigned char)loadAndRLEsource_ch;
                 last:=last+1;
                 block[last]:=(unsigned char)loadAndRLEsource_ch;
                 break$$$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             if (nm_3$=3 OR (switch$=1 AND break$$$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 last:=last+1;
                 block[last]:=(unsigned char)loadAndRLEsource_ch;
                 last:=last+1;
                 block[last]:=(unsigned char)loadAndRLEsource_ch;
                 last:=last+1;
                 block[last]:=(unsigned char)loadAndRLEsource_ch;
                 break$$$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             if(break$$$=0 AND return=0) then 
             {
                 inUse[loadAndRLEsource_2_runLen-4]:=1;
                 last:=last+1;
                 block[last]:=(unsigned char)loadAndRLEsource_ch;
                 last:=last+1;
                 block[last]:=(unsigned char)loadAndRLEsource_ch;
                 last:=last+1;
                 block[last]:=(unsigned char)loadAndRLEsource_ch;
                 last:=last+1;
                 block[last]:=(unsigned char)loadAndRLEsource_ch;
                 last:=last+1;
                 block[last]:=(unsigned char)(loadAndRLEsource_2_runLen-4);
                 break$$$<==1 and skip
                  
             }
             else
             {
                  skip
             }
         }
         else 
         {
              skip 
         }
     }
     )
     }; 
  function compressStream ( int stream,int zStream )
 {
     frame(compressStream_retVal,compressStream_blockCRC,compressStream_combinedCRC,compressStream_blockNo,break$$) and ( 
     int break$$<==0 and skip;
     int compressStream_retVal and skip;
     int compressStream_blockCRC,compressStream_combinedCRC and skip;
     int compressStream_blockNo and skip;
     compressStream_blockNo:=0;
     bytesIn:=0;
     bytesOut:=0;
     nBlocksRandomised:=0;
     ERROR_IF_NOT_ZERO(0);
     ERROR_IF_NOT_ZERO(0);
     bsSetStream(zStream,1);
     bsPutUChar('B');
     bsPutUChar('Z');
     bsPutUChar('h');
     bsPutUChar('0'+blockSize100k);
     compressStream_combinedCRC:=0;
     if(verbosity>=2) then 
     {
         fprintf(stdout,"\n",RValue) and skip
     }
     else 
     {
          skip 
     };
     break$$<==0 and skip;
     while( break$$=0)
     {
         compressStream_blockNo:=compressStream_blockNo+1;
         initialiseCRC();
         loadAndRLEsource(stream);
         ERROR_IF_NOT_ZERO(0);
         if(last=-1) then 
         {
             break$$<==1 and skip
          }
         else 
         {
              skip 
         };
         if(break$$=0)   then
         {
             compressStream_blockCRC:=getFinalCRC(RValue);
             compressStream_combinedCRC:=(compressStream_combinedCRC<<1) | (compressStream_combinedCRC>>31);
             compressStream_combinedCRC:=compressStream_combinedCRC^ (compressStream_blockCRC);
             if(verbosity>=2) then 
             {
                 fprintf(stdout,"    block %d: crc = 0x%8x, combined CRC = 0x%8x, size = %d",compressStream_blockNo,compressStream_blockCRC,compressStream_combinedCRC,last+1,RValue) and skip
             }
             else 
             {
                  skip 
             };
             doReversibleTransformation();
             bsPutUChar(49);
             bsPutUChar(65);
             bsPutUChar(89);
             bsPutUChar(38);
             bsPutUChar(83);
             bsPutUChar(89);
             bsPutUInt32(compressStream_blockCRC);
             if(blockRandomised) then 
             {
                 bsW(1,1);
                 nBlocksRandomised:=nBlocksRandomised+1
                 
             }
             else
             {
                 bsW(1,0)
             };
             moveToFrontCodeAndSend();
             ERROR_IF_NOT_ZERO(0)
         }
         else
         {
             skip
         }
     };
     break$$<==0 and skip;
     if(verbosity>=2 AND nBlocksRandomised>0) then 
     {
         fprintf(stdout,"    %d block%s needed randomisation\n",nBlocksRandomised,( if(nBlocksRandomised=1) then "" else "s"),RValue) and skip
     }
     else 
     {
          skip 
     };
     bsPutUChar(23);
     bsPutUChar(114);
     bsPutUChar(69);
     bsPutUChar(56);
     bsPutUChar(80);
     bsPutUChar(144);
     bsPutUInt32(compressStream_combinedCRC);
     if(verbosity>=2) then 
     {
         fprintf(stdout,"    final combined CRC = 0x%x\n   ",compressStream_combinedCRC,RValue) and skip
     }
     else 
     {
          skip 
     };
     bsFinishedWithStream();
     ERROR_IF_NOT_ZERO(0);
     compressStream_retVal:=0;
     ERROR_IF_EOF(compressStream_retVal);
     compressStream_retVal:=0;
     ERROR_IF_EOF(compressStream_retVal);
     ERROR_IF_NOT_ZERO(0);
     compressStream_retVal:=0;
     ERROR_IF_EOF(compressStream_retVal);
     if(bytesIn=0) then 
     {
         bytesIn:=1
     }
     else 
     {
          skip 
     };
     if(bytesOut=0) then 
     {
         bytesOut:=1
     }
     else 
     {
          skip 
     };
     if(verbosity>=1) then 
     {
         fprintf(stdout,"%6.3f:1, %6.3f bits/byte, ","%5.2f%% saved, %d in, %d out.\n",(float)bytesIn/ (float)bytesOut,(8.0*(float)bytesOut)/ (float)bytesIn,100.0*(1.0-(float)bytesOut/ (float)bytesIn),bytesIn,bytesOut,RValue) and skip
     }
     else 
     {
          skip 
     }
     )
     }; 
  function uncompressStream ( int zStream,int stream,unsigned char RValue )
 {
     frame(uncompressStream_magic1,uncompressStream_magic2,uncompressStream_magic3,uncompressStream_magic4,uncompressStream_magic5,uncompressStream_magic6,uncompressStream_storedBlockCRC,uncompressStream_storedCombinedCRC,uncompressStream_computedBlockCRC,uncompressStream_computedCombinedCRC,uncompressStream_currBlockNo,uncompressStream_retVal,return,break$$) and ( 
     int break$$<==0 and skip;
     int return<==0 and skip;
     unsigned char uncompressStream_magic1,uncompressStream_magic2,uncompressStream_magic3,uncompressStream_magic4 and skip;
     unsigned char uncompressStream_magic5,uncompressStream_magic6 and skip;
     int uncompressStream_storedBlockCRC,uncompressStream_storedCombinedCRC and skip;
     int uncompressStream_computedBlockCRC,uncompressStream_computedCombinedCRC and skip;
     int uncompressStream_currBlockNo and skip;
     int uncompressStream_retVal and skip;
     ERROR_IF_NOT_ZERO(0);
     ERROR_IF_NOT_ZERO(0);
     bsSetStream(zStream,0);
     uncompressStream_magic1:=bsGetUChar(RValue);
     uncompressStream_magic2:=bsGetUChar(RValue);
     uncompressStream_magic3:=bsGetUChar(RValue);
     uncompressStream_magic4:=bsGetUChar(RValue);
     if(uncompressStream_magic1!='B' OR uncompressStream_magic2!='Z' OR uncompressStream_magic3!='h' OR uncompressStream_magic4<'1' OR uncompressStream_magic4>'9') then 
     {
         bsFinishedWithStream();
         uncompressStream_retVal:=0;
         ERROR_IF_EOF(uncompressStream_retVal);
         return<==1 and RValue:=0;
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         setDecompressStructureSizes(uncompressStream_magic4-'0');
		 //output("yubin7111\n") and skip;
         uncompressStream_computedCombinedCRC:=0;
         if(verbosity>=2) then 
         {
             fprintf(stdout,"\n    ",RValue) and skip
         }
         else 
         {
              skip 
         };
         uncompressStream_currBlockNo:=0;
         break$$<==0 and skip;
         while( break$$=0 AND  1)
         {
             uncompressStream_magic1:=bsGetUChar(RValue);
             uncompressStream_magic2:=bsGetUChar(RValue);
             uncompressStream_magic3:=bsGetUChar(RValue);
             uncompressStream_magic4:=bsGetUChar(RValue);
             uncompressStream_magic5:=bsGetUChar(RValue);
             uncompressStream_magic6:=bsGetUChar(RValue);
             if(uncompressStream_magic1=23 AND uncompressStream_magic2=114 AND uncompressStream_magic3=69 AND uncompressStream_magic4=56 AND uncompressStream_magic5=80 AND uncompressStream_magic6=144) then 
             {
                 break$$<==1 and skip
              }
             else 
             {
                  skip 
             };
             if(break$$=0)   then
             {
                 if(uncompressStream_magic1!=49 OR uncompressStream_magic2!=65 OR uncompressStream_magic3!=89 OR uncompressStream_magic4!=38 OR uncompressStream_magic5!=83 OR uncompressStream_magic6!=89) then 
                 {
                     badBlockHeader()
                 }
                 else 
                 {
                      skip 
                 };
                 uncompressStream_storedBlockCRC:=bsGetUInt32(RValue);
                 if(extern bsR(1,RValue)=1) then 
                 {
                     blockRandomised:=1
                 }
                 else
                 {
                     blockRandomised:=0
                 };
                 uncompressStream_currBlockNo:=uncompressStream_currBlockNo+1;
                 if(verbosity>=2) then 
                 {
                     fprintf(stdout,"[%d: huff+mtf ",uncompressStream_currBlockNo,RValue) and skip
                 }
                 else 
                 {
                      skip 
                 };
                 getAndMoveToFrontDecode();
                 ERROR_IF_NOT_ZERO(0);
                 initialiseCRC();
                 if(verbosity>=2) then 
                 {
                     fprintf(stdout,"rt+rld",RValue) and skip
                 }
                 else 
                 {
                      skip 
                 };
                 if(smallMode) then 
                 {
                     undoReversibleTransformation_small(stream)
                 }
                 else
                 {
                     undoReversibleTransformation_fast(stream)
                 };
                 ERROR_IF_NOT_ZERO(0);
                 uncompressStream_computedBlockCRC:=getFinalCRC(RValue);
                 if(verbosity>=3) then 
                 {
                     fprintf(stdout," {0x%x, 0x%x}",uncompressStream_storedBlockCRC,uncompressStream_computedBlockCRC,RValue) and skip
                 }
                 else 
                 {
                      skip 
                 };
                 if(verbosity>=2) then 
                 {
                     fprintf(stdout,"] ",RValue) and skip
                 }
                 else 
                 {
                      skip 
                 };
                 if(uncompressStream_storedBlockCRC!=uncompressStream_computedBlockCRC) then 
                 {
                     crcError(uncompressStream_storedBlockCRC,uncompressStream_computedBlockCRC)
                 }
                 else 
                 {
                      skip 
                 };
                 uncompressStream_computedCombinedCRC:=(uncompressStream_computedCombinedCRC<<1) | (uncompressStream_computedCombinedCRC>>31);
                 uncompressStream_computedCombinedCRC:=uncompressStream_computedCombinedCRC^ (uncompressStream_computedBlockCRC)
             }
             else
             {
                 skip
             }
         };
         break$$<==0 and skip;
         if(verbosity>=2) then 
         {
             fprintf(stdout,"\n    ",RValue) and skip
         }
         else 
         {
              skip 
         };
         uncompressStream_storedCombinedCRC:=bsGetUInt32(RValue);
         if(verbosity>=2) then 
         {
             fprintf(stdout,"combined CRCs: stored = 0x%x, computed = 0x%x\n    ",uncompressStream_storedCombinedCRC,uncompressStream_computedCombinedCRC,RValue) and skip
         }
         else 
         {
              skip 
         };
         if(uncompressStream_storedCombinedCRC!=uncompressStream_computedCombinedCRC) then 
         {
             crcError(uncompressStream_storedCombinedCRC,uncompressStream_computedCombinedCRC)
         }
         else 
         {
              skip 
         };
         bsFinishedWithStream();
         ERROR_IF_NOT_ZERO(0);
         uncompressStream_retVal:=0;
         ERROR_IF_EOF(uncompressStream_retVal);
         ERROR_IF_NOT_ZERO(0);
         uncompressStream_retVal:=0;
         ERROR_IF_NOT_ZERO(uncompressStream_retVal);
         return<==1 and RValue:=1;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function testStream ( int zStream,unsigned char RValue )
 {
     frame(testStream_magic1,testStream_magic2,testStream_magic3,testStream_magic4,testStream_magic5,testStream_magic6,testStream_storedBlockCRC,testStream_storedCombinedCRC,testStream_computedBlockCRC,testStream_computedCombinedCRC,testStream_currBlockNo,testStream_retVal,return,break$$) and ( 
     int break$$<==0 and skip;
     int return<==0 and skip;
     unsigned char testStream_magic1,testStream_magic2,testStream_magic3,testStream_magic4 and skip;
     unsigned char testStream_magic5,testStream_magic6 and skip;
     int testStream_storedBlockCRC,testStream_storedCombinedCRC and skip;
     int testStream_computedBlockCRC,testStream_computedCombinedCRC and skip;
     int testStream_currBlockNo and skip;
     int testStream_retVal and skip;
     ERROR_IF_NOT_ZERO(0);
     bsSetStream(zStream,0);
     testStream_magic1:=bsGetUChar(RValue);
     testStream_magic2:=bsGetUChar(RValue);
     testStream_magic3:=bsGetUChar(RValue);
     testStream_magic4:=bsGetUChar(RValue);
     if(testStream_magic1!='B' OR testStream_magic2!='Z' OR testStream_magic3!='h' OR testStream_magic4<'1' OR testStream_magic4>'9') then 
     {
         bsFinishedWithStream();
         fclose(zStream) and skip;
         fprintf(stdout,"\n%s: bad magic number (ie, not created by bzip2)\n",inName,RValue) and skip;
         return<==1 and RValue:=0;
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         smallMode:=1;
         setDecompressStructureSizes(testStream_magic4-'0');
		 //output("yubin7222\n") and skip;
         testStream_computedCombinedCRC:=0;
         if(verbosity>=2) then 
         {
             fprintf(stdout,"\n",RValue) and skip
         }
         else 
         {
              skip 
         };
         testStream_currBlockNo:=0;
         break$$<==0 and skip;
         while( return=0 AND   break$$=0 AND  1)
         {
             testStream_magic1:=bsGetUChar(RValue);
             testStream_magic2:=bsGetUChar(RValue);
             testStream_magic3:=bsGetUChar(RValue);
             testStream_magic4:=bsGetUChar(RValue);
             testStream_magic5:=bsGetUChar(RValue);
             testStream_magic6:=bsGetUChar(RValue);
             if(testStream_magic1=23 AND testStream_magic2=114 AND testStream_magic3=69 AND testStream_magic4=56 AND testStream_magic5=80 AND testStream_magic6=144) then 
             {
                 break$$<==1 and skip
              }
             else 
             {
                  skip 
             };
             if(break$$=0)   then
             {
                 testStream_currBlockNo:=testStream_currBlockNo+1;
                 if(testStream_magic1!=49 OR testStream_magic2!=65 OR testStream_magic3!=89 OR testStream_magic4!=38 OR testStream_magic5!=83 OR testStream_magic6!=89) then 
                 {
                     bsFinishedWithStream();
                     fclose(zStream) and skip;
                     fprintf(stdout,"\n%s, block %d: bad header (not == 0x314159265359)\n",inName,testStream_currBlockNo,RValue) and skip;
                     return<==1 and RValue:=0;
                     skip
                     
                 }
                 else 
                 {
                      skip 
                 };
                 if(return=0)   then 
                 {
                     testStream_storedBlockCRC:=bsGetUInt32(RValue);
                     if(extern bsR(1,RValue)=1) then 
                     {
                         blockRandomised:=1
                     }
                     else
                     {
                         blockRandomised:=0
                     };
                     if(verbosity>=2) then 
                     {
                         fprintf(stdout,"    block [%d: huff+mtf ",testStream_currBlockNo,RValue) and skip
                     }
                     else 
                     {
                          skip 
                     };
                     getAndMoveToFrontDecode();
                     ERROR_IF_NOT_ZERO(0);
                     initialiseCRC();
                     if(verbosity>=2) then 
                     {
                         fprintf(stdout,"rt+rld",RValue) and skip
                     }
                     else 
                     {
                          skip 
                     };
                     undoReversibleTransformation_small(0);
                     testStream_computedBlockCRC:=getFinalCRC(RValue);
                     if(verbosity>=3) then 
                     {
                         fprintf(stdout," {0x%x, 0x%x}",testStream_storedBlockCRC,testStream_computedBlockCRC,RValue) and skip
                     }
                     else 
                     {
                          skip 
                     };
                     if(verbosity>=2) then 
                     {
                         fprintf(stdout,"] ",RValue) and skip
                     }
                     else 
                     {
                          skip 
                     };
                     if(testStream_storedBlockCRC!=testStream_computedBlockCRC) then 
                     {
                         bsFinishedWithStream();
                         fclose(zStream) and skip;
                         fprintf(stdout,"\n%s, block %d: computed CRC does not match stored one\n",inName,testStream_currBlockNo,RValue) and skip;
                         return<==1 and RValue:=0;
                         skip
                         
                     }
                     else 
                     {
                          skip 
                     };
                     if(return=0)   then 
                     {
                         if(verbosity>=2) then 
                         {
                             fprintf(stdout,"ok\n",RValue) and skip
                         }
                         else 
                         {
                              skip 
                         };
                         testStream_computedCombinedCRC:=(testStream_computedCombinedCRC<<1) | (testStream_computedCombinedCRC>>31);
                         testStream_computedCombinedCRC:=testStream_computedCombinedCRC^ (testStream_computedBlockCRC)
                     }
                     else
                     {
                         skip
                     }
                 }
                 else
                 {
                     skip
                 }
             }
             else
             {
                 skip
             }
         };
         break$$<==0 and skip;
         if(return=0)   then 
         {
             testStream_storedCombinedCRC:=bsGetUInt32(RValue);
             if(verbosity>=2) then 
             {
                 fprintf(stdout,"    combined CRCs: stored = 0x%x, computed = 0x%x\n    ",testStream_storedCombinedCRC,testStream_computedCombinedCRC,RValue) and skip
             }
             else 
             {
                  skip 
             };
             if(testStream_storedCombinedCRC!=testStream_computedCombinedCRC) then 
             {
                 bsFinishedWithStream();
                 fclose(zStream) and skip;
                 fprintf(stdout,"\n%s: computed CRC does not match stored one\n",inName,RValue) and skip;
                 return<==1 and RValue:=0;
                 skip
                 
             }
             else 
             {
                  skip 
             };
             if(return=0)   then 
             {
                 bsFinishedWithStream();
                 ERROR_IF_NOT_ZERO(0);
                 testStream_retVal:=0;
                 ERROR_IF_EOF(testStream_retVal);
                 return<==1 and RValue:=1;
                 skip
             }
             else
             {
                 skip
             }
         }
         else
         {
             skip
         }
     }
     else
     {
         skip
     }
     )
     }; 
  function cadvise (  )
 {
     fprintf(stdout,"\nIt is possible that the compressed file(s) have become corrupted.\n","You can use the -tvv option to test integrity of such files.\n\n","You can use the `bzip2recover' program to *attempt* to recover\n","data from undamaged sections of corrupted files.\n\n",RValue) and skip and skip
     
 };
 function showFileNames (  )
 {
     fprintf(stdout,"\tInput file = %s, output file = %s\n",( if(inName=NULL) then "(null)" else inName),( if(outName=NULL) then "(null)" else outName),RValue) and skip
     
 };
 function cleanUpAndFail ( int ec )
 {
     frame(cleanUpAndFail_retVal) and ( 
     int cleanUpAndFail_retVal and skip;
     if(srcMode=3 AND opMode!=3) then 
     {
         fprintf(stdout,"%s: Deleting output file %s, if it exists.\n",progName,( if(outName=NULL) then "(null)" else outName),RValue) and skip;
         cleanUpAndFail_retVal:=remove(outName,RValue);
         if(cleanUpAndFail_retVal!=0) then 
         {
             fprintf(stdout,"%s: WARNING: deletion of output file (apparently) failed.\n",progName,RValue) and skip
         }
         else 
         {
              skip 
         }
         
     }
     else 
     {
          skip 
     };
     if(numFileNames>0 AND numFilesProcessed<numFileNames) then 
     {
         fprintf(stdout,"%s: WARNING: some files have not been processed:\n","\t%d specified on command line, %d not processed yet.\n\n",progName,numFileNames,numFileNames-numFilesProcessed,RValue) and skip
         
     }
     else 
     {
          skip 
     };
     exit(0) 
     )
     }; 
  function panic ( char *s )
 {
     fprintf(stdout,"\n%s: PANIC -- internal consistency error:\n","\t%s\n","\tThis is a BUG.  Please report it to me at:\n","\tjseward@acm.org\n",progName,s,RValue) and skip;
     showFileNames();
     cleanUpAndFail(3)
     
 };
 function badBGLengths (  )
 {
     fprintf(stdout,"\n%s: error when reading background model code lengths,\n","\twhich probably means the compressed file is corrupted.\n",progName,RValue) and skip;
     showFileNames();
     cadvise();
     cleanUpAndFail(2)
	 
     
 };
 function crcError ( int crcStored,int crcComputed )
 {
     fprintf(stdout,"\n%s: Data integrity error when decompressing.\n","\tStored CRC = 0x%x, computed CRC = 0x%x\n",progName,crcStored,crcComputed,RValue) and skip;
     showFileNames();
     cadvise();
     cleanUpAndFail(2)
     
 };
 function compressedStreamEOF (  )
 {
     fprintf(stdout,"\n%s: Compressed file ends unexpectedly;\n\t","perhaps it is corrupted?  *Possible* reason follows.\n",progName,RValue) and skip;
     perror(progName,RValue) and skip;
     showFileNames();
     cadvise();
     cleanUpAndFail(2)
     
 };
 function ioError (  )
 {
     fprintf(stdout,"\n%s: I/O or other error, bailing out.  Possible reason follows.\n",progName,RValue) and skip;
     perror(progName,RValue) and skip;
     showFileNames();
     cleanUpAndFail(1)
     
 };
 function blockOverrun (  )
 {
     fprintf(stdout,"\n%s: block overrun during decompression,\n","\twhich probably means the compressed file\n","\tis corrupted.\n",progName,RValue) and skip;
     showFileNames();
     cadvise();
     cleanUpAndFail(2)
     
 };
 function badBlockHeader (  )
 {
     fprintf(stdout,"\n%s: bad block header in the compressed file,\n","\twhich probably means it is corrupted.\n",progName,RValue) and skip;
     showFileNames();
     cadvise();
     cleanUpAndFail(2)
     
 };
 function bitStreamEOF (  )
 {
     fprintf(stdout,"\n%s: read past the end of compressed data,\n","\twhich probably means it is corrupted.\n",progName,RValue) and skip;
     showFileNames();
     cadvise();
     cleanUpAndFail(2)
     
 };
 function mySignalCatcher ( int n )
 {
     fprintf(stdout,"\n%s: Control-C (or similar) caught, quitting.\n",progName,RValue) and skip;
     cleanUpAndFail(1)
     
 };
 function mySIGSEGVorSIGBUScatcher ( int n )
 {
     if(opMode=1) then 
     {
         fprintf(stdout,"\n%s: Caught a SIGSEGV or SIGBUS whilst compressing,\n","\twhich probably indicates a bug in bzip2.  Please\n","\treport it to me at: jseward@acm.org\n",progName,RValue) and skip
     }
     else
     {
         fprintf(stdout,"\n%s: Caught a SIGSEGV or SIGBUS whilst decompressing,\n","\twhich probably indicates that the compressed data\n","\tis corrupted.\n",progName,RValue) and skip
     };
     showFileNames();
     if(opMode=1) then 
     {
         cleanUpAndFail(3)
     }
     else
     {
         cadvise();
         cleanUpAndFail(2)
     }
     
 };
 function uncompressOutOfMemory ( int draw,int blockSize )
 {
     fprintf(stdout,"\n%s: Can't allocate enough memory for decompression.\n","\tRequested %d bytes for a block size of %d.\n","\tTry selecting space-economic decompress (with flag -s)\n","\tand failing that, find a machine with more memory.\n",progName,draw,blockSize,RValue) and skip;
     showFileNames();
     cleanUpAndFail(1)
     
 };
 function compressOutOfMemory ( int draw,int blockSize )
 {
     fprintf(stdout,"\n%s: Can't allocate enough memory for compression.\n","\tRequested %d bytes for a block size of %d.\n","\tTry selecting a small block size (with flag -s).\n",progName,draw,blockSize,RValue) and skip;
     showFileNames();
     cleanUpAndFail(1)
     
 };
 int dbglvl<==4 and skip;
 function debug ( int level ,char* str )
 {
     if(level<dbglvl) then 
     {
         printf (str) and skip 
     }
     else 
     {
          skip 
     }
     
 };
 function debug1 ( int level ,char* str ,int a )
 {
     if(level<dbglvl) then 
     {
         printf (str,a) and skip 
     }
     else 
     {
          skip 
     }
     
 };
 function debug2 ( int level ,char *str ,int a ,int b )
 {
     if(level<dbglvl) then 
     {
         printf (str,a,b) and skip 
     }
     else 
     {
          skip 
     }
     
 };
 function debug3 ( int level ,char* str ,int a ,int b ,int c )
 {
     if(level<dbglvl) then 
     {
         printf (str,a,b,c) and skip 
     }
     else 
     {
          skip 
     }
     
 };
 struct spec_fd_t {
 int limit and 
 int len$ and 
 int pos and 
 unsigned char *buf 
 };
 spec_fd_t  spec_fd[3] and skip;
 int seedi and skip;
 function ran ( float RValue )
 {
     frame(ran_lo,ran_hi,ran_test,return) and ( 
     int return<==0 and skip;
     int ran_lo and skip;
     int ran_hi and skip;
     int ran_test and skip;
     ran_hi:=seedi/ 127773;
     ran_lo:=seedi % 127773;
     ran_test:=16807*ran_lo-2836*ran_hi;
     if(ran_test>0) then 
     {
         seedi:=ran_test
         
     }
     else
     {
         seedi:=ran_test+2147483647
     };
     return<==1 and RValue:=((float)seedi/ 2147483647);
     skip
     )
     }; 
  function spec_init ( int RValue )
 {
     frame(spec_init_i,spec_init_j,spec_init_limit,return) and ( 
     int return<==0 and skip;
     int spec_init_i,spec_init_j and skip;
     if(3<dbglvl) then 
     {
         output ("spec_init\n") and skip
     }
     else 
     {
          skip 
     };
     spec_init_i:=0;
     
     while(spec_init_i<3)
     {
         int spec_init_limit<==spec_fd[spec_init_i].limit and skip;
         memset(&spec_fd[spec_init_i],0,sizeof(spec_fd_t),RValue) and skip;
         spec_fd[spec_init_i].limit:=spec_init_limit;
		 //output("yubin8\n") and skip;
         spec_fd[spec_init_i].buf:=(unsigned char *)malloc(spec_init_limit+(100*1024));
         if(spec_fd[spec_init_i].buf=NULL) then 
         {
             output ("spec_init: Error mallocing memory!\n") and skip;
             exit(0) and skip 
             
         }
         else 
         {
              skip 
         };
         spec_init_j:=0;
         
         while(spec_init_j<spec_init_limit)
         {
             spec_fd[spec_init_i].buf[spec_init_j]:=0;
             spec_init_j:=spec_init_j+1024
             
         };
         spec_init_i:=spec_init_i+1
         
     };
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function spec_random_load ( int fd,int RValue )
 {
     frame(spec_random_load_i,spec_random_load_j,random_text,spec_random_load_temp$_1,return) and ( 
     int return<==0 and skip;
     int spec_random_load_i,spec_random_load_j and skip;
     char spec_random_load_random_text[32,128*1024] and skip;
     debug(4,"Creating Chunks\n");
     spec_random_load_i:=0;
     
     while(spec_random_load_i<32)
     {
         debug1(5,"Creating Chunk %d\n",spec_random_load_i);
         spec_random_load_j:=0;
         
         while(spec_random_load_j<(128*1024))
         {
             spec_random_load_random_text[spec_random_load_i,spec_random_load_j]:=(int)(ran(RValue)*256);
             spec_random_load_j:=spec_random_load_j+1
             
         };
         spec_random_load_i:=spec_random_load_i+1
         
     };
     debug(4,"Filling input file\n");
     spec_random_load_i:=0;
     
     while(spec_random_load_i<spec_fd[fd].limit)
     {
         float spec_random_load_temp$_1 and skip;
         spec_random_load_temp$_1:=ran(RValue);
         memcpy(spec_fd[fd].buf+spec_random_load_i,spec_random_load_random_text[(int)(spec_random_load_temp$_1*32)],(128*1024),RValue) and skip;
         spec_random_load_i:=spec_random_load_i+(128*1024)
         
     };
     spec_fd[fd].len$:=1024;
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function spec_load ( int num,char *filename,int size,int RValue )
 {
     frame(spec_load_fd,spec_load_rc,spec_load_i,spec_load_1_temp$_1,spec_load_3_temp$_2,spec_load_4_tmp,return,break$$) and ( 
	 module_4<==1 and skip;
     int break$$<==0 and skip;
     int return<==0 and skip;
     int spec_load_fd,spec_load_rc,spec_load_i and skip;
     spec_load_fd:=_open(filename,32768,0,RValue);
     if(spec_load_fd<0) then 
     {
         int spec_load_1_temp$_1 and skip;
         //spec_load_1_temp$_1:=strerror(_errno(),RValue);
         fprintf(stdout,"Can't open file %s: %s\n",filename,spec_load_1_temp$_1,RValue) and skip;
         exit(0) 
         
     }
     else 
     {
          skip 
     };
     spec_fd[num].len$<==0 and spec_fd[num].pos<==spec_fd[num].len$ and skip;
     break$$<==0 and skip;
     spec_load_i:=0;
     
     while( break$$=0 AND  spec_load_i<size)
     {
         spec_load_rc:=_read(spec_load_fd,spec_fd[num].buf+spec_load_i,(128*1024),RValue);
         if(spec_load_rc=0) then 
         {
             break$$<==1 and skip
          }
         else 
         {
              skip 
         };
         if(break$$=0)   then
         {
             if(spec_load_rc<0) then 
             {
                 int spec_load_3_temp$_2 and skip;
                 //spec_load_3_temp$_2:=strerror(_errno(),RValue);
                 fprintf(stdout,"Error reading from %s: %s\n",filename,spec_load_3_temp$_2,RValue) and skip;
				 //("yubin!!!") and skip;
                 exit(0) 
                 
             }
             else 
             {
                  skip 
             };
             spec_fd[num].len$:=spec_fd[num].len$+spec_load_rc;
             spec_load_i:=spec_load_i+spec_load_rc
         }
         else
         {
             skip
         }
         
     };
     break$$<==0 and skip;
     _close(spec_load_fd,RValue) and skip;
     while(spec_fd[num].len$<size)
     {
         int spec_load_4_tmp<==size-spec_fd[num].len$ and skip;
         if(spec_load_4_tmp>spec_fd[num].len$) then 
         {
             spec_load_4_tmp:=spec_fd[num].len$
         }
         else 
         {
              skip 
         };
         debug1(3,"Duplicating %d bytes\n",spec_load_4_tmp);
         memcpy(spec_fd[num].buf+spec_fd[num].len$,spec_fd[num].buf,spec_load_4_tmp,RValue) and skip;
         spec_fd[num].len$:=spec_fd[num].len$+spec_load_4_tmp
     };
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function spec_read ( int fd,unsigned char *buf,int size,int RValue )
 {
     frame(spec_read_rc,return) and ( 
     int return<==0 and skip;
     int spec_read_rc<==0 and skip;
     debug3(4,"spec_read: %d, %p, %d = ",fd,(void *)buf,size);
     if(fd>3) then 
     {
         fprintf(stdout,"spec_read: fd=%d, > 3!\n",fd,RValue) and skip;
         exit(0) 
         
     }
     else 
     {
          skip 
     };
     if(spec_fd[fd].pos>=spec_fd[fd].len$) then 
     {
         debug(4,"-1\n");
         return<==1 and RValue:=(-1);
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         if(spec_fd[fd].pos+size>=spec_fd[fd].len$) then 
         {
             spec_read_rc:=spec_fd[fd].len$-spec_fd[fd].pos
             
         }
         else
         {
             spec_read_rc:=size
         };
         memcpy(buf,&(spec_fd[fd].buf[spec_fd[fd].pos]),spec_read_rc,RValue) and skip;
         spec_fd[fd].pos:=spec_fd[fd].pos+spec_read_rc;
         debug1(4,"%d\n",spec_read_rc);
         return<==1 and RValue:=spec_read_rc;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function spec_getc ( int fd,int RValue )
 {
     frame(spec_getc_rc,return) and ( 
     int return<==0 and skip;
     int spec_getc_rc<==0 and skip;
     debug1(4,"spec_getc: %d = ",fd);
     if(fd>3) then 
     {
         fprintf(stdout,"spec_read: fd=%d, > 3!\n",fd,RValue) and skip;
         exit(0) 
         
     }
     else 
     {
          skip 
     };
     if(spec_fd[fd].pos>=spec_fd[fd].len$) then 
     {
         debug(4,"-1\n");
         return<==1 and RValue:=(-1);
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         spec_getc_rc:=spec_fd[fd].buf[spec_fd[fd].pos];
         spec_fd[fd].pos:=spec_fd[fd].pos+1;
         debug1(4,"%d\n",spec_getc_rc);
         return<==1 and RValue:=spec_getc_rc;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function spec_ungetc ( unsigned char ch,int fd,int RValue )
 {
     frame(spec_ungetc_rc,return) and ( 
     int return<==0 and skip;
     int spec_ungetc_rc<==0 and skip;
     debug1(4,"spec_ungetc: %d = ",fd);
     if(fd>3) then 
     {
         fprintf(stdout,"spec_read: fd=%d, > 3!\n",fd,RValue) and skip;
         exit(1) 
         
     }
     else 
     {
          skip 
     };
	 
     if(spec_fd[fd].pos<=0) then 
     {
         fprintf(stdout,"spec_ungetc: pos %d <= 0\n",spec_fd[fd].pos,RValue) and skip;
         exit(1) 
         
     }
     else 
     {
          skip 
     };
	 spec_fd[fd].pos:=spec_fd[fd].pos-1;
     if(spec_fd[fd].buf[spec_fd[fd].pos]!=ch) then 
     {
         fprintf(stdout,"spec_ungetc: can't unget something that wasn't what was in the buffer!\n",RValue) and skip;
         exit(1) 
     }
     else 
     {
        skip
         
     };
     debug1(4,"%d\n",spec_ungetc_rc);
     return<==1 and RValue:=ch;
     skip
     )
     }; 
  function spec_rewind ( int fd,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     spec_fd[fd].pos:=0;
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function spec_reset ( int fd,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     memset(spec_fd[fd].buf,0,spec_fd[fd].len$,RValue) and skip;
     spec_fd[fd].len$<==0 and spec_fd[fd].pos<==spec_fd[fd].len$ and skip;
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function spec_write ( int fd,unsigned char *buf,int size,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     debug3(4,"spec_write: %d, %p, %d = ",fd,(void *)buf,size);
     if(fd>3) then 
     {
         fprintf(stdout,"spec_write: fd=%d, > 3!\n",fd,RValue) and skip;
         exit(0) 
         
     }
     else 
     {
          skip 
     };
     memcpy(&(spec_fd[fd].buf[spec_fd[fd].pos]),buf,size,RValue) and skip;
     spec_fd[fd].len$:=spec_fd[fd].len$+size;
     spec_fd[fd].pos:=spec_fd[fd].pos+size;
     debug1(4,"%d\n",size);
     return<==1 and RValue:=size;
     skip
     )
     }; 
  function spec_putc ( unsigned char ch,int fd,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     debug2(4,"spec_putc: %d, %d = ",ch,fd);
     if(fd>3) then 
     {
         fprintf(stdout,"spec_write: fd=%d, > 3!\n",fd,RValue) and skip;
         exit(0) 
         
     }
     else 
     {
          skip 
     };
     spec_fd[fd].buf[spec_fd[fd].pos]:=ch;
     spec_fd[fd].pos:=spec_fd[fd].pos+1;
     spec_fd[fd].len$:=spec_fd[fd].len$+1;
     return<==1 and RValue:=ch;
     skip
     )
     }; 
  function main ( int RValue )
 {
     frame(main_i,main_input_size,main_compressed_size,main_input_name,main_validate_array,return) and (
	 module_2<==1 and skip;
     int return<==0 and skip;
     int main_i and skip;
     int main_input_size<==4,main_compressed_size and skip;
     char main_input_name[22]<=="E:\\input\\output.txt" and skip;
     unsigned char *main_validate_array and skip;
	 while(return<10000000)
	 {
		return:=return+1
	 };
	 return<==0 and skip;
     seedi:=10;
	 main_compressed_size:=main_input_size;
     spec_fd[0].limit:=main_input_size*(1024);
     spec_fd[1].limit:=main_compressed_size*(1024);
     spec_fd[2].limit:=main_input_size*(1024);
     spec_init(RValue);
     debug_time(RValue);
     debug(2,"Loading Input Data\n");
     spec_load(0,main_input_name,main_input_size*(1024),RValue);
     debug1(3,"Input data %d bytes in length\n",spec_fd[0].len$);
	 //output("yubin9\n") and skip;
     main_validate_array:=(unsigned char *)malloc(main_input_size*(1024)/ 1024);
     if(main_validate_array=NULL) then 
     {
         output ("main: Error mallocing memory!\n") and skip;
         exit(0) 
         
     }
     else 
     {
          skip 
     };
     main_i:=0;
     
     while(main_i*1027<main_input_size*(1024))
     {
         main_validate_array[main_i]:=spec_fd[0].buf[main_i*1027];
         main_i:=main_i+1
         
     };
     spec_initbufs();
     main_level:=7;
     
     while(main_level<=9)
     {
         debug_time(RValue);
         debug1(2,"Compressing Input Data, level %d\n",main_level);
         spec_compress(0,1,main_level);
         debug_time(RValue);
         debug1(3,"Compressed data %d bytes in length\n",spec_fd[1].len$);
         spec_reset(0,RValue);
         spec_rewind(1,RValue);
         debug_time(RValue);
         debug(2,"Uncompressing Data\n");
         spec_uncompress(1,0,main_level);
         debug_time(RValue);
         debug1(3,"Uncompressed data %d bytes in length\n",spec_fd[0].len$);
         main_i:=0;
         
         while(main_i*1027<main_input_size*(1024))
         {
             if(main_validate_array[main_i]!=spec_fd[0].buf[main_i*1027]) then 
             {
                 output ("Tested ",main_input_size,"MB buffer: Miscompared!!\n") and skip;
                 exit(0) 
                 
             }
             else 
             {
                  skip 
             };
             main_i:=main_i+1
             
         };
         debug_time(RValue);
         debug(3,"Uncompressed data compared correctly\n");
         spec_reset(1,RValue);
         spec_rewind(0,RValue);
         main_level:=main_level+2
         
     };
     output ("Tested ",main_input_size,"MB buffer: OK!\n") and skip;
     return<==1 and RValue:=0;
     skip
     )
     }; 
  function spec_initbufs (  )
 {
     smallMode:=0;
     verbosity:=0;
     blockSize100k:=9;
     bsStream:=0;
     workFactor:=30;
     allocateCompressStructures()
     
 };
 function spec_compress ( int in,int out,int lev )
 {
	 module_3<==1 and skip;
     blockSize100k:=lev;
     compressStream(in,out)
     
 };
 function spec_uncompress ( int in,int out,int lev )
 {
     blockSize100k:=0;
     uncompressStream(in,out,RValue)
     
 };
 function debug_time ( int RValue )
 {
     frame(return) and (
     int return<==0 and skip;
     return<==1 and RValue:=0;
     skip
     )
 };
  frame(argv,argc,count$,str$) and ( 
  int argc<==0 and skip;
 char * argv[3] and skip;
  int count$<==0 and skip;
 char * str$ and skip;while(count$<argc){
  argv[count$]<==str$ and skip;
  count$:=count$+1 and skip
 };
 main(RValue)
 )
 )
