// TreeNode.h: interface for the CTreeNode class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _SYNTAXTREE_H_
#define _SYNTAXTREE_H_
#include <string>

using namespace std;

enum NODETYPE
{
	IMPLY_STA,
	IFF_STA,
	AND_STA,
	OR_STA,
	NEGATION_STA,
	PROJECTION_STA,
	NEXT_STA,
	WNEXT_STA,
	ALWAYS_STA,
	STIME_STA,
	CHOP_STA,
	LEN_STA,
	UNTIL_STA,
	TRUE_EXP,
	FALSE_EXP,
	EMPTY_EXP,
	IDENT_EXP,
	INTEGER_EXP,
	MORE_EXP,
	SKIP_EXP,
	PLUS_STA,
	CHOPSTAR_STA,
	FIN_EXP

};

class CTreeNode
{
public:
	bool compare(CTreeNode * ptree);//比较语法树
	bool compare1(CTreeNode * ptree);//为了比较原结点去掉fin后是否相同而构造，与原来compare功能相同
	bool compare2(CTreeNode * ptree);//为了比较原结点去掉fin后是否相同而构造，与原来compare功能相同
	void delete_fin2(CTreeNode * ptree);//去掉顶点中的fin结构
	void delete_fin(CTreeNode * ptree);//去掉顶点中的fin结构
	void chop_delete_fin(CTreeNode * ptree);//在delete_fin中调用，用来去掉根结点类型为CHOP的顶点中的fin
	void copy(CTreeNode * ptree); //用来复制一个顶点
	void copy_tree(CTreeNode * ptree);  //copy一个顶点树结构，先将原来的树结构删除
	//////////////
	void copy_tree1(CTreeNode * ptree);  //单纯的copy一个顶点树结构
	///////////////
	int POST_findintree1(CTreeNode * ptree, CTreeNode * target, NODETYPE ntype); //检查target是否是ptree的一部分，如：p是p&&q的一部分
	/*下面几个是不同参数个数的构造函数*/
	CTreeNode(NODETYPE ptype, string pstr, int istr, CTreeNode * s1, CTreeNode * s2, CTreeNode * s3);
	CTreeNode(NODETYPE ptype, string pstr, int istr, CTreeNode * s1, CTreeNode * s2);
	CTreeNode(NODETYPE ptype, string pstr, int istr, CTreeNode * s1);
	CTreeNode(NODETYPE ptype, string pstr, int istr);
	virtual ~CTreeNode();

	void creat_fin(_int64 m);//为chop结点添加fin(li)



	NODETYPE type;
	string  name_str;
	int		int_str;
	CTreeNode * child[3]; //每个顶点最多有三个子节点
	int atomicPropertyIndex;//add by yubin for malloc 2016/5/12,如果此节点是原子命题，atomicPropertyIndex记录propertyIndexMap中对应的下标，这样，每次验证的时候，就不用查找了

};

typedef CTreeNode * SyntaxTree;

#endif // !defined(_SYNTAXTREE_H_)
