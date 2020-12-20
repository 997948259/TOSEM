#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "cv.h"
//#include "highgui.h"
#include "math.h"
#define pi 3.14
#define RADIAN(angle) ((angle)*3.14/180.0)

#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef unsigned char       byte;
//#define MAX(a,b,c) a>(b>c?b:c)?a:
struct BMP_img
{
    WORD  bfType;
    DWORD size;
	DWORD reser;
	DWORD header_length;
    DWORD infoheader_length;
	DWORD width;
	DWORD height;
	WORD  biplanes;
	WORD  bmp_type;        /* 8bit 24bit; */
	DWORD compres;
	DWORD datasize;
    DWORD bixpm;
	DWORD biypm;
	DWORD clrused;
	DWORD  relclrused;
    BYTE *image;
    byte *header_info;
	DWORD lineBytes;

};

struct Bmp1{
	DWORD width;
	DWORD height;
	byte strc[67][800];
	BYTE *image;
	int p1[15];//xl
	int p2[15];//xr
	int p3[15];//yu
	int p4[15];//yd
	int up;
	int down;
    byte strr[7][2500];
	byte string[7];
	float ang;//倾斜角度
};

struct HSV{
  float H;
  float S;
  int V;
};
 struct RGB{
	 byte bitb;
	 byte bitg;
	 byte bitr;
	 byte  re;
              };
void read_img(FILE *infile, struct BMP_img *img);
//void read_img(FILE *infile, struct BMP_img *img);

void displaytwo(struct Bmp1 img,byte *srcBmp,byte *dstBmp,int yuzhi);
unsigned char  myGetMedianNum(unsigned char * bArray, int iFilterLen);
void cuizhitouying(struct Bmp1 *img,byte *temp);
void sob(byte *srcBmp,int width,int height,int type);
void shuipingtouying(struct Bmp1 *img,byte *temp);
//void display(BMP_img img,byte *temp);

void grayScale(struct BMP_img img,byte *srcBmp,byte *dstBmp);
void junheng(struct BMP_img img,byte *srcBmp,byte *dstBmp);
void CutBmp(struct BMP_img img,struct Bmp1 *img1,int HL,int HH,int VL,int VH);
void CutBmp1(struct Bmp1 *img1,int HL,int HH,int VL,int VH);
void testhsv(float h,float s,float v,byte r,byte g,byte b);
void hsvzation(byte *image,struct HSV *hsv,int width,int height);
void location(byte *image,int width,int height,int yuzhi,int *HL,int *HH,int *VL,int *VH);
void huidu(struct Bmp1 img,byte *srcBmp,byte *dstBmp);
void bmptwo(struct Bmp1 img,byte *srcBmp,byte *dstBmp,byte yuzhi);
void Thiningtest(struct BMP_img img,byte *srcBmp,byte *dstBmp);
void Thining(byte *srcBmp,int width,int height);
void ThinnerRosenfeld(void *image, unsigned long lx, unsigned long ly);
void delpoint(byte *dst,int width,int height,int yuzhi);
void Erosion(byte *image,int width,int height,int type,int num);
void deljunzao(byte *dst,int width,int height,int yuzhi);
void pingjun(byte *dst,int width,int height);
void changeGray(byte *srcBmp,byte *dstBmp,int width,int height,int nWidth,int nHeight);
byte *changeRGB(byte *srcBmp,int width,int height,int *lwidth,int *lheight,float f);
void strBmp(struct Bmp1 *img,byte *temp);
void guiyi(struct Bmp1 *img);
void readstr(FILE *infile, byte *srcBmp);
char *myitoa(int num, char *str, int radix);   // 整数字符串转换。
void readmoban(char *path,struct Bmp1 *img2);
void writebmp(const char *path,const char *name,byte *temp);
int cmpstr(byte *src,byte *moban);
void Hough(struct Bmp1 *img);
void strout(struct Bmp1 *img);
void edgesob8(byte *image,int width,int height);
void edgesob4(byte *image,int width,int height);//4邻域
int hough(byte *srcBmp,int width,int height);
void Dilation(byte *image,int width,int height,int type,int num);
void RotateGray(byte *image,int width,int height, float iRotateAngle);
byte *RotateRGB(byte *image, float iRotateAngle,int width,int height,int *lwidth,int *lheight);
void xuanzhuan(struct Bmp1 *img1);
byte *myMalloc(int num,const byte *bmp,int type);
void guiyiRGB(struct Bmp1 *img1);
void outtext(struct Bmp1 img1,int x,int y);
int calstr(byte *srcBmp);

int main()
{
   //	while(1)
//	{

	
	int HL=0,HH=0,VH=0,VL=0;
	struct BMP_img img;
	struct Bmp1 img1;
	FILE *f;
    byte *temp,*temp1;
    //char path[80]="C:\\test\\2.bmp";
    char path1[80]="/home/ictt1/big_example/test/moban";
	char path[80]="/home/ictt1/big_example/test/2.bmp";
    char path3[40];
    printf("Please Input Path\n");
  
    //scanf("%s",path3);
    //strcpy(path,path3);
    printf("the path is :%s\n",path);

   // char path1[80]="//mnt//arm1//test//moban//";
    //char path[80]="C:\\Documents and Settings\\liujia\\桌面\\test\\example06.bmp";
    //char path1[80]="C:\\Documents and Settings\\liujia\\桌面\\test\\moban\\";



    if((f=fopen(path,"rb"))==NULL)
	{
    	printf( "\nCan not open the path: %s \n", path);
	}
	read_img(f, &img);
	fclose(f);
	          temp=myMalloc(img.height*img.width*4,temp,0);//(byte *)malloc(sizeof(byte)*img.height*img.width*4);// byte *temp2=(byte *)malloc(sizeof(byte)*img.height*img.width);
	          temp1=myMalloc(img.height*img.width*4,temp,0);
	 location(img.image,img.width,img.height,15,&HL,&HH,&VL,&VH);
	 	CutBmp(img,&img1,HL,HH,VL,VH);
	 		Hough(&img1);
	 		xuanzhuan(&img1);
	location(img1.image,img1.width,img1.height,0,&HL,&HH,&VL,&VH);
	CutBmp1(&img1,HL,HH,VL,VH);
	huidu(img1,img1.image,temp);
	displaytwo(img1,temp,temp1,30);
    delpoint(temp1,img1.width,img1.height,3);
    shuipingtouying(&img1,temp1);
	delpoint(temp1,img1.width,img1.height,2);
    cuizhitouying(&img1,temp1);
    memset(temp,0,sizeof(char)*img1.width*img1.height);
	strBmp(&img1,temp1);//把车牌字符放到数组里面
    guiyi(&img1);
    readmoban(path1,&img1);
	strout(&img1);
    outtext(img1,0,600);
    free(temp1);
    free(temp);
    while(1)
    {
       int iiiii;
       iiiii=iiiii+1;
    }
//	getch();
//}
	return 0;
  }
void read_img(FILE *infile, struct BMP_img *img)
{

	DWORD iii,j,l,bitcolor;
	DWORD line24;
	DWORD line8;

    struct RGB *bitmap;
	fread(&img->bfType,sizeof(WORD),1,infile);//printf("\n打开的图为 %d",img->bfType);
	fread(&img->size,sizeof(DWORD),1,infile);     //        printf("\nBMP size             :%l",img->size);
	fread(&img->reser,sizeof(DWORD),1,infile);//printf("\n保留位:");
	fread(&img->header_length,sizeof(DWORD),1,infile); //printf("\nheader length    :%l",img->header_length);
	fread(&img->infoheader_length,sizeof(DWORD),1,infile);
	fread(&img->width, sizeof(DWORD), 1, infile);
	fread(&img->height, sizeof(DWORD), 1, infile);     //printf( "\nwidth   :%l\n  height  :%l ", img->width, img->height);
	fread(&img->biplanes, sizeof(WORD), 1, infile);
	fread(&img->bmp_type, sizeof(WORD), 1, infile);  // printf("\nBMP Tpye             :%l ", img->bmp_type);
	fread(&img->compres, sizeof(DWORD), 1, infile);    //if(img->compres==0) {printf("\nbmp图片为非压缩!");}printf(" ");
	fread(&img->datasize, sizeof(DWORD), 1, infile);//printf("\nBMP Data Size        :%l ",img->datasize);
	fread(&img->bixpm, sizeof(DWORD), 1, infile);
	fread(&img->biypm, sizeof(DWORD), 1, infile);
	fread(&img->clrused, sizeof(DWORD), 1, infile);    //printf("\n实际使用颜色数=%d ",img->clrused);printf(" ");
	fread(&img->relclrused, sizeof(DWORD), 1, infile);

	img->lineBytes=(img->width*img->bmp_type+31)/32*4;
	                                                                                                              //printf("\nLineBytes            :%l\n",img->lineBytes);

	line24=(img->width*24+31)/32*4;

	   line8=(img->width*8+31)/32*4;
	 if(img->bmp_type==1){bitcolor=2;printf("不能读取退出");}
	 if(img->bmp_type==4){bitcolor=16;printf("不能读取退出");}
	 if(img->bmp_type==8)
	 {
		 byte *temp=(BYTE*)malloc(img->height*line8*sizeof(BYTE));
		 memset(temp,0x00,img->height*img->lineBytes*sizeof(BYTE));

		 bitcolor=256;
		 bitmap=(struct RGB *)calloc(bitcolor,sizeof(struct RGB));
		 img->image=(unsigned char *)malloc(sizeof(unsigned char)*(line8*img->height));
		 memset(img->image,0x00,sizeof(byte)*line8*img->height);

		 if(img->image==NULL) {fprintf(stderr, "\n Allocation error for temp in read_bmp() \n");}

		 fseek(infile,0x36, SEEK_SET);
		 fread(bitmap,sizeof(struct RGB),bitcolor,infile);
		 fseek(infile, img->header_length, SEEK_SET);
		 //fread(temp, sizeof(unsigned char),lineBytes*img->height, infile);
		 fread(temp, img->lineBytes*img->height,1, infile);
		 if(temp==NULL)printf("\n读取失败\n");

		 for(iii=0;iii<img->height;iii++)
		 {
			 for(j=0;j<img->width;j++)
			 {
				 img->image[iii*img->width+j]=(byte)(0.299*bitmap[temp[iii*line8+j]].bitb+0.578*bitmap[temp[iii*line8+j]].bitg+0.114*bitmap[temp[iii*line8+j]].bitr);
			//	putpixel(j,img->height-i,RGB(img->image[i*img->width+j],img->image[i*img->width+j],img->image[i*img->width+j]));

			 }
		 }
		 free(temp);
		 temp=NULL;
	 }
	 if(img->bmp_type==24)
	 {
		 byte *temp=(byte *)malloc(sizeof(byte)*img->height*img->lineBytes);
               //  if(temp==NULL)
		//	 exit(-1);
		 img->image=(unsigned char *)malloc(sizeof(unsigned char)*((line24)*img->height));
		 if(img->image==NULL) fprintf(stderr, "\n Allocation error for temp in read_bmp() \n");
		 fseek(infile, img->header_length, SEEK_SET);
		 fread(temp, sizeof(unsigned char), (img->lineBytes)*img->height, infile);
	    // byte *temp=(byte *)malloc(sizeof(byte)*img->lineBytes*img->height)

		 for(iii=0;iii<img->height;iii++)
		 {
			l=0;
			 for(j=0;j<img->width*3;j+=3)
			{
				//l=(img->height-i-1)*img->lineBytes+j;
				 l=(img->height-iii-1)*img->width*3+j;
                      img->image[l+2]=*(temp+iii*img->lineBytes+j+2);
					  img->image[l+1]=*(temp+iii*img->lineBytes+j+1);
					  img->image[l]=*(temp+iii*img->lineBytes+j);
			}
		 }

	free(temp);
	temp=NULL;
	 }
}

