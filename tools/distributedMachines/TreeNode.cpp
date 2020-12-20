// TreeNode.cpp: implementation of the CTreeNode class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "TreeNode.h"
#include "string.h"
#include "Machine.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTreeNode::CTreeNode(NODETYPE ptype, string pstr, int istr, CTreeNode * s1, CTreeNode * s2, CTreeNode * s3)
{
	type = ptype;
	name_str = pstr;
	int_str = istr;
	child[0] = s1;
	child[1] = s2;
	child[2] = s3;
	atomicPropertyIndex = -1;
}
CTreeNode::CTreeNode(NODETYPE ptype, string pstr, int istr, CTreeNode * s1, CTreeNode * s2)
{
	type = ptype;
	name_str = pstr;
	int_str = istr;
	child[0] = s1;
	child[1] = s2;
	child[2] = NULL;
	atomicPropertyIndex = -1;
}
CTreeNode::CTreeNode(NODETYPE ptype, string pstr, int istr, CTreeNode * s1)
{
	type = ptype;
	name_str = pstr;
	int_str = istr;
	child[0] = s1;
	child[1] = NULL;
	child[2] = NULL;
	atomicPropertyIndex = -1;
}
CTreeNode::CTreeNode(NODETYPE ptype, string pstr, int istr)
{
	type = ptype;
	name_str = pstr;
	int_str = istr;
	child[0] = NULL;
	child[1] = NULL;
	child[2] = NULL;
	atomicPropertyIndex = -1;
}

CTreeNode::~CTreeNode()
{
	if (child[0] != NULL)
		delete child[0];

	if (child[1] != NULL)
		delete child[1];

	if (child[2] != NULL)
		delete child[2];

}

/*用来复制一个顶点*/
void CTreeNode::copy(CTreeNode *ptree)
{
	type = ptree->type;
	name_str = ptree->name_str;
	int_str = ptree->int_str;
}

/*单纯的copy一个顶点树结构*/
void CTreeNode::copy_tree1(CTreeNode *ptree)
{
	if (ptree != NULL)
	{
		if (ptree->child[0] != NULL)
		{
			child[0] = new CTreeNode(AND_STA, "", 0);
			child[0]->copy_tree1(ptree->child[0]);
		}
		else
		{
			child[0] = NULL;
		}
		if (ptree->child[1] != NULL)
		{
			child[1] = new CTreeNode(AND_STA, "", 0);
			child[1]->copy_tree1(ptree->child[1]);
		}
		else
		{
			child[1] = NULL;
		}
		if (ptree->child[2] != NULL)
		{
			child[2] = new CTreeNode(AND_STA, "", 0);
			child[2]->copy_tree1(ptree->child[2]);
		}
		else
		{
			child[2] = NULL;
		}
		copy(ptree);
	}
}


/*copy一个顶点树结构，先将原来的树结构删除*/
void CTreeNode::copy_tree(CTreeNode *ptree)
{
	CTreeNode *temp1;
	temp1 = new CTreeNode(AND_STA, "", 0);
	temp1->copy_tree1(ptree);

	if (this->child[0] != NULL)
	{
		delete this->child[0];
		this->child[0] = NULL;
	}

	if (this->child[1] != NULL)
	{
		delete this->child[1];
		this->child[1] = NULL;
	}

	if (this->child[2] != NULL)
	{
		delete this->child[2];
		this->child[2] = NULL;
	}

	this->copy_tree1(temp1);

	delete temp1;
	temp1 = NULL;

}

///////////////////////
/*为chop结点添加fin(li)*/
void CTreeNode::creat_fin(_int64 m)
{
	CTreeNode *temp01;
	temp01 = new CTreeNode(FIN_EXP, "", 0);
	temp01->child[0] = new CTreeNode(IDENT_EXP, "", 0);
	//CString name_num1;
	
	//name_num1.Format(_T("%I64d"), m);
	//USES_CONVERSION;
	//string name_num(W2A(name_num1));
	stringstream ss;
	string name_num;
	ss << m;
	ss >> name_num;
	temp01->child[0]->name_str = "l";
	temp01->child[0]->name_str += name_num;

	this->copy_tree(temp01);

	delete temp01;
	temp01 = NULL;
}

