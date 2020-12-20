//��ԭʼ����
#include "function.h"
#include<map>
#include<stack>
#include <process.h>
#include <algorithm>
#include "tpool.h"
#include <stdio.h>
#include <Windows.h>


#pragma comment(lib,"ws2_32.lib")
int ALTERNATELYINTERVAL; //����ÿ��һ���߳�ִ�ж��ٸ�״̬

string IntTostring(int num)
{
	string str;
	string str1;
	stringstream ss;
	ss << num;
	ss >> str1;
	str = str1.c_str();
	return str;
}

//����֪��Ѱ��������ر�
int find_edge_by_point(LNFGEdge_set set, LNFGNode* ln)
{
	LNFGEdge_set::iterator iter;
	int i = 0;
	for (iter = set.begin(); iter != set.end(); iter++)
	{
		if ((*iter)->start->compare(ln->node) && (*iter)->alreadyDraw == false)
		{
			return i;
		}
		else
		{
			i++;
		}
	}
	return -1;
}
//�ɱߵ�ĩ��Ѱ�ҽڵ�
int find_node_from_edge(LNFGNode_set set, CTreeNode* ptree)
{
	LNFGNode_set::iterator iter;
	int i = 0;
	CNFMachine cnf;
	for (iter = set.begin(); iter != set.end(); iter++)
	{
		string rte = "";
		cnf.showout = "";
		rte += cnf.show(ptree);
		rte = "";
		cnf.showout = "";
		rte += cnf.show((*iter)->node);
		if ((*iter)->node->compare(ptree))
		{
			return i;
		}
		else
		{
			i++;
		}
	}
	return -1;
}
//�õ��ض��ĵ���CL�����еı��
int get_node_no_of_cl(LNFGNode_set set, LNFGNode* ln)
{
	LNFGNode_set::iterator iter;
	int i = 0;
	for (iter = set.begin(); iter != set.end(); iter++)
	{
		if ((*iter)->node->compare(ln->node))
		{
			return i;
		}
		else
		{
			i++;
		}
	}
	return -1;
}

