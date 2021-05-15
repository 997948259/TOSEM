</
define p: rchrIndex1<=255;
define q: rchrIndex2<=255;
alw(p and q)
/>
/*</
define p: init=0;
define q: j=256;
alw(p -> som(q))
/>*/
frame(lin,rchrIndex1,rchrIndex2,init,j,tmp) and
(
	unsigned char lin[256] <== "asdffeagewaHAFEFaeDsFEawFdsFaefaeerdjgp" and skip;
	int rchrIndex1<==0 and skip;
	int rchrIndex2<==0 and skip;
	int init<==0 and skip;
	int j<==0 and skip;
	int tmp and skip;
	
	function icrc1 (int crc,char onech, int RValue)
	{
		int i and skip;
		int ans<==(crc^onech << 8) and skip;
		i<==0 and skip;
		while(i<8)
		{
			if(ans & 32768)then
			{
				ans:=ans << 1;
				ans:=ans ^ 4129
			}
			else
			{
				ans := ans << 1
			};
			i:=i+1
		};
		RValue:=ans;
		skip
	};
	function icrc(int crc, int len1, int jinit, int jrev,int RValue)
	{
		int icrctb[256] and skip;
		init<==0 and skip;
		char rchr[256] and skip;
		int tmp1, tmp2,cword and skip;
		char it[16]<==[0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15] and skip;
		cword:=crc;
		
		if(!init)then
		{
			init<==1 and skip;
			j<==0 and skip;
			while(j<=255)
			{
				icrctb[j]:=icrc1(j << 8,(char)0);
				rchr[j]:=(unsigned char)(it[j & 15] << 4 | it[j >> 4]);
				j:=j+1
			}
		}
		else
		{
			skip
		};
		if(jinit >= 0) then
		{
			cword:=((unsigned char) jinit) | (((unsigned char) jinit) << 8)
		}
		else
		{
			if(jrev < 0) then
			{
				cword:=rchr[(unsigned char)((cword)>>8)] | 	rchr[(unsigned char)((cword) & 255)] << 8
			}
			else
			{
				skip
			}
		};
		j<==1 and skip;
		while(j<=len1)
		{
			if(jrev < 0)then
			{
				tmp1 := rchr[lin[j]]^((unsigned char)((cword)>>8))
			}
			else
			{
				tmp1:=lin[j] ^ ((unsigned char)((cword)>>8))
			};
			cword := icrctb[tmp1] ^ ((unsigned char)(cword & 255)) << 8;
			j:=j+1
		};
		if(jrev >= 0) then
		{
			tmp2 := cword
		}
		else
		{
			rchrIndex1:=(unsigned char)((cword)>>8);
			rchrIndex2:=(unsigned char)(cword & 255);
			tmp2 := rchr[(unsigned char)((cword)>>8)] | rchr[(unsigned char)(cword & 255)] << 8
		};
		RValue:=tmp2;
		skip
	};
	function main_1()
	{
		int i1,i2 and skip;
		int n and skip;
		n<==40 and skip;
		lin[n+1]:=0;
		i1:=icrc(0,n,0,1);
		lin[n+1]:=(unsigned char)((i1) >> 8);
		lin[n+2]:=(unsigned char)((i1) & 255);
		i2:=icrc(i1,n+2,0,1);
		tmp:=10000000;
		while(tmp>0)
		{
		  tmp:=tmp-1
		}
	};
	main_1()
)