void readstr(FILE *infile, byte *srcBmp)
{

	int width,height, headlength;
	int i,j,bitcolor,line8;
	byte *temp;
	byte temp1;
	struct RGB *bitmap;

	width=20;
	height=40;
	headlength=1078;

	line8=(width*8+31)/32*4;

	temp=(BYTE*)malloc(height*line8*sizeof(BYTE));
    memset(temp,0x00,height*line8*sizeof(BYTE));
	     bitcolor=256;
    bitmap=(struct RGB *)malloc(sizeof(struct RGB)*bitcolor);
		 fseek(infile,0x36, SEEK_SET);
		 fread(bitmap,sizeof(struct RGB),bitcolor,infile);
		 fseek(infile, headlength, SEEK_SET);
		 fread(temp, line8*height,1, infile);
		 if(temp==NULL){printf("\n读取失败\n"); }

		 for(i=0;i<height;i++)
		 {
			 for(j=0;j<width;j++)
			 {

				temp1=temp[i*line8+j];
				if(temp1>=150)
					temp1=255;
				else temp1=0;
				 srcBmp[(height-i-1)*width+j]=temp1;//(byte)(0.299*bitmap[temp[i*line8+j]].bitb+0.578*bitmap[temp[i*line8+j]].bitg+0.114*bitmap[temp[i*line8+j]].bitr);

			 }
		 }
		 free(temp);
		 temp=NULL;
 }

void grayScale(struct BMP_img img,byte *srcBmp,byte *dstBmp)
{
	int i,j,temp1,n;
	float gray;
	temp1=img.width*3;
	srcBmp=img.image;
	for(i=0;i<img.height;i++)
    {
        for(j=0,n=0;j<img.width;n+=3,j++)

        {
			gray=(*(srcBmp+i*img.lineBytes+n+2)*0.299)+(*(srcBmp+i*img.lineBytes+n+1)*0.578)+(*(srcBmp+i*img.lineBytes+n)*0.114);
			dstBmp[i*img.lineBytes+n]=(byte)(gray+0.5);
			dstBmp[i*img.lineBytes+n+1]=(byte)(gray+0.5);
			dstBmp[i*img.lineBytes+n+2]=(byte)(gray+0.5);

		}
    }
}
void huidu(struct Bmp1 img,byte *srcBmp,byte *dstBmp)
{
	int i,j,n;
	float gray;
	srcBmp=img.image;
	for(i=0;i<img.height;i++)
    {
        for(j=0,n=0;j<img.width;n+=3,j++)

        {
			gray=(*(srcBmp+i*img.width*3+n+2)*0.299)+(*(srcBmp+i*img.width*3+n+1)*0.578)+(*(srcBmp+i*img.width*3+n)*0.114);
			dstBmp[i*img.width+j]=(byte)(gray+0.5);


		}
    }
}
void hsvzation(byte *image,struct HSV *hsv,int width,int height)
{
	int i,j,k;
	float min,max,delta,tmp;//h,s,v,m,n;
	//int lineBytes=(width*24+31)/32*4;
	byte r,g,b;
	for(i=0;i<height;i++)
	{
		for(k=0,j=0;j<width*3;k++,j+=3)
		{
			g=image[i*width*3+j+1];
			b=image[i*width*3+j];
			r=image[i*width*3+j+2];

			tmp=min(r,g);
			min=min(tmp,b);
			tmp=max(r,g);
			max=max(tmp,b);
			hsv[i*width+k].V=(int)max;
			delta=max-min;
			if(delta==0)
			{
				hsv[i*width+k].H=0;
				continue;
				//value=0;
				//return value;
			}
			if(max!=0)
			{

				//tmp=delta/max;
				hsv[i*width+k].S=delta/max;//tmp;
			}
			else
			{

				hsv[i*width+k].S=0;
				hsv[i*width+k].H=0;
				continue;

			}
			if(r==max)
			{
				// tmp=(g-b)/delta;
				hsv[i*width+k].H=(g-b)/delta;//tmp;
			}
			else if(g==max)
				hsv[i*width+k].H=2+(b-r);
			else
			{
				//tmp=4+(r-g)/delta;
				hsv[i*width+k].H=4+(r-g)/delta;//tmp;
			}
			hsv[i*width+k].H*=60;
			if(hsv[i*width+k].H<0)
				hsv[i*width+k].H+=360;
			//value=(int)(h+0.5);



		}
	}


}

void location(byte *image,int width,int height,int yuzhi,int *HL,int *HH,int *VL,int *VH)
{
    int i,j,n,maxnum,flag=0;
	struct HSV *hsv;
	int temp[2000]={0};
	byte *temp1;
    hsv=(struct HSV *)malloc(sizeof(struct HSV)*width*height);
    hsvzation(image,hsv,width,height);

	temp1=(byte *)malloc(sizeof(byte)*height*width);

	//int lineBytes=(width*24+31)/32*4;
		   for(i=0;i<height;i++)
		   {
			   for(j=0,n=0;j<width;n+=3,j++)
				{
				   if((hsv[i*width+j].H<220.0)&&(hsv[i*width+j].H>180.0)&&(hsv[i*width+j].V<250)&&(hsv[i*width+j].S>0.6))
				   {

					   temp1[i*width+j]=255;
					   //putpixel(j,i,RGB(255,255,255));
				   }
				   else
				   {
					   temp1[i*width+j]=0;
					   //putpixel(j,i,RGB(0,0,0));
				   }
			   }
		   }
		   for(i=0;i<height;i++)
		   {
			   for(j=0;j<width;j++)
			   {
				   if(temp1[i*width+j]==255)
				   {
					  temp[i]++;

				   }
			   }
		   }
		     edgesob8(temp1,width,height);

		   maxnum=temp[0];
		   for(i=1;i<height;i++)
		   {

			   if(temp[i]>maxnum)
				   maxnum=temp[i];
		   }
		   maxnum=maxnum/3;
		   for(i=0;i<height;i++)
		   {
			   if(flag==0)
			   {
                 if(temp[i]>maxnum)
				 {
				  *HL=i-yuzhi;

				   flag=1;
				 }
			   }
			   if(flag==1)
			   {

				   if(temp[i]==0)
				   {
					   *HH=i+yuzhi;

					   break;
				   }
			   }
		   }


           memset(temp,0x00,sizeof(int)*width);
		   for(i=0;i<width;i++)
		   {
			   for(j=0;j<height;j++)
			   {
				   if(temp1[j*width+i]==255)
				   {
					   temp[i]++;

				   }
			   }
		   }
		   flag=0;
		   maxnum=temp[0];



		   for(i=1;i<width;i++)
		   {

			   if(temp[i]>maxnum)
				   maxnum=temp[i];
		   }
		   maxnum=maxnum/3;
		   for(i=0;i<width;i++)
		   {
			   if(temp[i]>maxnum)
				   {
					   *VL=i-yuzhi;

					  break;
				   }
		   }

		   for(i=width;i>*VL;i--)
		   {
			    if(temp[i]>maxnum)
				   {
					   *VH=i+yuzhi;

					   break;
				   }

		   }
		   free(temp1);
		   temp1=NULL;
		   free(hsv);
}
void Hough(struct Bmp1 *img)
{
    int i,j,n;
	float ang;
	byte *temp1;
	//int temp[2000]={0};
    struct HSV *hsv=(struct HSV *)malloc(sizeof(struct HSV)*img->width*img->height);
    hsvzation(img->image,hsv,img->width,img->height);
	temp1=(byte *)malloc(sizeof(byte)*img->height*img->width);


		   for(i=0;i<img->height;i++)
		   {
			   for(j=0,n=0;j<img->width;n+=3,j++)
				{
				   if((hsv[i*img->width+j].H<220.0)&&(hsv[i*img->width+j].H>180.0)&&(hsv[i*img->width+j].V<250)&&(hsv[i*img->width+j].S>0.6))
				   {
				      temp1[i*img->width+j]=255;


				   }
				   else
				   {
					   temp1[i*img->width+j]=0;

				   }
			   }
		   }


		   Dilation(temp1,img->width,img->height,1,5);
		   sob(temp1,img->width,img->height,0);
		   ang=hough(temp1,img->width,img->height);
		  if((ang<=8)&&(ang>=1))
			   ang=ang-1;
		   if(ang>90)
		   {
			   ang=ang-180;

		   }
		   img->ang=ang;



}
void bmptwo(struct Bmp1 img,byte *srcBmp,byte *dstBmp,byte yuzhi)
{
	int i,j;
	for(i=0;i<img.height;i++)
	{
		for(j=0;j<img.width;j++)
		{
			if(srcBmp[i*img.width+j]>=yuzhi)
			{
				dstBmp[i*img.width+j]=255;
			}
			else
			{
				dstBmp[i*img.width+j]=0;


			}
		}
	 }
}
void displaytwo(struct Bmp1 img,byte *srcBmp,byte *dstBmp,int yuzhi)
{
    //int i,j,T,n,k,t,l;
	//int m;
	int totalPixels = img.width * img.height;
	int bestT = 0;


  int i,j;

	int histogramArray[256]={0};
	double densityArray[256]={0};
		double u0 = 0;
		double u1 = 0;
			double w0 = 0;
		double w1 = 0;
			double bestDeviation = 0;


	for(i=0;i<img.height;i++)
	{
		for(j=0;j<img.width;j++)
		{
		  histogramArray[srcBmp[i*img.width+j]]++;
		}
	 }
	for(i=0;i<256;i++)
	{
	densityArray[i] = histogramArray[i] * 1.0 / totalPixels;
	}
	for (i = 0; i < 256; i++)
		{
		w0 = 0;
		w1 = 0;
		for (j = 0; j <= i; j++) {
			w0 += densityArray[j];
		}
		for (j = i + 1; j < 256; j++) {
			w1 += densityArray[j];
		}
		u0 = 0;
		u1 = 0;
		for (j = 0; j <= i; j++) {
			u0 += j * densityArray[j];
		}
		for (j = i + 1; j < 256; j++) {
			u1 += j * densityArray[j];
		}
		u0 = u0 / w0;
		u1 = u1 / w1;
		if (w0 * w1 * (u0 - u1) * (u0 - u1) > bestDeviation) {
			bestT = i;
			bestDeviation = w0 * w1 * (u0 - u1) * (u0 - u1);
		}
	}
	for (i = 0; i < 256; i++) {
		histogramArray[i] = 0;
		}
	bestT=bestT+yuzhi;
	if(bestT<0)
		bestT=0;
	if(bestT>255)
		bestT=255;
	for(i=0;i<img.height;i++)
	{
		for(j=0;j<img.width;j++)
		{
			if(srcBmp[i*img.width+j]>bestT)
			{
				dstBmp[i*img.width+j]=255;

			}
			else
			{
				dstBmp[i*img.width+j]=0;


			}
		}
	 }


 }

