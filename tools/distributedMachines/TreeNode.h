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
	bool compare(CTreeNode * ptree);//�Ƚ��﷨��
	bool compare1(CTreeNode * ptree);//Ϊ�˱Ƚ�ԭ���ȥ��fin���Ƿ���ͬ�����죬��ԭ��compare������ͬ
	bool compare2(CTreeNode * ptree);//Ϊ�˱Ƚ�ԭ���ȥ��fin���Ƿ���ͬ�����죬��ԭ��compare������ͬ
	void delete_fin2(CTreeNode * ptree);//ȥ�������е�fin�ṹ
	void delete_fin(CTreeNode * ptree);//ȥ�������е�fin�ṹ
	void chop_delete_fin(CTreeNode * ptree);//��delete_fin�е��ã�����ȥ�����������ΪCHOP�Ķ����е�fin
	void copy(CTreeNode * ptree); //��������һ������
	void copy_tree(CTreeNode * ptree);  //copyһ���������ṹ���Ƚ�ԭ�������ṹɾ��
	//////////////
	void copy_tree1(CTreeNode * ptree);  //������copyһ���������ṹ
	///////////////
	int POST_findintree1(CTreeNode * ptree, CTreeNode * target, NODETYPE ntype); //���target�Ƿ���ptree��һ���֣��磺p��p&&q��һ����
	/*���漸���ǲ�ͬ���������Ĺ��캯��*/
	CTreeNode(NODETYPE ptype, string pstr, int istr, CTreeNode * s1, CTreeNode * s2, CTreeNode * s3);
	CTreeNode(NODETYPE ptype, string pstr, int istr, CTreeNode * s1, CTreeNode * s2);
	CTreeNode(NODETYPE ptype, string pstr, int istr, CTreeNode * s1);
	CTreeNode(NODETYPE ptype, string pstr, int istr);
	virtual ~CTreeNode();

	void creat_fin(_int64 m);//Ϊchop������fin(li)



	NODETYPE type;
	string  name_str;
	int		int_str;
	CTreeNode * child[3]; //ÿ����������������ӽڵ�
	int atomicPropertyIndex;//add by yubin for malloc 2016/5/12,����˽ڵ���ԭ�����⣬atomicPropertyIndex��¼propertyIndexMap�ж�Ӧ���±꣬������ÿ����֤��ʱ�򣬾Ͳ��ò�����

};

typedef CTreeNode * SyntaxTree;

#endif // !defined(_SYNTAXTREE_H_)
