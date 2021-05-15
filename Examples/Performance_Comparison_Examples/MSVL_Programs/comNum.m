/*</
define p:fuhe<100;
alw(p)
/>*/
/*</
define p:module_4=1;
som(p)
/>*/
</
define p:module_1=1;
define q:module_4=1;
alw(p->som(q))
/>
/*</
define p1:module_1=1;
define p2:module_2=1;
define p3:module_3=1;
define p4:module_4=1;
p1;(p2;p3;p4)#
/>*/


frame(zuhe,sum,fuhe,success,module_1,module_2,module_3,module_4) and (
float zuhe[4]<==[0] and skip;
int sum<==0 and skip;
int fuhe<==0 and skip;
int success<==0 and skip;
int module_1<==0 and skip;
int module_2<==0 and skip;
int module_3<==0 and skip;
int module_4<==0 and skip;
function main_1 (  )
 {
     frame(main_s,main_shu,main_i,main_j,main_1_s0) and ( 
	 module_1<==1 and skip;
     float main_s[4]<==[1,2,3,4],main_shu[4]<==[0] and skip;
     //output ("请输入六个数(0-9):\n") and skip;
     int main_i<==0 and skip;
     
     while(main_i<4)
     {
         //input(main_s[main_i]) and skip;
         int main_j<==main_i and skip;
         
         while(main_j>0)
         {
             if(main_s[main_j]<=main_s[main_j-1]) then 
             {
                 float main_1_s0<==main_s[main_j-1] and skip;
                 main_s[main_j-1]:=main_s[main_j];
                 main_s[main_j]:=main_1_s0
                 
             }
             else 
             {
                  skip 
             };
             main_j:=main_j-1
             
         };
         main_i:=main_i+1
         
     };
     //output ("六个数是:") and skip;
     main_i:=0;
     
     while(main_i<4)
     {
         //output (main_s[main_i]," "," ") and skip;
         main_i:=main_i+1
         
     };
     //output ("\n") and skip;
     zuheshu(main_s,4,RValue);
     output ("有",fuhe,"个算式符合\n") and skip;
	  success<==1 and skip
     )
     }; 
  function zuheshu ( float s[],int n,int RValue )
 {
     frame(zuheshu_i,zuheshu_2_p,zuheshu_2_o,zuheshu_2_k,zuheshu_4_5_p,zuheshu_4_5_o,zuheshu_4_5_k,return_1) and ( 
     int return_1<==0 and skip;
     if(n=1) then 
     {
         zuhe[4-n]:=s[0];
         zuhefu(RValue);
         return_1<==1 and RValue:=1;
         skip
         
     }
     else 
     {
          skip 
     };
     if(return_1=0)   then 
     {
         int zuheshu_i<==0 and skip;
         
         while(zuheshu_i<n)
         {
             if(zuheshu_i=0) then 
             {
                 zuhe[4-n]:=s[zuheshu_i];
                 float zuheshu_2_p[20] and skip;
                 int zuheshu_2_o<==0 and skip;
                 int zuheshu_2_k<==0 and skip;
                 
                 while(zuheshu_2_k<n)
                 {
                     if(zuheshu_2_k!=zuheshu_i) then 
                     {
                         zuheshu_2_p[zuheshu_2_o]:=s[zuheshu_2_k];
                         zuheshu_2_o:=zuheshu_2_o+1
                     }
                     else 
                     {
                          skip 
                     };
                     zuheshu_2_k:=zuheshu_2_k+1
                     
                 };
                 zuheshu(zuheshu_2_p,n-1,RValue)    
             }
             else
             {
                 if(s[zuheshu_i]!=s[zuheshu_i-1]) then 
                 {
                     zuhe[4-n]:=s[zuheshu_i];
                     float zuheshu_4_5_p[20] and skip;
                     int zuheshu_4_5_o<==0 and skip;
                     int zuheshu_4_5_k<==0 and skip;
                     
                     while(zuheshu_4_5_k<n)
                     {
                         if(zuheshu_4_5_k!=zuheshu_i) then 
                         {
                             zuheshu_4_5_p[zuheshu_4_5_o]:=s[zuheshu_4_5_k];
                             zuheshu_4_5_o:=zuheshu_4_5_o+1
                         }
                         else 
                         {
                              skip 
                         };
                         zuheshu_4_5_k:=zuheshu_4_5_k+1
                         
                     };
                     zuheshu(zuheshu_4_5_p,n-1,RValue)                 
                 }
                 else 
                 {
                      skip 
                 }
             };
             zuheshu_i:=zuheshu_i+1
             
         }
     }
     else
     {
         skip
     }
     )
     }; 
  function zuhefu ( int RValue )
 {
     frame(zuhefu_opter,zuhefu_h,zuhefu_i,zuhefu_j,zuhefu_op,zuhefu_khzh,zuhefu_k,nm_1$,break_1$,switch_1,zuhefu_1_m,zuhefu_1_n,return_1,continue) and ( 
	 module_2<==1 and skip;
     int continue_1<==0 and skip;
     int return_1<==0 and skip;
     char zuhefu_opter[4]<==['+','-','*','/'] and skip;
     int zuhefu_h<==0 and skip;
     
     while(zuhefu_h<4)
     {
         int zuhefu_i<==0 and skip;
         
         while(zuhefu_i<4)
         {
             int zuhefu_j<==0 and skip;
             
             while(zuhefu_j<4)
             {
                 char zuhefu_op[3] and skip;
                 zuhefu_op[0]:=zuhefu_opter[zuhefu_h];
                 zuhefu_op[1]:=zuhefu_opter[zuhefu_i];
                 zuhefu_op[2]:=zuhefu_opter[zuhefu_j];
                 int zuhefu_khzh[8,3]<==[[0,0,0],[0,0,1],[0,1,0],[1,0,0],[0,1,1],[1,0,1],[1,1,0],[1,1,1]] and skip;
                 int zuhefu_k<==0 and skip;
                 
                 while(zuhefu_k<=3)
                 {
                     int switch_1 and skip;
                     int break_1$ and skip;
                     break_1$<==0 and skip;
                      switch_1<==0 and skip;
                      int nm_1$ and skip;
                     nm_1$ := zuhefu_k;
                     if (nm_1$=0 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                     {
                         switch_1<==1 and skip;
                         yunsuan(zuhe,zuhefu_op,zuhefu_khzh[0],zuhefu_khzh[0],RValue);
                         break_1$<==1 and skip
                          
                     }
                     else
                     {
                         skip
                     };
                     if (nm_1$=1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                     {
                         switch_1<==1 and skip;
                         int zuhefu_1_m<==1 and skip;
                         
                         while(zuhefu_1_m<=3)
                         {
                             continue_1<==0 and skip;
                             int zuhefu_1_n<==1 and skip;
                             
                             while(zuhefu_1_n<=3)
                             {
                                  continue_1<==0 and skip;
                                 if((zuhefu_1_m=2 AND zuhefu_1_n=3) OR (zuhefu_1_m=1 AND zuhefu_1_n=2) OR (zuhefu_1_m=3 AND zuhefu_1_n=1) OR (zuhefu_1_m=1 AND zuhefu_1_n=3)) then 
                                 {
                                     continue_1<==1 and skip;
                                      zuhefu_1_n:=zuhefu_1_n+1}
                                     else 
                                     {
                                          skip 
                                     };
                                     if(continue_1=0)   then 
                                     {
                                         yunsuan(zuhe,zuhefu_op,zuhefu_khzh[zuhefu_1_m],zuhefu_khzh[zuhefu_1_n],RValue);
                                         zuhefu_1_n:=zuhefu_1_n+1
                                     }
                                     else
                                     {
                                         skip
                                     }
                                     
                                 };
                                 continue_1<==0 and skip;
                                 zuhefu_1_m:=zuhefu_1_m+1
                                 
                             };
                             break_1$<==1 and skip
                              
                         }
                         else
                         {
                             skip
                         };
                         if (nm_1$=2 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                         {
                             switch_1<==1 and skip;
                             yunsuan(zuhe,zuhefu_op,zuhefu_khzh[5],zuhefu_khzh[5],RValue);
                             break_1$<==1 and skip
                              
                         }
                         else
                         {
                             skip
                         };
                         if (nm_1$=3 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                         {
                             switch_1<==1 and skip;
                             break_1$<==1 and skip
                              
                         }
                         else
                         {
                             skip
                         };
                         zuhefu_k:=zuhefu_k+1
                         
                     };
                     zuhefu_j:=zuhefu_j+1
                     
                 };
                 zuhefu_i:=zuhefu_i+1
                 
             };
             zuhefu_h:=zuhefu_h+1
             
         };
         return_1<==1 and RValue:=1;
         skip
         )
         }; 
  function yunsuan ( float s[],char p[],int k0[],int k1[],int RValue )
 {
     frame(yunsuan_suanshi0,yunsuan_r,yunsuan_q,nm_2$,break_1$,switch_1,yunsuan_suanshi,yunsuan_i,yunsuan_f,yunsuan_sum0,yunsuan_10_t,return_1) and (
	 module_3<==1 and skip;	 
     int return_1<==0 and skip;
     float yunsuan_suanshi0[13]<==['0'] and skip;
     int yunsuan_r<==0 and skip;
     int yunsuan_q<==0 and skip;
     
     while(yunsuan_q<13)
     {
         int switch_1 and skip;
         int break_1$ and skip;
         break_1$<==0 and skip;
          switch_1<==0 and skip;
          int nm_2$ and skip;
         nm_2$ := yunsuan_q;
         if (nm_2$=0 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             if(k0[0]=1) then 
             {
                 yunsuan_suanshi0[yunsuan_r]:='(';
                 yunsuan_r:=yunsuan_r+1
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
         if (nm_2$=1 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             yunsuan_suanshi0[yunsuan_r]:=s[0];
             yunsuan_r:=yunsuan_r+1;
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_2$=2 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             yunsuan_suanshi0[yunsuan_r]:=p[0];
             yunsuan_r:=yunsuan_r+1;
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_2$=3 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             if(k0[1]=1) then 
             {
                 yunsuan_suanshi0[yunsuan_r]:='(';
                 yunsuan_r:=yunsuan_r+1
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
         if (nm_2$=4 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             yunsuan_suanshi0[yunsuan_r]:=s[1];
             yunsuan_r:=yunsuan_r+1;
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_2$=5 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             if(k1[0]=1) then 
             {
                 yunsuan_suanshi0[yunsuan_r]:=')';
                 yunsuan_r:=yunsuan_r+1
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
         if (nm_2$=4 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             yunsuan_suanshi0[yunsuan_r]:=p[1];
             yunsuan_r:=yunsuan_r+1;
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_2$=7 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             if(k0[2]=1) then 
             {
                 yunsuan_suanshi0[yunsuan_r]:='(';
                 yunsuan_r:=yunsuan_r+1
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
         if (nm_2$=8 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             yunsuan_suanshi0[yunsuan_r]:=s[2];
             yunsuan_r:=yunsuan_r+1;
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_2$=9 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             if(k1[1]=1) then 
             {
                 yunsuan_suanshi0[yunsuan_r]:=')';
                 yunsuan_r:=yunsuan_r+1
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
         if (nm_2$=10 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             yunsuan_suanshi0[yunsuan_r]:=p[2];
             yunsuan_r:=yunsuan_r+1;
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_2$=11 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             yunsuan_suanshi0[yunsuan_r]:=s[3];
             yunsuan_r:=yunsuan_r+1;
             break_1$<==1 and skip
              
         }
         else
         {
             skip
         };
         if (nm_2$=12 OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             if(k1[2]=1) then 
             {
                 yunsuan_suanshi0[yunsuan_r]:=')';
                 yunsuan_r:=yunsuan_r+1
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
         yunsuan_q:=yunsuan_q+1
         
     };
      float yunsuan_suanshi[20] and skip;
     int yunsuan_i<==0 and skip;
     
     while(yunsuan_i<yunsuan_r)
     {
         yunsuan_suanshi[yunsuan_i]:=yunsuan_suanshi0[yunsuan_i];
         yunsuan_i:=yunsuan_i+1
         
     };
     float yunsuan_f and skip;
     yunsuan_f:=hefa(yunsuan_suanshi,yunsuan_r,RValue);
     if(yunsuan_f=0) then 
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
         yunsuan_f:=jianjie(yunsuan_suanshi,yunsuan_r,RValue);
         if(yunsuan_f=0) then 
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
             float yunsuan_sum0 and skip;
             yunsuan_sum0:=qiujie(yunsuan_suanshi,yunsuan_r,RValue);
             if(yunsuan_sum0=24) then 
             {
                 fuhe:=fuhe+1;
                 int yunsuan_10_t<==0 and skip;
                 
                 while(yunsuan_10_t<yunsuan_r)
                 {
                     if(yunsuan_suanshi[yunsuan_10_t]>10) then 
                     {
                         //output ((char)(yunsuan_suanshi[yunsuan_10_t])) and skip
						 skip
                     }
                     else
                     {
                         //output (yunsuan_suanshi[yunsuan_10_t],"") and skip
						 skip
                     };
                     yunsuan_10_t:=yunsuan_10_t+1
                     
                 };
                 //output ("=",yunsuan_sum0) and skip;
                 //output ("\n") and skip
				 skip
                 
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
         }
     }
     else
     {
         skip
     }
     )
     }; 
  function hefa ( float suanshi[],int r,int RValue )
 {
     frame(hefa_p,hefa_q,hefa_flag,return_1,break_1) and ( 
	 module_4<==1 and skip;
     int break_1<==0 and skip;
     int return_1<==0 and skip;
     float *hefa_p<==&suanshi[0] and skip;
     float *hefa_q<==&suanshi[1] and skip;
     int hefa_flag<==1 and skip;
     break_1<==0 and skip;
     while( break_1=0 AND  1)
     {
         if(* hefa_p=40) then 
         {
             if((* hefa_q>=0) AND (* hefa_q<=9)) then 
             {
                 hefa_p:=hefa_p+1;
                 hefa_q:=hefa_q+1
             }
             else
             {
                 hefa_flag:=0;
                 break_1<==1 and skip
              }
             
         }
         else 
         {
              skip 
         };
         if(break_1=0)   then 
         {
             if((* hefa_p>=0) AND (* hefa_p<=9)) then 
             {
                 if((hefa_p-suanshi)>=(r-1)) then 
                 {
                     break_1<==1 and skip
                      
                 }
                 else 
                 {
                      skip 
                 };
                 if(break_1=0)   then
                 {
                     if(* hefa_q=')' OR ((* hefa_q>41) AND (* hefa_q<48))) then 
                     {
                         hefa_p:=hefa_p+1;
                         hefa_q:=hefa_q+1
                     }
                     else
                     {
                         hefa_flag:=0;
                         break_1<==1 and skip
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
             if(break_1=0)   then 
             {
                 if(* hefa_p=41) then 
                 {
                     if((hefa_p-suanshi)>=(r-1)) then 
                     {
                         break_1<==1 and skip
                          
                     }
                     else 
                     {
                          skip 
                     };
                     if(break_1=0)   then
                     {
                         if((* hefa_q>41) AND (* hefa_q<48)) then 
                         {
                             hefa_p:=hefa_p+1;
                             hefa_q:=hefa_q+1
                         }
                         else
                         {
                             hefa_flag:=0;
                             break_1<==1 and skip
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
                 if(break_1=0)   then 
                 {
                     if((* hefa_p>41) AND (* hefa_p<48)) then 
                     {
                         if(* hefa_q=40 OR ((* hefa_q>=0) AND (* hefa_q<=9))) then 
                         {
                             hefa_p:=hefa_p+1;
                             hefa_q:=hefa_q+1
                         }
                         else
                         {
                             hefa_flag:=0;
                             break_1<==1 and skip
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
     break_1<==0 and skip;
     return_1<==1 and RValue:=hefa_flag;
     skip
     )
     }; 
  function jianjie ( float suanshi[],int r,float RValue )
 {
     frame(jianjie_re,jianjie_p,jianjie_q,jianjie_k,jianjie_k1,jianjie_r0,jianjie_r2,jianjie_r1,jianjie_r3,jianjie_i,return_1,continue_1) and ( 
     int continue_1<==0 and skip;
     int return_1<==0 and skip;
     float jianjie_re<==1 and skip;
     float *jianjie_p<==&jianjie_re,*jianjie_q<==&jianjie_re and skip;
     int jianjie_k<==0 and skip;
     int jianjie_k1<==0 and skip;
     float jianjie_r0<==0 and skip;
     float jianjie_r2<==1 and skip;
     float jianjie_r1<==0 and skip;
     int jianjie_r3<==0 and skip;
     continue_1<==0 and skip;
     int jianjie_i<==0 and skip;
     
     while( return_1=0 AND  jianjie_i<r)
     {
          continue_1<==0 and skip;
         if(suanshi[jianjie_i]='(') then 
         {
             jianjie_k:=jianjie_k+1;
             if(* jianjie_p!='(' OR jianjie_k=1) then 
             {
                 jianjie_p:=&suanshi[jianjie_i];
                 if(jianjie_i!=0) then 
                 {
                     if(* (jianjie_p-1)='+' OR * (jianjie_p-1)='-') then 
                     {
                         jianjie_r0:=1
                         
                     }
                     else
                     {
                         if(* (jianjie_p-1)='*' OR * (jianjie_p-1)='/') then 
                         {
                             jianjie_r0:=2
                             
                         }
                         else 
                         {
                              skip 
                         }
                     };
                     if(* (jianjie_p-1)='-') then 
                     {
                         jianjie_r0:=jianjie_r0+100
                     }
                     else
                     {
                         if(* (jianjie_p-1)='/') then 
                         {
                             jianjie_r0:=jianjie_r0+1000
                             
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
             
         }
         else
         {
             if(suanshi[jianjie_i]=')') then 
             {
                 if(jianjie_k=1) then 
                 {
                     jianjie_k:=jianjie_k-1;
                     jianjie_q:=&suanshi[jianjie_i];
                     if(jianjie_i!=r-1) then 
                     {
                         if(* (jianjie_q+1)='+' OR * (jianjie_q+1)='-') then 
                         {
                             jianjie_r1:=1
                         }
                         else
                         {
                             if(* (jianjie_q+1)='*' OR * (jianjie_q+1)='/') then 
                             {
                                 jianjie_r1:=2
                                 
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
                     };
                     jianjie_re:=jianjie(jianjie_p+1,jianjie_q-jianjie_p-1,RValue);
                     if((int)(jianjie_r0/ 100)>=1) then 
                     {
                         if(((int)(jianjie_r0/ 100))=1 AND ((int)(jianjie_re/ 100))=1) then 
                         {
                             continue_1<==1 and skip;
                              jianjie_i:=jianjie_i+1}
                             else
                             {
                                 if(((int)(jianjie_r0/ 1000))=1 AND ((int)(jianjie_re/ 1000))=1) then 
                                 {
                                     continue_1<==1 and skip;
                                      jianjie_i:=jianjie_i+1
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
                         };
                         if(continue_1=0)  then
                         {
                             if((int)(jianjie_re/ 100)=1) then 
                             {
                                 jianjie_re:=jianjie_re-100
                             }
                             else 
                             {
                                  skip 
                             };
                             if((int)(jianjie_re/ 1000)=1) then 
                             {
                                 jianjie_re:=jianjie_re-1000
                             }
                             else 
                             {
                                  skip 
                             };
                             if((int)(jianjie_r0/ 100)=1) then 
                             {
                                 jianjie_r0:=jianjie_r0-100
                             }
                             else
                             {
                                 if((int)(jianjie_r0/ 1000)=1) then 
                                 {
                                     jianjie_r0:=jianjie_r0-1000
                                 }
                                 else 
                                 {
                                      skip 
                                 }
                             };
                             if(jianjie_re=0) then 
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
                                 if(jianjie_re>=jianjie_r0 AND jianjie_re>=jianjie_r1) then 
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
                         jianjie_k:=jianjie_k-1
                         
                     }
                 }
                 else
                 {
                     if(jianjie_k=0) then 
                     {
                         if(suanshi[jianjie_i]='+' OR suanshi[jianjie_i]='-') then 
                         {
                             jianjie_r2:=((jianjie_r2*jianjie_k1)+1)/ ((jianjie_k1+1));
                             jianjie_k1:=jianjie_k1+1;
                             jianjie_r3:=jianjie_r3/ 10+1
                         }
                         else
                         {
                             if(suanshi[jianjie_i]='*' OR suanshi[jianjie_i]='/') then 
                             {
                                 jianjie_r2:=(jianjie_r2*jianjie_k1+2)/ ((jianjie_k1+1));
                                 jianjie_k1:=jianjie_k1+1;
                                 jianjie_r3:=jianjie_r3 % 10+10
                                 
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
             };
             if(continue_1=0)  then 
             {
                 if(return_1=0)  then
                 {
                     jianjie_i:=jianjie_i+1
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
         if(return_1=0)   then 
         {
             if(jianjie_r3 % 10=1) then 
             {
                 jianjie_r2:=jianjie_r2+100
             }
             else 
             {
                  skip 
             };
             if(jianjie_r3/ 10=1) then 
             {
                 jianjie_r2:=jianjie_r2+1000
             }
             else 
             {
                  skip 
             };
             return_1<==1 and RValue:=jianjie_r2;
             skip
         }
         else
         {
             skip
         }
         )
         }; 
  function qiujie ( float suanshi[],int n,float RValue )
 {
     frame(qiujie_1_a,nm_3$,break_1$,switch_1,qiujie_pq,qiujie_p,qiujie_q,qiujie_k,qiujie_suanshi1,qiujie_s,qiujie_sum,qiujie_m,nm_4$,qiujie_9_10_11_ws,qiujie_9_10_11_w,qiujie_9_10_17_ws,qiujie_9_10_17_w,return_1,continue_1) and (
     int continue_1<==0 and skip;
     int return_1<==0 and skip;
     if(n=3) then 
     {
         float qiujie_1_a<==0 and skip;
         int switch_1 and skip;
         int break_1$ and skip;
         break_1$<==0 and skip;
          switch_1<==0 and skip;
          int nm_3$ and skip;
         nm_3$ := (char)(suanshi[1]);
         if (nm_3$='+' OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             return_1<==1 and RValue:=(suanshi[0]+suanshi[2]);
             skip
             
         }
         else
         {
             skip
         };
         if (nm_3$='-' OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             return_1<==1 and RValue:=(suanshi[0]-suanshi[2]);
             skip
             
         }
         else
         {
             skip
         };
         if (nm_3$='*' OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             return_1<==1 and RValue:=(suanshi[0]*suanshi[2]);
             skip
             
         }
         else
         {
             skip
         };
         if (nm_3$='/' OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
         {
             switch_1<==1 and skip;
             return_1<==1 and RValue:=(suanshi[0]/ suanshi[2]);
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
     if(return_1=0)   then 
     {
         float qiujie_pq<=='0' and skip;
         float *qiujie_p<==&qiujie_pq and skip;
         float *qiujie_q<==&qiujie_pq and skip;
         int qiujie_k<==0 and skip;
         float qiujie_suanshi1[7]<==['0'] and skip;
         int qiujie_s<==0 and skip;
         float qiujie_sum<==0 and skip;
         continue_1<==0 and skip;
         int qiujie_m<==0 and skip;
         
         while(qiujie_m<n)
         {
              continue_1<==0 and skip;
             if(suanshi[qiujie_m]='(') then 
             {
                 qiujie_k:=qiujie_k+1;
                 if((* qiujie_p)!='(') then 
                 {
                     qiujie_p:=&suanshi[qiujie_m]
                     
                 }
                 else 
                 {
                      skip 
                 };
                 continue_1<==1 and skip;
                  qiujie_m:=qiujie_m+1
             }
             else 
             {
                  skip 
             };
             if(continue_1=0)   then 
             {
                 if(suanshi[qiujie_m]=')') then 
                 {
                     if(qiujie_k=1) then 
                     {
                         qiujie_k:=qiujie_k-1;
                         qiujie_q:=&suanshi[qiujie_m];
                         qiujie_suanshi1[qiujie_s]:=qiujie(qiujie_p+1,qiujie_q-qiujie_p-1,RValue);
                         qiujie_s:=qiujie_s+1;
                         qiujie_p:=&qiujie_pq;
                         qiujie_q:=&qiujie_pq
                         
                     }
                     else 
                     {
                         qiujie_k:=qiujie_k-1
                         
                     };
                     continue_1<==1 and skip;
                      qiujie_m:=qiujie_m+1
                 }
                 else 
                 {
                      skip 
                 };
                 if(continue_1=0)   then 
                 {
                     if(qiujie_k=0) then 
                     {
                         qiujie_suanshi1[qiujie_s]:=suanshi[qiujie_m];
                         qiujie_s:=qiujie_s+1;
                         continue_1<==1 and skip;
                          qiujie_m:=qiujie_m+1
                     }
                     else 
                     {
                          skip 
                     };
                     if(continue_1=0)   then 
                     {
                         qiujie_m:=qiujie_m+1
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
         if(qiujie_s=3) then 
         {
             qiujie_sum:=qiujie(qiujie_suanshi1,qiujie_s,RValue)
             
         }
         else
         {
             qiujie_p:=&qiujie_suanshi1[0];
             qiujie_q:=&qiujie_suanshi1[2];
             qiujie_m:=0;
             
             while(qiujie_m<(qiujie_s-1)/ 2)
             {
                 break_1$<==0 and skip;
                  switch_1<==0 and skip;
                  int nm_4$ and skip;
                 nm_4$ := (char)(qiujie_suanshi1[2*qiujie_m+1]);
                 if (nm_4$='+' OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                 {
                     switch_1<==1 and skip;
                     if((qiujie_s-1)/ 2!=1 AND (qiujie_suanshi1[2*(qiujie_m+1)+1]='*' OR qiujie_suanshi1[2*(qiujie_m+1)+1]='/')) then 
                     {
                         * qiujie_q:=qiujie(qiujie_p+2,3,RValue);
                         int qiujie_9_10_11_ws<==&qiujie_suanshi1[qiujie_s-1]-&qiujie_suanshi1[2*(qiujie_m+1)] and skip;
                         int qiujie_9_10_11_w<==1 and skip;
                         
                         while(qiujie_9_10_11_w<=qiujie_9_10_11_ws)
                         {
                             if(((qiujie_q+qiujie_9_10_11_w+2)-(qiujie_q+qiujie_9_10_11_ws))>0) then 
                             {
                                 * (qiujie_q+qiujie_9_10_11_w):=-1
                                 
                             }
                             else
                             {
                                 * (qiujie_q+qiujie_9_10_11_w):=* (qiujie_q+qiujie_9_10_11_w+2)
                             };
                             qiujie_9_10_11_w:=qiujie_9_10_11_w+1
                             
                         };
                         qiujie_s:=qiujie_s-2;
                         qiujie_m:=qiujie_m-1
                         
                     }
                     else
                     {
                         if(qiujie_m=0) then 
                         {
                             qiujie_sum:=qiujie_sum+* qiujie_p+* qiujie_q
                             
                         }
                         else
                         {
                             qiujie_sum:=qiujie_sum+* qiujie_q
                         };
                         qiujie_p:=qiujie_p+2;
                         qiujie_q:=qiujie_q+2
                     };
                     break_1$<==1 and skip
                      
                 }
                 else
                 {
                     skip
                 };
                 if (nm_4$='-' OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                 {
                     switch_1<==1 and skip;
                     if((qiujie_s-1)/ 2!=1 AND (qiujie_suanshi1[2*(qiujie_m+1)+1]='*' OR qiujie_suanshi1[2*(qiujie_m+1)+1]='/')) then 
                     {
                         * qiujie_q:=qiujie(qiujie_p+2,3,RValue);
                         int qiujie_9_10_17_ws<==&qiujie_suanshi1[qiujie_s-1]-&qiujie_suanshi1[2*(qiujie_m+1)] and skip;
                         int qiujie_9_10_17_w<==1 and skip;
                         
                         while(qiujie_9_10_17_w<=qiujie_9_10_17_ws)
                         {
                             if(((qiujie_q+qiujie_9_10_17_w+2)-(qiujie_q+qiujie_9_10_17_ws))>0) then 
                             {
                                 * (qiujie_q+qiujie_9_10_17_w):=-1
                                 
                             }
                             else
                             {
                                 * (qiujie_q+qiujie_9_10_17_w):=* (qiujie_q+qiujie_9_10_17_w+2)
                             };
                             qiujie_9_10_17_w:=qiujie_9_10_17_w+1
                             
                         };
                         qiujie_s:=qiujie_s-2;
                         qiujie_m:=-1
                         
                     }
                     else
                     {
                         if(qiujie_m=0) then 
                         {
                             qiujie_sum:=qiujie_sum+* qiujie_p-* qiujie_q
                         }
                         else
                         {
                             qiujie_sum:=qiujie_sum-* qiujie_q
                         };
                         qiujie_p:=qiujie_p+2;
                         qiujie_q:=qiujie_q+2
                     };
                     break_1$<==1 and skip
                      
                 }
                 else
                 {
                     skip
                 };
                 if (nm_4$='*' OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                 {
                     switch_1<==1 and skip;
                     if(qiujie_m=0) then 
                     {
                         qiujie_sum:=qiujie_sum+(* qiujie_p)*(* qiujie_q)
                     }
                     else
                     {
                         qiujie_sum:=qiujie_sum** qiujie_q
                     };
                     qiujie_p:=qiujie_p+2;
                     qiujie_q:=qiujie_q+2;
                     break_1$<==1 and skip
                      
                 }
                 else
                 {
                     skip
                 };
                 if (nm_4$='/' OR (switch_1=1 AND break_1$=0 AND return_1=0) ) then 
                 {
                     switch_1<==1 and skip;
                     if(qiujie_m=0) then 
                     {
                         qiujie_sum:=qiujie_sum+(* qiujie_p)/ (* qiujie_q)
                         
                     }
                     else
                     {
                         qiujie_sum:=qiujie_sum/ * qiujie_q
                     };
                     qiujie_p:=qiujie_p+2;
                     qiujie_q:=qiujie_q+2;
                     break_1$<==1 and skip
                      
                 }
                 else
                 {
                     skip
                 };
                 qiujie_m:=qiujie_m+1
                 
             }
         };
         return_1<==1 and RValue:=qiujie_sum;
         skip
     }
     else
     {
         skip
     }
     )
 };
  main_1()
 )
