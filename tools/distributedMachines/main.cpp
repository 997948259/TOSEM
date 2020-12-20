#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include<map>
#include<vector>
#include<set>
#include <stdarg.h>
#include <iostream>
#include "parse.h"
#include "lex.h"
#include "stdio.h"
#include "Machine.h"
#include "function.h"
#include <fstream>
#include <process.h>
#include "tpool.h"
#include "time.h"
#pragma comment(lib,"ws2_32.lib")
#include<iostream>
using namespace std;

#define HELLO_WORLD_SERVER_PORT 8003
#define LENGTH_OF_LISTEN_QUEUE 20
#define BUFFER_SIZE 1024

extern SyntaxTree  g_syntaxTree;
extern int ALTERNATELYINTERVAL; //定义每次一个线程执行多少个状态

//-----------------------------------------------------------------------------
// GLOBALS
int    g_nErrors = 0;
extern FILE *yyin;
extern FILE *yyout;
extern int yyparse();
#include "ConsLNFG.h"

extern "C" int yywrap(void)
{
	return 1;
}

//CGraph * graph;
//-----------------------------------------------------------------------------
// Name: error()
// Desc: Function used to report errors
//-----------------------------------------------------------------------------
void error(char *cFormat, ...)
{
	va_list args;

	++g_nErrors;
	fprintf(stderr, "Line %d: ", lineno);
	va_start(args, cFormat);
	vfprintf(stderr, cFormat, args);
	va_end(args);
	cout << endl;
}

//-----------------------------------------------------------------------------
// Name: errorSummary()
// Desc: Show an error count
//-----------------------------------------------------------------------------
void errorSummary()
{
	cout << g_nErrors << " error(s) were found." << endl;
}

//-----------------------------------------------------------------------------
// Name: yyerror()
// Desc: Function called by the parser when an error occurs while parsing
//       (parse error or stack overflow)
//-----------------------------------------------------------------------------
void yyerror(char *msg)
{
	error(msg);
}

map<string, int> propertyIndexMap;//性质名字对应的下标
typedef struct
{
	CTreeNode* property;
	int endNodeNum;
	bool emptyFlag;//此边指向empty节点
	bool moreFlag;//此边指向more节点
}SNodeToENode;
//vector<SNodeToENode> SNodeToENodeVec[10];
vector<int> start_propositionValue;
vector< vector<int> > g_propositionValue;
int ***NoCounterExampleNodeArrayTotal[THREADNUMBER];
int $$state_num;
int $$empty1;
int segWhileTime=1;
extern map< int, vector<SNodeToENode> >SNodeToENodeMap;
extern vector< vector<SNodeToENode> >SNodeToENodeVec;
int EachSeg(int current_length);//传入的参数是需要开始展开的步长

typedef struct
{
	int InitialNodeNum;//因为分成了多线程，此变量记录到达该节点初始节点的编号
	int NodeNum;
	int current_length;
}ToExtendNode;

bool __Sat(int stateIndex, CTreeNode* property)
{
	switch (property->type)
	{
	case IDENT_EXP:
	{
		int atomicPropertyIndex = property->atomicPropertyIndex;
		if (atomicPropertyIndex == -1)//如果是fin标记，返回true
		{
			return true;
		}
		int VecSize = g_propositionValue[atomicPropertyIndex].size() - 1;
		int low = 0;
		int mid;
		int result;
		int firstNum = start_propositionValue[atomicPropertyIndex];
		while (low <= VecSize)//二分查找
		{
			mid = (low + VecSize) / 2;
			if (g_propositionValue[atomicPropertyIndex][mid]>stateIndex)
			{
				VecSize = mid - 1;
			}
			else if (g_propositionValue[atomicPropertyIndex][mid]<stateIndex)
			{
				low = mid + 1;
			}
			else//findthetarget
			{
				result = mid;
				//cout<<"result:"<<result<<endl;
				return (result % 2 != firstNum);
				//break;
			}
		}
		//the array does not contain the target

		result = low - 1;
		//cout<<"result:"<<result<<endl;
		return (result % 2 != firstNum);
	}

	break;
	case NEGATION_STA:
	{
		int atomicPropertyIndex = property->child[0]->atomicPropertyIndex;
		if (atomicPropertyIndex == -1)//如果是fin标记，返回false
		{
			return false;
		}
		int VecSize = g_propositionValue[atomicPropertyIndex].size() - 1;
		int low = 0;
		int mid;
		int result;
		int firstNum = start_propositionValue[atomicPropertyIndex];

		while (low <= VecSize)//二分查找
		{
			mid = (low + VecSize) / 2;
			int indexValue = g_propositionValue[atomicPropertyIndex][mid];
			if (indexValue>stateIndex)
			{
				VecSize = mid - 1;
			}
			else if (indexValue<stateIndex)
			{
				low = mid + 1;
			}
			else//findthetarget
			{
				result = mid;
				//cout<<"result:"<<result<<endl;
				/*if(result%2 != firstNum)
				{
				cout<<"stateIndex:"<<stateIndex<<endl;
				}*/
				return (result % 2 == firstNum);
				//break;
			}
		}
		result = low - 1;
		//cout<<"result:"<<result<<endl;
		/*if(result%2 != firstNum)
		{
		cout<<"stateIndex:"<<stateIndex<<endl;
		}*/
		return (result % 2 == firstNum);
	}
	break;
	case TRUE_EXP:
		return true;
		break;
	case FIN_EXP:
		return true;
		break;
	case OR_STA:
		if (__Sat(stateIndex, property->child[0]) || __Sat(stateIndex, property->child[1]))
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case AND_STA:
		if (__Sat(stateIndex, property->child[0]) && __Sat(stateIndex, property->child[1]))
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	}
}

unsigned int __stdcall FunProc2(void *pPM)
{
	//cout<<"即将进入EachSeg函数"<<endl;
	//cout<<"(int)pPM:"<<(int)pPM<<endl;
	EachSeg((int)pPM);
	return 1;
}

