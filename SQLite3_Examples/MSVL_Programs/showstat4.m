</
define p:sqlite3_column_text_call=1;
define q:sqlite3_column_bytes_call=1;
alw(q->p)
/>

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
             return<==1 and RValue:=decodeVarint_i+1;
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
         return<==1 and RValue:=9;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function main ( int RValue )
 {
     frame(verifystat,db,pstmt,main_zIdx,main_rc,main_j,main_x,main_y,main_mxHdr,main_aSample,main_nSample,main_iVal,main_zSep,main_iRow,main_2_temp$_1,main_3_4_temp$_2,main_3_4_temp$_3,main_3_8_sz,main_3_8_v,nm_1$,switch$,main_3_8_14_16_17_18_r,main_3_8_14_16_20_22_c,return,break$,continue) and (
     int continue<==0 and skip;
     int break$<==0 and skip;
     int return<==0 and skip;
     char *main_zIdx<==0 and skip;
     int main_rc,main_j,main_x,main_y,main_mxHdr and skip;
     unsigned char *main_aSample and skip;
     int main_nSample and skip;
     int main_iVal and skip;
     char *main_zSep and skip;
     int main_iRow<==0 and skip;
     main_rc:=sqlite3_open("showstat4.db",&db,RValue);
	 int verifystat<==0 and skip;
	 while(verifystat<30219095)
	 {
		verifystat:=verifystat+1
	 };
     if(main_rc!=0 OR db=0) then 
     {
         fprintf(stderr,"Cannot open database file\n") and skip
         
     }
     else 
     {
          skip 
     };
     main_rc:=sqlite3_prepare_v2(db,"SELECT tbl||'.'||idx, nEq, nLT, nDLt, sample FROM sqlite_stat4 ORDER BY 1",-1,&pstmt,0,RValue);
     if(main_rc!=0 OR pstmt=0) then 
     {
         int main_2_temp$_1 and skip;
         main_2_temp$_1:=sqlite3_errmsg(db,RValue);
         fprintf(stderr,"%s\n",main_2_temp$_1) and skip;
         sqlite3_close(db,RValue) and skip
         
     }
     else 
     {
          skip 
     };
     while(100=sqlite3_step(pstmt,RValue))
     {
         continue<==0 and skip;
         int main_3_4_temp$_2 and skip;
         main_3_4_temp$_2:=sqlite3_column_text(pstmt,0,RValue);
         if(main_zIdx=0 OR strcmp(main_zIdx,(char *)main_3_4_temp$_2)!=0) then 
         {
             if(main_zIdx) then 
             {
                 output ("\n****************************************************\n\n") and skip
             }
             else 
             {
                  skip 
             };
             sqlite3_free(main_zIdx,RValue) and skip;
             int main_3_4_temp$_3 and skip;
             main_3_4_temp$_3:=sqlite3_column_text(pstmt,0,RValue);
             main_zIdx:=sqlite3_mprintf("%s",main_3_4_temp$_3,RValue);
             main_iRow:=0
             
         }
         else 
         {
              skip 
         };
		 main_iRow:=main_iRow+1;
         //output (main_zIdx," sample ",(main_iRow+1)," ------------------------------------\n"," ------------------------------------\n") and skip;
         printf("%s sample %d ------------------------------------\n", main_zIdx, main_iRow) and skip;
		 output ("  nEq    = ",sqlite3_column_text(pstmt,1,RValue),"\n") and skip;
         output ("  nLt    = ",sqlite3_column_text(pstmt,2,RValue),"\n") and skip;
         output ("  nDLt   = ",sqlite3_column_text(pstmt,3,RValue),"\n") and skip;
         output ("  sample = x'") and skip;
         main_aSample:=sqlite3_column_blob(pstmt,4,RValue);
         main_nSample:=sqlite3_column_bytes(pstmt,4,RValue);
         main_j:=0;
         
         while(main_j<main_nSample)
         {
			 printf("%02x", main_aSample[main_j]) and skip;
             main_j:=main_j+1
             
         };
         output ("'\n          ") and skip;
         main_zSep:=" ";
         main_x:=decodeVarint(main_aSample,&main_iVal,RValue);
         if(main_iVal<main_x OR main_iVal>main_nSample) then 
         {
             output (" <error>\n") and skip;
             continue<==1 and skip
              
         }
         else 
         {
              skip 
         };
         if(continue=0)   then 
         {
             main_mxHdr<==(int)main_iVal and main_y<==main_mxHdr and skip;
             
             while(main_x<main_mxHdr)
             {
				break$<==0 and skip;
                 int main_3_8_sz and skip;
                 int main_3_8_v and skip;
                 main_x:=main_x+decodeVarint(main_aSample+main_x,&main_iVal,RValue);
                 if(main_x>main_mxHdr) then 
                 {
                     break$<==1 and skip
                  }
                 else 
                 {
                      skip 
                 };
                 if(break$=0)   then
                 {
                     if(main_iVal<0) then 
                     {
                         break$<==1 and skip
                      }
                     else 
                     {
                          skip 
                     };
                     if(break$=0)   then
                     {
                         int switch$ and skip;
                         break$<==0 and skip;
                          switch$<==0 and skip;
                          int nm_1$ and skip;
                         nm_1$ := main_iVal;
                         if (nm_1$=0 OR (switch$=1 AND break$=0 AND return=0) ) then 
                         {
                             switch$<==1 and skip;
                             main_3_8_sz:=0;
                             break$<==1 and skip
                              
                         }
                         else
                         {
                             skip
                         };
                         if (nm_1$=1 OR (switch$=1 AND break$=0 AND return=0) ) then 
                         {
							
                             switch$<==1 and skip;
                             main_3_8_sz:=1;
                             break$<==1 and skip
                              
                         }
                         else
                         {
                             skip
                         };
                         if (nm_1$=2 OR (switch$=1 AND break$=0 AND return=0) ) then 
                         {
                             switch$<==1 and skip;
                             main_3_8_sz:=2;
                             break$<==1 and skip
                              
                         }
                         else
                         {
                             skip
                         };
                         if (nm_1$=3 OR (switch$=1 AND break$=0 AND return=0) ) then 
                         {
                             switch$<==1 and skip;
                             main_3_8_sz:=3;
                             break$<==1 and skip
                              
                         }
                         else
                         {
                             skip
                         };
                         if (nm_1$=4 OR (switch$=1 AND break$=0 AND return=0) ) then 
                         {
                             switch$<==1 and skip;
                             main_3_8_sz:=4;
                             break$<==1 and skip
                              
                         }
                         else
                         {
                             skip
                         };
                         if (nm_1$=5 OR (switch$=1 AND break$=0 AND return=0) ) then 
                         {
                             switch$<==1 and skip;
                             main_3_8_sz:=6;
                             break$<==1 and skip
                              
                         }
                         else
                         {
                             skip
                         };
                         if (nm_1$=6 OR (switch$=1 AND break$=0 AND return=0) ) then 
                         {
                             switch$<==1 and skip;
                             main_3_8_sz:=8;
                             break$<==1 and skip
                              
                         }
                         else
                         {
                             skip
                         };
                         if (nm_1$=7 OR (switch$=1 AND break$=0 AND return=0) ) then 
                         {
                             switch$<==1 and skip;
                             main_3_8_sz:=8;
                             break$<==1 and skip
                              
                         }
                         else
                         {
                             skip
                         };
                         if (nm_1$=8 OR (switch$=1 AND break$=0 AND return=0) ) then 
                         {
                             switch$<==1 and skip;
                             main_3_8_sz:=0;
                             break$<==1 and skip
                              
                         }
                         else
                         {
                             skip
                         };
                         if (nm_1$=9 OR (switch$=1 AND break$=0 AND return=0) ) then 
                         {
                             switch$<==1 and skip;
                             main_3_8_sz:=0;
                             break$<==1 and skip
                              
                         }
                         else
                         {
                             skip
                         };
                         if (nm_1$=10 OR (switch$=1 AND break$=0 AND return=0) ) then 
                         {
                             switch$<==1 and skip
                             
                         }
                         else
                         {
                             skip
                         };
                         if (nm_1$=11 OR (switch$=1 AND break$=0 AND return=0) ) then 
                         {
                             switch$<==1 and skip;
                             main_3_8_sz:=0;
                             break$<==1 and skip
                              
                         }
                         else
                         {
                             skip
                         };
                         if(break$=0 AND return=0) then 
                         {
                             main_3_8_sz:=(int)(main_iVal-12)/ 2;
                             break$<==1 and skip
                              
                         }
                         else
                         {
                              skip
                         };
						
                         if(main_y+main_3_8_sz>main_nSample) then 
                         {
						  
                             break$<==1 and skip

                          }
                         else 
                         {
						
                              skip 
                         };
                             if(main_iVal=0) then 
                             {
                                 output (main_zSep,"NULL","NULL") and skip
                                 
                             }
                             else
                             {
                                 if(main_iVal=8 OR main_iVal=9) then 
                                 {
								 
									printf("%s%d", main_zSep, ((int)main_iVal)-8) and skip
                                     //output (main_zSep,((int)main_iVal)-8) and skip
                                 }
                                 else
                                 {
                                     if(main_iVal<=7) then 
                                     {

                                         main_3_8_v:=(char)main_aSample[main_y];
                                         main_j:=1;
                                         
                                         while(main_j<main_3_8_sz)
                                         {
                                             main_3_8_v:=(main_3_8_v<<8)+main_aSample[main_y+main_j];
                                             main_j:=main_j+1
                                             
                                         };
                                         if(main_iVal=7) then 
                                         {
                                             float main_3_8_14_16_17_18_r and skip;
                                             memcpy(&main_3_8_14_16_17_18_r,&main_3_8_v,8) and skip;
                                             output (main_zSep,main_3_8_14_16_17_18_r,"#g","#g") and skip
                                         }
                                         else
                                         {
											printf("%s%d", main_zSep, main_3_8_v) and skip
                                             //output (main_zSep,main_3_8_v,"") and skip
                                         }
                                     }
                                     else
                                     {
                                         if((main_iVal & 1)=0) then 
                                         {
                                             output (main_zSep,"x'","x'") and skip;
                                             main_j:=0;
                                             
                                             while(main_j<main_3_8_sz)
                                             {
                                                 output (main_aSample[main_y+main_j],"02x","02x") and skip;
                                                 main_j:=main_j+1
                                                 
                                             };
                                             output ("'") and skip
                                         }
                                         else
                                         {
                                             output (main_zSep,"'","'") and skip;
                                             main_j:=0;
                                             
                                             while(main_j<main_3_8_sz)
                                             {
                                                 char main_3_8_14_16_20_22_c<==(char)main_aSample[main_y+main_j] and skip;
                                                 if(isprint((unsigned char)(main_3_8_14_16_20_22_c),RValue)) then 
                                                 {
                                                     if(main_3_8_14_16_20_22_c='\'' OR main_3_8_14_16_20_22_c='\\') then 
                                                     {
                                                         putchar('\\') and skip
                                                     }
                                                     else 
                                                     {
                                                          skip 
                                                     };
                                                     putchar(main_3_8_14_16_20_22_c) and skip
                                                     
                                                 }
                                                 else
                                                 {
                                                     if(main_3_8_14_16_20_22_c='\n') then 
                                                     {
                                                         output ("\\n") and skip
                                                     }
                                                     else
                                                     {
                                                         if(main_3_8_14_16_20_22_c='\t') then 
                                                         {
                                                             output ("\\t") and skip
                                                         }
                                                         else
                                                         {
                                                             if(main_3_8_14_16_20_22_c='\r') then 
                                                             {
                                                                 output ("\\r") and skip
                                                             }
                                                             else
                                                             {
                                                                 //output ("\\",main_3_8_14_16_20_22_c,"03o") and skip
																 printf("\\%03o", main_3_8_14_16_20_22_c) and skip
                                                             }
                                                         }
                                                     }
                                                 };
                                                 main_j:=main_j+1
                                                 
                                             };
                                             output ("'") and skip
                                         }
                                     }
                                 }
                             };
                             main_zSep:=",";
                             main_y:=main_y+main_3_8_sz
                       
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
             break$<==0 and skip;
             output ("\n") and skip
         }
         else
         {
             skip
         }
     };
     continue<==0 and skip;
     sqlite3_free(main_zIdx,RValue) and skip;
     sqlite3_finalize(pstmt,RValue) and skip;
     sqlite3_close(db,RValue) and skip;
     return<==1 and RValue:=0;
     skip
     )
 };
  main(RValue)
