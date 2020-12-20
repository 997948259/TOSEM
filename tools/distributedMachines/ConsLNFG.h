/*author : ������*/
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
typedef vector<int> int_set;//���ֵļ���
typedef vector<CTreeNode *> treenode_set;//CTreeNode�ڵ㼯�ϵ�����
typedef vector<LNFGNode *> LNFGNode_set;//LNFG�ڵ㼯�ϵ�����
typedef vector<LNFGEdge *> LNFGEdge_set;//LNFG�߼��ϵ�����
typedef vector<LNFGNode_set> LNFGNode_set_of_set;//LNFG�ڵ㼯�ϵļ��ϵ�����
typedef vector<simpleNode*> simpleNode_set;//�򻯽ڵ㼯��
typedef vector<simpleNode_set> simpleNode_set_set;

class LNFGNode//LNFG�Ľڵ���
{
public:
	bool m_isTrueEmpty;
	bool already_draw;
	int nodeNo;
	int_set labelSet;
	//data of a LNFG node
	CTreeNode* node;//������CTreeNode�ڵ�
	bool mark;//�������ڵ��Ƿ��Ѿ������
	int AddE;//����Ƿ���terminal part
	int AddN;//����Ƿ���nonterminal part
	treenode_set terminal;//�洢terminal part
	treenode_set future;//�洢nonterminal part

	//function
	LNFGNode();//���캯��
	LNFGNode(CTreeNode* node);//���캯��
	LNFGNode(const LNFGNode& ln);//��������
	~LNFGNode();//��������
	void setAddE();//��������ڵ㲢�õ�terminal part����ĿAddE
	void setAddN();//��������ڵ㲢�õ�nonterminal part����ĿAddN
	void markToTrue();//���markΪtrue�����Ѿ�����������ڵ�
	void addTerminal(CTreeNode* ptree);//���������setAddE���õ����Ӻ�������Ϊ����terminalpart����Ŀ�����뼯��terminal��
	void addFuture(CTreeNode* ptree);//���������setAddN���õ����Ӻ�������Ϊ����nonterminalpart����Ŀ�����뼯��future��
	bool finEqual(LNFGNode* ln);//�жϵ�ǰ�ڵ��Ƿ��ln�ڵ�final �ȼ�

};


class LNFGEdge//LNFG�ı���
{
public:
	bool m_endTrueEMPTY;
	bool alreadyDraw;
	int edgeNo;
	int startNo;
	int endNo;
	//data of a LNFG edge
	CTreeNode* start;//��ʼ�ڵ�
	CTreeNode* end;//��ֹ�ڵ�
	CTreeNode* edgeSpec;//״̬��ʽ

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
	bool partitioned;//�Ƿ��Ѿ����ֵ�һ����ͼ
	bool visited;//tanjan���Ƿ���ʹ�����ջ��
	simpleNode(){ inDegree = 0; outDegree = 0; visited = false; partitioned = false; }//zxm ���ӳ�ʼ��visited��partitioned
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
	bool isTerminal(CTreeNode* ptree);//�жϺ�ȡ���Ƿ�����ȷ��ֹ��

	bool deletealoopInSimGraph(); ///ɾ��ͼ�е��Ի�

	//void showLNFG();
	//data of a LNFG
	bool satisfied;
	LNFGNode* Node;
	LNFGNode_set V0;//��ʼ�ڵ�ļ���
	LNFGNode_set CL;//δ��ǵ㼯
	bool cl_active;
	LNFGNode_set CL1;//���һ�ε㼯
	bool cl1_active;
	LNFGEdge_set EL;//�߼�,
	int k;//���ֵ��С
	LNFGNode_set_of_set L;//��Ǽ���
	vector<simpleGarph*> loopSet;//��·�ļ���
	stack<simpleNode*> tarjanStack;
	vector<simpleNode*> dfsStack;
	simpleGarph simGraphofLNFG;//��ͼ�в��һ�·
	vector<simpleGarph*> subSimGraphs;//ͼ��ǿ��ͨ��ͼ����
	vector<simpleGarph*> satisfied_subsimGraphs;//�������ǿ��ͨ��ͼ  zxm add 2014.7.1
	vector<simpleGarph*> not_satisfied_subsimGraphs;//���������ǿ��ͨ��ͼ  zxm add 2015-01-06
	string LoopString;
	//function
	LNFG();
	LNFG(CTreeNode* ptree);//Ĭ�ϱ��뺬�в���
	~LNFG();
	void MergeCL();//��CL��CL1�ϲ���CL�У�whileѭ��֮��Ĳ��֣�
	void construct();//����LNFG����
	void Add_fin_to_chop(LNFGNode* R, CTreeNode* ptree, int_set* nums);//����ǰ��ptree������������Ϊchop������final���,���ع�ʽ�Ƿ�ı�
	void Add_node_to_L(LNFGNode* R, int k);//����kֵ���ڵ������Ӧ��L����
	void loopOnce(int iter_no);//�㷨�ֵ�һ��whileѭ��
	int get_R_form_CL_or_CL1();//��CL��CL1�еõ�һ��δ������Ľڵ�
	bool EMPTY_in_CL();//�ж�EMPTY�ڵ��Ƿ���CL��
	int existFinEqual(CTreeNode* ptree, LNFGNode_set set);//����set�д��ں�ptree final�ȼ۵Ľڵ��򷵻�true
	void handleAddE(LNFGNode* R, CTreeNode* ptree);//����terminal part
	void handleAddN(LNFGNode* R, CTreeNode* ptree);//����nonterminal part
	void deleteIsolateNode();//ȥ�������ķ�EMPTY��
	void updateEL(LNFGNode* R_cp, LNFGNode* R);//��дfin֮�󣬸��±ߵļ���
	void rewriteFin(LNFGNode* R);//��д��ʽ������final���
	void rewriteEmptyChop(LNFGNode* R);//����÷�ʽ֮��Ӧ�ý�EMPTY&&p;q����ʽ��дΪp&&q
};
#endif