/*检查target是否是ptree的一部分，如：p是p&&q的一部分*/
int CTreeNode::POST_findintree1(CTreeNode * ptree, CTreeNode * target, NODETYPE ntype)
{
	if (target->compare(ptree->child[0]))
	{
		return 1;
	}
	else
		if (target->compare(ptree->child[1]))
		{
			return 1;
		}

	if (ptree->child[0] != NULL && ptree->child[0]->type == ntype)
	{
		if (POST_findintree1(ptree->child[0], target, ntype))
		{
			return 1;
		}
	}
	if (ptree->child[1] != NULL && ptree->child[1]->type == ntype)
	{
		if (POST_findintree1(ptree->child[1], target, ntype))
		{
			return 1;
		}
	}
	if (ptree->child[2] != NULL && ptree->child[2]->type == ntype)
	{
		if (POST_findintree1(ptree->child[2], target, ntype))
		{
			return 1;
		}
	}
	return 0;

}


//为了比较原结点取掉fin后是否相同而构造，与原来compare功能相同
bool CTreeNode::compare1(CTreeNode *ptree)
{
	CTreeNode *temp1, *temp2;
	//先将顶点中的fin(p)结构删除掉，再进行比较begin
	temp1 = new CTreeNode(AND_STA, "", 0);
	temp2 = new CTreeNode(AND_STA, "", 0);
	temp1->copy_tree(this);
	temp2->copy_tree(ptree);
	delete_fin(temp1);
	delete_fin(temp2);

	if (temp1->compare(temp2))
	{
		delete temp1;
		delete temp2;
		temp1 = NULL;
		temp2 = NULL;
		return 1;
	}
	else
	{
		delete temp1;
		delete temp2;
		temp1 = NULL;
		temp2 = NULL;

		return 0;
	}
}
//为了比较原结点取掉fin后是否相同而构造，与原来compare功能相同,用于构造ＬＮＦＧ的过程
bool CTreeNode::compare2(CTreeNode *ptree)
{
	CTreeNode *temp1, *temp2;
	//先将顶点中的fin(p)结构删除掉，再进行比较begin
	temp1 = new CTreeNode(AND_STA, "", 0);
	temp2 = new CTreeNode(AND_STA, "", 0);
	temp1->copy_tree(this);
	temp2->copy_tree(ptree);
	delete_fin2(temp1);
	delete_fin2(temp2);

	//*************************增加化简操作，对去除fin标记后进行化简*******************// zxm add 2014.02.14
	//  CNFMachine n;
	//   n.PRE(temp1);
	// n.PRE(temp2);


	if (temp1->compare(temp2))
	{
		delete temp1;
		delete temp2;
		temp1 = NULL;
		temp2 = NULL;
		return 1;
	}
	else
	{
		delete temp1;
		delete temp2;
		temp1 = NULL;
		temp2 = NULL;

		return 0;
	}
}
/*在delete_fin中调用，用来去掉根结点类型为CHOP的顶点中的fin*/
void CTreeNode::chop_delete_fin(CTreeNode * ptree)
{
	CTreeNode *temp1;
	//根节点类型为CHOP，不需判断直接默认ptree->type为CHOP_STA
	while (ptree->child[0] != NULL && ptree->child[0]->type == CHOP_STA)
	{
		temp1 = new CTreeNode(CHOP_STA, "", 0);
		temp1->child[0] = new CTreeNode(CHOP_STA, "", 0);
		temp1->child[1] = new CTreeNode(CHOP_STA, "", 0);
		temp1->child[0]->copy_tree(ptree->child[0]->child[1]);
		temp1->child[1]->copy_tree(ptree->child[1]);

		ptree->child[1]->copy_tree(temp1);
		ptree->child[0]->copy_tree(ptree->child[0]->child[0]);

		delete temp1;
	}
	if (ptree->child[0]->type == FIN_EXP)
	{
		temp1 = new CTreeNode(TRUE_EXP, "TRUE", 0);
		ptree->child[0]->copy_tree(temp1);
		delete temp1;
	}
	else if (ptree->child[0]->type == AND_STA)
	{
		while (ptree->child[0]->child[1] != NULL && ptree->child[0]->child[1]->type == AND_STA)
		{
			temp1 = new CTreeNode(AND_STA, "", 0);
			temp1->child[0] = new CTreeNode(AND_STA, "", 0);
			temp1->child[1] = new CTreeNode(AND_STA, "", 0);
			temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
			temp1->child[1]->copy_tree(ptree->child[0]->child[1]->child[0]);

			ptree->child[0]->child[1]->copy_tree(ptree->child[0]->child[1]->child[1]);
			ptree->child[0]->child[0]->copy_tree(temp1);

			delete temp1;
		}
		if (ptree->child[0]->child[1]->type == FIN_EXP)
			ptree->child[0]->copy_tree(ptree->child[0]->child[0]);
	}

}
//删除fin标记，我们假设输入的参数的主操作符是and或者是仅有一项析取项,如果变化之后需要递归
void CTreeNode::delete_fin(CTreeNode * ptree)
{
	CTreeNode *temp1;
	if (ptree->type == CHOP_STA)
		chop_delete_fin(ptree);
	else if (ptree->type == AND_STA)
	{
		while (ptree->child[1] != NULL && ptree->child[1]->type == AND_STA)
		{
			temp1 = new CTreeNode(AND_STA, "", 0);
			temp1->child[0] = new CTreeNode(AND_STA, "", 0);
			temp1->child[1] = new CTreeNode(AND_STA, "", 0);
			temp1->child[0]->copy_tree(ptree->child[0]);
			temp1->child[1]->copy_tree(ptree->child[1]->child[0]);

			ptree->child[1]->copy_tree(ptree->child[1]->child[1]);
			ptree->child[0]->copy_tree(temp1);

			delete temp1;
		}
		temp1 = new CTreeNode(AND_STA, "", 0);
		temp1 = ptree;
		while (temp1->type == AND_STA)
		{
			if (temp1->child[1]->type == CHOP_STA)
				chop_delete_fin(temp1->child[1]);
			temp1 = temp1->child[0];
		}
		if (temp1->type == CHOP_STA)
			chop_delete_fin(temp1);
		temp1 = NULL;

	}
}
//////////////////////////////////LXF add//////////////////////////////////////////////////
//删除fin标记，我们假设输入的参数的主操作符是and或者是仅有一项析取项,如果变化之后需要递归
void CTreeNode::delete_fin2(CTreeNode * ptree)
{
	bool changed = false;//决定delete_fin函数是否需要递归
	if (ptree->type != AND_STA)//仅一项则处理主操作符为chop的情况
	{
		if (ptree->type == CHOP_STA && ptree->child[0]->type == FIN_EXP&&ptree->child[0]->child[0]->name_str[0] == 'l')//fin;p
		{
			changed = true;
			//*****************修改fin;p=true;p********************//zxm modify 2014.02.15
			CTreeNode *temp;
			temp = new CTreeNode(TRUE_EXP, "TRUE", 0);
			ptree->child[0]->copy_tree(temp);
		}
		if (ptree->type == CHOP_STA && ptree->child[0]->type == AND_STA && ptree->child[0]->child[1]->type == FIN_EXP
			&& ptree->child[0]->child[1]->child[0]->name_str[0] == 'l')//p&&fin;q
		{
			changed = true;
			ptree->child[0]->copy_tree(ptree->child[0]->child[0]);
		}
		if (changed)
		{
			delete_fin2(ptree);
		}
	}
	else
	{
		CTreeNode *temp, *temp1;
		temp = ptree;
		temp1 = temp;
		adjust_right_child_and(temp);
		while (temp->type == AND_STA && temp->child[0]->type == AND_STA)
		{
			if (temp->child[1]->type == FIN_EXP && temp->child[1]->child[0]->name_str[0] == 'l')//fin(l1)
			{
				changed = true;
				temp->copy_tree(temp->child[0]);
				adjust_right_child_and(temp);
				continue;
			}
			if (temp->child[1]->type == IDENT_EXP && temp->child[1]->name_str[0] == 'l' && temp->child[1]->name_str[1] <= '9' && temp->child[1]->name_str[1] >= '1')//l1
			{
				changed = true;
				temp->copy_tree(temp->child[0]);
				adjust_right_child_and(temp);
				continue;
			}
			if (temp->child[1]->type == CHOP_STA && temp->child[1]->child[0]->type == FIN_EXP
				&& temp->child[1]->child[0]->child[0]->name_str[0] == 'l')//fin;p
			{
				changed = true;
				//*****************修改fin;p=true;p********************//zxm modify 2014.02.15
				CTreeNode *temp3;
				temp3 = new CTreeNode(TRUE_EXP, "TRUE", 0);
				temp->child[1]->child[0]->copy_tree(temp3);
				//	temp->child[1]->copy_tree(temp->child[1]->child[1]);//?????????????????
			}
			if (temp->child[1]->type == CHOP_STA && temp->child[1]->child[0]->type == AND_STA //p&&fin;q
				&& temp->child[1]->child[0]->child[1]->type == FIN_EXP &&
				temp->child[1]->child[0]->child[1]->child[0]->name_str[0] == 'l')
			{
				changed = true;
				temp->child[1]->child[0]->copy_tree(temp->child[1]->child[0]->child[0]);
			}
			temp1 = temp;
			temp = temp->child[0];
			adjust_right_child_and(temp);
		}
		if (temp->type == AND_STA && temp->child[0]->type != AND_STA)
		{
			if (temp->child[1]->type == IDENT_EXP && temp->child[1]->name_str[0] == 'l'&& temp->child[1]->name_str[1] <= '9' && temp->child[1]->name_str[1] >= '1')//lk
			{
				//这种情况下，temp的结构遭到了破坏，不能再按预订的期望访问temp->child[0]
				temp->copy_tree(temp->child[0]);
				//temp直接变成了仅一项合取的形式
				if (temp->type == IDENT_EXP && temp->name_str[0] == 'l'&& temp->name_str[1] <= '9' && temp->name_str[1] >= '1')
				{
					temp1->copy_tree(temp1->child[1]);
					delete_fin2(temp1);
					return;
				}
				if (temp->type == FIN_EXP && temp->child[0]->name_str[0] == 'l')
				{
					temp1->copy_tree(temp1->child[1]);
					delete_fin2(temp1);
					return;
				}
				if (temp->type == CHOP_STA && temp->child[0]->type == FIN_EXP&&temp->child[0]->child[0]->name_str[0] == 'l')//fin;p
				{
					//*****************修改fin;p=true;p********************//zxm modify 2014.02.15
					CTreeNode *temp3;
					temp3 = new CTreeNode(TRUE_EXP, "TRUE", 0);
					temp->child[0]->copy_tree(temp3);
					//	temp->copy_tree(temp->child[1]);	
				}
				if (temp->type == CHOP_STA && temp->child[0]->type == AND_STA && temp->child[0]->child[1]->type == FIN_EXP
					&& temp->child[0]->child[1]->child[0]->name_str[0] == 'l')//p&&fin;q
				{
					temp->child[0]->copy_tree(temp->child[0]->child[1]);
				}
				delete_fin2(ptree);
				return;
			}
			if (temp->child[1]->type == FIN_EXP && temp->child[1]->child[0]->name_str[0] == 'l')//fin(l1)
			{
				//这种情况下，temp的结构遭到了破坏，不能再按预订的期望访问temp->child[0]
				temp->copy_tree(temp->child[0]);
				//temp直接变成了仅一项合取的形式
				if (temp->type == IDENT_EXP && temp->name_str[0] == 'l'&& temp->name_str[1] <= '9' && temp->name_str[1] >= '1')
				{
					temp1->copy_tree(temp1->child[1]);
					delete_fin2(temp1);
					return;
				}
				if (temp->type == FIN_EXP && temp->child[0]->name_str[0] == 'l')
				{
					temp1->copy_tree(temp1->child[1]);
					delete_fin2(temp1);
					return;
				}
				if (temp->type == CHOP_STA && temp->child[0]->type == FIN_EXP&&temp->child[0]->child[0]->name_str[0] == 'l')//fin;p
				{
					//*****************修改fin;p=true;p********************//zxm modify 2014.02.15
					CTreeNode *temp3;
					temp3 = new CTreeNode(TRUE_EXP, "TRUE", 0);
					temp->child[0]->copy_tree(temp3);
					//temp->copy_tree(temp->child[1]);	
				}
				if (temp->type == CHOP_STA && temp->child[0]->type == AND_STA && temp->child[0]->child[1]->type == FIN_EXP
					&& temp->child[0]->child[1]->child[0]->name_str[0] == 'l')//p&&fin;q
				{
					temp->child[0]->copy_tree(temp->child[0]->child[1]);
				}
				delete_fin2(ptree);
				return;
			}
			if (temp->child[1]->type == CHOP_STA && temp->child[1]->child[0]->type == FIN_EXP
				&& temp->child[1]->child[0]->child[0]->name_str[0] == 'l')//fin;p
			{
				//*****************修改fin;p=true;p********************//zxm modify 2014.02.15
				CTreeNode *temp3;
				temp3 = new CTreeNode(TRUE_EXP, "TRUE", 0);
				temp->child[1]->child[0]->copy_tree(temp3);
				//temp->child[1]->copy_tree(temp->child[1]->child[1]);
				delete_fin2(ptree);
			}
			if (temp->child[1]->type == CHOP_STA && temp->child[1]->child[0]->type == AND_STA //p&&fin;q
				&& temp->child[1]->child[0]->child[1]->type == FIN_EXP &&
				temp->child[1]->child[0]->child[1]->child[0]->name_str[0] == 'l')
			{
				temp->child[1]->child[0]->copy_tree(temp->child[1]->child[0]->child[0]);
				delete_fin2(ptree);
			}
			//左子树
			if (temp->child[0]->type == IDENT_EXP && temp->child[0]->name_str[0] == 'l'&& temp->child[0]->name_str[1] <= '9' && temp->child[0]->name_str[1] >= '1')//l1
			{
				temp->copy_tree(temp->child[1]);
				return;
			}
			if (temp->child[0]->type == FIN_EXP && temp->child[0]->child[0]->name_str[0] == 'l')//fin(l1)
			{
				temp->copy_tree(temp->child[1]);
				return;
			}
			if (temp->child[0]->type == CHOP_STA && temp->child[0]->child[0]->type == FIN_EXP
				&& temp->child[0]->child[0]->child[0]->name_str[0] == 'l')//fin;p
			{
				//*****************修改fin;p=true;p********************//zxm modify 2014.02.15
				CTreeNode *temp3;
				temp3 = new CTreeNode(TRUE_EXP, "TRUE", 0);
				temp->child[0]->child[0]->copy_tree(temp3);
				//	temp->child[0]->copy_tree(temp->child[0]->child[1]);
				delete_fin2(ptree);
			}
			if (temp->child[0]->type == CHOP_STA && temp->child[0]->child[0]->type == AND_STA //p&&fin;q
				&& temp->child[0]->child[0]->child[1]->type == FIN_EXP &&
				temp->child[0]->child[0]->child[1]->child[0]->name_str[0] == 'l')
			{
				temp->child[0]->child[0]->copy_tree(temp->child[0]->child[0]->child[0]);
				delete_fin2(ptree);
			}
		}
		if (changed)
		{
			delete_fin2(ptree);
		}
	}
}




