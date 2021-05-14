//@ ltl invariant positive: [](AP(0<=MAXSIZE) && AP(0<=MAXWAVES));


unsigned NumberOfBitsNeeded ( unsigned PowerOfTwo )
{
    unsigned i;

    for ( i=0; ; i++ )
    {
        if ( PowerOfTwo & (1 << i) )
            return i;
    }
}



unsigned ReverseBits ( unsigned index, unsigned NumBits )
{
    unsigned i, rev;

    for ( i=rev=0; i < NumBits; i++ )
    {
        rev = (rev << 1) | (index & 1);
        index >>= 1;
    }

    return rev;
}

void fft_float (
    unsigned  NumSamples,
    int       InverseTransform,
    float    *RealIn,
    float    *ImagIn,
    float    *RealOut,
    float    *ImagOut )
{
    unsigned NumBits;   
    unsigned i, j, k, n;
    unsigned BlockSize, BlockEnd;

    double angle_numerator = 2.0 * 3.14159265358979323846;
    double tr, ti;   


    if ( InverseTransform )
        angle_numerator = -angle_numerator;


    NumBits = NumberOfBitsNeeded ( NumSamples );



    for ( i=0; i < NumSamples; i++ )
    {
        j = ReverseBits ( i, NumBits );
        RealOut[j] = RealIn[i];
        ImagOut[j] = (ImagIn == NULL) ? 0.0 : ImagIn[i];
    }



    BlockEnd = 1;
    for ( BlockSize = 2; BlockSize <= NumSamples; BlockSize <<= 1 )
    {
        double delta_angle = angle_numerator / (double)BlockSize;
        double sm2 = 0.3;
        double sm1 = 0.4;
        double cm2 = 0.5;
        double cm1 = 0.2;
        double w = 2 * cm1;
        double ar[3], ai[3];
        double temp;

        for ( i=0; i < NumSamples; i += BlockSize )
        {
            ar[2] = cm2;
            ar[1] = cm1;

            ai[2] = sm2;
            ai[1] = sm1;

            for ( j=i, n=0; n < BlockEnd; j++, n++ )
            {
                ar[0] = w*ar[1] - ar[2];
                ar[2] = ar[1];
                ar[1] = ar[0];

                ai[0] = w*ai[1] - ai[2];
                ai[2] = ai[1];
                ai[1] = ai[0];

                k = j + BlockEnd;
                tr = ar[0]*RealOut[k] - ai[0]*ImagOut[k];
                ti = ar[0]*ImagOut[k] + ai[0]*RealOut[k];

                RealOut[k] = RealOut[j] - tr;
                ImagOut[k] = ImagOut[j] - ti;

                RealOut[j] += tr;
                ImagOut[j] += ti;
            }
        }

        BlockEnd = BlockSize;
    }


    if ( InverseTransform )
    {
        double denom = (double)NumSamples;

        for ( i=0; i < NumSamples; i++ )
        {
            RealOut[i] /= denom;
            ImagOut[i] /= denom;
        }
    }
}


int MAXSIZE;
int MAXWAVES;
int i;
int j;
int tmp;
int main() {

	float *RealIn;
	float *ImagIn;
	float *RealOut;
	float *ImagOut;
	float *coeff;
	float *amp;
	int invfft=0;

	MAXSIZE=4096;
	MAXWAVES=4;
		


 RealIn=(float*)malloc(sizeof(float)*MAXSIZE);
 ImagIn=(float*)malloc(sizeof(float)*MAXSIZE);
 RealOut=(float*)malloc(sizeof(float)*MAXSIZE);
 ImagOut=(float*)malloc(sizeof(float)*MAXSIZE);
 coeff=(float*)malloc(sizeof(float)*MAXWAVES);
 amp=(float*)malloc(sizeof(float)*MAXWAVES);

	for(i=0;i<MAXWAVES;i++) 
	{
		coeff[i] = 235%1000;
		amp[i] = 652%1000;
	}
 for(i=0;i<MAXSIZE;i++) 
 {

	 RealIn[i]=0;
	 for(j=0;j<MAXWAVES;j++) 
	 {
		 if (1)
		 {
		 		RealIn[i]+=coeff[j]*0.3;
			}
		 else
		 {
		 	RealIn[i]+=coeff[j]*0.5;
		 }
  	 ImagIn[i]=0;
	 }
 }

 fft_float (MAXSIZE,invfft,RealIn,ImagIn,RealOut,ImagOut);
 
 free(RealIn);
 free(ImagIn);
 free(RealOut);
 free(ImagOut);
 free(coeff);
 free(amp);
 tmp=10000000;
 while (tmp>0) {tmp=tmp-1;}

}
