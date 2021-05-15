/*</
define p:readpackfile_i<=10;
alw(p)
/>*/
</
define p:readpackfile_i>10;
som(p)
/>
/*</
define p:module_1=1;
define q:module_4=1;
alw(p->som(q))
/>*/
/*</
define p1:module_1=1;
define p2:module_2=1;
define p3:module_3=1;
define p4:module_4=1;
p1;(p2;p3;p4)#
/>*/
frame(exit$,progname,options,packfile,ARCHnodes,ARCHpriv,ARCHmine,ARCHelems,ARCHglobalnodes,ARCHmesh_dim,ARCHglobalelems,ARCHcorners,ARCHsubdomains,ARCHduration,ARCHmatrixlen,ARCHcholeskylen,ARCHglobalnode,ARCHglobalelem,ARCHcoord,ARCHvertex,ARCHmatrixcol,ARCHmatrixindex,nodekind,nodekindf,source_elms,M,C,M23,C23,V23,vel,disp,K,Src,Exc,Damp,readpackfile_i,module_1,module_2,module_3,module_4) and (
struct optionss {
int quiet and 
int help 
};
struct excitation {
float dt and 
float duration and 
float t0 
};
struct damping {
float zeta,consta,constb,freq 
};
struct properties {
float cp and 
float cs and 
float den 
};
struct source {
float dip,strike,rake,fault and 
float xyz[3] and 
float epixyz[3] and 
int sourcenode and 
int epicenternode 
};
int module_1<==1 and skip;
int module_2<==0 and skip;
int module_3<==0 and skip;
int module_4<==0 and skip;
int readpackfile_i and skip;
int exit$ and skip;
char *progname and skip;
optionss options and skip;
FILE *packfile and skip;
int ARCHnodes and skip;
int ARCHpriv and skip;
int ARCHmine and skip;
int ARCHelems and skip;
int ARCHglobalnodes and skip;
int ARCHmesh_dim and skip;
int ARCHglobalelems and skip;
int ARCHcorners and skip;
int ARCHsubdomains and skip;
float ARCHduration and skip;
int ARCHmatrixlen and skip;
int ARCHcholeskylen and skip;
int *ARCHglobalnode and skip;
int *ARCHglobalelem and skip;
float **ARCHcoord and skip;
int **ARCHvertex and skip;
int *ARCHmatrixcol and skip;
int *ARCHmatrixindex and skip;
int *nodekind and skip;
float *nodekindf and skip;
int *source_elms and skip;
float **M,**C,**M23,**C23,**V23,**vel and skip;
float ***disp,***K and skip;
source Src and skip;
excitation Exc and skip;
damping Damp and skip;
 function main ( int RValue )
 {
     frame(main_i,main_j,main_k,main_ii,main_jj,main_kk,main_iter,main_timesteps,main_disptplus,main_dispt,main_disptminus,main_verticesonbnd,main_cor,main_bv,main_Step_stride,main_time,main_Ke,main_Me,main_Ce,main_Mexv,main_Cexv,main_v,main_alpha,main_c0,main_d1,main_d2,main_bigdist1,main_bigdist2,main_xc,main_uf,main_vertices,main_prop,return) and ( 
     module_2<==1 and skip;
	 int return<==0 and skip;
     int main_i,main_j,main_k,main_ii,main_jj,main_kk,main_iter,main_timesteps and skip;
     int main_disptplus,main_dispt,main_disptminus and skip;
     int main_verticesonbnd and skip;
     int main_cor[4],main_bv[4] and skip;
     int main_Step_stride and skip;
     float main_time and skip;
     float main_Ke[12,12],main_Me[12],main_Ce[12],main_Mexv[12],main_Cexv[12],main_v[12] and skip;
     float main_alpha,main_c0[3],main_d1,main_d2,main_bigdist1,main_bigdist2,main_xc[3],main_uf[3] and skip;
     float main_vertices[4,3] and skip;
     properties main_prop and skip;
	 arch_init(&options);
     mem_init();
     arch_readnodevector(nodekindf,ARCHnodes);
     Exc.dt:=0.0024;
     Exc.duration:=ARCHduration;
     Exc.t0:=0.6;
     main_timesteps:=Exc.duration/ Exc.dt+1;
     Damp.zeta:=30.0;
     Damp.consta:=0.00533333;
     Damp.constb:=0.06666667;
     Damp.freq:=0.5;
     Src.strike:=111.0*3.14/ 180.0;
     Src.dip:=44.0*3.14/ 180.0;
     Src.rake:=70.0*3.14/ 180.0;
     Src.fault:=29.640788;
     Src.xyz[0]:=32.264153;
     Src.xyz[1]:=23.814432;
     Src.xyz[2]:=-11.25;
     Src.epixyz[0]:=Src.xyz[0];
     Src.epixyz[1]:=Src.xyz[1];
     Src.epixyz[2]:=0.0;
     Src.sourcenode:=-1;
     Src.epicenternode:=-1;
     main_uf[2]<==0.0 and main_uf[1]<==main_uf[2] and main_uf[0]<==main_uf[1] and skip;
     slip(&main_uf[0],&main_uf[1],&main_uf[2]);
     main_uf[0]:=main_uf[0]*(Src.fault);
     main_uf[1]:=main_uf[1]*(Src.fault);
     main_uf[2]:=main_uf[2]*(Src.fault);
     main_prop.cp:=6.0;
     main_prop.cs:=3.2;
     main_prop.den:=2.0;
     main_Step_stride:=30;
     main_disptplus:=0;
     main_dispt:=1;
	 while(main_dispt<20000000)
	 {
		main_dispt:=main_dispt+1
	 };
	 main_dispt:=1;
     main_disptminus:=2;
     fprintf(stderr,"\n") and skip;
     fprintf(stderr,"CASE SUMMARY\n") and skip;
     fprintf(stderr,"Fault information\n") and skip;
     fprintf(stderr,"  Orientation:  strike: %f\n",Src.strike) and skip;
     fprintf(stderr,"                   dip: %f\n",Src.dip) and skip;
     fprintf(stderr,"                  rake: %f\n",Src.rake) and skip;
     fprintf(stderr,"           dislocation: %f cm\n",Src.fault) and skip;
     fprintf(stderr,"Hypocenter: (%f, %f, %f) Km\n",Src.xyz[0],Src.xyz[1],Src.xyz[2]) and skip;
     fprintf(stderr,"Excitation characteristics\n") and skip;
     fprintf(stderr,"     Time step: %f sec\n",Exc.dt) and skip;
     fprintf(stderr,"      Duration: %f sec\n",Exc.duration) and skip;
     fprintf(stderr,"     Rise time: %f sec\n",Exc.t0) and skip;
     fprintf(stderr,"\n") and skip;
     fflush(stderr) and skip;
     return<==1 and skip and RValue:=0;
     skip
     )
     }; 
  function shape_ders ( float **ds )
 {
     ds[0,0]:=-1;
     ds[1,0]:=-1;
     ds[2,0]:=-1;
     ds[0,1]:=1;
     ds[1,1]:=0;
     ds[2,1]:=0;
     ds[0,2]:=0;
     ds[1,2]:=1;
     ds[2,2]:=0;
     ds[0,3]:=0;
     ds[1,3]:=0;
     ds[2,3]:=1
     
 };
 function get_Enu ( properties *prop,float *E,float *nu )
 {
     frame(get_Enu_ratio) and ( 
     float get_Enu_ratio and skip;
     get_Enu_ratio:=prop->cp/ prop->cs;
     get_Enu_ratio:=get_Enu_ratio*get_Enu_ratio;
     * nu:=0.5*(get_Enu_ratio-2.0)/ (get_Enu_ratio-1.0);
     * E:=2.0*prop->den*prop->cs*prop->cs*(1.0+* nu)
     )
     }; 
  function inv_J ( float **a,float *det )
 {
     frame(inv_J_d1,inv_J_c,inv_J_i,inv_J_j) and ( 
     float inv_J_d1 and skip;
     float inv_J_c[3,3] and skip;
     int inv_J_i,inv_J_j and skip;
     inv_J_c[0,0]:=a[1,1]*a[2,2]-a[2,1]*a[1,2];
     inv_J_c[0,1]:=a[0,2]*a[2,1]-a[0,1]*a[2,2];
     inv_J_c[0,2]:=a[0,1]*a[1,2]-a[0,2]*a[1,1];
     inv_J_c[1,0]:=a[1,2]*a[2,0]-a[1,0]*a[2,2];
     inv_J_c[1,1]:=a[0,0]*a[2,2]-a[0,2]*a[2,0];
     inv_J_c[1,2]:=a[0,2]*a[1,0]-a[0,0]*a[1,2];
     inv_J_c[2,0]:=a[1,0]*a[2,1]-a[1,1]*a[2,0];
     inv_J_c[2,1]:=a[0,1]*a[2,0]-a[0,0]*a[2,1];
     inv_J_c[2,2]:=a[0,0]*a[1,1]-a[0,1]*a[1,0];
     * det:=a[0,0]*inv_J_c[0,0]+a[0,1]*inv_J_c[1,0]+a[0,2]*inv_J_c[2,0];
     inv_J_d1:=1.0/ * det;
     inv_J_i:=0;
     
     while(inv_J_i<3)
     {
         inv_J_j:=0;
         
         while(inv_J_j<3)
         {
             a[inv_J_i,inv_J_j]:=inv_J_c[inv_J_i,inv_J_j]*inv_J_d1;
             inv_J_j:=inv_J_j+1
             
         };
         inv_J_i:=inv_J_i+1
         
     }
     )
     }; 
  function element_matrices ( float **vertices,float **Ke,float *Me,properties *prop )
 {
     frame(element_matrices_ds,element_matrices_sum,element_matrices_jacobian,element_matrices_det,element_matrices_volume,element_matrices_E,element_matrices_nu,element_matrices_c1,element_matrices_c2,element_matrices_c3,element_matrices_tt,element_matrices_ts,element_matrices_i,element_matrices_j,element_matrices_m,element_matrices_n,element_matrices_row,element_matrices_column) and ( 
     float element_matrices_ds[3,4] and skip;
     float element_matrices_sum[3] and skip;
     float element_matrices_jacobian[3,3] and skip;
     float element_matrices_det and skip;
     float element_matrices_volume and skip;
     float element_matrices_E,element_matrices_nu and skip;
     float element_matrices_c1,element_matrices_c2,element_matrices_c3 and skip;
     float element_matrices_tt,element_matrices_ts and skip;
     int element_matrices_i,element_matrices_j,element_matrices_m,element_matrices_n,element_matrices_row,element_matrices_column and skip;
     shape_ders(element_matrices_ds);
     element_matrices_i:=0;
     
     while(element_matrices_i<3)
     {
         element_matrices_j:=0;
         
         while(element_matrices_j<3)
         {
             element_matrices_sum[0]:=0.0;
             element_matrices_m:=0;
             
             while(element_matrices_m<4)
             {
                 element_matrices_sum[0]:=element_matrices_sum[0]+element_matrices_ds[element_matrices_i,element_matrices_m]*vertices[element_matrices_m,element_matrices_j];
                 element_matrices_m:=element_matrices_m+1
                 
             };
             element_matrices_jacobian[element_matrices_j,element_matrices_i]:=element_matrices_sum[0];
             element_matrices_j:=element_matrices_j+1
             
         };
         element_matrices_i:=element_matrices_i+1
         
     };
     inv_J(element_matrices_jacobian,&element_matrices_det);
     element_matrices_m:=0;
     
     while(element_matrices_m<4)
     {
         element_matrices_i:=0;
         
         while(element_matrices_i<3)
         {
             element_matrices_sum[element_matrices_i]:=0.0;
             element_matrices_j:=0;
             
             while(element_matrices_j<3)
             {
                 element_matrices_sum[element_matrices_i]:=element_matrices_sum[element_matrices_i]+element_matrices_jacobian[element_matrices_j,element_matrices_i]*element_matrices_ds[element_matrices_j,element_matrices_m];
                 element_matrices_j:=element_matrices_j+1
                 
             };
             element_matrices_i:=element_matrices_i+1
             
         };
         element_matrices_i:=0;
         
         while(element_matrices_i<3)
         {
             element_matrices_ds[element_matrices_i,element_matrices_m]:=element_matrices_sum[element_matrices_i];
             element_matrices_i:=element_matrices_i+1
             
         };
         element_matrices_m:=element_matrices_m+1
         
     };
     element_matrices_volume:=element_matrices_det/ 6.0;
     if(element_matrices_volume<=0) then 
     {
         fprintf(stderr,"Warning: Element volume = %f !\n",element_matrices_volume) and skip
         
     }
     else 
     {
          skip 
     };
     get_Enu(prop,&element_matrices_E,&element_matrices_nu);
     element_matrices_c1:=element_matrices_E/ (2.0*(element_matrices_nu+1.0)*(1.0-element_matrices_nu*2.0))*element_matrices_volume;
     element_matrices_c2:=element_matrices_E*element_matrices_nu/ ((element_matrices_nu+1.0)*(1.0-element_matrices_nu*2.0))*element_matrices_volume;
     element_matrices_c3:=element_matrices_E/ ((element_matrices_nu+1.0)*2.0)*element_matrices_volume;
     element_matrices_row:=-1;
     element_matrices_m:=0;
     
     while(element_matrices_m<4)
     {
         element_matrices_i:=0;
         
         while(element_matrices_i<3)
         {
             element_matrices_row:=element_matrices_row+1;
             element_matrices_column:=-1;
             element_matrices_n:=0;
             
             while(element_matrices_n<=element_matrices_m)
             {
                 element_matrices_j:=0;
                 
                 while(element_matrices_j<3)
                 {
                     element_matrices_column:=element_matrices_column+1;
                     element_matrices_ts:=element_matrices_ds[element_matrices_i,element_matrices_m]*element_matrices_ds[element_matrices_j,element_matrices_n];
                     if(element_matrices_i=element_matrices_j) then 
                     {
                         element_matrices_ts:=element_matrices_ts*element_matrices_c1;
                         element_matrices_tt:=(element_matrices_ds[0,element_matrices_m]*element_matrices_ds[0,element_matrices_n]+element_matrices_ds[1,element_matrices_m]*element_matrices_ds[1,element_matrices_n]+element_matrices_ds[2,element_matrices_m]*element_matrices_ds[2,element_matrices_n])*element_matrices_c3
                         
                     }
                     else
                     {
                         if(element_matrices_m=element_matrices_n) then 
                         {
                             element_matrices_ts:=element_matrices_ts*element_matrices_c1;
                             element_matrices_tt:=0
                         }
                         else
                         {
                             element_matrices_ts:=element_matrices_ts*element_matrices_c2;
                             element_matrices_tt:=element_matrices_ds[element_matrices_j,element_matrices_m]*element_matrices_ds[element_matrices_i,element_matrices_n]*element_matrices_c3
                         }
                     };
                     Ke[element_matrices_row,element_matrices_column]:=Ke[element_matrices_row,element_matrices_column]+element_matrices_ts+element_matrices_tt;
                     element_matrices_j:=element_matrices_j+1
                     
                 };
                 element_matrices_n:=element_matrices_n+1
                 
             };
             element_matrices_i:=element_matrices_i+1
             
         };
         element_matrices_m:=element_matrices_m+1
         
     };
     element_matrices_tt:=prop->den*element_matrices_volume/ 4.0;
     element_matrices_i:=0;
     
     while(element_matrices_i<12)
     {
         Me[element_matrices_i]:=element_matrices_tt;
         element_matrices_i:=element_matrices_i+1
         
     };
     element_matrices_i:=0;
     
     while(element_matrices_i<12)
     {
         element_matrices_j:=0;
         
         while(element_matrices_j<=element_matrices_i)
         {
             Ke[element_matrices_j,element_matrices_i]:=Ke[element_matrices_i,element_matrices_j];
             element_matrices_j:=element_matrices_j+1
             
         };
         element_matrices_i:=element_matrices_i+1
         
     }
     )
     }; 
  function area_triangle ( float** vertices ,float RValue)
 {
     frame(area_triangle_a,area_triangle_b,area_triangle_c,area_triangle_x2,area_triangle_y2,area_triangle_z2,area_triangle_p,area_triangle_area,return) and ( 
     int return<==0 and skip;
     float area_triangle_a,area_triangle_b,area_triangle_c and skip;
     float area_triangle_x2,area_triangle_y2,area_triangle_z2 and skip;
     float area_triangle_p and skip;
     float area_triangle_area and skip;
     area_triangle_x2:=(vertices[0,0]-vertices[1,0])*(vertices[0,0]-vertices[1,0]);
     area_triangle_y2:=(vertices[0,1]-vertices[1,1])*(vertices[0,1]-vertices[1,1]);
     area_triangle_z2:=(vertices[0,2]-vertices[1,2])*(vertices[0,2]-vertices[1,2]);
     area_triangle_a:=sqrt(area_triangle_x2+area_triangle_y2+area_triangle_z2);
     area_triangle_x2:=(vertices[2,0]-vertices[1,0])*(vertices[2,0]-vertices[1,0]);
     area_triangle_y2:=(vertices[2,1]-vertices[1,1])*(vertices[2,1]-vertices[1,1]);
     area_triangle_z2:=(vertices[2,2]-vertices[1,2])*(vertices[2,2]-vertices[1,2]);
     area_triangle_b:=sqrt(area_triangle_x2+area_triangle_y2+area_triangle_z2);
     area_triangle_x2:=(vertices[0,0]-vertices[2,0])*(vertices[0,0]-vertices[2,0]);
     area_triangle_y2:=(vertices[0,1]-vertices[2,1])*(vertices[0,1]-vertices[2,1]);
     area_triangle_z2:=(vertices[0,2]-vertices[2,2])*(vertices[0,2]-vertices[2,2]);
     area_triangle_c:=sqrt(area_triangle_x2+area_triangle_y2+area_triangle_z2);
     area_triangle_p:=(area_triangle_a+area_triangle_b+area_triangle_c)/ 2.0;
     area_triangle_area:=sqrt(area_triangle_p*(area_triangle_p-area_triangle_a)*(area_triangle_p-area_triangle_b)*(area_triangle_p-area_triangle_c));
     return<==1 and RValue:=area_triangle_area;
     skip
     )
     }; 
  function abe_matrix ( float **vertices,int *bv,properties *prop,float *Ce )
 {
     frame(abe_matrix_i,abe_matrix_j,abe_matrix_area) and ( 
     int abe_matrix_i,abe_matrix_j and skip;
     float abe_matrix_area and skip;
     abe_matrix_area:=area_triangle(vertices,RValue);
     abe_matrix_i:=0;
     
     while(abe_matrix_i<3)
     {
         abe_matrix_j:=3*bv[abe_matrix_i];
         Ce[abe_matrix_j]:=Ce[abe_matrix_j]+prop->cs*prop->den*abe_matrix_area/ 3.0;
         Ce[abe_matrix_j+1]:=Ce[abe_matrix_j+1]+prop->cs*prop->den*abe_matrix_area/ 3.0;
         Ce[abe_matrix_j+2]:=Ce[abe_matrix_j+2]+prop->cp*prop->den*abe_matrix_area/ 3.0;
         abe_matrix_i:=abe_matrix_i+1
         
     }
     )
     }; 
  function phi0 ( float phi0_t,float RValue )
 {
     frame(phi0_value,return) and ( 
     int return<==0 and skip;
     float phi0_value and skip;
     if(phi0_t<=Exc.t0) then 
     {
         phi0_value:=0.5/ 3.14*(2.0*3.14*phi0_t/ Exc.t0-sin(2.0*3.14*phi0_t/ Exc.t0));
         return<==1 and RValue:=phi0_value;
         skip
     }
     else
     {
         return<==1 and RValue:=1.0;
         skip
     }
     )
     }; 
  function phi1 ( float phi1_t ,float RValue)
 {
     frame(phi1_value,return) and ( 
     int return<==0 and skip;
     float phi1_value and skip;
     if(phi1_t<=Exc.t0) then 
     {
         phi1_value:=(1.0-cos(2.0*3.14*phi1_t/ Exc.t0))/ Exc.t0;
         return<==1 and RValue:=phi1_value;
         skip
     }
     else
     {
         return<==1 and RValue:=0.0;
         skip
     }
     )
     }; 
  function phi2 ( float phi2_t ,float RValue)
 {
     frame(phi2_value,return) and ( 
     int return<==0 and skip;
     float phi2_value and skip;
     if(phi2_t<=Exc.t0) then 
     {
         phi2_value:=2.0*3.14/ Exc.t0/ Exc.t0*sin(2.0*3.14*phi2_t/ Exc.t0);
         return<==1 and RValue:=phi2_value;
         skip
     }
     else
     {
         return<==1 and RValue:=0.0;
         skip
     }
     )
     }; 
  function slip ( float *u,float *v,float *w )
 {
     * w<==0.0 and * v<==* w and * u<==* v and skip;
     * u:=(cos(Src.rake)*sin(Src.strike)-sin(Src.rake)*cos(Src.strike)*cos(Src.dip));
     * v:=(cos(Src.rake)*cos(Src.strike)+sin(Src.rake)*sin(Src.strike)*cos(Src.dip));
     * w:=sin(Src.rake)*sin(Src.dip)
     
 };
 function distance ( float *p1,float *p2,float RValue )
 {
     frame(return) and ( 
     int return<==0 and skip;
     return<==1 and RValue:=((p1[0]-p2[0])*(p1[0]-p2[0])+(p1[1]-p2[1])*(p1[1]-p2[1])+(p1[2]-p2[2])*(p1[2]-p2[2]));
     skip
     )
     }; 
  function centroid ( float **x,float *xc )
 {
     frame(centroid_i) and ( 
     int centroid_i and skip;
     centroid_i:=0;
     
     while(centroid_i<3)
     {
         xc[centroid_i]:=(x[0,centroid_i]+x[1,centroid_i]+x[2,centroid_i]+x[3,centroid_i])/ 4.0;
         centroid_i:=centroid_i+1
         
     }
     )
     }; 
  function point2fault ( float *x,float RValue )
 {
     frame(point2fault_nx,point2fault_ny,point2fault_nz,point2fault_d0,return) and ( 
     int return<==0 and skip;
     float point2fault_nx,point2fault_ny,point2fault_nz and skip;
     float point2fault_d0 and skip;
     point2fault_nx:=cos(Src.strike)*sin(Src.dip);
     point2fault_ny:=-sin(Src.strike)*sin(Src.dip);
     point2fault_nz:=cos(Src.dip);
     point2fault_d0:=-(point2fault_nx*Src.xyz[0]+point2fault_ny*Src.xyz[1]+point2fault_nz*Src.xyz[2]);
     return<==1 and RValue:=(float)point2fault_nx*x[0]+point2fault_ny*x[1]+point2fault_nz*x[2]+point2fault_d0;
     skip
     )
     }; 
  function mv12x12 ( float **m,float *v )
 {
     frame(mv12x12_i,mv12x12_j,mv12x12_u) and ( 
     int mv12x12_i,mv12x12_j and skip;
     float mv12x12_u[12] and skip;
     mv12x12_i:=0;
     
     while(mv12x12_i<12)
     {
         mv12x12_u[mv12x12_i]:=0;
         mv12x12_j:=0;
         
         while(mv12x12_j<12)
         {
             mv12x12_u[mv12x12_i]:=mv12x12_u[mv12x12_i]+(m[mv12x12_i,mv12x12_j]*v[mv12x12_j]);
             mv12x12_j:=mv12x12_j+1
             
         };
         mv12x12_i:=mv12x12_i+1
         
     };
     mv12x12_i:=0;
     
     while(mv12x12_i<12)
     {
         v[mv12x12_i]:=mv12x12_u[mv12x12_i];
         mv12x12_i:=mv12x12_i+1
         
     }
     )
     }; 
  function vv12x12 ( float *v1,float *v2,float *u )
 {
     frame(vv12x12_i) and ( 
     int vv12x12_i and skip;
     vv12x12_i:=0;
     
     while(vv12x12_i<12)
     {
         u[vv12x12_i]:=v1[vv12x12_i]*v2[vv12x12_i];
         vv12x12_i:=vv12x12_i+1
         
     }
     )
     }; 
  function arch_bail (  )
 {
     exit$<==0 and skip 
     
 };
 function arch_info (  )
 {
     output ("\n") and skip;
     output ("You are running an Archimedes finite element simulation called ",progname,".\n\n") and skip;
     output ("The command syntax is:\n\n") and skip;
     output (progname," [-Qh] < packfile\n\n"," [-Qh] < packfile\n\n") and skip;
     output ("Command line options:\n\n") and skip;
     output ("    -Q  Quietly suppress all explanation of what this program is doing\n") and skip;
     output ("        unless an error occurs.\n") and skip;
     output ("    -h  Print this message and exit$.\n") and skip
     
 };
 function arch_parsecommandline ( optionss *op)
 {
 skip
     
 };
 function arch_readnodevector ( float *v,int n )
 {
     frame(arch_readnodevector_i,arch_readnodevector_type,arch_readnodevector_attributes) and ( 
     int arch_readnodevector_i and skip;
     int arch_readnodevector_type,arch_readnodevector_attributes and skip;
     fscanf(packfile,"%d %d\n",&arch_readnodevector_type,&arch_readnodevector_attributes) and skip;
     if(arch_readnodevector_type!=2) then 
     {
         fprintf(stderr,"READNODEVECTOR: unexpected data type\n") and skip;
         arch_bail()
         
     }
     else 
     {
          skip 
     };
     if(arch_readnodevector_attributes!=1) then 
     {
         fprintf(stderr,"READNODEVECTOR: unexpected number of attributes\n") and skip;
         arch_bail()
         
     }
     else 
     {
          skip 
     };
     arch_readnodevector_i:=0;
     
     while(arch_readnodevector_i<n)
     {
         fscanf(packfile,"%lf",&v[arch_readnodevector_i]) and skip;
         arch_readnodevector_i:=arch_readnodevector_i+1
         
     }
     )
     }; 
  function arch_readelemvector ( float *v,int n )
 {
     frame(arch_readelemvector_i,arch_readelemvector_type,arch_readelemvector_attributes) and ( 
     int arch_readelemvector_i and skip;
     int arch_readelemvector_type,arch_readelemvector_attributes and skip;
     fscanf(packfile,"%d %d\n",&arch_readelemvector_type,&arch_readelemvector_attributes) and skip;
     if(arch_readelemvector_type!=1) then 
     {
         fprintf(stderr,"READELEMVECTOR: unexpected data type\n") and skip;
         arch_bail()
         
     }
     else 
     {
          skip 
     };
     if(arch_readelemvector_attributes!=1) then 
     {
         fprintf(stderr,"READELEMVECTOR: unexpected number of attributes\n") and skip;
         arch_bail()
         
     }
     else 
     {
          skip 
     };
     arch_readelemvector_i:=0;
     
     while(arch_readelemvector_i<n)
     {
         fscanf(packfile,"%lf",&v[arch_readelemvector_i]) and skip;
         arch_readelemvector_i:=arch_readelemvector_i+1
         
     }
     )
     }; 
  function arch_readdouble ( float *v )
 {
     frame(arch_readdouble_type,arch_readdouble_attributes) and ( 
     int arch_readdouble_type,arch_readdouble_attributes and skip;
     fscanf(packfile,"%d %d\n",&arch_readdouble_type,&arch_readdouble_attributes) and skip;
     if(arch_readdouble_type!=3) then 
     {
         fprintf(stderr,"READDOUBLE: unexpected data type\n") and skip;
         arch_bail()
         
     }
     else 
     {
          skip 
     };
     if(arch_readdouble_attributes!=1) then 
     {
         fprintf(stderr,"READDOUBLE: unexpected number of attributes\n") and skip;
         arch_bail()
         
     }
     else 
     {
          skip 
     };
     fscanf(packfile,"%lf",&v[0]) and skip
     )
     }; 
  function readpackfile ( FILE *packfile,optionss *op )
 {
     frame(readpackfile_oldrow,readpackfile_newrow,readpackfile_j,readpackfile_temp1,readpackfile_temp2) and ( 
     int readpackfile_oldrow,readpackfile_newrow and skip;
     int readpackfile_j and skip;
     int readpackfile_temp1,readpackfile_temp2 and skip;
     fscanf(packfile,"%d",&ARCHglobalnodes) and skip;
     fscanf(packfile,"%d",&ARCHmesh_dim) and skip;
     fscanf(packfile,"%d",&ARCHglobalelems) and skip;
     fscanf(packfile,"%d",&ARCHcorners) and skip;
     fscanf(packfile,"%d",&ARCHsubdomains) and skip;
     fscanf(packfile,"%lf",&ARCHduration) and skip;

	 fscanf(packfile, "%d %d %d", &ARCHnodes, &ARCHmine, &ARCHpriv) and skip;

	 ARCHglobalnode := (int *) malloc(ARCHnodes * sizeof(int));


     ARCHcoord:=(float **)malloc(ARCHnodes*sizeof(float *));
     readpackfile_i:=0;
     
     while(readpackfile_i<ARCHnodes)
     {
         ARCHcoord[readpackfile_i]:=(float *)malloc(3*sizeof(float));
         readpackfile_i:=readpackfile_i+1
         
     };
     readpackfile_i:=0;
     
     while(readpackfile_i<ARCHnodes)
     {
         fscanf(packfile,"%d",&ARCHglobalnode[readpackfile_i]) and skip;
         readpackfile_j:=0;
         
         while(readpackfile_j<ARCHmesh_dim)
         {
             fscanf(packfile,"%lf",&ARCHcoord[readpackfile_i,readpackfile_j]) and skip;
             readpackfile_j:=readpackfile_j+1
             
         };
         readpackfile_i:=readpackfile_i+1
         
     };
     fscanf(packfile,"%d",&ARCHelems) and skip;
     ARCHglobalelem:=(int *)malloc(ARCHelems*sizeof(int));
     ARCHvertex:=(int **)malloc(ARCHelems*sizeof(int *));
     readpackfile_i:=0;
     
     while(readpackfile_i<ARCHelems)
     {
         ARCHvertex[readpackfile_i]:=(int *)malloc(4*sizeof(int));
         readpackfile_i:=readpackfile_i+1
         
     };
     readpackfile_i:=0;
     
     while(readpackfile_i<ARCHelems)
     {
         fscanf(packfile,"%d",&ARCHglobalelem[readpackfile_i]) and skip;
         readpackfile_j:=0;
         
         while(readpackfile_j<ARCHcorners)
         {
             fscanf(packfile,"%d",&ARCHvertex[readpackfile_i,readpackfile_j]) and skip;
             readpackfile_j:=readpackfile_j+1
             
         };
         readpackfile_i:=readpackfile_i+1
         
     };
     fscanf(packfile,"%d %d",&ARCHmatrixlen,&ARCHcholeskylen) and skip;
     ARCHmatrixcol:=(int *)malloc((ARCHmatrixlen+1)*sizeof(int));
     ARCHmatrixindex:=(int *)malloc((ARCHnodes+1)*sizeof(int));
     readpackfile_oldrow:=-1;
     readpackfile_i:=0;
     
     while(readpackfile_i<ARCHmatrixlen)
     {
         fscanf(packfile,"%d",&readpackfile_newrow) and skip;
         fscanf(packfile,"%d",&ARCHmatrixcol[readpackfile_i]) and skip;
         while(readpackfile_oldrow<readpackfile_newrow)
         {
             ARCHmatrixindex[(readpackfile_oldrow+1)]:=readpackfile_i;
             readpackfile_oldrow:=readpackfile_oldrow+1
         };
         readpackfile_i:=readpackfile_i+1
         
     };
     while(readpackfile_oldrow<ARCHnodes)
     {
         ARCHmatrixindex[(readpackfile_oldrow+1)]:=ARCHmatrixlen;
         readpackfile_oldrow:=readpackfile_oldrow+1
     };
     fscanf(packfile,"%d %d",&readpackfile_temp1,&readpackfile_temp2) and skip
     )
     }; 
  function arch_init ( optionss *op )
 {
	module_3<==1 and skip;
     progname:="equake.exe";
     packfile:=fopen("E:\\input\\inp.in","r");
     readpackfile(packfile,op)
     
 };
 function smvp ( int nodes,float ***A,int *Acol,int *Aindex,float **v,float **w )
 {
     frame(smvp_i,smvp_Anext,smvp_Alast,smvp_col,smvp_sum0,smvp_sum1,smvp_sum2) and ( 
     int smvp_i and skip;
     int smvp_Anext,smvp_Alast,smvp_col and skip;
     float smvp_sum0,smvp_sum1,smvp_sum2 and skip;
     smvp_i:=0;
     
     while(smvp_i<nodes)
     {
         smvp_Anext:=Aindex[smvp_i];
         smvp_Alast:=Aindex[smvp_i+1];
         smvp_sum0:=A[smvp_Anext,0,0]*v[smvp_i,0]+A[smvp_Anext,0,1]*v[smvp_i,1]+A[smvp_Anext,0,2]*v[smvp_i,2];
         smvp_sum1:=A[smvp_Anext,1,0]*v[smvp_i,0]+A[smvp_Anext,1,1]*v[smvp_i,1]+A[smvp_Anext,1,2]*v[smvp_i,2];
         smvp_sum2:=A[smvp_Anext,2,0]*v[smvp_i,0]+A[smvp_Anext,2,1]*v[smvp_i,1]+A[smvp_Anext,2,2]*v[smvp_i,2];
         smvp_Anext:=smvp_Anext+1;
         while(smvp_Anext<smvp_Alast)
         {
             smvp_col:=Acol[smvp_Anext];
             smvp_sum0:=smvp_sum0+(A[smvp_Anext,0,0]*v[smvp_col,0]+A[smvp_Anext,0,1]*v[smvp_col,1]+A[smvp_Anext,0,2]*v[smvp_col,2]);
             smvp_sum1:=smvp_sum1+(A[smvp_Anext,1,0]*v[smvp_col,0]+A[smvp_Anext,1,1]*v[smvp_col,1]+A[smvp_Anext,1,2]*v[smvp_col,2]);
             smvp_sum2:=smvp_sum2+(A[smvp_Anext,2,0]*v[smvp_col,0]+A[smvp_Anext,2,1]*v[smvp_col,1]+A[smvp_Anext,2,2]*v[smvp_col,2]);
             w[smvp_col,0]:=w[smvp_col,0]+(A[smvp_Anext,0,0]*v[smvp_i,0]+A[smvp_Anext,1,0]*v[smvp_i,1]+A[smvp_Anext,2,0]*v[smvp_i,2]);
             w[smvp_col,1]:=w[smvp_col,1]+(A[smvp_Anext,0,1]*v[smvp_i,0]+A[smvp_Anext,1,1]*v[smvp_i,1]+A[smvp_Anext,2,1]*v[smvp_i,2]);
             w[smvp_col,2]:=w[smvp_col,2]+(A[smvp_Anext,0,2]*v[smvp_i,0]+A[smvp_Anext,1,2]*v[smvp_i,1]+A[smvp_Anext,2,2]*v[smvp_i,2]);
             smvp_Anext:=smvp_Anext+1
         };
         w[smvp_i,0]:=w[smvp_i,0]+(smvp_sum0);
         w[smvp_i,1]:=w[smvp_i,1]+(smvp_sum1);
         w[smvp_i,2]:=w[smvp_i,2]+(smvp_sum2);
         smvp_i:=smvp_i+1
         
     }
     )
     }; 
  function smvp_opt ( int nodes,float ***A,int *Acol,int *Aindex,float **v,float **w )
 {
     frame(smvp_opt_i,smvp_opt_Anext,smvp_opt_Alast,smvp_opt_vi0,smvp_opt_vi1,smvp_opt_vi2,smvp_opt_sum0,smvp_opt_sum1,smvp_opt_sum2,smvp_opt_value,smvp_opt_vcol0,smvp_opt_vcol1,smvp_opt_vcol2,smvp_opt_wcol0,smvp_opt_wcol1,smvp_opt_wcol2,smvp_opt_col) and ( 
     int smvp_opt_i and skip;
     int smvp_opt_Anext,smvp_opt_Alast and skip;
     float smvp_opt_vi0,smvp_opt_vi1,smvp_opt_vi2,smvp_opt_sum0,smvp_opt_sum1,smvp_opt_sum2,smvp_opt_value and skip;
     float smvp_opt_vcol0,smvp_opt_vcol1,smvp_opt_vcol2,smvp_opt_wcol0,smvp_opt_wcol1,smvp_opt_wcol2 and skip;
     int smvp_opt_col and skip;
     smvp_opt_i:=0;
     
     while(smvp_opt_i<nodes)
     {
         w[smvp_opt_i,0]:=0.0;
         w[smvp_opt_i,1]:=0.0;
         w[smvp_opt_i,2]:=0.0;
         smvp_opt_i:=smvp_opt_i+1
         
     };
     smvp_opt_i:=0;
     
     while(smvp_opt_i<nodes)
     {
         smvp_opt_vi0:=v[smvp_opt_i,0];
         smvp_opt_vi1:=v[smvp_opt_i,1];
         smvp_opt_vi2:=v[smvp_opt_i,2];
         smvp_opt_Anext:=Aindex[smvp_opt_i];
         smvp_opt_Alast:=Aindex[smvp_opt_i+1];
         smvp_opt_sum0:=w[smvp_opt_i,0]+A[smvp_opt_Anext,0,0]*smvp_opt_vi0+A[smvp_opt_Anext,0,1]*smvp_opt_vi1+A[smvp_opt_Anext,0,2]*smvp_opt_vi2;
         smvp_opt_sum1:=w[smvp_opt_i,1]+A[smvp_opt_Anext,1,0]*smvp_opt_vi0+A[smvp_opt_Anext,1,1]*smvp_opt_vi1+A[smvp_opt_Anext,1,2]*smvp_opt_vi2;
         smvp_opt_sum2:=w[smvp_opt_i,2]+A[smvp_opt_Anext,2,0]*smvp_opt_vi0+A[smvp_opt_Anext,2,1]*smvp_opt_vi1+A[smvp_opt_Anext,2,2]*smvp_opt_vi2;
         smvp_opt_Anext:=smvp_opt_Anext+1;
         while(smvp_opt_Anext<smvp_opt_Alast)
         {
             smvp_opt_col:=Acol[smvp_opt_Anext];
             smvp_opt_vcol0:=v[smvp_opt_col,0];
             smvp_opt_vcol1:=v[smvp_opt_col,1];
             smvp_opt_vcol2:=v[smvp_opt_col,2];
             smvp_opt_value:=A[smvp_opt_Anext,0,0];
             smvp_opt_sum0:=smvp_opt_sum0+(smvp_opt_value*smvp_opt_vcol0);
             smvp_opt_wcol0:=w[smvp_opt_col,0]+smvp_opt_value*smvp_opt_vi0;
             smvp_opt_value:=A[smvp_opt_Anext,0,1];
             smvp_opt_sum0:=smvp_opt_sum0+(smvp_opt_value*smvp_opt_vcol1);
             smvp_opt_wcol1:=w[smvp_opt_col,1]+smvp_opt_value*smvp_opt_vi0;
             smvp_opt_value:=A[smvp_opt_Anext,0,2];
             smvp_opt_sum0:=smvp_opt_sum0+(smvp_opt_value*smvp_opt_vcol2);
             smvp_opt_wcol2:=w[smvp_opt_col,2]+smvp_opt_value*smvp_opt_vi0;
             smvp_opt_value:=A[smvp_opt_Anext,1,0];
             smvp_opt_sum1:=smvp_opt_sum1+(smvp_opt_value*smvp_opt_vcol0);
             smvp_opt_wcol0:=smvp_opt_wcol0+(smvp_opt_value*smvp_opt_vi1);
             smvp_opt_value:=A[smvp_opt_Anext,1,1];
             smvp_opt_sum1:=smvp_opt_sum1+(smvp_opt_value*smvp_opt_vcol1);
             smvp_opt_wcol1:=smvp_opt_wcol1+(smvp_opt_value*smvp_opt_vi1);
             smvp_opt_value:=A[smvp_opt_Anext,1,2];
             smvp_opt_sum1:=smvp_opt_sum1+(smvp_opt_value*smvp_opt_vcol2);
             smvp_opt_wcol2:=smvp_opt_wcol2+(smvp_opt_value*smvp_opt_vi1);
             smvp_opt_value:=A[smvp_opt_Anext,2,0];
             smvp_opt_sum2:=smvp_opt_sum2+(smvp_opt_value*smvp_opt_vcol0);
             w[smvp_opt_col,0]:=smvp_opt_wcol0+smvp_opt_value*smvp_opt_vi2;
             smvp_opt_value:=A[smvp_opt_Anext,2,1];
             smvp_opt_sum2:=smvp_opt_sum2+(smvp_opt_value*smvp_opt_vcol1);
             w[smvp_opt_col,1]:=smvp_opt_wcol1+smvp_opt_value*smvp_opt_vi2;
             smvp_opt_value:=A[smvp_opt_Anext,2,2];
             smvp_opt_sum2:=smvp_opt_sum2+(smvp_opt_value*smvp_opt_vcol2);
             w[smvp_opt_col,2]:=smvp_opt_wcol2+smvp_opt_value*smvp_opt_vi2;
             smvp_opt_Anext:=smvp_opt_Anext+1
         };
         w[smvp_opt_i,0]:=smvp_opt_sum0;
         w[smvp_opt_i,1]:=smvp_opt_sum1;
         w[smvp_opt_i,2]:=smvp_opt_sum2;
         smvp_opt_i:=smvp_opt_i+1
         
     }
     )
     }; 
  function mem_init (  )
 {
     frame(mem_init_i,mem_init_j,mem_init_k) and (
	 module_4<==1 and skip;
     int mem_init_i,mem_init_j,mem_init_k and skip;
     nodekindf:=(float *)malloc(ARCHnodes*sizeof(float));
     if(nodekindf=(float *)NULL) then 
     {
         fprintf(stderr,"malloc failed for nodekindf\n") and skip;
         fflush(stderr) and skip;
         exit$<==0 and skip 
         
     }
     else 
     {
          skip 
     };
     nodekind:=(int *)malloc(ARCHnodes*sizeof(int));
     if(nodekind=(int *)NULL) then 
     {
         fprintf(stderr,"malloc failed for nodekind\n") and skip;
         fflush(stderr) and skip;
         exit$<==0 and skip 
         
     }
     else 
     {
          skip 
     };
     source_elms:=(int *)malloc(ARCHelems*sizeof(int));
     if(source_elms=(int *)NULL) then 
     {
         fprintf(stderr,"malloc failed for source_elms\n") and skip;
         fflush(stderr) and skip;
         exit$<==0 and skip 
         
     }
     else 
     {
          skip 
     };
     vel:=(float **)malloc(ARCHnodes*sizeof(float *));
     if(vel=(float **)NULL) then 
     {
         fprintf(stderr,"malloc failed for vel\n") and skip;
         fflush(stderr) and skip;
         exit$<==0 and skip 
         
     }
     else 
     {
          skip 
     };
     mem_init_i:=0;
     
     while(mem_init_i<ARCHnodes)
     {
         vel[mem_init_i]:=(float *)malloc(3*sizeof(float));
         if(vel[mem_init_i]=(float *)NULL) then 
         {
             fprintf(stderr,"malloc failed for vel[%d]\n",mem_init_i) and skip;
             fflush(stderr) and skip;
             exit$<==0 and skip 
             
         }
         else 
         {
              skip 
         };
         mem_init_i:=mem_init_i+1
         
     };
     M:=(float **)malloc(ARCHnodes*sizeof(float *));
     if(M=(float **)NULL) then 
     {
         fprintf(stderr,"malloc failed for M\n") and skip;
         fflush(stderr) and skip;
         exit$<==0 and skip 
         
     }
     else 
     {
          skip 
     };
     mem_init_i:=0;
     
     while(mem_init_i<ARCHnodes)
     {
         M[mem_init_i]:=(float *)malloc(3*sizeof(float));
         if(M[mem_init_i]=(float *)NULL) then 
         {
             fprintf(stderr,"malloc failed for M[%d]\n",mem_init_i) and skip;
             fflush(stderr) and skip;
             exit$<==0 and skip 
             
         }
         else 
         {
              skip 
         };
         mem_init_i:=mem_init_i+1
         
     };
     C:=(float **)malloc(ARCHnodes*sizeof(float *));
     if(C=(float **)NULL) then 
     {
         fprintf(stderr,"malloc failed for C\n") and skip;
         fflush(stderr) and skip;
         exit$<==0 and skip 
         
     }
     else 
     {
          skip 
     };
     mem_init_i:=0;
     
     while(mem_init_i<ARCHnodes)
     {
         C[mem_init_i]:=(float *)malloc(3*sizeof(float));
         if(C[mem_init_i]=(float *)NULL) then 
         {
             fprintf(stderr,"malloc failed for C[%d]\n",mem_init_i) and skip;
             fflush(stderr) and skip;
             exit$<==0 and skip 
             
         }
         else 
         {
              skip 
         };
         mem_init_i:=mem_init_i+1
         
     };
     M23:=(float **)malloc(ARCHnodes*sizeof(float *));
     if(M23=(float **)NULL) then 
     {
         fprintf(stderr,"malloc failed for M23\n") and skip;
         fflush(stderr) and skip;
         exit$<==0 and skip 
         
     }
     else 
     {
          skip 
     };
     mem_init_i:=0;
     
     while(mem_init_i<ARCHnodes)
     {
         M23[mem_init_i]:=(float *)malloc(3*sizeof(float));
         if(M23[mem_init_i]=(float *)NULL) then 
         {
             fprintf(stderr,"malloc failed for M23[%d]\n",mem_init_i) and skip;
             fflush(stderr) and skip;
             exit$<==0 and skip 
             
         }
         else 
         {
              skip 
         };
         mem_init_i:=mem_init_i+1
         
     };
     C23:=(float **)malloc(ARCHnodes*sizeof(float *));
     if(C23=(float **)NULL) then 
     {
         fprintf(stderr,"malloc failed for C23\n") and skip;
         fflush(stderr) and skip;
         exit$<==0 and skip 
         
     }
     else 
     {
          skip 
     };
     mem_init_i:=0;
     
     while(mem_init_i<ARCHnodes)
     {
         C23[mem_init_i]:=(float *)malloc(3*sizeof(float));
         if(C23[mem_init_i]=(float *)NULL) then 
         {
             fprintf(stderr,"malloc failed for C23[%d]\n",mem_init_i) and skip;
             fflush(stderr) and skip;
             exit$<==0 and skip 
             
         }
         else 
         {
              skip 
         };
         mem_init_i:=mem_init_i+1
         
     };
     V23:=(float **)malloc(ARCHnodes*sizeof(float *));
     if(V23=(float **)NULL) then 
     {
         fprintf(stderr,"malloc failed for V23\n") and skip;
         fflush(stderr) and skip;
         exit$<==0 and skip 
         
     }
     else 
     {
          skip 
     };
     mem_init_i:=0;
     
     while(mem_init_i<ARCHnodes)
     {
         V23[mem_init_i]:=(float *)malloc(3*sizeof(float));
         if(V23[mem_init_i]=(float *)NULL) then 
         {
             fprintf(stderr,"malloc failed for V23[%d]\n",mem_init_i) and skip;
             fflush(stderr) and skip;
             exit$<==0 and skip 
             
         }
         else 
         {
              skip 
         };
         mem_init_i:=mem_init_i+1
         
     };
     disp:=(float **)malloc(3*sizeof(int));
     mem_init_i:=0;
     
     while(mem_init_i<3)
     {
         disp[mem_init_i]:=(float **)malloc(ARCHnodes*sizeof(float *));
         if(disp[mem_init_i]=(float **)NULL) then 
         {
             fprintf(stderr,"malloc failed for disp[%d]\n",mem_init_i) and skip;
             fflush(stderr) and skip;
             exit$<==0 and skip 
             
         }
         else 
         {
              skip 
         };
         mem_init_j:=0;
         
         while(mem_init_j<ARCHnodes)
         {
             disp[mem_init_i,mem_init_j]:=(float *)malloc(3*sizeof(float));
             if(disp[mem_init_i,mem_init_j]=(float *)NULL) then 
             {
                 fprintf(stderr,"malloc failed for disp[%d][%d]\n",mem_init_i,mem_init_j) and skip;
                 fflush(stderr) and skip;
                 exit$<==0 and skip 
                 
             }
             else 
             {
                  skip 
             };
             mem_init_j:=mem_init_j+1
             
         };
         mem_init_i:=mem_init_i+1
         
     };
     K:=(float **)malloc(ARCHmatrixlen*sizeof(int));
     mem_init_i:=0;
     
     while(mem_init_i<ARCHmatrixlen)
     {
         K[mem_init_i]:=(float **)malloc(3*sizeof(float *));
         if(K[mem_init_i]=(float **)NULL) then 
         {
             fprintf(stderr,"malloc failed for K[%d]\n",mem_init_i) and skip;
             fflush(stderr) and skip;
             exit$<==0 and skip 
             
         }
         else 
         {
              skip 
         };
         mem_init_j:=0;
         
         while(mem_init_j<3)
         {
             K[mem_init_i,mem_init_j]:=(float *)malloc(3*sizeof(float));
             if(K[mem_init_i,mem_init_j]=(float *)NULL) then 
             {
                 fprintf(stderr,"malloc failed for K[%d][%d]\n",mem_init_i,mem_init_j) and skip;
                 fflush(stderr) and skip;
                 exit$<==0 and skip 
                 
             }
             else 
             {
                  skip 
             };
             mem_init_j:=mem_init_j+1
             
         };
         mem_init_i:=mem_init_i+1
         
     };
     mem_init_i:=0;
     
     while(mem_init_i<ARCHnodes)
     {
         nodekind[mem_init_i]:=0;
         mem_init_j:=0;
         
         while(mem_init_j<3)
         {
             M[mem_init_i,mem_init_j]:=0.0;
             C[mem_init_i,mem_init_j]:=0.0;
             M23[mem_init_i,mem_init_j]:=0.0;
             C23[mem_init_i,mem_init_j]:=0.0;
             V23[mem_init_i,mem_init_j]:=0.0;
             disp[0,mem_init_i,mem_init_j]:=0.0;
             disp[1,mem_init_i,mem_init_j]:=0.0;
             disp[2,mem_init_i,mem_init_j]:=0.0;
             mem_init_j:=mem_init_j+1
             
         };
         mem_init_i:=mem_init_i+1
         
     };
     mem_init_i:=0;
     
     while(mem_init_i<ARCHelems)
     {
         source_elms[mem_init_i]:=1;
         mem_init_i:=mem_init_i+1
         
     };
     mem_init_i:=0;
     
     while(mem_init_i<ARCHmatrixlen)
     {
         mem_init_j:=0;
         
         while(mem_init_j<3)
         {
             mem_init_k:=0;
             
             while(mem_init_k<3)
             {
                 K[mem_init_i,mem_init_j,mem_init_k]:=0.0;
                 mem_init_k:=mem_init_k+1
                 
             };
             mem_init_j:=mem_init_j+1
             
         };
         mem_init_i:=mem_init_i+1
         
     }
     )
 };
  main(RValue)
 )