vector<ToExtendNode> ToExtendNodeVecTotal[THREADNUMBER];//暂定为并行的段数为5
map<int, set<int> > reachToNodesFinal;//临时vector，记录终止节点
set<int> reachToNodesFinal1;
map<int, set<int> > EveryThreadThroughPathStartNodesToFinalNodesArray[THREADNUMBER];
map<int, set<int> > EveryThreadThroughPathStartNodesToFinalNodesArrayTotal;
vector<int> EveryThreadToEmptyOrMoreStartNodes[THREADNUMBER];
vector<int> EveryThreadToEmptyOrMoreStartNodesTotal;
int ModelCheckTheSameTimeResult[THREADNUMBER];
int ModelCheckTheSameTimeResultTotal = 0;//记录综合ModelCheckTheSameTimeResult数组之后的结果
tpool_t *tpool[THREADNUMBER];
DWORD TIME1, TIME2;
pthread_mutex_t mutex;
int current_length_total = 0;
void* EachPath(void *arg)//current_length表示此线程开始时的起始步长
{
	//TIME1 = GetTickCount();
	//register int currenttmp = segWhileTime;
	ToExtendNode* ToExtendNodePointer = (ToExtendNode *)arg;
	ToExtendNode currentExtendNode;//将malloc出来的arg中的值赋给局部变量currentExtendNode，然后free掉
	currentExtendNode.InitialNodeNum = ToExtendNodePointer->InitialNodeNum;
	currentExtendNode.NodeNum = ToExtendNodePointer->NodeNum;
	currentExtendNode.current_length = ToExtendNodePointer->current_length;
	free(ToExtendNodePointer);

	int ThreadIndex = (currentExtendNode.current_length - current_length_total) / ALTERNATELYINTERVAL;
	int current_length = current_length_total + ThreadIndex*ALTERNATELYINTERVAL;

	//int current_length = currentExtendNode.current_length;
	//cout << "current_length:" << current_length << endl;

	//SIMULATION6=GetTickCount();
	vector<ToExtendNode> ToExtendNodeVec;
	ToExtendNodeVec.push_back(currentExtendNode);
	int simulationStateNumCache = 0;//缓存仿真线程此时运行到的状态数，
	//cout<<"ThreadIndex111:"<<ThreadIndex<<endl;

	
	while (!ToExtendNodeVec.empty())
	{
		ToExtendNode currentExtendNode = ToExtendNodeVec.front();//获得当前待扩展的节点,每次处理的是栈最前面的节点，使用宽度优先遍历的方法
		vector< ToExtendNode >::iterator deleteIter = ToExtendNodeVec.begin();
		ToExtendNodeVec.erase(deleteIter); // 删除第一个元素
		//cout<<"当前扩展:NodeNum:"<<currentExtendNode.NodeNum<<"current_length:"<<currentExtendNode.current_length<<endl;
		int currentNodeNum = currentExtendNode.NodeNum;//获得当前待扩展节点的结点号
		int currentNodeLength = currentExtendNode.current_length;
		if (currentNodeLength > $$state_num)//如果当前节点大于程序的状态数，则退出
		{
			return NULL;
		}

		/*if (ToExtendNodeVec.size()>0 && tpool[ThreadIndex]->queue_cur_num < 5)//如果栈里面有多个节点,分给多个线程去运行
		{
			vector<ToExtendNode>::iterator ToExtendNodeVecIter;
			for (ToExtendNodeVecIter = ToExtendNodeVec.begin(); ToExtendNodeVecIter != ToExtendNodeVec.end(); ToExtendNodeVecIter++)
			{
				ToExtendNode* tmpMalloc = (ToExtendNode*)malloc(sizeof(ToExtendNode));
				tmpMalloc->InitialNodeNum = ToExtendNodeVecIter->InitialNodeNum;
				tmpMalloc->NodeNum = ToExtendNodeVecIter->NodeNum;
				tmpMalloc->current_length = ToExtendNodeVecIter->current_length;
				//cout << "forkNodeNum:" << tmpMalloc->NodeNum << endl;
				tpool_add_work(ThreadIndex, EachPath, (void*)tmpMalloc);

			}
			ToExtendNodeVec.clear();
		}*/

		vector<SNodeToENode>::iterator SNodeToENodeVecIter;
		//cout << "currentNodeNum:" << currentNodeNum<<endl;
		for (SNodeToENodeVecIter = SNodeToENodeVec[currentNodeNum].begin(); SNodeToENodeVecIter != SNodeToENodeVec[currentNodeNum].end(); SNodeToENodeVecIter++)
		{
			SNodeToENode currentEdge = (*SNodeToENodeVecIter);
			if (currentEdge.emptyFlag == 1)//表明在LNFG中此节点指向empty,并且程序也到达最后一个状态
			{
				//cout<<"这个分支1!!!"<<endl;
				if ($$empty1 == true && currentNodeLength == $$state_num)
				{
					if (__Sat(currentNodeLength, currentEdge.property))//如果性质的当前节点可以扩展
					{////性质指向empty节点，程序也到达最后一个状态，并且合取之后为true
						cout << "性质不满足3!!!" << endl;
						ModelCheckTheSameTimeResult[ThreadIndex] = -1;
						EveryThreadToEmptyOrMoreStartNodes[ThreadIndex].push_back(currentExtendNode.InitialNodeNum);
						//return NULL;//发现反例后，直接返回函数
						//如果有到达empty节点的路径，将其InitialNodeNum压入到EveryThreadToEmptyOrMoreStartNodes[ThreadIndex]中，需要继续其他节点，
						//以前是直接return，现在还得继续，因为此条路径可能和上个线程的连接不起来，如果直接返回了，可能会把后面的能够连接上的路径错过
						continue;
					}
				}
			}
			else if (currentEdge.moreFlag == 1)
			{
				//cout<<"这个分支1!!!"<<endl;
				if ($$empty1 == false || currentNodeLength<$$state_num)
				{
					if (__Sat(currentNodeLength, currentEdge.property))//如果性质的当前节点可以扩展
					{//性质指向empty节点，程序也到达最后一个状态，并且合取之后为true
						cout << "性质不满足4!!!" << endl;
						
						//FreeMallocAddr(NoCounterExampleNodeMap);
						ModelCheckTheSameTimeResult[ThreadIndex] = -1;
						EveryThreadToEmptyOrMoreStartNodes[ThreadIndex].push_back(currentExtendNode.InitialNodeNum);
						//return NULL;//发现反例后，直接返回函数
						//如果有到达empty节点的路径，将其InitialNodeNum压入到EveryThreadToEmptyOrMoreStartNodes[ThreadIndex]中，需要继续其他节点，
						//以前是直接return，现在还得继续，因为此条路径可能和上个线程的连接不起来，如果直接返回了，可能会把后面的能够连接上的路径错过
						continue;
					}
				}
			}
			else
			{
				//如果验证的状态数比缓存的状态数还小，则肯定比真实的仿真状态数小，如果性质需要获得的状态数比模型执行的状态数多，则需要更新一下currentLengthCache，
				//如果更新之后currentLengthCache还是比验证的状态数小，则验证线程就要等待仿真线程，引入局部变量currentLengthCache的目的是不每次都去访问全局变量$$state_num的值
				
				//cout<<"这个分支8!!!"<<endl;
				if (__Sat(currentNodeLength, currentEdge.property))//如果性质的当前节点可以扩展
				{
					if (currentNodeLength + 1 < current_length_total + (ThreadIndex+1)*(ALTERNATELYINTERVAL))
					{
						//cout << "currentEdge.endNodeNum:" << currentEdge.endNodeNum << endl;
						//cout << "currentExtendNode.InitialNodeNum:" << currentExtendNode.InitialNodeNum << endl;
						if (NoCounterExampleNodeArrayTotal[ThreadIndex][currentEdge.endNodeNum][currentExtendNode.InitialNodeNum][(currentNodeLength + 1 - current_length)] == segWhileTime)
						{//如果到达的节点之前出现过，则不用将此节点push到ToExtendNodeVec中，相同节点是指结点号相同，起始结点号相同并且步长也相同

							continue;//如果找到之前处理过的节点，则不处理此节点，直接处理下一个节点
						}
						else//如果此节点之前没加入到NoCounterExampleNodeArrayTotal[ThreadIndex]中，则将其置为true
						{
							NoCounterExampleNodeArrayTotal[ThreadIndex][currentEdge.endNodeNum][currentExtendNode.InitialNodeNum][(currentNodeLength + 1 - current_length)] = segWhileTime;

							ToExtendNode ToExtendNodeTmp;
							ToExtendNodeTmp.InitialNodeNum = currentExtendNode.InitialNodeNum;//将新节点的InitialNodeNum设为当前扩展节点的InitialNodeNum
							ToExtendNodeTmp.NodeNum = currentEdge.endNodeNum;
							ToExtendNodeTmp.current_length = currentNodeLength + 1;
							ToExtendNodeVec.push_back(ToExtendNodeTmp);
						}

					}
					else
					{//如果currentNodeLength+1==current_length+ALTERNATELYINTERVAL，表示此节点是此段扩展的最后一个节点，加入到ToExtendNodeVecTotal[ThreadIndex]中
						ToExtendNode ToExtendNodeTmp;
						ToExtendNodeTmp.InitialNodeNum = currentExtendNode.InitialNodeNum;//将新节点的InitialNodeNum设为当前扩展节点的InitialNodeNum
						ToExtendNodeTmp.NodeNum = currentEdge.endNodeNum;
						ToExtendNodeTmp.current_length = currentNodeLength + 1;
						pthread_mutex_lock(&mutex);
						ToExtendNodeVecTotal[ThreadIndex].push_back(ToExtendNodeTmp);
						pthread_mutex_unlock(&mutex);
						//cout << "current_length_total + ALTERNATELYINTERVAL:" << current_length_total + ALTERNATELYINTERVAL << endl;
						//cout << "ThreadIndex:" << ThreadIndex << endl;
						//cout << "push1:" << ToExtendNodeTmp.current_length << " 2:" << ToExtendNodeTmp.InitialNodeNum << " 3:" << ToExtendNodeTmp.NodeNum << endl;
					}
				}
				//cout<<"这个分支9!!!"<<endl;
			}
		}
	}
	//TIME2 = GetTickCount() - TIME1;
	return NULL;
}

