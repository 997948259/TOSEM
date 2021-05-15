/*</
define p:state_num<=powcondition_n*condition_n;
alw(p)
/>*/
/*</
define p:state_num>0;
som(p)
/>*/
/*</
define p:state_num>0;
define q:success=1;
alw(p->som(q))
/>*/

</
define p1:module_1=1;
define p2:module_2=1;
define p3:module_3=1;
define p4:module_4=1;
som(p1;(p2;p3)#;p4)
/>

frame(module_1,module_2,module_3,module_4,condition_n,powcondition_n,state_flag,state_num,ALWAYS,AND_1,EQUIV,EVENTUALLY,FALSE,IMPLIES,NOT,OR_1,PREDICATE,TRUE,U_OPER,V_OPER,tl_stats,tl_simp_log,tl_simp_diff,tl_simp_fly,tl_simp_scc,tl_fjtofj,tl_errs,tl_verbose,tl_terse,All_Mem,uform,hasuform,cnt,ltl_file,add_ltl,out1,label,sym_table,transition,final_set,node_id,sym_id,node_size,sym_size,astate_count,atrans_count,bstack,bstates,bremoved,scc_stack,accept,bstate_count,btrans_count,stored,Caches,CacheHits,gstack,gremoved,gstates,init,init_size,gstate_id,gstate_count,gtrans_count,fin$,final,rank,scc_id,scc_size,bad_scc,symtab,yytext,atrans_list,gtrans_list,btrans_list,aallocs,afrees,apool,gallocs,gfrees,gpool,ballocs,bfrees,bpool,freelist,req,event,tl_yychar,tl_yylval,prec,can,mod,Stack_mx,Max_Red,Total,dumpbuf,Bscc_stack,success,hasAuto,hasSipAtran,hasSipAuto,count_state,count_trans,count_before_state,count_before_trans,flag) and (
//hasAuto表示是否按算法转自动机
//hasSipAtran表示是否在转换时化简
//hasSipAuto表示是否化简自动机
 union __anonunion___value_2 {
 int __wch and 
 char __wchb[4] 
 };
 struct __anonstruct__mbstate_t_1 {
 int __count and 
 union __anonunion___value_2* __value 
 };
 struct _Bigint {
 struct _Bigint* _next and 
 int _k and 
 int _maxwds and 
 int _sign and 
 int _wds and 
 int _x[1] 
 };
 struct __tm {
 int __tm_sec and 
 int __tm_min and 
 int __tm_hour and 
 int __tm_mday and 
 int __tm_mon and 
 int __tm_year and 
 int __tm_wday and 
 int __tm_yday and 
 int __tm_isdst 
 };
 struct _on_exit_args {
 void *_fnargs[32] and 
 void *_dso_handle[32] and 
 int _fntypes and 
 int _is_cxa 
 };
 struct _atexit {
 struct _atexit* _next and 
 int _ind and 
 struct _on_exit_args* _on_exit_args$ 
 };
 struct __sbuf {
 unsigned char *_base and 
 int _size 
 };
 struct __sFILE64 {
 unsigned char *_p and 
 int _r and 
 int _w and 
 int _flags and 
 int _file and 
 struct __sbuf* _bf and 
 int _lbfsize and 
 struct _reent* _data and 
 void *_cookie and 
 struct __sbuf* _ub and 
 unsigned char *_up and 
 int _ur and 
 unsigned char _ubuf[3] and 
 unsigned char _nbuf[1] and 
 struct __sbuf* _lb and 
 int _blksize and 
 int _flags2 and 
 int _offset and 
 void* _lock 
 };
 struct _glue {
 struct _glue* _next and 
 int _niobs and 
 __sFILE64 *_iobs 
 };
 struct _rand48 {
 int _seed[3] and 
 int _mult[3] and 
 int _add 
 };
 struct __anonstruct__reent_4 {
 int _unused_rand and 
 char *_strtok_last and 
 char _asctime_buf[26] and 
 struct __tm* _localtime_buf and 
 int _gamma_signgam and 
 int _rand_next and 
 struct _rand48* _r48 and 
 __anonstruct__mbstate_t_1 _mblen_state and 
 __anonstruct__mbstate_t_1 _mbtowc_state and 
 __anonstruct__mbstate_t_1 _wctomb_state and 
 char _l64a_buf[8] and 
 char _signal_buf[24] and 
 int _getdate_err and 
 __anonstruct__mbstate_t_1 _mbrlen_state and 
 __anonstruct__mbstate_t_1 _mbrtowc_state and 
 __anonstruct__mbstate_t_1 _mbsrtowcs_state and 
 __anonstruct__mbstate_t_1 _wcrtomb_state and 
 __anonstruct__mbstate_t_1 _wcsrtombs_state 
 };
 struct __anonstruct__unused_5 {
 unsigned char *_nextf[30] and 
 int _nmalloc[30] 
 };
 union __anonunion__new_3 {
 struct __anonstruct__reent_4* _reent$ and 
 struct __anonstruct__unused_5* _unused 
 };
 struct _reent {
 int _errno and 
 __sFILE64 *_stdin and 
 __sFILE64 *_stdout and 
 __sFILE64 *_stderr and 
 int _inc and 
 char _emergency[25] and 
 int _current_category and 
 char *_current_locale and 
 int __sdidinit and 
 struct _Bigint* _result and 
 int _result_k and 
 struct _Bigint* _p5s and 
 struct _Bigint* _freelist and 
 int _cvtlen and 
 char *_cvtbuf and 
 union __anonunion__new_3* _new and 
 struct _atexit*  _atexit$ and 
 struct _atexit* _atexit0 and 
 struct _glue* __sglue and 
 __sFILE64 __sf[3] 
 };
 struct timeval {
 int tv_sec and 
 int tv_usec 
 };
 struct rusage {
 struct timeval* ru_utime and 
 struct timeval* ru_stime and 
 int ru_maxrss and 
 int ru_ixrss and 
 int ru_idrss and 
 int ru_isrss and 
 int ru_minflt and 
 int ru_majflt and 
 int ru_nswap and 
 int ru_inblock and 
 int ru_oublock and 
 int ru_msgsnd and 
 int ru_msgrcv and 
 int ru_nsignals and 
 int ru_nvcsw and 
 int ru_nivcsw 
 };
 struct Symbol {
 char *name and 
 struct Symbol* next$ 
 };
 struct Node {
 int ntyp and 
 struct Symbol* sym and 
 struct Node* lft and 
 struct Node* rgt and 
 struct Node* nxt 
 };
 struct Graph {
 Symbol *name and 
 Symbol *incoming and 
 Symbol *outgoing and 
 Symbol *oldstring and 
 Symbol *nxtstring and 
 Node *New and 
 Node *Old and 
 Node *Other and 
 Node *Next and 
 unsigned char isred[64],isgrn[64] and 
 unsigned char redcnt,grncnt and 
 unsigned char reachable and 
 struct Graph* nxt 
 };
 struct Mapping {
 char *from and 
 Graph *to and 
 struct Mapping* nxt 
 };
 struct ATrans {
 int *to and 
 int *pos and 
 int *neg and 
 struct ATrans* nxt 
 };
 struct AProd {
 int astate and 
 struct ATrans* prod and 
 struct ATrans* trans and 
 struct AProd* nxt and 
 struct AProd* prv 
 };
 struct GTrans {
 int *pos and 
 int *neg and 
 struct GState* to and 
 int *final and 
 struct GTrans* nxt 
 };
 struct GState {
 int id and 
 int incoming and 
 int *nodes_set and 
 struct GTrans* trans and 
 struct GState* nxt and 
 struct GState* prv 
 };
 struct BTrans {
 struct BState* to and 
 int *pos and 
 int *neg and 
 struct BTrans* nxt 
 };
 struct BState {
 struct GState* gstate and 
 int id and 
 int incoming and 
 int final and 
 struct BTrans* trans and 
 struct BState* nxt and 
 struct BState* prv 
 };
 struct GScc {
 struct GState* gstate and 
 int rank and 
 int theta and 
 struct GScc* nxt 
 };
 struct BScc {
 struct BState* bstate and 
 int rank and 
 int theta and 
 struct BScc* nxt 
 };
 int module_1<==1 and skip;
 int module_2<==0 and skip;
 int module_3<==0 and skip;
 int module_4<==0 and skip;
  int ALWAYS<==257 and int AND_1<==258 and  int EQUIV<==259 and  int EVENTUALLY<==260 and  int FALSE<==261 and  int IMPLIES<==262 and  int NOT<==263 and  int OR_1<==264 and  int PREDICATE<==265 and  int TRUE<==266 and  int U_OPER<==267 and  int V_OPER<==268 and  skip;
  int count_state<==0 and skip;
  int count_trans<==0 and skip;
  int state_flag<==1 and skip;
  int state_num<==0 and skip;
  int count_before_state<==0 and skip;
  int count_before_trans<==0 and skip;
  int flag<==0 and skip;
  int condition_n<==0 and skip;
  int powcondition_n<==0 and skip;
  int success<==0 and skip;
 int tl_stats<==1 and skip;
 int tl_simp_log<==1 and skip;
 int tl_simp_diff<==1 and skip;
 int tl_simp_fly<==1 and skip;
 int tl_simp_scc<==1 and skip;
 int tl_fjtofj<==1 and skip;
 int tl_errs<==0 and skip;
 int tl_verbose<==1 and skip;
 int tl_terse<==0 and skip;
 int All_Mem<==0 and skip;
 char uform[4096] and skip;

 int hasAuto<==0 and skip;
 while(hasAuto<5000000)
 {
	hasAuto:=hasAuto+1
 };
 hasAuto<==0 and skip;
 int hasSipAtran<==0 and skip;
 int hasSipAuto<==0 and skip;
 int hasuform<==0,cnt<==0 and skip;
 char **ltl_file<==NULL and skip;
 char **add_ltl<==NULL and skip;
 char out1[64] and skip;
 Node **label and skip;
 char **sym_table and skip;
 ATrans **transition and skip;
 int *final_set,node_id<==1,sym_id<==0,node_size,sym_size and skip;
 int astate_count<==0,atrans_count<==0 and skip;
 BState *bstack,*bstates,*bremoved and skip;
 BScc *Bscc_stack and skip;
 int accept,bstate_count<==0,btrans_count<==0 and skip;
 struct Cache {
 Node *before and 
 Node *after and 
 int same and 
 struct Cache* nxt 
 };
 Cache *stored<==NULL and skip;
 int Caches<==0,CacheHits<==0 and skip;
 GState *gstack,*gremoved,*gstates,**init and skip;
 GScc *scc_stack and skip;
 int init_size<==0,gstate_id<==1,gstate_count<==0,gtrans_count<==0 and skip;
 int *fin$<==NULL and skip;
 int *final<==NULL and skip;
 int rank,scc_id,scc_size and skip;
 int *bad_scc<==NULL and skip;
 Symbol *symtab[255+1] and skip;
 char yytext[2048] and skip;
 ATrans *atrans_list<==NULL and skip;
 GTrans *gtrans_list<==NULL and skip;
 BTrans *btrans_list<==NULL and skip;
 int aallocs<==0,afrees<==0,apool<==0 and skip;
 int gallocs<==0,gfrees<==0,gpool<==0 and skip;
 int ballocs<==0,bfrees<==0,bpool<==0 and skip;
 union M {
 int size and 
 union M* link 
 };
 M *freelist[80] and skip;
 int req[80] and skip;
 int event[3,80] and skip;
 int tl_yychar<==0 and skip;
 Node* tl_yylval and skip;
 int prec[2,4]<=={{U_OPER,V_OPER,0,0},{OR_1,AND_1,IMPLIES,EQUIV}} and skip;
 Node *can<==NULL and skip;
 int mod<==8*4 and skip;
 int Stack_mx<==0,Max_Red<==0,Total<==0 and skip;
 char dumpbuf[2048] and skip;
 function alldone ( int estatus )
 {
     if(strlen(out1)>0) then 
     {
       //  unlink((char *)out1) and skip
	   skip
     }
     else 
     {
          skip 
     }
     
 };
 function emalloc ( int n,char* RValue )
 {
     frame(emalloc_tmp,return_1) and ( 
     int return_1<==0 and skip;
     char *emalloc_tmp and skip;
     emalloc_tmp<==(char *)malloc(n) and skip;
     if(!(emalloc_tmp)) then 
     {
         fatal("not enough memory",NULL)
     }
     else 
     {
          skip 
     };
     memset(emalloc_tmp,0,n) and skip;
     return_1<==1 and RValue:=emalloc_tmp;
     skip
     )
     }; 
  function tl_Getchar ( int RValue )
 {
     frame(return_1) and ( 
     int return_1<==0 and skip;
     if(cnt<hasuform) then 
     {
         return_1<==1 and RValue:=uform[cnt];
         cnt:=cnt+1;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         cnt:=cnt+1;
         return_1<==1 and RValue:=-1;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function put_uform (  )
 {
     output (uform) and skip
     
 };
 function tl_UnGetchar (  )
 {
     if(cnt>0) then 
     {
         cnt:=cnt-1
     }
     else 
     {
          skip 
     }
     
 };
 function usage (  )
 {
     output ("usage: ltl2ba [-flag] -f formula\n") and skip;
     output ("                   or -F file\n") and skip;
     output (" -f \"formula\"\ttranslate LTL ") and skip;
     output ("into never claim\n") and skip;
     output (" -F file\tlike -f, but with the LTL ") and skip;
     output ("formula stored in a 1-line file\n") and skip;
     output (" -d\t\tdisplay automata (D)escription at each step\n") and skip;
     output (" -s\t\tcomputing time and automata sizes (S)tatistics\n") and skip;
     output (" -l\t\tdisable (L)ogic formula simplification\n") and skip;
     output (" -p\t\tdisable a-(P)osteriori simplification\n") and skip;
     output (" -o\t\tdisable (O)n-the-fly simplification\n") and skip;
     output (" -c\t\tdisable strongly (C)onnected components simplification\n") and skip;
     output (" -a\t\tdisable trick in (A)ccepting conditions\n") and skip;
     alldone(1)
     
 };
 function tl_main_1 ( int RValue )
 {
     frame(tl_main_1_i,return_1) and ( 
	 module_2<==1 and skip;
     int return_1<==0 and skip;
     int tl_main_1_i and skip;
	 //"!(([]<>p1&&[]<>p2)->[](q-><>r))" 第一个
	 //"!([]<>p->[](q-><>r))"第二个
	 //"([]<>p1||<>[]p2)&&([]<>p2||<>[]p3)"第三个       && []<>p2 && []<>p3 && []<>p4 && []<>p5&& []<>p4 && []<>p5 && []<>p6 && []<>p7
	//output("please input n fairness condition:") and skip;
	//input(condition_n) and skip;
	//output("please input formula:") and skip;
	//input(uform) and skip;
	condition_n:=1;
	powcondition_n:=2;
	uform:="p";
	// uform:="!(([]<>p && []<>p1 && []<>p2 && []<>p3 && []<>p4)->[](q-><>r))" and skip;
     hasuform<==strlen(uform) and skip;
     if(hasuform=0) then 
     {
         usage()
     }
     else 
     {
          skip 
     };
     tl_parse();
     if(tl_stats) then 
     {
         tl_endstats()
     }
     else 
     {
          skip 
     };
     return_1<==1 and RValue:=tl_errs;
     skip
     )
     }; 
  function main_1 ( int RValue )
 {
     frame(main_1_i,main_1_1_formula,return_1) and ( 
     int return_1<==0 and skip;
     int main_1_i and skip;
     if(ltl_file) then 
     {
         char main_1_1_formula[4096] and skip;
         add_ltl:=ltl_file-2;
         add_ltl[1,1]:='f';
         * ltl_file:=(char *)main_1_1_formula
         
     }
     else 
     {
          skip 
     };
     tl_main_1(RValue);
     return_1<==1 and RValue:=0;
     skip
     );
	 success:=1
     }; 
  function tl_endstats (  )
 {
     output ("\ntotal memory used: ",All_Mem,"\n") and skip;
     a_stats()
     
 };
 function dump ( Node *n )
 {
     frame(nm_1$,break_1$,switch_1,return_1) and ( 
     int return_1<==0 and skip;
     if(!n) then 
     {
          return_1<==1 and skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         int switch_1 and skip;
         int break_1$ and skip;
         break_1$<==0 and skip;
          switch_1<==0 and skip;
          int nm_1$ and skip;
         nm_1$ := n->ntyp;
         if (nm_1$=OR_1 OR (switch_1=1 AND  break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             output ("(") and skip;
             dump(n->lft);
             output (" || ") and skip;
             dump(n->rgt);
             output (")") and skip;
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_1$=AND_1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             output ("(") and skip;
             dump(n->lft);
             output (" && ") and skip;
             dump(n->rgt);
             output (")") and skip;
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_1$=U_OPER OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             output ("(") and skip;
             dump(n->lft);
             output (" U ") and skip;
             dump(n->rgt);
             output (")") and skip;
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_1$=V_OPER OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             output ("(") and skip;
             dump(n->lft);
             output (" V ") and skip;
             dump(n->rgt);
             output (")") and skip;
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_1$=NOT OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             output ("!") and skip;
             output (" (") and skip;
             dump(n->lft);
             output (")") and skip;
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_1$=FALSE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             output ("false") and skip;
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_1$=TRUE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             output ("true") and skip;
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_1$=PREDICATE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             output ("(",n->sym->name,")") and skip;
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_1$=-1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             output (" D ") and skip;
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if(break_1$=0 AND return_1=0) then 
         {
             output ("Unknown token: ") and skip;
             tl_explain(n->ntyp);
             break_1$<==1 and skip
              
         }
         else
         {
              skip
             }}
             else
             {
                 skip
             }
             )
             }; 
  function tl_explain ( int n )///yixie
 {
     frame(nm_2$,break_1$,switch_1,return_1) and ( 
     int return_1<==0 and skip;
     int switch_1 and skip;
     int break_1$ and skip;
     break_1$<==0 and skip;
      switch_1<==0 and skip;
      int nm_2$ and skip;
     nm_2$ := n;
     if (nm_2$=ALWAYS OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         output ("[]") and skip;
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_2$=EVENTUALLY OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         output ("<>") and skip;
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_2$=IMPLIES OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         output ("->") and skip;
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_2$=EQUIV OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         output ("<->") and skip;
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_2$=PREDICATE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         output ("predicate") and skip;
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_2$=OR_1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         output ("||") and skip;
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_2$=AND_1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         output ("&&") and skip;
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_2$=NOT OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         output ("!") and skip;
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_2$=U_OPER OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         output ("U") and skip;
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_2$=V_OPER OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         output ("V") and skip;
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_2$=TRUE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         output ("true") and skip;
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_2$=FALSE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         output ("false") and skip;
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_2$=';' OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         output ("end of formula") and skip;
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if(break_1$=0 AND return_1=0) then 
     {
         output (n) and skip;
         break_1$<==1 and skip
          
     }
     else
     {
          skip
         })
         }; 
  function non_fatal ( char *s1,char *s2 )///yixie
 {
     frame(non_fatal_i) and ( 
     int non_fatal_i and skip;
     output ("ltl2ba: ") and skip;
     if(s2) then 
     {
         output (s1,s2) and skip 
     }
     else
     {
         output (s1) and skip 
     };
     if(tl_yychar!=-1 AND tl_yychar!=0) then 
     {
         output (", saw '") and skip;
         tl_explain(tl_yychar);
         output ("'") and skip
         
     }
     else 
     {
          skip 
     };
     output ("\nltl2ba: ",uform,"\n---------") and skip;
     non_fatal_i:=0;
     
     while(non_fatal_i<cnt)
     {
         output ("-") and skip;
         non_fatal_i:=non_fatal_i+1
         
     };
     output ("^\n") and skip;
     tl_errs:=tl_errs+1
     )
     }; 
  function tl_yyerror ( char *s1 )///yixie
 {
     Fatal(s1,NULL)
     
 };
 function Fatal ( char *s1,char *s2 )///yixie
 {
     non_fatal(s1,s2);
     alldone(1)
     
 };
 function fatal ( char *s1,char *s2 )///yixie
 {
     non_fatal(s1,s2);
     alldone(1)
     
 };
 function calculate_node_size ( Node *p,int RValue )
 {
     frame(nm_3$,break_1$,switch_1,return_1) and ( 
     int return_1<==0 and skip;
     int switch_1 and skip;
     int break_1$ and skip;
     break_1$<==0 and skip;
      switch_1<==0 and skip;
      int nm_3$ and skip;
     nm_3$ := p->ntyp;
     if (nm_3$=AND_1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip
         
     }
     else
     {
         skip
     };
     if (nm_3$=OR_1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip
         
     }
     else
     {
         skip
     };
     if (nm_3$=U_OPER OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip
         
     }
     else
     {
         skip
     };
     if (nm_3$=V_OPER OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         return_1<==1 and RValue:=((extern calculate_node_size(p->lft,RValue))+(extern calculate_node_size(p->rgt,RValue))+1);
         skip
         
     }
     else
     {
         skip
     };
     if(break_1$=0 AND return_1=0) then 
     {
         return_1<==1 and RValue:=1;
         skip;
         break_1$<==1 and skip
          
     }
     else
     {
          skip
         })
         }; 
  function calculate_sym_size ( Node *p,int RValue )
 {
     frame(nm_4$,break_1$,switch_1,return_1) and ( 
     int return_1<==0 and skip;
     int switch_1 and skip;
     int break_1$ and skip;
     break_1$<==0 and skip;
      switch_1<==0 and skip;
      int nm_4$ and skip;
     nm_4$ := p->ntyp;
     if (nm_4$=AND_1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip
         
     }
     else
     {
         skip
     };
     if (nm_4$=OR_1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip
         
     }
     else
     {
         skip
     };
     if (nm_4$=U_OPER OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip
         
     }
     else
     {
         skip
     };
     if (nm_4$=V_OPER OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         return_1<==1 and RValue:=((extern calculate_sym_size(p->lft,RValue))+(extern calculate_sym_size(p->rgt,RValue)));
         skip
         
     }
     else
     {
         skip
     };
     if (nm_4$=NOT OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip
         
     }
     else
     {
         skip
     };
     if (nm_4$=PREDICATE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         return_1<==1 and RValue:=1;
         skip
         
     }
     else
     {
         skip
     };
     if(break_1$=0 AND return_1=0) then 
     {
         return_1<==1 and RValue:=0;
         skip
         
     }
     else
     {
          skip
         })
         }; 
  function dup_trans ( ATrans *trans,ATrans* RValue )
 {
     frame(dup_trans_result,return_1) and ( 
     int return_1<==0 and skip;
     ATrans *dup_trans_result and skip;
     if(!trans) then 
     {
         return_1<==1 and RValue:=trans;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         dup_trans_result:=emalloc_atrans(RValue);
         copy_set(trans->to,dup_trans_result->to,0);
         copy_set(trans->pos,dup_trans_result->pos,1);
         copy_set(trans->neg,dup_trans_result->neg,1);
         return_1<==1 and RValue:=dup_trans_result;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function do_merge_trans ( ATrans **result,ATrans *trans1,ATrans *trans2 )
 {
     frame(return_1) and ( 
     int return_1<==0 and skip;
     if(!trans1 OR !trans2) then 
     {
         free_atrans(* result,0);
         * result:=NULL;
          return_1<==1 and skip
         
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         if(!* result) then 
         {
             * result:=emalloc_atrans(RValue)
         }
         else 
         {
              skip 
         };
         do_merge_sets((* result)->to,trans1->to,trans2->to,0);
         do_merge_sets((* result)->pos,trans1->pos,trans2->pos,1);
         do_merge_sets((* result)->neg,trans1->neg,trans2->neg,1);
         if(!(extern empty_intersect_sets((* result)->pos,(* result)->neg,1,RValue))) then 
         {
             free_atrans(* result,0);
             * result:=NULL
             
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
  function merge_trans ( ATrans *trans1,ATrans *trans2,ATrans* RValue )
 {
     frame(merge_trans_result,return_1) and ( 
     int return_1<==0 and skip;
     ATrans *merge_trans_result and skip;
     merge_trans_result:=emalloc_atrans(RValue);
     do_merge_trans(&merge_trans_result,trans1,trans2);
     return_1<==1 and RValue:=merge_trans_result;
     skip
     )
     }; 
  function already_done ( Node *p,int RValue )
 {
     frame(already_done_i,return_1) and ( 
     int return_1<==0 and skip;
     int already_done_i and skip;
     already_done_i:=1;
     
     while( return_1=0 AND  already_done_i<node_id)
     {
         if(extern isequal(p,label[already_done_i],RValue)) then 
         {
             return_1<==1 and RValue:=already_done_i;
             skip
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             already_done_i:=already_done_i+1
         }
         else
         {
             skip
         }
         
     };
     if(return_1=0)   then 
     {
         return_1<==1 and RValue:=-1;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function get_sym_id ( char *s,int RValue )
 {
     frame(get_sym_id_i,return_1) and ( 
     int return_1<==0 and skip;
     int get_sym_id_i and skip;
     get_sym_id_i:=0;
     
     while( return_1=0 AND  get_sym_id_i<sym_id)
     {
         if(!strcmp(s,sym_table[get_sym_id_i])) then 
         {
             return_1<==1 and RValue:=get_sym_id_i;
             skip
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             get_sym_id_i:=get_sym_id_i+1
         }
         else
         {
             skip
         }
         
     };
     if(return_1=0)   then 
     {
         sym_table[sym_id]:=s;
         return_1<==1 and RValue:=sym_id;
         sym_id:=sym_id+1;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function boolean ( Node *p,ATrans* RValue )
 {
     frame(boolean_t1,boolean_t2,boolean_lft,boolean_rgt,boolean_result,boolean_id,nm_5$,break_1$,switch_1,boolean_1_tmp,boolean_1_tmp_1,boolean_1_tmp_2,boolean_1_temp$_1,return_1) and ( 
     int return_1<==0 and skip;
     ATrans *boolean_t1,*boolean_t2,*boolean_lft,*boolean_rgt,*boolean_result<==NULL and skip;
     int boolean_id and skip;
     int switch_1 and skip;
     int break_1$ and skip;
     break_1$<==0 and skip;
      switch_1<==0 and skip;
      int nm_5$ and skip;
     nm_5$ := p->ntyp;
     if (nm_5$=TRUE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         boolean_result:=emalloc_atrans(RValue);
         clear_set(boolean_result->to,0,RValue);
         clear_set(boolean_result->pos,1,RValue);
         clear_set(boolean_result->neg,1,RValue)
         
     }
     else
     {
         skip
     };
     if (nm_5$=FALSE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_5$=AND_1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         boolean_lft:=boolean(p->lft,RValue);
         boolean_rgt:=boolean(p->rgt,RValue);
         boolean_t1:=boolean_lft;
         
         while(boolean_t1)
         {
             boolean_t2:=boolean_rgt;
             
             while(boolean_t2)
             {
                 ATrans *boolean_1_tmp and skip;
                 boolean_1_tmp:=merge_trans(boolean_t1,boolean_t2,RValue);
                 if(boolean_1_tmp) then 
                 {
                     boolean_1_tmp->nxt:=boolean_result;
                     boolean_result:=boolean_1_tmp
                     
                 }
                 else 
                 {
                      skip 
                 };
                 boolean_t2:=boolean_t2->nxt
                 
             };
             boolean_t1:=boolean_t1->nxt
             
         };
         free_atrans(boolean_lft,1);
         free_atrans(boolean_rgt,1);
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_5$=OR_1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         boolean_lft:=boolean(p->lft,RValue);
         boolean_t1:=boolean_lft;
         
         while(boolean_t1)
         {
             ATrans *boolean_1_tmp_1 and skip;
             boolean_1_tmp_1:=dup_trans(boolean_t1,RValue);
             boolean_1_tmp_1->nxt:=boolean_result;
             boolean_result:=boolean_1_tmp_1;
             boolean_t1:=boolean_t1->nxt
             
         };
         free_atrans(boolean_lft,1);
         boolean_rgt:=boolean(p->rgt,RValue);
         boolean_t1:=boolean_rgt;
         
         while(boolean_t1)
         {
             ATrans *boolean_1_tmp_2 and skip;
             boolean_1_tmp_2:=dup_trans(boolean_t1,RValue);
             boolean_1_tmp_2->nxt:=boolean_result;
             boolean_result:=boolean_1_tmp_2;
             boolean_t1:=boolean_t1->nxt
             
         };
         free_atrans(boolean_rgt,1);
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if(break_1$=0 AND return_1=0) then 
     {
         build_alternating(p,RValue);
         boolean_result:=emalloc_atrans(RValue);
         clear_set(boolean_result->to,0,RValue);
         clear_set(boolean_result->pos,1,RValue);
         clear_set(boolean_result->neg,1,RValue);
         int boolean_1_temp$_1 and skip;
         boolean_1_temp$_1:=already_done(p,RValue);
         add_set(boolean_result->to,boolean_1_temp$_1)
         
     }
     else
     {
          skip
     };
     return_1<==1 and RValue:=boolean_result;
     skip
     )
     }; 
  function build_alternating ( Node *p,ATrans* RValue )
 {
     frame(build_alternating_t1,build_alternating_t2,build_alternating_t,build_alternating_node,nm_6$,break_1$,switch_1,build_alternating_2_temp$_1,build_alternating_2_temp$_2,build_alternating_2_tmp,build_alternating_2_tmp_2,build_alternating_2_tmp_3,build_alternating_2_tmp_4,build_alternating_2_tmp_5,build_alternating_2_tmp_6,return_1) and (
	 hasAuto<==1 and skip;
     int return_1<==0 and skip;
     ATrans *build_alternating_t1,*build_alternating_t2,*build_alternating_t<==NULL and skip;
     int build_alternating_node and skip;
     build_alternating_node:=already_done(p,RValue);
     if(build_alternating_node>=0) then 
     {
         return_1<==1 and RValue:=transition[build_alternating_node]
     }
     else 
     {
		  skip
     };
     if(return_1=0)   then 
     {
         int switch_1 and skip;
         int break_1$ and skip;
         break_1$<==0 and skip;
          switch_1<==0 and skip;
          int nm_6$ and skip;
         nm_6$ := p->ntyp;
         if (nm_6$=TRUE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             build_alternating_t:=emalloc_atrans(RValue);
             clear_set(build_alternating_t->to,0,RValue);
             clear_set(build_alternating_t->pos,1,RValue);
             clear_set(build_alternating_t->neg,1,RValue)
             
         }
         else
         {
             skip
         };
         if (nm_6$=FALSE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_6$=PREDICATE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             build_alternating_t:=emalloc_atrans(RValue);
             clear_set(build_alternating_t->to,0,RValue);
             clear_set(build_alternating_t->pos,1,RValue);
             clear_set(build_alternating_t->neg,1,RValue);
             int build_alternating_2_temp$_1 and skip;
             build_alternating_2_temp$_1:=get_sym_id(p->sym->name,RValue);
             add_set(build_alternating_t->pos,build_alternating_2_temp$_1);
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_6$=NOT OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             build_alternating_t:=emalloc_atrans(RValue);
             clear_set(build_alternating_t->to,0,RValue);
             clear_set(build_alternating_t->pos,1,RValue);
             clear_set(build_alternating_t->neg,1,RValue);
             int build_alternating_2_temp$_2 and skip;
             build_alternating_2_temp$_2:=get_sym_id(p->lft->sym->name,RValue);
             add_set(build_alternating_t->neg,build_alternating_2_temp$_2);
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_6$=U_OPER OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             build_alternating_t2:=build_alternating(p->rgt,RValue);
             
             while(build_alternating_t2)
             {
                 ATrans *build_alternating_2_tmp and skip;
                 build_alternating_2_tmp:=dup_trans(build_alternating_t2,RValue);
                 build_alternating_2_tmp->nxt:=build_alternating_t;
                 build_alternating_t:=build_alternating_2_tmp;
                 build_alternating_t2:=build_alternating_t2->nxt
                 
             };
             build_alternating_t1:=build_alternating(p->lft,RValue);
             
             while(build_alternating_t1)
             {
                 ATrans *build_alternating_2_tmp_2 and skip;
                 build_alternating_2_tmp_2:=dup_trans(build_alternating_t1,RValue);
                 add_set(build_alternating_2_tmp_2->to,node_id);
                 build_alternating_2_tmp_2->nxt:=build_alternating_t;
                 build_alternating_t:=build_alternating_2_tmp_2;
                 build_alternating_t1:=build_alternating_t1->nxt
                 
             };
             add_set(final_set,node_id);
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_6$=V_OPER OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             build_alternating_t1:=build_alternating(p->rgt,RValue);
             
             while(build_alternating_t1)
             {
                 ATrans *build_alternating_2_tmp_3 and skip;
                 build_alternating_t2:=build_alternating(p->lft,RValue);
                 
                 while(build_alternating_t2)
                 {
                     build_alternating_2_tmp_3:=merge_trans(build_alternating_t1,build_alternating_t2,RValue);
                     if(build_alternating_2_tmp_3) then 
                     {
                         build_alternating_2_tmp_3->nxt:=build_alternating_t;
                         build_alternating_t:=build_alternating_2_tmp_3
                         
                     }
                     else 
                     {
                          skip 
                     };
                     build_alternating_t2:=build_alternating_t2->nxt
                     
                 };
                 build_alternating_2_tmp_3:=dup_trans(build_alternating_t1,RValue);
                 add_set(build_alternating_2_tmp_3->to,node_id);
                 build_alternating_2_tmp_3->nxt:=build_alternating_t;
                 build_alternating_t:=build_alternating_2_tmp_3;
                 build_alternating_t1:=build_alternating_t1->nxt
                 
             };
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_6$=AND_1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             build_alternating_t:=NULL;
             build_alternating_t1:=build_alternating(p->lft,RValue);
             
             while(build_alternating_t1)
             {
                 build_alternating_t2:=build_alternating(p->rgt,RValue);
                 
                 while(build_alternating_t2)
                 {
                     ATrans *build_alternating_2_tmp_4 and skip;
                     build_alternating_2_tmp_4:=merge_trans(build_alternating_t1,build_alternating_t2,RValue);
                     if(build_alternating_2_tmp_4) then 
                     {
                         build_alternating_2_tmp_4->nxt:=build_alternating_t;
                         build_alternating_t:=build_alternating_2_tmp_4
                         
                     }
                     else 
                     {
                          skip 
                     };
                     build_alternating_t2:=build_alternating_t2->nxt
                     
                 };
                 build_alternating_t1:=build_alternating_t1->nxt
                 
             };
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_6$=OR_1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             build_alternating_t:=NULL;
             build_alternating_t1:=build_alternating(p->lft,RValue);
             
             while(build_alternating_t1)
             {
                 ATrans *build_alternating_2_tmp_5 and skip;
                 build_alternating_2_tmp_5:=dup_trans(build_alternating_t1,RValue);
                 build_alternating_2_tmp_5->nxt:=build_alternating_t;
                 build_alternating_t:=build_alternating_2_tmp_5;
                 build_alternating_t1:=build_alternating_t1->nxt
                 
             };
             build_alternating_t1:=build_alternating(p->rgt,RValue);
             
             while(build_alternating_t1)
             {
                 ATrans *build_alternating_2_tmp_6 and skip;
                 build_alternating_2_tmp_6:=dup_trans(build_alternating_t1,RValue);
                 build_alternating_2_tmp_6->nxt:=build_alternating_t;
                 build_alternating_t:=build_alternating_2_tmp_6;
                 build_alternating_t1:=build_alternating_t1->nxt
                 
             };
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if(break_1$=0 AND return_1=0) then 
         {
             break_1$<==1 and skip
              
         }
         else
         {
              skip
         };
         transition[node_id]:=build_alternating_t;
         label[node_id]:=p;
         node_id:=node_id+1;
         return_1<==1 and RValue:=build_alternating_t;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function simplify_atrans ( ATrans **mytrans )
 {
     frame(simplify_atrans_t,simplify_atrans_father,simplify_atrans_t1,break_1,continue_1) and (
     hasSipAtran<==0 and skip; 
     int continue_1<==0 and skip;
     int break_1<==0 and skip;
     ATrans *simplify_atrans_t,*simplify_atrans_father<==NULL and skip;
     continue_1<==0 and skip;
     simplify_atrans_t:=* mytrans;
     while(simplify_atrans_t)
     {
          continue_1<==0 and skip;
         ATrans *simplify_atrans_t1 and skip;
         break_1<==0 and skip;
         simplify_atrans_t1:=* mytrans;
         while( break_1=0 AND  simplify_atrans_t1)
         {
             if((simplify_atrans_t1!=simplify_atrans_t) AND (extern included_set(simplify_atrans_t1->to,simplify_atrans_t->to,0,RValue)) AND (extern included_set(simplify_atrans_t1->pos,simplify_atrans_t->pos,1,RValue)) AND (extern included_set(simplify_atrans_t1->neg,simplify_atrans_t->neg,1,RValue))) then 
             {
			 
                 break_1<==1 and skip
              }
             else 
             {
                  skip 
             };
			
             if(break_1=0)   then
             {
                 simplify_atrans_t1:=simplify_atrans_t1->nxt;
                 hasSipAtran<==1 and skip
             }
             else
             {
                 skip
             }
             
         };
         break_1<==0 and skip;
         if(simplify_atrans_t1) then 
         {
             if(simplify_atrans_father) then 
             {
                 simplify_atrans_father->nxt:=simplify_atrans_t->nxt
             }
             else
             {
                 * mytrans:=simplify_atrans_t->nxt
             };
             free_atrans(simplify_atrans_t,0);
             if(simplify_atrans_father) then 
             {
                 simplify_atrans_t:=simplify_atrans_father->nxt
             }
             else
             {
                 simplify_atrans_t:=* mytrans
             };
             continue_1<==1 and skip;
             hasSipAtran<==1 and skip
         }
         else 
         {
              skip 
         };
         if(continue_1=0)   then 
         {
             atrans_count:=atrans_count+1;
             simplify_atrans_father:=simplify_atrans_t;
             simplify_atrans_t:=simplify_atrans_t->nxt
         }
         else
         {
             skip
         }
     };
     continue_1<==0 and skip
     )
     }; 
  function simplify_astates (  )
 {
     frame(simplify_astates_t,simplify_astates_i,simplify_astates_acc,continue_1) and ( 
     int continue_1<==0 and skip;
     hasSipAuto<==0 and skip;
     ATrans *simplify_astates_t and skip;
     int simplify_astates_i,*simplify_astates_acc and skip;
     simplify_astates_acc:=make_set(-1,0,RValue);
     simplify_astates_t:=transition[0];
     while(simplify_astates_t)
     {
         merge_sets(simplify_astates_acc,simplify_astates_t->to,0);
         simplify_astates_t:=simplify_astates_t->nxt and simplify_astates_i:=0   
     };
     continue_1<==0 and skip;
     simplify_astates_i:=node_id-1;
     while(simplify_astates_i>0)
     {
          continue_1<==0 and skip;
         if(!(extern in_set(simplify_astates_acc,simplify_astates_i,RValue))) then 
         {
             label[simplify_astates_i]:=NULL;
             free_atrans(transition[simplify_astates_i],1);
             transition[simplify_astates_i]:=NULL;
             continue_1<==1 and skip;
             hasSipAuto<==1 and skip;
              simplify_astates_i:=simplify_astates_i-1
         }
         else 
         {
              skip 
         };
         if(continue_1=0)   then 
         {
             astate_count:=astate_count+1;
             simplify_atrans(&transition[simplify_astates_i]);
             simplify_astates_t:=transition[simplify_astates_i];
             
             while(simplify_astates_t)
             {
                 merge_sets(simplify_astates_acc,simplify_astates_t->to,0);
                 simplify_astates_t:=simplify_astates_t->nxt
                 
             };
             simplify_astates_i:=simplify_astates_i-1
         }
         else
         {
             skip
         }
         
     };
     continue_1<==0 and skip;
     tfree(simplify_astates_acc)
     )
     }; 
  function print_alternating (  )
 {
     frame(print_alternating_i,print_alternating_t,continue_1) and ( 
     int continue_1<==0 and skip;
     int print_alternating_i and skip;
     ATrans *print_alternating_t and skip;
     output ("init :\n") and skip;
     print_alternating_t:=transition[0];
     
     while(print_alternating_t)
     {
         print_set(print_alternating_t->to,0);
         output ("\n") and skip;
         print_alternating_t:=print_alternating_t->nxt
         
     };
     continue_1<==0 and skip;
     print_alternating_i:=node_id-1;
     
     while(print_alternating_i>0)
     {
          continue_1<==0 and skip;
         if(!label[print_alternating_i]) then 
         {
             continue_1<==1 and skip;
              print_alternating_i:=print_alternating_i-1
         }
         else 
         {
              skip 
         };
         if(continue_1=0)   then 
         {
             output ("state ",print_alternating_i,"i : ") and skip;
             dump(label[print_alternating_i]);
             output ("\n") and skip;
             print_alternating_t:=transition[print_alternating_i];
             
             while(print_alternating_t)
             {
                 if((extern empty_set(print_alternating_t->pos,1,RValue)) AND (extern empty_set(print_alternating_t->neg,1,RValue))) then 
                 {
                     output ("1") and skip
                 }
                 else 
                 {
                      skip 
                 };
                 print_set(print_alternating_t->pos,1);
                 if(!(extern empty_set(print_alternating_t->pos,1,RValue)) AND !(extern empty_set(print_alternating_t->neg,1,RValue))) then 
                 {
                     output (" & ") and skip
                 }
                 else 
                 {
                      skip 
                 };
                 print_set(print_alternating_t->neg,2);
                 output (" -> ") and skip;
                 print_set(print_alternating_t->to,0);
                 output ("\n") and skip;
                 print_alternating_t:=print_alternating_t->nxt
                 
             };
             print_alternating_i:=print_alternating_i-1
         }
         else
         {
             skip
         }
     };
     continue_1<==0 and skip
     )
     }; 
  function mk_alternating ( Node *p )
 {
     node_size:=(extern calculate_node_size(p,RValue))+1;
     label:=(Node **)(extern tl_emalloc(node_size*4,RValue));
     transition:=(ATrans **)(extern tl_emalloc(node_size*4,RValue));
     node_size:=node_size/ (8*4)+1;
     sym_size:=calculate_sym_size(p,RValue);
	 
     if(sym_size) then 
     {
         sym_table:=(char **)(extern tl_emalloc(sym_size*4,RValue))
     }
     else 
     {
          skip 
     };
     sym_size:=sym_size/ (8*4)+1;
     final_set:=make_set(-1,0,RValue);
     transition[0]:=boolean(p,RValue);
     if(tl_verbose) then 
     {
         output ("\nAlternating automaton before simplification\n") and skip;
         print_alternating()
         
     }
     else 
     {
          skip 
     };
     if(tl_simp_diff) then 
     {
         simplify_astates();
         if(tl_verbose) then 
         {
             output ("\nAlternating automaton after simplification\n") and skip;
             print_alternating()
             
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
     releasenode(1,p);
     tfree(label)
     
 };
 function free_bstate ( BState *s )
 {
     free_btrans(s->trans->nxt,s->trans,1);
     tfree(s)
     
 };
 function remove_bstate ( BState *s,BState *s1,BState* RValue )
 {
     frame(remove_bstate_prv,return_1) and ( 
     int return_1<==0 and skip;
     BState *remove_bstate_prv<==s->prv and skip;
     s->prv->nxt:=s->nxt;
     s->nxt->prv:=s->prv;
     free_btrans(s->trans->nxt,s->trans,0);
     s->trans:=NULL;
     s->nxt:=bremoved->nxt;
     bremoved->nxt:=s;
     s->prv:=s1;
     s1:=bremoved->nxt;
     
     while(s1!=bremoved)
     {
         if(s1->prv=s) then 
         {
             s1->prv:=s->prv
         }
         else 
         {
              skip 
         };
         s1:=s1->nxt
         
     };
     return_1<==1 and RValue:=remove_bstate_prv;
     skip
     )
     }; 
  function copy_btrans ( BTrans *from,BTrans *to )
 {
     to->to:=from->to;
     copy_set(from->pos,to->pos,1);
     copy_set(from->neg,to->neg,1)
     
 };
 function simplify_btrans ( int RValue )
 {
     frame(simplify_btrans_s,simplify_btrans_t,simplify_btrans_t1,simplify_btrans_changed,simplify_btrans_1_3_free,return_1) and ( 
     int return_1<==0 and skip;
     BState *simplify_btrans_s and skip;
     BTrans *simplify_btrans_t,*simplify_btrans_t1 and skip;
     int simplify_btrans_changed<==0 and skip;
     simplify_btrans_s:=bstates->nxt;
     
     while(simplify_btrans_s!=bstates)
     {
         simplify_btrans_t:=simplify_btrans_s->trans->nxt;
         
         while(simplify_btrans_t!=simplify_btrans_s->trans)
         {
             simplify_btrans_t1:=simplify_btrans_s->trans->nxt;
             copy_btrans(simplify_btrans_t,simplify_btrans_s->trans);
             while((simplify_btrans_t=simplify_btrans_t1) OR (simplify_btrans_t->to!=simplify_btrans_t1->to) OR !(extern included_set(simplify_btrans_t1->pos,simplify_btrans_t->pos,1,RValue)) OR !(extern included_set(simplify_btrans_t1->neg,simplify_btrans_t->neg,1,RValue)))
             {
                 simplify_btrans_t1:=simplify_btrans_t1->nxt
             };
             if(simplify_btrans_t1!=simplify_btrans_s->trans) then 
             {
                 BTrans *simplify_btrans_1_3_free<==simplify_btrans_t->nxt and skip;
                 simplify_btrans_t->to:=simplify_btrans_1_3_free->to;
                 copy_set(simplify_btrans_1_3_free->pos,simplify_btrans_t->pos,1);
                 copy_set(simplify_btrans_1_3_free->neg,simplify_btrans_t->neg,1);
                 simplify_btrans_t->nxt:=simplify_btrans_1_3_free->nxt;
                 if(simplify_btrans_1_3_free=simplify_btrans_s->trans) then 
                 {
                     simplify_btrans_s->trans:=simplify_btrans_t
                 }
                 else 
                 {
                      skip 
                 };
                 free_btrans(simplify_btrans_1_3_free,0,0);
                 simplify_btrans_changed:=simplify_btrans_changed+1
             }
             else
             {
                 simplify_btrans_t:=simplify_btrans_t->nxt
             }
             
         };
         simplify_btrans_s:=simplify_btrans_s->nxt
         
     };
     if(tl_stats) then 
     {
         output ("\n",simplify_btrans_changed,"itions removed\n") and skip
         
     }
     else 
     {
          skip 
     };
     return_1<==1 and RValue:=simplify_btrans_changed;
     skip
     )
     }; 
  function same_btrans ( BTrans *s,BTrans *t,int RValue )
 {
     frame(return_1) and ( 
     int return_1<==0 and skip;
     return_1<==1 and RValue:=((s->to=t->to) AND same_sets(s->pos,t->pos,1,RValue) AND same_sets(s->neg,t->neg,1,RValue));
     skip
     )
     }; 
  function remove_btrans ( BState *to )
 {
     frame(remove_btrans_s,remove_btrans_t,remove_btrans_i,remove_btrans_1_2_3_free) and ( 
     BState *remove_btrans_s and skip;
     BTrans *remove_btrans_t and skip;
     int remove_btrans_i and skip;
     remove_btrans_s:=bstates->nxt;
     
     while(remove_btrans_s!=bstates)
     {
         remove_btrans_t:=remove_btrans_s->trans->nxt;
         
         while(remove_btrans_t!=remove_btrans_s->trans)
         {
             if(remove_btrans_t->to=to) then 
             {
                 BTrans *remove_btrans_1_2_3_free<==remove_btrans_t->nxt and skip;
                 remove_btrans_t->to:=remove_btrans_1_2_3_free->to;
                 copy_set(remove_btrans_1_2_3_free->pos,remove_btrans_t->pos,1);
                 copy_set(remove_btrans_1_2_3_free->neg,remove_btrans_t->neg,1);
                 remove_btrans_t->nxt:=remove_btrans_1_2_3_free->nxt;
                 if(remove_btrans_1_2_3_free=remove_btrans_s->trans) then 
                 {
                     remove_btrans_s->trans:=remove_btrans_t
                 }
                 else 
                 {
                      skip 
                 };
                 free_btrans(remove_btrans_1_2_3_free,0,0)
                 
             }
             else 
             {
                  skip 
             };
             remove_btrans_t:=remove_btrans_t->nxt
             
         };
         remove_btrans_s:=remove_btrans_s->nxt
         
     }
     )
     }; 
  function retarget_all_btrans (  )
 {
     frame(retarget_all_btrans_s,retarget_all_btrans_t,retarget_all_btrans_1_2_3_4_free) and ( 
     BState *retarget_all_btrans_s and skip;
     BTrans *retarget_all_btrans_t and skip;
     retarget_all_btrans_s:=bstates->nxt;
     
     while(retarget_all_btrans_s!=bstates)
     {
         retarget_all_btrans_t:=retarget_all_btrans_s->trans->nxt;
         
         while(retarget_all_btrans_t!=retarget_all_btrans_s->trans)
         {
             if(!retarget_all_btrans_t->to->trans) then 
             {
                 retarget_all_btrans_t->to:=retarget_all_btrans_t->to->prv;
                 if(!retarget_all_btrans_t->to) then 
                 {
                     BTrans *retarget_all_btrans_1_2_3_4_free<==retarget_all_btrans_t->nxt and skip;
                     retarget_all_btrans_t->to:=retarget_all_btrans_1_2_3_4_free->to;
                     copy_set(retarget_all_btrans_1_2_3_4_free->pos,retarget_all_btrans_t->pos,1);
                     copy_set(retarget_all_btrans_1_2_3_4_free->neg,retarget_all_btrans_t->neg,1);
                     retarget_all_btrans_t->nxt:=retarget_all_btrans_1_2_3_4_free->nxt;
                     if(retarget_all_btrans_1_2_3_4_free=retarget_all_btrans_s->trans) then 
                     {
                         retarget_all_btrans_s->trans:=retarget_all_btrans_t
                     }
                     else 
                     {
                          skip 
                     };
                     free_btrans(retarget_all_btrans_1_2_3_4_free,0,0)
                     
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
             retarget_all_btrans_t:=retarget_all_btrans_t->nxt
             
         };
         retarget_all_btrans_s:=retarget_all_btrans_s->nxt
         
     };
     while(bremoved->nxt!=bremoved)
     {
         retarget_all_btrans_s:=bremoved->nxt;
         bremoved->nxt:=bremoved->nxt->nxt;
         tfree(retarget_all_btrans_s)
     }
     )
     }; 
  function all_btrans_match ( BState *a,BState *b,int RValue )
 {
     frame(all_btrans_match_s,all_btrans_match_t,return_1) and ( 
     int return_1<==0 and skip;
     BTrans *all_btrans_match_s,*all_btrans_match_t and skip;
     if(((a->final=accept) OR (b->final=accept)) AND ((a->final+b->final)!=2*accept) AND a->incoming>=0 AND b->incoming>=0) then 
     {
         return_1<==1 and RValue:=0;
         skip
         
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         all_btrans_match_s:=a->trans->nxt;
         
         while( return_1=0 AND  all_btrans_match_s!=a->trans)
         {
             copy_btrans(all_btrans_match_s,b->trans);
             all_btrans_match_t:=b->trans->nxt;
             while(!(extern same_btrans(all_btrans_match_s,all_btrans_match_t,RValue)))
             {
                 all_btrans_match_t:=all_btrans_match_t->nxt
             };
             if(all_btrans_match_t=b->trans) then 
             {
                 return_1<==1 and RValue:=0;
                 skip
             }
             else 
             {
                  skip 
             };
             if(return_1=0)   then 
             {
                 all_btrans_match_s:=all_btrans_match_s->nxt
             }
             else
             {
                 skip
             }
             
         };
         if(return_1=0)   then 
         {
             all_btrans_match_s:=b->trans->nxt;
             
             while( return_1=0 AND  all_btrans_match_s!=b->trans)
             {
                 copy_btrans(all_btrans_match_s,a->trans);
                 all_btrans_match_t:=a->trans->nxt;
                 while(!(extern same_btrans(all_btrans_match_s,all_btrans_match_t,RValue)))
                 {
                     all_btrans_match_t:=all_btrans_match_t->nxt
                 };
                 if(all_btrans_match_t=a->trans) then 
                 {
                     return_1<==1 and RValue:=0;
                     skip
                 }
                 else 
                 {
                      skip 
                 };
                 if(return_1=0)   then 
                 {
                     all_btrans_match_s:=all_btrans_match_s->nxt
                 }
                 else
                 {
                     skip
                 }
                 
             };
             if(return_1=0)   then 
             {
                 return_1<==1 and RValue:=1;
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
  function simplify_bstates ( int RValue )
 {
     frame(simplify_bstates_s,simplify_bstates_s1,simplify_bstates_changed,return_1,continue_1) and ( 
     int continue_1<==0 and skip;
     int return_1<==0 and skip;
     BState *simplify_bstates_s,*simplify_bstates_s1 and skip;
     int simplify_bstates_changed<==0 and skip;
     continue_1<==0 and skip;
     simplify_bstates_s:=bstates->nxt;
     
     while(simplify_bstates_s!=bstates)
     {
          continue_1<==0 and skip;
         if(simplify_bstates_s->trans=simplify_bstates_s->trans->nxt) then 
         {
             simplify_bstates_s:=remove_bstate(simplify_bstates_s,NULL,RValue);
             simplify_bstates_changed:=simplify_bstates_changed+1;
             continue_1<==1 and skip;
              simplify_bstates_s:=simplify_bstates_s->nxt
         }
         else 
         {
              skip 
         };
         if(continue_1=0)   then 
         {
             bstates->trans:=simplify_bstates_s->trans;
             bstates->final:=simplify_bstates_s->final;
             simplify_bstates_s1:=simplify_bstates_s->nxt;
             while(!(extern all_btrans_match(simplify_bstates_s,simplify_bstates_s1,RValue)))
             {
                 simplify_bstates_s1:=simplify_bstates_s1->nxt
             };
             if(simplify_bstates_s1!=bstates) then 
             {
                 if(simplify_bstates_s1->incoming=-1) then 
                 {
                     simplify_bstates_s1->final:=simplify_bstates_s->final
                 }
                 else 
                 {
                      skip 
                 };
                 simplify_bstates_s:=remove_bstate(simplify_bstates_s,simplify_bstates_s1,RValue);
                 simplify_bstates_changed:=simplify_bstates_changed+1
                 
             }
             else 
             {
                  skip 
             };
             simplify_bstates_s:=simplify_bstates_s->nxt
         }
         else
         {
             skip
         }
         
     };
     continue_1<==0 and skip;
     retarget_all_btrans();
     return_1<==1 and RValue:=simplify_bstates_changed;
     skip
     )
     }; 
  function bdfs ( BState *s,int RValue )
 {
     frame(bdfs_t,bdfs_c,bdfs_scc,bdfs_1_result,return_1,break_1) and ( 
     int break_1<==0 and skip;
     int return_1<==0 and skip;
     BTrans *bdfs_t and skip;
     BScc *bdfs_c and skip;
     BScc *bdfs_scc and skip;
     bdfs_scc:=(BScc *)(extern tl_emalloc(16,RValue));
     bdfs_scc->bstate:=s;
     bdfs_scc->rank:=rank;
     bdfs_scc->theta:=rank;
     rank:=rank+1;
     bdfs_scc->nxt:=Bscc_stack;
     Bscc_stack:=bdfs_scc;
     s->incoming:=1;
     bdfs_t:=s->trans->nxt;
     
     while(bdfs_t!=s->trans)
     {
         if(bdfs_t->to->incoming=0) then 
         {
             int bdfs_1_result and skip;
             bdfs_1_result:=bdfs(bdfs_t->to,RValue);
             bdfs_scc->theta:=(( if((bdfs_scc->theta<bdfs_1_result)) then bdfs_scc->theta else bdfs_1_result))
             
         }
         else
         {
             break_1<==0 and skip;
             bdfs_c:=Bscc_stack->nxt;
             
             while( break_1=0 AND  bdfs_c!=NULL)
             {
                 if(bdfs_c->bstate=bdfs_t->to) then 
                 {
                     bdfs_scc->theta:=(( if((bdfs_scc->theta<bdfs_c->rank)) then bdfs_scc->theta else bdfs_c->rank));
                     break_1<==1 and skip
                      
                 }
                 else 
                 {
                      skip 
                 };
                 if(break_1=0)   then
                 {
                     bdfs_c:=bdfs_c->nxt
                 }
                 else
                 {
                     skip
                 }
             };
             break_1<==0 and skip
         };
         bdfs_t:=bdfs_t->nxt
         
     };
     if(bdfs_scc->rank=bdfs_scc->theta) then 
     {
         if(Bscc_stack=bdfs_scc) then 
         {
             s->incoming:=-1;
             bdfs_t:=s->trans->nxt;
             
             while(bdfs_t!=s->trans)
             {
                 if(bdfs_t->to=s) then 
                 {
                     s->incoming:=1
                 }
                 else 
                 {
                      skip 
                 };
                 bdfs_t:=bdfs_t->nxt
                 
             }
             
         }
         else 
         {
              skip 
         };
         Bscc_stack:=bdfs_scc->nxt
         
     }
     else 
     {
          skip 
     };
     return_1<==1 and RValue:=bdfs_scc->theta;
     skip
     )
     }; 
  function simplify_bscc (  )
 {
     frame(simplify_bscc_s,return_1) and ( 
     int return_1<==0 and skip;
     BState *simplify_bscc_s and skip;
     rank:=1;
     Bscc_stack:=0;
     if(bstates=bstates->nxt) then 
     {
          return_1<==1 and skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         simplify_bscc_s:=bstates->nxt;
         
         while(simplify_bscc_s!=bstates)
         {
             simplify_bscc_s->incoming:=0;
             simplify_bscc_s:=simplify_bscc_s->nxt
             
         };
         bdfs(bstates->prv,RValue);
         simplify_bscc_s:=bstates->nxt;
         
         while(simplify_bscc_s!=bstates)
         {
             if(simplify_bscc_s->incoming=0) then 
             {
                 remove_bstate(simplify_bscc_s,0,RValue)
             }
             else 
             {
                  skip 
             };
             simplify_bscc_s:=simplify_bscc_s->nxt
             
         }
     }
     else
     {
         skip
     }
     )
     }; 
  function find_bstate ( GState **state,int final,BState *s,BState* RValue )
 {
     frame(return_1) and ( 
     int return_1<==0 and skip;
     if((s->gstate=* state) AND (s->final=final)) then 
     {
         return_1<==1 and RValue:=s;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         s:=bstack->nxt;
         bstack->gstate:=* state;
         bstack->final:=final;
         while(!(s->gstate=* state) OR !(s->final=final))
         {
             s:=s->nxt
         };
         if(s!=bstack) then 
         {
             return_1<==1 and RValue:=s;
             skip
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             s:=bstates->nxt;
             bstates->gstate:=* state;
             bstates->final:=final;
             while(!(s->gstate=* state) OR !(s->final=final))
             {
                 s:=s->nxt
             };
             if(s!=bstates) then 
             {
                 return_1<==1 and RValue:=s;
                 skip
             }
             else 
             {
                  skip 
             };
             if(return_1=0)   then 
             {
                 s:=bremoved->nxt;
                 bremoved->gstate:=* state;
                 bremoved->final:=final;
                 while(!(s->gstate=* state) OR !(s->final=final))
                 {
                     s:=s->nxt
                 };
                 if(s!=bremoved) then 
                 {
                     return_1<==1 and RValue:=s;
                     skip
                 }
                 else 
                 {
                      skip 
                 };
                 if(return_1=0)   then 
                 {
                     s:=(BState *)(extern tl_emalloc(28,RValue));
                     s->gstate:=* state;
                     s->id:=(* state)->id;
                     s->incoming:=0;
                     s->final:=final;
                     s->trans:=emalloc_btrans(RValue);
                     s->trans->nxt:=s->trans;
                     s->nxt:=bstack->nxt;
                     bstack->nxt:=s;
                     return_1<==1 and RValue:=s;
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
  function next_final ( int *set,int fin$,int RValue )
 {
     frame(return_1) and ( 
     int return_1<==0 and skip;
     if((fin$!=accept) AND (extern in_set(set,final[fin$+1],RValue))) then 
     {
         return_1<==1 and RValue:=next_final(set,fin$+1,RValue);
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         return_1<==1 and RValue:=fin$;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function make_btrans ( BState *s )
 {
     frame(make_btrans_state_trans,make_btrans_t,make_btrans_t1,make_btrans_s1,make_btrans_1_fin$,make_btrans_1_to,make_btrans_1_2_free,make_btrans_1_7_trans,return_1,break_1) and ( 
     int break_1<==0 and skip;
     int return_1<==0 and skip;
     int make_btrans_state_trans<==0 and skip;
     GTrans *make_btrans_t and skip;
     BTrans *make_btrans_t1 and skip;
     BState *make_btrans_s1 and skip;
     if(s->gstate->trans) then 
     {
         make_btrans_t:=s->gstate->trans->nxt;
         
         while(make_btrans_t!=s->gstate->trans)
         {
             int make_btrans_1_fin$ and skip;
             make_btrans_1_fin$:=next_final(make_btrans_t->final,( if((s->final=accept)) then 0 else s->final),RValue);
             BState *make_btrans_1_to and skip;
             make_btrans_1_to:=find_bstate(&make_btrans_t->to,make_btrans_1_fin$,s,RValue);
             break_1<==0 and skip;
             make_btrans_t1:=s->trans->nxt;
             
             while( break_1=0 AND  make_btrans_t1!=s->trans)
             {
                 if(tl_simp_fly AND (make_btrans_1_to=make_btrans_t1->to) AND (extern included_set(make_btrans_t->pos,make_btrans_t1->pos,1,RValue)) AND (extern included_set(make_btrans_t->neg,make_btrans_t1->neg,1,RValue))) then 
                 {
                     BTrans *make_btrans_1_2_free<==make_btrans_t1->nxt and skip;
                     make_btrans_t1->to->incoming:=make_btrans_t1->to->incoming-1;
                     make_btrans_t1->to:=make_btrans_1_2_free->to;
                     copy_set(make_btrans_1_2_free->pos,make_btrans_t1->pos,1);
                     copy_set(make_btrans_1_2_free->neg,make_btrans_t1->neg,1);
                     make_btrans_t1->nxt:=make_btrans_1_2_free->nxt;
                     if(make_btrans_1_2_free=s->trans) then 
                     {
                         s->trans:=make_btrans_t1
                     }
                     else 
                     {
                          skip 
                     };
                     free_btrans(make_btrans_1_2_free,0,0);
                     make_btrans_state_trans:=make_btrans_state_trans-1
                 }
                 else
                 {
                     if(tl_simp_fly AND (make_btrans_t1->to=make_btrans_1_to) AND (extern included_set(make_btrans_t1->pos,make_btrans_t->pos,1,RValue)) AND (extern included_set(make_btrans_t1->neg,make_btrans_t->neg,1,RValue))) then 
                     {
                         break_1<==1 and skip
                      }
                     else
                     {
                         make_btrans_t1:=make_btrans_t1->nxt
                     }
                 }
                 
             };
             break_1<==0 and skip;
             if(make_btrans_t1=s->trans) then 
             {
                 BTrans *make_btrans_1_7_trans and skip;
                 make_btrans_1_7_trans:=emalloc_btrans(RValue);
                 make_btrans_1_7_trans->to:=make_btrans_1_to;
                 make_btrans_1_7_trans->to->incoming:=make_btrans_1_7_trans->to->incoming+1;
                 copy_set(make_btrans_t->pos,make_btrans_1_7_trans->pos,1);
                 copy_set(make_btrans_t->neg,make_btrans_1_7_trans->neg,1);
                 make_btrans_1_7_trans->nxt:=s->trans->nxt;
                 s->trans->nxt:=make_btrans_1_7_trans;
                 make_btrans_state_trans:=make_btrans_state_trans+1
                 
             }
             else 
             {
                  skip 
             };
             make_btrans_t:=make_btrans_t->nxt
             
         }
     }
     else 
     {
          skip 
     };
     if(tl_simp_fly) then 
     {
         if(s->trans=s->trans->nxt) then 
         {
             free_btrans(s->trans->nxt,s->trans,1);
             s->trans:=NULL;
             s->prv:=NULL;
             s->nxt:=bremoved->nxt;
             bremoved->nxt:=s;
             make_btrans_s1:=bremoved->nxt;
             
             while(make_btrans_s1!=bremoved)
             {
                 if(make_btrans_s1->prv=s) then 
                 {
                     make_btrans_s1->prv:=NULL
                 }
                 else 
                 {
                      skip 
                 };
                 make_btrans_s1:=make_btrans_s1->nxt
                 
             };
              return_1<==1 and skip
             
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             bstates->trans:=s->trans;
             bstates->final:=s->final;
             make_btrans_s1:=bstates->nxt;
             while(!(extern all_btrans_match(s,make_btrans_s1,RValue)))
             {
                 make_btrans_s1:=make_btrans_s1->nxt
             };
             if(make_btrans_s1!=bstates) then 
             {
                 free_btrans(s->trans->nxt,s->trans,1);
                 s->trans:=NULL;
                 s->prv:=make_btrans_s1;
                 s->nxt:=bremoved->nxt;
                 bremoved->nxt:=s;
                 make_btrans_s1:=bremoved->nxt;
                 
                 while(make_btrans_s1!=bremoved)
                 {
                     if(make_btrans_s1->prv=s) then 
                     {
                         make_btrans_s1->prv:=s->prv
                     }
                     else 
                     {
                          skip 
                     };
                     make_btrans_s1:=make_btrans_s1->nxt
                     
                 };
                  return_1<==1 and skip
                 
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
     if(return_1=0)  then
     {
         s->nxt:=bstates->nxt;
         s->prv:=bstates;
         s->nxt->prv:=s;
         bstates->nxt:=s;
         btrans_count:=btrans_count+make_btrans_state_trans;
         bstate_count:=bstate_count+1
     }
     else
     {
         skip
     }
     )
     }; 
  function print_buchi ( BState *s )
 {
     frame(print_buchi_t,return_1) and ( 
     int return_1<==0 and skip;
     BTrans *print_buchi_t and skip;
     if(s=bstates) then 
     {
          return_1<==1 and skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         print_buchi(s->nxt);
         output ("state ") and skip;
		 if(flag=1) then
          {    count_state:=count_state+1
          }
        else
          {  count_before_state:=count_before_state+1
          };
         if(s->id=-1) then 
         {
             output ("init") and skip
         }
         else
         {
             if(s->final=accept) then 
             {
                 output ("accept") and skip
             }
             else
             {
                 output ("T",s->final,"i") and skip
             };
             output ("_",s->id,"i") and skip
         };
         output ("\n") and skip;
         print_buchi_t:=s->trans->nxt;
         
         while(print_buchi_t!=s->trans)
         {
             if((extern empty_set(print_buchi_t->pos,1,RValue)) AND (extern empty_set(print_buchi_t->neg,1,RValue))) then 
             {
                 output ("1") and skip
             }
             else 
             {
                  skip 
             };
             print_set(print_buchi_t->pos,1);
             if(!(extern empty_set(print_buchi_t->pos,1,RValue)) AND !(extern empty_set(print_buchi_t->neg,1,RValue))) then 
             {
                 output (" & ") and skip
             }
             else 
             {
                  skip 
             };
             print_set(print_buchi_t->neg,2);
             output (" -> ") and skip;
			   if(flag=1) then
          {    count_trans:=count_trans+1
          }
        else
          {  count_before_trans:=count_before_trans+1
          };
             if(print_buchi_t->to->id=-1) then 
             {
                 output ("init\n") and skip
             }
             else
             {
                 if(print_buchi_t->to->final=accept) then 
                 {
                     output ("accept") and skip
                 }
                 else
                 {
                     output ("T",print_buchi_t->to->final,"i") and skip
                 };
                 output ("_",print_buchi_t->to->id,"i\n") and skip
             };
             print_buchi_t:=print_buchi_t->nxt
             
         }
     }
     else
     {
         skip
     }
     )
     }; 
  function print_spin_buchi (  )
 {
     frame(print_spin_buchi_t,print_spin_buchi_s,print_spin_buchi_accept_all,print_spin_buchi_init_count,print_spin_buchi_t1,return_1,continue_1) and ( 
     int continue_1<==0 and skip;
     int return_1<==0 and skip;
     BTrans *print_spin_buchi_t and skip;
     BState *print_spin_buchi_s and skip;
     int print_spin_buchi_accept_all<==0,print_spin_buchi_init_count<==0 and skip;
     if(bstates->nxt=bstates) then 
     {
         output ("never {
         \n") and skip;
         output ("T0_init:\n") and skip;
         output ("\tfalse;\n") and skip;
         output ("}\n") and skip;
          return_1<==1 and skip
         
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         if(bstates->nxt->nxt=bstates AND bstates->nxt->id=0) then 
         {
             output ("never {
             \n") and skip;
             output ("accept_init:\n") and skip;
             output ("\tif\n") and skip;
             output ("\t:: (1) -> goto_1 accept_init\n") and skip;
             output ("\tfi;\n") and skip;
             output ("}\n") and skip;
              return_1<==1 and skip
             
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             output ("never {
             \n") and skip;
             continue_1<==0 and skip;
             print_spin_buchi_s:=bstates->prv;
             
             while(print_spin_buchi_s!=bstates)
             {
                  continue_1<==0 and skip;
                 if(print_spin_buchi_s->id=0) then 
                 {
                     print_spin_buchi_accept_all:=1;
                     continue_1<==1 and skip;
                      print_spin_buchi_s:=print_spin_buchi_s->prv
                 }
                 else 
                 {
                      skip 
                 };
                 if(continue_1=0)   then 
                 {
                     if(print_spin_buchi_s->final=accept) then 
                     {
                         output ("accept_") and skip
                     }
                     else
                     {
                         output ("T",print_spin_buchi_s->final,"i_") and skip
                     };
                     if(print_spin_buchi_s->id=-1) then 
                     {
                         output ("init:\n") and skip
                     }
                     else
                     {
                         output ("S",print_spin_buchi_s->id,"i:\n") and skip
                     };
                     if(print_spin_buchi_s->trans->nxt=print_spin_buchi_s->trans) then 
                     {
                         output ("\tfalse;\n") and skip;
                         continue_1<==1 and skip;
                          print_spin_buchi_s:=print_spin_buchi_s->prv
                     }
                     else 
                     {
                          skip 
                     };
                     if(continue_1=0)   then 
                     {
                         output ("\tif\n") and skip;
                         print_spin_buchi_t:=print_spin_buchi_s->trans->nxt;
                         
                         while(print_spin_buchi_t!=print_spin_buchi_s->trans)
                         {
                             BTrans *print_spin_buchi_t1 and skip;
                             output ("\t:: (") and skip;
                             spin_print_set(print_spin_buchi_t->pos,print_spin_buchi_t->neg);
                             print_spin_buchi_t1:=print_spin_buchi_t;
                             
                             while(print_spin_buchi_t1->nxt!=print_spin_buchi_s->trans)
                             {
                                 if(print_spin_buchi_t1->nxt->to->id=print_spin_buchi_t->to->id AND print_spin_buchi_t1->nxt->to->final=print_spin_buchi_t->to->final) then 
                                 {
                                     output (") || (") and skip;
                                     spin_print_set(print_spin_buchi_t1->nxt->pos,print_spin_buchi_t1->nxt->neg);
                                     print_spin_buchi_t1->nxt:=print_spin_buchi_t1->nxt->nxt
                                 }
                                 else
                                 {
                                     print_spin_buchi_t1:=print_spin_buchi_t1->nxt
                                 }
                                 
                                 
                             };
                             output (") -> goto_1 ") and skip;
                             if(print_spin_buchi_t->to->final=accept) then 
                             {
                                 output ("accept_") and skip
                             }
                             else
                             {
                                 output ("T",print_spin_buchi_t->to->final,"i_") and skip
                             };
                             if(print_spin_buchi_t->to->id=0) then 
                             {
                                 output ("all\n") and skip
                             }
                             else
                             {
                                 if(print_spin_buchi_t->to->id=-1) then 
                                 {
                                     output ("init\n") and skip
                                 }
                                 else
                                 {
                                     output ("S",print_spin_buchi_t->to->id,"i\n") and skip
                                 }
                             };
                             print_spin_buchi_t:=print_spin_buchi_t->nxt
                             
                         };
                         output ("\tfi;\n") and skip;
                         print_spin_buchi_s:=print_spin_buchi_s->prv
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
             continue_1<==0 and skip;
             if(print_spin_buchi_accept_all) then 
             {
                 output ("accept_all:\n") and skip;
                 output ("\tskip\n") and skip
                 
             }
             else 
             {
                  skip 
             };
             output ("}\n") and skip
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
  function mk_buchi (  )
 {
     frame(mk_buchi_i,mk_buchi_s,mk_buchi_t,mk_buchi_t1,mk_buchi_1_fin$,mk_buchi_1_to,mk_buchi_1_2_free,mk_buchi_1_7_trans,break_1,continue_1) and ( 
     int continue_1<==0 and skip;
     int break_1<==0 and skip;
     int mk_buchi_i and skip;
     BState *mk_buchi_s and skip;
     mk_buchi_s:=(BState *)(extern tl_emalloc(28,RValue));
     GTrans *mk_buchi_t and skip;
     BTrans *mk_buchi_t1 and skip;
     rank:=0;
     accept:=final[0]-1;
     bstack:=(BState *)(extern tl_emalloc(28,RValue));
     bstack->nxt:=bstack;
     bremoved:=(BState *)(extern tl_emalloc(28,RValue));
     bremoved->nxt:=bremoved;
     bstates:=(BState *)(extern tl_emalloc(28,RValue));
     bstates->nxt:=mk_buchi_s;
     bstates->prv:=mk_buchi_s;
     mk_buchi_s->nxt:=bstates;
     mk_buchi_s->prv:=bstates;
     mk_buchi_s->id:=-1;
     mk_buchi_s->incoming:=1;
     mk_buchi_s->final:=0;
     mk_buchi_s->gstate:=0;
     mk_buchi_s->trans:=emalloc_btrans(RValue);
     mk_buchi_s->trans->nxt:=mk_buchi_s->trans;
     mk_buchi_i:=0;
     
     while(mk_buchi_i<init_size)
     {
         if(init[mk_buchi_i]) then 
         {
             mk_buchi_t:=init[mk_buchi_i]->trans->nxt;
             
             while(mk_buchi_t!=init[mk_buchi_i]->trans)
             {
                 int mk_buchi_1_fin$ and skip;
                 mk_buchi_1_fin$:=next_final(mk_buchi_t->final,0,RValue);
                 BState *mk_buchi_1_to and skip;
                mk_buchi_1_to:=find_bstate(&mk_buchi_t->to,mk_buchi_1_fin$,mk_buchi_s,RValue);
                 break_1<==0 and skip;
                 mk_buchi_t1:=mk_buchi_s->trans->nxt;
                 
                 while( break_1=0 AND  mk_buchi_t1!=mk_buchi_s->trans)
                 {
                     if(tl_simp_fly AND (mk_buchi_1_to=mk_buchi_t1->to) AND (extern included_set(mk_buchi_t->pos,mk_buchi_t1->pos,1,RValue)) AND (extern included_set(mk_buchi_t->neg,mk_buchi_t1->neg,1,RValue))) then 
                     {
                         BTrans *mk_buchi_1_2_free<==mk_buchi_t1->nxt and skip;
                         mk_buchi_t1->to->incoming:=mk_buchi_t1->to->incoming-1;
                         mk_buchi_t1->to:=mk_buchi_1_2_free->to;
                         copy_set(mk_buchi_1_2_free->pos,mk_buchi_t1->pos,1);
                         copy_set(mk_buchi_1_2_free->neg,mk_buchi_t1->neg,1);
                         mk_buchi_t1->nxt:=mk_buchi_1_2_free->nxt;
                         if(mk_buchi_1_2_free=mk_buchi_s->trans) then 
                         {
                             mk_buchi_s->trans:=mk_buchi_t1
                         }
                         else 
                         {
                              skip 
                         };
                         free_btrans(mk_buchi_1_2_free,0,0)
                     }
                     else
                     {
                         if(tl_simp_fly AND (mk_buchi_t1->to=mk_buchi_1_to) AND (extern included_set(mk_buchi_t1->pos,mk_buchi_t->pos,1,RValue)) AND (extern included_set(mk_buchi_t1->neg,mk_buchi_t->neg,1,RValue))) then 
                         {
                             break_1<==1 and skip
                          }
                         else
                         {
                             mk_buchi_t1:=mk_buchi_t1->nxt
                         }
                     }
                     
                 };
                 break_1<==0 and skip;
                 if(mk_buchi_t1=mk_buchi_s->trans) then 
                 {
                     BTrans *mk_buchi_1_7_trans and skip;
                     mk_buchi_1_7_trans:=emalloc_btrans(RValue);
                     mk_buchi_1_7_trans->to:=mk_buchi_1_to;
                     mk_buchi_1_7_trans->to->incoming:=mk_buchi_1_7_trans->to->incoming+1;
                     copy_set(mk_buchi_t->pos,mk_buchi_1_7_trans->pos,1);
                     copy_set(mk_buchi_t->neg,mk_buchi_1_7_trans->neg,1);
                     mk_buchi_1_7_trans->nxt:=mk_buchi_s->trans->nxt;
                     mk_buchi_s->trans->nxt:=mk_buchi_1_7_trans
                     
                 }
                 else 
                 {
                      skip 
                 };
                 mk_buchi_t:=mk_buchi_t->nxt
                 
             }
             
         }
         else 
         {
              skip 
         };
         mk_buchi_i:=mk_buchi_i+1
         
     };
     while(bstack->nxt!=bstack)
     {
         continue_1<==0 and skip;
         mk_buchi_s:=bstack->nxt;
         bstack->nxt:=bstack->nxt->nxt;
         if(!mk_buchi_s->incoming) then 
         {
             free_bstate(mk_buchi_s);
             continue_1<==1 and skip
              
         }
         else 
         {
              skip 
         };
         if(continue_1=0)   then 
         {
             make_btrans(mk_buchi_s)
         }
         else
         {
             skip
         }
     };
     continue_1<==0 and skip;
     retarget_all_btrans();
     if(tl_verbose) then 
     {
         output ("\nBuchi automaton before simplification\n") and skip;
         print_buchi(bstates->nxt);
         if(bstates=bstates->nxt) then 
         {
             output ("empty automaton, refuses all words\n") and skip
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
     if(tl_simp_diff) then 
     {
         simplify_btrans(RValue);
         if(tl_simp_scc) then 
         {
             simplify_bscc()
         }
         else 
         {
              skip 
         };
         while(extern simplify_bstates(RValue))
         {
             simplify_btrans(RValue);
             if(tl_simp_scc) then 
             {
                 simplify_bscc()
             }
             else 
             {
                  skip 
             }
         };
         if(tl_verbose) then 
         {
             output ("\nBuchi automaton after simplification\n") and skip;
			 flag<==1 and skip;
             print_buchi(bstates->nxt);
             if(bstates=bstates->nxt) then 
             {
                 output ("empty automaton, refuses all words\n") and skip
             }
             else 
             {
                  skip 
             };
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
	 output(count_state," states,",count_trans,"transitions\n") and skip;
     print_spin_buchi()
     )
     }; 
  function cache_dump (  )
 {
     frame(cache_dump_d,cache_dump_nr,continue_1) and ( 
     int continue_1<==0 and skip;
     Cache *cache_dump_d and skip;
     int cache_dump_nr<==0 and skip;
     output ("\nCACHE DUMP:\n") and skip;
     continue_1<==0 and skip;
     cache_dump_d:=stored;
     
     while(cache_dump_d)
     {
          continue_1<==0 and skip;
         if(cache_dump_d->same) then 
         {
             continue_1<==1 and skip;
              cache_dump_d:=cache_dump_d->nxt and cache_dump_nr:=cache_dump_nr+1}
             else 
             {
                  skip 
             };
             if(continue_1=0)   then 
             {
                 output ("B",cache_dump_nr,": ") and skip;
                 dump(cache_dump_d->before);
                 output ("\n") and skip;
                 output ("A",cache_dump_nr,": ") and skip;
                 dump(cache_dump_d->after);
                 output ("\n") and skip;
                 cache_dump_d:=cache_dump_d->nxt and cache_dump_nr:=cache_dump_nr+1
             }
             else
             {
                 skip
             }
             
         };
         continue_1<==0 and skip;
         output ("============\n") and skip
         )
         }; 
  function in_cache ( Node *n,Node* RValue )
 {
     frame(in_cache_d,in_cache_nr,return_1) and ( 
     int return_1<==0 and skip;
     Cache *in_cache_d and skip;
     int in_cache_nr<==0 and skip;
     in_cache_d:=stored;
     while(in_cache_d)
     {
         in_cache_d->same:=0;
         in_cache_d:=in_cache_d->nxt
     };
     in_cache_d:=stored;
     
     while( return_1=0 AND  in_cache_d)
     {
         if(extern isequal(in_cache_d->before,n,RValue)) then 
         {
             CacheHits:=CacheHits+1;
             if( (extern ismatch(n,in_cache_d->before,RValue)) AND in_cache_d->same  ) then 
             {
                 return_1<==1 and RValue:=n;
                 skip
             }
             else 
             {
                  skip 
             };
             if(return_1=0)   then 
             {
                 return_1<==1 and RValue:=dupnode(in_cache_d->after,RValue);
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
         };
         if(return_1=0)  then
         {
             if(return_1=0)   then 
             {
                 in_cache_d:=in_cache_d->nxt and in_cache_nr:=in_cache_nr+1
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
     if(return_1=0)   then 
     {
         return_1<==1 and RValue:=NULL;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function cached ( Node *n,Node* RValue )
 {
     frame(cached_d,cached_m,return_1) and ( 
     int return_1<==0 and skip;
     Cache *cached_d and skip;
     Node *cached_m and skip;
     if(!n) then 
     {
         return_1<==1 and RValue:=n;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         cached_m:=in_cache(n,RValue) ;
         if(cached_m) then 
         {
             return_1<==1 and RValue:=cached_m;
             skip
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             Caches:=Caches+1;
             cached_d:=(Cache *)(extern tl_emalloc(16,RValue));
             cached_d->before:=dupnode(n,RValue);
             cached_d->after:=Canonical(n,RValue);
             if((extern ismatch(cached_d->before,cached_d->after,RValue))) then 
             {
                 cached_d->same:=1;
                 releasenode(1,cached_d->after);
                 cached_d->after:=cached_d->before
                 
             }
             else 
             {
                  skip 
             };
             cached_d->nxt:=stored;
             stored:=cached_d;
             return_1<==1 and RValue:=dupnode(cached_d->after,RValue);
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
  function cache_stats (  )
 {
     output ("cache stores     : ",Caches,"\n") and skip;
     output ("cache hits       : ",CacheHits,"\n") and skip
     
 };
 function releasenode ( int all_levels,Node *n )
 {
     frame(return_1) and ( 
     int return_1<==0 and skip;
     if(!n) then 
     {
          return_1<==1 and skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         if(all_levels) then 
         {
             releasenode(1,n->lft);
             n->lft:=NULL;
             releasenode(1,n->rgt);
             n->rgt:=NULL
             
         }
         else 
         {
              skip 
         };
         tfree(n)
     }
     else
     {
         skip
     }
     )
     }; 
  function tl_nn ( int t,Node *ll,Node *rl,Node* RValue )
 {
     frame(tl_nn_n,return_1) and ( 
     int return_1<==0 and skip;
     Node *tl_nn_n and skip;
     tl_nn_n:=(Node *)(extern tl_emalloc(20,RValue));
     tl_nn_n->ntyp:=(int)t;
     tl_nn_n->lft:=ll;
     tl_nn_n->rgt:=rl;
     return_1<==1 and RValue:=tl_nn_n;
     skip
     )
     }; 
  function getnode ( Node *p,Node* RValue )
 {
     frame(getnode_n,return_1) and ( 
     int return_1<==0 and skip;
     Node *getnode_n and skip;
     if(!p) then 
     {
         return_1<==1 and RValue:=p;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         getnode_n:=(Node *)(extern tl_emalloc(20,RValue));
         getnode_n->ntyp:=p->ntyp;
         getnode_n->sym:=p->sym;
         getnode_n->lft:=p->lft;
         getnode_n->rgt:=p->rgt;
         return_1<==1 and RValue:=getnode_n;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function dupnode ( Node *n,Node* RValue )
 {
     frame(dupnode_d,return_1) and ( 
     int return_1<==0 and skip;
     Node *dupnode_d and skip;
     if(!n) then 
     {
         return_1<==1 and RValue:=n;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         dupnode_d:=getnode(n,RValue);
         dupnode_d->lft:=dupnode(n->lft,RValue);
         dupnode_d->rgt:=dupnode(n->rgt,RValue);
         return_1<==1 and RValue:=dupnode_d;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function one_lft ( int ntyp,Node *x,Node *in,int RValue )
 {
     frame(return_1) and ( 
     int return_1<==0 and skip;
     if(!x) then 
     {
         return_1<==1 and RValue:=1;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         if(!in) then 
         {
             return_1<==1 and RValue:=0;
             skip
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             if(extern sameform(x,in,RValue)) then 
             {
                 return_1<==1 and RValue:=1;
                 skip
             }
             else 
             {
                  skip 
             };
             if(return_1=0)   then 
             {
                 if(in->ntyp!=ntyp) then 
                 {
                     return_1<==1 and RValue:=0;
                     skip
                 }
                 else 
                 {
                      skip 
                 };
                 if(return_1=0)   then 
                 {
                     if(extern one_lft(ntyp,x,in->lft,RValue)) then 
                     {
                         return_1<==1 and RValue:=1;
                         skip
                     }
                     else 
                     {
                          skip 
                     };
                     if(return_1=0)   then 
                     {
                         return_1<==1 and RValue:=one_lft(ntyp,x,in->rgt,RValue);
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
     }
     else
     {
         skip
     }
     )
     }; 
  function all_lfts ( int ntyp,Node *from,Node *in,int RValue )
 {
     frame(return_1) and ( 
     int return_1<==0 and skip;
     if(!from) then 
     {
         return_1<==1 and RValue:=1;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         if(from->ntyp!=ntyp) then 
         {
             return_1<==1 and RValue:=one_lft(ntyp,from,in,RValue);
             skip
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             if(!(extern one_lft(ntyp,from->lft,in,RValue))) then 
             {
                 return_1<==1 and RValue:=0;
                 skip
             }
             else 
             {
                  skip 
             };
             if(return_1=0)   then 
             {
                 return_1<==1 and RValue:=all_lfts(ntyp,from->rgt,in,RValue);
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
  function sametrees ( int ntyp,Node *a,Node *b,int RValue )
 {
     frame(return_1) and ( 
     int return_1<==0 and skip;
     if(!(extern all_lfts(ntyp,a,b,RValue))) then 
     {
         return_1<==1 and RValue:=0;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         return_1<==1 and RValue:=all_lfts(ntyp,b,a,RValue);
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function sameform ( Node *a,Node *b,int RValue )
 {
     frame(nm_7$,break_1$,switch_1,return_1) and ( 
     int return_1<==0 and skip;
     if(!a AND !b) then 
     {
         return_1<==1 and RValue:=1;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         if(!a OR !b) then 
         {
             return_1<==1 and RValue:=0;
             skip
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             if(a->ntyp!=b->ntyp) then 
             {
                 return_1<==1 and RValue:=0;
                 skip
             }
             else 
             {
                  skip 
             };
             if(return_1=0)   then 
             {
                 if(a->sym AND b->sym AND strcmp(a->sym->name,b->sym->name)!=0) then 
                 {
                     return_1<==1 and RValue:=0;
                     skip
                 }
                 else 
                 {
                      skip 
                 };
                 if(return_1=0)   then 
                 {
                     int switch_1 and skip;
                     int break_1$ and skip;
                     break_1$<==0 and skip;
                      switch_1<==0 and skip;
                      int nm_7$ and skip;
                     nm_7$ := a->ntyp;
                     if (nm_7$=TRUE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                     {
                         switch_1<==1 and skip
                         
                     }
                     else
                     {
                         skip
                     };
                     if (nm_7$=FALSE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                     {
                         switch_1<==1 and skip;
                         return_1<==1 and RValue:=1;
                         skip
                         
                     }
                     else
                     {
                         skip
                     };
                     if (nm_7$=PREDICATE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                     {
                         switch_1<==1 and skip;
                         if(!a->sym OR !b->sym) then 
                         {
                             fatal("sameform...",NULL)
                         }
                         else 
                         {
                              skip 
                         };
                         return_1<==1 and RValue:=!strcmp(a->sym->name,b->sym->name);
                         skip
                         
                     }
                     else
                     {
                         skip
                     };
                     if (nm_7$=NOT OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                     {
                         switch_1<==1 and skip;
                         return_1<==1 and RValue:=sameform(a->lft,b->lft,RValue);
                         skip
                         
                     }
                     else
                     {
                         skip
                     };
                     if (nm_7$=U_OPER OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                     {
                         switch_1<==1 and skip
                         
                     }
                     else
                     {
                         skip
                     };
                     if (nm_7$=V_OPER OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                     {
                         switch_1<==1 and skip;
                         if(!(extern sameform(a->lft,b->lft,RValue))) then 
                         {
                             return_1<==1 and RValue:=0;
                             skip
                         }
                         else 
                         {
                              skip 
                         };
                         if(return_1=0)   then 
                         {
                             if(!(extern sameform(a->rgt,b->rgt,RValue))) then 
                             {
                                 return_1<==1 and RValue:=0;
                                 skip
                             }
                             else 
                             {
                                  skip 
                             };
                             if(return_1=0)   then 
                             {
                                 return_1<==1 and RValue:=1;
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
                     };
                     if (nm_7$=AND_1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                     {
                         switch_1<==1 and skip
                         
                     }
                     else
                     {
                         skip
                     };
                     if (nm_7$=OR_1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                     {
                         switch_1<==1 and skip;
                         return_1<==1 and RValue:=sametrees(a->ntyp,a,b,RValue);
                         skip
                         
                     }
                     else
                     {
                         skip
                     };
                     if(break_1$=0 AND return_1=0) then 
                     {
                         output ("type: ",a->ntyp,"\n") and skip;
                         fatal("cannot happen, sameform",NULL)
                         
                     }
                     else
                     {
                          skip
                     };
                     if(return_1=0)   then 
                     {
                         return_1<==1 and RValue:=0;
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
     }
     else
     {
         skip
     }
     )
     }; 
  function isequal ( Node *a,Node *b,int RValue )
 {
     frame(return_1) and ( 
     int return_1<==0 and skip;
     if(!a AND !b) then 
     {
         return_1<==1 and RValue:=1;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         if(!a OR !b) then 
         {
             if(!a) then 
             {
                 if(b->ntyp=TRUE) then 
                 {
                     return_1<==1 and RValue:=1;
                     skip
                 }
                 else 
                 {
                      skip 
                 }
                 
             }
             else
             {
                 if(a->ntyp=TRUE) then 
                 {
                     return_1<==1 and RValue:=1;
                     skip
                 }
                 else 
                 {
                      skip 
                 }
             };
             if(return_1=0)  then
             {
                 return_1<==1 and RValue:=0;
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
         };
         if(return_1=0)  then
         {
             if(return_1=0)   then 
             {
                 if(a->ntyp!=b->ntyp) then 
                 {
                     return_1<==1 and RValue:=0;
                     skip
                 }
                 else 
                 {
                      skip 
                 };
                 if(return_1=0)   then 
                 {
                     if(a->sym AND b->sym AND strcmp(a->sym->name,b->sym->name)!=0) then 
                     {
                         return_1<==1 and RValue:=0;
                         skip
                     }
                     else 
                     {
                          skip 
                     };
                     if(return_1=0)   then 
                     {
                         if((extern isequal(a->lft,b->lft,RValue)) AND (extern isequal(a->rgt,b->rgt,RValue))) then 
                         {
                             return_1<==1 and RValue:=1;
                             skip
                         }
                         else 
                         {
                              skip 
                         };
                         if(return_1=0)   then 
                         {
                             return_1<==1 and RValue:=sameform(a,b,RValue);
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
  function ismatch ( Node *a,Node *b,int RValue )
 {
     frame(return_1) and ( 
     int return_1<==0 and skip;
     if(!a AND !b) then 
     {
         return_1<==1 and RValue:=1;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         if(!a OR !b) then 
         {
             return_1<==1 and RValue:=0;
             skip
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             if(a->ntyp!=b->ntyp) then 
             {
                 return_1<==1 and RValue:=0;
                 skip
             }
             else 
             {
                  skip 
             };
             if(return_1=0)   then 
             {
                 if(a->sym AND b->sym AND strcmp(a->sym->name,b->sym->name)!=0) then 
                 {
                     return_1<==1 and RValue:=0;
                     skip
                 }
                 else 
                 {
                      skip 
                 };
                 if(return_1=0)   then 
                 {
                     if((extern ismatch(a->lft,b->lft,RValue)) AND (extern ismatch(a->rgt,b->rgt,RValue))) then 
                     {
                         return_1<==1 and RValue:=1;
                         skip
                     }
                     else 
                     {
                          skip 
                     };
                     if(return_1=0)   then 
                     {
                         return_1<==1 and RValue:=0;
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
     }
     else
     {
         skip
     }
     )
     }; 
  function any_term ( Node *srch,Node *in,int RValue )
 {
     frame(return_1) and ( 
     int return_1<==0 and skip;
     if(!in) then 
     {
         return_1<==1 and RValue:=0;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         if(in->ntyp=AND_1) then 
         {
             return_1<==1 and RValue:= (any_term(srch,in->lft,RValue) OR any_term(srch,in->rgt,RValue))
       
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             return_1<==1 and RValue:=isequal(in,srch,RValue);
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
  function any_and ( Node *srch,Node *in,int RValue )
 {
     frame(return_1) and ( 
     int return_1<==0 and skip;
     if(!in) then 
     {
         return_1<==1 and RValue:=0;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         if(srch->ntyp=AND_1) then 
         {
             return_1<==1 and RValue:= ((extern any_and(srch->lft,in,RValue)) AND (extern any_and(srch->rgt,in,RValue)));
             skip
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             return_1<==1 and RValue:=any_term(srch,in,RValue);
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
  function any_lor ( Node *srch,Node *in,int RValue )
 {
     frame(return_1) and ( 
     int return_1<==0 and skip;
     if(!in) then 
     {
         return_1<==1 and RValue:=0;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         if(in->ntyp=OR_1) then 
         {
             return_1<==1 and RValue:= (any_lor(srch,in->lft,RValue) OR any_lor(srch,in->rgt,RValue))
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             return_1<==1 and RValue:=isequal(in,srch,RValue);
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
  function anywhere ( int tok,Node *srch,Node *in,int RValue )
 {
     frame(nm_8$,break_1$,switch_1,return_1) and ( 
     int return_1<==0 and skip;
     if(!in) then 
     {
         return_1<==1 and RValue:=0;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         int switch_1 and skip;
         int break_1$ and skip;
         break_1$<==0 and skip;
          switch_1<==0 and skip;
          int nm_8$ and skip;
         nm_8$ := tok;
         if (nm_8$=AND_1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             return_1<==1 and RValue:=any_and(srch,in,RValue);
             skip
             
         }
         else
         {
             skip
         };
         if (nm_8$=OR_1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             return_1<==1 and RValue:=any_lor(srch,in,RValue);
             skip
             
         }
         else
         {
             skip
         };
         if (nm_8$=0 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             return_1<==1 and RValue:=any_term(srch,in,RValue);
             skip
             
         }
         else
         {
             skip
         };
         if(return_1=0)   then 
         {
             fatal("cannot happen, anywhere",NULL);
             return_1<==1 and RValue:=0;
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
  function free_gstate ( GState *s )
 {
     free_gtrans(s->trans->nxt,s->trans,1);
     tfree(s->nodes_set);
     tfree(s)
     
 };
 function remove_gstate ( GState *s,GState *s1,GState* RValue )
 {
     frame(remove_gstate_prv,return_1) and ( 
     int return_1<==0 and skip;
     GState *remove_gstate_prv<==s->prv and skip;
     s->prv->nxt:=s->nxt;
     s->nxt->prv:=s->prv;
     free_gtrans(s->trans->nxt,s->trans,0);
     s->trans:=NULL;
     tfree(s->nodes_set);
     s->nodes_set:=0;
     s->nxt:=gremoved->nxt;
     gremoved->nxt:=s;
     s->prv:=s1;
     s1:=gremoved->nxt;
     
     while(s1!=gremoved)
     {
         if(s1->prv=s) then 
         {
             s1->prv:=s->prv
         }
         else 
         {
              skip 
         };
         s1:=s1->nxt
         
     };
     return_1<==1 and RValue:=remove_gstate_prv;
     skip
     )
     }; 
  function copy_gtrans ( GTrans *from,GTrans *to )
 {
     to->to:=from->to;
     copy_set(from->pos,to->pos,1);
     copy_set(from->neg,to->neg,1);
     copy_set(from->final,to->final,0)
     
 };
 function same_gtrans ( GState *a,GTrans *s,GState *b,GTrans *t,int use_scc,int RValue )
 {
     frame(return_1) and ( 
     int return_1<==0 and skip;
     if((s->to!=t->to) OR !(extern same_sets(s->pos,t->pos,1,RValue)) OR !(extern same_sets(s->neg,t->neg,1,RValue))) then 
     {
         return_1<==1 and RValue:=0;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         if((extern same_sets(s->final,t->final,0,RValue))) then 
         {
             return_1<==1 and RValue:=1;
             skip
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             if(use_scc AND ((extern in_set(bad_scc,a->incoming,RValue)) OR (extern in_set(bad_scc,b->incoming,RValue)) OR (a->incoming!=s->to->incoming) OR (b->incoming!=t->to->incoming))) then 
             {
                 return_1<==1 and RValue:=1;
                 skip
             }
             else 
             {
                  skip 
             };
             if(return_1=0)   then 
             {
                 return_1<==1 and RValue:=0;
                 skip;
                 if(!use_scc) then 
                 {
                     return_1<==1 and RValue:=0;
                     skip
                 }
                 else 
                 {
                      skip 
                 };
                 if(return_1=0)   then 
                 {
                     if((a->incoming=b->incoming) AND (a->incoming=s->to->incoming)) then 
                     {
                         return_1<==1 and RValue:=0;
                         skip
                     }
                     else 
                     {
                          skip 
                     };
                     if(return_1=0)   then 
                     {
                         return_1<==1 and RValue:=1;
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
     }
     else
     {
         skip
     }
     )
     }; 
  function simplify_gtrans ( int RValue )
 {
     frame(simplify_gtrans_changed,simplify_gtrans_s,simplify_gtrans_t,simplify_gtrans_t1,simplify_gtrans_1_3_free,return_1) and ( 
     int return_1<==0 and skip;
     int simplify_gtrans_changed<==0 and skip;
     GState *simplify_gtrans_s and skip;
     GTrans *simplify_gtrans_t,*simplify_gtrans_t1 and skip;
     simplify_gtrans_s:=gstates->nxt;
     
     while(simplify_gtrans_s!=gstates)
     {
         simplify_gtrans_t:=simplify_gtrans_s->trans->nxt;
         while(simplify_gtrans_t!=simplify_gtrans_s->trans)
         {
             copy_gtrans(simplify_gtrans_t,simplify_gtrans_s->trans);
             simplify_gtrans_t1:=simplify_gtrans_s->trans->nxt;
             while(!((simplify_gtrans_t!=simplify_gtrans_t1) AND (simplify_gtrans_t1->to=simplify_gtrans_t->to) AND (extern included_set(simplify_gtrans_t1->pos,simplify_gtrans_t->pos,1,RValue)) AND (extern included_set(simplify_gtrans_t1->neg,simplify_gtrans_t->neg,1,RValue)) AND ((extern included_set(simplify_gtrans_t->final,simplify_gtrans_t1->final,0,RValue)) OR (tl_simp_scc AND ((simplify_gtrans_s->incoming!=simplify_gtrans_t->to->incoming) OR (extern in_set(bad_scc,simplify_gtrans_s->incoming,RValue)))))))
             {
                 simplify_gtrans_t1:=simplify_gtrans_t1->nxt
             };
             if(simplify_gtrans_t1!=simplify_gtrans_s->trans) then 
             {
                 GTrans *simplify_gtrans_1_3_free<==simplify_gtrans_t->nxt and skip;
                 simplify_gtrans_t->to:=simplify_gtrans_1_3_free->to;
                 copy_set(simplify_gtrans_1_3_free->pos,simplify_gtrans_t->pos,1);
                 copy_set(simplify_gtrans_1_3_free->neg,simplify_gtrans_t->neg,1);
                 copy_set(simplify_gtrans_1_3_free->final,simplify_gtrans_t->final,0);
                 simplify_gtrans_t->nxt:=simplify_gtrans_1_3_free->nxt;
                 if(simplify_gtrans_1_3_free=simplify_gtrans_s->trans) then 
                 {
                     simplify_gtrans_s->trans:=simplify_gtrans_t
                 }
                 else 
                 {
                      skip 
                 };
                 free_gtrans(simplify_gtrans_1_3_free,0,0);
                 simplify_gtrans_changed:=simplify_gtrans_changed+1
             }
             else
             {
                 simplify_gtrans_t:=simplify_gtrans_t->nxt
             }
         };
         simplify_gtrans_s:=simplify_gtrans_s->nxt
         
     };
     return_1<==1 and RValue:=simplify_gtrans_changed;
     skip
     )
     }; 
  function retarget_all_gtrans (  )
 {
     frame(retarget_all_gtrans_s,retarget_all_gtrans_t,retarget_all_gtrans_i,retarget_all_gtrans_3_4_5_6_free) and ( 
     GState *retarget_all_gtrans_s and skip;
     GTrans *retarget_all_gtrans_t and skip;
     int retarget_all_gtrans_i and skip;
     retarget_all_gtrans_i:=0;
     
     while(retarget_all_gtrans_i<init_size)
     {
         if(init[retarget_all_gtrans_i] AND !init[retarget_all_gtrans_i]->trans) then 
         {
             init[retarget_all_gtrans_i]:=init[retarget_all_gtrans_i]->prv
         }
         else 
         {
              skip 
         };
         retarget_all_gtrans_i:=retarget_all_gtrans_i+1
         
     };
     retarget_all_gtrans_s:=gstates->nxt;
     
     while(retarget_all_gtrans_s!=gstates)
     {
         retarget_all_gtrans_t:=retarget_all_gtrans_s->trans->nxt;
         
         while(retarget_all_gtrans_t!=retarget_all_gtrans_s->trans)
         {
             if(!retarget_all_gtrans_t->to->trans) then 
             {
                 retarget_all_gtrans_t->to:=retarget_all_gtrans_t->to->prv;
                 if(!retarget_all_gtrans_t->to) then 
                 {
                     GTrans *retarget_all_gtrans_3_4_5_6_free<==retarget_all_gtrans_t->nxt and skip;
                     retarget_all_gtrans_t->to:=retarget_all_gtrans_3_4_5_6_free->to;
                     copy_set(retarget_all_gtrans_3_4_5_6_free->pos,retarget_all_gtrans_t->pos,1);
                     copy_set(retarget_all_gtrans_3_4_5_6_free->neg,retarget_all_gtrans_t->neg,1);
                     copy_set(retarget_all_gtrans_3_4_5_6_free->final,retarget_all_gtrans_t->final,0);
                     retarget_all_gtrans_t->nxt:=retarget_all_gtrans_3_4_5_6_free->nxt;
                     if(retarget_all_gtrans_3_4_5_6_free=retarget_all_gtrans_s->trans) then 
                     {
                         retarget_all_gtrans_s->trans:=retarget_all_gtrans_t
                     }
                     else 
                     {
                          skip 
                     };
                     free_gtrans(retarget_all_gtrans_3_4_5_6_free,0,0)
                 }
                 else
                 {
                     retarget_all_gtrans_t:=retarget_all_gtrans_t->nxt
                 }
             }
             else
             {
                 retarget_all_gtrans_t:=retarget_all_gtrans_t->nxt
             }
             
             
         };
         retarget_all_gtrans_s:=retarget_all_gtrans_s->nxt
         
     };
     while(gremoved->nxt!=gremoved)
     {
         retarget_all_gtrans_s:=gremoved->nxt;
         gremoved->nxt:=gremoved->nxt->nxt;
         if(retarget_all_gtrans_s->nodes_set) then 
         {
             tfree(retarget_all_gtrans_s->nodes_set)
         }
         else 
         {
              skip 
         };
         tfree(retarget_all_gtrans_s)
     }
     )
     }; 
  function all_gtrans_match ( GState *a,GState *b,int use_scc,int RValue )
 {
     frame(all_gtrans_match_s,all_gtrans_match_t,return_1) and ( 
     int return_1<==0 and skip;
     GTrans *all_gtrans_match_s,*all_gtrans_match_t and skip;
     all_gtrans_match_s:=a->trans->nxt;
     
     while( return_1=0 AND  all_gtrans_match_s!=a->trans)
     {
         copy_gtrans(all_gtrans_match_s,b->trans);
         all_gtrans_match_t:=b->trans->nxt;
         while(!(extern same_gtrans(a,all_gtrans_match_s,b,all_gtrans_match_t,use_scc,RValue)))
         {
             all_gtrans_match_t:=all_gtrans_match_t->nxt
         };
         if(all_gtrans_match_t=b->trans) then 
         {
             return_1<==1 and RValue:=0;
             skip
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             all_gtrans_match_s:=all_gtrans_match_s->nxt
         }
         else
         {
             skip
         }
         
     };
     if(return_1=0)   then 
     {
         all_gtrans_match_t:=b->trans->nxt;
         
         while( return_1=0 AND  all_gtrans_match_t!=b->trans)
         {
             copy_gtrans(all_gtrans_match_t,a->trans);
             all_gtrans_match_s:=a->trans->nxt;
             while(!(extern same_gtrans(a,all_gtrans_match_s,b,all_gtrans_match_t,use_scc,RValue)))
             {
                 all_gtrans_match_s:=all_gtrans_match_s->nxt
             };
             if(all_gtrans_match_s=a->trans) then 
             {
                 return_1<==1 and RValue:=0;
                 skip
             }
             else 
             {
                  skip 
             };
             if(return_1=0)   then 
             {
                 all_gtrans_match_t:=all_gtrans_match_t->nxt
             }
             else
             {
                 skip
             }
             
         };
         if(return_1=0)   then 
         {
             return_1<==1 and RValue:=1;
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
  function simplify_gstates ( int RValue )
 {
     frame(simplify_gstates_changed,simplify_gstates_a,simplify_gstates_b,return_1,continue_1) and ( 
     int continue_1<==0 and skip;
     int return_1<==0 and skip;
     int simplify_gstates_changed<==0 and skip;
     GState *simplify_gstates_a,*simplify_gstates_b and skip;
     continue_1<==0 and skip;
     simplify_gstates_a:=gstates->nxt;
     
     while(simplify_gstates_a!=gstates)
     {
          continue_1<==0 and skip;
         if(simplify_gstates_a->trans=simplify_gstates_a->trans->nxt) then 
         {
             simplify_gstates_a:=remove_gstate(simplify_gstates_a,NULL,RValue);
             simplify_gstates_changed:=simplify_gstates_changed+1;
             continue_1<==1 and skip;
              simplify_gstates_a:=simplify_gstates_a->nxt
         }
         else 
         {
              skip 
         };
         if(continue_1=0)   then 
         {
             gstates->trans:=simplify_gstates_a->trans;
             simplify_gstates_b:=simplify_gstates_a->nxt;
             while(!(extern all_gtrans_match(simplify_gstates_a,simplify_gstates_b,tl_simp_scc,RValue)))
             {
                 simplify_gstates_b:=simplify_gstates_b->nxt
             };
             if(simplify_gstates_b!=gstates) then 
             {
                 if(simplify_gstates_a->incoming>simplify_gstates_b->incoming) then 
                 {
                     simplify_gstates_a:=remove_gstate(simplify_gstates_a,simplify_gstates_b,RValue)
                 }
                 else
                 {
                     remove_gstate(simplify_gstates_b,simplify_gstates_a,RValue)
                 };
                 simplify_gstates_changed:=simplify_gstates_changed+1
                 
             }
             else 
             {
                  skip 
             };
             simplify_gstates_a:=simplify_gstates_a->nxt
         }
         else
         {
             skip
         }
         
     };
     continue_1<==0 and skip;
     retarget_all_gtrans();
     return_1<==1 and RValue:=simplify_gstates_changed;
     skip
     )
     }; 
  function gdfs ( GState *s,int RValue )
 {
     frame(gdfs_t,gdfs_c,gdfs_scc,gdfs_1_result,return_1,break_1) and ( 
     int break_1<==0 and skip;
     int return_1<==0 and skip;
     GTrans *gdfs_t and skip;
     GScc *gdfs_c and skip;
     GScc *gdfs_scc and skip;
     gdfs_scc:=(GScc *)(extern tl_emalloc(16,RValue));
     gdfs_scc->gstate:=s;
     gdfs_scc->rank:=rank;
     gdfs_scc->theta:=rank;
     rank:=rank+1;
     gdfs_scc->nxt:=scc_stack;
     scc_stack:=gdfs_scc;
     s->incoming:=1;
     gdfs_t:=s->trans->nxt;
     
     while(gdfs_t!=s->trans)
     {
         if(gdfs_t->to->incoming=0) then 
         {
             int gdfs_1_result and skip;
             gdfs_1_result:=gdfs(gdfs_t->to,RValue);
             gdfs_scc->theta:=(( if((gdfs_scc->theta<gdfs_1_result)) then gdfs_scc->theta else gdfs_1_result))
             
         }
         else
         {
             break_1<==0 and skip;
             gdfs_c:=scc_stack->nxt;
             
             while( break_1=0 AND  gdfs_c!=NULL)
             {
                 if(gdfs_c->gstate=gdfs_t->to) then 
                 {
                     gdfs_scc->theta:=(( if((gdfs_scc->theta<gdfs_c->rank)) then gdfs_scc->theta else gdfs_c->rank));
                     break_1<==1 and skip
                      
                 }
                 else 
                 {
                      skip 
                 };
                 if(break_1=0)   then
                 {
                     gdfs_c:=gdfs_c->nxt
                 }
                 else
                 {
                     skip
                 }
             };
             break_1<==0 and skip
         };
         gdfs_t:=gdfs_t->nxt
         
     };
     if(gdfs_scc->rank=gdfs_scc->theta) then 
     {
         while(scc_stack!=gdfs_scc)
         {
             scc_stack->gstate->incoming:=scc_id;
             scc_stack:=scc_stack->nxt
         };
         gdfs_scc->gstate->incoming:=scc_id;
         scc_id:=scc_id+1;
         scc_stack:=gdfs_scc->nxt
         
     }
     else 
     {
          skip 
     };
     return_1<==1 and RValue:=gdfs_scc->theta;
     skip
     )
     }; 
  function simplify_gscc (  )
 {
     frame(simplify_gscc_s,simplify_gscc_t,simplify_gscc_i,simplify_gscc_scc_final,return_1) and ( 
     int return_1<==0 and skip;
     GState *simplify_gscc_s and skip;
     GTrans *simplify_gscc_t and skip;
     int simplify_gscc_i,**simplify_gscc_scc_final and skip;
     rank:=1;
     scc_stack:=0;
     scc_id:=1;
     if(gstates=gstates->nxt) then 
     {
          return_1<==1 and skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         simplify_gscc_s:=gstates->nxt;
         
         while(simplify_gscc_s!=gstates)
         {
             simplify_gscc_s->incoming:=0;
             simplify_gscc_s:=simplify_gscc_s->nxt
             
         };
         simplify_gscc_i:=0;
         
         while(simplify_gscc_i<init_size)
         {
             if(init[simplify_gscc_i] AND init[simplify_gscc_i]->incoming=0) then 
             {
                 gdfs(init[simplify_gscc_i],RValue)
             }
             else 
             {
                  skip 
             };
             simplify_gscc_i:=simplify_gscc_i+1
             
         };
         simplify_gscc_scc_final:=(int **)(extern tl_emalloc(scc_id*4,RValue));
         simplify_gscc_i:=0;
         
         while(simplify_gscc_i<scc_id)
         {
             simplify_gscc_scc_final[simplify_gscc_i]:=make_set(-1,0,RValue);
             simplify_gscc_i:=simplify_gscc_i+1
             
         };
         simplify_gscc_s:=gstates->nxt;
         
         while(simplify_gscc_s!=gstates)
         {
             if(simplify_gscc_s->incoming=0) then 
             {
                 simplify_gscc_s:=remove_gstate(simplify_gscc_s,0,RValue)
             }
             else
             {
                 simplify_gscc_t:=simplify_gscc_s->trans->nxt;
                 
                 while(simplify_gscc_t!=simplify_gscc_s->trans)
                 {
                     if(simplify_gscc_t->to->incoming=simplify_gscc_s->incoming) then 
                     {
                         merge_sets(simplify_gscc_scc_final[simplify_gscc_s->incoming],simplify_gscc_t->final,0)
                     }
                     else 
                     {
                          skip 
                     };
                     simplify_gscc_t:=simplify_gscc_t->nxt
                     
                 }
             };
             simplify_gscc_s:=simplify_gscc_s->nxt
             
         };
         scc_size:=(scc_id+1)/ (8*4)+1;
         bad_scc:=make_set(-1,2,RValue);
         simplify_gscc_i:=0;
         
         while(simplify_gscc_i<scc_id)
         {
             if(!(extern included_set(final_set,simplify_gscc_scc_final[simplify_gscc_i],0,RValue))) then 
             {
                 add_set(bad_scc,simplify_gscc_i)
             }
             else 
             {
                  skip 
             };
             simplify_gscc_i:=simplify_gscc_i+1
             
         };
         simplify_gscc_i:=0;
         
         while(simplify_gscc_i<scc_id)
         {
             tfree(simplify_gscc_scc_final[simplify_gscc_i]);
             simplify_gscc_i:=simplify_gscc_i+1
             
         };
         tfree(simplify_gscc_scc_final)
     }
     else
     {
         skip
     }
     )
     }; 
  function is_final ( int *from,ATrans *at,int i,int RValue )
 {
     frame(is_final_t,is_final_in_to,return_1) and ( 
     int return_1<==0 and skip;
     ATrans *is_final_t and skip;
     int is_final_in_to and skip;
     if((tl_fjtofj AND !(extern in_set(at->to,i,RValue))) OR (!tl_fjtofj AND !(extern in_set(from,i,RValue)))) then 
     {
         return_1<==1 and RValue:=1;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         is_final_in_to:=in_set(at->to,i,RValue);
         rem_set(at->to,i);
         is_final_t:=transition[i];
         
         while( return_1=0 AND  is_final_t)
         {
             if((extern included_set(is_final_t->to,at->to,0,RValue)) AND (extern included_set(is_final_t->pos,at->pos,1,RValue)) AND (extern included_set(is_final_t->neg,at->neg,1,RValue))) then 
             {
                 if(is_final_in_to) then 
                 {
                     add_set(at->to,i)
                 }
                 else 
                 {
                      skip 
                 };
                 return_1<==1 and RValue:=1;
                 skip
                 
             }
             else 
             {
                  skip 
             };
             if(return_1=0)   then 
             {
                 is_final_t:=is_final_t->nxt
             }
             else
             {
                 skip
             }
             
         };
         if(return_1=0)   then 
         {
             if(is_final_in_to) then 
             {
                 add_set(at->to,i)
             }
             else 
             {
                  skip 
             };
             return_1<==1 and RValue:=0;
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
  function find_gstate ( int *set,GState *s,GState* RValue )
 {
     frame(return_1) and ( 
     int return_1<==0 and skip;
     if(extern same_sets(set,s->nodes_set,0,RValue)) then 
     {
         return_1<==1 and RValue:=s;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         s:=gstack->nxt;
         gstack->nodes_set:=set;
         while(!(extern same_sets(set,s->nodes_set,0,RValue)))
         {
             s:=s->nxt
         };
         if(s!=gstack) then 
         {
             return_1<==1 and RValue:=s;
             skip
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             s:=gstates->nxt;
             gstates->nodes_set:=set;
             while(!(extern same_sets(set,s->nodes_set,0,RValue)))
             {
                 s:=s->nxt
             };
             if(s!=gstates) then 
             {
                 return_1<==1 and RValue:=s;
                 skip
             }
             else 
             {
                  skip 
             };
             if(return_1=0)   then 
             {
                 s:=gremoved->nxt;
                 gremoved->nodes_set:=set;
                 while(!(extern same_sets(set,s->nodes_set,0,RValue)))
                 {
                     s:=s->nxt
                 };
                 if(s!=gremoved) then 
                 {
                     return_1<==1 and RValue:=s;
                     skip
                 }
                 else 
                 {
                      skip 
                 };
                 if(return_1=0)   then 
                 {
                     s:=(GState *)(extern tl_emalloc(24,RValue));
                     s->id:=( if(((extern empty_set(set,0,RValue)))) then 0 else gstate_id);
                     if(!(extern empty_set(set,0,RValue))) then 
                     {
                         gstate_id:=gstate_id+1
                     }
                     else 
                     {
                          skip 
                     };
                     s->incoming:=0;
                     s->nodes_set:=dup_set(set,0,RValue);
                     s->trans:=emalloc_gtrans(RValue);
                     s->trans->nxt:=s->trans;
                     s->nxt:=gstack->nxt;
                     gstack->nxt:=s;
                     return_1<==1 and RValue:=s;
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
  function make_gtrans ( GState *s )
 {
     frame(make_gtrans_i,make_gtrans_list$,make_gtrans_state_trans,make_gtrans_trans_exist,make_gtrans_s1,make_gtrans_t,make_gtrans_t1,make_gtrans_free,make_gtrans_prod,make_gtrans_p,make_gtrans_2_p,make_gtrans_2_3_trans,make_gtrans_2_3_t2,make_gtrans_2_3_5_free,make_gtrans_15_p,return_1,break_1) and ( 
     int break_1<==0 and skip;
     int return_1<==0 and skip;
     int make_gtrans_i,*make_gtrans_list$,make_gtrans_state_trans<==0,make_gtrans_trans_exist<==1 and skip;
     GState *make_gtrans_s1 and skip;
     GTrans *make_gtrans_t and skip;
     ATrans *make_gtrans_t1,*make_gtrans_free and skip;
     AProd *make_gtrans_prod and skip;
     make_gtrans_prod:=(AProd *)(extern tl_emalloc(20,RValue));
     make_gtrans_prod->nxt:=make_gtrans_prod;
     make_gtrans_prod->prv:=make_gtrans_prod;
     make_gtrans_prod->prod:=emalloc_atrans(RValue);
     clear_set(make_gtrans_prod->prod->to,0,RValue);
     clear_set(make_gtrans_prod->prod->pos,1,RValue);
     clear_set(make_gtrans_prod->prod->neg,1,RValue);
     make_gtrans_prod->trans:=make_gtrans_prod->prod;
     make_gtrans_prod->trans->nxt:=make_gtrans_prod->prod;
     make_gtrans_list$:=list_set(s->nodes_set,0,RValue);
     make_gtrans_i:=1;
     
     while(make_gtrans_i<make_gtrans_list$[0])
     {
         AProd *make_gtrans_p and skip;
         make_gtrans_p:=(AProd *)(extern tl_emalloc(20,RValue));
         make_gtrans_p->astate:=make_gtrans_list$[make_gtrans_i];
         make_gtrans_p->trans:=transition[make_gtrans_list$[make_gtrans_i]];
         if(!make_gtrans_p->trans) then 
         {
             make_gtrans_trans_exist:=0
         }
         else 
         {
              skip 
         };
         make_gtrans_p->prod:=merge_trans(make_gtrans_prod->nxt->prod,make_gtrans_p->trans,RValue);
         make_gtrans_p->nxt:=make_gtrans_prod->nxt;
         make_gtrans_p->prv:=make_gtrans_prod;
         make_gtrans_p->nxt->prv:=make_gtrans_p;
         make_gtrans_p->prv->nxt:=make_gtrans_p;
         make_gtrans_i:=make_gtrans_i+1
         
     };
     break_1<==0 and skip;
     while( break_1=0 AND  make_gtrans_trans_exist)
     {
         AProd *make_gtrans_2_p<==make_gtrans_prod->nxt and skip;
         make_gtrans_t1:=make_gtrans_2_p->prod;
         if(make_gtrans_t1) then 
         {
             GTrans *make_gtrans_2_3_trans,*make_gtrans_2_3_t2 and skip;
             clear_set(fin$,0,RValue);
             make_gtrans_i:=1;
             
             while(make_gtrans_i<final[0])
             {
                 if(extern is_final(s->nodes_set,make_gtrans_t1,final[make_gtrans_i],RValue)) then 
                 {
                     add_set(fin$,final[make_gtrans_i])
                 }
                 else 
                 {
                      skip 
                 };
                 make_gtrans_i:=make_gtrans_i+1
                 
             };
             break_1<==0 and skip;
             make_gtrans_2_3_t2:=s->trans->nxt;
             
             while( break_1=0 AND  make_gtrans_2_3_t2!=s->trans)
             {
                 if(tl_simp_fly AND (extern included_set(make_gtrans_t1->to,make_gtrans_2_3_t2->to->nodes_set,0,RValue)) AND (extern included_set(make_gtrans_t1->pos,make_gtrans_2_3_t2->pos,1,RValue)) AND (extern included_set(make_gtrans_t1->neg,make_gtrans_2_3_t2->neg,1,RValue)) AND (extern same_sets(fin$,make_gtrans_2_3_t2->final,0,RValue))) then 
                 {
                     GTrans *make_gtrans_2_3_5_free<==make_gtrans_2_3_t2->nxt and skip;
                     make_gtrans_2_3_t2->to->incoming:=make_gtrans_2_3_t2->to->incoming-1;
                     make_gtrans_2_3_t2->to:=make_gtrans_2_3_5_free->to;
                     copy_set(make_gtrans_2_3_5_free->pos,make_gtrans_2_3_t2->pos,1);
                     copy_set(make_gtrans_2_3_5_free->neg,make_gtrans_2_3_t2->neg,1);
                     copy_set(make_gtrans_2_3_5_free->final,make_gtrans_2_3_t2->final,0);
                     make_gtrans_2_3_t2->nxt:=make_gtrans_2_3_5_free->nxt;
                     if(make_gtrans_2_3_5_free=s->trans) then 
                     {
                         s->trans:=make_gtrans_2_3_t2
                     }
                     else 
                     {
                          skip 
                     };
                     free_gtrans(make_gtrans_2_3_5_free,0,0);
                     make_gtrans_state_trans:=make_gtrans_state_trans-1
                 }
                 else
                 {
                     if(tl_simp_fly AND (extern included_set(make_gtrans_2_3_t2->to->nodes_set,make_gtrans_t1->to,0,RValue)) AND (extern included_set(make_gtrans_2_3_t2->pos,make_gtrans_t1->pos,1,RValue)) AND (extern included_set(make_gtrans_2_3_t2->neg,make_gtrans_t1->neg,1,RValue)) AND (extern same_sets(make_gtrans_2_3_t2->final,fin$,0,RValue))) then 
                     {
                         break_1<==1 and skip
                      }
                     else
                     {
                         make_gtrans_2_3_t2:=make_gtrans_2_3_t2->nxt
                     }
                 }
                 
             };
             break_1<==0 and skip;
             if(make_gtrans_2_3_t2=s->trans) then 
             {
                 make_gtrans_2_3_trans:=emalloc_gtrans(RValue);
                 make_gtrans_2_3_trans->to:=find_gstate(make_gtrans_t1->to,s,RValue);
                 make_gtrans_2_3_trans->to->incoming:=make_gtrans_2_3_trans->to->incoming+1;
                 copy_set(make_gtrans_t1->pos,make_gtrans_2_3_trans->pos,1);
                 copy_set(make_gtrans_t1->neg,make_gtrans_2_3_trans->neg,1);
                 copy_set(fin$,make_gtrans_2_3_trans->final,0);
                 make_gtrans_2_3_trans->nxt:=s->trans->nxt;
                 s->trans->nxt:=make_gtrans_2_3_trans;
                 make_gtrans_state_trans:=make_gtrans_state_trans+1
                 
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
         if(!make_gtrans_2_p->trans) then 
         {
             break_1<==1 and skip
          }
         else 
         {
              skip 
         };
         if(break_1=0)   then
         {
             while(!make_gtrans_2_p->trans->nxt)
             {
                 make_gtrans_2_p:=make_gtrans_2_p->nxt
             };
             if(make_gtrans_2_p=make_gtrans_prod) then 
             {
                 break_1<==1 and skip
              }
             else 
             {
                  skip 
             };
             if(break_1=0)   then
             {
                 make_gtrans_2_p->trans:=make_gtrans_2_p->trans->nxt;
                 do_merge_trans(&(make_gtrans_2_p->prod),make_gtrans_2_p->nxt->prod,make_gtrans_2_p->trans);
                 make_gtrans_2_p:=make_gtrans_2_p->prv;
                 while(make_gtrans_2_p!=make_gtrans_prod)
                 {
                     make_gtrans_2_p->trans:=transition[make_gtrans_2_p->astate];
                     do_merge_trans(&(make_gtrans_2_p->prod),make_gtrans_2_p->nxt->prod,make_gtrans_2_p->trans);
                     make_gtrans_2_p:=make_gtrans_2_p->prv
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
     break_1<==0 and skip;
     tfree(make_gtrans_list$);
     while(make_gtrans_prod->nxt!=make_gtrans_prod)
     {
         AProd *make_gtrans_15_p<==make_gtrans_prod->nxt and skip;
         make_gtrans_prod->nxt:=make_gtrans_15_p->nxt;
         free_atrans(make_gtrans_15_p->prod,0);
         tfree(make_gtrans_15_p)
     };
     free_atrans(make_gtrans_prod->prod,0);
     tfree(make_gtrans_prod);
     if(tl_simp_fly) then 
     {
         if(s->trans=s->trans->nxt) then 
         {
             free_gtrans(s->trans->nxt,s->trans,1);
             s->trans:=NULL;
             s->prv:=NULL;
             s->nxt:=gremoved->nxt;
             gremoved->nxt:=s;
             make_gtrans_s1:=gremoved->nxt;
             
             while(make_gtrans_s1!=gremoved)
             {
                 if(make_gtrans_s1->prv=s) then 
                 {
                     make_gtrans_s1->prv:=NULL
                 }
                 else 
                 {
                      skip 
                 };
                 make_gtrans_s1:=make_gtrans_s1->nxt
                 
             };
              return_1<==1 and skip
             
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             gstates->trans:=s->trans;
             make_gtrans_s1:=gstates->nxt;
             while(!(extern all_gtrans_match(s,make_gtrans_s1,0,RValue)))
             {
                 make_gtrans_s1:=make_gtrans_s1->nxt
             };
             if(make_gtrans_s1!=gstates) then 
             {
                 free_gtrans(s->trans->nxt,s->trans,1);
                 s->trans:=NULL;
                 s->prv:=make_gtrans_s1;
                 s->nxt:=gremoved->nxt;
                 gremoved->nxt:=s;
                 make_gtrans_s1:=gremoved->nxt;
                 
                 while(make_gtrans_s1!=gremoved)
                 {
                     if(make_gtrans_s1->prv=s) then 
                     {
                         make_gtrans_s1->prv:=s->prv
                     }
                     else 
                     {
                          skip 
                     };
                     make_gtrans_s1:=make_gtrans_s1->nxt
                     
                 };
                  return_1<==1 and skip
                 
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
     if(return_1=0)  then
     {
         s->nxt:=gstates->nxt;
         s->prv:=gstates;
         s->nxt->prv:=s;
         gstates->nxt:=s;
         gtrans_count:=gtrans_count+make_gtrans_state_trans;
         gstate_count:=gstate_count+1
     }
     else
     {
         skip
     }
     )
     }; 
  function reverse_print_generalized ( GState *s )
 {
     frame(reverse_print_generalized_t,return_1) and ( 
     int return_1<==0 and skip;
     GTrans *reverse_print_generalized_t and skip;
     if(s=gstates) then 
     {
          return_1<==1 and skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         reverse_print_generalized(s->nxt);
         output ("state ",s->id,"i (") and skip;
         print_set(s->nodes_set,0);
         output (") : ",s->incoming,"i\n") and skip;
         reverse_print_generalized_t:=s->trans->nxt;
         
         while(reverse_print_generalized_t!=s->trans)
         {
             if((extern empty_set(reverse_print_generalized_t->pos,1,RValue)) AND (extern empty_set(reverse_print_generalized_t->neg,1,RValue))) then 
             {
                 output ("1") and skip
             }
             else 
             {
                  skip 
             };
             print_set(reverse_print_generalized_t->pos,1);
             if(!(extern empty_set(reverse_print_generalized_t->pos,1,RValue)) AND !(extern empty_set(reverse_print_generalized_t->neg,1,RValue))) then 
             {
                 output (" & ") and skip
             }
             else 
             {
                  skip 
             };
             print_set(reverse_print_generalized_t->neg,1);
             output (" -> ",reverse_print_generalized_t->to->id,"i : ") and skip;
             print_set(reverse_print_generalized_t->final,0);
             output ("\n") and skip;
             reverse_print_generalized_t:=reverse_print_generalized_t->nxt
             
         }
     }
     else
     {
         skip
     }
     )
     }; 
  function print_generalized (  )
 {
     frame(print_generalized_i) and ( 
     int print_generalized_i and skip;
     output ("init :\n") and skip;
     print_generalized_i:=0;
     
     while(print_generalized_i<init_size)
     {
         if(init[print_generalized_i]) then 
         {
             output (init[print_generalized_i]->id,"i\n","i\n") and skip
         }
         else 
         {
              skip 
         };
         print_generalized_i:=print_generalized_i+1
         
     };
     reverse_print_generalized(gstates->nxt)
     )
     }; 
  function mk_generalized (  )
 {
     frame(mk_generalized_t,mk_generalized_s,mk_generalized_i,continue_1) and ( 
     int continue_1<==0 and skip;
     ATrans *mk_generalized_t and skip;
     GState *mk_generalized_s and skip;
     int mk_generalized_i and skip;
     fin$:=new_set(0,RValue);
     bad_scc:=0;
     final:=list_set(final_set,0,RValue);
     gstack:=(GState *)(extern tl_emalloc(24,RValue));
     gstack->nxt:=gstack;
     gremoved:=(GState *)(extern tl_emalloc(24,RValue));
     gremoved->nxt:=gremoved;
     gstates:=(GState *)(extern tl_emalloc(24,RValue));
     gstates->nxt:=gstates;
     gstates->prv:=gstates;
     mk_generalized_t:=transition[0];
     
     while(mk_generalized_t)
     {
         mk_generalized_s:=(GState *)(extern tl_emalloc(24,RValue));
         mk_generalized_s->id:=( if(((extern empty_set(mk_generalized_t->to,0,RValue)))) then 0 else gstate_id);
         if(!((extern empty_set(mk_generalized_t->to,0,RValue)))) then 
         {
             gstate_id:=gstate_id+1
         }
         else 
         {
              skip 
         };
         mk_generalized_s->incoming:=1;
         mk_generalized_s->nodes_set:=dup_set(mk_generalized_t->to,0,RValue);
         mk_generalized_s->trans:=emalloc_gtrans(RValue);
         mk_generalized_s->trans->nxt:=mk_generalized_s->trans;
         mk_generalized_s->nxt:=gstack->nxt;
         gstack->nxt:=mk_generalized_s;
         init_size:=init_size+1;
         mk_generalized_t:=mk_generalized_t->nxt
         
     };
     if(init_size) then 
     {
         init:=(GState **)(extern tl_emalloc(init_size*4,RValue))
     }
     else 
     {
          skip 
     };
     init_size:=0;
     mk_generalized_s:=gstack->nxt;
     
     while(mk_generalized_s!=gstack)
     {
         init[init_size]:=mk_generalized_s;
         init_size:=init_size+1;
         mk_generalized_s:=mk_generalized_s->nxt
         
     };
     while(gstack->nxt!=gstack)
     {
         continue_1<==0 and skip;
         mk_generalized_s:=gstack->nxt;
         gstack->nxt:=gstack->nxt->nxt;
         if(!mk_generalized_s->incoming) then 
         {
             free_gstate(mk_generalized_s);
             continue_1<==1 and skip
              
         }
         else 
         {
              skip 
         };
         if(continue_1=0)   then 
         {
             make_gtrans(mk_generalized_s)
         }
         else
         {
             skip
         }
     };
     continue_1<==0 and skip;
     retarget_all_gtrans();
     tfree(gstack);
     free_all_atrans();
     tfree(transition);
     if(tl_verbose) then 
     {
         output ("\nGeneralized Buchi automaton before simplification\n") and skip;
         print_generalized()
         
     }
     else 
     {
          skip 
     };
     if(tl_simp_diff) then 
     {
         if(tl_simp_scc) then 
         {
             simplify_gscc()
         }
         else 
         {
              skip 
         };
         simplify_gtrans(RValue);
         if(tl_simp_scc) then 
         {
             simplify_gscc()
         }
         else 
         {
              skip 
         };
         while(extern simplify_gstates(RValue))
         {
             if(tl_simp_scc) then 
             {
                 simplify_gscc()
             }
             else 
             {
                  skip 
             };
             simplify_gtrans(RValue);
             if(tl_simp_scc) then 
             {
                 simplify_gscc()
             }
             else 
             {
                  skip 
             }
         };
         if(tl_verbose) then 
         {
             output ("\nGeneralized Buchi automaton after simplification\n") and skip;
             print_generalized()
             
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
  function isalnum_ ( int c,int RValue )
 {
     frame(return_1) and ( 
     int return_1<==0 and skip;
     return_1<==1 and RValue:=(((c>47) AND (c<58)) OR ((c>64) AND (c<91)) OR ((c>96) AND (c<123)) OR (c='_'))
     )
     };
 function hash ( char *s,int RValue )
 {
     frame(hash_h,return_1) and ( 
     int return_1<==0 and skip;
     int hash_h<==0 and skip;
     while(* s)
     {
         hash_h:=hash_h+* s;
         s:=s+1;
         hash_h:=hash_h<< (1 );
         if(hash_h & (255+1)) then 
         {
             hash_h:=hash_h| (1)
         }
         else 
         {
              skip 
         }
     };
     return_1<==1 and RValue:= hash_h & 255;
     skip
     )
     };
  function getword ( int first,void (*tst)(int s,int RValue) )
 {
     frame(getword_i,getword_c,getword_1_temp$_1) and ( 
     int getword_i<==0 and skip;
     char getword_c and skip;
     yytext[getword_i]:=(char)first;
     getword_i:=getword_i+1;
     int getword_1_temp$_1 and skip;
     getword_1_temp$_1:=tl_Getchar(RValue);
     getword_c:=getword_1_temp$_1 ;
     while(extern tst(getword_c,RValue))
     {
         yytext[getword_i]:=getword_c;
         getword_i:=getword_i+1;
         getword_1_temp$_1:=tl_Getchar(RValue);
         getword_c:=getword_1_temp$_1 
     };
     yytext[getword_i]:='\0';
     tl_UnGetchar()
     )
     }; 
  function follow ( int tok,int ifyes,int ifno,int RValue )
 {
     frame(follow_c,follow_buf,return_1) and ( 
     int return_1<==0 and skip;
     int follow_c and skip;
     char follow_buf[32] and skip;
     follow_c:=tl_Getchar(RValue) ;
     if((follow_c)=tok) then 
     {
         return_1<==1 and RValue:=ifyes;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         tl_UnGetchar();
         tl_yychar:=follow_c;
         sprintf(follow_buf,"expected '%c'",tok) and skip;
         tl_yyerror(follow_buf);
         return_1<==1 and RValue:=ifno;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function tl_yylex ( int RValue )///yixie
 {
     frame(tl_yylex_c,return_1) and ( 
     int return_1<==0 and skip;
     int tl_yylex_c and skip;
     tl_yylex_c:=tl_lex(RValue);
     return_1<==1 and RValue:=tl_yylex_c;
     skip
     )
     }; 
  function tl_lex ( int RValue )///yixie
 {
     frame(tl_lex_c,count$,nm_9$,break_1$,switch_1,return_1) and ( 
     int return_1<==0 and skip;
     int tl_lex_c and skip;
     int count$<==0 and skip;
     while( return_1=0 AND   ( count$=0 OR tl_lex_c=' '))
     {
         count$:=count$+1;
         tl_lex_c:=tl_Getchar(RValue);
         yytext[0]:=(char)tl_lex_c;
         yytext[1]:='\0';
         if(tl_lex_c<=0) then 
         {
             tl_yylval:=tl_nn(';',NULL,NULL,RValue);
             return_1<==1 and RValue:=';';
             skip
             
         }
         else 
         {
              skip 
         }
     };
     if(return_1=0)   then 
     {
         if(tl_lex_c>96 AND tl_lex_c<123) then 
         {
             getword(tl_lex_c,isalnum_);
             if(strcmp("true",yytext)=0) then 
             {
                 tl_yylval:=tl_nn(TRUE,NULL,NULL,RValue);
                 return_1<==1 and RValue:=TRUE;
                 skip
                 
             }
             else 
             {
                  skip 
             };
             if(return_1=0)   then 
             {
                 if(strcmp("false",yytext)=0) then 
                 {
                     tl_yylval:=tl_nn(FALSE,NULL,NULL,RValue);
                     return_1<==1 and RValue:=FALSE;
                     skip
                     
                 }
                 else 
                 {
                      skip 
                 };
                 if(return_1=0)   then 
                 {
                     tl_yylval:=tl_nn(PREDICATE,NULL,NULL,RValue);
                     tl_yylval->sym:=tl_lookup(yytext,RValue);
                     return_1<==1 and RValue:=PREDICATE;
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
         };
         if(return_1=0)  then
         {
             if(return_1=0)   then 
             {
                 if(tl_lex_c='<') then 
                 {
                     tl_lex_c:=tl_Getchar(RValue);
                     if(tl_lex_c='>') then 
                     {
                         tl_yylval:=tl_nn(EVENTUALLY,NULL,NULL,RValue);
                         return_1<==1 and RValue:=EVENTUALLY;
                         skip
                         
                     }
                     else 
                     {
                          skip 
                     };
                     if(return_1=0)   then 
                     {
                         if(tl_lex_c!='-') then 
                         {
                             tl_UnGetchar();
                             tl_yyerror("expected '<>' or '<->'")
                             
                         }
                         else 
                         {
                              skip 
                         };
                         tl_lex_c:=tl_Getchar(RValue);
                         if(tl_lex_c='>') then 
                         {
                             tl_yylval:=tl_nn(EQUIV,NULL,NULL,RValue);
                             return_1<==1 and RValue:=EQUIV;
                             skip
                             
                         }
                         else 
                         {
                              skip 
                         };
                         if(return_1=0)   then 
                         {
                             tl_UnGetchar();
                             tl_yyerror("expected '<->'")
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
                 if(return_1=0)  then
                 {
                     int switch_1 and skip;
                     int break_1$ and skip;
                     break_1$<==0 and skip;
                      switch_1<==0 and skip;
                      int nm_9$ and skip;
                     nm_9$ := tl_lex_c;
                     if (nm_9$='/' OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                     {
                         switch_1<==1 and skip;
                         tl_lex_c:=follow('\\',AND_1,'/',RValue);
                         break_1$<==1 and skip
                          
                     }
                     else
                     {
                         skip
                     };
                     if (nm_9$='\\' OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                     {
                         switch_1<==1 and skip;
                         tl_lex_c:=follow('/',OR_1,'\\',RValue);
                         break_1$<==1 and skip
                          
                     }
                     else
                     {
                         skip
                     };
                     if (nm_9$='&' OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                     {
                         switch_1<==1 and skip;
                         tl_lex_c:=follow('&',AND_1,'&',RValue);
                         break_1$<==1 and skip
                          
                     }
                     else
                     {
                         skip
                     };
                     if (nm_9$='|' OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                     {
                         switch_1<==1 and skip;
                         tl_lex_c:=follow('|',OR_1,'|',RValue);
                         break_1$<==1 and skip
                          
                     }
                     else
                     {
                         skip
                     };
                     if (nm_9$='[' OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                     {
                         switch_1<==1 and skip;
                         tl_lex_c:=follow(']',ALWAYS,'[',RValue);
                         break_1$<==1 and skip
                          
                     }
                     else
                     {
                         skip
                     };
                     if (nm_9$='-' OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                     {
                         switch_1<==1 and skip;
                         tl_lex_c:=follow('>',IMPLIES,'-',RValue);
                         break_1$<==1 and skip
                          
                     }
                     else
                     {
                         skip
                     };
                     if (nm_9$='!' OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                     {
                         switch_1<==1 and skip;
                         tl_lex_c:=NOT;
                         break_1$<==1 and skip
                          
                     }
                     else
                     {
                         skip
                     };
                     if (nm_9$='U' OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                     {
                         switch_1<==1 and skip;
                         tl_lex_c:=U_OPER;
                         break_1$<==1 and skip
                          
                     }
                     else
                     {
                         skip
                     };
                     if (nm_9$='V' OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                     {
                         switch_1<==1 and skip;
                         tl_lex_c:=V_OPER;
                         break_1$<==1 and skip
                          
                     }
                     else
                     {
                         skip
                     };
                     if(break_1$=0 AND return_1=0) then 
                     {
                         break_1$<==1 and skip
                          
                     }
                     else
                     {
                          skip
                     };
                     tl_yylval:=tl_nn(tl_lex_c,NULL,NULL,RValue);
                     return_1<==1 and RValue:=tl_lex_c;
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
  function tl_lookup ( char *s,Symbol* RValue )
 {
     frame(tl_lookup_sp,tl_lookup_h,tl_lookup_j,tl_lookup_temp$_1,return_1) and ( 
     int return_1<==0 and skip;
     Symbol *tl_lookup_sp and skip;
     int tl_lookup_h and skip;
     tl_lookup_h:=hash(s,RValue);
     int tl_lookup_j<==0 and skip;
     
     while(tl_lookup_j<255+1)
     {
         symtab[tl_lookup_j]:=NULL;
         tl_lookup_j:=tl_lookup_j+1
         
     };
     tl_lookup_sp:=symtab[tl_lookup_h];
     
     while( return_1=0 AND  tl_lookup_sp)
     {
         if(strcmp(tl_lookup_sp->name,s)=0) then 
         {
             return_1<==1 and RValue:=tl_lookup_sp;
             skip
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             tl_lookup_sp:=tl_lookup_sp->next$
         }
         else
         {
             skip
         }
         
     };
     if(return_1=0)   then 
     {
         tl_lookup_sp:=(Symbol *)(extern tl_emalloc(8,RValue));
         int tl_lookup_temp$_1 and skip;
         tl_lookup_temp$_1:=strlen(s);
         tl_lookup_sp->name:=(char *)(extern tl_emalloc(tl_lookup_temp$_1+1,RValue));
         strcpy(tl_lookup_sp->name,s) and skip;
         tl_lookup_sp->next$:=symtab[tl_lookup_h];
         symtab[tl_lookup_h]:=tl_lookup_sp;
         return_1<==1 and RValue:=tl_lookup_sp;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function getsym ( Symbol *s,Symbol* RValue )
 {
     frame(getsym_n,return_1) and ( 
     int return_1<==0 and skip;
     Symbol *getsym_n and skip;
     getsym_n:=(Symbol *)(extern tl_emalloc(8,RValue));
     getsym_n->name:=s->name;
     return_1<==1 and RValue:=getsym_n;
     skip
     )
     }; 
  function tl_emalloc ( int U,void* RValue )
 {
     frame(tl_emalloc_r,return_1) and ( 
     int return_1<==0 and skip;
     void *tl_emalloc_r and skip;
     tl_emalloc_r<==(void *)malloc(U) and skip;
     memset(tl_emalloc_r,0,U) and skip;
     return_1<==1 and RValue:=tl_emalloc_r;
     skip
     )
     }; 
  function tfree ( void *v )
 {
     frame(tfree_i) and ( 
     int tfree_i<==0 and skip;
	 free(v) and skip
     )
 }; 
  function emalloc_atrans ( ATrans* RValue )
 {
     frame(emalloc_atrans_result,return_1) and ( 
     int return_1<==0 and skip;
     ATrans *emalloc_atrans_result and skip;
     if(!atrans_list) then 
     {
         emalloc_atrans_result:=(ATrans *)(extern tl_emalloc(20,RValue));
         emalloc_atrans_result->pos:=new_set(1,RValue);
         emalloc_atrans_result->neg:=new_set(1,RValue);
         emalloc_atrans_result->to:=new_set(0,RValue);
         apool:=apool+1
         
     }
     else
     {
         emalloc_atrans_result:=atrans_list;
         atrans_list:=atrans_list->nxt;
         emalloc_atrans_result->nxt:=NULL
     };
     aallocs:=aallocs+1;
     return_1<==1 and RValue:=emalloc_atrans_result;
     skip
     )
     }; 
  function free_atrans ( ATrans *t,int rec )
 {
     frame(return_1) and ( 
     int return_1<==0 and skip;
     if(!t) then 
     {
          return_1<==1 and skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         if(rec) then 
         {
             free_atrans(t->nxt,rec)
         }
         else 
         {
              skip 
         };
         t->nxt:=atrans_list;
         atrans_list:=t;
         afrees:=afrees+1
     }
     else
     {
         skip
     }
     )
     }; 
  function free_all_atrans (  )
 {
     frame(free_all_atrans_t) and ( 
     ATrans *free_all_atrans_t and skip;
     while(atrans_list)
     {
         free_all_atrans_t:=atrans_list;
         atrans_list:=free_all_atrans_t->nxt;
         tfree(free_all_atrans_t->to);
         tfree(free_all_atrans_t->pos);
         tfree(free_all_atrans_t->neg);
         tfree(free_all_atrans_t)
     }
     )
     }; 
  function emalloc_gtrans ( GTrans* RValue )
 {
     frame(emalloc_gtrans_result,return_1) and ( 
     int return_1<==0 and skip;
     GTrans *emalloc_gtrans_result and skip;
     if(!gtrans_list) then 
     {
         emalloc_gtrans_result:=(GTrans *)(extern tl_emalloc(20,RValue));
         emalloc_gtrans_result->pos:=new_set(1,RValue);
         emalloc_gtrans_result->neg:=new_set(1,RValue);
         emalloc_gtrans_result->final:=new_set(0,RValue);
         gpool:=gpool+1
         
     }
     else
     {
         emalloc_gtrans_result:=gtrans_list;
         gtrans_list:=gtrans_list->nxt
     };
     gallocs:=gallocs+1;
     return_1<==1 and RValue:=emalloc_gtrans_result;
     skip
     )
     }; 
  function free_gtrans ( GTrans *t,GTrans *sentinel,int fly )
 {
     gfrees:=gfrees+1;
     if(sentinel AND (t!=sentinel)) then 
     {
         free_gtrans(t->nxt,sentinel,fly);
         if(fly) then 
         {
             t->to->incoming:=t->to->incoming-1
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
     t->nxt:=gtrans_list;
     gtrans_list:=t
     
 };
 function emalloc_btrans ( BTrans* RValue )
 {
     frame(emalloc_btrans_result,return_1) and ( 
     int return_1<==0 and skip;
     BTrans *emalloc_btrans_result and skip;
     if(!btrans_list) then 
     {
         emalloc_btrans_result:=(BTrans *)(extern tl_emalloc(16,RValue));
         emalloc_btrans_result->pos:=new_set(1,RValue);
         emalloc_btrans_result->neg:=new_set(1,RValue);
         bpool:=bpool+1
         
     }
     else
     {
         emalloc_btrans_result:=btrans_list;
         btrans_list:=btrans_list->nxt
     };
     ballocs:=ballocs+1;
     return_1<==1 and RValue:=emalloc_btrans_result;
     skip
     )
     }; 
  function free_btrans ( BTrans *t,BTrans *sentinel,int fly )
 {
     bfrees:=bfrees+1;
     if(sentinel AND (t!=sentinel)) then 
     {
         free_btrans(t->nxt,sentinel,fly);
         if(fly) then 
         {
             t->to->incoming:=t->to->incoming-1
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
     t->nxt:=btrans_list;
     btrans_list:=t
     
 };
 function a_stats (  )//yixie
 {
     frame(a_stats_p,a_stats_a,a_stats_f,a_stats_i) and ( 
     int a_stats_p,a_stats_a,a_stats_f and skip;
     int a_stats_i and skip;
     output (" size\t  pool\tallocs\t frees\n") and skip;
     a_stats_i:=0;
     
     while(a_stats_i<80)
     {
         a_stats_p:=event[0,a_stats_i];
         a_stats_a:=event[1,a_stats_i];
         a_stats_f:=event[2,a_stats_i];
         if(a_stats_p | a_stats_a | a_stats_f) then 
         {
             output (a_stats_i,"\t",a_stats_p,"\t",a_stats_a,"\t",a_stats_f,"\n","\n") and skip
         }
         else 
         {
              skip 
         };
         a_stats_i:=a_stats_i+1
         
     };
     output ("atrans\t",apool,"\t",aallocs,"\t",afrees,"\n") and skip;
     output ("gtrans\t",gpool,"\t",gallocs,"\t",gfrees,"\n") and skip;
     output ("btrans\t",bpool,"\t",ballocs,"\t",bfrees,"\n") and skip
     )
     }; 
  function implies ( Node *a,Node *b,int RValue )
 {
     frame(return_1) and ( 
     int return_1<==0 and skip;
     return_1<==1 and RValue:=(extern isequal(a,b,RValue) OR b->ntyp=TRUE OR a->ntyp=FALSE OR (b->ntyp=AND_1 AND extern implies(a,b->lft,RValue) AND extern implies(a,b->rgt,RValue)) OR (a->ntyp=OR_1 AND extern implies(a->lft,b,RValue) AND extern implies(a->rgt,b,RValue)) OR (a->ntyp=AND_1 AND (extern implies(a->lft,b,RValue) OR extern implies(a->rgt,b,RValue))) OR (b->ntyp=OR_1 AND (extern implies(a,b->lft,RValue) OR extern implies(a,b->rgt,RValue))) OR (b->ntyp=U_OPER AND extern  implies(a,b->rgt,RValue)) OR (a->ntyp=V_OPER AND extern implies(a->rgt,b,RValue)) OR (a->ntyp=U_OPER AND extern implies(a->lft,b,RValue) AND extern implies(a->rgt,b,RValue)) OR (b->ntyp=V_OPER AND extern implies(a,b->lft,RValue) AND extern implies(a,b->rgt,RValue)) OR ((a->ntyp=U_OPER OR a->ntyp=V_OPER) AND a->ntyp=b->ntyp AND extern implies(a->lft,b->lft,RValue) AND extern implies(a->rgt,b->rgt,RValue)));
     skip
     )
     }; 
  function bin_simpler ( Node *ptr,Node* RValue )
 {
     frame(bin_simpler_a,bin_simpler_b,nm_10$,break_1$,switch_1,bin_simpler_1_2_8_temp$_1,bin_simpler_1_2_8_temp$_2,bin_simpler_1_2_8_temp$_3,bin_simpler_1_2_14_temp$_4,bin_simpler_1_2_14_temp$_5,bin_simpler_1_2_14_temp$_6,bin_simpler_1_2_temp$_7,bin_simpler_1_2_temp$_8,bin_simpler_1_2_temp$_9,bin_simpler_1_2_temp$_10,bin_simpler_1_2_temp$_11,bin_simpler_1_2_temp$_12,bin_simpler_1_2_temp$_13,bin_simpler_1_2_temp$_14,bin_simpler_1_2_temp$_15,bin_simpler_1_2_temp$_16,bin_simpler_1_2_temp$_17,bin_simpler_1_2_temp$_18,bin_simpler_1_2_temp$_19,bin_simpler_1_2_temp$_20,bin_simpler_1_2_21_temp$_21,bin_simpler_1_2_22_temp$_22,bin_simpler_1_2_26_temp$_23,bin_simpler_1_2_26_temp$_24,bin_simpler_1_2_26_temp$_25,bin_simpler_1_2_26_temp$_26,bin_simpler_1_2_27_temp$_27,bin_simpler_1_2_27_temp$_28,bin_simpler_1_2_27_temp$_29,bin_simpler_1_2_27_temp$_30,bin_simpler_1_2_27_temp$_31,bin_simpler_1_2_27_temp$_32,bin_simpler_1_2_30_temp$_33,bin_simpler_1_2_33_temp$_34,bin_simpler_1_2_35_temp$_35,bin_simpler_1_2_35_temp$_36,bin_simpler_1_2_35_temp$_37,bin_simpler_1_2_35_temp$_38,bin_simpler_1_2_36_temp$_39,bin_simpler_1_2_36_temp$_40,bin_simpler_1_2_36_temp$_41,bin_simpler_1_2_36_temp$_42,bin_simpler_1_2_36_temp$_43,bin_simpler_1_2_36_temp$_44,return_1) and ( 
     int return_1<==0 and skip;
     Node *bin_simpler_a,*bin_simpler_b and skip;
     if(ptr) then 
     {
         int switch_1 and skip;
         int break_1$ and skip;
         break_1$<==0 and skip;
          switch_1<==0 and skip;
          int nm_10$ and skip;
         nm_10$ := ptr->ntyp;
         if (nm_10$=U_OPER OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             if(ptr->rgt->ntyp=TRUE OR ptr->rgt->ntyp=FALSE OR ptr->lft->ntyp=FALSE) then 
             {
                 ptr:=ptr->rgt;
                 break_1$<==1 and skip
                  
             }
             else 
             {
                  skip 
             };
             if(break_1$=0)   then
             {
                 if(extern implies(ptr->lft,ptr->rgt,RValue)) then 
                 {
                     ptr:=ptr->rgt;
                     break_1$<==1 and skip
                      
                 }
                 else 
                 {
                      skip 
                 };
                 if(break_1$=0)   then
                 {
                     if(ptr->lft->ntyp=U_OPER AND (extern isequal(ptr->lft->lft,ptr->rgt,RValue))) then 
                     {
                         ptr->lft:=ptr->lft->rgt;
                         break_1$<==1 and skip
                          
                     }
                     else 
                     {
                          skip 
                     };
                     if(break_1$=0)   then
                     {
                         if(ptr->rgt->ntyp=U_OPER AND (extern implies(ptr->lft,ptr->rgt->lft,RValue))) then 
                         {
                             ptr:=ptr->rgt;
                             break_1$<==1 and skip
                              
                         }
                         else 
                         {
                              skip 
                         };
                         if(break_1$=0)   then
                         {
                             if(ptr->lft->ntyp=TRUE AND ptr->rgt->ntyp=V_OPER AND ptr->rgt->lft->ntyp=FALSE AND ptr->rgt->rgt->ntyp=U_OPER AND ptr->rgt->rgt->lft->ntyp=TRUE) then 
                             {
                                 ptr:=ptr->rgt;
                                 break_1$<==1 and skip
                                  
                             }
                             else 
                             {
                                  skip 
                             };
                             if(break_1$=0)   then
                             {
                                 Node* bin_simpler_1_2_8_temp$_1 and skip;
                                 bin_simpler_1_2_8_temp$_1:=dupnode(ptr->rgt,RValue);
                                 Node* bin_simpler_1_2_8_temp$_2 and skip;
                                 bin_simpler_1_2_8_temp$_2:=tl_nn(NOT,bin_simpler_1_2_8_temp$_1,NULL,RValue);
                                 Node* bin_simpler_1_2_8_temp$_3 and skip;
                                 bin_simpler_1_2_8_temp$_3:=push_negation(bin_simpler_1_2_8_temp$_2,RValue);
                                 if(ptr->lft->ntyp!=TRUE AND (extern implies(bin_simpler_1_2_8_temp$_3,ptr->lft,RValue))) then 
                                 {
                                     ptr->lft:=tl_nn(TRUE,NULL,NULL,RValue);
                                     break_1$<==1 and skip
                                      
                                 }
                                 else 
                                 {
                                      skip 
                                 };
                                 if(break_1$=0)   then
                                 {
                                     break_1$<==1 and skip
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
         if (nm_10$=V_OPER OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             if(ptr->rgt->ntyp=FALSE OR ptr->rgt->ntyp=TRUE OR ptr->lft->ntyp=TRUE) then 
             {
                 ptr:=ptr->rgt;
                 break_1$<==1 and skip
                  
             }
             else 
             {
                  skip 
             };
             if(break_1$=0)   then
             {
                 if(extern implies(ptr->rgt,ptr->lft,RValue)) then 
                 {
                     ptr:=ptr->rgt;
                     break_1$<==1 and skip
                      
                 }
                 else 
                 {
                      skip 
                 };
                 if(break_1$=0)   then
                 {
                     if(ptr->lft->ntyp=FALSE AND ptr->rgt->ntyp=V_OPER) then 
                     {
                         ptr->rgt:=ptr->rgt->rgt;
                         break_1$<==1 and skip
                          
                     }
                     else 
                     {
                          skip 
                     };
                     if(break_1$=0)   then
                     {
                         if(ptr->lft->ntyp=FALSE AND ptr->rgt->ntyp=U_OPER AND ptr->rgt->lft->ntyp=TRUE AND ptr->rgt->rgt->ntyp=V_OPER AND ptr->rgt->rgt->lft->ntyp=FALSE) then 
                         {
                             ptr:=ptr->rgt;
                             break_1$<==1 and skip
                              
                         }
                         else 
                         {
                              skip 
                         };
                         if(break_1$=0)   then
                         {
                             if(ptr->rgt->ntyp=V_OPER AND (extern implies(ptr->rgt->lft,ptr->lft,RValue))) then 
                             {
                                 ptr:=ptr->rgt;
                                 break_1$<==1 and skip
                                  
                             }
                             else 
                             {
                                  skip 
                             };
                             if(break_1$=0)   then
                             {
                                 Node* bin_simpler_1_2_14_temp$_4 and skip;
                                 bin_simpler_1_2_14_temp$_4:=dupnode(ptr->rgt,RValue);
                                 Node* bin_simpler_1_2_14_temp$_5 and skip;
                                 bin_simpler_1_2_14_temp$_5:=tl_nn(NOT,bin_simpler_1_2_14_temp$_4,NULL,RValue);
                                 Node* bin_simpler_1_2_14_temp$_6 and skip;
                                 bin_simpler_1_2_14_temp$_6:=push_negation(bin_simpler_1_2_14_temp$_5,RValue);
                                 if(ptr->lft->ntyp!=FALSE AND (extern implies(ptr->lft,bin_simpler_1_2_14_temp$_6,RValue))) then 
                                 {
                                     ptr->lft:=tl_nn(FALSE,NULL,NULL,RValue);
                                     break_1$<==1 and skip
                                      
                                 }
                                 else 
                                 {
                                      skip 
                                 };
                                 if(break_1$=0)   then
                                 {
                                     break_1$<==1 and skip
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
         if (nm_10$=IMPLIES OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             if((extern implies(ptr->lft,ptr->rgt,RValue))) then 
             {
                 ptr:=tl_nn(TRUE,NULL,NULL,RValue);
                 break_1$<==1 and skip
                  
             }
             else 
             {
                  skip 
             };
             if(break_1$=0)   then
             {
                 Node* bin_simpler_1_2_temp$_7 and skip;
                 bin_simpler_1_2_temp$_7:=tl_nn(NOT,ptr->lft,NULL,RValue);
                 Node* bin_simpler_1_2_temp$_8 and skip;
                 bin_simpler_1_2_temp$_8:=push_negation(bin_simpler_1_2_temp$_7,RValue);
                 ptr:=tl_nn(OR_1,bin_simpler_1_2_temp$_8,ptr->rgt,RValue);
                 Node* bin_simpler_1_2_temp$_9 and skip;
                 bin_simpler_1_2_temp$_9:=right_linked(ptr,RValue);
                 ptr:=canonical(bin_simpler_1_2_temp$_9,RValue);
                 break_1$<==1 and skip
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
         if (nm_10$=EQUIV OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             if((extern implies(ptr->lft,ptr->rgt,RValue)) AND (extern implies(ptr->rgt,ptr->lft,RValue))) then 
             {
                 ptr:=tl_nn(TRUE,NULL,NULL,RValue);
                 break_1$<==1 and skip
                  
             }
             else 
             {
                  skip 
             };
             if(break_1$=0)   then
             {
                 Node* bin_simpler_1_2_temp$_10 and skip;
                 bin_simpler_1_2_temp$_10:=dupnode(ptr->rgt,RValue);
                 Node* bin_simpler_1_2_temp$_11 and skip;
                 bin_simpler_1_2_temp$_11:=dupnode(ptr->lft,RValue);
                 Node* bin_simpler_1_2_temp$_12 and skip;
                 bin_simpler_1_2_temp$_12:=tl_nn(AND_1,bin_simpler_1_2_temp$_11,bin_simpler_1_2_temp$_10,RValue);
                 Node* bin_simpler_1_2_temp$_13 and skip;
                 bin_simpler_1_2_temp$_13:=right_linked(bin_simpler_1_2_temp$_12,RValue);
                 bin_simpler_a:=canonical(bin_simpler_1_2_temp$_13,RValue);
                 Node* bin_simpler_1_2_temp$_14 and skip;
                 bin_simpler_1_2_temp$_14:=tl_nn(NOT,ptr->rgt,NULL,RValue);
                 Node* bin_simpler_1_2_temp$_15 and skip;
                 bin_simpler_1_2_temp$_15:=push_negation(bin_simpler_1_2_temp$_14,RValue);
                 Node* bin_simpler_1_2_temp$_16 and skip;
                 bin_simpler_1_2_temp$_16:=tl_nn(NOT,ptr->lft,NULL,RValue);
                 Node* bin_simpler_1_2_temp$_17 and skip;
                 bin_simpler_1_2_temp$_17:=push_negation(bin_simpler_1_2_temp$_16,RValue);
                 Node* bin_simpler_1_2_temp$_18 and skip;
                 bin_simpler_1_2_temp$_18:=tl_nn(AND_1,bin_simpler_1_2_temp$_17,bin_simpler_1_2_temp$_15,RValue);
                 Node* bin_simpler_1_2_temp$_19 and skip;
                 bin_simpler_1_2_temp$_19:=right_linked(bin_simpler_1_2_temp$_18,RValue);
                 bin_simpler_b:=canonical(bin_simpler_1_2_temp$_19,RValue);
                 ptr:=tl_nn(OR_1,bin_simpler_a,bin_simpler_b,RValue);
                 Node* bin_simpler_1_2_temp$_20 and skip;
                 bin_simpler_1_2_temp$_20:=right_linked(ptr,RValue);
                 ptr:=canonical(bin_simpler_1_2_temp$_20,RValue);
                 break_1$<==1 and skip
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
         if (nm_10$=AND_1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             if(ptr->rgt->ntyp=U_OPER AND (extern isequal(ptr->rgt->rgt,ptr->lft,RValue))) then 
             {
                 ptr:=ptr->lft;
                 break_1$<==1 and skip
                  
             }
             else 
             {
                  skip 
             };
             if(break_1$=0)   then
             {
                 if(ptr->lft->ntyp=U_OPER AND (extern isequal(ptr->lft->rgt,ptr->rgt,RValue))) then 
                 {
                     ptr:=ptr->rgt;
                     break_1$<==1 and skip
                      
                 }
                 else 
                 {
                      skip 
                 };
                 if(break_1$=0)   then
                 {
                     if(ptr->rgt->ntyp=V_OPER AND (extern isequal(ptr->rgt->rgt,ptr->lft,RValue))) then 
                     {
                         ptr:=ptr->rgt;
                         break_1$<==1 and skip
                          
                     }
                     else 
                     {
                          skip 
                     };
                     if(break_1$=0)   then
                     {
                         if(ptr->lft->ntyp=V_OPER AND (extern isequal(ptr->lft->rgt,ptr->rgt,RValue))) then 
                         {
                             ptr:=ptr->lft;
                             break_1$<==1 and skip
                              
                         }
                         else 
                         {
                              skip 
                         };
                         if(break_1$=0)   then
                         {
                             if(ptr->rgt->ntyp=U_OPER AND ptr->lft->ntyp=U_OPER AND (extern isequal(ptr->rgt->rgt,ptr->lft->rgt,RValue))) then 
                             {
                                 Node* bin_simpler_1_2_21_temp$_21 and skip;
                                 bin_simpler_1_2_21_temp$_21:=tl_nn(AND_1,ptr->lft->lft,ptr->rgt->lft,RValue);
                                 ptr:=tl_nn(U_OPER,bin_simpler_1_2_21_temp$_21,ptr->lft->rgt,RValue);
                                 break_1$<==1 and skip
                                  
                             }
                             else 
                             {
                                  skip 
                             };
                             if(break_1$=0)   then
                             {
                                 if(ptr->rgt->ntyp=V_OPER AND ptr->lft->ntyp=V_OPER AND (extern isequal(ptr->rgt->lft,ptr->lft->lft,RValue))) then 
                                 {
                                     Node* bin_simpler_1_2_22_temp$_22 and skip;
                                     bin_simpler_1_2_22_temp$_22:=tl_nn(AND_1,ptr->lft->rgt,ptr->rgt->rgt,RValue);
                                     ptr:=tl_nn(V_OPER,ptr->rgt->lft,bin_simpler_1_2_22_temp$_22,RValue);
                                     break_1$<==1 and skip
                                      
                                 }
                                 else 
                                 {
                                      skip 
                                 };
                                 if(break_1$=0)   then
                                 {
                                     if(ptr->rgt->ntyp=U_OPER AND ptr->lft->ntyp=V_OPER AND (extern isequal(ptr->lft->rgt,ptr->rgt->rgt,RValue))) then 
                                     {
                                         ptr:=ptr->lft;
                                         break_1$<==1 and skip
                                          
                                     }
                                     else 
                                     {
                                          skip 
                                     };
                                     if(break_1$=0)   then
                                     {
                                         if((extern isequal(ptr->lft,ptr->rgt,RValue)) OR ptr->rgt->ntyp=FALSE OR ptr->lft->ntyp=TRUE OR (extern implies(ptr->rgt,ptr->lft,RValue))) then 
                                         {
                                             ptr:=ptr->rgt;
                                             break_1$<==1 and skip
                                              
                                         }
                                         else 
                                         {
                                              skip 
                                         };
                                         if(break_1$=0)   then
                                         {
                                             if(ptr->rgt->ntyp=TRUE OR ptr->lft->ntyp=FALSE OR (extern implies(ptr->lft,ptr->rgt,RValue))) then 
                                             {
                                                 ptr:=ptr->lft;
                                                 break_1$<==1 and skip
                                                  
                                             }
                                             else 
                                             {
                                                  skip 
                                             };
                                             if(break_1$=0)   then
                                             {
                                                 if(ptr->lft->ntyp=U_OPER AND ptr->lft->lft->ntyp=TRUE AND ptr->lft->rgt->ntyp=V_OPER AND ptr->lft->rgt->lft->ntyp=FALSE AND ptr->rgt->ntyp=U_OPER AND ptr->rgt->lft->ntyp=TRUE AND ptr->rgt->rgt->ntyp=V_OPER AND ptr->rgt->rgt->lft->ntyp=FALSE) then 
                                                 {
                                                     Node* bin_simpler_1_2_26_temp$_23 and skip;
                                                     bin_simpler_1_2_26_temp$_23:=tl_nn(AND_1,ptr->lft->rgt->rgt,ptr->rgt->rgt->rgt,RValue);
                                                     Node* bin_simpler_1_2_26_temp$_24 and skip;
                                                     bin_simpler_1_2_26_temp$_24:=tl_nn(FALSE,NULL,NULL,RValue);
                                                     Node* bin_simpler_1_2_26_temp$_25 and skip;
                                                     bin_simpler_1_2_26_temp$_25:=tl_nn(V_OPER,bin_simpler_1_2_26_temp$_24,bin_simpler_1_2_26_temp$_23,RValue);
                                                     Node* bin_simpler_1_2_26_temp$_26 and skip;
                                                     bin_simpler_1_2_26_temp$_26:=tl_nn(TRUE,NULL,NULL,RValue);
                                                     ptr:=tl_nn(U_OPER,bin_simpler_1_2_26_temp$_26,bin_simpler_1_2_26_temp$_25,RValue);
                                                     break_1$<==1 and skip
                                                      
                                                 }
                                                 else 
                                                 {
                                                      skip 
                                                 };
                                                 if(break_1$=0)   then
                                                 {
                                                     Node* bin_simpler_1_2_27_temp$_27 and skip;
                                                     bin_simpler_1_2_27_temp$_27:=dupnode(ptr->lft,RValue);
                                                     Node* bin_simpler_1_2_27_temp$_28 and skip;
                                                     bin_simpler_1_2_27_temp$_28:=tl_nn(NOT,bin_simpler_1_2_27_temp$_27,NULL,RValue);
                                                     Node* bin_simpler_1_2_27_temp$_29 and skip;
                                                     bin_simpler_1_2_27_temp$_29:=push_negation(bin_simpler_1_2_27_temp$_28,RValue);
                                                     Node* bin_simpler_1_2_27_temp$_30 and skip;
                                                     bin_simpler_1_2_27_temp$_30:=dupnode(ptr->rgt,RValue);
                                                     Node* bin_simpler_1_2_27_temp$_31 and skip;
                                                     bin_simpler_1_2_27_temp$_31:=tl_nn(NOT,bin_simpler_1_2_27_temp$_30,NULL,RValue);
                                                     Node* bin_simpler_1_2_27_temp$_32 and skip;
                                                     bin_simpler_1_2_27_temp$_32:=push_negation(bin_simpler_1_2_27_temp$_31,RValue);
                                                     if((extern implies(ptr->lft,bin_simpler_1_2_27_temp$_32,RValue)) OR (extern implies(ptr->rgt,bin_simpler_1_2_27_temp$_29,RValue))) then 
                                                     {
                                                         ptr:=tl_nn(FALSE,NULL,NULL,RValue);
                                                         break_1$<==1 and skip
                                                          
                                                     }
                                                     else 
                                                     {
                                                          skip 
                                                     };
                                                     if(break_1$=0)   then
                                                     {
                                                         break_1$<==1 and skip
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
         if (nm_10$=OR_1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             if(ptr->rgt->ntyp=U_OPER AND (extern isequal(ptr->rgt->rgt,ptr->lft,RValue))) then 
             {
                 ptr:=ptr->rgt;
                 break_1$<==1 and skip
                  
             }
             else 
             {
                  skip 
             };
             if(break_1$=0)   then
             {
                 if(ptr->rgt->ntyp=V_OPER AND (extern isequal(ptr->rgt->rgt,ptr->lft,RValue))) then 
                 {
                     ptr:=ptr->lft;
                     break_1$<==1 and skip
                      
                 }
                 else 
                 {
                      skip 
                 };
                 if(break_1$=0)   then
                 {
                     if(ptr->rgt->ntyp=U_OPER AND ptr->lft->ntyp=U_OPER AND (extern isequal(ptr->rgt->lft,ptr->lft->lft,RValue))) then 
                     {
                         Node* bin_simpler_1_2_30_temp$_33 and skip;
                         bin_simpler_1_2_30_temp$_33:=tl_nn(OR_1,ptr->lft->rgt,ptr->rgt->rgt,RValue);
                         ptr:=tl_nn(U_OPER,ptr->rgt->lft,bin_simpler_1_2_30_temp$_33,RValue);
                         break_1$<==1 and skip
                          
                     }
                     else 
                     {
                          skip 
                     };
                     if(break_1$=0)   then
                     {
                         if((extern isequal(ptr->lft,ptr->rgt,RValue)) OR ptr->rgt->ntyp=FALSE OR ptr->lft->ntyp=TRUE OR (extern implies(ptr->rgt,ptr->lft,RValue))) then 
                         {
                             ptr:=ptr->lft;
                             break_1$<==1 and skip
                              
                         }
                         else 
                         {
                              skip 
                         };
                         if(break_1$=0)   then
                         {
                             if(ptr->rgt->ntyp=TRUE OR ptr->lft->ntyp=FALSE OR (extern implies(ptr->lft,ptr->rgt,RValue))) then 
                             {
                                 ptr:=ptr->rgt;
                                 break_1$<==1 and skip
                                  
                             }
                             else 
                             {
                                  skip 
                             };
                             if(break_1$=0)   then
                             {
                                 if(ptr->rgt->ntyp=V_OPER AND ptr->lft->ntyp=V_OPER AND (extern isequal(ptr->lft->rgt,ptr->rgt->rgt,RValue))) then 
                                 {
                                     Node* bin_simpler_1_2_33_temp$_34 and skip;
                                     bin_simpler_1_2_33_temp$_34:=tl_nn(OR_1,ptr->lft->lft,ptr->rgt->lft,RValue);
                                     ptr:=tl_nn(V_OPER,bin_simpler_1_2_33_temp$_34,ptr->rgt->rgt,RValue);
                                     break_1$<==1 and skip
                                      
                                 }
                                 else 
                                 {
                                      skip 
                                 };
                                 if(break_1$=0)   then
                                 {
                                     if(ptr->rgt->ntyp=U_OPER AND ptr->lft->ntyp=V_OPER AND (extern isequal(ptr->lft->rgt,ptr->rgt->rgt,RValue))) then 
                                     {
                                         ptr:=ptr->rgt;
                                         break_1$<==1 and skip
                                          
                                     }
                                     else 
                                     {
                                          skip 
                                     };
                                     if(break_1$=0)   then
                                     {
                                         if(ptr->lft->ntyp=V_OPER AND ptr->lft->lft->ntyp=FALSE AND ptr->lft->rgt->ntyp=U_OPER AND ptr->lft->rgt->lft->ntyp=TRUE AND ptr->rgt->ntyp=V_OPER AND ptr->rgt->lft->ntyp=FALSE AND ptr->rgt->rgt->ntyp=U_OPER AND ptr->rgt->rgt->lft->ntyp=TRUE) then 
                                         {
                                             Node* bin_simpler_1_2_35_temp$_35 and skip;
                                             bin_simpler_1_2_35_temp$_35:=tl_nn(OR_1,ptr->lft->rgt->rgt,ptr->rgt->rgt->rgt,RValue);
                                             Node* bin_simpler_1_2_35_temp$_36 and skip;
                                             bin_simpler_1_2_35_temp$_36:=tl_nn(TRUE,NULL,NULL,RValue);
                                             Node* bin_simpler_1_2_35_temp$_37 and skip;
                                             bin_simpler_1_2_35_temp$_37:=tl_nn(U_OPER,bin_simpler_1_2_35_temp$_36,bin_simpler_1_2_35_temp$_35,RValue);
                                             Node* bin_simpler_1_2_35_temp$_38 and skip;
                                             bin_simpler_1_2_35_temp$_38:=tl_nn(FALSE,NULL,NULL,RValue);
                                             ptr:=tl_nn(V_OPER,bin_simpler_1_2_35_temp$_38,bin_simpler_1_2_35_temp$_37,RValue);
                                             break_1$<==1 and skip
                                              
                                         }
                                         else 
                                         {
                                              skip 
                                         };
                                         if(break_1$=0)   then
                                         {
                                             Node* bin_simpler_1_2_36_temp$_39 and skip;
                                             bin_simpler_1_2_36_temp$_39:=dupnode(ptr->lft,RValue);
                                             Node* bin_simpler_1_2_36_temp$_40 and skip;
                                             bin_simpler_1_2_36_temp$_40:=tl_nn(NOT,bin_simpler_1_2_36_temp$_39,NULL,RValue);
                                             Node* bin_simpler_1_2_36_temp$_41 and skip;
                                             bin_simpler_1_2_36_temp$_41:=push_negation(bin_simpler_1_2_36_temp$_40,RValue);
                                             Node* bin_simpler_1_2_36_temp$_42 and skip;
                                             bin_simpler_1_2_36_temp$_42:=dupnode(ptr->rgt,RValue);
                                             Node* bin_simpler_1_2_36_temp$_43 and skip;
                                             bin_simpler_1_2_36_temp$_43:=tl_nn(NOT,bin_simpler_1_2_36_temp$_42,NULL,RValue);
                                             Node* bin_simpler_1_2_36_temp$_44 and skip;
                                             bin_simpler_1_2_36_temp$_44:=push_negation(bin_simpler_1_2_36_temp$_43,RValue);
                                             if((extern implies(bin_simpler_1_2_36_temp$_44,ptr->lft,RValue)) OR (extern implies(bin_simpler_1_2_36_temp$_41,ptr->rgt,RValue))) then 
                                             {
                                                 ptr:=tl_nn(TRUE,NULL,NULL,RValue);
                                                 break_1$<==1 and skip
                                                  
                                             }
                                             else 
                                             {
                                                  skip 
                                             };
                                             if(break_1$=0)   then
                                             {
                                                 break_1$<==1 and skip
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
             }}
             else 
             {
                  skip 
             };
             return_1<==1 and RValue:=ptr;
             skip
             )
             }; 
  function bin_minimal ( Node *ptr,Node* RValue )
 {
     frame(nm_11$,break_1$,switch_1,bin_minimal_1_2_temp$_1,bin_minimal_1_2_temp$_2,bin_minimal_1_2_temp$_3,bin_minimal_1_2_temp$_4,bin_minimal_1_2_temp$_5,bin_minimal_1_2_temp$_6,bin_minimal_1_2_temp$_7,bin_minimal_1_2_temp$_8,bin_minimal_1_2_temp$_9,bin_minimal_1_2_temp$_10,return_1) and ( 
     int return_1<==0 and skip;
     if(ptr) then 
     {
         int switch_1 and skip;
         int break_1$ and skip;
         break_1$<==0 and skip;
          switch_1<==0 and skip;
          int nm_11$ and skip;
         nm_11$ := ptr->ntyp;
         if (nm_11$=IMPLIES OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             Node* bin_minimal_1_2_temp$_1 and skip;
             bin_minimal_1_2_temp$_1:=tl_nn(NOT,ptr->lft,NULL,RValue);
             Node* bin_minimal_1_2_temp$_2 and skip;
             bin_minimal_1_2_temp$_2:=push_negation(bin_minimal_1_2_temp$_1,RValue);
             return_1<==1 and RValue:=tl_nn(OR_1,bin_minimal_1_2_temp$_2,ptr->rgt,RValue);
             skip
             
         }
         else
         {
             skip
         };
         if (nm_11$=EQUIV OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             Node* bin_minimal_1_2_temp$_3 and skip;
             bin_minimal_1_2_temp$_3:=tl_nn(NOT,ptr->rgt,NULL,RValue);
             Node* bin_minimal_1_2_temp$_4 and skip;
             bin_minimal_1_2_temp$_4:=push_negation(bin_minimal_1_2_temp$_3,RValue);
             Node* bin_minimal_1_2_temp$_5 and skip;
             bin_minimal_1_2_temp$_5:=tl_nn(NOT,ptr->lft,NULL,RValue);
             Node* bin_minimal_1_2_temp$_6 and skip;
             bin_minimal_1_2_temp$_6:=push_negation(bin_minimal_1_2_temp$_5,RValue);
             Node* bin_minimal_1_2_temp$_7 and skip;
             bin_minimal_1_2_temp$_7:=tl_nn(AND_1,bin_minimal_1_2_temp$_6,bin_minimal_1_2_temp$_4,RValue);
             Node* bin_minimal_1_2_temp$_8 and skip;
             bin_minimal_1_2_temp$_8:=dupnode(ptr->rgt,RValue);
             Node* bin_minimal_1_2_temp$_9 and skip;
             bin_minimal_1_2_temp$_9:=dupnode(ptr->lft,RValue);
             Node* bin_minimal_1_2_temp$_10 and skip;
             bin_minimal_1_2_temp$_10:=tl_nn(AND_1,bin_minimal_1_2_temp$_9,bin_minimal_1_2_temp$_8,RValue);
             return_1<==1 and RValue:=tl_nn(OR_1,bin_minimal_1_2_temp$_10,bin_minimal_1_2_temp$_7,RValue);
             skip
             
         }
         else
         {
             skip
             }}
             else 
             {
                  skip 
             };
             if(return_1=0)   then 
             {
                 return_1<==1 and RValue:=ptr;
                 skip
             }
             else
             {
                 skip
             }
             )
             }; 
  function tl_factor ( Node* RValue )
 {
     frame(tl_factor_ptr,nm_12$,break_1$,switch_1,tl_factor_1_temp$_1,tl_factor_1_temp$_2,return_1) and ( 
     int return_1<==0 and skip;
     Node *tl_factor_ptr<==NULL and skip;
     int switch_1 and skip;
     int break_1$ and skip;
     break_1$<==0 and skip;
      switch_1<==0 and skip;
      int nm_12$ and skip;
     nm_12$ := tl_yychar;
     if (nm_12$='(' OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         tl_factor_ptr:=tl_formula(RValue);
         if(tl_yychar!=')') then 
         {
             tl_yyerror("expected ')'")
         }
         else 
         {
              skip 
         };
         tl_yychar:=tl_yylex(RValue);
         if(tl_simp_log) then 
         {
             tl_factor_ptr:=bin_simpler(tl_factor_ptr,RValue)
         }
         else 
         {
              skip 
         };
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_12$=NOT OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         tl_factor_ptr:=tl_yylval;
         tl_yychar:=tl_yylex(RValue);
         tl_factor_ptr->lft:=tl_factor(RValue);
         tl_factor_ptr:=push_negation(tl_factor_ptr,RValue);
         if(tl_simp_log) then 
         {
             tl_factor_ptr:=bin_simpler(tl_factor_ptr,RValue)
         }
         else 
         {
              skip 
         };
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_12$=ALWAYS OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         tl_yychar:=tl_yylex(RValue);
         tl_factor_ptr:=tl_factor(RValue);
         if(tl_simp_log) then 
         {
             if(tl_factor_ptr->ntyp=FALSE OR tl_factor_ptr->ntyp=TRUE) then 
             {
                 break_1$<==1 and skip
              }
             else 
             {
                  skip 
             };
             if(break_1$=0)   then
             {
                 if(tl_factor_ptr->ntyp=V_OPER) then 
                 {
                     if(tl_factor_ptr->lft->ntyp=FALSE) then 
                     {
                         break_1$<==1 and skip
                      }
                     else 
                     {
                          skip 
                     };
                     if(break_1$=0)   then
                     {
                         tl_factor_ptr:=tl_factor_ptr->rgt
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
         if(break_1$=0)   then 
         {
             Node* tl_factor_1_temp$_1 and skip;
             tl_factor_1_temp$_1:=tl_nn(FALSE,NULL,NULL,RValue);
             tl_factor_ptr:=tl_nn(V_OPER,tl_factor_1_temp$_1,tl_factor_ptr,RValue);
             if(tl_simp_log) then 
             {
                 tl_factor_ptr:=bin_simpler(tl_factor_ptr,RValue)
             }
             else 
             {
                  skip 
             };
             break_1$<==1 and skip
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
     if (nm_12$=EVENTUALLY OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         tl_yychar:=tl_yylex(RValue);
         tl_factor_ptr:=tl_factor(RValue);
         if(tl_simp_log) then 
         {
             if(tl_factor_ptr->ntyp=TRUE OR tl_factor_ptr->ntyp=FALSE) then 
             {
                 break_1$<==1 and skip
              }
             else 
             {
                  skip 
             };
             if(break_1$=0)   then
             {
                 if(tl_factor_ptr->ntyp=U_OPER AND tl_factor_ptr->lft->ntyp=TRUE) then 
                 {
                     break_1$<==1 and skip
                  }
                 else 
                 {
                      skip 
                 };
                 if(break_1$=0)   then
                 {
                     if(tl_factor_ptr->ntyp=U_OPER) then 
                     {
                         tl_factor_ptr:=tl_factor_ptr->rgt
                         
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
         if(break_1$=0)   then 
         {
             Node* tl_factor_1_temp$_2 and skip;
             tl_factor_1_temp$_2:=tl_nn(TRUE,NULL,NULL,RValue);
             tl_factor_ptr:=tl_nn(U_OPER,tl_factor_1_temp$_2,tl_factor_ptr,RValue);
             if(tl_simp_log) then 
             {
                 tl_factor_ptr:=bin_simpler(tl_factor_ptr,RValue)
             }
             else 
             {
                  skip 
             };
             break_1$<==1 and skip
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
     if (nm_12$=PREDICATE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         tl_factor_ptr:=tl_yylval;
         tl_yychar:=tl_yylex(RValue);
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_12$=TRUE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip
         
     }
     else
     {
         skip
     };
     if (nm_12$=FALSE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         tl_factor_ptr:=tl_yylval;
         tl_yychar:=tl_yylex(RValue);
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if(!tl_factor_ptr) then 
     {
         tl_yyerror("expected predicate")
     }
     else 
     {
          skip 
     };
     return_1<==1 and RValue:=tl_factor_ptr;
     skip
     )
     }; 
  function tl_level ( int nr,Node* RValue )
 {
     frame(tl_level_i,tl_level_ptr,tl_level_2_3_temp$_1,return_1) and ( 
     int return_1<==0 and skip;
     int tl_level_i and skip;
     Node *tl_level_ptr<==NULL and skip;
     if(nr<0) then 
     {
         return_1<==1 and RValue:=tl_factor(RValue);
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         tl_level_ptr:=tl_level(nr-1,RValue);
         tl_level_i:=0;
         
         while(tl_level_i<4)
         {
             if(tl_yychar=prec[nr,tl_level_i]) then 
             {
                 tl_yychar:=tl_yylex(RValue);
                 Node* tl_level_2_3_temp$_1 and skip;
                 tl_level_2_3_temp$_1:=tl_level(nr-1,RValue);
                 tl_level_ptr:=tl_nn(prec[nr,tl_level_i],tl_level_ptr,tl_level_2_3_temp$_1,RValue);
                 if(tl_simp_log) then 
                 {
                     tl_level_ptr:=bin_simpler(tl_level_ptr,RValue)
                 }
                 else
                 {
                     tl_level_ptr:=bin_minimal(tl_level_ptr,RValue)
                 };
                 tl_level_i:=-1
                 
             }
             else 
             {
                  skip 
             };
             tl_level_i:=tl_level_i+1
             
         };
         if(!tl_level_ptr) then 
         {
             tl_yyerror("syntax error")
         }
         else 
         {
              skip 
         };
         return_1<==1 and RValue:=tl_level_ptr;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function tl_formula ( Node* RValue )///yixie
 {
     frame(return_1) and ( 
	 module_4<==1 and skip;
     int return_1<==0 and skip;
     tl_yychar:=tl_yylex(RValue);
     return_1<==1 and RValue:=tl_level(1,RValue);
     skip
     )
     }; 
  function tl_parse (  )///yixie
 {
     frame(tl_parse_n) and ( 
	 module_3<==1 and skip;
     Node *tl_parse_n and skip;
     tl_parse_n:=tl_formula(RValue);
     if(tl_verbose) then 
     {
         output ("formula: ") and skip;
         put_uform();
         output ("\n") and skip
         
     }
     else 
     {
          skip 
     };
     trans(tl_parse_n)
     )
     }; 
  function right_linked ( Node *n,Node* RValue )
 {
     frame(right_linked_2_3_tmp,return_1) and ( 
     int return_1<==0 and skip;
     if(!n) then 
     {
         return_1<==1 and RValue:=n;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         if(n->ntyp=AND_1 OR n->ntyp=OR_1) then 
         {
             while(n->lft AND n->lft->ntyp=n->ntyp)
             {
                 Node *right_linked_2_3_tmp<==n->lft and skip;
                 n->lft:=right_linked_2_3_tmp->rgt;
                 right_linked_2_3_tmp->rgt:=n;
                 n:=right_linked_2_3_tmp
             }
         }
         else 
         {
              skip 
         };
         n->lft:=right_linked(n->lft,RValue);
         n->rgt:=right_linked(n->rgt,RValue);
         return_1<==1 and RValue:=n;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function canonical ( Node *n,Node* RValue )
 {
     frame(canonical_m,return_1) and ( 
     int return_1<==0 and skip;
     Node *canonical_m and skip;
     if(!n) then 
     {
         return_1<==1 and RValue:=n;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         canonical_m:=in_cache(n,RValue) ;
         if(canonical_m) then 
         {
             return_1<==1 and RValue:=canonical_m;
             skip
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             n->rgt:=canonical(n->rgt,RValue);
             n->lft:=canonical(n->lft,RValue);
             return_1<==1 and RValue:=cached(n,RValue);
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
  function push_negation ( Node *n,Node* RValue )
 {
     frame(push_negation_m,nm_13$,break_1$,switch_1,push_negation_2_temp$_1,push_negation_2_temp$_2,push_negation_2_temp$_3,push_negation_2_temp$_4,push_negation_temp$_5,return_1) and ( 
     int return_1<==0 and skip;
     Node *push_negation_m and skip;
     if(!(n->ntyp=NOT)) then 
     {
         tl_explain(n->ntyp);
         Fatal(": assertion failed\n",NULL)
         
     }
     else 
     {
          skip 
     };
     int switch_1 and skip;
     int break_1$ and skip;
     break_1$<==0 and skip;
      switch_1<==0 and skip;
      int nm_13$ and skip;
     nm_13$ := n->lft->ntyp;
     if (nm_13$=TRUE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         releasenode(0,n->lft);
         n->lft:=NULL;
         n->ntyp:=FALSE;
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_13$=FALSE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         releasenode(0,n->lft);
         n->lft:=NULL;
         n->ntyp:=TRUE;
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_13$=NOT OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         push_negation_m:=n->lft->lft;
         releasenode(0,n->lft);
         n->lft:=NULL;
         releasenode(0,n);
         n:=push_negation_m;
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_13$=V_OPER OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         n->ntyp:=U_OPER;
         push_negation_m:=n->lft->rgt;
         n->lft->rgt:=NULL;
         Node* push_negation_2_temp$_1 and skip;
         push_negation_2_temp$_1:=tl_nn(NOT,push_negation_m,NULL,RValue);
         n->rgt:=push_negation(push_negation_2_temp$_1,RValue);
         n->lft->ntyp:=NOT;
         push_negation_m:=n->lft;
         n->lft:=push_negation(push_negation_m,RValue);
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_13$=U_OPER OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         n->ntyp:=V_OPER;
         push_negation_m:=n->lft->rgt;
         n->lft->rgt:=NULL;
         Node* push_negation_2_temp$_2 and skip;
         push_negation_2_temp$_2:=tl_nn(NOT,push_negation_m,NULL,RValue);
         n->rgt:=push_negation(push_negation_2_temp$_2,RValue);
         n->lft->ntyp:=NOT;
         push_negation_m:=n->lft;
         n->lft:=push_negation(push_negation_m,RValue);
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_13$=AND_1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         n->ntyp:=OR_1;
         push_negation_m:=n->lft->rgt;
         n->lft->rgt:=NULL;
         Node* push_negation_2_temp$_3 and skip;
         push_negation_2_temp$_3:=tl_nn(NOT,push_negation_m,NULL,RValue);
         n->rgt:=push_negation(push_negation_2_temp$_3,RValue);
         n->lft->ntyp:=NOT;
         push_negation_m:=n->lft;
         n->lft:=push_negation(push_negation_m,RValue);
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_13$=OR_1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         n->ntyp:=AND_1;
         push_negation_m:=n->lft->rgt;
         n->lft->rgt:=NULL;
         Node* push_negation_2_temp$_4 and skip;
         push_negation_2_temp$_4:=tl_nn(NOT,push_negation_m,NULL,RValue);
         n->rgt:=push_negation(push_negation_2_temp$_4,RValue);
         n->lft->ntyp:=NOT;
         push_negation_m:=n->lft;
         n->lft:=push_negation(push_negation_m,RValue);
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     Node* push_negation_temp$_5 and skip;
     push_negation_temp$_5:=right_linked(n,RValue);
     return_1<==1 and RValue:=canonical(push_negation_temp$_5,RValue);
     skip
     )
     }; 
  function addcan ( int tok,Node *n )
 {
     frame(addcan_m,addcan_prev,addcan_ptr,addcan_N,addcan_s,addcan_t,addcan_cmp,return_1,goto_1) and ( 
     int goto_1<==0 and skip;
     int return_1<==0 and skip;
     Node *addcan_m,*addcan_prev<==NULL and skip;
     Node **addcan_ptr and skip;
     Node *addcan_N and skip;
     Symbol *addcan_s,*addcan_t and skip;
     int addcan_cmp and skip;
     if(!n) then 
     {
          return_1<==1 and skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         if(n->ntyp=tok) then 
         {
             addcan(tok,n->rgt);
             addcan(tok,n->lft);
              return_1<==1 and skip
             
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             addcan_N:=dupnode(n,RValue);
             if(!can) then 
             {
                 can:=addcan_N;
                  return_1<==1 and skip
                 
             }
             else 
             {
                  skip 
             };
             if(return_1=0)   then 
             {
                 addcan_s:=DoDump(addcan_N,RValue);
                 if(can->ntyp!=tok) then 
                 {
                     addcan_ptr:=&can;
                     goto_1<==1 and skip
                     
                 }
                 else 
                 {
                      skip 
                 };
                 if(goto_1=0)   then 
                 {
                     addcan_prev:=NULL;
                     addcan_m:=can;
                     
                     while( return_1=0 AND  addcan_m->ntyp=tok AND addcan_m->rgt)
                     {
                         addcan_t:=DoDump(addcan_m->lft,RValue);
                         addcan_cmp:=strcmp(addcan_s->name,addcan_t->name);
                         if(addcan_cmp=0) then 
                         {
                              return_1<==1 and skip
                         }
                         else 
                         {
                              skip 
                         };
                         if(return_1=0)   then 
                         {
                             if(addcan_cmp<0) then 
                             {
                                 if(!addcan_prev) then 
                                 {
                                     can:=tl_nn(tok,addcan_N,can,RValue);
                                      return_1<==1 and skip
                                 }
                                 else
                                 {
                                     addcan_ptr:=&(addcan_prev->rgt);
                                     goto_1<==1 and skip
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
                         if(return_1=0)  then
                         {
                             if(goto_1=0)   then 
                             {
                                 addcan_prev:=addcan_m and addcan_m:=addcan_m->rgt
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
                     if(return_1=0)   then 
                     {
                         if(goto_1=0)   then 
                         {
                             addcan_ptr:=&(addcan_prev->rgt)
                             
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
     if(return_1=0)  then
     {
         addcan_t:=DoDump(* addcan_ptr,RValue);
         addcan_cmp:=strcmp(addcan_s->name,addcan_t->name);
         if(addcan_cmp=0) then 
         {
              return_1<==1 and skip
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             if(addcan_cmp<0) then 
             {
                 * addcan_ptr:=tl_nn(tok,addcan_N,* addcan_ptr,RValue)
             }
             else
             {
                 * addcan_ptr:=tl_nn(tok,* addcan_ptr,addcan_N,RValue)
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
  function marknode ( int tok,Node *m )
 {
     if(m->ntyp!=tok) then 
     {
         releasenode(0,m->rgt);
         m->rgt:=NULL
         
     }
     else 
     {
          skip 
     };
     m->ntyp:=-1
     
 };
 function Canonical ( Node *n,Node* RValue )
 {
     frame(Canonical_m,Canonical_p,Canonical_k1,Canonical_k2,Canonical_prev,Canonical_dflt,Canonical_tok,return_1,goto_1,continue_1) and ( 
     int continue_1<==0 and skip;
     int goto_1<==0 and skip;
     int return_1<==0 and skip;
     Node *Canonical_m,*Canonical_p,*Canonical_k1,*Canonical_k2,*Canonical_prev,*Canonical_dflt<==NULL and skip;
     int Canonical_tok and skip;
     if(!n) then 
     {
         return_1<==1 and RValue:=n;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         Canonical_tok:=n->ntyp;
         if(Canonical_tok!=AND_1 AND Canonical_tok!=OR_1) then 
         {
             return_1<==1 and RValue:=n;
             skip
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             can:=NULL;
             addcan(Canonical_tok,n);
             if(0) then 
             {
                 output ("\nA0: ") and skip
             }
             else 
             {
                  skip 
             };
             if(0) then 
             {
                 dump(can)
             }
             else 
             {
                  skip 
             };
             if(0) then 
             {
                 output ("\nA1: ") and skip
             }
             else 
             {
                  skip 
             };
             if(0) then 
             {
                 dump(n)
             }
             else 
             {
                  skip 
             };
             if(0) then 
             {
                 output ("\n") and skip
             }
             else 
             {
                  skip 
             };
             releasenode(1,n);
             if(Canonical_tok=AND_1) then 
             {
                 continue_1<==0 and skip;
                 Canonical_m:=can;
                 
                 while(Canonical_m)
                 {
                      continue_1<==0 and skip;
                     Canonical_k1:=( if((Canonical_m->ntyp=AND_1)) then Canonical_m->lft else Canonical_m);
                     if(Canonical_k1->ntyp=TRUE) then 
                     {
                         marknode(AND_1,Canonical_m);
                         Canonical_dflt:=tl_nn(TRUE,NULL,NULL,RValue);
                         continue_1<==1 and skip;
                          Canonical_m:=( if((Canonical_m->ntyp=AND_1)) then Canonical_m->rgt else NULL)
                     }
                     else 
                     {
                          skip 
                     };
                     if(continue_1=0)   then 
                     {
                         if(Canonical_k1->ntyp=FALSE) then 
                         {
                             releasenode(1,can);
                             can:=tl_nn(FALSE,NULL,NULL,RValue);
                             goto_1<==1 and skip
                             
                         }
                         else 
                         {
                              skip 
                         };
                         if(goto_1=0)   then 
                         {
                             Canonical_m:=( if((Canonical_m->ntyp=AND_1)) then Canonical_m->rgt else NULL)
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
                 continue_1<==0 and skip;
                 if(goto_1=0)   then 
                 {
                     Canonical_m:=can;
                     
                     while(Canonical_m)
                     {
                         continue_1<==0 and skip;
                         Canonical_p:=can;
                         
                         while(Canonical_p)
                         {
                              continue_1<==0 and skip;
                             if(Canonical_p=Canonical_m OR Canonical_p->ntyp=-1 OR Canonical_m->ntyp=-1) then 
                             {
                                 continue_1<==1 and skip;
                                  Canonical_p:=( if((Canonical_p->ntyp=AND_1)) then Canonical_p->rgt else NULL)}
                                 else 
                                 {
                                      skip 
                                 };
                                 if(continue_1=0)   then 
                                 {
                                     Canonical_k1:=( if((Canonical_m->ntyp=AND_1)) then Canonical_m->lft else Canonical_m);
                                     Canonical_k2:=( if((Canonical_p->ntyp=AND_1)) then Canonical_p->lft else Canonical_p);
                                     if(extern isequal(Canonical_k1,Canonical_k2,RValue)) then 
                                     {
                                         marknode(AND_1,Canonical_p);
                                         continue_1<==1 and skip;
                                          Canonical_p:=( if((Canonical_p->ntyp=AND_1)) then Canonical_p->rgt else NULL)
                                     }
                                     else 
                                     {
                                          skip 
                                     };
                                     if(continue_1=0)   then 
                                     {
                                         if(extern anywhere(OR_1,Canonical_k1,Canonical_k2,RValue)) then 
                                         {
                                             marknode(AND_1,Canonical_p);
                                             continue_1<==1 and skip;
                                              Canonical_p:=( if((Canonical_p->ntyp=AND_1)) then Canonical_p->rgt else NULL)
                                         }
                                         else 
                                         {
                                              skip 
                                         };
                                         if(continue_1=0)   then 
                                         {
                                             if(Canonical_k2->ntyp=U_OPER AND (extern anywhere(AND_1,Canonical_k2->rgt,can,RValue))) then 
                                             {
                                                 marknode(AND_1,Canonical_p);
                                                 continue_1<==1 and skip;
                                                  Canonical_p:=( if((Canonical_p->ntyp=AND_1)) then Canonical_p->rgt else NULL)
                                             }
                                             else 
                                             {
                                                  skip 
                                             };
                                             if(continue_1=0)   then 
                                             {
                                                 Canonical_p:=( if((Canonical_p->ntyp=AND_1)) then Canonical_p->rgt else NULL)
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
                             continue_1<==0 and skip;
                             Canonical_m:=( if((Canonical_m->ntyp=AND_1)) then Canonical_m->rgt else NULL)
                             
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
                 if(goto_1=0)   then 
                 {
                     if(Canonical_tok=OR_1) then 
                     {
                         continue_1<==0 and skip;
                         Canonical_m:=can;
                         
                         while(Canonical_m)
                         {
                              continue_1<==0 and skip;
                             Canonical_k1:=( if((Canonical_m->ntyp=OR_1)) then Canonical_m->lft else Canonical_m);
                             if(Canonical_k1->ntyp=FALSE) then 
                             {
                                 marknode(OR_1,Canonical_m);
                                 Canonical_dflt:=tl_nn(FALSE,NULL,NULL,RValue);
                                 continue_1<==1 and skip;
                                  Canonical_m:=( if((Canonical_m->ntyp=OR_1)) then Canonical_m->rgt else NULL)
                             }
                             else 
                             {
                                  skip 
                             };
                             if(continue_1=0)   then 
                             {
                                 if(Canonical_k1->ntyp=TRUE) then 
                                 {
                                     releasenode(1,can);
                                     can:=tl_nn(TRUE,NULL,NULL,RValue);
                                     goto_1<==1 and skip
                                     
                                 }
                                 else 
                                 {
                                      skip 
                                 };
                                 if(goto_1=0)   then 
                                 {
                                     Canonical_m:=( if((Canonical_m->ntyp=OR_1)) then Canonical_m->rgt else NULL)
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
                         continue_1<==0 and skip;
                         if(goto_1=0)   then 
                         {
                             Canonical_m:=can;
                             
                             while(Canonical_m)
                             {
                                 continue_1<==0 and skip;
                                 Canonical_p:=can;
                                 
                                 while(Canonical_p)
                                 {
                                      continue_1<==0 and skip;
                                     if(Canonical_p=Canonical_m OR Canonical_p->ntyp=-1 OR Canonical_m->ntyp=-1) then 
                                     {
                                         continue_1<==1 and skip;
                                          Canonical_p:=( if((Canonical_p->ntyp=OR_1)) then Canonical_p->rgt else NULL)}
                                         else 
                                         {
                                              skip 
                                         };
                                         if(continue_1=0)   then 
                                         {
                                             Canonical_k1:=( if((Canonical_m->ntyp=OR_1)) then Canonical_m->lft else Canonical_m);
                                             Canonical_k2:=( if((Canonical_p->ntyp=OR_1)) then Canonical_p->lft else Canonical_p);
                                             if(extern isequal(Canonical_k1,Canonical_k2,RValue)) then 
                                             {
                                                 marknode(OR_1,Canonical_p);
                                                 continue_1<==1 and skip;
                                                  Canonical_p:=( if((Canonical_p->ntyp=OR_1)) then Canonical_p->rgt else NULL)
                                             }
                                             else 
                                             {
                                                  skip 
                                             };
                                             if(continue_1=0)   then 
                                             {
                                                 if((extern anywhere(AND_1,Canonical_k1,Canonical_k2,RValue))) then 
                                                 {
                                                     marknode(OR_1,Canonical_p);
                                                     continue_1<==1 and skip;
                                                      Canonical_p:=( if((Canonical_p->ntyp=OR_1)) then Canonical_p->rgt else NULL)
                                                 }
                                                 else 
                                                 {
                                                      skip 
                                                 };
                                                 if(continue_1=0)   then 
                                                 {
                                                     if(Canonical_k2->ntyp=V_OPER AND Canonical_k2->lft->ntyp=FALSE AND (extern anywhere(AND_1,Canonical_k2->rgt,can,RValue))) then 
                                                     {
                                                         marknode(OR_1,Canonical_p);
                                                         continue_1<==1 and skip;
                                                          Canonical_p:=( if((Canonical_p->ntyp=OR_1)) then Canonical_p->rgt else NULL)
                                                     }
                                                     else 
                                                     {
                                                          skip 
                                                     };
                                                     if(continue_1=0)   then 
                                                     {
                                                         Canonical_p:=( if((Canonical_p->ntyp=OR_1)) then Canonical_p->rgt else NULL)
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
                                     continue_1<==0 and skip;
                                     Canonical_m:=( if((Canonical_m->ntyp=OR_1)) then Canonical_m->rgt else NULL)
                                     
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
                         if(goto_1=0)   then 
                         {
                             continue_1<==0 and skip;
                             Canonical_m:=can and Canonical_prev:=NULL;
                             while(Canonical_m)
                             {
                                  continue_1<==0 and skip;
                                 if(Canonical_m->ntyp=-1) then 
                                 {
                                     Canonical_k2:=Canonical_m->rgt;
                                     releasenode(0,Canonical_m);
                                     if(!Canonical_prev) then 
                                     {
                                         can<==can->rgt and Canonical_m<==can and skip
                                         
                                     }
                                     else
                                     {
                                         Canonical_prev->rgt<==Canonical_k2 and Canonical_m<==Canonical_prev->rgt and skip;
                                         if(!Canonical_prev->rgt AND Canonical_prev->lft AND (Canonical_prev->ntyp=AND_1 OR Canonical_prev->ntyp=OR_1)) then 
                                         {
                                             Canonical_k1:=Canonical_prev->lft;
                                             Canonical_prev->ntyp:=Canonical_prev->lft->ntyp;
                                             Canonical_prev->sym:=Canonical_prev->lft->sym;
                                             Canonical_prev->rgt:=Canonical_prev->lft->rgt;
                                             Canonical_prev->lft:=Canonical_prev->lft->lft;
                                             releasenode(0,Canonical_k1)
                                             
                                         }
                                         else 
                                         {
                                              skip 
                                         }
                                     };
                                     continue_1<==1 and skip
                                      
                                 }
                                 else 
                                 {
                                      skip 
                                 };
                                 if(continue_1=0)   then 
                                 {
                                     Canonical_prev:=Canonical_m;
                                     Canonical_m:=Canonical_m->rgt
                                 }
                                 else
                                 {
                                     skip
                                 }
                                 
                             };
                             continue_1<==0 and skip
                             
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
             if(return_1=0)  then
             {
                 if(0) then 
                 {
                     output ("A2: ") and skip
                 }
                 else 
                 {
                      skip 
                 };
                 if(0) then 
                 {
                     dump(can)
                 }
                 else 
                 {
                      skip 
                 };
                 if(0) then 
                 {
                     output ("\n") and skip
                 }
                 else 
                 {
                      skip 
                 };
                 if(!can) then 
                 {
                     if(!Canonical_dflt) then 
                     {
                         fatal("cannot happen, Canonical",NULL)
                     }
                     else 
                     {
                          skip 
                     };
                     return_1<==1 and RValue:=Canonical_dflt;
                     skip
                     
                 }
                 else 
                 {
                      skip 
                 };
                 if(return_1=0)   then 
                 {
                     return_1<==1 and RValue:=can;
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
  function new_set ( int type,int* RValue )
 {
     frame(return_1) and ( 
     int return_1<==0 and skip;
     return_1<==1 and RValue:=(int *)(extern tl_emalloc((( if(type=1) then sym_size else (( if(type=2) then scc_size else node_size))))*4,RValue));
     skip
     )
     }; 
  function clear_set ( int *l,int type,int* RValue )
 {
     frame(clear_set_i,return_1) and ( 
     int return_1<==0 and skip;
     int clear_set_i and skip;
     clear_set_i:=0;
     
     while(clear_set_i<(( if(type=1) then sym_size else (( if(type=2) then scc_size else node_size)))))
     {
         l[clear_set_i]:=0;
         clear_set_i:=clear_set_i+1
         
     };
     return_1<==1 and RValue:=l;
     skip
     )
     }; 
  function make_set ( int n,int type,int* RValue )
 {
     frame(make_set_temp$_1,make_set_l,return_1) and ( 
     int return_1<==0 and skip;
     int* make_set_temp$_1 and skip;
     make_set_temp$_1:=new_set(type,RValue);
     int *make_set_l and skip;
     make_set_l:=clear_set(make_set_temp$_1,type,RValue);
     if(n=-1) then 
     {
         return_1<==1 and RValue:=make_set_l;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         make_set_l[n/ mod]:=1<<(n % mod);
         return_1<==1 and RValue:=make_set_l;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function copy_set ( int *from,int *to,int type )//yixie
 {
     frame(copy_set_i) and ( 
     int copy_set_i and skip;
     copy_set_i:=0;
     
     while(copy_set_i<(( if(type=1) then sym_size else (( if(type=2) then scc_size else node_size)))))
     {
         to[copy_set_i]:=from[copy_set_i];
         copy_set_i:=copy_set_i+1
         
     }
     )
     }; 
  function dup_set ( int *l,int type,int* RValue )
 {
     frame(dup_set_i,dup_set_m,return_1) and ( 
     int return_1<==0 and skip;
     int dup_set_i,*dup_set_m and skip;
     dup_set_m:=new_set(type,RValue);
     dup_set_i:=0;
     
     while(dup_set_i<(( if(type=1) then sym_size else (( if(type=2) then scc_size else node_size)))))
     {
         dup_set_m[dup_set_i]:=l[dup_set_i];
         dup_set_i:=dup_set_i+1
         
     };
     return_1<==1 and RValue:=dup_set_m;
     skip
     )
     }; 
  function merge_sets ( int *l1,int *l2,int type )
 {
     frame(merge_sets_i) and ( 
     int merge_sets_i and skip;
     merge_sets_i:=0;
     
     while(merge_sets_i<(( if(type=1) then sym_size else (( if(type=2) then scc_size else node_size)))))
     {
         l1[merge_sets_i]:=l1[merge_sets_i] | l2[merge_sets_i];
         merge_sets_i:=merge_sets_i+1
         
     }
     )
     }; 
  function do_merge_sets ( int *l,int *l1,int *l2,int type )
 {
     frame(do_merge_sets_i) and ( 
     int do_merge_sets_i and skip;
     do_merge_sets_i:=0;
     
     while(do_merge_sets_i<(( if(type=1) then sym_size else (( if(type=2) then scc_size else node_size)))))
     {
         l[do_merge_sets_i]:=l1[do_merge_sets_i] | l2[do_merge_sets_i];
         do_merge_sets_i:=do_merge_sets_i+1
         
     }
     )
     }; 
  function intersect_sets ( int *l1,int *l2,int type,int* RValue )
 {
     frame(intersect_sets_i,intersect_sets_l,return_1) and ( 
     int return_1<==0 and skip;
     int intersect_sets_i,*intersect_sets_l and skip;
     intersect_sets_l:=new_set(type,RValue);
     intersect_sets_i:=0;
     
     while(intersect_sets_i<(( if(type=1) then sym_size else (( if(type=2) then scc_size else node_size)))))
     {
         intersect_sets_l[intersect_sets_i]:=l1[intersect_sets_i] & l2[intersect_sets_i];
         intersect_sets_i:=intersect_sets_i+1
         
     };
     return_1<==1 and RValue:=intersect_sets_l;
     skip
     )
     }; 
  function empty_intersect_sets ( int *l1,int *l2,int type,int RValue )
 {
     frame(empty_intersect_sets_i,empty_intersect_sets_test,return_1) and ( 
     int return_1<==0 and skip;
     int empty_intersect_sets_i,empty_intersect_sets_test<==0 and skip;
     empty_intersect_sets_i:=0;
     
     while(empty_intersect_sets_i<(( if(type=1) then sym_size else (( if(type=2) then scc_size else node_size)))))
     {
         empty_intersect_sets_test:=empty_intersect_sets_test| (l1[empty_intersect_sets_i] & l2[empty_intersect_sets_i]);
         empty_intersect_sets_i:=empty_intersect_sets_i+1
         
     };
     return_1<==1 and RValue:=!empty_intersect_sets_test
     )
     }; 
  function add_set ( int *l,int n )
 {
     l[n/ mod]:=l[n/ mod]| (1<<(n % mod))
     
 };
 function rem_set ( int *l,int n )
 {
     l[n/ mod]:=l[n/ mod]&(-1-(1<<(n % mod)))
     
 };
 function spin_print_set ( int *pos,int *neg )
 {
     frame(spin_print_set_i,spin_print_set_j,spin_print_set_start) and ( 
     int spin_print_set_i,spin_print_set_j,spin_print_set_start<==1 and skip;
     spin_print_set_i:=0;
     
     while(spin_print_set_i<sym_size)
     {
         spin_print_set_j:=0;
         
         while(spin_print_set_j<mod)
         {
             if(pos[spin_print_set_i] & (1<<spin_print_set_j)) then 
             {
                 if(!spin_print_set_start) then 
                 {
                     output (" && ") and skip
                 }
                 else 
                 {
                      skip 
                 };
                 output (sym_table[mod*spin_print_set_i+spin_print_set_j]) and skip;
                 spin_print_set_start:=0
                 
             }
             else 
             {
                  skip 
             };
             if(neg[spin_print_set_i] & (1<<spin_print_set_j)) then 
             {
                 if(!spin_print_set_start) then 
                 {
                     output (" && ") and skip
                 }
                 else 
                 {
                      skip 
                 };
                 output ("!",sym_table[mod*spin_print_set_i+spin_print_set_j]) and skip;
                 spin_print_set_start:=0
                 
             }
             else 
             {
                  skip 
             };
             spin_print_set_j:=spin_print_set_j+1
             
         };
         spin_print_set_i:=spin_print_set_i+1
         
     };
     if(spin_print_set_start) then 
     {
         output ("1") and skip
     }
     else 
     {
          skip 
     }
     )
     }; 
  function print_set ( int *l,int type )
 {
     frame(print_set_i,print_set_j,print_set_start,nm_14$,break_1$,switch_1,return_1) and ( 
     int return_1<==0 and skip;
     int print_set_i,print_set_j,print_set_start<==1 and skip;
     if(type!=1) then 
     {
         output ("{") and skip
     }
     else 
     {
          skip 
     };
     print_set_i:=0;
     
     while(print_set_i<(( if(type=1) then sym_size else (( if(type=2) then scc_size else node_size)))))
     {
         print_set_j:=0;
         
         while(print_set_j<mod)
         {
             if(l[print_set_i] & (1<<print_set_j)) then 
             {
                 int switch_1 and skip;
                 int break_1$ and skip;
                 break_1$<==0 and skip;
                  switch_1<==0 and skip;
                  int nm_14$ and skip;
                 nm_14$ := type;
                 if (nm_14$=0 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                 {
                     switch_1<==1 and skip
                     
                 }
                 else
                 {
                     skip
                 };
                 if (nm_14$=2 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                 {
                     switch_1<==1 and skip;
                     if(!print_set_start) then 
                     {
                         output (",") and skip
                     }
                     else 
                     {
                          skip 
                     };
					 if(state_flag=1) then
				    {
				    state_num<==mod*print_set_i+print_set_j and skip;
					output("state_num:\n") and skip;
					output(state_num) and skip;
					output("\n") and skip
				    }
				    else
				    {
				       skip
				    };
                     output (mod*print_set_i+print_set_j,"i") and skip;
                     break_1$<==1 and skip
                      
                 }
                 else
                 {
                     skip
                 };
				 
                 if (nm_14$=1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                 {
                     switch_1<==1 and skip;
                     if(!print_set_start) then 
                     {
                         output (" & ") and skip
                     }
                     else 
                     {
                          skip 
                     };
                     output (sym_table[mod*print_set_i+print_set_j]) and skip;
                     break_1$<==1 and skip
                      
                 }
                 else
                 {
                     skip
                 };
                 print_set_start:=0
                 
             }
             else 
             {
                  skip 
             };
             print_set_j:=print_set_j+1
             
         };
         print_set_i:=print_set_i+1
         
     };
     if(type!=1) then 
     {
         output ("}") and skip
     }
     else 
     {
          skip 
     };
	 state_flag<==0 and skip
     )
     }; 
  function empty_set ( int *l,int type,int RValue )
 {
     frame(empty_set_i,empty_set_test,return_1) and ( 
     int return_1<==0 and skip;
     int empty_set_i,empty_set_test<==0 and skip;
     empty_set_i:=0;
     
     while(empty_set_i<(( if(type=1) then sym_size else (( if(type=2) then scc_size else node_size)))))
     {
         empty_set_test:=empty_set_test| (l[empty_set_i]);
         empty_set_i:=empty_set_i+1
         
     };
     return_1<==1 and RValue:=!empty_set_test;
     skip
     )
     }; 
  function same_sets ( int *l1,int *l2,int type,int RValue )
 {
     frame(same_sets_i,same_sets_test,return_1) and ( 
     int return_1<==0 and skip;
     int same_sets_i,same_sets_test<==1 and skip;
     same_sets_i:=0;
     
     while(same_sets_i<(( if(type=1) then sym_size else (( if(type=2) then scc_size else node_size)))))
     {
         same_sets_test:=same_sets_test&(l1[same_sets_i]=l2[same_sets_i]);
         same_sets_i:=same_sets_i+1
         
     };
     return_1<==1 and RValue:=same_sets_test;
     skip
     )
     }; 
  function included_set ( int *l1,int *l2,int type,int RValue )
 {
     frame(included_set_i,included_set_test,return_1) and ( 
     int return_1<==0 and skip;
     int included_set_i,included_set_test<==0 and skip;
     included_set_i:=0;
     while(included_set_i<(( if(type=1) then sym_size else (( if(type=2) then scc_size else node_size)))))
     {
         included_set_test:=included_set_test| (l1[included_set_i] & ~l2[included_set_i]);
         included_set_i:=included_set_i+1
         
     };
     return_1<==1 and RValue:=!included_set_test
     )
     }; 
  function in_set ( int *l,int n,int RValue )
 {
     frame(return_1) and ( 
     int return_1<==0 and skip;
     return_1<==1 and RValue:=(l[n/ mod] & (1<<(n % mod)));
     skip
     )
     }; 
  function list_set ( int *l,int type,int* RValue )
 {
     frame(list_set_i,list_set_j,list_set_size,list_set_list$,return_1) and ( 
     int return_1<==0 and skip;
     int list_set_i,list_set_j,list_set_size<==1,*list_set_list$ and skip;
     list_set_i:=0;
     
     while(list_set_i<(( if(type=1) then sym_size else (( if(type=2) then scc_size else node_size)))))
     {
         list_set_j:=0;
         
         while(list_set_j<mod)
         {
             if(l[list_set_i] & (1<<list_set_j)) then 
             {
                 list_set_size:=list_set_size+1
             }
             else 
             {
                  skip 
             };
             list_set_j:=list_set_j+1
             
         };
         list_set_i:=list_set_i+1
         
     };
     list_set_list$:=(int *)(extern tl_emalloc(list_set_size*4,RValue));
     list_set_list$[0]:=list_set_size;
     list_set_size:=1;
     list_set_i:=0;
     
     while(list_set_i<(( if(type=1) then sym_size else (( if(type=2) then scc_size else node_size)))))
     {
         list_set_j:=0;
         
         while(list_set_j<mod)
         {
             if(l[list_set_i] & (1<<list_set_j)) then 
             {
                 list_set_list$[list_set_size]:=mod*list_set_i+list_set_j;
                 list_set_size:=list_set_size+1
             }
             else 
             {
                  skip 
             };
             list_set_j:=list_set_j+1
             
         };
         list_set_i:=list_set_i+1
         
     };
     return_1<==1 and RValue:=list_set_list$;
     skip
     )
     }; 
  function dump_cond ( Node *pp,Node *r,int first,int RValue )
 {
     frame(dump_cond_q,dump_cond_frst,dump_cond_temp$_1,return_1) and ( 
     int return_1<==0 and skip;
     Node *dump_cond_q and skip;
     int dump_cond_frst<==first and skip;
     if(!pp) then 
     {
         return_1<==1 and RValue:=dump_cond_frst;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         dump_cond_q:=dupnode(pp,RValue);
         Node* dump_cond_temp$_1 and skip;
         dump_cond_temp$_1:=right_linked(dump_cond_q,RValue);
         dump_cond_q:=canonical(dump_cond_temp$_1,RValue);
         if(dump_cond_q->ntyp=PREDICATE OR dump_cond_q->ntyp=NOT OR dump_cond_q->ntyp=OR_1 OR dump_cond_q->ntyp=FALSE) then 
         {
             if(!dump_cond_frst) then 
             {
                 output (" && ") and skip
             }
             else 
             {
                  skip 
             };
             dump(dump_cond_q);
             dump_cond_frst:=0
             
         }
         else
         {
             if(dump_cond_q->ntyp=V_OPER AND !(extern anywhere(AND_1,dump_cond_q->rgt,r,RValue))) then 
             {
                 dump_cond_frst:=dump_cond(dump_cond_q->rgt,r,dump_cond_frst,RValue)
             }
             else
             {
                 if(dump_cond_q->ntyp=AND_1) then 
                 {
                     dump_cond_frst:=dump_cond(dump_cond_q->lft,r,dump_cond_frst,RValue);
                     dump_cond_frst:=dump_cond(dump_cond_q->rgt,r,dump_cond_frst,RValue)
                     
                 }
                 else 
                 {
                      skip 
                 }
             }
         };
         return_1<==1 and RValue:=dump_cond_frst;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function sdump ( Node *n )
 {
     frame(nm_15$,break_1$,switch_1,return_1) and ( 
     int return_1<==0 and skip;
     int switch_1 and skip;
     int break_1$ and skip;
     break_1$<==0 and skip;
      switch_1<==0 and skip;
      int nm_15$ and skip;
     nm_15$ := n->ntyp;
     if (nm_15$=PREDICATE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         strcat(dumpbuf,n->sym->name) and skip;
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_15$=U_OPER OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         strcat(dumpbuf,"U") and skip;
         sdump(n->rgt);
         sdump(n->lft);
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_15$=V_OPER OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         strcat(dumpbuf,"V") and skip;
         sdump(n->rgt);
         sdump(n->lft);
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_15$=OR_1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         strcat(dumpbuf,"|") and skip;
         sdump(n->rgt);
         sdump(n->lft);
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_15$=AND_1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         strcat(dumpbuf,"&") and skip;
         sdump(n->rgt);
         sdump(n->lft);
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_15$=NOT OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         strcat(dumpbuf,"!") and skip;
         sdump(n->lft);
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_15$=TRUE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         strcat(dumpbuf,"T") and skip;
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if (nm_15$=FALSE OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
     {
         switch_1<==1 and skip;
         strcat(dumpbuf,"F") and skip;
         break_1$<==1 and skip
          
     }
     else
     {
         skip
     };
     if(break_1$=0 AND return_1=0) then 
     {
         strcat(dumpbuf,"?") and skip;
         break_1$<==1 and skip
          
     }
     else
     {
          skip
         })
         }; 
  function DoDump ( Node *n,Symbol* RValue )
 {
     frame(return_1) and ( 
     int return_1<==0 and skip;
     if(!n) then 
     {
         return_1<==1 and RValue:=NULL;
         skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         if(n->ntyp=PREDICATE) then 
         {
             return_1<==1 and RValue:=n->sym;
             skip
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
             dumpbuf[0]:='\0';
             sdump(n);
             return_1<==1 and RValue:=tl_lookup(dumpbuf,RValue);
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
  function trans ( Node *p )
 {
     frame(return_1) and (
     int return_1<==0 and skip;
     if(!p OR tl_errs) then 
     {
          return_1<==1 and skip
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         if(tl_verbose OR tl_terse) then 
         {
             output ("\t
             \n") and skip
             
         }
         else 
         {
              skip 
         };
         if(tl_terse) then 
         {
              return_1<==1 and skip
         }
         else 
         {
              skip 
         };
         if(return_1=0)   then 
         {
			 mk_alternating(p);
             mk_generalized();
             mk_buchi()
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
  main_1(RValue)
 )