bool makeNO(LNFG *lnfg)
{
	bool	m_emptyDraw = false;
	bool	m_terminalDraw = false;
	int m_terminalId;
	int m_emptyId;
	int edgeId = 1;
	int nodeId = 0;
	queue<LNFGNode*> NodeToExtend;


	lnfg->construct();
	cout << "construct�����Ѿ�����!!!" << endl;
	if (!lnfg->CL.empty())
	{

		//Ϊv0�Ľڵ����λ�ü����ţ�����ͼ
		CNFMachine cnf;
		LNFGNode_set::iterator iter;
		for (iter = lnfg->V0.begin(); iter != lnfg->V0.end(); iter++)//���ڵ�
		{
			int node_no_cl = get_node_no_of_cl(lnfg->CL, (*iter));
			lnfg->CL[node_no_cl]->already_draw = true;
			lnfg->CL[node_no_cl]->nodeNo = nodeId;
			lnfg->V0[node_no_cl]->nodeNo = nodeId;
			//���ӽڵ���ı���Ϣ
			//m_LNFGNodeInfo=lnfg->addNodeInfo(m_LNFGNodeInfo,lnfg->CL[node_no_cl]);

			if (lnfg->CL[node_no_cl]->node->type == EMPTY_EXP && lnfg->CL[node_no_cl]->m_isTrueEmpty == true)//�࿼��һ��terminal
			{
				//�Ӹ��ڵ�Ļ�ͼ����

				//	nodeId++;
				if (m_terminalDraw == true)
				{

				}
				else
				{
					//������ֹ�ڵ�
					m_emptyDraw = true;
					m_emptyId = lnfg->CL[node_no_cl]->nodeNo;
					m_terminalId = nodeId;
					m_terminalDraw = true;
					//������ֹ�ڵ�Ļ�ͼ��Ϣ

					nodeId++;
				}
				edgeId++;
			}
			else//���������
			{
				// 				//��ӱ�ǲ��ֵĻ�ͼ����

				lnfg->GetLabelOfNode(lnfg->CL[node_no_cl], &lnfg->CL[node_no_cl]->labelSet);
				//�Ӹ��ڵ�Ļ�ͼ����
				//	this->addStartNodeCodeInfo(lnfg->CL[node_no_cl]->nodeNo);
				NodeToExtend.push(lnfg->CL[node_no_cl]);//�������չ�ڵ����
				nodeId++;
			}

		}
		//������������ڵ����չ�ڵ�
		while (!NodeToExtend.empty())
		{
			LNFGNode *CurExtendNode = NodeToExtend.front();
			NodeToExtend.pop();
			int edge_no = find_edge_by_point(lnfg->EL, CurExtendNode);
			//update curPoint
			while (edge_no != -1)//����ÿһ�����߼���Ӧ�ս��
			{
				//������EPISILON�����ı�
				if (lnfg->EL[edge_no]->m_endTrueEMPTY == false && lnfg->EL[edge_no]->end->type == EMPTY_EXP)//terminal
				{
					lnfg->EL[edge_no]->alreadyDraw = true;
					if (m_terminalDraw == true)
					{
						lnfg->EL[edge_no]->edgeNo = edgeId;
						lnfg->EL[edge_no]->alreadyDraw = true;

						//Ϊ��������ʼ�ڵ����ֹ�ڵ�ı��
						lnfg->EL[edge_no]->startNo = CurExtendNode->nodeNo;
						lnfg->EL[edge_no]->endNo = m_terminalId;
						edgeId++;
					}
					else
					{
						//��terminal��
						m_terminalDraw = true;
						m_terminalId = nodeId;

						lnfg->EL[edge_no]->edgeNo = edgeId;
						lnfg->EL[edge_no]->alreadyDraw = true;

						//Ϊ��������ʼ�ڵ����ֹ�ڵ�ı��
						lnfg->EL[edge_no]->startNo = CurExtendNode->nodeNo;
						lnfg->EL[edge_no]->endNo = nodeId;
						edgeId++;
						nodeId++;
					}
				}
				else if (lnfg->EL[edge_no]->m_endTrueEMPTY == true)//empty
				{
					lnfg->EL[edge_no]->alreadyDraw = true;
					if (m_emptyDraw == true)
					{
						lnfg->EL[edge_no]->edgeNo = edgeId;
						lnfg->EL[edge_no]->alreadyDraw = true;
						//Ϊ��������ʼ�ڵ����ֹ�ڵ�ı��
						lnfg->EL[edge_no]->startNo = CurExtendNode->nodeNo;
						lnfg->EL[edge_no]->endNo = m_emptyId;
						edgeId++;
					}
					else
					{
						m_emptyDraw = true;
						m_emptyId = nodeId;
						lnfg->EL[edge_no]->edgeNo = edgeId;
						lnfg->EL[edge_no]->alreadyDraw = true;
						//Ϊ��������ʼ�ڵ����ֹ�ڵ�ı��
						lnfg->EL[edge_no]->startNo = CurExtendNode->nodeNo;
						lnfg->EL[edge_no]->endNo = nodeId;

						edgeId++;
						nodeId++;
						//��terminal��
						if (m_terminalDraw == true)
						{

							edgeId++;
						}
						else
						{
							//��terminal��
							m_terminalDraw = true;
							m_terminalId = nodeId;

							edgeId++;
							nodeId++;
						}
					}
				}
				else//��ͨ��
				{
					CTreeNode* ptree = lnfg->EL[edge_no]->end;
					int node_no = find_node_from_edge(lnfg->CL, ptree);

					if (node_no != -1)
					{
						int edgeEndId;
						if (lnfg->CL[node_no]->already_draw == false)
						{
							lnfg->EL[edge_no]->edgeNo = edgeId;
							lnfg->EL[edge_no]->alreadyDraw = true;
							//���ӱߵĻ�ͼ��Ϣ
							//addEdgeCodeInfo(CurExtendNode->nodeNo,nodeId,edgeId);

							lnfg->CL[node_no]->nodeNo = nodeId;
							lnfg->CL[node_no]->already_draw = true;

							lnfg->GetLabelOfNode(lnfg->CL[node_no], &lnfg->CL[node_no]->labelSet);
							edgeEndId = nodeId;
							NodeToExtend.push(lnfg->CL[node_no]);
							nodeId++;
						}
						else
						{
							lnfg->EL[edge_no]->edgeNo = edgeId;
							lnfg->EL[edge_no]->alreadyDraw = true;
							//���ӱߵĻ�ͼ��Ϣ

							edgeEndId = lnfg->CL[node_no]->nodeNo;

						}

						//Ϊ��������ʼ�ڵ����ֹ�ڵ�ı��
						lnfg->EL[edge_no]->startNo = CurExtendNode->nodeNo;
						lnfg->EL[edge_no]->endNo = edgeEndId;
						edgeId++;

					}
					else
					{
						lnfg->EL[edge_no]->alreadyDraw = true;
						//MessageBox("graph not complete!");
					}
				}
				edge_no = find_edge_by_point(lnfg->EL, CurExtendNode);
			}
		}

	}
	else
	{
		//	m_CLisEmpty=true;
		//**************����false����********************//ZXM ADD 2014.02.10
		//	UnsatisfyExplain+="��ʽ��������:\r\n������Ϊfalse\r\n";
		lnfg->satisfied = false;
	}
	if (!lnfg->CL.empty())
	{
		//empty�ڵ���
		LNFGNode_set::iterator iter;
		for (iter = lnfg->CL.begin(); iter != lnfg->CL.end(); iter++)
		{
			if ((*iter)->node->type == EMPTY_EXP)
			{
				(*iter)->nodeNo = m_terminalId;
			}
		}
		//bool satisfied = lnfg->DecisionProcecdure();//test
		//lnfg->satisfied = satisfied;
		//	LoopString=lnfg->LoopString;
	}
	return true;
}



