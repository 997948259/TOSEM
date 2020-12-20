// Machine.h: interface for the CNFMachine class.
//
//////////////////////////////////////////////////////////////////////

//#if !defined(AFX_MACHINE_H__156375C9_DE36_468F_8A59_BDEDE7D68AF3__INCLUDED_)
//#define AFX_MACHINE_H__156375C9_DE36_468F_8A59_BDEDE7D68AF3__INCLUDED_

#ifndef _MACHINE_H
#define _MACHINE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"

#include "TreeNode.h"


//
#include <list>
#include <set>
#include <algorithm>
#include <iterator>
using namespace std;
//#define MAX_VERTEX_NUM  50

//int a[MAX_VERTEX_NUM];
typedef set < int, less< int > >ims;
typedef set < CTreeNode* > node_set;
//
typedef set < _int64, less < _int64 > >ims64;
typedef set <string > s_set;
typedef set < s_set > s_set_set;
bool adjust_right_child_and(CTreeNode* ptree);
bool adjust_right_child_or(CTreeNode* ptree);
class CNFMachine
{
public:
	void PRE_until(CTreeNode* ptree);
	void untilReplace(CTreeNode* temp1, CTreeNode* ptree);
	void UNTIL(CTreeNode* ptree);
	void plus_tree(CTreeNode* ptree);
	void length(CTreeNode* ptree);
	void deleteAllEmptyInChop(CTreeNode* ptree);
	void handleChopstarRewritting(CTreeNode* ptree, CTreeNode* starTree);
	void chop_star_tree(CTreeNode* ptree);
	///////////////////////////////////
	void PRE_imply_equal(CTreeNode * ptree);//deal with imply and equal
	void PRE_not(CTreeNode * ptree);//deal with !
	void PRE_not_recur(CTreeNode * ptree);//deal with !
	void PRE_and(CTreeNode * ptree);//deal with &&
	void PRE_and_recur(CTreeNode * ptree);//deal with &&
	void PRE_or(CTreeNode * ptree);//deal with ||
	void PRE_or_shortcut(CTreeNode * ptree);//deal with || the shortcut
	void PRE_or_recur(CTreeNode * ptree);//deal with ||
	bool delete_p_and_q_of_p(CTreeNode * ptree);//(...||(p&&q)||...)||p---->delete p&&q
	bool delete_right_p_and_q_of_p(CTreeNode * ptree);//(...||(p)||...)||p&&q---->delete (p&&q)
	bool delete_p_in_p_and_q_of_not_p(CTreeNode * ptree);//(...||(p&&q)||...)||!p---->delete p
	bool delete_not_p_in_not_p_and_q_of_p(CTreeNode * ptree);//(...||(!p&&q)||...)||p---->delete !p
	bool delete_right_not_p_of_not_p_and_q(CTreeNode * ptree);//(...||(p)||...)||!p&&q---->delete !p  (...||(!p)||...)||p&&q---->delete p
	bool find_left_in_right_and_and(CTreeNode * ptree, CTreeNode * find);//p&&q||p&&r&&q 
	bool find_complement_element_in_and(CTreeNode* ptree, CTreeNode* find);//p&&q&&r    !p
	bool find_complement_element_in_or(CTreeNode* ptree, CTreeNode* find);//p||q||r    !p
	int delete_not_p_of_p(CTreeNode *ptree, CTreeNode *find);//!p&&q   ||p---->delete !p 
	bool find_complement_element_or_and(CTreeNode *ptree, CTreeNode *ptree1);//decide complementation relation of complex formula
	bool complement_relation(CTreeNode*, CTreeNode*);//decide complementation relation
	bool delete_not_p_and_q_of_and_and(CTreeNode * ptree);//(p&&q)||!(p&&q)&&r
	bool find_not_p_in_or_construct(CTreeNode * ptree, CTreeNode * find);//(...||(!p)||...)find !p return true


