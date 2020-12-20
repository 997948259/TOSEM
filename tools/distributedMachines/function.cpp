//最原始备份
#include "function.h"
#include<map>
#include<stack>
#include <process.h>
#include <algorithm>
#include "tpool.h"
#include <stdio.h>
#include <Windows.h>


#pragma comment(lib,"ws2_32.lib")
int ALTERNATELYINTERVAL; //定义每次一个线程执行多少个状态

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

//由已知点寻找它的相关边
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
//由边的末端寻找节点
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
//得到特定的点在CL集合中的编号
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
	cout << "construct函数已经结束!!!" << endl;
	if (!lnfg->CL.empty())
	{

		//为v0的节点分配位置加入编号，并画图
		CNFMachine cnf;
		LNFGNode_set::iterator iter;
		for (iter = lnfg->V0.begin(); iter != lnfg->V0.end(); iter++)//根节点
		{
			int node_no_cl = get_node_no_of_cl(lnfg->CL, (*iter));
			lnfg->CL[node_no_cl]->already_draw = true;
			lnfg->CL[node_no_cl]->nodeNo = nodeId;
			lnfg->V0[node_no_cl]->nodeNo = nodeId;
			//增加节点的文本信息
			//m_LNFGNodeInfo=lnfg->addNodeInfo(m_LNFGNodeInfo,lnfg->CL[node_no_cl]);

			if (lnfg->CL[node_no_cl]->node->type == EMPTY_EXP && lnfg->CL[node_no_cl]->m_isTrueEmpty == true)//多考虑一个terminal
			{
				//加根节点的画图代码

				//	nodeId++;
				if (m_terminalDraw == true)
				{

				}
				else
				{
					//增加终止节点
					m_emptyDraw = true;
					m_emptyId = lnfg->CL[node_no_cl]->nodeNo;
					m_terminalId = nodeId;
					m_terminalDraw = true;
					//增加终止节点的画图信息

					nodeId++;
				}
				edgeId++;
			}
			else//正常情况下
			{
				// 				//添加标记部分的画图代码

				lnfg->GetLabelOfNode(lnfg->CL[node_no_cl], &lnfg->CL[node_no_cl]->labelSet);
				//加根节点的画图代码
				//	this->addStartNodeCodeInfo(lnfg->CL[node_no_cl]->nodeNo);
				NodeToExtend.push(lnfg->CL[node_no_cl]);//加入待扩展节点队列
				nodeId++;
			}

		}
		//逐个画出各个节点的扩展节点
		while (!NodeToExtend.empty())
		{
			LNFGNode *CurExtendNode = NodeToExtend.front();
			NodeToExtend.pop();
			int edge_no = find_edge_by_point(lnfg->EL, CurExtendNode);
			//update curPoint
			while (edge_no != -1)//加入每一个出边及对应终结点
			{
				//处理以EPISILON结束的边
				if (lnfg->EL[edge_no]->m_endTrueEMPTY == false && lnfg->EL[edge_no]->end->type == EMPTY_EXP)//terminal
				{
					lnfg->EL[edge_no]->alreadyDraw = true;
					if (m_terminalDraw == true)
					{
						lnfg->EL[edge_no]->edgeNo = edgeId;
						lnfg->EL[edge_no]->alreadyDraw = true;

						//为边增加起始节点和终止节点的编号
						lnfg->EL[edge_no]->startNo = CurExtendNode->nodeNo;
						lnfg->EL[edge_no]->endNo = m_terminalId;
						edgeId++;
					}
					else
					{
						//加terminal点
						m_terminalDraw = true;
						m_terminalId = nodeId;

						lnfg->EL[edge_no]->edgeNo = edgeId;
						lnfg->EL[edge_no]->alreadyDraw = true;

						//为边增加起始节点和终止节点的编号
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
						//为边增加起始节点和终止节点的编号
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
						//为边增加起始节点和终止节点的编号
						lnfg->EL[edge_no]->startNo = CurExtendNode->nodeNo;
						lnfg->EL[edge_no]->endNo = nodeId;

						edgeId++;
						nodeId++;
						//加terminal点
						if (m_terminalDraw == true)
						{

							edgeId++;
						}
						else
						{
							//加terminal点
							m_terminalDraw = true;
							m_terminalId = nodeId;

							edgeId++;
							nodeId++;
						}
					}
				}
				else//普通边
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
							//增加边的画图信息
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
							//增加边的画图信息

							edgeEndId = lnfg->CL[node_no]->nodeNo;

						}

						//为边增加起始节点和终止节点的编号
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
		//**************增加false处理********************//ZXM ADD 2014.02.10
		//	UnsatisfyExplain+="公式不可满足:\r\n化简结果为false\r\n";
		lnfg->satisfied = false;
	}
	if (!lnfg->CL.empty())
	{
		//empty节点编号
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

void GetLabelOfNode(LNFGNode* ln, int_set* label, LNFG *lnfg)//得到节点ln所属的标记集合的标号集
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
extern map<string, int> propertyIndexMap;//性质名字对应的下标
extern vector<int> start_propositionValue;
extern vector<bool> last_propositionValue1;
//extern vector<int> last_propositionIndex;//存储上一个状态对应到g_propositionValue的第几个下标
extern int last_propositionIndex[2];
extern CRITICAL_SECTION cs; // 定义临界区对象，如果程序是OOP的，可以定义为类non-static成员  
extern int lock;
//extern pthread_mutex_t mutex;
extern int $$state_num;
vector<bool> tmpAtomTruth;//记录每个状态所有原子命题的真假
int count1 = 1;
extern int size1;
bool getAtoProTruth(int stateIndex, int atomicPropertyIndex)
{

	int VecSize = g_propositionValue[atomicPropertyIndex].size() - 1;
	int low = 0;
	int mid;
	int result;
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
	bool emptyFlag;//此边指向empty节点
	bool moreFlag;//此边指向more节点
}SNodeToENode;

map< int, vector<SNodeToENode> >SNodeToENodeMap;
vector< vector<SNodeToENode> >SNodeToENodeVec;//将SNodeToENodeMap中的元素压入到SNodeToENodeVec中，以后访问的时候，通过下标就可以访问，不用每次都查找，节约时间
map< int, vector<int> >NodeReachToNodesMap;//存储从一个节点能够到达的所有节点，除了more节点和empty节点
vector< vector<int> >NodeReachToNodesVec;//将NodeReachToNodesMap中的元素压入到NodeReachToNodesVec中，以后访问的时候，通过下标就可以访问，不用每次都查找，节约时间

typedef struct
{
	int InitialNodeNum;//因为分成了多线程，此变量记录到达该节点初始节点的编号
	int NodeNum;
	int current_length;
}ToExtendNode;
int total_length;

void FreeMallocAddr(vector<bool* > NoCounterExampleNodeMap)//用于释放NoCounterExampleNodeMap动态申请的内存
{
	vector<bool* >::iterator NoCounterExampleNodeMapIter;
	for (NoCounterExampleNodeMapIter = NoCounterExampleNodeMap.begin(); NoCounterExampleNodeMapIter != NoCounterExampleNodeMap.end(); NoCounterExampleNodeMapIter++)
	{
		free(*NoCounterExampleNodeMapIter);
	}
}

vector <vector <int> > EveryThreadFinalNodes(THREADNUMBER);//记录每个线程运行完之后，所有终止节点的编号
vector <vector <int> > EveryThreadThroughPathStartNodes(THREADNUMBER);//记录每个线程中能走的通的路径的初始节点

int EachPath(ToExtendNode currentExtendNode, int current_length, int ThreadIndex);
int EachSeg(int current_length);//传入的参数是需要开始展开的步长

//
vector<map<int, set<int> > >EveryThreadThroughPathStartNodesToFinalNodesArrayFirst;//EveryThreadThroughPathStartNodesToFinalNodesArray第一个元素
map<int, set<int> >EveryThreadThroughPathStartNodesToFinalNodesArrayTmp;
vector<vector<int> >EveryThreadToEmptyOrMoreStartNodes(THREADNUMBER);//记录每个线程能够到达empty或者more节点的初始节点
vector<ToExtendNode> GlobalToExtendNodeVec;//存储全局的待扩展的节点

HANDLE threadProMultiPath[THREADNUMBER][MULTIPATHNUM];//将多个线程定义成数组
int threadProMultiPathIndex[THREADNUMBER];//代表当前创建到第几个线程


vector <vector<int> > edgeAtoProNum;//存储每条边上原子命题的编号
vector <vector<vector<bool> > > edgeAtoProTruth;//存储每条边上原子命题的真假

vector<ToExtendNode> ToExtendNodeVec2;
set<int> reachToNodes;//临时vector，记录起始节点
int totalNodeNum = 0;//记录性质的LNFG中一共有几个节点
bool stateNumOver[THREADNUMBER];//记录每个线程中是否验证的数目已经超过整个程序的状态数，如果是，则置为true
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
memset(NoCounterExampleNodeArray[i][j], 0, ALTERNATELYINTERVAL);//这里要注意，之前是total_length，现在改成total_length+1
}
}
return NoCounterExampleNodeArray;

}*/


