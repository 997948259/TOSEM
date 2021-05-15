//main_temp变量改成malloc
/*</
define p:read_img_i<=480;
alw(p)
/>*/
/*</
define p:read_img_i>0;
som(p)
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
 frame(exit,i,read_img_i,module_1,module_2,module_3,module_4) and
 (
 int module_1<==1 and skip;
 int module_2<==0 and skip;
 int module_3<==0 and skip;
 int module_4<==0 and skip;
 int exit,i and skip;
 int read_img_i and skip;
 
 struct BMP_img {
 int bfType and 
 int size and 
 int reser and 
 int header_length and 
 int infoheader_length and 
 int width and 
 int height and 
 int biplanes and 
 int bmp_type and 
 int compres and 
 int datasize and 
 int bixpm and 
 int biypm and 
 int clrused and 
 int relclrused and 
 unsigned char *image and 
 unsigned char *header_info and 
 int lineBytes 
 };
 struct Bmp1 {
 int width and 
 int height and 
 unsigned char strc[67,800] and 
 unsigned char *image and 
 int p1[15] and 
 int p2[15] and 
 int p3[15] and 
 int p4[15] and 
 int up and 
 int down and 
 unsigned char strr[7,2500] and 
 unsigned char string$[7] and 
 float ang 
 };
 struct HSV {
 float H and 
 float S and 
 int V 
 };
 struct RGB {
 unsigned char bitb and 
 unsigned char bitg and 
 unsigned char bitr and 
 unsigned char re 
 };
 function main_1 ( int RValue )
 {
     frame(main_HL,main_HH,main_VH,main_VL,main_img,main_img1,main_f,main_temp,main_temp1,main_path1,main_path,main_path3,return) and ( 
	 module_2<==1 and skip;
     int return<==0 and skip;
     int main_HL<==0,main_HH<==0,main_VH<==0,main_VL<==0 and skip;
     BMP_img *main_img<==(BMP_img *)malloc(sizeof(BMP_img)) and skip;
	 memset(main_img,0,sizeof(BMP_img)) and skip;
	 Bmp1 *main_img1<==(Bmp1 *)malloc(sizeof(Bmp1)) and skip;
     FILE *main_f and skip;
     unsigned char *main_temp,*main_temp1 and skip;
     char main_path1[80]<=="E:/input/test/moban/" and skip;
     char main_path[80]<=="E:\\input\\test\\1.bmp" and skip;
     char main_path3[40] and skip;
     output ("Please Input Path\n") and skip;
     output ("the path is :",main_path,"\n") and skip;
     main_f:=fopen (main_path,"rb") ;
     if((main_f)=NULL) then 
     {
         output ("\nCan not open the path: ",main_path," \n") and skip;
         exit<==0 and skip 
         
     }
     else 
     {
          skip 
     };
     read_img(main_f,main_img);
     fclose (main_f) and skip;
	 //output("yubin000\n") and skip;
     //main_temp:=myMalloc((*main_img).height*(*main_img).width*4,main_temp,0,RValue);
     //main_temp1:=myMalloc((*main_img).height*(*main_img).width*4,main_temp,0,RValue);
	 main_temp:=(unsigned char *)malloc((*main_img).height*(*main_img).width*4*sizeof(unsigned char));
	 main_temp1:=(unsigned char *)malloc((*main_img).height*(*main_img).width*4*sizeof(unsigned char));

     location((*main_img).image,(*main_img).width,(*main_img).height,15,&main_HL,&main_HH,&main_VL,&main_VH);


     CutBmp(*main_img,main_img1,main_HL,main_HH,main_VL,main_VH);
    	 
     Hough(main_img1);
	 
     xuanzhuan(main_img1);
	 
     location(main_img1->image,main_img1->width,main_img1->height,0,&main_HL,&main_HH,&main_VL,&main_VH);
     

     CutBmp1(main_img1,main_HL,main_HH,main_VL,main_VH);

	 
     huidu(*main_img1,main_img1->image,main_temp);
	 main_temp[1546]:=145;
	 main_temp[7187]:=178;
     
   
	
     displaytwo(*main_img1,main_temp,main_temp1,30);
	 
     
     delpoint(main_temp1,main_img1->width,main_img1->height,3);

     
     shuipingtouying(main_img1,main_temp1);
     
     delpoint(main_temp1,main_img1->width,main_img1->height,2);
     
	 cuizhitouying(main_img1,main_temp1);

	 
	
     memset(main_temp,0,1*(main_img1->width)*(main_img1->height)) and skip;
      
     
     strBmp(main_img1,main_temp1);

     guiyi(main_img1);

     readmoban(main_path1,main_img1);

     strout(main_img1);
     outtext(*main_img1,0,600);
     free(main_temp1) and skip;
     free(main_temp) and skip;
     return<==1 and RValue:=0;
	 free(main_img) and skip;
	 main_img<==NULL and skip;
	 free(main_img1) and skip;
	 main_img1<==NULL and skip;
     skip
     )
     }; 

     function printBmp_img(BMP_img *img)
     {
        output("bfType: ", img->bfType," ") and skip;
        output("size: ", img->size," ") and skip;
        output("reser: ", img->reser," ") and skip;
        output("header_length: ", img->header_length," ") and skip;
        output("infoheader_length: ", img->infoheader_length," ") and skip;
        output("width: ", img->width," ") and skip;
        output("height: ", img->height," ") and skip;
        output("biplanes: ", img->biplanes," ") and skip;
        output("bmp_type: ", img->bmp_type," ") and skip;
        output("compres: ", img->compres," ") and skip;
        output("datasize: ", img->datasize," ") and skip;
        output("bixpm: ", img->bixpm," ") and skip;
        output("biypm: ", img->biypm," ") and skip;
        output("clrused: ", img->clrused," ") and skip;
        output("relclrused: ", img->relclrused," ") and skip;
        output("lineBytes: ", img->lineBytes," ") and skip
     };

  function read_img ( FILE *infile,BMP_img *img )
 {
     frame(read_img_i,read_img_j,read_img_l,read_img_bitcolor,read_img_line24,read_img_line8,read_img_bitmap,read_img_3_temp,read_img_6_temp) and ( 
	 module_3<==1 and skip;
     int read_img_j,read_img_l,read_img_bitcolor and skip;
     int read_img_line24 and skip;
     int read_img_line8 and skip;
     RGB *read_img_bitmap and skip;
     fread(&(img->bfType),2,1,infile) and skip;
     fread(&img->size,4,1,infile) and skip;
     fread(&img->reser,4,1,infile) and skip;
     fread(&img->header_length,4,1,infile) and skip;
     fread(&img->infoheader_length,4,1,infile) and skip;
     fread(&img->width,4,1,infile) and skip;
     fread(&img->height,4,1,infile) and skip;
     fread(&img->biplanes,2,1,infile) and skip;
     fread(&img->bmp_type,2,1,infile) and skip;
     fread(&img->compres,4,1,infile) and skip;
     fread(&img->datasize,4,1,infile) and skip;
     fread(&img->bixpm,4,1,infile) and skip;
     fread(&img->biypm,4,1,infile) and skip;
     fread(&img->clrused,4,1,infile) and skip;
     fread(&img->relclrused,4,1,infile) and skip;
     img->lineBytes:=(img->width*img->bmp_type+31)/ 32*4;
     read_img_line24:=(img->width*24+31)/ 32*4;
     read_img_line8:=(img->width*8+31)/ 32*4;
     if(img->bmp_type=1) then 
     {
         read_img_bitcolor:=2;
         output ("不能读取退出") and skip;
         exit<==0 and skip 
         
     }
     else 
     {
          skip 
     };
     if(img->bmp_type=4) then 
     {
         read_img_bitcolor:=16;
         output ("不能读取退出") and skip;
         exit<==0 and skip 
         
     }
     else 
     {
          skip 
     };
	 output("aaaaa\n") and skip;
     if(img->bmp_type=8) then 
     {
         unsigned char *read_img_3_temp and skip;
         read_img_3_temp:=(unsigned char *)malloc(img->height*read_img_line8*sizeof(unsigned char));
         memset(read_img_3_temp,0,img->height*img->lineBytes*1) and skip;
         read_img_bitcolor:=256;
         read_img_bitmap:=(RGB *)calloc(read_img_bitcolor,4);
         img->image:=(unsigned char *)malloc((read_img_line8*img->height)*sizeof(unsigned char));
         memset(img->image,0,1*read_img_line8*img->height) and skip;
         if(img->image=NULL) then 
         {
             //fprintf(stderr,"\n Allocation error for temp in read_bmp() \n",RValue)
             output("\n Allocation error for temp in read_bmp() \n") and skip
         }
         else 
         {
              skip 
         };
         fseek(infile,0x54,0) and skip;
         fread(read_img_bitmap,sizeof(RGB),read_img_bitcolor,infile) and skip;
         fseek(infile,img->header_length,0) and skip;
         fread(read_img_3_temp,img->lineBytes*img->height,1,infile) and skip;
         if(read_img_3_temp=NULL) then 
         {
             output ("\n读取失败\n") and skip
         }
         else 
         {
              skip 
         };
         read_img_i:=0;
         
         while(read_img_i<img->height)
         {
             read_img_j:=0;
             
             while(read_img_j<img->width)
             {
                 img->image[read_img_i*img->width+read_img_j]:=(unsigned char)(0.299*read_img_bitmap[read_img_3_temp[read_img_i*read_img_line8+read_img_j]].bitb+0.578*read_img_bitmap[read_img_3_temp[read_img_i*read_img_line8+read_img_j]].bitg+0.114*read_img_bitmap[read_img_3_temp[read_img_i*read_img_line8+read_img_j]].bitr);
                 read_img_j:=read_img_j+1
                 
             };
             read_img_i:=read_img_i+1
             
         };
         free(read_img_3_temp) and skip;
         read_img_3_temp:=NULL
         
     }
     else 
     {
          skip 
     };

     if(img->bmp_type=24) then 
     {

         unsigned char *read_img_6_temp and skip;
		 //output("yubin333\n") and skip;
         read_img_6_temp:=(unsigned char *)malloc(img->height*sizeof(unsigned char)*img->lineBytes);
		 //output("yubin444\n") and skip;
         img->image:=(unsigned char *)malloc(sizeof(unsigned char)*((read_img_line24)*img->height));
         if(read_img_6_temp=NULL) then 
         {
             exit<==0 and skip 
         }
         else 
         {
              skip 
         };
         if(img->image=NULL) then 
         {
             //fprintf(stderr,"\n Allocation error for temp in read_bmp() \n",RValue)
             output("\n Allocation error for temp in read_bmp() \n") and skip
         }
         else 
         {
              skip 
         };
         fseek(infile,img->header_length,0) and skip;
         fread(read_img_6_temp,1,(img->lineBytes)*img->height,infile) and skip;
         read_img_i:=0;
         

         while(read_img_i<img->height)
         {
             read_img_l:=0;
             read_img_j:=0;
             
             while(read_img_j<img->width*3)
             {
                 read_img_l:=(img->height-read_img_i-1)*img->width*3+read_img_j;
                 img->image[read_img_l+2]:=* (read_img_6_temp+read_img_i*img->lineBytes+read_img_j+2);
                 img->image[read_img_l+1]:=* (read_img_6_temp+read_img_i*img->lineBytes+read_img_j+1);
                 img->image[read_img_l]:=* (read_img_6_temp+read_img_i*img->lineBytes+read_img_j);
                 read_img_j:=read_img_j+3
                 
             };
             read_img_i:=read_img_i+1
             
         };
         free(read_img_6_temp) and skip;
         read_img_6_temp:=NULL
         
     }
     else 
     {
          skip 
     }
	 
     )
   }; 
  function readstr ( FILE *infile,unsigned char *srcBmp )
 {
     frame(readstr_width,readstr_height,readstr_headlength,readstr_i,readstr_j,readstr_bitcolor,readstr_line8,readstr_temp,readstr_temp1,readstr_bitmap) and ( 
     int readstr_width,readstr_height,readstr_headlength and skip;
     int readstr_i,readstr_j,readstr_bitcolor,readstr_line8 and skip;
     unsigned char readstr_temp[800] and skip;
     unsigned char readstr_temp1 and skip;
	 RGB readstr_bitmap_tmp[256] and skip;
     RGB *readstr_bitmap and skip;
	 readstr_bitmap<==&readstr_bitmap_tmp and skip;
     readstr_width:=20;
     readstr_height:=40;
     readstr_headlength:=1078;
     readstr_line8:=(readstr_width*8+31)/ 32*4;
	 //output("yubin555\n") and skip;
     //readstr_temp:=(unsigned char *)malloc(readstr_height*readstr_line8*sizeof(unsigned char));
	
     memset(readstr_temp,0,readstr_height*readstr_line8*1) and skip;
     readstr_bitcolor:=256;
	 //output("yubin666\n") and skip;
     //readstr_bitmap:=(RGB *)malloc(readstr_bitcolor*sizeof(RGB));

     fseek(infile,54,0) and skip;

     fread(readstr_bitmap,sizeof(RGB),readstr_bitcolor,infile) and skip;
     fseek(infile,readstr_headlength,0) and skip;
     fread(readstr_temp,readstr_line8*readstr_height,1,infile) and skip;
	 //output("666\n") and skip;
	          
     if(readstr_temp=NULL) then 
     {
         output ("\n读取失败\n") and skip;
         exit<==0 and skip 
         
     }
     else 
     {
          skip 
     };
     readstr_i:=0;
    
     while(readstr_i<readstr_height)
     {
         readstr_j:=0;
         
         while(readstr_j<readstr_width)
         {
             readstr_temp1:=readstr_temp[readstr_i*readstr_line8+readstr_j];
             if(readstr_temp1>=150) then 
             {
                 readstr_temp1:=255
             }
             else
             {
                 readstr_temp1:=0
             };
             srcBmp[(readstr_height-readstr_i-1)*readstr_width+readstr_j]:=readstr_temp1;
             readstr_j:=readstr_j+1
             
         };
         readstr_i:=readstr_i+1
         
     }
     //free(readstr_temp) and skip;
     //readstr_temp:=NULL
     )
     }; 
  function grayScale ( BMP_img img,unsigned char *srcBmp,unsigned char *dstBmp )
 {
     frame(grayScale_i,grayScale_j,grayScale_temp1,grayScale_n,grayScale_gray) and ( 
     int grayScale_i,grayScale_j,grayScale_temp1,grayScale_n and skip;
     float grayScale_gray and skip;
     grayScale_temp1:=img.width*3;
     srcBmp:=img.image;
     grayScale_i:=0;
     
     while(grayScale_i<img.height)
     {
         grayScale_j:=0 ; grayScale_n:=0;
         while(grayScale_j<img.width)
         {
             grayScale_gray:=(* (srcBmp+grayScale_i*img.lineBytes+grayScale_n+2)*0.299)+(* (srcBmp+grayScale_i*img.lineBytes+grayScale_n+1)*0.578)+(* (srcBmp+grayScale_i*img.lineBytes+grayScale_n)*0.114);
             dstBmp[grayScale_i*img.lineBytes+grayScale_n]:=(unsigned char)(grayScale_gray+0.5);
             dstBmp[grayScale_i*img.lineBytes+grayScale_n+1]:=(unsigned char)(grayScale_gray+0.5);
             dstBmp[grayScale_i*img.lineBytes+grayScale_n+2]:=(unsigned char)(grayScale_gray+0.5);
             grayScale_n:=grayScale_n+3 ; grayScale_j:=grayScale_j+1
             
         };
         grayScale_i:=grayScale_i+1
         
     }
     )
     }; 
  function huidu ( Bmp1 img,unsigned char *srcBmp,unsigned char *dstBmp )
 {
     frame(huidu_i,huidu_j,huidu_n,huidu_gray) and ( 
     int huidu_i,huidu_j,huidu_n and skip;
     float huidu_gray and skip;
     srcBmp:=img.image;
     huidu_i:=0;
     
     while(huidu_i<img.height)
     {
         huidu_j:=0 ; huidu_n:=0;
         while(huidu_j<img.width)
         {
             huidu_gray:=(* (srcBmp+huidu_i*img.width*3+huidu_n+2)*0.299)+(* (srcBmp+huidu_i*img.width*3+huidu_n+1)*0.578)+(* (srcBmp+huidu_i*img.width*3+huidu_n)*0.114);
             dstBmp[huidu_i*img.width+huidu_j]:=(unsigned char)(huidu_gray+0.5);
             huidu_n:=huidu_n+3 ; huidu_j:=huidu_j+1
             
         };
         huidu_i:=huidu_i+1
         
     }
     )
     }; 
  function hsvzation ( unsigned char *image,HSV *hsv,int width,int height )
 {
     frame(hsvzation_i,hsvzation_j,hsvzation_k,hsvzation_min,hsvzation_max,hsvzation_delta,hsvzation_tmp,hsvzation_r,hsvzation_g,hsvzation_b,continue, temp) and ( 
     int continue<==0 and skip;
     int hsvzation_i,hsvzation_j,hsvzation_k and skip;
     float hsvzation_min,hsvzation_max,hsvzation_delta,hsvzation_tmp and skip;
     unsigned char hsvzation_r,hsvzation_g,hsvzation_b and skip;
     hsvzation_i:=0;
  
     while(hsvzation_i<height)
     {
         continue<==0 and skip;
         hsvzation_k:=0 ; hsvzation_j:=0;

         while(hsvzation_j<width*3)
         {
              continue<==0 and skip;
             hsvzation_g:=image[hsvzation_i*width*3+hsvzation_j+1];
             hsvzation_b:=image[hsvzation_i*width*3+hsvzation_j];
             hsvzation_r:=image[hsvzation_i*width*3+hsvzation_j+2];
            
             hsvzation_tmp:=(( if((hsvzation_r<hsvzation_g)) then hsvzation_r else hsvzation_g));
             hsvzation_min:=(( if((hsvzation_tmp<hsvzation_b)) then hsvzation_tmp else hsvzation_b));
             hsvzation_tmp:=(( if((hsvzation_r>hsvzation_g)) then hsvzation_r else hsvzation_g));
             hsvzation_max:=(( if((hsvzation_tmp>hsvzation_b)) then hsvzation_tmp else hsvzation_b));
             hsv[hsvzation_i*width+hsvzation_k].V:=(int)hsvzation_max;
             hsvzation_delta:=hsvzation_max-hsvzation_min;
              
             if(hsvzation_delta=0) then 
             {
                 hsv[hsvzation_i*width+hsvzation_k].H:=0;
                 continue<==1 and skip;
                  hsvzation_k:=hsvzation_k+1 ; hsvzation_j:=hsvzation_j+3
             }
             else 
             {
                  skip 
             };
             if(continue=0)   then 
             {
                
                 if(hsvzation_max!=0) then 
                 {
                     hsv[hsvzation_i*width+hsvzation_k].S:=hsvzation_delta/ hsvzation_max
                 }
                 else
                 {
                     hsv[hsvzation_i*width+hsvzation_k].S:=0;
                     hsv[hsvzation_i*width+hsvzation_k].H:=0;
                     continue<==1 and skip;
                      hsvzation_k:=hsvzation_k+1 ; hsvzation_j:=hsvzation_j+3};
                     if(continue=0)  then 
                     {

                         if(hsvzation_r=hsvzation_max) then 
                         {
                             hsv[hsvzation_i*width+hsvzation_k].H:=(hsvzation_g-hsvzation_b)/ hsvzation_delta

                         }
                         else
                         {

                             if(hsvzation_g=hsvzation_max) then 
                             {
                                 hsv[hsvzation_i*width+hsvzation_k].H:=2+(hsvzation_b-hsvzation_r)
                             }
                             else
                             {
                                 hsv[hsvzation_i*width+hsvzation_k].H:=4+(hsvzation_r-hsvzation_g)/ hsvzation_delta
                             }
 
                         };
                         hsv[hsvzation_i*width+hsvzation_k].H:=hsv[hsvzation_i*width+hsvzation_k].H*60;
                         if(hsv[hsvzation_i*width+hsvzation_k].H<0) then 
                         {
                             hsv[hsvzation_i*width+hsvzation_k].H:=hsv[hsvzation_i*width+hsvzation_k].H+360
                         }
                         else 
                         {
                              skip 
                         };
                         hsvzation_k:=hsvzation_k+1 ; hsvzation_j:=hsvzation_j+3

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
             hsvzation_i:=hsvzation_i+1
             
         }
         )
         }; 
  function location ( unsigned char *image,int width,int height,int yuzhi,int *HL,int *HH,int *VL,int *VH )
 {
     frame(location_i,location_j,location_n,location_maxnum,location_flag,location_hsv,location_temp,location_temp1,break$) and (
	 module_4<==1 and skip;
     int break$<==0 and skip;
     int location_i,location_j,location_n,location_maxnum,location_flag<==0 and skip;
     HSV *location_hsv and skip;
     int location_temp[2000] and skip;
    memset(location_temp,0,8000) and skip;
     unsigned char *location_temp1 and skip;
	 //output("yubin777\n") and skip;
     location_hsv:=(HSV *)malloc(width*sizeof(HSV)*height);
	 
     hsvzation(image,location_hsv,width,height);
	 //output("yubin777\n") and skip;
	 //output("yubin888\n") and skip;
     location_temp1:=(unsigned char *)malloc(height*sizeof(unsigned char)*width);
      
     location_i:=0;
 
     while(location_i<height)
     {
         location_j:=0 ; location_n:=0;
         while(location_j<width)
         {
             if((location_hsv[location_i*width+location_j].H<220.0) AND (location_hsv[location_i*width+location_j].H>180.0) AND (location_hsv[location_i*width+location_j].V<250) AND (location_hsv[location_i*width+location_j].S>0.6)) then 
             {
                 location_temp1[location_i*width+location_j]:=255
                 
             }
             else
             {
                 location_temp1[location_i*width+location_j]:=0
             };
             location_n:=location_n+3 ; location_j:=location_j+1
             
         };
         location_i:=location_i+1
         
     };
     location_i:=0;
     
     while(location_i<height)
     {
         location_j:=0;
         
         while(location_j<width)
         {
             if(location_temp1[location_i*width+location_j]=255) then 
             {
                 location_temp[location_i]:=location_temp[location_i]+1
                 
             }
             else 
             {
                  skip 
             };
             location_j:=location_j+1
             
         };
         location_i:=location_i+1
         
     };

     edgesob8(location_temp1,width,height);
     location_maxnum:=location_temp[0];
     location_i:=1;
     while(location_i<height)
     {
         if(location_temp[location_i]>location_maxnum) then 
         {
             location_maxnum:=location_temp[location_i]
         }
         else 
         {
              skip 
         };
         location_i:=location_i+1
         
     };
     location_maxnum:=location_maxnum/ 3;
     break$<==0 and skip;
     location_i:=0;
     
     while( break$=0 AND  location_i<height)
     {
         if(location_flag=0) then 
         {
             if(location_temp[location_i]>location_maxnum) then 
             {
                 * HL:=location_i-yuzhi;
                 location_flag:=1
                 
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
         if(location_flag=1) then 
         {
             if(location_temp[location_i]=0) then 
             {
                 * HH:=location_i+yuzhi;
                 break$<==1 and skip
                  
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
         if(break$=0)   then 
         {
             location_i:=location_i+1
         }
         else
         {
             skip
         }
         
     };
     break$<==0 and skip;
     memset(location_temp,0,4*width) and skip;
     location_i:=0;
     
     while(location_i<width)
     {
         location_j:=0;
         
         while(location_j<height)
         {
             if(location_temp1[location_j*width+location_i]=255) then 
             {
                 location_temp[location_i]:=location_temp[location_i]+1
                 
             }
             else 
             {
                  skip 
             };
             location_j:=location_j+1
             
         };
         location_i:=location_i+1
         
     };
     location_flag:=0;
     location_maxnum:=location_temp[0];
     location_i:=1;
     
     while(location_i<width)
     {
         if(location_temp[location_i]>location_maxnum) then 
         {
             location_maxnum:=location_temp[location_i]
         }
         else 
         {
              skip 
         };
         location_i:=location_i+1
         
     };
     location_maxnum:=location_maxnum/ 3;
     break$<==0 and skip;
     location_i:=0;
     
     while( break$=0 AND  location_i<width)
     {
         if(location_temp[location_i]>location_maxnum) then 
         {
             * VL:=location_i-yuzhi;
             break$<==1 and skip
              
         }
         else 
         {
              skip 
         };
         if(break$=0)   then
         {
             location_i:=location_i+1
         }
         else
         {
             skip
         }
         
     };
     break$<==0 and skip;
     break$<==0 and skip;
     location_i:=width;
     
     while( break$=0 AND  location_i>* VL)
     {
         if(location_temp[location_i]>location_maxnum) then 
         {
             * VH:=location_i+yuzhi;
             break$<==1 and skip
              
         }
         else 
         {
              skip 
         };
         if(break$=0)   then
         {
             location_i:=location_i-1
         }
         else
         {
             skip
         }
         
     };
     break$<==0 and skip;
     free(location_temp1) and skip;
     location_temp1:=NULL;
     free(location_hsv) and skip
     )
     }; 
  function Hough ( Bmp1 *img )
 {
     frame(Hough_i,Hough_j,Hough_n,Hough_ang,Hough_temp1,Hough_hsv) and ( 
     int Hough_i,Hough_j,Hough_n and skip;
     float Hough_ang and skip;
     unsigned char *Hough_temp1 and skip;
     HSV *Hough_hsv and skip;
     Hough_hsv:=(HSV *)malloc(img->width*sizeof(HSV)*img->height);
     hsvzation(img->image,Hough_hsv,img->width,img->height);
     Hough_temp1:=(unsigned char *)malloc(img->height*sizeof(unsigned char)*img->width);
     Hough_i:=0;
     
     while(Hough_i<img->height)
     {
         Hough_j:=0 ; Hough_n:=0;
         while(Hough_j<img->width)
         {
             if((Hough_hsv[Hough_i*img->width+Hough_j].H<220.0) AND (Hough_hsv[Hough_i*img->width+Hough_j].H>180.0) AND (Hough_hsv[Hough_i*img->width+Hough_j].V<250) AND (Hough_hsv[Hough_i*img->width+Hough_j].S>0.6)) then 
             {
                 Hough_temp1[Hough_i*img->width+Hough_j]:=255
                 
             }
             else
             {
                 Hough_temp1[Hough_i*img->width+Hough_j]:=0
             };
             Hough_n:=Hough_n+3 ; Hough_j:=Hough_j+1
             
         };
         Hough_i:=Hough_i+1
         
     };
     Dilation(Hough_temp1,img->width,img->height,1,5);
     sob(Hough_temp1,img->width,img->height,0); 
      memset(Hough_temp1,0,img->height*sizeof(unsigned char)*img->width) and skip;


     Hough_ang:=hough(Hough_temp1,img->width,img->height,RValue);
     if((Hough_ang<=8) AND (Hough_ang>=1)) then 
     {
         Hough_ang:=Hough_ang-1
     }
     else 
     {
          skip 
     };
     if(Hough_ang>90) then 
     {
         Hough_ang:=Hough_ang-180
         
     }
     else 
     {
          skip 
     };
     img->ang:=Hough_ang
     )
     }; 
  function bmptwo ( Bmp1 img,unsigned char *srcBmp,unsigned char *dstBmp,unsigned char yuzhi )
 {
     frame(bmptwo_i,bmptwo_j) and ( 
     int bmptwo_i,bmptwo_j and skip;
     bmptwo_i:=0;
     
     while(bmptwo_i<img.height)
     {
         bmptwo_j:=0;
         
         while(bmptwo_j<img.width)
         {
             if(srcBmp[bmptwo_i*img.width+bmptwo_j]>=yuzhi) then 
             {
                 dstBmp[bmptwo_i*img.width+bmptwo_j]:=255
                 
             }
             else
             {
                 dstBmp[bmptwo_i*img.width+bmptwo_j]:=0
             };
             bmptwo_j:=bmptwo_j+1
             
         };
         bmptwo_i:=bmptwo_i+1
         
     }
     )
     }; 
  function displaytwo ( Bmp1 img,unsigned char *srcBmp,unsigned char *dstBmp,int yuzhi )
 {
     frame(displaytwo_totalPixels,displaytwo_bestT,displaytwo_i,displaytwo_j,displaytwo_histogramArray,displaytwo_densityArray,displaytwo_u0,displaytwo_u1,displaytwo_w0,displaytwo_w1,displaytwo_bestDeviation) and ( 
     int displaytwo_totalPixels<==img.width*img.height and skip;
     int displaytwo_bestT<==0 and skip;
     int displaytwo_i,displaytwo_j and skip;
     int displaytwo_histogramArray[256] and skip;
     memset(displaytwo_histogramArray,0,256*4) and skip;
     float displaytwo_densityArray[256] and skip;
     memset(displaytwo_densityArray,0,256*4) and skip;
     float displaytwo_u0<==0 and skip;
     float displaytwo_u1<==0 and skip;
     float displaytwo_w0<==0 and skip;
     float displaytwo_w1<==0 and skip;
     float displaytwo_bestDeviation<==0 and skip;
     displaytwo_i:=0;

  
	 while(displaytwo_i<img.height)
     {
         displaytwo_j:=0;
         while(displaytwo_j<img.width)
         {
             displaytwo_histogramArray[(unsigned int)srcBmp[displaytwo_i*img.width+displaytwo_j]]:=displaytwo_histogramArray[(unsigned int)srcBmp[displaytwo_i*img.width+displaytwo_j]]+1;
             displaytwo_j:=displaytwo_j+1
             
         };
         displaytwo_i:=displaytwo_i+1
         
     };

	

     displaytwo_i:=0;
     
     while(displaytwo_i<256)
     {
         displaytwo_densityArray[displaytwo_i]:=displaytwo_histogramArray[displaytwo_i]*1.0/ displaytwo_totalPixels;
         displaytwo_i:=displaytwo_i+1
         
     };
     displaytwo_i:=0;
     
     while(displaytwo_i<256)
     {
         displaytwo_w0:=0;
         displaytwo_w1:=0;
         displaytwo_j:=0;
         
         while(displaytwo_j<=displaytwo_i)
         {
             displaytwo_w0:=displaytwo_w0+displaytwo_densityArray[displaytwo_j];
             displaytwo_j:=displaytwo_j+1
             
         };
         displaytwo_j:=displaytwo_i+1;
         
         while(displaytwo_j<256)
         {
             displaytwo_w1:=displaytwo_w1+displaytwo_densityArray[displaytwo_j];
             displaytwo_j:=displaytwo_j+1
             
         };
         displaytwo_u0:=0;
         displaytwo_u1:=0;
         displaytwo_j:=0;
         
         while(displaytwo_j<=displaytwo_i)
         {
             displaytwo_u0:=displaytwo_u0+displaytwo_j*displaytwo_densityArray[displaytwo_j];
             displaytwo_j:=displaytwo_j+1
             
         };
         displaytwo_j:=displaytwo_i+1;
         
         while(displaytwo_j<256)
         {
             displaytwo_u1:=displaytwo_u1+displaytwo_j*displaytwo_densityArray[displaytwo_j];
             displaytwo_j:=displaytwo_j+1
             
         };
         displaytwo_u0:=displaytwo_u0/ displaytwo_w0;
         displaytwo_u1:=displaytwo_u1/ displaytwo_w1;
		
         if(displaytwo_w0*displaytwo_w1*(displaytwo_u0-displaytwo_u1)*(displaytwo_u0-displaytwo_u1)>displaytwo_bestDeviation) then 
         {
             displaytwo_bestT:=displaytwo_i;
		
             displaytwo_bestDeviation:=displaytwo_w0*displaytwo_w1*(displaytwo_u0-displaytwo_u1)*(displaytwo_u0-displaytwo_u1)
             
         }
         else 
         {
              skip 
         };
         displaytwo_i:=displaytwo_i+1
         
     };
     displaytwo_i:=0;
     
     while(displaytwo_i<256)
     {
         displaytwo_histogramArray[displaytwo_i]:=0;
         displaytwo_i:=displaytwo_i+1
         
     };
	 
     displaytwo_bestT:=displaytwo_bestT+yuzhi;
	 
     if(displaytwo_bestT<0) then 
     {
         displaytwo_bestT:=0
     }
     else 
     {
          skip 
     };
     if(displaytwo_bestT>255) then 
     {
         displaytwo_bestT:=255
     }
     else 
     {
          skip 
     };
     displaytwo_i:=0;
     while(displaytwo_i<img.height)
     {
         displaytwo_j:=0;
         
         while(displaytwo_j<img.width)
         {
             if(srcBmp[displaytwo_i*img.width+displaytwo_j]>displaytwo_bestT) then 
             {
                 dstBmp[displaytwo_i*img.width+displaytwo_j]:=255
                 
             }
             else
             {
                 dstBmp[displaytwo_i*img.width+displaytwo_j]:=0
             };
             displaytwo_j:=displaytwo_j+1
             
         };
         displaytwo_i:=displaytwo_i+1
         
     }
     )
     }; 
  function myMedianFilter ( Bmp1 img,unsigned char *temp,int iFilterH,int iFilterW,int iFilterMX,int iFilterMY,int RValue )
 {
     frame(myMedianFilter_lpSrc,myMedianFilter_lpDst,myMedianFilter_lHeight,myMedianFilter_lWidth,myMedianFilter_aValue,myMedianFilter_hArray,myMedianFilter_i,myMedianFilter_j,myMedianFilter_l,myMedianFilter_k,myMedianFilter_lpNewDIBBits,return) and ( 
     int return<==0 and skip;
     unsigned char *myMedianFilter_lpSrc and skip;
     unsigned char *myMedianFilter_lpDst and skip;
     int myMedianFilter_lHeight<==img.height and skip;
     int myMedianFilter_lWidth<==img.width and skip;
     unsigned char *myMedianFilter_aValue and skip;
     unsigned char *myMedianFilter_hArray and skip;
     int myMedianFilter_i,myMedianFilter_j,myMedianFilter_l,myMedianFilter_k and skip;
     unsigned char *myMedianFilter_lpNewDIBBits and skip;
	 //output("yubin111111\n") and skip;
     myMedianFilter_lpNewDIBBits:=(unsigned char *)malloc(img.height*sizeof(unsigned char)*img.width);
     if(myMedianFilter_lpNewDIBBits=NULL) then 
     {
         exit<==0 and skip 
     }
     else 
     {
          skip 
     };
     memcpy(myMedianFilter_lpNewDIBBits,temp,img.width*myMedianFilter_lHeight) and skip;
	 //output("yubin121212\n") and skip;
     myMedianFilter_hArray:=(unsigned char *)malloc(iFilterH*sizeof(unsigned char)*iFilterW);
	 //output("yubin131313\n") and skip;
     myMedianFilter_aValue:=(unsigned char *)malloc(iFilterH*sizeof(unsigned char)*iFilterW);
     myMedianFilter_i:=iFilterMY;
     
     while(myMedianFilter_i<myMedianFilter_lHeight-iFilterH+iFilterMY+1)
     {
         myMedianFilter_j:=iFilterMX;
         
         while(myMedianFilter_j<myMedianFilter_lWidth-iFilterW+iFilterMX+1)
         {
             myMedianFilter_lpDst:=(unsigned char *)myMedianFilter_lpNewDIBBits+img.width*(myMedianFilter_lHeight-1-myMedianFilter_i)+myMedianFilter_j;
             myMedianFilter_k:=0;
             
             while(myMedianFilter_k<iFilterH)
             {
                 myMedianFilter_l:=0;
                 
                 while(myMedianFilter_l<iFilterW)
                 {
                     myMedianFilter_lpSrc:=(unsigned char *)temp+img.width*(myMedianFilter_lHeight-1-myMedianFilter_i+iFilterMY-myMedianFilter_k)+myMedianFilter_j-iFilterMX+myMedianFilter_l;
                     myMedianFilter_aValue[myMedianFilter_k*iFilterW+myMedianFilter_l]:=* myMedianFilter_lpSrc;
                     myMedianFilter_l:=myMedianFilter_l+1
                     
                 };
                 myMedianFilter_k:=myMedianFilter_k+1
                 
             };
             * myMedianFilter_lpDst:=myGetMedianNum(myMedianFilter_aValue,iFilterH*iFilterW,RValue);
             myMedianFilter_j:=myMedianFilter_j+1
             
         };
         myMedianFilter_i:=myMedianFilter_i+1
         
     };
     memcpy(temp,myMedianFilter_lpNewDIBBits,img.width*img.height) and skip;
     free(myMedianFilter_lpNewDIBBits) and skip;
     myMedianFilter_lpNewDIBBits:=NULL;
     free(myMedianFilter_hArray) and skip;
     myMedianFilter_hArray:=NULL;
     return<==1 and RValue:=1;
     skip
     )
     }; 
  function myGetMedianNum ( unsigned char *bArray,int iFilterLen,unsigned char RValue )
 {
     frame(myGetMedianNum_i,myGetMedianNum_j,myGetMedianNum_bTemp,return) and ( 
     int return<==0 and skip;
     int myGetMedianNum_i and skip;
     int myGetMedianNum_j and skip;
     unsigned char myGetMedianNum_bTemp and skip;
     myGetMedianNum_j:=0;
     
     while(myGetMedianNum_j<iFilterLen-1)
     {
         myGetMedianNum_i:=0;
         
         while(myGetMedianNum_i<iFilterLen-myGetMedianNum_j-1)
         {
             if(bArray[myGetMedianNum_i]>bArray[myGetMedianNum_i+1]) then 
             {
                 myGetMedianNum_bTemp:=bArray[myGetMedianNum_i];
                 bArray[myGetMedianNum_i]:=bArray[myGetMedianNum_i+1];
                 bArray[myGetMedianNum_i+1]:=myGetMedianNum_bTemp
                 
             }
             else 
             {
                  skip 
             };
             myGetMedianNum_i:=myGetMedianNum_i+1
             
         };
         myGetMedianNum_j:=myGetMedianNum_j+1
         
     };
     if((iFilterLen & 1)>0) then 
     {
         myGetMedianNum_bTemp:=bArray[(iFilterLen+1)/ 2]
         
     }
     else
     {
         myGetMedianNum_bTemp:=(bArray[iFilterLen/ 2]+bArray[iFilterLen/ 2+1])/ 2
     };
     return<==1 and RValue:=myGetMedianNum_bTemp;
     skip
     )
     }; 
  function shuipingtouying ( Bmp1 *img,unsigned char *dst )
 {
     frame(shuipingtouying_temp,shuipingtouying_i,shuipingtouying_j,shuipingtouying_p,break$) and ( 
     int break$<==0 and skip;
     unsigned char shuipingtouying_temp and skip;
     int shuipingtouying_i,shuipingtouying_j and skip;
     int shuipingtouying_p[500] and skip;
     memset(shuipingtouying_p,0,500*4) and skip;
     memset(shuipingtouying_p,0,img->height*4) and skip;
     shuipingtouying_i:=0;
     
     while(shuipingtouying_i<img->width)
     {
         if((dst[shuipingtouying_i]>=200) OR (dst[img->width+shuipingtouying_i]>=200)) then 
         {
             break$<==0 and skip;
             shuipingtouying_j:=0;
             
             while( break$=0 AND  shuipingtouying_j<img->height)
             {
                 if(dst[shuipingtouying_j*img->width+shuipingtouying_i]>=200) then 
                 {
                     dst[shuipingtouying_j*img->width+shuipingtouying_i]:=0
                 }
                 else
                 {
                     break$<==1 and skip
                  };
                 if(break$=0)   then 
                 {
                     shuipingtouying_j:=shuipingtouying_j+1
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
         shuipingtouying_i:=shuipingtouying_i+1
         
     };
     shuipingtouying_i:=0;
     
     while(shuipingtouying_i<img->width)
     {
         if((dst[img->width*(img->height-1)+shuipingtouying_i]>=200) OR (dst[img->width*(img->height-2)+shuipingtouying_i]>=200)) then 
         {
             break$<==0 and skip;
             shuipingtouying_j:=img->height-1;
             
             while( break$=0 AND  shuipingtouying_j>0)
             {
                 if(dst[shuipingtouying_j*img->width+shuipingtouying_i]>=200) then 
                 {
                     dst[shuipingtouying_j*img->width+shuipingtouying_i]:=0
                 }
                 else
                 {
                     break$<==1 and skip
                  };
                 if(break$=0)   then 
                 {
                     shuipingtouying_j:=shuipingtouying_j-1
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
         shuipingtouying_i:=shuipingtouying_i+1
         
     };
     shuipingtouying_i:=2;

     while(shuipingtouying_i<img->height-2)
     {
         shuipingtouying_j:=0;
         
         while(shuipingtouying_j<img->width)
         {
             if(dst[shuipingtouying_i*img->width+shuipingtouying_j]>=200) then 
             {
                 shuipingtouying_p[shuipingtouying_i]:=shuipingtouying_p[shuipingtouying_i]+1
             }
             else 
             {
                  skip 
             };
             shuipingtouying_j:=shuipingtouying_j+1
             
         };
         shuipingtouying_i:=shuipingtouying_i+1
         
     };
     shuipingtouying_temp:=0;
     shuipingtouying_i:=0;
     
     while(shuipingtouying_i<img->height)
     {

         if(shuipingtouying_p[shuipingtouying_i]>shuipingtouying_temp) then 
         {
             shuipingtouying_temp:=shuipingtouying_p[shuipingtouying_i]
             
         }
         else 
         {
              skip 
         };
         shuipingtouying_i:=shuipingtouying_i+1
         
     };
     shuipingtouying_j:=shuipingtouying_temp/ 5;
     break$<==0 and skip;
     shuipingtouying_i:=img->height;

     while( break$=0 AND  shuipingtouying_i>img->up)
     {
         if(shuipingtouying_p[shuipingtouying_i]>shuipingtouying_j) then 
         {
             img->down:=shuipingtouying_i;
             break$<==1 and skip
              
         }
         else 
         {
              skip 
         };
         if(break$=0)   then
         {
             if(shuipingtouying_i<img->height/ 2) then 
             {
                 exit<==0 and skip 
             }
             else 
             {
                  skip 
             };
             shuipingtouying_i:=shuipingtouying_i-1
         }
         else
         {
             skip
         }
         
     };
     break$<==0 and skip;
     shuipingtouying_j:=shuipingtouying_temp/ 3;
     break$<==0 and skip;
     shuipingtouying_i:=0;
     
     while( break$=0 AND  shuipingtouying_i<img->down)
     {
         if(shuipingtouying_p[shuipingtouying_i]>shuipingtouying_j) then 
         {
             img->up:=shuipingtouying_i;
             break$<==1 and skip
              
         }
         else 
         {
              skip 
         };
         if(break$=0)   then
         {
             if(shuipingtouying_i>img->height/ 2) then 
             {
                 exit<==0 and skip 
             }
             else 
             {
                  skip 
             };
             shuipingtouying_i:=shuipingtouying_i+1
         }
         else
         {
             skip
         }
         
     };
     break$<==0 and skip;
     shuipingtouying_i:=0;
     
     while(shuipingtouying_i<img->up-1)
     {
         shuipingtouying_j:=0;
         
         while(shuipingtouying_j<img->width)
         {
             dst[shuipingtouying_i*img->width+shuipingtouying_j]:=0;
             shuipingtouying_j:=shuipingtouying_j+1
             
         };
         shuipingtouying_i:=shuipingtouying_i+1
         
     };
     shuipingtouying_i:=img->height;
     
     while(shuipingtouying_i>img->down+1)
     {
         shuipingtouying_j:=0;
         
         while(shuipingtouying_j<img->width)
         {
             dst[shuipingtouying_i*img->width+shuipingtouying_j]:=0;
             shuipingtouying_j:=shuipingtouying_j+1
             
         };
         shuipingtouying_i:=shuipingtouying_i-1
         
     }
     )
     }; 
  function sob ( unsigned char *srcBmp,int width,int height,int type )
 {
     frame(sob_i,sob_j,sob_l,sob_x,sob_y,sob_p1,sob_tempy,sob_tempx) and ( 
     int sob_i,sob_j,sob_l,sob_x,sob_y and skip;
     int sob_p1[4] and skip;
     memset(sob_p1,0,16) and skip;
     unsigned char *sob_tempy and skip;
     unsigned char *sob_tempx and skip;
	 //output("yubin141414\n") and skip;
     sob_tempx:=(unsigned char *)malloc(width*sizeof(unsigned char)*width);
     if(sob_tempx=NULL) then 
     {
         exit<==0 and skip 
     }
     else 
     {
          skip 
     };
	 //output("yubin151515\n") and skip;
     sob_tempy:=(unsigned char *)malloc(width*sizeof(unsigned char)*width);
     if(sob_tempy=NULL) then 
     {
         exit<==0 and skip 
     }
     else 
     {
          skip 
     };
     sob_i:=1;
     
     while(sob_i<height-1)
     {
         sob_j:=1;
         
         while(sob_j<width-1)
         {
             if(sob_i=height-1) then 
             {
                 sob_x:=0;sob_y:=0}
                 else
                 {
                     if(sob_j=width-1) then 
                     {
                         sob_x:=0;sob_y:=0}
                         else
                         {
                             sob_p1[0]:=(unsigned char)* (srcBmp+sob_i*width+sob_j);
                             sob_p1[1]:=(unsigned char)* (srcBmp+sob_i*width+sob_j+1);
                             sob_p1[2]:=(unsigned char)* (srcBmp+(sob_i+1)*width+sob_j);
                             sob_p1[3]:=(unsigned char)* (srcBmp+(sob_i+1)*width+sob_j+1);
                             sob_x:=abs(sob_p1[0]-sob_p1[2]);
                             sob_y:=abs(sob_p1[0]-sob_p1[1]);
                             if(sob_x>0) then 
                             {
                                 sob_x:=255
                             }
                             else
                             {
                                 sob_x:=0
                             };
                             if(sob_y>0) then 
                             {
                                 sob_y:=255
                             }
                             else
                             {
                                 sob_y:=0
                             }
                         }
                     };
                     sob_tempx[sob_i*width+sob_j]:=(unsigned char)sob_x;
                     sob_tempy[sob_i*width+sob_j]:=(unsigned char)sob_y;
                     sob_j:=sob_j+1
                     
                 };
                 sob_i:=sob_i+1
                 
             };
             sob_i:=0;
             
             while(sob_i<width)
             {
                 sob_tempx[sob_i]:=0;
                 sob_tempy[sob_i]:=0;
                 sob_tempx[width*(height-1)+sob_i]:=0;
                 sob_tempy[width*(height-1)+sob_i]:=0;
                 sob_i:=sob_i+1
                 
             };
             sob_i:=0;
             
             while(sob_i<height)
             {
                 sob_tempx[sob_i*width]:=0;
                 sob_tempy[sob_i*width]:=0;
                 sob_tempx[sob_i*width+width-1]:=0;
                 sob_tempy[sob_i*width+width-1]:=0;
                 sob_i:=sob_i+1
                 
             };
             if(type=0) then 
             {
                 memcpy(srcBmp,sob_tempx,1*width*height) and skip
             }
             else 
             {
                  skip 
             };
             if(type=1) then 
             {
                 memcpy(srcBmp,sob_tempy,1*width*height) and skip
             }
             else 
             {
                  skip 
             };
             if(type=2) then 
             {
                 sob_i:=0;
                 
                 while(sob_i<height)
                 {
                     sob_j:=0;
                     
                     while(sob_j<width)
                     {
                         sob_l:=sob_tempx[sob_i*width+sob_j]+sob_tempy[sob_i*height+sob_j];
                         if(sob_l>255) then 
                         {
                             sob_l:=255
                         }
                         else 
                         {
                              skip 
                         };
                         sob_tempx[sob_i*width+sob_j]:=sob_l;
                         sob_j:=sob_j+1
                         
                     };
                     sob_i:=sob_i+1
                     
                 };
                 memcpy(srcBmp,sob_tempx,1*width*height) and skip
                 
             }
             else 
             {
                  skip 
             };
             free(sob_tempx) and skip;
             free(sob_tempy) and skip;
             sob_tempx:=NULL;
             sob_tempy:=NULL
             )
             }; 
  function cuizhitouying ( Bmp1 *img,unsigned char *temp )
 {
     frame(cuizhitouying_p3,cuizhitouying_i,cuizhitouying_j,cuizhitouying_k,cuizhitouying_m,cuizhitouying_num,cuizhitouying_flag,cuizhitouying_up,cuizhitouying_down,cuizhitouying_p,break$,continue) and ( 
     int continue<==0 and skip;
     int break$<==0 and skip;
     int cuizhitouying_p3[15]<=={0} and skip;
     memset(cuizhitouying_p3,0,60) and skip;
     int cuizhitouying_i,cuizhitouying_j,cuizhitouying_k<==0,cuizhitouying_m,cuizhitouying_num,cuizhitouying_flag and skip;
     int cuizhitouying_up<==0 and skip;
     int cuizhitouying_down<==0 and skip;
     int cuizhitouying_p[500]<=={0} and skip;
     memset(cuizhitouying_p,0,2000) and skip;
     cuizhitouying_i:=0;

     while(cuizhitouying_i<img->width)
     {
         cuizhitouying_j:=0;
         
         while(cuizhitouying_j<img->height)
         {
             if(temp[cuizhitouying_j*img->width+cuizhitouying_i]=255) then 
             {
                 cuizhitouying_p[cuizhitouying_i]:=cuizhitouying_p[cuizhitouying_i]+1
                 
             }
             else 
             {
                  skip 
             };
             cuizhitouying_j:=cuizhitouying_j+1
             
         };
         cuizhitouying_i:=cuizhitouying_i+1
         
     };
     cuizhitouying_i:=1;
     
     while(cuizhitouying_i<img->width)
     {
         if(cuizhitouying_p[cuizhitouying_i]>0) then 
         {
             if((cuizhitouying_p[cuizhitouying_i-1]=0) AND (cuizhitouying_p[cuizhitouying_i+1]=0)) then 
             {
                 if(cuizhitouying_p[cuizhitouying_i]<5) then 
                 {
                     cuizhitouying_p[cuizhitouying_i]:=0
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
         cuizhitouying_i:=cuizhitouying_i+1
         
     };
     cuizhitouying_flag:=0;cuizhitouying_m:=0;break$<==0 and skip;
     cuizhitouying_i:=0;
     
     while( break$=0 AND  cuizhitouying_i<img->width)
     {
         if(cuizhitouying_p[cuizhitouying_i]>0) then 
         {
             cuizhitouying_flag:=1;
             cuizhitouying_m:=cuizhitouying_m+1
             
         }
         else 
         {
              skip 
         };
         if((cuizhitouying_p[cuizhitouying_i]=0) AND (cuizhitouying_flag=1)) then 
         {
             break$<==1 and skip
          }
         else 
         {
              skip 
         };
         if(break$=0)   then
         {
             cuizhitouying_i:=cuizhitouying_i+1
         }
         else
         {
             skip
         }
         
     };
     break$<==0 and skip;
     break$<==0 and skip;

     while( break$=0 AND  1)
     {
         cuizhitouying_num:=0;
         cuizhitouying_flag:=0;
         continue<==0 and skip;
         break$<==0 and skip;
         cuizhitouying_i:=0;
         while( break$=0 AND  cuizhitouying_i<img->width)
         {

              continue<==0 and skip;
             if(cuizhitouying_p[cuizhitouying_i]>1) then 
             {
                 if(cuizhitouying_flag=0) then 
                 {
                     img->p1[cuizhitouying_num]:=cuizhitouying_i;
                     cuizhitouying_flag:=1
                     
                 }
                 else 
                 {
                      skip 
                 }
                 
             }
             else
             {
                 if(cuizhitouying_p[cuizhitouying_i]=0) then 
                 {
                     if(cuizhitouying_flag=1) then 
                     {
                         img->p2[cuizhitouying_num]:=cuizhitouying_i-1;
                         cuizhitouying_flag:=0;
                         cuizhitouying_j:=img->p2[cuizhitouying_num]-img->p1[cuizhitouying_num];
                         if(cuizhitouying_j<cuizhitouying_m/ 3) then 
                         {
                             if(cuizhitouying_p[cuizhitouying_i-1]<(img->down-img->up)/ 2) then 
                             {
                                 continue<==1 and skip;
                                  cuizhitouying_i:=cuizhitouying_i+1}
                                 else 
                                 {
                                      skip 
                                 }
                                 
                             }
                             else 
                             {
                                  skip 
                             };
                             if(continue=0)  then
                             {
                                 cuizhitouying_num:=cuizhitouying_num+1
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
                 if(continue=0)  then 
                 {
                     if((cuizhitouying_flag=1) AND (cuizhitouying_i=img->width-1)) then 
                     {
                         img->p2[cuizhitouying_num]:=cuizhitouying_i;
                         cuizhitouying_num:=cuizhitouying_num+1;
                         break$<==1 and skip
                          
                     }
                     else 
                     {
                          skip 
                     };
                     if(break$=0)   then
                     {
                         cuizhitouying_i:=cuizhitouying_i+1
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
             continue<==0 and skip;
             if(cuizhitouying_num=7) then 
             {
                 break$<==1 and skip
              }
             else
             {
                 if(cuizhitouying_num=8) then 
                 {
                     cuizhitouying_j:=100;
                     cuizhitouying_i:=0;
                     
                     while(cuizhitouying_i<cuizhitouying_num)
                     {
                         cuizhitouying_p3[cuizhitouying_i]:=img->p2[cuizhitouying_i]-img->p1[cuizhitouying_i];
                         if(cuizhitouying_p3[cuizhitouying_i]<cuizhitouying_j) then 
                         {
                             cuizhitouying_j:=cuizhitouying_p3[cuizhitouying_i];
                             cuizhitouying_k:=cuizhitouying_i
                             
                         }
                         else 
                         {
                              skip 
                         };
                         cuizhitouying_i:=cuizhitouying_i+1
                         
                     };
                     cuizhitouying_i:=cuizhitouying_k;
                     
                     while(cuizhitouying_i<=cuizhitouying_num-cuizhitouying_k)
                     {
                         img->p1[cuizhitouying_i]:=img->p1[cuizhitouying_i+1];
                         img->p2[cuizhitouying_i]:=img->p2[cuizhitouying_i+1];
                         cuizhitouying_i:=cuizhitouying_i+1
                         
                     };
                     cuizhitouying_num:=cuizhitouying_num-1;
                     break$<==1 and skip
                  }
                 else
                 {
                     cuizhitouying_i:=0;
                     
                     while(cuizhitouying_i<img->width)
                     {
                         if(cuizhitouying_p[cuizhitouying_i]>0) then 
                         {
                             cuizhitouying_p[cuizhitouying_i]:=cuizhitouying_p[cuizhitouying_i]-1
                         }
                         else 
                         {
                              skip 
                         };
                         cuizhitouying_i:=cuizhitouying_i+1
                         
                     }
                 }
             }
         };

         break$<==0 and skip;
         cuizhitouying_flag:=0;
         cuizhitouying_up:=0;
         cuizhitouying_down:=0;
         cuizhitouying_up:=img->up-3;
         if(cuizhitouying_up<0) then 
         {
             cuizhitouying_up:=img->up
         }
         else 
         {
              skip 
         };
         cuizhitouying_down:=img->down+4;
         if(cuizhitouying_down>img->height) then 
         {
             cuizhitouying_down:=img->down
         }
         else 
         {
              skip 
         };
         cuizhitouying_k:=0;
         
         while(cuizhitouying_k<7)
         {
             break$<==0 and skip;
             cuizhitouying_i:=cuizhitouying_up;
             
             while( break$=0 AND  cuizhitouying_i<=cuizhitouying_down)
             {
                 break$<==0 and skip;
                 cuizhitouying_j:=img->p1[cuizhitouying_k];
                 
                 while( break$=0 AND  cuizhitouying_j<=img->p2[cuizhitouying_k])
                 {
                     if(temp[cuizhitouying_i*img->width+cuizhitouying_j]=255) then 
                     {
                         img->p3[cuizhitouying_k]:=cuizhitouying_i;
                         cuizhitouying_flag:=1;
                         break$<==1 and skip
                          
                     }
                     else 
                     {
                          skip 
                     };
                     if(break$=0)   then
                     {
                         cuizhitouying_j:=cuizhitouying_j+1
                     }
                     else
                     {
                         skip
                     }
                     
                 };
                 break$<==0 and skip;
                 if(cuizhitouying_flag=1) then 
                 {
                     cuizhitouying_flag:=0;
                     break$<==1 and skip
                      
                 }
                 else 
                 {
                      skip 
                 };
                 if(break$=0)   then
                 {
                     cuizhitouying_i:=cuizhitouying_i+1
                 }
                 else
                 {
                     skip
                 }
                 
             };
             break$<==0 and skip;
             break$<==0 and skip;
             cuizhitouying_i:=cuizhitouying_down;
             
             while( break$=0 AND  cuizhitouying_i>=cuizhitouying_up)
             {
                 break$<==0 and skip;
                 cuizhitouying_j:=img->p1[cuizhitouying_k];
                 
                 while( break$=0 AND  cuizhitouying_j<=img->p2[cuizhitouying_k])
                 {
                     if(temp[cuizhitouying_i*img->width+cuizhitouying_j]=255) then 
                     {
                         img->p4[cuizhitouying_k]:=cuizhitouying_i;
                         cuizhitouying_flag:=1;
                         break$<==1 and skip
                          
                     }
                     else 
                     {
                          skip 
                     };
                     if(break$=0)   then
                     {
                         cuizhitouying_j:=cuizhitouying_j+1
                     }
                     else
                     {
                         skip
                     }
                     
                 };
                 break$<==0 and skip;
                 if(cuizhitouying_flag=1) then 
                 {
                     cuizhitouying_flag:=0;
                     break$<==1 and skip
                      
                 }
                 else 
                 {
                      skip 
                 };
                 if(break$=0)   then
                 {
                     cuizhitouying_i:=cuizhitouying_i-1
                 }
                 else
                 {
                     skip
                 }
                 
             };
             break$<==0 and skip;
             cuizhitouying_k:=cuizhitouying_k+1
             
         }
         )
         }; 
  function junheng ( BMP_img img,unsigned char *srcBmp,unsigned char *dstBmp )
 {
     frame(junheng_n,junheng_p,junheng_c,junheng_height,junheng_width,junheng_totalPixels,junheng_i,junheng_j,junheng_max,junheng_min,junheng_l) and ( 
     int junheng_n[256]<=={0} and skip;
     memset(junheng_n,0,256*4) and skip;
     float junheng_p[256]<=={0} and skip;
     memset(junheng_p,0,256*4) and skip;
     float junheng_c[256]<=={0} and skip;
     memset(junheng_c,0,256*4) and skip;
     int junheng_height<==img.height and skip;
     int junheng_width<==img.width and skip;
     int junheng_totalPixels<==junheng_width*junheng_height and skip;
     int junheng_i,junheng_j,junheng_max,junheng_min,junheng_l and skip;
     junheng_i:=0;
     
     while(junheng_i<img.height)
     {
         junheng_j:=0 ; junheng_l:=0;
         while(junheng_j<img.width)
         {
             srcBmp[junheng_i*img.width+junheng_j]:=* (srcBmp+junheng_i*img.lineBytes+junheng_l);
             junheng_l:=junheng_l+3 ; junheng_j:=junheng_j+1
             
         };
         junheng_i:=junheng_i+1
         
     };
     junheng_i:=0;
     
     while(junheng_i<img.height)
     {
         junheng_j:=0;
         
         while(junheng_j<img.width)
         {
             junheng_n[srcBmp[junheng_i*junheng_width+junheng_j]]:=junheng_n[srcBmp[junheng_i*junheng_width+junheng_j]]+1;
             junheng_j:=junheng_j+1
             
         };
         junheng_i:=junheng_i+1
         
     };
     junheng_i:=0;
     
     while(junheng_i<256)
     {
         junheng_p[junheng_i]:=junheng_n[junheng_i]*1.0/ junheng_totalPixels;
         junheng_i:=junheng_i+1
         
     };
     junheng_i:=0;
     
     while(junheng_i<256)
     {
         junheng_j:=0;
         
         while(junheng_j<=junheng_i)
         {
             junheng_c[junheng_i]:=junheng_c[junheng_i]+junheng_p[junheng_j];
             junheng_j:=junheng_j+1
             
         };
         junheng_i:=junheng_i+1
         
     };
     junheng_min<==srcBmp[0] and junheng_max<==junheng_min and skip;
     junheng_i:=0;
     
     while(junheng_i<img.height)
     {
         junheng_j:=0;
         
         while(junheng_j<img.width)
         {
             junheng_n[srcBmp[junheng_i*junheng_width+junheng_j]]:=junheng_n[srcBmp[junheng_i*junheng_width+junheng_j]]+1;
             junheng_j:=junheng_j+1
             
         };
         junheng_i:=junheng_i+1
         
     };
     junheng_i:=0;
     
     while(junheng_i<junheng_height)
     {
         junheng_j:=0;
         
         while(junheng_j<junheng_width)
         {
             if(junheng_max<srcBmp[junheng_i*junheng_width+junheng_j]) then 
             {
                 junheng_max:=srcBmp[junheng_i*junheng_width+junheng_j]
                 
             }
             else
             {
                 if(junheng_min>srcBmp[junheng_i*junheng_width+junheng_j]) then 
                 {
                     junheng_min:=srcBmp[junheng_i*junheng_width+junheng_j]
                     
                 }
                 else 
                 {
                      skip 
                 }
             };
             junheng_j:=junheng_j+1
             
         };
         junheng_i:=junheng_i+1
         
     };
     junheng_i:=0;
     
     while(junheng_i<junheng_height)
     {
         junheng_j:=0;
         
         while(junheng_j<junheng_width)
         {
             dstBmp[junheng_i*img.lineBytes+junheng_j*3]:=(unsigned char)(junheng_c[srcBmp[junheng_i*junheng_width+junheng_j]]*(junheng_max-junheng_min)+junheng_min+0.5);
             dstBmp[junheng_i*img.lineBytes+junheng_j*3+1]:=(unsigned char)(junheng_c[srcBmp[junheng_i*junheng_width+junheng_j]]*(junheng_max-junheng_min)+junheng_min+0.5);
             dstBmp[junheng_i*img.lineBytes+junheng_j*3+2]:=(unsigned char)(junheng_c[srcBmp[junheng_i*junheng_width+junheng_j]]*(junheng_max-junheng_min)+junheng_min+0.5);
             junheng_j:=junheng_j+1
             
         };
         junheng_i:=junheng_i+1
         
     }
     )
     }; 
  function CutBmp ( BMP_img img,Bmp1 *img1,int HL,int HH,int VL,int VH )
 {
     frame(CutBmp_i,CutBmp_j,CutBmp_n,CutBmp_x,CutBmp_y) and ( 
     int CutBmp_i,CutBmp_j,CutBmp_n and skip;
     int CutBmp_x<==0,CutBmp_y<==0 and skip;
     img1->width:=VH-VL;
     img1->height:=HH-HL;
	 //output("yubin161616\n") and skip;
     //img1->image:=myMalloc(img1->height*img1->width*3,0,0,RValue);
	 img1->image:=(unsigned char *)malloc(img1->height*img1->width*3*sizeof(unsigned char));

     CutBmp_x:=0 ; CutBmp_i:=HL;
     while(CutBmp_i<HH)
     {
         CutBmp_y:=0 ; CutBmp_n:=0 ; CutBmp_j:=VL*3;
         while(CutBmp_j<VH*3)
         {
             img1->image[CutBmp_x*img1->width*3+CutBmp_y]:=img.image[CutBmp_i*img.width*3+CutBmp_j];
             img1->image[CutBmp_x*img1->width*3+CutBmp_y+1]:=img.image[CutBmp_i*img.width*3+CutBmp_j+1];
             img1->image[CutBmp_x*img1->width*3+CutBmp_y+2]:=img.image[CutBmp_i*img.width*3+CutBmp_j+2];
             CutBmp_n:=CutBmp_n+1 ; CutBmp_j:=CutBmp_j+3 ; CutBmp_y:=CutBmp_y+3
             
         };
         CutBmp_x:=CutBmp_x+1 ; CutBmp_i:=CutBmp_i+1
         
     }
     )
     }; 
  function CutBmp1 ( Bmp1 *img1,int HL,int HH,int VL,int VH )
 {
     frame(CutBmp1_i,CutBmp1_j,CutBmp1_n,CutBmp1_x,CutBmp1_y,CutBmp1_width,CutBmp1_height) and ( 
     int CutBmp1_i,CutBmp1_j,CutBmp1_n and skip;
     int CutBmp1_x<==0,CutBmp1_y<==0 and skip;
     int CutBmp1_width,CutBmp1_height and skip;
     CutBmp1_width:=img1->width;
     CutBmp1_height:=img1->height;
     img1->width:=VH-VL;
     img1->height:=HH-HL;
     CutBmp1_x:=0 ; CutBmp1_i:=HL;
     while(CutBmp1_i<HH)
     {
         CutBmp1_y:=0 ; CutBmp1_n:=0 ; CutBmp1_j:=VL*3;
         while(CutBmp1_j<VH*3)
         {
             img1->image[CutBmp1_x*img1->width*3+CutBmp1_y]:=img1->image[CutBmp1_i*CutBmp1_width*3+CutBmp1_j];
             img1->image[CutBmp1_x*img1->width*3+CutBmp1_y+1]:=img1->image[CutBmp1_i*CutBmp1_width*3+CutBmp1_j+1];
             img1->image[CutBmp1_x*img1->width*3+CutBmp1_y+2]:=img1->image[CutBmp1_i*CutBmp1_width*3+CutBmp1_j+2];
             CutBmp1_n:=CutBmp1_n+1 ; CutBmp1_j:=CutBmp1_j+3 ; CutBmp1_y:=CutBmp1_y+3
             
         };
         CutBmp1_x:=CutBmp1_x+1 ; CutBmp1_i:=CutBmp1_i+1
         
     }
     )
     }; 
  function ThinnerRosenfeld ( void *image,unsigned int lx,unsigned int ly )
 {
     frame(ThinnerRosenfeld_f,ThinnerRosenfeld_g,ThinnerRosenfeld_n,ThinnerRosenfeld_a,ThinnerRosenfeld_b,ThinnerRosenfeld_nrnd,ThinnerRosenfeld_cond,ThinnerRosenfeld_n48,ThinnerRosenfeld_n26,ThinnerRosenfeld_n24,ThinnerRosenfeld_n46,ThinnerRosenfeld_n68,ThinnerRosenfeld_n82,ThinnerRosenfeld_n123,ThinnerRosenfeld_n345,ThinnerRosenfeld_n567,ThinnerRosenfeld_n781,ThinnerRosenfeld_k,ThinnerRosenfeld_shori,ThinnerRosenfeld_i,ThinnerRosenfeld_j,ThinnerRosenfeld_ii,ThinnerRosenfeld_jj,ThinnerRosenfeld_kk,ThinnerRosenfeld_kk1,ThinnerRosenfeld_kk2,ThinnerRosenfeld_kk3,ThinnerRosenfeld_size,count$,return,continue) and ( 
     int continue<==0 and skip;
     int return<==0 and skip;
     char *ThinnerRosenfeld_f,*ThinnerRosenfeld_g and skip;
     char ThinnerRosenfeld_n[10] and skip;
     char ThinnerRosenfeld_a[5]<=={0,-1,1,0,0} and skip;
     char ThinnerRosenfeld_b[5]<=={0,0,0,1,-1} and skip;
     char ThinnerRosenfeld_nrnd,ThinnerRosenfeld_cond,ThinnerRosenfeld_n48,ThinnerRosenfeld_n26,ThinnerRosenfeld_n24,ThinnerRosenfeld_n46,ThinnerRosenfeld_n68,ThinnerRosenfeld_n82,ThinnerRosenfeld_n123,ThinnerRosenfeld_n345,ThinnerRosenfeld_n567,ThinnerRosenfeld_n781 and skip;
     int ThinnerRosenfeld_k,ThinnerRosenfeld_shori and skip;
     int ThinnerRosenfeld_i,ThinnerRosenfeld_j and skip;
     int ThinnerRosenfeld_ii,ThinnerRosenfeld_jj,ThinnerRosenfeld_kk,ThinnerRosenfeld_kk1,ThinnerRosenfeld_kk2,ThinnerRosenfeld_kk3,ThinnerRosenfeld_size and skip;
     ThinnerRosenfeld_size:=(int)lx*(int)ly;
	 //output("yubin171717\n") and skip;
     ThinnerRosenfeld_g:=(char *)malloc(ThinnerRosenfeld_size);
     if(ThinnerRosenfeld_g=NULL) then 
     {
         output ("error in alocating mmeory!\n") and skip;
          return<==1 and skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         ThinnerRosenfeld_f:=(char *)image;
         ThinnerRosenfeld_kk:=0;
         
         while(ThinnerRosenfeld_kk<ThinnerRosenfeld_size)
         {
             ThinnerRosenfeld_g[ThinnerRosenfeld_kk]:=ThinnerRosenfeld_f[ThinnerRosenfeld_kk];
             ThinnerRosenfeld_kk:=ThinnerRosenfeld_kk+1
             
         };
         int count$<==0 and skip;
         while( ( count$=0 OR ThinnerRosenfeld_shori))
         {
             count$:=count$+1;
             ThinnerRosenfeld_shori:=0;
             ThinnerRosenfeld_k:=1;
             
             while(ThinnerRosenfeld_k<=4)
             {
                 ThinnerRosenfeld_i:=1;
                 
                 while(ThinnerRosenfeld_i<lx-1)
                 {
                     ThinnerRosenfeld_ii:=ThinnerRosenfeld_i+ThinnerRosenfeld_a[ThinnerRosenfeld_k];
                     continue<==0 and skip;
                     ThinnerRosenfeld_j:=1;
                     
                     while(ThinnerRosenfeld_j<ly-1)
                     {
                          continue<==0 and skip;
                         ThinnerRosenfeld_kk:=ThinnerRosenfeld_i*ly+ThinnerRosenfeld_j;
                         if(!ThinnerRosenfeld_f[ThinnerRosenfeld_kk]) then 
                         {
                             continue<==1 and skip;
                              ThinnerRosenfeld_j:=ThinnerRosenfeld_j+1}
                             else 
                             {
                                  skip 
                             };
                             if(continue=0)   then 
                             {
                                 ThinnerRosenfeld_jj:=ThinnerRosenfeld_j+ThinnerRosenfeld_b[ThinnerRosenfeld_k];
                                 ThinnerRosenfeld_kk1:=ThinnerRosenfeld_ii*ly+ThinnerRosenfeld_jj;
                                 if(ThinnerRosenfeld_f[ThinnerRosenfeld_kk1]) then 
                                 {
                                     continue<==1 and skip;
                                      ThinnerRosenfeld_j:=ThinnerRosenfeld_j+1}
                                     else 
                                     {
                                          skip 
                                     };
                                     if(continue=0)   then 
                                     {
                                         ThinnerRosenfeld_kk1:=ThinnerRosenfeld_kk-ly-1;
                                         ThinnerRosenfeld_kk2:=ThinnerRosenfeld_kk1+1;
                                         ThinnerRosenfeld_kk3:=ThinnerRosenfeld_kk2+1;
                                         ThinnerRosenfeld_n[3]:=ThinnerRosenfeld_f[ThinnerRosenfeld_kk1];
                                         ThinnerRosenfeld_n[2]:=ThinnerRosenfeld_f[ThinnerRosenfeld_kk2];
                                         ThinnerRosenfeld_n[1]:=ThinnerRosenfeld_f[ThinnerRosenfeld_kk3];
                                         ThinnerRosenfeld_kk1:=ThinnerRosenfeld_kk-1;
                                         ThinnerRosenfeld_kk3:=ThinnerRosenfeld_kk+1;
                                         ThinnerRosenfeld_n[4]:=ThinnerRosenfeld_f[ThinnerRosenfeld_kk1];
                                         ThinnerRosenfeld_n[8]:=ThinnerRosenfeld_f[ThinnerRosenfeld_kk3];
                                         ThinnerRosenfeld_kk1:=ThinnerRosenfeld_kk+ly-1;
                                         ThinnerRosenfeld_kk2:=ThinnerRosenfeld_kk1+1;
                                         ThinnerRosenfeld_kk3:=ThinnerRosenfeld_kk2+1;
                                         ThinnerRosenfeld_n[5]:=ThinnerRosenfeld_f[ThinnerRosenfeld_kk1];
                                         ThinnerRosenfeld_n[6]:=ThinnerRosenfeld_f[ThinnerRosenfeld_kk2];
                                         ThinnerRosenfeld_n[7]:=ThinnerRosenfeld_f[ThinnerRosenfeld_kk3];
                                         ThinnerRosenfeld_nrnd:=ThinnerRosenfeld_n[1]+ThinnerRosenfeld_n[2]+ThinnerRosenfeld_n[3]+ThinnerRosenfeld_n[4]+ThinnerRosenfeld_n[5]+ThinnerRosenfeld_n[6]+ThinnerRosenfeld_n[7]+ThinnerRosenfeld_n[8];
                                         if(ThinnerRosenfeld_nrnd<=1) then 
                                         {
                                             continue<==1 and skip;
                                              ThinnerRosenfeld_j:=ThinnerRosenfeld_j+1}
                                             else 
                                             {
                                                  skip 
                                             };
                                             if(continue=0)   then 
                                             {
                                                 ThinnerRosenfeld_cond:=0;
                                                 ThinnerRosenfeld_n48:=ThinnerRosenfeld_n[4]+ThinnerRosenfeld_n[8];
                                                 ThinnerRosenfeld_n26:=ThinnerRosenfeld_n[2]+ThinnerRosenfeld_n[6];
                                                 ThinnerRosenfeld_n24:=ThinnerRosenfeld_n[2]+ThinnerRosenfeld_n[4];
                                                 ThinnerRosenfeld_n46:=ThinnerRosenfeld_n[4]+ThinnerRosenfeld_n[6];
                                                 ThinnerRosenfeld_n68:=ThinnerRosenfeld_n[6]+ThinnerRosenfeld_n[8];
                                                 ThinnerRosenfeld_n82:=ThinnerRosenfeld_n[8]+ThinnerRosenfeld_n[2];
                                                 ThinnerRosenfeld_n123:=ThinnerRosenfeld_n[1]+ThinnerRosenfeld_n[2]+ThinnerRosenfeld_n[3];
                                                 ThinnerRosenfeld_n345:=ThinnerRosenfeld_n[3]+ThinnerRosenfeld_n[4]+ThinnerRosenfeld_n[5];
                                                 ThinnerRosenfeld_n567:=ThinnerRosenfeld_n[5]+ThinnerRosenfeld_n[6]+ThinnerRosenfeld_n[7];
                                                 ThinnerRosenfeld_n781:=ThinnerRosenfeld_n[7]+ThinnerRosenfeld_n[8]+ThinnerRosenfeld_n[1];
                                                 if(ThinnerRosenfeld_n[2]=1 AND ThinnerRosenfeld_n48=0 AND ThinnerRosenfeld_n567>0) then 
                                                 {
                                                     if(!ThinnerRosenfeld_cond) then 
                                                     {
                                                         continue<==1 and skip;
                                                          ThinnerRosenfeld_j:=ThinnerRosenfeld_j+1}
                                                         else 
                                                         {
                                                              skip 
                                                         };
                                                         if(continue=0)   then 
                                                         {
                                                             ThinnerRosenfeld_g[ThinnerRosenfeld_kk]:=0;
                                                             ThinnerRosenfeld_shori:=1;
                                                             continue<==1 and skip;
                                                              ThinnerRosenfeld_j:=ThinnerRosenfeld_j+1}
                                                             else
                                                             {
                                                                 skip
                                                             }
                                                             
                                                         }
                                                         else 
                                                         {
                                                              skip 
                                                         };
                                                         if(continue=0)  then
                                                         {
                                                             if(continue=0)   then 
                                                             {
                                                                 if(ThinnerRosenfeld_n[6]=1 AND ThinnerRosenfeld_n48=0 AND ThinnerRosenfeld_n123>0) then 
                                                                 {
                                                                     if(!ThinnerRosenfeld_cond) then 
                                                                     {
                                                                         continue<==1 and skip;
                                                                          ThinnerRosenfeld_j:=ThinnerRosenfeld_j+1}
                                                                         else 
                                                                         {
                                                                              skip 
                                                                         };
                                                                         if(continue=0)   then 
                                                                         {
                                                                             ThinnerRosenfeld_g[ThinnerRosenfeld_kk]:=0;
                                                                             ThinnerRosenfeld_shori:=1;
                                                                             continue<==1 and skip;
                                                                              ThinnerRosenfeld_j:=ThinnerRosenfeld_j+1}
                                                                             else
                                                                             {
                                                                                 skip
                                                                             }
                                                                             
                                                                         }
                                                                         else 
                                                                         {
                                                                              skip 
                                                                         };
                                                                         if(continue=0)  then
                                                                         {
                                                                             if(continue=0)   then 
                                                                             {
                                                                                 if(ThinnerRosenfeld_n[8]=1 AND ThinnerRosenfeld_n26=0 AND ThinnerRosenfeld_n345>0) then 
                                                                                 {
                                                                                     if(!ThinnerRosenfeld_cond) then 
                                                                                     {
                                                                                         continue<==1 and skip;
                                                                                          ThinnerRosenfeld_j:=ThinnerRosenfeld_j+1}
                                                                                         else 
                                                                                         {
                                                                                              skip 
                                                                                         };
                                                                                         if(continue=0)   then 
                                                                                         {
                                                                                             ThinnerRosenfeld_g[ThinnerRosenfeld_kk]:=0;
                                                                                             ThinnerRosenfeld_shori:=1;
                                                                                             continue<==1 and skip;
                                                                                              ThinnerRosenfeld_j:=ThinnerRosenfeld_j+1}
                                                                                             else
                                                                                             {
                                                                                                 skip
                                                                                             }
                                                                                             
                                                                                         }
                                                                                         else 
                                                                                         {
                                                                                              skip 
                                                                                         };
                                                                                         if(continue=0)  then
                                                                                         {
                                                                                             if(continue=0)   then 
                                                                                             {
                                                                                                 if(ThinnerRosenfeld_n[4]=1 AND ThinnerRosenfeld_n26=0 AND ThinnerRosenfeld_n781>0) then 
                                                                                                 {
                                                                                                     if(!ThinnerRosenfeld_cond) then 
                                                                                                     {
                                                                                                         continue<==1 and skip;
                                                                                                          ThinnerRosenfeld_j:=ThinnerRosenfeld_j+1}
                                                                                                         else 
                                                                                                         {
                                                                                                              skip 
                                                                                                         };
                                                                                                         if(continue=0)   then 
                                                                                                         {
                                                                                                             ThinnerRosenfeld_g[ThinnerRosenfeld_kk]:=0;
                                                                                                             ThinnerRosenfeld_shori:=1;
                                                                                                             continue<==1 and skip;
                                                                                                              ThinnerRosenfeld_j:=ThinnerRosenfeld_j+1}
                                                                                                             else
                                                                                                             {
                                                                                                                 skip
                                                                                                             }
                                                                                                             
                                                                                                         }
                                                                                                         else 
                                                                                                         {
                                                                                                              skip 
                                                                                                         };
                                                                                                         if(continue=0)  then
                                                                                                         {
                                                                                                             if(continue=0)   then 
                                                                                                             {
                                                                                                                 if(ThinnerRosenfeld_n[5]=1 AND ThinnerRosenfeld_n46=0) then 
                                                                                                                 {
                                                                                                                     if(!ThinnerRosenfeld_cond) then 
                                                                                                                     {
                                                                                                                         continue<==1 and skip;
                                                                                                                          ThinnerRosenfeld_j:=ThinnerRosenfeld_j+1}
                                                                                                                         else 
                                                                                                                         {
                                                                                                                              skip 
                                                                                                                         };
                                                                                                                         if(continue=0)   then 
                                                                                                                         {
                                                                                                                             ThinnerRosenfeld_g[ThinnerRosenfeld_kk]:=0;
                                                                                                                             ThinnerRosenfeld_shori:=1;
                                                                                                                             continue<==1 and skip;
                                                                                                                              ThinnerRosenfeld_j:=ThinnerRosenfeld_j+1}
                                                                                                                             else
                                                                                                                             {
                                                                                                                                 skip
                                                                                                                             }
                                                                                                                             
                                                                                                                         }
                                                                                                                         else 
                                                                                                                         {
                                                                                                                              skip 
                                                                                                                         };
                                                                                                                         if(continue=0)  then
                                                                                                                         {
                                                                                                                             if(continue=0)   then 
                                                                                                                             {
                                                                                                                                 if(ThinnerRosenfeld_n[7]=1 AND ThinnerRosenfeld_n68=0) then 
                                                                                                                                 {
                                                                                                                                     if(!ThinnerRosenfeld_cond) then 
                                                                                                                                     {
                                                                                                                                         continue<==1 and skip;
                                                                                                                                          ThinnerRosenfeld_j:=ThinnerRosenfeld_j+1}
                                                                                                                                         else 
                                                                                                                                         {
                                                                                                                                              skip 
                                                                                                                                         };
                                                                                                                                         if(continue=0)   then 
                                                                                                                                         {
                                                                                                                                             ThinnerRosenfeld_g[ThinnerRosenfeld_kk]:=0;
                                                                                                                                             ThinnerRosenfeld_shori:=1;
                                                                                                                                             continue<==1 and skip;
                                                                                                                                              ThinnerRosenfeld_j:=ThinnerRosenfeld_j+1}
                                                                                                                                             else
                                                                                                                                             {
                                                                                                                                                 skip
                                                                                                                                             }
                                                                                                                                             
                                                                                                                                         }
                                                                                                                                         else 
                                                                                                                                         {
                                                                                                                                              skip 
                                                                                                                                         };
                                                                                                                                         if(continue=0)  then
                                                                                                                                         {
                                                                                                                                             if(continue=0)   then 
                                                                                                                                             {
                                                                                                                                                 if(ThinnerRosenfeld_n[1]=1 AND ThinnerRosenfeld_n82=0) then 
                                                                                                                                                 {
                                                                                                                                                     if(!ThinnerRosenfeld_cond) then 
                                                                                                                                                     {
                                                                                                                                                         continue<==1 and skip;
                                                                                                                                                          ThinnerRosenfeld_j:=ThinnerRosenfeld_j+1}
                                                                                                                                                         else 
                                                                                                                                                         {
                                                                                                                                                              skip 
                                                                                                                                                         };
                                                                                                                                                         if(continue=0)   then 
                                                                                                                                                         {
                                                                                                                                                             ThinnerRosenfeld_g[ThinnerRosenfeld_kk]:=0;
                                                                                                                                                             ThinnerRosenfeld_shori:=1;
                                                                                                                                                             continue<==1 and skip;
                                                                                                                                                              ThinnerRosenfeld_j:=ThinnerRosenfeld_j+1}
                                                                                                                                                             else
                                                                                                                                                             {
                                                                                                                                                                 skip
                                                                                                                                                             }
                                                                                                                                                             
                                                                                                                                                         }
                                                                                                                                                         else 
                                                                                                                                                         {
                                                                                                                                                              skip 
                                                                                                                                                         };
                                                                                                                                                         if(continue=0)  then
                                                                                                                                                         {
                                                                                                                                                             if(continue=0)   then 
                                                                                                                                                             {
                                                                                                                                                                 if(ThinnerRosenfeld_n[3]=1 AND ThinnerRosenfeld_n24=0) then 
                                                                                                                                                                 {
                                                                                                                                                                     if(!ThinnerRosenfeld_cond) then 
                                                                                                                                                                     {
                                                                                                                                                                         continue<==1 and skip;
                                                                                                                                                                          ThinnerRosenfeld_j:=ThinnerRosenfeld_j+1}
                                                                                                                                                                         else 
                                                                                                                                                                         {
                                                                                                                                                                              skip 
                                                                                                                                                                         };
                                                                                                                                                                         if(continue=0)   then 
                                                                                                                                                                         {
                                                                                                                                                                             ThinnerRosenfeld_g[ThinnerRosenfeld_kk]:=0;
                                                                                                                                                                             ThinnerRosenfeld_shori:=1;
                                                                                                                                                                             continue<==1 and skip;
                                                                                                                                                                              ThinnerRosenfeld_j:=ThinnerRosenfeld_j+1}
                                                                                                                                                                             else
                                                                                                                                                                             {
                                                                                                                                                                                 skip
                                                                                                                                                                             }
                                                                                                                                                                             
                                                                                                                                                                         }
                                                                                                                                                                         else 
                                                                                                                                                                         {
                                                                                                                                                                              skip 
                                                                                                                                                                         };
                                                                                                                                                                         if(continue=0)  then
                                                                                                                                                                         {
                                                                                                                                                                             if(continue=0)   then 
                                                                                                                                                                             {
                                                                                                                                                                                 ThinnerRosenfeld_cond:=1;
                                                                                                                                                                                 if(!ThinnerRosenfeld_cond) then 
                                                                                                                                                                                 {
                                                                                                                                                                                     continue<==1 and skip;
                                                                                                                                                                                      ThinnerRosenfeld_j:=ThinnerRosenfeld_j+1}
                                                                                                                                                                                     else 
                                                                                                                                                                                     {
                                                                                                                                                                                          skip 
                                                                                                                                                                                     };
                                                                                                                                                                                     if(continue=0)   then 
                                                                                                                                                                                     {
                                                                                                                                                                                         ThinnerRosenfeld_g[ThinnerRosenfeld_kk]:=0;
                                                                                                                                                                                         ThinnerRosenfeld_shori:=1;
                                                                                                                                                                                         ThinnerRosenfeld_j:=ThinnerRosenfeld_j+1
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
                                                                                                         
                                                                                                     };
                                                                                                     continue<==0 and skip;
                                                                                                     ThinnerRosenfeld_i:=ThinnerRosenfeld_i+1
                                                                                                     
                                                                                                 };
                                                                                                 ThinnerRosenfeld_i:=0;
                                                                                                 
                                                                                                 while(ThinnerRosenfeld_i<lx)
                                                                                                 {
                                                                                                     ThinnerRosenfeld_j:=0;
                                                                                                     
                                                                                                     while(ThinnerRosenfeld_j<ly)
                                                                                                     {
                                                                                                         ThinnerRosenfeld_kk:=ThinnerRosenfeld_i*ly+ThinnerRosenfeld_j;
                                                                                                         ThinnerRosenfeld_f[ThinnerRosenfeld_kk]:=ThinnerRosenfeld_g[ThinnerRosenfeld_kk];
                                                                                                         ThinnerRosenfeld_j:=ThinnerRosenfeld_j+1
                                                                                                         
                                                                                                     };
                                                                                                     ThinnerRosenfeld_i:=ThinnerRosenfeld_i+1
                                                                                                     
                                                                                                 };
                                                                                                 ThinnerRosenfeld_k:=ThinnerRosenfeld_k+1
                                                                                                 
                                                                                             }
                                                                                         };
                                                                                         free(ThinnerRosenfeld_g) and skip
                                                                                     }
                                                                                     else
                                                                                     {
                                                                                         skip
                                                                                     }
                                                                                     )
                                                                                     }; 
  function Thining ( unsigned char *srcBmp,int width,int height )
 {
     frame(Thining_i,Thining_j,Thining_lWidth,Thining_lHeight,Thining_image) and ( 
     int Thining_i,Thining_j and skip;
     int Thining_lWidth<==width,Thining_lHeight<==height and skip;
     unsigned char *Thining_image and skip;
	 //output("yubin181818\n") and skip;
     Thining_image:=(unsigned char *)malloc(Thining_lWidth*Thining_lHeight*sizeof(unsigned char));
     Thining_i:=0;
     
     while(Thining_i<Thining_lHeight)
     {
         Thining_j:=0;
         
         while(Thining_j<Thining_lWidth)
         {
             if(srcBmp[Thining_i*width+Thining_j]=0) then 
             {
                 Thining_image[Thining_i*Thining_lWidth+Thining_j]:=0
             }
             else
             {
                 Thining_image[Thining_i*Thining_lWidth+Thining_j]:=1
             };
             Thining_j:=Thining_j+1
             
         };
         Thining_i:=Thining_i+1
         
     };
     ThinnerRosenfeld(Thining_image,height,width);
     Thining_i:=0;
     
     while(Thining_i<Thining_lHeight)
     {
         Thining_j:=0;
         
         while(Thining_j<Thining_lWidth)
         {
             if(Thining_image[Thining_i*Thining_lWidth+Thining_j]=1) then 
             {
                 srcBmp[Thining_i*width+Thining_j]:=(unsigned char)255
             }
             else
             {
                 srcBmp[Thining_i*width+Thining_j]:=(unsigned char)0
             };
             Thining_j:=Thining_j+1
             
         };
         Thining_i:=Thining_i+1
         
     }
     )
     }; 
  function Thiningtest ( BMP_img img,unsigned char *srcBmp,unsigned char *dstBmp )
 {
     frame(Thiningtest_i,Thiningtest_j,Thiningtest_n,Thiningtest_lWidth,Thiningtest_lHeight,Thiningtest_image,Thiningtest_lineBytes,Thiningtest_gray) and ( 
     int Thiningtest_i,Thiningtest_j,Thiningtest_n and skip;
     int Thiningtest_lWidth<==img.width,Thiningtest_lHeight<==img.height and skip;
     unsigned char *Thiningtest_image and skip;
	 //output("yubin191919\n") and skip;
     Thiningtest_image:=(unsigned char *)malloc(Thiningtest_lWidth*Thiningtest_lHeight*sizeof(unsigned char));
     int Thiningtest_lineBytes<==(img.width*24+31)/ 32*4 and skip;
     float Thiningtest_gray and skip;
     Thiningtest_i:=0;
     
     while(Thiningtest_i<img.height)
     {
         Thiningtest_j:=0 ; Thiningtest_n:=0;
         while(Thiningtest_j<img.width)
         {
             Thiningtest_gray:=0.299*(float)(img.image[Thiningtest_lineBytes*Thiningtest_i+Thiningtest_n+2])+0.578*(float)(* (img.image+Thiningtest_lineBytes*Thiningtest_i+Thiningtest_n+1))+0.114*(float)(* (img.image+Thiningtest_lineBytes*Thiningtest_i+Thiningtest_n));
             if(Thiningtest_gray>120.0) then 
             {
                 srcBmp[Thiningtest_i*img.width+Thiningtest_j]:=255
             }
             else
             {
                 srcBmp[Thiningtest_i*img.width+Thiningtest_j]:=0
             };
             Thiningtest_n:=Thiningtest_n+3 ; Thiningtest_j:=Thiningtest_j+1
             
         };
         Thiningtest_i:=Thiningtest_i+1
         
     };
     Thiningtest_i:=0;
     
     while(Thiningtest_i<Thiningtest_lHeight)
     {
         Thiningtest_j:=0;
         
         while(Thiningtest_j<Thiningtest_lWidth)
         {
             if(srcBmp[Thiningtest_i*img.width+Thiningtest_j]=0) then 
             {
                 Thiningtest_image[Thiningtest_i*Thiningtest_lWidth+Thiningtest_j]:=1
             }
             else
             {
                 Thiningtest_image[Thiningtest_i*Thiningtest_lWidth+Thiningtest_j]:=0
             };
             Thiningtest_j:=Thiningtest_j+1
             
         };
         Thiningtest_i:=Thiningtest_i+1
         
     };
     ThinnerRosenfeld(Thiningtest_image,img.height,img.width);
     Thiningtest_i:=0;
     
     while(Thiningtest_i<Thiningtest_lHeight)
     {
         Thiningtest_j:=0;
         
         while(Thiningtest_j<Thiningtest_lWidth)
         {
             if(Thiningtest_image[Thiningtest_i*Thiningtest_lWidth+Thiningtest_j]=1) then 
             {
                 dstBmp[Thiningtest_i*img.width+Thiningtest_j]:=(unsigned char)0
             }
             else
             {
                 dstBmp[Thiningtest_i*img.width+Thiningtest_j]:=(unsigned char)255
             };
             Thiningtest_j:=Thiningtest_j+1
             
         };
         Thiningtest_i:=Thiningtest_i+1
         
     }
     )
     }; 
  function delpoint ( unsigned char *dst,int width,int height,int yuzhi )
 {
     frame(delpoint_i,delpoint_j,delpoint_num,delpoint_num1,delpoint_src) and ( 
     int delpoint_i,delpoint_j,delpoint_num<==0,delpoint_num1 and skip;
     unsigned char delpoint_src[10000] and skip;
	 //output("yubin202020\n") and skip;
     //delpoint_src<==(unsigned char *)malloc(width*sizeof(unsigned char)*height) and skip;
     
     memset(delpoint_src,0,1*width*height) and skip;
     delpoint_i:=1;
     
     while(delpoint_i<height-1)
     {
         delpoint_j:=1;
         
         while(delpoint_j<width-1)
         {
             if(dst[delpoint_i*width+delpoint_j]>200) then 
             {
                 delpoint_num1:=dst[delpoint_i*width+delpoint_j-1]+dst[delpoint_i*width+delpoint_j+1]+dst[(delpoint_i-1)*width+delpoint_j-1]+dst[(delpoint_i-1)*width+delpoint_j]+dst[(delpoint_i-1)*width+delpoint_j+1]+dst[(delpoint_i+1)*width+delpoint_j-1]+dst[(delpoint_i+1)*width+delpoint_j]+dst[(delpoint_i+1)*width+delpoint_j+1]+255;
                 delpoint_num:=delpoint_num1/ 255;

                 if(delpoint_num>=yuzhi) then 
                 {
                     delpoint_src[delpoint_i*width+delpoint_j]:=255
                 }
                 else
                 {
                     delpoint_src[delpoint_i*width+delpoint_j]:=0
                 }
                 
             }
             else 
             {
                  skip 
             };
             delpoint_j:=delpoint_j+1
             
         };
         delpoint_i:=delpoint_i+1
         
     };
     memcpy(dst,delpoint_src,1*width*height) and skip
     )
     }; 
  function deljunzao ( unsigned char *dst,int width,int height,int yuzhi )
 {
     frame(deljunzao_i,deljunzao_j,deljunzao_num,deljunzao_num1,deljunzao_src) and ( 
     int deljunzao_i,deljunzao_j,deljunzao_num<==0,deljunzao_num1 and skip;
     unsigned char *deljunzao_src and skip;
	 //output("yubin212121\n") and skip;
     deljunzao_src:=(unsigned char *)malloc(width*sizeof(unsigned char)*height);
     memset(deljunzao_src,0,1*width*height) and skip;
     deljunzao_i:=1;
     
     while(deljunzao_i<height-1)
     {
         deljunzao_j:=1;
         
         while(deljunzao_j<width-1)
         {
             deljunzao_num1:=dst[deljunzao_i*width+deljunzao_j-1]+dst[deljunzao_i*width+deljunzao_j+1]+dst[(deljunzao_i-1)*width+deljunzao_j-1]+dst[(deljunzao_i-1)*width+deljunzao_j]+dst[(deljunzao_i-1)*width+deljunzao_j+1]+dst[(deljunzao_i+1)*width+deljunzao_j-1]+dst[(deljunzao_i+1)*width+deljunzao_j]+dst[(deljunzao_i+1)*width+deljunzao_j+1]+dst[deljunzao_i*width+deljunzao_j];
             deljunzao_num:=deljunzao_num1/ 255;
             if(deljunzao_num>=yuzhi) then 
             {
                 deljunzao_src[deljunzao_i*width+deljunzao_j]:=255
             }
             else
             {
                 deljunzao_src[deljunzao_i*width+deljunzao_j]:=0
             };
             deljunzao_j:=deljunzao_j+1
             
         };
         deljunzao_i:=deljunzao_i+1
         
     };
     deljunzao_i:=1;
     
     while(deljunzao_i<height-1)
     {
         deljunzao_j:=1;
         
         while(deljunzao_j<width-1)
         {
             if(dst[deljunzao_i*width+deljunzao_j]>200) then 
             {
                 deljunzao_num:=dst[deljunzao_i*width+deljunzao_j-1]+dst[deljunzao_i*width+deljunzao_j+1]+dst[(deljunzao_i-1)*width+deljunzao_j-1]+dst[(deljunzao_i-1)*width+deljunzao_j]+dst[(deljunzao_i-1)*width+deljunzao_j+1]+dst[(deljunzao_i+1)*width+deljunzao_j-1]+dst[(deljunzao_i+1)*width+deljunzao_j]+dst[(deljunzao_i+1)*width+deljunzao_j+1]+255;
                 deljunzao_num:=deljunzao_num/ 255;
                 if(deljunzao_num>=2) then 
                 {
                     deljunzao_src[deljunzao_i*width+deljunzao_j]:=255
                 }
                 else
                 {
                     deljunzao_src[deljunzao_i*width+deljunzao_j]:=0
                 }
                 
             }
             else 
             {
                  skip 
             };
             deljunzao_j:=deljunzao_j+1
             
         };
         deljunzao_i:=deljunzao_i+1
         
     };
     memcpy(dst,deljunzao_src,1*width*height) and skip
     )
     }; 
  function pingjun ( unsigned char *dst,int width,int height )
 {
     frame(pingjun_i,pingjun_j,pingjun_num,pingjun_num1,pingjun_src) and ( 
     int pingjun_i,pingjun_j,pingjun_num<==0 and skip;
     float pingjun_num1 and skip;
     unsigned char *pingjun_src and skip;
	 //output("yubin222222\n") and skip;
     pingjun_src:=(unsigned char *)malloc(width*sizeof(unsigned char)*height);
     memset(pingjun_src,0,1*width*height) and skip;
     pingjun_i:=1;
     
     while(pingjun_i<height-1)
     {
         pingjun_j:=1;
         
         while(pingjun_j<width-1)
         {
             pingjun_num1:=dst[pingjun_i*width+pingjun_j-1]+dst[pingjun_i*width+pingjun_j+1]+dst[(pingjun_i-1)*width+pingjun_j-1]+dst[(pingjun_i-1)*width+pingjun_j]+dst[(pingjun_i-1)*width+pingjun_j+1]+dst[(pingjun_i+1)*width+pingjun_j-1]+dst[(pingjun_i+1)*width+pingjun_j]+dst[(pingjun_i+1)*width+pingjun_j+1]+dst[pingjun_i*width+pingjun_j];
             pingjun_num:=(int)(pingjun_num1/ 9+0.5);
             pingjun_src[pingjun_i*width+pingjun_j]:=pingjun_num;
             pingjun_j:=pingjun_j+1
             
         };
         pingjun_i:=pingjun_i+1
         
     };
     memcpy(dst,pingjun_src,1*width*height) and skip
     )
     }; 
  function Dilation ( unsigned char *image,int width,int height,int type,int num )
 {
     frame(Dilation_dwWidth,Dilation_dwHeight,Dilation_i,Dilation_j,Dilation_g,Dilation_temp,Dilation_k,break$) and ( 
     int break$<==0 and skip;
     int Dilation_dwWidth<==width and skip;
     int Dilation_dwHeight<==height and skip;
     int Dilation_i<==0 and skip;
     int Dilation_j<==0 and skip;
     unsigned char Dilation_g<==0 and skip;
     unsigned char *Dilation_temp and skip;
     int Dilation_k<==0 and skip;
	 //output("yubin232323\n") and skip;
     Dilation_temp:=(unsigned char *)malloc(Dilation_dwHeight*Dilation_dwWidth*sizeof(unsigned char));
     memcpy(Dilation_temp,image,Dilation_dwHeight*Dilation_dwWidth*1) and skip;
     memset(Dilation_temp,0,Dilation_dwWidth*Dilation_dwHeight*1) and skip;
     if(type=0) then 
     {
         Dilation_i:=0;
         
         while(Dilation_i<Dilation_dwHeight)
         {
             Dilation_j:=(num-1)/ 2;
             
             while(Dilation_j<Dilation_dwWidth-(num-1)/ 2)
             {
                 break$<==0 and skip;
                 Dilation_k:=-(num-1)/ 2;
                 
                 while( break$=0 AND  Dilation_k<=(num-1)/ 2)
                 {
                     Dilation_g:=* (image+Dilation_dwWidth*Dilation_i+Dilation_j+Dilation_k);
                     if(Dilation_g=255) then 
                     {
                         * (Dilation_temp+Dilation_dwWidth*Dilation_i+Dilation_j):=255;
                         break$<==1 and skip
                          
                     }
                     else 
                     {
                          skip 
                     };
                     if(break$=0)   then
                     {
                         Dilation_k:=Dilation_k+1
                     }
                     else
                     {
                         skip
                     }
                     
                 };
                 break$<==0 and skip;
                 Dilation_j:=Dilation_j+1
                 
             };
             Dilation_i:=Dilation_i+1
             
         }
         
     }
     else
     {
         Dilation_i:=(num-1)/ 2;
         
         while(Dilation_i<Dilation_dwHeight-(num-1)/ 2)
         {
             Dilation_j:=0;
             
             while(Dilation_j<Dilation_dwWidth)
             {
                 break$<==0 and skip;
                 Dilation_k:=-(num-1)/ 2;
                 
                 while( break$=0 AND  Dilation_k<=(num-1)/ 2)
                 {
                     Dilation_g:=* (image+Dilation_dwWidth*(Dilation_i+Dilation_k)+Dilation_j);
                     if(Dilation_g=255) then 
                     {
                         * (Dilation_temp+Dilation_dwWidth*Dilation_i+Dilation_j):=255;
                         break$<==1 and skip
                          
                     }
                     else 
                     {
                          skip 
                     };
                     if(break$=0)   then
                     {
                         Dilation_k:=Dilation_k+1
                     }
                     else
                     {
                         skip
                     }
                     
                 };
                 break$<==0 and skip;
                 Dilation_j:=Dilation_j+1
                 
             };
             Dilation_i:=Dilation_i+1
             
         }
     };
     memcpy(image,Dilation_temp,1*width*height) and skip;
     free(Dilation_temp) and skip;
     Dilation_temp:=NULL
     )
     }; 
  function Erosion ( unsigned char *image,int width,int height,int type,int num )
 {
     frame(Erosion_dwWidth,Erosion_dwHeight,Erosion_i,Erosion_j,Erosion_g,Erosion_temp,Erosion_k,break$) and ( 
     int break$<==0 and skip;
     int Erosion_dwWidth<==width and skip;
     int Erosion_dwHeight<==height and skip;
     int Erosion_i<==0 and skip;
     int Erosion_j<==0 and skip;
     unsigned char Erosion_g<==0 and skip;
     unsigned char *Erosion_temp and skip;
     int Erosion_k<==0 and skip;
	 //output("yubin242424\n") and skip;
     Erosion_temp:=(unsigned char *)malloc(Erosion_dwHeight*Erosion_dwWidth*sizeof(unsigned char));
     memset(Erosion_temp,0,Erosion_dwWidth*Erosion_dwHeight*1) and skip;
     if(type=0) then 
     {
         Erosion_i:=0;
         
         while(Erosion_i<Erosion_dwHeight)
         {
             Erosion_j:=(num-1)/ 2;
             
             while(Erosion_j<Erosion_dwWidth-(num-1)/ 2)
             {
                 break$<==0 and skip;
                 Erosion_k:=-(num-1)/ 2;
                 
                 while( break$=0 AND  Erosion_k<=(num-1)/ 2)
                 {
                     Erosion_g:=* (image+width*Erosion_i+Erosion_j+Erosion_k);
                     if(Erosion_g=0) then 
                     {
                         * (Erosion_temp+width*Erosion_i+Erosion_j):=0;
                         break$<==1 and skip
                          
                     }
                     else 
                     {
                          skip 
                     };
                     if(break$=0)   then
                     {
                         Erosion_k:=Erosion_k+1
                     }
                     else
                     {
                         skip
                     }
                     
                 };
                 break$<==0 and skip;
                 Erosion_j:=Erosion_j+1
                 
             };
             Erosion_i:=Erosion_i+1
             
         }
         
     }
     else
     {
         Erosion_i:=(num-1)/ 2;
         
         while(Erosion_i<Erosion_dwHeight-(num-1)/ 2)
         {
             Erosion_j:=0;
             
             while(Erosion_j<Erosion_dwWidth)
             {
                 break$<==0 and skip;
                 Erosion_k:=-(num-1)/ 2;
                 
                 while( break$=0 AND  Erosion_k<=(num-1)/ 2)
                 {
                     Erosion_g:=* (image+width*(Erosion_i+Erosion_k)+Erosion_j);
                     if(Erosion_g=0) then 
                     {
                         * (Erosion_temp+width*Erosion_i+Erosion_j):=0;
                         break$<==1 and skip
                          
                     }
                     else 
                     {
                          skip 
                     };
                     if(break$=0)   then
                     {
                         Erosion_k:=Erosion_k+1
                     }
                     else
                     {
                         skip
                     }
                     
                 };
                 break$<==0 and skip;
                 Erosion_j:=Erosion_j+1
                 
             };
             Erosion_i:=Erosion_i+1
             
         }
     };
     memcpy(image,Erosion_temp,1*width*height) and skip;
     free(Erosion_temp) and skip;
     Erosion_temp:=NULL
     )
     }; 
  function changeGray ( unsigned char *srcBmp,unsigned char *dstBmp,int width,int height,int nWidth,int nHeight )
 {
     frame(changeGray_i,changeGray_j,changeGray_i0,changeGray_j0,changeGray_xx,changeGray_yy) and ( 
     int changeGray_i<==0,changeGray_j<==0,changeGray_i0,changeGray_j0 and skip;
     float changeGray_xx and skip;
     float changeGray_yy and skip;
     changeGray_xx:=(float)nWidth/ width;
     changeGray_yy:=(float)nHeight/ height;
     memset(dstBmp,0,nHeight*nWidth*1) and skip;
     changeGray_i:=0;
     
     while(changeGray_i<nHeight)
     {
         changeGray_j:=0;
         
         while(changeGray_j<nWidth)
         {
             changeGray_i0:=(int)((float)changeGray_i/ changeGray_yy);
             changeGray_j0:=(int)((float)changeGray_j/ changeGray_xx);
             if((changeGray_j0>=0) AND (changeGray_j0<width) AND (changeGray_i0>=0) AND (changeGray_i0<height)) then 
             {
                 dstBmp[changeGray_i*nWidth+changeGray_j]:=srcBmp[changeGray_i0*width+changeGray_j0]
             }
             else 
             {
                  skip 
             };
             changeGray_j:=changeGray_j+1
             
         };
         changeGray_i:=changeGray_i+1
         
     }
     )
     }; 
  function strBmp ( Bmp1 *img,unsigned char *temp )
 {
     frame(strBmp_i,strBmp_j,strBmp_k,strBmp_m,strBmp_n,strBmp_o) and ( 
     int strBmp_i,strBmp_j,strBmp_k,strBmp_m,strBmp_n,strBmp_o and skip;
     strBmp_i:=0;
     
     while(strBmp_i<7)
     {
         strBmp_o:=img->p2[strBmp_i]-img->p1[strBmp_i]+1;
         strBmp_m:=0 ; strBmp_j:=img->p3[strBmp_i];
         while(strBmp_j<=img->p4[strBmp_i])
         {
             strBmp_n:=0 ; strBmp_k:=img->p1[strBmp_i];
             while(strBmp_k<=img->p2[strBmp_i])
             {
                 img->strr[strBmp_i,strBmp_m*strBmp_o+strBmp_n]:=temp[strBmp_j*img->width+strBmp_k];
                 strBmp_k:=strBmp_k+1 ; strBmp_n:=strBmp_n+1
                 
             };
             strBmp_j:=strBmp_j+1 ; strBmp_m:=strBmp_m+1
             
         };
         strBmp_i:=strBmp_i+1
         
     }
     )
     }; 
  function guiyi ( Bmp1 *img )
 {
     frame(guiyi_xxx,guiyi_i,guiyi_yyy,guiyi_temp) and ( 
     int guiyi_xxx and skip;
     int guiyi_i and skip;
     int guiyi_yyy and skip;
     unsigned char *guiyi_temp and skip;
     guiyi_temp:=(unsigned char *)malloc(800*sizeof(unsigned char));
     guiyi_i:=0;
     
     while(guiyi_i<7)
     {
         guiyi_xxx:=img->p2[guiyi_i]-img->p1[guiyi_i]+1;
         guiyi_yyy:=img->p4[guiyi_i]-img->p3[guiyi_i]+1;
         changeGray(img->strr[guiyi_i],guiyi_temp,guiyi_xxx,guiyi_yyy,20,40);
         memcpy(img->strr[guiyi_i],guiyi_temp,1*800) and skip;
         guiyi_i:=guiyi_i+1
         
     }
     )
     }; 
  function readmoban ( char *path,Bmp1 *img2 )
 {
     frame(readmoban_f,readmoban_i,readmoban_str2,readmoban_str,readmoban_str1) and ( 
     FILE *readmoban_f[72] and skip;
	 memset(readmoban_f,0,288) and skip;
     int readmoban_i and skip;
     char readmoban_str2[5]<==".bmp" and skip;
     char readmoban_str[80] and skip;
     char readmoban_str1[10] and skip;
     readmoban_i:=0;
     
     while(readmoban_i<=66)
     {
         strcpy(readmoban_str,path) and skip;
         myitoa(readmoban_i,readmoban_str1,10,RValue);
         strcat(readmoban_str1,readmoban_str2) and skip;
         strcat(readmoban_str,readmoban_str1) and skip;
         readmoban_f[readmoban_i]:=fopen (readmoban_str,"rb");
         if(readmoban_f[readmoban_i]=NULL) then 
         {
             exit<==0 and skip 
         }
         else 
         {
              skip 
         };
		 

         readstr(readmoban_f[readmoban_i],img2->strc[readmoban_i]);

         fclose (readmoban_f[readmoban_i]) and skip;
         readmoban_i:=readmoban_i+1
     }
     )
     }; 
  function myitoa ( int num,char *str,int radix,char* RValue )
 {
     frame(myitoa_index,myitoa_unum,myitoa_i,myitoa_j,myitoa_k,count$,return) and ( 
     int return<==0 and skip;
     char myitoa_index[37]<=="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" and skip;
     int myitoa_unum and skip;
     int myitoa_i<==0,myitoa_j,myitoa_k and skip;
     if(radix=10 AND num<0) then 
     {
         myitoa_unum:=-num;
         str[myitoa_i]:='-';
         myitoa_i:=myitoa_i+1
         
     }
     else
     {
         myitoa_unum:=(int)num
     };
     int count$<==0 and skip;
     while( ( count$=0 OR myitoa_unum))
     {
         count$:=count$+1;
         str[myitoa_i]:=myitoa_index[myitoa_unum % (int)radix];
         myitoa_i:=myitoa_i+1;
         myitoa_unum:=myitoa_unum/ radix
     };
     str[myitoa_i]:='\0';
     if(str[0]='-') then 
     {
         myitoa_k:=1
     }
     else
     {
         myitoa_k:=0
     };
     myitoa_j:=myitoa_k;
     
     while(myitoa_j<(myitoa_i-1)/ 2.0+myitoa_k)
     {
         num:=str[myitoa_j];
         str[myitoa_j]:=str[myitoa_i-myitoa_j-1+myitoa_k];
         str[myitoa_i-myitoa_j-1+myitoa_k]:=num;
         myitoa_j:=myitoa_j+1
         
     };
     return<==1 and RValue:=str;
     skip
     )
     }; 
  function writebmp ( char *path,char *name,unsigned char *temp )
 {
     frame(writebmp_f1,writebmp_f2,writebmp_i,writebmp_j,writebmp_temp1,writebmp_path1,writebmp_path2,writebmp_p1,writebmp_p4,writebmp_p2,writebmp_p3) and ( 
     FILE *writebmp_f1,*writebmp_f2 and skip;
     int writebmp_i,writebmp_j and skip;
     unsigned char writebmp_temp1 and skip;
     char writebmp_path1[40] and skip;
     char writebmp_path2[40] and skip;
     char *writebmp_p1<=="header.txt" and skip;
     char writebmp_p4[5]<==".bmp" and skip;
     char writebmp_p2[1078] and skip;
     char writebmp_p3[800] and skip;
     strcpy(writebmp_path1,path) and skip;
     strcat(writebmp_path1,writebmp_p1) and skip;
     strcpy(writebmp_path2,path) and skip;
     strcat(writebmp_path2,name) and skip;
     strcat(writebmp_path2,writebmp_p4) and skip;
     writebmp_f1:=fopen (writebmp_path1,"rb") ;
     if((writebmp_f1)=NULL) then 
     {
         output ("\n 不能打开  \n") and skip;
         exit<==0 and skip 
         
     }
     else 
     {
          skip 
     };
     fread(writebmp_p2,1078,1,writebmp_f1) and skip;
     writebmp_i:=0;
     
     while(writebmp_i<40)
     {
         writebmp_j:=0;
         
         while(writebmp_j<20)
         {
             writebmp_temp1:=temp[writebmp_i*20+writebmp_j];
             if(writebmp_temp1=0) then 
             {
                 writebmp_temp1:=0
             }
             else
             {
                 writebmp_temp1:=255
             };
             writebmp_p3[(40-writebmp_i-1)*20+writebmp_j]:=writebmp_temp1;
             writebmp_j:=writebmp_j+1
             
         };
         writebmp_i:=writebmp_i+1
         
     };
     writebmp_f2:=fopen (writebmp_path2,"wb") ;
     if((writebmp_f2)=NULL) then 
     {
         output ("\n不能创建",writebmp_path1,"图\n") and skip;
         exit<==0 and skip 
         
     }
     else 
     {
          skip 
     };
     if(extern fwrite(writebmp_p2,1078*1,1,writebmp_f2)!=1) then 
     {
         output ("不能写入",writebmp_path2,"图\n") and skip;
         fclose (writebmp_f2) and skip
         
     }
     else 
     {
          skip 
     };
     fseek(writebmp_f2,1078,0) and skip;
     if(extern fwrite(writebmp_p3,20*40,1,writebmp_f2)!=1) then 
     {
         output ("不能写入",writebmp_path2,"图\n") and skip;
         fclose (writebmp_f2) and skip
         
     }
     else 
     {
          skip 
     };
     fclose (writebmp_f1) and skip;
     fclose (writebmp_f2) and skip
     )
     }; 
  function strout ( Bmp1 *img )
 {
     frame(strout_i,strout_j,strout_k,strout_m,strout_n,break$) and ( 
     int break$<==0 and skip;
     int strout_i,strout_j,strout_k<==0,strout_m<==800,strout_n and skip;
     break$<==0 and skip;
     strout_i:=36;
     
     while( break$=0 AND  strout_i<67)
     {
         strout_k:=cmpstr(img->strr[0],img->strc[strout_i],RValue);
         if(strout_k=0) then 
         {
             strout_n:=strout_i;
             break$<==1 and skip
              
         }
         else
         {
             if(strout_k<strout_m) then 
             {
                 strout_m:=strout_k;
                 strout_n:=strout_i
                 
             }
             else 
             {
                  skip 
             }
         };
         if(break$=0)   then 
         {
             strout_i:=strout_i+1
         }
         else
         {
             skip
         }
         
     };
     break$<==0 and skip;
     img->string$[0]:=strout_n;
     strout_i:=1;
     
     while(strout_i<7)
     {
         strout_n:=0;
         strout_k:=0;
         strout_m:=800;
         break$<==0 and skip;
         strout_j:=0;
         
         while( break$=0 AND  strout_j<36)
         {
             if((img->p2[strout_i]-img->p1[strout_i])<4) then 
             {
                 strout_n:=1;
                 break$<==1 and skip
                  
             }
             else 
             {
                  skip 
             };
             if(break$=0)   then
             {
                 strout_k:=cmpstr(img->strr[strout_i],img->strc[strout_j],RValue);
                 if(strout_k=0) then 
                 {
                     strout_n:=strout_j;
                     break$<==1 and skip
                      
                 }
                 else
                 {
                     if(strout_k<strout_m) then 
                     {
                         strout_m:=strout_k;
                         strout_n:=strout_j
                         
                     }
                     else 
                     {
                          skip 
                     }
                 };
                 if(break$=0)   then 
                 {
                     strout_j:=strout_j+1
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
         if(strout_n=27) then 
         {
             strout_k:=cmpstr(img->strc[27],img->strr[strout_i],RValue);
             strout_j:=cmpstr(img->strr[strout_i],img->strc[25],RValue);
             if(strout_k<strout_j) then 
             {
                 strout_n:=27
             }
             else
             {
                 strout_n:=25
             }
             
         }
         else 
         {
              skip 
         };
         if(strout_n=0) then 
         {
             strout_j:=cmpstr(img->strc[0],img->strr[strout_i],RValue);
             strout_k:=cmpstr(img->strr[strout_i],img->strc[12],RValue);
             if(strout_j>strout_k) then 
             {
                 strout_n:=12
             }
             else
             {
                 strout_n:=0
             }
             
         }
         else 
         {
              skip 
         };
         if(strout_n=26) then 
         {
             strout_k:=cmpstr(img->strc[26],img->strr[strout_i],RValue);
             strout_j:=cmpstr(img->strr[strout_i],img->strc[0],RValue);
             if(strout_k<strout_j) then 
             {
                 strout_n:=26
             }
             else
             {
                 strout_n:=0
             }
             
         }
         else 
         {
              skip 
         };
         if(strout_n=19) then 
         {
             strout_k:=cmpstr(img->strc[0],img->strr[strout_i],RValue);
             strout_j:=cmpstr(img->strr[19],img->strc[strout_i],RValue);
             if(strout_k<strout_j) then 
             {
                 strout_n:=0
             }
             else
             {
                 strout_n:=19
             }
             
         }
         else 
         {
              skip 
         };
         if(strout_n=13) then 
         {
             strout_k:=cmpstr(img->strc[13],img->strr[strout_i],RValue);
             strout_j:=cmpstr(img->strr[strout_i],img->strc[0],RValue);
             if(strout_k<strout_j) then 
             {
                 strout_n:=13
             }
             else
             {
                 strout_n:=0
             }
             
         }
         else 
         {
              skip 
         };
         if(strout_n=14) then 
         {
             strout_k:=cmpstr(img->strc[14],img->strr[strout_i],RValue);
             strout_j:=cmpstr(img->strr[strout_i],img->strc[15],RValue);
             if(strout_k<strout_j) then 
             {
                 strout_n:=14
             }
             else
             {
                 strout_n:=15
             }
             
         }
         else 
         {
              skip 
         };
         if(strout_n=8) then 
         {
             strout_k:=cmpstr(img->strc[8],img->strr[strout_i],RValue);
             strout_j:=cmpstr(img->strr[strout_i],img->strc[3],RValue);
             if(strout_k<strout_j) then 
             {
                 strout_n:=8
             }
             else
             {
                 strout_n:=3
             }
             
         }
         else 
         {
              skip 
         };
         img->string$[strout_i]:=strout_n;
         strout_i:=strout_i;
         strout_i:=strout_i+1
         
     }
     )
     }; 
  function cmpstr ( unsigned char *src,unsigned char *moban,int RValue )
 {
     frame(cmpstr_i,cmpstr_j,cmpstr_k,cmpstr_temp,return) and ( 
     int return<==0 and skip;
     int cmpstr_i,cmpstr_j,cmpstr_k<==0 and skip;
     unsigned char cmpstr_temp[800]<=={0} and skip;
     memset(cmpstr_temp,0,800) and skip;
     memcpy(cmpstr_temp,src,800) and skip;
     cmpstr_i:=0;
     
     while(cmpstr_i<40)
     {
         cmpstr_j:=0;
         
         while(cmpstr_j<20)
         {
             if(cmpstr_temp[cmpstr_i*20+cmpstr_j]=255) then 
             {
                 if(moban[cmpstr_i*20+cmpstr_j]=255) then 
                 {
                     cmpstr_temp[cmpstr_i*20+cmpstr_j]:=0
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
             cmpstr_j:=cmpstr_j+1
             
         };
         cmpstr_i:=cmpstr_i+1
         
     };
     delpoint(cmpstr_temp,40,20,4);
     cmpstr_i:=0;
     
     while(cmpstr_i<40)
     {
         cmpstr_j:=0;
         
         while(cmpstr_j<20)
         {
             if(cmpstr_temp[cmpstr_i*20+cmpstr_j]=255) then 
             {
                 cmpstr_k:=cmpstr_k+1
                 
             }
             else 
             {
                  skip 
             };
             cmpstr_j:=cmpstr_j+1
             
         };
         cmpstr_i:=cmpstr_i+1
         
     };
     return<==1 and RValue:=cmpstr_k;
     skip
     )
     }; 
  function calstr ( unsigned char *srcBmp,int RValue )
 {
     frame(calstr_i,calstr_j,calstr_num,return) and ( 
     int return<==0 and skip;
     int calstr_i,calstr_j,calstr_num<==0 and skip;
     calstr_i:=0;
     
     while(calstr_i<40)
     {
         calstr_j:=0;
         
         while(calstr_j<20)
         {
             if(srcBmp[calstr_i*20+calstr_j]=255) then 
             {
                 calstr_num:=calstr_num+1
                 
             }
             else 
             {
                  skip 
             };
             calstr_j:=calstr_j+1
             
         };
         calstr_i:=calstr_i+1
         
     };
     return<==1 and RValue:=calstr_num;
     skip
     )
     }; 
  function edgesob8 ( unsigned char *image,int width,int height )
 {
     frame(edgesob8_i,edgesob8_j,edgesob8_logNum,edgesob8_temp) and ( 
     int edgesob8_i,edgesob8_j,edgesob8_logNum and skip;
     unsigned char *edgesob8_temp and skip;
	 //output("yubin262626\n") and skip;
     edgesob8_temp:=(unsigned char *)malloc(width*sizeof(unsigned char)*height);
     memset(edgesob8_temp,0,1*width*height) and skip;
     edgesob8_i:=3;
     
     while(edgesob8_i<height-2)
     {
         edgesob8_j:=3;
         
         while(edgesob8_j<width-2)
         {
             edgesob8_logNum:=16*image[edgesob8_i*width+edgesob8_j]-image[(edgesob8_i-2)*width+edgesob8_j]-image[(edgesob8_i-1)*width+edgesob8_j-1]-2*image[(edgesob8_i-1)*width+edgesob8_j]-image[(edgesob8_i-1)*width+edgesob8_j+1]-image[edgesob8_i*width+edgesob8_j-2]-2*image[edgesob8_i*width+edgesob8_j-1]-2*image[edgesob8_i*width+edgesob8_j+1]-image[edgesob8_i*width+edgesob8_j+2]-image[(edgesob8_i+1)*width+edgesob8_j-1]-2*image[(edgesob8_i+1)*width+edgesob8_j]-image[(edgesob8_i+1)*width+edgesob8_j+1]-image[(edgesob8_i+2)*width+edgesob8_j];
             if(edgesob8_logNum>0) then 
             {
                 edgesob8_temp[edgesob8_i*width+edgesob8_j]:=255
             }
             else
             {
                 edgesob8_temp[edgesob8_i*width+edgesob8_j]:=0
             };
             edgesob8_j:=edgesob8_j+1
             
         };
         edgesob8_i:=edgesob8_i+1
         
     };
     memcpy(image,edgesob8_temp,width*height) and skip;
     free(edgesob8_temp) and skip;
     edgesob8_temp:=NULL
     )
     }; 
  function edgesob4 ( unsigned char *image,int width,int height )
 {
     frame(edgesob4_i,edgesob4_j,edgesob4_p,edgesob4_result,edgesob4_temp) and ( 
     int edgesob4_i,edgesob4_j and skip;
     int edgesob4_p[8] and skip;
     float edgesob4_result and skip;
     unsigned char *edgesob4_temp and skip;
	 //output("yubin272727\n") and skip;
     edgesob4_temp:=(unsigned char *)malloc(width*sizeof(unsigned char)*height);
     memset(edgesob4_temp,0,1*width*height) and skip;
     edgesob4_i:=0;
     
     while(edgesob4_i<=height-1)
     {
         edgesob4_j:=0;
         
         while(edgesob4_j<=width-1)
         {
             if(edgesob4_i=height-1) then 
             {
                 edgesob4_temp[edgesob4_i*width+edgesob4_j]:=0
             }
             else
             {
                 if(edgesob4_j=width-1) then 
                 {
                     edgesob4_temp[edgesob4_i*width+edgesob4_j]:=0
                 }
                 else
                 {
                     edgesob4_p[0]:=(unsigned char)* (image+edgesob4_i*width+edgesob4_j);
                     edgesob4_p[1]:=(unsigned char)* (image+edgesob4_i*width+edgesob4_j+1);
                     edgesob4_p[2]:=(unsigned char)* (image+(edgesob4_i+1)*width+edgesob4_j);
                     edgesob4_p[3]:=(unsigned char)* (image+(edgesob4_i+1)*width+edgesob4_j+1);
                     edgesob4_result:=sqrt((edgesob4_p[0]-edgesob4_p[3])*(edgesob4_p[0]-edgesob4_p[3])+(edgesob4_p[1]-edgesob4_p[2])*(edgesob4_p[1]-edgesob4_p[2]));
                     if(edgesob4_result<=0.0) then 
                     {
                         edgesob4_result:=0
                     }
                     else 
                     {
                          skip 
                     };
                     if(edgesob4_result>=255.0) then 
                     {
                         edgesob4_result:=255
                     }
                     else 
                     {
                          skip 
                     };
                     edgesob4_temp[edgesob4_i*width+edgesob4_j]:=(unsigned char)edgesob4_result
                 }
             };
             edgesob4_j:=edgesob4_j+1
             
         };
         edgesob4_i:=edgesob4_i+1
         
     };
     memcpy(image,edgesob4_temp,width*height) and skip;
     free(edgesob4_temp) and skip;
     edgesob4_temp:=NULL
     )
     }; 
  function hough ( unsigned char *srcBmp,int width,int height,int RValue )
 {
     frame(hough_kmax,hough_pmax,hough_yuzhi,hough_i,hough_j,hough_k,hough_n,hough_p,hough_mp,hough_ma,hough_npp,return) and ( 
     int return<==0 and skip;
     int hough_kmax<==0 and skip;
     int hough_pmax<==0 and skip;
     int hough_yuzhi<==0 and skip;
     int hough_i,hough_j,hough_k,hough_n,hough_p<==(int)(height*cos(3.14)+width*sin(3.14)) and skip;
     int hough_mp<==(int)(sqrt(width*width+height*height)+1) and skip;
     int hough_ma<==1 and skip;
     int *hough_npp[1] and skip;
     hough_i:=0;

    while(hough_i<1)
    {
	//output("yubin282828\n") and skip;
        hough_npp[hough_i]:= (int*)malloc(4000);
        hough_i:=hough_i+1
    };
    hough_i:=0;
     while(hough_i<1)
     {
         hough_j:=0;
         
         while(hough_j<1000)
         {
             hough_npp[hough_i,hough_j]:=0;
             hough_j:=hough_j+1
         };
         hough_i:=hough_i+1
         
     };
     hough_i:=1;
     
     while(hough_i<height)
     {
         hough_j:=1;
         
         while(hough_j<width)
         {
             if(srcBmp[hough_i*width+hough_j]=255) then 
             {
                 hough_k:=1;
                 
                 while(hough_k<hough_ma)
                 {
                     hough_p:=(int)(hough_i*cos(3.14*hough_k/ 180)+hough_j*sin(3.14*hough_k/ 180));
                     hough_p:=(int)(hough_p/ 2+hough_mp/ 2);
                     hough_npp[hough_k,hough_p]:=hough_npp[hough_k,hough_p];
                     hough_npp[hough_k,hough_p]:=hough_npp[hough_k,hough_p]+1;
                     hough_k:=hough_k+1
                     
                 }
                 
             }
             else 
             {
                  skip 
             };
             hough_j:=hough_j+1
             
         };
         hough_i:=hough_i+1
         
     };
     hough_kmax:=0;
     hough_pmax:=0;
     hough_n:=0;
     hough_i:=1;
     
     while(hough_i<hough_ma)
     {
         hough_j:=1;
         
         while(hough_j<hough_mp)
         {
             if(hough_npp[hough_i,hough_j]>hough_yuzhi) then 
             {
                 hough_yuzhi:=hough_npp[hough_i,hough_j];
                 hough_kmax:=hough_i;
                 hough_pmax:=hough_j
                 
             }
             else 
             {
                  skip 
             };
             hough_j:=hough_j+1
             
         };
         hough_i:=hough_i+1
         
     };
      hough_i:=0;

    while(hough_i<1)
    {
        free(hough_npp[hough_i]) and skip;
        hough_i:=hough_i+1
    };
     return<==1 and RValue:=hough_kmax;
     skip
     )
     }; 
  function RotateGray ( unsigned char *image,int width,int height,float iRotateAngle )
 {
     frame(RotateGray_i,RotateGray_j,RotateGray_lNewWidth,RotateGray_lNewHeight,RotateGray_i0,RotateGray_j0,RotateGray_ang,RotateGray_fRotateAngle,RotateGray_fSina,RotateGray_fCosa,RotateGray_fSrcX1,RotateGray_fSrcY1,RotateGray_fSrcX2,RotateGray_fSrcY2,RotateGray_fSrcX3,RotateGray_fSrcY3,RotateGray_fSrcX4,RotateGray_fSrcY4,RotateGray_fDstX1,RotateGray_fDstY1,RotateGray_fDstX2,RotateGray_fDstY2,RotateGray_fDstX3,RotateGray_fDstY3,RotateGray_fDstX4,RotateGray_fDstY4,RotateGray_f1,RotateGray_f2,RotateGray_temp) and ( 
     int RotateGray_i,RotateGray_j,RotateGray_lNewWidth,RotateGray_lNewHeight,RotateGray_i0,RotateGray_j0 and skip;
     int RotateGray_ang and skip;
     float RotateGray_fRotateAngle and skip;
     float RotateGray_fSina,RotateGray_fCosa and skip;
     float RotateGray_fSrcX1,RotateGray_fSrcY1,RotateGray_fSrcX2,RotateGray_fSrcY2,RotateGray_fSrcX3,RotateGray_fSrcY3,RotateGray_fSrcX4,RotateGray_fSrcY4 and skip;
     float RotateGray_fDstX1,RotateGray_fDstY1,RotateGray_fDstX2,RotateGray_fDstY2,RotateGray_fDstX3,RotateGray_fDstY3,RotateGray_fDstX4,RotateGray_fDstY4 and skip;
     float RotateGray_f1,RotateGray_f2 and skip;
     unsigned char *RotateGray_temp and skip;
	 //output("yubin292929\n") and skip;
     RotateGray_temp:=(unsigned char *)malloc(RotateGray_lNewHeight*sizeof(unsigned char)*RotateGray_lNewWidth);
     if(RotateGray_temp=NULL) then 
     {
         output ("\nerror\n") and skip
     }
     else 
     {
          skip 
     };
     RotateGray_fRotateAngle:=(float)(iRotateAngle*3.14/ 180.0);
     RotateGray_fSina:=(float)sin((float)RotateGray_fRotateAngle);
     RotateGray_fCosa:=(float)cos((float)RotateGray_fRotateAngle);
     RotateGray_fSrcX1:=(float)(-(width-1)/ 2);
     RotateGray_fSrcY1:=(float)((height-1)/ 2);
     RotateGray_fSrcX2:=(float)((width-1)/ 2);
     RotateGray_fSrcY2:=(float)((height-1)/ 2);
     RotateGray_fSrcX3:=(float)(-(width-1)/ 2);
     RotateGray_fSrcY3:=(float)(-(height-1)/ 2);
     RotateGray_fSrcX4:=(float)((width-1)/ 2);
     RotateGray_fSrcY4:=(float)(-(height-1)/ 2);
     RotateGray_fDstX1:=RotateGray_fCosa*RotateGray_fSrcX1+RotateGray_fSina*RotateGray_fSrcY1;
     RotateGray_fDstY1:=-RotateGray_fSina*RotateGray_fSrcX1+RotateGray_fCosa*RotateGray_fSrcY1;
     RotateGray_fDstX2:=RotateGray_fCosa*RotateGray_fSrcX2+RotateGray_fSina*RotateGray_fSrcY2;
     RotateGray_fDstY2:=-RotateGray_fSina*RotateGray_fSrcX2+RotateGray_fCosa*RotateGray_fSrcY2;
     RotateGray_fDstX3:=RotateGray_fCosa*RotateGray_fSrcX3+RotateGray_fSina*RotateGray_fSrcY3;
     RotateGray_fDstY3:=-RotateGray_fSina*RotateGray_fSrcX3+RotateGray_fCosa*RotateGray_fSrcY3;
     RotateGray_fDstX4:=RotateGray_fCosa*RotateGray_fSrcX4+RotateGray_fSina*RotateGray_fSrcY4;
     RotateGray_fDstY4:=-RotateGray_fSina*RotateGray_fSrcX4+RotateGray_fCosa*RotateGray_fSrcY4;
     RotateGray_lNewWidth:=(int)((( if(((fabs(RotateGray_fDstX4-RotateGray_fDstX1))>(fabs(RotateGray_fDstX3-RotateGray_fDstX2)))) then (fabs(RotateGray_fDstX4-RotateGray_fDstX1)) else (fabs(RotateGray_fDstX3-RotateGray_fDstX2))))+0.5);
     RotateGray_lNewHeight:=(int)((( if(((fabs(RotateGray_fDstY4-RotateGray_fDstY1))>(fabs(RotateGray_fDstY3-RotateGray_fDstY2)))) then (fabs(RotateGray_fDstY4-RotateGray_fDstY1)) else (fabs(RotateGray_fDstY3-RotateGray_fDstY2))))+0.5);
     RotateGray_f1:=(float)(-0.5*(RotateGray_lNewWidth-1)*RotateGray_fCosa-0.5*(RotateGray_lNewHeight-1)*RotateGray_fSina+0.5*(width-1));
     RotateGray_f2:=(float)(0.5*(RotateGray_lNewWidth-1)*RotateGray_fSina-0.5*(RotateGray_lNewHeight-1)*RotateGray_fCosa+0.5*(height-1));
     memset(RotateGray_temp,(unsigned char)0,RotateGray_lNewHeight*RotateGray_lNewWidth*1) and skip ;
     RotateGray_i:=0;
     
     while(RotateGray_i<RotateGray_lNewHeight)
     {
         RotateGray_j:=0;
         
         while(RotateGray_j<RotateGray_lNewWidth)
         {
             RotateGray_i0:=(int)(-((float)RotateGray_j)*RotateGray_fSina+((float)RotateGray_i)*RotateGray_fCosa+RotateGray_f2+0.5);
             RotateGray_j0:=(int)(((float)RotateGray_j)*RotateGray_fCosa+((float)RotateGray_i)*RotateGray_fSina+RotateGray_f1+0.5);
             if((RotateGray_j0>=0) AND (RotateGray_j0<width) AND (RotateGray_i0>=0) AND (RotateGray_i0<height)) then 
             {
                 * (RotateGray_temp+RotateGray_lNewWidth*RotateGray_i+RotateGray_j):=* (image+width*RotateGray_i0+RotateGray_j0)
                 
             }
             else
             {
                 * (RotateGray_temp+RotateGray_lNewWidth*RotateGray_i+RotateGray_j):=0
             };
             RotateGray_j:=RotateGray_j+1
             
         };
         RotateGray_i:=RotateGray_i+1
         
     };
     RotateGray_ang:=hough(RotateGray_temp,RotateGray_lNewWidth,RotateGray_lNewHeight,RValue);
     free(RotateGray_temp) and skip;
     RotateGray_temp:=NULL
     )
     }; 
  function xuanzhuan ( Bmp1 *img1 )
 {
     frame(xuanzhuan_lwidth,xuanzhuan_lheight,xuanzhuan_p) and ( 
     int xuanzhuan_lwidth<==0,xuanzhuan_lheight<==0 and skip;
     unsigned char *xuanzhuan_p and skip;
     xuanzhuan_p:=RotateRGB(img1->image,img1->ang,img1->width,img1->height,&xuanzhuan_lwidth,&xuanzhuan_lheight,RValue);
     img1->width:=xuanzhuan_lwidth;
     img1->height:=xuanzhuan_lheight;
     free(img1->image) and skip;
     img1->image:=NULL;
     img1->image:=xuanzhuan_p
     )
     }; 
  function myMalloc ( int num,unsigned char *bmp,int type,char* RValue )
 {
     frame(myMalloc_p,return) and ( 
     int return<==0 and skip;
     unsigned char *myMalloc_p and skip;
     myMalloc_p:=(unsigned char *)malloc(num*sizeof(unsigned char));
     if(myMalloc_p=NULL) then 
     {
         exit<==0 and skip 
     }
     else 
     {
          skip 
     };
     if(type=0) then 
     {
         memset(myMalloc_p,0,1*num) and skip
     }
     else 
     {
          skip 
     };
     if(type=1) then 
     {
         memset(myMalloc_p,255,1*num) and skip
     }
     else 
     {
          skip 
     };
     if(type=2) then 
     {
         memcpy(myMalloc_p,bmp,1*num) and skip
     }
     else 
     {
          skip 
     };
     return<==1 and RValue:=myMalloc_p;
     skip
     )
     }; 
  function changeRGB ( unsigned char *srcBmp,int width,int height,int *lwidth,int *lheight,float f,char* RValue )
 {
     frame(changeRGB_i,changeRGB_j,changeRGB_k,changeRGB_i0,changeRGB_j0,changeRGB_m,changeRGB_n,changeRGB_nwidth,changeRGB_nheight,changeRGB_temp,return) and ( 
     int return<==0 and skip;
     int changeRGB_i,changeRGB_j,changeRGB_k,changeRGB_i0,changeRGB_j0,changeRGB_m,changeRGB_n and skip;
     int changeRGB_nwidth<==(int)(f*width+0.5) and skip;
     int changeRGB_nheight<==(int)(f*height+0.5) and skip;
     unsigned char *changeRGB_temp and skip;
	 //output("yubin303030\n") and skip;
     //changeRGB_temp:=myMalloc(changeRGB_nwidth*changeRGB_nheight,0,0,RValue);
	 changeRGB_temp:=(unsigned char *)malloc(changeRGB_nwidth*changeRGB_nheight*sizeof(unsigned char));
     changeRGB_i:=0;
     
     while(changeRGB_i<changeRGB_nheight)
     {
         changeRGB_m:=0 ; changeRGB_j:=0;
         while(changeRGB_j<changeRGB_nwidth)
         {
             changeRGB_i0:=(unsigned int)(changeRGB_i/ f+0.5);
             changeRGB_j0:=(unsigned int)(changeRGB_j/ f+0.5);
             changeRGB_n:=changeRGB_i0*width*3+changeRGB_j0*3;
             changeRGB_k:=changeRGB_nwidth*changeRGB_i*3+changeRGB_m;
             if((changeRGB_j0>=0) AND (changeRGB_j0<width) AND (changeRGB_i0>=0) AND (changeRGB_i0<height)) then 
             {
                 * (changeRGB_temp+changeRGB_k+1):=* (srcBmp+changeRGB_n+1);
                 * (changeRGB_temp+changeRGB_k+2):=* (srcBmp+changeRGB_n+2);
                 * (changeRGB_temp+changeRGB_k):=* (srcBmp+changeRGB_n)
                 
             }
             else
             {
                 * (changeRGB_temp+changeRGB_k+1):=0;
                 * (changeRGB_temp+changeRGB_k+2):=0;
                 * (changeRGB_temp+changeRGB_k):=0
             };
             changeRGB_m:=changeRGB_m+3 ; changeRGB_j:=changeRGB_j+1
             
         };
         changeRGB_i:=changeRGB_i+1
         
     };
     * lwidth:=changeRGB_nwidth;
     * lheight:=changeRGB_nheight;
     return<==1 and RValue:=changeRGB_temp;
     skip
     )
     }; 
  function guiyiRGB ( Bmp1 *img1 )
 {
     frame(guiyiRGB_nwidth,guiyiRGB_nheight,guiyiRGB_m,guiyiRGB_q) and ( 
     int guiyiRGB_nwidth<==0,guiyiRGB_nheight<==0 and skip;
     float guiyiRGB_m and skip;
     unsigned char *guiyiRGB_q and skip;
     guiyiRGB_m:=1;
     if(img1->width<200) then 
     {
         guiyiRGB_m:=(float)200/ img1->width;
         guiyiRGB_q:=changeRGB(img1->image,img1->width,img1->height,&guiyiRGB_nwidth,&guiyiRGB_nheight,guiyiRGB_m,RValue);
         img1->width:=guiyiRGB_nwidth;
         img1->height:=guiyiRGB_nheight;
         free(img1->image) and skip;
         img1->image:=NULL;
         img1->image:=guiyiRGB_q
         
     }
     else 
     {
          skip 
     }
     )
     }; 
  function outtext ( Bmp1 img1,int x,int y )
 {
     frame(outtext_table,outtext_i) and ( 
     char *outtext_table[]<=={"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","京","冀","津","晋","蒙","辽","吉","黑","沪","苏","浙","皖","闽","赣","鲁","豫","鄂","湘","粤","桂","琼","渝","川","贵","云","藏","陕","甘","青","宁","新"} and skip;
     int outtext_i and skip;
     output ("\n\n\n\n\n\n\n\n") and skip;
     output ("\n        The Car Id Is\n") and skip;
     output ("\n") and skip;
     outtext_i:=0;
     
     while(outtext_i<7)
     {
         output ("   ") and skip;
         //output (outtext_table[img1.string$[outtext_i]]) and skip;
         outtext_i:=outtext_i+1
         
     };
     output ("\n") and skip;
     output ("\n   This is designed by liujia\n") and skip;
     output ("\n\n\n\n\n\n\n\n") and skip
     )
     }; 
  function RotateRGB ( unsigned char *image,float iRotateAngle,int width,int height,int *lwidth,int *lheight,char* RValue )
 {
     frame(RotateRGB_temp,RotateRGB_i,RotateRGB_j,RotateRGB_m,RotateRGB_n,RotateRGB_lNewWidth,RotateRGB_lNewHeight,RotateRGB_i0,RotateRGB_j0,RotateRGB_fRotateAngle,RotateRGB_fSina,RotateRGB_fCosa,RotateRGB_fSrcX1,RotateRGB_fSrcY1,RotateRGB_fSrcX2,RotateRGB_fSrcY2,RotateRGB_fSrcX3,RotateRGB_fSrcY3,RotateRGB_fSrcX4,RotateRGB_fSrcY4,RotateRGB_fDstX1,RotateRGB_fDstY1,RotateRGB_fDstX2,RotateRGB_fDstY2,RotateRGB_fDstX3,RotateRGB_fDstY3,RotateRGB_fDstX4,RotateRGB_fDstY4,RotateRGB_f1,RotateRGB_f2,return) and (
     int return<==0 and skip;
     unsigned char *RotateRGB_temp and skip;
     int RotateRGB_i,RotateRGB_j,RotateRGB_m,RotateRGB_n,RotateRGB_lNewWidth,RotateRGB_lNewHeight,RotateRGB_i0,RotateRGB_j0 and skip;
     float RotateRGB_fRotateAngle and skip;
     float RotateRGB_fSina,RotateRGB_fCosa and skip;
     float RotateRGB_fSrcX1,RotateRGB_fSrcY1,RotateRGB_fSrcX2,RotateRGB_fSrcY2,RotateRGB_fSrcX3,RotateRGB_fSrcY3,RotateRGB_fSrcX4,RotateRGB_fSrcY4 and skip;
     float RotateRGB_fDstX1,RotateRGB_fDstY1,RotateRGB_fDstX2,RotateRGB_fDstY2,RotateRGB_fDstX3,RotateRGB_fDstY3,RotateRGB_fDstX4,RotateRGB_fDstY4 and skip;
     float RotateRGB_f1,RotateRGB_f2 and skip;
     RotateRGB_fRotateAngle:=(float)(iRotateAngle*3.14/ 180.0);
     RotateRGB_fSina:=(float)sin((float)RotateRGB_fRotateAngle);
     RotateRGB_fCosa:=(float)cos((float)RotateRGB_fRotateAngle);
     RotateRGB_fSrcX1:=(float)(-(width-1)/ 2);
     RotateRGB_fSrcY1:=(float)((height-1)/ 2);
     RotateRGB_fSrcX2:=(float)((width-1)/ 2);
     RotateRGB_fSrcY2:=(float)((height-1)/ 2);
     RotateRGB_fSrcX3:=(float)(-(width-1)/ 2);
     RotateRGB_fSrcY3:=(float)(-(height-1)/ 2);
     RotateRGB_fSrcX4:=(float)((width-1)/ 2);
     RotateRGB_fSrcY4:=(float)(-(height-1)/ 2);
     RotateRGB_fDstX1:=RotateRGB_fCosa*RotateRGB_fSrcX1+RotateRGB_fSina*RotateRGB_fSrcY1;
     RotateRGB_fDstY1:=-RotateRGB_fSina*RotateRGB_fSrcX1+RotateRGB_fCosa*RotateRGB_fSrcY1;
     RotateRGB_fDstX2:=RotateRGB_fCosa*RotateRGB_fSrcX2+RotateRGB_fSina*RotateRGB_fSrcY2;
     RotateRGB_fDstY2:=-RotateRGB_fSina*RotateRGB_fSrcX2+RotateRGB_fCosa*RotateRGB_fSrcY2;
     RotateRGB_fDstX3:=RotateRGB_fCosa*RotateRGB_fSrcX3+RotateRGB_fSina*RotateRGB_fSrcY3;
     RotateRGB_fDstY3:=-RotateRGB_fSina*RotateRGB_fSrcX3+RotateRGB_fCosa*RotateRGB_fSrcY3;
     RotateRGB_fDstX4:=RotateRGB_fCosa*RotateRGB_fSrcX4+RotateRGB_fSina*RotateRGB_fSrcY4;
     RotateRGB_fDstY4:=-RotateRGB_fSina*RotateRGB_fSrcX4+RotateRGB_fCosa*RotateRGB_fSrcY4;
     RotateRGB_lNewWidth:=(int)((( if(((fabs(RotateRGB_fDstX4-RotateRGB_fDstX1))>(fabs(RotateRGB_fDstX3-RotateRGB_fDstX2)))) then (fabs(RotateRGB_fDstX4-RotateRGB_fDstX1)) else (fabs(RotateRGB_fDstX3-RotateRGB_fDstX2))))+0.5);
     RotateRGB_lNewHeight:=(int)((( if(((fabs(RotateRGB_fDstY4-RotateRGB_fDstY1))>(fabs(RotateRGB_fDstY3-RotateRGB_fDstY2)))) then (fabs(RotateRGB_fDstY4-RotateRGB_fDstY1)) else (fabs(RotateRGB_fDstY3-RotateRGB_fDstY2))))+0.5);
	 RotateRGB_temp:=(unsigned char *)malloc(RotateRGB_lNewHeight*RotateRGB_lNewWidth*3*sizeof(unsigned char));
     RotateRGB_f1:=(float)(-0.5*(RotateRGB_lNewWidth-1)*RotateRGB_fCosa-0.5*(RotateRGB_lNewHeight-1)*RotateRGB_fSina+0.5*(width-1));
     RotateRGB_f2:=(float)(0.5*(RotateRGB_lNewWidth-1)*RotateRGB_fSina-0.5*(RotateRGB_lNewHeight-1)*RotateRGB_fCosa+0.5*(height-1));
     RotateRGB_i:=0;
     
	 //output(RotateRGB_fRotateAngle," ",RotateRGB_fSina," ",RotateRGB_fCosa," ",RotateRGB_fSrcX1," ",RotateRGB_fSrcY1," ",RotateRGB_fSrcX2,"\n") and skip;
	 //output(RotateRGB_fSrcY2," ",RotateRGB_fSrcX3," ",RotateRGB_fSrcY3," ",RotateRGB_fSrcX4," ",RotateRGB_fSrcY4," ",RotateRGB_fDstX1,"\n ") and skip;
	 //output(RotateRGB_fDstY1," ",RotateRGB_fDstX2," ",RotateRGB_fDstY2," ",RotateRGB_fDstX3," ",RotateRGB_fDstY3," ",RotateRGB_fDstX4," \n") and skip;
	 //output(RotateRGB_fDstY4," ",RotateRGB_lNewWidth," ",RotateRGB_lNewHeight," ",RotateRGB_temp," ",RotateRGB_f1," ",RotateRGB_f2,"\n ") and skip;
     while(RotateRGB_i<RotateRGB_lNewHeight)
     {
         RotateRGB_m:=0 ; RotateRGB_j:=0;
         while(RotateRGB_j<RotateRGB_lNewWidth)
         {
             RotateRGB_i0:=(int)(-((float)RotateRGB_j)*RotateRGB_fSina+((float)RotateRGB_i)*RotateRGB_fCosa+RotateRGB_f2+0.5);
             RotateRGB_j0:=(int)(((float)RotateRGB_j)*RotateRGB_fCosa+((float)RotateRGB_i)*RotateRGB_fSina+RotateRGB_f1+0.5);
             if((RotateRGB_j0>=0) AND (RotateRGB_j0<width) AND (RotateRGB_i0>=0) AND (RotateRGB_i0<height)) then 
             {
                 RotateRGB_n:=RotateRGB_i0*width*3+RotateRGB_j0*3;
                 * (RotateRGB_temp+RotateRGB_lNewWidth*RotateRGB_i*3+RotateRGB_m+1):=* (image+RotateRGB_n+1);
                 * (RotateRGB_temp+RotateRGB_lNewWidth*RotateRGB_i*3+RotateRGB_m+2):=* (image+RotateRGB_n+2);
                 * (RotateRGB_temp+RotateRGB_lNewWidth*RotateRGB_i*3+RotateRGB_m):=* (image+RotateRGB_n)
                 
             }
             else
             {
                 * (RotateRGB_temp+RotateRGB_lNewWidth*RotateRGB_i*3+RotateRGB_m+1):=0;
                 * (RotateRGB_temp+RotateRGB_lNewWidth*RotateRGB_i*3+RotateRGB_m+2):=0;
                 * (RotateRGB_temp+RotateRGB_lNewWidth*RotateRGB_i*3+RotateRGB_m):=0
             };
             RotateRGB_m:=RotateRGB_m+3 ; RotateRGB_j:=RotateRGB_j+1
             
         };
         RotateRGB_i:=RotateRGB_i+1
         
     };
     * lwidth:=RotateRGB_lNewWidth;
     * lheight:=RotateRGB_lNewHeight;
     return<==1 and RValue:=RotateRGB_temp;
     skip
     )
 };
  main_1(RValue)
 )
