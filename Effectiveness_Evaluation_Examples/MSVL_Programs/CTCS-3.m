
/*--------------CTCS-3���п�ϵͳ---------------------------/
/*CTCS-3���п�ϵͳ�ǻ���GSM-R����ͨ��ʵ�ֳ�-����Ϣ˫���䡢
/*���߱�������(RBC)�����г����MA���п�ϵͳ��CTCS-3���п�ϵ
/*ͳ��Ŀ����������ٶȿ���ģʽ�����豸�Զ����ȵķ�ʽ�������
/*����ȫ����
/*--------------------------------------------------------*/

/*</
     define p: j<=MaxLength;
	 alw(p)
/>*/

/*</
     define p: RBC2TRAIN[9]=2;
	 define q: RBC2TRAIN[5]=2;
	 define r: RBC2TRAIN[8]=2;
	 som(p and q and r)
/>*/

</
	define p: RBC2LINK_[6]=0;
	define q: RBC2LINK_[6]=2;
	alw(p -> som(q))
/>

</
     define p1: Departure=1;
	 define p2: CalMA=1;
	 define p3: IntervalDriving=1;
	 define p4: Arrival=1;
	 som(p1;(p2;p3)#;p4)
/>

function CalculateMA() //���ݵ�·����״̬��������MA
{
	if(LinkState[k]=0 AND LinkState[k+1]=0)
	then
	{	
		MA:=k+2
	}
	else 
	{
		if(LinkState[k]=0 AND LinkState[k+1]=1)
		then
		{
			MA:=k+1
		}
		else {LinkError:=1}
	};

	if(MA>MaxLength-1)
	then 
	{
		MA:=MaxLength-1 and skip
	}
	else {empty};

	output ("Train2: Change MA...New MA is", MA)and skip
};
function CalculateMA_() //���ݵ�·����״̬��������MA
{
	if(LinkState[k_]=0 AND LinkState[k_+1]=0)
	then
	{	
		MA_:=k_+2
	}
	else 
	{
		if(LinkState[k_]=0 AND LinkState[k_+1]=1)
		then
		{
			MA_:=k_+1
		}
		else {LinkError_:=1}
	};

	if(MA_>MaxLength-1)
	then 
	{
		MA_:=MaxLength-1
	}
	else {skip};

	if(MA_=MA)
	then{
	MA_:=MA-1
	}
	else 
	{
	skip
	};

	output ("Train2: Change MA_...New MA_ is", MA_)and skip
};




frame(RailwayInfo,LinkState,MaxLength,TrainInfo,
RBC2CTC,RBC2LINK,RBC2TRAIN,
i,j,k,temp,
TrainID,rbc,MA,TrainNum,RailError,LinkError,
RegisterList,
TrainInfo_,RBC2CTC_,RBC2LINK_,RBC2TRAIN_,
i_,j_,k_,temp_,
TrainID_,rbc_,MA_,TrainNum_,RailError_,LinkError_,
num,
Departure,Arrival,CalMA,IntervalDriving) and

(
     int Departure<==1 and
	 int Arrival<==0 and 
	 int CalMA<==0 and 
	 int IntervalDriving<==0 and 
	int RailwayInfo[100] and //������ֵ���洢Ϊ�����Ƶ�·������Ϣ
	int LinkState[99] and    //��ʶ�������״̬��0��δ���� 1�����գ�
	int MaxLength and       //����������ֵ

	int TrainID,rbc,MA,TrainNum,RailError,LinkError and 
	int TrainID_,rbc_,MA_<==0,TrainNum_,RailError_,LinkError_ and
		int i,j,k,temp and
		int	TrainInfo[6] and   //�г�ע�ἰע����Ϣ
		int	RBC2CTC[6] and    //RBC��CTC�źŸ�ʽ
		int	RBC2LINK[7] and   //RBC�������豸�źŸ�ʽ
		int	RBC2TRAIN[18] and   //RBC�복���豸�źŸ�ʽ

		int i_,j_,k_,temp_ and
		int	TrainInfo_[6]  and     //�г�ע�ἰע����Ϣ
		int	RBC2CTC_[6] and      //RBC��CTC�źŸ�ʽ
		int	RBC2LINK_[7] and    //RBC�������豸�źŸ�ʽ
		int	RBC2TRAIN_[18] and  //RBC�복���豸�źŸ�ʽ

        int RegisterList[10] and //ע�����������ע���г�ID��
		

		int num<==0 and skip;
		while(num<10000000)
		{
		   num:=num+1   
		};
		num<==0 and skip;
		
	/*��ʼ����·���� */    
	MaxLength:=13;
	RailwayInfo[0]<==0 and //0����ʾ��վ
	RailwayInfo[1]<==1 and //1����ʾ���
	RailwayInfo[2]<==1 and
	RailwayInfo[3]<==0 and
	RailwayInfo[4]<==1 and
	RailwayInfo[5]<==1 and
	RailwayInfo[6]<==1 and
	RailwayInfo[7]<==0 and
	RailwayInfo[8]<==1 and
	RailwayInfo[9]<==1 and
	RailwayInfo[10]<==1 and
	RailwayInfo[11]<==1 and
	RailwayInfo[12]<==0 and skip;

	/*num<==13 and skip;
	
	while(num<9999)
	{
	   if(num%300=0)
	   then{RailwayInfo[num]<==0 and skip}
	   else{RailwayInfo[num]<==1 and skip};
	   num:=num+1   
	};*/
	
	RailwayInfo[num]<==0 and skip;

	/*��ʼ����·����״̬����ʼ״̬��Ϊ0����ÿһ�����·������ʹ�� */
	LinkState[0]<==0 and
	LinkState[1]<==0 and
	LinkState[2]<==0 and
	LinkState[3]<==0 and
	LinkState[4]<==0 and
	LinkState[5]<==0 and
	LinkState[6]<==0 and
	LinkState[7]<==0 and
	LinkState[8]<==0 and
	LinkState[9]<==0 and
	LinkState[10]<==0 and
	LinkState[11]<==0 and skip;

	num<==12 and skip;	
	/*while(num<9999)
	{
	    LinkState[num]<==0 and skip;
	   num:=num+1   
	};*/

	/*��ʼ��ע������ */    
		
		RegisterList[0]<==0 and
		RegisterList[1]<==0 and
		RegisterList[2]<==0 and
		RegisterList[3]<==0 and
		RegisterList[4]<==0 and
		RegisterList[5]<==0 and
		RegisterList[6]<==0 and
		RegisterList[7]<==0 and
		RegisterList[8]<==0 and
		RegisterList[9]<==0 and skip;
	
	(//////////////////////////////////////////////		
		i<==0 and j<==0 and 
		k<==0 and //��ʾ����ţ�ѭ����ʹ�ã�
		rbc<==-1 and //��ʶRBC���
		MA<==0 and //�г����(��ǰ��ȫ�г��������)
		TrainNum<==0 and //�г�����
		RailError<==0 and //��ʾ��ʼ�����ʱ���д���
		LinkError<==0 and //��·��������MA�����������죬��������ͣ��
		temp<==0 and skip;

		/* ***************************��ʼ�� ******************************************/
		TrainInfo[0]<==-1 and //�г���ǰ��ʻʱ��RBC���
		TrainInfo[1]<==0 and  //ע�ἰע���г�����
		TrainInfo[2]<==0 and  //�г�����(0���� 1���տ� 2������ 3���ؿ� 4������ 5������)
		TrainInfo[3]<==0 and  //�г�����(��λ��m)
		TrainInfo[4]<==0 and  //���ʱ��(��λ��km/h)
		TrainInfo[5]<==-1 and skip; //���з���(0��˳�� 1������)

		RBC2CTC[0]<==0 and  //�г�����
		RBC2CTC[1]<==-1 and //��ͷλ��(����ͷλ�����ڵĹ�������)
		RBC2CTC[2]<==-1 and //��������(0���������� 1��ͣ������ 2��MA��������)
		RBC2CTC[3]<==0 and //�г����(��ǰ��ȫ�г��������)
		RBC2CTC[4]<==0 and //��ʱ����(��λ��km/h)
		RBC2CTC[5]<==-1 and skip; //��������(0������ 1���ܾ�)

		RBC2LINK[0]<==0 and //�г�����
		RBC2LINK[1]<==-1 and //��ͷλ��(����ͷλ�����ڵĹ�������)
		RBC2LINK[2]<==-1 and //���з���(0��˳�� 1������)
		RBC2LINK[3]<==0 and //�г����MA(��ǰ��ȫ�г��������)
		RBC2LINK[4]<==0 and //��·����״̬(0��ʹ�� 1������)
		RBC2LINK[5]<==0 and //��·״̬(0������ 1������)
		RBC2LINK[6]<==0 and skip; //��·����(0���� 1��������ҵ 2���ӳ���ҵ 3��ͨ����ҵ 4�������г�)  

		RBC2TRAIN[0]<==0 and //�г�����
		RBC2TRAIN[1]<==-1 and //��ǰ��ʻ����RBC���
		RBC2TRAIN[2]<==0 and //�г�������Ȩ(0���� 1��������ҵ 2���ӳ���ҵ 3��ͨ����ҵ 4�������г�)
		RBC2TRAIN[3]<==0 and //�г����MA(��ǰ��ȫ�г��������)
		RBC2TRAIN[4]<==-1 and //�г������־����ֹͣ����ִ����Ϻ��г��������ƶ�(0���� 1����)
		RBC2TRAIN[5]<==0 and //��վ�źŵ�(0���� 1����)
		RBC2TRAIN[6]<==0 and //��վ�źŵ�(0���� 1����)
		RBC2TRAIN[7]<==0 and //�����վ�źŵ�(0���� 1����)
		RBC2TRAIN[8]<==0 and //�����վ�źŵ�(0���� 1����)
		RBC2TRAIN[9]<==0 and //�ӽ�����źŵ�(0���� 1����)
		RBC2TRAIN[10]<==0 and //ǰ�������־λ���������г���־(ǰ���������������)
		RBC2TRAIN[11]<==0 and //��������ͣ����Ϣ��Ҫ���г���ָ��λ��ǰͣ��
		RBC2TRAIN[12]<==-1 and //ͣ��״̬(0��δͣ�� 1��ͣ�ȣ�������������״̬)
		RBC2TRAIN[13]<==0 and //�г�ģʽ��Ȩ(1����ȫ���ģʽ 2��Ŀ���г�ģʽ)
		RBC2TRAIN[14]<==0 and //��ǰ�г��ȼ�(1��CTCS-3�ȼ� 2��CTCS-2�ȼ�)
		RBC2TRAIN[15]<==0 and //CTCS�ȼ�ת������(0���� 1���л�)
		RBC2TRAIN[16]<==0 and //ת���߽��źŵ�(0���� 1����)
		RBC2TRAIN[17]<==0 and skip;//RBC�л����0���� 1���л���
		/* ***************************��ʼ�� ******************************************/

		

		TrainID<==110 and skip;

		////////Register();//ע���г���Ϣbegin

	output ("Train1: ע��\n") and skip;

	i:=0 and j:=0;
	while(i<10 AND i!=-1)
	{
		if(RegisterList[i]=0)
		then 
		{
			RegisterList[i]:=TrainID and 
			i:=-1 //ѭ������
		}
		else {i:=i+1}
	};
	if(i=10)
	then {output ("Train1: Register Error! The capacity is not enought...\n") and empty} //��������������ע��
	else {empty};

	rbc:=0;

	//��¼�г������Ϣ
	
	TrainNum:=TrainNum+1; //�г���Ŀ����1	

	TrainInfo[0]:=rbc and //�г���ǰ��ʻʱ��RBC���
	TrainInfo[1]:=TrainID and //ע�ἰע���г�����
	TrainInfo[2]:=4 and //�г�����(0���� 1���տ� 2������ 3���ؿ� 4������ 5������)			
	TrainInfo[3]:=100 and //�г�����(��λ��m)
	TrainInfo[4]:=250 and //���ʱ��(��λ��km/h)
	TrainInfo[5]:=0;  //���з���(0��˳�� 1������)

	//////////ע���г���Ϣ  end


	 extern	CalculateMA() and skip;//ע��֮������MA��MA��������Ҫ����·����״̬��أ�begin


		/* ע��֮���޸��ź�λ ��׼������ */
		k:=0 and
		RBC2CTC[0]:=TrainID and
		RBC2CTC[1]:=k and //��ͷλ��0
		RBC2CTC[2]:=0 and //��������
		RBC2CTC[3]:=MA;//��ȫ�г�����
	
		RBC2LINK[0]:=TrainID and
		RBC2LINK[1]:=k and
		RBC2LINK[2]:=0 and //˳��
		RBC2LINK[3]:=MA and
		RBC2LINK[4]:=0 and //��·����ʹ��
		RBC2LINK[5]:=0;//��·״̬����
		//RBC2LINK[6]:=1 and skip; //��·���ͣ�������ҵ
	
		RBC2TRAIN[0]:=TrainID and //
		RBC2TRAIN[1]:=rbc and //
		//RBC2TRAIN[2]:=1 and //�г�������Ȩ��������ҵ
		RBC2TRAIN[3]:=MA; //

		if(k=MaxLength)
		then 
		{
			RBC2TRAIN[10]:=k
		}
		else 
		{
			RBC2TRAIN[10]:=k+1
		}; //ǰ�����������ʶ��
	
		//output ("*****j",j) and skip;
		j:=0;
		while(j<MaxLength-2)
		{
			if(RailwayInfo[j]=0 AND RailwayInfo[j+1]=0)	
			then
			{
				RailError:=1;
				j:=MaxLength
			}
			else
			{
				j:=j+1
			}
		};

		if(RailError=0 AND LinkError=0)
		then 
		{
			while(k<MaxLength AND LinkError=0)
			{	
				output ("Train1: k=",k,"  MA=",MA,"  rbc=",rbc) and skip;

				output ("\n") and skip;

				output ("Train1: The LinkStates are as follows: ",LinkState[0],LinkState[1],LinkState[2],
						LinkState[3],LinkState[4],LinkState[5],LinkState[6],LinkState[7],LinkState[8],
						LinkState[9],LinkState[10],LinkState[11]) and skip;

				output ("\n") and skip;

				if(RailwayInfo[k]=0 AND k=0)//ʼ��վ����������
				then 
				{
					if(LinkState[k]=0)//��һ������δ�����գ�������ʹ��
					then
					{	
						extern CalculateMA() and skip;//ע��֮������MA��MA��������Ҫ����·����״̬��أ�begin
						
						LinkState[k]:=1;//��һ������Ϊ������

						RBC2TRAIN[4]:=0;//�г���ͣ�ȣ�������
						RBC2TRAIN[6]:=1;//��վ�źŵ����𣬸��г�ָʾλ��
						RBC2TRAIN[7]:=1;//�����վ�źŵ����𣬸��г�ָʾλ��
			
						////DepartureDriving() //������ҵ begin
						
						Departure:=1;						
						output ("Train1: ������ҵ\n") and skip;

	                    if(RBC2CTC[2]=0)//�г���������
	                    then 
	                    {
	                   	   RBC2CTC[5]:=1 and //����õ���Ӧ�����ܷ�������
		                   RBC2LINK[6]:=1 and //RBC�������źţ���֪����
		                   RBC2LINK[4]:=1 and //�������յ�ǰ��·��������һ�����·��գ����г�ʹ�ã�
		                   RBC2TRAIN[1]:=1  //RBC����CTC����������������豸���ͷ�������
	                     }
	                     else {output ("Train1: No Departure Request...\n") and empty};
	
	                     if(RBC2TRAIN[4]=0)//�г�������
	                     then 
	                     {
		                     RBC2TRAIN[13]:=1; //���г�������ȫ���ģʽ��Ȩ
		                     RBC2TRAIN[14]:=1  //��ȫ���ģʽ��Ȩʱ��ִ��CTCS-3�ȼ�
	                     }  
	                     else 
	                     {
		                     RBC2TRAIN[13]:=2; //���г�����Ŀ���г�ģʽ��Ȩ
		                     RBC2TRAIN[14]:=2  //Ŀ���г�ģʽ��Ȩʱ��ִ��CTCS-2�ȼ�
	                     }; 

	                     if(RBC2TRAIN[6]=0)//��վ�źŵ��Ƿ���
	                     then 
	                     {
		                     MA:=MA-1
	                     } //δʻ����վ�źŵƣ�����С�г���Ȩ��ΧMA
	                     else 
	                     {
	                     	output ("Train1: Don't change MA...Move on\n") and skip;
		                    if(	RBC2TRAIN[7]=1)//�����վ�źŵ�����
		                    then 
		                    {
		                         empty
		                    }
		                    else {output ("Train1: Don't change MA...Move on\n") and skip}
	                     };

	                     RBC2TRAIN[6]:=0;//��վ�źŵ���
	                     RBC2TRAIN[7]:=0;//�����վ�źŵ���
						 
						 Departure:=0
						/////������ҵ end
					}
					else {output ("Train1: Error...It's dangerous...\n") and skip};//�����ŵĹ����ռ�ã���ʱ����Σ��״̬

					empty
				}
				else {empty};

				/************************************/
				if(k=3) 
				then 
				{
					RBC2TRAIN[2]:=3 and skip //��k=3 �趨Ϊͨ����վ����ͣ��
				} 
				else {empty};
				/***********************************/

				if(RailwayInfo[k]=0 AND k!=0 AND k!=MaxLength-1)//�м�ͣ��վ��Ҫ�ӳ���ҵ��ͣ����Ȼ�󷢳���ҵ
				then 
				{
					if(RBC2TRAIN[2]!=3)//�ڴ�վ����Ҫͣ������ͣ��
					then
					{
						//�ӳ�
						RBC2LINK[6]:=2;  //��Ȩ����ӳ���ҵ��������·��������Ϊ�ӳ���ҵ
						RBC2TRAIN[9]:=1; //�ӽ�����źŵ���
						RBC2TRAIN[5]:=1; //��վ�źŵ���
						RBC2TRAIN[8]:=1; //�����վ�źŵ���

						////ArrivalDriving();//�ӳ���ҵbegin
					  
					  Arrival:=1;
					  
					
					output ("Train1: �ӳ���ҵ\n") and skip;

	                if(RBC2LINK[6]=2) //RBC�յ��ӳ�����ź���Ȩ������·����Ϊ�ӳ���ҵ
	                then 
	                {
		               RBC2LINK[4]:=1;//�������յ�ǰ��·��������һ�����·��գ����г�ʹ�ã�
		               RBC2CTC[2]:=1  //�г���CTC����ͣ����������
	                }
	                else {output ("Train1: No Arrival Request...\n") and empty};
	
	                if(RBC2TRAIN[9]=1)//�г��Ѿ��ӽ���������ӽ�����źŵ���
	                then 
	                {
	                 	RBC2TRAIN[2]:=2 //���г����ͽӳ���ҵ��Ȩ
	                }
	                else {output ("Train1: Wait the monment...\n") and empty};

	                if(RBC2TRAIN[5]=1)
	                then
	                {
		                RBC2TRAIN[11]:=1; //��������ͣ����Ϣ��Ҫ���г���ָ��λ��ǰͣ��
		                if(RBC2TRAIN[8]=1)
		                then
		                {
		                	output ("Train1: Arrival the train...\n") and skip;
			                RBC2CTC[5]:=0; //ͣ�������������
			                 RBC2TRAIN[12]:=1 //�г���ͣ�ȣ�������������ͣ��״̬
		                 }
		                 else {output ("Train1: Wait the monment...\n") and empty}	
	}
	else {output ("Train1: Wait the monment...\n") and empty};

	RBC2TRAIN[9]:=0; //�ӽ�����źŵ���
	RBC2TRAIN[5]:=0; //��վ�źŵ���
	RBC2TRAIN[8]:=0;  //�����վ�źŵ���
	
	Arrival:=0;
					    //////�ӳ���ҵ end
						output ("Train1: The train should be stopped for a moment....\n") and skip;

						extern CalculateMA() and skip;///////////////ע��֮������MA��MA��������Ҫ����·����״̬��أ�begin
						

						if(LinkState[k]=0)
						then
						{
							LinkState[k-1]:=0;//�ͷŵ�ǰ�������������Ϊδ��ռ��
							LinkState[k]:=1;//����һ���������Ϊռ�ã�����

							//����
							RBC2CTC[2]:=0; //��������
							RBC2CTC[3]:=MA;//��ȫ�г�����
							RBC2TRAIN[4]:=0;//�г���ͣ�ȣ�������
							RBC2TRAIN[6]:=1;//��վ�źŵ����𣬸��г�ָʾλ��
							RBC2TRAIN[7]:=1;//�����վ�źŵ����𣬸��г�ָʾλ��
			
							////DepartureDriving()//������ҵ begin
							output ("Train1: ������ҵ\n") and skip;

	if(RBC2CTC[2]=0)//�г���������
	then 
	{
		RBC2CTC[5]:=1 and //����õ���Ӧ�����ܷ�������
		RBC2LINK[6]:=1 and //RBC�������źţ���֪����
		RBC2LINK[4]:=1 and //�������յ�ǰ��·��������һ�����·��գ����г�ʹ�ã�
		RBC2TRAIN[1]:=1  //RBC����CTC����������������豸���ͷ�������
	}
	else {output ("Train1: No Departure Request...\n") and empty};
	
	if(RBC2TRAIN[4]=0)//�г�������
	then 
	{
		RBC2TRAIN[13]:=1; //���г�������ȫ���ģʽ��Ȩ
		RBC2TRAIN[14]:=1  //��ȫ���ģʽ��Ȩʱ��ִ��CTCS-3�ȼ�
	}  
	else 
	{
		RBC2TRAIN[13]:=2; //���г�����Ŀ���г�ģʽ��Ȩ
		RBC2TRAIN[14]:=2  //Ŀ���г�ģʽ��Ȩʱ��ִ��CTCS-2�ȼ�
	}; 

	if(RBC2TRAIN[6]=0)//��վ�źŵ��Ƿ���
	then 
	{
		MA:=MA-1
	} //δʻ����վ�źŵƣ�����С�г���Ȩ��ΧMA
	else 
	{
		output ("Train1: Don't change MA...Move on\n") and skip;
		if(	RBC2TRAIN[7]=1)//�����վ�źŵ�����
		then 
		{
			empty
		}
		else {output ("Train1: Don't change MA...Move on\n") and skip}
	};

	RBC2TRAIN[6]:=0;//��վ�źŵ���
	RBC2TRAIN[7]:=0//�����վ�źŵ���
							//////������ҵ end
						}
						else {output ("Train1: Error...It's dangerous !\n") and skip};//�����ŵĹ����ռ�ã���ʱ����    Σ��״̬
			
						empty
					}
					else //RBC2TRAIN[2]=3��ͨ����ҵ����ͣ��
					{	
						extern CalculateMA() and skip;//////ע��֮������MA��MA��������Ҫ����·����״̬��أ�begin
						

						///PassDriving();/////ͨ����ҵ������վ�㣬��ͣ�� begin
							output ("Train1: ͨ����ҵ\n") and skip;

	                     //�ӳ����̣�ֻ��ʵ�ֽӳ���һ���̣�����ʵ��ͣ�����ӳ��������������м䲻ͣ��

	                   //�ӳ������ź�
	                    RBC2LINK[6]:=2;  //��Ȩ����ӳ���ҵ��������·��������Ϊ�ӳ���ҵ
                     	RBC2TRAIN[9]:=1; //�ӽ�����źŵ���
	RBC2TRAIN[5]:=1; //��վ�źŵ���
	RBC2TRAIN[8]:=1; //�����վ�źŵ���

	if(RBC2LINK[6]=2) //RBC�յ��ӳ�����ź���Ȩ������·����Ϊ�ӳ���ҵ
	then 
	{
		RBC2LINK[4]:=1 //�������յ�ǰ��·��������һ�����·��գ����г�ʹ�ã�
		//RBC2CTC[2]:=1 and skip //�г���CTC����ͣ����������
	}
	else {output ("Train1: No Arrival Request...\n") and empty};
	
	if(RBC2TRAIN[9]=1)//�г��Ѿ��ӽ���������ӽ�����źŵ���
	then 
	{
		RBC2TRAIN[2]:=2 //���г����ͽӳ���ҵ��Ȩ
	}
	else {output ("Train1: Wait the monment...\n") and empty};

	if(RBC2TRAIN[5]=1)
	then
	{
		RBC2TRAIN[11]:=1; //��������ͣ����Ϣ��Ҫ���г���ָ��λ��ǰͣ��
		if(RBC2TRAIN[8]=1)
		then
		{
			output ("Train1: Arrival the train...\n") and skip
			//RBC2CTC[5]:=0; //ͣ�������������
			//RBC2TRAIN[12]:=1 and skip//�г���ͣ�ȣ�������������ͣ��״̬
		}
		else {output ("Train1: Wait the monment...\n") and empty}	
	}
	else {output ("Train1: Wait the monment...\n") and empty};

	RBC2TRAIN[9]:=0; //�ӽ�����źŵ���
	RBC2TRAIN[5]:=0; //��վ�źŵ���
	RBC2TRAIN[8]:=0;  //�����վ�źŵ���

	//��������
	if(LinkState[k]=0)//����һ����δ��ռ�ã���û������
	then
	{
		LinkState[k-1]:=0;//�ͷŵ�ǰ�������������Ϊδ��ռ��
		LinkState[k]:=1;//����һ���������Ϊռ�ã�����

		//���������ź�
		RBC2CTC[2]:=0; //��������
		RBC2CTC[3]:=MA;//��ȫ�г�����
		RBC2TRAIN[6]:=1;//��վ�źŵ����𣬸��г�ָʾλ��
		RBC2TRAIN[7]:=1;//�����վ�źŵ����𣬸��г�ָʾλ��

		if(RBC2CTC[2]=0)//�г���������
		then 
		{
			RBC2CTC[5]:=1 and //����õ���Ӧ�����ܷ�������
			RBC2LINK[6]:=1 and //RBC�������źţ���֪����
			RBC2LINK[4]:=1 and //�������յ�ǰ��·��������һ�����·��գ����г�ʹ�ã�
			RBC2TRAIN[1]:=1  //RBC����CTC����������������豸���ͷ�������
		}
		else {output ("Train1: No Departure Request...\n") and empty};
		
		/* ��Ϊ��ͣ�����ʲ����������⣬�г���ԭ���ĵȼ�ģʽ�г�
		if(RBC2TRAIN[4]=0)
		then 
		{
			RBC2TRAIN[13]:=1; //���г�������ȫ���ģʽ��Ȩ
			RBC2TRAIN[14]:=1  //��ȫ���ģʽ��Ȩʱ��ִ��CTCS-3�ȼ�
		}  	
		else 
		{
			RBC2TRAIN[13]:=2; //���г�����Ŀ���г�ģʽ��Ȩ
			RBC2TRAIN[14]:=2  //Ŀ���г�ģʽ��Ȩʱ��ִ��CTCS-2�ȼ�
		}; 
		*/

		if(RBC2TRAIN[6]=0)//��վ�źŵ��Ƿ���
		then 
		{
			MA:=MA-1 and skip
		} //δʻ����վ�źŵƣ�����С�г���Ȩ��ΧMA
		else 
		{
			output ("Train1: Don't change MA...Move on\n") and skip;
			if(	RBC2TRAIN[7]=1)//�����վ�źŵ�����
			then 
			{
				empty
			}
			else {output ("Train1: Don't change MA...Move on\n") and skip}
		};

		RBC2TRAIN[6]:=0;//��վ�źŵ���
		RBC2TRAIN[7]:=0//�����վ�źŵ���
	}
	else {output ("Train1: Error...It's dangerous...\n") and skip};//�����ŵĹ����ռ�ã���ʱ����Σ��״̬

						/////ͨ����ҵ������վ�㣬��ͣ��end
						empty
					}
				}
				else {empty};

				if(RailwayInfo[k]=0 AND k=MaxLength-1)//�յ�վ���ӳ���ҵ��Ȼ��ͣ��,ͣ�Ⱥ�ע���г���Ϣ
				then 
				{
					//�ӳ�
					RBC2LINK[6]:=2;  //��Ȩ����ӳ���ҵ��������·��������Ϊ�ӳ���ҵ
					RBC2TRAIN[9]:=1; //�ӽ�����źŵ���
					RBC2TRAIN[5]:=1; //��վ�źŵ���
					RBC2TRAIN[8]:=1; //�����վ�źŵ���

					////ArrivalDriving();//�ӳ���ҵbegin
					output ("Train1: �ӳ���ҵ\n") and skip;

	if(RBC2LINK[6]=2) //RBC�յ��ӳ�����ź���Ȩ������·����Ϊ�ӳ���ҵ
	then 
	{
		RBC2LINK[4]:=1;//�������յ�ǰ��·��������һ�����·��գ����г�ʹ�ã�
		RBC2CTC[2]:=1  //�г���CTC����ͣ����������
	}
	else {output ("Train1: No Arrival Request...\n") and empty};
	
	if(RBC2TRAIN[9]=1)//�г��Ѿ��ӽ���������ӽ�����źŵ���
	then 
	{
		RBC2TRAIN[2]:=2 //���г����ͽӳ���ҵ��Ȩ
	}
	else {output ("Train1: Wait the monment...\n") and empty};

	if(RBC2TRAIN[5]=1)
	then
	{
		RBC2TRAIN[11]:=1; //��������ͣ����Ϣ��Ҫ���г���ָ��λ��ǰͣ��
		if(RBC2TRAIN[8]=1)
		then
		{
			output ("Train1: Arrival the train...\n") and skip;
			RBC2CTC[5]:=0; //ͣ�������������
			RBC2TRAIN[12]:=1 //�г���ͣ�ȣ�������������ͣ��״̬
		}
		else {output ("Train1: Wait the monment...\n") and empty}	
	}
	else {output ("Train1: Wait the monment...\n") and empty};

	RBC2TRAIN[9]:=0; //�ӽ�����źŵ���
	RBC2TRAIN[5]:=0; //��վ�źŵ���
	RBC2TRAIN[8]:=0;  //�����վ�źŵ���
					/////�ӳ���ҵend

					if(RBC2TRAIN[12]=1)//�г��Ѿ�ͣ��
					then
					{
						///Cancel() //ע���г���Ϣbegin
							output ("Train1: ע��\n") and skip;

	i:=0;
	while(i<10 AND i!=-1)
	{
		if(RegisterList[i]=TrainID)
		then 
		{
			RegisterList[i]:=0 and 
			i:=-1
		}
		else {i:=i+1}
	};
	if(i=10)
	then {output ("Train1: Cancle Error! Can't find the TrainID...\n") and empty} //���г�ID���޷�ע����ע������
	else {empty};

	LinkState[k-1]:=0;//�ͷ�ǰһ����������Ϊδ������

	//ע���г���Ϣ
	TrainInfo[0]:=-1 and //�г���ǰ��ʻʱ��RBC���
	TrainInfo[1]:=0 and  //ע�ἰע���г�����
	TrainInfo[2]:=0 and  //�г�����(0���� 1���տ� 2������ 3���ؿ� 4������ 5������)
	TrainInfo[3]:=0 and  //�г�����(��λ��m)
	TrainInfo[4]:=0 and  //���ʱ��(��λ��km/h)
	TrainInfo[5]:=-1 //���з���(0��˳�� 1������)

						/////ע���г���Ϣend
					}
					else {empty};

					empty
				}
				else {empty};


				if(k!=0 AND k%2=0 AND k!=MaxLength-1) //���վ���յ�վ�������л�RBC�����ע�ᣬ�յ�ע��
				then 
				{
					//����RBC�յ�ת��λ��Ԥ��������豸����RBCת������
					RBC2TRAIN[17]:=1;//RBC�л����0���� 1���л���	

					///ChangeRBC();//�л�RBC begin
						output ("Train1: �л�RBC\n") and skip;

	if(RBC2TRAIN[17]=1)
	then
	{
		rbc:=rbc+1;
		TrainInfo[0]:=rbc; //�г���ǰ��ʻʱ��RBC���
		RBC2TRAIN[1]:=rbc  //��ǰ��ʻ����RBC���
	}
	else {empty};

	RBC2TRAIN[17]:=0;//�л���Ϻ���������

					//////�л�RBC end
			
					empty
				}
				else {empty};
				

				if(RailwayInfo[k]=1)//վ��վ֮��,����ĳһ�����յ㣬��ʱ��������MA
				then 
				{	
				     CalMA:=1;
					 extern CalculateMA() and skip;///////////ע��֮������MA��MA��������Ҫ����·����״̬��أ�begin
					 CalMA:=0;

					if(LinkState[k]=0)
					then
					{
						LinkState[k-1]:=0;//�ͷŵ�ǰ�������������Ϊδ��ռ��
						LinkState[k]:=1;//����һ���������Ϊռ�ã�����

						RBC2TRAIN[2]:=4; //�г�������Ȩ(4�������г�)
						RBC2LINK[4]:=1;  //������һ���䣬��֤��ǰ�г����У������κ��г�����ռ��
						RBC2LINK[5]:=0;  //��·״̬����
						RBC2LINK[6]:=0;  //��·����(4�������г�)  

						////IntervalDriving()  ////�����г�begin
						
						IntervalDriving:=1;
							output ("Train1: �����г�\n") and skip;

	if(RBC2TRAIN[2]=4)//RBC�յ������г���Ȩ����
	then
	{
		RBC2TRAIN[10]:=1 //ǰ�������־λ���������г���־(ǰ���������������)
	}
	else {output ("Train1: No Interval Request...\n") and empty};

	if(RBC2TRAIN[10]=1)
	then
	{
		RBC2TRAIN[11]:=1 //��ǰ����־��ΪĿ�����г���������ͣ����Ϣ
	}
	else {output ("Train1: Wait the monment...\n") and empty};
	
	            IntervalDriving:=0
						//////�����г�end
					}
					else {output ("Train1: Error...It's dangerous !\n") and skip};//�����ŵĹ����ռ�ã���ʱ����Σ��״̬

					empty
				}
				else {empty};


				//�ȼ�ת��ʱ��ֻ�轫RBC2TRAIN[15]��Ϊ1����
				//RBC2TRAIN[15]:=1 
				if(RBC2TRAIN[15]=1) //�յ�CTCSת������
				then
				{
					RBC2TRAIN[16]:=1; //ת���߽��źŵ���
		
				////	ChangeCTCS(); //�л�CTCS�ȼ�begin
				output ("Train1: �л�CTCS�ȼ�\n")  and skip;
	
	if(TrainNum >10)
	then
	{	
		output ("Train1: Error...The capacity is not enought...\n") and skip;
		empty
	}
	else 
	{
		if(RBC2TRAIN[16]=1)
		then
		{	
			if(RBC2TRAIN[14]=1)
			then 
			{
				RBC2TRAIN[14]:=2;
				empty
			}
			else
			{
				RBC2TRAIN[14]:=1;
				empty				
			}
		}
		else {empty}
	};

	RBC2TRAIN[15]:=0; //�ȼ�ת����������
	RBC2TRAIN[16]:=0; //ת���߽��źŵ��� 
				//////�л�CTCS�ȼ�end

					empty
				}
				else {empty};

				k:=k+1

			};

			output ("Train1: The LinkStates are as follows: ",LinkState[0],LinkState[1],LinkState[2],
					LinkState[3],LinkState[4],LinkState[5],LinkState[6],LinkState[7],LinkState[8],
					LinkState[9],LinkState[10],LinkState[11]) and skip;
					output ("\n") and skip
		}
		else { empty};
	
		if(RailError=1)
		then
		{
			output ("Train1: The Railway is Error...Please input again !\n") and skip
		}
		else {empty};

		if(LinkError=1)
		then
		{
			output ("Train1: MA is Error...The train is dangerous and must be stopped immediately !\n") and skip
		}
		else {empty}
	

	)/////////////////////////////////////////////////



	||////////////////////////////////////////////////



	(/////////////////////////////////////////////////
		await(k=3);


		i_<==0 and j_<==0 and 
		k_<==0 and //��ʾ����ţ�ѭ����ʹ�ã�
		rbc_<==-1 and //��ʶRBC���
		///MA_<==0 and //�г����(��ǰ��ȫ�г��������)
		TrainNum_<==0 and //�г�����
		RailError_<==0 and //��ʾ��ʼ�����ʱ���д���
		LinkError_<==0 and //��·��������MA�����������죬��������ͣ��
		temp_<==0 and skip;

		/* ***************************��ʼ�� ******************************************/
		TrainInfo_[0]<==-1 and //�г���ǰ��ʻʱ��RBC���
		TrainInfo_[1]<==0 and  //ע�ἰע���г�����
		TrainInfo_[2]<==0 and  //�г�����(0���� 1���տ� 2������ 3���ؿ� 4������ 5������)
		TrainInfo_[3]<==0 and  //�г�����(��λ��m)
		TrainInfo_[4]<==0 and  //���ʱ��(��λ��km/h)
		TrainInfo_[5]<==-1 and skip; //���з���(0��˳�� 1������)

		RBC2CTC_[0]<==0 and  //�г�����
		RBC2CTC_[1]<==-1 and //��ͷλ��(����ͷλ�����ڵĹ�������)
		RBC2CTC_[2]<==-1 and //��������(0���������� 1��ͣ������ 2��MA��������)
		RBC2CTC_[3]<==0 and //�г����(��ǰ��ȫ�г��������)
		RBC2CTC_[4]<==0 and //��ʱ����(��λ��km/h)
		RBC2CTC_[5]<==-1 and skip; //��������(0������ 1���ܾ�)

		RBC2LINK_[0]<==0 and //�г�����
		RBC2LINK_[1]<==-1 and //��ͷλ��(����ͷλ�����ڵĹ�������)
		RBC2LINK_[2]<==-1 and //���з���(0��˳�� 1������)
		RBC2LINK_[3]<==0 and //�г����MA(��ǰ��ȫ�г��������)
		RBC2LINK_[4]<==0 and //��·����״̬(0��ʹ�� 1������)
		RBC2LINK_[5]<==0 and //��·״̬(0������ 1������)
		RBC2LINK_[6]<==0 and skip; //��·����(0���� 1��������ҵ 2���ӳ���ҵ 3��ͨ����ҵ 4�������г�)  

		RBC2TRAIN_[0]<==0 and //�г�����
		RBC2TRAIN_[1]<==-1 and //��ǰ��ʻ����RBC���
		RBC2TRAIN_[2]<==0 and //�г�������Ȩ(0���� 1��������ҵ 2���ӳ���ҵ 3��ͨ����ҵ 4�������г�)
		RBC2TRAIN_[3]<==0 and //�г����MA(��ǰ��ȫ�г��������)
		RBC2TRAIN_[4]<==-1 and //�г������־����ֹͣ����ִ����Ϻ��г��������ƶ�(0���� 1����)
		RBC2TRAIN_[5]<==0 and //��վ�źŵ�(0���� 1����)
		RBC2TRAIN_[6]<==0 and //��վ�źŵ�(0���� 1����)
		RBC2TRAIN_[7]<==0 and //�����վ�źŵ�(0���� 1����)
		RBC2TRAIN_[8]<==0 and //�����վ�źŵ�(0���� 1����)
		RBC2TRAIN_[9]<==0 and //�ӽ�����źŵ�(0���� 1����)
		RBC2TRAIN_[10]<==0 and //ǰ�������־λ���������г���־(ǰ���������������)
		RBC2TRAIN_[11]<==0 and //��������ͣ����Ϣ��Ҫ���г���ָ��λ��ǰͣ��
		RBC2TRAIN_[12]<==-1 and //ͣ��״̬(0��δͣ�� 1��ͣ�ȣ�������������״̬)
		RBC2TRAIN_[13]<==0 and //�г�ģʽ��Ȩ(1����ȫ���ģʽ 2��Ŀ���г�ģʽ)
		RBC2TRAIN_[14]<==0 and //��ǰ�г��ȼ�(1��CTCS-3�ȼ� 2��CTCS-2�ȼ�)
		RBC2TRAIN_[15]<==0 and //CTCS�ȼ�ת������(0���� 1���л�)
		RBC2TRAIN_[16]<==0 and //ת���߽��źŵ�(0���� 1����)
		RBC2TRAIN_[17]<==0 and skip;//RBC�л����0���� 1���л���
		/* ***************************��ʼ�� ******************************************/

		

		TrainID_<==119 and skip;

		///Register_();//ע���г���Ϣ begin
		output ("Train2: ע��_\n") and skip;

	i_:=0 and j_:=0 and skip;
	while(i_<10 AND i_!=-1)
	{
		if(RegisterList[i_]=0)
		then 
		{
			RegisterList[i_]:=TrainID_ and 
			i_:=-1 and skip //ѭ������
		}
		else {i_:=i_+1 and skip}
	};
	if(i_=10)
	then {output ("Train2: Register Error! The capacity is not enought...\n") and empty} //��������������ע��
	else {empty};

	rbc_:=0 and skip;

	//��¼�г������Ϣ
	
	TrainNum_:=TrainNum_+1; //�г���Ŀ����1	

	TrainInfo_[0]:=rbc_ and //�г���ǰ��ʻʱ��RBC���
	TrainInfo_[1]:=TrainID_ and //ע�ἰע���г�����
	TrainInfo_[2]:=4 and //�г�����(0���� 1���տ� 2������ 3���ؿ� 4������ 5������)			
	TrainInfo_[3]:=100 and //�г�����(��λ��m)
	TrainInfo_[4]:=250 and //���ʱ��(��λ��km/h)
	TrainInfo_[5]:=0; //���з���(0��˳�� 1������)
		/////ע���г���Ϣend

		extern CalculateMA_() and skip;//ע��֮������MA��MA��������Ҫ����·����״̬��أ�begin
		


		//skip;Cancel_();
		//output(TrainInfo_[0],TrainInfo_[1],TrainInfo_[2],TrainInfo_[3],TrainInfo_[4],TrainInfo_[5]) and  skip

		/* ע��֮���޸��ź�λ ��׼������ */
		k_:=0 and
		RBC2CTC_[0]:=TrainID_ and
		RBC2CTC_[1]:=k_ and //��ͷλ��0
		RBC2CTC_[2]:=0 and //��������
		RBC2CTC_[3]:=MA_;//��ȫ�г�����
	
		RBC2LINK_[0]:=TrainID_ and
		RBC2LINK_[1]:=k_ and
		RBC2LINK_[2]:=0 and //˳��
		RBC2LINK_[3]:=MA_ and
		RBC2LINK_[4]:=0 and //��·����ʹ��
		RBC2LINK_[5]:=0;//��·״̬����
		//RBC2LINK_[6]:=1 and skip; //��·���ͣ�������ҵ
	
		RBC2TRAIN_[0]:=TrainID_ and //
		RBC2TRAIN_[1]:=rbc_ and //
		RBC2TRAIN_[2]:=1 and //�г�������Ȩ��������ҵ
		RBC2TRAIN_[3]:=MA_; //

		if(k_=MaxLength)
		then 
		{
			RBC2TRAIN_[10]:=k_ 
		}
		else 
		{
			RBC2TRAIN_[10]:=k_+1
		}; //ǰ�����������ʶ��
	
		//output ("*****j_",j_) and skip;
		j_:=0;
		while(j_<MaxLength-2)
		{
			if(RailwayInfo[j_]=0 AND RailwayInfo[j_+1]=0)	
			then
			{
				RailError_:=1;
				j_:=MaxLength
			}
			else
			{
				j_:=j_+1
			}
		};

		if(RailError_=0 AND LinkError_=0)
		then 
		{
			while(k_<MaxLength AND LinkError_=0)
			{	
				output ("Train2: k_=",k_,"  MA_=",MA_,"  rbc_=",rbc_) and skip;

				output ("\n") and skip;

				output ("Train2: The LinkStates are as follows: ",LinkState[0],LinkState[1],LinkState[2],
						LinkState[3],LinkState[4],LinkState[5],LinkState[6],LinkState[7],LinkState[8],
						LinkState[9],LinkState[10],LinkState[11]) and skip;

						output ("\n") and skip;
				if(RailwayInfo[k_]=0 AND k_=0)//ʼ��վ����������
				then 
				{
					if(LinkState[k_]=0)//��һ������δ�����գ�������ʹ��
					then
					{	
						extern CalculateMA_() and skip;////////ע��֮������MA��MA��������Ҫ����·����״̬��أ�begin
						
						LinkState[k_]:=1;//��һ������Ϊ������

						RBC2TRAIN_[4]:=0;//�г���ͣ�ȣ�������
						RBC2TRAIN_[6]:=1;//��վ�źŵ����𣬸��г�ָʾλ��
						RBC2TRAIN_[7]:=1;//�����վ�źŵ����𣬸��г�ָʾλ��
			
						///DepartureDriving_()  //������ҵ begin
							output ("Train2: ������ҵ_\n") and skip;

	if(RBC2CTC_[2]=0)//�г���������
	then 
	{
		RBC2CTC_[5]:=1 and //����õ���Ӧ�����ܷ�������
		RBC2LINK_[6]:=1 and //RBC�������źţ���֪����
		RBC2LINK_[4]:=1 and //�������յ�ǰ��·��������һ�����·��գ����г�ʹ�ã�
		RBC2TRAIN_[1]:=1  //RBC����CTC����������������豸���ͷ�������
	}
	else {output ("Train2: No Departure Request...\n") and empty};
	
	if(RBC2TRAIN_[4]=0)//�г�������
	then 
	{
		RBC2TRAIN_[13]:=1; //���г�������ȫ���ģʽ��Ȩ
		RBC2TRAIN_[14]:=1  //��ȫ���ģʽ��Ȩʱ��ִ��CTCS-3�ȼ�
	}  
	else 
	{
		RBC2TRAIN_[13]:=2; //���г�����Ŀ���г�ģʽ��Ȩ
		RBC2TRAIN_[14]:=2  //Ŀ���г�ģʽ��Ȩʱ��ִ��CTCS-2�ȼ�
	}; 

	if(RBC2TRAIN_[6]=0)//��վ�źŵ��Ƿ���
	then 
	{
		MA_:=MA_-1
	} //δʻ����վ�źŵƣ�����С�г���Ȩ��ΧMA
	else 
	{
		output ("Train2: Don't change MA_...Move on\n") and skip;
		if(	RBC2TRAIN_[7]=1)//�����վ�źŵ�����
		then 
		{
			empty
		}
		else {output ("Train2: Don't change MA_...Move on\n") and skip}
	};

	RBC2TRAIN_[6]:=0;//��վ�źŵ���
	RBC2TRAIN_[7]:=0//�����վ�źŵ���
						/////������ҵend
					}
					else {output ("Train2: Error...It's dangerous...\n") and skip};//�����ŵĹ����ռ�ã���ʱ����Σ��״̬

					empty
				}
				else {empty};

				/************************************/
				if(k_=3) 
				then 
				{
					RBC2TRAIN_[2]:=3 and skip //��k=3 �趨Ϊͨ����վ����ͣ��
				} 
				else {empty};
				/***********************************/

				if(RailwayInfo[k_]=0 AND k_!=0 AND k_!=MaxLength-1)//�м�ͣ��վ��Ҫ�ӳ���ҵ��ͣ����Ȼ�󷢳���ҵ
				then 
				{
					if(RBC2TRAIN_[2]!=3)//�ڴ�վ����Ҫͣ������ͣ��
					then
					{
						//�ӳ�
						RBC2LINK_[6]:=2;  //��Ȩ����ӳ���ҵ��������·��������Ϊ�ӳ���ҵ
						RBC2TRAIN_[9]:=1; //�ӽ�����źŵ���
						RBC2TRAIN_[5]:=1; //��վ�źŵ���
						RBC2TRAIN_[8]:=1; //�����վ�źŵ���

						////ArrivalDriving_();//�ӳ���ҵ begin
							output ("Train2: �ӳ���ҵ_\n") and skip;

	if(RBC2LINK_[6]=2) //RBC�յ��ӳ�����ź���Ȩ������·����Ϊ�ӳ���ҵ
	then 
	{
		RBC2LINK_[4]:=1;//�������յ�ǰ��·��������һ�����·��գ����г�ʹ�ã�
		RBC2CTC_[2]:=1 //�г���CTC����ͣ����������
	}
	else {output ("Train2: No Arrival Request...\n") and empty};
	
	if(RBC2TRAIN_[9]=1)//�г��Ѿ��ӽ���������ӽ�����źŵ���
	then 
	{
		RBC2TRAIN_[2]:=2 //���г����ͽӳ���ҵ��Ȩ
	}
	else {output ("Train2: Wait the monment...\n") and empty};

	if(RBC2TRAIN_[5]=1)
	then
	{
		RBC2TRAIN_[11]:=1; //��������ͣ����Ϣ��Ҫ���г���ָ��λ��ǰͣ��
		if(RBC2TRAIN_[8]=1)
		then
		{
			output ("Train2: Arrival the train...\n") and skip;
			RBC2CTC_[5]:=0; //ͣ�������������
			RBC2TRAIN_[12]:=1 //�г���ͣ�ȣ�������������ͣ��״̬
		}
		else {output ("Train2: Wait the monment...\n") and empty}	
	}
	else {output ("Train2: Wait the monment...\n") and empty};

	RBC2TRAIN_[9]:=0; //�ӽ�����źŵ���
	RBC2TRAIN_[5]:=0; //��վ�źŵ���
	RBC2TRAIN_[8]:=0;  //�����վ�źŵ���
						//////�ӳ���ҵend
					
						output ("Train2: The train should be stopped for a moment....\n") and skip;

					  extern CalculateMA_() and skip;///////////////ע��֮������MA��MA��������Ҫ����·����״̬��أ�begin
					

						if(LinkState[k_]=0)
						then
						{
							LinkState[k_-1]:=0;//�ͷŵ�ǰ�������������Ϊδ��ռ��
							LinkState[k_]:=1;//����һ���������Ϊռ�ã�����

							//����
							RBC2CTC_[2]:=0; //��������
							RBC2CTC_[3]:=MA_;//��ȫ�г�����
							RBC2TRAIN_[4]:=0;//�г���ͣ�ȣ�������
							RBC2TRAIN_[6]:=1;//��վ�źŵ����𣬸��г�ָʾλ��
							RBC2TRAIN_[7]:=1;//�����վ�źŵ����𣬸��г�ָʾλ��
			
							///DepartureDriving_()//������ҵbegin
								output ("Train2: ������ҵ_\n") and skip;

	if(RBC2CTC_[2]=0)//�г���������
	then 
	{
		RBC2CTC_[5]:=1 and //����õ���Ӧ�����ܷ�������
		RBC2LINK_[6]:=1 and //RBC�������źţ���֪����
		RBC2LINK_[4]:=1 and //�������յ�ǰ��·��������һ�����·��գ����г�ʹ�ã�
		RBC2TRAIN_[1]:=1  //RBC����CTC����������������豸���ͷ�������
	}
	else {output ("Train2: No Departure Request...\n") and empty};
	
	if(RBC2TRAIN_[4]=0)//�г�������
	then 
	{
		RBC2TRAIN_[13]:=1; //���г�������ȫ���ģʽ��Ȩ
		RBC2TRAIN_[14]:=1  //��ȫ���ģʽ��Ȩʱ��ִ��CTCS-3�ȼ�
	}  
	else 
	{
		RBC2TRAIN_[13]:=2; //���г�����Ŀ���г�ģʽ��Ȩ
		RBC2TRAIN_[14]:=2  //Ŀ���г�ģʽ��Ȩʱ��ִ��CTCS-2�ȼ�
	}; 

	if(RBC2TRAIN_[6]=0)//��վ�źŵ��Ƿ���
	then 
	{
		MA_:=MA_-1
	} //δʻ����վ�źŵƣ�����С�г���Ȩ��ΧMA
	else 
	{
		output ("Train2: Don't change MA_...Move on\n") and skip;
		if(	RBC2TRAIN_[7]=1)//�����վ�źŵ�����
		then 
		{
			empty
		}
		else {output ("Train2: Don't change MA_...Move on\n") and skip}
	};

	RBC2TRAIN_[6]:=0;//��վ�źŵ���
	RBC2TRAIN_[7]:=0//�����վ�źŵ���
							//////������ҵend
						}
						else {output ("Train2: Error...It's dangerous !\n") and skip};//�����ŵĹ����ռ�ã���ʱ����    Σ��״̬
			
						empty
					}
					else //RBC2TRAIN_[2]=3��ͨ����ҵ����ͣ��
					{	
						extern CalculateMA_() and skip;/////////////ע��֮������MA��MA��������Ҫ����·����״̬��أ�begin
						
						///PassDriving_(); //ͨ����ҵ������վ�㣬��ͣ��begin
							output ("Train2: ͨ����ҵ_") and skip;

	//�ӳ����̣�ֻ��ʵ�ֽӳ���һ���̣�����ʵ��ͣ�����ӳ��������������м䲻ͣ��

	//�ӳ������ź�
	RBC2LINK_[6]:=2;  //��Ȩ����ӳ���ҵ��������·��������Ϊ�ӳ���ҵ
	RBC2TRAIN_[9]:=1; //�ӽ�����źŵ���
	RBC2TRAIN_[5]:=1; //��վ�źŵ���
	RBC2TRAIN_[8]:=1; //�����վ�źŵ���

	if(RBC2LINK_[6]=2) //RBC�յ��ӳ�����ź���Ȩ������·����Ϊ�ӳ���ҵ
	then 
	{
		RBC2LINK_[4]:=1 //�������յ�ǰ��·��������һ�����·��գ����г�ʹ�ã�
		//RBC2CTC_[2]:=1 and skip //�г���CTC����ͣ����������
	}
	else {output ("Train2: No Arrival Request...") and empty};
	
	if(RBC2TRAIN_[9]=1)//�г��Ѿ��ӽ���������ӽ�����źŵ���
	then 
	{
		RBC2TRAIN_[2]:=2 //���г����ͽӳ���ҵ��Ȩ
	}
	else {output ("Train2: Wait the monment...") and empty};

	if(RBC2TRAIN_[5]=1)
	then
	{
		RBC2TRAIN_[11]:=1; //��������ͣ����Ϣ��Ҫ���г���ָ��λ��ǰͣ��
		if(RBC2TRAIN_[8]=1)
		then
		{
			output ("Train2: Arrival the train...") and skip
			//RBC2CTC_[5]:=0; //ͣ�������������
			//RBC2TRAIN_[12]:=1 and skip//�г���ͣ�ȣ�������������ͣ��״̬
		}
		else {output ("Train2: Wait the monment...") and empty}	
	}
	else {output ("Train2: Wait the monment...") and empty};

	RBC2TRAIN_[9]:=0; //�ӽ�����źŵ���
	RBC2TRAIN_[5]:=0; //��վ�źŵ���
	RBC2TRAIN_[8]:=0;  //�����վ�źŵ���

	//��������
	if(LinkState[k_]=0)//����һ����δ��ռ�ã���û������
	then
	{
		LinkState[k_-1]:=0;//�ͷŵ�ǰ�������������Ϊδ��ռ��
		LinkState[k_]:=1;//����һ���������Ϊռ�ã�����

		//���������ź�
		RBC2CTC_[2]:=0; //��������
		RBC2CTC_[3]:=MA_;//��ȫ�г�����
		RBC2TRAIN_[6]:=1;//��վ�źŵ����𣬸��г�ָʾλ��
		RBC2TRAIN_[7]:=1;//�����վ�źŵ����𣬸��г�ָʾλ��

		if(RBC2CTC_[2]=0)//�г���������
		then 
		{
			RBC2CTC_[5]:=1 and //����õ���Ӧ�����ܷ�������
			RBC2LINK_[6]:=1 and //RBC�������źţ���֪����
			RBC2LINK_[4]:=1 and //�������յ�ǰ��·��������һ�����·��գ����г�ʹ�ã�
			RBC2TRAIN_[1]:=1 and skip //RBC����CTC����������������豸���ͷ�������
		}
		else {output ("Train2: No Departure Request...") and empty};
		
		/* ��Ϊ��ͣ�����ʲ����������⣬�г���ԭ���ĵȼ�ģʽ�г�
		if(RBC2TRAIN_[4]=0)
		then 
		{
			RBC2TRAIN_[13]:=1; //���г�������ȫ���ģʽ��Ȩ
			RBC2TRAIN_[14]:=1  //��ȫ���ģʽ��Ȩʱ��ִ��CTCS-3�ȼ�
		}  	
		else 
		{
			RBC2TRAIN_[13]:=2; //���г�����Ŀ���г�ģʽ��Ȩ
			RBC2TRAIN_[14]:=2  //Ŀ���г�ģʽ��Ȩʱ��ִ��CTCS-2�ȼ�
		}; 
		*/

		if(RBC2TRAIN_[6]=0)//��վ�źŵ��Ƿ���
		then 
		{
			MA_:=MA_-1 and skip
		} //δʻ����վ�źŵƣ�����С�г���Ȩ��ΧMA
		else 
		{
			output ("Train2: Don't change MA_...Move on") and skip;
			if(	RBC2TRAIN_[7]=1)//�����վ�źŵ�����
			then 
			{
				empty
			}
			else {output ("Train2: Don't change MA_...Move on") and skip}
		};

		RBC2TRAIN_[6]:=0;//��վ�źŵ���
		RBC2TRAIN_[7]:=0//�����վ�źŵ���
	}
	else {output ("Train2: Error...It's dangerous...") and skip};//�����ŵĹ����ռ�ã���ʱ����Σ��״̬

						/////ͨ����ҵ������վ�㣬��ͣ��end
						empty
					}
				}
				else {empty};

				if(RailwayInfo[k_]=0 AND k_=MaxLength-1)//�յ�վ���ӳ���ҵ��Ȼ��ͣ��,ͣ�Ⱥ�ע���г���Ϣ
				then 
				{
					//�ӳ�
					RBC2LINK_[6]:=2;  //��Ȩ����ӳ���ҵ��������·��������Ϊ�ӳ���ҵ
					RBC2TRAIN_[9]:=1; //�ӽ�����źŵ���
					RBC2TRAIN_[5]:=1; //��վ�źŵ���
					RBC2TRAIN_[8]:=1; //�����վ�źŵ���

					////ArrivalDriving_(); //�ӳ���ҵbegin
						output ("Train2: �ӳ���ҵ_") and skip;

	if(RBC2LINK_[6]=2) //RBC�յ��ӳ�����ź���Ȩ������·����Ϊ�ӳ���ҵ
	then 
	{
		RBC2LINK_[4]:=1;//�������յ�ǰ��·��������һ�����·��գ����г�ʹ�ã�
		RBC2CTC_[2]:=1 //�г���CTC����ͣ����������
	}
	else {output ("Train2: No Arrival Request...") and empty};
	
	if(RBC2TRAIN_[9]=1)//�г��Ѿ��ӽ���������ӽ�����źŵ���
	then 
	{
		RBC2TRAIN_[2]:=2 //���г����ͽӳ���ҵ��Ȩ
	}
	else {output ("Train2: Wait the monment...") and empty};

	if(RBC2TRAIN_[5]=1)
	then
	{
		RBC2TRAIN_[11]:=1; //��������ͣ����Ϣ��Ҫ���г���ָ��λ��ǰͣ��
		if(RBC2TRAIN_[8]=1)
		then
		{
			output ("Train2: Arrival the train...") and skip;
			RBC2CTC_[5]:=0; //ͣ�������������
			RBC2TRAIN_[12]:=1 //�г���ͣ�ȣ�������������ͣ��״̬
		}
		else {output ("Train2: Wait the monment...") and empty}	
	}
	else {output ("Train2: Wait the monment...") and empty};

	RBC2TRAIN_[9]:=0; //�ӽ�����źŵ���
	RBC2TRAIN_[5]:=0; //��վ�źŵ���
	RBC2TRAIN_[8]:=0;  //�����վ�źŵ���
					//////�ӳ���ҵend

					if(RBC2TRAIN_[12]=1)//�г��Ѿ�ͣ��
					then
					{
						///Cancel_() //ע���г���Ϣbegin
							output ("Train2: ע��_") and skip;

	i_:=0 and skip;
	while(i_<10 AND i_!=-1)
	{
		if(RegisterList[i_]=TrainID_)
		then 
		{
			RegisterList[i_]:=0 and 
			i_:=-1 and skip
		}
		else {i_:=i_+1 and skip}
	};
	if(i_=10)
	then {output ("Train2: Cancle Error! Can't find the TrainID...") and empty} //���г�ID���޷�ע����ע������
	else {empty};

	LinkState[k_-1]:=0;//�ͷ�ǰһ����������Ϊδ������

	//ע���г���Ϣ
	TrainInfo_[0]:=-1 and //�г���ǰ��ʻʱ��RBC���
	TrainInfo_[1]:=0 and  //ע�ἰע���г�����
	TrainInfo_[2]:=0 and  //�г�����(0���� 1���տ� 2������ 3���ؿ� 4������ 5������)
	TrainInfo_[3]:=0 and  //�г�����(��λ��m)
	TrainInfo_[4]:=0 and  //���ʱ��(��λ��km/h)
	TrainInfo_[5]:=-1 and skip //���з���(0��˳�� 1������)
						//ע���г���Ϣend
					}
					else {empty};

					empty
				}
				else {empty};


				if(k_!=0 AND k_%2=0 AND k_!=MaxLength-1) //���վ���յ�վ�������л�RBC�����ע�ᣬ�յ�ע��
				then 
				{
					//����RBC�յ�ת��λ��Ԥ��������豸����RBCת������
					RBC2TRAIN_[17]:=1;//RBC�л����0���� 1���л���	

					///ChangeRBC_();//�л�RBC begin
					output ("Train2: �л�RBC_") and skip;

	if(RBC2TRAIN_[17]=1)
	then
	{
		rbc_:=rbc_+1;
		TrainInfo_[0]:=rbc_; //�г���ǰ��ʻʱ��RBC���
		RBC2TRAIN_[1]:=rbc_  //��ǰ��ʻ����RBC���
	}
	else {empty};

	RBC2TRAIN_[17]:=0;//�л���Ϻ���������
					/////�л�RBC end
			
					empty
				}
				else {empty};


				if(RailwayInfo[k_]=1)//վ��վ֮��,����ĳһ�����յ㣬��ʱ��������MA
				then 
				{	
					extern CalculateMA_() and skip;////////ע��֮������MA��MA��������Ҫ����·����״̬��أ�begin
					

					if(LinkState[k_]=0)
					then
					{
						LinkState[k_-1]:=0;//�ͷŵ�ǰ�������������Ϊδ��ռ��
						LinkState[k_]:=1;//����һ���������Ϊռ�ã�����

						RBC2TRAIN_[2]:=4; //�г�������Ȩ(4�������г�)
						RBC2LINK_[4]:=1;  //������һ���䣬��֤��ǰ�г����У������κ��г�����ռ��
						RBC2LINK_[5]:=0;  //��·״̬����
						RBC2LINK_[6]:=0;  //��·����(4�������г�)  

						///IntervalDriving_() ///�����г�begin
							output ("Train2: �����г�_") and skip;

	if(RBC2TRAIN_[2]=4)//RBC�յ������г���Ȩ����
	then
	{
		RBC2TRAIN_[10]:=1 //ǰ�������־λ���������г���־(ǰ���������������)
	}
	else {output ("Train2: No Interval Request...") and empty};

	if(RBC2TRAIN_[10]=1)
	then
	{
		RBC2TRAIN_[11]:=1 //��ǰ����־��ΪĿ�����г���������ͣ����Ϣ
	}
	else {output ("Train2: Wait the monment...") and empty}
						///////�����г�end
					}
					else {output ("Train2: Error...It's dangerous !") and skip};//�����ŵĹ����ռ�ã���ʱ����Σ��״̬

					empty
				}
				else {empty};


				//�ȼ�ת��ʱ��ֻ�轫RBC2TRAIN[15]��Ϊ1����
				//RBC2TRAIN_[15]:=1 
				if(RBC2TRAIN_[15]=1) //�յ�CTCSת������
				then
				{
					RBC2TRAIN_[16]:=1; //ת���߽��źŵ���
		
					///ChangeCTCS_(); //�л�CTCS�ȼ� begin
						output ("Train2: �л�CTCS�ȼ�_")  and skip;
	
	if(TrainNum_ >10)
	then
	{	
		output ("Train2: Error...The capacity is not enought...") and skip;
		empty
	}
	else 
	{
		if(RBC2TRAIN_[16]=1)
		then
		{	
			if(RBC2TRAIN_[14]=1)
			then 
			{
				RBC2TRAIN_[14]:=2;
				empty
			}
			else
			{
				RBC2TRAIN_[14]:=1;
				empty				
			}
		}
		else {empty}
	};

	RBC2TRAIN_[15]:=0; //�ȼ�ת����������
	RBC2TRAIN_[16]:=0; //ת���߽��źŵ��� 
					/////�л�CTCS�ȼ�end

					empty
				}
				else {empty};

				k_:=k_+1

			};

			output ("Train2: The LinkStates are as follows: ",LinkState[0],LinkState[1],LinkState[2],
					LinkState[3],LinkState[4],LinkState[5],LinkState[6],LinkState[7],LinkState[8],
					LinkState[9],LinkState[10],LinkState[11]) and skip;
					output ("\n") and skip 
		}
		else { empty};
	
		if(RailError_=1)
		then
		{
			output ("Train2: The Railway is Error...Please input again !\n") and skip
		}
		else {empty};

		if(LinkError_=1)
		then
		{
			output ("Train2: MA_ is Error...The train is dangerous and must be stopped immediately !\n") and skip
		}
		else {empty}
		)//////////////////////////////////////////////////
)