bool edge_in_notSCC(LNFGEdge* edge, simpleGarph *graph)
{
	vector<simpleEdge*>::iterator iter;
	for (iter = graph->edgeSet.begin(); iter != graph->edgeSet.end(); ++iter)
	{

		if (edge->startNo == (*iter)->start&&edge->endNo == (*iter)->end)
			return true;
	}
	return false;
}

void GetLabelOfNode(LNFGNode* ln, int_set* label, LNFG *lnfg)//�õ��ڵ�ln�����ı�Ǽ��ϵı�ż�
{
	LNFGNode_set_of_set::iterator iter1;
	int label_num = 1;

	for (iter1 = lnfg->L.begin(); iter1 != lnfg->L.end(); iter1++)
	{
		LNFGNode_set::iterator iter2;
		for (iter2 = iter1->begin(); iter2 != iter1->end(); iter2++)
		{
			if ((*iter2)->node->compare(ln->node))
			{

				(*label).push_back(label_num);
				break;
			}
		}
		label_num++;
	}
}

void drawPic(LNFG *lnfg)
{
	string str_lnfg = drawLNFG(lnfg);
}

//extern vector< vector<bool> > g_propositionValue;  
extern vector< vector<int> > g_propositionValue;
extern map<string, int> propertyIndexMap;//�������ֶ�Ӧ���±�
extern vector<int> start_propositionValue;
extern vector<bool> last_propositionValue1;
//extern vector<int> last_propositionIndex;//�洢��һ��״̬��Ӧ��g_propositionValue�ĵڼ����±�
extern int last_propositionIndex[2];
extern CRITICAL_SECTION cs; // �����ٽ����������������OOP�ģ����Զ���Ϊ��non-static��Ա  
extern int lock;
//extern pthread_mutex_t mutex;
extern int $$state_num;
vector<bool> tmpAtomTruth;//��¼ÿ��״̬����ԭ����������
int count1 = 1;
extern int size1;
bool getAtoProTruth(int stateIndex, int atomicPropertyIndex)
{

	int VecSize = g_propositionValue[atomicPropertyIndex].size() - 1;
	int low = 0;
	int mid;
	int result;
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
			break;
		}
	}
	//the array does not contain the target
	if (low>VecSize)
	{
		result = low - 1;
		//cout<<"result:"<<result<<endl;
	}


	int firstNum = start_propositionValue[atomicPropertyIndex];
	if (result % 2 == firstNum)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

typedef struct
{
	CTreeNode* property;
	int endNodeNum;
	bool emptyFlag;//�˱�ָ��empty�ڵ�
	bool moreFlag;//�˱�ָ��more�ڵ�
}SNodeToENode;