/*比较语法树*/
bool CTreeNode::compare(CTreeNode *ptree)
{
	CTreeNode *temp1, *temp2;

	if (ptree == NULL)
		return 0;

	if (type != ptree->type)
		return 0;

	//	if (name_str!=ptree->name_str)
	//		return 0;

	// change to:
	if (type == IDENT_EXP && ptree->type == IDENT_EXP)
	{
		if (name_str != ptree->name_str)
			return 0;
	}


	if (int_str != ptree->int_str)
		return 0;

	///////////////////下面是新改成的部分//////////

	////////////////////////////////////////////
	if (child[0] == NULL)
	{
		if (ptree->child[0] != NULL)
		{
			return 0;
		}
	}
	else
	{
		if (ptree->child[0] == NULL)
			return 0;
	}


	if (child[1] == NULL)
	{
		if (ptree->child[1] != NULL)
		{
			return 0;
		}
	}
	else
	{
		if (ptree->child[1] == NULL)
			return 0;
	}

	if (child[2] == NULL)
	{
		if (ptree->child[2] != NULL)
		{
			return 0;
		}
	}
	else
	{
		if (ptree->child[2] == NULL)
			return 0;
	}

	if (child[0] != NULL && child[1] == NULL && child[2] == NULL)
	{
		if (!child[0]->compare(ptree->child[0]))
			return 0;
	}

	else
		if (child[0] != NULL && child[1] != NULL && child[2] == NULL)
		{

			if (type == AND_STA && ptree->type == AND_STA)
			{
				temp1 = new CTreeNode(AND_STA, "", 0);
				temp2 = new CTreeNode(AND_STA, "", 0);
				temp1->copy_tree(this);
				temp2->copy_tree(ptree);
				int same = 1;
				while (temp2->type == AND_STA && temp2->child[0] != NULL && temp2->child[0]->type == AND_STA)
				{
					if (!(POST_findintree1(this, temp2->child[1], AND_STA)))
					{
						same = 0;
						break;
					}
					temp2->copy_tree(temp2->child[0]);
				}
				if (temp2->type == AND_STA && temp2->child[0] != NULL && temp2->child[0]->type != AND_STA)
				{
					if (!(POST_findintree1(this, temp2->child[0], AND_STA)))
						same = 0;
					if (!(POST_findintree1(this, temp2->child[1], AND_STA)))
						same = 0;
				}
				delete temp2;

				while (temp1->type == AND_STA && temp1->child[0] != NULL && temp1->child[0]->type == AND_STA)
				{
					if (!(POST_findintree1(ptree, temp1->child[1], AND_STA)))
					{
						same = 0;
						break;
					}
					temp1->copy_tree(temp1->child[0]);
				}
				if (temp1->type == AND_STA && temp1->child[0] != NULL && temp1->child[0]->type != AND_STA)
				{
					if (!(POST_findintree1(ptree, temp1->child[0], AND_STA)))
						same = 0;
					if (!(POST_findintree1(ptree, temp1->child[1], AND_STA)))
						same = 0;
				}
				delete temp1;

				if (same == 1)
					return 1;
				else
					return 0;
			}

			else
				if (type == OR_STA && ptree->type == OR_STA)
				{
					temp1 = new CTreeNode(OR_STA, "", 0);
					temp2 = new CTreeNode(OR_STA, "", 0);
					temp1->copy_tree(this);
					temp2->copy_tree(ptree);
					int same = 1;
					while (temp2->type == OR_STA && temp2->child[0] != NULL && temp2->child[0]->type == OR_STA)
					{
						if (!(POST_findintree1(this, temp2->child[1], OR_STA)))
						{
							same = 0;
							break;
						}
						temp2->copy_tree(temp2->child[0]);
					}
					if (temp2->type == OR_STA && temp2->child[0] != NULL && temp2->child[0]->type != OR_STA)
					{
						if (!(POST_findintree1(this, temp2->child[0], OR_STA)))
							same = 0;
						if (!(POST_findintree1(this, temp2->child[1], OR_STA)))
							same = 0;
					}
					delete temp2;

					while (temp1->type == OR_STA && temp1->child[0] != NULL && temp1->child[0]->type == OR_STA)
					{
						if (!(POST_findintree1(ptree, temp1->child[1], OR_STA)))
						{
							same = 0;
							break;
						}
						temp1->copy_tree(temp1->child[0]);
					}
					if (temp1->type == OR_STA && temp1->child[0] != NULL && temp1->child[0]->type != OR_STA)
					{
						if (!(POST_findintree1(ptree, temp1->child[0], OR_STA)))
							same = 0;
						if (!(POST_findintree1(ptree, temp1->child[1], OR_STA)))
							same = 0;
					}
					delete temp1;
					if (same == 1)
						return 1;
					else
						return 0;
				}
				else
					if (!(child[0]->compare(ptree->child[0]) && child[1]->compare(ptree->child[1])))
						return 0;
		}

		else
			if (child[2] != NULL)
			{
				if (child[0] != NULL && ptree->child[0] != NULL)
				{
					if (!(child[0]->compare(ptree->child[0])))
						return 0;
				}
				if (child[1] != NULL && ptree->child[1] != NULL)
				{
					if (!(child[1]->compare(ptree->child[1])))
						return 0;
				}
				if (ptree->child[2] != NULL)
				{
					if (!(child[2]->compare(ptree->child[2])))
						return 0;
				}
			}

	return 1;
}




















