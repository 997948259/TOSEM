//#Safe
//@ ltl invariant positive: []( AP(lock == 1) ==> <>AP( lock == 0));

</
define p: lock=1;
define q: lock=0;
alw(p->som(q))
/>

frame(
lock,
CancelIrql,
irql,
csl,
CurrentWaitIrp,
NewMask,
CancelIrp,
Mask,
length,
NewTimeouts,
SerialStatus,
pBaudRate,
pLineControl,
LData,
LStop,
LParity,
keA,
keR,
DeviceObject,
Irp,
status,
OldIrql,tmp) and (

int lock and
int CancelIrql and
int irql and
int csl and
int CurrentWaitIrp<==0 and

int NewMask and
int CancelIrp and

int Mask and
int length and

int NewTimeouts and
int SerialStatus and 
int pBaudRate and 
int pLineControl and 
int LData and

int LStop and
int LParity and
//int Mask and
int keA and
int keR and
 int DeviceObject and 
 int Irp and 
 int status and
 int OldIrql and int tmp and skip;
 main()
 );

 function IoAcquireCancelSpinLock ( int *ip )
 {
     csl:=1;
     (* ip):=irql
     
 };
 
 function IoReleaseCancelSpinLock ( int ip )
 {
     csl:=0;
     irql:=ip
     
 };