/*************************************************************************
*
* 函数名称：
*   MedianFilter()
*
* 参数:
*   LPSTR lpDIBBits		- 指向源DIB图像指针
*   LONG  lWidth			- 源图像宽度（象素数）
*   LONG  lHeight			- 源图像高度（象素数）
*   int   iFilterH			- 滤波器的高度
*   int   iFilterW			- 滤波器的宽度
*   int   iFilterMX		- 滤波器的中心元素X坐标
*   int   iFilterMY		- 滤波器的中心元素Y坐标
*
* 返回值:
*   BOOL					- 成功返回TRUE，否则返回FALSE。
*
* 说明:
*   该函数对DIB图像进行中值滤波。
*
************************************************************************/
int myMedianFilter(struct Bmp1 img,byte *temp,int iFilterH,int iFilterW,int iFilterMX,int iFilterMY)
{


	unsigned char*	lpSrc;
	unsigned char*	lpDst;
	int lHeight=img.height;
	int lWidth=img.width;
   	unsigned char	*aValue;
	byte			*hArray;

	// 循环变量
	int	i,j,l,k;

	byte *lpNewDIBBits=(byte *)malloc(sizeof(byte)*img.height*img.width);
	if(lpNewDIBBits==NULL)
		//exit(-1);


	memcpy(lpNewDIBBits,temp, img.width * lHeight);

	hArray=(byte *)malloc(sizeof(byte)*iFilterH*iFilterW);
	aValue=(byte *)malloc(sizeof(byte)*iFilterH*iFilterW);

	for(i = iFilterMY; i < lHeight - iFilterH + iFilterMY + 1; i++)
	{
		// 列(除去边缘几列)
		for(j = iFilterMX; j < lWidth - iFilterW + iFilterMX + 1; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			lpDst = (unsigned char*)lpNewDIBBits + img.width * (lHeight - 1 - i) + j;

			// 读取滤波器数组
			for (k = 0; k < iFilterH; k++)
			{
				for (l = 0; l < iFilterW; l++)
				{
					// 指向DIB第i - iFilterMY + k行，第j - iFilterMX + l个象素的指针
					lpSrc = (unsigned char*)temp + img.width * (lHeight - 1 - i + iFilterMY - k) + j - iFilterMX + l;

					// 保存象素值
					aValue[k * iFilterW + l] = *lpSrc;
				}
			}

			// 获取中值
			* lpDst = myGetMedianNum(aValue, iFilterH * iFilterW);
		}
	}

   memcpy(temp, lpNewDIBBits, img.width * img.height);
	// 释放内存
	free(lpNewDIBBits);
	lpNewDIBBits=NULL;
    free(hArray);
	hArray=NULL;

	// 返回
	return 1;
}
/*************************************************************************
*
* 函数名称：
*   GetMedianNum()
*
* 参数:
*   unsigned char * bpArray	- 指向要获取中值的数组指针
*   int   iFilterLen			- 数组长度
*
* 返回值:
*   unsigned char      - 返回指定数组的中值。
*
* 说明:
*   该函数用冒泡法对一维数组进行排序，并返回数组元素的中值。
*
************************************************************************/

