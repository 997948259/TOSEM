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
extern int ALTERNATELYINTERVAL; //����ÿ��һ���߳�ִ�ж��ٸ�״̬

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

map<string, int> propertyIndexMap;//�������ֶ�Ӧ���±�
typedef struct
{
	CTreeNode* property;
	int endNodeNum;
	bool emptyFlag;//�˱�ָ��empty�ڵ�
	bool moreFlag;//�˱�ָ��more�ڵ�
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
int EachSeg(int current_length);//����Ĳ�������Ҫ��ʼչ���Ĳ���

typedef struct
{
	int InitialNodeNum;//��Ϊ�ֳ��˶��̣߳��˱�����¼����ýڵ��ʼ�ڵ�ı��
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
		if (atomicPropertyIndex == -1)//�����fin��ǣ�����true
		{
			return true;
		}
		int VecSize = g_propositionValue[atomicPropertyIndex].size() - 1;
		int low = 0;
		int mid;
		int result;
		int firstNum = start_propositionValue[atomicPropertyIndex];
		while (low <= VecSize)//���ֲ���
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
		if (atomicPropertyIndex == -1)//�����fin��ǣ�����false
		{
			return false;
		}
		int VecSize = g_propositionValue[atomicPropertyIndex].size() - 1;
		int low = 0;
		int mid;
		int result;
		int firstNum = start_propositionValue[atomicPropertyIndex];

		while (low <= VecSize)//���ֲ���
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
	//cout<<"��������EachSeg����"<<endl;
	//cout<<"(int)pPM:"<<(int)pPM<<endl;
	EachSeg((int)pPM);
	return 1;
}

vector<ToExtendNode> ToExtendNodeVecTotal[THREADNUMBER];//�ݶ�Ϊ���еĶ���Ϊ5
map<int, set<int> > reachToNodesFinal;//��ʱvector����¼��ֹ�ڵ�
set<int> reachToNodesFinal1;
map<int, set<int> > EveryThreadThroughPathStartNodesToFinalNodesArray[THREADNUMBER];
map<int, set<int> > EveryThreadThroughPathStartNodesToFinalNodesArrayTotal;
vector<int> EveryThreadToEmptyOrMoreStartNodes[THREADNUMBER];
vector<int> EveryThreadToEmptyOrMoreStartNodesTotal;
int ModelCheckTheSameTimeResult[THREADNUMBER];
int ModelCheckTheSameTimeResultTotal = 0;//��¼�ۺ�ModelCheckTheSameTimeResult����֮��Ľ��
tpool_t *tpool[THREADNUMBER];
DWORD TIME1, TIME2;
pthread_mutex_t mutex;
int current_length_total = 0;
void* EachPath(void *arg)//current_length��ʾ���߳̿�ʼʱ����ʼ����
{
	//TIME1 = GetTickCount();
	//register int currenttmp = segWhileTime;
	ToExtendNode* ToExtendNodePointer = (ToExtendNode *)arg;
	ToExtendNode currentExtendNode;//��malloc������arg�е�ֵ�����ֲ�����currentExtendNode��Ȼ��free��
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
	int simulationStateNumCache = 0;//��������̴߳�ʱ���е���״̬����
	//cout<<"ThreadIndex111:"<<ThreadIndex<<endl;

	
	while (!ToExtendNodeVec.empty())
	{
		ToExtendNode currentExtendNode = ToExtendNodeVec.front();//��õ�ǰ����չ�Ľڵ�,ÿ�δ������ջ��ǰ��Ľڵ㣬ʹ�ÿ�����ȱ����ķ���
		vector< ToExtendNode >::iterator deleteIter = ToExtendNodeVec.begin();
		ToExtendNodeVec.erase(deleteIter); // ɾ����һ��Ԫ��
		//cout<<"��ǰ��չ:NodeNum:"<<currentExtendNode.NodeNum<<"current_length:"<<currentExtendNode.current_length<<endl;
		int currentNodeNum = currentExtendNode.NodeNum;//��õ�ǰ����չ�ڵ�Ľ���
		int currentNodeLength = currentExtendNode.current_length;
		if (currentNodeLength > $$state_num)//�����ǰ�ڵ���ڳ����״̬�������˳�
		{
			return NULL;
		}

		/*if (ToExtendNodeVec.size()>0 && tpool[ThreadIndex]->queue_cur_num < 5)//���ջ�����ж���ڵ�,�ָ�����߳�ȥ����
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
			if (currentEdge.emptyFlag == 1)//������LNFG�д˽ڵ�ָ��empty,���ҳ���Ҳ�������һ��״̬
			{
				//cout<<"�����֧1!!!"<<endl;
				if ($$empty1 == true && currentNodeLength == $$state_num)
				{
					if (__Sat(currentNodeLength, currentEdge.property))//������ʵĵ�ǰ�ڵ������չ
					{////����ָ��empty�ڵ㣬����Ҳ�������һ��״̬�����Һ�ȡ֮��Ϊtrue
						cout << "���ʲ�����3!!!" << endl;
						ModelCheckTheSameTimeResult[ThreadIndex] = -1;
						EveryThreadToEmptyOrMoreStartNodes[ThreadIndex].push_back(currentExtendNode.InitialNodeNum);
						//return NULL;//���ַ�����ֱ�ӷ��غ���
						//����е���empty�ڵ��·��������InitialNodeNumѹ�뵽EveryThreadToEmptyOrMoreStartNodes[ThreadIndex]�У���Ҫ���������ڵ㣬
						//��ǰ��ֱ��return�����ڻ��ü�������Ϊ����·�����ܺ��ϸ��̵߳����Ӳ����������ֱ�ӷ����ˣ����ܻ�Ѻ�����ܹ������ϵ�·�����
						continue;
					}
				}
			}
			else if (currentEdge.moreFlag == 1)
			{
				//cout<<"�����֧1!!!"<<endl;
				if ($$empty1 == false || currentNodeLength<$$state_num)
				{
					if (__Sat(currentNodeLength, currentEdge.property))//������ʵĵ�ǰ�ڵ������չ
					{//����ָ��empty�ڵ㣬����Ҳ�������һ��״̬�����Һ�ȡ֮��Ϊtrue
						cout << "���ʲ�����4!!!" << endl;
						
						//FreeMallocAddr(NoCounterExampleNodeMap);
						ModelCheckTheSameTimeResult[ThreadIndex] = -1;
						EveryThreadToEmptyOrMoreStartNodes[ThreadIndex].push_back(currentExtendNode.InitialNodeNum);
						//return NULL;//���ַ�����ֱ�ӷ��غ���
						//����е���empty�ڵ��·��������InitialNodeNumѹ�뵽EveryThreadToEmptyOrMoreStartNodes[ThreadIndex]�У���Ҫ���������ڵ㣬
						//��ǰ��ֱ��return�����ڻ��ü�������Ϊ����·�����ܺ��ϸ��̵߳����Ӳ����������ֱ�ӷ����ˣ����ܻ�Ѻ�����ܹ������ϵ�·�����
						continue;
					}
				}
			}
			else
			{
				//�����֤��״̬���Ȼ����״̬����С����϶�����ʵ�ķ���״̬��С�����������Ҫ��õ�״̬����ģ��ִ�е�״̬���࣬����Ҫ����һ��currentLengthCache��
				//�������֮��currentLengthCache���Ǳ���֤��״̬��С������֤�߳̾�Ҫ�ȴ������̣߳�����ֲ�����currentLengthCache��Ŀ���ǲ�ÿ�ζ�ȥ����ȫ�ֱ���$$state_num��ֵ
				
				//cout<<"�����֧8!!!"<<endl;
				if (__Sat(currentNodeLength, currentEdge.property))//������ʵĵ�ǰ�ڵ������չ
				{
					if (currentNodeLength + 1 < current_length_total + (ThreadIndex+1)*(ALTERNATELYINTERVAL))
					{
						//cout << "currentEdge.endNodeNum:" << currentEdge.endNodeNum << endl;
						//cout << "currentExtendNode.InitialNodeNum:" << currentExtendNode.InitialNodeNum << endl;
						if (NoCounterExampleNodeArrayTotal[ThreadIndex][currentEdge.endNodeNum][currentExtendNode.InitialNodeNum][(currentNodeLength + 1 - current_length)] == segWhileTime)
						{//�������Ľڵ�֮ǰ���ֹ������ý��˽ڵ�push��ToExtendNodeVec�У���ͬ�ڵ���ָ������ͬ����ʼ������ͬ���Ҳ���Ҳ��ͬ

							continue;//����ҵ�֮ǰ������Ľڵ㣬�򲻴���˽ڵ㣬ֱ�Ӵ�����һ���ڵ�
						}
						else//����˽ڵ�֮ǰû���뵽NoCounterExampleNodeArrayTotal[ThreadIndex]�У�������Ϊtrue
						{
							NoCounterExampleNodeArrayTotal[ThreadIndex][currentEdge.endNodeNum][currentExtendNode.InitialNodeNum][(currentNodeLength + 1 - current_length)] = segWhileTime;

							ToExtendNode ToExtendNodeTmp;
							ToExtendNodeTmp.InitialNodeNum = currentExtendNode.InitialNodeNum;//���½ڵ��InitialNodeNum��Ϊ��ǰ��չ�ڵ��InitialNodeNum
							ToExtendNodeTmp.NodeNum = currentEdge.endNodeNum;
							ToExtendNodeTmp.current_length = currentNodeLength + 1;
							ToExtendNodeVec.push_back(ToExtendNodeTmp);
						}

					}
					else
					{//���currentNodeLength+1==current_length+ALTERNATELYINTERVAL����ʾ�˽ڵ��Ǵ˶���չ�����һ���ڵ㣬���뵽ToExtendNodeVecTotal[ThreadIndex]��
						ToExtendNode ToExtendNodeTmp;
						ToExtendNodeTmp.InitialNodeNum = currentExtendNode.InitialNodeNum;//���½ڵ��InitialNodeNum��Ϊ��ǰ��չ�ڵ��InitialNodeNum
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
				//cout<<"�����֧9!!!"<<endl;
			}
		}
	}
	//TIME2 = GetTickCount() - TIME1;
	return NULL;
}

int EachSeg(int current_length)//����Ĳ�������Ҫ��ʼչ���Ĳ���
{
	vector<ToExtendNode> ToExtendNodeVec;
	//����ǵý�һЩȫ�ֱ�����λ�������Ӱ���������һ����֤���
	int ThreadIndex = (current_length - current_length_total) / (ALTERNATELYINTERVAL);
	ModelCheckTheSameTimeResult[ThreadIndex] = 0;
	ToExtendNodeVecTotal[ThreadIndex].clear();//�ǵ����
	EveryThreadToEmptyOrMoreStartNodes[ThreadIndex].clear();//��EveryThreadToEmptyOrMoreStartNodes��գ����������һֱ���еĻ�����Ӱ����һ�����н��
	EveryThreadThroughPathStartNodesToFinalNodesArray[ThreadIndex].clear();

	pthread_mutex_init(&mutex, NULL); //��Ĭ�����Գ�ʼ��һ������������

	set<int>::iterator iter1;
	for (iter1 = reachToNodesFinal1.begin(); iter1 != reachToNodesFinal1.end(); iter1++)
	{
		ToExtendNode firstNode;
		firstNode.InitialNodeNum = *iter1;//����ʼ�ڵ��InitialNodeNum��Ϊ-1
		firstNode.NodeNum = *iter1;//��ʼ�ڵ�ı��Ϊ1
		firstNode.current_length = current_length;//��ʼ����Ϊ����current_length��ֵ
		ToExtendNodeVec.push_back(firstNode);

		set<int> tmpVec1;
		EveryThreadThroughPathStartNodesToFinalNodesArray[ThreadIndex].insert(pair< int, set<int> >(*iter1, tmpVec1));
	}

	
	tpool[ThreadIndex]->cur_max_thr_num = 5;//Ŀǰ�̳߳صĴ�С�ǹ̶��ģ���Ϊ5

	vector<ToExtendNode>::iterator ToExtendNodeVecIter;
	//DWORD SIMULATION1 = GetTickCount();
	for (ToExtendNodeVecIter = ToExtendNodeVec.begin(); ToExtendNodeVecIter != ToExtendNodeVec.end(); ToExtendNodeVecIter++)
	{
		ToExtendNode* tmpMalloc = (ToExtendNode*)malloc(sizeof(ToExtendNode));
		tmpMalloc->InitialNodeNum = ToExtendNodeVecIter->InitialNodeNum;
		tmpMalloc->NodeNum = ToExtendNodeVecIter->NodeNum;
		tmpMalloc->current_length = ToExtendNodeVecIter->current_length;

		tpool_add_work(ThreadIndex,EachPath, (void*)tmpMalloc);//��ÿһ���ڵ㽻��һ���߳�ȥ����
		//EachPath((void*)tmpMalloc);
	}
	//DWORD SIMULATION2 = GetTickCount();
	
	DWORD SIMULATION1 = GetTickCount();
	tpool_await(ThreadIndex);//�ȴ��̳߳��е������̶߳�ִ�н���
	DWORD SIMULATION2 = GetTickCount();
	//cout << "each path time:" << SIMULATION2 - SIMULATION1 << endl;
	if (current_length <= $$state_num)
	{
		if (ToExtendNodeVecTotal[ThreadIndex].empty() && EveryThreadToEmptyOrMoreStartNodes[ThreadIndex].empty())//û�нڵ������չ������1��ʾ��������
		{
			ModelCheckTheSameTimeResult[ThreadIndex] = 1;
			return 1;
		}
		else//��ʾĿǰ���нڵ���Ҫ��һ����չ
		{
			vector<ToExtendNode>::iterator ToExtendNodeVecIter;
			for (ToExtendNodeVecIter = ToExtendNodeVecTotal[ThreadIndex].begin(); ToExtendNodeVecIter != ToExtendNodeVecTotal[ThreadIndex].end(); ToExtendNodeVecIter++)
			{
				map<int, set<int> >::iterator iter3 = EveryThreadThroughPathStartNodesToFinalNodesArray[ThreadIndex].find(ToExtendNodeVecIter->InitialNodeNum);
				if (iter3 != EveryThreadThroughPathStartNodesToFinalNodesArray[ThreadIndex].end())//���map���г�ʼ�ڵ㣬ֱ��ѹ����ֹ�ڵ�
				{
					set<int>::iterator findResult = iter3->second.find(ToExtendNodeVecIter->NodeNum);

					if (findResult == iter3->second.end()) //û�ҵ��Ļ����ٰѿɴ�ڵ�ѹ��ȥ�������ѹ��ܶ��ظ��Ľڵ�
					{
						iter3->second.insert(ToExtendNodeVecIter->NodeNum);
					}
					else
					{
						//cout<<"�Ѵ�����ͬ�ڵ�!!!"<<endl;	
					}
				}
				else
				{
					cout << "ToExtendNodeVecIter->InitialNodeNum:" << ToExtendNodeVecIter->InitialNodeNum << endl;
					cout << "�߳̽�������EveryThreadThroughPathStartNodesToFinalNodesʱ����!!!" << endl;
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

HANDLE threadPro1[THREADNUMBER];//������̶߳��������
map<int, set<int> > reachToNodes;//��ʱvector����¼��ʼ�ڵ�

void TraceCheck(int initialNodeCurrentLength)//initialNodeCurrentLength��ʾ�ӿͻ��˴������ĳ�ʼ����
{
	//cout << "�Ѿ�����TraceCheck����" << endl;
	current_length_total = initialNodeCurrentLength;//��һ�εĳ�ʼ����
	ModelCheckTheSameTimeResultTotal = 0;
	if (initialNodeCurrentLength == 150)
	{
		int a = 0;
	}
	for (int i = 0; i < THREADNUMBER; i++)
	{
		threadPro1[i] = (HANDLE)_beginthreadex(NULL, 0, FunProc2, (void*)(initialNodeCurrentLength + i*(ALTERNATELYINTERVAL)), 0, NULL);
	}
	WaitForMultipleObjects(THREADNUMBER, threadPro1, TRUE, INFINITE);//�ȴ�����߳�ͬʱ����
	
	//������reduce�Ĺ���
	for (int j = 0; j<THREADNUMBER; j++)//�ж�ModelCheckTheSameTimeResult���Ƿ����Ԫ��Ϊ1
	{
		if (ModelCheckTheSameTimeResult[j] == 1)//����Ƿ�����߳������·�ǲ�ͨ�ģ������һ���ǲ�ͨ�ģ�����·Ҳ��ͨ����ʱ���ʿ϶�����
		{
			cout << "������������!!!" << endl;
			ModelCheckTheSameTimeResultTotal = 1;//ֻҪ����ModelCheckTheSameTimeResult����һ��Ԫ��Ϊ1����ModelCheckTheSameTimeResultTotal������Ϊ1
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
		//������һ����Ҫ�޸ģ��Ȳ�����һ�Σ������ط��޸ĺ�֮�����޸���һ��
		if (!EveryThreadToEmptyOrMoreStartNodes[Threadi].empty())//������ڽڵ��ܹ�����empty����more�ڵ�
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
						cout << "�нڵ��ܹ�����empty����more�ڵ㣬������ʲ�����!!!" << endl;
						//thisPathIsValid = false;
						//������empty����more�ĳ�ʼ�ڵ�ѹ�뵽EveryThreadToEmptyOrMoreStartNodesTotal��
						//�����ͻ��˴���Ҳ��EveryThreadToEmptyOrMoreStartNodesTotal����������
						EveryThreadToEmptyOrMoreStartNodesTotal.push_back(iter1->first);
					}
				}
			}
		}

		//���û���ҵ��ɵ���empty�ڵ����more�ڵ��·�����ٽ����������
		map<int, set<int> >::iterator iter5;
		reachToNodesFinal.clear();//��reachToNodesFinal���  
		for (iter5 = reachToNodes.begin(); iter5 != reachToNodes.end(); iter5++)//������ʼ�ڵ�
		{
			//cout<<"*iter5:"<<*iter5<<endl;
			EveryThreadThroughPathStartNodesToFinalNodes = EveryThreadThroughPathStartNodesToFinalNodesArray[Threadi];
			set<int>::iterator iter6;
			for (iter6 = iter5->second.begin(); iter6 != iter5->second.end(); iter6++)
			{
				iter4 = EveryThreadThroughPathStartNodesToFinalNodes.find(*iter6);//��EveryThreadThroughPathStartNodesToFinalNodes�в�����(*iter5)��Ϊ������ֹ�ڵ�
				if (iter4 != EveryThreadThroughPathStartNodesToFinalNodes.end())
				{//������ڵĻ�������(*iter5)��Ϊ������ֹ�ڵ���뵽reachToNodesFinal��
				
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
					//��Ϊ��������£���ʹsecondΪ�գ�Ҳ���ҵ����������û���ҵ�������ʾ����
					cout << "���ҳ���!!!" << endl;
				}
			}
			
		}
		
		if (reachToNodesFinal.empty())//�����һ���̵߳���ֹ�ڵ����һ���̵߳���ʼ�ڵ��νӲ��ϣ����ʾ��չ��ͨ����ʱ���ʳ���
		{
			cout << "һ���߳����ɴ�ڵ����һ�����̵ĳ�ʼ�ڵ�û�н�����������ʳ���!!!" << endl;
			ModelCheckTheSameTimeResultTotal = 1;//���˱�����Ϊ1��Ȼ�󴫸��ͻ���
			return;
		}
		else
		{
			reachToNodes = reachToNodesFinal;//��reachToNodesFinal����reachToNodes����ʼ��һ��ѭ��
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
	if (pFile == NULL)//��ȡ�����ļ�
	{
		cout << "open the Info.txt failed!!!" << endl;
	}
	char inputLine[50] = {};
	fgets(inputLine, 50, pFile);
	char chFile[50];
	strcpy(chFile, inputLine);
	//cout << "inputLine:"<<inputLine << endl;
	int choose = atoi(inputLine);//0����һ���û���1�������û�
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
	if (choose == 0)//0����һ���û�
	{
		while (1)
		{
			//cout << chooseFlag << endl;
			WSADATA  Ws;
			/* Init Windows Socket */
			if (WSAStartup(MAKEWORD(2, 2), &Ws) != 0)//ʹ��Winsock�⺯��֮ǰ,�����ȵ��ú���WSAStartup,�ú��������ʼ����̬���ӿ�Ws2_32.dll.
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
			//���propertyIndexMap��ÿ��ԭ�������Ӧ�ĺ��룬��ʽΪp#0%q#1%����ʾp��Ӧ�ı����0��q��Ӧ�ı��Ϊ1
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
			//�����ǽ���ALTERNATELYINTERVAL��ֵ
			recv(client_socket, SendBuffer, 1024, 0);
			//cout << "SendBuffer1:" << SendBuffer << endl;
			ALTERNATELYINTERVAL = atoi(SendBuffer) / THREADNUMBER;
			//cout << "ALTERNATELYINTERVAL:" << ALTERNATELYINTERVAL << endl;

			//�����ǽ���ÿ��ԭ�������ʼֵ�����
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

			//���մ���֤������
			recv(client_socket, SendBuffer, 1024, 0);
			char prop[1024];
			strcpy(prop, SendBuffer);
			cout << "prop:" << prop << endl;

			cout << "����ptlnc����" << endl;
			string stra, strc;
			yyin = NULL;

			FILE* pFile;
			pFile = fopen(".\\src", "w+");
			fputs(prop, pFile);
			fclose(pFile);

			yyin = fopen(".\\src", "rt+");//�򿪴������ļ�
			yyparse(); // Call the parser
			fclose(yyin);
			if (remove(".\\src") != 0)//remove�����ɹ�����0
			{
				cout << "ɾ�������ļ�ʧ��,�����˳�!!!" << endl;
				return 0;
			}

			CTreeNode* m_syntaxTree = new CTreeNode(AND_STA, "AND", 0);
			m_syntaxTree->copy_tree1(g_syntaxTree);
			LNFG *lnfg;

			CNFMachine nf;
			if (!g_nErrors)
			{
				lnfg = new LNFG(g_syntaxTree);
				cout << "����makeNO����" << endl;
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
			{//��SNodeToENodeMap�е�Ԫ��ѹ�뵽SNodeToENodeVec�У��Ժ���ʵ�ʱ��ͨ���±�Ϳ��Է��ʣ�����ÿ�ζ����ң���Լʱ��	
				SNodeToENodeVec.push_back(SNodeToENodeMapIter1->second);
				totalNodeNum++;
			}

			if (firstInvoke == true)//ֻ���ڵ�һ�ε��õ�ʱ�򣬵���tpool_create������ΪNoCounterExampleNodeArrayTotal����ռ�
			{
				//Ϊÿһ�δ���һ���̳߳أ�MULTIPATHNUM��ʾ�̳߳صĴ�С���ú궨��
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
						memset(NoCounterExampleNodeArrayTotal[i][i1][j1], 0, ALTERNATELYINTERVAL * 4);//����Ҫע�⣬֮ǰ��total_length�����ڸĳ�total_length+1
					}
				}
			}
			
			
			TIME2 = GetTickCount();
			cout << "memset time:" << TIME2 - TIME1 << endl;
			//���������ֻ��Ҫ�ڸտ�ʼ��ʱ����һ�Σ������������Ҫÿ����֤��ʱ�򶼽��գ���Ϊ·���ϵ���Ϣ�ǲ������ӵ�
			SIMULATION11 = 0;//��each segment time���㣬�ÿ�ʱ��
			while (1)
			{
				DWORD SIMULATION3 = GetTickCount();
				int recvValue = recv(client_socket, SendBuffer, 1024, 0);//���ͻ��˴��������������ݴ浽resultTotalArray�У�����reachToNodesFinal��ÿ����ʼ�ڵ�Ĳ�����$$empty1,$$state_num,ThreadIndex,ÿ����*����
				if (recvValue == 0 || recvValue == -1)
				{
					cout << "��֤���!!!" << endl;
					break;
				}
				else if (strcmp(SendBuffer, "endVerification") == 0)
				{
					cout << "�ȴ��´ε���!!!" << endl;
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
				char atomicProTruthVal[10][100];//10��ʾԭ������������Ϊ10����100��ʾ����ÿ��ԭ���������ֵ�ı��״̬��Ŀ���Ϊ50������Ϊÿ��״̬����"#"
				int atomicProTruthValIndex = 0;
				g_propositionValue.clear();//�Ƚ�g_propositionValue��գ�������ظ�ѹ��
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
				result6 = strtok(resultTotalArray[1], "#");//��ÿ�ε���ʼ�ڵ���뵽reachToNodesFinal��
				while (result6 != NULL)
				{
					reachToNodesFinal1.insert(atoi(result6));
					//cout << "atoi(result6):" << atoi(result6) << endl;
					result6 = strtok(NULL, "#");
				}
				int initialNodeCurrentLength = atoi(resultTotalArray[2]);
				$$empty1 = atoi(resultTotalArray[3]);
				$$state_num = atoi(resultTotalArray[4]);
				int segmentIndex = atoi(resultTotalArray[5]);//���segmentIndex��ֵ
				int idleServerIndex = atoi(resultTotalArray[6]);
				DWORD SIMULATION10 = GetTickCount();
				//EachSeg(initialNodeCurrentLength);
				TraceCheck(initialNodeCurrentLength);
				SIMULATION11 += GetTickCount() - SIMULATION10;
				cout << "each segment time:" << SIMULATION11 << endl;
				segWhileTime++;//ÿ�ε���Eachseg�����󣬽�segWhileTimeֵ��1
				//���ؽ��
				//����ThreadIndex#ModelCheckTheSameTimeResult#
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
				//��ǰ�Ƿ���EveryThreadThroughPathStartNodesToFinalNodesArray�����ڸĳɷ���reachToNodes
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
			//�ͷ�NoCounterExampleNodeArrayTotal������ڴ�	
			for (int i = 0; i < THREADNUMBER; i++)
			{
				//tpool_destroy(i);	//��������֮�󣬽��߳�����
				ReleaseNoCounterExampleNodeArray(NoCounterExampleNodeArrayTotal[i], totalNodeNum);
			}
			SNodeToENodeMap.clear();
			SNodeToENodeVec.clear();
			closesocket(client_socket);
			closesocket(server_socket);
		}
	}
	else if (choose == 1)//1�������û�
	{	
		int start_port = atoi(inputLine); //��ʼ�˿ں�
		pFile = fopen(".\\Info.txt", "w");//�����һ���û���˿ںŲ��䣬����Ƕ���û��򽫶˿ںż�1�����´�ŵ��ļ���
		fputs(chFile, pFile);
		char next_port[50];
		itoa(start_port + 1, next_port, 10);
		fputs(next_port, pFile);
		fputs("\n", pFile);
		fclose(pFile);
		cout << "start_port:" << start_port << endl;
		WSADATA  Ws;
		/* Init Windows Socket */
		if (WSAStartup(MAKEWORD(2, 2), &Ws) != 0)//ʹ��Winsock�⺯��֮ǰ,�����ȵ��ú���WSAStartup,�ú��������ʼ����̬���ӿ�Ws2_32.dll.
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

		//����˽��̺�һ�������������������ӳɹ��������´���һ�����̼�������
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
		//���propertyIndexMap��ÿ��ԭ�������Ӧ�ĺ��룬��ʽΪp#0%q#1%����ʾp��Ӧ�ı����0��q��Ӧ�ı��Ϊ1
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
		//�����ǽ���ALTERNATELYINTERVAL��ֵ
		recv(client_socket, SendBuffer, 1024, 0);
		//cout << "SendBuffer1:" << SendBuffer << endl;
		ALTERNATELYINTERVAL = atoi(SendBuffer) / THREADNUMBER;
		//cout << "ALTERNATELYINTERVAL:" << ALTERNATELYINTERVAL << endl;

		//�����ǽ���ÿ��ԭ�������ʼֵ�����
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

		//���մ���֤������
		recv(client_socket, SendBuffer, 1024, 0);
		char prop[1024];
		strcpy(prop, SendBuffer);
		cout << "prop:" << prop << endl;

		cout << "����ptlnc����" << endl;
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
		//yyin = fopen(".\\src", "rt+");//�򿪴������ļ�
		yyparse(); // Call the parser
		fclose(yyin);
		if (remove(readFile.data()) != 0)//remove�����ɹ�����0
		{
			cout << "ɾ�������ļ�ʧ��,�����˳�!!!" << endl;
			return 0;
		}
		CTreeNode* m_syntaxTree = new CTreeNode(AND_STA, "AND", 0);
		m_syntaxTree->copy_tree1(g_syntaxTree);
		LNFG *lnfg;

		CNFMachine nf;
		if (!g_nErrors)
		{
			lnfg = new LNFG(g_syntaxTree);
			cout << "����makeNO����" << endl;
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
		{//��SNodeToENodeMap�е�Ԫ��ѹ�뵽SNodeToENodeVec�У��Ժ���ʵ�ʱ��ͨ���±�Ϳ��Է��ʣ�����ÿ�ζ����ң���Լʱ��	
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
					memset(NoCounterExampleNodeArrayTotal[i][i1][j1], 0, ALTERNATELYINTERVAL * 4);//����Ҫע�⣬֮ǰ��total_length�����ڸĳ�total_length+1
				}
			}
		}
		//Ϊÿһ�δ���һ���̳߳أ�MULTIPATHNUM��ʾ�̳߳صĴ�С���ú궨��
		for (int i = 0; i < THREADNUMBER; i++)
		{
			if (tpool_create(i, MULTIPATHNUM) != 0) {
				printf("tpool_create failed\n");
				exit(1);
			}
		}
		
		TIME2 = GetTickCount();
		cout << "memset time:" << TIME2 - TIME1 << endl;
		//���������ֻ��Ҫ�ڸտ�ʼ��ʱ����һ�Σ������������Ҫÿ����֤��ʱ�򶼽��գ���Ϊ·���ϵ���Ϣ�ǲ������ӵ�
		while (1)
		{
			DWORD SIMULATION3 = GetTickCount();
			int recvValue = recv(client_socket, SendBuffer, 1024, 0);//���ͻ��˴��������������ݴ浽resultTotalArray�У�����reachToNodesFinal��ÿ����ʼ�ڵ�Ĳ�����$$empty1,$$state_num,ThreadIndex,ÿ����*����
			if (recvValue == 0 || recvValue == -1)
			{
				cout << "��֤���!!!" << endl;
				break;
			}
			else if (strcmp(SendBuffer, "endVerification") == 0)
			{
				cout << "�ȴ��´ε���!!!" << endl;
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
			char atomicProTruthVal[10][100];//10��ʾԭ������������Ϊ10����100��ʾ����ÿ��ԭ���������ֵ�ı��״̬��Ŀ���Ϊ50������Ϊÿ��״̬����"#"
			int atomicProTruthValIndex = 0;
			g_propositionValue.clear();//�Ƚ�g_propositionValue��գ�������ظ�ѹ��
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
			result6 = strtok(resultTotalArray[1], "#");//��ÿ�ε���ʼ�ڵ���뵽reachToNodesFinal��
			while (result6 != NULL)
			{
				reachToNodesFinal1.insert(atoi(result6));
				//cout << "atoi(result6):" << atoi(result6) << endl;
				result6 = strtok(NULL, "#");
			}
			int initialNodeCurrentLength = atoi(resultTotalArray[2]);
			$$empty1 = atoi(resultTotalArray[3]);
			$$state_num = atoi(resultTotalArray[4]);
			int segmentIndex = atoi(resultTotalArray[5]);//���segmentIndex��ֵ
			int idleServerIndex = atoi(resultTotalArray[6]);
			DWORD SIMULATION10 = GetTickCount();
			//EachSeg(initialNodeCurrentLength);
			TraceCheck(initialNodeCurrentLength);
			SIMULATION11 += GetTickCount() - SIMULATION10;
			cout << "each segment time:" << SIMULATION11 << endl;
			segWhileTime++;//ÿ�ε���Eachseg�����󣬽�segWhileTimeֵ��1
			//���ؽ��
			//����ThreadIndex#ModelCheckTheSameTimeResult#
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
			//��ǰ�Ƿ���EveryThreadThroughPathStartNodesToFinalNodesArray�����ڸĳɷ���reachToNodes
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
		//�ͷ�NoCounterExampleNodeArrayTotal������ڴ�	
		/*for (int i = 0; i < THREADNUMBER; i++)
		{
			tpool_destroy(i);	//��������֮�󣬽��߳�����
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

