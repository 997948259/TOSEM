//@ ltl invariant positive: [](AP(init=0) ==> <>(AP(j=256)));


typedef unsigned char uchar;
#define LOBYTE(x) ((uchar)((x) & 0xFF))
#define HIBYTE(x) ((uchar)((x) >> 8))

unsigned char lin[256];

unsigned short icrc1(unsigned short crc, unsigned char onech)
{
	int i;
	unsigned short ans=(crc^onech << 8);

	for (i=0;i<8;i++) { 
		if (ans & 0x8000)
			ans = (ans <<= 1) ^ 4129;
		else
			ans <<= 1;
	}
	return ans;
}
       unsigned char rchrIndex1;
	unsigned char rchrIndex2;
	unsigned short init=0;
	unsigned short j=0;
	int tmp;
unsigned short icrc(unsigned short crc, unsigned long len, 
		    short jinit, int jrev)
{
	unsigned short icrc1(unsigned short crc, unsigned char onech);
	static unsigned short icrctb[256];
	
	static uchar rchr[256];
	unsigned short tmp1, tmp2,cword=crc;
	static uchar it[16]={0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};\
     rchrIndex1=0;
	rchrIndex2=0;
	
	if (!init) {
		init=1;
		for (j=0;j<=255;j++) {
			icrctb[j]=icrc1(j << 8,(uchar)0);
			rchr[j]=(uchar)(it[j & 0xF] << 4 | it[j >> 4]);
		}
	}
	if (jinit >= 0) cword=((uchar) jinit) | (((uchar) jinit) << 8);
	else if (jrev < 0) 
	  cword=rchr[HIBYTE(cword)] | rchr[LOBYTE(cword)] << 8;

	printf("len = %d\n", len);

	for (j=1;j<=len;j++) {
	  if (jrev < 0) {
	    tmp1 = rchr[lin[j]]^ HIBYTE(cword);
	  }
	  else {
	    tmp1 = lin[j]^ HIBYTE(cword);
	  }
	  cword = icrctb[tmp1] ^ LOBYTE(cword) << 8;
	}
	if (jrev >= 0) {
	  tmp2 = cword;
	}
	else {
          rchrIndex1=HIBYTE(cword);
	  rchrIndex2=LOBYTE(cword);
	  tmp2 = rchr[HIBYTE(cword)] | rchr[LOBYTE(cword)] << 8;
	}
	return (tmp2 );
}


int main(void)
{

	unsigned short i1,i2;
	unsigned long n;
	lin[0] = 'a';
	lin[1]='s';
	lin[2]='d';
	lin[3]='f';
	lin[4]='f';
	lin[5]='e';
	lin[6]='a';
	lin[7]='g';
	lin[8]='e';
	lin[9]='w';
	lin[10]='a';
	lin[11]='H';
	lin[12]='A';
	lin[13]='F';
	lin[14]='E';
	lin[15]='F';
	lin[16]='a';
	lin[17]='e';
	lin[18]='D';
	lin[19]='s';
	lin[20]='F';
	lin[21]='E';
	lin[22]='a';
	lin[23]='w';
	lin[24]='F';
	lin[25]='d';
	lin[26]='s';
	lin[27]='F';
	lin[28]='a';
	lin[29]='e';
	lin[30]='f';
	lin[31]='a';
	lin[32]='e';
	lin[33]='e';
	lin[34]='r';
	lin[35]='d';
	lin[36]='j';
	lin[37]='g';
	lin[38]='p';
	n=40;
		lin[n+1]=0;
		i1=icrc(0,n,(short)0,1);
		lin[n+1]=HIBYTE(i1);
		lin[n+2]=LOBYTE(i1);
		i2=icrc(i1,n+2,(short)0,1);
		tmp=10000000;
		while (tmp>0) {tmp=tmp-1;}
	return 0;
}