unsigned char  myGetMedianNum(unsigned char * bArray, int iFilterLen)
{
	// 循环变量
	int		i;
	int		j;

	// 中间变量
	unsigned char bTemp;

	// 用冒泡法对数组进行排序
	for (j = 0; j < iFilterLen - 1; j ++)
	{
		for (i = 0; i < iFilterLen - j - 1; i ++)
		{
			if (bArray[i] > bArray[i + 1])
			{
				// 互换
				bTemp = bArray[i];
				bArray[i] = bArray[i + 1];
				bArray[i + 1] = bTemp;
			}
		}
	}

	// 计算中值
	if ((iFilterLen & 1) > 0)
	{
		// 数组有奇数个元素，返回中间一个元素
		bTemp = bArray[(iFilterLen + 1) / 2];
	}
	else
	{
		// 数组有偶数个元素，返回中间两个元素平均值
		bTemp = (bArray[iFilterLen / 2] + bArray[iFilterLen / 2 + 1]) / 2;
	}

	// 返回中值
	return bTemp;
}
void shuipingtouying(struct Bmp1 *img,byte *dst)//得到车牌的上下边缘
{

	byte temp;
    int i,j;
	 //int *p=(int *)malloc(sizeof(int)*img.height);
	int p[500]={0};
	 memset(p,0,img->height*sizeof(int));

	 for(i=0;i<img->width;i++)
	{
      	if((dst[i]>=200)||(dst[img->width+i]>=200))
        for(j=0;j<img->height;j++)
		{
			if(dst[j*img->width+i]>=200)
                dst[j*img->width+i]=0;
			else break;
		}
	}
	for(i=0;i<img->width;i++)
	{
		if((dst[img->width*(img->height-1)+i]>=200)||(dst[img->width*(img->height-2)+i]>=200))
			for(j=img->height-1;j>0;j--)
			{
				if(dst[j*img->width+i]>=200)
					dst[j*img->width+i]=0;
				else break;
			}
	}

	 for(i=2;i<img->height-2;i++)
	{

		for(j=0;j<img->width;j++)
		{
			if(dst[i*img->width+j]>=200)
				p[i]++;

		}
	}

	 temp=0;
	 for(i=0;i<img->height;i++)
	 {
        if(p[i]>temp)
		{
		  temp=p[i];

		}

	 }

			j=temp/5;
			for(i=img->height;i>img->up;i--)
			{
				if(p[i]>j)
				{
				 img->down=i;
				 break;
				}
			//	if(i<img->height/2)
					//exit(-1);
			}


				j=temp/3;
			for(i=0;i<img->down;i++)
			{

               if(p[i]>j)
			   {
				   img->up=i;
				   break;
			   }
			//   if(i>img->height/2)
				//   exit(-1);

			}

	for(i=0;i<img->up-1;i++)
		{
		 for(j=0;j<img->width;j++)
		   {
			dst[i*img->width+j]=0;

		   }

		}
		for(i=img->height;i>img->down+1;i--)
		{
		 for(j=0;j<img->width;j++)
		   {
			dst[i*img->width+j]=0;

		   }

		}

}
void sob(byte *srcBmp,int width,int height,int type)	    //sob算子边缘检测；取出边界；
{
 int i,j,l,x,y;
// int px[6]={0};
 //int py[6]={0};
 int p1[4]={0};
 //double result;
 byte *tempy;
 byte *tempx;
 tempx=(byte *)malloc(sizeof(byte)*width*width);
 if(tempx==NULL)
	// exit(-1);
 tempy=(byte *)malloc(sizeof(byte)*width*width);
 if(tempy==NULL)
	// exit(-1);
 	for(i =1; i<height-1; i++)
		{
			for(j=1;j<width-1;j++)//由于使用3×3的模板，为防止越界，所以不处理最下边和最右边的两列像素
			{

						if(i==height-1)
							x=0,y=0;
						else if(j==width-1)
							x=0,y=0;

						else{

							p1[0] = (byte)*(srcBmp+i*width+j);
							p1[1] = (byte)*(srcBmp+i*width+j+1);
							p1[2] = (byte)*(srcBmp+(i+1)*width+j);
							p1[3] = (byte)*(srcBmp+(i+1)*width+j+1);



							x=abs(p1[0]-p1[2]); //sqrt(( p1[1] - p1[2] )*( p1[1] - p1[2] ));
							y=abs(p1[0]-p1[1]);
							if(x>0)
								x=255;
							else
								x=0;
							if(y>0)
								y=255;
							else
								 y=0;

						}


			tempx[i*width+j]=(byte)x;
			tempy[i*width+j]=(byte)y;
			}
		}
	for (i = 0; i < width; i++)
	{
		tempx[i] = 0;
		tempy[i] = 0;
		tempx[width*(height-1)+i] = 0;
		tempy[width*(height-1)+i] = 0;
	}
	for (i = 0; i < height; i++)
	{
		tempx[i*width] = 0;
		tempy[i*width] = 0;
		tempx[i*width+width-1] = 0;
		tempy[i*width+width-1] = 0;
	}
    if(type==0)
       memcpy(srcBmp,tempx,sizeof(byte)*width*height);
    if(type==1)
       memcpy(srcBmp,tempy,sizeof(byte)*width*height);
    if(type==2)
	{
      for(i=0;i<height;i++)
		  for(j=0;j<width;j++)
		  {
			  l=tempx[i*width+j]+tempy[i*height+j];
			  if(l>255)
				  l=255;
			  tempx[i*width+j]=l;
		  }
       memcpy(srcBmp,tempx,sizeof(byte)*width*height);
	}
	  free(tempx);
	  free(tempy);
	  tempx=NULL;
	  tempy=NULL;

}
void cuizhitouying(struct Bmp1 *img,byte *temp)
{


	int p3[15]={0};
    int i,j,k=0,m,num,flag;
	//img.p1[15]={0};
	//img.p2[15]={0};

      int up=0;
	  int down=0;
    int p[500]={0};

    	for(i=0;i<img->width;i++)
	{

		for(j=0;j<img->height;j++)
		{
			if(temp[j*img->width+i]==255)
			{	p[i]++;}

		}
	}

		for(i=1;i<img->width;i++)//除燥
		{
			if(p[i]>0)
			{
			 if((p[i-1]==0)&&(p[i+1]==0))
				 if(p[i]<5)
				 p[i]=0;

			}
		}
		flag=0,m=0;
		for(i=0;i<img->width;i++)
		{
			if(p[i]>0)
			{
			  flag=1;
			  m++;
			}
			if((p[i]==0)&&(flag==1))
				break;
		}


      while(1)
	  {
		 num=0;
		 flag=0;

	    for(i=0;i<img->width;i++)
		{
	      if(p[i]>1)
		  {
            if(flag==0)
			{
			   img->p1[num]=i;
			   flag=1;
			}

		 }
	     else if(p[i]==0)
		 {
		   if(flag==1)
		   {
			   img->p2[num]=i-1;
			   flag=0;
			   j=img->p2[num]-img->p1[num];
			   if(j<m/3)
			   {
				   if(p[i-1]<(img->down-img->up)/2)
				   continue;
			   }
			   num++;
		   }
		}
	   if((flag==1)&&(i==img->width-1))
	   {
		   img->p2[num]=i;
		   num++;
		   break;
	   }

	  }
      if(num==7)
		  break;
	  else if(num==8)
	  {


		  j=100;
		  for(i=0;i<num;i++)
		 {
           p3[i]=img->p2[i]-img->p1[i];
			 if(p3[i]<j)
             {
				 j=p3[i];
				 k=i;
			 }
		 }
		  for(i=k;i<=num-k;i++)
		  {
		   img->p1[i]=img->p1[i+1];
		   img->p2[i]=img->p2[i+1];
		  }
		  num--;
		  break;
	  }
	   else //(num<7)
	   {
		 for(i=0;i<img->width;i++)
           {
			   if(p[i]>0)
				   p[i]--;
		   }
	   }
	  }
	  flag=0;
	   up=0;
	   down=0;
	  up=img->up-3;
	  if(up<0)
		  up=img->up;
	  down=img->down+4;
	  if(down>img->height)
		  down=img->down;

	 for(k=0;k<7;k++)
	  {
		  for(i=up;i<=down;i++)
		  {
			  for(j=img->p1[k];j<=img->p2[k];j++)
			  {
				  if(temp[i*img->width+j]==255)
				  {
                     img->p3[k]=i;
					 flag=1;
					 break;
				  }
			  }
			  if(flag==1)
			  {
				  flag=0;
				  break;
			  }
		  }
		  for(i=down;i>=up;i--)
		  {
			  for(j=img->p1[k];j<=img->p2[k];j++)
			  {
				  if(temp[i*img->width+j]==255)
				  {
					  img->p4[k]=i;
					  flag=1;
					  break;
				  }
			  }
			  if(flag==1)
			  {
				  flag=0;
				  break;
			  }
		  }
	  }
 }









void junheng(struct BMP_img img,byte *srcBmp,byte *dstBmp)
{
	 int n[256]={0};
	 double p[256]={0};
     double c[256]={0};
	 int height=img.height;
	 int width=img.width;
     int totalPixels = width * height;
//	 double gray=0;
     int i,j,max,min,l;
	 for(i=0;i<img.height;i++)
	 {
		 for(j=0,l=0;j<img.width;l+=3,j++)

		 {
			 //gray=(*(srcBmp+i*img.lineBytes+l+2)*0.299)+(*(srcBmp+i*img.lineBytes+l+1)*0.578)+(*(srcBmp+i*img.lineBytes+l)*0.114);

			 srcBmp[i*img.width+j]=*(srcBmp+i*img.lineBytes+l);
		 }
    }
	 for(i=0;i<img.height;i++)
	 {
		 for(j=0;j<img.width;j++)

		 {

			 n[srcBmp[i*width+j]]++;
		 }
	 }
	 for(i=0;i<256;i++){
		 p[i] = n[i]*1.0/totalPixels;
	 }

	 for(i=0;i<256;i++){
		 for(j=0;j<=i;j++){
			 c[i]+=p[j];	//累计直方图
		 }
	 }

	 max=min=srcBmp[0];

	 for(i=0;i<img.height;i++)
	 {
		 for(j=0;j<img.width;j++)

		 {
			 n[srcBmp[i*width+j]]++;
		 }
	 }
	 for(i=0;i<height;i++)
	 {
		 for(j=0;j<width;j++)
		 {
			 if(max<srcBmp[i*width+j])
			 {max=srcBmp[i*width+j];}
			 else if(min>srcBmp[i*width+j]){min=srcBmp[i*width+j];}
		 }
	 }

	 for(i=0;i<height;i++){
		 for(j=0;j<width;j++){
			 dstBmp[i*img.lineBytes+j*3]=(byte)(c[srcBmp[i*width+j]]*(max-min)+min+0.5);
			 dstBmp[i*img.lineBytes+j*3+1]=(byte)(c[srcBmp[i*width+j]]*(max-min)+min+0.5);
			 dstBmp[i*img.lineBytes+j*3+2]=(byte)(c[srcBmp[i*width+j]]*(max-min)+min+0.5);
		 }
	 }
	 //display(img,temp1);

}

void CutBmp(struct BMP_img img,struct Bmp1 *img1,int HL,int HH,int VL,int VH)
{
   int i,j,n;
   //float gray;
   int x=0,y=0;
   img1->width=VH-VL;
   img1->height=HH-HL;
   img1->image=myMalloc(img1->height*img1->width*3,0,0);//(byte *)malloc(sizeof(byte)*img1->height*img1->width*3);

   for(x=0,i=HL;i<HH;x++,i++)
   {
	   for(y=0,n=0,j=VL*3;j<VH*3;n++,j+=3,y+=3)

	   {

			   img1->image[x*img1->width*3+y]=img.image[i*img.width*3+j];
			   img1->image[x*img1->width*3+y+1]=img.image[i*img.width*3+j+1];
			   img1->image[x*img1->width*3+y+2]=img.image[i*img.width*3+j+2];


	   }

    }

}
void CutBmp1(struct Bmp1 *img1,int HL,int HH,int VL,int VH)
{
	int i,j,n;
	//float gray;
	int x=0,y=0;
	int width,height;
	width=img1->width;
	height=img1->height;

	//myMalloc(img1->width*img1->height*3,p,0);

	img1->width=VH-VL;
    img1->height=HH-HL;

	for(x=0,i=HL;i<HH;x++,i++)
	{
		for(y=0,n=0,j=VL*3;j<VH*3;n++,j+=3,y+=3)

	   {


			img1->image[x*img1->width*3+y]=img1->image[i*width*3+j];
			img1->image[x*img1->width*3+y+1]=img1->image[i*width*3+j+1];
			img1->image[x*img1->width*3+y+2]=img1->image[i*width*3+j+2];

		}

    }
}