map< int, vector<SNodeToENode> >SNodeToENodeMap;
vector< vector<SNodeToENode> >SNodeToENodeVec;//��SNodeToENodeMap�е�Ԫ��ѹ�뵽SNodeToENodeVec�У��Ժ���ʵ�ʱ��ͨ���±�Ϳ��Է��ʣ�����ÿ�ζ����ң���Լʱ��
map< int, vector<int> >NodeReachToNodesMap;//�洢��һ���ڵ��ܹ���������нڵ㣬����more�ڵ��empty�ڵ�
vector< vector<int> >NodeReachToNodesVec;//��NodeReachToNodesMap�е�Ԫ��ѹ�뵽NodeReachToNodesVec�У��Ժ���ʵ�ʱ��ͨ���±�Ϳ��Է��ʣ�����ÿ�ζ����ң���Լʱ��

typedef struct
{
	int InitialNodeNum;//��Ϊ�ֳ��˶��̣߳��˱�����¼����ýڵ��ʼ�ڵ�ı��
	int NodeNum;
	int current_length;
}ToExtendNode;
int total_length;

void FreeMallocAddr(vector<bool* > NoCounterExampleNodeMap)//�����ͷ�NoCounterExampleNodeMap��̬������ڴ�
{
	vector<bool* >::iterator NoCounterExampleNodeMapIter;
	for (NoCounterExampleNodeMapIter = NoCounterExampleNodeMap.begin(); NoCounterExampleNodeMapIter != NoCounterExampleNodeMap.end(); NoCounterExampleNodeMapIter++)
	{
		free(*NoCounterExampleNodeMapIter);
	}
}

vector <vector <int> > EveryThreadFinalNodes(THREADNUMBER);//��¼ÿ���߳�������֮��������ֹ�ڵ�ı��
vector <vector <int> > EveryThreadThroughPathStartNodes(THREADNUMBER);//��¼ÿ���߳������ߵ�ͨ��·���ĳ�ʼ�ڵ�

int EachPath(ToExtendNode currentExtendNode, int current_length, int ThreadIndex);
int EachSeg(int current_length);//����Ĳ�������Ҫ��ʼչ���Ĳ���

//
vector<map<int, set<int> > >EveryThreadThroughPathStartNodesToFinalNodesArrayFirst;//EveryThreadThroughPathStartNodesToFinalNodesArray��һ��Ԫ��
map<int, set<int> >EveryThreadThroughPathStartNodesToFinalNodesArrayTmp;
vector<vector<int> >EveryThreadToEmptyOrMoreStartNodes(THREADNUMBER);//��¼ÿ���߳��ܹ�����empty����more�ڵ�ĳ�ʼ�ڵ�
vector<ToExtendNode> GlobalToExtendNodeVec;//�洢ȫ�ֵĴ���չ�Ľڵ�

HANDLE threadProMultiPath[THREADNUMBER][MULTIPATHNUM];//������̶߳��������
int threadProMultiPathIndex[THREADNUMBER];//����ǰ�������ڼ����߳�


vector <vector<int> > edgeAtoProNum;//�洢ÿ������ԭ������ı��
vector <vector<vector<bool> > > edgeAtoProTruth;//�洢ÿ������ԭ����������

vector<ToExtendNode> ToExtendNodeVec2;
set<int> reachToNodes;//��ʱvector����¼��ʼ�ڵ�
int totalNodeNum = 0;//��¼���ʵ�LNFG��һ���м����ڵ�
bool stateNumOver[THREADNUMBER];//��¼ÿ���߳����Ƿ���֤����Ŀ�Ѿ��������������״̬��������ǣ�����Ϊtrue
/*inline bool *** CreateNoCounterExampleNodeArray()
{
//cout<<"totalNodeNum:"<<totalNodeNum<<endl;
bool *** NoCounterExampleNodeArray = new bool**[totalNodeNum];
int i, j;
for (i = 0; i < totalNodeNum; i++)
{
NoCounterExampleNodeArray[i] = new bool*[totalNodeNum];
}
for (i = 0; i < totalNodeNum; i++)
{
for (j = 0; j < totalNodeNum; j++)
{
NoCounterExampleNodeArray[i][j] = new bool[ALTERNATELYINTERVAL];
memset(NoCounterExampleNodeArray[i][j], 0, ALTERNATELYINTERVAL);//����Ҫע�⣬֮ǰ��total_length�����ڸĳ�total_length+1
}
}
return NoCounterExampleNodeArray;

}*/


