</
define p:sqlite3_column_text_call=1;
define q:sqlite3_column_bytes_call=1;
alw(q->p)
/>

frame(g,pStmt1) and (
struct SHA1Context {
unsigned int state[5] and 
unsigned int count[2] and 
unsigned char buffer[64] 
};
struct GlobalVars {
char *zArgv0 and 
int fDebug and 
SHA1Context cx 
};
GlobalVars g and skip;
 function hash_init (  )
 {
     g.cx.state[0]:=0x67452301;
     g.cx.state[1]:=0xEFCDAB89;
     g.cx.state[2]:=0x98BADCFE;
     g.cx.state[3]:=0x10325476;
     g.cx.state[4]:=0xC3D2E1F0;
     g.cx.count[1]<==0 and g.cx.count[0]<==g.cx.count[1] and skip
     
 };
 function hash_step ( unsigned char *data,unsigned int len$ )
 {
     frame(hash_step_i,hash_step_j,tmp) and ( 
     unsigned int hash_step_i,hash_step_j and skip;
     hash_step_j:=g.cx.count[0];
	 unsigned int tmp<==len$<<3 and skip;
	 g.cx.count[0]:=g.cx.count[0]+tmp;
     if(g.cx.count[0]<hash_step_j) then 
     {
		
         g.cx.count[1]:=g.cx.count[1]+(len$>>29)+1
         
     }
     else 
     {
          skip 
     };
     hash_step_j:=(hash_step_j>>3) & 63;
     if((hash_step_j+len$)>63) then 
     {
         hash_step_i:=64-hash_step_j ;
         memcpy(&g.cx.buffer[hash_step_j],data,(hash_step_i)) and skip;
         SHA1Transform(g.cx.state,g.cx.buffer,RValue) and skip;
         while(hash_step_i+63<len$)
         {
             SHA1Transform(g.cx.state,&data[hash_step_i],RValue) and skip;
             hash_step_i:=hash_step_i+64
             
         };
         hash_step_j:=0
         
     }
     else
     {
         hash_step_i:=0
     };
     memcpy(&g.cx.buffer[hash_step_j],&data[hash_step_i],len$-hash_step_i) 
     )
     }; 
  function hash_finish ( char *zName )
 {
     frame(hash_finish_i,hash_finish_finalcount,hash_finish_digest,hash_finish_zEncode,hash_finish_zOut,tmp_i) and ( 
     int hash_finish_i and skip;
     unsigned char hash_finish_finalcount[8] and skip;
     unsigned char hash_finish_digest[20] and skip;
     char hash_finish_zEncode[17]<=="0123456789abcdef" and skip;
     char hash_finish_zOut[41] and skip;
     hash_finish_i:=0;
	 int tmp_i<==0 and skip;
     
     while(hash_finish_i<8)
     {
		if(hash_finish_i>=4) then
		{
			tmp_i<==0 and skip
		}
		else
		{
			tmp_i<==1 and skip
		};
         hash_finish_finalcount[hash_finish_i]:=(unsigned char)((g.cx.count[tmp_i]>>((3-(hash_finish_i & 3))*8)) & 255);
         hash_finish_i:=hash_finish_i+1
         
     };
     hash_step((unsigned char *)"\200",1);
	 
     while((g.cx.count[0] & 504)!=448)
     {
         hash_step((unsigned char *)"\0",1)
     };
     hash_step(hash_finish_finalcount,8);
     hash_finish_i:=0;
     while(hash_finish_i<20)
     {
	 tmp_i<==hash_finish_i>>2 and skip;
         hash_finish_digest[hash_finish_i]:=(unsigned char)((g.cx.state[tmp_i]>>((3-(hash_finish_i & 3))*8)) & 255);
         hash_finish_i:=hash_finish_i+1
         
     };
     hash_finish_i:=0;
     while(hash_finish_i<20)
     {
	 tmp_i<==(hash_finish_digest[hash_finish_i]>>4) & 15 and skip;
         hash_finish_zOut[hash_finish_i*2]:=hash_finish_zEncode[tmp_i];
		 tmp_i<==hash_finish_digest[hash_finish_i] & 15 and skip;
         hash_finish_zOut[hash_finish_i*2+1]:=hash_finish_zEncode[tmp_i];
         hash_finish_i:=hash_finish_i+1
         
     };
     hash_finish_zOut[hash_finish_i*2]:=0;
     output (hash_finish_zOut," ") and skip;
	 printf("%s\n",zName) and skip
     )
     }; 
 function my_hash_one_query ()
 {
     frame(my_hash_one_query_nCol,my_hash_one_query_i,nm_1$,switch$,my_hash_one_query_1_2_u,my_hash_one_query_1_2_j,my_hash_one_query_1_2_x,my_hash_one_query_1_2_v,my_hash_one_query_1_2_4_temp$_1,my_hash_one_query_1_2_r,my_hash_one_query_1_2_5_temp$_2,my_hash_one_query_1_2_n,my_hash_one_query_1_2_6_temp$_3,my_hash_one_query_1_2_z,return,break$) and ( 
     int break$<==0 and skip;
     int return<==0 and skip;
     int my_hash_one_query_nCol and skip;
     int my_hash_one_query_i and skip;
	 int my_hash_one_query_1_2_u and skip;
     int my_hash_one_query_1_2_j and skip;
	 int my_hash_one_query_1_2_n and skip;
	 unsigned char my_hash_one_query_1_2_x[8] and skip;
	 unsigned char *my_hash_one_query_1_2_z and skip;
     my_hash_one_query_nCol:=sqlite3_column_count(pStmt1,RValue);
     while(100=sqlite3_step(pStmt1,RValue))
     {
         my_hash_one_query_i:=0;
         
         while(my_hash_one_query_i<my_hash_one_query_nCol)
         {
             int switch$ and skip;
             break$<==0 and skip;
              switch$<==0 and skip;
              int nm_1$ and skip;
             nm_1$ := sqlite3_column_type(pStmt1,my_hash_one_query_i,RValue);
             if (nm_1$=5 OR (switch$=1 AND break$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 hash_step((unsigned char *)"0",1);
                 if(g.fDebug & 0x00000001) then 
                 {
                     fprintf(stderr,"NULL\n") and skip
                 }
                 else 
                 {
                      skip 
                 };
                 break$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             if (nm_1$=1 OR (switch$=1 AND break$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 
                 
                 int my_hash_one_query_1_2_v and skip;
                 my_hash_one_query_1_2_v:=sqlite3_column_int64(pStmt1,my_hash_one_query_i,RValue);
                 memcpy(&my_hash_one_query_1_2_u,&my_hash_one_query_1_2_v,8) and skip;
                 my_hash_one_query_1_2_j:=7;
                 
                 while(my_hash_one_query_1_2_j>=0)
                 {
                     my_hash_one_query_1_2_x[my_hash_one_query_1_2_j]:=my_hash_one_query_1_2_u & 255;
                     my_hash_one_query_1_2_u:=my_hash_one_query_1_2_u>> (8 );
                     my_hash_one_query_1_2_j:=my_hash_one_query_1_2_j-1
                     
                 };
                 hash_step((unsigned char *)"1",1);
                 hash_step(my_hash_one_query_1_2_x,8);
                 if(g.fDebug & 0x00000001) then 
                 {
                     int my_hash_one_query_1_2_4_temp$_1 and skip;
                     my_hash_one_query_1_2_4_temp$_1:=sqlite3_column_text(pStmt1,my_hash_one_query_i,RValue);
                     fprintf(stderr,"INT %s\n",my_hash_one_query_1_2_4_temp$_1) and skip
                     
                 }
                 else 
                 {
                      skip 
                 };
                 break$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             if (nm_1$=2 OR (switch$=1 AND break$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 float my_hash_one_query_1_2_r and skip;
                 my_hash_one_query_1_2_r:=sqlite3_column_double(pStmt1,my_hash_one_query_i,RValue);
                 memcpy(&my_hash_one_query_1_2_u,&my_hash_one_query_1_2_r,8) and skip;
                 my_hash_one_query_1_2_j:=7;
                 
                 while(my_hash_one_query_1_2_j>=0)
                 {
                     my_hash_one_query_1_2_x[my_hash_one_query_1_2_j]:=my_hash_one_query_1_2_u & 255;
                     my_hash_one_query_1_2_u:=my_hash_one_query_1_2_u>> (8 );
                     my_hash_one_query_1_2_j:=my_hash_one_query_1_2_j-1
                     
                 };
                 hash_step((unsigned char *)"2",1);
                 hash_step(my_hash_one_query_1_2_x,8);
                 if(g.fDebug & 0x00000001) then 
                 {
                     int my_hash_one_query_1_2_5_temp$_2 and skip;
                     my_hash_one_query_1_2_5_temp$_2:=sqlite3_column_text(pStmt1,my_hash_one_query_i,RValue);
                     fprintf(stderr,"FLOAT %s\n",my_hash_one_query_1_2_5_temp$_2) and skip
                     
                 }
                 else 
                 {
                      skip 
                 };
                 break$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             if (nm_1$=3 OR (switch$=1 AND break$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 my_hash_one_query_1_2_n:=sqlite3_column_bytes(pStmt1,my_hash_one_query_i,RValue);
				 skip;
                 my_hash_one_query_1_2_z:=sqlite3_column_text(pStmt1,my_hash_one_query_i,RValue);
                 hash_step((unsigned char *)"3",1);
                 hash_step(my_hash_one_query_1_2_z,my_hash_one_query_1_2_n);
                 if(g.fDebug & 0x00000001) then 
                 {
                     int my_hash_one_query_1_2_6_temp$_3 and skip;
                     my_hash_one_query_1_2_6_temp$_3:=sqlite3_column_text(pStmt1,my_hash_one_query_i,RValue);
                     fprintf(stderr,"TEXT '%s'\n",my_hash_one_query_1_2_6_temp$_3) and skip
                     
                 }
                 else 
                 {
                      skip 
                 };
                 break$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             if (nm_1$=4 OR (switch$=1 AND break$=0 AND return=0) ) then 
             {
                 switch$<==1 and skip;
                 my_hash_one_query_1_2_n:=sqlite3_column_bytes(pStmt1,my_hash_one_query_i,RValue);
                 my_hash_one_query_1_2_z:=sqlite3_column_blob(pStmt1,my_hash_one_query_i,RValue);
                 hash_step((unsigned char *)"4",1);
                 hash_step(my_hash_one_query_1_2_z,my_hash_one_query_1_2_n);
                 if(g.fDebug & 0x00000001) then 
                 {
                     fprintf(stderr,"BLOB (%d bytes)\n",my_hash_one_query_1_2_n) and skip
                     
                 }
                 else 
                 {
                      skip 
                 };
                 break$<==1 and skip
                  
             }
             else
             {
                 skip
             };
             my_hash_one_query_i:=my_hash_one_query_i+1
             
         }
     };
     sqlite3_finalize(pStmt1,RValue)
     )
     }; 
  function showHelp (  )
 {
     output ("Usage: ",g.zArgv0," [options] FILE ...\n") and skip;
     output ("Compute a SHA1 hash on the content of database FILE.  System tables such as\nsqlite_stat1, sqlite_stat4, and sqlite_sequence are omitted from the hash.\nOptions:\n   --debug N           Set debugging flags to N (experts only)\n   --like PATTERN      Only hash tables whose name is LIKE the pattern\n   --schema-only       Only hash the schema - omit table content\n   --without-schema    Only hash table content - omit the schema\n") and skip
     
 };
 function main ( int RValue )
 {
     frame(verifystat,tmp,db,main_zDb,main_i,main_rc,main_zErrMsg,pStmt2,main_zLike,main_omitSchema,main_omitContent,main_nFile,main_openFlags,main_3_4_temp$_1,return) and (
     int return<==0 and skip;
     char *main_zDb<==0 and skip;
     int main_i and skip;
     int main_rc and skip;
     char *main_zErrMsg and skip;
     char *main_zLike<=="%" and skip;
     int main_omitSchema<=="%" and skip;
     int main_omitContent<==0 and skip;
     int main_nFile<==0 and skip;
	 //main_zLike <== "%" and skip;
     sqlite3_config(1,RValue) and skip;
	 int tmp<==0 and skip;
     main_omitSchema:=1;
     int main_openFlags<==0x00000002 | 0x00000040 and skip;
     main_zDb:="dbhash.db";
	 int verifystat<==0 and skip;
	 while(verifystat<7000194)
	 {
		verifystat:=verifystat+1
	 };
     main_rc:=sqlite3_open_v2(main_zDb,&db,main_openFlags,0,RValue);
     if(main_rc) then 
     {
         fprintf(stderr,"cannot open database file '%s'\n",main_zDb) and skip
         
     }
     else 
     {
          skip 
     };
     main_rc:=sqlite3_exec(db,"SELECT * FROM sqlite_master",0,0,&main_zErrMsg,RValue);
     if(main_rc OR main_zErrMsg) then 
     {
         sqlite3_close(db,RValue) and skip;
         db:=0;
         fprintf(stderr,"'%s' is not a valid SQLite database\n",main_zDb) and skip
         
     }
     else 
     {
          skip 
     };
     hash_init();
     if(!main_omitContent) then 
     {
		 my_db_prepare(main_zLike) and skip;
         while(100=sqlite3_step(pStmt2,RValue))
         {
             int main_3_4_temp$_1 and skip;
             //main_3_4_temp$_1:=sqlite3_column_text(pStmt2,0,RValue);
             //hash_one_query("SELECT * FROM \"%w\"",main_3_4_temp$_1,RValue) and skip;
			 my_hash_one_query1() and skip;
			 my_hash_one_query()
         };
         sqlite3_finalize(pStmt2,RValue)
         
     }
     else 
     {
          skip 
     };
     if(!main_omitSchema) then 
     {
         //hash_one_query("SELECT type, name, tbl_name, sql FROM sqlite_master\n WHERE tbl_name LIKE '%q'\n ORDER BY name COLLATE nocase;\n",main_zLike,RValue) and skip;
         my_hash_one_query2(main_zLike) and skip;
		 my_hash_one_query()
     }
     else 
     {
          skip 
     };
     hash_finish(main_zDb);
     sqlite3_close(db,RValue) and skip;
     return<==1 and skip;
	 RValue:=0;
     skip
     )
 };
  main(RValue)
 )