/**************************************************
* 函数名称：
*     ThinnerRosenfeld
*
* 参数：
*   void*     image             －二值化图像矩阵前景色为1背景色为0
*   unsigned  longlx             －图像的宽度
*   unsigned  longly             －图像的高度
*
* 返回值
*       无
*
*函数功能：
*       对输入的图像进行细化，输出细化后的图像
***********************************************************/
void ThinnerRosenfeld(void *image, unsigned long lx, unsigned long ly)
{
    char *f, *g;
    char n[10];
    char a[5] = {0, -1, 1, 0, 0};
    char b[5] = {0, 0, 0, 1, -1};
    char nrnd, cond, n48, n26, n24, n46, n68, n82, n123, n345, n567, n781;
    short k, shori;
    unsigned long i, j;
    long ii, jj, kk, kk1, kk2, kk3, size;
    size = (long)lx * (long)ly;

    g = (char *)malloc(size);
    if(g==NULL)
    {
        printf("error in alocating mmeory!\n");
        return;
    }

    f = (char *)image;
    for(kk=0l; kk<size; kk++)
    {
        g[kk] = f[kk];
    }

    do
    {
        shori = 0;
        for(k=1; k<=4; k++)
        {
            for(i=1; i<lx-1; i++)
            {
                ii = i + a[k];

                for(j=1; j<ly-1; j++)
                {
                    kk = i*ly + j;

                    if(!f[kk])
                        continue;

                    jj = j + b[k];
                    kk1 = ii*ly + jj;

                    if(f[kk1])
                        continue;

                    kk1 = kk - ly -1;
                    kk2 = kk1 + 1;
                    kk3 = kk2 + 1;
                    n[3] = f[kk1];
                    n[2] = f[kk2];
                    n[1] = f[kk3];
                    kk1 = kk - 1;
                    kk3 = kk + 1;
                    n[4] = f[kk1];
                    n[8] = f[kk3];
                    kk1 = kk + ly - 1;
                    kk2 = kk1 + 1;
                    kk3 = kk2 + 1;
                    n[5] = f[kk1];
                    n[6] = f[kk2];
                    n[7] = f[kk3];

                    nrnd = n[1] + n[2] + n[3] + n[4]
                        +n[5] + n[6] + n[7] + n[8];
                    if(nrnd<=1)
                        continue;

                    cond = 0;
                    n48 = n[4] + n[8];
                    n26 = n[2] + n[6];
                    n24 = n[2] + n[4];
                    n46 = n[4] + n[6];
                    n68 = n[6] + n[8];
                    n82 = n[8] + n[2];
                    n123 = n[1] + n[2] + n[3];
                    n345 = n[3] + n[4] + n[5];
                    n567 = n[5] + n[6] + n[7];
                    n781 = n[7] + n[8] + n[1];

                    if(n[2]==1 && n48==0 && n567>0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    if(n[6]==1 && n48==0 && n123>0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    if(n[8]==1 && n26==0 && n345>0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    if(n[4]==1 && n26==0 && n781>0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    if(n[5]==1 && n46==0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    if(n[7]==1 && n68==0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    if(n[1]==1 && n82==0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    if(n[3]==1 && n24==0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    cond = 1;
                    if(!cond)
                        continue;
                    g[kk] = 0;
                    shori = 1;
                }
            }

            for(i=0; i<lx; i++)
            {
                for(j=0; j<ly; j++)
                {
                    kk = i*ly + j;
                    f[kk] = g[kk];
                }
            }
        }
    }while(shori);

    free(g);
}

void Thining(byte *srcBmp,int width,int height)
{

	//循环变量
    int i,j;
    int lWidth=width,lHeight=height;
    //建立存储区存放2值矩阵
	BYTE *image = (BYTE*)malloc(lWidth*lHeight*sizeof(BYTE));
    //DWORD lineBytes=(img.width*24+31)/32*4;
	//float gray;
	//给2值矩阵赋值

	for(i=0;i<lHeight;i++)
	{
		for(j=0;j<lWidth;j++)
		{

			if(srcBmp[i*width+j]==0)
				image[i*lWidth+j]=0;

			else
				image[i*lWidth+j]=1;
			//putpixel(j,i,RGB(srcBmp[i*img.width+j],srcBmp[i*img.width+j],srcBmp[i*img.width+j]));

		}
	}

	//调用函数进行细化,两种函数可以选择

	ThinnerRosenfeld(image,height,width);

	//ThinnerHilditch(image,lHeight,lWidth);



	//将结果赋值到原图像中

	for(i=0;i<lHeight;i++)
	{
		for(j=0;j<lWidth;j++)
		{
			if(image[i*lWidth+j]==1)
				srcBmp[i*width+j]=(BYTE)255;
			else
				srcBmp[i*width+j]=(BYTE)0;
			}

	}

}

void Thiningtest(struct BMP_img img,byte *srcBmp,byte *dstBmp)
{

	//循环变量
    int i,j,n;
    int lWidth=img.width,lHeight=img.height;
    //建立存储区存放2值矩阵
	BYTE *image = (BYTE*)malloc(lWidth*lHeight*sizeof(BYTE));
    DWORD lineBytes=(img.width*24+31)/32*4;
	float gray;
	//给2值矩阵赋值
	for(i=0;i<img.height;i++)
	{
		for(j=0,n=0;j<img.width;n+=3,j++)

		{

			gray= 0.299*(float)(img.image[lineBytes*i+n+2])+0.578*(float)(*(img.image+lineBytes*i+n+1))+0.114*(float)(*(img.image+lineBytes*i+n));
			if(gray>120.0)
				srcBmp[i*img.width+j]=255;
			else srcBmp[i*img.width+j]=0;//(byte)gray;
        }
    }
	for(i=0;i<lHeight;i++)
	{
	    for(j=0;j<lWidth;j++)
		{

	      if(srcBmp[i*img.width+j]==0)
	      image[i*lWidth+j]=1;

		  else
         image[i*lWidth+j]=0;
		}
	}

   //调用函数进行细化,两种函数可以选择

   ThinnerRosenfeld(image,img.height,img.width);





   //将结果赋值到原图像中

   for(i=0;i<lHeight;i++)
   {
     for(j=0;j<lWidth;j++)
	 {
	   if(image[i*lWidth+j]==1)
	    dstBmp[i*img.width+j]=(BYTE)0;
	   else
        dstBmp[i*img.width+j]=(BYTE)255;
	 }

   }

}
void delpoint(byte *dst,int width,int height,int yuzhi)
{
	int i,j,num=0,num1;
	byte *src=(byte *)malloc(sizeof(byte)*width*height);
	memset(src,0x00,sizeof(byte)*width*height);
	for(i=1;i<height-1;i++)//消除孤立噪点
	{
		for(j=1;j<width-1;j++)
		{
			if(dst[i*width+j]>200)
			{
				num1=dst[i*width+j-1]+dst[i*width+j+1]+dst[(i-1)*width+j-1]+dst[(i-1)*width+j]+dst[(i-1)*width+j+1]+dst[(i+1)*width+j-1]+dst[(i+1)*width+j]+dst[(i+1)*width+j+1]+255;
				num=num1/255;
				if(num>=yuzhi)
					//if((dst[i*width+j-1]==0)&&(dst[i*width+j-1]==0)&&(dst[(i-1)*width+j+1]==0)&&(dst[(i-1)*width+j]==0)&&(dst[(i-1)*width+j+1]==0)&&(dst[(i+1)*width+j-1]==0)&&(dst[(i+1)*width+j]==0)&&(dst[(i+1)*width+j+1]==0))
					src[i*width+j]=255;
				else src[i*width+j]=0;
			}
		}
	}
	memcpy(dst,src,sizeof(byte)*width*height);
}
void deljunzao(byte *dst,int width,int height,int yuzhi)
{
	int i,j,num=0,num1;

	byte *src=(byte *)malloc(sizeof(byte)*width*height);
	memset(src,0x00,sizeof(byte)*width*height);
	for(i=1;i<height-1;i++)//消除孤立噪点
	{
		for(j=1;j<width-1;j++)
		{
				num1=dst[i*width+j-1]+dst[i*width+j+1]+dst[(i-1)*width+j-1]+
					dst[(i-1)*width+j]+dst[(i-1)*width+j+1]+dst[(i+1)*width+j-1]+
					dst[(i+1)*width+j]+dst[(i+1)*width+j+1]+dst[i*width+j];
				num=num1/255;
				if(num>=yuzhi)
				//if((dst[i*width+j-1]==0)&&(dst[i*width+j-1]==0)&&(dst[(i-1)*width+j+1]==0)&&(dst[(i-1)*width+j]==0)&&(dst[(i-1)*width+j+1]==0)&&(dst[(i+1)*width+j-1]==0)&&(dst[(i+1)*width+j]==0)&&(dst[(i+1)*width+j+1]==0))
					src[i*width+j]=255;
				else src[i*width+j]=0;

		}
	}
	for(i=1;i<height-1;i++)//消除孤立噪点
	{
		for(j=1;j<width-1;j++)
		{
			if(dst[i*width+j]>200)
			{
				num=dst[i*width+j-1]+dst[i*width+j+1]+dst[(i-1)*width+j-1]+dst[(i-1)*width+j]+dst[(i-1)*width+j+1]+dst[(i+1)*width+j-1]+dst[(i+1)*width+j]+dst[(i+1)*width+j+1]+255;
				num=num/255;
				if(num>=2)
					//if((dst[i*width+j-1]==0)&&(dst[i*width+j-1]==0)&&(dst[(i-1)*width+j+1]==0)&&(dst[(i-1)*width+j]==0)&&(dst[(i-1)*width+j+1]==0)&&(dst[(i+1)*width+j-1]==0)&&(dst[(i+1)*width+j]==0)&&(dst[(i+1)*width+j+1]==0))
					src[i*width+j]=255;
				else src[i*width+j]=0;
			}
		}
	}
	memcpy(dst,src,sizeof(byte)*width*height);
}
void pingjun(byte *dst,int width,int height)
{
	int i,j,num=0;
	float num1;

	byte *src=(byte *)malloc(sizeof(byte)*width*height);
	memset(src,0x00,sizeof(byte)*width*height);
	for(i=1;i<height-1;i++)//消除孤立噪点
	{
		for(j=1;j<width-1;j++)
		{
			num1=dst[i*width+j-1]+dst[i*width+j+1]+dst[(i-1)*width+j-1]+
				dst[(i-1)*width+j]+dst[(i-1)*width+j+1]+dst[(i+1)*width+j-1]+
				dst[(i+1)*width+j]+dst[(i+1)*width+j+1]+dst[i*width+j];
			num=(int)(num1/9+0.5);

		    src[i*width+j]=num;

		}
	}

	memcpy(dst,src,sizeof(byte)*width*height);
}
void Dilation(byte *image,int width,int height,int type,int num)
{
	int dwWidth=width;
	int dwHeight=height;

	int i=0;
	int j=0;
	//int n=0;

	BYTE g=0;

	//double avg=0;
	BYTE *temp;
	int k=0;




	temp=(BYTE*)malloc(dwHeight*dwWidth*sizeof(BYTE));
	memcpy(temp,image,dwHeight*dwWidth*sizeof(byte));


	memset(temp,0,dwWidth*dwHeight*sizeof(BYTE));




	if(type==0)
	{
		//水平方向
		for(i=0;i<dwHeight;i++)
		{
			for(j=(num-1)/2;j<dwWidth-(num-1)/2;j++)
			{
				for(k=-(num-1)/2;k<=(num-1)/2;k++)
				{
					g=*(image+dwWidth*i+j+k);
					if(g==255)
					{
						*(temp+dwWidth*i+j)=255;
						break;
					}
				}
			}
		}
	}
	else
	{
		//垂直方向
		for(i=(num-1)/2;i<dwHeight-(num-1)/2;i++)
		{
			for(j=0;j<dwWidth;j++)
			{
				for(k=-(num-1)/2;k<=(num-1)/2;k++)
				{
					g=*(image+dwWidth*(i+k)+j);
					if(g==255)
					{
						*(temp+dwWidth*i+j)=255;
						break;
					}
				}
			}
		}
	}
	memcpy(image,temp,sizeof(byte)*width*height);
	free(temp);
	temp=NULL;
}

void Erosion(byte *image,int width,int height,int type,int num)
{
	int dwWidth=width;
	int dwHeight=height;
	int i=0;
	int j=0;
	//int n=0;
	BYTE g=0;
	//double avg=0;
	BYTE *temp;
	int k=0;
	temp=(BYTE*)malloc(dwHeight*dwWidth*sizeof(BYTE));
	memset(temp,0,dwWidth*dwHeight*sizeof(BYTE));
	if(type==0)
	{
		//水平方向
		for(i=0;i<dwHeight;i++)
		{
			for(j=(num-1)/2;j<dwWidth-(num-1)/2;j++)
			{
				for(k=-(num-1)/2;k<=(num-1)/2;k++)
				{
					g=*(image+width*i+j+k);
					if(g==0)
					{
						*(temp+width*i+j)=0;
						break;
					}
				}
			}
		}
	}
	else
	{
		//垂直方向
		for(i=(num-1)/2;i<dwHeight-(num-1)/2;i++)
		{
			for(j=0;j<dwWidth;j++)
			{
				for(k=-(num-1)/2;k<=(num-1)/2;k++)
				{
					g=*(image+width*(i+k)+j);
					if(g==0)
					{
						*(temp+width*i+j)=0;
						break;
					}
				}
			}
		}
  }
	memcpy(image,temp,sizeof(byte)*width*height);
	free(temp);
	temp=NULL;
}



void changeGray(byte *srcBmp,byte *dstBmp,int width,int height,int nWidth,int nHeight)
{

  int i=0,j=0,i0,j0;
  float xx;float yy;
  xx=(float)nWidth/width;
  yy=(float)nHeight/height;

  //memset(srcBmp,0x00,nHeight*nWidth*sizeof(byte));
  memset(dstBmp,0x00,nHeight*nWidth*sizeof(byte));
 for(i = 0; i <nHeight; i++)
 {
	for(j = 0; j <nWidth; j++)
	{
	  //i0 = (int) ((float)i/yy+0.5);
	  //j0 = (int) ((float)j/xx+0.5);
	  i0 = (int) ((float)i/yy);
	  j0 = (int) ((float)j/xx);
	  if((j0>=0)&&(j0<width)&&(i0>=0)&&(i0<height))
		// {
			dstBmp[i*nWidth+j]=srcBmp[i0*width+j0];
		 //}
		 //else
		 //{
		//	dstBmp[i*nWidth+j]=255;
		 //}
	 }
 }

}
void strBmp(struct Bmp1 *img,byte *temp)
{
  int i,j,k,m,n,o;
  //int width=20,height=20;
  for(i=0;i<7;i++)
  {
	  o=img->p2[i]-img->p1[i]+1;
	  for(m=0,j=img->p3[i];j<=img->p4[i];j++,m++)
	  {

		  for(n=0,k=img->p1[i];k<=img->p2[i];k++,n++)
		  {
           img->strr[i][m*o+n]=temp[j*img->width+k];
		  }
	  }
  }
}
void guiyi(struct Bmp1 *img)
{
	int xxx;
	int i;
	//xxx=img->p2[0]-img->p1[0]+1;
	int yyy;
	//
	byte *temp=(byte *)malloc(sizeof(byte)*800);
	//strBmp(&img1,temp1);
	for(i=0;i<7;i++)
	{
		xxx=img->p2[i]-img->p1[i]+1;
		yyy=img->p4[i]-img->p3[i]+1;

	    changeGray(img->strr[i],temp,xxx,yyy,20,40);

		memcpy(img->strr[i],temp,sizeof(byte)*800);
	}
}

void readmoban(char *path,struct Bmp1 *img2)
{
	FILE *f[72];
	int i;
	 char str2[]=".bmp";
	 char str[80];
	 char str1[10];
	for(i=0;i<=66;i++)
	{
		//char str[80];
		strcpy(str,path);
	    //char str1[10];
		myitoa(i,str1,10);
		strcat(str1,str2);
		strcat(str,str1);
		f[i]=fopen(str,"rb");
		if(f[i]==NULL)
		//	exit(-1);
		readstr(f[i],img2->strc[i]);
		fclose(f[i]);

	}





}

char *myitoa(int num,char *str,int radix)
{

char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";/* 索引表 */
unsigned unum; /* 中间变量 */
int i=0,j,k;/* 确定unum的值 */

	if(radix==10&&num<0) /* 十进制负数 */
	{
	 unum=(unsigned)-num;
	 str[i++]='-';
	}
	else unum=(unsigned)num; /* 其他情况 */
	/* 逆序 */
	do
	{
	str[i++]=index[unum%(unsigned)radix];
	unum/=radix;
	}while(unum);
	str[i]='\0';
	/* 转换 */
	if(str[0]=='-') k=1; /* 十进制负数 */
	else k=0;
	/* 将原来的“/2”改为“/2.0”，保证当num在16~255之间，radix等于16时，也能得到正确结果 */
	for(j=k;j<(i-1)/2.0+k;j++)
	{
	num=str[j];
    str[j]=str[i-j-1+k];
	str[i-j-1+k]=num;
	}
	return str;
}

void writebmp(const char *path,const char *name,byte *temp)
{

    FILE *f1,*f2;
    int i,j;
	byte temp1;
	char path1[40];
	char path2[40];
	char *p1="header.txt";
	char p4[5]=".bmp";
	char p2[1078];
	char p3[800];
	strcpy(path1,path);
	strcat(path1,p1);
	strcpy(path2,path);
	strcat(path2,name);
	strcat(path2,p4);
	if((f1=fopen(path1,"rb"))==NULL)
	{
		printf( "\n 不能打开  \n");
		//exit(-1);
	}
	fread(p2,1078,1,f1);

	for(i=0;i<40;i++)
	{
		for(j=0;j<20;j++)
		{

			temp1=temp[i*20+j];
			if(temp1==0)
				temp1=0;
			else temp1=255;
			p3[(40-i-1)*20+j]=temp1;
		}
		 }

	if((f2=fopen(path2,"wb"))==NULL)
    {
        printf("\n不能创建%s图\n",path1);
      //  exit(-1);
    }
	if(fwrite(p2,1078*sizeof(BYTE),1,f2)!=1)
    {
        printf("不能写入%s图\n",path2);
        fclose(f2);

    }
    fseek(f2,1078,SEEK_SET);

    if(fwrite(p3,20*40,1,f2)!=1)
    {
        printf("不能写入%s图\n",path2);
        fclose(f2);

    }
	fclose(f1);
    fclose(f2);

}
void strout(struct Bmp1 *img)
{
	int i,j,k=0,m=800,n;
	//int p[5]={0};
    for(i=36;i<67;i++)
	{
		k=cmpstr(img->strr[0],img->strc[i]);
	   if(k==0)
	   {
		   n=i;
		   break;
	   }
	   else
	   {
          if(k<m)
		  {
			  m=k;
		      n=i;
		  }
	   }
	 }
	   img->string[0]=n;

     for(i=1;i<7;i++)
	 {
		 n=0;k=0;m=800;
		 for(j=0;j<36;j++)
		 {
			 if((img->p2[i]-img->p1[i])<4)
             {
                  n=1;
				  break;

			 }
			 k=cmpstr(img->strr[i],img->strc[j]);
			 if(k==0)
			 {
				 n=j;
				 break;
			 }
			 else
			 {
				 if(k<m)
				 {
					 m=k;
					 n=j;
				 }
			 }
		 }


	 if(n==27)//p&r
	 {
		 k=cmpstr(img->strc[27],img->strr[i]);
		 j=cmpstr(img->strr[i],img->strc[25]);
		 if(k<j)
			 n=27;
		 else n=25;
	 }
	 if(n==0)//0
	 {
	    j=cmpstr(img->strc[0],img->strr[i]);
		k=cmpstr(img->strr[i],img->strc[12]);
	 if(j>k)
		 n=12;
	 else n=0;

	 }
	 if(n==26)
	 {
		 k=cmpstr(img->strc[26],img->strr[i]);
		 j=cmpstr(img->strr[i],img->strc[0]);
		 if(k<j)
			 n=26;
		 else n=0;
	 }
	if(n==19)
	 {
		 k=cmpstr(img->strc[0],img->strr[i]);
		 j=cmpstr(img->strr[19],img->strc[i]);
		 if(k<j)
			 n=0;
		 else n=19;
	 }
	if(n==13)
	{
		k=cmpstr(img->strc[13],img->strr[i]);
		j=cmpstr(img->strr[i],img->strc[0]);
		if(k<j)
			n=13;
		else n=0;
	 }

	 /*if((n==6)||(n==3))
	 {
		 k=cmpstr(img->strc[6],img->strr[i]);
		 j=cmpstr(img->strc[3],img->strr[i]);
		 if(k<j)
			 n=5;
		 else n=3;
	 }
	 if(n==12)
	 {
		 k=cmpstr(img->strc[0],img->strr[i]);
		 j=cmpstr(img->strc[12],img->strr[i]);
		 if(k<j)
			 n=0;
		 else n=12;
	 }*/
	 if(n==14)//E F
	 {
		 k=cmpstr(img->strc[14],img->strr[i]);
		 j=cmpstr(img->strr[i],img->strc[15]);
		 if(k<j)
			 n=14;
		 else n=15;
	 }
	 if(n==8)
	 {
		 k=cmpstr(img->strc[8],img->strr[i]);
		 j=cmpstr(img->strr[i],img->strc[3]);
		 if(k<j)
			 n=8;
	   else n=3;
	 }
	 img->string[i]=n;

	  i=i;
	 }


}
int cmpstr(byte *src,byte *moban)
{
    int i,j,k=0;
	byte temp[800]={0};
	memcpy(temp,src,800);

	for(i=0;i<40;i++)
		for(j=0;j<20;j++)
		{
		  if(temp[i*20+j]==255)
		  {
			  if(moban[i*20+j]==255)
				  temp[i*20+j]=0;

		  }
		}
		delpoint(temp,40,20,4);
for(i=0;i<40;i++)
	for(j=0;j<20;j++)
		{
		  if(temp[i*20+j]==255)
		  {
			  k++;
		  }

		}

	return k;
}
int calstr(byte *srcBmp)
{
   int i,j,num=0;
	for(i=0;i<40;i++)
		for(j=0;j<20;j++)
		{
		  if(srcBmp[i*20+j]==255)
		  {
			  num++;

		  }
		}
		return num;
}

void edgesob8(byte *image,int width,int height)//8邻域
{

    //int sum1,sum2,sum;double gray;
    int i,j,logNum;
    //int p[8];
	BYTE *temp;
	temp=(byte*)malloc(sizeof(byte)*width*height);
	memset(temp,0x00,sizeof(byte)*width*height);
    for(i=3;i<height-2;i++)
		for(j=3;j<width-2;j++)
		{
			logNum=16*image[i*width+j]-image[(i-2)*width+j]-image[(i-1)*width+j-1]-2*image[(i-1)*width+j]-image[(i-1)*width+j+1]-image[i*width+j-2]-2*image[i*width+j-1]-2*image[i*width+j+1]-image[i*width+j+2]-image[(i+1)*width+j-1]-2*image[(i+1)*width+j]-image[(i+1)*width+j+1]-image[(i+2)*width+j];
			if(logNum > 0)

				temp[i*width+j]=255;

			else

				temp[i*width+j]=0;
	  }
   memcpy(image,temp,width*height);
   free(temp);
   temp=NULL;

}
void edgesob4(byte *image,int width,int height)//4邻域
{

   // int sum1,sum2,sum;double gray;
    int i,j;
    int p[8];
	float result;
	BYTE *temp=(byte*)malloc(sizeof(byte)*width*height);
	memset(temp,0x00,sizeof(byte)*width*height);
	for(i =0; i<=height-1; i++)			//sob算子边缘检测；取出边界；
	{
		for(j=0;j<=width-1;j++)//由于使用2×2的模板，为防止越界，所以不处理最下边和最右边的两列像素
		{

			if(i==height-1)
				temp[i*width+j]=0;
			else if(j==width-1)
				temp[i*width+j]=0;

			else{

				p[0] = (byte)*(image+i*width+j);
				p[1] = (byte)*(image+i*width+j+1);
				p[2] = (byte)*(image+(i+1)*width+j);
				p[3] = (byte)*(image+(i+1)*width+j+1);
			   result = sqrt(( p[0] - p[3] )*( p[0] - p[3] )+( p[1] - p[2] )*( p[1] - p[2] ));
				if(result<=0.0)
					result=0;
				if(result>=255.0)
					result=255;
				temp[i*width+j] = (byte)result;
			}
		}
	}
		memcpy(image,temp,width*height);
		free(temp);
		temp=NULL;

}
int hough(byte *srcBmp,int width,int height)
{
    int kmax=0;
    int pmax=0;
	int yuzhi=0;
	int i,j,k,n,p=(int)(height*cos(pi)+width*sin(pi));
	int mp= (int) (sqrt(width*width + height*height)+1);
	int ma=180;//180
	//int ap;
	int npp[180][1000];
	for(i=0;i<180;i++)
	for(j=0;j<1000;j++)
	npp[i][j]=0;
	/*ap=90*(p+mp);
	int *npp=(int *)malloc(sizeof(int)*ap);//myMalloc(ap,0,0);
	memset(npp,0x00,sizeof(int)*ap);*/
	for(i=1;i<height;i++)
		for(j=1;j<width;j++)
		{
			if(srcBmp[i*width+j]==255)
			{
				for(k=1;k<ma;k++)
				{
					p=(int)(i*cos(pi*k/180)+j*sin(pi*k/180));
					p=(int)(p/2+mp/2);
					npp[k][p]=npp[k][p]++;
					//npp[k*p+k]=npp[k*p+k]++;
				}
			}
		}
		kmax=0;
		pmax=0;
		n=0;
		for(i=1;i<ma;i++)
			for(j=1;j<mp;j++)
			{
				if(npp[i][j]>yuzhi)
			//	if(npp[i*j+i]>yuzhi)
				{
					yuzhi=npp[i][j];
                  //  yuzhi=npp[i*j+i];
					kmax=i;
					pmax=j;
				}
			}

				return kmax;
}

void RotateGray(byte *image,int width,int height, float iRotateAngle)
{

	// 循环变量
    int i,j,lNewWidth,lNewHeight,i0,j0;
	// 旋转后图像的宽度和高度
    int ang;
	// 象素在源DIB中的坐标

	// 旋转角度（弧度）
	float	fRotateAngle;
	// 旋转角度的正弦和余弦
	float	fSina, fCosa;
	// 源图四个角的坐标（以图像中心为坐标系原点）
	float	fSrcX1,fSrcY1,fSrcX2,fSrcY2,fSrcX3,fSrcY3,fSrcX4,fSrcY4;
	// 旋转后四个角的坐标（以图像中心为坐标系原点）
	float	fDstX1,fDstY1,fDstX2,fDstY2,fDstX3,fDstY3,fDstX4,fDstY4;
	// 两个中间常量
	float	f1,f2;

	byte *temp=(byte *)malloc(sizeof(byte)*lNewHeight*lNewWidth);
				if(temp==NULL)
					printf("\nerror\n");

	// 将旋转角度从度转换到弧度
	fRotateAngle = (float) RADIAN(iRotateAngle);
	// 计算旋转角度的正弦
	fSina = (float) sin((double)fRotateAngle);
	// 计算旋转角度的余弦
	fCosa = (float) cos((double)fRotateAngle);
	// 计算原图的四个角的坐标（以图像中心为坐标系原点）
	fSrcX1 = (float) (- (width  - 1) / 2);
	fSrcY1 = (float) (  (height - 1) / 2);
	fSrcX2 = (float) (  (width  - 1) / 2);
	fSrcY2 = (float) (  (height - 1) / 2);
	fSrcX3 = (float) (- (width  - 1) / 2);
	fSrcY3 = (float) (- (height - 1) / 2);
	fSrcX4 = (float) (  (width  - 1) / 2);
	fSrcY4 = (float) (- (height - 1) / 2);

	// 计算新图四个角的坐标（以图像中心为坐标系原点）
	fDstX1 =  fCosa * fSrcX1 + fSina * fSrcY1;
	fDstY1 = -fSina * fSrcX1 + fCosa * fSrcY1;
	fDstX2 =  fCosa * fSrcX2 + fSina * fSrcY2;
	fDstY2 = -fSina * fSrcX2 + fCosa * fSrcY2;
	fDstX3 =  fCosa * fSrcX3 + fSina * fSrcY3;
	fDstY3 = -fSina * fSrcX3 + fCosa * fSrcY3;
	fDstX4 =  fCosa * fSrcX4 + fSina * fSrcY4;
	fDstY4 = -fSina * fSrcX4 + fCosa * fSrcY4;
    // 计算旋转后的图像实际宽度
	lNewWidth  = (int) ( max( fabs(fDstX4 - fDstX1), fabs(fDstX3 - fDstX2) ) + 0.5);

	// 计算旋转后的图像高度
	lNewHeight = (int) ( max( fabs(fDstY4 - fDstY1), fabs(fDstY3 - fDstY2) )  + 0.5);


	// 两个常数，这样不用以后每次都计算了
	f1 = (float) (-0.5 * (lNewWidth - 1) * fCosa - 0.5 * (lNewHeight - 1) * fSina
		+ 0.5 * (width  - 1));
	f2 = (float) ( 0.5 * (lNewWidth - 1) * fSina - 0.5 * (lNewHeight - 1) * fCosa
		+ 0.5 * (height - 1));

				memset(temp,(byte)0,lNewHeight*lNewWidth*sizeof(byte));

	// 针对图像每行进行操作
	for(i = 0; i < lNewHeight; i++)
	{
		// 针对图像每列进行操作
		for(j = 0; j < lNewWidth; j++)
		{

			// 计算该象素在源DIB中的坐标
			i0 = (int) (-((float) j) * fSina + ((float) i) * fCosa + f2 + 0.5);
			j0 = (int) ( ((float) j) * fCosa + ((float) i) * fSina + f1 + 0.5);

			// 判断是否在源图范围内
			if( (j0 >= 0) && (j0 < width) && (i0 >= 0) && (i0 < height))
			{
				// 复制象素
			   //*(temp + lNewWidth * (lNewHeight - 1 - i) + j)=*(image + width * (height - 1 - i0) + j0);
			    *(temp + lNewWidth * i + j)=*(image + width * i0 + j0);
			}
			else
			{
				// 对于源图中没有的象素，直接赋值为255
				*(temp + lNewWidth * i + j) = 0;
				//*(temp + lNewWidth * (lNewHeight - 1 - i) + j);
			}
		}
	}


   ang=hough(temp,lNewWidth,lNewHeight);


   	free(temp);
    temp=NULL;
}

void xuanzhuan(struct Bmp1 *img1)
{
	int lwidth=0,lheight=0;
	//int nwidth=0,nheight=0;
	//float m;

	  byte *p;
	  p=RotateRGB(img1->image,img1->ang,img1->width,img1->height,&lwidth,&lheight);
       img1->width=lwidth;
       img1->height=lheight;
	   free(img1->image);
	   img1->image=NULL;
	   img1->image=p;


}
byte *myMalloc(int num,const byte *bmp,int type)
{
   byte *p=(byte *)malloc(sizeof(byte)*num);
   if(p==NULL)
	 //  exit(-1);
   if(type==0)
	   memset(p,0x00,sizeof(byte)*num);
   if(type==1)
       memset(p,255,sizeof(byte)*num);
   if(type==2)
       memcpy(p,bmp,sizeof(byte)*num);
   return p;
}
byte *changeRGB(byte *srcBmp,int width,int height,int *lwidth,int *lheight,float f)
{
	int i,j,k,i0,j0,m,n;
	int nwidth=(int)(f*width+0.5);
    int nheight=(int)(f*height+0.5);
	byte *temp;
	temp=myMalloc(nwidth*nheight,0,0);


   for(i = 0; i < nheight; i++)
	{
		for(m=0,j = 0;j < nwidth;m+=3,j++)
		{

			i0 = (unsigned int) (i/f + 0.5);
			j0 = (unsigned int) (j/f + 0.5);
			n=i0*width*3+j0*3;
			k=nwidth*i*3+m;
			if( (j0 >= 0) && (j0 < width) && (i0 >= 0) && (i0 < height))
			{

			     *(temp + k+1)=*(srcBmp + n+1);
				 *(temp + k+2)=*(srcBmp+ n+2);
				 *(temp + k)=*(srcBmp + n);
			}
			else
			{
				 *(temp + k+1)=0;
				 *(temp + k+2)=0;
				 *(temp + k)=0;

			}
		}
	}
   *lwidth=nwidth;
   *lheight=nheight;
   //displayRGB(temp,nwidth,nheight,0,0);
   return temp;
}
void guiyiRGB(struct Bmp1 *img1)
{
	int nwidth=0,nheight=0;
	float m;
	byte *q;
	m=1;
	if(img1->width<200)
    {
		m=(float)(200)/img1->width;
		q=changeRGB(img1->image,img1->width,img1->height,&nwidth,&nheight,m);
		img1->width=nwidth;
		img1->height=nheight;
		free(img1->image);
		img1->image=NULL;
		img1->image=q;
	}

}
void outtext(struct Bmp1 img1,int x,int y)
{
	char *table[]={"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F",\
		"G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","京",\
		"冀","津","晋","蒙","辽","吉","黑","沪","苏","浙","皖","闽","赣","鲁","豫","鄂","湘",\
		"粤","桂","琼","渝","川","贵","云",\
		"藏","陕","甘","青","宁","新"};
	int i;

    printf("\n\n\n\n\n\n\n\n");
    printf("\n        The Car Id Is\n");
    printf("\n");
	for(i=0;i<7;i++)
	{
		printf("   ");
		printf("%s",table[img1.string[i]]);
	    //outtextxy(x+i*40,y,table[img1.string[i]]);

	}
    printf("\n");
	printf("\n   This is designed by liujia\n");
	printf("\n\n\n\n\n\n\n\n");


}

byte *RotateRGB(byte *image, float iRotateAngle,int width,int height,int *lwidth,int *lheight)
{
    byte *temp;
	// 循环变量
    int i,j,m,n,lNewWidth,lNewHeight,i0,j0;
	// 旋转后图像的宽度和高度

	// 象素在源DIB中的坐标

	// 旋转角度（弧度）
	float	fRotateAngle;
	// 旋转角度的正弦和余弦
	float	fSina, fCosa;
	// 源图四个角的坐标（以图像中心为坐标系原点）
	float	fSrcX1,fSrcY1,fSrcX2,fSrcY2,fSrcX3,fSrcY3,fSrcX4,fSrcY4;
	// 旋转后四个角的坐标（以图像中心为坐标系原点）
	float	fDstX1,fDstY1,fDstX2,fDstY2,fDstX3,fDstY3,fDstX4,fDstY4;
	// 两个中间常量
	float	f1,f2;


	// 将旋转角度从度转换到弧度
	fRotateAngle = (float) RADIAN(iRotateAngle);
	// 计算旋转角度的正弦
	fSina = (float) sin((double)fRotateAngle);
	// 计算旋转角度的余弦
	fCosa = (float) cos((double)fRotateAngle);
	// 计算原图的四个角的坐标（以图像中心为坐标系原点）
	fSrcX1 = (float) (- (width  - 1) / 2);
	fSrcY1 = (float) (  (height - 1) / 2);
	fSrcX2 = (float) (  (width  - 1) / 2);
	fSrcY2 = (float) (  (height - 1) / 2);
	fSrcX3 = (float) (- (width  - 1) / 2);
	fSrcY3 = (float) (- (height - 1) / 2);
	fSrcX4 = (float) (  (width  - 1) / 2);
	fSrcY4 = (float) (- (height - 1) / 2);

	// 计算新图四个角的坐标（以图像中心为坐标系原点）
	fDstX1 =  fCosa * fSrcX1 + fSina * fSrcY1;
	fDstY1 = -fSina * fSrcX1 + fCosa * fSrcY1;
	fDstX2 =  fCosa * fSrcX2 + fSina * fSrcY2;
	fDstY2 = -fSina * fSrcX2 + fCosa * fSrcY2;
	fDstX3 =  fCosa * fSrcX3 + fSina * fSrcY3;
	fDstY3 = -fSina * fSrcX3 + fCosa * fSrcY3;
	fDstX4 =  fCosa * fSrcX4 + fSina * fSrcY4;
	fDstY4 = -fSina * fSrcX4 + fCosa * fSrcY4;
    // 计算旋转后的图像实际宽度
	lNewWidth  = (int) ( max( fabs(fDstX4 - fDstX1), fabs(fDstX3 - fDstX2) ) + 0.5);

	// 计算旋转后的图像高度
	lNewHeight = (int) ( max( fabs(fDstY4 - fDstY1), fabs(fDstY3 - fDstY2) )  + 0.5);

     temp=myMalloc(lNewHeight*lNewWidth*3,0,0);
	// 两个常数，这样不用以后每次都计算了
	f1 = (float) (-0.5 * (lNewWidth - 1) * fCosa - 0.5 * (lNewHeight - 1) * fSina
		+ 0.5 * (width  - 1));
	f2 = (float) ( 0.5 * (lNewWidth - 1) * fSina - 0.5 * (lNewHeight - 1) * fCosa
		+ 0.5 * (height - 1));


	for(i = 0; i < lNewHeight; i++)
	{
		// 针对图像每列进行操作
		for(m=0,j = 0;j < lNewWidth;m+=3,j++)
		{

			// 计算该象素在源DIB中的坐标
			i0 = (int) (-((float) j) * fSina + ((float) i) * fCosa + f2 + 0.5);
			j0 = (int) ( ((float) j) * fCosa + ((float) i) * fSina + f1 + 0.5);

			// 判断是否在源图范围内
			if( (j0 >= 0) && (j0 < width) && (i0 >= 0) && (i0 < height))
			{
				n=i0*width*3+j0*3;
			   //*(temp + lNewWidth * (lNewHeight - 1 - i) + j)=*(image + width * (height - 1 - i0) + j0);
			     *(temp + lNewWidth * i*3 + m+1)=*(image + n+1);
				 *(temp + lNewWidth * i*3 + m+2)=*(image + n+2);
				 *(temp + lNewWidth * i*3+ m)=*(image + n);
				  //*(temp1 + n)=0;
			}
			else
			{
				// 对于源图中没有的象素，直接赋值为255
				 *(temp + lNewWidth * i*3+ m+1)=0;
				 *(temp + lNewWidth * i*3+ m+2)=0;
				 *(temp + lNewWidth * i*3+ m)=0;
				//*(temp + lNewWidth * (lNewHeight - 1 - i) + j);
			}
		}
	}

   *lwidth=lNewWidth;
	*lheight=lNewHeight;
		return temp;
}