int EachSeg(int current_length)//传入的参数是需要开始展开的步长
{
	vector<ToExtendNode> ToExtendNodeVec;
	//下面记得将一些全局变量复位，否则会影响服务器下一次验证结果
	int ThreadIndex = (current_length - current_length_total) / (ALTERNATELYINTERVAL);
	ModelCheckTheSameTimeResult[ThreadIndex] = 0;
	ToExtendNodeVecTotal[ThreadIndex].clear();//记得清空
	EveryThreadToEmptyOrMoreStartNodes[ThreadIndex].clear();//将EveryThreadToEmptyOrMoreStartNodes清空，否则服务器一直运行的话，会影响下一次运行结果
	EveryThreadThroughPathStartNodesToFinalNodesArray[ThreadIndex].clear();

	pthread_mutex_init(&mutex, NULL); //用默认属性初始化一个互斥锁对象

	set<int>::iterator iter1;
	for (iter1 = reachToNodesFinal1.begin(); iter1 != reachToNodesFinal1.end(); iter1++)
	{
		ToExtendNode firstNode;
		firstNode.InitialNodeNum = *iter1;//将初始节点的InitialNodeNum置为-1
		firstNode.NodeNum = *iter1;//初始节点的编号为1
		firstNode.current_length = current_length;//初始步长为参数current_length的值
		ToExtendNodeVec.push_back(firstNode);

		set<int> tmpVec1;
		EveryThreadThroughPathStartNodesToFinalNodesArray[ThreadIndex].insert(pair< int, set<int> >(*iter1, tmpVec1));
	}

	
	tpool[ThreadIndex]->cur_max_thr_num = 5;//目前线程池的大小是固定的，设为5

	vector<ToExtendNode>::iterator ToExtendNodeVecIter;
	//DWORD SIMULATION1 = GetTickCount();
	for (ToExtendNodeVecIter = ToExtendNodeVec.begin(); ToExtendNodeVecIter != ToExtendNodeVec.end(); ToExtendNodeVecIter++)
	{
		ToExtendNode* tmpMalloc = (ToExtendNode*)malloc(sizeof(ToExtendNode));
		tmpMalloc->InitialNodeNum = ToExtendNodeVecIter->InitialNodeNum;
		tmpMalloc->NodeNum = ToExtendNodeVecIter->NodeNum;
		tmpMalloc->current_length = ToExtendNodeVecIter->current_length;

		tpool_add_work(ThreadIndex,EachPath, (void*)tmpMalloc);//把每一个节点交给一个线程去处理
		//EachPath((void*)tmpMalloc);
	}
	//DWORD SIMULATION2 = GetTickCount();
	
	DWORD SIMULATION1 = GetTickCount();
	tpool_await(ThreadIndex);//等待线程池中的所有线程都执行结束
	DWORD SIMULATION2 = GetTickCount();
	//cout << "each path time:" << SIMULATION2 - SIMULATION1 << endl;
	if (current_length <= $$state_num)
	{
		if (ToExtendNodeVecTotal[ThreadIndex].empty() && EveryThreadToEmptyOrMoreStartNodes[ThreadIndex].empty())//没有节点可以扩展，返回1表示性质满足
		{
			ModelCheckTheSameTimeResult[ThreadIndex] = 1;
			return 1;
		}
		else//表示目前还有节点需要进一步扩展
		{
			vector<ToExtendNode>::iterator ToExtendNodeVecIter;
			for (ToExtendNodeVecIter = ToExtendNodeVecTotal[ThreadIndex].begin(); ToExtendNodeVecIter != ToExtendNodeVecTotal[ThreadIndex].end(); ToExtendNodeVecIter++)
			{
				map<int, set<int> >::iterator iter3 = EveryThreadThroughPathStartNodesToFinalNodesArray[ThreadIndex].find(ToExtendNodeVecIter->InitialNodeNum);
				if (iter3 != EveryThreadThroughPathStartNodesToFinalNodesArray[ThreadIndex].end())//如果map中有初始节点，直接压入终止节点
				{
					set<int>::iterator findResult = iter3->second.find(ToExtendNodeVecIter->NodeNum);

					if (findResult == iter3->second.end()) //没找到的话，再把可达节点压进去，否则会压入很多重复的节点
					{
						iter3->second.insert(ToExtendNodeVecIter->NodeNum);
					}
					else
					{
						//cout<<"已存在相同节点!!!"<<endl;	
					}
				}
				else
				{
					cout << "ToExtendNodeVecIter->InitialNodeNum:" << ToExtendNodeVecIter->InitialNodeNum << endl;
					cout << "线程结束插入EveryThreadThroughPathStartNodesToFinalNodes时出错!!!" << endl;
				}
			}
		}

	}
	
}

inline void ReleaseNoCounterExampleNodeArray(int ***NoCounterExampleNodeArrayTotal,int totalNodeNum)
{
	int i, j;
	for (i = 0; i < totalNodeNum; i++)
	{
		for (j = 0; j < totalNodeNum; j++)
		{
			delete[] NoCounterExampleNodeArrayTotal[i][j];
		}

	}
	for (i = 0; i < totalNodeNum; i++)
	{
		delete[]NoCounterExampleNodeArrayTotal[i];
	}
	delete[]NoCounterExampleNodeArrayTotal;

}