function main()
{
  frame(ddd2,
  continue_1) and (
  int ddd2 and
  
  int continue_1<==0 and skip;
  
	keA := 0; 
	keR := 0;
	//DD: init lock with 0 to avoid trivial satisfaction
	lock := 0;
	
	CancelIrql := 0;
	irql :=0;
	csl :=0;
	DeviceObject := 0;
	
	Irp :=0;
	status:=1;
	status := 2;
	keA := 0;
	keR := 0;
	length := 2;
	
	NewTimeouts := 0;
	
	SerialStatus:=0;
	pBaudRate :=0;
	pLineControl :=0;
	
	LData := 0;
	
	LStop := 0;
	LParity := 0;
	Mask := 255;

	if(2!=status) then 
     {
         while(1)
         {
             ddd2:=ddd2
         }        
     };
	
	if(1)then
	{
		if(0) then 
		{
			if (0) then 
			{
				status := 4 
			}
		}
		else 
		{
			if(1) then
			{
				CurrentWaitIrp:=0;
				NewMask := 0;
				if (0) 
				{
					status := 4 
				} 
				else 
				{
				   keA := 1; 
				
					keA := 0; 
					lock := 1; 
					OldIrql := irql;
					
					NewMask := 0;
					keR := 1; 
					
					keR := 0; 
					lock := 0; 
					
					irql := OldIrql;
					
					if (CurrentWaitIrp != 0) then
					{
						skip
					}
				}
			}
			else
			{
				if(1) then
				{
					CurrentWaitIrp:=0;
					if (1) then
					{
						status := 4
					};
					keA := 1; 
					keA := 0; 
					lock := 1; 
					
					OldIrql := irql;
					CurrentWaitIrp:=0;
					if (1) then 
					{
						status:=1 
					} 
					else 
					{
						status:=7
					};
					keR := 1; 
					keR := 0; 
					lock := 0; 
					
					irql := OldIrql;
					if (CurrentWaitIrp != 0) then
					{
						skip
					}
				}
				else
				{
					if(1) then
					{
						CancelIrp :=0; 
						Mask:= 1; 
						if (1) then 
						{
							status := 4 
						};
						//DD: Changed & to && to prevent LassoRanker error
						if (Mask AND 10)then 
						{
							keA := 1; 
							keA := 0; 
							lock := 1; 
							OldIrql := irql;
							
							length := 2;
							while (length>0)
							{
								length:=length-1;
								CancelIrp:=0;
								IoAcquireCancelSpinLock(&CancelIrql);
								if (1) then 
								{
									IoReleaseCancelSpinLock(CancelIrql);
									continue_1:=1
								};
								if(!continue_1)then
								{
								   IoReleaseCancelSpinLock(CancelIrql);
								   keR := 1; 
								   keR := 0; 
								   lock := 0; 
								   irql := OldIrql;
								   keA := 1; 
								   keA := 0; 
								   lock := 1; 
								   OldIrql := irql
								}
						   };
						   CancelIrp:=0;
						   if (1) then
						   {
								CancelIrp:=0
						   };
						   keR := 1; 
						   keR := 0; 
						   lock := 0; 
						   irql := OldIrql;
						   if (CancelIrp != 0)then
						   {
								skip
						   }
						}
					}
					else
					{
						if(1) then
						{
							if(1) then
							{
								status = 4
							}
						}
						else
						{
							if(1) then
							{
								NewTimeouts := 0;
								if (1) then
								{
									status := 4
								};
								if (1) then
								{
									status := 15 
								};
								keA := 1; 
								keA := 0; 
								lock := 1; 
								OldIrql := irql;
								keR := 1; 
								keR := 0; 
								lock := 0; 
								irql := OldIrql
							}
							else
							{
								if(1) then
								{
									if (1) then
									{
										status := 4 
									};
									keA := 1; 
									keA := 0; 
									lock := 1; 
									
									OldIrql := irql;
									keR := 1; 
									keR := 0; 
									lock := 0; 
									irql := OldIrql
								}
								else
								{
									if(1) then
									{
										SerialStatus:=0;
										if (1) then 
										{
											status := 4
										};
										keA := 1; 
										keA := 0; 
										
										lock := 1; 
										
										OldIrql := irql;
										keR := 1; 
										keR := 0; 
										lock := 0; 
										irql := OldIrql
									}
									else
									{
										if(1) then
										{
											keA := 1; 
											keA := 0; 
										   lock := 1; 
										   
										   OldIrql := irql;
										   if (1) then
										   {
												skip
										   } 
										   else 
										   {
												if (1) then 
												{
													skip
												}
										   };
										   keR := 1; 
										   keR := 0; 
										   
										   lock := 0; 
										   irql := OldIrql
										}
										else
										{
											if(1) then
											{
												if(1) then
												{
													
													status := 4
												}
											}
											else
											{
												if(1) then
												{
													if(1) then
													{
														status := 4
													}
													else
													{
														keA := 1; 
														keA := 0; 
														lock := 1; 
														OldIrql := irql;
														
														keR := 1; 
														keR := 0; 
														lock := 0; 
														irql := OldIrql
													}
												
												}
												else
												{
													if(1) then
													{
														pBaudRate := 0;
														if (1) then 
														{
															status := 4
														} 
														else 
														{
															keA := 1; 
															keA := 0; 
															lock := 1; 
															OldIrql := irql;
															
															keR := 1; 
															keR := 0; 
															lock := 0; 
															irql := OldIrql
														}
													}
													else
													{
														if(1) then
														{
															pLineControl := 0;
															LData := 0;
															LStop := 0;
															LParity := 0;
															Mask := 255;
															if (1) then 
															{
																status := 4 
															};
															if(1) then
															{ 
																if(1) /* case 5:*/ 
																{
																	LData := 27;
																	Mask := 31
																}
																else
																{
																	if(1) then
																	{
																		LData := 24;
																		Mask := 63
																	}
																	else
																	{
																		if(1) then
																		{
																			LData := 25;
																			Mask := 127
																		}
																		else
																		{
																			if(1) then
																			{
																				LData := 26
																			}
																			else
																			{
																				status := 15
																			}
																		}
																	}
																}
															};
															if (status != 2) then
															{
															   skip
															};
															if(1) then
															{
																if(1) then
																{
																	LParity:=29
																}
																else
																{
																	if(1) then
																	{
																		LParity:=31
																	}
																	else
																	{
																		if(1) then
																		{
																			LParity:=33
																		}
																		else
																		{
																			if(1) then
																			{
																				LParity:=35
																			}
																			else
																			{
																				if(1) then
																				{
																					LParity:=37
																				}
																				else
																				{
																					status:=15
																				}
																			}
																		}
																	}
																}
															};
															if (status != 2) then
															{
															   skip
															};
															if (1) then
															{
																if(1) 
																{
																	LStop := 32
																}
																else
																{
																	if(1) then
																	{
																		if (LData != 27) then
																		{
																			status := 15
																		};
																		LStop := 37
																	}
																	else
																	{
																		if(1) then
																		{
																			if (LData = 27) then
																			{
																				status := 15
																			};
																			LStop := 33
																			
																		}
																		else
																		{
																			status := 15
																		}
																	}
																}
															};
															if (status != 2)then
															{
																skip
															};
															keA := 1; 
															keA := 0; 
															
															lock := 1; 
															OldIrql := irql;
															
															keR := 1; 
															keR := 0; 
															lock := 0; 
															irql := OldIrql
														
														}
														else
														{
															if(1) then
															{
																if(1) then
																{
																	status：=4
																};
																keA := 1; 
																keA := 0; 
																
																lock := 1; 
																OldIrql := irql;
																
																keR := 1; 
																keR := 0; 
																lock := 0; 
																irql := OldIrql
															}
															else
															{
																if(1) then
																{
																	skip
																}
																else
																{
																	status:=41
																}
															}
														}
														
														
													}
													
												}
											}
											
										}
									}
									
								}
							
							}
						}
					}
				}
			}
		}
	};
	if (status != 7)then
	{
		if (Irp != 0)then
		{
			skip
		}
	};
	tmp:=10000000;
    while(tmp>0)
    {
	  tmp:=tmp-1
    }
)
}