extern int thisPathIsValid;
//int segWhileTime = 1;//add by yubin 2016-8-31,表示第几次并行的处理若干个segment，用于作为NoCounterExampleNodeArrayTotal的元素，这样就不用每次都将NoCounterExampleNodeArrayTotal进行memset
int pace = 1;
#define PACE 1
int poolSize = MULTIPATHNUM;
int preTime=0;
bool mark = 1;
int prePoolSize = 0;

vector< vector<string> > edgeAtoProName;//每条边上原子命题的名字
void GetEdgeAtomicPro(CTreeNode* property)
{
	CTreeNode* p = property;
	if (p != NULL)
	{
		if (p->type == IDENT_EXP && p->name_str[0] != 'l')
		{
			//cout<<"原子命题为:"<<p->name_str<<endl;
			/*if (propertyIndexMap.find(property->name_str) == propertyIndexMap.end())//表明此原子命题对应的序号尚未加入到propertyIndexMap中
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
			property->atomicPropertyIndex = -1;//如果是以l开头的话，将atomicPropertyIndex置为-1，这样在__Sat函数中，就只需判断atomicPropertyIndex是否为1就行了， 加快速度
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
	edgeAtoProNum.push_back(tmp1);//纯粹为了占位
	edgeAtoProTruth.push_back(tmp2);//纯粹为了占位
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
			if (propositionIndex == propertyIndexMap.end())//没找到
			{
				cout << "没有找到" << *iter1 << "，查找失败!" << endl;
				return;//如果没有找到，返回-1
			}
			tmp.push_back(propositionIndex->second);
			//tmp[i]=propositionIndex->second;
			//cout<<"i:"<<i<<"propositionIndex->second:"<<propositionIndex->second<<endl;
			//i++;
		}
		edgeAtoProNum.push_back(tmp);
	}

}

map< int, vector<int> >SNodeToENodeMapForBFS;//此变量只在下面查找所有可达节点时才用到
int visited[200] = { 0 };
void DFS(int v, vector<int> &tmpVec1)
{
	map< int, vector<int> >::iterator iter = SNodeToENodeMapForBFS.find(v);
	vector<int>::iterator iter1;
	for (iter1 = (*iter).second.begin(); iter1 != (*iter).second.end(); iter1++)
	{	//begin是第一个邻接顶点，若顶点没有邻接顶点，则返回
		if (!visited[(*iter1)])
		{
			visited[*iter1] = 1;
			tmpVec1.push_back(*iter1);
			DFS((*iter1), tmpVec1);; //对v的尚未访问的邻接顶点w调用DFS
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
			hasEmptyNode = (*iterNode)->nodeNo; //将empty节点的结点号赋给hasEmptyNode，否则hasEmptyNode还是-1
		}
		else if ((*iterNode)->node->type == TRUE_EXP)
		{
			hasMoreNode = (*iterNode)->nodeNo; //将true节点的结点号赋给hasMoreNode，否则hasMoreNode还是-1
		}
	}


	//add by yubin 2016-9-2,为了获得节点的所有可达节点
	if (!lnfg->EL.empty())  //将所有边对应的开始节点与直接到达的节点的关系保存在SNodeToENodeMapForBFS
	{
		for (iter = lnfg->EL.begin(); iter != lnfg->EL.end(); iter++)//边是按输入压入的，
		{
			//开始节点不能是true,结束节点不能是empty和more
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

				if (iter1 == SNodeToENodeMapForBFS.end())//如果没有找到,创建一个新的
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


	//将节点信息写入文件，每一行的第一个字符0表示普通节点 1表示初始节点
	if (!lnfg->EL.empty())
	{
		for (iter = lnfg->EL.begin(); iter != lnfg->EL.end(); iter++)//边是按输入压入的，
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
				//SNodeToENodeMap.insert(pair< int, vector<SNodeToENode> >((*iter)->endNo, tmpVec));//压入一个空栈，如果之前压过，insert就插不进去了
				
				//vector<int> tmpVec1;
				//NodeReachToNodesMap.insert(pair< int, vector<int> >((*iter)->endNo, tmpVec1));

			}
			else if ((*iter)->end->type == TRUE_EXP)//遇到true节点，把此节点的类型标为more节点
			{
				tmpEndNode.moreFlag = true;
				tmpEndNode.emptyFlag = false;
				//vector<SNodeToENode> tmpVec;
				//SNodeToENodeMap.insert(pair< int, vector<SNodeToENode> >((*iter)->endNo, tmpVec));//压入一个空栈，如果之前压过，insert就插不进去了
				//vector<int> tmpVec1;
				//NodeReachToNodesMap.insert(pair< int, vector<int> >((*iter)->endNo, tmpVec1));
			}
			if ((*iter)->start->type != TRUE_EXP)//从true节点出发的边不加入到SNodeToENodeMap中
			{
				//修改边的初始节点标号
				startNumber = (*iter)->startNo;
				if (hasEmptyNode != -1 && (*iter)->startNo > hasEmptyNode)
				{
					startNumber--;
				}
				if (hasMoreNode != -1 && (*iter)->startNo > hasMoreNode)
				{
					startNumber--;
				}

				//修改边的到达节点标号
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
				if (iter1 == SNodeToENodeMap.end())//如果没有找到,创建一个新的
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
				cout << "此边的初始节点为:" << (*iter)->startNo << ",为true，不加入到SNodeToENodeMap中!!!" << endl;
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