extern int thisPathIsValid;
//int segWhileTime = 1;//add by yubin 2016-8-31,��ʾ�ڼ��β��еĴ������ɸ�segment��������ΪNoCounterExampleNodeArrayTotal��Ԫ�أ������Ͳ���ÿ�ζ���NoCounterExampleNodeArrayTotal����memset
int pace = 1;
#define PACE 1
int poolSize = MULTIPATHNUM;
int preTime=0;
bool mark = 1;
int prePoolSize = 0;

vector< vector<string> > edgeAtoProName;//ÿ������ԭ�����������
void GetEdgeAtomicPro(CTreeNode* property)
{
	CTreeNode* p = property;
	if (p != NULL)
	{
		if (p->type == IDENT_EXP && p->name_str[0] != 'l')
		{
			//cout<<"ԭ������Ϊ:"<<p->name_str<<endl;
			/*if (propertyIndexMap.find(property->name_str) == propertyIndexMap.end())//������ԭ�������Ӧ�������δ���뵽propertyIndexMap��
			{
				property->atomicPropertyIndex = propertyIndexMap.size();
				propertyIndexMap.insert(pair< string, int >(property->name_str, propertyIndexMap.size()));
			}
			else
			{
				property->atomicPropertyIndex = propertyIndexMap.find(property->name_str)->second;
			}*/
			property->atomicPropertyIndex = propertyIndexMap.find(property->name_str)->second;
			//cout << "property->atomicPropertyIndex: " << property->atomicPropertyIndex << endl;
			
		}
		else if (p->type == IDENT_EXP && p->name_str[0] == 'l')
		{
			property->atomicPropertyIndex = -1;//�������l��ͷ�Ļ�����atomicPropertyIndex��Ϊ-1��������__Sat�����У���ֻ���ж�atomicPropertyIndex�Ƿ�Ϊ1�����ˣ� �ӿ��ٶ�
		}
		else
		{
			if (p->type != IDENT_EXP)
			{
				GetEdgeAtomicPro(p->child[0]);
				GetEdgeAtomicPro(p->child[1]);
				GetEdgeAtomicPro(p->child[2]);
			}
		}

	}
}

void GetEdgeAtomicProNum(vector< vector<string> > edgeAtoProName)
{
	vector< vector<string> >::iterator edgeAtoProNameIter;
	vector<int> tmp1;
	vector<vector<bool> >tmp2;
	edgeAtoProNum.push_back(tmp1);//����Ϊ��ռλ
	edgeAtoProTruth.push_back(tmp2);//����Ϊ��ռλ
	for (edgeAtoProNameIter = edgeAtoProName.begin(); edgeAtoProNameIter != edgeAtoProName.end(); edgeAtoProNameIter++)
	{
		//int* tmp=(int*)malloc(sizeof(int)*((*edgeAtoProNameIter).size()));
		vector<int> tmp;

		vector<vector<bool> >tmp3;
		edgeAtoProTruth.push_back(tmp3);
		vector<string>::iterator iter1;
		//int i=0;
		for (iter1 = (*edgeAtoProNameIter).begin(); iter1 != (*edgeAtoProNameIter).end(); iter1++)
		{
			map<string, int>::iterator propositionIndex = propertyIndexMap.find(*iter1);
			if (propositionIndex == propertyIndexMap.end())//û�ҵ�
			{
				cout << "û���ҵ�" << *iter1 << "������ʧ��!" << endl;
				return;//���û���ҵ�������-1
			}
			tmp.push_back(propositionIndex->second);
			//tmp[i]=propositionIndex->second;
			//cout<<"i:"<<i<<"propositionIndex->second:"<<propositionIndex->second<<endl;
			//i++;
		}
		edgeAtoProNum.push_back(tmp);
	}

}