	void PRE_chop(CTreeNode * ptree);//deal with ;
	void PRE_chop_recur(CTreeNode * ptree);//deal with ;
	void PRE_prj(CTreeNode * ptree);//deal with prj
	void PRE_prj_recur(CTreeNode * ptree);//deal with prj
	void PRE_chopstar(CTreeNode * ptree);//deal with chopstar
	void PRE_chopstar_recur(CTreeNode * ptree);//deal with chopstar
	void PRE(CTreeNode * ptree);
	//add pre end
	///////////////////////////////////
	//DNF(),DNF_neg(),DNF_and():תΪ��ȡ��ʽ
	void DNF(CTreeNode * ptree);
	void DNF_neg(CTreeNode * ptree);
	void DNF_and(CTreeNode * ptree);
	////////////////////////////////////////
	//NF(),NFDNF():תΪNormalForm
	void NF(CTreeNode * ptree);
	void NFDNF(CTreeNode * ptree);
	///////////////////////////////////////
	//PRJ()��PRJ_chop():����Projection�ṹ
	void PRJ(CTreeNode * ptree);
	void PRJ_chop(CTreeNode * ptree);
	///////////////////////////////////////
	//CHOP(R):����Chop�ṹ
	void CHOP(CTreeNode * ptree);

	////////////////////////////////////////
	//NEG(),CONF(),CONF_nfalse(),CONF_or()
	//CONF_nor:���� ������ȫNF �ṹ
	void NEG(CTreeNode * ptree);
	void CONF(CTreeNode * ptree);
	void CONF_nfalse(CTreeNode * ptree);
	void CONF_or(CTreeNode * ptree1, CTreeNode * ptree2);
	void CONF_nor(CTreeNode * ptree1, CTreeNode * ptree2);
	////////////////////////////////////////
	//CONF_tree(),CONF_emptytree(),CONF_emptytree1(),
	//CONF_nexttree(),CONF_nexttree1():�����﷨��
	void CONF_tree(CTreeNode * ptree);
	void CONF_emptytree(CTreeNode * ptree);
	void CONF_emptytree1();
	void CONF_nexttree(CTreeNode * ptree);
	void CONF_nexttree1();
	//////////////////////////////////////////
	//AND():����AND�ṹ
	void AND(CTreeNode * ptree);
	///////////////////////////////////////
	void SF(CTreeNode * ptree);//SF(R):�ж��Ƿ�ΪState Formula
	void EmNea(CTreeNode * ptree); //�ж��Ƿ���empty����next���
	////////////////////////////////////
	//POST():������
	void POST(CTreeNode * ptree);  //�޸ĺ��ɶԶ���Ԥ�������߻�����ȡ��ʽ

	void COMB(CTreeNode * ptree);//����ʽ�е�empty�Լ�()������ͬ����Щ��ǰ���״̬��ʽ�ϲ�������next������ǰ����PRE
	void NNF(CTreeNode * ptree);//������ʹ�ã�ֻ������ԭ������ǰ��ǰ���ǹ�ʽ���Ѿ�û��->������
	///////////////
	s_set_set DNF_P(CTreeNode * ptree);//��ʽ����ȡ��ʽ������ֵ��һ��string���ϵļ���
	s_set_set CONJ(s_set_set set1, s_set_set set2);// ����ʽ��ʽΪP && Qʱ����DNF��Ҫ����CONJ
	void cons_tree(s_set_set temp, CTreeNode *aimtree);//�Ӽ���temp�������ṹ


	//�ж�target�Ƿ���ptree��һ���ӽṹ��һ���֣������磺p��p&&q��һ����
	int  POST_findintree(CTreeNode * ptree, CTreeNode * target, NODETYPE ntype);

	///show():��ʾNormalForm�Ľ��
	string show(CTreeNode * ptree);

	//add by yubin 2013-9-25,���ڽ����ϵ���Ϣ������ļ���
	string msvl_show(CTreeNode * ptree, int current_length);

	/////////////////////////////////////////////
	CNFMachine();
	virtual ~CNFMachine();
	string showout;
	string result;
	string strnc;
protected:
	CTreeNode * origin;
	CTreeNode * remain;
	CTreeNode * current;
	CTreeNode * nor;
	CTreeNode * emptytree;
	CTreeNode * nexttree;
	int SFA;
	int EMNEA;
	int Ema;
	int Nea;
	int andT;
	int markr;
	int visitline[50];
	int visitnum;
	int hitsall;

};

#endif // !defined(AFX_MACHINE_H__156375C9_DE36_468F_8A59_BDEDE7D68AF3__INCLUDED_)





