HANDLE threadPro1[THREADNUMBER];//将多个线程定义成数组
map<int, set<int> > reachToNodes;//临时vector，记录起始节点

void TraceCheck(int initialNodeCurrentLength)//initialNodeCurrentLength表示从客户端传过来的初始步长
{
	//cout << "已经进入TraceCheck函数" << endl;
	current_length_total = initialNodeCurrentLength;//这一段的初始步长
	ModelCheckTheSameTimeResultTotal = 0;
	if (initialNodeCurrentLength == 150)
	{
		int a = 0;
	}
	for (int i = 0; i < THREADNUMBER; i++)
	{
		threadPro1[i] = (HANDLE)_beginthreadex(NULL, 0, FunProc2, (void*)(initialNodeCurrentLength + i*(ALTERNATELYINTERVAL)), 0, NULL);
	}
	WaitForMultipleObjects(THREADNUMBER, threadPro1, TRUE, INFINITE);//等待多个线程同时结束
	
	//下面是reduce的过程
	for (int j = 0; j<THREADNUMBER; j++)//判断ModelCheckTheSameTimeResult中是否存在元素为1
	{
		if (ModelCheckTheSameTimeResult[j] == 1)//检查是否存在线程里面的路是不通的，如果有一条是不通的，整个路也不通，这时性质肯定成立
		{
			cout << "性质最终满足!!!" << endl;
			ModelCheckTheSameTimeResultTotal = 1;//只要数组ModelCheckTheSameTimeResult中有一个元素为1，则将ModelCheckTheSameTimeResultTotal变量置为1
			return;
		}
	}

	map<int, set<int> > EveryThreadThroughPathStartNodesToFinalNodes = EveryThreadThroughPathStartNodesToFinalNodesArray[0];
	map<int, set<int> >::iterator iter4;
	reachToNodes = EveryThreadThroughPathStartNodesToFinalNodes;
	//cout << "reachToNodes.size():" << reachToNodes.size() << endl;
	for (iter4 = reachToNodes.begin(); iter4 != reachToNodes.end(); iter4++)
	{
		iter4->second.insert(iter4->first);
	}

	int Threadi = 0;
	for (Threadi = 0; Threadi < THREADNUMBER; Threadi++)
	{
		//下面这一段需要修改，先不管这一段，其他地方修改好之后再修改这一块
		if (!EveryThreadToEmptyOrMoreStartNodes[Threadi].empty())//如果存在节点能够到达empty或者more节点
		{
			//cout << "Threadi:" << Threadi << endl;
			//cout << "EveryThreadToEmptyOrMoreStartNodes[Threadi].size():" << EveryThreadToEmptyOrMoreStartNodes[Threadi].size() << endl;
			vector <int>::iterator EveryThreadToEmptyOrMoreStartNodesIter;
			for (EveryThreadToEmptyOrMoreStartNodesIter = EveryThreadToEmptyOrMoreStartNodes[Threadi].begin(); EveryThreadToEmptyOrMoreStartNodesIter != EveryThreadToEmptyOrMoreStartNodes[Threadi].end(); EveryThreadToEmptyOrMoreStartNodesIter++)
			{
				//cout<<" (*EveryThreadToEmptyOrMoreStartNodesIter):"<< (*EveryThreadToEmptyOrMoreStartNodesIter)<<endl;
				//vector<int>::iterator result = find(reachToNodes.begin(), reachToNodes.end(), (*EveryThreadToEmptyOrMoreStartNodesIter));
				map<int, set<int> >::iterator iter1;
			
				for (iter1 = reachToNodes.begin(); iter1 != reachToNodes.end(); iter1++)
				{
					set<int>::iterator result = iter1->second.find(*EveryThreadToEmptyOrMoreStartNodesIter);
					if (result != iter1->second.end())
					{
						cout << "有节点能够到达empty或者more节点，因此性质不成立!!!" << endl;
						//thisPathIsValid = false;
						//将到达empty或者more的初始节点压入到EveryThreadToEmptyOrMoreStartNodesTotal中
						//最后给客户端传的也是EveryThreadToEmptyOrMoreStartNodesTotal变量的内容
						EveryThreadToEmptyOrMoreStartNodesTotal.push_back(iter1->first);
					}
				}
			}
		}

		//如果没有找到可到达empty节点或者more节点的路径，再进行下面操作
		map<int, set<int> >::iterator iter5;
		reachToNodesFinal.clear();//将reachToNodesFinal清空  
		for (iter5 = reachToNodes.begin(); iter5 != reachToNodes.end(); iter5++)//遍历初始节点
		{
			//cout<<"*iter5:"<<*iter5<<endl;
			EveryThreadThroughPathStartNodesToFinalNodes = EveryThreadThroughPathStartNodesToFinalNodesArray[Threadi];
			set<int>::iterator iter6;
			for (iter6 = iter5->second.begin(); iter6 != iter5->second.end(); iter6++)
			{
				iter4 = EveryThreadThroughPathStartNodesToFinalNodes.find(*iter6);//在EveryThreadThroughPathStartNodesToFinalNodes中查找以(*iter5)作为起点的终止节点
				if (iter4 != EveryThreadThroughPathStartNodesToFinalNodes.end())
				{//如果存在的话，把以(*iter5)作为起点的终止节点加入到reachToNodesFinal中
				
					map<int, set<int> >::iterator iter7 = reachToNodesFinal.find(iter5->first);
					if ( iter7 == reachToNodesFinal.end())
					{
						set<int> tmpSet = iter4->second;
						reachToNodesFinal.insert(pair<int, set<int> >(iter5->first, tmpSet));
					}
					else
					{
						set<int>::iterator iter8;
						for (iter8 = iter4->second.begin(); iter8 != iter4->second.end(); iter8++)
						{
							iter7->second.insert(*iter8);
						}
					}
				}
				else
				{
					//因为正常情况下，即使second为空，也会找到，所以如果没有找到，则提示出错，
					cout << "查找出错!!!" << endl;
				}
			}
			
		}
		
		if (reachToNodesFinal.empty())//如果上一个线程的终止节点和下一个线程的起始节点衔接不上，则表示扩展不通，此时性质成立
		{
			cout << "一个线程最后可达节点和下一个进程的初始节点没有交集，因此性质成立!!!" << endl;
			ModelCheckTheSameTimeResultTotal = 1;//将此变量置为1，然后传给客户端
			return;
		}
		else
		{
			reachToNodes = reachToNodesFinal;//将reachToNodesFinal赋给reachToNodes，开始下一轮循环
		}
	}   

}
DWORD SIMULATION11;
char* IP_ADDRESS;