map< int, vector<int> >SNodeToENodeMapForBFS;//�˱���ֻ������������пɴ�ڵ�ʱ���õ�
int visited[200] = { 0 };
void DFS(int v, vector<int> &tmpVec1)
{
	map< int, vector<int> >::iterator iter = SNodeToENodeMapForBFS.find(v);
	vector<int>::iterator iter1;
	for (iter1 = (*iter).second.begin(); iter1 != (*iter).second.end(); iter1++)
	{	//begin�ǵ�һ���ڽӶ��㣬������û���ڽӶ��㣬�򷵻�
		if (!visited[(*iter1)])
		{
			visited[*iter1] = 1;
			tmpVec1.push_back(*iter1);
			DFS((*iter1), tmpVec1);; //��v����δ���ʵ��ڽӶ���w����DFS
		}
	}
}
void DFSTraverse()
{
	int i;
	map< int, vector<int> >::iterator iter1;
	int vexnum = SNodeToENodeMapForBFS.size();
	for (iter1 = SNodeToENodeMapForBFS.begin(); iter1 != SNodeToENodeMapForBFS.end(); iter1++)
	{
		vector<int> temp1;
		for (i = 0; i<200; i++)
		{
			visited[i] = 0;
		}
		DFS((*iter1).first, temp1);
		NodeReachToNodesMap.insert(pair< int, vector<int> >((*iter1).first, temp1));
	}

}

