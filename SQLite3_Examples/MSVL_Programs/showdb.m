/*</
define p:sqlite3_mprintf_call=1;
define q:sqlite3_free_call=1;
alw(p->som(q))
/>*/

</
define p:sqlite3_open_call=1;
define q:sqlite3_close_call=1;
alw(p->som(q))
/>

frame(pagesize,dbfd,mxPage,perLine,bRaw,db,zPageUse) and (
int pagesize<==1024 and skip;
int dbfd<==-1 and skip;
int mxPage<==0 and skip;
int perLine<==16 and skip;
int bRaw<==0 and skip;
 function decodeVarint ( unsigned char *z,int *pVal,int RValue )
 {
     frame(decodeVarint_v,decodeVarint_i,return) and ( 
     int return<==0 and skip;
     int decodeVarint_v<==0 and skip;
     int decodeVarint_i and skip;
     decodeVarint_i:=0;
     
     while( return=0 AND  decodeVarint_i<8)
     {
         decodeVarint_v:=(decodeVarint_v<<7)+(z[decodeVarint_i] & 127);
         if((z[decodeVarint_i] & 128)=0) then 
         {
             * pVal:=decodeVarint_v;
             return<==1 and skip;
			 RValue:=decodeVarint_i+1;
             skip
             
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             decodeVarint_i:=decodeVarint_i+1
         }
         else
         {
             skip
         }
         
     };
     if(return=0)   then 
     {
         decodeVarint_v:=(decodeVarint_v<<8)+(z[decodeVarint_i] & 255);
         * pVal:=decodeVarint_v;
         return<==1 and skip;
		 RValue:=9;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function decodeInt32 ( unsigned char *z,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and skip;
	 RValue:=(z[0]<<24)+(z[1]<<16)+(z[2]<<8)+z[3];
     skip
     )
     }; 
  function out_of_memory (  )
 {
     fprintf(stderr,"Out of memory...\n") and skip
     
 };
 function openDatabase ( char *zPrg,char *zName,struct sqlite3* RValue )
 {
     frame(gp_sqlite3,openDatabase_flags,openDatabase_rc,openDatabase_1_zErr,return) and ( 
     int return<==0 and skip;
     int openDatabase_flags<==(0x00000002 | 0x00000040) and skip;
     int openDatabase_rc and skip;
     openDatabase_rc:=sqlite3_open_v2(zName,&gp_sqlite3,openDatabase_flags,0,RValue);
     if(openDatabase_rc!=0) then 
     {
         char *openDatabase_1_zErr and skip;
         openDatabase_1_zErr:=sqlite3_errmsg(gp_sqlite3,RValue);
         fprintf(stderr,"%s: can't open %s (%s)\n",zPrg,zName,openDatabase_1_zErr) and skip;
         sqlite3_close(gp_sqlite3,RValue) and skip
         
     }
     else 
     {
          skip 
     };
     return<==1 and skip;
	 RValue:=gp_sqlite3;
     skip
     )
     }; 
  function fileOpen ( char *zPrg,char *zName )
 {
     frame(fileOpen_1_rc,fileOpen_1_pArg) and ( 
	 printf("zName:%s\n",zName) and skip;
     if(bRaw=0) then 
     {
         int fileOpen_1_rc and skip;
         void *fileOpen_1_pArg<==NULL and skip;
         db:=openDatabase(zPrg,zName,RValue);
         fileOpen_1_rc:=sqlite3_file_control(db,"main",7,fileOpen_1_pArg,RValue);
         if(fileOpen_1_rc!=0) then 
         {
             fprintf(stderr,"%s: failed to obtain fd for %s (SQLite too old?)\n",zPrg,zName) and skip
             
         }
         else 
         {
              skip 
         }
     }
     else
     {
         dbfd:=_open(zName,0x0000,0);
         if(dbfd<0) then 
         {
             fprintf(stderr,"%s: can't open %s\n",zPrg,zName) and skip
             
         }
         else 
         {
              skip 
         }
     }
     )
     }; 
  function fileClose (  )
 {
     if(bRaw=0) then 
     {
         sqlite3_close(db,RValue) and skip;
         db:=0
     }
     else
     {
         _close(dbfd) and skip;
         dbfd:=-1
     }
     
 };
 function fileRead ( int ofst,int nByte,unsigned char* RValue )
 {
     frame(fileRead_aData,fileRead_got,fileRead_2_rc,return) and ( 
     int return<==0 and skip;
     unsigned char *fileRead_aData and skip;
     int fileRead_got and skip;
     fileRead_aData:=sqlite3_malloc(nByte+32,RValue);
     if(fileRead_aData=0) then 
     {
         out_of_memory()
     }
     else 
     {
          skip 
     };
     //memset(fileRead_aData,0,nByte+32) and skip;
     if(bRaw=0) then 
     {
         int fileRead_2_rc<==0 and skip;
         if(fileRead_2_rc!=0 AND fileRead_2_rc!=((10 | (2<<8)))) then 
         {
             fprintf(stderr,"error in xRead() - %d\n",fileRead_2_rc) and skip
             
         }
         else 
         {
              skip 
         }
         
     }
     else
     {
         _lseek(dbfd,(int)ofst,0,RValue) and skip;
         fileRead_got:=_read(dbfd,fileRead_aData,nByte);
         if(fileRead_got>0 AND fileRead_got<nByte) then 
         {
             //memset(fileRead_aData+fileRead_got,0,nByte-fileRead_got) and skip
			 skip
         }
         else 
         {
              skip 
         }
     };
     return<==1 and skip;
	 RValue:=fileRead_aData;
     skip
     )
     }; 
 
  function print_byte_range ( int ofst,int nByte,int printOfst,unsigned char* RValue )
 {
     frame(print_byte_range_aData,print_byte_range_i,print_byte_range_j,print_byte_range_zOfstFmt,print_byte_range_12_temp$_1,return) and ( 
     int return<==0 and skip;
     unsigned char *print_byte_range_aData and skip;
     int print_byte_range_i,print_byte_range_j and skip;
     char *print_byte_range_zOfstFmt and skip;
     if(((printOfst+nByte) & ~4095)=0) then 
     {
         print_byte_range_zOfstFmt:=" %03x: "
         
     }
     else
     {
         if(((printOfst+nByte) & ~65535)=0) then 
         {
             print_byte_range_zOfstFmt:=" %04x: "
         }
         else
         {
             if(((printOfst+nByte) & ~1048575)=0) then 
             {
                 print_byte_range_zOfstFmt:=" %05x: "
             }
             else
             {
                 if(((printOfst+nByte) & ~16777215)=0) then 
                 {
                     print_byte_range_zOfstFmt:=" %06x: "
                 }
                 else
                 {
                     print_byte_range_zOfstFmt:=" %08x: "
                 }
             }
         }
     };
     print_byte_range_aData:=fileRead(ofst,nByte,RValue);
     print_byte_range_i:=0;
     
     while(print_byte_range_i<nByte)
     {
         fprintf(stdout,print_byte_range_zOfstFmt,print_byte_range_i+printOfst) and skip;
         print_byte_range_j:=0;
         
         while(print_byte_range_j<perLine)
         {
             if(print_byte_range_i+print_byte_range_j>nByte) then 
             {
                 fprintf(stdout,"   ") and skip
                 
             }
             else
             {
                 fprintf(stdout,"%02x ",print_byte_range_aData[print_byte_range_i+print_byte_range_j]) and skip
             };
             print_byte_range_j:=print_byte_range_j+1
             
         };
         print_byte_range_j:=0;
         
         while(print_byte_range_j<perLine)
         {
             if(print_byte_range_i+print_byte_range_j>nByte) then 
             {
                 fprintf(stdout," ") and skip
                 
             }
             else
             {
                 int print_byte_range_12_temp$_1 and skip;
                 print_byte_range_12_temp$_1:=isprint((unsigned char)(print_byte_range_aData[print_byte_range_i+print_byte_range_j]),RValue);
                 fprintf(stdout,"%c",( if(print_byte_range_12_temp$_1) then print_byte_range_aData[print_byte_range_i+print_byte_range_j] else '.')) and skip
             };
             print_byte_range_j:=print_byte_range_j+1
             
         };
         fprintf(stdout,"\n") and skip;
         print_byte_range_i:=print_byte_range_i+perLine
         
     };
     return<==1 and skip;
	 RValue:=print_byte_range_aData;
     skip
     )
     }; 
  function print_page ( int iPg )
 {
     frame(print_page_iStart,print_page_aData) and ( 
     int print_page_iStart and skip;
     unsigned char *print_page_aData and skip;
     print_page_iStart:=(iPg-1)*pagesize;
     fprintf(stdout,"Page %d:   (offsets 0x%x..0x%x)\n",iPg,print_page_iStart,print_page_iStart+pagesize-1) and skip;
     print_page_aData:=print_byte_range(print_page_iStart,pagesize,0,RValue);
     sqlite3_free(print_page_aData,RValue) and skip
     )
     }; 
  function print_decode_line ( unsigned char *aData,int ofst,int nByte,char *zMsg )
 {
     frame(print_decode_line_i,print_decode_line_j,print_decode_line_val,print_decode_line_zBuf) and ( 
     int print_decode_line_i,print_decode_line_j and skip;
     int print_decode_line_val<==aData[ofst] and skip;
     char print_decode_line_zBuf[100] and skip;
     sprintf(print_decode_line_zBuf," %03x: %02x",ofst,aData[ofst]) and skip;
     print_decode_line_i:=(int)strlen(print_decode_line_zBuf);
     print_decode_line_j:=1;
     
     while(print_decode_line_j<4)
     {
         if(print_decode_line_j>=nByte) then 
         {
             sprintf(&print_decode_line_zBuf[print_decode_line_i],"   ") and skip
             
         }
         else
         {
             sprintf(&print_decode_line_zBuf[print_decode_line_i]," %02x",aData[ofst+print_decode_line_j]) and skip;
             print_decode_line_val:=print_decode_line_val*256+aData[ofst+print_decode_line_j]
         };
         print_decode_line_i:=print_decode_line_i+(int)strlen(&print_decode_line_zBuf[print_decode_line_i]);
         print_decode_line_j:=print_decode_line_j+1
         
     };
     sprintf(&print_decode_line_zBuf[print_decode_line_i],"   %9d",print_decode_line_val) and skip;
     output (print_decode_line_zBuf,"  ",zMsg,"\n","\n") and skip
     )
     }; 
  function print_db_header (  )
 {
     frame(print_db_header_aData) and ( 
     unsigned char *print_db_header_aData and skip;
     print_db_header_aData:=print_byte_range(0,100,0,RValue);
     output ("Decoded:\n") and skip;
     print_decode_line(print_db_header_aData,16,2,"Database page size");
     print_decode_line(print_db_header_aData,18,1,"File format write version");
     print_decode_line(print_db_header_aData,19,1,"File format read version");
     print_decode_line(print_db_header_aData,20,1,"Reserved space at end of page");
     print_decode_line(print_db_header_aData,24,4,"File change counter");
     print_decode_line(print_db_header_aData,28,4,"Size of database in pages");
     print_decode_line(print_db_header_aData,32,4,"Page number of first freelist page");
     print_decode_line(print_db_header_aData,36,4,"Number of freelist pages");
     print_decode_line(print_db_header_aData,40,4,"Schema cookie");
     print_decode_line(print_db_header_aData,44,4,"Schema format version");
     print_decode_line(print_db_header_aData,48,4,"Default page cache size");
     print_decode_line(print_db_header_aData,52,4,"Largest auto-vac root page");
     print_decode_line(print_db_header_aData,56,4,"Text encoding");
     print_decode_line(print_db_header_aData,60,4,"User version");
     print_decode_line(print_db_header_aData,64,4,"Incremental-vacuum mode");
     print_decode_line(print_db_header_aData,68,4,"Application ID");
     print_decode_line(print_db_header_aData,72,4,"meta[8]");
     print_decode_line(print_db_header_aData,76,4,"meta[9]");
     print_decode_line(print_db_header_aData,80,4,"meta[10]");
     print_decode_line(print_db_header_aData,84,4,"meta[11]");
     print_decode_line(print_db_header_aData,88,4,"meta[12]");
     print_decode_line(print_db_header_aData,92,4,"Change counter for version number");
     print_decode_line(print_db_header_aData,96,4,"SQLite version number")
     )
     }; 
  function describeContent ( unsigned char *a,int nLocal,char *zDesc,int RValue )
 {
     frame(describeContent_nDesc,describeContent_n,describeContent_j,describeContent_i,describeContent_x,describeContent_v,describeContent_pData,describeContent_pLimit,describeContent_sep,nm_1$,switch$,describeContent_1_3_6_8_10_12_13_size,return,break$) and ( 
     int return<==0 and skip;
	 int break$<==0 and skip;
     int describeContent_nDesc<==0 and skip;
     int describeContent_n,describeContent_j and skip;
     int describeContent_i,describeContent_x,describeContent_v and skip;
     unsigned char *describeContent_pData and skip;
     unsigned char *describeContent_pLimit and skip;
     char describeContent_sep<==' ' and skip;
     describeContent_pLimit:=&a[nLocal];
     describeContent_n:=decodeVarint(a,&describeContent_x,RValue);
     describeContent_pData:=&a[describeContent_x];
     a:=a+describeContent_n;
     describeContent_i:=describeContent_x-describeContent_n;
     while(describeContent_i>0 AND describeContent_pData<=describeContent_pLimit)
     {
         describeContent_n:=decodeVarint(a,&describeContent_x,RValue);
         a:=a+describeContent_n;
         describeContent_i:=describeContent_i-describeContent_n;
         nLocal:=nLocal-describeContent_n;
         zDesc[0]:=describeContent_sep;
         describeContent_sep:=',';
         describeContent_nDesc:=describeContent_nDesc+1;
         zDesc:=zDesc+1;
         if(describeContent_x=0) then 
         {
             sprintf(zDesc,"*") and skip
             
         }
         else
         {
             if(describeContent_x>=1 AND describeContent_x<=6) then 
             {
                 describeContent_v:=(char)describeContent_pData[0];
                 describeContent_pData:=describeContent_pData+1;
                 int switch$ and skip;
                 break$<==0 and skip;
                  switch$<==0 and skip;
                  int nm_1$ and skip;
                 nm_1$ := describeContent_x;
                 if (nm_1$=6 OR (switch$=1 AND break$=0 AND return=0) ) then 
                 {
                     switch$<==1 and skip;
                     describeContent_v:=(describeContent_v<<16)+(describeContent_pData[0]<<8)+describeContent_pData[1];
                     describeContent_pData:=describeContent_pData+2
                     
                 }
                 else
                 {
                     skip
                 };
                 if (nm_1$=5 OR (switch$=1 AND break$=0 AND return=0) ) then 
                 {
                     switch$<==1 and skip;
                     describeContent_v:=(describeContent_v<<16)+(describeContent_pData[0]<<8)+describeContent_pData[1];
                     describeContent_pData:=describeContent_pData+2
                     
                 }
                 else
                 {
                     skip
                 };
                 if (nm_1$=4 OR (switch$=1 AND break$=0 AND return=0) ) then 
                 {
                     switch$<==1 and skip;
                     describeContent_v:=(describeContent_v<<8)+describeContent_pData[0];
                     describeContent_pData:=describeContent_pData+1
                     
                 }
                 else
                 {
                     skip
                 };
                 if (nm_1$=3 OR (switch$=1 AND break$=0 AND return=0) ) then 
                 {
                     switch$<==1 and skip;
                     describeContent_v:=(describeContent_v<<8)+describeContent_pData[0];
                     describeContent_pData:=describeContent_pData+1
                     
                 }
                 else
                 {
                     skip
                 };
                 if (nm_1$=2 OR (switch$=1 AND break$=0 AND return=0) ) then 
                 {
                     switch$<==1 and skip;
                     describeContent_v:=(describeContent_v<<8)+describeContent_pData[0];
                     describeContent_pData:=describeContent_pData+1
                     
                 }
                 else
                 {
                     skip
                 };
                 sprintf(zDesc,"%lld",describeContent_v) and skip
             }
             else
             {
                 if(describeContent_x=7) then 
                 {
                     sprintf(zDesc,"real") and skip;
                     describeContent_pData:=describeContent_pData+8
                 }
                 else
                 {
                     if(describeContent_x=8) then 
                     {
                         sprintf(zDesc,"0") and skip
                     }
                     else
                     {
                         if(describeContent_x=9) then 
                         {
                             sprintf(zDesc,"1") and skip
                         }
                         else
                         {
                             if(describeContent_x>=12) then 
                             {
                                 int describeContent_1_3_6_8_10_12_13_size<==(describeContent_x-12)/ 2 and skip;
                                 if((describeContent_x & 1)=0) then 
                                 {
                                     sprintf(zDesc,"blob(%lld)",describeContent_1_3_6_8_10_12_13_size) and skip
                                     
                                 }
                                 else
                                 {
                                     sprintf(zDesc,"txt(%lld)",describeContent_1_3_6_8_10_12_13_size) and skip
                                 };
                                 describeContent_pData:=describeContent_pData+describeContent_1_3_6_8_10_12_13_size
                                 
                             }
                             else 
                             {
                                  skip 
                             }
                         }
                     }
                 }
             }
         };
         describeContent_j:=(int)strlen(zDesc);
         zDesc:=zDesc+describeContent_j;
         describeContent_nDesc:=describeContent_nDesc+describeContent_j
     };
     return<==1 and skip;
	 RValue:=describeContent_nDesc;
     skip
     )
     }; 
  function localPayload ( int nPayload,char cType,int RValue )
 {
     frame(localPayload_maxLocal,localPayload_minLocal,localPayload_surplus,localPayload_nLocal,return) and ( 
     int return<==0 and skip;
     int localPayload_maxLocal and skip;
     int localPayload_minLocal and skip;
     int localPayload_surplus and skip;
     int localPayload_nLocal and skip;
     if(cType=13) then 
     {
         localPayload_maxLocal:=pagesize-35;
         localPayload_minLocal:=(pagesize-12)*32/ 255-23
         
     }
     else
     {
         localPayload_maxLocal:=(pagesize-12)*64/ 255-23;
         localPayload_minLocal:=(pagesize-12)*32/ 255-23
     };
     if(nPayload>localPayload_maxLocal) then 
     {
         localPayload_surplus:=localPayload_minLocal+(nPayload-localPayload_minLocal) % (pagesize-4);
         if(localPayload_surplus<=localPayload_maxLocal) then 
         {
             localPayload_nLocal:=localPayload_surplus
         }
         else
         {
             localPayload_nLocal:=localPayload_minLocal
         }
         
     }
     else
     {
         localPayload_nLocal:=nPayload
     };
     return<==1 and skip;
	 RValue:=localPayload_nLocal;
     skip
     )
     }; 
  function describeCell ( unsigned char cType,unsigned char *a,int showCellContent,char **pzDesc,int RValue )
 {
     frame(describeCell_i,describeCell_nDesc,describeCell_n,describeCell_leftChild,describeCell_nPayload,describeCell_rowid,describeCell_nLocal,describeCell_zDesc,describeCell_5_ovfl,describeCell_5_b,return) and ( 
     int return<==0 and skip;
     int describeCell_i and skip;
     int describeCell_nDesc<==0 and skip;
     int describeCell_n<==0 and skip;
     int describeCell_leftChild and skip;
     int describeCell_nPayload and skip;
     int describeCell_rowid and skip;
     int describeCell_nLocal and skip;
     char describeCell_zDesc[1000] and skip;
     describeCell_i:=0;
     if(cType<=5) then 
     {
         describeCell_leftChild:=((a[0]*256+a[1])*256+a[2])*256+a[3];
         a:=a+4;
         describeCell_n:=describeCell_n+4;
         sprintf(describeCell_zDesc,"lx: %d ",describeCell_leftChild) and skip;
         describeCell_nDesc:=strlen(describeCell_zDesc)
         
     }
     else 
     {
          skip 
     };
     if(cType!=5) then 
     {
         describeCell_i:=decodeVarint(a,&describeCell_nPayload,RValue);
         a:=a+describeCell_i;
         describeCell_n:=describeCell_n+describeCell_i;
         sprintf(&describeCell_zDesc[describeCell_nDesc],"n: %lld ",describeCell_nPayload) and skip;
         describeCell_nDesc:=describeCell_nDesc+strlen(&describeCell_zDesc[describeCell_nDesc]);
         describeCell_nLocal:=localPayload(describeCell_nPayload,cType,RValue)
         
     }
     else
     {
         describeCell_nLocal<==0 and describeCell_nPayload<==describeCell_nLocal and skip
     };
     if(cType=5 OR cType=13) then 
     {
         describeCell_i:=decodeVarint(a,&describeCell_rowid,RValue);
         a:=a+describeCell_i;
         describeCell_n:=describeCell_n+describeCell_i;
         sprintf(&describeCell_zDesc[describeCell_nDesc],"r: %lld ",describeCell_rowid) and skip;
         describeCell_nDesc:=describeCell_nDesc+strlen(&describeCell_zDesc[describeCell_nDesc])
         
     }
     else 
     {
          skip 
     };
     if(describeCell_nLocal<describeCell_nPayload) then 
     {
         int describeCell_5_ovfl and skip;
         unsigned char *describeCell_5_b<==&a[describeCell_nLocal] and skip;
         describeCell_5_ovfl:=((describeCell_5_b[0]*256+describeCell_5_b[1])*256+describeCell_5_b[2])*256+describeCell_5_b[3];
         sprintf(&describeCell_zDesc[describeCell_nDesc],"ov: %d ",describeCell_5_ovfl) and skip;
         describeCell_nDesc:=describeCell_nDesc+strlen(&describeCell_zDesc[describeCell_nDesc]);
         describeCell_n:=describeCell_n+4
         
     }
     else 
     {
          skip 
     };
     if(showCellContent AND cType!=5) then 
     {
         describeCell_nDesc:=describeCell_nDesc+describeContent(a,describeCell_nLocal,&describeCell_zDesc[describeCell_nDesc-1],RValue)
         
     }
     else 
     {
          skip 
     };
     * pzDesc:=describeCell_zDesc;
     return<==1 and skip;
	 RValue:=describeCell_nLocal+describeCell_n;
     skip
     )
     }; 
  function printBytes ( unsigned char *aData,unsigned char *aStart,int nByte )
 {
     frame(printBytes_j) and ( 
     int printBytes_j and skip;
     output (" ",(int)(aStart-aData),"03x: ") and skip;
     printBytes_j:=0;
     
     while(printBytes_j<9)
     {
         if(printBytes_j>=nByte) then 
         {
             output ("   ") and skip
             
         }
         else
         {
             output (aStart[printBytes_j],"02x ","02x ") and skip
         };
         printBytes_j:=printBytes_j+1
         
     }
     )
     }; 
  function decodeCell ( unsigned char *a,int pgno,int iCell,int szPgHdr,int ofst )
 {
     frame(decodeCell_i,decodeCell_j,decodeCell_leftChild,decodeCell_k,decodeCell_nPayload,decodeCell_rowid,decodeCell_nHdr,decodeCell_iType,decodeCell_nLocal,decodeCell_x,decodeCell_end,decodeCell_cType,decodeCell_nCol,decodeCell_szCol,decodeCell_ofstCol,decodeCell_typeCol,decodeCell_7_8_zTypeName,decodeCell_7_8_sz,decodeCell_7_8_zNm,nm_2$,switch$,decodeCell_7_s,decodeCell_7_v,decodeCell_7_pData,decodeCell_7_11_12_r,decodeCell_7_14_ii,decodeCell_7_14_jj,decodeCell_7_14_zConst,return,break$,continue) and ( 
     int continue<==0 and skip;
     int break$<==0 and skip;
     int return<==0 and skip;
     int decodeCell_i,decodeCell_j<==0 and skip;
     int decodeCell_leftChild and skip;
     int decodeCell_k and skip;
     int decodeCell_nPayload and skip;
     int decodeCell_rowid and skip;
     int decodeCell_nHdr and skip;
     int decodeCell_iType and skip;
     int decodeCell_nLocal and skip;
     unsigned char *decodeCell_x<==a+ofst and skip;
     unsigned char *decodeCell_end and skip;
     unsigned char decodeCell_cType<==a[0] and skip;
     int decodeCell_nCol<==0 and skip;
     int decodeCell_szCol[2000] and skip;
     int decodeCell_ofstCol[2000] and skip;
     int decodeCell_typeCol[2000] and skip;
     output ("Cell[",iCell,"]:\n") and skip;
     if(decodeCell_cType<=5) then 
     {
         decodeCell_leftChild:=((decodeCell_x[0]*256+decodeCell_x[1])*256+decodeCell_x[2])*256+decodeCell_x[3];
         printBytes(a,decodeCell_x,4);
         output ("left child page:: ",decodeCell_leftChild,"\n") and skip;
         decodeCell_x:=decodeCell_x+4
         
     }
     else 
     {
          skip 
     };
     if(decodeCell_cType!=5) then 
     {
         decodeCell_i:=decodeVarint(decodeCell_x,&decodeCell_nPayload,RValue);
         printBytes(a,decodeCell_x,decodeCell_i);
         decodeCell_nLocal:=localPayload(decodeCell_nPayload,decodeCell_cType,RValue);
         if(decodeCell_nLocal=decodeCell_nPayload) then 
         {
             output ("payload-size: ",decodeCell_nPayload,"\n") and skip
             
         }
         else
         {
             output ("payload-size: ",decodeCell_nPayload," (",decodeCell_nLocal," local, ",decodeCell_nPayload-decodeCell_nLocal," overflow)\n") and skip
         };
         decodeCell_x:=decodeCell_x+decodeCell_i
         
     }
     else
     {
         decodeCell_nLocal<==0 and decodeCell_nPayload<==decodeCell_nLocal and skip
     };
     decodeCell_end:=decodeCell_x+decodeCell_nLocal;
     if(decodeCell_cType=5 OR decodeCell_cType=13) then 
     {
         decodeCell_i:=decodeVarint(decodeCell_x,&decodeCell_rowid,RValue);
         printBytes(a,decodeCell_x,decodeCell_i);
         output ("rowid: ",decodeCell_rowid,"\n") and skip;
         decodeCell_x:=decodeCell_x+decodeCell_i
         
     }
     else 
     {
          skip 
     };
     if(decodeCell_nLocal>0) then 
     {
         decodeCell_i:=decodeVarint(decodeCell_x,&decodeCell_nHdr,RValue);
         printBytes(a,decodeCell_x,decodeCell_i);
         output ("record-header-size: ",(int)decodeCell_nHdr,"\n") and skip;
         decodeCell_j:=decodeCell_i;
         decodeCell_nCol:=0;
         decodeCell_k:=decodeCell_nHdr;
         while(decodeCell_x+decodeCell_j<=decodeCell_end AND decodeCell_j<decodeCell_nHdr)
         {
             char *decodeCell_7_8_zTypeName and skip;
             int decodeCell_7_8_sz<==0 and skip;
             char decodeCell_7_8_zNm[30] and skip;
             decodeCell_i:=decodeVarint(decodeCell_x+decodeCell_j,&decodeCell_iType,RValue);
             printBytes(a,decodeCell_x+decodeCell_j,decodeCell_i);
             output ("typecode[",decodeCell_nCol,"]: ",(int)decodeCell_iType," - ") and skip;
             int switch$ and skip;
             break$<==0 and skip;
              switch$<==0 and skip;
              int nm_2$ and skip;
             nm_2$ := decodeCell_iType;
             if (nm_2$=0 OR (switch$=1 AND break$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 decodeCell_7_8_zTypeName:="NULL";
                 decodeCell_7_8_sz:=0;
                 break$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             if (nm_2$=1 OR (switch$=1 AND break$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 decodeCell_7_8_zTypeName:="int8";
                 decodeCell_7_8_sz:=1;
                 break$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             if (nm_2$=2 OR (switch$=1 AND break$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 decodeCell_7_8_zTypeName:="int16";
                 decodeCell_7_8_sz:=2;
                 break$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             if (nm_2$=3 OR (switch$=1 AND break$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 decodeCell_7_8_zTypeName:="int24";
                 decodeCell_7_8_sz:=3;
                 break$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             if (nm_2$=4 OR (switch$=1 AND break$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 decodeCell_7_8_zTypeName:="int32";
                 decodeCell_7_8_sz:=4;
                 break$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             if (nm_2$=5 OR (switch$=1 AND break$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 decodeCell_7_8_zTypeName:="int48";
                 decodeCell_7_8_sz:=6;
                 break$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             if (nm_2$=6 OR (switch$=1 AND break$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 decodeCell_7_8_zTypeName:="int64";
                 decodeCell_7_8_sz:=8;
                 break$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             if (nm_2$=7 OR (switch$=1 AND break$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 decodeCell_7_8_zTypeName:="double";
                 decodeCell_7_8_sz:=8;
                 break$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             if (nm_2$=8 OR (switch$=1 AND break$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 decodeCell_7_8_zTypeName:="zero";
                 decodeCell_7_8_sz:=0;
                 break$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             if (nm_2$=9 OR (switch$=1 AND break$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 decodeCell_7_8_zTypeName:="one";
                 decodeCell_7_8_sz:=0;
                 break$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             if (nm_2$=10 OR (switch$=1 AND break$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip
                 
             }
             else
             {
                 skip
             };
             if (nm_2$=11 OR (switch$=1 AND break$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 decodeCell_7_8_zTypeName:="error";
                 decodeCell_7_8_sz:=0;
                 break$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             if(break$=0 AND return=0) then 
             {
                 decodeCell_7_8_sz:=(int)(decodeCell_iType-12)/ 2;
                 sprintf(decodeCell_7_8_zNm,( if((decodeCell_iType & 1)=0) then "blob(%d)" else "text(%d)"),decodeCell_7_8_sz) and skip;
                 decodeCell_7_8_zTypeName:=decodeCell_7_8_zNm;
                 break$<==1 and skip
                  
             }
             else
             {
                  skip
             };
             output (decodeCell_7_8_zTypeName,"\n","\n") and skip;
             decodeCell_szCol[decodeCell_nCol]:=decodeCell_7_8_sz;
             decodeCell_ofstCol[decodeCell_nCol]:=(int)decodeCell_k;
             decodeCell_typeCol[decodeCell_nCol]:=(int)decodeCell_iType;
             decodeCell_k:=decodeCell_k+decodeCell_7_8_sz;
             decodeCell_nCol:=decodeCell_nCol+1;
             decodeCell_j:=decodeCell_j+decodeCell_i
         };
         continue<==0 and skip;
         decodeCell_i:=0;
         
         while(decodeCell_i<decodeCell_nCol AND decodeCell_ofstCol[decodeCell_i]+decodeCell_szCol[decodeCell_i]<=decodeCell_nLocal)
         {
              continue<==0 and skip;
             int decodeCell_7_s<==decodeCell_ofstCol[decodeCell_i] and skip;
             int decodeCell_7_v and skip;
             unsigned char *decodeCell_7_pData and skip;
             if(decodeCell_szCol[decodeCell_i]=0) then 
             {
                 continue<==1 and skip;
                  decodeCell_i:=decodeCell_i+1
             }
             else 
             {
                  skip 
             };
             if(continue=0)   then 
             {
                 printBytes(a,decodeCell_x+decodeCell_7_s,decodeCell_szCol[decodeCell_i]);
                 output ("data[",decodeCell_i,"]: ") and skip;
                 decodeCell_7_pData:=decodeCell_x+decodeCell_7_s;
                 if(decodeCell_typeCol[decodeCell_i]<=7) then 
                 {
                     decodeCell_7_v:=(char)decodeCell_7_pData[0];
                     decodeCell_k:=1;
                     
                     while(decodeCell_k<decodeCell_szCol[decodeCell_i])
                     {
                         decodeCell_7_v:=(decodeCell_7_v<<8)+decodeCell_7_pData[decodeCell_k];
                         decodeCell_k:=decodeCell_k+1
                         
                     };
                     if(decodeCell_typeCol[decodeCell_i]=7) then 
                     {
                         float decodeCell_7_11_12_r and skip;
                         memcpy(&decodeCell_7_11_12_r,&decodeCell_7_v,8) and skip;
                         output (decodeCell_7_11_12_r,"#g\n","#g\n") and skip
                     }
                     else
                     {
                         output (decodeCell_7_v,"\n","\n") and skip
                     }
                     
                 }
                 else
                 {
                     int decodeCell_7_14_ii,decodeCell_7_14_jj and skip;
                     char decodeCell_7_14_zConst[32] and skip;
                     if((decodeCell_typeCol[decodeCell_i] & 1)=0) then 
                     {
                         decodeCell_7_14_zConst[0]:='x';
                         decodeCell_7_14_zConst[1]:='\'';
                         decodeCell_7_14_ii:=2 and decodeCell_7_14_jj:=0;
                         while(decodeCell_7_14_jj<decodeCell_szCol[decodeCell_i] AND decodeCell_7_14_ii<24)
                         {
                             sprintf(decodeCell_7_14_zConst+decodeCell_7_14_ii,"%02x",decodeCell_7_pData[decodeCell_7_14_jj]) and skip;
                             decodeCell_7_14_jj:=decodeCell_7_14_jj+1 and decodeCell_7_14_ii:=decodeCell_7_14_ii+2
                             
                         }
                         
                     }
                     else
                     {
                         decodeCell_7_14_zConst[0]:='\'';
                         decodeCell_7_14_ii:=1 and decodeCell_7_14_jj:=0;
                         while(decodeCell_7_14_jj<decodeCell_szCol[decodeCell_i] AND decodeCell_7_14_ii<24)
                         {
                             decodeCell_7_14_zConst[decodeCell_7_14_ii]:=( if(isprint((unsigned char)(decodeCell_7_pData[decodeCell_7_14_jj]),RValue)) then decodeCell_7_pData[decodeCell_7_14_jj] else '.');
                             decodeCell_7_14_jj:=decodeCell_7_14_jj+1 and decodeCell_7_14_ii:=decodeCell_7_14_ii+1
                             
                         };
                         decodeCell_7_14_zConst[decodeCell_7_14_ii]:=0
                     };
                     if(decodeCell_7_14_jj<decodeCell_szCol[decodeCell_i]) then 
                     {
                         memcpy(decodeCell_7_14_zConst+decodeCell_7_14_ii,"...'",5) and skip
                         
                     }
                     else
                     {
                         memcpy(decodeCell_7_14_zConst+decodeCell_7_14_ii,"'",2) and skip
                     };
                     output (decodeCell_7_14_zConst,"\n","\n") and skip
                 };
                 decodeCell_j:=decodeCell_ofstCol[decodeCell_i]+decodeCell_szCol[decodeCell_i];
                 decodeCell_i:=decodeCell_i+1
             }
             else
             {
                 skip
             }
         };
         continue<==0 and skip
         
     }
     else 
     {
          skip 
     };
     if(decodeCell_j<decodeCell_nLocal) then 
     {
         printBytes(a,decodeCell_x+decodeCell_j,0);
         output ("... ",decodeCell_nLocal-decodeCell_j," bytes of content ...\n") and skip
         
     }
     else 
     {
          skip 
     };
     if(decodeCell_nLocal<decodeCell_nPayload) then 
     {
         printBytes(a,decodeCell_x+decodeCell_nLocal,4);
         output ("overflow-page: ",decodeInt32(decodeCell_x+decodeCell_nLocal,RValue),"\n") and skip
         
     }
     else 
     {
          skip 
     }
     )
     }; 
  function decode_btree_page ( unsigned char *a,int pgno,int hdrSize,char *zArgs )
 {
     frame(decode_btree_page_zType,decode_btree_page_nCell,decode_btree_page_i,decode_btree_page_j,decode_btree_page_iCellPtr,decode_btree_page_showCellContent,decode_btree_page_showMap,decode_btree_page_cellToDecode,decode_btree_page_zMap,nm_3$,switch$,nm_4$,decode_btree_page_cofst,decode_btree_page_zDesc,decode_btree_page_n,decode_btree_page_11_zBuf,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     char *decode_btree_page_zType<=="unknown" and skip;
     int decode_btree_page_nCell and skip;
     int decode_btree_page_i,decode_btree_page_j and skip;
     int decode_btree_page_iCellPtr and skip;
     int decode_btree_page_showCellContent<==0 and skip;
     int decode_btree_page_showMap<==0 and skip;
     int decode_btree_page_cellToDecode<==-2 and skip;
     char *decode_btree_page_zMap<==0 and skip;
     int switch$ and skip;
     break$<==0 and skip;
      switch$<==0 and skip;
      int nm_3$ and skip;
     nm_3$ := a[0];
     if (nm_3$=2 OR (switch$=1 AND break$=0 AND return=0) ) then 
     {
         switch$<==1 and skip;
         decode_btree_page_zType:="index interior node";
         break$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_3$=5 OR (switch$=1 AND break$=0 AND return=0) ) then 
     {
         switch$<==1 and skip;
         decode_btree_page_zType:="table interior node";
         break$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_3$=10 OR (switch$=1 AND break$=0 AND return=0) ) then 
     {
         switch$<==1 and skip;
         decode_btree_page_zType:="index leaf";
         break$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_3$=13 OR (switch$=1 AND break$=0 AND return=0) ) then 
     {
         switch$<==1 and skip;
         decode_btree_page_zType:="table leaf";
         break$<==1 and skip
          
     }
     else
     {
         skip
     };
     while(zArgs[0])
     {
         break$<==0 and skip;
          switch$<==0 and skip;
          int nm_4$ and skip;
         nm_4$ := zArgs[0];
         if (nm_4$='c' OR (switch$=1 AND break$=0 AND return=0) ) then 
         {
             switch$<==1 and skip;
             decode_btree_page_showCellContent:=1;
             break$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_4$='m' OR (switch$=1 AND break$=0 AND return=0) ) then 
         {
             switch$<==1 and skip;
             decode_btree_page_showMap:=1;
             break$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_4$='d' OR (switch$=1 AND break$=0 AND return=0) ) then 
         {
             switch$<==1 and skip;
             if(!isdigit((unsigned char)(zArgs[1]))) then 
             {
                 decode_btree_page_cellToDecode:=-1
                 
             }
             else
             {
                 decode_btree_page_cellToDecode:=0;
                 while(isdigit((unsigned char)(zArgs[1])))
                 {
                     zArgs:=zArgs+1;
                     decode_btree_page_cellToDecode:=decode_btree_page_cellToDecode*10+zArgs[0]-'0'
                 }
             };
             break$<==1 and skip
              
         }
         else
         {
             skip
         };
         zArgs:=zArgs+1
     };
     decode_btree_page_nCell:=a[3]*256+a[4];
     decode_btree_page_iCellPtr:=( if((a[0]=2 OR a[0]=5)) then 12 else 8);
     if(decode_btree_page_cellToDecode>=decode_btree_page_nCell) then 
     {
         output ("Page ",pgno," has only ",decode_btree_page_nCell," cells\n") and skip;
          return<==1 and skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         output ("Header on btree page ",pgno,":\n") and skip;
         print_decode_line(a,0,1,decode_btree_page_zType);
         print_decode_line(a,1,2,"Offset to first freeblock");
         print_decode_line(a,3,2,"Number of cells on this page");
         print_decode_line(a,5,2,"Offset to cell content area");
         print_decode_line(a,7,1,"Fragmented byte count");
         if(a[0]=2 OR a[0]=5) then 
         {
             print_decode_line(a,8,4,"Right child")
             
         }
         else 
         {
              skip 
         };
         if(decode_btree_page_cellToDecode=(-2) AND decode_btree_page_nCell>0) then 
         {
             output (" key: lx=left-child n=payload-size r=rowid\n") and skip
             
         }
         else 
         {
              skip 
         };
         if(decode_btree_page_showMap) then 
         {
             decode_btree_page_zMap:=sqlite3_malloc(pagesize,RValue)
             //memset(decode_btree_page_zMap,'.',pagesize) and skip;
             //memset(decode_btree_page_zMap,'1',hdrSize) and skip;
             //memset(&decode_btree_page_zMap[hdrSize],'H',decode_btree_page_iCellPtr) and skip;
             //memset(&decode_btree_page_zMap[hdrSize+decode_btree_page_iCellPtr],'P',2*decode_btree_page_nCell) and skip
             
         }
         else 
         {
              skip 
         };
         decode_btree_page_i:=0;
         
         while(decode_btree_page_i<decode_btree_page_nCell)
         {
             int decode_btree_page_cofst<==decode_btree_page_iCellPtr+decode_btree_page_i*2 and skip;
             char *decode_btree_page_zDesc and skip;
             int decode_btree_page_n and skip;
             decode_btree_page_cofst:=a[decode_btree_page_cofst]*256+a[decode_btree_page_cofst+1];
             decode_btree_page_n:=describeCell(a[0],&a[decode_btree_page_cofst-hdrSize],decode_btree_page_showCellContent,&decode_btree_page_zDesc,RValue);
             if(decode_btree_page_showMap) then 
             {
                 char decode_btree_page_11_zBuf[30] and skip;
                 //memset(&decode_btree_page_zMap[decode_btree_page_cofst],'*',(int)decode_btree_page_n) and skip;
                 decode_btree_page_zMap[decode_btree_page_cofst]:='[';
                 decode_btree_page_zMap[decode_btree_page_cofst+decode_btree_page_n-1]:=']';
                 sprintf(decode_btree_page_11_zBuf,"%d",decode_btree_page_i) and skip;
                 decode_btree_page_j:=(int)strlen(decode_btree_page_11_zBuf);
                 if(decode_btree_page_j<=decode_btree_page_n-2) then 
                 {
                     memcpy(&decode_btree_page_zMap[decode_btree_page_cofst+1],decode_btree_page_11_zBuf,decode_btree_page_j) and skip
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
             if(decode_btree_page_cellToDecode=(-2)) then 
             {
                 output (" ",decode_btree_page_cofst,"ell[",decode_btree_page_i,"] ",decode_btree_page_zDesc,"\n") and skip
                 
             }
             else
             {
                 if(decode_btree_page_cellToDecode=(-1) OR decode_btree_page_cellToDecode=decode_btree_page_i) then 
                 {
                     decodeCell(a,pgno,decode_btree_page_i,hdrSize,decode_btree_page_cofst-hdrSize)
                     
                 }
                 else 
                 {
                      skip 
                 }
             };
             decode_btree_page_i:=decode_btree_page_i+1
             
         };
         if(decode_btree_page_showMap) then 
         {
             output ("Page map:  (H=header P=cell-index 1=page-1-header .=free-space)\n") and skip;
             decode_btree_page_i:=0;
             
             while(decode_btree_page_i<pagesize)
             {
                 output (" ",decode_btree_page_i,"03x: ",&decode_btree_page_zMap[decode_btree_page_i],"\n") and skip;
                 decode_btree_page_i:=decode_btree_page_i+64
                 
             };
             sqlite3_free(decode_btree_page_zMap,RValue) and skip
             
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
  function decode_trunk_page ( int pgno,int detail,int recursive )
 {
     frame(decode_trunk_page_n,decode_trunk_page_i,decode_trunk_page_a,decode_trunk_page_1_2_x,decode_trunk_page_1_2_zIdx) and ( 
     int decode_trunk_page_n,decode_trunk_page_i and skip;
     unsigned char *decode_trunk_page_a and skip;
     while(pgno>0)
     {
         decode_trunk_page_a:=fileRead((pgno-1)*pagesize,pagesize,RValue);
         output ("Decode of freelist trunk page ",pgno,":\n") and skip;
         print_decode_line(decode_trunk_page_a,0,4,"Next freelist trunk page");
         print_decode_line(decode_trunk_page_a,4,4,"Number of entries on this page");
         if(detail) then 
         {
             decode_trunk_page_n:=(int)decodeInt32(&decode_trunk_page_a[4],RValue);
             decode_trunk_page_i:=0;
             
             while(decode_trunk_page_i<decode_trunk_page_n)
             {
                 int decode_trunk_page_1_2_x and skip;
                 decode_trunk_page_1_2_x:=decodeInt32(&decode_trunk_page_a[8+4*decode_trunk_page_i],RValue);
                 char decode_trunk_page_1_2_zIdx[10] and skip;
                 sprintf(decode_trunk_page_1_2_zIdx,"[%d]",decode_trunk_page_i) and skip;
                 output ("  ",decode_trunk_page_1_2_zIdx," ",decode_trunk_page_1_2_x,"7u") and skip;
                 if(decode_trunk_page_i % 5=4) then 
                 {
                     output ("\n") and skip
                 }
                 else 
                 {
                      skip 
                 };
                 decode_trunk_page_i:=decode_trunk_page_i+1
                 
             };
             if(decode_trunk_page_i % 5!=0) then 
             {
                 output ("\n") and skip
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
         if(!recursive) then 
         {
             pgno:=0
             
         }
         else
         {
             pgno:=(int)decodeInt32(&decode_trunk_page_a[0],RValue)
         };
         sqlite3_free(decode_trunk_page_a,RValue) and skip
     }
     )
     }; 
      char **zPageUse and skip;
 
  function page_usage_cell ( unsigned char cType,unsigned char *a,int pgno,int cellno )
 {
     frame(page_usage_cell_i,page_usage_cell_n,page_usage_cell_nPayload,page_usage_cell_rowid,page_usage_cell_nLocal,page_usage_cell_5_ovfl,page_usage_cell_5_cnt) and ( 
     int page_usage_cell_i and skip;
     int page_usage_cell_n<==0 and skip;
     int page_usage_cell_nPayload and skip;
     int page_usage_cell_rowid and skip;
     int page_usage_cell_nLocal and skip;
     page_usage_cell_i:=0;
     if(cType<=5) then 
     {
         a:=a+4;
         page_usage_cell_n:=page_usage_cell_n+4
         
     }
     else 
     {
          skip 
     };
     if(cType!=5) then 
     {
         page_usage_cell_i:=decodeVarint(a,&page_usage_cell_nPayload,RValue);
         a:=a+page_usage_cell_i;
         page_usage_cell_n:=page_usage_cell_n+page_usage_cell_i;
         page_usage_cell_nLocal:=localPayload(page_usage_cell_nPayload,cType,RValue)
         
     }
     else
     {
         page_usage_cell_nLocal<==0 and page_usage_cell_nPayload<==page_usage_cell_nLocal and skip
     };
     if(cType=5 OR cType=13) then 
     {
         page_usage_cell_i:=decodeVarint(a,&page_usage_cell_rowid,RValue);
         a:=a+page_usage_cell_i;
         page_usage_cell_n:=page_usage_cell_n+page_usage_cell_i
         
     }
     else 
     {
          skip 
     };
     if(page_usage_cell_nLocal<page_usage_cell_nPayload) then 
     {
         int page_usage_cell_5_ovfl and skip;
         page_usage_cell_5_ovfl:=decodeInt32(a+page_usage_cell_nLocal,RValue);
         int page_usage_cell_5_cnt<==0 and skip;
         while(page_usage_cell_5_ovfl AND (page_usage_cell_5_cnt)<mxPage)
         {
             page_usage_cell_5_cnt:=page_usage_cell_5_cnt+1;
             //page_usage_msg(page_usage_cell_5_ovfl,"overflow %d from cell %d of page %d",page_usage_cell_5_cnt,cellno,pgno);
             a:=fileRead((page_usage_cell_5_ovfl-1)*pagesize,4,RValue);
             page_usage_cell_5_ovfl:=decodeInt32(a,RValue);
             sqlite3_free(a,RValue) and skip
         }
         
     }
     else 
     {
          skip 
     }
     )
     }; 
  function page_usage_btree ( int pgno,int parent,int idx,char *zName )
 {
     frame(page_usage_btree_a,page_usage_btree_zType,page_usage_btree_nCell,page_usage_btree_i,page_usage_btree_hdr,nm_5$,switch$,page_usage_btree_5_cellstart,page_usage_btree_5_child,page_usage_btree_5_ofst,page_usage_btree_6_cellstart,page_usage_btree_6_ofst,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     unsigned char *page_usage_btree_a and skip;
     char *page_usage_btree_zType<=="corrupt node" and skip;
     int page_usage_btree_nCell and skip;
     int page_usage_btree_i and skip;
     int page_usage_btree_hdr<==( if(pgno=1) then 100 else 0) and skip;
     if(pgno<=0 OR pgno>mxPage) then 
     {
          return<==1 and skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         page_usage_btree_a:=fileRead((pgno-1)*pagesize,pagesize,RValue);
         int switch$ and skip;
         break$<==0 and skip;
          switch$<==0 and skip;
          int nm_5$ and skip;
         nm_5$ := page_usage_btree_a[page_usage_btree_hdr];
         if (nm_5$=2 OR (switch$=1 AND break$=0 AND return=0) ) then 
         {
             switch$<==1 and skip;
             page_usage_btree_zType:="interior node of index";
             break$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_5$=5 OR (switch$=1 AND break$=0 AND return=0) ) then 
         {
             switch$<==1 and skip;
             page_usage_btree_zType:="interior node of table";
             break$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_5$=10 OR (switch$=1 AND break$=0 AND return=0) ) then 
         {
             switch$<==1 and skip;
             page_usage_btree_zType:="leaf of index";
             break$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_5$=13 OR (switch$=1 AND break$=0 AND return=0) ) then 
         {
             switch$<==1 and skip;
             page_usage_btree_zType:="leaf of table";
             break$<==1 and skip
              
         }
         else
         {
             skip
         };
         if(parent) then 
         {
             //page_usage_msg(pgno,"%s [%s], child %d of page %d",page_usage_btree_zType,zName,idx,parent)
             skip
         }
         else
         {
             //page_usage_msg(pgno,"root %s [%s]",page_usage_btree_zType,zName)
			 skip
         };
         page_usage_btree_nCell:=page_usage_btree_a[page_usage_btree_hdr+3]*256+page_usage_btree_a[page_usage_btree_hdr+4];
         if(page_usage_btree_a[page_usage_btree_hdr]=2 OR page_usage_btree_a[page_usage_btree_hdr]=5) then 
         {
             int page_usage_btree_5_cellstart<==page_usage_btree_hdr+12 and skip;
             int page_usage_btree_5_child and skip;
             page_usage_btree_i:=0;
             
             while(page_usage_btree_i<page_usage_btree_nCell)
             {
                 int page_usage_btree_5_ofst and skip;
                 page_usage_btree_5_ofst:=page_usage_btree_5_cellstart+page_usage_btree_i*2;
                 page_usage_btree_5_ofst:=page_usage_btree_a[page_usage_btree_5_ofst]*256+page_usage_btree_a[page_usage_btree_5_ofst+1];
                 page_usage_btree_5_child:=decodeInt32(page_usage_btree_a+page_usage_btree_5_ofst,RValue);
                 page_usage_btree(page_usage_btree_5_child,pgno,page_usage_btree_i,zName);
                 page_usage_btree_i:=page_usage_btree_i+1
                 
             };
             page_usage_btree_5_child:=decodeInt32(page_usage_btree_a+page_usage_btree_5_cellstart-4,RValue);
             page_usage_btree(page_usage_btree_5_child,pgno,page_usage_btree_i,zName)
             
         }
         else 
         {
              skip 
         };
         if(page_usage_btree_a[page_usage_btree_hdr]=2 OR page_usage_btree_a[page_usage_btree_hdr]=10 OR page_usage_btree_a[page_usage_btree_hdr]=13) then 
         {
             int page_usage_btree_6_cellstart<==page_usage_btree_hdr+8+4*(page_usage_btree_a[page_usage_btree_hdr]<=5) and skip;
             page_usage_btree_i:=0;
             
             while(page_usage_btree_i<page_usage_btree_nCell)
             {
                 int page_usage_btree_6_ofst and skip;
                 page_usage_btree_6_ofst:=page_usage_btree_6_cellstart+page_usage_btree_i*2;
                 page_usage_btree_6_ofst:=page_usage_btree_a[page_usage_btree_6_ofst]*256+page_usage_btree_a[page_usage_btree_6_ofst+1];
                 page_usage_cell(page_usage_btree_a[page_usage_btree_hdr],page_usage_btree_a+page_usage_btree_6_ofst,pgno,page_usage_btree_i);
                 page_usage_btree_i:=page_usage_btree_i+1
                 
             }
             
         }
         else 
         {
              skip 
         };
         sqlite3_free(page_usage_btree_a,RValue) and skip
     }
     else
     {
         skip
     }
     )
     }; 
  function page_usage_freelist ( int pgno )
 {
     frame(page_usage_freelist_a,page_usage_freelist_cnt,page_usage_freelist_i,page_usage_freelist_n,page_usage_freelist_iNext,page_usage_freelist_parent,page_usage_freelist_1_child) and ( 
     unsigned char *page_usage_freelist_a and skip;
     int page_usage_freelist_cnt<==0 and skip;
     int page_usage_freelist_i and skip;
     int page_usage_freelist_n and skip;
     int page_usage_freelist_iNext and skip;
     int page_usage_freelist_parent<==1 and skip;
     while(pgno>0 AND pgno<=mxPage AND (page_usage_freelist_cnt)<mxPage)
     {
         page_usage_freelist_cnt:=page_usage_freelist_cnt+1;
         //page_usage_msg(pgno,"freelist trunk #%d child of %d",page_usage_freelist_cnt,page_usage_freelist_parent);
         page_usage_freelist_a:=fileRead((pgno-1)*pagesize,pagesize,RValue);
         page_usage_freelist_iNext:=decodeInt32(page_usage_freelist_a,RValue);
         page_usage_freelist_n:=decodeInt32(page_usage_freelist_a+4,RValue);
         page_usage_freelist_i:=0;
         
         while(page_usage_freelist_i<page_usage_freelist_n)
         {
             int page_usage_freelist_1_child and skip;
             page_usage_freelist_1_child:=decodeInt32(page_usage_freelist_a+(page_usage_freelist_i*4+8),RValue);
             //page_usage_msg(page_usage_freelist_1_child,"freelist leaf, child %d of trunk page %d",page_usage_freelist_i,pgno);
             page_usage_freelist_i:=page_usage_freelist_i+1
             
         };
         sqlite3_free(page_usage_freelist_a,RValue) and skip;
         page_usage_freelist_parent:=pgno;
         pgno:=page_usage_freelist_iNext
     }
     )
     }; 
  function page_usage_ptrmap ( unsigned char *a )
 {
     frame(page_usage_ptrmap_1_usable,page_usage_ptrmap_1_pgno,page_usage_ptrmap_1_perPage) and ( 
     if(a[55]) then 
     {
         int page_usage_ptrmap_1_usable<==pagesize-a[20] and skip;
         int page_usage_ptrmap_1_pgno<==2 and skip;
         int page_usage_ptrmap_1_perPage<==page_usage_ptrmap_1_usable/ 5 and skip;
         while(page_usage_ptrmap_1_pgno<=mxPage)
         {
             //page_usage_msg(page_usage_ptrmap_1_pgno,"PTRMAP page covering %d..%d",page_usage_ptrmap_1_pgno+1,page_usage_ptrmap_1_pgno+page_usage_ptrmap_1_perPage);
             page_usage_ptrmap_1_pgno:=page_usage_ptrmap_1_pgno+page_usage_ptrmap_1_perPage+1
         }
         
     }
     else 
     {
          skip 
     }
     )
     }; 
  function page_usage_report ( char *zPrg,char *zDbName )
 {
     frame(page_usage_report_i,page_usage_report_j,page_usage_report_rc,db1,pStmt2,page_usage_report_a,page_usage_report_zQuery,page_usage_report_temp$_1,page_usage_report_3_4_pgno,page_usage_report_3_4_temp$_2,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     int page_usage_report_i,page_usage_report_j and skip;
     int page_usage_report_rc and skip;
     unsigned char *page_usage_report_a and skip;
     char page_usage_report_zQuery[200] and skip;
     if(mxPage<1) then 
     {
         output ("empty database\n") and skip;
          return<==1 and skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         db1:=openDatabase(zPrg,zDbName,RValue);
         zPageUse:=sqlite3_malloc(sizeof((zPageUse[0]))*(mxPage+1),RValue);
         if(zPageUse=0) then 
         {
             out_of_memory()
         }
         else 
         {
              skip 
         };
         //memset(zPageUse,0,sizeof((zPageUse[0]))*(mxPage+1)) and skip;
         page_usage_report_a:=fileRead(0,100,RValue);
         int page_usage_report_temp$_1 and skip;
         page_usage_report_temp$_1:=decodeInt32(page_usage_report_a+32,RValue);
         page_usage_freelist(page_usage_report_temp$_1);
         page_usage_ptrmap(page_usage_report_a);
         sqlite3_free(page_usage_report_a,RValue) and skip;
         page_usage_btree(1,0,0,"sqlite_master");
         sqlite3_exec(db1,"PRAGMA writable_schema=ON",0,0,0,RValue) and skip;
         break$<==0 and skip;
         page_usage_report_j:=0;
         
         while( break$=0 AND  page_usage_report_j<2)
         {
             sqlite3_snprintf(200,page_usage_report_zQuery,"SELECT type, name, rootpage FROM SQLITE_MASTER WHERE rootpage ORDER BY rowid %s",( if(page_usage_report_j) then "DESC" else ""),RValue) and skip;
             page_usage_report_rc:=sqlite3_prepare_v2(db1,page_usage_report_zQuery,-1,&pStmt2,0,RValue);
             if(page_usage_report_rc=0) then 
             {
                 while(sqlite3_step(pStmt2,RValue)=100)
                 {
                     int page_usage_report_3_4_pgno and skip;
                     page_usage_report_3_4_pgno:=sqlite3_column_int(pStmt2,2,RValue);
                     int page_usage_report_3_4_temp$_2 and skip;
                     page_usage_report_3_4_temp$_2:=sqlite3_column_text(pStmt2,1,RValue);
                     page_usage_btree(page_usage_report_3_4_pgno,0,0,(char *)page_usage_report_3_4_temp$_2)
                 }
                 
             }
             else
             {
                 output ("ERROR: cannot query database: ",sqlite3_errmsg(db1,RValue),"\n") and skip
             };
             page_usage_report_rc:=sqlite3_finalize(pStmt2,RValue);
             if(page_usage_report_rc=0) then 
             {
                 break$<==1 and skip
              }
             else 
             {
                  skip 
             };
             if(break$=0)   then
             {
                 page_usage_report_j:=page_usage_report_j+1
             }
             else
             {
                 skip
             }
             
         };
         break$<==0 and skip;
         sqlite3_close(db1,RValue) and skip;
         page_usage_report_i:=1;
         
         while(page_usage_report_i<=mxPage)
         {
             output (page_usage_report_i,": ",( if(zPageUse[page_usage_report_i]) then zPageUse[page_usage_report_i] else "???"),"\n","\n") and skip;
             sqlite3_free(zPageUse[page_usage_report_i],RValue) and skip;
             page_usage_report_i:=page_usage_report_i+1
             
         };
         sqlite3_free(zPageUse,RValue) and skip;
         zPageUse:=0
     }
     else
     {
         skip
     }
     )
     }; 
  function ptrmap_coverage_report ( char *zDbName )
 {
     frame(ptrmap_coverage_report_pgno,ptrmap_coverage_report_aHdr,ptrmap_coverage_report_a,ptrmap_coverage_report_usable,ptrmap_coverage_report_perPage,ptrmap_coverage_report_i,ptrmap_coverage_report_zType,ptrmap_coverage_report_iFrom,nm_6$,switch$,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     int ptrmap_coverage_report_pgno and skip;
     unsigned char *ptrmap_coverage_report_aHdr and skip;
     unsigned char *ptrmap_coverage_report_a and skip;
     int ptrmap_coverage_report_usable and skip;
     int ptrmap_coverage_report_perPage and skip;
     int ptrmap_coverage_report_i and skip;
     if(mxPage<1) then 
     {
         output ("empty database\n") and skip;
          return<==1 and skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         ptrmap_coverage_report_aHdr:=fileRead(0,100,RValue);
         if(ptrmap_coverage_report_aHdr[55]=0) then 
         {
             output ("database does not use PTRMAP pages\n") and skip;
              return<==1 and skip
             
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             ptrmap_coverage_report_usable:=pagesize-ptrmap_coverage_report_aHdr[20];
             ptrmap_coverage_report_perPage:=ptrmap_coverage_report_usable/ 5;
             sqlite3_free(ptrmap_coverage_report_aHdr,RValue) and skip;
             output (1,": root of sqlite_master\n",": root of sqlite_master\n") and skip;
             ptrmap_coverage_report_pgno:=2;
             
             while(ptrmap_coverage_report_pgno<=mxPage)
             {
                 output (ptrmap_coverage_report_pgno,": PTRMAP page covering ",ptrmap_coverage_report_pgno+1,"..",ptrmap_coverage_report_pgno+ptrmap_coverage_report_perPage,"\n","\n") and skip;
                 ptrmap_coverage_report_a:=fileRead((ptrmap_coverage_report_pgno-1)*pagesize,ptrmap_coverage_report_usable,RValue);
                 ptrmap_coverage_report_i:=0;
                 
                 while(ptrmap_coverage_report_i+5<=ptrmap_coverage_report_usable AND ptrmap_coverage_report_pgno+1+ptrmap_coverage_report_i/ 5<=mxPage)
                 {
                     char *ptrmap_coverage_report_zType<=="???" and skip;
                     int ptrmap_coverage_report_iFrom and skip;
                     ptrmap_coverage_report_iFrom:=decodeInt32(&ptrmap_coverage_report_a[ptrmap_coverage_report_i+1],RValue);
                     int switch$ and skip;
                     break$<==0 and skip;
                      switch$<==0 and skip;
                      int nm_6$ and skip;
                     nm_6$ := ptrmap_coverage_report_a[ptrmap_coverage_report_i];
                     if (nm_6$=1 OR (switch$=1 AND break$=0 AND return=0) ) then 
                     {
                         switch$<==1 and skip;
                         ptrmap_coverage_report_zType:="b-tree root page";
                         break$<==1 and skip
                          
                     }
                     else
                     {
                         skip
                     };
                     if (nm_6$=2 OR (switch$=1 AND break$=0 AND return=0) ) then 
                     {
                         switch$<==1 and skip;
                         ptrmap_coverage_report_zType:="freelist page";
                         break$<==1 and skip
                          
                     }
                     else
                     {
                         skip
                     };
                     if (nm_6$=3 OR (switch$=1 AND break$=0 AND return=0) ) then 
                     {
                         switch$<==1 and skip;
                         ptrmap_coverage_report_zType:="first page of overflow";
                         break$<==1 and skip
                          
                     }
                     else
                     {
                         skip
                     };
                     if (nm_6$=4 OR (switch$=1 AND break$=0 AND return=0) ) then 
                     {
                         switch$<==1 and skip;
                         ptrmap_coverage_report_zType:="later page of overflow";
                         break$<==1 and skip
                          
                     }
                     else
                     {
                         skip
                     };
                     if (nm_6$=5 OR (switch$=1 AND break$=0 AND return=0) ) then 
                     {
                         switch$<==1 and skip;
                         ptrmap_coverage_report_zType:="b-tree non-root page";
                         break$<==1 and skip
                          
                     }
                     else
                     {
                         skip
                     };
                     output (ptrmap_coverage_report_pgno+1+ptrmap_coverage_report_i/ 5,": ",ptrmap_coverage_report_zType,", parent=",ptrmap_coverage_report_iFrom,"u\n","u\n") and skip;
                     ptrmap_coverage_report_i:=ptrmap_coverage_report_i+5
                     
                 };
                 sqlite3_free(ptrmap_coverage_report_a,RValue) and skip;
                 ptrmap_coverage_report_pgno:=ptrmap_coverage_report_pgno+ptrmap_coverage_report_perPage+1
                 
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
  function usage ( char *argv0 )
 {
     fprintf(stderr,"Usage %s ?--uri? FILENAME ?args...?\n\n",argv0) and skip;
     fprintf(stderr,"switches:\n    --raw           Read db file directly, bypassing SQLite VFS\nargs:\n    dbheader        Show database header\n    pgidx           Index of how each page is used\n    ptrmap          Show all PTRMAP page content\n    NNN..MMM        Show hex of pages NNN through MMM\n    NNN..end        Show hex of pages NNN through end of file\n    NNNb            Decode btree page NNN\n    NNNbc           Decode btree page NNN and show content\n    NNNbm           Decode btree page NNN and show a layout map\n    NNNbdCCC        Decode cell CCC on btree page NNN\n    NNNt            Decode freelist trunk page NNN\n    NNNtd           Show leaf freelist pages on the decode\n    NNNtr           Recursively decode freelist starting at NNN\n") and skip
     
 };
 function main ( int RValue )
 {
     frame(verifystat,main_argc,main_argv,main_szFile,main_zPgSz,main_zPrg,main_azArg,main_nArg,main_4_i,main_6_i,main_6_iStart,main_6_iEnd,main_6_zLeft,main_6_13_15_16_ofst,main_6_13_15_16_nByte,main_6_13_15_16_hdrSize,main_6_13_15_16_a,main_6_13_15_19_20_detail,main_6_13_15_19_20_recursive,main_6_13_15_19_20_j,return,continue) and (
     int continue<==0 and skip;
     int return<==0 and skip;
     int main_argc<==3 and skip;
     char *main_argv[]<=={"showdb.exe","-raw","sdu.db"} and skip;
     int main_szFile and skip;
     unsigned char *main_zPgSz and skip;
     char *main_zPrg<==main_argv[0] and skip;
     char **main_azArg<==main_argv and skip;
     int main_nArg<==3 and skip;
	 int verifystat<==0 and skip;
	 while(verifystat<28485919)
	 {
		verifystat:=verifystat+1
	 };
     if(main_nArg>1) then 
     {
         if(sqlite3_stricmp("-raw","-raw",RValue)=0 OR sqlite3_stricmp("--raw","-raw",RValue)=0) then 
         {
			printf("ttttt") and skip;
             bRaw:=1;
             main_azArg:=main_azArg+1;
             main_nArg:=main_nArg-1
			 
             
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
	 printf("aaaaa\n") and skip;
	 
     fileOpen(main_zPrg,"stu.db");
	 printf("bbbb\n") and skip;
     main_szFile:=fileGetsize(dbfd,RValue);
     main_zPgSz:=fileRead(16,2,RValue);
     pagesize:=main_zPgSz[0]*256+main_zPgSz[1]*65536;
     if(pagesize=0) then 
     {
         pagesize:=1024
     }
     else 
     {
          skip 
     };
     sqlite3_free(main_zPgSz,RValue) and skip;
     output ("Pagesize: ",pagesize,"\n") and skip;
     mxPage:=(int)((main_szFile+pagesize-1)/ pagesize);
     output ("Available pages: 1..",mxPage,"\n") and skip;
     if(main_nArg=2) then 
     {
         int main_4_i and skip;
         main_4_i:=1;
         
         while(main_4_i<=mxPage)
         {
             print_page(main_4_i);
             main_4_i:=main_4_i+1
             
         }
         
     }
     else
     {
         int main_6_i and skip;
         continue<==0 and skip;
         main_6_i:=2;
         
         while(main_6_i<main_nArg)
         {
              continue<==0 and skip;
             int main_6_iStart,main_6_iEnd and skip;
             char *main_6_zLeft and skip;
             if(strcmp(main_azArg[main_6_i],"dbheader")=0) then 
             {
                 print_db_header();
                 continue<==1 and skip;
                  main_6_i:=main_6_i+1
                 
             }
             else 
             {
                  skip 
             };
             if(continue=0)   then 
             {
                 if(strcmp(main_azArg[main_6_i],"pgidx")=0) then 
                 {
                     page_usage_report(main_zPrg,main_azArg[1]);
                     continue<==1 and skip;
                      main_6_i:=main_6_i+1
                     
                 }
                 else 
                 {
                      skip 
                 };
                 if(continue=0)   then 
                 {
                     if(strcmp(main_azArg[main_6_i],"ptrmap")=0) then 
                     {
                         ptrmap_coverage_report(main_azArg[1]);
                         continue<==1 and skip;
                          main_6_i:=main_6_i+1
                         
                     }
                     else 
                     {
                          skip 
                     };
                     if(continue=0)   then 
                     {
                         if(strcmp(main_azArg[main_6_i],"help")=0) then 
                         {
                             usage(main_zPrg);
                             continue<==1 and skip;
                              main_6_i:=main_6_i+1
                             
                         }
                         else 
                         {
                              skip 
                         };
                         if(continue=0)   then 
                         {
                             if(!isdigit((unsigned char)(main_azArg[main_6_i,0]))) then 
                             {
                                 fprintf(stderr,"%s: unknown option: [%s]\n",main_zPrg,main_azArg[main_6_i]) and skip;
                                 continue<==1 and skip;
                                  main_6_i:=main_6_i+1
                                 
                             }
                             else 
                             {
                                  skip 
                             };
                             if(continue=0)   then 
                             {
                                 main_6_iStart:=strtol(main_azArg[main_6_i],&main_6_zLeft,0,RValue);
                                 if(main_6_zLeft AND strcmp(main_6_zLeft,"..end")=0) then 
                                 {
                                     main_6_iEnd:=mxPage
                                     
                                 }
                                 else
                                 {
                                     if(main_6_zLeft AND main_6_zLeft[0]='.' AND main_6_zLeft[1]='.') then 
                                     {
                                         main_6_iEnd:=strtol(&main_6_zLeft[2],0,0,RValue)
                                     }
                                     else
                                     {
                                         if(main_6_zLeft AND main_6_zLeft[0]='b') then 
                                         {
                                             int main_6_13_15_16_ofst,main_6_13_15_16_nByte,main_6_13_15_16_hdrSize and skip;
                                             unsigned char *main_6_13_15_16_a and skip;
                                             if(main_6_iStart=1) then 
                                             {
                                                 main_6_13_15_16_hdrSize<==100 and main_6_13_15_16_ofst<==main_6_13_15_16_hdrSize and skip;
                                                 main_6_13_15_16_nByte:=pagesize-100
                                                 
                                             }
                                             else
                                             {
                                                 main_6_13_15_16_hdrSize:=0;
                                                 main_6_13_15_16_ofst:=(main_6_iStart-1)*pagesize;
                                                 main_6_13_15_16_nByte:=pagesize
                                             };
                                             main_6_13_15_16_a:=fileRead(main_6_13_15_16_ofst,main_6_13_15_16_nByte,RValue);
                                             decode_btree_page(main_6_13_15_16_a,main_6_iStart,main_6_13_15_16_hdrSize,&main_6_zLeft[1]);
                                             sqlite3_free(main_6_13_15_16_a,RValue) and skip;
                                             continue<==1 and skip;
                                              main_6_i:=main_6_i+1
                                         }
                                         else
                                         {
                                             if(main_6_zLeft AND main_6_zLeft[0]='t') then 
                                             {
                                                 int main_6_13_15_19_20_detail<==0 and skip;
                                                 int main_6_13_15_19_20_recursive<==0 and skip;
                                                 int main_6_13_15_19_20_j and skip;
                                                 main_6_13_15_19_20_j:=1;
                                                 
                                                 while(main_6_zLeft[main_6_13_15_19_20_j])
                                                 {
                                                     if(main_6_zLeft[main_6_13_15_19_20_j]='r') then 
                                                     {
                                                         main_6_13_15_19_20_recursive:=1
                                                     }
                                                     else 
                                                     {
                                                          skip 
                                                     };
                                                     if(main_6_zLeft[main_6_13_15_19_20_j]='d') then 
                                                     {
                                                         main_6_13_15_19_20_detail:=1
                                                     }
                                                     else 
                                                     {
                                                          skip 
                                                     };
                                                     main_6_13_15_19_20_j:=main_6_13_15_19_20_j+1
                                                     
                                                 };
                                                 decode_trunk_page(main_6_iStart,main_6_13_15_19_20_detail,main_6_13_15_19_20_recursive);
                                                 continue<==1 and skip
                                              }
                                             else
                                             {
                                                 main_6_iEnd:=main_6_iStart
                                             }
                                         }
                                     }
                                 };
                                 if(continue=0)  then 
                                 {
                                     if(main_6_iStart<1 OR main_6_iEnd<main_6_iStart OR main_6_iEnd>mxPage) then 
                                     {
                                         fprintf(stderr,"Page argument should be LOWER?..UPPER?.  Range 1 to %d\n",mxPage) and skip
                                         
                                     }
                                     else 
                                     {
                                          skip 
                                     };
                                     while(main_6_iStart<=main_6_iEnd)
                                     {
                                         print_page(main_6_iStart);
                                         main_6_iStart:=main_6_iStart+1
                                     };
                                     main_6_i:=main_6_i+1
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
     };
     fileClose();
     return<==1 and skip;
	 RValue:=0;
     skip
     )
 };
  main(RValue)
 )
