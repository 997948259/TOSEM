</
define p:sqlite3_vmprintf_call=1;
define q:sqlite3_free_call=1;
alw(p->som(q))
/>

struct GState {
char *zErr and 
FILE *f and 
int szPg and 
int iRoot and 
int iCol and 
int pgno and 
unsigned char *aPage and 
unsigned char *aStack[20] and 
int aPgno[20] and 
int nStack and 
int bTrace 
};
  function ofstError ( GState *p,char *zFormat)
 {
	frame(ap) and(
     char* ap and skip;
	  sqlite3_free(p->zErr) and skip;
	  my_va_start(ap, zFormat) and skip;
	  p->zErr := sqlite3_vmprintf(zFormat, ap);
	  my_va_end(ap) and skip
	  )
     
 };
 function ofstRootAndColumn ( GState *p,char *zFile,char *zTable,char *zColumn )
 {
     frame(tmp,db,pstmt,ofstRootAndColumn_zSql,ofstRootAndColumn_rc,ofstRootAndColumn_3_temp$_1,ofstRootAndColumn_6_temp$_2,ofstRootAndColumn_8_zCol,ofstRootAndColumn_8_9_temp$_3,ofstRootAndColumn_11_temp$_4,return,goto,break$) and ( 
     int break$<==0 and skip;
     int goto<==0 and skip;
     int return<==0 and skip;
	 char tmp[100] and skip;
     char *ofstRootAndColumn_zSql<==0 and skip;
     int ofstRootAndColumn_rc and skip;
     if(p->zErr) then 
     {
          return<==1 and skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         ofstRootAndColumn_rc:=sqlite3_open(zFile,&db,RValue);
         if(ofstRootAndColumn_rc) then 
         {
			 sprintf(tmp, "cannot open database file \"%s\"", zFile) and skip;
             ofstError(p,tmp,RValue)
             
         }
         else 
         {
              skip 
         };
         if(goto=0)   then 
         {
             ofstRootAndColumn_zSql:=sqlite3_mprintf("SELECT rootpage FROM sqlite_master WHERE name=%Q",zTable,RValue);
             ofstRootAndColumn_rc:=sqlite3_prepare_v2(db,ofstRootAndColumn_zSql,-1,&pstmt,0,RValue);
             int ofstRootAndColumn_3_temp$_1 and skip;
             ofstRootAndColumn_3_temp$_1:=sqlite3_errmsg(db,RValue);
             if(ofstRootAndColumn_rc) then 
             {
				sprintf(tmp,"%s: [%s]",ofstRootAndColumn_3_temp$_1,ofstRootAndColumn_zSql) and skip;
                 ofstError(p,tmp,RValue)
             }
             else 
             {
                  skip 
             };
             sqlite3_free(ofstRootAndColumn_zSql,RValue) and skip;
             if(p->zErr) then 
             {
                 goto<==1 and skip
             }
             else 
             {
                  skip 
             };
             if(goto=0)   then 
             {
                 if(sqlite3_step(pstmt,RValue)!=100) then 
                 {
					sprintf(tmp,"cannot find table [%s]\n",zTable) and skip;
                     ofstError(p,tmp,RValue);
                     sqlite3_finalize(pstmt,RValue) and skip;
                     goto<==1 and skip
                     
                 }
                 else 
                 {
                      skip 
                 };
                 if(goto=0)   then 
                 {
                     p->iRoot:=sqlite3_column_int(pstmt,0,RValue);
                     sqlite3_finalize(pstmt,RValue) and skip;
                     p->iCol:=-1;
                     ofstRootAndColumn_zSql:=sqlite3_mprintf("PRAGMA table_info(%Q)",zTable,RValue);
                     ofstRootAndColumn_rc:=sqlite3_prepare_v2(db,ofstRootAndColumn_zSql,-1,&pstmt,0,RValue);
                     int ofstRootAndColumn_6_temp$_2 and skip;
                     ofstRootAndColumn_6_temp$_2:=sqlite3_errmsg(db,RValue);
                     if(ofstRootAndColumn_rc) then 
                     {
						sprintf(tmp,"%s: [%s}",ofstRootAndColumn_6_temp$_2,ofstRootAndColumn_zSql) and skip;
                         ofstError(p,tmp,RValue)
                     }
                     else 
                     {
                          skip 
                     };
                     sqlite3_free(ofstRootAndColumn_zSql,RValue) and skip;
                     if(p->zErr) then 
                     {
                         goto<==1 and skip
                     }
                     else 
                     {
                          skip 
                     };
                     if(goto=0)   then 
                     {
						
                         break$<==0 and skip;
                         while( break$=0 AND  sqlite3_step(pstmt,RValue)=100)
                         {
                             char *ofstRootAndColumn_8_zCol and skip;
                             ofstRootAndColumn_8_zCol:=sqlite3_column_text(pstmt,1,RValue);
                             int ofstRootAndColumn_8_9_temp$_3 and skip;
                             ofstRootAndColumn_8_9_temp$_3:=strlen(ofstRootAndColumn_8_zCol);
                             if(strlen(ofstRootAndColumn_8_zCol)=strlen(zColumn) AND sqlite3_strnicmp(ofstRootAndColumn_8_zCol,zColumn,ofstRootAndColumn_8_9_temp$_3,RValue)=0) then 
                             {
                                 p->iCol:=sqlite3_column_int(pstmt,0,RValue);
                                 break$<==1 and skip
                                  
                             }
                             else 
                             {
                                  skip 
                             }
                         };
                         break$<==0 and skip;
                         sqlite3_finalize(pstmt,RValue) and skip;
                         if(p->iCol<0) then 
                         {	
							sprintf(tmp,"no such column: %s.%s",zTable,zColumn) and skip;
                             ofstError(p,tmp,RValue);
                             goto<==1 and skip
                             
                         }
                         else 
                         {
                              skip 
                         };
                         if(goto=0)   then 
                         {
                             ofstRootAndColumn_zSql:=sqlite3_mprintf("PRAGMA page_size",RValue);
                             ofstRootAndColumn_rc:=sqlite3_prepare_v2(db,ofstRootAndColumn_zSql,-1,&pstmt,0,RValue);
                             int ofstRootAndColumn_11_temp$_4 and skip;
                             ofstRootAndColumn_11_temp$_4:=sqlite3_errmsg(db,RValue);
                             if(ofstRootAndColumn_rc) then 
                             {
								sprintf(tmp,"%s: [%s]",ofstRootAndColumn_11_temp$_4,ofstRootAndColumn_zSql) and skip;
                                 ofstError(p,tmp,RValue)
                             }
                             else 
                             {
                                  skip 
                             };
                             sqlite3_free(ofstRootAndColumn_zSql,RValue) and skip;
                             if(p->zErr) then 
                             {
                                 goto<==1 and skip
                             }
                             else 
                             {
                                  skip 
                             };
                             if(goto=0)   then 
                             {
                                 if(sqlite3_step(pstmt,RValue)!=100) then 
                                 {
									sprintf(tmp, "cannot find page size", zFile) and skip;
                                     ofstError(p,tmp,RValue)
                                 }
                                 else
                                 {
                                     p->szPg:=sqlite3_column_int(pstmt,0,RValue)
                                 };
                                 sqlite3_finalize(pstmt,RValue) and skip
                                 
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
     }
     else
     {
         skip
     };
     if(return=0)  then
     {
         sqlite3_close(db,RValue) and skip;
          return<==1 and skip
     }
     else
     {
         skip
     }
     )
     }; 
 function ofstPopPage ( GState *p )
 {
     frame(return) and ( 
     int return<==0 and skip;
     if(p->nStack<=0) then 
     {
          return<==1 and skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         p->nStack:=p->nStack-1;
         sqlite3_free(p->aStack[p->nStack],RValue) and skip;
         p->pgno:=p->aPgno[p->nStack-1];
         p->aPage:=p->aStack[p->nStack-1]
     }
     else
     {
         skip
     }
     )
     }; 
  function ofstPushPage ( GState *p,int pgno )
 {
     frame(tmp,ofstPushPage_got,return,pPage) and ( 
     int return<==0 and skip;
     unsigned char* pPage and skip;
	 char tmp[100] and skip;
     int ofstPushPage_got and skip;
     if(p->zErr) then 
     {
          return<==1 and skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         if(p->nStack>=(sizeof((p->aStack))/ sizeof((p->aStack[0])))) then 
         {
			sprintf(tmp, "page stack overflow") and skip;
             ofstError(p,tmp,RValue);
              return<==1 and skip
             
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             p->aPgno[p->nStack]:=pgno;
             pPage<==sqlite3_malloc(p->szPg,RValue) and p->aStack[p->nStack]<==pPage and skip;
             if(pPage=0) then 
             {
                 fprintf(stderr,"out of memory\n") and skip
                 
             }
             else 
             {
                  skip 
             };
             p->nStack:=p->nStack+1;
             p->aPage:=pPage;
             p->pgno:=pgno;
             fseek(p->f,(pgno-1)*p->szPg,0) and skip;
             ofstPushPage_got:=fread(pPage,1,p->szPg,p->f);
             if(ofstPushPage_got!=p->szPg) then 
             {
				sprintf(tmp,"unable to read page %d",pgno) and skip;
                 ofstError(p,tmp,RValue);
                 ofstPopPage(p)
                 
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
  function ofst2byte ( GState *p,int ofst,int RValue )
 {
     frame(ofst2byte_x,return) and ( 
     int return<==0 and skip;
     int ofst2byte_x<==p->aPage[ofst] and skip;
     return<==1 and skip;
	 RValue:=(ofst2byte_x<<8)+p->aPage[ofst+1];
     skip
     )
     }; 
  function ofst4byte ( GState *p,int ofst,int RValue )
 {
     frame(ofst4byte_x,return) and ( 
     int return<==0 and skip;
     int ofst4byte_x<==p->aPage[ofst] and skip;
     ofst4byte_x:=(ofst4byte_x<<8)+p->aPage[ofst+1];
     ofst4byte_x:=(ofst4byte_x<<8)+p->aPage[ofst+2];
     ofst4byte_x:=(ofst4byte_x<<8)+p->aPage[ofst+3];
     return<==1 and skip;
	 RValue:=ofst4byte_x;
     skip
     )
     }; 
  function ofstVarint ( GState *p,int *pOfst,int RValue )
 {
     frame(ofstVarint_x,ofstVarint_a,ofstVarint_n,return) and ( 
     int return<==0 and skip;
     int ofstVarint_x<==0 and skip;
     unsigned char *ofstVarint_a<==&p->aPage[* pOfst] and skip;
     int ofstVarint_n<==0 and skip;
     while(ofstVarint_n<8 AND (ofstVarint_a[0] & 128)!=0)
     {
         ofstVarint_x:=(ofstVarint_x<<7)+(ofstVarint_a[0] & 127);
         ofstVarint_n:=ofstVarint_n+1;
         ofstVarint_a:=ofstVarint_a+1
     };
     if(ofstVarint_n=8) then 
     {
         ofstVarint_x:=(ofstVarint_x<<8)+ofstVarint_a[0]
         
     }
     else
     {
         ofstVarint_x:=(ofstVarint_x<<7)+ofstVarint_a[0]
     };
     * pOfst:=* pOfst+(ofstVarint_n+1);
     return<==1 and skip;
	 RValue:=ofstVarint_x;
     skip
     )
     }; 
  function ofstInFile ( GState *p,int ofst,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and skip;
	 RValue:=p->szPg*(p->pgno-1)+ofst;
     skip
     )
     }; 
  function ofstSerialSize ( int scode,int RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     if(scode<5) then 
     {
         return<==1 and skip;
		 RValue:=scode;
         skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         if(scode=5) then 
         {
             return<==1 and skip;
			 RValue:=6;
             skip
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             if(scode<8) then 
             {
                 return<==1 and skip;
				 RValue:=8;
                 skip
             }
             else 
             {
                  skip 
             };
             if(return=0)   then 
             {
                 if(scode<12) then 
                 {
                     return<==1 and skip;
					 RValue:=0;
                     skip
                 }
                 else 
                 {
                      skip 
                 };
                 if(return=0)   then 
                 {
                     return<==1 and skip;
					 RValue:=(scode-12)/ 2;
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
     }
     else
     {
         skip
     }
     )
     }; 
  function ofstWalkInteriorPage ( GState *p )
 {
     frame(ofstWalkInteriorPage_nCell,ofstWalkInteriorPage_i,ofstWalkInteriorPage_ofst,ofstWalkInteriorPage_iChild,ofstWalkInteriorPage_temp$_1,return) and ( 
     int return<==0 and skip;
     int ofstWalkInteriorPage_nCell and skip;
     int ofstWalkInteriorPage_i and skip;
     int ofstWalkInteriorPage_ofst and skip;
     int ofstWalkInteriorPage_iChild and skip;
     ofstWalkInteriorPage_nCell:=ofst2byte(p,3,RValue);
     ofstWalkInteriorPage_i:=0;
     
     while( return=0 AND  ofstWalkInteriorPage_i<ofstWalkInteriorPage_nCell)
     {
         ofstWalkInteriorPage_ofst:=ofst2byte(p,12+ofstWalkInteriorPage_i*2,RValue);
         ofstWalkInteriorPage_iChild:=ofst4byte(p,ofstWalkInteriorPage_ofst,RValue);
         ofstWalkPage(p,ofstWalkInteriorPage_iChild,RValue);
         if(p->zErr) then 
         {
              return<==1 and skip
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             ofstWalkInteriorPage_i:=ofstWalkInteriorPage_i+1
         }
         else
         {
             skip
         }
         
     };
     if(return=0)   then 
     {
         int ofstWalkInteriorPage_temp$_1 and skip;
         ofstWalkInteriorPage_temp$_1:=ofst4byte(p,8,RValue);
         ofstWalkPage(p,ofstWalkInteriorPage_temp$_1,RValue)
     }
     else
     {
         skip
     }
     )
     }; 
  function ofstWalkLeafPage ( GState *p )
 {
     frame(ofstWalkLeafPage_nCell,ofstWalkLeafPage_i,ofstWalkLeafPage_ofst,ofstWalkLeafPage_nPayload,ofstWalkLeafPage_rowid,ofstWalkLeafPage_nHdr,ofstWalkLeafPage_j,ofstWalkLeafPage_scode,ofstWalkLeafPage_sz,ofstWalkLeafPage_dataOfst,ofstWalkLeafPage_zMsg,ofstWalkLeafPage_temp$_1,continue) and ( 
     int continue<==0 and skip;
     int ofstWalkLeafPage_nCell and skip;
     int ofstWalkLeafPage_i and skip;
     int ofstWalkLeafPage_ofst and skip;
     int ofstWalkLeafPage_nPayload and skip;
     int ofstWalkLeafPage_rowid and skip;
     int ofstWalkLeafPage_nHdr and skip;
     int ofstWalkLeafPage_j and skip;
     int ofstWalkLeafPage_scode and skip;
     int ofstWalkLeafPage_sz and skip;
     int ofstWalkLeafPage_dataOfst and skip;
     char ofstWalkLeafPage_zMsg[200] and skip;
     ofstWalkLeafPage_nCell:=ofst2byte(p,3,RValue);
     continue<==0 and skip;
     ofstWalkLeafPage_i:=0;
     
     while(ofstWalkLeafPage_i<ofstWalkLeafPage_nCell)
     {
          continue<==0 and skip;
         ofstWalkLeafPage_ofst:=ofst2byte(p,8+ofstWalkLeafPage_i*2,RValue);
         ofstWalkLeafPage_nPayload:=ofstVarint(p,&ofstWalkLeafPage_ofst,RValue);
         ofstWalkLeafPage_rowid:=ofstVarint(p,&ofstWalkLeafPage_ofst,RValue);
         if(ofstWalkLeafPage_nPayload>p->szPg-35) then 
         {
             sqlite3_snprintf(200,ofstWalkLeafPage_zMsg,"# overflow rowid %lld",ofstWalkLeafPage_rowid,RValue) and skip;
             output (ofstWalkLeafPage_zMsg,"\n","\n") and skip;
             continue<==1 and skip;
              ofstWalkLeafPage_i:=ofstWalkLeafPage_i+1
             
         }
         else 
         {
              skip 
         };
         if(continue=0)   then 
         {
             ofstWalkLeafPage_dataOfst:=ofstWalkLeafPage_ofst;
             ofstWalkLeafPage_nHdr:=ofstVarint(p,&ofstWalkLeafPage_ofst,RValue);
             ofstWalkLeafPage_dataOfst:=ofstWalkLeafPage_dataOfst+ofstWalkLeafPage_nHdr;
             ofstWalkLeafPage_j:=0;
             
             while(ofstWalkLeafPage_j<p->iCol)
             {
                 ofstWalkLeafPage_scode:=ofstVarint(p,&ofstWalkLeafPage_ofst,RValue);
                 ofstWalkLeafPage_dataOfst:=ofstWalkLeafPage_dataOfst+ofstSerialSize(ofstWalkLeafPage_scode,RValue);
                 ofstWalkLeafPage_j:=ofstWalkLeafPage_j+1
                 
             };
             ofstWalkLeafPage_scode:=ofstVarint(p,&ofstWalkLeafPage_ofst,RValue);
             ofstWalkLeafPage_sz:=ofstSerialSize(ofstWalkLeafPage_scode,RValue);
             int ofstWalkLeafPage_temp$_1 and skip;
             ofstWalkLeafPage_temp$_1:=ofstInFile(p,ofstWalkLeafPage_dataOfst,RValue);
             sqlite3_snprintf(200,ofstWalkLeafPage_zMsg,"rowid %12lld size %5d offset %8d",ofstWalkLeafPage_rowid,ofstWalkLeafPage_sz,ofstWalkLeafPage_temp$_1,RValue) and skip;
             output (ofstWalkLeafPage_zMsg,"\n","\n") and skip;
             ofstWalkLeafPage_i:=ofstWalkLeafPage_i+1
         }
         else
         {
             skip
         }
     };
     continue<==0 and skip
     )
     }; 
  function ofstWalkPage ( GState *p,int pgno )
 {
     frame(return,tmp) and ( 
     int return<==0 and skip;
	 char tmp[100] and skip;
     if(p->zErr) then 
     {
          return<==1 and skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         ofstPushPage(p,pgno);
         if(p->zErr) then 
         {
              return<==1 and skip
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             if(p->aPage[0]=5) then 
             {
                 ofstWalkInteriorPage(p)
                 
             }
             else
             {
                 if(p->aPage[0]=13) then 
                 {
                     ofstWalkLeafPage(p)
                 }
                 else
                 {
					sprintf(tmp,"page %d has a faulty type byte: %d",pgno,p->aPage[0]) and skip;
                     ofstError(p,tmp,RValue)
                 }
             };
             ofstPopPage(p)
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
  function main ( int RValue )
 {
     frame(main_g,return,verifystat) and (
     int return<==0 and skip;
     GState main_g and skip;
     ofstRootAndColumn(&main_g,"offsets.db","test","rootpag");
     if(main_g.zErr) then 
     {
         fprintf(stderr,"%s\n",main_g.zErr) and skip;
         return<==1 and skip
     }
     else 
     {
          skip 
     };
	 int verifystat<==0 and skip;
	 while(verifystat<20494917)
	 {
		verifystat:=verifystat+1
	 };
	 if(return=0) then
	 {
		ofstTrace(&main_g,"# szPg = %d\n",main_g.szPg,RValue) and skip;
		 ofstTrace(&main_g,"# iRoot = %d\n",main_g.iRoot,RValue) and skip;
		 ofstTrace(&main_g,"# iCol = %d\n",main_g.iCol,RValue) and skip;
		 main_g.f:=fopen("offsets.db","rb");
		 if(main_g.f=0) then 
		 {
			 fprintf(stderr,"cannot open \"%s\"\n","offsets.db") and skip;
			return<==1 and skip
		 }
		 else 
		 {
			  skip 
		 };
		 if(return=0) then
		 {
			 ofstWalkPage(&main_g,main_g.iRoot);
			 if(main_g.zErr) then 
			 {
				 fprintf(stderr,"%s\n",main_g.zErr) and skip;	
				 return<==1 and skip
			 }
			 else 
			 {
				  skip 
			 };
			 if(return=0) then
			 {
				return<==1 and skip;
				 RValue:=0;
				 skip
			 }
		 }
	 }
     )
 };
  main(RValue)