string drawLNFG(LNFG *lnfg)
{
	CNFMachine nf;

	LNFGEdge_set::iterator iter;
	string str_lnfg;
	int v0num = lnfg->V0.size();
	int hasEmptyNode = -1;
	int hasMoreNode = -1;
	int startNumber = -1;
	SNodeToENodeMapForBFS.clear();


	//add by yubin 2016-9-14
	LNFGNode_set::iterator iterNode;
	for (iterNode = lnfg->CL.begin(); iterNode != lnfg->CL.end(); iterNode++)
	{
		if ((*iterNode)->node->type == EMPTY_EXP)
		{
			hasEmptyNode = (*iterNode)->nodeNo; //��empty�ڵ�Ľ��Ÿ���hasEmptyNode������hasEmptyNode����-1
		}
		else if ((*iterNode)->node->type == TRUE_EXP)
		{
			hasMoreNode = (*iterNode)->nodeNo; //��true�ڵ�Ľ��Ÿ���hasMoreNode������hasMoreNode����-1
		}
	}


	//add by yubin 2016-9-2,Ϊ�˻�ýڵ�����пɴ�ڵ�
	if (!lnfg->EL.empty())  //�����б߶�Ӧ�Ŀ�ʼ�ڵ���ֱ�ӵ���Ľڵ�Ĺ�ϵ������SNodeToENodeMapForBFS
	{
		for (iter = lnfg->EL.begin(); iter != lnfg->EL.end(); iter++)//���ǰ�����ѹ��ģ�
		{
			//��ʼ�ڵ㲻����true,�����ڵ㲻����empty��more
			if (((*iter)->start->type != TRUE_EXP) && ((*iter)->end->type != EMPTY_EXP) && ((*iter)->end->type != TRUE_EXP))
			{
				startNumber = (*iter)->startNo;
				if (hasEmptyNode != -1 && (*iter)->startNo > hasEmptyNode)
				{
					startNumber--;
				}
				if (hasMoreNode != -1 && (*iter)->startNo > hasMoreNode)
				{
					startNumber--;
				}


				map< int, vector<int> >::iterator iter1 = SNodeToENodeMapForBFS.find(startNumber);
				int endNumber = (*iter)->endNo;
				if (hasEmptyNode != -1 && (*iter)->endNo > hasEmptyNode)
				{
					endNumber--;
				}
				if (hasMoreNode != -1 && (*iter)->endNo > hasMoreNode)
				{
					endNumber--;
				}

				if (iter1 == SNodeToENodeMapForBFS.end())//���û���ҵ�,����һ���µ�
				{
					vector<int> tmpVec;
					tmpVec.push_back(endNumber);
					SNodeToENodeMapForBFS.insert(pair< int, vector<int> >(startNumber, tmpVec));
				}
				else
				{
					iter1->second.push_back(endNumber);
				}
			}
		}
	}


	//���ڵ���Ϣд���ļ���ÿһ�еĵ�һ���ַ�0��ʾ��ͨ�ڵ� 1��ʾ��ʼ�ڵ�
	if (!lnfg->EL.empty())
	{
		for (iter = lnfg->EL.begin(); iter != lnfg->EL.end(); iter++)//���ǰ�����ѹ��ģ�
		{

			SNodeToENode tmpEndNode;
			tmpEndNode.endNodeNum = (*iter)->endNo;
			tmpEndNode.property = (*iter)->edgeSpec;
			tmpEndNode.emptyFlag = false;
			tmpEndNode.moreFlag = false;
			//tmpEndNode.edgeNum=(*iter)->edgeNo;
			//vector<string> tmpString;
			//edgeAtoProName.push_back(tmpString);
			GetEdgeAtomicPro(tmpEndNode.property);

			//cout<<"ELNum:"<<(*iter)->edgeNo<<endl;

			if ((*iter)->end->type == EMPTY_EXP)
			{
				tmpEndNode.emptyFlag = true;
				tmpEndNode.moreFlag = false;
				
				//vector<SNodeToENode> tmpVec;
				//SNodeToENodeMap.insert(pair< int, vector<SNodeToENode> >((*iter)->endNo, tmpVec));//ѹ��һ����ջ�����֮ǰѹ����insert�Ͳ岻��ȥ��
				
				//vector<int> tmpVec1;
				//NodeReachToNodesMap.insert(pair< int, vector<int> >((*iter)->endNo, tmpVec1));

			}
			else if ((*iter)->end->type == TRUE_EXP)//����true�ڵ㣬�Ѵ˽ڵ�����ͱ�Ϊmore�ڵ�
			{
				tmpEndNode.moreFlag = true;
				tmpEndNode.emptyFlag = false;
				//vector<SNodeToENode> tmpVec;
				//SNodeToENodeMap.insert(pair< int, vector<SNodeToENode> >((*iter)->endNo, tmpVec));//ѹ��һ����ջ�����֮ǰѹ����insert�Ͳ岻��ȥ��
				//vector<int> tmpVec1;
				//NodeReachToNodesMap.insert(pair< int, vector<int> >((*iter)->endNo, tmpVec1));
			}
			if ((*iter)->start->type != TRUE_EXP)//��true�ڵ�����ı߲����뵽SNodeToENodeMap��
			{
				//�޸ıߵĳ�ʼ�ڵ���
				startNumber = (*iter)->startNo;
				if (hasEmptyNode != -1 && (*iter)->startNo > hasEmptyNode)
				{
					startNumber--;
				}
				if (hasMoreNode != -1 && (*iter)->startNo > hasMoreNode)
				{
					startNumber--;
				}

				//�޸ıߵĵ���ڵ���
				int endNumber = (*iter)->endNo;
				if (hasEmptyNode != -1 && (*iter)->endNo > hasEmptyNode)
				{
					endNumber--;
				}
				if (hasMoreNode != -1 && (*iter)->endNo > hasMoreNode)
				{
					endNumber--;
				}
				tmpEndNode.endNodeNum = endNumber;

				
				map< int, vector<SNodeToENode> >::iterator iter1 = SNodeToENodeMap.find(startNumber);
				if (iter1 == SNodeToENodeMap.end())//���û���ҵ�,����һ���µ�
				{
					vector<SNodeToENode> tmpVec;
					tmpVec.push_back(tmpEndNode);
					SNodeToENodeMap.insert(pair< int, vector<SNodeToENode> >(startNumber, tmpVec));
				}
				else
				{
					iter1->second.push_back(tmpEndNode);
				}
			}
			else
			{
				cout << "�˱ߵĳ�ʼ�ڵ�Ϊ:" << (*iter)->startNo << ",Ϊtrue�������뵽SNodeToENodeMap��!!!" << endl;
			}

		}
	}

	/*map< int, vector<SNodeToENode> >::iterator iter3;
	for (iter3 = SNodeToENodeMap.begin(); iter3 != SNodeToENodeMap.end(); iter3++)
	{
		vector<SNodeToENode>::iterator temp1;
		cout << "SNO1:" << iter3->first << endl;
		for (temp1 = iter3->second.begin(); temp1 != iter3->second.end(); temp1++)
		{
			cout << " " << temp1->endNodeNum;;
		}
		cout << endl;
	}*/


	DFSTraverse();
	/*map< int, vector<int> >::iterator iter2;
	for (iter2 = NodeReachToNodesMap.begin(); iter2 != NodeReachToNodesMap.end(); iter2++)
	{
		vector<int>::iterator temp1;
		cout << "SNO:" << iter2->first << endl;
		for (temp1 = iter2->second.begin(); temp1 != iter2->second.end(); temp1++)
		{
			cout << " " << *temp1;
		}
		cout << endl;
	}*/
	return str_lnfg;
}