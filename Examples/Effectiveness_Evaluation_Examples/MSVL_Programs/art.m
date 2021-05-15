/*</
define p:lwidth<=320;
define q:lheight<=240;
alw(p and q)
/>*/
/*</
define p:lwidth>0;
define q:lheight>0;
som(p or q)
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
p1;(p2;p3;p4)#
/>
frame(cimage,tds,bus,lwidth,lheight,width,height,numinputs,i,j,pass_flag,highx,highy,highest_confidence,set_high,fp,winner,numf1s,numf2s,resonant,cp,numpatterns,a,b,c,d,theta,delta_t,rho,f1_layer,Y,module_1,module_2,module_3,module_4) and (
int module_1<==1 and skip;
int module_2<==0 and skip;
int module_3<==0 and skip;
int module_4<==0 and skip;
unsigned char **cimage and skip;
float **tds and skip;
float **bus and skip;
int lwidth,lheight and skip;
int width,height,numinputs and skip;
int i,j and skip;
int pass_flag and skip;
int highx[2],highy[2] and skip;
float highest_confidence[2] and skip;
int set_high[2] and skip;
FILE *fp and skip;
int winner,numf1s,numf2s,resonant,cp,numpatterns and skip;
float a,b,c,d,theta,delta_t and skip;
float rho and skip;
struct f1_neuron {
float *I and 
float W and 
float X and 
float V and 
float U and 
float P and 
float Q and 
float R 
};
f1_neuron *f1_layer and skip;
struct xyz {
float y and 
int reset 
};
xyz *Y and skip;
 function g ( int i,float RValue )
 {
     frame(g_result,return) and ( 
     int return<==0 and skip;
     float g_result and skip;
     if(i!=winner) then 
     {
         g_result:=0
     }
     else
     {
         if(Y[i].y>0) then 
         {
             g_result:=d
         }
         else
         {
             g_result:=0
         }
     };
     return<==1 and RValue:=g_result;
     skip
     )
     }; 
  function find_match (  )
 {
     frame(find_match_i) and ( 
     int find_match_i and skip;
     winner:=0;
     find_match_i:=0;
     
     while(find_match_i<numf2s)
     {
         if(Y[find_match_i].y>Y[winner].y) then 
         {
             winner:=find_match_i
         }
         else 
         {
              skip 
         };
         find_match_i:=find_match_i+1
         
     }
     )
     }; 
  function simtest ( float RValue )
 {
     frame(simtest_j,simtest_sum,simtest_norm,simtest_temp_sum,return) and ( 
     int return<==0 and skip;
     int simtest_j and skip;
     float simtest_sum,simtest_norm and skip;
     float simtest_temp_sum and skip;
     simtest_norm<==0 and simtest_sum<==simtest_norm and skip;
     simtest_j:=0;
     
     while(simtest_j<numf1s)
     {
         simtest_norm:=simtest_norm+(f1_layer[simtest_j].P*f1_layer[simtest_j].P);
         simtest_j:=simtest_j+1
         
     };
     simtest_norm:=sqrt((float)simtest_norm);
     simtest_norm:=simtest_norm*(c);
     simtest_sum:=simtest_sum+(simtest_norm);
     simtest_norm:=0;
     simtest_j:=0;
     
     while(simtest_j<numf1s)
     {
         simtest_temp_sum:=f1_layer[simtest_j].U*f1_layer[simtest_j].U;
         simtest_norm:=simtest_norm+(simtest_temp_sum);
         simtest_j:=simtest_j+1
         
     };
     simtest_norm:=sqrt((float)simtest_norm);
     simtest_sum:=simtest_sum+(simtest_norm);
     simtest_j:=0;
     
     while(simtest_j<numf1s)
     {
         f1_layer[simtest_j].R:=(f1_layer[simtest_j].U+c*f1_layer[simtest_j].P)/ simtest_sum;
         simtest_j:=simtest_j+1
         
     };
     simtest_norm:=0;
     simtest_j:=0;
     
     while(simtest_j<numf1s)
     {
         simtest_norm:=simtest_norm+(f1_layer[simtest_j].R*f1_layer[simtest_j].R);
         simtest_j:=simtest_j+1
         
     };
     simtest_norm:=sqrt((float)simtest_norm);
     return<==1 and RValue:=simtest_norm;
     skip
     )
     }; 
  function simtest2 ( float RValue )
 {
     frame(simtest2_j,simtest2_Su,simtest2_Sp,simtest2_numerator,simtest2_denom,simtest2_su,simtest2_sp,simtest2_su2,simtest2_sp2,simtest2_sup,simtest2_r,simtest2_e,return) and ( 
     int return<==0 and skip;
     int simtest2_j and skip;
     float simtest2_Su,simtest2_Sp,simtest2_numerator,simtest2_denom and skip;
     float simtest2_su,simtest2_sp and skip;
     float simtest2_su2,simtest2_sp2 and skip;
     float simtest2_sup and skip;
     float simtest2_r and skip;
     float simtest2_e<==0.0000000001 and skip;
     simtest2_numerator<==0.0 and simtest2_sp2<==simtest2_numerator and simtest2_su2<==simtest2_sp2 and simtest2_sup<==simtest2_su2 and simtest2_sp<==simtest2_sup and simtest2_su<==simtest2_sp and skip;
     simtest2_j:=0;
     
     while(simtest2_j<numf1s)
     {
         simtest2_su:=simtest2_su+(f1_layer[simtest2_j].U);
         simtest2_sp:=simtest2_sp+(f1_layer[simtest2_j].P);
         simtest2_su2:=simtest2_su2+(f1_layer[simtest2_j].U*f1_layer[simtest2_j].U);
         simtest2_sp2:=simtest2_sp2+(f1_layer[simtest2_j].P*f1_layer[simtest2_j].P);
         simtest2_sup:=simtest2_sup+(f1_layer[simtest2_j].U*f1_layer[simtest2_j].P);
         simtest2_j:=simtest2_j+1
         
     };
     simtest2_Su:=((float)numf1s*simtest2_su2-simtest2_su*simtest2_su)/ ((float)numf1s*((float)numf1s-1.0));
     simtest2_Su:=sqrt(simtest2_Su);
     simtest2_Sp:=((float)numf1s*simtest2_sp2-simtest2_sp*simtest2_sp)/ ((float)numf1s*((float)numf1s-1.0));
     simtest2_Sp:=sqrt(simtest2_Sp);
     simtest2_numerator:=(float)numf1s*simtest2_sup-simtest2_su*simtest2_sp;
     simtest2_denom:=sqrt((float)numf1s*simtest2_su2-simtest2_su*simtest2_su)*sqrt((float)numf1s*simtest2_sp2-simtest2_sp*simtest2_sp);
     simtest2_r:=(simtest2_numerator+simtest2_e)/ (simtest2_denom+simtest2_e);
     if((simtest2_numerator=0) OR (simtest2_denom=0)) then 
     {
         fprintf(stderr,"potential div by zero") and skip;
         simtest2_r:=1
         
     }
     else 
     {
          skip 
     };
     if((simtest2_numerator!=0) AND (simtest2_denom=0)) then 
     {
         fprintf(stderr,"div by zero") and skip;
         simtest2_r:=1
         
     }
     else 
     {
          skip 
     };
     simtest2_r:=simtest2_r*(simtest2_r);
     return<==1 and RValue:=simtest2_r;
     skip
     )
     }; 
  function weightadj (  )
 {
     frame(weightadj_i,weightadj_j,weightadj_k,weightadj_temp,weightadj_er) and ( 
     int weightadj_i,weightadj_j,weightadj_k and skip;
     float weightadj_temp and skip;
     float weightadj_er<==0.000000001 and skip;
     weightadj_i:=winner;
     weightadj_k:=0;
     
     while(weightadj_k<1)
     {
         resonant:=0;
         weightadj_j:=0;
         
         while(weightadj_j<numf1s)
         {
             weightadj_temp:=tds[weightadj_j,weightadj_i];
             tds[weightadj_j,weightadj_i]:=tds[weightadj_j,weightadj_i]+(g(weightadj_i,RValue)*(f1_layer[weightadj_j].P-tds[weightadj_j,weightadj_i])*delta_t);
             if(fabs(weightadj_temp-tds[weightadj_j,weightadj_i])<=weightadj_er) then 
             {
                 resonant:=1
             }
             else 
             {
                  skip 
             };
             weightadj_j:=weightadj_j+1
             
         };
         weightadj_j:=0;
         
         while(weightadj_j<numf1s)
         {
             weightadj_temp:=bus[weightadj_j,weightadj_i];
             bus[weightadj_j,weightadj_i]:=bus[weightadj_j,weightadj_i]+(g(weightadj_i,RValue)*(f1_layer[weightadj_j].P-bus[weightadj_j,weightadj_i])*delta_t);
             if((fabs(weightadj_temp-bus[weightadj_j,weightadj_i])<=weightadj_er) AND resonant) then 
             {
                 resonant:=1
                 
             }
             else
             {
                 resonant:=0
             };
             weightadj_j:=weightadj_j+1
             
         };
         weightadj_k:=weightadj_k+1
         
     }
     )
     }; 
  function init_globs ( int mode )
 {
     if(mode=0) then 
     {
         a:=255;
         b:=0.0;
         c:=0.11;
         d:=0.9;
         theta:=1/ sqrt((float)numf1s);
         delta_t:=0.1;
         rho:=0.70
     }
     else
     {
         a:=255;
         b:=10.0;
         c:=0.11;
         d:=0.9;
         theta:=1/ sqrt((float)numf1s);
         delta_t:=0.7;
         rho:=0.95
     }
     
 };
 function init_net (  )
 {
     frame(init_net_i) and ( 
     int init_net_i and skip;
     f1_layer:=(f1_neuron *)malloc(numf1s*sizeof(f1_neuron));
     init_net_i:=0;
     
     while(init_net_i<numf1s)
     {
         f1_layer[init_net_i].I:=(float *)malloc(2*sizeof(float));
         f1_layer[init_net_i].W:=0;
         f1_layer[init_net_i].X:=0;
         f1_layer[init_net_i].V:=0;
         f1_layer[init_net_i].U:=0;
         f1_layer[init_net_i].P:=0;
         f1_layer[init_net_i].Q:=0;
         f1_layer[init_net_i].R:=0;
         init_net_i:=init_net_i+1
         
     };
     Y:=(xyz *)malloc(numf2s*sizeof(xyz))
     )
     }; 
  function analog_conv (  )
 {
     frame(analog_conv_j,analog_conv_lines,analog_conv_k,analog_conv_x1,analog_conv_x2,analog_conv_y1,analog_conv_y2) and ( 
     int analog_conv_j,analog_conv_lines,analog_conv_k and skip;
     int analog_conv_x1,analog_conv_x2 and skip;
     float analog_conv_y1,analog_conv_y2 and skip;
     fscanf(fp,"%i",&analog_conv_lines) and skip;
     analog_conv_j:=0;
     
     while(analog_conv_j<analog_conv_lines)
     {
         fscanf(fp,"%i %f %i %f",&analog_conv_x1,&analog_conv_y1,&analog_conv_x2,&analog_conv_y2) and skip;
         analog_conv_k:=analog_conv_x1;
         
         while(analog_conv_k<=analog_conv_x2)
         {
             f1_layer[analog_conv_k].I[cp]:=((analog_conv_y2-analog_conv_y1)/ (analog_conv_x2-analog_conv_x1)*(analog_conv_k-analog_conv_x2))+analog_conv_y2;
             analog_conv_k:=analog_conv_k+1
             
         };
         analog_conv_j:=analog_conv_j+1
         
     }
     )
     }; 
  function get_pat (  )
 {
     frame(get_pat_i) and ( 
     int get_pat_i and skip;
     get_pat_i:=0;
     
     while(get_pat_i<numf1s)
     {
         fscanf(fp,"%f",&f1_layer[get_pat_i].I[cp]) and skip;
         get_pat_i:=get_pat_i+1
         
     }
     )
     }; 
  function show_pat (  )
 {
     frame(show_pat_i) and ( 
     int show_pat_i and skip;
     show_pat_i:=0;
     
     while(show_pat_i<numf1s)
     {
         if((show_pat_i % 5)=0) then 
         {
             output ("\n") and skip
         }
         else 
         {
              skip 
         };
         output (" ",f1_layer[show_pat_i].I[cp]," ") and skip;
         show_pat_i:=show_pat_i+1
         
     };
     output ("\n\n") and skip
     )
     }; 
  function reset_nodes (  )
 {
     frame(reset_nodes_i) and ( 
     int reset_nodes_i and skip;
     reset_nodes_i:=0;
     
     while(reset_nodes_i<numf1s)
     {
         f1_layer[reset_nodes_i].W:=0.0;
         f1_layer[reset_nodes_i].X:=0.0;
         f1_layer[reset_nodes_i].V:=0.0;
         f1_layer[reset_nodes_i].U:=0.0;
         f1_layer[reset_nodes_i].P:=0.0;
         f1_layer[reset_nodes_i].Q:=0.0;
         f1_layer[reset_nodes_i].R:=0.0;
         reset_nodes_i:=reset_nodes_i+1
         
     };
     reset_nodes_i:=0;
     
     while(reset_nodes_i<numf2s)
     {
         Y[reset_nodes_i].y:=0.0;
         Y[reset_nodes_i].reset:=0;
         reset_nodes_i:=reset_nodes_i+1
         
     };
     winner:=0;
     resonant:=0
     )
     }; 
  function reset_nodes2 (  )
 {
     frame(reset_nodes2_i) and ( 
     int reset_nodes2_i and skip;
     reset_nodes2_i:=0;
     
     while(reset_nodes2_i<numf1s)
     {
         f1_layer[reset_nodes2_i].W:=0.0;
         f1_layer[reset_nodes2_i].X:=0.0;
         f1_layer[reset_nodes2_i].V:=0.0;
         f1_layer[reset_nodes2_i].U:=0.0;
         f1_layer[reset_nodes2_i].P:=0.0;
         f1_layer[reset_nodes2_i].Q:=0.0;
         f1_layer[reset_nodes2_i].R:=0.0;
         reset_nodes2_i:=reset_nodes2_i+1
         
     };
     reset_nodes2_i:=0;
     
     while(reset_nodes2_i<numf2s)
     {
         Y[reset_nodes2_i].y:=0.0;
         reset_nodes2_i:=reset_nodes2_i+1
         
     };
     winner:=0;
     resonant:=0
     )
     }; 
  function print_weights (  )
 {
     frame(print_weights_i,print_weights_j) and ( 
     int print_weights_i,print_weights_j and skip;
     output ("============  TOP down WEIGHTS ==============\n") and skip;
     print_weights_i:=0;
     
     while(print_weights_i<numf1s)
     {
         print_weights_j:=0;
         
         while(print_weights_j<numf2s)
         {
             if(print_weights_j=(numf2s-1)) then 
             {
                 output (" ",tds[print_weights_i,print_weights_j],"\n") and skip
             }
             else
             {
                 output (" ",tds[print_weights_i,print_weights_j]," ") and skip
             };
             print_weights_j:=print_weights_j+1
             
         };
         print_weights_i:=print_weights_i+1
         
     };
     output ("============  BOTTOM up WEIGHTS ==============\n") and skip;
     print_weights_i:=0;
     
     while(print_weights_i<numf1s)
     {
         print_weights_j:=0;
         
         while(print_weights_j<numf2s)
         {
             if(print_weights_j=(numf2s-1)) then 
             {
                 output (" ",bus[print_weights_i,print_weights_j],"\n") and skip
             }
             else
             {
                 output (" ",bus[print_weights_i,print_weights_j]," ") and skip
             };
             print_weights_j:=print_weights_j+1
             
         };
         print_weights_i:=print_weights_i+1
         
     }
     )
     }; 
  function print_f12 (  )
 {
     frame(print_f12_j) and ( 
     int print_f12_j and skip;
     output ("\n\n") and skip;
     print_f12_j:=0;
     
     while(print_f12_j<numf2s)
     {
         output (" j = ",print_f12_j,"i  Y= ",Y[print_f12_j].y,"\n") and skip;
         print_f12_j:=print_f12_j+1
         
     }
     )
     }; 
  function train_match ( int spot )
 {
     frame(train_match_j,train_match_matched,train_match_f1res,train_match_mt,train_match_ti,train_match_tj,train_match_tresult,train_match_tnorm,train_match_xr,train_match_qr,train_match_tsum,train_match_ttemp,train_match_matchtest,train_match_match_confidence) and ( 
     int train_match_j,train_match_matched,train_match_f1res,train_match_mt and skip;
     int train_match_ti,train_match_tj,train_match_tresult and skip;
     float train_match_tnorm and skip;
     float train_match_xr,train_match_qr,train_match_tsum,train_match_ttemp and skip;
     char train_match_matchtest and skip;
     float train_match_match_confidence and skip;
     train_match_f1res:=0;
     reset_nodes();
     cp:=spot;
     train_match_matched:=0;
     while(!train_match_matched)
     {
         train_match_f1res:=0;
         train_match_j:=0;
         
         while(train_match_j<9 AND !train_match_f1res)
         {
             train_match_tnorm:=0;
             train_match_ti:=0;
             
             while(train_match_ti<numf1s)
             {
                 f1_layer[train_match_ti].W:=f1_layer[train_match_ti].I[cp]+a*(f1_layer[train_match_ti].U);
                 train_match_tnorm:=train_match_tnorm+(f1_layer[train_match_ti].W*f1_layer[train_match_ti].W);
                 train_match_ti:=train_match_ti+1
                 
             };
             train_match_tnorm:=sqrt((float)train_match_tnorm);
             train_match_tj:=0;
             
             while(train_match_tj<numf1s)
             {
                 f1_layer[train_match_tj].X:=f1_layer[train_match_tj].W/ train_match_tnorm;
                 train_match_tj:=train_match_tj+1
                 
             };
             train_match_tnorm:=0;
             train_match_ti:=0;
             
             while(train_match_ti<numf1s)
             {
                 if(f1_layer[train_match_ti].X<theta) then 
                 {
                     train_match_xr:=0
                 }
                 else
                 {
                     train_match_xr:=f1_layer[train_match_ti].X
                 };
                 if(f1_layer[train_match_ti].Q<theta) then 
                 {
                     train_match_qr:=0
                 }
                 else
                 {
                     train_match_qr:=f1_layer[train_match_ti].Q
                 };
                 f1_layer[train_match_ti].V:=train_match_xr+b*train_match_qr;
                 train_match_tnorm:=train_match_tnorm+(f1_layer[train_match_ti].V*f1_layer[train_match_ti].V);
                 train_match_ti:=train_match_ti+1
                 
             };
             train_match_tnorm:=sqrt((float)train_match_tnorm);
             train_match_tj:=0;
             
             while(train_match_tj<numf1s)
             {
                 f1_layer[train_match_tj].U:=f1_layer[train_match_tj].V/ train_match_tnorm;
                 train_match_tj:=train_match_tj+1
                 
             };
             train_match_tnorm:=0;
             train_match_tsum:=0;
             train_match_tresult:=1;
             train_match_ti:=0;
             
             while(train_match_ti<numf1s)
             {
                 train_match_tsum:=0;
                 train_match_ttemp:=f1_layer[train_match_ti].P;
                 train_match_tj:=spot;
                 
                 while(train_match_tj<numf2s)
                 {
                     if((train_match_tj=winner) AND (Y[train_match_tj].y>0)) then 
                     {
                         train_match_tsum:=train_match_tsum+(tds[train_match_ti,train_match_tj]*d)
                     }
                     else 
                     {
                          skip 
                     };
                     train_match_tj:=train_match_tj+1
                     
                 };
                 f1_layer[train_match_ti].P:=f1_layer[train_match_ti].U+train_match_tsum;
                 train_match_tnorm:=train_match_tnorm+(f1_layer[train_match_ti].P*f1_layer[train_match_ti].P);
                 if(train_match_ttemp!=f1_layer[train_match_ti].P) then 
                 {
                     train_match_tresult:=0
                 }
                 else 
                 {
                      skip 
                 };
                 train_match_ti:=train_match_ti+1
                 
             };
             train_match_f1res:=train_match_tresult;
             train_match_tnorm:=sqrt((float)train_match_tnorm);
             train_match_tj:=0;
             
             while(train_match_tj<numf1s)
             {
                 f1_layer[train_match_tj].Q:=f1_layer[train_match_tj].P;
                 train_match_tj:=train_match_tj+1
                 
             };
             train_match_tj:=spot;
             
             while(train_match_tj<numf2s)
             {
                 Y[train_match_tj].y:=0;
                 if(!Y[train_match_tj].reset) then 
                 {
                     train_match_ti:=0;
                     
                     while(train_match_ti<numf1s)
                     {
                         Y[train_match_tj].y:=Y[train_match_tj].y+(f1_layer[train_match_ti].P*bus[train_match_ti,train_match_tj]);
                         train_match_ti:=train_match_ti+1
                         
                     }
                 }
                 else 
                 {
                      skip 
                 };
                 train_match_tj:=train_match_tj+1
                 
             };
             winner:=0;
             train_match_ti:=spot;
             
             while(train_match_ti<numf2s)
             {
                 if(Y[train_match_ti].y>Y[winner].y) then 
                 {
                     winner:=train_match_ti
                 }
                 else 
                 {
                      skip 
                 };
                 train_match_ti:=train_match_ti+1
                 
             };
             train_match_j:=train_match_j+1
             
         };
         train_match_match_confidence:=simtest(RValue);
         if(train_match_match_confidence>rho) then 
         {
             weightadj();
             train_match_matched:=1
         }
         else
         {
             Y[winner].y:=0;
             Y[winner].reset:=1;
             train_match_matchtest:=0;
             train_match_mt:=spot;
             
             while(train_match_mt<numf2s)
             {
                 if(Y[train_match_mt].reset=0) then 
                 {
                     train_match_matchtest:=1
                 }
                 else 
                 {
                      skip 
                 };
                 train_match_mt:=train_match_mt+1
                 
             };
             if(train_match_matchtest) then 
             {
                 find_match()
             }
             else
             {
                 train_match_matched:=1
             }
         }
     }
     )
     }; 
  function match (  )
 {
     frame(match_j,match_matched,match_f1res,match_mt,match_ti,match_tj,match_tresult,match_tnorm,match_xr,match_qr,match_tsum,match_ttemp,match_matchtest,match_match_confidence) and ( 
     int match_j,match_matched,match_f1res,match_mt and skip;
     int match_ti,match_tj,match_tresult and skip;
     float match_tnorm and skip;
     float match_xr,match_qr,match_tsum,match_ttemp and skip;
     char match_matchtest and skip;
     float match_match_confidence and skip;
     match_f1res:=0;
     cp:=0;
     reset_nodes();
     match_matched:=0;
     while(!match_matched)
     {
         reset_nodes2();
         match_f1res:=0;
         match_j:=0;
         
         while(match_j<9 AND !match_f1res)
         {
             match_tnorm:=0;
             match_ti:=0;
             
             while(match_ti<numf1s)
             {
                 f1_layer[match_ti].W:=f1_layer[match_ti].I[cp]+a*(f1_layer[match_ti].U);
                 match_tnorm:=match_tnorm+(f1_layer[match_ti].W*f1_layer[match_ti].W);
                 match_ti:=match_ti+1
                 
             };
             match_tnorm:=sqrt((float)match_tnorm);
             match_tj:=0;
             
             while(match_tj<numf1s)
             {
                 f1_layer[match_tj].X:=f1_layer[match_tj].W/ match_tnorm;
                 match_tj:=match_tj+1
                 
             };
             match_tnorm:=0;
             match_ti:=0;
             
             while(match_ti<numf1s)
             {
                 if(f1_layer[match_ti].X<theta) then 
                 {
                     match_xr:=0
                 }
                 else
                 {
                     match_xr:=f1_layer[match_ti].X
                 };
                 if(f1_layer[match_ti].Q<theta) then 
                 {
                     match_qr:=0
                 }
                 else
                 {
                     match_qr:=f1_layer[match_ti].Q
                 };
                 f1_layer[match_ti].V:=match_xr+b*match_qr;
                 match_tnorm:=match_tnorm+(f1_layer[match_ti].V*f1_layer[match_ti].V);
                 match_ti:=match_ti+1
                 
             };
             match_tnorm:=sqrt((float)match_tnorm);
             match_tj:=0;
             
             while(match_tj<numf1s)
             {
                 f1_layer[match_tj].U:=f1_layer[match_tj].V/ match_tnorm;
                 match_tj:=match_tj+1
                 
             };
             match_tnorm:=0;
             match_tsum:=0;
             match_tresult:=1;
             match_ti:=0;
             
             while(match_ti<numf1s)
             {
                 match_tsum:=0;
                 match_ttemp:=f1_layer[match_ti].P;
                 match_tj:=0;
                 
                 while(match_tj<numf2s)
                 {
                     if((match_tj=winner) AND (Y[match_tj].y>0)) then 
                     {
                         match_tsum:=match_tsum+(tds[match_ti,match_tj]*d)
                     }
                     else 
                     {
                          skip 
                     };
                     match_tj:=match_tj+1
                     
                 };
                 f1_layer[match_ti].P:=f1_layer[match_ti].U+match_tsum;
                 match_tnorm:=match_tnorm+(f1_layer[match_ti].P*f1_layer[match_ti].P);
                 if(match_ttemp!=f1_layer[match_ti].P) then 
                 {
                     match_tresult:=0
                 }
                 else 
                 {
                      skip 
                 };
                 match_ti:=match_ti+1
                 
             };
             match_f1res:=match_tresult;
             match_tnorm:=sqrt((float)match_tnorm);
             match_tj:=0;
             
             while(match_tj<numf1s)
             {
                 f1_layer[match_tj].Q:=f1_layer[match_tj].P;
                 match_tj:=match_tj+1
                 
             };
             match_tj:=0;
             
             while(match_tj<numf2s)
             {
                 Y[match_tj].y:=0;
                 if(!Y[match_tj].reset) then 
                 {
                     match_ti:=0;
                     
                     while(match_ti<numf1s)
                     {
                         Y[match_tj].y:=Y[match_tj].y+(f1_layer[match_ti].P*bus[match_ti,match_tj]);
                         match_ti:=match_ti+1
                         
                     }
                 }
                 else 
                 {
                      skip 
                 };
                 match_tj:=match_tj+1
                 
             };
             winner:=0;
             match_ti:=0;
             
             while(match_ti<numf2s)
             {
                 if(Y[match_ti].y>Y[winner].y) then 
                 {
                     winner:=match_ti
                 }
                 else 
                 {
                      skip 
                 };
                 match_ti:=match_ti+1
                 
             };
             match_j:=match_j+1
             
         };
         match_match_confidence:=simtest2(RValue);
         if(match_match_confidence>rho) then 
         {
             if(winner!=numf2s-1) then 
             {
                 pass_flag:=1;
                 fprintf(stdout,"F2 neuron %d passes vigilance with a value of %0.4f\n",winner,match_match_confidence) and skip;
                 print_f12();
                 if(match_match_confidence>highest_confidence[winner]) then 
                 {
                     highest_confidence[winner]:=match_match_confidence;
                     set_high[winner]:=1
                     
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
             match_matched:=1
         }
         else
         {
             Y[winner].y:=0;
             Y[winner].reset:=1;
             match_matchtest:=0;
             match_mt:=0;
             
             while(match_mt<numf2s)
             {
                 if(Y[match_mt].reset=0) then 
                 {
                     match_matchtest:=1
                 }
                 else 
                 {
                      skip 
                 };
                 match_mt:=match_mt+1
                 
             };
             if(match_matchtest) then 
             {
                 find_match()
             }
             else
             {
                 match_matched:=1
             }
         }
     }
     )
     }; 
  function loadimage ( char *input_file )
 {
     frame(loadimage_i,loadimage_j,loadimage_fd,loadimage_buffer,loadimage_superbuffer) and ( 
	 module_3<==1 and skip;
     int loadimage_i,loadimage_j and skip;
     int loadimage_fd and skip;
     char loadimage_buffer[64] and skip;
     char *loadimage_superbuffer and skip;
     loadimage_fd:=_open("E:/input/in.in\0",0,0) ;
     if((loadimage_fd)=-1) then 
     {
         fprintf(stderr,"Error opening %s\n",input_file) and skip
         
     }
     else 
     {
          skip 
     };
     //read(loadimage_fd,loadimage_buffer,8,RValue) and skip;
     //read(loadimage_fd,loadimage_buffer,4,RValue) and skip;
	  
     loadimage_i:=0;
     
     while(loadimage_i<4)
     {
         if(loadimage_buffer[loadimage_i]!=' ') then 
         {
             width:=width*10+loadimage_buffer[loadimage_i]-'0'
         }
         else 
         {
              skip 
         };
         loadimage_i:=loadimage_i+1
         
     };
     //read(loadimage_fd,loadimage_buffer,4,RValue) and skip;
     loadimage_i:=0;
     
     while(loadimage_i<4)
     {
         if(loadimage_buffer[loadimage_i]!=' ') then 
         {
             height:=height*10+loadimage_buffer[loadimage_i]-'0'
         }
         else 
         {
              skip 
         };
         loadimage_i:=loadimage_i+1
         
     };
	 width<==10 and skip;
	 height<==10 and skip;
     loadimage_superbuffer:=(char *)malloc(width*height*sizeof(char));
     cimage:=(unsigned char **)malloc(height*4);
     loadimage_i:=0;
    
     while(loadimage_i<height)
     {
         cimage[loadimage_i]:=(unsigned char *)malloc(width*sizeof(unsigned char));
         loadimage_i:=loadimage_i+1
         
     };
     //read(loadimage_fd,loadimage_superbuffer,width*height,RValue) and skip;
     loadimage_i:=0;
     
     while(loadimage_i<height)
     {
         loadimage_j:=0;
         
         while(loadimage_j<width)
         {
             cimage[loadimage_i,loadimage_j]:=loadimage_superbuffer[loadimage_i*width+loadimage_j];
             loadimage_j:=loadimage_j+1
             
         };
         loadimage_i:=loadimage_i+1
         
     };
	 skip
     )
     }; 
  function load_weights ( char *weightfile )
 {
     frame(load_weights_a,load_weights_i,load_weights_j,load_weights_inp) and ( 
     float load_weights_a and skip;
     int load_weights_i,load_weights_j and skip;
     FILE *load_weights_inp and skip;
     load_weights_inp:=fopen(weightfile,"r") ;
     if((load_weights_inp)=NULL) then 
     {
         fprintf(stderr,"Unable to open %s\n",weightfile) and skip
         
     }
     else 
     {
          skip 
     };
     output ("made it to load_weights\n") and skip;
     fscanf(load_weights_inp,"%d %d",&lwidth,&lheight) and skip;
     numinputs<==lwidth*lheight and numf1s<==numinputs and skip;
     numf2s:=numpatterns+1;
     alloc_td_bu();
     load_weights_j:=0;
     load_weights_i:=0;
     
     while(load_weights_i<numf1s)
     {
         fscanf(load_weights_inp,"%le",&load_weights_a) and skip;
         tds[load_weights_i,load_weights_j]<==load_weights_a and bus[load_weights_i,load_weights_j]<==tds[load_weights_i,load_weights_j] and skip;
         load_weights_i:=load_weights_i+1
         
     }
     )
     }; 
  function alloc_td_bu (  )
 {
     bus:=(float **)malloc(numf1s*sizeof(float *));
     tds:=(float **)malloc(numf1s*sizeof(float *));
     i:=0;
     
     while(i<numf1s)
     {
         bus[i]:=(float *)malloc(numf2s*sizeof(float));
         tds[i]:=(float *)malloc(numf2s*sizeof(float));
         i:=i+1
         
     }
     
 };
 function init_td ( int start )
 {
     frame(init_td_i,init_td_j) and ( 
     int init_td_i,init_td_j and skip;
     init_td_i:=0;
     
     while(init_td_i<numf1s)
     {
         init_td_j:=start;
         
         while(init_td_j<numf2s)
         {
             tds[init_td_i,init_td_j]:=0.0;
             init_td_j:=init_td_j+1
             
         };
         init_td_i:=init_td_i+1
         
     }
     )
     }; 
  function init_bu ( int start )
 {
     frame(init_bu_i,init_bu_j) and ( 
     int init_bu_i,init_bu_j and skip;
     init_bu_i:=0;
     
     while(init_bu_i<numf1s)
     {
         init_bu_j:=start;
         
         while(init_bu_j<numf2s)
         {
             bus[init_bu_i,init_bu_j]:=1/ (1.0-d)/ sqrt((float)numf1s);
             init_bu_j:=init_bu_j+1
             
         };
         init_bu_i:=init_bu_i+1
         
     }
     )
     }; 
  function load_train ( char *trainfile,int mode,int objects )
 {
     frame(load_train_i,load_train_fd,load_train_buffer,load_train_superbuffer,load_train_t,load_train_spot) and ( 
     int load_train_i and skip;
     int load_train_fd and skip;
     char load_train_buffer[64] and skip;
     char *load_train_superbuffer and skip;
     unsigned char load_train_t and skip;
     int load_train_spot and skip;
     if(mode=1) then 
     {
         load_train_spot:=0
         
     }
     else
     {
         load_train_spot:=1
     };
     load_train_fd:=_open("E:\\input\\hc.img\0",0,0);
     if((load_train_fd)=-1) then 
     {
         fprintf(stderr,"Error opening %s\n",trainfile) and skip
         
     }
     else 
     {
          skip 
     };
     lwidth:=0;
     lheight:=0;
     //read(load_train_fd,load_train_buffer,8,RValue) and skip;
     //read(load_train_fd,load_train_buffer,4,RValue) and skip;
     load_train_i:=0;
     
     while(load_train_i<4)
     {
         if(load_train_buffer[load_train_i]!=' ') then 
         {
             lwidth:=lwidth*10+load_train_buffer[load_train_i]-'0'
         }
         else 
         {
              skip 
         };
         load_train_i:=load_train_i+1
         
     };
     //read(load_train_fd,load_train_buffer,4,RValue) and skip;
     load_train_i:=0;
     
     while(load_train_i<4)
     {
         if(load_train_buffer[load_train_i]!=' ') then 
         {
             lheight:=lheight*10+load_train_buffer[load_train_i]-'0'
         }
         else 
         {
              skip 
         };
         load_train_i:=load_train_i+1
         
     };
	 lheight<==10 and skip;
	 lwidth<==10 and skip;
     if(mode=1) then 
     {
         numinputs<==lwidth*lheight and numf1s<==numinputs and skip;
         numf2s:=objects+1;
         init_globs(1);
         init_net()
         
     }
     else
     {
         if((lwidth*lheight)!=numf1s) then 
         {
             fprintf(stderr,"Dimensions of first image do not match") and skip;
             fprintf(stderr," dimensions of second.\n") and skip
             
         }
         else 
         {
              skip 
         }
     };
     load_train_superbuffer:=(char *)malloc(lwidth*lheight*sizeof(char));
     //read(load_train_fd,load_train_superbuffer,lwidth*lheight,RValue) and skip;
     load_train_i:=0;
     
     while(load_train_i<lheight*lwidth)
     {
         load_train_t:=load_train_superbuffer[load_train_i];
         f1_layer[load_train_i].I[load_train_spot]:=(float)load_train_t;
         load_train_i:=load_train_i+1
         
     };
	 free(load_train_superbuffer) and skip
     )
     }; 
  function sim_other_objects ( int low,int high,int stop )
 {
     frame(sim_other_objects_i,sim_other_objects_j,sim_other_objects_noise1,sim_other_objects_noise2,return) and ( 
     int return<==0 and skip;
     int sim_other_objects_i,sim_other_objects_j and skip;
     int sim_other_objects_noise1 and skip;
     float sim_other_objects_noise2 and skip;
     if(high<=low) then 
     {
          return<==1 and skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         srand(10,RValue) and skip;
         sim_other_objects_i:=low;
         
         while(sim_other_objects_i<high)
         {
             sim_other_objects_j:=0;
             
             while(sim_other_objects_j<numf1s)
             {
                 if(sim_other_objects_i % low) then 
                 {
                     tds[sim_other_objects_j,sim_other_objects_i]:=tds[sim_other_objects_j,0];
                     tds[sim_other_objects_j,sim_other_objects_i]:=bus[sim_other_objects_j,0]
                     
                 }
                 else
                 {
                     tds[sim_other_objects_j,sim_other_objects_i]:=tds[sim_other_objects_j,1];
                     tds[sim_other_objects_j,sim_other_objects_i]:=bus[sim_other_objects_j,1]
                 };
                 sim_other_objects_j:=sim_other_objects_j+1
                 
             };
             sim_other_objects_i:=sim_other_objects_i+1
             
         };
         sim_other_objects_i:=low;
         
         while(sim_other_objects_i<high)
         {
             sim_other_objects_j:=0;
             
             while(sim_other_objects_j<numf1s)
             {
                 sim_other_objects_noise1:=rand(RValue) & 65535;
                 sim_other_objects_noise2:=(float)sim_other_objects_noise1/ (float)65535;
                 tds[sim_other_objects_j,sim_other_objects_i]:=tds[sim_other_objects_j,sim_other_objects_i]+(sim_other_objects_noise2);
                 bus[sim_other_objects_j,sim_other_objects_i]:=bus[sim_other_objects_j,sim_other_objects_i]+(sim_other_objects_noise2);
                 sim_other_objects_j:=sim_other_objects_j+1
                 
             };
             sim_other_objects_i:=sim_other_objects_i+1
             
         };
         sim_other_objects_i:=low;
         
         while(sim_other_objects_i<high)
         {
             sim_other_objects_j:=0;
             
             while(sim_other_objects_j<numf1s)
             {
                 fprintf(stderr,"%d %d %f\n",sim_other_objects_i,sim_other_objects_j,tds[sim_other_objects_j,sim_other_objects_i]) and skip;
                 sim_other_objects_j:=sim_other_objects_j+1
                 
             };
             sim_other_objects_i:=sim_other_objects_i+1
             
         }
     }
     else
     {
         skip
     }
     )
     }; 
  function setup_base_pattern ( int spot )
 {
     frame(setup_base_pattern_i,setup_base_pattern_j) and ( 
     int setup_base_pattern_i,setup_base_pattern_j and skip;
     setup_base_pattern_i:=0;
     
     while(setup_base_pattern_i<numf1s)
     {
         setup_base_pattern_j:=spot;
         
         while(setup_base_pattern_j<numf2s)
         {
             bus[setup_base_pattern_i,setup_base_pattern_j]<==1.0/ sqrt((float)numf1s)/ (1-d) and tds[setup_base_pattern_i,setup_base_pattern_j]<==bus[setup_base_pattern_i,setup_base_pattern_j] and skip;
             setup_base_pattern_j:=setup_base_pattern_j+1
             
         };
         setup_base_pattern_i:=setup_base_pattern_i+1
         
     }
     )
     }; 
  function scan_recognize ( int startx,int starty,int endx,int endy,int stride )
 {
     frame(scan_recognize_i,scan_recognize_j,scan_recognize_m,scan_recognize_n,scan_recognize_k) and ( 
	 module_4<==1 and skip;
     int scan_recognize_i,scan_recognize_j,scan_recognize_m,scan_recognize_n and skip;
     int scan_recognize_k and skip;
     if((starty>(height-lheight+1)) OR (startx>(width-lwidth+1))) then 
     {
         fprintf(stderr,"Startx %d or Starty %d is out of range\n",startx,starty) and skip
         
     }
     else 
     {
          skip 
     };
     if((endy>(height-lheight+1)) OR (endx>(width-lwidth+1))) then 
     {
         fprintf(stderr,"endx %d or endy %d is out of range\n",endx,endy) and skip
         
     }
     else 
     {
          skip 
     };
     scan_recognize_j:=starty;
     
     while(scan_recognize_j<endy)
     {
         scan_recognize_i:=startx;
         
         while(scan_recognize_i<endx)
         {
             scan_recognize_k:=0;
             scan_recognize_m:=scan_recognize_j;
             
             while(scan_recognize_m<(lheight+scan_recognize_j))
             {
                 scan_recognize_n:=scan_recognize_i;
                 
                 while(scan_recognize_n<(lwidth+scan_recognize_i))
                 {
                     f1_layer[scan_recognize_k].I[0]:=cimage[scan_recognize_m,scan_recognize_n];
                     scan_recognize_k:=scan_recognize_k+1;
                     scan_recognize_n:=scan_recognize_n+1
                     
                 };
                 scan_recognize_m:=scan_recognize_m+1
                 
             };
             pass_flag:=0;
             match();
             if(pass_flag=1) then 
             {
                 if(set_high[0]=1) then 
                 {
                     highx[0]:=scan_recognize_i;
                     highy[0]:=scan_recognize_j;
                     set_high[0]:=0
                     
                 }
                 else 
                 {
                      skip 
                 };
                 if(set_high[1]=1) then 
                 {
                     highx[1]:=scan_recognize_i;
                     highy[1]:=scan_recognize_j;
                     set_high[1]:=0
                     
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
             scan_recognize_i:=scan_recognize_i+stride
             
         };
         scan_recognize_j:=scan_recognize_j+stride
         
     }
     )
     }; 
  function main ( int RValue )
 {
     frame(main_k,main_startx,main_starty,main_endx,main_endy,main_stride,main_objects,main_arg_index,main_scanfile,main_weightfile,main_trainfile1,main_trainfile2,return) and (
	 module_2<==1 and skip;
     int return<==0 and skip;
     int main_k and skip;
     int main_startx,main_starty and skip;
     int main_endx,main_endy and skip;
     int main_stride and skip;
     int main_objects and skip;
     int main_arg_index and skip;
     char *main_scanfile<==NULL and skip;
     char *main_weightfile<==NULL and skip;
     char *main_trainfile1<==NULL and skip;
     char *main_trainfile2<==NULL and skip;
     main_stride:=10;
     main_startx:=0;
     main_starty:=0;
     main_endy:=0;
     main_endx:=0;
     main_objects:=0;
     main_arg_index:=1;
     main_scanfile:="E:\\input\\in.in";
     main_trainfile1:="E:\\input\\hc.img";
     loadimage(main_scanfile);
	 while(main_arg_index<5000000)
	 {
		main_arg_index:=main_arg_index+1
	 };
	 main_arg_index<==1 and skip;
	 
     if(main_weightfile!=NULL) then 
     {
         numpatterns:=1;
         if(main_objects=0) then 
         {
             main_objects:=numpatterns
             
         }
         else 
         {
              skip 
         };
         load_weights(main_weightfile);
         init_globs(0);
         init_net()
         
     }
     else
     {
         if(main_trainfile2!=NULL) then 
         {
             numpatterns:=2;
             if(main_objects<numpatterns) then 
             {
                 main_objects:=numpatterns
                 
             }
             else 
             {
                  skip 
             };
             load_train(main_trainfile1,1,main_objects);
             alloc_td_bu();
             init_td(0);
             init_bu(0);
             main_k<==0 and resonant<==main_k and skip;
             while(!resonant)
             {
                 train_match(0);
                 main_k:=main_k+1
             };
             load_train(main_trainfile2,2,main_objects);
             init_globs(2);
             init_td(1);
             init_bu(1);
             main_k<==0 and resonant<==main_k and skip;
             while(!resonant)
             {
                 train_match(1);
                 main_k:=main_k+1
             };
             init_globs(0);
             init_td(main_objects);
             init_bu(main_objects);
             sim_other_objects(numpatterns,main_objects,numf2s);
             setup_base_pattern(main_objects)
         }
         else
         {
             numpatterns:=1;
             if(main_objects<numpatterns) then 
             {
                 main_objects:=numpatterns
                 
             }
             else 
             {
                  skip 
             };
             load_train(main_trainfile1,1,main_objects);
             alloc_td_bu();
             init_td(0);
             init_bu(0);
             main_k<==0 and resonant<==main_k and skip;
             while(!resonant)
             {
                 train_match(0);
                 main_k:=main_k+1
             };
             init_globs(0);
             init_td(1);
             init_bu(1);
             setup_base_pattern(1)
         }
     };
     if(main_endy=0) then 
     {
         main_endy:=height-lheight
         
     }
     else 
     {
          skip 
     };
     if(main_endx=0) then 
     {
         main_endx:=width-lwidth
         
     }
     else 
     {
          skip 
     };
     highest_confidence[0]:=0.0;
     highest_confidence[1]:=0.0;
     highx[0]:=0;
     highx[1]:=0;
     highy[0]:=0;
     highy[1]:=0;
     set_high[0]:=0;
     set_high[1]:=0;
	
     scan_recognize(main_startx,main_starty,main_endx,main_endy,main_stride);
     fprintf(stdout,"Highest vigilance for 1 = %0.4f for object at X = %d, Y = %d\n",highest_confidence[0],highx[0],highy[0]) and skip;
     if(numpatterns=2) then 
     {
         fprintf(stdout,"Highest vigilance for 2 = %0.4f for object at X = %d, Y = %d\n",highest_confidence[1],highx[1],highy[1]) and skip
         
     }
     else 
     {
          skip 
     };
     return<==1 and RValue:=0;
     skip
     )
 };
  main(RValue)
 )
