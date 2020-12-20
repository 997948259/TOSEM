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
	//DNF(),DNF_neg(),DNF_and():转为析取范式
	void DNF(CTreeNode * ptree);
	void DNF_neg(CTreeNode * ptree);
	void DNF_and(CTreeNode * ptree);
	////////////////////////////////////////
	//NF(),NFDNF():转为NormalForm
	void NF(CTreeNode * ptree);
	void NFDNF(CTreeNode * ptree);
	///////////////////////////////////////
	//PRJ()，PRJ_chop():处理Projection结构
	void PRJ(CTreeNode * ptree);
	void PRJ_chop(CTreeNode * ptree);
	///////////////////////////////////////
	//CHOP(R):处理Chop结构
	void CHOP(CTreeNode * ptree);

	////////////////////////////////////////
	//NEG(),CONF(),CONF_nfalse(),CONF_or()
	//CONF_nor:处理 ！、完全NF 结构
	void NEG(CTreeNode * ptree);
	void CONF(CTreeNode * ptree);
	void CONF_nfalse(CTreeNode * ptree);
	void CONF_or(CTreeNode * ptree1, CTreeNode * ptree2);
	void CONF_nor(CTreeNode * ptree1, CTreeNode * ptree2);
	////////////////////////////////////////
	//CONF_tree(),CONF_emptytree(),CONF_emptytree1(),
	//CONF_nexttree(),CONF_nexttree1():整理语法树
	void CONF_tree(CTreeNode * ptree);
	void CONF_emptytree(CTreeNode * ptree);
	void CONF_emptytree1();
	void CONF_nexttree(CTreeNode * ptree);
	void CONF_nexttree1();
	//////////////////////////////////////////
	//AND():处理AND结构
	void AND(CTreeNode * ptree);
	///////////////////////////////////////
	void SF(CTreeNode * ptree);//SF(R):判断是否为State Formula
	void EmNea(CTreeNode * ptree); //判断是否有empty结点和next结点
	////////////////////////////////////
	//POST():整理化简
	void POST(CTreeNode * ptree);  //修改后变成对顶点预处理，将边化成析取范式

	void COMB(CTreeNode * ptree);//将公式中的empty以及()后面相同的那些项前面的状态公式合并，并对next结点进行前处理PRE
	void NNF(CTreeNode * ptree);//处理！，使得！只出现在原子命题前，前提是公式中已经没有->操作符
	///////////////
	s_set_set DNF_P(CTreeNode * ptree);//求公式的析取范式，返回值是一个string集合的集合
	s_set_set CONJ(s_set_set set1, s_set_set set2);// 当公式形式为P && Q时，求DNF需要调用CONJ
	void cons_tree(s_set_set temp, CTreeNode *aimtree);//从集合temp构造树结构


	//判断target是否是ptree的一个子结构（一部分），例如：p是p&&q的一部分
	int  POST_findintree(CTreeNode * ptree, CTreeNode * target, NODETYPE ntype);

	///show():显示NormalForm的结果
	string show(CTreeNode * ptree);

	//add by yubin 2013-9-25,用于将边上的信息输出到文件中
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





















