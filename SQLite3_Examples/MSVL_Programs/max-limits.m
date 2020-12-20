</
define p:sqlite3_open_call=1;
define q:sqlite3_close_call=1;
alw(p->som(q))
/>

frame(aLimit) and (
struct struct$0 {
int eCode and 
char *zName 
};
struct$0 aLimit[12]<=={{0,"SQLITE_MAX_LENGTH"},{1,"SQLITE_MAX_SQL_LENGTH"},{2,"SQLITE_MAX_COLUMN"},{3,"SQLITE_MAX_EXPR_DEPTH"},{4,"SQLITE_MAX_COMPOUND_SELECT"},{5,"SQLITE_MAX_VDBE_OP"},{6,"SQLITE_MAX_FUNCTION_ARG"},{7,"SQLITE_MAX_ATTACHED"},{8,"SQLITE_MAX_LIKE_PATTERN_LENGTH"},{9,"SQLITE_MAX_VARIABLE_NUMBER"},{10,"SQLITE_MAX_TRIGGER_DEPTH"},{11,"SQLITE_MAX_WORKER_THREADS"}} and skip;
 function maxLimit ( struct sqlite3 *db,int eCode,int RValue )
 {
     frame(maxLimit_iOrig,return) and ( 
     int return<==0 and skip;
     int maxLimit_iOrig and skip;
     maxLimit_iOrig:=sqlite3_limit(db,eCode,0x7fffffff,RValue);
     return<==1 and RValue:=sqlite3_limit(db,eCode,maxLimit_iOrig,RValue);
     skip
     )
     }; 
  function main ( int RValue )
 {
     frame(db,main_j,main_rc,verifystat) and (
     int main_j,main_rc and skip;
     main_rc:=sqlite3_open(":memory:",&db,RValue);
	 int verifystat<==0 and skip;
	 while(verifystat<9069051)
	 {
		verifystat:=verifystat+1
	 };
     if(main_rc=0) then 
     {
         main_j:=0;
         
         while(main_j<sizeof((aLimit))/ sizeof((aLimit[0])))
         {
             output (aLimit[main_j].zName," ",maxLimit(db,aLimit[main_j].eCode,RValue),"\n","\n") and skip;
             main_j:=main_j+1
             
         };
         sqlite3_close(db,RValue) and skip
         
     }
     else 
     {
          skip 
     }
     )
 };
  main(RValue)
 )
