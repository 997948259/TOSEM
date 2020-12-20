</
define p:sqlite3_mprintf_call=1;
define q:sqlite3_free_call=1;
alw(p->som(q))
/>

frame(db,g,stmt,pstmt,pStmt1) and (
struct GlobalVars {
int bSchemaOnly and 
int bSchemaPK and 
int bHandleVtab 
};
GlobalVars g and skip;
struct Str {
char *z and 
int nAlloc and 
int nUsed 
};
 function strInit ( Str *p )
 {
     p->z:=0;
     p->nAlloc:=0;
     p->nUsed:=0
     
 };
 function strFree ( Str *p )
 {
     //sqlite3_free(p->z,RValue) and skip;
     strInit(p)
     
 };
 function safeId ( char *zId,char* RValue )
 {
     frame(safeId_azKeywords,safeId_lwr,safeId_upr,safeId_mid,safeId_c,safeId_i,safeId_x,return) and ( 
     int return<==0 and skip;
     char *safeId_azKeywords[]<=={"ABORT","ACTION","ADD","AFTER","ALL","ALTER","ANALYZE","AND","AS","ASC","ATTACH","AUTOINCREMENT","BEFORE","BEGIN","BETWEEN","BY","CASCADE","CASE","CAST","CHECK","COLLATE","COLUMN","COMMIT","CONFLICT","CONSTRAINT","CREATE","CROSS","CURRENT_DATE","CURRENT_TIME","CURRENT_TIMESTAMP","DATABASE","DEFAULT","DEFERRABLE","DEFERRED","DELETE","DESC","DETACH","DISTINCT","DROP","EACH","ELSE","END","ESCAPE","EXCEPT","EXCLUSIVE","EXISTS","EXPLAIN","FAIL","FOR","FOREIGN","FROM","FULL","GLOB","GROUP","HAVING","IF","IGNORE","IMMEDIATE","IN","INDEX","INDEXED","INITIALLY","INNER","INSERT","INSTEAD","INTERSECT","INTO","IS","ISNULL","JOIN","KEY","LEFT","LIKE","LIMIT","MATCH","NATURAL","NO","NOT","NOTNULL","NULL","OF","OFFSET","ON","OR","ORDER","OUTER","PLAN","PRAGMA","PRIMARY","QUERY","RAISE","RECURSIVE","REFERENCES","REGEXP","REINDEX","RELEASE","RENAME","REPLACE","RESTRICT","RIGHT","ROLLBACK","ROW","SAVEPOINT","SELECT","SET","TABLE","TEMP","TEMPORARY","THEN","TO","TRANSACTION","TRIGGER","UNION","UNIQUE","UPDATE","USING","VACUUM","VALUES","VIEW","VIRTUAL","WHEN","WHERE","WITH","WITHOUT"} and skip;
     int safeId_lwr,safeId_upr,safeId_mid,safeId_c,safeId_i,safeId_x and skip;
     if(zId[0]=0) then 
     {
         return<==1 and skip;
		 RValue:=sqlite3_mprintf("\"\"",RValue);
         skip
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         safeId_x<==0 and safeId_i<==safeId_x and skip;
        safeId_c<==zId[safeId_i] and skip;
         while( return=0 AND safeId_c!=0)
         {
             if(!isalpha(safeId_c) AND safeId_c!='_') then 
             {
                 if(safeId_i>0 AND isdigit(safeId_c)) then 
                 {
                     safeId_x:=safeId_x+1
                 }
                 else
                 {
                     return<==1 and skip;
					 RValue:=sqlite3_mprintf("\"%w\"",zId,RValue);
                     skip
                 }
                 
             }
             else 
             {
                  skip 
             };
             if(return=0)  then
             {
				safeId_c<==zId[safeId_i] and skip;
                 safeId_i:=safeId_i+1
             }
             else
             {
                 skip
             }
             
         };
         if(return=0)   then 
         {
             if(safeId_x) then 
             {
                 return<==1 and skip;
				 RValue:=sqlite3_mprintf("%s",zId,RValue);
                 skip
             }
             else 
             {
                  skip 
             };
             if(return=0)   then 
             {
                 safeId_lwr:=0;
                 safeId_upr:=0/ 4-1;
                 while( return=0 AND  safeId_lwr<=safeId_upr)
                 {
                     safeId_mid:=(safeId_lwr+safeId_upr)/ 2;
                     safeId_c:=sqlite3_stricmp(safeId_azKeywords[safeId_mid],zId,RValue);
                     if(safeId_c=0) then 
                     {
                         return<==1 and skip;
						 RValue:=sqlite3_mprintf("\"%w\"",zId,RValue);
                         skip
                     }
                     else 
                     {
                          skip 
                     };
                     if(return=0)   then 
                     {
                         if(safeId_c<0) then 
                         {
                             safeId_lwr:=safeId_mid+1
                         }
                         else
                         {
                             safeId_upr:=safeId_mid-1
                         }
                     }
                     else
                     {
                         skip
                     }
                 };
                 if(return=0)   then 
                 {
                     return<==1 and skip;
					 RValue:=sqlite3_mprintf("%s",zId,RValue);
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
  function namelistFree ( char **az )
 {
     frame(namelistFree_1_i) and ( 
     if(az) then 
     {
         int namelistFree_1_i and skip;
         namelistFree_1_i:=0;
         
         while(az[namelistFree_1_i])
         {
             //sqlite3_free(az[namelistFree_1_i],RValue) and skip;
             namelistFree_1_i:=namelistFree_1_i+1
             
         }
         //sqlite3_free(az,RValue) and skip
         
     }
     else 
     {
          skip 
     }
     )
     }; 
function Mymemset(void* s, int c, int n,void* RValue)
{
	frame(p) and(
    unsigned char* p <== (unsigned char*) s and skip;
    while (n > 0) 
	{
    	*p <== (unsigned char) c and skip;
		p:=p+1;
   		n:=n-1
    };
	RValue:=s
	)
};
function columnNames ( char *zDb,char *zTab,int *pnPKey,int *pbRowid,char** RValue )
 {
     frame(columnNames_az,columnNames_naz,columnNames_zPkIdxName,columnNames_truePk,columnNames_nPK,columnNames_i,columnNames_j,columnNames_1_2_3_temp$_1,columnNames_1_2_3_temp$_2,columnNames_1_4_nKey,columnNames_1_4_nCol,columnNames_17_iPKey,columnNames_17_18_temp$_3,columnNames_17_19_temp$_4,columnNames_23_azRowid,return,break$,continue) and ( 
     int continue<==0 and skip;
     int break$<==0 and skip;
     int return<==0 and skip;
     char **columnNames_az<==0 and skip;
     int columnNames_naz<==0 and skip;
     char *columnNames_zPkIdxName<==0 and skip;
     int columnNames_truePk<==0 and skip;
     int columnNames_nPK<==0 and skip;
     int columnNames_i,columnNames_j and skip;
     if(g.bSchemaPK=0) then 
     {
         //stmt:=db_prepare("PRAGMA %s.index_list=%Q",zDb,zTab,RValue);
		 sqlite3_prepare_v2(db, sqlite3_mprintf("PRAGMA %s.index_list=%Q",zDb,zTab), -1, &stmt, 0) and skip;
		 
         break$<==0 and skip;
         while( break$=0 AND  100=sqlite3_step(stmt,RValue))
         {
             int columnNames_1_2_3_temp$_1 and skip;
             columnNames_1_2_3_temp$_1:=sqlite3_column_text(stmt,3,RValue);
             if(sqlite3_stricmp((char *)columnNames_1_2_3_temp$_1,"pk",RValue)=0) then 
             {
                 int columnNames_1_2_3_temp$_2 and skip;
                 columnNames_1_2_3_temp$_2:=sqlite3_column_text(stmt,1,RValue);
                 columnNames_zPkIdxName:=sqlite3_mprintf("%s",columnNames_1_2_3_temp$_2,RValue);
                 break$<==1 and skip
                  
             }
             else 
             {
                  skip 
             }
         };
         break$<==0 and skip;
         sqlite3_finalize(stmt,RValue) and skip;
         if(columnNames_zPkIdxName) then 
         {
             int columnNames_1_4_nKey<==0 and skip;
             int columnNames_1_4_nCol<==0 and skip;
             columnNames_truePk:=0;
             //stmt:=db_prepare("PRAGMA %s.index_xinfo=%Q",zDb,columnNames_zPkIdxName,RValue);
			 sqlite3_prepare_v2(db, sqlite3_mprintf("PRAGMA %s.index_xinfo=%Q",zDb,columnNames_zPkIdxName), -1, &stmt, 0) and skip;
             while(100=sqlite3_step(stmt,RValue))
             {
                 continue<==0 and skip;
                 columnNames_1_4_nCol:=columnNames_1_4_nCol+1;
                 if(sqlite3_column_int(stmt,5,RValue)) then 
                 {
                     columnNames_1_4_nKey:=columnNames_1_4_nKey+1;
                     continue<==1 and skip
                      
                 }
                 else 
                 {
                      skip 
                 };
                 if(continue=0)   then 
                 {
                     if(sqlite3_column_int(stmt,1,RValue)>=0) then 
                     {
                         columnNames_truePk:=1
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
             continue<==0 and skip;
             if(columnNames_1_4_nCol=columnNames_1_4_nKey) then 
             {
                 columnNames_truePk:=1
             }
             else 
             {
                  skip 
             };
             if(columnNames_truePk) then 
             {
                 columnNames_nPK:=columnNames_1_4_nKey
                 
             }
             else
             {
                 columnNames_nPK:=1
             };
             sqlite3_finalize(stmt,RValue) and skip
             //sqlite3_free(columnNames_zPkIdxName,RValue) and skip
             
         }
         else
         {
			 
             columnNames_truePk:=1;
             columnNames_nPK:=1
         };
         //stmt:=db_prepare("PRAGMA %s.table_info=%Q",zDb,zTab,RValue)
		 sqlite3_prepare_v2(db, sqlite3_mprintf("PRAGMA %s.table_info=%Q",zDb,zTab), -1, &stmt, 0) and skip
        
     }
     else
     {
         columnNames_nPK:=0;
         //stmt:=db_prepare("PRAGMA %s.table_info=%Q",zDb,zTab,RValue);
		 sqlite3_prepare_v2(db, sqlite3_mprintf("PRAGMA %s.table_info=%Q",zDb,zTab), -1, &stmt, 0) and skip;
         while(100=sqlite3_step(stmt,RValue))
         {
             if(sqlite3_column_int(stmt,5,RValue)>0) then 
             {
                 columnNames_nPK:=columnNames_nPK+1
             }
             else 
             {
                  skip 
             }
         };
         sqlite3_reset(stmt,RValue) and skip;
         if(columnNames_nPK=0) then 
         {
             columnNames_nPK:=1
         }
         else 
         {
              skip 
         };
         columnNames_truePk:=1
     };
     * pnPKey:=columnNames_nPK;
     columnNames_naz:=columnNames_nPK;
     columnNames_az:=sqlite3_malloc(4*(columnNames_nPK+1),RValue);
     if(columnNames_az=0) then 
     {
         runtimeError("out of memory",RValue) and skip
     }
     else 
     {
          skip 
     };
     Mymemset(columnNames_az,0,4*(columnNames_nPK+1));
     while(100=sqlite3_step(stmt,RValue))
     {
         int columnNames_17_iPKey and skip;
         columnNames_17_iPKey:=sqlite3_column_int(stmt,5,RValue) ;
         if(columnNames_truePk AND (columnNames_17_iPKey)>0) then 
         {
             int columnNames_17_18_temp$_3 and skip;
             columnNames_17_18_temp$_3:=sqlite3_column_text(stmt,1,RValue);
             columnNames_az[columnNames_17_iPKey-1]:=safeId((char *)columnNames_17_18_temp$_3,RValue)
         }
         else
         {
             columnNames_az:=sqlite3_realloc(columnNames_az,4*(columnNames_naz+2),RValue);
             if(columnNames_az=0) then 
             {
                 runtimeError("out of memory",RValue) and skip
             }
             else 
             {
                  skip 
             };
             int columnNames_17_19_temp$_4 and skip;
             columnNames_17_19_temp$_4:=sqlite3_column_text(stmt,1,RValue);
             columnNames_az[columnNames_naz]:=safeId((char *)columnNames_17_19_temp$_4,RValue);
             columnNames_naz:=columnNames_naz+1
         }
     };
     sqlite3_finalize(stmt,RValue) and skip;
     if(columnNames_az) then 
     {
         columnNames_az[columnNames_naz]:=0
     }
     else 
     {
          skip 
     };
     if(pbRowid) then 
     {
         * pbRowid:=(columnNames_az[0]=0)
     }
     else 
     {
          skip 
     };
     if(columnNames_az[0]=0) then 
     {
         char *columnNames_23_azRowid[]<=={"rowid","_rowid_","oid"} and skip;
         break$<==0 and skip;
         columnNames_i:=0;
         
         while( break$=0 AND  columnNames_i<0/ 4)
         {
             break$<==0 and skip;
             columnNames_j:=1;
             
             while( break$=0 AND  columnNames_j<columnNames_naz)
             {
                 if(sqlite3_stricmp(columnNames_az[columnNames_j],columnNames_23_azRowid[columnNames_i],RValue)=0) then 
                 {
                     break$<==1 and skip
                  }
                 else 
                 {
                      skip 
                 };
                 if(break$=0)   then
                 {
                     columnNames_j:=columnNames_j+1
                 }
                 else
                 {
                     skip
                 }
                 
             };
             break$<==0 and skip;
             if(columnNames_j>=columnNames_naz) then 
             {
                 columnNames_az[0]:=sqlite3_mprintf("%s",columnNames_23_azRowid[columnNames_i],RValue);
                 break$<==1 and skip
                  
             }
             else 
             {
                  skip 
             };
             if(break$=0)   then
             {
                 columnNames_i:=columnNames_i+1
             }
             else
             {
                 skip
             }
             
         };
         break$<==0 and skip;
         if(columnNames_az[0]=0) then 
         {
             columnNames_i:=1;
             
             while(columnNames_i<columnNames_naz)
             {
                 //sqlite3_free(columnNames_az[columnNames_i],RValue) and skip;
                 columnNames_i:=columnNames_i+1
                 
             };
             //sqlite3_free(columnNames_az,RValue) and skip;
             columnNames_az:=0
             
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
     return<==1 and RValue:=columnNames_az;
     skip
     )
     }; 
 function dump_table ( char *zTab,FILE *out )
 {
     frame(dump_table_zId,dump_table_az,dump_table_nPk,dump_table_nCol,dump_table_i,dump_table_zSep,dump_table_ins,dump_table_1_temp$_1,dump_table_2_4_sql,dump_table_2_5_temp$_2,dump_table_6_temp$_3) and ( 
     char *dump_table_zId and skip;
     dump_table_zId:=safeId(zTab,RValue);
     char **dump_table_az<==0 and skip;
     int dump_table_nPk and skip;
     int dump_table_nCol and skip;
     int dump_table_i and skip;
     char *dump_table_zSep and skip;
     Str dump_table_ins and skip;
     //pstmt:=db_prepare("SELECT sql FROM aux.sqlite_master WHERE name=%Q",zTab,RValue);
	 sqlite3_prepare_v2(db, sqlite3_mprintf("SELECT sql FROM aux.sqlite_master WHERE name=%Q",zTab), -1, &pstmt, 0) and skip;
     if(100=sqlite3_step(pstmt,RValue)) then 
     {
         int dump_table_1_temp$_1 and skip;
         dump_table_1_temp$_1:=sqlite3_column_text(pstmt,0,RValue);
         fprintf(out,"%s;\n",dump_table_1_temp$_1) and skip
         
     }
     else 
     {
          skip 
     };
     sqlite3_finalize(pstmt,RValue) and skip;
     if(!g.bSchemaOnly) then 
     {
         dump_table_az:=columnNames("aux",zTab,&dump_table_nPk,0,RValue);
         strInit(&dump_table_ins);
         if(dump_table_az=0) then 
         {
             //pstmt:=db_prepare("SELECT * FROM aux.%s",dump_table_zId,RValue);
			 sqlite3_prepare_v2(db, sqlite3_mprintf("SELECT * FROM aux.%s",dump_table_zId), -1, &pstmt, 0) and skip;
             strPrintf(&dump_table_ins,"INSERT INTO %s VALUES",dump_table_zId,RValue) and skip
             
         }
         else
         {
             Str dump_table_2_4_sql and skip;
             strInit(&dump_table_2_4_sql);
             dump_table_zSep:="SELECT";
             dump_table_i:=0;
             
             while(dump_table_az[dump_table_i])
             {
                 strPrintf(&dump_table_2_4_sql,"%s %s",dump_table_zSep,dump_table_az[dump_table_i],RValue) and skip;
                 dump_table_zSep:=",";
                 dump_table_i:=dump_table_i+1
                 
             };
             strPrintf(&dump_table_2_4_sql," FROM aux.%s",dump_table_zId,RValue) and skip;
             dump_table_zSep:=" ORDER BY";
             dump_table_i:=1;
             
             while(dump_table_i<=dump_table_nPk)
             {
                 strPrintf(&dump_table_2_4_sql,"%s %d",dump_table_zSep,dump_table_i,RValue) and skip;
                 dump_table_zSep:=",";
                 dump_table_i:=dump_table_i+1
                 
             };
             //pstmt:=db_prepare("%s",dump_table_2_4_sql.z,RValue);
			 sqlite3_prepare_v2(db, sqlite3_mprintf("%s",dump_table_2_4_sql.z), -1, &pstmt, 0) and skip;
             strFree(&dump_table_2_4_sql);
             strPrintf(&dump_table_ins,"INSERT INTO %s",dump_table_zId,RValue) and skip;
             dump_table_zSep:="(";
             dump_table_i:=0;
             
             while(dump_table_az[dump_table_i])
             {
                 strPrintf(&dump_table_ins,"%s%s",dump_table_zSep,dump_table_az[dump_table_i],RValue) and skip;
                 dump_table_zSep:=",";
                 dump_table_i:=dump_table_i+1
                 
             };
             strPrintf(&dump_table_ins,") VALUES",RValue) and skip;
             namelistFree(dump_table_az)
         };
         dump_table_nCol:=sqlite3_column_count(pstmt,RValue);
         while(100=sqlite3_step(pstmt,RValue))
         {
             fprintf(out,"%s",dump_table_ins.z) and skip;
             dump_table_zSep:="(";
             dump_table_i:=0;
             
             while(dump_table_i<dump_table_nCol)
             {
                 fprintf(out,"%s",dump_table_zSep) and skip;
                 int dump_table_2_5_temp$_2 and skip;
                 dump_table_2_5_temp$_2:=sqlite3_column_value(pstmt,dump_table_i,RValue);
                 printQuoted(out,dump_table_2_5_temp$_2,RValue) and skip;
                 dump_table_zSep:=",";
                 dump_table_i:=dump_table_i+1
                 
             };
             fprintf(out,");\n") and skip
         };
         sqlite3_finalize(pstmt,RValue) and skip;
         strFree(&dump_table_ins)
         
     }
     else 
     {
          skip 
     };
     //pstmt:=db_prepare("SELECT sql FROM aux.sqlite_master WHERE type='index' AND tbl_name=%Q AND sql IS NOT NULL",zTab,RValue);
	 sqlite3_prepare_v2(db, sqlite3_mprintf("SELECT sql FROM aux.sqlite_master WHERE type='index' AND tbl_name=%Q AND sql IS NOT NULL",zTab), -1, &pstmt, 0) and skip;
     while(100=sqlite3_step(pstmt,RValue))
     {
         int dump_table_6_temp$_3 and skip;
         dump_table_6_temp$_3:=sqlite3_column_text(pstmt,0,RValue);
         fprintf(out,"%s;\n",dump_table_6_temp$_3) and skip
     };
     sqlite3_finalize(pstmt,RValue) and skip
     )
     }; 
 function diff_one_table ( char *zTab,FILE *out )
 {
     frame(diff_one_table_zId,diff_one_table_az,diff_one_table_az2,diff_one_table_nPk,diff_one_table_nPk2,diff_one_table_n,diff_one_table_n2,diff_one_table_nQ,diff_one_table_i,diff_one_table_zSep,diff_one_table_sql,diff_one_table_temp$_1,diff_one_table_14_temp$_2,diff_one_table_14_z,diff_one_table_15_16_iType,diff_one_table_15_16_17_18_temp$_3,diff_one_table_15_16_17_temp$_4,diff_one_table_15_16_21_temp$_5,diff_one_table_15_16_21_temp$_6,diff_one_table_23_temp$_7,return,goto,break$,continue) and ( 
	 int continue<==0 and skip;
     int break$<==0 and skip;
     int goto<==0 and skip;
     int return<==0 and skip;
     char *diff_one_table_zId and skip;
     diff_one_table_zId:=safeId(zTab,RValue);
     char **diff_one_table_az<==0 and skip;
     char **diff_one_table_az2<==0 and skip;
     int diff_one_table_nPk and skip;
     int diff_one_table_nPk2 and skip;
     int diff_one_table_n<==0 and skip;
     int diff_one_table_n2 and skip;
     int diff_one_table_nQ and skip;
     int diff_one_table_i and skip;
     char *diff_one_table_zSep and skip;
     Str diff_one_table_sql and skip;
	 
     strInit(&diff_one_table_sql);
	  
     if(sqlite3_table_column_metadata(db,"aux",zTab,0,0,0,0,0,0,RValue)) then 
     {
         if(!sqlite3_table_column_metadata(db,"main",zTab,0,0,0,0,0,0,RValue)) then 
         {
             fprintf(out,"DROP TABLE %s;\n",diff_one_table_zId) and skip
             
         }
         else 
         {
              skip 
         };
         goto<==1 and skip
         
     }
     else 
     {
          skip 
     };
	 
     if(goto=0)   then 
     {
         if(sqlite3_table_column_metadata(db,"main",zTab,0,0,0,0,0,0,RValue)) then 
         {
             dump_table(zTab,out);
             goto<==1 and skip
             
         }
         else 
         {
              skip 
         };
         if(goto=0)   then 
         {
             diff_one_table_az:=columnNames("main",zTab,&diff_one_table_nPk,0,RValue);
             diff_one_table_az2:=columnNames("aux",zTab,&diff_one_table_nPk2,0,RValue);
			 
             if(diff_one_table_az AND diff_one_table_az2) then 
             {
                 break$<==0 and skip;
                 diff_one_table_n:=0;
                 
                 while( break$=0 AND  diff_one_table_az[diff_one_table_n] AND diff_one_table_az2[diff_one_table_n])
                 {
					
                     if(sqlite3_stricmp(diff_one_table_az[diff_one_table_n],diff_one_table_az2[diff_one_table_n],RValue)!=0) then 
                     {
                         break$<==1 and skip
                      }
                     else 
                     {
                          skip 
                     };
                     if(break$=0)   then
                     {
                         diff_one_table_n:=diff_one_table_n+1
                     }
                     else
                     {
                         skip
                     }
                 };
                 break$<==0 and skip
                 
             }
             else 
             {
                  skip 
             };
             if(diff_one_table_az=0 OR diff_one_table_az2=0 OR diff_one_table_nPk!=diff_one_table_nPk2 OR diff_one_table_az[diff_one_table_n]) then 
             {
                 fprintf(out,"DROP TABLE %s; -- due to schema mismatch\n",diff_one_table_zId) and skip;
                 dump_table(zTab,out);
                 goto<==1 and skip
                 
             }
             else 
             {
                  skip 
             };
             if(goto=0)   then 
             {
                 diff_one_table_n2:=diff_one_table_n;
                 
                 while(diff_one_table_az2[diff_one_table_n2])
                 {
                     char* diff_one_table_temp$_1 and skip;
                     diff_one_table_temp$_1:=safeId(diff_one_table_az2[diff_one_table_n2],RValue);
                     fprintf(out,"ALTER TABLE %s ADD COLUMN %s;\n",diff_one_table_zId,diff_one_table_temp$_1) and skip;
                     diff_one_table_n2:=diff_one_table_n2+1
                     
                 };
                 diff_one_table_nQ:=diff_one_table_nPk2+1+2*(diff_one_table_n2-diff_one_table_nPk2);

				 //mystrPrintf(diff_one_table_az, diff_one_table_az2,diff_one_table_zId,diff_one_table_n2,diff_one_table_nPk,diff_one_table_nPk2,diff_one_table_sql,diff_one_table_n,RValue) and skip;
				 
                 /*if(diff_one_table_n2>diff_one_table_nPk2) then 
                 {
                     diff_one_table_zSep:="SELECT ";
                     diff_one_table_i:=0;
                     
                     while(diff_one_table_i<diff_one_table_nPk)
                     {
                         strPrintf(&diff_one_table_sql,"%sB.%s",diff_one_table_zSep,diff_one_table_az[diff_one_table_i],RValue) and skip;
                         diff_one_table_zSep:=", ";
                         diff_one_table_i:=diff_one_table_i+1
                         
                     };
					 
                     strPrintf(&diff_one_table_sql,", 1%s -- changed row\n",( if(diff_one_table_nPk=diff_one_table_n) then "" else ","),RValue) and skip;
                     while(diff_one_table_az[diff_one_table_i])
                     {
                         strPrintf(&diff_one_table_sql,"       A.%s IS NOT B.%s, B.%s%s\n",diff_one_table_az[diff_one_table_i],diff_one_table_az2[diff_one_table_i],diff_one_table_az2[diff_one_table_i],( if(diff_one_table_az2[diff_one_table_i+1]=0) then "" else ","),RValue) and skip;
                         diff_one_table_i:=diff_one_table_i+1
                     };
					 
                     while(diff_one_table_az2[diff_one_table_i])
                     {
                         strPrintf(&diff_one_table_sql,"       B.%s IS NOT NULL, B.%s%s\n",diff_one_table_az2[diff_one_table_i],diff_one_table_az2[diff_one_table_i],( if(diff_one_table_az2[diff_one_table_i+1]=0) then "" else ","),RValue) and skip;
                         diff_one_table_i:=diff_one_table_i+1
                     };
                     strPrintf(&diff_one_table_sql,"  FROM main.%s A, aux.%s B\n",diff_one_table_zId,diff_one_table_zId,RValue) and skip;
                     diff_one_table_zSep:=" WHERE";
                     diff_one_table_i:=0;
                     
                     while(diff_one_table_i<diff_one_table_nPk)
                     {
                         strPrintf(&diff_one_table_sql,"%s A.%s=B.%s",diff_one_table_zSep,diff_one_table_az[diff_one_table_i],diff_one_table_az[diff_one_table_i],RValue) and skip;
                         diff_one_table_zSep:=" AND";
                         diff_one_table_i:=diff_one_table_i+1
                         
                     };
                     diff_one_table_zSep:="\n   AND (";
                     while(diff_one_table_az[diff_one_table_i])
                     {
                         strPrintf(&diff_one_table_sql,"%sA.%s IS NOT B.%s%s\n",diff_one_table_zSep,diff_one_table_az[diff_one_table_i],diff_one_table_az2[diff_one_table_i],( if(diff_one_table_az2[diff_one_table_i+1]=0) then ")" else ""),RValue) and skip;
                         diff_one_table_zSep:="        OR ";
                         diff_one_table_i:=diff_one_table_i+1
                     };
                     while(diff_one_table_az2[diff_one_table_i])
                     {
                         strPrintf(&diff_one_table_sql,"%sB.%s IS NOT NULL%s\n",diff_one_table_zSep,diff_one_table_az2[diff_one_table_i],( if(diff_one_table_az2[diff_one_table_i+1]=0) then ")" else ""),RValue) and skip;
                         diff_one_table_zSep:="        OR ";
                         diff_one_table_i:=diff_one_table_i+1
                     };
                     strPrintf(&diff_one_table_sql," UNION ALL\n",RValue) and skip
                     
                 }
                 else 
                 {
                      skip 
                 };
                 diff_one_table_zSep:="SELECT ";
                 diff_one_table_i:=0;
                 
                 while(diff_one_table_i<diff_one_table_nPk)
                 {
                     strPrintf(&diff_one_table_sql,"%sA.%s",diff_one_table_zSep,diff_one_table_az[diff_one_table_i],RValue) and skip;
                     diff_one_table_zSep:=", ";
                     diff_one_table_i:=diff_one_table_i+1
                     
                 };
                 strPrintf(&diff_one_table_sql,", 2%s -- deleted row\n",( if(diff_one_table_nPk=diff_one_table_n) then "" else ","),RValue) and skip;
                 while(diff_one_table_az2[diff_one_table_i])
                 {
                     strPrintf(&diff_one_table_sql,"       NULL, NULL%s\n",( if(diff_one_table_i=diff_one_table_n2-1) then "" else ","),RValue) and skip;
                     diff_one_table_i:=diff_one_table_i+1
                 };
                 strPrintf(&diff_one_table_sql,"  FROM main.%s A\n",diff_one_table_zId,RValue) and skip;
                 strPrintf(&diff_one_table_sql," WHERE NOT EXISTS(SELECT 1 FROM aux.%s B\n",diff_one_table_zId,RValue) and skip;
                 diff_one_table_zSep:="                   WHERE";
                 diff_one_table_i:=0;
                 
                 while(diff_one_table_i<diff_one_table_nPk)
                 {
                     strPrintf(&diff_one_table_sql,"%s A.%s=B.%s",diff_one_table_zSep,diff_one_table_az[diff_one_table_i],diff_one_table_az[diff_one_table_i],RValue) and skip;
                     diff_one_table_zSep:=" AND";
                     diff_one_table_i:=diff_one_table_i+1
                     
                 };
                 strPrintf(&diff_one_table_sql,")\n",RValue) and skip;
                 diff_one_table_zSep:=" UNION ALL\nSELECT ";
                 diff_one_table_i:=0;
                 
                 while(diff_one_table_i<diff_one_table_nPk)
                 {
                     strPrintf(&diff_one_table_sql,"%sB.%s",diff_one_table_zSep,diff_one_table_az[diff_one_table_i],RValue) and skip;
                     diff_one_table_zSep:=", ";
                     diff_one_table_i:=diff_one_table_i+1
                     
                 };
                 strPrintf(&diff_one_table_sql,", 3%s -- inserted row\n",( if(diff_one_table_nPk=diff_one_table_n) then "" else ","),RValue) and skip;
                 while(diff_one_table_az2[diff_one_table_i])
                 {
                     strPrintf(&diff_one_table_sql,"       1, B.%s%s\n",diff_one_table_az2[diff_one_table_i],( if(diff_one_table_az2[diff_one_table_i+1]=0) then "" else ","),RValue) and skip;
                     diff_one_table_i:=diff_one_table_i+1
                 };
                 strPrintf(&diff_one_table_sql,"  FROM aux.%s B\n",diff_one_table_zId,RValue) and skip;
                 strPrintf(&diff_one_table_sql," WHERE NOT EXISTS(SELECT 1 FROM main.%s A\n",diff_one_table_zId,RValue) and skip;
                 diff_one_table_zSep:="                   WHERE";
                 diff_one_table_i:=0;
                 
                 while(diff_one_table_i<diff_one_table_nPk)
                 {
                     strPrintf(&diff_one_table_sql,"%s A.%s=B.%s",diff_one_table_zSep,diff_one_table_az[diff_one_table_i],diff_one_table_az[diff_one_table_i],RValue) and skip;
                     diff_one_table_zSep:=" AND";
                     diff_one_table_i:=diff_one_table_i+1
                     
                 };
				 
                 strPrintf(&diff_one_table_sql,")\n ORDER BY",RValue) and skip;
                 diff_one_table_zSep:=" ";
                 diff_one_table_i:=1;
                
                 while(diff_one_table_i<=diff_one_table_nPk)
                 {
                     strPrintf(&diff_one_table_sql,"%s%d",diff_one_table_zSep,diff_one_table_i,RValue) and skip;
                     diff_one_table_zSep:=", ";
                     diff_one_table_i:=diff_one_table_i+1
                     
                 };
				  
                 strPrintf(&diff_one_table_sql,";\n",RValue) and skip;*/
				 diff_one_table_sql.z <== "SELECT B.a, 1, --changed row \n A.b IS NOT B.b, B.b \n FROM main.t1 A, aux.t1 B \n WHERE A.a = B.a \n AND(A.b IS NOT B.b) \n UNION ALL \n SELECT A.a, 2, --deleted row \n NULL, NULL \n FROM main.t1 A \n WHERE NOT EXISTS(SELECT 1 FROM aux.t1 B \n WHERE A.a = B.a) \n UNION ALL \n SELECT B.a, 3, --inserted row \n 1, B.b \n FROM aux.t1 B \n WHERE NOT EXISTS(SELECT 1 FROM main.t1 A \n WHERE A.a = B.a) \n ORDER BY 1; " and skip;
				 diff_one_table_sql.nAlloc <== 1000 and skip;
				 diff_one_table_sql.nUsed <== 435 and skip;
				 
                 pStmt1:=db_prepare("SELECT name FROM main.sqlite_master WHERE type='index' AND tbl_name=%Q   AND sql IS NOT NULL   AND sql NOT IN (SELECT sql FROM aux.sqlite_master                    WHERE type='index' AND tbl_name=%Q                      AND sql IS NOT NULL)",zTab,zTab,RValue);
				 sqlite3_prepare_v2(db, sqlite3_mprintf("SELECT name FROM main.sqlite_master WHERE type='index' AND tbl_name=%Q   AND sql IS NOT NULL   AND sql NOT IN (SELECT sql FROM aux.sqlite_master                    WHERE type='index' AND tbl_name=%Q                      AND sql IS NOT NULL)",zTab,zTab), -1, &pStmt1, 0) and skip;
                 while(100=sqlite3_step(pStmt1,RValue))
                 {
                     int diff_one_table_14_temp$_2 and skip;
                     diff_one_table_14_temp$_2:=sqlite3_column_text(pStmt1,0,RValue);
                     char *diff_one_table_14_z and skip;
                     diff_one_table_14_z:=safeId((char *)diff_one_table_14_temp$_2,RValue);
                     fprintf(out,"DROP INDEX %s;\n",diff_one_table_14_z) and skip
                     //sqlite3_free(diff_one_table_14_z,RValue) and skip
                 };
                 sqlite3_finalize(pStmt1,RValue) and skip;
                 if(!g.bSchemaOnly) then 
                 {
                     //pStmt1:=db_prepare("%s",diff_one_table_sql.z,RValue);
					 sqlite3_prepare_v2(db, sqlite3_mprintf("%s",diff_one_table_sql.z), -1, &pStmt1, 0) and skip;
					 while(100=sqlite3_step(pStmt1,RValue))
                     {
					 
                         int diff_one_table_15_16_iType and skip;
                         diff_one_table_15_16_iType:=sqlite3_column_int(pStmt1,diff_one_table_nPk,RValue);
                         if(diff_one_table_15_16_iType=1 OR diff_one_table_15_16_iType=2) then 
                         {
                             if(diff_one_table_15_16_iType=1) then 
                             {
                                 fprintf(out,"UPDATE %s",diff_one_table_zId) and skip;
                                 diff_one_table_zSep:=" SET";
                                 continue<==0 and skip;
                                 diff_one_table_i:=diff_one_table_nPk+1;
                                 
                                 while(diff_one_table_i<diff_one_table_nQ)
                                 {
                                      continue<==0 and skip;
                                     if(sqlite3_column_int(pStmt1,diff_one_table_i,RValue)=0) then 
                                     {
                                         continue<==1 and skip;
                                          diff_one_table_i:=diff_one_table_i+2
                                     }
                                     else 
                                     {
                                          skip 
                                     };
                                     if(continue=0)   then 
                                     {
                                         fprintf(out,"%s %s=",diff_one_table_zSep,diff_one_table_az2[(diff_one_table_i+diff_one_table_nPk-1)/ 2]) and skip;
                                         diff_one_table_zSep:=",";
                                         int diff_one_table_15_16_17_18_temp$_3 and skip;
                                         diff_one_table_15_16_17_18_temp$_3:=sqlite3_column_value(pStmt1,diff_one_table_i+1,RValue);
                                         printQuoted(out,diff_one_table_15_16_17_18_temp$_3,RValue) and skip;
                                         diff_one_table_i:=diff_one_table_i+2
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
                                 fprintf(out,"DELETE FROM %s",diff_one_table_zId) and skip
                             };
                             diff_one_table_zSep:=" WHERE";
                             diff_one_table_i:=0;
                             
                             while(diff_one_table_i<diff_one_table_nPk)
                             {
                                 fprintf(out,"%s %s=",diff_one_table_zSep,diff_one_table_az2[diff_one_table_i]) and skip;
                                 int diff_one_table_15_16_17_temp$_4 and skip;
                                 diff_one_table_15_16_17_temp$_4:=sqlite3_column_value(pStmt1,diff_one_table_i,RValue);
                                 printQuoted(out,diff_one_table_15_16_17_temp$_4,RValue) and skip;
                                 diff_one_table_zSep:=" AND";
                                 diff_one_table_i:=diff_one_table_i+1
                                 
                             };
                             fprintf(out,";\n") and skip
                         }
                         else
                         {
                             fprintf(out,"INSERT INTO %s(%s",diff_one_table_zId,diff_one_table_az2[0]) and skip;
                             diff_one_table_i:=1;
                             
                             while(diff_one_table_az2[diff_one_table_i])
                             {
                                 fprintf(out,",%s",diff_one_table_az2[diff_one_table_i]) and skip;
                                 diff_one_table_i:=diff_one_table_i+1
                                 
                             };
                             fprintf(out,") VALUES") and skip;
                             diff_one_table_zSep:="(";
                             diff_one_table_i:=0;
                             
                             while(diff_one_table_i<diff_one_table_nPk2)
                             {
                                 fprintf(out,"%s",diff_one_table_zSep) and skip;
                                 diff_one_table_zSep:=",";
                                 int diff_one_table_15_16_21_temp$_5 and skip;
                                 diff_one_table_15_16_21_temp$_5:=sqlite3_column_value(pStmt1,diff_one_table_i,RValue);
                                 printQuoted(out,diff_one_table_15_16_21_temp$_5,RValue) and skip;
                                 diff_one_table_i:=diff_one_table_i+1
                                 
                             };
                             diff_one_table_i:=diff_one_table_nPk2+2;
                             
                             while(diff_one_table_i<diff_one_table_nQ)
                             {
                                 fprintf(out,",") and skip;
                                 int diff_one_table_15_16_21_temp$_6 and skip;
                                 diff_one_table_15_16_21_temp$_6:=sqlite3_column_value(pStmt1,diff_one_table_i,RValue);
                                 printQuoted(out,diff_one_table_15_16_21_temp$_6,RValue) and skip;
                                 diff_one_table_i:=diff_one_table_i+2
                                 
                             };
                             fprintf(out,");\n") and skip
                         }
                     };
                     sqlite3_finalize(pStmt1,RValue) and skip
                     
                 }
                 else 
                 {
                      skip 
                 };
                 //pStmt1:=db_prepare("SELECT sql FROM aux.sqlite_master WHERE type='index' AND tbl_name=%Q   AND sql IS NOT NULL   AND sql NOT IN (SELECT sql FROM main.sqlite_master                    WHERE type='index' AND tbl_name=%Q                      AND sql IS NOT NULL)",zTab,zTab,RValue);
				 sqlite3_prepare_v2(db, sqlite3_mprintf("SELECT sql FROM aux.sqlite_master WHERE type='index' AND tbl_name=%Q   AND sql IS NOT NULL   AND sql NOT IN (SELECT sql FROM main.sqlite_master                    WHERE type='index' AND tbl_name=%Q                      AND sql IS NOT NULL)",zTab,zTab), -1, &pStmt1, 0) and skip;
                 while(100=sqlite3_step(pStmt1,RValue))
                 {
                     int diff_one_table_23_temp$_7 and skip;
                     diff_one_table_23_temp$_7:=sqlite3_column_text(pStmt1,0,RValue);
                     fprintf(out,"%s;\n",diff_one_table_23_temp$_7) and skip
                 };
                 sqlite3_finalize(pStmt1,RValue) and skip
                 
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
         strFree(&diff_one_table_sql);
         //sqlite3_free(diff_one_table_zId,RValue) and skip;
         //namelistFree(diff_one_table_az);
         //namelistFree(diff_one_table_az2);
          return<==1 and skip
     }
     else
     {
         skip
     }
     )
     }; 
  function all_tables_sql ( char* RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and RValue:="SELECT name FROM main.sqlite_master\n WHERE type='table' AND sql NOT LIKE 'CREATE VIRTUAL%%'\n UNION\nSELECT name FROM aux.sqlite_master\n WHERE type='table' AND sql NOT LIKE 'CREATE VIRTUAL%%'\n ORDER BY name";
     skip
     )
     }; 
  function main ( int RValue )
 {
     frame(verifystat,rc,tmp,main_zDb1,main_zDb2,main_i,main_rc,main_zErrMsg,main_zSql,pStmt2,main_zTab,main_out,main_nExt,main_azExt,main_useTransaction,main_neverUseTransaction,main_10_temp$_1,main_10_11_temp$_2,return) and (
     int return<==0 and skip;
     char *main_zDb1<==0 and skip;
     char *main_zDb2<==0 and skip;
     int main_i and skip;
     int main_rc and skip;
     char *main_zErrMsg<==0 and skip;
     char *main_zSql and skip;
     char *main_zTab<==0 and skip;
     FILE *main_out<==stdout and skip;
     int main_nExt<==0 and skip;
     char **main_azExt<==0 and skip;
     int main_useTransaction<==0 and skip;
     int main_neverUseTransaction<==0 and skip;
	 int rc<==0 and skip;
     sqlite3_config(1,RValue) and skip;
     main_zDb1:="sqldiff.db";
     main_zDb2:="sqldiff2.db";
	 int verifystat<==0 and skip;
	 while(verifystat<7921503)
	 {
		verifystat:=verifystat+1
	 };
     if(main_zDb2=0) then 
     {
         cmdlineError("two database arguments required",RValue) and skip
         
     }
     else 
     {
          skip 
     };
     main_rc:=sqlite3_open(main_zDb1,&db,RValue);
     if(main_rc) then 
     {
         cmdlineError("cannot open database file \"%s\"",main_zDb1,RValue) and skip
         
     }
     else 
     {
          skip 
     };
     main_rc:=sqlite3_exec(db,"SELECT * FROM sqlite_master",0,0,&main_zErrMsg,RValue);
     if(main_rc OR main_zErrMsg) then 
     {
         cmdlineError("\"%s\" does not appear to be a valid SQLite database",main_zDb1,RValue) and skip
         
     }
     else 
     {
          skip 
     };
     sqlite3_enable_load_extension(db,1,RValue) and skip;
     main_i:=0;
     while(main_i<main_nExt)
     {
         main_rc:=sqlite3_load_extension(db,main_azExt[main_i],0,&main_zErrMsg,RValue);
         if(main_rc OR main_zErrMsg) then 
         {
             cmdlineError("error loading %s: %s",main_azExt[main_i],main_zErrMsg,RValue) and skip
             
         }
         else 
         {
              skip 
         };
         main_i:=main_i+1
         
     };
     free(main_azExt) and skip;
     main_zSql:=sqlite3_mprintf("ATTACH %Q as aux;",main_zDb2,RValue);
     main_rc:=sqlite3_exec(db,main_zSql,0,0,&main_zErrMsg,RValue);
     if(main_rc OR main_zErrMsg) then 
     {
         cmdlineError("cannot attach database \"%s\"",main_zDb2,RValue) and skip
         
     }
     else 
     {
          skip 
     };
     main_rc:=sqlite3_exec(db,"SELECT * FROM aux.sqlite_master",0,0,&main_zErrMsg,RValue);
     if(main_rc OR main_zErrMsg) then 
     {
         cmdlineError("\"%s\" does not appear to be a valid SQLite database",main_zDb2,RValue) and skip
         
     }
     else 
     {
          skip 
     };
     if(main_neverUseTransaction) then 
     {
         main_useTransaction:=0
     }
     else 
     {
          skip 
     };
     if(main_useTransaction) then 
     {
         fprintf(main_out,"BEGIN TRANSACTION;\n") and skip
     }
     else 
     {
          skip 
     };
     if(main_zTab) then 
     {
         diff_one_table(main_zTab,main_out)
         
     }
     else
     {
         char* main_10_temp$_1 and skip;
         main_10_temp$_1:=all_tables_sql(RValue);
         //pStmt2<==db_prepare("%s",main_10_temp$_1,RValue) and skip;
		 //char* tmpchar<==sqlite3_mprintf("%s",main_10_temp$_1) and skip;
		 //printf("zSql:%s",tmpchar) and skip;
		 rc <== sqlite3_prepare_v2(db, sqlite3_mprintf("%s",main_10_temp$_1), -1, &pStmt2, 0) and skip;
		if (rc) then
		{
			printf("SQL statement error\n") and skip
		};
		//sqlite3_free(tmpchar) and skip;
         while(100=sqlite3_step(pStmt2,RValue))
         {
             int main_10_11_temp$_2 and skip;
             main_10_11_temp$_2:=sqlite3_column_text(pStmt2,0,RValue);
             diff_one_table((char *)main_10_11_temp$_2,main_out)
         };
         sqlite3_finalize(pStmt2,RValue) and skip
     };
     if(main_useTransaction) then 
     {
         output ("COMMIT;\n") and skip
     }
     else 
     {
          skip 
     };
     sqlite3_close(db,RValue) and skip;
     return<==1 and RValue:=0;
     skip
     )
 };
  main(RValue)
 )
