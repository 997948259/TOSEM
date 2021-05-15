/*</
define p: 0<=MAXSIZE;
define q: 0<=MAXWAVES;
alw(p and q)
/>*/
</
define p: j=0;
define q: 0>MAXWAVES;
alw(p->som(q))
/>

frame(MAXSIZE,MAXWAVES,i,j,RealIn,ImagIn,RealOut,ImagOut,coeff,amp,invfft,tmp) and
(
 function NumberOfBitsNeeded (unsigned int PowerOfTwo,unsigned int RValue)
 {
	unsigned int i and skip;
	int break1<==0 and skip;
	i<==0 and skip;
	while(break1!=1)
	{
		if(PowerOfTwo & (1 << i)) then
		{
			break1<==1
		}
		else
		{
			i:=i+1
		}
	};
	RValue:=i
 };
function ReverseBits (unsigned int index, unsigned int NumBits, unsigned int RValue)
{
	unsigned int i, rev and skip;
	i<==0 and skip;
	rev<==0 and skip;
	while(i < NumBits)
	{
		rev := (rev << 1) | (index & 1);
		index:=index>>1;
		i:=i+1
	};
	RValue:=rev
};
	function fft_float(unsigned int NumSamples,int InverseTransform, float *RealIn, float *ImagIn,float *RealOut, float *ImagOut)
	{
		unsigned int NumBits and skip; 
		unsigned int i, j, k, n and skip;
		unsigned int BlockSize, BlockEnd and skip;
		float angle_numerator <== 2.0 * 3.14159265358979323846 and skip;
		float tr,ti and skip;
		if ( InverseTransform ) then
		{
			angle_numerator := -angle_numerator
		};
		NumBits := NumberOfBitsNeeded (NumSamples,RValue);
		i<==0 and skip;
		while(i<NumSamples)
		{
			j:=ReverseBits ( i, NumBits,RValue );
			RealOut[j] := RealIn[i];
			if(ImagIn = NULL) then
			{
				ImagOut[j]:=0.0
			}
			else
			{
				ImagOut[j]:=ImagIn[i]
			};
			i:=i+1
		};
		BlockEnd <== 1 and skip;
		BlockSize <== 2 and skip;
		while(BlockSize <= NumSamples)
		{
			float delta_angle <== angle_numerator / (float)BlockSize and skip;
			float sm2 <== 0.3 and skip;
			float sm1 <== 0.4 and skip;
			float cm2 <== 0.5 and skip;
			float cm1 <== 0.2 and skip;
			float w <== 2 * cm1 and skip;
			float ar[3], ai[3] and skip;
			float temp and skip;
			i<==0 and skip;
			while(i < NumSamples)
			{
				ar[2] := cm2;
				ar[1] := cm1;
				ai[2] := sm2;
				ai[1] := sm1;
				j<==i and skip;
				n<==0 and skip;
				while(n < BlockEnd)
				{
					ar[0] := w*ar[1] - ar[2];
					ar[2] := ar[1];
					ar[1] := ar[0];

					ai[0] := w*ai[1] - ai[2];
					ai[2] := ai[1];
					ai[1] := ai[0];

					k := j + BlockEnd;
					tr := ar[0]*RealOut[k] - ai[0]*ImagOut[k];
					ti := ar[0]*ImagOut[k] + ai[0]*RealOut[k];

					RealOut[k] := RealOut[j] - tr;
					ImagOut[k] := ImagOut[j] - ti;

					RealOut[j] := RealOut[j]+tr;
					ImagOut[j] := ImagOut[j]+ti;
					j:=j+1;
					n:=n+1
				};
				i:=i+BlockSize
			};
			BlockEnd := BlockSize;
			BlockSize :=BlockSize << 1
		};
		if (InverseTransform) then
		{
			float denom <== (float)NumSamples and skip;
			i<==0 and skip;
			while(i < NumSamples)
			{
				RealOut[i] := RealOut[i]/denom;
				ImagOut[i] := ImagOut[i]/denom;
				i:=i+1
			}
		}
		else
		{
			skip
		}
	};
	unsigned int MAXSIZE and skip;
	unsigned int MAXWAVES and skip;
	unsigned int i,j and skip;
	int tmp and skip;

	float *RealIn and skip;
	float *ImagIn and skip;
	float *RealOut and skip;
	float *ImagOut and skip;
	float *coeff and skip;
	float *amp and skip;
	int invfft<==0 and skip;
	MAXSIZE<==4096 and skip;
	MAXWAVES<==4 and skip;
	RealIn<==(float*)malloc(sizeof(float)*MAXSIZE) and skip;
	ImagIn<==(float*)malloc(sizeof(float)*MAXSIZE) and skip;
	RealOut<==(float*)malloc(sizeof(float)*MAXSIZE) and skip;
	ImagOut<==(float*)malloc(sizeof(float)*MAXSIZE) and skip;
	coeff<==(float*)malloc(sizeof(float)*MAXWAVES) and skip;
	amp<==(float*)malloc(sizeof(float)*MAXWAVES) and skip;
	i<==0 and skip;
	while(i<MAXWAVES)
	{
		coeff[i] := 235%1000;
		amp[i] := 652%1000;
		i:=i+1
	};
	i<==0 and skip;
	while(i<MAXSIZE)
	{
		RealIn[i]:=0;
		j<==0 and skip;
		while(j<MAXWAVES)
		{
			if(1) then
			{
				RealIn[i]:=RealIn[i]+coeff[j]*0.3
			}
			else
			{
				RealIn[i]:=RealIn[i]+coeff[j]*0.5
			};
			ImagIn[i]:=0;
			j:=j+1
		};
		i:=i+1
	};
	fft_float(MAXSIZE,invfft,RealIn,ImagIn,RealOut,ImagOut);
	
	free(RealIn) and skip;
	free(ImagIn) and skip;
	free(RealOut) and skip;
	free(ImagOut) and skip;
	free(coeff) and skip;
	free(amp) and skip;
	tmp:=10000000;
	while(tmp>0)
	{
	  tmp:=tmp-1
	}
)