int main(int argc, char **argv)
{
	/*HANDLE mutex;
	mutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, TEXT("memtest"));
	if (mutex == NULL)
	{
		//printf("null and create\n");
		mutex = CreateMutex(NULL, FALSE, TEXT("memtest"));
	}
	WaitForSingleObject(mutex, INFINITE);*/
	FILE* pFile;
	pFile = fopen(".\\Info.txt", "r");
	if (pFile == NULL)//读取配置文件
	{
		cout << "open the Info.txt failed!!!" << endl;
	}
	char inputLine[50] = {};
	fgets(inputLine, 50, pFile);
	char chFile[50];
	strcpy(chFile, inputLine);
	//cout << "inputLine:"<<inputLine << endl;
	int choose = atoi(inputLine);//0代表一个用户，1代表多个用户
	fgets(inputLine, 50, pFile);
	//cout << "inputLine:" << inputLine << endl;
	int i = 0;
	string port="";
	while (inputLine[i] != '\n')
	{
		//cout << inputLine[i];
		port += inputLine[i++];
	}
	
	cout << "choose:"<<choose << endl;
	cout << "port:" << port << endl;
	fclose(pFile);
	
	//ReleaseMutex(mutex);
	//CloseHandle(mutex);
	bool firstInvoke = true;
	if (choose == 0)//0代表一个用户
	{
		while (1)
		{
			//cout << chooseFlag << endl;
			WSADATA  Ws;
			/* Init Windows Socket */
			if (WSAStartup(MAKEWORD(2, 2), &Ws) != 0)//使用Winsock库函数之前,必须先调用函数WSAStartup,该函数负责初始化动态连接库Ws2_32.dll.
			{
				printf("Init Windows Socket Failed::%d\n", GetLastError());
				return -1;
			}
			int opt = 1;
			BOOL bNoDelay = TRUE;
			struct sockaddr_in ClientAddr;
			struct sockaddr_in server_addr;
			int server_socket;
			int client_socket;
			int ret = 0;
			/* connect socket */
			struct sockaddr_in client_addr;
			//int client_socket;
			int length;
			/* accept socket from client */
			length = sizeof(client_addr);

			server_addr.sin_family = AF_INET;
			server_addr.sin_addr.s_addr = htons(INADDR_ANY);//any ip address 
			server_addr.sin_port = htons(atoi(inputLine));
			memset(server_addr.sin_zero, 0x00, 8);

			/* create a socket */
			server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			setsockopt(server_socket, IPPROTO_TCP, TCP_NODELAY, (char FAR *)&bNoDelay, sizeof(BOOL));
			if (server_socket < 0)
			{
				printf("Create Socket Failed!");
				exit(1);
			}
			/*bind socket to a specified address */
			setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

			if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)))
			{
				printf("Server Bind Port : %d Failed!", HELLO_WORLD_SERVER_PORT);
				exit(1);
			}
			/* listen a socket */
			if (listen(server_socket, LENGTH_OF_LISTEN_QUEUE))
			{
				printf("Server Listen Failed!");
				exit(1);
			}
			client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &length);
			if (client_socket < 0)
			{
				printf("Server Accept Failed!\n");
				// break;
			}
			else
			{
				printf("Server Accept Succeed!\n");
			}
			char SendBuffer[1024];
			//获得propertyIndexMap中每个原子命题对应的号码，格式为p#0%q#1%，表示p对应的标号是0，q对应的标号为1
			//cout << "recv...." << endl;
			int n = recv(client_socket, SendBuffer, 1024, 0);
			//SendBuffer[n] = '\0';
			printf("SendBuffer2:%s\n", SendBuffer);
			char *result4 = NULL;
			result4 = strtok(SendBuffer, "#");
			propertyIndexMap.clear();
			while (result4 != NULL)
			{
				string str = result4;
				result4 = strtok(NULL, "%");
				propertyIndexMap.insert(pair< string, int >(str, atoi(result4)));
				cout << "str:" << str << endl;
				cout << "atoi(result4):" << atoi(result4) << endl;
				result4 = strtok(NULL, "#");
			}

			DWORD TIME1 = GetTickCount();
			//下面是接收ALTERNATELYINTERVAL的值
			recv(client_socket, SendBuffer, 1024, 0);
			//cout << "SendBuffer1:" << SendBuffer << endl;
			ALTERNATELYINTERVAL = atoi(SendBuffer) / THREADNUMBER;
			//cout << "ALTERNATELYINTERVAL:" << ALTERNATELYINTERVAL << endl;

			//下面是接收每个原子命题初始值的真假
			recv(client_socket, SendBuffer, 1024, 0);
			printf("SendBuffer1:%s", SendBuffer);

			start_propositionValue.clear();
			char *result3 = NULL;
			result3 = strtok(SendBuffer, "#");
			while (result3 != NULL)
			{
				int i = atoi(result3);
				start_propositionValue.push_back(atoi(result3));
				result3 = strtok(NULL, "#");
			}

			//接收待验证的性质
			recv(client_socket, SendBuffer, 1024, 0);
			char prop[1024];
			strcpy(prop, SendBuffer);
			cout << "prop:" << prop << endl;

			cout << "进入ptlnc函数" << endl;
			string stra, strc;
			yyin = NULL;

			FILE* pFile;
			pFile = fopen(".\\src", "w+");
			fputs(prop, pFile);
			fclose(pFile);

			yyin = fopen(".\\src", "rt+");//打开待处理文件
			yyparse(); // Call the parser
			fclose(yyin);
			if (remove(".\\src") != 0)//remove函数成功返回0
			{
				cout << "删除性质文件失败,程序退出!!!" << endl;
				return 0;
			}

			CTreeNode* m_syntaxTree = new CTreeNode(AND_STA, "AND", 0);
			m_syntaxTree->copy_tree1(g_syntaxTree);
			LNFG *lnfg;

			CNFMachine nf;
			if (!g_nErrors)
			{
				lnfg = new LNFG(g_syntaxTree);
				cout << "进入makeNO函数" << endl;
				makeNO(lnfg);
				drawPic(lnfg);
			}
			else
			{
				strc = "Form Error!";
				return 0;
			}

			int totalNodeNum = 0;
			map<int, vector<SNodeToENode> >::iterator SNodeToENodeMapIter1;
			for (SNodeToENodeMapIter1 = SNodeToENodeMap.begin(); SNodeToENodeMapIter1 != SNodeToENodeMap.end(); SNodeToENodeMapIter1++)
			{//将SNodeToENodeMap中的元素压入到SNodeToENodeVec中，以后访问的时候，通过下标就可以访问，不用每次都查找，节约时间	
				SNodeToENodeVec.push_back(SNodeToENodeMapIter1->second);
				totalNodeNum++;
			}

			if (firstInvoke == true)//只是在第一次调用的时候，调用tpool_create，并且为NoCounterExampleNodeArrayTotal分配空间
			{
				//为每一段创建一个线程池，MULTIPATHNUM表示线程池的大小，用宏定义
				for (int i = 0; i < THREADNUMBER; i++)
				{
					if (tpool_create(i, MULTIPATHNUM) != 0) {
						printf("tpool_create failed\n");
						exit(1);
					}
				}
				firstInvoke = false;
			}
			
			for (int i = 0; i < THREADNUMBER; i++)
			{
				NoCounterExampleNodeArrayTotal[i] = new int**[totalNodeNum];
				int i1, j1;
				for (i1 = 0; i1 < totalNodeNum; i1++)
				{
					NoCounterExampleNodeArrayTotal[i][i1] = new int*[totalNodeNum];
				}

				for (i1 = 0; i1 < totalNodeNum; i1++)
				{
					for (j1 = 0; j1 < totalNodeNum; j1++)
					{
						NoCounterExampleNodeArrayTotal[i][i1][j1] = new int[ALTERNATELYINTERVAL];
						memset(NoCounterExampleNodeArrayTotal[i][i1][j1], 0, ALTERNATELYINTERVAL * 4);//这里要注意，之前是total_length，现在改成total_length+1
					}
				}
			}
			
			
			TIME2 = GetTickCount();
			cout << "memset time:" << TIME2 - TIME1 << endl;
			//上面的内容只需要在刚开始的时候传输一次，下面的内容需要每次验证的时候都接收，因为路径上的信息是不断增加的
			SIMULATION11 = 0;//将each segment time清零，好看时间
			while (1)
			{
				DWORD SIMULATION3 = GetTickCount();
				int recvValue = recv(client_socket, SendBuffer, 1024, 0);//将客户端传过来的所有内容存到resultTotalArray中，包括reachToNodesFinal，每段起始节点的步长，$$empty1,$$state_num,ThreadIndex,每项用*隔开
				if (recvValue == 0 || recvValue == -1)
				{
					cout << "验证完成!!!" << endl;
					break;
				}
				else if (strcmp(SendBuffer, "endVerification") == 0)
				{
					cout << "等待下次迭代!!!" << endl;
					break;
				}
				printf("SendBufferRecv:%s", SendBuffer);
				DWORD SIMULATION4 = GetTickCount();
				//cout << "SIMULATION3"
				cout << "communication time:" << SIMULATION4 - SIMULATION3 << "ms" << endl;
				char *resultTotal = NULL;
				char resultTotalArray[7][1000];
				resultTotal = strtok(SendBuffer, "@");
				int resultTotalArrayIndex = 0;
				while (resultTotal != NULL)
				{
					strcpy(resultTotalArray[resultTotalArrayIndex], resultTotal);
					resultTotalArrayIndex++;
					//cout << "resultTotalArray[]" << resultTotalArrayIndex << ":" << resultTotalArray[resultTotalArrayIndex] << endl;
					resultTotal = strtok(NULL, "@");
				}
				char *result4 = NULL;
				result4 = strtok(resultTotalArray[0], "*");
				char atomicProTruthVal[10][100];//10表示原子命题个数最多为10个，100表示代表每个原子命题真假值改变的状态数目最多为50个，因为每个状态后有"#"
				int atomicProTruthValIndex = 0;
				g_propositionValue.clear();//先将g_propositionValue清空，否则会重复压入
				while (result4 != NULL)
				{
					strcpy(atomicProTruthVal[atomicProTruthValIndex], result4);
					atomicProTruthValIndex++;
					vector<int> p;
					g_propositionValue.push_back(p);
					result4 = strtok(NULL, "*");
				}
				for (int i = 0; i < atomicProTruthValIndex; i++)
				{
					char *result5 = NULL;
					result5 = strtok(atomicProTruthVal[i], "#");
					while (result5 != NULL)
					{
						g_propositionValue[i].push_back(atoi(result5));
						result5 = strtok(NULL, "#");
					}
				}
				char *result6 = NULL;
				reachToNodesFinal1.clear();
				result6 = strtok(resultTotalArray[1], "#");//将每段的起始节点存入到reachToNodesFinal中
				while (result6 != NULL)
				{
					reachToNodesFinal1.insert(atoi(result6));
					//cout << "atoi(result6):" << atoi(result6) << endl;
					result6 = strtok(NULL, "#");
				}
				int initialNodeCurrentLength = atoi(resultTotalArray[2]);
				$$empty1 = atoi(resultTotalArray[3]);
				$$state_num = atoi(resultTotalArray[4]);
				int segmentIndex = atoi(resultTotalArray[5]);//获得segmentIndex的值
				int idleServerIndex = atoi(resultTotalArray[6]);
				DWORD SIMULATION10 = GetTickCount();
				//EachSeg(initialNodeCurrentLength);
				TraceCheck(initialNodeCurrentLength);
				SIMULATION11 += GetTickCount() - SIMULATION10;
				cout << "each segment time:" << SIMULATION11 << endl;
				segWhileTime++;//每次调用Eachseg函数后，将segWhileTime值加1
				//返回结果
				//返回ThreadIndex#ModelCheckTheSameTimeResult#
				DWORD SIMULATION7 = GetTickCount();
				string SendBuffer1 = "";
				char* SendBuffer2;
				char c[5];
				itoa(segmentIndex, c, 10);
				SendBuffer1 += c;
				SendBuffer1 += "@";
				itoa(idleServerIndex, c, 10);
				SendBuffer1 += c;
				SendBuffer1 += "@";
				itoa(ModelCheckTheSameTimeResultTotal, c, 10);
				SendBuffer1 += c;
				SendBuffer1 += "#";
				SendBuffer1 += "@";
				vector<int>::iterator Iter1;
				for (Iter1 = EveryThreadToEmptyOrMoreStartNodesTotal.begin(); Iter1 != EveryThreadToEmptyOrMoreStartNodesTotal.end(); Iter1++)
				{
					itoa(*Iter1, c, 10);
					SendBuffer1 += c;
					SendBuffer1 += "#";
				}
				SendBuffer1 += "#";
				SendBuffer1 += "@";
				EveryThreadToEmptyOrMoreStartNodesTotal.clear();
				map<int, set<int> >::iterator Iter2;
				//以前是发送EveryThreadThroughPathStartNodesToFinalNodesArray，现在改成发送reachToNodes
				for (Iter2 = reachToNodes.begin(); Iter2 != reachToNodes.end(); Iter2++)
				{
					itoa(Iter2->first, c, 10);
					SendBuffer1 += c;
					SendBuffer1 += "%";
					set<int>::iterator Iter3;
					for (Iter3 = Iter2->second.begin(); Iter3 != Iter2->second.end(); Iter3++)
					{
						itoa(*Iter3, c, 10);
						SendBuffer1 += c;
						SendBuffer1 += "#";
					}
					SendBuffer1 += "*";
				}
				SendBuffer1 += "@";
				SendBuffer1 += "^";
				SendBuffer2 = (char*)SendBuffer1.c_str();
				char trans[1024];
				strcpy(trans, SendBuffer2);
				if (send(client_socket, trans, 1024, 0) < 0)
				{
					printf("Send Info Error1::\n");
				}
				reachToNodes.clear();
				reachToNodesFinal.clear();
				//printf("SendBufferSend:%s", SendBuffer2);
				DWORD SIMULATION8 = GetTickCount();
				cout << "result communication time:" << SIMULATION8 - SIMULATION7 << "ms" << endl;

			}
			//释放NoCounterExampleNodeArrayTotal申请的内存	
			for (int i = 0; i < THREADNUMBER; i++)
			{
				//tpool_destroy(i);	//整段完了之后，将线程销毁
				ReleaseNoCounterExampleNodeArray(NoCounterExampleNodeArrayTotal[i], totalNodeNum);
			}
			SNodeToENodeMap.clear();
			SNodeToENodeVec.clear();
			closesocket(client_socket);
			closesocket(server_socket);
		}
	}
	else if (choose == 1)//1代表多个用户
	{	
		int start_port = atoi(inputLine); //起始端口号
		pFile = fopen(".\\Info.txt", "w");//如果是一个用户则端口号不变，如果是多个用户则将端口号加1，重新存放到文件中
		fputs(chFile, pFile);
		char next_port[50];
		itoa(start_port + 1, next_port, 10);
		fputs(next_port, pFile);
		fputs("\n", pFile);
		fclose(pFile);
		cout << "start_port:" << start_port << endl;
		WSADATA  Ws;
		/* Init Windows Socket */
		if (WSAStartup(MAKEWORD(2, 2), &Ws) != 0)//使用Winsock库函数之前,必须先调用函数WSAStartup,该函数负责初始化动态连接库Ws2_32.dll.
		{
			printf("Init Windows Socket Failed::%d\n", GetLastError());
			return -1;
		}
		int opt = 1;
		BOOL bNoDelay = TRUE;
		struct sockaddr_in ClientAddr;
		struct sockaddr_in server_addr;
		int server_socket;
		int client_socket;
		int ret = 0;
		/* connect socket */
		struct sockaddr_in client_addr;
		//int client_socket;
		int length;
		/* accept socket from client */
		length = sizeof(client_addr);

		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = htons(INADDR_ANY);//any ip address 
		server_addr.sin_port = htons(start_port);
		memset(server_addr.sin_zero, 0x00, 8);
		//cout << start_port << endl;
		
		/* create a socket */
		server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		setsockopt(server_socket, IPPROTO_TCP, TCP_NODELAY, (char FAR *)&bNoDelay, sizeof(BOOL));
		if (server_socket < 0)
		{
			printf("Create Socket Failed!");
			exit(1);
		}
		/*bind socket to a specified address */
		setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

		if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)))
		{
			printf("Server Bind Port : %d Failed!", start_port);
			exit(1);
		}
		/* listen a socket */
		if (listen(server_socket, LENGTH_OF_LISTEN_QUEUE))
		{
			printf("Server Listen Failed!");
			exit(1);
		}
		client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &length);
		if (client_socket < 0)
		{
			printf("Server Accept Failed!\n");
			// break;
		}
		else
		{
			printf("Server Accept Succeed!\n");
		}

		//如果此进程和一个服务器传过来的连接成功，则重新创建一个进程继续监听
		SHELLEXECUTEINFO ShExecInfo = { 0 };
		ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		ShExecInfo.hwnd = NULL;
		ShExecInfo.lpVerb = NULL;
		ShExecInfo.lpFile = "Release\\test.exe";
		ShExecInfo.lpParameters = "";
		ShExecInfo.lpDirectory = NULL;
		ShExecInfo.nShow = SW_SHOW;
		ShExecInfo.hInstApp = NULL;
		ShellExecuteEx(&ShExecInfo);
		

		char SendBuffer[1024];
		//获得propertyIndexMap中每个原子命题对应的号码，格式为p#0%q#1%，表示p对应的标号是0，q对应的标号为1
		//cout << "recv...." << endl;
		int n = recv(client_socket, SendBuffer, 1024, 0);
		//SendBuffer[n] = '\0';
		printf("SendBuffer2:%s\n", SendBuffer);
		char *result4 = NULL;
		result4 = strtok(SendBuffer, "#");
		propertyIndexMap.clear();
		while (result4 != NULL)
		{
			string str = result4;
			result4 = strtok(NULL, "%");
			propertyIndexMap.insert(pair< string, int >(str, atoi(result4)));
			cout << "str:" << str << endl;
			cout << "atoi(result4):" << atoi(result4) << endl;
			result4 = strtok(NULL, "#");
		}

		DWORD TIME1 = GetTickCount();
		//下面是接收ALTERNATELYINTERVAL的值
		recv(client_socket, SendBuffer, 1024, 0);
		//cout << "SendBuffer1:" << SendBuffer << endl;
		ALTERNATELYINTERVAL = atoi(SendBuffer) / THREADNUMBER;
		//cout << "ALTERNATELYINTERVAL:" << ALTERNATELYINTERVAL << endl;

		//下面是接收每个原子命题初始值的真假
		recv(client_socket, SendBuffer, 1024, 0);
		printf("SendBuffer1:%s", SendBuffer);

		start_propositionValue.clear();
		char *result3 = NULL;
		result3 = strtok(SendBuffer, "#");
		while (result3 != NULL)
		{
			int i = atoi(result3);
			start_propositionValue.push_back(atoi(result3));
			result3 = strtok(NULL, "#");
		}

		//接收待验证的性质
		recv(client_socket, SendBuffer, 1024, 0);
		char prop[1024];
		strcpy(prop, SendBuffer);
		cout << "prop:" << prop << endl;

		cout << "进入ptlnc函数" << endl;
		string stra, strc;
		yyin = NULL;

		FILE* pFile1;
		string readFile = ".\\src";
		readFile += port;
		//cout << readFile.append("src").append(port).data() << endl;
		pFile1 = fopen(readFile.data(), "w+");//modified by hx at 2017/1/4
		//pFile1 = fopen(readFile.data(), "w+");
		fputs(prop, pFile1);
		fclose(pFile1);
		cout << readFile << endl;
		readFile = ".\\src";
		readFile += port;
		yyin = fopen(readFile.data(), "rt+");//modified by hx at 2017/1/4
		//cout << readFile << endl;
		//yyin = fopen(".\\src", "rt+");//打开待处理文件
		yyparse(); // Call the parser
		fclose(yyin);
		if (remove(readFile.data()) != 0)//remove函数成功返回0
		{
			cout << "删除性质文件失败,程序退出!!!" << endl;
			return 0;
		}
		CTreeNode* m_syntaxTree = new CTreeNode(AND_STA, "AND", 0);
		m_syntaxTree->copy_tree1(g_syntaxTree);
		LNFG *lnfg;

		CNFMachine nf;
		if (!g_nErrors)
		{
			lnfg = new LNFG(g_syntaxTree);
			cout << "进入makeNO函数" << endl;
			makeNO(lnfg);
			drawPic(lnfg);
		}
		else
		{
			strc = "Form Error!";
			return 0;
		}

		int totalNodeNum = 0;
		map<int, vector<SNodeToENode> >::iterator SNodeToENodeMapIter1;
		for (SNodeToENodeMapIter1 = SNodeToENodeMap.begin(); SNodeToENodeMapIter1 != SNodeToENodeMap.end(); SNodeToENodeMapIter1++)
		{//将SNodeToENodeMap中的元素压入到SNodeToENodeVec中，以后访问的时候，通过下标就可以访问，不用每次都查找，节约时间	
			SNodeToENodeVec.push_back(SNodeToENodeMapIter1->second);
			totalNodeNum++;
		}

		for (int i = 0; i < THREADNUMBER; i++)
		{
			NoCounterExampleNodeArrayTotal[i] = new int**[totalNodeNum];
			int i1, j1;
			for (i1 = 0; i1 < totalNodeNum; i1++)
			{
				NoCounterExampleNodeArrayTotal[i][i1] = new int*[totalNodeNum];
			}

			for (i1 = 0; i1 < totalNodeNum; i1++)
			{
				for (j1 = 0; j1 < totalNodeNum; j1++)
				{
					NoCounterExampleNodeArrayTotal[i][i1][j1] = new int[ALTERNATELYINTERVAL];
					memset(NoCounterExampleNodeArrayTotal[i][i1][j1], 0, ALTERNATELYINTERVAL * 4);//这里要注意，之前是total_length，现在改成total_length+1
				}
			}
		}
		//为每一段创建一个线程池，MULTIPATHNUM表示线程池的大小，用宏定义
		for (int i = 0; i < THREADNUMBER; i++)
		{
			if (tpool_create(i, MULTIPATHNUM) != 0) {
				printf("tpool_create failed\n");
				exit(1);
			}
		}
		
		TIME2 = GetTickCount();
		cout << "memset time:" << TIME2 - TIME1 << endl;
		//上面的内容只需要在刚开始的时候传输一次，下面的内容需要每次验证的时候都接收，因为路径上的信息是不断增加的
		while (1)
		{
			DWORD SIMULATION3 = GetTickCount();
			int recvValue = recv(client_socket, SendBuffer, 1024, 0);//将客户端传过来的所有内容存到resultTotalArray中，包括reachToNodesFinal，每段起始节点的步长，$$empty1,$$state_num,ThreadIndex,每项用*隔开
			if (recvValue == 0 || recvValue == -1)
			{
				cout << "验证完成!!!" << endl;
				break;
			}
			else if (strcmp(SendBuffer, "endVerification") == 0)
			{
				cout << "等待下次迭代!!!" << endl;
				break;
			}
			printf("SendBufferRecv:%s", SendBuffer);
			DWORD SIMULATION4 = GetTickCount();
			//cout << "SIMULATION3"
			cout << "communication time:" << SIMULATION4 - SIMULATION3 << "ms" << endl;
			char *resultTotal = NULL;
			char resultTotalArray[7][1000];
			resultTotal = strtok(SendBuffer, "@");
			int resultTotalArrayIndex = 0;
			while (resultTotal != NULL)
			{
				strcpy(resultTotalArray[resultTotalArrayIndex], resultTotal);
				resultTotalArrayIndex++;
				//cout << "resultTotalArray[]" << resultTotalArrayIndex << ":" << resultTotalArray[resultTotalArrayIndex] << endl;
				resultTotal = strtok(NULL, "@");
			}
			char *result4 = NULL;
			result4 = strtok(resultTotalArray[0], "*");
			char atomicProTruthVal[10][100];//10表示原子命题个数最多为10个，100表示代表每个原子命题真假值改变的状态数目最多为50个，因为每个状态后有"#"
			int atomicProTruthValIndex = 0;
			g_propositionValue.clear();//先将g_propositionValue清空，否则会重复压入
			while (result4 != NULL)
			{
				strcpy(atomicProTruthVal[atomicProTruthValIndex], result4);
				atomicProTruthValIndex++;
				vector<int> p;
				g_propositionValue.push_back(p);
				result4 = strtok(NULL, "*");
			}
			for (int i = 0; i < atomicProTruthValIndex; i++)
			{
				char *result5 = NULL;
				result5 = strtok(atomicProTruthVal[i], "#");
				while (result5 != NULL)
				{
					g_propositionValue[i].push_back(atoi(result5));
					result5 = strtok(NULL, "#");
				}
			}
			char *result6 = NULL;
			reachToNodesFinal1.clear();
			result6 = strtok(resultTotalArray[1], "#");//将每段的起始节点存入到reachToNodesFinal中
			while (result6 != NULL)
			{
				reachToNodesFinal1.insert(atoi(result6));
				//cout << "atoi(result6):" << atoi(result6) << endl;
				result6 = strtok(NULL, "#");
			}
			int initialNodeCurrentLength = atoi(resultTotalArray[2]);
			$$empty1 = atoi(resultTotalArray[3]);
			$$state_num = atoi(resultTotalArray[4]);
			int segmentIndex = atoi(resultTotalArray[5]);//获得segmentIndex的值
			int idleServerIndex = atoi(resultTotalArray[6]);
			DWORD SIMULATION10 = GetTickCount();
			//EachSeg(initialNodeCurrentLength);
			TraceCheck(initialNodeCurrentLength);
			SIMULATION11 += GetTickCount() - SIMULATION10;
			cout << "each segment time:" << SIMULATION11 << endl;
			segWhileTime++;//每次调用Eachseg函数后，将segWhileTime值加1
			//返回结果
			//返回ThreadIndex#ModelCheckTheSameTimeResult#
			DWORD SIMULATION7 = GetTickCount();
			string SendBuffer1 = "";
			char* SendBuffer2;
			char c[5];
			itoa(segmentIndex, c, 10);
			SendBuffer1 += c;
			SendBuffer1 += "@";
			itoa(idleServerIndex, c, 10);
			SendBuffer1 += c;
			SendBuffer1 += "@";
			itoa(ModelCheckTheSameTimeResultTotal, c, 10);
			SendBuffer1 += c;
			SendBuffer1 += "#";
			SendBuffer1 += "@";
			vector<int>::iterator Iter1;
			for (Iter1 = EveryThreadToEmptyOrMoreStartNodesTotal.begin(); Iter1 != EveryThreadToEmptyOrMoreStartNodesTotal.end(); Iter1++)
			{
				itoa(*Iter1, c, 10);
				SendBuffer1 += c;
				SendBuffer1 += "#";
			}
			SendBuffer1 += "#";
			SendBuffer1 += "@";
			EveryThreadToEmptyOrMoreStartNodesTotal.clear();
			map<int, set<int> >::iterator Iter2;
			//以前是发送EveryThreadThroughPathStartNodesToFinalNodesArray，现在改成发送reachToNodes
			for (Iter2 = reachToNodes.begin(); Iter2 != reachToNodes.end(); Iter2++)
			{
				itoa(Iter2->first, c, 10);
				SendBuffer1 += c;
				SendBuffer1 += "%";
				set<int>::iterator Iter3;
				for (Iter3 = Iter2->second.begin(); Iter3 != Iter2->second.end(); Iter3++)
				{
					itoa(*Iter3, c, 10);
					SendBuffer1 += c;
					SendBuffer1 += "#";
				}
				SendBuffer1 += "*";
			}
			SendBuffer1 += "@";
			SendBuffer1 += "^";
			SendBuffer2 = (char*)SendBuffer1.c_str();
			char trans[1024];
			strcpy(trans, SendBuffer2);
			if (send(client_socket, trans, 1024, 0) < 0)
			{
				printf("Send Info Error1::\n");
			}
			reachToNodes.clear();
			reachToNodesFinal.clear();
			//printf("SendBufferSend:%s", SendBuffer2);
			DWORD SIMULATION8 = GetTickCount();
			cout << "result communication time:" << SIMULATION8 - SIMULATION7 << "ms" << endl;

		}
		//释放NoCounterExampleNodeArrayTotal申请的内存	
		/*for (int i = 0; i < THREADNUMBER; i++)
		{
			tpool_destroy(i);	//整段完了之后，将线程销毁
			ReleaseNoCounterExampleNodeArray(NoCounterExampleNodeArrayTotal[i], totalNodeNum);
		}*/
		SNodeToENodeMap.clear();
		SNodeToENodeVec.clear();
		closesocket(client_socket);
		closesocket(server_socket);
	}
	else
	{
		cout << "choose error,please modify it!" << endl;
	}
	
	return 0;
}

