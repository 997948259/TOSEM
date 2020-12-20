
/*--------------CTCS-3级列控系统---------------------------/
/*CTCS-3级列控系统是基于GSM-R无线通信实现车-地信息双向传输、
/*无线闭塞中心(RBC)生成行车许可MA的列控系统。CTCS-3级列控系
/*统以目标距离连续速度控制模式、以设备自动优先的方式来监控列
/*车安全运行
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

function CalculateMA() //根据道路联锁状态，来计算MA
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
function CalculateMA_() //根据道路联锁状态，来计算MA
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
	int RailwayInfo[100] and //输入数值，存储为二进制道路区间信息
	int LinkState[99] and    //标识轨道锁闭状态（0：未锁闭 1：锁闭）
	int MaxLength and       //轨道区间最大值

	int TrainID,rbc,MA,TrainNum,RailError,LinkError and 
	int TrainID_,rbc_,MA_<==0,TrainNum_,RailError_,LinkError_ and
		int i,j,k,temp and
		int	TrainInfo[6] and   //列车注册及注销信息
		int	RBC2CTC[6] and    //RBC与CTC信号格式
		int	RBC2LINK[7] and   //RBC与联锁设备信号格式
		int	RBC2TRAIN[18] and   //RBC与车载设备信号格式

		int i_,j_,k_,temp_ and
		int	TrainInfo_[6]  and     //列车注册及注销信息
		int	RBC2CTC_[6] and      //RBC与CTC信号格式
		int	RBC2LINK_[7] and    //RBC与联锁设备信号格式
		int	RBC2TRAIN_[18] and  //RBC与车载设备信号格式

        int RegisterList[10] and //注册链表，存放已注册列车ID号
		

		int num<==0 and skip;
		while(num<10000000)
		{
		   num:=num+1   
		};
		num<==0 and skip;
		
	/*初始化道路区间 */    
	MaxLength:=13;
	RailwayInfo[0]<==0 and //0：表示车站
	RailwayInfo[1]<==1 and //1：表示轨道
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

	/*初始化道路联锁状态，初始状态都为0，即每一区间道路都可以使用 */
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

	/*初始化注册链表 */    
		
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
		k<==0 and //表示区间号（循环中使用）
		rbc<==-1 and //标识RBC编号
		MA<==0 and //行车许可(当前安全行车的区间号)
		TrainNum<==0 and //列车数量
		RailError<==0 and //表示初始化轨道时候有错误
		LinkError<==0 and //道路联锁错误，MA不能正常延伸，触发紧急停车
		temp<==0 and skip;

		/* ***************************初始化 ******************************************/
		TrainInfo[0]<==-1 and //列车当前行驶时的RBC编号
		TrainInfo[1]<==0 and  //注册及注销列车车次
		TrainInfo[2]<==0 and  //列车类型(0：无 1：普快 2：快速 3：特快 4：动车 5：高铁)
		TrainInfo[3]<==0 and  //列车长度(单位：m)
		TrainInfo[4]<==0 and  //最高时速(单位：km/h)
		TrainInfo[5]<==-1 and skip; //运行方向(0：顺行 1：逆行)

		RBC2CTC[0]<==0 and  //列车车次
		RBC2CTC[1]<==-1 and //车头位置(即车头位置所在的轨道区间号)
		RBC2CTC[2]<==-1 and //请求命令(0：发车请求 1：停车请求 2：MA延伸请求)
		RBC2CTC[3]<==0 and //行车许可(当前安全行车的区间号)
		RBC2CTC[4]<==0 and //临时限速(单位：km/h)
		RBC2CTC[5]<==-1 and skip; //接受命令(0：接受 1：拒绝)

		RBC2LINK[0]<==0 and //列车车次
		RBC2LINK[1]<==-1 and //车头位置(即车头位置所在的轨道区间号)
		RBC2LINK[2]<==-1 and //运行方向(0：顺行 1：逆行)
		RBC2LINK[3]<==0 and //行车许可MA(当前安全行车的区间号)
		RBC2LINK[4]<==0 and //道路联锁状态(0：使用 1：锁闭)
		RBC2LINK[5]<==0 and //进路状态(0：正常 1：出错)
		RBC2LINK[6]<==0 and skip; //进路类型(0：无 1：发车作业 2：接车作业 3：通过作业 4：区间行车)  

		RBC2TRAIN[0]<==0 and //列车车次
		RBC2TRAIN[1]<==-1 and //当前行驶区间RBC编号
		RBC2TRAIN[2]<==0 and //行车命令授权(0：无 1：发车作业 2：接车作业 3：通过作业 4：区间行车)
		RBC2TRAIN[3]<==0 and //行车许可MA(当前安全行车的区间号)
		RBC2TRAIN[4]<==-1 and //列车溜入标志，即停止命令执行完毕后，列车依旧在移动(0：无 1：有)
		RBC2TRAIN[5]<==0 and //进站信号灯(0：灭 1：亮)
		RBC2TRAIN[6]<==0 and //出站信号灯(0：灭 1：亮)
		RBC2TRAIN[7]<==0 and //反向进站信号灯(0：灭 1：亮)
		RBC2TRAIN[8]<==0 and //反向出站信号灯(0：灭 1：亮)
		RBC2TRAIN[9]<==0 and //接近轨道信号灯(0：灭 1：亮)
		RBC2TRAIN[10]<==0 and //前方区间标志位，即区间行车标志(前方到达轨道的区间号)
		RBC2TRAIN[11]<==0 and //条件紧急停车消息，要求列车在指定位置前停车
		RBC2TRAIN[12]<==-1 and //停车状态(0：未停稳 1：停稳，并向联锁发送状态)
		RBC2TRAIN[13]<==0 and //行车模式授权(1：完全监控模式 2：目视行车模式)
		RBC2TRAIN[14]<==0 and //当前行车等级(1：CTCS-3等级 2：CTCS-2等级)
		RBC2TRAIN[15]<==0 and //CTCS等级转换命令(0：无 1：切换)
		RBC2TRAIN[16]<==0 and //转换边界信号灯(0：灭 1：亮)
		RBC2TRAIN[17]<==0 and skip;//RBC切换命令（0：无 1：切换）
		/* ***************************初始化 ******************************************/

		

		TrainID<==110 and skip;

		////////Register();//注册列车信息begin

	output ("Train1: 注册\n") and skip;

	i:=0 and j:=0;
	while(i<10 AND i!=-1)
	{
		if(RegisterList[i]=0)
		then 
		{
			RegisterList[i]:=TrainID and 
			i:=-1 //循环结束
		}
		else {i:=i+1}
	};
	if(i=10)
	then {output ("Train1: Register Error! The capacity is not enought...\n") and empty} //超过容量，不能注册
	else {empty};

	rbc:=0;

	//记录列车相关信息
	
	TrainNum:=TrainNum+1; //列车数目自增1	

	TrainInfo[0]:=rbc and //列车当前行驶时的RBC编号
	TrainInfo[1]:=TrainID and //注册及注销列车车次
	TrainInfo[2]:=4 and //列车类型(0：无 1：普快 2：快速 3：特快 4：动车 5：高铁)			
	TrainInfo[3]:=100 and //列车长度(单位：m)
	TrainInfo[4]:=250 and //最高时速(单位：km/h)
	TrainInfo[5]:=0;  //运行方向(0：顺行 1：逆行)

	//////////注册列车信息  end


	 extern	CalculateMA() and skip;//注册之后，延伸MA（MA的延伸需要跟道路联锁状态相关）begin


		/* 注册之后，修改信号位 ，准备发车 */
		k:=0 and
		RBC2CTC[0]:=TrainID and
		RBC2CTC[1]:=k and //车头位置0
		RBC2CTC[2]:=0 and //发车请求
		RBC2CTC[3]:=MA;//安全行车区间
	
		RBC2LINK[0]:=TrainID and
		RBC2LINK[1]:=k and
		RBC2LINK[2]:=0 and //顺行
		RBC2LINK[3]:=MA and
		RBC2LINK[4]:=0 and //进路可以使用
		RBC2LINK[5]:=0;//进路状态正常
		//RBC2LINK[6]:=1 and skip; //进路类型：发车作业
	
		RBC2TRAIN[0]:=TrainID and //
		RBC2TRAIN[1]:=rbc and //
		//RBC2TRAIN[2]:=1 and //行车命令授权：发车作业
		RBC2TRAIN[3]:=MA; //

		if(k=MaxLength)
		then 
		{
			RBC2TRAIN[10]:=k
		}
		else 
		{
			RBC2TRAIN[10]:=k+1
		}; //前方到达区间标识号
	
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

				if(RailwayInfo[k]=0 AND k=0)//始发站：发车操作
				then 
				{
					if(LinkState[k]=0)//下一区间轨道未被锁闭，即可以使用
					then
					{	
						extern CalculateMA() and skip;//注册之后，延伸MA（MA的延伸需要跟道路联锁状态相关）begin
						
						LinkState[k]:=1;//下一区间标记为：锁闭

						RBC2TRAIN[4]:=0;//列车已停稳，无溜入
						RBC2TRAIN[6]:=1;//出站信号灯亮起，给列车指示位置
						RBC2TRAIN[7]:=1;//方向进站信号灯亮起，给列车指示位置
			
						////DepartureDriving() //发车作业 begin
						
						Departure:=1;						
						output ("Train1: 发车作业\n") and skip;

	                    if(RBC2CTC[2]=0)//列车发车请求
	                    then 
	                    {
	                   	   RBC2CTC[5]:=1 and //请求得到响应，接受发车请求
		                   RBC2LINK[6]:=1 and //RBC给联锁信号，告知发车
		                   RBC2LINK[4]:=1 and //联锁锁闭当前道路（即将下一区间道路清空，备列车使用）
		                   RBC2TRAIN[1]:=1  //RBC根据CTC发过来的命令，向车载设备发送发车命令
	                     }
	                     else {output ("Train1: No Departure Request...\n") and empty};
	
	                     if(RBC2TRAIN[4]=0)//列车无溜入
	                     then 
	                     {
		                     RBC2TRAIN[13]:=1; //向列车发送完全监控模式授权
		                     RBC2TRAIN[14]:=1  //完全监控模式授权时，执行CTCS-3等级
	                     }  
	                     else 
	                     {
		                     RBC2TRAIN[13]:=2; //向列车发送目视行车模式授权
		                     RBC2TRAIN[14]:=2  //目视行车模式授权时，执行CTCS-2等级
	                     }; 

	                     if(RBC2TRAIN[6]=0)//出站信号灯是否亮
	                     then 
	                     {
		                     MA:=MA-1
	                     } //未驶过出站信号灯，则缩小行车授权范围MA
	                     else 
	                     {
	                     	output ("Train1: Don't change MA...Move on\n") and skip;
		                    if(	RBC2TRAIN[7]=1)//反向进站信号灯亮起
		                    then 
		                    {
		                         empty
		                    }
		                    else {output ("Train1: Don't change MA...Move on\n") and skip}
	                     };

	                     RBC2TRAIN[6]:=0;//出站信号灯灭
	                     RBC2TRAIN[7]:=0;//反向进站信号灯灭
						 
						 Departure:=0
						/////发车作业 end
					}
					else {output ("Train1: Error...It's dangerous...\n") and skip};//紧挨着的轨道被占用，此时处于危险状态

					empty
				}
				else {empty};

				/************************************/
				if(k=3) 
				then 
				{
					RBC2TRAIN[2]:=3 and skip //将k=3 设定为通过车站，不停车
				} 
				else {empty};
				/***********************************/

				if(RailwayInfo[k]=0 AND k!=0 AND k!=MaxLength-1)//中间停靠站，要接车作业，停车，然后发车作业
				then 
				{
					if(RBC2TRAIN[2]!=3)//在此站点需要停靠，即停车
					then
					{
						//接车
						RBC2LINK[6]:=2;  //授权轨道接车作业，即将进路类型设置为接车作业
						RBC2TRAIN[9]:=1; //接近轨道信号灯亮
						RBC2TRAIN[5]:=1; //进站信号灯亮
						RBC2TRAIN[8]:=1; //反向出站信号灯亮

						////ArrivalDriving();//接车作业begin
					  
					  Arrival:=1;
					  
					
					output ("Train1: 接车作业\n") and skip;

	                if(RBC2LINK[6]=2) //RBC收到接车轨道信号授权，即进路类型为接车作业
	                then 
	                {
		               RBC2LINK[4]:=1;//联锁锁闭当前道路（即将下一区间道路清空，备列车使用）
		               RBC2CTC[2]:=1  //列车向CTC发送停车请求命令
	                }
	                else {output ("Train1: No Arrival Request...\n") and empty};
	
	                if(RBC2TRAIN[9]=1)//列车已经接近轨道，即接近轨道信号灯亮
	                then 
	                {
	                 	RBC2TRAIN[2]:=2 //向列车发送接车作业授权
	                }
	                else {output ("Train1: Wait the monment...\n") and empty};

	                if(RBC2TRAIN[5]=1)
	                then
	                {
		                RBC2TRAIN[11]:=1; //条件紧急停车消息，要求列车在指定位置前停车
		                if(RBC2TRAIN[8]=1)
		                then
		                {
		                	output ("Train1: Arrival the train...\n") and skip;
			                RBC2CTC[5]:=0; //停车请求命令被接受
			                 RBC2TRAIN[12]:=1 //列车已停稳，并向联锁发送停车状态
		                 }
		                 else {output ("Train1: Wait the monment...\n") and empty}	
	}
	else {output ("Train1: Wait the monment...\n") and empty};

	RBC2TRAIN[9]:=0; //接近轨道信号灯灭
	RBC2TRAIN[5]:=0; //进站信号灯灭
	RBC2TRAIN[8]:=0;  //反向出站信号灯灭
	
	Arrival:=0;
					    //////接车作业 end
						output ("Train1: The train should be stopped for a moment....\n") and skip;

						extern CalculateMA() and skip;///////////////注册之后，延伸MA（MA的延伸需要跟道路联锁状态相关）begin
						

						if(LinkState[k]=0)
						then
						{
							LinkState[k-1]:=0;//释放当前区间轨道，即标记为未被占用
							LinkState[k]:=1;//将下一区间轨道标记为占用，锁闭

							//发车
							RBC2CTC[2]:=0; //发车请求
							RBC2CTC[3]:=MA;//安全行车区间
							RBC2TRAIN[4]:=0;//列车已停稳，无溜入
							RBC2TRAIN[6]:=1;//出站信号灯亮起，给列车指示位置
							RBC2TRAIN[7]:=1;//方向进站信号灯亮起，给列车指示位置
			
							////DepartureDriving()//发车作业 begin
							output ("Train1: 发车作业\n") and skip;

	if(RBC2CTC[2]=0)//列车发车请求
	then 
	{
		RBC2CTC[5]:=1 and //请求得到响应，接受发车请求
		RBC2LINK[6]:=1 and //RBC给联锁信号，告知发车
		RBC2LINK[4]:=1 and //联锁锁闭当前道路（即将下一区间道路清空，备列车使用）
		RBC2TRAIN[1]:=1  //RBC根据CTC发过来的命令，向车载设备发送发车命令
	}
	else {output ("Train1: No Departure Request...\n") and empty};
	
	if(RBC2TRAIN[4]=0)//列车无溜入
	then 
	{
		RBC2TRAIN[13]:=1; //向列车发送完全监控模式授权
		RBC2TRAIN[14]:=1  //完全监控模式授权时，执行CTCS-3等级
	}  
	else 
	{
		RBC2TRAIN[13]:=2; //向列车发送目视行车模式授权
		RBC2TRAIN[14]:=2  //目视行车模式授权时，执行CTCS-2等级
	}; 

	if(RBC2TRAIN[6]=0)//出站信号灯是否亮
	then 
	{
		MA:=MA-1
	} //未驶过出站信号灯，则缩小行车授权范围MA
	else 
	{
		output ("Train1: Don't change MA...Move on\n") and skip;
		if(	RBC2TRAIN[7]=1)//反向进站信号灯亮起
		then 
		{
			empty
		}
		else {output ("Train1: Don't change MA...Move on\n") and skip}
	};

	RBC2TRAIN[6]:=0;//出站信号灯灭
	RBC2TRAIN[7]:=0//反向进站信号灯灭
							//////发车作业 end
						}
						else {output ("Train1: Error...It's dangerous !\n") and skip};//紧挨着的轨道被占用，此时处于    危险状态
			
						empty
					}
					else //RBC2TRAIN[2]=3：通过作业，不停靠
					{	
						extern CalculateMA() and skip;//////注册之后，延伸MA（MA的延伸需要跟道路联锁状态相关）begin
						

						///PassDriving();/////通过作业：到达站点，不停车 begin
							output ("Train1: 通过作业\n") and skip;

	                     //接车过程，只是实现接车这一过程，并不实际停车，接车后立即发车，中间不停靠

	                   //接车所需信号
	                    RBC2LINK[6]:=2;  //授权轨道接车作业，即将进路类型设置为接车作业
                     	RBC2TRAIN[9]:=1; //接近轨道信号灯亮
	RBC2TRAIN[5]:=1; //进站信号灯亮
	RBC2TRAIN[8]:=1; //反向出站信号灯亮

	if(RBC2LINK[6]=2) //RBC收到接车轨道信号授权，即进路类型为接车作业
	then 
	{
		RBC2LINK[4]:=1 //联锁锁闭当前道路（即将下一区间道路清空，备列车使用）
		//RBC2CTC[2]:=1 and skip //列车向CTC发送停车请求命令
	}
	else {output ("Train1: No Arrival Request...\n") and empty};
	
	if(RBC2TRAIN[9]=1)//列车已经接近轨道，即接近轨道信号灯亮
	then 
	{
		RBC2TRAIN[2]:=2 //向列车发送接车作业授权
	}
	else {output ("Train1: Wait the monment...\n") and empty};

	if(RBC2TRAIN[5]=1)
	then
	{
		RBC2TRAIN[11]:=1; //条件紧急停车消息，要求列车在指定位置前停车
		if(RBC2TRAIN[8]=1)
		then
		{
			output ("Train1: Arrival the train...\n") and skip
			//RBC2CTC[5]:=0; //停车请求命令被接受
			//RBC2TRAIN[12]:=1 and skip//列车已停稳，并向联锁发送停车状态
		}
		else {output ("Train1: Wait the monment...\n") and empty}	
	}
	else {output ("Train1: Wait the monment...\n") and empty};

	RBC2TRAIN[9]:=0; //接近轨道信号灯灭
	RBC2TRAIN[5]:=0; //进站信号灯灭
	RBC2TRAIN[8]:=0;  //反向出站信号灯灭

	//发车过程
	if(LinkState[k]=0)//若下一区间未被占用，即没被锁闭
	then
	{
		LinkState[k-1]:=0;//释放当前区间轨道，即标记为未被占用
		LinkState[k]:=1;//将下一区间轨道标记为占用，锁闭

		//发车所需信号
		RBC2CTC[2]:=0; //发车请求
		RBC2CTC[3]:=MA;//安全行车区间
		RBC2TRAIN[6]:=1;//出站信号灯亮起，给列车指示位置
		RBC2TRAIN[7]:=1;//方向进站信号灯亮起，给列车指示位置

		if(RBC2CTC[2]=0)//列车发车请求
		then 
		{
			RBC2CTC[5]:=1 and //请求得到响应，接受发车请求
			RBC2LINK[6]:=1 and //RBC给联锁信号，告知发车
			RBC2LINK[4]:=1 and //联锁锁闭当前道路（即将下一区间道路清空，备列车使用）
			RBC2TRAIN[1]:=1  //RBC根据CTC发过来的命令，向车载设备发送发车命令
		}
		else {output ("Train1: No Departure Request...\n") and empty};
		
		/* 因为不停车，故不进行溜入检测，列车按原来的等级模式行车
		if(RBC2TRAIN[4]=0)
		then 
		{
			RBC2TRAIN[13]:=1; //向列车发送完全监控模式授权
			RBC2TRAIN[14]:=1  //完全监控模式授权时，执行CTCS-3等级
		}  	
		else 
		{
			RBC2TRAIN[13]:=2; //向列车发送目视行车模式授权
			RBC2TRAIN[14]:=2  //目视行车模式授权时，执行CTCS-2等级
		}; 
		*/

		if(RBC2TRAIN[6]=0)//出站信号灯是否亮
		then 
		{
			MA:=MA-1 and skip
		} //未驶过出站信号灯，则缩小行车授权范围MA
		else 
		{
			output ("Train1: Don't change MA...Move on\n") and skip;
			if(	RBC2TRAIN[7]=1)//反向进站信号灯亮起
			then 
			{
				empty
			}
			else {output ("Train1: Don't change MA...Move on\n") and skip}
		};

		RBC2TRAIN[6]:=0;//出站信号灯灭
		RBC2TRAIN[7]:=0//反向进站信号灯灭
	}
	else {output ("Train1: Error...It's dangerous...\n") and skip};//紧挨着的轨道被占用，此时处于危险状态

						/////通过作业：到达站点，不停车end
						empty
					}
				}
				else {empty};

				if(RailwayInfo[k]=0 AND k=MaxLength-1)//终点站：接车作业，然后停车,停稳后注销列车信息
				then 
				{
					//接车
					RBC2LINK[6]:=2;  //授权轨道接车作业，即将进路类型设置为接车作业
					RBC2TRAIN[9]:=1; //接近轨道信号灯亮
					RBC2TRAIN[5]:=1; //进站信号灯亮
					RBC2TRAIN[8]:=1; //反向出站信号灯亮

					////ArrivalDriving();//接车作业begin
					output ("Train1: 接车作业\n") and skip;

	if(RBC2LINK[6]=2) //RBC收到接车轨道信号授权，即进路类型为接车作业
	then 
	{
		RBC2LINK[4]:=1;//联锁锁闭当前道路（即将下一区间道路清空，备列车使用）
		RBC2CTC[2]:=1  //列车向CTC发送停车请求命令
	}
	else {output ("Train1: No Arrival Request...\n") and empty};
	
	if(RBC2TRAIN[9]=1)//列车已经接近轨道，即接近轨道信号灯亮
	then 
	{
		RBC2TRAIN[2]:=2 //向列车发送接车作业授权
	}
	else {output ("Train1: Wait the monment...\n") and empty};

	if(RBC2TRAIN[5]=1)
	then
	{
		RBC2TRAIN[11]:=1; //条件紧急停车消息，要求列车在指定位置前停车
		if(RBC2TRAIN[8]=1)
		then
		{
			output ("Train1: Arrival the train...\n") and skip;
			RBC2CTC[5]:=0; //停车请求命令被接受
			RBC2TRAIN[12]:=1 //列车已停稳，并向联锁发送停车状态
		}
		else {output ("Train1: Wait the monment...\n") and empty}	
	}
	else {output ("Train1: Wait the monment...\n") and empty};

	RBC2TRAIN[9]:=0; //接近轨道信号灯灭
	RBC2TRAIN[5]:=0; //进站信号灯灭
	RBC2TRAIN[8]:=0;  //反向出站信号灯灭
					/////接车作业end

					if(RBC2TRAIN[12]=1)//列车已经停稳
					then
					{
						///Cancel() //注销列车信息begin
							output ("Train1: 注销\n") and skip;

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
	then {output ("Train1: Cancle Error! Can't find the TrainID...\n") and empty} //无列车ID，无法注销，注销错误
	else {empty};

	LinkState[k-1]:=0;//释放前一区间轨道，置为未被锁闭

	//注销列车信息
	TrainInfo[0]:=-1 and //列车当前行驶时的RBC编号
	TrainInfo[1]:=0 and  //注册及注销列车车次
	TrainInfo[2]:=0 and  //列车类型(0：无 1：普快 2：快速 3：特快 4：动车 5：高铁)
	TrainInfo[3]:=0 and  //列车长度(单位：m)
	TrainInfo[4]:=0 and  //最高时速(单位：km/h)
	TrainInfo[5]:=-1 //运行方向(0：顺行 1：逆行)

						/////注销列车信息end
					}
					else {empty};

					empty
				}
				else {empty};


				if(k!=0 AND k%2=0 AND k!=MaxLength-1) //起点站和终点站都不用切换RBC：起点注册，终点注销
				then 
				{
					//即：RBC收到转换位置预告后，向车载设备发送RBC转换命令
					RBC2TRAIN[17]:=1;//RBC切换命令（0：无 1：切换）	

					///ChangeRBC();//切换RBC begin
						output ("Train1: 切换RBC\n") and skip;

	if(RBC2TRAIN[17]=1)
	then
	{
		rbc:=rbc+1;
		TrainInfo[0]:=rbc; //列车当前行驶时的RBC编号
		RBC2TRAIN[1]:=rbc  //当前行驶区间RBC编号
	}
	else {empty};

	RBC2TRAIN[17]:=0;//切换完毕后，重置命令

					//////切换RBC end
			
					empty
				}
				else {empty};
				

				if(RailwayInfo[k]=1)//站与站之间,到达某一区间终点，此时请求延伸MA
				then 
				{	
				     CalMA:=1;
					 extern CalculateMA() and skip;///////////注册之后，延伸MA（MA的延伸需要跟道路联锁状态相关）begin
					 CalMA:=0;

					if(LinkState[k]=0)
					then
					{
						LinkState[k-1]:=0;//释放当前区间轨道，即标记为未被占用
						LinkState[k]:=1;//将下一区间轨道标记为占用，锁闭

						RBC2TRAIN[2]:=4; //行车命令授权(4：区间行车)
						RBC2LINK[4]:=1;  //锁闭下一区间，保证当前列车运行，其他任何列车不得占用
						RBC2LINK[5]:=0;  //进路状态正常
						RBC2LINK[6]:=0;  //进路类型(4：区间行车)  

						////IntervalDriving()  ////区间行车begin
						
						IntervalDriving:=1;
							output ("Train1: 区间行车\n") and skip;

	if(RBC2TRAIN[2]=4)//RBC收到区间行车授权命令
	then
	{
		RBC2TRAIN[10]:=1 //前方区间标志位，即区间行车标志(前方到达轨道的区间号)
	}
	else {output ("Train1: No Interval Request...\n") and empty};

	if(RBC2TRAIN[10]=1)
	then
	{
		RBC2TRAIN[11]:=1 //以前方标志点为目标向列车发送条件停车信息
	}
	else {output ("Train1: Wait the monment...\n") and empty};
	
	            IntervalDriving:=0
						//////区间行车end
					}
					else {output ("Train1: Error...It's dangerous !\n") and skip};//紧挨着的轨道被占用，此时处于危险状态

					empty
				}
				else {empty};


				//等级转换时，只需将RBC2TRAIN[15]置为1即可
				//RBC2TRAIN[15]:=1 
				if(RBC2TRAIN[15]=1) //收到CTCS转换命令
				then
				{
					RBC2TRAIN[16]:=1; //转换边界信号灯亮
		
				////	ChangeCTCS(); //切换CTCS等级begin
				output ("Train1: 切换CTCS等级\n")  and skip;
	
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

	RBC2TRAIN[15]:=0; //等级转换命令重置
	RBC2TRAIN[16]:=0; //转换边界信号灯灭 
				//////切换CTCS等级end

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
		k_<==0 and //表示区间号（循环中使用）
		rbc_<==-1 and //标识RBC编号
		///MA_<==0 and //行车许可(当前安全行车的区间号)
		TrainNum_<==0 and //列车数量
		RailError_<==0 and //表示初始化轨道时候有错误
		LinkError_<==0 and //道路联锁错误，MA不能正常延伸，触发紧急停车
		temp_<==0 and skip;

		/* ***************************初始化 ******************************************/
		TrainInfo_[0]<==-1 and //列车当前行驶时的RBC编号
		TrainInfo_[1]<==0 and  //注册及注销列车车次
		TrainInfo_[2]<==0 and  //列车类型(0：无 1：普快 2：快速 3：特快 4：动车 5：高铁)
		TrainInfo_[3]<==0 and  //列车长度(单位：m)
		TrainInfo_[4]<==0 and  //最高时速(单位：km/h)
		TrainInfo_[5]<==-1 and skip; //运行方向(0：顺行 1：逆行)

		RBC2CTC_[0]<==0 and  //列车车次
		RBC2CTC_[1]<==-1 and //车头位置(即车头位置所在的轨道区间号)
		RBC2CTC_[2]<==-1 and //请求命令(0：发车请求 1：停车请求 2：MA延伸请求)
		RBC2CTC_[3]<==0 and //行车许可(当前安全行车的区间号)
		RBC2CTC_[4]<==0 and //临时限速(单位：km/h)
		RBC2CTC_[5]<==-1 and skip; //接受命令(0：接受 1：拒绝)

		RBC2LINK_[0]<==0 and //列车车次
		RBC2LINK_[1]<==-1 and //车头位置(即车头位置所在的轨道区间号)
		RBC2LINK_[2]<==-1 and //运行方向(0：顺行 1：逆行)
		RBC2LINK_[3]<==0 and //行车许可MA(当前安全行车的区间号)
		RBC2LINK_[4]<==0 and //道路联锁状态(0：使用 1：锁闭)
		RBC2LINK_[5]<==0 and //进路状态(0：正常 1：出错)
		RBC2LINK_[6]<==0 and skip; //进路类型(0：无 1：发车作业 2：接车作业 3：通过作业 4：区间行车)  

		RBC2TRAIN_[0]<==0 and //列车车次
		RBC2TRAIN_[1]<==-1 and //当前行驶区间RBC编号
		RBC2TRAIN_[2]<==0 and //行车命令授权(0：无 1：发车作业 2：接车作业 3：通过作业 4：区间行车)
		RBC2TRAIN_[3]<==0 and //行车许可MA(当前安全行车的区间号)
		RBC2TRAIN_[4]<==-1 and //列车溜入标志，即停止命令执行完毕后，列车依旧在移动(0：无 1：有)
		RBC2TRAIN_[5]<==0 and //进站信号灯(0：灭 1：亮)
		RBC2TRAIN_[6]<==0 and //出站信号灯(0：灭 1：亮)
		RBC2TRAIN_[7]<==0 and //反向进站信号灯(0：灭 1：亮)
		RBC2TRAIN_[8]<==0 and //反向出站信号灯(0：灭 1：亮)
		RBC2TRAIN_[9]<==0 and //接近轨道信号灯(0：灭 1：亮)
		RBC2TRAIN_[10]<==0 and //前方区间标志位，即区间行车标志(前方到达轨道的区间号)
		RBC2TRAIN_[11]<==0 and //条件紧急停车消息，要求列车在指定位置前停车
		RBC2TRAIN_[12]<==-1 and //停车状态(0：未停稳 1：停稳，并向联锁发送状态)
		RBC2TRAIN_[13]<==0 and //行车模式授权(1：完全监控模式 2：目视行车模式)
		RBC2TRAIN_[14]<==0 and //当前行车等级(1：CTCS-3等级 2：CTCS-2等级)
		RBC2TRAIN_[15]<==0 and //CTCS等级转换命令(0：无 1：切换)
		RBC2TRAIN_[16]<==0 and //转换边界信号灯(0：灭 1：亮)
		RBC2TRAIN_[17]<==0 and skip;//RBC切换命令（0：无 1：切换）
		/* ***************************初始化 ******************************************/

		

		TrainID_<==119 and skip;

		///Register_();//注册列车信息 begin
		output ("Train2: 注册_\n") and skip;

	i_:=0 and j_:=0 and skip;
	while(i_<10 AND i_!=-1)
	{
		if(RegisterList[i_]=0)
		then 
		{
			RegisterList[i_]:=TrainID_ and 
			i_:=-1 and skip //循环结束
		}
		else {i_:=i_+1 and skip}
	};
	if(i_=10)
	then {output ("Train2: Register Error! The capacity is not enought...\n") and empty} //超过容量，不能注册
	else {empty};

	rbc_:=0 and skip;

	//记录列车相关信息
	
	TrainNum_:=TrainNum_+1; //列车数目自增1	

	TrainInfo_[0]:=rbc_ and //列车当前行驶时的RBC编号
	TrainInfo_[1]:=TrainID_ and //注册及注销列车车次
	TrainInfo_[2]:=4 and //列车类型(0：无 1：普快 2：快速 3：特快 4：动车 5：高铁)			
	TrainInfo_[3]:=100 and //列车长度(单位：m)
	TrainInfo_[4]:=250 and //最高时速(单位：km/h)
	TrainInfo_[5]:=0; //运行方向(0：顺行 1：逆行)
		/////注册列车信息end

		extern CalculateMA_() and skip;//注册之后，延伸MA（MA的延伸需要跟道路联锁状态相关）begin
		


		//skip;Cancel_();
		//output(TrainInfo_[0],TrainInfo_[1],TrainInfo_[2],TrainInfo_[3],TrainInfo_[4],TrainInfo_[5]) and  skip

		/* 注册之后，修改信号位 ，准备发车 */
		k_:=0 and
		RBC2CTC_[0]:=TrainID_ and
		RBC2CTC_[1]:=k_ and //车头位置0
		RBC2CTC_[2]:=0 and //发车请求
		RBC2CTC_[3]:=MA_;//安全行车区间
	
		RBC2LINK_[0]:=TrainID_ and
		RBC2LINK_[1]:=k_ and
		RBC2LINK_[2]:=0 and //顺行
		RBC2LINK_[3]:=MA_ and
		RBC2LINK_[4]:=0 and //进路可以使用
		RBC2LINK_[5]:=0;//进路状态正常
		//RBC2LINK_[6]:=1 and skip; //进路类型：发车作业
	
		RBC2TRAIN_[0]:=TrainID_ and //
		RBC2TRAIN_[1]:=rbc_ and //
		RBC2TRAIN_[2]:=1 and //行车命令授权：发车作业
		RBC2TRAIN_[3]:=MA_; //

		if(k_=MaxLength)
		then 
		{
			RBC2TRAIN_[10]:=k_ 
		}
		else 
		{
			RBC2TRAIN_[10]:=k_+1
		}; //前方到达区间标识号
	
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
				if(RailwayInfo[k_]=0 AND k_=0)//始发站：发车操作
				then 
				{
					if(LinkState[k_]=0)//下一区间轨道未被锁闭，即可以使用
					then
					{	
						extern CalculateMA_() and skip;////////注册之后，延伸MA（MA的延伸需要跟道路联锁状态相关）begin
						
						LinkState[k_]:=1;//下一区间标记为：锁闭

						RBC2TRAIN_[4]:=0;//列车已停稳，无溜入
						RBC2TRAIN_[6]:=1;//出站信号灯亮起，给列车指示位置
						RBC2TRAIN_[7]:=1;//方向进站信号灯亮起，给列车指示位置
			
						///DepartureDriving_()  //发车作业 begin
							output ("Train2: 发车作业_\n") and skip;

	if(RBC2CTC_[2]=0)//列车发车请求
	then 
	{
		RBC2CTC_[5]:=1 and //请求得到响应，接受发车请求
		RBC2LINK_[6]:=1 and //RBC给联锁信号，告知发车
		RBC2LINK_[4]:=1 and //联锁锁闭当前道路（即将下一区间道路清空，备列车使用）
		RBC2TRAIN_[1]:=1  //RBC根据CTC发过来的命令，向车载设备发送发车命令
	}
	else {output ("Train2: No Departure Request...\n") and empty};
	
	if(RBC2TRAIN_[4]=0)//列车无溜入
	then 
	{
		RBC2TRAIN_[13]:=1; //向列车发送完全监控模式授权
		RBC2TRAIN_[14]:=1  //完全监控模式授权时，执行CTCS-3等级
	}  
	else 
	{
		RBC2TRAIN_[13]:=2; //向列车发送目视行车模式授权
		RBC2TRAIN_[14]:=2  //目视行车模式授权时，执行CTCS-2等级
	}; 

	if(RBC2TRAIN_[6]=0)//出站信号灯是否亮
	then 
	{
		MA_:=MA_-1
	} //未驶过出站信号灯，则缩小行车授权范围MA
	else 
	{
		output ("Train2: Don't change MA_...Move on\n") and skip;
		if(	RBC2TRAIN_[7]=1)//反向进站信号灯亮起
		then 
		{
			empty
		}
		else {output ("Train2: Don't change MA_...Move on\n") and skip}
	};

	RBC2TRAIN_[6]:=0;//出站信号灯灭
	RBC2TRAIN_[7]:=0//反向进站信号灯灭
						/////发车作业end
					}
					else {output ("Train2: Error...It's dangerous...\n") and skip};//紧挨着的轨道被占用，此时处于危险状态

					empty
				}
				else {empty};

				/************************************/
				if(k_=3) 
				then 
				{
					RBC2TRAIN_[2]:=3 and skip //将k=3 设定为通过车站，不停车
				} 
				else {empty};
				/***********************************/

				if(RailwayInfo[k_]=0 AND k_!=0 AND k_!=MaxLength-1)//中间停靠站，要接车作业，停车，然后发车作业
				then 
				{
					if(RBC2TRAIN_[2]!=3)//在此站点需要停靠，即停车
					then
					{
						//接车
						RBC2LINK_[6]:=2;  //授权轨道接车作业，即将进路类型设置为接车作业
						RBC2TRAIN_[9]:=1; //接近轨道信号灯亮
						RBC2TRAIN_[5]:=1; //进站信号灯亮
						RBC2TRAIN_[8]:=1; //反向出站信号灯亮

						////ArrivalDriving_();//接车作业 begin
							output ("Train2: 接车作业_\n") and skip;

	if(RBC2LINK_[6]=2) //RBC收到接车轨道信号授权，即进路类型为接车作业
	then 
	{
		RBC2LINK_[4]:=1;//联锁锁闭当前道路（即将下一区间道路清空，备列车使用）
		RBC2CTC_[2]:=1 //列车向CTC发送停车请求命令
	}
	else {output ("Train2: No Arrival Request...\n") and empty};
	
	if(RBC2TRAIN_[9]=1)//列车已经接近轨道，即接近轨道信号灯亮
	then 
	{
		RBC2TRAIN_[2]:=2 //向列车发送接车作业授权
	}
	else {output ("Train2: Wait the monment...\n") and empty};

	if(RBC2TRAIN_[5]=1)
	then
	{
		RBC2TRAIN_[11]:=1; //条件紧急停车消息，要求列车在指定位置前停车
		if(RBC2TRAIN_[8]=1)
		then
		{
			output ("Train2: Arrival the train...\n") and skip;
			RBC2CTC_[5]:=0; //停车请求命令被接受
			RBC2TRAIN_[12]:=1 //列车已停稳，并向联锁发送停车状态
		}
		else {output ("Train2: Wait the monment...\n") and empty}	
	}
	else {output ("Train2: Wait the monment...\n") and empty};

	RBC2TRAIN_[9]:=0; //接近轨道信号灯灭
	RBC2TRAIN_[5]:=0; //进站信号灯灭
	RBC2TRAIN_[8]:=0;  //反向出站信号灯灭
						//////接车作业end
					
						output ("Train2: The train should be stopped for a moment....\n") and skip;

					  extern CalculateMA_() and skip;///////////////注册之后，延伸MA（MA的延伸需要跟道路联锁状态相关）begin
					

						if(LinkState[k_]=0)
						then
						{
							LinkState[k_-1]:=0;//释放当前区间轨道，即标记为未被占用
							LinkState[k_]:=1;//将下一区间轨道标记为占用，锁闭

							//发车
							RBC2CTC_[2]:=0; //发车请求
							RBC2CTC_[3]:=MA_;//安全行车区间
							RBC2TRAIN_[4]:=0;//列车已停稳，无溜入
							RBC2TRAIN_[6]:=1;//出站信号灯亮起，给列车指示位置
							RBC2TRAIN_[7]:=1;//方向进站信号灯亮起，给列车指示位置
			
							///DepartureDriving_()//发车作业begin
								output ("Train2: 发车作业_\n") and skip;

	if(RBC2CTC_[2]=0)//列车发车请求
	then 
	{
		RBC2CTC_[5]:=1 and //请求得到响应，接受发车请求
		RBC2LINK_[6]:=1 and //RBC给联锁信号，告知发车
		RBC2LINK_[4]:=1 and //联锁锁闭当前道路（即将下一区间道路清空，备列车使用）
		RBC2TRAIN_[1]:=1  //RBC根据CTC发过来的命令，向车载设备发送发车命令
	}
	else {output ("Train2: No Departure Request...\n") and empty};
	
	if(RBC2TRAIN_[4]=0)//列车无溜入
	then 
	{
		RBC2TRAIN_[13]:=1; //向列车发送完全监控模式授权
		RBC2TRAIN_[14]:=1  //完全监控模式授权时，执行CTCS-3等级
	}  
	else 
	{
		RBC2TRAIN_[13]:=2; //向列车发送目视行车模式授权
		RBC2TRAIN_[14]:=2  //目视行车模式授权时，执行CTCS-2等级
	}; 

	if(RBC2TRAIN_[6]=0)//出站信号灯是否亮
	then 
	{
		MA_:=MA_-1
	} //未驶过出站信号灯，则缩小行车授权范围MA
	else 
	{
		output ("Train2: Don't change MA_...Move on\n") and skip;
		if(	RBC2TRAIN_[7]=1)//反向进站信号灯亮起
		then 
		{
			empty
		}
		else {output ("Train2: Don't change MA_...Move on\n") and skip}
	};

	RBC2TRAIN_[6]:=0;//出站信号灯灭
	RBC2TRAIN_[7]:=0//反向进站信号灯灭
							//////发车作业end
						}
						else {output ("Train2: Error...It's dangerous !\n") and skip};//紧挨着的轨道被占用，此时处于    危险状态
			
						empty
					}
					else //RBC2TRAIN_[2]=3：通过作业，不停靠
					{	
						extern CalculateMA_() and skip;/////////////注册之后，延伸MA（MA的延伸需要跟道路联锁状态相关）begin
						
						///PassDriving_(); //通过作业：到达站点，不停车begin
							output ("Train2: 通过作业_") and skip;

	//接车过程，只是实现接车这一过程，并不实际停车，接车后立即发车，中间不停靠

	//接车所需信号
	RBC2LINK_[6]:=2;  //授权轨道接车作业，即将进路类型设置为接车作业
	RBC2TRAIN_[9]:=1; //接近轨道信号灯亮
	RBC2TRAIN_[5]:=1; //进站信号灯亮
	RBC2TRAIN_[8]:=1; //反向出站信号灯亮

	if(RBC2LINK_[6]=2) //RBC收到接车轨道信号授权，即进路类型为接车作业
	then 
	{
		RBC2LINK_[4]:=1 //联锁锁闭当前道路（即将下一区间道路清空，备列车使用）
		//RBC2CTC_[2]:=1 and skip //列车向CTC发送停车请求命令
	}
	else {output ("Train2: No Arrival Request...") and empty};
	
	if(RBC2TRAIN_[9]=1)//列车已经接近轨道，即接近轨道信号灯亮
	then 
	{
		RBC2TRAIN_[2]:=2 //向列车发送接车作业授权
	}
	else {output ("Train2: Wait the monment...") and empty};

	if(RBC2TRAIN_[5]=1)
	then
	{
		RBC2TRAIN_[11]:=1; //条件紧急停车消息，要求列车在指定位置前停车
		if(RBC2TRAIN_[8]=1)
		then
		{
			output ("Train2: Arrival the train...") and skip
			//RBC2CTC_[5]:=0; //停车请求命令被接受
			//RBC2TRAIN_[12]:=1 and skip//列车已停稳，并向联锁发送停车状态
		}
		else {output ("Train2: Wait the monment...") and empty}	
	}
	else {output ("Train2: Wait the monment...") and empty};

	RBC2TRAIN_[9]:=0; //接近轨道信号灯灭
	RBC2TRAIN_[5]:=0; //进站信号灯灭
	RBC2TRAIN_[8]:=0;  //反向出站信号灯灭

	//发车过程
	if(LinkState[k_]=0)//若下一区间未被占用，即没被锁闭
	then
	{
		LinkState[k_-1]:=0;//释放当前区间轨道，即标记为未被占用
		LinkState[k_]:=1;//将下一区间轨道标记为占用，锁闭

		//发车所需信号
		RBC2CTC_[2]:=0; //发车请求
		RBC2CTC_[3]:=MA_;//安全行车区间
		RBC2TRAIN_[6]:=1;//出站信号灯亮起，给列车指示位置
		RBC2TRAIN_[7]:=1;//方向进站信号灯亮起，给列车指示位置

		if(RBC2CTC_[2]=0)//列车发车请求
		then 
		{
			RBC2CTC_[5]:=1 and //请求得到响应，接受发车请求
			RBC2LINK_[6]:=1 and //RBC给联锁信号，告知发车
			RBC2LINK_[4]:=1 and //联锁锁闭当前道路（即将下一区间道路清空，备列车使用）
			RBC2TRAIN_[1]:=1 and skip //RBC根据CTC发过来的命令，向车载设备发送发车命令
		}
		else {output ("Train2: No Departure Request...") and empty};
		
		/* 因为不停车，故不进行溜入检测，列车按原来的等级模式行车
		if(RBC2TRAIN_[4]=0)
		then 
		{
			RBC2TRAIN_[13]:=1; //向列车发送完全监控模式授权
			RBC2TRAIN_[14]:=1  //完全监控模式授权时，执行CTCS-3等级
		}  	
		else 
		{
			RBC2TRAIN_[13]:=2; //向列车发送目视行车模式授权
			RBC2TRAIN_[14]:=2  //目视行车模式授权时，执行CTCS-2等级
		}; 
		*/

		if(RBC2TRAIN_[6]=0)//出站信号灯是否亮
		then 
		{
			MA_:=MA_-1 and skip
		} //未驶过出站信号灯，则缩小行车授权范围MA
		else 
		{
			output ("Train2: Don't change MA_...Move on") and skip;
			if(	RBC2TRAIN_[7]=1)//反向进站信号灯亮起
			then 
			{
				empty
			}
			else {output ("Train2: Don't change MA_...Move on") and skip}
		};

		RBC2TRAIN_[6]:=0;//出站信号灯灭
		RBC2TRAIN_[7]:=0//反向进站信号灯灭
	}
	else {output ("Train2: Error...It's dangerous...") and skip};//紧挨着的轨道被占用，此时处于危险状态

						/////通过作业：到达站点，不停车end
						empty
					}
				}
				else {empty};

				if(RailwayInfo[k_]=0 AND k_=MaxLength-1)//终点站：接车作业，然后停车,停稳后注销列车信息
				then 
				{
					//接车
					RBC2LINK_[6]:=2;  //授权轨道接车作业，即将进路类型设置为接车作业
					RBC2TRAIN_[9]:=1; //接近轨道信号灯亮
					RBC2TRAIN_[5]:=1; //进站信号灯亮
					RBC2TRAIN_[8]:=1; //反向出站信号灯亮

					////ArrivalDriving_(); //接车作业begin
						output ("Train2: 接车作业_") and skip;

	if(RBC2LINK_[6]=2) //RBC收到接车轨道信号授权，即进路类型为接车作业
	then 
	{
		RBC2LINK_[4]:=1;//联锁锁闭当前道路（即将下一区间道路清空，备列车使用）
		RBC2CTC_[2]:=1 //列车向CTC发送停车请求命令
	}
	else {output ("Train2: No Arrival Request...") and empty};
	
	if(RBC2TRAIN_[9]=1)//列车已经接近轨道，即接近轨道信号灯亮
	then 
	{
		RBC2TRAIN_[2]:=2 //向列车发送接车作业授权
	}
	else {output ("Train2: Wait the monment...") and empty};

	if(RBC2TRAIN_[5]=1)
	then
	{
		RBC2TRAIN_[11]:=1; //条件紧急停车消息，要求列车在指定位置前停车
		if(RBC2TRAIN_[8]=1)
		then
		{
			output ("Train2: Arrival the train...") and skip;
			RBC2CTC_[5]:=0; //停车请求命令被接受
			RBC2TRAIN_[12]:=1 //列车已停稳，并向联锁发送停车状态
		}
		else {output ("Train2: Wait the monment...") and empty}	
	}
	else {output ("Train2: Wait the monment...") and empty};

	RBC2TRAIN_[9]:=0; //接近轨道信号灯灭
	RBC2TRAIN_[5]:=0; //进站信号灯灭
	RBC2TRAIN_[8]:=0;  //反向出站信号灯灭
					//////接车作业end

					if(RBC2TRAIN_[12]=1)//列车已经停稳
					then
					{
						///Cancel_() //注销列车信息begin
							output ("Train2: 注销_") and skip;

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
	then {output ("Train2: Cancle Error! Can't find the TrainID...") and empty} //无列车ID，无法注销，注销错误
	else {empty};

	LinkState[k_-1]:=0;//释放前一区间轨道，置为未被锁闭

	//注销列车信息
	TrainInfo_[0]:=-1 and //列车当前行驶时的RBC编号
	TrainInfo_[1]:=0 and  //注册及注销列车车次
	TrainInfo_[2]:=0 and  //列车类型(0：无 1：普快 2：快速 3：特快 4：动车 5：高铁)
	TrainInfo_[3]:=0 and  //列车长度(单位：m)
	TrainInfo_[4]:=0 and  //最高时速(单位：km/h)
	TrainInfo_[5]:=-1 and skip //运行方向(0：顺行 1：逆行)
						//注销列车信息end
					}
					else {empty};

					empty
				}
				else {empty};


				if(k_!=0 AND k_%2=0 AND k_!=MaxLength-1) //起点站和终点站都不用切换RBC：起点注册，终点注销
				then 
				{
					//即：RBC收到转换位置预告后，向车载设备发送RBC转换命令
					RBC2TRAIN_[17]:=1;//RBC切换命令（0：无 1：切换）	

					///ChangeRBC_();//切换RBC begin
					output ("Train2: 切换RBC_") and skip;

	if(RBC2TRAIN_[17]=1)
	then
	{
		rbc_:=rbc_+1;
		TrainInfo_[0]:=rbc_; //列车当前行驶时的RBC编号
		RBC2TRAIN_[1]:=rbc_  //当前行驶区间RBC编号
	}
	else {empty};

	RBC2TRAIN_[17]:=0;//切换完毕后，重置命令
					/////切换RBC end
			
					empty
				}
				else {empty};


				if(RailwayInfo[k_]=1)//站与站之间,到达某一区间终点，此时请求延伸MA
				then 
				{	
					extern CalculateMA_() and skip;////////注册之后，延伸MA（MA的延伸需要跟道路联锁状态相关）begin
					

					if(LinkState[k_]=0)
					then
					{
						LinkState[k_-1]:=0;//释放当前区间轨道，即标记为未被占用
						LinkState[k_]:=1;//将下一区间轨道标记为占用，锁闭

						RBC2TRAIN_[2]:=4; //行车命令授权(4：区间行车)
						RBC2LINK_[4]:=1;  //锁闭下一区间，保证当前列车运行，其他任何列车不得占用
						RBC2LINK_[5]:=0;  //进路状态正常
						RBC2LINK_[6]:=0;  //进路类型(4：区间行车)  

						///IntervalDriving_() ///区间行车begin
							output ("Train2: 区间行车_") and skip;

	if(RBC2TRAIN_[2]=4)//RBC收到区间行车授权命令
	then
	{
		RBC2TRAIN_[10]:=1 //前方区间标志位，即区间行车标志(前方到达轨道的区间号)
	}
	else {output ("Train2: No Interval Request...") and empty};

	if(RBC2TRAIN_[10]=1)
	then
	{
		RBC2TRAIN_[11]:=1 //以前方标志点为目标向列车发送条件停车信息
	}
	else {output ("Train2: Wait the monment...") and empty}
						///////区间行车end
					}
					else {output ("Train2: Error...It's dangerous !") and skip};//紧挨着的轨道被占用，此时处于危险状态

					empty
				}
				else {empty};


				//等级转换时，只需将RBC2TRAIN[15]置为1即可
				//RBC2TRAIN_[15]:=1 
				if(RBC2TRAIN_[15]=1) //收到CTCS转换命令
				then
				{
					RBC2TRAIN_[16]:=1; //转换边界信号灯亮
		
					///ChangeCTCS_(); //切换CTCS等级 begin
						output ("Train2: 切换CTCS等级_")  and skip;
	
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

	RBC2TRAIN_[15]:=0; //等级转换命令重置
	RBC2TRAIN_[16]:=0; //转换边界信号灯灭 
					/////切换CTCS等级end

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

