/*author : 刘晓芳*/
#if !defined(__CONSLNFG_H__)
#define __CONSLNFG_H__

#include"Machine.h"
#include <VECTOR>
#include <iostream>
#include <sstream>
#include <stack>
class LNFGNode;
class LNFGEdge;
struct simpleNode;
typedef vector<int> int_set;//数字的集合
typedef vector<CTreeNode *> treenode_set;//CTreeNode节点集合的类型
typedef vector<LNFGNode *> LNFGNode_set;//LNFG节点集合的类型
typedef vector<LNFGEdge *> LNFGEdge_set;//LNFG边集合的类型
typedef vector<LNFGNode_set> LNFGNode_set_of_set;//LNFG节点集合的集合的类型
typedef vector<simpleNode*> simpleNode_set;//简化节点集合
typedef vector<simpleNode_set> simpleNode_set_set;

class LNFGNode//LNFG的节点类
{
public:
	bool m_isTrueEmpty;
	bool already_draw;
	int nodeNo;
	int_set labelSet;
	//data of a LNFG node
	CTreeNode* node;//所含的CTreeNode节点
	bool mark;//标记这个节点是否已经处理过
	int AddE;//标记是否含有terminal part
	int AddN;//标记是否含有nonterminal part
	treenode_set terminal;//存储terminal part
	treenode_set future;//存储nonterminal part

	//function
	LNFGNode();//构造函数
	LNFGNode(CTreeNode* node);//构造函数
	LNFGNode(const LNFGNode& ln);//拷贝构造
	~LNFGNode();//析构函数
	void setAddE();//分析这个节点并得到terminal part的数目AddE
	void setAddN();//分析这个节点并得到nonterminal part的数目AddN
	void markToTrue();//标记mark为true，即已经分析了这个节点
	void addTerminal(CTreeNode* ptree);//这个函数是setAddE中用到的子函数，作为增加terminalpart的数目并加入集合terminal中
	void addFuture(CTreeNode* ptree);//这个函数是setAddN中用到的子函数，作为增加nonterminalpart的数目并加入集合future中
	bool finEqual(LNFGNode* ln);//判断当前节点是否和ln节点final 等价

};


class LNFGEdge//LNFG的边类
{
public:
	bool m_endTrueEMPTY;
	bool alreadyDraw;
	int edgeNo;
	int startNo;
	int endNo;
	//data of a LNFG edge
	CTreeNode* start;//起始节点
	CTreeNode* end;//终止节点
	CTreeNode* edgeSpec;//状态公式

	//function
	LNFGEdge(CTreeNode * p, CTreeNode * r, CTreeNode* q);
	~LNFGEdge();
};
struct simpleNode
{
	int No;
	int_set labelSet;
	int inDegree;
	int outDegree;
	int DFN;
	int Low;
	bool partitioned;//是否已经划分到一个子图
	bool visited;//tanjan中是否访问过（入栈）
	simpleNode(){ inDegree = 0; outDegree = 0; visited = false; partitioned = false; }//zxm 增加初始化visited和partitioned
};
struct simpleEdge
{
	int start;
	int end;
};
struct simpleGarph
{
	vector<simpleNode*> nodeSet;
	vector<simpleEdge*> edgeSet;
};
class LNFG
{
public:
	bool labelSetIsEmpty();
	string DecisionExplainString;
	bool DecisionProcecdure();
	int nodeInStack(int topNode);
//	void showSimpleLoops();
	//	void dfsSubOneGraph(simpleGarph *graph);
	void partitionSimEdges();
	void tarjanOfSimGraph(simpleNode* node);
	//void showSimpleGraph(simpleGarph* simGraph);
	void deleteRelevantInEdge(int nodeNo);
	void deleteRelevantOutEdge(int nodeNo);
	int nodeNoToNode(int nodeNo, simpleGarph* graph);
	void calculateDegreeOfNodes();
	void deleteIrrelevantNodes();
	void getSimpleGraphOfLNFG();
	bool loopSearchInLNFG();
	void MergeEgdeOfSameLoc();
	void deleteSameNodeInV0(int index);
	void deleteSameNodeInL(int index);
	void deleteRelevantEdge(int index);
	int existIsolateNode();
	string addTerminalNodeInfo(string nodeInfo, int nodeId);
	string addTerminalEdgeInfo(string edgeInfo, int edgeId, int startId, int EndId);
	string addEdgeInfo(string edgeInfo, int edgeId, LNFGEdge* le, int startId, int endId);
	string addNodeInfo(string NodeInfo, LNFGNode* ln);
	void GetLabelOfNode(LNFGNode* ln, int_set* label);
	bool isTerminal(CTreeNode* ptree);//判断合取项是否含有明确终止项

	bool deletealoopInSimGraph(); ///删除图中的自环

	//void showLNFG();
	//data of a LNFG
	bool satisfied;
	LNFGNode* Node;
	LNFGNode_set V0;//初始节点的集合
	LNFGNode_set CL;//未标记点集
	bool cl_active;
	LNFGNode_set CL1;//标记一次点集
	bool cl1_active;
	LNFGEdge_set EL;//边集,
	int k;//标记值大小
	LNFGNode_set_of_set L;//标记集合
	vector<simpleGarph*> loopSet;//环路的集合
	stack<simpleNode*> tarjanStack;
	vector<simpleNode*> dfsStack;
	simpleGarph simGraphofLNFG;//简化图中查找环路
	vector<simpleGarph*> subSimGraphs;//图的强连通子图集合
	vector<simpleGarph*> satisfied_subsimGraphs;//可满足的强连通子图  zxm add 2014.7.1
	vector<simpleGarph*> not_satisfied_subsimGraphs;//不可满足的强连通子图  zxm add 2015-01-06
	string LoopString;
	//function
	LNFG();
	LNFG(CTreeNode* ptree);//默认必须含有参数
	~LNFG();
	void MergeCL();//将CL和CL1合并到CL中（while循环之后的部分）
	void construct();//构造LNFG函数
	void Add_fin_to_chop(LNFGNode* R, CTreeNode* ptree, int_set* nums);//给当前的ptree（主操作符必为chop）增加final标记,返回公式是否改变
	void Add_node_to_L(LNFGNode* R, int k);//根据k值将节点加入相应的L集合
	void loopOnce(int iter_no);//算法种的一次while循环
	int get_R_form_CL_or_CL1();//从CL并CL1中得到一个未被处理的节点
	bool EMPTY_in_CL();//判断EMPTY节点是否在CL中
	int existFinEqual(CTreeNode* ptree, LNFGNode_set set);//集合set中存在和ptree final等价的节点则返回true
	void handleAddE(LNFGNode* R, CTreeNode* ptree);//处理terminal part
	void handleAddN(LNFGNode* R, CTreeNode* ptree);//处理nonterminal part
	void deleteIsolateNode();//去掉单独的非EMPTY点
	void updateEL(LNFGNode* R_cp, LNFGNode* R);//重写fin之后，更新边的集合
	void rewriteFin(LNFGNode* R);//重写公式，增加final标记
	void rewriteEmptyChop(LNFGNode* R);//在求得范式之后，应该将EMPTY&&p;q的形式重写为p&&q
};
#endif