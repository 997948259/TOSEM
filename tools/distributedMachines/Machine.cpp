// Machine.cpp: implementation of the CNFMachine class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "Machine.h"
#include <string.h>
#include <set>
#include <algorithm>
#include<iterator>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
extern SyntaxTree  g_syntaxTree;

bool is_state_formula(CTreeNode * ptree);
////////////////////////////////////////////////////lxf add////////////////////////////////////////////////////
void ptree_to_empty(CTreeNode *ptree)
{
	CTreeNode *temp1;
	temp1 = new CTreeNode(EMPTY_EXP, "EMPTY", 0);
	ptree->copy_tree(temp1);
	delete temp1;
	return;
}
////////////////////////////////////////////////////lxf add////////////////////////////////////////////////////
void ptree_to_false(CTreeNode *ptree)
{
	CTreeNode *temp1;
	temp1 = new CTreeNode(FALSE_EXP, "FALSE", 0);
	ptree->copy_tree(temp1);
	delete temp1;
	return;
}
////////////////////////////////////////////////////lxf add////////////////////////////////////////////////////
void ptree_to_true(CTreeNode * ptree)
{
	CTreeNode *temp1;
	temp1 = new CTreeNode(TRUE_EXP, "TRUE", 0);
	ptree->copy_tree(temp1);
	delete temp1;
	return;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CNFMachine::CNFMachine()
{
	current = NULL;
	remain = NULL;
	origin = NULL;
	showout = "";
	visitnum = 1;
	for (int i = 0; i<50; i++) visitline[i] = 0;
}

CNFMachine::~CNFMachine()
{

}

//返回该树对应的公式
string CNFMachine::show(CTreeNode *ptree)
{
	//showout="";
	if (ptree == NULL)
	{
		return showout;
	}

	switch (ptree->type)
	{
	case IDENT_EXP:
		showout += "(";
		showout += ptree->name_str.c_str();
		showout += ")";
		break;
	case TRUE_EXP:
		showout += ptree->name_str.c_str();
		break;
	case FALSE_EXP:
		showout += ptree->name_str.c_str();
		break;
	case EMPTY_EXP:
		showout += ptree->name_str.c_str();
		break;
	case SKIP_EXP:
		showout += ptree->name_str.c_str();
		break;
	case LEN_STA:
		showout += "len(";
		showout += ptree->child[0]->name_str.c_str();
		showout += ")";
		break;
	case OR_STA:
		if (ptree->child[0]->type == OR_STA)
		{
			show(ptree->child[0]);
		}
		else
		{
			if (ptree->child[0]->type == AND_STA || ptree->child[0]->type == CHOP_STA)
			{
				if (ptree->child[0]->type != OR_STA && ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
				{
					showout += "(";
				}
				show(ptree->child[0]);
				if (ptree->child[0]->type != OR_STA && ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
				{
					showout += ")";
				}
			}
			else
				show(ptree->child[0]);
		}

		showout += " || ";

		if (ptree->child[1]->type == OR_STA)
		{
			show(ptree->child[1]);
		}
		else
		{
			if (ptree->child[1]->type == AND_STA || ptree->child[1]->type == CHOP_STA)
			{
				if (ptree->child[1]->type != OR_STA && ptree->child[1]->type != IDENT_EXP && ptree->child[1]->type != TRUE_EXP && ptree->child[1]->type != FALSE_EXP && ptree->child[1]->type != EMPTY_EXP && ptree->child[1]->type != NEGATION_STA && ptree->child[1]->type != NEXT_STA && ptree->child[1]->type != STIME_STA && ptree->child[1]->type != ALWAYS_STA && ptree->child[1]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
				{
					showout += "(";
				}
				show(ptree->child[1]);
				if (ptree->child[1]->type != OR_STA && ptree->child[1]->type != IDENT_EXP && ptree->child[1]->type != TRUE_EXP && ptree->child[1]->type != FALSE_EXP && ptree->child[1]->type != EMPTY_EXP && ptree->child[1]->type != NEGATION_STA && ptree->child[1]->type != NEXT_STA && ptree->child[1]->type != STIME_STA && ptree->child[1]->type != ALWAYS_STA && ptree->child[1]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
				{
					showout += ")";
				}
			}
			else
				show(ptree->child[1]);
		}
		break;
	case AND_STA:
		if (ptree->child[0] == NULL && ptree->child[1] == NULL)
		{
			showout += "tau";
		}
		else
		{

			if (ptree->child[0]->type != AND_STA && ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
			{
				showout += "(";
			}
			show(ptree->child[0]);
			if (ptree->child[0]->type != AND_STA && ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
			{
				showout += ")";
			}
			showout += " && ";
			if (ptree->child[1]->type != AND_STA && ptree->child[1]->type != IDENT_EXP && ptree->child[1]->type != TRUE_EXP && ptree->child[1]->type != FALSE_EXP && ptree->child[1]->type != EMPTY_EXP && ptree->child[1]->type != NEGATION_STA && ptree->child[1]->type != NEXT_STA && ptree->child[1]->type != STIME_STA && ptree->child[1]->type != ALWAYS_STA && ptree->child[1]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
			{
				showout += "(";
			}
			show(ptree->child[1]);
			if (ptree->child[1]->type != AND_STA && ptree->child[1]->type != IDENT_EXP && ptree->child[1]->type != TRUE_EXP && ptree->child[1]->type != FALSE_EXP && ptree->child[1]->type != EMPTY_EXP && ptree->child[1]->type != NEGATION_STA && ptree->child[1]->type != NEXT_STA && ptree->child[1]->type != STIME_STA && ptree->child[1]->type != ALWAYS_STA && ptree->child[1]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
			{
				showout += ")";
			}
		}
		break;
	case NEGATION_STA:
		showout += "!";
		if (ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += "(";
		}
		show(ptree->child[0]);
		if (ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += ")";
		}
		break;
	case NEXT_STA:
		showout += "()";
		if (ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += "(";
		}
		show(ptree->child[0]);
		if (ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += ")";
		}
		break;
	case WNEXT_STA:
		showout += "(.)";
		if (ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += "(";
		}
		show(ptree->child[0]);
		if (ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += ")";
		}
		break;
	case STIME_STA:
		showout += "<>";
		if (ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += "(";
		}
		show(ptree->child[0]);
		if (ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += ")";
		}
		break;
	case ALWAYS_STA:
		showout += "[]";
		if (ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += "(";
		}
		show(ptree->child[0]);
		if (ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += ")";
		}
		break;
	case PROJECTION_STA:
		showout += "(";
		show(ptree->child[0]);
		origin = ptree;
		while (ptree->child[1] != NULL)
		{
			ptree = ptree->child[1];
			showout += ",";
			show(ptree->child[0]);
		}
		showout += ") prj ";
		if (origin->child[2]->type == TRUE_EXP || origin->child[2]->type == FALSE_EXP || origin->child[2]->type == EMPTY_EXP)
		{

			show(origin->child[2]);

		}
		else
		{
			showout += "(";
			show(origin->child[2]);
			showout += ")";
		}
		break;
	case CHOP_STA:
		if (ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += "(";
		}
		show(ptree->child[0]);
		if (ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += ")";
		}
		showout += " ; ";
		if (ptree->child[1]->type != IDENT_EXP && ptree->child[1]->type != TRUE_EXP && ptree->child[1]->type != FALSE_EXP && ptree->child[1]->type != EMPTY_EXP && ptree->child[1]->type != NEGATION_STA && ptree->child[1]->type != NEXT_STA && ptree->child[1]->type != STIME_STA && ptree->child[1]->type != ALWAYS_STA && ptree->child[1]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += "(";
		}
		show(ptree->child[1]);
		if (ptree->child[1]->type != IDENT_EXP && ptree->child[1]->type != TRUE_EXP && ptree->child[1]->type != FALSE_EXP && ptree->child[1]->type != EMPTY_EXP && ptree->child[1]->type != NEGATION_STA && ptree->child[1]->type != NEXT_STA && ptree->child[1]->type != STIME_STA && ptree->child[1]->type != ALWAYS_STA && ptree->child[1]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += ")";
		}
		break;
	case IMPLY_STA:
		if (ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += "(";
		}
		show(ptree->child[0]);
		if (ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += ")";
		}
		showout += " -> ";
		if (ptree->child[1]->type != IDENT_EXP && ptree->child[1]->type != TRUE_EXP && ptree->child[1]->type != FALSE_EXP && ptree->child[1]->type != EMPTY_EXP && ptree->child[1]->type != NEGATION_STA && ptree->child[1]->type != NEXT_STA && ptree->child[1]->type != STIME_STA && ptree->child[1]->type != ALWAYS_STA && ptree->child[1]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += "(";
		}
		show(ptree->child[1]);
		if (ptree->child[1]->type != IDENT_EXP && ptree->child[1]->type != TRUE_EXP && ptree->child[1]->type != FALSE_EXP && ptree->child[1]->type != EMPTY_EXP && ptree->child[1]->type != NEGATION_STA && ptree->child[1]->type != NEXT_STA && ptree->child[1]->type != STIME_STA && ptree->child[1]->type != ALWAYS_STA && ptree->child[1]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += ")";
		}
		break;
	case IFF_STA:
		if (ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += "(";
		}
		show(ptree->child[0]);
		if (ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += ")";
		}
		showout += " <-> ";
		if (ptree->child[1]->type != IDENT_EXP && ptree->child[1]->type != TRUE_EXP && ptree->child[1]->type != FALSE_EXP && ptree->child[1]->type != EMPTY_EXP && ptree->child[1]->type != NEGATION_STA && ptree->child[1]->type != NEXT_STA && ptree->child[1]->type != STIME_STA && ptree->child[1]->type != ALWAYS_STA && ptree->child[1]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += "(";
		}
		show(ptree->child[1]);
		if (ptree->child[1]->type != IDENT_EXP && ptree->child[1]->type != TRUE_EXP && ptree->child[1]->type != FALSE_EXP && ptree->child[1]->type != EMPTY_EXP && ptree->child[1]->type != NEGATION_STA && ptree->child[1]->type != NEXT_STA && ptree->child[1]->type != STIME_STA && ptree->child[1]->type != ALWAYS_STA && ptree->child[1]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += ")";
		}
		break;
	case UNTIL_STA:
		if (ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += "(";
		}
		show(ptree->child[0]);
		if (ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += ")";
		}
		showout += " U ";
		if (ptree->child[1]->type != IDENT_EXP && ptree->child[1]->type != TRUE_EXP && ptree->child[1]->type != FALSE_EXP && ptree->child[1]->type != EMPTY_EXP && ptree->child[1]->type != NEGATION_STA && ptree->child[1]->type != NEXT_STA && ptree->child[1]->type != STIME_STA && ptree->child[1]->type != ALWAYS_STA && ptree->child[1]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += "(";
		}
		show(ptree->child[1]);
		if (ptree->child[1]->type != IDENT_EXP && ptree->child[1]->type != TRUE_EXP && ptree->child[1]->type != FALSE_EXP && ptree->child[1]->type != EMPTY_EXP && ptree->child[1]->type != NEGATION_STA && ptree->child[1]->type != NEXT_STA && ptree->child[1]->type != STIME_STA && ptree->child[1]->type != ALWAYS_STA && ptree->child[1]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += ")";
		}
		break;
	case CHOPSTAR_STA:
		if (ptree->child[0] != NULL)
		{
			showout += "(";
			show(ptree->child[0]);
			showout += ")";
		}
		showout += "*";
		break;
	case PLUS_STA:
		if (ptree->child[0] != NULL)
		{
			showout += "(";
			show(ptree->child[0]);
			showout += ")";
		}
		showout += "+";
		break;
	case MORE_EXP:
		showout += ptree->name_str.c_str();
		break;
	case FIN_EXP:
		showout += "(";
		showout += "fin";
		if (ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += "(";
		}
		show(ptree->child[0]);
		if (ptree->child[0]->type != IDENT_EXP && ptree->child[0]->type != TRUE_EXP && ptree->child[0]->type != FALSE_EXP && ptree->child[0]->type != EMPTY_EXP && ptree->child[0]->type != NEGATION_STA && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != STIME_STA && ptree->child[0]->type != ALWAYS_STA && ptree->child[0]->type != PROJECTION_STA && ptree->child[0]->type != FIN_EXP)
		{
			showout += ")";
		}
		showout += ")";
		break;
	}
	return showout;
}

///////////////////////////////////////////////lxf add///////////////////////////////////////////////////////////
void CNFMachine::PRE_not(CTreeNode * ptree)//deal with !
{
	CTreeNode *temp1;
	if (ptree->child[0]->type == NEGATION_STA)//!!p
	{
		ptree->copy_tree(ptree->child[0]->child[0]);
		PRE(ptree);
		return;
	}
	else if (ptree->child[0]->type == TRUE_EXP)//!true
	{
		ptree_to_false(ptree);
		return;
	}
	else if (ptree->child[0]->type == FALSE_EXP)//!false
	{
		ptree_to_true(ptree);
		return;
	}
	else if (ptree->child[0]->type == EMPTY_EXP)//!empty
	{
		temp1 = new CTreeNode(NEXT_STA, "", 0);
		temp1->child[0] = new CTreeNode(TRUE_EXP, "TRUE", 0);
		ptree->copy_tree(temp1);
		delete temp1;
		return;
	}
	else if (ptree->child[0]->type == MORE_EXP)
	{
		ptree_to_empty(ptree);
		return;
	}
	else
	{
		PRE(ptree->child[0]);
		PRE_not_recur(ptree);
	}
}
///////////////////////////////////////////////lxf add///////////////////////////////////////////////////////////

void CNFMachine::PRE_not_recur(CTreeNode * ptree)//deal with !

{

	CTreeNode *temp1, *temp2, *temp3, *temp4;

	if (ptree->child[0] != NULL)


		if (ptree->child[0]->type == NEGATION_STA)//!!P

		{

			ptree->copy_tree(ptree->child[0]->child[0]);

			return;

		}

	//add pre begin

	//!true-->false

	if (ptree->child[0]->type == TRUE_EXP)

	{

		ptree_to_false(ptree);

		return;

	}


	//!false -->true

	else if (ptree->child[0]->type == FALSE_EXP)

	{

		ptree_to_true(ptree);

		return;

	}


	//!empty --> ()true

	else if (ptree->child[0]->type == EMPTY_EXP)

	{

		temp1 = new CTreeNode(NEXT_STA, "", 0);

		temp1->child[0] = new CTreeNode(TRUE_EXP, "TRUE", 0);

		ptree->copy_tree(temp1);

		delete temp1;

		return;

	}



	//!more-->empty

	else if (ptree->child[0]->type == MORE_EXP)

	{

		ptree_to_empty(ptree);

		return;

	}



	//add pre end



	//////// add /////////////

	else if (ptree->child[0]->type == ALWAYS_STA)

	{

		temp1 = new CTreeNode(NEGATION_STA, "NEGATION", 0);

		temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);

		temp1->child[0]->copy_tree(ptree->child[0]->child[0]);

		PRE_not(temp1);
		ptree->type = STIME_STA;

		ptree->child[0]->copy_tree(temp1);
		PRE(ptree);

		delete temp1;
		return;

	}

	else if (ptree->child[0]->type == STIME_STA)

	{

		temp1 = new CTreeNode(NEGATION_STA, "NEGATION", 0);

		temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);

		temp1->child[0]->copy_tree(ptree->child[0]->child[0]);

		//add 

		PRE_not(temp1);
		ptree->type = ALWAYS_STA;

		ptree->child[0]->copy_tree(temp1);
		PRE(ptree);

		delete temp1;

		//add pre delete

		return;

	}
	else if (ptree->child[0]->type == NEXT_STA)

	{

		temp1 = new CTreeNode(NEGATION_STA, "NEGATION", 0);

		temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);

		temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
		//PRE_not(temp1);
		temp2 = new CTreeNode(NEXT_STA, "", 0);
		temp2->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp2->child[0]->copy_tree(temp1);
		PRE(temp2);
		temp3 = new CTreeNode(EMPTY_EXP, "EMPTY", 0);
		temp4 = new CTreeNode(OR_STA, "OR", 0);
		temp4->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp4->child[0]->copy_tree(temp3);
		temp4->child[1] = new CTreeNode(AND_STA, "AND", 0);
		temp4->child[1]->copy_tree(temp2);

		//add 
		ptree->copy_tree(temp4);


		delete temp1;
		delete temp2;
		delete temp3;
		delete temp4;
		if (ptree->child[1]->type == MORE_EXP)
		{
			ptree_to_true(ptree);
		}
		if (ptree->child[1]->type == TRUE_EXP)
		{
			ptree_to_true(ptree);
		}
		if (ptree->child[1]->type == FALSE_EXP)
		{
			ptree->copy_tree(ptree->child[0]);
		}

		//add pre delete

		return;

	}
	else if (ptree->child[0]->type == AND_STA)
	{
		temp1 = new CTreeNode(NEGATION_STA, "NEGATION", 0);

		temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
		temp2 = new CTreeNode(NEGATION_STA, "NEGATION", 0);

		temp2->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp2->child[0]->copy_tree(ptree->child[0]->child[1]);
		temp4 = new CTreeNode(OR_STA, "OR", 0);
		temp4->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp4->child[0]->copy_tree(temp1);
		temp4->child[1] = new CTreeNode(AND_STA, "AND", 0);
		temp4->child[1]->copy_tree(temp2);
		ptree->copy_tree(temp4);
		PRE(ptree);
		delete temp1;
		delete temp2;
		delete temp4;

		return;
	}
	else if (ptree->child[0]->type == OR_STA)
	{
		temp1 = new CTreeNode(NEGATION_STA, "NEGATION", 0);

		temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
		temp2 = new CTreeNode(NEGATION_STA, "NEGATION", 0);

		temp2->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp2->child[0]->copy_tree(ptree->child[0]->child[1]);
		temp4 = new CTreeNode(AND_STA, "AND", 0);
		temp4->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp4->child[0]->copy_tree(temp1);
		temp4->child[1] = new CTreeNode(AND_STA, "AND", 0);
		temp4->child[1]->copy_tree(temp2);
		ptree->copy_tree(temp4);
		PRE(ptree);
		delete temp1;
		delete temp2;
		delete temp4;

		return;
	}

	else if (ptree->child[0]->type == CHOP_STA && ptree->child[0]->child[0]->type == TRUE_EXP)

	{

		temp1 = new CTreeNode(NEGATION_STA, "NEGATION", 0);

		temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);

		temp1->child[0]->copy_tree(ptree->child[0]->child[1]);

		temp2 = new CTreeNode(ALWAYS_STA, "ALWAYS", 0);

		temp2->child[0] = new CTreeNode(NEGATION_STA, "", 0);

		temp2->child[0]->copy_tree(temp1);

		//add

		PRE_not(temp2->child[0]);

		ptree->copy_tree(temp2);

		delete temp1;

		delete temp2;

		PRE(ptree);

		//add pre delete

		return;

	}
	else
		return;

}
////////////////////////////////////////////////////LXF add//////////////////////////////////////////////////
bool get_conflict(CTreeNode * p1, CTreeNode * pcom)
{
	bool b1 = false, b2 = false;
	if (p1 == NULL)
		return false;
	if (pcom == NULL)
		return false;
	if (pcom->type == NEGATION_STA && p1->compare(pcom->child[0]))//first compare the tree itself
		return true;
	if (pcom != NULL&&p1->type == NEGATION_STA && pcom->compare(p1->child[0]))
		return true;
	if (pcom->type == ALWAYS_STA && pcom->child[0]->type == STIME_STA &&
		p1->type == STIME_STA && p1->child[0]->type == ALWAYS_STA &&
		(pcom->child[0]->child[0]->type == NEGATION_STA && pcom->child[0]->child[0]->child[0]->compare(p1->child[0]->child[0])
		|| p1->child[0]->child[0]->type == NEGATION_STA && p1->child[0]->child[0]->child[0]->compare(pcom->child[0]->child[0])))//[]<>p and  <>[]!p
		return true;
	if (pcom->type == STIME_STA && pcom->child[0]->type == ALWAYS_STA &&
		p1->type == ALWAYS_STA && p1->child[0]->type == STIME_STA &&
		(pcom->child[0]->child[0]->type == NEGATION_STA && pcom->child[0]->child[0]->child[0]->compare(p1->child[0]->child[0])
		|| p1->child[0]->child[0]->type == NEGATION_STA && p1->child[0]->child[0]->child[0]->compare(pcom->child[0]->child[0])))//[]<>p  and  []<>p 
		return true;
	if (pcom != NULL&&p1->type == NEGATION_STA && pcom->compare(p1->child[0]))
		return true;
	if (pcom->type == AND_STA)
	{
		if (pcom->child[0] != NULL)
		{
			b1 = get_conflict(p1, pcom->child[0]);
		}
		if (pcom->child[1] != NULL)
		{
			b2 = get_conflict(p1, pcom->child[1]);
		}
	}
	return b1 || b2;
}
////////////////////////////////////////////////////LXF add//////////////////////////////////////////////////
bool get_conflict_all(CTreeNode * ptree)
{
	CTreeNode* temp1;
	if (ptree == NULL)
		return false;
	if (ptree->type != AND_STA)
		return false;

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

	if (get_conflict(ptree->child[1], ptree->child[0]))
	{
		return true;
	}
	else
		return get_conflict_all(ptree->child[0]);
}
////////////////////////////////////////////////////lxf add////////////////////////////////////////////////////
bool adjust_right_child_and(CTreeNode *ptree)//adjust the tree so that the right child is not or type
{
	bool changed = false;
	CTreeNode *temp1;
	while (ptree->child[1] != NULL && ptree->child[1]->type == AND_STA)

	{
		changed = true;

		temp1 = new CTreeNode(AND_STA, "", 0);

		temp1->child[0] = new CTreeNode(AND_STA, "", 0);

		temp1->child[1] = new CTreeNode(AND_STA, "", 0);

		temp1->child[0]->copy_tree(ptree->child[0]);

		temp1->child[1]->copy_tree(ptree->child[1]->child[0]);



		ptree->child[1]->copy_tree(ptree->child[1]->child[1]);

		ptree->child[0]->copy_tree(temp1);

		delete temp1;

	}
	return changed;
}
////////////////////////////////////////////////////lxf add////////////////////////////////////////////////////
bool false_condition_and(CTreeNode *ptree)
{
	if (ptree->child[0]->type == EMPTY_EXP && ptree->child[1]->type == MORE_EXP ||
		ptree->child[1]->type == EMPTY_EXP && ptree->child[0]->type == MORE_EXP ||
		ptree->child[0]->type == FALSE_EXP || ptree->child[1]->type == FALSE_EXP)
		return true;
	else
		return false;
}
////////////////////////////////////////////////////LXF add//////////////////////////////////////////////////

void CNFMachine::PRE_and(CTreeNode * ptree)//deal with &&

{
	adjust_right_child_and(ptree);
	if (get_conflict(ptree->child[1], ptree->child[0]) || false_condition_and(ptree))//separately compare with the left and right tree
	{
		ptree_to_false(ptree);
		return;
	}
	if (ptree->child[1]->type == TRUE_EXP)//p&&true
	{
		ptree->copy_tree(ptree->child[0]);
		PRE(ptree);
		return;
	}
	//added by LXF 2013/08/27 17:06:49 []<>!p  and  <>[]p    ---->   false
	if (ptree->child[0]->type == ALWAYS_STA && ptree->child[0]->child[0]->type == STIME_STA &&
		ptree->child[1]->type == STIME_STA && ptree->child[1]->child[0]->type == ALWAYS_STA &&
		complement_relation(ptree->child[0]->child[0]->child[0], ptree->child[1]->child[0]->child[0]))
	{
		ptree_to_false(ptree);
		return;
	}
	//added by LXF 2013/08/27 17:06:49   <>[]p  and  []<>!p    ---->   false
	if (ptree->child[1]->type == ALWAYS_STA && ptree->child[1]->child[0]->type == STIME_STA &&
		ptree->child[0]->type == STIME_STA && ptree->child[0]->child[0]->type == ALWAYS_STA &&
		complement_relation(ptree->child[0]->child[0]->child[0], ptree->child[1]->child[0]->child[0]))
	{
		ptree_to_false(ptree);
		return;
	}
	//***************p && []p =[]p*************//zxm add
	if (ptree->child[1]->type == ALWAYS_STA && ptree->child[1]->child[0]->compare(ptree->child[0]))
	{
		ptree->copy_tree(ptree->child[1]);
		PRE(ptree);
		return;
	}
	//***************[]p && p =[]p*************//zxm add
	if (ptree->child[0]->type == ALWAYS_STA && ptree->child[0]->child[0]->compare(ptree->child[1]))
	{
		ptree->copy_tree(ptree->child[0]);
		PRE(ptree);
		return;
	}
	//***************<>p and p = p************//zxm add
	if (ptree->child[0]->type == STIME_STA && ptree->child[0]->child[0]->compare(ptree->child[1]))
	{
		ptree->copy_tree(ptree->child[1]);
		PRE(ptree);
		return;
	}
	//***************p and <>p = p************//zxm add
	if (ptree->child[1]->type == STIME_STA && ptree->child[1]->child[0]->compare(ptree->child[0]))
	{
		ptree->copy_tree(ptree->child[0]);
		PRE(ptree);
		return;
	}
	if (ptree->child[0]->type == TRUE_EXP)//true&&p
	{
		ptree->copy_tree(ptree->child[1]);
		PRE(ptree);
		return;
	}
	if (ptree->child[0]->compare(ptree->child[1]))//p&&p

	{

		ptree->copy_tree(ptree->child[0]);
		PRE(ptree);

		return;

	}
	if (ptree->child[0]->type == EMPTY_EXP && ptree->child[1]->type == NEXT_STA || ptree->child[1]->type == EMPTY_EXP && 	ptree->child[0]->type == NEXT_STA)//empty && ()p=fasle;  ()p && empty=false

	{

		ptree_to_false(ptree);
		return;

	}

	PRE(ptree->child[0]);
	if (ptree->child[0]->type == FALSE_EXP)
	{
		ptree_to_false(ptree);
		return;
	}
	else if (ptree->child[0]->type == TRUE_EXP)
	{
		ptree->copy_tree(ptree->child[1]);
		PRE(ptree);
		return;
	}
	PRE(ptree->child[1]);
	if (ptree->child[1]->type == FALSE_EXP)
	{
		ptree_to_false(ptree);
		return;
	}
	else if (ptree->child[1]->type == TRUE_EXP)
	{
		ptree->copy_tree(ptree->child[0]);
		return;
	}
	PRE_and_recur(ptree);

}
////////////////////////////////////////////////////LXF add//////////////////////////////////////////////////
void eliminate_true(CTreeNode *ptree)
{
	if (ptree == NULL)
		return;
	if (ptree->type != AND_STA)
		return;
	if (ptree->child[0] != NULL && ptree->child[1] != NULL&&ptree->child[0]->type == TRUE_EXP)
	{
		ptree->copy_tree(ptree->child[1]);
		eliminate_true(ptree);
		return;
	}
	if (ptree->child[1] != NULL && ptree->child[0] != NULL&& ptree->child[1]->type == TRUE_EXP)
	{
		ptree->copy_tree(ptree->child[0]);
		eliminate_true(ptree);
		return;
	}
	else
	{
		eliminate_true(ptree->child[0]);
		eliminate_true(ptree->child[1]);
		return;
	}
}
////////////////////////////////////////////////////LXF add//////////////////////////////////////////////////
void and_distributive_right(CTreeNode * ptree)
{
	//(p||q)&&r----->(p&&r)||(q&&r)
	CTreeNode *temp1, *temp2, *temp3;
	temp1 = new CTreeNode(AND_STA, "AND", 0);
	temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
	temp1->child[1] = new CTreeNode(AND_STA, "AND", 0);
	temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
	temp1->child[1]->copy_tree(ptree->child[1]);
	temp2 = new CTreeNode(AND_STA, "AND", 0);
	temp2->child[0] = new CTreeNode(AND_STA, "AND", 0);
	temp2->child[1] = new CTreeNode(AND_STA, "AND", 0);
	temp2->child[0]->copy_tree(ptree->child[0]->child[1]);
	temp2->child[1]->copy_tree(ptree->child[1]);
	temp3 = new CTreeNode(OR_STA, "OR", 0);
	temp3->child[0] = new CTreeNode(AND_STA, "AND", 0);
	temp3->child[1] = new CTreeNode(AND_STA, "AND", 0);
	temp3->child[0]->copy_tree(temp1);
	temp3->child[1]->copy_tree(temp2);
	ptree->copy_tree(temp3);
	delete temp1;
	delete temp2;
	delete temp3;
}
////////////////////////////////////////////////////LXF add//////////////////////////////////////////////////
void and_distributive_left(CTreeNode *ptree)
{
	//r&&(p||q)
	CTreeNode *temp1, *temp2, *temp3;
	temp1 = new CTreeNode(AND_STA, "AND", 0);
	temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
	temp1->child[1] = new CTreeNode(AND_STA, "AND", 0);
	temp1->child[0]->copy_tree(ptree->child[0]);
	temp1->child[1]->copy_tree(ptree->child[1]->child[0]);
	temp2 = new CTreeNode(AND_STA, "AND", 0);
	temp2->child[0] = new CTreeNode(AND_STA, "AND", 0);
	temp2->child[1] = new CTreeNode(AND_STA, "AND", 0);
	temp2->child[0]->copy_tree(ptree->child[0]);
	temp2->child[1]->copy_tree(ptree->child[1]->child[1]);
	temp3 = new CTreeNode(OR_STA, "OR", 0);
	temp3->child[0] = new CTreeNode(AND_STA, "AND", 0);
	temp3->child[1] = new CTreeNode(AND_STA, "AND", 0);
	temp3->child[0]->copy_tree(temp1);
	temp3->child[1]->copy_tree(temp2);
	ptree->copy_tree(temp3);
	delete temp1;
	delete temp2;
	delete temp3;
}
//r&&(p||q)
////////////////////////////////////////////////////LXF add//////////////////////////////////////////////////
void merge_present_future(CTreeNode * ptree)
{
	CTreeNode *temp1, *temp2, *temp3;
	temp1 = new CTreeNode(AND_STA, "AND", 0);

	temp1->child[0] = new CTreeNode(AND_STA, "", 0);

	temp1->child[1] = new CTreeNode(AND_STA, "", 0);

	temp1->child[0]->copy_tree(ptree->child[0]->child[0]);

	temp1->child[1]->copy_tree(ptree->child[1]->child[0]);

	temp2 = new CTreeNode(AND_STA, "AND", 0);

	temp2->child[0] = new CTreeNode(AND_STA, "", 0);

	temp2->child[1] = new CTreeNode(AND_STA, "", 0);

	temp2->child[0]->copy_tree(ptree->child[0]->child[1]->child[0]);

	temp2->child[1]->copy_tree(ptree->child[1]->child[1]->child[0]);

	temp3 = new CTreeNode(NEXT_STA, "NEXT", 0);

	temp3->child[0] = new CTreeNode(AND_STA, "", 0);

	temp3->child[0]->copy_tree(temp2);

	ptree->child[0]->copy_tree(temp1);

	ptree->child[1]->copy_tree(temp3);

	delete temp1;

	delete temp2;

	delete temp3;
	return;
}
////////////////////////////////////////////////////LXF add//////////////////////////////////////////////////

void CNFMachine::PRE_and_recur(CTreeNode * ptree)//deal with &&

{



	if (adjust_right_child_and(ptree))
		PRE(ptree->child[0]);

	if (get_conflict(ptree->child[1], ptree) || false_condition_and(ptree))
	{
		ptree_to_false(ptree);
		return;
	}
	if (ptree->child[1]->type == TRUE_EXP)//p&&true
	{
		ptree->copy_tree(ptree->child[0]);
		PRE(ptree);
		return;
	}
	if (ptree->child[0]->type == TRUE_EXP)//true&&p
	{
		ptree->copy_tree(ptree->child[1]);
		PRE(ptree);
		return;
	}
	if (ptree->child[0]->compare(ptree->child[1]))//p&&p

	{

		ptree->copy_tree(ptree->child[0]);
		PRE(ptree);
		return;

	}
	if (ptree->child[0]->type == AND_STA && ptree->child[1]->type == AND_STA && ptree->child[0]->child[1]->type == NEXT_STA && ptree->child[1]->child[1]->type == NEXT_STA)//p&&Xq && r&&Xs-----> p&&r && X q&&s(previous code)
	{

		merge_present_future(ptree);

	}

	//暂时加上分配律
	if (ptree->child[0]->type == OR_STA)

	{

		and_distributive_right(ptree);
		PRE(ptree);
		return;

	}//if(ptree->child[0]->type==OR_STA)

	else if (ptree->child[1]->type == OR_STA)

	{
		and_distributive_left(ptree);
		PRE(ptree);
		return;

	}//if(ptree->child[1]->type==OR_STA)


	else if (ptree->child[0]->type == AND_STA)

	{

		if (POST_findintree(ptree->child[0], ptree->child[1], AND_STA))

		{

			ptree->copy_tree(ptree->child[0]);

			return;

		}

	}
	eliminate_true(ptree);
	if (get_conflict_all(ptree))
	{
		ptree_to_false(ptree);
		return;
	}

}
////////////////////////////////////////////////////LXF add//////////////////////////////////////////////////
bool get_conflict_or(CTreeNode * p1, CTreeNode * pcom)
{
	bool b1 = false, b2 = false;
	if (p1 == NULL)
		return false;
	if (pcom == NULL)
		return false;
	if (pcom->type == NEGATION_STA && p1->compare(pcom->child[0]))//first compare the tree itself
		return true;
	if (pcom != NULL&&p1->type == NEGATION_STA && pcom->compare(p1->child[0]))
		return true;
	if (pcom->type == ALWAYS_STA && pcom->child[0]->type == STIME_STA &&
		p1->type == STIME_STA && p1->child[0]->type == ALWAYS_STA &&
		(pcom->child[0]->child[0]->type == NEGATION_STA && pcom->child[0]->child[0]->child[0]->compare(p1->child[0]->child[0])
		|| p1->child[0]->child[0]->type == NEGATION_STA && p1->child[0]->child[0]->child[0]->compare(pcom->child[0]->child[0])))//[]<>p and  <>[]!p
		return true;
	if (pcom->type == STIME_STA && pcom->child[0]->type == ALWAYS_STA &&
		p1->type == ALWAYS_STA && p1->child[0]->type == STIME_STA &&
		(pcom->child[0]->child[0]->type == NEGATION_STA && pcom->child[0]->child[0]->child[0]->compare(p1->child[0]->child[0])
		|| p1->child[0]->child[0]->type == NEGATION_STA && p1->child[0]->child[0]->child[0]->compare(pcom->child[0]->child[0])))//[]<>p  and  []<>p 
		return true;
	if (pcom->type == OR_STA)
	{
		if (pcom->child[0] != NULL)
		{
			b1 = get_conflict_or(p1, pcom->child[0]);
		}
		if (pcom->child[1] != NULL)
		{
			b2 = get_conflict_or(p1, pcom->child[1]);
		}
	}
	return b1 || b2;
}
////////////////////////////////////////////////////LXF add//////////////////////////////////////////////////
bool get_conflict_or_all(CTreeNode *ptree)
{
	CTreeNode* temp1;
	if (ptree == NULL)
		return false;
	if (ptree->type == IDENT_EXP || ptree->type != OR_STA)
		return false;
	while (ptree->child[1] != NULL && ptree->child[1]->type == OR_STA&& ptree->type == OR_STA)

	{

		temp1 = new CTreeNode(OR_STA, "", 0);

		temp1->child[0] = new CTreeNode(OR_STA, "", 0);

		temp1->child[1] = new CTreeNode(OR_STA, "", 0);

		temp1->child[0]->copy_tree(ptree->child[0]);

		temp1->child[1]->copy_tree(ptree->child[1]->child[0]);

		ptree->child[1]->copy_tree(ptree->child[1]->child[1]);

		ptree->child[0]->copy_tree(temp1);



		delete temp1;

	}

	if (get_conflict_or(ptree->child[1], ptree->child[0]))
	{
		return true;
	}
	else
	{
		if (ptree->child[0]->type == OR_STA)
			return get_conflict_or(ptree->child[0]->child[1], ptree->child[0]->child[0]);
		else
			return false;
	}
}
////////////////////////////////////////////////////lxf add////////////////////////////////////////////////////
bool true_condition_or(CTreeNode *ptree)
{
	if (ptree->child[0]->type == TRUE_EXP ||
		ptree->child[1]->type == TRUE_EXP ||
		ptree->child[0]->type == NEGATION_STA && ptree->child[1]->type != NEGATION_STA&&ptree->child[0]->child[0]->compare(ptree->child[1]) ||
		ptree->child[1]->type == NEGATION_STA && ptree->child[0]->type != NEGATION_STA&&ptree->child[1]->child[0]->compare(ptree->child[0]) ||
		ptree->child[0]->type == EMPTY_EXP && ptree->child[1]->type == MORE_EXP ||
		ptree->child[1]->type == EMPTY_EXP && ptree->child[0]->type == MORE_EXP)
		return true;
	else
		return false;
}
////////////////////////////////////////////////////lxf add////////////////////////////////////////////////////
bool  adjust_right_child_or(CTreeNode *ptree)//adjust the tree so that the right child is not or type
{
	bool changed = false;
	CTreeNode *temp1;
	while (ptree->child[1] != NULL && ptree->child[1]->type == OR_STA)

	{
		changed = true;

		temp1 = new CTreeNode(OR_STA, "", 0);

		temp1->child[0] = new CTreeNode(OR_STA, "", 0);

		temp1->child[1] = new CTreeNode(OR_STA, "", 0);

		temp1->child[0]->copy_tree(ptree->child[0]);

		temp1->child[1]->copy_tree(ptree->child[1]->child[0]);

		ptree->child[1]->copy_tree(ptree->child[1]->child[1]);

		ptree->child[0]->copy_tree(temp1);

		delete temp1;

	}
	return changed;
}
////////////////////////////////////////////////////lxf add////////////////////////////////////////////////////
bool CNFMachine::find_complement_element_in_and(CTreeNode* ptree, CTreeNode* find)
{
	CTreeNode *temp1;
	temp1 = ptree;
	adjust_right_child_and(temp1);
	if (find->type == NEGATION_STA && POST_findintree(temp1, find->child[0], AND_STA))
	{
		return true;
	}
	while (temp1->type == AND_STA && temp1->child[0]->type == AND_STA)
	{
		if (temp1->child[1]->type == NEGATION_STA && temp1->child[1]->child[0]->compare(find))
			return true;
		temp1 = temp1->child[0];
		adjust_right_child_and(temp1);
	}
	if (temp1->type == AND_STA && temp1->child[0]->type != AND_STA)
	{
		if (temp1->child[1]->type == NEGATION_STA && temp1->child[1]->child[0]->compare(find))
			return true;
		if (temp1->child[0]->type == NEGATION_STA && temp1->child[0]->child[0]->compare(find))
			return true;
	}
	return false;
}
////////////////////////////////////////////////////lxf add////////////////////////////////////////////////////
bool CNFMachine::find_complement_element_in_or(CTreeNode* ptree, CTreeNode* find)
{
	CTreeNode *temp1;
	temp1 = ptree;
	adjust_right_child_or(temp1);
	if (find->type == NEGATION_STA && POST_findintree(temp1, find->child[0], OR_STA))
	{
		return true;
	}
	while (temp1->type == OR_STA && temp1->child[0]->type == OR_STA)
	{
		if (temp1->child[1]->type == NEGATION_STA && temp1->child[1]->child[0]->compare(find))
			return true;
		temp1 = temp1->child[0];
		adjust_right_child_and(temp1);
	}
	if (temp1->type == OR_STA && temp1->child[0]->type != OR_STA)
	{
		if (temp1->child[1]->type == NEGATION_STA && temp1->child[1]->child[0]->compare(find))
			return true;
		if (temp1->child[0]->type == NEGATION_STA && temp1->child[0]->child[0]->compare(find))
			return true;
	}
	return false;
}
////////////////////////////////////////////////////lxf add////////////////////////////////////////////////////
bool CNFMachine::find_complement_element_or_and(CTreeNode *ptree, CTreeNode *ptree1)
{
	CTreeNode *temp1;
	adjust_right_child_or(ptree);
	temp1 = ptree;
	bool res = true;
	while (temp1->type == OR_STA &&temp1->child[0]->type == OR_STA)
	{
		if (find_complement_element_in_and(ptree1, temp1->child[1]))//write a func
		{
			temp1 = temp1->child[0];
			adjust_right_child_or(temp1->child[0]);
		}
		else
		{
			res = false;
			return res;
		}
	}
	if (res == true && temp1->type == OR_STA &&temp1->child[0]->type != OR_STA)
	{
		if (find_complement_element_in_and(ptree1, temp1->child[1]) && find_complement_element_in_and(ptree1, temp1->child[0]))
		{
			;
		}
		else
			return false;
	}
	adjust_right_child_and(ptree1);
	temp1 = ptree1;
	while (temp1->type == AND_STA &&temp1->child[0]->type == AND_STA)
	{
		if (find_complement_element_in_or(ptree, temp1->child[1]))//write a func
		{
			temp1 = temp1->child[0];
			adjust_right_child_or(temp1->child[0]);
		}
		else
		{
			res = false;
			return res;
		}
	}
	if (res == true && temp1->type == AND_STA &&temp1->child[0]->type != AND_STA)
	{
		if (find_complement_element_in_or(ptree, temp1->child[1]) && find_complement_element_in_or(ptree, temp1->child[0]))
		{
			return true;
		}
		else
			return false;
	}
}
////////////////////////////////////////////////////lxf add////////////////////////////////////////////////////
bool CNFMachine::complement_relation(CTreeNode *ptree, CTreeNode *ptree1)
{
	if (ptree == NULL || ptree1 == NULL)
	{
		return false;
	}
	if (ptree->type == NEGATION_STA&&ptree->child[0]->compare(ptree1))
	{
		return true;
	}
	if (ptree1->type == NEGATION_STA&&ptree1->child[0]->compare(ptree))
	{
		return true;
	}
	if (ptree->type == OR_STA&&ptree1->type == AND_STA)
	{
		if (find_complement_element_or_and(ptree, ptree1))
		{
			return true;
		}
	}
	if (ptree1->type == OR_STA&&ptree->type == AND_STA)
	{
		if (find_complement_element_or_and(ptree1, ptree))
		{
			return true;
		}
	}
	return false;
}
////////////////////////////////////////////////////lxf add////////////////////////////////////////////////////
int delete_p_of_not_p(CTreeNode *ptree, CTreeNode *find)//p&&q   ||!p---->delete p 
{
	int res = 0;
	CTreeNode *temp1;
	adjust_right_child_and(ptree);
	temp1 = ptree;
	while (temp1->type == AND_STA && temp1->child[0]->type == AND_STA)
	{
		int i = 0;
		if (temp1->child[1]->compare(find))
		{
			i = 1;
			temp1->copy_tree(temp1->child[0]);
			res = 1;
		}
		if (temp1->child[0]->compare(find))
		{
			i = 1;
			temp1->copy_tree(temp1->child[1]);
			res = 1;
		}
		if (i == 0)
			temp1 = temp1->child[0];
		adjust_right_child_and(ptree);
	}
	if (temp1->type == AND_STA && temp1->child[0]->type != AND_STA)
	{
		if (find->compare(temp1->child[1]))
		{
			temp1->copy_tree(temp1->child[0]); res = 1;
		}
		if (find->compare(temp1->child[0]))
		{
			temp1->copy_tree(temp1->child[1]); res = 1;
		}
	}
	return res;
}
int CNFMachine::delete_not_p_of_p(CTreeNode *ptree, CTreeNode *find)//!p&&q   ||p---->delete !p 
{
	int res = 0;
	CTreeNode *temp1;
	adjust_right_child_and(ptree);
	temp1 = ptree;
	while (temp1->type == AND_STA && temp1->child[0]->type == AND_STA)
	{
		int i = 0;
		/*if(temp1->child[1]->type==NEGATION_STA && temp1->child[1]->child[0]->compare(find))
		{
		i=1;
		temp1->copy_tree(temp1->child[0]);
		res=1;
		}*/
		if (complement_relation(temp1->child[1], find))
		{
			i = 1;
			temp1->copy_tree(temp1->child[0]);
			res = 1;
		}
		if (i == 0)
			temp1 = temp1->child[0];
		adjust_right_child_and(ptree);
	}
	if (temp1->type == AND_STA && temp1->child[0]->type != AND_STA)
	{
		if (complement_relation(temp1->child[1], find))
		{
			temp1->copy_tree(temp1->child[0]); res = 1;
		}
		if (complement_relation(temp1->child[0], find))
		{
			temp1->copy_tree(temp1->child[1]); res = 1;
		}
	}
	return res;
}
////////////////////////////////////////////////////lxf add////////////////////////////////////////////////////
void CNFMachine::PRE_or_shortcut(CTreeNode * ptree)//deal with || the shortcut
{
	PRE(ptree->child[0]);
	if (ptree->child[0]->type == TRUE_EXP)
	{
		ptree_to_true(ptree);
		return;
	}
	else if (ptree->child[0]->type == FALSE_EXP)
	{
		ptree->copy_tree(ptree->child[1]);
		PRE(ptree);
		return;
	}
	PRE(ptree->child[1]);
	if (ptree->child[1]->type == TRUE_EXP)
	{
		ptree_to_true(ptree);
		return;
	}
	else if (ptree->child[1]->type == FALSE_EXP)
	{
		ptree->copy_tree(ptree->child[0]);
		PRE(ptree);
		return;
	}
	PRE_or_recur(ptree);
	return;
}
////////////////////////////////////////////////////lxf add////////////////////////////////////////////////////
bool CNFMachine::delete_p_and_q_of_p(CTreeNode * ptree)//(...||(p&&q)||...)||p---->delete p&&q
{
	CTreeNode *temp1;
	temp1 = ptree->child[0];
	bool res = false;
	while (temp1->type == OR_STA &&temp1->child[0]->type == OR_STA)
	{
		adjust_right_child_or(temp1);
		int i = 0;
		if (temp1->child[1]->type == AND_STA &&ptree->child[1]->type == AND_STA && find_left_in_right_and_and(temp1->child[1], ptree->child[1]))
		{
			res = true;
			i = 1;
			temp1->copy_tree(temp1->child[0]);
		}
		//*******************增加判断是否为null的语句*********************//zxm add 2014.02.12
		if (temp1->child[1] != NULL&&temp1->child[1]->type == AND_STA &&POST_findintree(temp1->child[1], ptree->child[1], AND_STA))//find p int the right child
		{
			res = true;
			i = 1;
			temp1->copy_tree(temp1->child[0]);
		}
		if (i == 0)
			temp1 = temp1->child[0];
	}
	if (temp1->type == OR_STA &&temp1->child[0]->type != OR_STA)
	{
		//*******************增加判断是否为null的语句*********************//zxm add 2014.02.12
		if (temp1->child[1]->type == AND_STA && POST_findintree(temp1->child[1], ptree->child[1], AND_STA))//find p int the right child
		{
			temp1->copy_tree(temp1->child[0]); res = true;
		}
		if (temp1->child[1] != NULL&&temp1->child[1]->type == AND_STA &&ptree->child[1]->type == AND_STA && find_left_in_right_and_and(temp1->child[1], ptree->child[1]))
		{
			res = true;
			temp1->copy_tree(temp1->child[0]);
		}
		if (temp1->child[0] != NULL&&temp1->child[0]->type == AND_STA && POST_findintree(temp1->child[0], ptree->child[1], AND_STA))//find p int the right child
		{
			temp1->copy_tree(temp1->child[1]); res = true;
		}
		if (temp1->child[0] != NULL&&temp1->child[0]->type == AND_STA &&ptree->child[1]->type == AND_STA && find_left_in_right_and_and(temp1->child[0], ptree->child[1]))
		{
			res = true;
			temp1->copy_tree(temp1->child[1]);
		}
	}
	return res;
}
////////////////////////////////////////////////////lxf add////////////////////////////////////////////////////
bool CNFMachine::delete_p_in_p_and_q_of_not_p(CTreeNode * ptree)//(...||(p&&q)||...)||!p---->delete p
{
	CTreeNode *temp1;
	temp1 = ptree->child[0];
	bool res = false;
	while (temp1->type == OR_STA &&temp1->child[0]->type == OR_STA)
	{
		adjust_right_child_or(temp1);
		int i = 0;
		if (temp1->child[1]->type == AND_STA)//find p int the right child
		{
			i = delete_p_of_not_p(temp1->child[1], ptree->child[1]->child[0]);
			if (i == 1)
				res = true;
		}
		if (i == 0)
			temp1 = temp1->child[0];
	}
	if (temp1->type == OR_STA &&temp1->child[0]->type != OR_STA)
	{
		int i = 0;
		if (temp1->child[1]->type == AND_STA)//find p int the right child
		{
			i = delete_p_of_not_p(temp1->child[1], ptree->child[1]->child[0]);
			if (i == 1)
				res = true;
		}
		if (temp1->child[0]->type == AND_STA)//find p int the right child
		{
			i = 0;
			i = delete_p_of_not_p(temp1->child[0], ptree->child[1]->child[0]);
			if (i == 1)
				res = true;
		}
	}
	return res;
}
////////////////////////////////////////////////////lxf add////////////////////////////////////////////////////
bool CNFMachine::delete_not_p_in_not_p_and_q_of_p(CTreeNode * ptree)//(...||(!p&&q)||...)||p---->delete !p
{
	CTreeNode *temp1;
	bool res = false;
	temp1 = ptree->child[0];
	while (temp1->type == OR_STA &&temp1->child[0]->type == OR_STA)
	{
		adjust_right_child_or(temp1);
		int i = 0;
		if (temp1->child[1]->type == AND_STA)//find p int the right child
		{
			i = delete_not_p_of_p(temp1->child[1], ptree->child[1]);
			if (i == 1)
				res = true;
		}
		if (i == 0)
			temp1 = temp1->child[0];
	}
	if (temp1->type == OR_STA &&temp1->child[0]->type != OR_STA)
	{
		int i = 0;
		if (temp1->child[1]->type == AND_STA)//find p int the right child
		{
			i = delete_not_p_of_p(temp1->child[1], ptree->child[1]);
			if (i == 1)
				res = true;
		}
		if (temp1->child[0]->type == AND_STA)//find p int the right child
		{
			i = 0;
			i = delete_not_p_of_p(temp1->child[0], ptree->child[1]);
			if (i == 1)
				res = true;
		}
	}
	return res;
}
////////////////////////////////////////////////////lxf add////////////////////////////////////////////////////
bool CNFMachine::delete_right_p_and_q_of_p(CTreeNode * ptree)//(...||(p)||...)||p&&q---->delete (p&&q)
{
	CTreeNode *temp1;
	bool res = false;
	temp1 = ptree->child[1];
	adjust_right_child_and(temp1);
	while (temp1->type == AND_STA && temp1->child[0]->type == AND_STA)
	{
		if (POST_findintree(ptree->child[0], temp1->child[1], OR_STA))
		{
			ptree->copy_tree(ptree->child[0]);
			res = true;
			return res;
		}
		if (POST_findintree(ptree->child[0], temp1->child[0], OR_STA))
		{
			ptree->copy_tree(ptree->child[0]);
			res = true;
			return res;
		}
		temp1 = temp1->child[0];
		adjust_right_child_and(temp1);
	}
	if (temp1->type == AND_STA && temp1->child[0]->type != AND_STA)
	{
		if (POST_findintree(ptree->child[0], temp1->child[1], OR_STA))
		{
			ptree->copy_tree(ptree->child[0]);
			res = true;
			return res;
		}
		if (POST_findintree(ptree->child[0], temp1->child[0], OR_STA))
		{
			ptree->copy_tree(ptree->child[0]);
			res = true;
			return res;
		}
	}
	//compare from the sight of left child
	temp1 = ptree->child[0];
	adjust_right_child_or(temp1);
	while (temp1->type == OR_STA && temp1->child[0]->type == OR_STA)
	{
		if (temp1->child[1]->type == AND_STA&&find_left_in_right_and_and(ptree->child[1], temp1->child[1]))
		{
			ptree->copy_tree(ptree->child[0]);
			res = true;
			return res;
		}
		temp1 = temp1->child[0];
		adjust_right_child_or(temp1);
	}
	if (temp1->type == OR_STA && temp1->child[0]->type != OR_STA)
	{
		if (temp1->child[1]->type == AND_STA&&find_left_in_right_and_and(ptree->child[1], temp1->child[1]))
		{
			ptree->copy_tree(ptree->child[0]);
			res = true;
			return res;
		}
		if (temp1->child[0]->type == AND_STA&&find_left_in_right_and_and(ptree->child[1], temp1->child[0]))
		{
			ptree->copy_tree(ptree->child[0]);
			res = true;
			return res;
		}
	}
	return res;
}
bool CNFMachine::find_not_p_in_or_construct(CTreeNode * ptree, CTreeNode * find)//(...||(!p)||...)find !p return true
{
	bool res = false;
	CTreeNode *temp1, *temp2;
	temp1 = ptree;
	adjust_right_child_or(temp1);
	while (temp1->type == OR_STA && temp1->child[0]->type == OR_STA)
	{
		if (complement_relation(temp1->child[1], find))
			return true;
		temp1 = temp1->child[0];
		adjust_right_child_or(temp1);
	}
	if (temp1->type == OR_STA && temp1->child[0]->type != OR_STA)
	{
		if (complement_relation(temp1->child[1], find))
		{
			return true;
		}
		if (complement_relation(temp1->child[1], find))
		{
			return true;
		}
	}
	if (find->type == AND_STA)
	{
		temp2 = new CTreeNode(NEGATION_STA, "NEGATION", 0);
		temp2->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp2->child[0]->copy_tree(find);
		PRE(temp2);
		if (POST_findintree(ptree, temp2, OR_STA))
		{
			res = true;
		}
		delete temp2;
	}
	return res;
}
////////////////////////////////////////////////////lxf add////////////////////////////////////////////////////
bool CNFMachine::delete_right_not_p_of_not_p_and_q(CTreeNode * ptree)//(...||(p)||...)||!p&&q---->delete !p  (...||(!p)||...)||p&&q---->delete p
{
	CTreeNode *temp1;
	bool res = false;
	temp1 = ptree->child[1];
	adjust_right_child_and(temp1);
	while (temp1->type == AND_STA && temp1->child[0]->type == AND_STA)
	{
		if (temp1->child[1]->type == NEGATION_STA && POST_findintree(ptree->child[0], temp1->child[1]->child[0], OR_STA))
		{
			temp1->copy_tree(temp1->child[0]);
			res = true;
			return res;
		}
		if (temp1->child[1]->type != NEGATION_STA && find_not_p_in_or_construct(ptree->child[0], temp1->child[1]))
		{
			temp1->copy_tree(temp1->child[0]);
			res = true;
			return res;
		}
		if (temp1->child[0]->type == NEGATION_STA &&find_not_p_in_or_construct(ptree->child[0], temp1->child[0]))
		{
			temp1->copy_tree(temp1->child[1]);
			res = true;
			return res;
		}
		temp1 = temp1->child[0];
		adjust_right_child_and(temp1);
	}
	if (temp1->type == AND_STA && temp1->child[0]->type != AND_STA)
	{
		if (temp1->child[1]->type == NEGATION_STA && POST_findintree(ptree->child[0], temp1->child[1]->child[0], OR_STA))
		{
			temp1->copy_tree(temp1->child[0]);
			res = true;
			return res;
		}
		if (temp1->child[1]->type != NEGATION_STA && find_not_p_in_or_construct(ptree->child[0], temp1->child[1]))
		{
			temp1->copy_tree(temp1->child[0]);
			res = true;
			return res;
		}
		if (temp1->child[0]->type == NEGATION_STA && POST_findintree(ptree->child[0], temp1->child[0]->child[0], OR_STA))
		{
			temp1->copy_tree(temp1->child[1]);
			res = true;
			return res;
		}
		if (temp1->child[0]->type != NEGATION_STA && find_not_p_in_or_construct(ptree->child[0], temp1->child[0]))
		{
			temp1->copy_tree(temp1->child[1]);
			res = true;
			return res;
		}
	}
	return res;
}

bool  CNFMachine::delete_not_p_and_q_of_and_and(CTreeNode * ptree)//(p&&q)||!(p&&q)&&r
{
	bool res = false;
	CTreeNode *temp1;
	temp1 = ptree->child[1];
	adjust_right_child_and(temp1);
	while (temp1->type == AND_STA && temp1->child[0]->type == AND_STA)
	{
		int i = 0;
		if (complement_relation(temp1->child[1], ptree->child[0]))
		{
			i = 1;
			temp1->copy_tree(temp1->child[0]);
			res = true;
		}
		if (i == 0)
			temp1 = temp1->child[0];
		adjust_right_child_and(temp1);
	}
	if (temp1->type == AND_STA && temp1->child[0]->type != AND_STA)
	{
		if (complement_relation(temp1->child[1], ptree->child[0]))
		{
			temp1->copy_tree(temp1->child[0]);
			res = true;
		}
		if (complement_relation(temp1->child[0], ptree->child[0]))
		{
			temp1->copy_tree(temp1->child[1]);
			res = true;
		}
	}
	return res;
}
////////////////////////////////////////////////////lxf add////////////////////////////////////////////////////
bool CNFMachine::find_left_in_right_and_and(CTreeNode * ptree, CTreeNode * find)//p&&q||p&&r&&q 
{
	CTreeNode *temp1;
	temp1 = find;
	bool res = true;
	while (temp1->type == AND_STA && temp1->child[0]->type == AND_STA)
	{
		if (POST_findintree(ptree, temp1->child[1], AND_STA))
		{
			temp1 = temp1->child[0];
			adjust_right_child_and(temp1);
			continue;
		}
		else
		{
			res = false; break;
		}
	}
	if (temp1->type == AND_STA && temp1->child[0]->type != AND_STA&&res == true)
	{
		if (POST_findintree(ptree, temp1->child[1], AND_STA) && POST_findintree(ptree, temp1->child[0], AND_STA))
		{
			return true;
		}
	}
	return false;
}
////////////////////////////////////////////////////lxf add////////////////////////////////////////////////////

void CNFMachine::PRE_or(CTreeNode * ptree)//deal with ||

{


	//adjust the tree so that the right child is not or type

	adjust_right_child_or(ptree);
	//get_conflict_or find if there is !right

	if (get_conflict_or_all(ptree) || true_condition_or(ptree))//true

	{

		ptree_to_true(ptree);
		return;

	}
	else if (ptree->child[1]->compare(ptree->child[0]))//p||p

	{

		ptree->copy_tree(ptree->child[0]);
		PRE(ptree);
		return;

	}
	// 	//added by LXF 2013/08/27 17:06:49 []<>!p  or  <>[]p    ---->   false
	// 	if (ptree->child[0]->type==ALWAYS_STA && ptree->child[0]->child[0]->type==STIME_STA &&
	// 		ptree->child[1]->type==STIME_STA && ptree->child[1]->child[0]->type==ALWAYS_STA &&
	// 		complement_relation(ptree->child[0]->child[0]->child[0],ptree->child[1]->child[0]->child[0]))
	// 	{
	// 		ptree_to_true(ptree);
	// 		return;
	// 	}
	// 	//added by LXF 2013/08/27 17:06:49   <>[]p  or  []<>!p    ---->   false
	// 	if (ptree->child[1]->type==ALWAYS_STA && ptree->child[1]->child[0]->type==STIME_STA &&
	// 		ptree->child[0]->type==STIME_STA && ptree->child[0]->child[0]->type==ALWAYS_STA &&
	// 		complement_relation(ptree->child[0]->child[0]->child[0],ptree->child[1]->child[0]->child[0]))
	// 	{
	// 		ptree_to_true(ptree);
	// 		return;
	// 	}
	else
	{
		if (ptree->child[0]->type == AND_STA)
		{
			//(1)left: and right:not and   
			if (ptree->child[1]->type != AND_STA)
			{
				//(p&&q)||p
				if (POST_findintree(ptree->child[0], ptree->child[1], AND_STA))
				{

					ptree->copy_tree(ptree->child[1]);
					PRE(ptree);
					return;
				}
				//(p&&q)||!p
				if (ptree->child[1]->type == NEGATION_STA && delete_p_of_not_p(ptree->child[0], ptree->child[1]->child[0]) == 1)
				{
					PRE(ptree);
				}
				//(!p&&q)||p
				if (ptree->child[1]->type != NEGATION_STA && delete_not_p_of_p(ptree->child[0], ptree->child[1]) == 1)
				{
					PRE(ptree);
				}
				//if not special ,need to reduce sub formulas
				PRE_or_shortcut(ptree);
				return;
			}
			//(2)left: and right: and   
			else// if(ptree->child[1]->type==AND_STA)
			{
				//p&&q||p&&q&&r
				if (POST_findintree(ptree->child[1], ptree->child[0], AND_STA))
				{

					ptree->copy_tree(ptree->child[0]);
					PRE(ptree);
					return;
				}
				//p&&q||p&&r&&q not near condition revized
				if (find_left_in_right_and_and(ptree->child[1], ptree->child[0]))
				{
					ptree->copy_tree(ptree->child[0]);
					PRE(ptree);
					return;
				}
				//(p&&q)||!(p&&q)&&r
				if (delete_not_p_and_q_of_and_and(ptree))
				{
					PRE(ptree);
					return;
				}
				//p&&q&&r||p&&q
				if (POST_findintree(ptree->child[0], ptree->child[1], AND_STA))
				{

					ptree->copy_tree(ptree->child[1]);
					PRE(ptree);
					return;
				}
				//p&&r&&q|| p&&q not near condition revized
				if (find_left_in_right_and_and(ptree->child[0], ptree->child[1]))
				{
					ptree->copy_tree(ptree->child[1]);
					PRE(ptree);
					return;
				}
				//!(p&&q)&&r||(p&&q)
				if (ptree->child[1]->type != NEGATION_STA && delete_not_p_of_p(ptree->child[0], ptree->child[1]) == 1)
				{
					PRE(ptree);
					return;
				}
				//if not special ,need to reduce sub formulas
				PRE_or_shortcut(ptree);
				return;
			}
		}
		else if (ptree->child[0]->type == OR_STA)
		{
			//(3)left: or right: not and   
			if (ptree->child[1]->type != AND_STA)
			{
				//(...||(p&&q)||...)||p---->delete p&&q
				if (delete_p_and_q_of_p(ptree))
				{
					PRE(ptree);
					return;
				}
				//(...||(p&&q)||...)||!p---->delete p
				if (ptree->child[1]->type == NEGATION_STA&&delete_p_in_p_and_q_of_not_p(ptree))
				{
					PRE(ptree);
					return;
				}
				//(...||(!p&&q)||...)||p---->delete !p  union these two condition    (...||(!p)||...)||p&&q---->delete p
				if (ptree->child[1]->type != NEGATION_STA&&delete_not_p_in_not_p_and_q_of_p(ptree))
				{
					PRE(ptree);
					return;
				}
				PRE_or_shortcut(ptree);
				return;
			}
			//(4)left: or right: and   
			else //if(ptree->child[1]->type==AND_STA)
			{
				//(...||(p&&q&&r)||...)||p&&q---->delete (p&&q&&r) not near condition revized
				if (delete_p_and_q_of_p(ptree))
				{
					PRE(ptree);
					return;
				}
				//(...||(p&&q&&r)||...)||!(p&&q)---->delete (p&&q)
				if (ptree->child[1]->type == NEGATION_STA&&delete_p_in_p_and_q_of_not_p(ptree))
				{
					PRE(ptree);
					return;
				}
				//(...||(!(p&&q)&&r)||...)||(p&&q)---->delete !(p&&q)
				if (ptree->child[1]->type != NEGATION_STA&&delete_not_p_in_not_p_and_q_of_p(ptree))
				{
					PRE(ptree);
					return;
				}

				//(...||(p)||...)||p&&q---->delete (p&&q) not near condition revized
				if (delete_right_p_and_q_of_p(ptree))
				{
					PRE(ptree);
					return;
				}
				//(...||(p)||...)||!p&&q---->delete !p
				if (delete_right_not_p_of_not_p_and_q(ptree))
				{
					PRE(ptree);
					return;
				}
				//(...||(!p)||...)||p&&q---->delete (p&&q)
				if (delete_right_not_p_of_not_p_and_q(ptree))
				{
					PRE(ptree);
					return;
				}
				PRE_or_shortcut(ptree);
				return;
			}
		}
		else
		{
			//(5)left: not and right:and 
			//p||(p&&q)
			if (ptree->child[1]->type == AND_STA&&POST_findintree(ptree->child[1], ptree->child[0], AND_STA))
			{

				ptree->copy_tree(ptree->child[0]);
				PRE(ptree);
				return;
			}
			//!p||(p&&q)
			if (ptree->child[0]->type == NEGATION_STA && delete_p_of_not_p(ptree->child[1], ptree->child[0]->child[0]) == 1)
			{
				PRE(ptree);
			}
			//p||(!p&&q)
			if (ptree->child[0]->type != NEGATION_STA && delete_not_p_of_p(ptree->child[1], ptree->child[0]) == 1)
			{
				PRE(ptree);
			}
			//(6)left: not and right:not and the formula is not special
			PRE_or_shortcut(ptree);
			return;
		}
	}

}

////////////////////////////////////////////////////lxf add////////////////////////////////////////////////////
void CNFMachine::PRE_or_recur(CTreeNode * ptree)//deal with ||

{

	//adjust the tree so that the right child's type is not or(the end of or)

	if (adjust_right_child_or(ptree))
		PRE(ptree->child[0]);
	//true || p         p||true---------->true

	if (get_conflict_or(ptree->child[1], ptree->child[0]) || true_condition_or(ptree))

	{

		ptree_to_true(ptree);
		return;

	}
	else if (ptree->child[1]->compare(ptree->child[0]))//p||p

	{

		ptree->copy_tree(ptree->child[0]);
		return;

	}

	else
	{
		if (ptree->child[0]->type == AND_STA)
		{
			//(1)left: and right:not and   
			if (ptree->child[1]->type != AND_STA)
			{
				//(p&&q)||p
				if (POST_findintree(ptree->child[0], ptree->child[1], AND_STA))
				{

					ptree->copy_tree(ptree->child[1]);
					PRE(ptree);
					return;
				}
				//(p&&q)||!p
				if (ptree->child[1]->type == NEGATION_STA && delete_p_of_not_p(ptree->child[0], ptree->child[1]->child[0]) == 1)
				{
					PRE(ptree);
					return;
				}
				//(!p&&q)||p
				if (ptree->child[1]->type != NEGATION_STA && delete_not_p_of_p(ptree->child[0], ptree->child[1]) == 1)
				{
					PRE(ptree);
					return;
				}
				//if not special end reduce
			}
			//(2)left: and right: and   
			else// if(ptree->child[1]->type==AND_STA)
			{
				//p&&q||p&&q&&r
				if (POST_findintree(ptree->child[1], ptree->child[0], AND_STA))
				{

					ptree->copy_tree(ptree->child[0]);
					PRE(ptree);
					return;
				}
				//p&&q||p&&r&&q not near condition revized
				if (find_left_in_right_and_and(ptree->child[1], ptree->child[0]))
				{
					ptree->copy_tree(ptree->child[0]);
					PRE(ptree);
					return;
				}
				//(p&&q)||!(p&&q)&&r
				if (delete_not_p_and_q_of_and_and(ptree))
				{
					PRE(ptree);
					return;
				}
				//p&&q&&r||p&&q 
				if (POST_findintree(ptree->child[0], ptree->child[1], AND_STA))
				{

					ptree->copy_tree(ptree->child[1]);
					PRE(ptree);
					return;
				}
				//p&&r&&q|| p&&q not near condition revized
				if (find_left_in_right_and_and(ptree->child[0], ptree->child[1]))
				{
					ptree->copy_tree(ptree->child[1]);
					PRE(ptree);
					return;
				}
				//p&&q&&r||!(p&&q)
				if (ptree->child[1]->type == NEGATION_STA && delete_p_of_not_p(ptree->child[0], ptree->child[1]->child[0]) == 1)
				{
					PRE(ptree);
					return;
				}
				//!(p&&q)||p&&q&&r
				//if not special ,end reduce
			}
		}
		else if (ptree->child[0]->type == OR_STA)
		{
			//(3)left: or right: not and   
			if (ptree->child[1]->type != AND_STA)
			{
				//(...||(p&&q)||...)||p---->delete p&&q not near condition revized
				if (delete_p_and_q_of_p(ptree))
				{
					PRE(ptree);
					return;
				}
				//(...||(p&&q)||...)||!p---->delete p
				if (ptree->child[1]->type == NEGATION_STA&&delete_p_in_p_and_q_of_not_p(ptree))
				{
					PRE(ptree);
					return;
				}
				//(...||(!p&&q)||...)||p---->delete !p  union these two condition    (...||(!p)||...)||p&&q---->delete p
				if (ptree->child[1]->type != NEGATION_STA&&delete_not_p_in_not_p_and_q_of_p(ptree))
				{
					PRE(ptree);
					return;
				}
				if (POST_findintree(ptree->child[0], ptree->child[1], OR_STA))
				{
					ptree->copy_tree(ptree->child[0]);
					//PRE(ptree);
					return;
				}
			}
			//(4)left: or right: and   
			else //if(ptree->child[1]->type==AND_STA)
			{
				//(...||(p&&q&&r)||...)||p&&q---->delete (p&&q&&r)
				if (delete_p_and_q_of_p(ptree))
				{
					PRE(ptree);
					return;
				}
				//(...||(p&&q&&r)||...)||!(p&&q)---->delete (p&&q)
				if (ptree->child[1]->type == NEGATION_STA&&delete_p_in_p_and_q_of_not_p(ptree))
				{
					PRE(ptree);
					return;
				}
				//(...||(!(p&&q)&&r)||...)||(p&&q)---->delete !(p&&q)
				if (ptree->child[1]->type != NEGATION_STA&&delete_not_p_in_not_p_and_q_of_p(ptree))
				{
					PRE(ptree);
					return;
				}

				//(...||(p)||...)||p&&q---->delete (p&&q) not near condition revized
				if (delete_right_p_and_q_of_p(ptree))
				{
					PRE(ptree);
					return;
				}
				//(...||(p)||...)||!p&&q---->delete !p
				if (delete_right_not_p_of_not_p_and_q(ptree))
				{
					PRE(ptree);
					return;
				}
				//(...||(!p)||...)||p&&q---->delete (p&&q)
				if (delete_right_not_p_of_not_p_and_q(ptree))
				{
					PRE(ptree);
					return;
				}
			}
		}
		else
		{
			//(5)left: not and right:and 
			//p||(p&&q)
			if (ptree->child[1]->type == AND_STA&&POST_findintree(ptree->child[1], ptree->child[0], AND_STA))
			{

				ptree->copy_tree(ptree->child[0]);
				PRE(ptree);
				return;
			}
			//!p||(p&&q)
			if (ptree->child[0]->type == NEGATION_STA && delete_p_of_not_p(ptree->child[1], ptree->child[0]->child[0]) == 1)
			{
				PRE(ptree);
			}
			//p||(!p&&q)
			if (ptree->child[0]->type != NEGATION_STA && delete_not_p_of_p(ptree->child[1], ptree->child[0]) == 1)
			{
				PRE(ptree);
			}
			//(6)left: not and right:not and the formula is not special

		}
	}



}
//////////////////////////////lxf add//////////////////////////////////////////////
bool chop_get_false(CTreeNode* ptree)
{
	if (ptree == NULL)
		return false;
	if (ptree->type == CHOP_STA)
	{
		if (ptree->child[0]->type == CHOP_STA&& ptree->child[1]->type != CHOP_STA)
		{
			if (ptree->child[1]->type == FALSE_EXP)
				return true;
			else
				return chop_get_false(ptree->child[0]);
		}
		else if (ptree->child[1]->type == CHOP_STA&& ptree->child[0]->type != CHOP_STA)
		{
			if (ptree->child[0]->type == FALSE_EXP)
				return true;
			else
				return chop_get_false(ptree->child[1]);
		}
		else if (ptree->child[1]->type != CHOP_STA&& ptree->child[0]->type != CHOP_STA)
		{
			if (ptree->child[0]->type == FALSE_EXP)
				return true;
			else if (ptree->child[1]->type == FALSE_EXP)
				return true;
			else
				return false;
		}
		else
		{
			return chop_get_false(ptree->child[1]) | chop_get_false(ptree->child[0]);
		}
	}
	else
	{
		return false;
	}
}
//////////////////////////////lxf add//////////////////////////////////////////////
//修改返回值为bool   2014.02.17
bool elim_emp(CTreeNode *ptree)
{
	if (ptree == NULL)
		return false;
	if (ptree->type != AND_STA)
		return false;
	else if (ptree->type == AND_STA&&ptree->child[0] != NULL&&ptree->child[0]->type == EMPTY_EXP)
	{
		ptree->copy_tree(ptree->child[1]);
		elim_emp(ptree);
		return true;
	}
	else if (ptree->type == AND_STA&&ptree->child[1] != NULL&&ptree->child[1]->type == EMPTY_EXP)
	{
		ptree->copy_tree(ptree->child[0]);
		elim_emp(ptree);
		return true;
	}
	else
	{
		bool b1, b2;
		b1 = elim_emp(ptree->child[0]);
		b2 = elim_emp(ptree->child[1]);
		return (b1 || b2);
	}
}
//added by LXF 2013/08/21 18:01:29
bool adjust_right_child_chop(CTreeNode *ptree)//adjust the tree so that the right child is not or type
{
	bool changed = false;
	CTreeNode *temp1;
	while (ptree->child[1] != NULL && ptree->child[1]->type == CHOP_STA)

	{
		changed = true;

		temp1 = new CTreeNode(CHOP_STA, "", 0);

		temp1->child[0] = new CTreeNode(AND_STA, "", 0);

		temp1->child[1] = new CTreeNode(AND_STA, "", 0);

		temp1->child[0]->copy_tree(ptree->child[0]);

		temp1->child[1]->copy_tree(ptree->child[1]->child[0]);



		ptree->child[1]->copy_tree(ptree->child[1]->child[1]);

		ptree->child[0]->copy_tree(temp1);

		delete temp1;

	}
	return changed;
}
//added by LXF 2013/08/22 15:36:17
bool adjust_left_child_chop(CTreeNode *ptree)//adjust the tree so that the right child is not or type
{
	bool changed = false;
	CTreeNode *temp1;
	while (ptree->child[0] != NULL && ptree->child[0]->type == CHOP_STA)

	{
		changed = true;

		temp1 = new CTreeNode(CHOP_STA, "", 0);

		temp1->child[0] = new CTreeNode(AND_STA, "", 0);

		temp1->child[1] = new CTreeNode(AND_STA, "", 0);

		temp1->child[1]->copy_tree(ptree->child[1]);

		temp1->child[0]->copy_tree(ptree->child[0]->child[1]);



		ptree->child[0]->copy_tree(ptree->child[0]->child[0]);

		ptree->child[1]->copy_tree(temp1);

		delete temp1;

	}
	return changed;
}
//////////////////////////////lxf add//////////////////////////////////////////////
void CNFMachine::PRE_chop(CTreeNode * ptree)//deal with ;

{

	CTreeNode *temp1, *temp2;

	if (chop_get_false(ptree))

	{
		ptree_to_false(ptree);
		return;
	}

	// 	if(ptree->child[0]!=NULL&&ptree->child[0]->type==EMPTY_EXP&& ptree->child[1]!=NULL)//empty;p
	// 	{
	// 		ptree->copy_tree(ptree->child[1]);
	// 		PRE(ptree);
	// 		return;
	// 	}
	adjust_right_child_chop(ptree);
	if (ptree->child[1]->type == EMPTY_EXP)
	{
		adjust_left_child_chop(ptree);
	}
	else//delete all empty in chop 
	{
		deleteAllEmptyInChop(ptree);
		if (ptree->type != CHOP_STA)
		{
			PRE(ptree);
			return;
		}
		adjust_left_child_chop(ptree);
	}
	if (ptree->child[0] != NULL && ptree->child[0]->type == TRUE_EXP && ptree->child[1] != NULL && ptree->child[1]->type == TRUE_EXP)//true;true

	{

		ptree->copy_tree(ptree->child[0]);
		return;

	}
	// 	else if(ptree->child[0]->type==TRUE_EXP)//true;p
	// 	{
	// 		temp1=new CTreeNode(STIME_STA,"STIME",0);
	// 		temp1->child[0]=new CTreeNode(AND_STA,"AND",0);
	// 		temp1->child[0]->copy_tree(ptree->child[1]);
	// 		temp2=new CTreeNode(NEXT_STA,"",0);
	// 		temp2->child[0]=new CTreeNode(AND_STA,"AND",0);
	// 		temp2->child[0]->copy_tree(temp1);
	// 		temp3=new CTreeNode(OR_STA,"OR",0);
	// 		temp3->child[0]=new CTreeNode(AND_STA,"AND",0);
	// 		temp3->child[1]=new CTreeNode(AND_STA,"AND",0);
	// 		temp3->child[0]->copy_tree(ptree->child[1]);
	// 		temp3->child[1]->copy_tree(temp2);	
	// 		ptree->copy_tree(temp3)	;
	// 		PRE(ptree);
	// 		delete temp1;
	// 		delete temp2;
	// 		delete temp3;
	// 		return;
	// 	}
	else//shortcuts
	{
		if (ptree->child[0]->type == AND_STA)/////////////(p&&q);r-->p&&q&&r???????????zxm
		{
			temp1 = new CTreeNode(AND_STA, "AND", 0);
			temp1->copy_tree(ptree->child[0]);
			bool b = elim_emp(temp1);
			if (b&&is_state_formula(temp1)) //修改
			{
				temp2 = new CTreeNode(AND_STA, "AND", 0);
				temp2->child[0] = new CTreeNode(AND_STA, "AND", 0);
				temp2->child[1] = new CTreeNode(AND_STA, "AND", 0);
				temp2->child[0]->copy_tree(temp1);
				temp2->child[1]->copy_tree(ptree->child[1]);
				ptree->copy_tree(temp2);
				delete temp2;
				PRE(ptree);
				return;
			}
			delete temp1;

		}
		PRE(ptree->child[0]);
		if (ptree->child[0]->type == FALSE_EXP)
		{
			ptree_to_false(ptree);
			return;
		}
		PRE(ptree->child[1]);
		if (ptree->child[1] && ptree->child[1]->type == FALSE_EXP)
		{
			ptree_to_false(ptree);
			return;
		}
		PRE_chop_recur(ptree);
		return;
	}

}
//////////////////////////////lxf add//////////////////////////////////////////////
void CNFMachine::PRE_chopstar(CTreeNode * ptree)//deal with chopstar
{
	if (ptree->child[0]->type == EMPTY_EXP)
	{
		ptree->copy_tree(ptree->child[0]);
		return;
	}
	while (ptree->child[0]->type == CHOPSTAR_STA)
	{
		ptree->copy_tree(ptree->child[0]);
	}
	PRE(ptree->child[0]);
	if (ptree->child[0]->type == EMPTY_EXP)
	{
		ptree->copy_tree(ptree->child[0]);
		return;
	}
	PRE_chopstar_recur(ptree);
	return;
}
//////////////////////////////lxf add//////////////////////////////////////////////
void CNFMachine::PRE_chopstar_recur(CTreeNode * ptree)//deal with chopstar
{
	if (ptree->child[0]->type == EMPTY_EXP)
	{
		ptree->copy_tree(ptree->child[0]);
		return;
	}
	while (ptree->child[0]->type == CHOPSTAR_STA)
	{
		ptree->copy_tree(ptree->child[0]);
	}
	return;
}
//////////////////////////////lxf add//////////////////////////////////////////////
void CNFMachine::PRE_chop_recur(CTreeNode * ptree)//deal with ;
{
	CTreeNode *temp1, *temp2;

	if (chop_get_false(ptree))

	{
		ptree_to_false(ptree);
		return;
	}

	// 	if(ptree->child[0]!=NULL&&ptree->child[0]->type==EMPTY_EXP&& ptree->child[1]!=NULL)//empty;p
	// 	{
	// 		ptree->copy_tree(ptree->child[1]);
	// 		PRE(ptree);
	// 		return;
	// 	}
	adjust_right_child_chop(ptree);
	if (ptree->child[1]->type == EMPTY_EXP)
	{
		adjust_left_child_chop(ptree);
		return;
	}
	else//delete all empty in chop 
	{
		deleteAllEmptyInChop(ptree);
		if (ptree->type != CHOP_STA)
		{
			PRE(ptree);
			return;
		}
		adjust_left_child_chop(ptree);
	}
	if (ptree->child[0] != NULL && ptree->child[0]->type == TRUE_EXP && ptree->child[1] != NULL && ptree->child[1]->type == TRUE_EXP)//true;true

	{

		ptree->copy_tree(ptree->child[0]);
		return;

	}
	// 	else if(ptree->child[0]->type==TRUE_EXP)//true;p
	// 	{
	// 		temp1=new CTreeNode(STIME_STA,"STIME",0);
	// 		temp1->child[0]=new CTreeNode(AND_STA,"AND",0);
	// 		temp1->child[0]->copy_tree(ptree->child[1]);
	// 		temp2=new CTreeNode(NEXT_STA,"",0);
	// 		temp2->child[0]=new CTreeNode(AND_STA,"AND",0);
	// 		temp2->child[0]->copy_tree(temp1);
	// 		temp3=new CTreeNode(OR_STA,"OR",0);
	// 		temp3->child[0]=new CTreeNode(AND_STA,"AND",0);
	// 		temp3->child[1]=new CTreeNode(AND_STA,"AND",0);
	// 		temp3->child[0]->copy_tree(ptree->child[1]);
	// 		temp3->child[1]->copy_tree(temp2);	
	// 		ptree->copy_tree(temp3)	;
	// 		PRE(ptree);
	// 		delete temp1;
	// 		delete temp2;
	// 		delete temp3;
	// 		return;
	// 	}
	else
	{
		if (ptree->child[0]->type == AND_STA)
		{
			temp1 = new CTreeNode(AND_STA, "AND", 0);
			temp1->copy_tree(ptree->child[0]);
			bool b = elim_emp(temp1);
			if (b&&is_state_formula(temp1))//修改
			{
				temp2 = new CTreeNode(AND_STA, "AND", 0);
				temp2->child[0] = new CTreeNode(AND_STA, "AND", 0);
				temp2->child[1] = new CTreeNode(AND_STA, "AND", 0);
				temp2->child[0]->copy_tree(temp1);
				temp2->child[1]->copy_tree(ptree->child[1]);
				ptree->copy_tree(temp2);
				delete temp2;
				PRE(ptree);
				return;
			}
			delete temp1;

		}
		return;
	}
}
//////////////////////////////lxf add//////////////////////////////////////////////
void adjust_tree_order(CTreeNode* ptree)//chop order 
{
	CTreeNode *temp1, *temp2, *temp3;
	if (ptree->child[0]->type != CHOP_STA &&ptree->child[1]->type != CHOP_STA)
		return;
	temp1 = new CTreeNode(CHOP_STA, "CHOP", 0);
	temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
	temp1->child[1] = new CTreeNode(AND_STA, "AND", 0);
	temp1->child[0]->copy_tree(ptree->child[0]);
	temp1->child[1]->copy_tree(ptree->child[1]->child[0]);
	temp3 = ptree->child[1]->child[1];
	if (temp3->type != CHOP_STA)
	{
		temp2 = new CTreeNode(CHOP_STA, "CHOP", 0);
		temp2->child[0] = new CTreeNode(CHOP_STA, "CHOP", 0);
		temp2->child[1] = new CTreeNode(AND_STA, "AND", 0);
		temp2->child[0]->copy_tree(temp1);
		temp2->child[1]->copy_tree(temp3);
		delete temp1;
		temp1 = new CTreeNode(CHOP_STA, "CHOP", 0);
		temp1->copy_tree(temp2);
		delete temp2;

	}
	while (temp3 != NULL && temp3->type == CHOP_STA&&temp3->child[1]->type == CHOP_STA)
	{
		temp2 = new CTreeNode(CHOP_STA, "CHOP", 0);
		temp2->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp2->child[1] = new CTreeNode(AND_STA, "AND", 0);
		temp2->child[0]->copy_tree(temp1);
		temp2->child[1]->copy_tree(temp3->child[0]);
		delete temp1;
		temp1 = new CTreeNode(CHOP_STA, "CHOP", 0);
		temp1->copy_tree(temp2);
		delete temp2;
		temp3 = temp3->child[1];
	}
	if (temp3->type == CHOP_STA&&temp3->child[1]->type != CHOP_STA)
	{
		temp2 = new CTreeNode(CHOP_STA, "CHOP", 0);
		temp2->child[0] = new CTreeNode(CHOP_STA, "CHOP", 0);
		temp2->child[1] = new CTreeNode(AND_STA, "AND", 0);
		temp2->child[0]->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp2->child[0]->child[1] = new CTreeNode(AND_STA, "AND", 0);
		temp2->child[1]->copy_tree(temp3->child[1]);
		temp2->child[0]->child[1]->copy_tree(temp3->child[0]);
		temp2->child[0]->child[0]->copy_tree(temp1);
		delete temp1;
		temp1 = new CTreeNode(CHOP_STA, "CHOP", 0);
		temp1->copy_tree(temp2);
		delete temp2;
	}

	ptree->copy_tree(temp1);
	delete temp1;
}
//////////////////////////////lxf add//////////////////////////////////////////////
bool is_state_formula(CTreeNode * ptree)
{
	if (ptree->type == EMPTY_EXP || ptree->type == NEXT_STA || ptree->type == MORE_EXP
		|| ptree->type == ALWAYS_STA || ptree->type == SKIP_EXP || ptree->type == LEN_STA
		|| ptree->type == STIME_STA || ptree->type == PROJECTION_STA || ptree->type == CHOP_STA
		|| ptree->type == CHOPSTAR_STA || ptree->type == FIN_EXP || ptree->type == FALSE_EXP
		|| ptree->type == TRUE_EXP)
		return false;
	else
	{
		bool b0 = true, b1 = true, b2 = true;
		if (ptree->child[0] != NULL)
			b0 = is_state_formula(ptree->child[0]);
		if (ptree->child[1] != NULL)
			b1 = is_state_formula(ptree->child[1]);
		if (ptree->child[2] != NULL)
			b2 = is_state_formula(ptree->child[2]);
		return b0&b1&b2;
	}
}
//////////////////////////////lxf add//////////////////////////////////////////////
void CNFMachine::PRE_prj(CTreeNode * ptree)//deal with prj
{
	CTreeNode *temp1, *temp2, *temp3, *temp4, *temp5;

	if (ptree->child[0] != NULL&&ptree->child[0]->type == FALSE_EXP)

	{
		ptree_to_false(ptree);
		return;
	}
	if (ptree->child[1] != NULL&&ptree->child[1]->type == PROJECTION_STA)
	{
		temp1 = ptree->child[1];
		while (temp1 != NULL&&temp1->type == PROJECTION_STA)
		{
			if (temp1->child[0] != NULL && temp1->child[0]->type == FALSE_EXP)
			{
				ptree_to_false(ptree);
				return;
			}
			temp1 = temp1->child[1];
		}
	}
	if (ptree->child[2] != NULL && ptree->child[2]->type == FALSE_EXP)
	{
		ptree_to_false(ptree);
		return;
	}
	if (ptree->child[0] != NULL&&ptree->child[0]->type == EMPTY_EXP&& ptree->child[1] == NULL&&ptree->child[2] != NULL&&ptree->child[2]->type == EMPTY_EXP)//e prj e
	{
		ptree->copy_tree(ptree->child[0]);
		return;
	}
	else if (ptree->child[2] != NULL&&ptree->child[2]->type == EMPTY_EXP)//(p1,p2,...,pm) prj empty
	{
		if (ptree->child[1] == NULL)
		{
			ptree->copy_tree(ptree->child[0]);
			PRE(ptree);
			return;
		}
		temp1 = new CTreeNode(CHOP_STA, "CHOP", 0);
		temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp1->child[1] = new CTreeNode(AND_STA, "AND", 0);
		temp1->child[0]->copy_tree(ptree->child[0]);
		temp1->child[1]->copy_tree(ptree->child[1]);
		ptree->copy_tree(temp1);
		delete temp1;
		temp2 = ptree->child[1];
		while (temp2 != NULL && temp2->type == PROJECTION_STA)
		{
			if (temp2->child[1] != NULL)
			{
				temp1 = new CTreeNode(CHOP_STA, "CHOP", 0);
				temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
				temp1->child[1] = new CTreeNode(AND_STA, "AND", 0);
				temp1->child[0]->copy_tree(temp2->child[0]);
				temp1->child[1]->copy_tree(temp2->child[1]);
				temp2->copy_tree(temp1);
				delete temp1;
				temp2 = temp2->child[1];
			}
			else
			{
				temp2->copy_tree(temp2->child[0]);
			}
		}
		//change the order of the tree
		adjust_tree_order(ptree);
		PRE(ptree);
		return;
	}
	else if (ptree->child[1] == NULL&&ptree->child[0]->type == EMPTY_EXP)// empty prj Q
	{
		ptree->copy_tree(ptree->child[2]);
		PRE(ptree);
		return;
	}
	else if (ptree->child[0]->type == OR_STA)//(p1||p2,...)prj Q
	{
		temp1 = new CTreeNode(PROJECTION_STA, "PROJECTION", 0);
		temp1->copy_tree(ptree);
		temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
		temp2 = new CTreeNode(PROJECTION_STA, "PROJECTION", 0);
		temp2->copy_tree(ptree);
		temp2->child[0]->copy_tree(ptree->child[0]->child[1]);
		temp3 = new CTreeNode(OR_STA, "OR", 0);
		temp3->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp3->child[1] = new CTreeNode(AND_STA, "AND", 0);
		temp3->child[0]->copy_tree(temp1);
		temp3->child[1]->copy_tree(temp2);
		ptree->copy_tree(temp3);
		PRE(ptree);
		delete temp1;
		delete temp2;
		delete temp3;
		return;
	}
	else if (ptree->child[2]->type == OR_STA)//(p1,p2,...)prj Q1||Q2
	{
		temp1 = new CTreeNode(PROJECTION_STA, "PROJECTION", 0);
		temp1->copy_tree(ptree);
		temp1->child[2]->copy_tree(ptree->child[2]->child[0]);
		temp2 = new CTreeNode(PROJECTION_STA, "PROJECTION", 0);
		temp2->copy_tree(ptree);
		temp2->child[2]->copy_tree(ptree->child[2]->child[1]);
		temp3 = new CTreeNode(OR_STA, "OR", 0);
		temp3->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp3->child[1] = new CTreeNode(AND_STA, "AND", 0);
		temp3->child[0]->copy_tree(temp1);
		temp3->child[1]->copy_tree(temp2);
		ptree->copy_tree(temp3);
		PRE(ptree);
		delete temp1;
		delete temp2;
		delete temp3;
		return;
	}
	else
	{
		temp1 = ptree->child[1];
		int counter = 0;
		while (temp1 != NULL && temp1->type == PROJECTION_STA)
		{

			if (temp1->child[0]->type == OR_STA)
			{
				temp2 = new CTreeNode(PROJECTION_STA, "PROJECTION", 0);
				temp2->copy_tree(ptree);

				temp1->child[0]->copy_tree(temp1->child[0]->child[0]);//change
				temp3 = new CTreeNode(PROJECTION_STA, "PROJECTION", 0);
				temp3->copy_tree(ptree);
				//locate or
				temp5 = temp2->child[1];
				int i = counter;
				while (i>0)
				{
					temp5 = temp5->child[1];
					i--;
				}
				temp5->child[0]->copy_tree(temp5->child[0]->child[1]);


				temp4 = new CTreeNode(OR_STA, "OR", 0);
				temp4->child[0] = new CTreeNode(AND_STA, "AND", 0);
				temp4->child[1] = new CTreeNode(AND_STA, "AND", 0);
				temp4->child[0]->copy_tree(temp3);
				temp4->child[1]->copy_tree(temp2);
				ptree->copy_tree(temp4);
				PRE(ptree);
				delete temp2;
				delete temp3;
				delete temp4;
				return;
			}
			counter++;
			temp1 = temp1->child[1];
		}
		//else here 
		if (ptree->child[0] != NULL && ptree->child[0]->type == AND_STA)//p1 include state formula,maybe need to revize
		{
			if (is_state_formula(ptree->child[0]->child[0]) && !is_state_formula(ptree->child[0]))
			{
				temp1 = new CTreeNode(AND_STA, "AND", 0);
				temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
				temp1->child[1] = new CTreeNode(PROJECTION_STA, "PROJECTION", 0);
				temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
				ptree->child[0]->copy_tree(ptree->child[0]->child[1]);
				temp1->child[1]->copy_tree(ptree);
				ptree->copy_tree(temp1);
				delete temp1;
				PRE(ptree);
				return;
			}
			if (is_state_formula(ptree->child[0]->child[1]) && !is_state_formula(ptree->child[0]))
			{
				temp1 = new CTreeNode(AND_STA, "AND", 0);
				temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
				temp1->child[1] = new CTreeNode(PROJECTION_STA, "PROJECTION", 0);
				temp1->child[0]->copy_tree(ptree->child[0]->child[1]);
				ptree->child[0]->copy_tree(ptree->child[0]->child[0]);
				temp1->child[1]->copy_tree(ptree);
				ptree->copy_tree(temp1);
				delete temp1;
				PRE(ptree);
				return;
			}

		}
		if (ptree->child[2] != NULL && ptree->child[2]->type == AND_STA)//Q includes state formula
		{
			if (is_state_formula(ptree->child[2]->child[0]) && !is_state_formula(ptree->child[2]))
			{
				temp1 = new CTreeNode(AND_STA, "AND", 0);
				temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
				temp1->child[1] = new CTreeNode(PROJECTION_STA, "PROJECTION", 0);
				temp1->child[0]->copy_tree(ptree->child[2]->child[0]);
				ptree->child[2]->copy_tree(ptree->child[2]->child[1]);
				temp1->child[1]->copy_tree(ptree);
				ptree->copy_tree(temp1);
				delete temp1;
				PRE(ptree);
				return;
			}
			if (is_state_formula(ptree->child[2]->child[1]) && !is_state_formula(ptree->child[2]))
			{
				temp1 = new CTreeNode(AND_STA, "AND", 0);
				temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
				temp1->child[1] = new CTreeNode(PROJECTION_STA, "PROJECTION", 0);
				temp1->child[0]->copy_tree(ptree->child[2]->child[1]);
				ptree->child[2]->copy_tree(ptree->child[2]->child[0]);
				temp1->child[1]->copy_tree(ptree);
				ptree->copy_tree(temp1);
				delete temp1;
				PRE(ptree);
				return;
			}
		}
		PRE(ptree->child[0]);
		if (ptree->child[0]->type == FALSE_EXP)
		{
			ptree_to_false(ptree);
			return;
		}
		temp1 = ptree->child[1];
		while (temp1 != NULL && temp1->type == PROJECTION_STA)
		{
			PRE(temp1->child[0]);
			if (temp1->child[0]->type == FALSE_EXP)
			{
				ptree_to_false(ptree);
				return;
			}
			temp1 = temp1->child[1];
		}
		PRE(ptree->child[2]);
		if (ptree->child[2]->type == FALSE_EXP)
		{
			ptree_to_false(ptree);
			return;
		}
		PRE_prj_recur(ptree);
	}


}
//////////////////////////////lxf add//////////////////////////////////////////////
void CNFMachine::PRE_prj_recur(CTreeNode * ptree)//deal with prj
{
	CTreeNode *temp1, *temp2, *temp3, *temp4, *temp5;
	if (ptree->child[0] != NULL&&ptree->child[0]->type == EMPTY_EXP&& ptree->child[1] == NULL&&ptree->child[2] != NULL&&ptree->child[2]->type == EMPTY_EXP)//e prj e
	{
		ptree->copy_tree(ptree->child[0]);
		return;
	}
	else if (ptree->child[2] != NULL&&ptree->child[2]->type == EMPTY_EXP)//(p1,p2,...,pm) prj empty
	{
		temp1 = new CTreeNode(CHOP_STA, "CHOP", 0);
		temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp1->child[1] = new CTreeNode(AND_STA, "AND", 0);
		temp1->child[0]->copy_tree(ptree->child[0]);
		temp1->child[1]->copy_tree(ptree->child[1]);
		ptree->copy_tree(temp1);
		delete temp1;
		temp2 = ptree->child[1];
		while (temp2 != NULL && temp2->type == PROJECTION_STA)
		{
			if (temp2->child[1] != NULL)
			{
				temp2->type = CHOP_STA;
				temp2 = temp2->child[1];
			}
			else
			{
				temp2->copy_tree(temp2->child[0]);
			}
		}
		//change the order of the tree
		adjust_tree_order(ptree);
		PRE(ptree);
		return;
	}
	else if (ptree->child[1] == NULL&&ptree->child[0]->type == EMPTY_EXP)// empty prj Q
	{
		ptree->copy_tree(ptree->child[2]);
		PRE(ptree);
		return;
	}
	else if (ptree->child[0]->type == OR_STA)//(p1||p2,...)prj Q
	{
		temp1 = new CTreeNode(PROJECTION_STA, "PROJECTION", 0);
		temp1->copy_tree(ptree);
		temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
		temp2 = new CTreeNode(PROJECTION_STA, "PROJECTION", 0);
		temp2->copy_tree(ptree);
		temp2->child[0]->copy_tree(ptree->child[0]->child[1]);
		temp3 = new CTreeNode(OR_STA, "OR", 0);
		temp3->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp3->child[1] = new CTreeNode(AND_STA, "AND", 0);
		temp3->child[0]->copy_tree(temp1);
		temp3->child[1]->copy_tree(temp2);
		ptree->copy_tree(temp3);
		PRE(ptree);
		delete temp1;
		delete temp2;
		delete temp3;
		return;
	}
	else if (ptree->child[2]->type == OR_STA)//(p1,p2,...)prj Q1||Q2
	{
		temp1 = new CTreeNode(PROJECTION_STA, "PROJECTION", 0);
		temp1->copy_tree(ptree);
		temp1->child[2]->copy_tree(ptree->child[2]->child[0]);
		temp2 = new CTreeNode(PROJECTION_STA, "PROJECTION", 0);
		temp2->copy_tree(ptree);
		temp2->child[2]->copy_tree(ptree->child[2]->child[1]);
		temp3 = new CTreeNode(OR_STA, "OR", 0);
		temp3->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp3->child[1] = new CTreeNode(AND_STA, "AND", 0);
		temp3->child[0]->copy_tree(temp1);
		temp3->child[1]->copy_tree(temp2);
		ptree->copy_tree(temp3);
		PRE(ptree);
		delete temp1;
		delete temp2;
		delete temp3;
		return;
	}
	else
	{
		temp1 = ptree->child[1];
		int counter = 0;
		while (temp1 != NULL && temp1->type == PROJECTION_STA)
		{

			if (temp1->child[0]->type == OR_STA)
			{
				temp2 = new CTreeNode(PROJECTION_STA, "PROJECTION", 0);
				temp2->copy_tree(ptree);

				temp1->child[0]->copy_tree(temp1->child[0]->child[0]);//change
				temp3 = new CTreeNode(PROJECTION_STA, "PROJECTION", 0);
				temp3->copy_tree(ptree);
				//locate or
				temp5 = temp2->child[1];
				int i = counter;
				while (i>0)
				{
					temp5 = temp5->child[1];
					i--;
				}
				temp5->child[0]->copy_tree(temp5->child[0]->child[1]);


				temp4 = new CTreeNode(OR_STA, "OR", 0);
				temp4->child[0] = new CTreeNode(AND_STA, "AND", 0);
				temp4->child[1] = new CTreeNode(AND_STA, "AND", 0);
				temp4->child[0]->copy_tree(temp3);
				temp4->child[1]->copy_tree(temp2);
				ptree->copy_tree(temp4);
				PRE(ptree);
				delete temp2;
				delete temp3;
				delete temp4;
				return;
			}
			counter++;
			temp1 = temp1->child[1];
		}
		//else here 
		if (ptree->child[0] != NULL && ptree->child[0]->type == AND_STA)//p1 include state formula,maybe need to revize
		{
			if (is_state_formula(ptree->child[0]->child[0]) && !is_state_formula(ptree->child[0]))
			{
				temp1 = new CTreeNode(AND_STA, "AND", 0);
				temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
				temp1->child[1] = new CTreeNode(PROJECTION_STA, "PROJECTION", 0);
				temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
				ptree->child[0]->copy_tree(ptree->child[0]->child[1]);
				temp1->child[1]->copy_tree(ptree);
				ptree->copy_tree(temp1);
				delete temp1;
				PRE(ptree);
				return;
			}
			if (is_state_formula(ptree->child[0]->child[1]) && !is_state_formula(ptree->child[0]))
			{
				temp1 = new CTreeNode(AND_STA, "AND", 0);
				temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
				temp1->child[1] = new CTreeNode(PROJECTION_STA, "PROJECTION", 0);
				temp1->child[0]->copy_tree(ptree->child[0]->child[1]);
				ptree->child[0]->copy_tree(ptree->child[0]->child[0]);
				temp1->child[1]->copy_tree(ptree);
				ptree->copy_tree(temp1);
				delete temp1;
				PRE(ptree);
				return;
			}

		}
		if (ptree->child[2] != NULL && ptree->child[2]->type == AND_STA)//Q includes state formula
		{
			if (is_state_formula(ptree->child[2]->child[0]) && !is_state_formula(ptree->child[2]))
			{
				temp1 = new CTreeNode(AND_STA, "AND", 0);
				temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
				temp1->child[1] = new CTreeNode(PROJECTION_STA, "PROJECTION", 0);
				temp1->child[0]->copy_tree(ptree->child[2]->child[0]);
				ptree->child[2]->copy_tree(ptree->child[2]->child[1]);
				temp1->child[1]->copy_tree(ptree);
				ptree->copy_tree(temp1);
				delete temp1;
				PRE(ptree);
				return;
			}
			if (is_state_formula(ptree->child[2]->child[1]) && !is_state_formula(ptree->child[2]))
			{
				temp1 = new CTreeNode(AND_STA, "AND", 0);
				temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
				temp1->child[1] = new CTreeNode(PROJECTION_STA, "PROJECTION", 0);
				temp1->child[0]->copy_tree(ptree->child[2]->child[1]);
				ptree->child[2]->copy_tree(ptree->child[2]->child[0]);
				temp1->child[1]->copy_tree(ptree);
				ptree->copy_tree(temp1);
				delete temp1;
				PRE(ptree);
				return;
			}
		}
		return;
	}
}
////////////////////////////////////////////added by LXF/////////////////////////////////////////////
void CNFMachine::PRE_imply_equal(CTreeNode * ptree)//deal with imply and equal
{
	CTreeNode *temp1, *temp2, *temp3, *temp4;
	if (ptree == NULL)
	{
		return;
	}
	if (ptree->type == IDENT_EXP || ptree->type == EMPTY_EXP || ptree->type == TRUE_EXP || ptree->type == FALSE_EXP || ptree->type == MORE_EXP)
		return;
	if (ptree->type == AND_STA && ptree->child[0]->type == IMPLY_STA &&ptree->child[1]->type == IFF_STA &&
		ptree->child[0]->child[0]->compare(ptree->child[1]->child[0]) && ptree->child[0]->child[1]->compare(ptree->child[1]->child[1]))
	{
		ptree->copy_tree(ptree->child[1]);
		PRE_imply_equal(ptree);
		return;
	}
	if (ptree->type == AND_STA && ptree->child[0]->type == IMPLY_STA &&ptree->child[1]->type == IFF_STA &&
		ptree->child[0]->child[0]->compare(ptree->child[1]->child[1]) && ptree->child[0]->child[1]->compare(ptree->child[1]->child[0]))
	{
		ptree->copy_tree(ptree->child[1]);
		PRE_imply_equal(ptree);
		return;
	}
	if (ptree->type == AND_STA && ptree->child[1]->type == IMPLY_STA &&ptree->child[0]->type == IFF_STA &&
		ptree->child[1]->child[0]->compare(ptree->child[0]->child[0]) && ptree->child[1]->child[1]->compare(ptree->child[0]->child[1]))
	{
		ptree->copy_tree(ptree->child[0]);
		PRE_imply_equal(ptree);
		return;
	}
	if (ptree->type == AND_STA && ptree->child[1]->type == IMPLY_STA &&ptree->child[0]->type == IFF_STA &&
		ptree->child[1]->child[0]->compare(ptree->child[0]->child[1]) && ptree->child[1]->child[1]->compare(ptree->child[0]->child[0]))
	{
		ptree->copy_tree(ptree->child[0]);
		PRE_imply_equal(ptree);
		return;
	}
	if (ptree->type == IMPLY_STA)
	{
		if (ptree->child[0]->type == FALSE_EXP)
		{
			temp1 = new CTreeNode(TRUE_EXP, "TRUE", 0);
			ptree->copy_tree(temp1);
			delete temp1;
			return;
		}
		else if (ptree->child[0]->type == TRUE_EXP)
		{
			ptree->copy_tree(ptree->child[1]);
		}
		else if (ptree->child[1]->type == FALSE_EXP)
		{
			temp1 = new CTreeNode(NEGATION_STA, "", 0);
			temp1->child[0] = new CTreeNode(AND_STA, "", 0);
			temp1->child[0]->copy_tree(ptree->child[0]);
			ptree->copy_tree(temp1);
			delete temp1;
		}
		else
		{
			ptree->type = OR_STA;
			temp1 = new CTreeNode(AND_STA, "", 0);
			temp1->copy_tree(ptree->child[0]);
			ptree->child[0] = new CTreeNode(NEGATION_STA, "", 0);
			ptree->child[0]->child[0] = new CTreeNode(AND_STA, "", 0);
			ptree->child[0]->child[0]->copy_tree(temp1);
			PRE_imply_equal(ptree->child[0]);
			PRE_imply_equal(ptree->child[1]);
			delete temp1;

		}
		return;
	}
	else if (ptree->type == IFF_STA)
	{
		if (ptree->child[0]->compare(ptree->child[1]))
		{
			ptree_to_true(ptree);
			return;
		}
		if (ptree->child[0]->type == FALSE_EXP && ptree->child[1]->type != FALSE_EXP)
		{
			temp1 = new CTreeNode(NEGATION_STA, "", 0);
			temp1->child[0] = new CTreeNode(AND_STA, "", 0);
			temp1->child[0]->copy_tree(ptree->child[1]);
			ptree->copy_tree(temp1);
			delete temp1;
		}
		else if (ptree->child[1]->type == FALSE_EXP && ptree->child[0]->type != FALSE_EXP)
		{
			temp1 = new CTreeNode(NEGATION_STA, "", 0);
			temp1->child[0] = new CTreeNode(AND_STA, "", 0);
			temp1->child[0]->copy_tree(ptree->child[0]);
			ptree->copy_tree(temp1);
			delete temp1;
		}

		else if (ptree->child[0]->type == TRUE_EXP && ptree->child[1]->type != TRUE_EXP)
		{
			ptree->copy_tree(ptree->child[1]);
		}
		else if (ptree->child[1]->type == TRUE_EXP && ptree->child[0]->type != TRUE_EXP)
		{
			ptree->copy_tree(ptree->child[0]);
		}
		else if (ptree->child[1]->type == NEGATION_STA && ptree->child[0]->compare(ptree->child[1]->child[0]))
		{
			ptree_to_false(ptree);
			return;
		}
		else if (ptree->child[0]->type == NEGATION_STA && ptree->child[1]->compare(ptree->child[0]->child[0]))
		{
			ptree_to_false(ptree);
			return;
		}
		else
		{
			temp1 = new CTreeNode(NEGATION_STA, "", 0);
			temp1->child[0] = new CTreeNode(AND_STA, "", 0);
			temp1->child[0]->copy_tree(ptree->child[0]);
			temp2 = new CTreeNode(NEGATION_STA, "", 0);
			temp2->child[0] = new CTreeNode(AND_STA, "", 0);
			temp2->child[0]->copy_tree(ptree->child[1]);
			temp3 = new CTreeNode(AND_STA, "", 0);
			temp3->child[0] = new CTreeNode(AND_STA, "", 0);
			temp3->child[1] = new CTreeNode(AND_STA, "", 0);
			temp3->child[0]->copy_tree(ptree->child[0]);
			temp3->child[1]->copy_tree(ptree->child[1]);
			temp4 = new CTreeNode(AND_STA, "", 0);
			temp4->child[0] = new CTreeNode(AND_STA, "", 0);
			temp4->child[1] = new CTreeNode(AND_STA, "", 0);
			temp4->child[0]->copy_tree(temp1);
			temp4->child[1]->copy_tree(temp2);

			ptree->type = OR_STA;
			ptree->child[0]->copy_tree(temp3);
			ptree->child[1]->copy_tree(temp4);
			PRE_imply_equal(ptree->child[0]);
			PRE_imply_equal(ptree->child[1]);
			delete temp1;
			delete temp2;
			delete temp3;
			delete temp4;
		}
		return;
	}
	else
	{
		if (ptree->child[0] != NULL)
			PRE_imply_equal(ptree->child[0]);
		if (ptree->child[1] != NULL)
			PRE_imply_equal(ptree->child[1]);
		if (ptree->child[2] != NULL)
			PRE_imply_equal(ptree->child[2]);
	}

}
////////////////////////////////////////////added by LXF/////////////////////////////////////////////

void CNFMachine::PRE(CTreeNode *ptree){
	PRE_imply_equal(ptree);
	CTreeNode *temp1;
	if (ptree == NULL)
	{
		return;
	}
	switch (ptree->type)
	{
	case IDENT_EXP:		 break;//atom lxf
	case FALSE_EXP:		 break;//false lxf
	case TRUE_EXP:		 break;//true lxf
	case EMPTY_EXP:		 break;//empty lxf
	case MORE_EXP:		 break;//empty lxf
	case FIN_EXP:
		if (ptree->child[0] != NULL)
			PRE(ptree->child[0]);
		if (ptree->child[0]->type == EMPTY_EXP)
		{
			temp1 = new CTreeNode(STIME_STA, "STIME", 0);
			temp1->child[0] = new CTreeNode(EMPTY_EXP, "EMPTY", 0);
			ptree->copy_tree(temp1);
			delete temp1;
		}
		else if (ptree->child[0]->type == TRUE_EXP)
		{
			ptree_to_true(ptree);
			return;
		}
		else if (ptree->child[0]->type == FALSE_EXP)
		{
			ptree_to_false(ptree);
			return;
		}
		break;//fin lxf


	case CHOPSTAR_STA:
		PRE_chopstar(ptree);
		break;


	case LEN_STA:

		if (ptree->child[0] != NULL)
		{
			int count_n = atoi(ptree->child[0]->name_str.c_str());
			if (count_n == 0)
			{
				ptree_to_empty(ptree);
			}
			else
			{
				;
			}

		}
		break;//len(x) lxf

	case NEXT_STA:

		if (ptree->child[0] != NULL)

			PRE(ptree->child[0]);

		if (ptree->child[0]->type == FALSE_EXP)
		{
			ptree_to_false(ptree);
		}
		// 			 if (ptree->child[0]->type==EMPTY_EXP)
		// 			 {
		// 				CTreeNode temp0=new CTreeNode(LEN_STA,"",0);
		// 				temp0->child[0]=
		// 			 }
		break;//next lxf

	case NEGATION_STA:

		PRE_not(ptree);// negation lxf

		break;

	case AND_STA:

		PRE_and(ptree);//negation lxf

		break;

	case OR_STA:

		PRE_or(ptree);//negation lxf

		break;

	case CHOP_STA:

		PRE_chop(ptree);//chop lxf

		break;

	case PROJECTION_STA:

		PRE_prj(ptree);//prj lxf

		break;

	case WNEXT_STA:

		if (ptree->child[0] != NULL)

			PRE(ptree->child[0]);

		ptree->type = OR_STA;

		//

		temp1 = new CTreeNode(AND_STA, "", 0);

		temp1->copy_tree(ptree->child[0]);

		//

		ptree->child[0] = new CTreeNode(NEXT_STA, "", 0);

		ptree->child[0]->child[0] = new CTreeNode(AND_STA, "", 0);

		ptree->child[0]->child[0]->copy_tree(temp1);

		delete temp1;

		ptree->child[1] = new CTreeNode(EMPTY_EXP, "EMPTY", 0);

		break;

	case ALWAYS_STA:

		if (ptree->child[0] != NULL)

			PRE(ptree->child[0]);

		if (ptree->child[0]->type == ALWAYS_STA)

		{

			ptree->copy_tree(ptree->child[0]);

			PRE(ptree);

			return;

		}
		else if (ptree->child[0]->type == EMPTY_EXP)
			ptree_to_empty(ptree);
		else if (ptree->child[0]->type == TRUE_EXP)
			ptree_to_true(ptree);
		else if (ptree->child[0]->type == FALSE_EXP)
			ptree_to_false(ptree);//always lxf

		break;

	case STIME_STA:

		if (ptree->child[0] != NULL)

		{

			PRE(ptree->child[0]);

		}

		if (ptree->child[0]->type == STIME_STA)

		{

			ptree->copy_tree(ptree->child[0]);

			PRE(ptree);

			return;

		}
		else if (ptree->child[0]->type == TRUE_EXP)
			ptree_to_true(ptree);
		else if (ptree->child[0]->type == FALSE_EXP)
			ptree_to_false(ptree);//sometimes lxf

		break;
	case UNTIL_STA:
		PRE_until(ptree);
		break;


	}
	return;
}



void CNFMachine::DNF(CTreeNode * ptree)
{
	DNF_neg(ptree);
	DNF_and(ptree);
	return;
}
void CNFMachine::DNF_and(CTreeNode * ptree)
{
	CTreeNode *temp1, *temp2;

	if (ptree == NULL)
	{
		return;
	}

	if (ptree->type == OR_STA)
	{
		DNF_and(ptree->child[0]);
		DNF_and(ptree->child[1]);
		return;
	}

	if (ptree->type == AND_STA)
	{
		DNF_and(ptree->child[0]);
		DNF_and(ptree->child[1]);
		if (ptree->child[1] != NULL && ptree->child[1]->type == OR_STA)
		{
			temp1 = new CTreeNode(AND_STA, "", 0);
			temp1->child[0] = new CTreeNode(AND_STA, "", 0);
			temp1->child[0]->copy_tree(ptree->child[0]);
			temp1->child[1] = new CTreeNode(AND_STA, "", 0);
			temp1->child[1]->copy_tree(ptree->child[1]->child[0]);

			temp2 = new CTreeNode(AND_STA, "", 0);
			temp2->child[0] = new CTreeNode(AND_STA, "", 0);
			temp2->child[0]->copy_tree(ptree->child[0]);
			temp2->child[1] = new CTreeNode(AND_STA, "", 0);
			temp2->child[1]->copy_tree(ptree->child[1]->child[1]);
			ptree->type = OR_STA;
			ptree->child[0]->copy_tree(temp1);
			ptree->child[1]->copy_tree(temp2);
			delete temp1;
			delete temp2;

			DNF_and(ptree);
			return;
		}
		if (ptree->child[0] != NULL && ptree->child[0]->type == OR_STA)
		{
			temp1 = new CTreeNode(AND_STA, "", 0);
			temp1->child[0] = new CTreeNode(AND_STA, "", 0);
			temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
			temp1->child[1] = new CTreeNode(AND_STA, "", 0);
			temp1->child[1]->copy_tree(ptree->child[1]);

			temp2 = new CTreeNode(AND_STA, "", 0);
			temp2->child[0] = new CTreeNode(AND_STA, "", 0);
			temp2->child[0]->copy_tree(ptree->child[0]->child[1]);
			temp2->child[1] = new CTreeNode(AND_STA, "", 0);
			temp2->child[1]->copy_tree(ptree->child[1]);
			ptree->type = OR_STA;
			ptree->child[0]->copy_tree(temp1);
			ptree->child[1]->copy_tree(temp2);
			delete temp1;
			delete temp2;

			DNF_and(ptree);
		}
	}
}
void CNFMachine::DNF_neg(CTreeNode * ptree)
{
	CTreeNode *temp1, *temp2;
	if (ptree == NULL)
	{
		return;
	}
	if (ptree->type == AND_STA || ptree->type == OR_STA)
	{
		DNF_neg(ptree->child[0]);
		DNF_neg(ptree->child[1]);
		return;
	}
	if (ptree->type == NEGATION_STA && ptree->child[0]->type == AND_STA)
	{
		DNF_neg(ptree->child[0]->child[0]);
		DNF_neg(ptree->child[0]->child[1]);

		temp1 = new CTreeNode(NEGATION_STA, "", 0);
		temp1->child[0] = new CTreeNode(AND_STA, "", 0);
		temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
		temp2 = new CTreeNode(NEGATION_STA, "", 0);
		temp2->child[0] = new CTreeNode(AND_STA, "", 0);
		temp2->child[0]->copy_tree(ptree->child[0]->child[1]);
		ptree->type = OR_STA;
		ptree->child[0]->copy_tree(temp1);
		ptree->child[1] = new CTreeNode(AND_STA, "", 0);
		ptree->child[1]->copy_tree(temp2);
		delete temp1;
		delete temp2;

		DNF_neg(ptree);
		return;
	}

	if (ptree->type == NEGATION_STA && ptree->child[0]->type == OR_STA)
	{
		DNF_neg(ptree->child[0]->child[0]);
		DNF_neg(ptree->child[0]->child[1]);

		temp1 = new CTreeNode(NEGATION_STA, "", 0);
		temp1->child[0] = new CTreeNode(AND_STA, "", 0);
		temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
		temp2 = new CTreeNode(NEGATION_STA, "", 0);
		temp2->child[0] = new CTreeNode(AND_STA, "", 0);
		temp2->child[0]->copy_tree(ptree->child[0]->child[1]);
		ptree->type = AND_STA;
		ptree->child[0]->copy_tree(temp1);
		ptree->child[1] = new CTreeNode(AND_STA, "", 0);
		ptree->child[1]->copy_tree(temp2);
		delete temp1;
		delete temp2;

		DNF_neg(ptree);
		return;
	}
	if (ptree->type == NEGATION_STA && ptree->child[0]->type == NEGATION_STA)
	{
		ptree->copy_tree(ptree->child[0]->child[0]);
		DNF_neg(ptree);
	}
}

void CNFMachine::NFDNF(CTreeNode * ptree)
{
	CTreeNode *temp1, *temp2, *temp3, *temp4, *temp5, *temp6, *temp7;

	temp1 = new CTreeNode(OR_STA, "", 0);
	temp2 = new CTreeNode(AND_STA, "", 0);
	temp3 = new CTreeNode(AND_STA, "", 0);

	temp4 = new CTreeNode(EMPTY_EXP, "EMPTY", 0);
	temp5 = new CTreeNode(NEXT_STA, "", 0);
	temp6 = new CTreeNode(TRUE_EXP, "TRUE", 0);

	temp5->child[0] = new CTreeNode(AND_STA, "", 0);
	temp5->child[0]->copy_tree(temp6);

	temp7 = new CTreeNode(TRUE_EXP, "", 0);
	temp7->copy_tree(ptree);
	temp2->child[0] = new CTreeNode(AND_STA, "", 0);
	temp2->child[0]->copy_tree(temp7);
	temp2->child[1] = new CTreeNode(AND_STA, "", 0);
	temp2->child[1]->copy_tree(temp4);

	temp3->child[0] = new CTreeNode(AND_STA, "", 0);
	temp3->child[0]->copy_tree(temp7);
	temp3->child[1] = new CTreeNode(AND_STA, "", 0);
	temp3->child[1]->copy_tree(temp5);

	temp1->child[0] = new CTreeNode(AND_STA, "", 0);
	temp1->child[0]->copy_tree(temp2);
	temp1->child[1] = new CTreeNode(AND_STA, "", 0);
	temp1->child[1]->copy_tree(temp3);

	ptree->copy_tree(temp1);

	delete temp4;
	delete temp6;

	delete temp1;
	delete temp2;
	delete temp3;
	delete temp5;
	delete temp7;

}

/*将公式中的empty以及()后面相同的那些项前面的状态公式合并*/
/*next结点是新生成的结点，新结点需要前处理PRE*/
void CNFMachine::COMB(CTreeNode * ptree)
{
	CTreeNode *temp1, *temp2;
	while (ptree->type == OR_STA && ptree->child[1]->type == OR_STA)
	{
		temp1 = new CTreeNode(OR_STA, "", 0);
		temp1->child[0] = new CTreeNode(OR_STA, "", 0);
		temp1->child[1] = new CTreeNode(OR_STA, "", 0);
		temp1->child[0]->copy_tree(ptree->child[0]);
		temp1->child[1]->copy_tree(ptree->child[1]->child[0]);

		ptree->child[1]->copy_tree(ptree->child[1]->child[1]);
		ptree->child[0]->copy_tree(temp1);

		delete temp1;
	}
	if (ptree->child[0] != NULL && ptree->child[0]->type == OR_STA)
		COMB(ptree->child[0]);

	if (ptree->type == NEXT_STA)
		PRE(ptree);
	else
		if (ptree->type == AND_STA && ptree->child[1]->type == NEXT_STA)
		{
			PRE(ptree->child[1]);
			if (ptree->child[1]->type == FALSE_EXP)
			{
				temp1 = new CTreeNode(FALSE_EXP, "FALSE", 0);
				ptree->copy_tree(temp1);
				delete temp1;
			}
		}
		else
			if (ptree->type == OR_STA && ptree->child[0] != NULL && ptree->child[1] != NULL)
			{
				//add pre begin
				if (ptree->child[0]->type == NEXT_STA)
					PRE(ptree->child[0]);
				else
					if (ptree->child[0]->type == AND_STA && ptree->child[0]->child[1]->type == NEXT_STA)
						PRE(ptree->child[0]->child[1]);
				if (ptree->child[1]->type == NEXT_STA)
					PRE(ptree->child[1]);
				else
					if (ptree->child[1]->type == AND_STA && ptree->child[1]->child[1]->type == NEXT_STA)
						PRE(ptree->child[1]->child[1]);

				//add pre end
				//add begin

				if ((ptree->child[0]->type == FALSE_EXP || ptree->child[0]->type == AND_STA && ptree->child[0]->child[1]->type == FALSE_EXP) && (ptree->child[1]->type == FALSE_EXP || ptree->child[1]->type == AND_STA && ptree->child[1]->child[1]->type == FALSE_EXP))
				{
					temp1 = new CTreeNode(FALSE_EXP, "FALSE", 0);
					ptree->copy_tree(temp1);
					delete temp1;
				}
				else
					if (ptree->child[0]->type == FALSE_EXP || ptree->child[0]->type == AND_STA && ptree->child[0]->child[1]->type == FALSE_EXP)
						ptree->copy_tree(ptree->child[1]);
					else
						if (ptree->child[1]->type == FALSE_EXP || ptree->child[1]->type == AND_STA && ptree->child[1]->child[1]->type == FALSE_EXP)
							ptree->copy_tree(ptree->child[0]);
				//add end
				//empty || empty-->empty           ;        p && empty || p && empty--> p && empty ; p && ()q || p && ()q --> p && ()q;  ()p || ()p-->()p(next后面暂时不考虑fin)
						else
							if (ptree->child[0]->compare(ptree->child[1]))
								ptree->copy_tree(ptree->child[0]);
				// ()p || ()p -->  ()p  (p中有fin标记的)
							else
								if (ptree->child[0]->type == NEXT_STA && ptree->child[1]->type == NEXT_STA && ptree->child[0]->child[0]->compare1(ptree->child[1]->child[0]))
									ptree->copy_tree(ptree->child[0]);

				//empty || p && empty --> empty
								else
									if (ptree->child[0]->type == EMPTY_EXP && ptree->child[1]->type == AND_STA && (ptree->child[1]->child[0]->type == EMPTY_EXP || ptree->child[1]->child[1]->type == EMPTY_EXP))
										ptree->copy_tree(ptree->child[0]);
				//p && empty || empty --> empty
									else
										if (ptree->child[1]->type == EMPTY_EXP && ptree->child[0]->type == AND_STA && (ptree->child[0]->child[0]->type == EMPTY_EXP || ptree->child[0]->child[1]->type == EMPTY_EXP))
											ptree->copy_tree(ptree->child[1]);
				//()p || q && ()p --> ()p
										else
											if (ptree->child[0]->type == NEXT_STA && ptree->child[1]->type == AND_STA && (ptree->child[1]->child[0]->type == NEXT_STA && ptree->child[1]->child[0]->child[0]->compare(ptree->child[0]->child[0]) || ptree->child[1]->child[1]->type == NEXT_STA && ptree->child[1]->child[1]->child[0]->compare(ptree->child[0]->child[0])))
												ptree->copy_tree(ptree->child[0]);//changed by LXF 2013/08/19 15:59:12 compare1->compare
				//q && ()p || ()p --> ()p
											else
												if (ptree->child[1]->type == NEXT_STA && ptree->child[0]->type == AND_STA && (ptree->child[0]->child[0]->type == NEXT_STA && ptree->child[0]->child[0]->child[0]->compare(ptree->child[1]->child[0]) || ptree->child[0]->child[1]->type == NEXT_STA && ptree->child[0]->child[1]->child[0]->compare(ptree->child[1]->child[0])))
												{
													ptree->copy_tree(ptree->child[1]);
												}//changed by LXF 2013/08/19 15:59:12 compare1->compare

				//p && empty || q && empty --> (p || q) && empty
												else
													if (ptree->child[0]->type == AND_STA && ptree->child[0]->child[1]->type == EMPTY_EXP && ptree->child[1]->type == AND_STA && ptree->child[1]->child[1]->type == EMPTY_EXP)
													{
														temp1 = new CTreeNode(OR_STA, "", 0);
														temp1->child[0] = new CTreeNode(OR_STA, "", 0);
														temp1->child[1] = new CTreeNode(OR_STA, "", 0);
														temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
														temp1->child[1]->copy_tree(ptree->child[1]->child[0]);
														ptree->child[1]->copy_tree(ptree->child[1]->child[1]);
														ptree->child[0]->copy_tree(temp1);
														ptree->type = AND_STA;

														delete temp1;
													}
				//p && ()r || q && ()r --> (p || q) && ()r
													else
														if (ptree->child[0]->type == AND_STA && ptree->child[0]->child[1]->type == NEXT_STA && ptree->child[1]->type == AND_STA && ptree->child[1]->child[1]->type == NEXT_STA && ptree->child[0]->child[1]->child[0]->compare(ptree->child[1]->child[1]->child[0]))
														{//changed by LXF 2013/08/19 16:16:27 compare1->comapre1
															temp1 = new CTreeNode(OR_STA, "", 0);
															temp1->child[0] = new CTreeNode(OR_STA, "", 0);
															temp1->child[1] = new CTreeNode(OR_STA, "", 0);
															temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
															temp1->child[1]->copy_tree(ptree->child[1]->child[0]);
															ptree->child[1]->copy_tree(ptree->child[1]->child[1]);
															ptree->child[0]->copy_tree(temp1);
															ptree->type = AND_STA;

															delete temp1;
														}
														else
															if (ptree->child[0]->type == OR_STA)
															{
																//p || empty || q || empty --> p || empty || q ;   p || r && empty || q || empty --> p || q || empty
																if (ptree->child[1]->type == EMPTY_EXP)
																{
																	if (POST_findintree(ptree->child[0], ptree->child[1], OR_STA))
																		ptree->copy_tree(ptree->child[0]);
																	else
																	{
																		temp1 = ptree->child[0];
																		while (temp1->type == OR_STA && temp1->child[0]->type == OR_STA)
																		{
																			if (temp1->child[1]->type == AND_STA && temp1->child[1]->child[1]->type == EMPTY_EXP)
																			{
																				temp1->copy_tree(temp1->child[0]);
																				temp1 = NULL;
																				return;
																			}
																			temp1 = temp1->child[0];
																		}
																		if (temp1->type == OR_STA && temp1->child[0]->type != OR_STA)
																		{
																			if (temp1->child[1]->type == AND_STA && temp1->child[1]->child[1]->type == EMPTY_EXP)
																			{
																				temp1->copy_tree(temp1->child[0]);
																				temp1 = NULL;
																				return;
																			}
																			else
																				if (temp1->child[0]->type == AND_STA && temp1->child[0]->child[1]->type == EMPTY_EXP)
																				{
																					temp1->copy_tree(temp1->child[1]);
																					temp1 = NULL;
																					return;
																				}
																		}
																		temp1 = NULL;
																	}
																}//if(ptree->child[1]->type==EMPTY_EXP)

																// p || ()q || r || ()q-->p || ()q || r ;      p || s && ()q || r || ()q --> p || r || ()q 
																else
																	if (ptree->child[1]->type == NEXT_STA)
																	{
																		if (POST_findintree(ptree->child[0], ptree->child[1], OR_STA))
																			ptree->copy_tree(ptree->child[0]);
																		else
																		{
																			temp1 = ptree->child[0];
																			while (temp1->type == OR_STA && temp1->child[0]->type == OR_STA)
																			{
																				if (temp1->child[1]->type == AND_STA && temp1->child[1]->child[1]->type == NEXT_STA && temp1->child[1]->child[1]->child[0]->compare1(ptree->child[1]->child[0]))
																				{
																					temp1->copy_tree(temp1->child[0]);
																					temp1 = NULL;
																					return;
																				}
																				temp1 = temp1->child[0];
																			}
																			if (temp1->type == OR_STA && temp1->child[0]->type != OR_STA)
																			{
																				if (temp1->child[1]->type == AND_STA && temp1->child[1]->child[1]->type == NEXT_STA && temp1->child[1]->child[1]->child[0]->compare1(ptree->child[1]->child[0]))
																				{
																					temp1->copy_tree(temp1->child[0]);
																					temp1 = NULL;
																					return;
																				}
																				else
																					if (temp1->child[0]->type == AND_STA && temp1->child[0]->child[1]->type == NEXT_STA && temp1->child[0]->child[1]->child[0]->compare1(ptree->child[1]->child[0]))
																					{
																						temp1->copy_tree(temp1->child[1]);
																						temp1 = NULL;
																						return;
																					}
																			}
																			temp1 = NULL;
																		}
																	}//if(ptree->child[1]->type==NEXT_STA)

																// p || empty || r || q && empty--> p || empty || r;        p || s && empty || r || q && empty --> p || r || (s ||q) && empty
																	else
																		if (ptree->child[1]->type == AND_STA && ptree->child[1]->child[1]->type == EMPTY_EXP)
																		{
																			if (POST_findintree(ptree->child[0], ptree->child[1]->child[1], OR_STA))
																				ptree->copy_tree(ptree->child[0]);
																			else
																			{
																				temp1 = ptree->child[0];
																				while (temp1->type == OR_STA && temp1->child[0]->type == OR_STA)
																				{
																					if (temp1->child[1]->type == AND_STA && temp1->child[1]->child[1]->type == EMPTY_EXP)
																					{
																						temp2 = new CTreeNode(OR_STA, "", 0);
																						temp2->child[0] = new CTreeNode(OR_STA, "", 0);
																						temp2->child[1] = new CTreeNode(OR_STA, "", 0);
																						temp2->child[0]->copy_tree(temp1->child[1]->child[0]);
																						temp2->child[1]->copy_tree(ptree->child[1]->child[0]);

																						ptree->child[1]->child[0]->copy_tree(temp2);
																						delete temp2;

																						temp1->copy_tree(temp1->child[0]);
																						temp1 = NULL;
																						return;
																					}
																					temp1 = temp1->child[0];

																				}
																				if (temp1->type == OR_STA && temp1->child[0]->type != OR_STA)
																				{
																					if (temp1->child[1]->type == AND_STA && temp1->child[1]->child[1]->type == EMPTY_EXP)
																					{
																						temp2 = new CTreeNode(OR_STA, "", 0);
																						temp2->child[0] = new CTreeNode(OR_STA, "", 0);
																						temp2->child[1] = new CTreeNode(OR_STA, "", 0);
																						temp2->child[0]->copy_tree(temp1->child[1]->child[0]);
																						temp2->child[1]->copy_tree(ptree->child[1]->child[0]);

																						ptree->child[1]->child[0]->copy_tree(temp2);
																						delete temp2;

																						temp1->copy_tree(temp1->child[0]);
																						temp1 = NULL;
																						return;
																					}
																					else
																						if (temp1->child[0]->type == AND_STA && temp1->child[0]->child[1]->type == EMPTY_EXP)
																						{
																							temp2 = new CTreeNode(OR_STA, "", 0);
																							temp2->child[0] = new CTreeNode(OR_STA, "", 0);
																							temp2->child[1] = new CTreeNode(OR_STA, "", 0);
																							temp2->child[0]->copy_tree(temp1->child[0]->child[0]);
																							temp2->child[1]->copy_tree(ptree->child[1]->child[0]);

																							ptree->child[1]->child[0]->copy_tree(temp2);
																							delete temp2;

																							temp1->copy_tree(temp1->child[1]);
																							temp1 = NULL;
																							return;
																						}
																				}
																				temp1 = NULL;
																			}
																		}//if(ptree->child[1]->type==AND_STA && ptree->child[1]->child[1]->type==EMPTY_EXP)

																//p || ()s || r || q && ()s--> p || ()s || r;        p || r && ()s || r || q && ()s --> p || r || (r ||q) && ()s
																		else
																			if (ptree->child[1]->type == AND_STA && ptree->child[1]->child[1]->type == NEXT_STA)
																			{
																				if (POST_findintree(ptree->child[0], ptree->child[1]->child[1], OR_STA))
																					ptree->copy_tree(ptree->child[0]);
																				else
																				{
																					temp1 = ptree->child[0];
																					while (temp1->type == OR_STA && temp1->child[0]->type == OR_STA)
																					{
																						if (temp1->child[1]->type == AND_STA && temp1->child[1]->child[1]->type == NEXT_STA && temp1->child[1]->child[1]->child[0]->compare1(ptree->child[1]->child[1]->child[0]))
																						{
																							temp2 = new CTreeNode(OR_STA, "", 0);
																							temp2->child[0] = new CTreeNode(OR_STA, "", 0);
																							temp2->child[1] = new CTreeNode(OR_STA, "", 0);
																							temp2->child[0]->copy_tree(temp1->child[1]->child[0]);
																							temp2->child[1]->copy_tree(ptree->child[1]->child[0]);

																							ptree->child[1]->child[0]->copy_tree(temp2);
																							delete temp2;

																							temp1->copy_tree(temp1->child[0]);
																							temp1 = NULL;
																							return;
																						}
																						temp1 = temp1->child[0];

																					}
																					if (temp1->type == OR_STA && temp1->child[0]->type != OR_STA)
																					{
																						if (temp1->child[1]->type == AND_STA && temp1->child[1]->child[1]->type == NEXT_STA && temp1->child[1]->child[1]->child[0]->compare1(ptree->child[1]->child[1]->child[0]))
																						{
																							temp2 = new CTreeNode(OR_STA, "", 0);
																							temp2->child[0] = new CTreeNode(OR_STA, "", 0);
																							temp2->child[1] = new CTreeNode(OR_STA, "", 0);
																							temp2->child[0]->copy_tree(temp1->child[1]->child[0]);
																							temp2->child[1]->copy_tree(ptree->child[1]->child[0]);

																							ptree->child[1]->child[0]->copy_tree(temp2);
																							delete temp2;

																							temp1->copy_tree(temp1->child[0]);
																							temp1 = NULL;
																							return;
																						}
																						else
																							if (temp1->child[0]->type == AND_STA && temp1->child[0]->child[1]->type == NEXT_STA && temp1->child[0]->child[1]->child[0]->compare1(ptree->child[1]->child[1]->child[0]))
																							{
																								temp2 = new CTreeNode(OR_STA, "", 0);
																								temp2->child[0] = new CTreeNode(OR_STA, "", 0);
																								temp2->child[1] = new CTreeNode(OR_STA, "", 0);
																								temp2->child[0]->copy_tree(temp1->child[0]->child[0]);
																								temp2->child[1]->copy_tree(ptree->child[1]->child[0]);

																								ptree->child[1]->child[0]->copy_tree(temp2);
																								delete temp2;

																								temp1->copy_tree(temp1->child[1]);
																								temp1 = NULL;
																								return;
																							}
																					}
																					temp1 = NULL;
																				}
																			}//if(ptree->child[1]->type==AND_STA && ptree->child[1]->child[1]->type==NEXT_STA)

															}//if(ptree->child[0]->type==OR_STA)

			}//if(ptree->type==OR_STA && ptree->child[0]!=NULL && ptree->child[1]!=NULL)
	return;
}

void CNFMachine::NNF(CTreeNode * ptree)//处理！，使得！只出现在原子命题前，前提是公式中已经没有->操作符
{
	CTreeNode *temp1, *temp2, *temp3;
	//原子命题p或者原子命题的非!p或true或fasle直接不变

	//!true --> false
	if (ptree->type == NEGATION_STA && ptree->child[0] != NULL && ptree->child[0]->type == TRUE_EXP)
	{
		temp1 = new CTreeNode(FALSE_EXP, "FALSE", 0);
		ptree->copy_tree(temp1);
		delete temp1;
	}

	//!false --> true
	else
		if (ptree->type == NEGATION_STA && ptree->child[0] != NULL && ptree->child[0]->type == FALSE_EXP)
		{
			temp1 = new CTreeNode(TRUE_EXP, "TRUE", 0);
			ptree->copy_tree(temp1);
			delete temp1;
		}

	//!!P-->处理P
		else
			if (ptree->type == NEGATION_STA && ptree->child[0] != NULL && ptree->child[0]->type == NEGATION_STA)
			{
				ptree->copy_tree(ptree->child[0]->child[0]);
				NNF(ptree);
			}

	//P &&　Q -->处理P 和 Q
			else
				if (ptree->type == AND_STA)
				{
					NNF(ptree->child[0]);
					NNF(ptree->child[1]);
				}

	//P || Q -->处理P 和 Q
				else
					if (ptree->type == OR_STA)
					{
						NNF(ptree->child[0]);
						NNF(ptree->child[1]);
					}

	//!(P && Q) -->处理 !p 和 !Q
					else
						if (ptree->type == NEGATION_STA && ptree->child[0] != NULL && ptree->child[0]->type == AND_STA)
						{
							temp2 = new CTreeNode(NEGATION_STA, "", 0);
							temp2->child[0] = new CTreeNode(OR_STA, "", 0);
							temp2->child[0]->copy_tree(ptree->child[0]->child[0]);

							temp3 = new CTreeNode(NEGATION_STA, "", 0);
							temp3->child[0] = new CTreeNode(OR_STA, "", 0);
							temp3->child[0]->copy_tree(ptree->child[0]->child[1]);

							temp1 = new CTreeNode(OR_STA, "", 0);
							temp1->child[0] = new CTreeNode(OR_STA, "", 0);
							temp1->child[1] = new CTreeNode(OR_STA, "", 0);
							temp1->child[0]->copy_tree(temp2);
							temp1->child[1]->copy_tree(temp3);

							ptree->copy_tree(temp1);
							delete temp2;
							delete temp3;
							delete temp1;

							NNF(ptree->child[0]);
							NNF(ptree->child[1]);
						}

	//!(P || Q) -->处理 !P 和 !Q
						else
							if (ptree->type == NEGATION_STA && ptree->child[0] != NULL && ptree->child[0]->type == OR_STA)
							{
								temp2 = new CTreeNode(NEGATION_STA, "", 0);
								temp2->child[0] = new CTreeNode(OR_STA, "", 0);
								temp2->child[0]->copy_tree(ptree->child[0]->child[0]);

								temp3 = new CTreeNode(NEGATION_STA, "", 0);
								temp3->child[0] = new CTreeNode(OR_STA, "", 0);
								temp3->child[0]->copy_tree(ptree->child[0]->child[1]);

								temp1 = new CTreeNode(AND_STA, "", 0);
								temp1->child[0] = new CTreeNode(AND_STA, "", 0);
								temp1->child[1] = new CTreeNode(AND_STA, "", 0);
								temp1->child[0]->copy_tree(temp2);
								temp1->child[1]->copy_tree(temp3);

								ptree->copy_tree(temp1);
								delete temp2;
								delete temp3;
								delete temp1;

								NNF(ptree->child[0]);
								NNF(ptree->child[1]);
							}
}



/*ptree无蕴涵，并且是NNF形式*/
/*求公式的析取范式，返回值是一个string集合的集合*/
s_set_set CNFMachine::DNF_P(CTreeNode * ptree)
{
	s_set_set endset;


	//false返回空集
	if (ptree->type == FALSE_EXP)
	{
		endset.clear();
		return endset;
	}

	//原子命题p或true直接为{{p/true}}
	else
		if (ptree->type == IDENT_EXP || ptree->type == TRUE_EXP)
		{
			s_set temp;
			temp.insert(ptree->name_str.c_str());
			endset.insert(temp);
			//add
			temp.clear();
			return endset;
		}

	//原子命题的非!p直接为{{!p}}
		else
			if (ptree->type == NEGATION_STA && ptree->child[0]->type == IDENT_EXP)
			{
				s_set temp;
				string ss = "";
				ss += "!";
				ss += ptree->child[0]->name_str.c_str();
				temp.insert(ss);
				endset.insert(temp);
				//add
				temp.clear();
				return endset;
			}

	//P || Q时结果是DNF(P)和DNF(Q)的并集
			else
				if (ptree->type == OR_STA)
				{
					s_set_set temp1 = DNF_P(ptree->child[0]);
					s_set_set temp2 = DNF_P(ptree->child[1]);
					string ss = "TRUE";
					s_set temp;
					temp.insert(ss);

					//外层有true直接将并集设为true
					if (temp1.size() == 1 && temp1.find(temp) != temp1.end() || temp2.size() == 1 && temp2.find(temp) != temp2.end())
					{
						endset.insert(temp);
						//add clear
						temp1.clear();
						temp2.clear();
						temp.clear();
						return endset;
					}
					//有p || !p时，并集也为true
					else
						if (temp1.size() <= temp2.size())  //从规模小的集合中比较更省时
						{
							set<s_set>::iterator i1 = temp1.begin();
							while (i1 != temp1.end())
							{
								if ((*i1).size() == 1)
								{
									set<string>::iterator i2 = (*i1).begin();
									//如果temp1中有一个p，就查找temp2中是否有!p
									if ((*i2)[0] != '!')
									{
										string tt;
										tt += "!";
										tt += *i2;
										s_set set1;
										set1.insert(tt);
										if (temp2.find(set1) != temp2.end())
										{
											endset.insert(temp);
											//add clear
											set1.clear();
											temp1.clear();
											temp2.clear();
											temp.clear();
											return endset;
										}
									}
									else
										if ((*i2)[0] == '!')
										{
											string tt1;
											tt1 = *i2;
											string tt = tt1.substr(1,tt1.length() - 1);
											//tt.Delete(0, 1);
											s_set set1;
											set1.insert(tt);
											if (temp2.find(set1) != temp2.end())
											{
												endset.insert(temp);
												//add clear
												set1.clear();
												temp1.clear();
												temp2.clear();
												temp.clear();
												return endset;
											}
										}
								}//if((*i1).size()==1)
								i1++;
							}//while(i1!=temp1.end())
						}//if(temp1.size()<=temp2.size())

						else
							if (temp1.size()>temp2.size())
							{
								set<s_set>::iterator i1 = temp2.begin();
								while (i1 != temp2.end())
								{
									if ((*i1).size() == 1)
									{
										set<string>::iterator i2 = (*i1).begin();
										//如果temp1中有一个p，就查找temp2中是否有!p
										if ((*i2)[0] != '!')
										{
											string tt;
											tt += "!";
											tt += *i2;
											s_set set1;
											set1.insert(tt);
											if (temp1.find(set1) != temp1.end())
											{
												endset.insert(temp);
												//add clear
												set1.clear();
												temp1.clear();
												temp2.clear();
												temp.clear();
												return endset;
											}
										}
										else
											if ((*i2)[0] == '!')
											{
												string tt1;
												tt1 = *i2;
												string tt = tt1.substr(1, tt1.length() - 1);
												/*
												string tt;
												tt = *i2;
												tt.Delete(0, 1);
												*/
												s_set set1;
												set1.insert(tt);
												if (temp1.find(set1) != temp1.end())
												{
													endset.insert(temp);
													//add clear
													set1.clear();
													temp1.clear();
													temp2.clear();
													temp.clear();
													return endset;
												}
											}
									}//if((*i1).size()==1)
									i1++;
								}//while(i1!=temp2.end())	  
							}//if(temp1.size()>temp2.size())

					//前面几种都不满足的情况下，就合并temp1和temp2
					std::set_union(temp1.begin(), temp1.end(), temp2.begin(), temp2.end(), inserter(endset, endset.begin()));
					//add clear
					temp1.clear();
					temp2.clear();
					return endset;
				}//if(ptree->type==OR_STA)
	//    else 
	// 	   if (ptree->type==UNTIL_STA)
	// 	   {
	// 		   s_set_set temp1;
	// 		   s_set temp2;
	// 		  string utl="";
	// 		   utl+=
	// 		   temp1.
	// 		   return CONJ()
	// 	   }
				else
					if (ptree->type == AND_STA)
						return CONJ(DNF_P(ptree->child[0]), DNF_P(ptree->child[1]));
}

/*前置条件：set1，set2均为集合的集合*/
/*后置条件：返回值是集合的集合*/
s_set_set CNFMachine::CONJ(s_set_set set1, s_set_set set2)
{
	s_set_set endset;

	//set1和set2至少有一个为空时，结果即为空
	if (set1.size() == 0 || set2.size() == 0)
	{
		endset.clear();
		return endset;
	}

	//当set1为{set11,set12,……,set1m}时，分解set1
	else
		if (set1.size()>1)
		{
			set<s_set>::iterator i1 = set1.begin();
			while (i1 != set1.end())
			{
				s_set_set temp1, temp2, aimtemp;
				temp1.insert(*i1);
				temp2 = CONJ(temp1, set2);
				std::set_union(endset.begin(), endset.end(), temp2.begin(), temp2.end(), inserter(aimtemp, aimtemp.begin()));
				endset = aimtemp;
				//add clear
				temp1.clear();
				temp2.clear();
				aimtemp.clear();
				i1++;
			}
			return endset;
		}

	//当set2为{set21,set22,……,set2n}时，分解set2
		else
			if (set2.size()>1)
			{
				set<s_set>::iterator i1 = set2.begin();
				while (i1 != set2.end())
				{
					s_set_set temp1, temp2, aimtemp;
					temp1.insert(*i1);
					temp2 = CONJ(set1, temp1);
					std::set_union(endset.begin(), endset.end(), temp2.begin(), temp2.end(), inserter(aimtemp, aimtemp.begin()));
					endset = aimtemp;
					//add clear
					temp1.clear();
					temp2.clear();
					aimtemp.clear();
					i1++;
				}
				return endset;
			}

	//当set1和set2都是一个集合元素时，分情况合并
			else
				if (set1.size() == 1 && set2.size() == 1)
				{
					set<s_set>::iterator i1 = set1.begin();
					set<s_set>::iterator i2 = set2.begin();
					string tt;
					tt = "TRUE";
					//set1中如果有true，则结果为set2
					if ((*i1).size() == 1 && (*i1).find(tt) != (*i1).end())
					{
						endset = set2;
						return endset;
					}

					//set2中如果有true，则结果为set1
					else
						if ((*i2).size() == 1 && (*i2).find(tt) != (*i2).end())
						{
							endset = set1;
							return endset;
						}

					//一个集合有p，另一个集合有!p，则结果为空 ，从较小集合开始遍历，更省时间
						else
							if ((*i1).size() <= (*i2).size())
							{
								set<string>::iterator i3 = (*i1).begin();
								while (i3 != (*i1).end())
								{
									if ((*i3)[0] != '!')//s10中有p，则看s20中是否有!p
									{
										string ss;
										ss += "!";
										ss += (*i3);
										if ((*i2).find(ss) != (*i2).end())
										{
											endset.clear();
											return endset;
										}
									}

									else
										if ((*i3)[0] == '!')//s10中有!p,则看s20中是否有p
										{
											string tt1;
											tt1 = *i3;
											string ss = tt1.substr(1, tt1.length() - 1);
											/*
											string ss;
											ss = (*i3);
											ss.Delete(0, 1);
											*/
											if ((*i2).find(ss) != (*i2).end())
											{
												endset.clear();
												return endset;
											}
										}
									i3++;
								}
							}

							else
								if ((*i1).size()>(*i2).size())
								{
									set<string>::iterator i3 = (*i2).begin();
									while (i3 != (*i2).end())
									{
										if ((*i3)[0] != '!')//s10中有p，则看s20中是否有!p
										{
											string ss;
											ss += "!";
											ss += (*i3);
											if ((*i1).find(ss) != (*i1).end())
											{
												endset.clear();
												return endset;
											}
										}

										else
											if ((*i3)[0] == '!')//s10中有!p,则看s20中是否有p
											{
												string tt1;
												tt1 = *i3;
												string ss = tt1.substr(1, tt1.length() - 1);
												/*
												string ss;
												ss = (*i3);
												ss.Delete(0, 1);
												*/
												if ((*i1).find(ss) != (*i1).end())
												{
													endset.clear();
													return endset;
												}
											}
										i3++;
									}
								}
					s_set aimtemp;
					std::set_union((*i1).begin(), (*i1).end(), (*i2).begin(), (*i2).end(), inserter(aimtemp, aimtemp.begin()));
					endset.insert(aimtemp);
					//add clear
					aimtemp.clear();
					return endset;
				}
}

void CNFMachine::cons_tree(s_set_set temp, CTreeNode *aimtree)//从集合temp构造树结构
{
	//DNF结果为空集表示化简为false
	if (temp.size() == 0)
	{
		CTreeNode *t_tree;
		t_tree = new CTreeNode(FALSE_EXP, "FALSE", 0);
		aimtree->copy_tree(t_tree);
		delete t_tree;
		return;
	}
	//DNF结果不为空，则需要构造ortree
	set<s_set>::iterator i1 = temp.begin();
	CTreeNode *ortree, *ortemp;
	ortree = new CTreeNode(OR_STA, "", 0);
	ortemp = ortree;

	while (i1 != temp.end())
	{
		set<string>::iterator i2 = (*i1).begin();
		CTreeNode *andtree, *andtemp;
		andtree = new CTreeNode(AND_STA, "", 0);
		andtemp = andtree;

		while (i2 != (*i1).end())
		{
			if ((*i2)[0] != '!')
			{
				if ((*i2) == "TRUE")
				{
					andtree->child[0] = new CTreeNode(AND_STA, "", 0);
					andtree->child[1] = new CTreeNode(TRUE_EXP, "TRUE", 0);
					andtree = andtree->child[0];
				}
				else
				{
					andtree->child[0] = new CTreeNode(AND_STA, "", 0);
					andtree->child[1] = new CTreeNode(IDENT_EXP, "", 0);
					andtree->child[1]->name_str = (*i2);
					andtree = andtree->child[0];
				}
			}//if((*i2)[0]!='!')
			else
				if ((*i2)[0] == '!')
				{
					string tt1;
					tt1 = *i2;
					string ss = tt1.substr(1, tt1.length() - 1);
					/*
					string ss;
					ss = (*i2);
					ss.Delete(0, 1);
					*/
					andtree->child[0] = new CTreeNode(AND_STA, "", 0);
					andtree->child[1] = new CTreeNode(NEGATION_STA, "", 0);
					andtree->child[1]->child[0] = new CTreeNode(IDENT_EXP, "", 0);
					andtree->child[1]->child[0]->name_str = (ss);
					andtree = andtree->child[0];
				}//if((*i2)[0]=='!')
			i2++;
		}//while(i2!=(*i1).end())

		//delete the last "and" node of the andtree
		andtree = andtemp;
		while (andtemp != NULL && andtemp->child[0] != NULL && andtemp->child[0]->child[0] != NULL)
			andtemp = andtemp->child[0];
		andtemp->copy_tree(andtemp->child[1]);

		andtemp = NULL;

		ortree->child[0] = new CTreeNode(OR_STA, "", 0);
		ortree->child[1] = new CTreeNode(AND_STA, "", 0);
		ortree->child[1]->copy_tree(andtree);

		delete andtree;
		ortree = ortree->child[0];
		i1++;
	}//while(i1!=temp.end())

	ortree = ortemp;

	//delete the last "or" node of the ortree
	while (ortemp != NULL && ortemp->child[0] != NULL && ortemp->child[0]->child[0] != NULL)
		ortemp = ortemp->child[0];
	ortemp->copy_tree(ortemp->child[1]);

	ortemp = NULL;
	aimtree->copy_tree(ortree);
	delete ortree;
}

void CNFMachine::POST(CTreeNode * ptree)
{

	COMB(ptree);//将公式中的empty以及()后面相同的那些项前面的状态公式合并
	// 	string str="";
	// 	 showout="";
	//  	str=show(ptree);	
	NNF(ptree);//处理！，使得！只出现在原子命题前，前提是公式中已经没有->操作符

	/*接下来是将所有的empty或者()前面的或者单独的那些状态公式用集合的方式表示，化成相应的析取范式*/

	if (ptree->type == AND_STA && (ptree->child[1]->type == EMPTY_EXP || ptree->child[1]->type == NEXT_STA))
	{
		s_set_set temp;
		temp = DNF_P(ptree->child[0]);//DNF_P:求公式的析取范式，返回值是一个string集合的集合
		if (temp.size() == 0)
		{
			CTreeNode *t_tree;
			t_tree = new CTreeNode(FALSE_EXP, "FALSE", 0);
			ptree->copy_tree(t_tree);
			delete t_tree;
			return;
		}
		cons_tree(temp, ptree->child[0]);//cons_tree:从集合temp构造树结构
		temp.clear();
	}
	else
		if (ptree->type == AND_STA && ptree->child[1]->type != EMPTY_EXP && ptree->child[1]->type != NEXT_STA)
		{
			s_set_set temp;
			temp = DNF_P(ptree);
			if (temp.size() == 0)
			{
				CTreeNode *t_tree;
				t_tree = new CTreeNode(FALSE_EXP, "FALSE", 0);
				ptree->copy_tree(t_tree);
				delete t_tree;
				return;
			}
			cons_tree(temp, ptree);
			temp.clear();
		}
		else
			if (ptree->type == OR_STA)
			{
				CTreeNode *t_tree;
				t_tree = ptree;

				while (t_tree->type == OR_STA && t_tree->child[0]->type == OR_STA)
				{
					int ii = 0;
					if (t_tree->child[1]->type == AND_STA && (t_tree->child[1]->child[1]->type == EMPTY_EXP || t_tree->child[1]->child[1]->type == NEXT_STA))
					{
						s_set_set temp;
						temp = DNF_P(t_tree->child[1]->child[0]);
						if (temp.size() == 0)
						{
							t_tree->copy_tree(t_tree->child[0]);
							ii = 1;
						}
						else
						{
							cons_tree(temp, t_tree->child[1]->child[0]);
							temp.clear();
						}
					}
					else
						if (t_tree->child[1]->type == AND_STA && t_tree->child[1]->child[1]->type != EMPTY_EXP && t_tree->child[1]->child[1]->type != NEXT_STA)
						{
							s_set_set temp;
							temp = DNF_P(t_tree->child[1]);
							if (temp.size() == 0)
							{
								t_tree->copy_tree(t_tree->child[0]);
								ii = 1;
							}
							else
							{
								cons_tree(temp, t_tree->child[1]);
								temp.clear();
							}
						}
					if (ii == 0)
						t_tree = t_tree->child[0];
				}//while(t_tree->type==OR_STA && t_tree->child[0]->type==OR_STA)
				if (t_tree->type == OR_STA && t_tree->child[0]->type != OR_STA)
				{
					int has_done = 0;
					if (t_tree->child[1]->type == AND_STA && (t_tree->child[1]->child[1]->type == EMPTY_EXP || t_tree->child[1]->child[1]->type == NEXT_STA))
					{
						s_set_set temp;
						temp = DNF_P(t_tree->child[1]->child[0]);
						if (temp.size() == 0)
						{
							t_tree->copy_tree(t_tree->child[0]);
							has_done = 1;
						}
						else
						{
							cons_tree(temp, t_tree->child[1]->child[0]);
							temp.clear();
						}
					}
					else
						if (t_tree->child[1]->type == AND_STA && t_tree->child[1]->child[1]->type != EMPTY_EXP && t_tree->child[1]->child[1]->type != NEXT_STA)
						{
							s_set_set temp;
							temp = DNF_P(t_tree->child[1]);
							if (temp.size() == 0)
							{
								t_tree->copy_tree(t_tree->child[0]);
								has_done = 1;
							}
							else
							{
								cons_tree(temp, t_tree->child[1]);
								temp.clear();
							}
						}
					if (has_done == 0)
					{
						if (t_tree->child[0]->type == AND_STA && (t_tree->child[0]->child[1]->type == EMPTY_EXP || t_tree->child[0]->child[1]->type == NEXT_STA))
						{
							s_set_set temp;
							temp = DNF_P(t_tree->child[0]->child[0]);
							if (temp.size() == 0)
								t_tree->copy_tree(t_tree->child[1]);
							else
							{
								cons_tree(temp, t_tree->child[0]->child[0]);
								temp.clear();
							}
						}
						else
							if (t_tree->child[0]->type == AND_STA && t_tree->child[0]->child[1]->type != EMPTY_EXP && t_tree->child[0]->child[1]->type != NEXT_STA)
							{
								s_set_set temp;
								temp = DNF_P(t_tree->child[0]);
								if (temp.size() == 0)
									t_tree->copy_tree(t_tree->child[1]);
								else
								{
									cons_tree(temp, t_tree->child[0]);
									temp.clear();
								}
							}
					}//if(has_done==0
					else
						if (has_done == 1)
						{
							if (t_tree->type == AND_STA && (t_tree->child[1]->type == EMPTY_EXP || t_tree->child[1]->type == NEXT_STA))
							{
								s_set_set temp;
								temp = DNF_P(t_tree->child[0]);
								if (temp.size() == 0)
								{
									CTreeNode *temp1;
									temp1 = new CTreeNode(FALSE_EXP, "FALSE", 0);
									t_tree->copy_tree(temp1);
									delete temp1;
									//if the ptree is not false ,delete the last false of the ptree
									t_tree = NULL;
									if (ptree->type == OR_STA)
									{
										t_tree = ptree;
										while (t_tree->type == OR_STA && t_tree->child[0]->type == OR_STA)
											t_tree = t_tree->child[0];
										if (t_tree->type == OR_STA && t_tree->child[0]->type == FALSE_EXP)
											t_tree->copy_tree(t_tree->child[1]);
									}
									t_tree = NULL;
								}
								else
								{
									cons_tree(temp, t_tree->child[0]);
									temp.clear();
								}
							}
							else
								if (t_tree->type == AND_STA && t_tree->child[1]->type != EMPTY_EXP && t_tree->child[1]->type != NEXT_STA)
								{
									s_set_set temp;
									temp = DNF_P(t_tree);
									if (temp.size() == 0)
									{
										CTreeNode *temp1;
										temp1 = new CTreeNode(FALSE_EXP, "FALSE", 0);
										t_tree->copy_tree(temp1);
										delete temp1;
										//if the ptree is not false ,delete the last false of the ptree
										t_tree = NULL;
										if (ptree->type == OR_STA)
										{
											t_tree = ptree;
											while (t_tree->type == OR_STA && t_tree->child[0]->type == OR_STA)
												t_tree = t_tree->child[0];
											if (t_tree->type == OR_STA && t_tree->child[0]->type == FALSE_EXP)
												t_tree->copy_tree(t_tree->child[1]);
										}
										t_tree = NULL;
									}
									else
									{
										cons_tree(temp, t_tree);
										temp.clear();
									}
								}
						}//if(has_done==1)
				}//if(t_tree->type==OR_STA && t_tree->child[0]->type!=OR_STA)
			}

} //POST


int CNFMachine::POST_findintree(CTreeNode * ptree, CTreeNode * target, NODETYPE ntype)
{
	if (target->type == NEXT_STA)
	{
		if (ptree->child[0]->type == NEXT_STA && target->child[0]->compare1(ptree->child[0]->child[0]))
		{
			return 1;
		}
		else
			if (ptree->child[1]->type == NEXT_STA && target->child[0]->compare1(ptree->child[1]->child[0]))
			{
				return 1;
			}

	}
	else
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
	}
	if (ptree->child[0] != NULL && ptree->child[0]->type == ntype)
	{
		if (POST_findintree(ptree->child[0], target, ntype))
		{
			return 1;
		}
	}
	if (ptree->child[1] != NULL && ptree->child[1]->type == ntype)
	{
		if (POST_findintree(ptree->child[1], target, ntype))
		{
			return 1;
		}
	}
	if (ptree->child[2] != NULL && ptree->child[2]->type == ntype)
	{
		if (POST_findintree(ptree->child[2], target, ntype))
		{
			return 1;
		}
	}
	return 0;

}



void CNFMachine::PRJ_chop(CTreeNode * ptree)
{
	CTreeNode *temp1, *temp2;
	temp1 = new CTreeNode(CHOP_STA, "", 0);
	temp1->child[0] = new CTreeNode(AND_STA, "", 0);
	temp1->child[0]->copy_tree(ptree->child[0]);

	if (ptree->child[1]->child[1] != NULL)
	{
		temp2 = new CTreeNode(PROJECTION_STA, "", 0);
		temp2->child[0] = new CTreeNode(AND_STA, "", 0);
		temp2->child[0]->copy_tree(ptree->child[1]->child[0]);
		temp2->child[1] = new CTreeNode(AND_STA, "", 0);
		temp2->child[1]->copy_tree(ptree->child[1]->child[1]);
		temp2->child[2] = new CTreeNode(AND_STA, "", 0);
		temp2->child[2]->copy_tree(ptree->child[2]);
		temp1->child[1] = new CTreeNode(AND_STA, "", 0);
		temp1->child[1]->copy_tree(temp2);
		ptree->copy_tree(temp1);
		delete temp2;

	}
	else
	{
		////////////////  change   to  /////////////////////
		if (ptree->child[1]->child[0] != NULL)
		{
			temp1->child[1] = new CTreeNode(AND_STA, "", 0);
			temp1->child[1]->copy_tree(ptree->child[1]->child[0]);
		}
		ptree->copy_tree(temp1);
		///////////////////////////////////////////////////
	}
	if (temp1->child[1]->type == PROJECTION_STA)
	{
		delete temp1;

		PRJ_chop(ptree->child[1]);
	}
	else
		delete temp1;
}

void CNFMachine::PRJ(CTreeNode * ptree)
{
	CTreeNode *temp1, *temp2, *temp3, *temp4, *temp5, *temp6;
	int done;
	done = 0;
	//(false,p)prj q=false
	if (done == 0 && ptree->child[0]->type == FALSE_EXP)
	{
		ptree->copy_tree(ptree->child[0]);
		done = 1;
	}
	//(p,false)prj q=false
	temp1 = new CTreeNode(FALSE_EXP, "FALSE", 0);
	if (done == 0 && ptree->child[1] != NULL && POST_findintree(ptree->child[1], temp1, PROJECTION_STA))
	{
		ptree->copy_tree(temp1);
		done = 1;
	}
	delete temp1;
	//empty prj empty --> empty
	if (done == 0 && ptree->child[0]->type == EMPTY_EXP && ptree->child[1] == NULL && ptree->child[2]->type == EMPTY_EXP)
	{
		ptree->type = EMPTY_EXP;
		ptree->name_str = "EMPTY";
		done = 1;
	}

	//empty prj Q -->Q
	if (done == 0 && ptree->child[0]->type == EMPTY_EXP && ptree->child[1] == NULL && ptree->child[2]->type != EMPTY_EXP)
	{
		ptree->copy_tree(ptree->child[2]);
		NF(ptree);
		done = 1;
	}

	//P prj empty --> P
	if (done == 0 && ptree->child[0]->type != EMPTY_EXP && ptree->child[1] == NULL && ptree->child[2]->type == EMPTY_EXP)
	{
		ptree->copy_tree(ptree->child[0]);
		NF(ptree);
		done = 1;
	}

	if (done == 0 && ptree->child[0] != NULL && ptree->child[1] == NULL && ptree->child[2] != NULL && ptree->child[2]->type == TRUE_EXP)
	{
		ptree->copy_tree(ptree->child[0]);
		NF(ptree);
		done = 1;
	}
	//(empty,P2...Pm) prj Q  --> (P2,...Pm) prj Q
	if (done == 0 && ptree->child[0]->type == EMPTY_EXP && ptree->child[1] != NULL)
	{
		int de_1 = 0;
		temp1 = new CTreeNode(PROJECTION_STA, "", 0);
		temp1->child[0] = new CTreeNode(AND_STA, "", 0);
		temp1->child[0]->copy_tree(ptree->child[1]->child[0]);
		if (ptree->child[1]->child[1] != NULL)
		{
			temp1->child[1] = new CTreeNode(AND_STA, "", 0);
			temp1->child[1]->copy_tree(ptree->child[1]->child[1]);
			de_1 = 1;
		}
		temp1->child[2] = new CTreeNode(AND_STA, "", 0);
		temp1->child[2]->copy_tree(ptree->child[2]);
		ptree->copy_tree(temp1);
		delete temp1;

		PRJ(ptree);
		done = 1;
	}
	//(p,q)prj false=false
	if (done == 0 && ptree->child[2]->type == FALSE_EXP)
	{
		ptree->copy_tree(ptree->child[2]);
		done = 1;
	}

	//(P1,P2....Pm) prj (Q1 || Q2) --> (P1,P2,...Pm) prj Q1 || (P1,P2,...Pm) prj Q2
	if (done == 0 && ptree->child[2]->type == OR_STA)
	{
		int de_1_1 = 0, de_2_1 = 0;
		temp1 = new CTreeNode(PROJECTION_STA, "", 0);
		temp4 = new CTreeNode(AND_STA, "", 0);
		temp5 = new CTreeNode(AND_STA, "", 0);
		temp4->copy_tree(ptree);
		temp5->copy_tree(ptree->child[2]->child[0]);
		temp1->child[0] = new CTreeNode(AND_STA, "", 0);
		temp1->child[0]->copy_tree(temp4->child[0]);
		if (temp4->child[1] != NULL)
		{
			temp1->child[1] = new CTreeNode(AND_STA, "", 0);
			temp1->child[1]->copy_tree(temp4->child[1]);
			de_1_1 = 1;
		}
		temp1->child[2] = new CTreeNode(AND_STA, "", 0);
		temp1->child[2]->copy_tree(temp5);

		temp2 = new CTreeNode(PROJECTION_STA, "", 0);
		temp3 = new CTreeNode(AND_STA, "", 0);
		temp6 = new CTreeNode(AND_STA, "", 0);
		temp3->copy_tree(ptree);
		temp6->copy_tree(ptree->child[2]->child[1]);
		temp2->child[0] = new CTreeNode(AND_STA, "", 0);
		temp2->child[0]->copy_tree(temp3->child[0]);
		if (temp3->child[1] != NULL)
		{
			temp2->child[1] = new CTreeNode(AND_STA, "", 0);
			temp2->child[1]->copy_tree(temp3->child[1]);
			de_2_1 = 1;
		}
		temp2->child[2] = new CTreeNode(AND_STA, "", 0);
		temp2->child[2]->copy_tree(temp6);

		ptree->type = OR_STA;
		ptree->child[0]->copy_tree(temp1);
		if (ptree->child[1] == NULL)
		{
			ptree->child[1] = new CTreeNode(AND_STA, "", 0);
			ptree->child[1]->copy_tree(temp2);
		}
		else
		{
			ptree->child[1]->copy_tree(temp2);
		}
		ptree->child[2] = NULL;
		delete temp1;
		delete temp2;
		delete temp3;
		delete temp4;
		delete temp5;
		delete temp6;


		PRJ(ptree->child[0]);
		PRJ(ptree->child[1]);
		done = 1;
	}

	//(P1 || P1', ... ) prj Q --> (P1,...) prj Q || (P1',...) prj Q
	if (done == 0 && ptree->child[0]->type == OR_STA)
	{
		int de_1_1 = 0, de_2_1 = 0;
		temp1 = new CTreeNode(PROJECTION_STA, "", 0);
		temp1->child[0] = new CTreeNode(AND_STA, "", 0);
		temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
		if (ptree->child[1] != NULL)
		{
			temp1->child[1] = new CTreeNode(AND_STA, "", 0);
			temp1->child[1]->copy_tree(ptree->child[1]);
			de_1_1 = 1;
		}
		temp1->child[2] = new CTreeNode(AND_STA, "", 0);
		temp1->child[2]->copy_tree(ptree->child[2]);

		temp2 = new CTreeNode(PROJECTION_STA, "", 0);
		temp2->child[0] = new CTreeNode(AND_STA, "", 0);
		temp2->child[0]->copy_tree(ptree->child[0]->child[1]);
		if (ptree->child[1] != NULL)
		{
			temp2->child[1] = new CTreeNode(AND_STA, "", 0);
			temp2->child[1]->copy_tree(ptree->child[1]);
			de_2_1 = 1;
		}
		temp2->child[2] = new CTreeNode(AND_STA, "", 0);
		temp2->child[2]->copy_tree(ptree->child[2]);

		ptree->type = OR_STA;
		ptree->child[0]->copy_tree(temp1);
		if (ptree->child[1] == NULL)
		{
			ptree->child[1] = new CTreeNode(AND_STA, "", 0);
			ptree->child[1]->copy_tree(temp2);
		}
		else
		{
			ptree->child[1]->copy_tree(temp2);
		}
		ptree->child[2] = NULL;
		delete temp1;
		delete temp2;

		PRJ(ptree->child[0]);
		PRJ(ptree->child[1]);
		done = 1;
	}

	//(P1,P2....Pm) prj empty --> P1;(P2;...Pm)
	if (done == 0 && ptree->child[1] != NULL && ptree->child[2]->type == EMPTY_EXP)
	{
		int de_1 = 0;
		temp1 = new CTreeNode(CHOP_STA, "", 0);
		temp1->child[0] = new CTreeNode(AND_STA, "", 0);
		temp1->child[0]->copy_tree(ptree->child[0]);
		if (ptree->child[1]->child[1] != NULL)
		{
			temp2 = new CTreeNode(PROJECTION_STA, "", 0);
			temp2->child[0] = new CTreeNode(AND_STA, "", 0);
			temp2->child[0]->copy_tree(ptree->child[1]->child[0]);
			temp2->child[1] = new CTreeNode(AND_STA, "", 0);
			temp2->child[1]->copy_tree(ptree->child[1]->child[1]);
			temp2->child[2] = new CTreeNode(AND_STA, "", 0);
			temp2->child[2]->copy_tree(ptree->child[2]);
			temp1->child[1] = new CTreeNode(AND_STA, "", 0);
			temp1->child[1]->copy_tree(temp2);
			de_1 = 1;
			ptree->copy_tree(temp1);
			delete temp2;

		}
		else
		{
			if (ptree->child[1]->child[0] != NULL)
			{
				temp1->child[1] = new CTreeNode(AND_STA, "", 0);
				temp1->child[1]->copy_tree(ptree->child[1]->child[0]);
				de_1 = 1;
			}
			ptree->copy_tree(temp1);
		}

		if (temp1->child[1]->type == PROJECTION_STA)
		{
			PRJ_chop(ptree->child[1]);
		}
		delete temp1;

		CHOP(ptree);
		done = 1;
	}

	//@P prj @Q --> ()(P ; Q)
	if (done == 0 && ptree->child[0]->type == NEXT_STA && ptree->child[1] == NULL && ptree->child[2]->type == NEXT_STA)
	{
		temp1 = new CTreeNode(CHOP_STA, "", 0);
		temp1->child[0] = new CTreeNode(AND_STA, "", 0);
		temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
		temp1->child[1] = new CTreeNode(AND_STA, "", 0);
		temp1->child[1]->copy_tree(ptree->child[2]->child[0]);
		ptree->type = NEXT_STA;
		ptree->child[0]->copy_tree(temp1);
		delete temp1;

		done = 1;
	}

	//(@P1,P2...Pm) prj @Q --> ()(P1; ((P2,...Pm) prj Q))
	if (done == 0 && ptree->child[0]->type == NEXT_STA && ptree->child[1] != NULL && ptree->child[2]->type == NEXT_STA)
	{
		int de_3_1 = 0;
		temp1 = new CTreeNode(NEXT_STA, "", 0);
		temp2 = new CTreeNode(CHOP_STA, "", 0);
		temp3 = new CTreeNode(PROJECTION_STA, "", 0);

		temp3->child[0] = new CTreeNode(AND_STA, "", 0);
		temp3->child[0]->copy_tree(ptree->child[1]->child[0]);
		if (ptree->child[1]->child[1] != NULL)
		{
			temp3->child[1] = new CTreeNode(AND_STA, "", 0);
			temp3->child[1]->copy_tree(ptree->child[1]->child[1]);
			de_3_1 = 1;
		}
		temp3->child[2] = new CTreeNode(AND_STA, "", 0);
		temp3->child[2]->copy_tree(ptree->child[2]->child[0]);

		temp2->child[0] = new CTreeNode(AND_STA, "", 0);
		temp2->child[0]->copy_tree(ptree->child[0]->child[0]);
		temp2->child[1] = new CTreeNode(AND_STA, "", 0);
		temp2->child[1]->copy_tree(temp3);

		temp1->child[0] = new CTreeNode(AND_STA, "", 0);
		temp1->child[0]->copy_tree(temp2);

		ptree->copy_tree(temp1);
		delete temp1;
		delete temp2;
		delete temp3;

		done = 1;
	}

	//(w && P1,p2...Pm) prj Q --> w && PRJ((P1,P2,...Pm) prj Q)
	if (done == 0 && ptree->child[0]->type == AND_STA)
	{
		SFA = 1;
		SF(ptree->child[0]->child[0]);
		if (SFA)
		{
			int de_2_1 = 0;
			temp1 = new CTreeNode(AND_STA, "", 0);
			temp2 = new CTreeNode(PROJECTION_STA, "", 0);


			temp2->child[0] = new CTreeNode(AND_STA, "", 0);
			temp2->child[0]->copy_tree(ptree->child[0]->child[1]);
			if (ptree->child[1] != NULL)
			{
				temp2->child[1] = new CTreeNode(AND_STA, "", 0);
				temp2->child[1]->copy_tree(ptree->child[1]);
				de_2_1 = 1;
			}
			temp2->child[2] = new CTreeNode(AND_STA, "", 0);
			temp2->child[2]->copy_tree(ptree->child[2]);

			temp1->child[0] = new CTreeNode(AND_STA, "", 0);
			temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
			temp1->child[1] = new CTreeNode(AND_STA, "", 0);
			temp1->child[1]->copy_tree(temp2);

			ptree->copy_tree(temp1);
			delete temp1;
			delete temp2;

			NF(ptree);
			done = 1;
		}
		else
		{
			SFA = 1;
			SF(ptree->child[0]->child[1]);
			if (SFA)
			{
				int de_2_1 = 0;
				temp1 = new CTreeNode(AND_STA, "", 0);
				temp2 = new CTreeNode(PROJECTION_STA, "", 0);

				temp2->child[0] = new CTreeNode(AND_STA, "", 0);
				temp2->child[0]->copy_tree(ptree->child[0]->child[0]);
				if (ptree->child[1] != NULL)
				{
					temp2->child[1] = new CTreeNode(AND_STA, "", 0);
					temp2->child[1]->copy_tree(ptree->child[1]);
					de_2_1 = 1;
				}
				temp2->child[2] = new CTreeNode(AND_STA, "", 0);
				temp2->child[2]->copy_tree(ptree->child[2]);

				temp1->child[0] = new CTreeNode(AND_STA, "", 0);
				temp1->child[0]->copy_tree(ptree->child[0]->child[1]);
				temp1->child[1] = new CTreeNode(AND_STA, "", 0);
				temp1->child[1]->copy_tree(temp2);

				ptree->copy_tree(temp1);
				delete temp1;
				delete temp2;

				NF(ptree);
				done = 1;
			}
		}

	}

	//(P1,P2...Pm) prj (w && Q) --> w && PRJ((P1,P2,...Pm) prj Q)
	if (done == 0 && ptree->child[2]->type == AND_STA)
	{
		SFA = 1;
		SF(ptree->child[2]->child[0]);
		if (SFA)
		{
			int de_2_1 = 0;
			temp1 = new CTreeNode(AND_STA, "", 0);
			temp2 = new CTreeNode(PROJECTION_STA, "", 0);

			temp2->child[0] = new CTreeNode(AND_STA, "", 0);
			temp2->child[0]->copy_tree(ptree->child[0]);
			if (ptree->child[1] != NULL)
			{
				temp2->child[1] = new CTreeNode(AND_STA, "", 0);
				temp2->child[1]->copy_tree(ptree->child[1]);
				de_2_1 = 1;
			}
			temp2->child[2] = new CTreeNode(AND_STA, "", 0);
			temp2->child[2]->copy_tree(ptree->child[2]->child[1]);

			temp1->child[0] = new CTreeNode(AND_STA, "", 0);
			temp1->child[0]->copy_tree(ptree->child[2]->child[0]);
			temp1->child[1] = new CTreeNode(AND_STA, "", 0);
			temp1->child[1]->copy_tree(temp2);

			ptree->copy_tree(temp1);
			delete temp1;
			delete temp2;

			NF(ptree);
			done = 1;
		}
		else
		{
			SFA = 1;
			SF(ptree->child[2]->child[1]);
			if (SFA)
			{
				int de_2_0 = 0;
				temp1 = new CTreeNode(AND_STA, "", 0);
				temp2 = new CTreeNode(PROJECTION_STA, "", 0);
				if (ptree->child[0] != NULL)
				{
					temp2->child[0] = new CTreeNode(AND_STA, "", 0);
					temp2->child[0]->copy_tree(ptree->child[0]);
					de_2_0 = 1;
				}
				temp2->child[1] = new CTreeNode(AND_STA, "", 0);
				temp2->child[1]->copy_tree(ptree->child[1]);

				temp2->child[2] = new CTreeNode(AND_STA, "", 0);
				temp2->child[2]->copy_tree(ptree->child[2]->child[0]);

				temp1->child[0] = new CTreeNode(AND_STA, "", 0);
				temp1->child[0]->copy_tree(ptree->child[2]->child[1]);
				temp1->child[1] = new CTreeNode(AND_STA, "", 0);
				temp1->child[1]->copy_tree(temp2);

				ptree->copy_tree(temp1);
				delete temp1;
				delete temp2;

				NF(ptree);
				done = 1;
			}
		}
	}
	//else 返回PRJ( (NF(P1),...,Pm) prj NF(Q) )
	if (done == 0)
	{
		NF(ptree->child[0]);
		NF(ptree->child[2]);
		POST(ptree->child[0]);
		POST(ptree->child[2]);
		PRJ(ptree);
	}
}

//DEL void CNFMachine::CHOP(CTreeNode * ptree,int n)
//DEL {
//DEL   //此时ptree的结构是p;p*
//DEL 	NF(ptree->child[0]);
//DEL 	POST(ptree->child[0]);
//DEL 	CTreeNode *temp1,*temp2;
//DEL 	temp1=ptree->child[0];
//DEL 	while(temp1->type==OR_STA)
//DEL 	{
//DEL 	  if(temp1->child[1]!=NULL && temp1->child[1]->type==EMPTY_EXP || temp1->child[1]!=NULL && temp1->child[1]->type==AND_STA && temp1->child[1]->child[1]!=NULL && temp1->child[1]->child[1]->type==EMPTY_EXP)
//DEL 	  {
//DEL 	     temp2=new CTreeNode(FALSE_EXP,"FALSE",0);
//DEL 		 temp1->child[1]->copy_tree(temp2);
//DEL 		 delete temp2;
//DEL 		 temp1=NULL;
//DEL 		 delete temp1;
//DEL 		 CHOP(ptree);
//DEL 		 return;
//DEL 	  }
//DEL 	  else
//DEL 		  temp1=temp1->child[0];
//DEL 	}
//DEL 	if(temp1->type==EMPTY_EXP || temp1->type==AND_STA && temp1->child[1]!=NULL && temp1->child[1]->type==EMPTY_EXP)
//DEL 	{
//DEL 	    temp2=new CTreeNode(FALSE_EXP,"FALSE",0);
//DEL 		temp1->copy_tree(temp2);
//DEL 		delete temp2;
//DEL 		temp1=NULL;
//DEL 		delete temp1;
//DEL 		CHOP(ptree);
//DEL 		return;
//DEL 	}
//DEL 
//DEL 	temp1=NULL;
//DEL 	delete temp1;
//DEL 	CHOP(ptree);
//DEL 	return;
//DEL }


void CNFMachine::CHOP(CTreeNode * ptree)
{
	CTreeNode * temp1, *temp2, *temp3;
	int done;
	done = 0;
	//false;p --> false
	if (done == 0 && ptree->child[0]->type == FALSE_EXP)
	{
		temp1 = new CTreeNode(FALSE_EXP, "FALSE", 0);
		ptree->copy_tree(temp1);
		delete temp1;
		done = 1;
	}
	//empty ; Q --> Q
	if (done == 0 && ptree->child[0]->type == EMPTY_EXP)
	{
		temp1 = new CTreeNode(AND_STA, "", 0);
		temp1->copy_tree(ptree->child[1]);
		ptree->copy_tree(temp1);
		delete temp1;


		NF(ptree);
		done = 1;
	}
	//T;T --> T
	if (done == 0 && ptree->child[0]->type == TRUE_EXP && ptree->child[1]->type == TRUE_EXP)
	{
		ptree->copy_tree(ptree->child[0]);
		NF(ptree);
		done = 1;
	}

	//()P ; Q --> ()(p;q)
	if (done == 0 && ptree->child[0]->type == NEXT_STA)
	{
		temp1 = new CTreeNode(CHOP_STA, "", 0);
		temp1->child[0] = new CTreeNode(AND_STA, "", 0);
		temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
		temp1->child[1] = new CTreeNode(AND_STA, "", 0);
		temp1->child[1]->copy_tree(ptree->child[1]);

		temp2 = new CTreeNode(NEXT_STA, "", 0);
		temp2->child[0] = new CTreeNode(AND_STA, "", 0);
		temp2->child[0]->copy_tree(temp1);

		ptree->copy_tree(temp2);
		delete temp1;
		delete temp2;

		done = 1;
	}

	//w && P ; Q --> w && CHOP(P;Q)
	if (done == 0 && ptree->child[0]->type == AND_STA)
	{
		SFA = 1;
		SF(ptree->child[0]->child[0]);
		if (SFA == 1)
		{
			SFA = 1;
			temp2 = new CTreeNode(CHOP_STA, "", 0);
			temp2->child[0] = new CTreeNode(AND_STA, "", 0);
			temp2->child[0]->copy_tree(ptree->child[0]->child[1]);
			temp2->child[1] = new CTreeNode(AND_STA, "", 0);
			temp2->child[1]->copy_tree(ptree->child[1]);

			temp1 = new CTreeNode(AND_STA, "", 0);
			temp1->child[0] = new CTreeNode(AND_STA, "", 0);
			temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
			temp1->child[1] = new CTreeNode(AND_STA, "", 0);
			temp1->child[1]->copy_tree(temp2);

			ptree->copy_tree(temp1);
			delete temp1;
			delete temp2;

			NF(ptree);
			done = 1;

		}
		else
		{
			SF(ptree->child[0]->child[1]);
			if (SFA == 1)
			{
				SFA = 1;
				temp2 = new CTreeNode(CHOP_STA, "", 0);
				temp2->child[0] = new CTreeNode(AND_STA, "", 0);
				temp2->child[0]->copy_tree(ptree->child[0]->child[0]);
				temp2->child[1] = new CTreeNode(AND_STA, "", 0);
				temp2->child[1]->copy_tree(ptree->child[1]);

				temp1 = new CTreeNode(AND_STA, "", 0);
				temp1->child[0] = new CTreeNode(AND_STA, "", 0);
				temp1->child[0]->copy_tree(ptree->child[0]->child[1]);
				temp1->child[1] = new CTreeNode(AND_STA, "", 0);
				temp1->child[1]->copy_tree(temp2);

				ptree->copy_tree(temp1);
				delete temp1;
				delete temp2;

				NF(ptree);
				done = 1;

			}///if(SFA==1)
		}//else
	}

	//P1 || P2 ; Q --> P1;Q || P2;Q
	if (done == 0 && ptree->child[0]->type == OR_STA)
	{
		temp1 = new CTreeNode(CHOP_STA, "", 0);
		temp1->child[0] = new CTreeNode(AND_STA, "", 0);
		temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
		temp1->child[1] = new CTreeNode(AND_STA, "", 0);
		temp1->child[1]->copy_tree(ptree->child[1]);

		temp2 = new CTreeNode(CHOP_STA, "", 0);
		temp2->child[0] = new CTreeNode(AND_STA, "", 0);
		temp2->child[0]->copy_tree(ptree->child[0]->child[1]);
		temp2->child[1] = new CTreeNode(AND_STA, "", 0);
		temp2->child[1]->copy_tree(ptree->child[1]);

		temp3 = new CTreeNode(OR_STA, "", 0);
		temp3->child[0] = new CTreeNode(AND_STA, "", 0);
		temp3->child[0]->copy_tree(temp1);
		temp3->child[1] = new CTreeNode(AND_STA, "", 0);
		temp3->child[1]->copy_tree(temp2);

		ptree->copy_tree(temp3);
		delete temp1;
		delete temp2;
		delete temp3;

		CHOP(ptree->child[0]);
		CHOP(ptree->child[1]);
		done = 1;
	}


	//P ; Q1 || Q2 --> P;Q1 || P;Q2
	if (done == 0 && ptree->child[1]->type == OR_STA)
	{
		temp1 = new CTreeNode(CHOP_STA, "", 0);
		temp1->child[0] = new CTreeNode(AND_STA, "", 0);
		temp1->child[0]->copy_tree(ptree->child[0]);
		temp1->child[1] = new CTreeNode(AND_STA, "", 0);
		temp1->child[1]->copy_tree(ptree->child[1]->child[0]);

		temp2 = new CTreeNode(CHOP_STA, "", 0);
		temp2->child[0] = new CTreeNode(AND_STA, "", 0);
		temp2->child[0]->copy_tree(ptree->child[0]);
		temp2->child[1] = new CTreeNode(AND_STA, "", 0);
		temp2->child[1]->copy_tree(ptree->child[1]->child[1]);

		temp3 = new CTreeNode(OR_STA, "", 0);
		temp3->child[0] = new CTreeNode(CHOP_STA, "", 0);
		temp3->child[0]->copy_tree(temp1);
		temp3->child[1] = new CTreeNode(CHOP_STA, "", 0);
		temp3->child[1]->copy_tree(temp2);

		ptree->copy_tree(temp3);
		delete temp1;
		delete temp2;
		delete temp3;

		CHOP(ptree->child[0]);
		CHOP(ptree->child[1]);
		done = 1;
	}



	if (done == 0)
	{
		NF(ptree->child[0]);
		POST(ptree->child[0]);
		CHOP(ptree);
	}

}

//将公式中empty和next分别整理到emptytree和nexttree中
void CNFMachine::CONF_tree(CTreeNode * ptree)
{

	if (ptree->type == OR_STA)
	{
		if (ptree->child[0] != NULL && ptree->child[0]->type == AND_STA)
		{
			if (ptree->child[0]->child[0] != NULL && ptree->child[0]->child[0]->type == EMPTY_EXP)
			{
				CONF_emptytree(ptree->child[0]);
				ptree->child[0] = NULL;
			}
			else
				if (ptree->child[0]->child[0] != NULL && ptree->child[0]->child[0]->type == NEXT_STA)
				{
					CONF_nexttree(ptree->child[0]);
					ptree->child[0] = NULL;
				}
			if (ptree->child[0]->child[1] != NULL && ptree->child[0]->child[1]->type == EMPTY_EXP)
			{
				CONF_emptytree(ptree->child[0]);
				ptree->child[0] = NULL;
			}
			else
				if (ptree->child[0]->child[1] != NULL && ptree->child[0]->child[1]->type == NEXT_STA)
				{
					CONF_nexttree(ptree->child[0]);
					ptree->child[0] = NULL;
				}
		}
		else
			if (ptree->child[0]->type == NEXT_STA)
			{
				CONF_nexttree(ptree->child[0]);
				ptree->child[0] = NULL;

			}
			else
				if (ptree->child[0]->type == EMPTY_EXP)
				{
					CONF_emptytree(ptree->child[0]);
					ptree->child[0] = NULL;
				}

		if (ptree->child[1] != NULL && ptree->child[1]->type == AND_STA)
		{
			if (ptree->child[1]->child[0] != NULL && ptree->child[1]->child[0]->type == EMPTY_EXP)
			{
				CONF_emptytree(ptree->child[1]);
				ptree->child[1] = NULL;
			}
			else
				if (ptree->child[1]->child[0] != NULL && ptree->child[1]->child[0]->type == NEXT_STA)
				{
					CONF_nexttree(ptree->child[1]);
					ptree->child[1] = NULL;
				}
				else
					if (ptree->child[1]->child[1] != NULL && ptree->child[1]->child[1]->type == EMPTY_EXP)
					{
						CONF_emptytree(ptree->child[1]);
						ptree->child[1] = NULL;
					}
					else
						if (ptree->child[1]->child[1] != NULL && ptree->child[1]->child[1]->type == NEXT_STA)
						{
							CONF_nexttree(ptree->child[1]);
							ptree->child[1] = NULL;
						}
		}
		else
			if (ptree->child[1]->type == NEXT_STA)
			{
				CONF_nexttree(ptree->child[1]);
				ptree->child[1] = NULL;
			}
			else
				if (ptree->child[1]->type == EMPTY_EXP)
				{
					CONF_emptytree(ptree->child[1]);
					ptree->child[1] = NULL;
				}
	}
	if (ptree->child[0] != NULL)
	{
		CONF_tree(ptree->child[0]);
	}
	if (ptree->child[1] != NULL)
	{
		CONF_tree(ptree->child[1]);
	}
	if (ptree->child[2] != NULL)
	{
		CONF_tree(ptree->child[2]);
	}

}
//将包含empty的结构整理到一个emptytree结构中
void CNFMachine::CONF_emptytree(CTreeNode * ptree)
{
	CTreeNode *temp4, *temp2;
	temp4 = emptytree;
	while (temp4->child[0] != NULL)
	{
		temp4 = temp4->child[0];
	}
	temp4->child[0] = new CTreeNode(OR_STA, "", 0);


	/////////////////   add  ///////////////
	////////////////////////////////////////
	//将empty整理到AND的右边
	if (ptree->type == AND_STA && ptree->child[0] != NULL && ptree->child[0]->type == EMPTY_EXP)
	{
		temp2 = new CTreeNode(EMPTY_EXP, "", 0);
		ptree->child[0]->copy_tree(ptree->child[1]);
		ptree->child[1]->copy_tree(temp2);
		delete temp2;
	}
	///////////   add over   ////////////////
	/////////////////////////////////////

	temp4->child[1] = new CTreeNode(OR_STA, "", 0);
	temp4->child[1]->copy_tree(ptree);

	temp4 = NULL;
}
//删除emptytree中最后一级初始化出来的多余的or结构
void CNFMachine::CONF_emptytree1()
{
	CTreeNode * temp4;

	temp4 = emptytree;
	if (temp4->child[0] == NULL && temp4->child[1] == NULL)
	{

		temp4 = NULL;

		return;
	}
	while (temp4->child[0]->child[0] != NULL)
	{
		temp4 = temp4->child[0];
	}
	temp4->copy_tree(temp4->child[1]);

	temp4 = NULL;
}
//将包含next的结构整理到一个nexttree结构中
void CNFMachine::CONF_nexttree(CTreeNode * ptree)
{
	CTreeNode *temp4, *temp2;

	temp4 = nexttree;
	while (temp4->child[0] != NULL)
	{
		temp4 = temp4->child[0];
	}
	temp4->child[0] = new CTreeNode(OR_STA, "", 0);

	/////////////////   add  ///////////////
	////////////////////////////////////////
	//将next整理到AND的右边
	if (ptree->type == AND_STA && ptree->child[0] != NULL && ptree->child[0]->type == NEXT_STA)
	{
		temp2 = new CTreeNode(NEXT_STA, "", 0);
		temp2->copy_tree(ptree->child[0]);
		ptree->child[0]->copy_tree(ptree->child[1]);
		ptree->child[1]->copy_tree(temp2);

		delete temp2;

	}
	///////////   add over   ////////////////
	/////////////////////////////////////

	temp4->child[1] = new CTreeNode(OR_STA, "", 0);
	temp4->child[1]->copy_tree(ptree);

	temp4 = NULL;
}
//删除nexttree中最后一级初始化出来的多余的or结构
void CNFMachine::CONF_nexttree1()
{
	CTreeNode * temp4;

	temp4 = nexttree;
	if (temp4->child[0] == NULL && temp4->child[1] == NULL)
	{

		temp4 = NULL;
		return;
	}
	while (temp4->child[0]->child[0] != NULL)
	{
		temp4 = temp4->child[0];
	}
	temp4->copy_tree(temp4->child[1]);

	temp4 = NULL;
}
//求完全正则式
void CNFMachine::CONF(CTreeNode * ptree) //对next tree 由下至上逐层画完全NF，每处理一层，项数增倍
{
	CTreeNode * temp1, *temp2, *temp3, *temp4;
	if (ptree->type == AND_STA && (ptree->child[0]->type == NEXT_STA || ptree->child[1]->type == NEXT_STA))
	{
		CONF_nfalse(ptree);  // deal with (p && ()p1)
	}
	//////////  add ///////////////
	else
		if (ptree->type == NEXT_STA)
		{
			CONF_nfalse(ptree);
		}
		else
			//////// add over  /////////////

			if (ptree->type == OR_STA)
			{
				int n, m, p;
				n = 0;
				p = 0;
				temp1 = new CTreeNode(AND_STA, "", 0);
				temp1->copy_tree(ptree);
				temp2 = new CTreeNode(AND_STA, "", 0);
				while (temp1->child[0] != NULL && temp1->child[0]->type == OR_STA)
				{
					n++;
					temp2->copy_tree(temp1);
					temp1->copy_tree(temp1->child[0]);
				}
				temp2->copy_tree(temp1);
				temp1->copy_tree(temp1->child[0]);
				temp3 = new CTreeNode(AND_STA, "", 0);
				temp3->copy_tree(temp2->child[1]);
				CONF_nfalse(temp1);
				temp2->copy_tree(temp1);
				//将p&&()p1 || q&&()q1分两步划成完全NF
				//add 
				if (temp2->child[0]->child[1]->child[0] != NULL&&temp2->child[0]->child[1]->child[0]->type != TRUE_EXP)
					//add over
					CONF_or(temp2->child[0], temp3);  // p&&q&&()(p1||q1)  ||  p&&!q&&()p1
				//add 
				if (temp2->child[1]->child[1]->child[0] != NULL&&temp2->child[1]->child[1]->child[0]->type != TRUE_EXP)
					//add over
					CONF_or(temp2->child[1], temp3);  // !p&&q&&()q1   ||  !p&&!q&&()false
				temp4 = new CTreeNode(AND_STA, "", 0);
				while (n != 0)
				{
					p = 1;
					temp1->copy_tree(ptree);
					m = n;
					while (m != 1)
					{
						temp1->copy_tree(temp1->child[0]);
						m--;
					}
					temp4->copy_tree(temp1->child[1]);
					temp1->copy_tree(temp2);
					CONF_nor(temp1, temp4);
					temp2->copy_tree(temp1);
					n--;
				}
				if (p == 1)
				{
					ptree->copy_tree(temp1);
				}
				else
				{
					ptree->copy_tree(temp2);
				}

				delete temp1;
				delete temp2;
				delete temp3;
				delete temp4;

			}

}
void CNFMachine::CONF_nfalse(CTreeNode * ptree)
{
	CTreeNode * temp1, *temp2, *temp3, *temp4, *temp5, *temp6, *temp7;
	if (ptree->type == NEXT_STA)
	{
		temp1 = new CTreeNode(AND_STA, "", 0);
		temp1->child[0] = new CTreeNode(TRUE_EXP, "TRUE", 0);
		temp1->child[1] = new CTreeNode(NEXT_STA, "", 0);
		temp1->child[1]->copy_tree(ptree);
		ptree->copy_tree(temp1);

		delete temp1;

	}
	if (ptree->child[0] != NULL && ptree->child[0]->type == NEXT_STA)
	{
		temp2 = new CTreeNode(NEGATION_STA, "", 0);
		temp3 = new CTreeNode(NEGATION_STA, "", 0);
		temp2->copy_tree(ptree->child[0]);
		temp3->copy_tree(ptree->child[1]);
	}
	else
	{
		temp2 = new CTreeNode(NEGATION_STA, "", 0);
		temp3 = new CTreeNode(NEGATION_STA, "", 0);
		temp2->copy_tree(ptree->child[1]);
		temp3->copy_tree(ptree->child[0]);
	}
	temp1 = new CTreeNode(NEGATION_STA, "", 0);
	temp1->child[0] = new CTreeNode(AND_STA, "", 0);
	temp1->child[0]->copy_tree(temp3);

	temp5 = new CTreeNode(FALSE_EXP, "FALSE", 0);
	temp4 = new CTreeNode(NEXT_STA, "", 0);
	temp4->child[0] = new CTreeNode(AND_STA, "", 0);
	temp4->child[0]->copy_tree(temp5);

	temp6 = new CTreeNode(AND_STA, "", 0);
	temp6->child[0] = new CTreeNode(AND_STA, "", 0);
	temp6->child[1] = new CTreeNode(AND_STA, "", 0);
	temp6->child[0]->copy_tree(temp1);
	temp6->child[1]->copy_tree(temp4);


	//change to:
	temp7 = new CTreeNode(AND_STA, "", 0);
	temp7->child[0] = new CTreeNode(AND_STA, "", 0);
	temp7->child[1] = new CTreeNode(AND_STA, "", 0);
	temp7->child[0]->copy_tree(temp3);
	temp7->child[1]->copy_tree(temp2);

	ptree->type = OR_STA;
	ptree->child[0] = new CTreeNode(AND_STA, "", 0);
	ptree->child[0]->copy_tree(temp7);
	ptree->child[1] = new CTreeNode(AND_STA, "", 0);
	ptree->child[1]->copy_tree(temp6);

	delete temp3;
	delete temp1;
	delete temp2;
	delete temp5;
	delete temp4;
	delete temp6;
	delete temp7;

}
void CNFMachine::CONF_or(CTreeNode * ptree1, CTreeNode * ptree2)
{
	//以下部分是整理为左边是p右边是next p以及将next p整理为T && ()p
	CTreeNode * temp1, *temp2, *temp3, *temp4, *temp5, *temp6, *temp7, *temp8;
	if (ptree2->type == AND_STA && ptree2->child[0] != NULL && ptree2->child[0]->type == NEXT_STA)//将ptree2原先为empty&&p的形式，转换为p&&empty
	{
		temp1 = new CTreeNode(AND_STA, "", 0);
		temp1->copy_tree(ptree2->child[1]);
		ptree2->child[1]->copy_tree(ptree2->child[0]);
		ptree2->child[0]->copy_tree(temp1);
		delete temp1;

	}
	if (ptree2->type == NEXT_STA)//将ptree2原来为()p的形式转换为true&&()p
	{
		temp1 = new CTreeNode(TRUE_EXP, "TRUE", 0);
		temp2 = new CTreeNode(AND_STA, "", 0);
		temp2->child[0] = new CTreeNode(AND_STA, "", 0);
		temp2->child[1] = new CTreeNode(AND_STA, "", 0);
		temp2->child[0]->copy_tree(temp1);
		temp2->child[1]->copy_tree(ptree2);

		ptree2->copy_tree(temp2);
		delete temp1;
		delete temp2;

	}
	if (ptree1->type == AND_STA && ptree1->child[0] != NULL && ptree1->child[0]->type == NEXT_STA)//将ptree1原先为empty&&p的形式，转换为p&&empty
	{
		temp1 = new CTreeNode(AND_STA, "", 0);
		temp1->copy_tree(ptree1->child[1]);
		ptree1->child[1]->copy_tree(ptree1->child[0]);
		ptree1->child[0]->copy_tree(temp1);
		delete temp1;

	}
	if (ptree1->type == NEXT_STA)//将ptree1原来为()p的形式转换为true&&()p
	{
		temp1 = new CTreeNode(TRUE_EXP, "TRUE", 0);
		temp2 = new CTreeNode(AND_STA, "", 0);
		temp2->child[0] = new CTreeNode(AND_STA, "", 0);
		temp2->child[1] = new CTreeNode(AND_STA, "", 0);
		temp2->child[0]->copy_tree(temp1);
		temp2->child[1]->copy_tree(ptree1);

		ptree1->copy_tree(temp2);
		delete temp2;

		delete temp1;
	}
	//以上部分是整理为左边是p右边是next p以及将next p整理为T && ()p

	//new add讨论()T
	if (ptree2->child[1] != NULL&&ptree2->child[1]->type == NEXT_STA && ptree2->child[1]->child[0] != NULL&&ptree2->child[1]->child[0]->type == TRUE_EXP &&ptree1->child[0] != NULL&& ptree1->child[0]->type != FALSE_EXP)
	{
		temp1 = new CTreeNode(AND_STA, "AND", 0);
		temp1->child[0] = new CTreeNode(AND_STA, "", 0);
		temp1->child[0]->copy_tree(ptree1->child[0]);
		temp1->child[1] = new CTreeNode(NEGATION_STA, "NEGATION", 0);
		temp1->child[1]->child[0] = new CTreeNode(AND_STA, "", 0);
		temp1->child[1]->child[0]->copy_tree(ptree2->child[0]);

		POST(temp1);
		ptree1->child[0]->copy_tree(temp1);

		delete temp1;

	}
	//原来的用一个ELSE
	//add over


	//ptree1: p && ()p1      ptree2:   q && ()q1   
	//p1 || q1
	else if (ptree1->child[0]->type != FALSE_EXP)
	{
		if (ptree1->child[0]->compare(ptree2->child[0]))////////////
		{/////////////
			//p1 || q1
			if (ptree1->child[1]->child[0] != NULL && ptree1->child[1]->child[0]->type == FALSE_EXP)
			{
				temp1 = new CTreeNode(AND_STA, "", 0);
				temp1->copy_tree(ptree2->child[1]->child[0]);
			}
			else
			{
				temp1 = new CTreeNode(OR_STA, "", 0);
				temp1->child[0] = new CTreeNode(AND_STA, "", 0);
				temp1->child[0]->copy_tree(ptree1->child[1]->child[0]);
				temp1->child[1] = new CTreeNode(AND_STA, "", 0);
				temp1->child[1]->copy_tree(ptree2->child[1]->child[0]);
			}
			ptree1->child[1]->child[0]->copy_tree(temp1);

			delete temp1;

		}////////////////
		else  if (!(ptree1->child[0]->type == NEGATION_STA && ptree1->child[0]->child[0]->compare(ptree2->child[0]) || ptree2->child[0]->type == NEGATION_STA && ptree2->child[0]->child[0]->compare(ptree1->child[0])))
		{
			if (ptree1->child[1]->child[0] != NULL && ptree1->child[1]->child[0]->type == FALSE_EXP)
			{
				temp1 = new CTreeNode(AND_STA, "", 0);
				temp1->copy_tree(ptree2->child[1]->child[0]);
			}

			else
			{
				temp1 = new CTreeNode(OR_STA, "", 0);
				temp1->child[0] = new CTreeNode(AND_STA, "", 0);
				temp1->child[0]->copy_tree(ptree1->child[1]->child[0]);
				temp1->child[1] = new CTreeNode(AND_STA, "", 0);
				temp1->child[1]->copy_tree(ptree2->child[1]->child[0]);
			}
			//()(p1 || q1)
			temp2 = new CTreeNode(NEXT_STA, "", 0);
			temp2->child[0] = new CTreeNode(OR_STA, "", 0);
			temp2->child[0]->copy_tree(temp1);
			//p && q
			temp3 = new CTreeNode(AND_STA, "", 0);
			temp3->child[0] = new CTreeNode(AND_STA, "", 0);
			temp3->child[0]->copy_tree(ptree1->child[0]);
			temp3->child[1] = new CTreeNode(AND_STA, "", 0);
			temp3->child[1]->copy_tree(ptree2->child[0]);
			//p && q && ()(p1 || q1)
			temp4 = new CTreeNode(AND_STA, "", 0);
			temp4->child[0] = new CTreeNode(AND_STA, "", 0);
			temp4->child[0]->copy_tree(temp3);
			temp4->child[1] = new CTreeNode(AND_STA, "", 0);
			temp4->child[1]->copy_tree(temp2);
			//!q
			temp5 = new CTreeNode(NEGATION_STA, "", 0);
			temp5->child[0] = new CTreeNode(AND_STA, "", 0);
			temp5->child[0]->copy_tree(ptree2->child[0]);
			//p && !q
			temp6 = new CTreeNode(AND_STA, "", 0);
			temp6->child[0] = new CTreeNode(AND_STA, "", 0);
			temp6->child[0]->copy_tree(ptree1->child[0]);
			temp6->child[1] = new CTreeNode(AND_STA, "", 0);
			temp6->child[1]->copy_tree(temp5);
			//p && !q && ()p1
			temp7 = new CTreeNode(AND_STA, "", 0);
			temp7->child[0] = new CTreeNode(AND_STA, "", 0);
			temp7->child[0]->copy_tree(temp6);
			temp7->child[1] = new CTreeNode(AND_STA, "", 0);
			temp7->child[1]->copy_tree(ptree1->child[1]);
			//(p && q && ()(p1 || q1))||(p && !q && ()p1)
			temp8 = new CTreeNode(OR_STA, "", 0);
			temp8->child[0] = new CTreeNode(AND_STA, "", 0);
			temp8->child[0]->copy_tree(temp4);
			temp8->child[1] = new CTreeNode(AND_STA, "", 0);
			temp8->child[1]->copy_tree(temp7);

			ptree1->copy_tree(temp8);

			delete temp1;
			delete temp2;
			delete temp3;
			delete temp4;
			delete temp5;
			delete temp6;
			delete temp7;
			delete temp8;
		}//else
	}//else if(ptree1->child[0]->type!=FALSE_EXP)
}
void CNFMachine::CONF_nor(CTreeNode * ptree1, CTreeNode * ptree2)
{
	if (ptree1 != NULL && ptree1->type != OR_STA)
	{
		//new add
		if (ptree1->child[1] != NULL && ptree1->child[1]->type == NEXT_STA && ptree1->child[1]->child[0]->type != TRUE_EXP)
			// add over
			CONF_or(ptree1, ptree2);
	}
	else
		if (ptree1 != NULL && ptree1->type == OR_STA)
		{
			CONF_nor(ptree1->child[0], ptree2);
			CONF_nor(ptree1->child[1], ptree2);
		}
}
//对完全正则式求非的函数，其输入是完全正则式形式。
void CNFMachine::NEG(CTreeNode * ptree)
{
	CTreeNode *temp1;
	if (ptree->type == AND_STA && ptree->child[1] != NULL && ptree->child[1]->type == NEXT_STA)
	{
		temp1 = new CTreeNode(NEGATION_STA, "", 0);
		temp1->child[0] = new CTreeNode(AND_STA, "", 0);
		temp1->child[0]->copy_tree(ptree->child[1]->child[0]);
		if (ptree->child[1]->child[0]->type == FALSE_EXP)
		{
			temp1->type = TRUE_EXP;
			temp1->name_str = "TRUE";
			temp1->int_str = 0;
			temp1->child[0] = NULL;
			temp1->child[1] = NULL;
			temp1->child[2] = NULL;
			ptree->child[1]->child[0]->copy_tree(temp1);
		}
		else
			if (ptree->child[1]->child[0]->type == TRUE_EXP)
			{
				temp1->type = FALSE_EXP;
				temp1->name_str = "FALSE";
				temp1->int_str = 0;
				temp1->child[0] = NULL;
				temp1->child[1] = NULL;
				temp1->child[2] = NULL;
				ptree->child[1]->child[0]->copy_tree(temp1);
			}
			else
			{
				ptree->child[1]->child[0]->copy_tree(temp1);
			}

		delete temp1;
		//
		return;
	}
	else
		if (ptree->type == AND_STA && ptree->child[1] != NULL && ptree->child[1]->type == EMPTY_EXP)
		{
			temp1 = new CTreeNode(NEGATION_STA, "", 0);
			temp1->child[0] = new CTreeNode(AND_STA, "", 0);
			temp1->child[0]->copy_tree(ptree->child[0]);
			if (ptree->child[0]->type == FALSE_EXP)
			{
				temp1->type = TRUE_EXP;
				temp1->name_str = "TRUE";
				temp1->int_str = 0;
				temp1->child[0] = NULL;
				temp1->child[1] = NULL;
				temp1->child[2] = NULL;
				ptree->child[0]->copy_tree(temp1);
			}
			else
				if (ptree->child[0]->type == TRUE_EXP)
				{
					temp1->type = FALSE_EXP;
					temp1->name_str = "FALSE";
					temp1->int_str = 0;
					temp1->child[0] = NULL;
					temp1->child[1] = NULL;
					temp1->child[2] = NULL;
					ptree->child[0]->copy_tree(temp1);
				}
				else
				{
					ptree->child[0]->copy_tree(temp1);
				}
			delete temp1;
			//
			return;
		}
	//屏蔽下面一段，原因是在CONF_emptytree中已经将empty整理到AND的右边
		else
			if (ptree->type == AND_STA && ptree->child[0] != NULL && ptree->child[0]->type == EMPTY_EXP)
			{
				temp1 = new CTreeNode(NEGATION_STA, "", 0);
				temp1->child[0] = new CTreeNode(AND_STA, "", 0);
				temp1->child[0]->copy_tree(ptree->child[1]);
				ptree->child[1]->copy_tree(temp1);

				delete temp1;
				//
				return;
			}

	if (ptree->child[0] != NULL)
	{
		NEG(ptree->child[0]);
	}
	if (ptree->child[1] != NULL)
	{
		NEG(ptree->child[1]);
	}
	if (ptree->child[2] != NULL)
	{
		NEG(ptree->child[2]);
	}

}
void CNFMachine::AND(CTreeNode * ptree)
{
	CTreeNode * temp1, *temp2, *temp3, *temp4;
	//p && false -->false   ; false && p -->false
	if (ptree->child[0]->type == FALSE_EXP || ptree->child[1]->type == FALSE_EXP)
	{
		temp1 = new CTreeNode(FALSE_EXP, "FALSE", 0);
		ptree->copy_tree(temp1);
		delete temp1;
	}
	//p && true-->p   
	else
		if (ptree->child[1]->type == TRUE_EXP)
			ptree->copy_tree(ptree->child[0]);
	//true && p -->p
		else
			if (ptree->child[0]->type == TRUE_EXP)
				ptree->copy_tree(ptree->child[1]);
	//empty && empty --> empty
			else
				if (ptree->child[0] != NULL && ptree->child[1] != NULL && ptree->child[0]->type == EMPTY_EXP && ptree->child[1]->type == EMPTY_EXP)
				{
					temp1 = new CTreeNode(EMPTY_EXP, "EMPTY", 0);
					ptree->copy_tree(temp1);
					delete temp1;
				}
				else
					//next && next          ()p && ()q ==> ()(p && q)
					if (ptree->child[0] != NULL && ptree->child[1] != NULL && ptree->child[0]->type == NEXT_STA && ptree->child[1]->type == NEXT_STA)
					{
						temp1 = new CTreeNode(AND_STA, "", 0);
						temp1->child[0] = new CTreeNode(AND_STA, "", 0);
						temp1->child[1] = new CTreeNode(AND_STA, "", 0);
						temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
						temp1->child[1]->copy_tree(ptree->child[1]->child[0]);

						temp2 = new CTreeNode(NEXT_STA, "", 0);
						temp2->child[0] = new CTreeNode(AND_STA, "", 0);
						temp2->child[0]->copy_tree(temp1);

						ptree->copy_tree(temp2);

						delete temp1;
						delete temp2;

					}
					else
						//P && Q , P is (P1 || P2)  --> (P1 && Q) || (P2 && Q)
						if (ptree->child[0] != NULL && ptree->child[0]->type == OR_STA)
						{
							if (ptree->child[0]->child[0] != NULL && ptree->child[0]->child[0]->type == AND_STA && ((ptree->child[0]->child[0]->child[0] != NULL && ptree->child[1]->compare(ptree->child[0]->child[0]->child[0])) || (ptree->child[0]->child[0]->child[1] != NULL && ptree->child[1]->compare(ptree->child[0]->child[0]->child[1]))))
							{
								//((p1 && p2) || q) && p1  ///// ((p1 && p2) || q) && p2
								temp1 = new CTreeNode(AND_STA, "", 0);
								temp1->copy_tree(ptree->child[0]->child[0]);
							}
							else
							{
								temp1 = new CTreeNode(AND_STA, "", 0);
								temp1->child[0] = new CTreeNode(AND_STA, "", 0);
								temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
								temp1->child[1] = new CTreeNode(AND_STA, "", 0);
								temp1->child[1]->copy_tree(ptree->child[1]);
							}

							if (ptree->child[0]->child[1] != NULL && ptree->child[0]->child[1]->type == AND_STA && ((ptree->child[0]->child[1]->child[0] != NULL && ptree->child[1]->compare(ptree->child[0]->child[1]->child[0])) || (ptree->child[0]->child[1]->child[1] != NULL && ptree->child[1]->compare(ptree->child[0]->child[1]->child[1]))))
							{
								// (p || (q1 && q2)) && q1  ////// (p || (q1 && q2)) && q2
								temp2 = new CTreeNode(AND_STA, "", 0);
								temp2->copy_tree(ptree->child[0]->child[1]);
							}
							else
							{
								temp2 = new CTreeNode(AND_STA, "", 0);
								temp2->child[0] = new CTreeNode(AND_STA, "", 0);
								temp2->child[0]->copy_tree(ptree->child[0]->child[1]);
								temp2->child[1] = new CTreeNode(AND_STA, "", 0);
								temp2->child[1]->copy_tree(ptree->child[1]);
							}
							temp3 = new CTreeNode(OR_STA, "", 0);
							temp3->child[0] = new CTreeNode(AND_STA, "", 0);
							temp3->child[0]->copy_tree(temp1);
							temp3->child[1] = new CTreeNode(AND_STA, "", 0);
							temp3->child[1]->copy_tree(temp2);

							ptree->copy_tree(temp3);

							delete temp1;
							delete temp2;
							delete temp3;

							AND(ptree->child[0]);
							AND(ptree->child[1]);
						}
						else
							//P && Q , Q is(Q1 || Q2)  --> (P && Q1) || (P && Q2)
							if (ptree->child[1] != NULL && ptree->child[1]->type == OR_STA)
							{
								if (ptree->child[1]->child[0] != NULL && ptree->child[1]->child[0]->type == AND_STA && ((ptree->child[1]->child[0]->child[0] != NULL && ptree->child[0]->compare(ptree->child[1]->child[0]->child[0])) || (ptree->child[1]->child[0]->child[1] != NULL && ptree->child[0]->compare(ptree->child[1]->child[0]->child[1]))))
								{
									//p1 && ((p1 && p2) || q)  ///  p2 && ((p1 && p2) || q)
									temp1 = new CTreeNode(AND_STA, "", 0);
									temp1->copy_tree(ptree->child[1]->child[0]);
								}
								else
								{
									temp1 = new CTreeNode(AND_STA, "", 0);
									temp1->child[0] = new CTreeNode(AND_STA, "", 0);
									temp1->child[0]->copy_tree(ptree->child[0]);
									temp1->child[1] = new CTreeNode(AND_STA, "", 0);
									temp1->child[1]->copy_tree(ptree->child[1]->child[0]);
								}

								if (ptree->child[1]->child[1] != NULL && ptree->child[1]->child[1]->type == AND_STA && ((ptree->child[1]->child[1]->child[0] != NULL && ptree->child[0]->compare(ptree->child[1]->child[1]->child[0])) || (ptree->child[1]->child[1]->child[1] != NULL && ptree->child[0]->compare(ptree->child[1]->child[1]->child[1]))))
								{
									// q1 && (p || (q1 && q2))   ////  q2 && (p || (q1 && q2))
									temp2 = new CTreeNode(AND_STA, "", 0);
									temp2->copy_tree(ptree->child[1]->child[1]);
								}
								else
								{
									temp2 = new CTreeNode(AND_STA, "", 0);
									temp2->child[0] = new CTreeNode(AND_STA, "", 0);
									temp2->child[0]->copy_tree(ptree->child[0]);
									temp2->child[1] = new CTreeNode(AND_STA, "", 0);
									temp2->child[1]->copy_tree(ptree->child[1]->child[1]);
								}
								temp3 = new CTreeNode(OR_STA, "", 0);
								temp3->child[0] = new CTreeNode(AND_STA, "", 0);
								temp3->child[0]->copy_tree(temp1);
								temp3->child[1] = new CTreeNode(AND_STA, "", 0);
								temp3->child[1]->copy_tree(temp2);

								ptree->copy_tree(temp3);

								delete temp1;
								delete temp2;
								delete temp3;

								AND(ptree->child[0]);
								AND(ptree->child[1]);
							}

							else
								//P && Q , P is (Pe && empty) Q is (Qe && empty) --> (Pe && Qe) && empty
								if (ptree->child[0] != NULL && ptree->child[0]->type == AND_STA && (ptree->child[0]->child[0]->type == EMPTY_EXP || ptree->child[0]->child[1]->type == EMPTY_EXP) && ptree->child[1] != NULL && ptree->child[1]->type == AND_STA && (ptree->child[1]->child[0]->type == EMPTY_EXP || ptree->child[1]->child[1]->type == EMPTY_EXP))
								{
									temp1 = new CTreeNode(AND_STA, "", 0);
									if (ptree->child[0]->child[0]->type == EMPTY_EXP)
									{
										temp1->child[0] = new CTreeNode(AND_STA, "", 0);
										temp1->child[0]->copy_tree(ptree->child[0]->child[1]);
									}
									else
									{
										temp1->child[0] = new CTreeNode(AND_STA, "", 0);
										temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
									}
									if (ptree->child[1]->child[0]->type == EMPTY_EXP)
									{
										temp1->child[1] = new CTreeNode(AND_STA, "", 0);
										temp1->child[1]->copy_tree(ptree->child[1]->child[1]);
									}
									else
									{
										temp1->child[1] = new CTreeNode(AND_STA, "", 0);
										temp1->child[1]->copy_tree(ptree->child[1]->child[0]);
									}

									temp2 = new CTreeNode(EMPTY_EXP, "EMPTY", 0);

									temp3 = new CTreeNode(AND_STA, "", 0);
									temp3->child[0] = new CTreeNode(AND_STA, "", 0);
									temp3->child[0]->copy_tree(temp1);
									temp3->child[1] = new CTreeNode(AND_STA, "", 0);
									temp3->child[1]->copy_tree(temp2);

									ptree->copy_tree(temp3);
									delete temp2;

									delete temp1;
									delete temp3;

								}


	/////////////////////////////////////////////////
	////////////////////  add  /////////////////////
	//(p && empty) && empty --> p && empty
								else
									if (ptree->child[1]->type == EMPTY_EXP && ptree->child[0]->type == AND_STA && (ptree->child[0]->child[0]->type == EMPTY_EXP || ptree->child[0]->child[1]->type == EMPTY_EXP))
										ptree->copy_tree(ptree->child[0]);
	//empty && (p && empty) --> p && empty
									else
										if (ptree->child[0]->type == EMPTY_EXP && ptree->child[1]->type == AND_STA && (ptree->child[1]->child[0]->type == EMPTY_EXP || ptree->child[1]->child[1]->type == EMPTY_EXP))
											ptree->copy_tree(ptree->child[1]);

	/////////////// add over  /////////////////////


										else
											//P && Q ,P is (Pi && @Pi') Q is(Qi && @Qi') --> Pi && Qi && ()(Pi' && Qi')
											if (ptree->child[0] != NULL && ptree->child[0]->type == AND_STA && (ptree->child[0]->child[0]->type == NEXT_STA || ptree->child[0]->child[1]->type == NEXT_STA) && ptree->child[1] != NULL && ptree->child[1]->type == AND_STA && (ptree->child[1]->child[0]->type == NEXT_STA || ptree->child[1]->child[1]->type == NEXT_STA))
											{
												temp1 = new CTreeNode(AND_STA, "", 0);
												temp2 = new CTreeNode(AND_STA, "", 0);
												if (ptree->child[0]->child[0]->type == NEXT_STA)
												{
													temp1->child[0] = new CTreeNode(AND_STA, "", 0);
													temp1->child[0]->copy_tree(ptree->child[0]->child[1]);
													temp2->child[0] = new CTreeNode(AND_STA, "", 0);
													temp2->child[0]->copy_tree(ptree->child[0]->child[0]->child[0]);
												}
												else
												{
													temp1->child[0] = new CTreeNode(AND_STA, "", 0);
													temp1->child[0]->copy_tree(ptree->child[0]->child[0]);
													temp2->child[0] = new CTreeNode(AND_STA, "", 0);
													temp2->child[0]->copy_tree(ptree->child[0]->child[1]->child[0]);
												}
												if (ptree->child[1]->child[0]->type == NEXT_STA)
												{
													temp1->child[1] = new CTreeNode(AND_STA, "", 0);
													temp1->child[1]->copy_tree(ptree->child[1]->child[1]);
													temp2->child[1] = new CTreeNode(AND_STA, "", 0);
													temp2->child[1]->copy_tree(ptree->child[1]->child[0]->child[0]);
												}
												else
												{
													temp1->child[1] = new CTreeNode(AND_STA, "", 0);
													temp1->child[1]->copy_tree(ptree->child[1]->child[0]);
													temp2->child[1] = new CTreeNode(AND_STA, "", 0);
													temp2->child[1]->copy_tree(ptree->child[1]->child[1]->child[0]);
												}

												temp3 = new CTreeNode(NEXT_STA, "", 0);
												temp3->child[0] = new CTreeNode(AND_STA, "", 0);
												temp3->child[0]->copy_tree(temp2);

												temp4 = new CTreeNode(AND_STA, "", 0);
												temp4->child[0] = new CTreeNode(AND_STA, "", 0);
												temp4->child[0]->copy_tree(temp1);
												temp4->child[1] = new CTreeNode(AND_STA, "", 0);
												temp4->child[1]->copy_tree(temp3);


												ptree->copy_tree(temp4);

												delete temp1;
												delete temp2;
												delete temp3;
												delete temp4;
											}
											else
												//P && Q ,P is @P ,Q is (Q && @Q) --> Q && ()(p && q)
												if (ptree->child[0] != NULL && ptree->child[0]->type == NEXT_STA && ptree->child[1] != NULL && ptree->child[1]->type == AND_STA && (ptree->child[1]->child[0]->type == NEXT_STA || ptree->child[1]->child[1]->type == NEXT_STA))
												{
													temp1 = new CTreeNode(AND_STA, "", 0);
													temp2 = new CTreeNode(AND_STA, "", 0);
													temp2->child[0] = new CTreeNode(AND_STA, "", 0);

													temp2->child[0]->copy_tree(ptree->child[0]->child[0]);

													if (ptree->child[1]->child[0]->type == NEXT_STA)
													{
														temp1->copy_tree(ptree->child[1]->child[1]);
														temp2->child[1] = new CTreeNode(AND_STA, "", 0);
														temp2->child[1]->copy_tree(ptree->child[1]->child[0]->child[0]);
													}
													else
													{
														temp1->copy_tree(ptree->child[1]->child[0]);
														temp2->child[1] = new CTreeNode(AND_STA, "", 0);
														temp2->child[1]->copy_tree(ptree->child[1]->child[1]->child[0]);
													}

													temp3 = new CTreeNode(NEXT_STA, "", 0);
													temp3->child[0] = new CTreeNode(AND_STA, "", 0);
													temp3->child[0]->copy_tree(temp2);

													temp4 = new CTreeNode(AND_STA, "", 0);
													temp4->child[0] = new CTreeNode(AND_STA, "", 0);
													temp4->child[0]->copy_tree(temp1);
													temp4->child[1] = new CTreeNode(AND_STA, "", 0);
													temp4->child[1]->copy_tree(temp3);


													ptree->copy_tree(temp4);

													delete temp1;
													delete temp2;
													delete temp3;
													delete temp4;
												}
												else
													//P && Q ,P is (P && @p) ,Q is @q --> P && ()(p && q)
													if (ptree->child[1] != NULL && ptree->child[1]->type == NEXT_STA && ptree->child[0] != NULL && ptree->child[0]->type == AND_STA && (ptree->child[0]->child[0]->type == NEXT_STA || ptree->child[0]->child[1]->type == NEXT_STA))
													{
														temp1 = new CTreeNode(AND_STA, "", 0);
														temp2 = new CTreeNode(AND_STA, "", 0);
														temp2->child[1] = new CTreeNode(AND_STA, "", 0);

														temp2->child[1]->copy_tree(ptree->child[1]->child[0]);

														if (ptree->child[0]->child[0]->type == NEXT_STA)
														{
															temp1->copy_tree(ptree->child[0]->child[1]);
															temp2->child[0] = new CTreeNode(AND_STA, "", 0);
															temp2->child[0]->copy_tree(ptree->child[0]->child[0]->child[0]);
														}
														else
														{
															temp1->copy_tree(ptree->child[0]->child[0]);
															temp2->child[0] = new CTreeNode(AND_STA, "", 0);
															temp2->child[0]->copy_tree(ptree->child[0]->child[1]->child[0]);
														}

														temp3 = new CTreeNode(NEXT_STA, "", 0);
														temp3->child[0] = new CTreeNode(AND_STA, "", 0);
														temp3->child[0]->copy_tree(temp2);

														temp4 = new CTreeNode(AND_STA, "", 0);
														temp4->child[0] = new CTreeNode(AND_STA, "", 0);
														temp4->child[0]->copy_tree(temp1);
														temp4->child[1] = new CTreeNode(AND_STA, "", 0);
														temp4->child[1]->copy_tree(temp3);


														ptree->copy_tree(temp4);

														delete temp1;
														delete temp2;
														delete temp3;
														delete temp4;
													}
	//P && Q, contain @ && empty --> false
													else
													{
														Ema = 0;
														Nea = 0;
														EmNea(ptree);
														if (Ema == 1 && Nea == 1)
														{
															temp1 = new CTreeNode(FALSE_EXP, "FALSE", 0);
															ptree->copy_tree(temp1);
															delete temp1;
														}
													}
}


void CNFMachine::NF(CTreeNode * ptree)
{
	PRE(ptree);
	CTreeNode *temp1, *temp2, *temp3, *temp4, *temp5, *temp6;
	SFA = 1;
	SF(ptree);
	//没有时序操作符时
	if (SFA == 1)
	{
		DNF(ptree);
		NFDNF(ptree);
	}
	//有时序操作符时，根据最外层操作符不同而分情况处理
	else
	{
		switch (ptree->type) {

		case FIN_EXP:
			//fin(p) --> p && empty || ()fin(p)
			temp1 = new CTreeNode(OR_STA, "OR", 0);
			temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
			temp1->child[0]->child[0] = new CTreeNode(AND_STA, "AND", 0);
			temp1->child[0]->child[0]->copy_tree(ptree->child[0]);
			temp1->child[0]->child[1] = new CTreeNode(EMPTY_EXP, "EMPTY", 0);
			temp1->child[1] = new CTreeNode(NEXT_STA, "", 0);
			temp1->child[1]->child[0] = new CTreeNode(AND_STA, "AND", 0);
			temp1->child[1]->child[0]->copy_tree(ptree);
			ptree->copy_tree(temp1);
			delete temp1;
			break;

		case CHOPSTAR_STA:
			//added by LXF 2013/08/19 8:58:43
			chop_star_tree(ptree);
			break;
		case PLUS_STA:
			//added by LXF 2013/09/15 10:53:49
			plus_tree(ptree);
			break;
		case AND_STA:
			//()P && Q
			if (ptree->child[0]->type == NEXT_STA && ptree->child[1]->type != EMPTY_EXP)
			{
				SFA = 1;
				SF(ptree->child[1]);
				/*如果是()P && q的情况，而q是纯状态公式的话，就只需调整下前后顺序即可，无需做其他处理*/
				if (SFA == 1)
				{
					//////////////改POST算法时添加的
					temp1 = new CTreeNode(OR_STA, "OR", 0);
					temp1->copy_tree(ptree->child[1]);
					ptree->child[1]->copy_tree(ptree->child[0]);
					ptree->child[0]->copy_tree(temp1);
					delete temp1;
					////////////////
					break;
				}
			}
			//Q && ()P
			if (ptree->child[1]->type == NEXT_STA && ptree->child[0]->type != EMPTY_EXP)
			{
				SFA = 1;
				SF(ptree->child[0]);
				/*如果是q && ()P的情况，而q是纯状态公式的话，无需处理*/
				if (SFA == 1)
				{
					break;
				}
			}
			//empty && Q
			if (ptree->child[0]->type == EMPTY_EXP && ptree->child[1]->type != NEXT_STA)
			{
				SFA = 1;
				SF(ptree->child[1]);
				/*如果是empty && Q的情况，而Q是纯状态公式的话，就只需调整下前后顺序即可，无需做其他处理*/
				if (SFA == 1)
				{
					//////////////改POST算法时添加的
					temp1 = new CTreeNode(OR_STA, "OR", 0);
					temp1->copy_tree(ptree->child[1]);
					ptree->child[1]->copy_tree(ptree->child[0]);
					ptree->child[0]->copy_tree(temp1);
					delete temp1;
					////////////////

					break;
				}
			}
			//P && empty
			if (ptree->child[1]->type == EMPTY_EXP && ptree->child[0]->type != NEXT_STA)
			{
				SFA = 1;
				SF(ptree->child[0]);
				/*如果是P && empty的情况，而P是纯状态公式的话，无需处理*/
				if (SFA == 1)
				{
					break;
				}
			}
			//empty && empty --> empty
			if (ptree->child[0]->type == EMPTY_EXP && ptree->child[1]->type == EMPTY_EXP)
			{
				temp1 = new CTreeNode(EMPTY_EXP, "EMPTY", 0);
				ptree->copy_tree(temp1);
				delete temp1;
				break;
			}
			// False && P  --> false
			if (ptree->child[0]->type == FALSE_EXP || ptree->child[1]->type == FALSE_EXP)
			{
				ptree->type = FALSE_EXP;
				ptree->name_str = "FALSE";
				ptree->child[0] = NULL;
				ptree->child[1] = NULL;
				ptree->child[2] = NULL;
				break;
			}

			////////////////////////////
			//////////////  add  /////////////
			//p && p --> p
			if (ptree->child[0]->compare(ptree->child[1]) && ptree->child[0]->type != EMPTY_EXP)
			{
				ptree->copy_tree(ptree->child[0]);
				NF(ptree);
				break;
			}
			//(p && q) && p --> p && q
			if (ptree->child[0]->type == AND_STA)
			{
				if (POST_findintree(ptree->child[0], ptree->child[1], AND_STA))
				{
					ptree->copy_tree(ptree->child[0]);
					NF(ptree);
					break;
				}
			}
			//p && (p && q) --> p && q
			if (ptree->child[1]->type == AND_STA)
			{
				if (POST_findintree(ptree->child[1], ptree->child[0], AND_STA))
				{
					ptree->copy_tree(ptree->child[1]);
					NF(ptree);
					break;
				}
			}
			///////////////  add over  /////////////
			///////////////////////////////////

			//P && Q
			/*先将前后两部分分别求NF，然后再将两部分“与”起来*/
			NF(ptree->child[0]);
			POST(ptree->child[0]);
			NF(ptree->child[1]);
			POST(ptree->child[1]);
			AND(ptree);
			break;
		case OR_STA:

			/*或起来的两部分，直接将前后两部分分别求NF即可*/
			NF(ptree->child[0]);
			NF(ptree->child[1]);
			break;
		case TRUE_EXP:
			//true --> empty || ()true
			ptree->type = OR_STA;
			temp1 = new CTreeNode(EMPTY_EXP, "EMPTY", 0);
			temp2 = new CTreeNode(TRUE_EXP, "TRUE", 0);
			temp3 = new CTreeNode(NEXT_STA, "", 0);
			temp3->child[0] = new CTreeNode(AND_STA, "", 0);
			temp3->child[0]->copy_tree(temp2);
			ptree->child[0] = new CTreeNode(EMPTY_EXP, "EMPTY", 0);
			ptree->child[0]->copy_tree(temp1);
			ptree->child[1] = new CTreeNode(NEXT_STA, "", 0);
			ptree->child[1]->copy_tree(temp3);
			delete temp1;
			delete temp2;

			delete temp3;
			break;
		case FALSE_EXP:

			break;
		case MORE_EXP:
			//more --> ()true
			ptree->type = NEXT_STA;
			ptree->child[0] = new CTreeNode(TRUE_EXP, "TRUE", 0);
			break;
		case SKIP_EXP:
			// skip -> ()empty
			ptree->type = NEXT_STA;
			ptree->child[0] = new CTreeNode(EMPTY_EXP, "EMPTY", 0);
			break;
		case CHOP_STA:
		{
			//减少new ,delete 次数,整理为统一结构
			while (ptree->child[0]->type == CHOP_STA)
			{
				temp1 = new CTreeNode(CHOP_STA, "", 0);
				temp1->child[0] = new CTreeNode(AND_STA, "", 0);
				temp1->child[1] = new CTreeNode(AND_STA, "", 0);
				temp2 = new CTreeNode(AND_STA, "", 0);
				temp1->child[0]->copy_tree(ptree->child[0]->child[1]);
				temp1->child[1]->copy_tree(ptree->child[1]);
				temp2->copy_tree(ptree->child[0]->child[0]);
				ptree->child[0]->copy_tree(temp2);
				ptree->child[1]->copy_tree(temp1);

				delete temp1;
				delete temp2;
			}

		}
		//最外层操作符为;的直接用CHOP算法处理
		CHOP(ptree);//改为原来的处理chop的算法
		break;
		case NEGATION_STA:
			//change to
			ptree->copy_tree(ptree->child[0]);
			//////////// add ////////////////////
			///////////////////////////////////
			//如果是双层非，直接去掉双层非后求NF即可. !!p --> p
			if (ptree->type == NEGATION_STA)
			{
				ptree->copy_tree(ptree->child[0]);
				NF(ptree);
			}
			else
				//////////  add over  //////////////////
				//////////////////////////////////////
				//!empty --> ()true
				if (ptree->type == EMPTY_EXP)
				{
					temp1 = new CTreeNode(NEXT_STA, "", 0);
					temp1->child[0] = new CTreeNode(TRUE_EXP, "TRUE", 0);
					ptree->copy_tree(temp1);
					delete temp1;
				}
			//!true --> false
				else
					if (ptree->type == TRUE_EXP)
					{
						temp1 = new CTreeNode(FALSE_EXP, "FALSE", 0);
						ptree->copy_tree(temp1);
						delete temp1;
					}
			//!false --> true
					else
						if (ptree->type == FALSE_EXP)
						{
							temp1 = new CTreeNode(TRUE_EXP, "TRUE", 0);
							ptree->copy_tree(temp1);
							delete temp1;
							NF(ptree);
						}
			// !more --> empty
						else
							if (ptree->type == MORE_EXP)
							{
								temp1 = new CTreeNode(EMPTY_EXP, "EMPTY", 0);
								ptree->copy_tree(temp1);
								delete temp1;
							}
			//!(T;P)=[]!P
			///////////
							else
							{
								//此时的ptree是原ptree去掉!后的树结构
								NF(ptree);
								POST(ptree);
								//!false --> true
								if (ptree->type == FALSE_EXP)
								{
									temp1 = new CTreeNode(TRUE_EXP, "TRUE", 0);
									ptree->copy_tree(temp1);
									delete temp1;
									NF(ptree);
								}
								//!true --> false
								else
									if (ptree->type == TRUE_EXP)
									{
										temp1 = new CTreeNode(FALSE_EXP, "FALSE", 0);
										ptree->copy_tree(temp1);
										delete temp1;
									}
								//****************! empty = o true*****************//zxm add  2014.02.11
									else if (ptree->type == EMPTY_EXP)
									{
										temp1 = new CTreeNode(NEXT_STA, "", 0);
										temp1->child[0] = new CTreeNode(TRUE_EXP, "TRUE", 0);
										ptree->copy_tree(temp1);
										delete temp1;
									}
								/*如果是!P结构，前面求出P的NF，接下来要求出其完全正则式，最后再对完全正则式处理即可*/
									else
									{
										emptytree = new CTreeNode(OR_STA, "", 0);
										nexttree = new CTreeNode(OR_STA, "", 0);
										if (ptree->type == OR_STA)
										{
											CONF_tree(ptree);  //语法树为几部分的或，则分别处理树的子孩子中的empty,next
										}
										else
											if (ptree->type == AND_STA)
											{
												if (ptree->child[0] != NULL && ptree->child[0]->type == NEXT_STA)
												{
													CONF_nexttree(ptree);
												}
												else
													if (ptree->child[1] != NULL && ptree->child[1]->type == NEXT_STA)
													{
														CONF_nexttree(ptree);
													}


												/////////////////////////////////////////
												///////////////    Add   //////////////
												if (ptree->child[0] != NULL && ptree->child[0]->type == EMPTY_EXP)
												{
													CONF_emptytree(ptree);
												}
												else
													if (ptree->child[1] != NULL && ptree->child[1]->type == EMPTY_EXP)
													{
														CONF_emptytree(ptree);
													}

												//////////////////   Add over   //////////////
												///////////////////////////////////////////


											}
											else
												if (ptree->type == EMPTY_EXP)
												{
													CONF_emptytree(ptree);
												}
												else
													if (ptree->type == NEXT_STA)  //前面已有empty的讨论，所以不再讨论
													{
														CONF_nexttree(ptree);
													}
										CONF_emptytree1();
										CONF_nexttree1();
										if (!(nexttree->child[0] == NULL&&nexttree->child[1] == NULL))
										{
											CONF(nexttree);
										}

										int hasempty = 1;
										int hasnext = 1;
										if (emptytree->child[0] == NULL && emptytree->child[1] == NULL)
										{
											hasempty = 0;
											ptree->copy_tree(nexttree);
										}
										else if (nexttree->child[0] == NULL && nexttree->child[1] == NULL)
										{
											hasnext = 0;
											ptree->copy_tree(emptytree);
										}
										else
										{
											temp2 = new CTreeNode(OR_STA, "", 0);
											temp2->child[0] = new CTreeNode(OR_STA, "", 0);
											temp2->child[1] = new CTreeNode(OR_STA, "", 0);
											temp2->child[0]->copy_tree(emptytree);
											temp2->child[1]->copy_tree(nexttree);
											ptree->copy_tree(temp2);
											delete temp2;

										}
										//内存

										delete emptytree;
										delete nexttree;
										//内存
										if (ptree->type == NEXT_STA)
										{
											temp1 = new CTreeNode(NEGATION_STA, "", 0);
											temp1->child[0] = new CTreeNode(AND_STA, "", 0);
											temp1->child[0]->copy_tree(ptree->child[0]);
											temp2 = new CTreeNode(NEXT_STA, "", 0);
											temp2->child[0] = new CTreeNode(AND_STA, "", 0);
											temp2->child[0]->copy_tree(temp1);
											ptree->copy_tree(temp2);

											delete temp1;
											delete temp2;

										}
										else
										{
											NEG(ptree); // 对完全正则式求非，即可得到以!为主操作符的原公式的NF
											if (hasempty == 0)
											{
												CTreeNode *emptytree, *temptree;
												emptytree = new CTreeNode(EMPTY_EXP, "EMPTY", 0);
												temptree = new CTreeNode(OR_STA, "", 0);
												temptree->child[0] = new CTreeNode(AND_STA, "", 0);
												temptree->child[0]->copy_tree(emptytree);
												temptree->child[1] = new CTreeNode(AND_STA, "", 0);
												temptree->child[1]->copy_tree(ptree);

												ptree->copy_tree(temptree);
												delete emptytree;

												delete temptree;

											}
											if (hasnext == 0)
											{
												CTreeNode *nexttree, *temptree;
												nexttree = new CTreeNode(NEXT_STA, "NEXT", 0);
												nexttree->child[0] = new CTreeNode(TRUE_EXP, "TRUE", 0);
												temptree = new CTreeNode(OR_STA, "", 0);
												temptree->child[1] = new CTreeNode(AND_STA, "", 0);
												temptree->child[1]->copy_tree(nexttree);
												temptree->child[0] = new CTreeNode(AND_STA, "", 0);
												temptree->child[0]->copy_tree(ptree);

												ptree->copy_tree(temptree);
												delete nexttree;

												delete temptree;

											}
										}//	else
									}//else

							}//else
			break;
		case ALWAYS_STA:
			//NF([]p) --> NF(p && empty) || NF(p && ()[]p)
			temp1 = new CTreeNode(AND_STA, "", 0);
			temp1->copy_tree(ptree->child[0]);
			temp2 = new CTreeNode(EMPTY_EXP, "EMPTY", 0);
			temp3 = new CTreeNode(AND_STA, "", 0);
			temp3->child[0] = new CTreeNode(AND_STA, "", 0);
			temp3->child[1] = new CTreeNode(AND_STA, "", 0);
			temp3->child[0]->copy_tree(temp1);
			temp3->child[1]->copy_tree(temp2);
			temp4 = new CTreeNode(ALWAYS_STA, "", 0);
			temp4->child[0] = new CTreeNode(AND_STA, "", 0);
			temp4->child[0]->copy_tree(temp1);
			temp5 = new CTreeNode(NEXT_STA, "", 0);
			temp5->child[0] = new CTreeNode(AND_STA, "", 0);
			temp5->child[0]->copy_tree(temp4);
			temp6 = new CTreeNode(AND_STA, "", 0);
			temp6->child[0] = new CTreeNode(AND_STA, "", 0);
			temp6->child[1] = new CTreeNode(AND_STA, "", 0);
			temp6->child[0]->copy_tree(temp1);
			temp6->child[1]->copy_tree(temp5);

			delete temp2;
			temp2 = new CTreeNode(OR_STA, "", 0);
			temp2->child[0] = new CTreeNode(AND_STA, "", 0);
			temp2->child[1] = new CTreeNode(AND_STA, "", 0);
			temp2->child[0]->copy_tree(temp3);
			temp2->child[1]->copy_tree(temp6);

			ptree->copy_tree(temp2);

			delete temp2;

			delete temp1;
			delete temp3;
			delete temp4;
			delete temp5;
			delete temp6;


			NF(ptree->child[0]);
			NF(ptree->child[1]);
			break;
		case PROJECTION_STA:
			//主操作符为prj的直接用PRJ算法处理
			PRJ(ptree);
			break;
		case STIME_STA:
			//首先将<>p转换为true;p，然后再求true;p的NF
			/*
			temp1=new CTreeNode(CHOP_STA,"",0);
			temp1->child[0]=new CTreeNode(AND_STA,"",0);
			temp1->child[1]=new CTreeNode(AND_STA,"",0);
			temp2=new CTreeNode(TRUE_EXP,"TRUE",0);
			temp1->child[0]->copy_tree(temp2);
			temp1->child[1]->copy_tree(ptree->child[0]);
			ptree->copy_tree(temp1);
			delete temp2;

			delete temp1;

			NF(ptree);*/
			/*
			//added by LXF 2013/08/27 10:01:21
			//不把<>p与true;p联系
			//NF(ptree->child[0]);
			temp1=new CTreeNode(OR_STA,"OR",0);//p||()<>p
			temp1->child[0]=new CTreeNode(AND_STA,"",0);
			temp1->child[1]=new CTreeNode(NEXT_STA,"",0);
			temp1->child[0]->copy_tree(ptree->child[0]);//p
			temp1->child[1]->child[0]=new CTreeNode(AND_STA,"",0);
			temp1->child[1]->child[0]->copy_tree(ptree);//<>p
			ptree->copy_tree(temp1);
			NF(ptree->child[0]);
			delete temp1;*/
			temp1 = new CTreeNode(CHOP_STA, "", 0);
			temp1->child[0] = new CTreeNode(AND_STA, "", 0);
			temp1->child[1] = new CTreeNode(AND_STA, "", 0);
			temp2 = new CTreeNode(TRUE_EXP, "TRUE", 0);
			temp1->child[0]->copy_tree(temp2);
			temp1->child[1]->copy_tree(ptree->child[0]);
			ptree->copy_tree(temp1);
			delete temp2;

			delete temp1;

			NF(ptree);
			break;
		case LEN_STA:
			length(ptree);
			break;
		case UNTIL_STA:
			UNTIL(ptree);
			break;
		default:
			break;
		}
	}


}
//判断是否是单纯的状态公式，即不包含时序操作符，其中用SFA变量记录，一旦包含时序操作符，则SFA变量的值变成0，否则为1
void CNFMachine::SF(CTreeNode * ptree)
{
	if (ptree->type == LEN_STA || ptree->type == FIN_EXP || ptree->type == UNTIL_STA || ptree->type == CHOPSTAR_STA || ptree->type == PLUS_STA || ptree->type == PROJECTION_STA || ptree->type == STIME_STA || ptree->type == CHOP_STA || ptree->type == CHOP_STA || ptree->type == MORE_EXP || ptree->type == SKIP_EXP || ptree->type == ALWAYS_STA || ptree->type == NEXT_STA || ptree->type == TRUE_EXP || ptree->type == FALSE_EXP || ptree->type == EMPTY_EXP)
	{
		SFA = 0;
	}
	if (ptree->child[0] != NULL || ptree->child[1] != NULL || ptree->child[2] != NULL)
	{
		if (ptree->type == LEN_STA || ptree->type == FIN_EXP || ptree->type == UNTIL_STA || ptree->type == CHOPSTAR_STA || ptree->type == PLUS_STA || ptree->type == PROJECTION_STA || ptree->type == STIME_STA || ptree->type == CHOP_STA || ptree->type == MORE_EXP || ptree->type == SKIP_EXP || ptree->type == ALWAYS_STA || ptree->type == NEXT_STA || ptree->type == TRUE_EXP || ptree->type == FALSE_EXP || ptree->type == EMPTY_EXP)
		{
			SFA = 0;
		}

		if (ptree->child[0] != NULL){ SF(ptree->child[0]); }
		if (ptree->child[1] != NULL){ SF(ptree->child[1]); }
		if (ptree->child[2] != NULL){ SF(ptree->child[2]); }
	}

}

//判断公式中是否包含empty和()，用变量Ema和Nea记录，如果包含empty则Ema的值为1，如果包含()则Nea的值为1
void CNFMachine::EmNea(CTreeNode * ptree)
{
	if (ptree->child[0] != NULL || ptree->child[1] != NULL)
	{
		if (ptree->type == AND_STA)
		{
			if (ptree->child[0]->type == EMPTY_EXP || ptree->child[1]->type == EMPTY_EXP)
			{
				Ema = 1;
			}
			if (ptree->child[0]->type == NEXT_STA || ptree->child[1]->type == NEXT_STA)
			{
				Nea = 1;
			}
		}

		if (ptree->child[0] != NULL && ptree->child[0]->type != NEXT_STA && ptree->child[0]->type != EMPTY_EXP){ EmNea(ptree->child[0]); }
		if (ptree->child[1] != NULL && ptree->child[1]->type != NEXT_STA && ptree->child[1]->type != EMPTY_EXP){ EmNea(ptree->child[1]); }
	}
}
//added by LXF 2013/08/19 9:15:34
//chop star类型公式的求范式函数
void CNFMachine::chop_star_tree(CTreeNode *ptree)
{
	CTreeNode *Temp;//表示将要被求NF以及转换的公式
	Temp = new CTreeNode(OR_STA, "OR", 0);
	Temp->child[0] = new CTreeNode(EMPTY_EXP, "EMPTY", 0);//左子树EMPTY
	Temp->child[1] = new CTreeNode(OR_STA, "OR", 0);//右子树存放future部分
	Temp->child[1]->copy_tree(ptree->child[0]);//得到公式p
	NF(Temp->child[1]);//求得公式p的NF
	// 	 	string cs="";
	// 	 	showout="";
	//  	cs=show(Temp->child[1]);
	POST(Temp->child[1]);
	string cs = "";
	showout = "";
	cs = show(Temp->child[1]);
	handleChopstarRewritting(Temp, ptree);
	ptree->copy_tree(Temp);
	delete Temp;
}
//added by LXF 2013/08/19 9:58:03
//处理chop star的一个future部分
void handleFutureOfChopstar(CTreeNode* ptree, CTreeNode* starTree)
{
	CTreeNode *temp1;
	if (ptree->type == NEXT_STA)//()p
	{
		temp1 = new CTreeNode(CHOP_STA, "CHOP", 0);
		temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp1->child[1] = new CTreeNode(AND_STA, "AND", 0);
		temp1->child[0]->copy_tree(ptree->child[0]);
		temp1->child[1]->copy_tree(starTree);
		ptree->child[0]->copy_tree(temp1);
		delete temp1;
	}
	else//pi&&()qi
	{
		temp1 = new CTreeNode(CHOP_STA, "CHOP", 0);
		temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp1->child[1] = new CTreeNode(AND_STA, "AND", 0);
		temp1->child[0]->copy_tree(ptree->child[1]->child[0]);
		temp1->child[1]->copy_tree(starTree);
		ptree->child[1]->child[0]->copy_tree(temp1);
		delete temp1;
	}
}
//added by LXF 2013/08/19 9:43:12
//处理chop star求范式过程中的重写过程
void CNFMachine::handleChopstarRewritting(CTreeNode *ptree, CTreeNode* starTree)
{
	//重写包含两个部分：1.去掉EMPTY部分 2.将next部分按理论来替代
	CTreeNode *temp1, *temp2, *temp3;
	temp1 = new CTreeNode(EMPTY_EXP, "EMPTY", 0);
	//仅一项termina部分的情况
	if (ptree->child[1]->type != OR_STA && (ptree->child[1]->type == EMPTY_EXP || ptree->child[1]->child[1] != NULL&&ptree->child[1]->child[1]->type == EMPTY_EXP))//含有EMPTY部分或者是就是EMPTY的时候
	{
		ptree->copy_tree(ptree->child[0]);
	}
	//仅一项future部分 ()p
	else if (ptree->child[1]->type != OR_STA && (ptree->child[1]->type == NEXT_STA || ptree->child[1]->child[1] != NULL&&ptree->child[1]->child[1]->type == NEXT_STA))
	{
		handleFutureOfChopstar(ptree->child[1], starTree);
	}
	else
	{
		adjust_right_child_or(ptree->child[1]);
		temp2 = ptree->child[1];
		temp3 = ptree;//除了第一步外，temp2为temp3的左子树
		while (temp2->type == OR_STA && temp2->child[0]->type == OR_STA)
		{
			if (temp2->child[1]->type == EMPTY_EXP || temp2->child[1]->child[1] != NULL&&temp2->child[1]->child[1]->type == EMPTY_EXP)
			{
				temp2->copy_tree(temp2->child[0]);
			}
			else
			{
				handleFutureOfChopstar(temp2->child[1], starTree);
				temp3 = temp2;
				temp2 = temp2->child[0];
			}
			adjust_right_child_or(temp2);
		}
		if (temp2->type == OR_STA && temp2->child[0]->type != OR_STA)
		{
			if (temp2->child[1]->type == EMPTY_EXP || temp2->child[1]->child[1] != NULL&&temp2->child[1]->child[1]->type == EMPTY_EXP)
			{
				temp2->copy_tree(temp2->child[0]);
				if (temp2->child[1]->type == EMPTY_EXP || temp2->type == EMPTY_EXP)
				{
					temp3->copy_tree(temp3->child[1]);
				}
				else
				{
					handleFutureOfChopstar(temp2, starTree);
				}
			}
			else
			{
				handleFutureOfChopstar(temp2->child[1], starTree);
				temp3 = temp2;
				temp2 = temp2->child[0];
				if (temp2->type == EMPTY_EXP || temp2->child[1] != NULL&&temp2->child[1]->type == EMPTY_EXP)//zxm  fised 2014.03.21
				{
					temp3->copy_tree(temp3->child[1]);
				}
				else
				{
					handleFutureOfChopstar(temp2, starTree);
				}
			}
		}
	}
	delete temp1;
}

void CNFMachine::deleteAllEmptyInChop(CTreeNode *ptree)
{
	adjust_right_child_chop(ptree);
	CTreeNode *temp1;
	temp1 = ptree;
	while (temp1->type == CHOP_STA && temp1->child[0]->type == CHOP_STA)
	{
		if (temp1->child[1]->type == EMPTY_EXP)
		{
			temp1->copy_tree(temp1->child[0]);

		}
		else
		{
			temp1 = temp1->child[0];
		}
		adjust_right_child_chop(temp1);
	}
	if (temp1->type == CHOP_STA && temp1->child[0]->type != CHOP_STA)
	{
		if (temp1->child[1]->type == EMPTY_EXP)
		{
			temp1->copy_tree(temp1->child[0]);
			return;
		}
		if (temp1->child[0]->type == EMPTY_EXP)
		{
			temp1->copy_tree(temp1->child[1]);
			return;
		}
	}
}
int strToInt(string str)
{
	return atoi(str.c_str());
}
//added by LXF 2013/09/04 15:20:55
void CNFMachine::length(CTreeNode *ptree)
{
	CTreeNode* temp, *temp1;
	temp1 = new CTreeNode(EMPTY_EXP, "EMPTY", 0);
	int lenInt;
	lenInt = strToInt(ptree->child[0]->name_str.c_str());
	if (lenInt == 0)
	{
		delete ptree;
		ptree->copy_tree(temp1);
	}
	else
	{
		while (lenInt != 0)
		{

			temp = new CTreeNode(NEXT_STA, "NEXT", 0);
			temp->child[0] = new CTreeNode(AND_STA, "AND", 0);
			temp->child[0]->copy_tree(temp1);
			temp1->copy_tree(temp);
			delete temp;
			lenInt--;
		}
		ptree->copy_tree(temp1);
	}
	delete temp1;
}

void CNFMachine::plus_tree(CTreeNode *ptree)
{
	CTreeNode* newTree = new CTreeNode(CHOP_STA, "CHOP", 0);
	newTree->child[0] = new CTreeNode(AND_STA, "AND", 0);
	newTree->child[0]->copy_tree(ptree->child[0]);
	newTree->child[1] = new CTreeNode(AND_STA, "AND", 0);
	newTree->child[1]->copy_tree(ptree);
	newTree->child[1]->type = CHOPSTAR_STA;
	ptree->copy_tree(newTree);
	delete newTree;
	NF(ptree);
}

void CNFMachine::UNTIL(CTreeNode* ptree)
{
	CTreeNode *temp1, *temp2, *temp3;
	temp1 = new CTreeNode(AND_STA, "AND", 0);
	temp2 = new CTreeNode(AND_STA, "AND", 0);
	temp1->copy_tree(ptree->child[0]);//P
	temp2->copy_tree(ptree->child[1]);//Q
	NF(temp1);
	POST(temp1);
	NF(temp2);
	POST(temp2);
	//Until的特殊处理P只留下future部分并且将ptree加入每一个next部分
	untilReplace(temp1, ptree);
	temp3 = new CTreeNode(OR_STA, "OR", 0);//Q || P && ()(P U Q)
	temp3->child[0] = new CTreeNode(AND_STA, "AND", 0);
	temp3->child[0]->copy_tree(temp2);//Q
	temp3->child[1] = new CTreeNode(AND_STA, "AND", 0);
	temp3->child[1]->copy_tree(temp1);
	delete temp1;
	delete temp2;
	ptree->copy_tree(temp3);
	delete temp3;
}
void consAnd(CTreeNode* res, CTreeNode* left, CTreeNode* right)
{
	res->child[0] = new CTreeNode(AND_STA, "AND", 0);
	res->child[0]->copy_tree(left);
	res->child[1] = new CTreeNode(AND_STA, "AND", 0);
	res->child[1]->copy_tree(right);
}


void CNFMachine::untilReplace(CTreeNode *temp1, CTreeNode *ptree)//将temp1中的empty子公式去掉，ptree为原来的until公式
{
	CTreeNode *temp2, *curTree;
	//公式没有析取符号，仅一项
	if (temp1->type != OR_STA)
	{
		if (temp1->type == EMPTY_EXP)
		{
			ptree_to_false(temp1);
		}
		else if (temp1->type == NEXT_STA)
		{
			temp2 = new CTreeNode(AND_STA, "AND", 0);
			consAnd(temp2, temp1->child[0], ptree);
			temp1->child[0]->copy_tree(temp2);
			delete temp2;
		}
		else if (temp1->type == AND_STA)
		{
			if (temp1->child[1]->type == EMPTY_EXP)
			{
				ptree_to_false(temp1);
			}
			else if (temp1->child[1]->type == NEXT_STA)
			{
				temp2 = new CTreeNode(AND_STA, "AND", 0);
				consAnd(temp2, temp1->child[1]->child[0], ptree);
				temp1->child[1]->child[0]->copy_tree(temp2);
				delete temp2;
			}
		}
		return;
	}
	adjust_right_child_or(temp1);
	curTree = temp1;
	while (curTree->type == OR_STA && curTree->child[0]->type == OR_STA)
	{
		if (curTree->child[1]->type == EMPTY_EXP || (curTree->child[1]->type == AND_STA && curTree->child[1]->child[1]->type == EMPTY_EXP))
		{
			curTree->copy_tree(curTree->child[0]);
		}
		else
		{
			temp2 = new CTreeNode(AND_STA, "AND", 0);
			if (curTree->child[1]->type == NEXT_STA)
			{
				consAnd(temp2, curTree->child[1]->child[0], ptree);
				curTree->child[1]->child[0]->copy_tree(temp2);
			}
			else if (curTree->child[1]->type == AND_STA && curTree->child[1]->child[1]->type == NEXT_STA)
			{
				consAnd(temp2, curTree->child[1]->child[1]->child[0], ptree);
				curTree->child[1]->child[1]->child[0]->copy_tree(temp2);
			}
			delete temp2;
			curTree = curTree->child[0];
		}
		adjust_right_child_or(curTree);
	}
	if (curTree->type == OR_STA && curTree->child[0]->type != OR_STA)
	{
		if (curTree->child[1]->type == EMPTY_EXP || curTree->child[1]->type == AND_STA && curTree->child[1]->child[1]->type == EMPTY_EXP)
		{
			curTree->copy_tree(curTree->child[0]);
			temp2 = new CTreeNode(AND_STA, "AND", 0);
			if (curTree->type = NEXT_STA)
			{
				consAnd(temp2, curTree->child[0], ptree);
				curTree->child[0]->copy_tree(temp2);
			}
			else if (curTree->type == AND_STA && curTree->child[1]->type == NEXT_STA)
			{
				consAnd(temp2, curTree->child[1]->child[0], ptree);
				curTree->child[1]->child[0]->copy_tree(temp2);
			}
			delete temp2;
			return;
		}
		if (curTree->child[0]->type == EMPTY_EXP || curTree->child[0]->type == AND_STA && curTree->child[0]->child[1]->type == EMPTY_EXP)
		{
			curTree->copy_tree(curTree->child[1]);
			temp2 = new CTreeNode(AND_STA, "AND", 0);
			if (curTree->type == NEXT_STA)
			{
				consAnd(temp2, curTree->child[0], ptree);
				curTree->child[0]->copy_tree(temp2);
			}
			else if (curTree->type == AND_STA && curTree->child[1]->type == NEXT_STA)
			{
				consAnd(temp2, curTree->child[1]->child[0], ptree);
				curTree->child[1]->child[0]->copy_tree(temp2);
			}
			delete temp2;
			return;
		}
		else//另个next
		{
			temp2 = new CTreeNode(AND_STA, "AND", 0);
			if (curTree->child[1]->type == NEXT_STA)
			{
				consAnd(temp2, curTree->child[1]->child[0], ptree);
				curTree->child[1]->child[0]->copy_tree(temp2);
			}
			else if (curTree->child[1]->type == AND_STA && curTree->child[1]->child[1]->type == NEXT_STA)
			{
				consAnd(temp2, curTree->child[1]->child[1]->child[0], ptree);
				curTree->child[1]->child[1]->child[0]->copy_tree(temp2);
			}
			delete temp2;
			temp2 = new CTreeNode(AND_STA, "AND", 0);
			if (curTree->child[0]->type == NEXT_STA)
			{
				consAnd(temp2, curTree->child[0]->child[0], ptree);
				curTree->child[0]->child[0]->copy_tree(temp2);
			}
			else if (curTree->child[0]->type == AND_STA && curTree->child[0]->child[1]->type == NEXT_STA)
			{
				consAnd(temp2, curTree->child[0]->child[1]->child[0], ptree);
				curTree->child[0]->child[1]->child[0]->copy_tree(temp2);
			}
			delete temp2;
		}
	}

}

void CNFMachine::PRE_until(CTreeNode *ptree)
{
	//p U false-->false
	if (ptree->child[1]->type == FALSE_EXP)
	{
		ptree_to_false(ptree);
		return;
	}
	//false U p--->p
	if (ptree->child[0]->type == FALSE_EXP)
	{
		ptree->copy_tree(ptree->child[1]);
		PRE(ptree);
		return;
	}
	//empty U p-->p
	if (ptree->child[0]->type == EMPTY_EXP)
	{
		ptree->copy_tree(ptree->child[1]);
		PRE(ptree);
		return;
	}
	//p U empty-->[](more->p)&&<>empty
	if (ptree->child[1]->type == EMPTY_EXP)
	{
		CTreeNode* temp = new CTreeNode(AND_STA, "AND", 0);
		//leftside
		temp->child[0] = new CTreeNode(ALWAYS_STA, "ALWAYS", 0);
		temp->child[0]->child[0] = new CTreeNode(IMPLY_STA, "IMPLY", 0);
		temp->child[0]->child[0]->child[0] = new CTreeNode(MORE_EXP, "MORE", 0);
		temp->child[0]->child[0]->child[1] = new CTreeNode(AND_STA, "AND", 0);
		temp->child[0]->child[0]->child[1]->copy_tree(ptree->child[0]);
		//right
		temp->child[1] = new CTreeNode(STIME_STA, "STIME", 0);
		temp->child[1]->child[0] = new CTreeNode(EMPTY_EXP, "EMPTY", 0);
		ptree->copy_tree(temp);
		delete temp;
		PRE(ptree);
		return;

	}
	//true U p--><>p
	if (ptree->child[0]->type == TRUE_EXP)
	{
		CTreeNode * temp1 = new CTreeNode(STIME_STA, "STIME", 0);
		temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
		PRE(ptree->child[1]);
		temp1->child[0]->copy_tree(ptree->child[1]);
		ptree->copy_tree(temp1);
		PRE(ptree);
		delete temp1;
		return;
	}
	//p U true-->true
	if (ptree->child[1]->type == TRUE_EXP)
	{
		ptree_to_true(ptree);
		return;
	}
	//p U (p && empty)-->[]p&&<>empty
	if (ptree->child[1] != NULL && ptree->child[1]->child[1] != NULL&& ptree->child[1]->child[1]->type == EMPTY_EXP && ptree->child[0]->compare(ptree->child[1]->child[0]))
	{
		CTreeNode* temp = new CTreeNode(AND_STA, "AND", 0);
		temp->child[0] = new CTreeNode(ALWAYS_STA, "ALWAYS", 0);
		temp->child[0]->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp->child[0]->child[0]->copy_tree(ptree->child[0]);
		temp->child[1] = new CTreeNode(STIME_STA, "STIME", 0);
		temp->child[1]->child[0] = new CTreeNode(EMPTY_EXP, "EMPTY", 0);
		ptree->copy_tree(temp);
		PRE(ptree);
		delete temp;
		return;
	}
	/*
	//p U true ---->p
	if (ptree->child[1]->type==TRUE_EXP)
	{
	ptree->copy_tree(ptree->child[0]);
	PRE(ptree);
	return;
	}*/
	//p U (p U q)
	if (ptree->type == UNTIL_STA && ptree->child[1]->type == UNTIL_STA)
	{
		if (ptree->child[0]->compare(ptree->child[1]->child[0]))
		{
			ptree->copy_tree(ptree->child[1]);
			PRE_until(ptree);
		}
	}

	//(p U q) U q
	else if (ptree->type == UNTIL_STA && ptree->child[0]->type == UNTIL_STA)
	{
		if (ptree->child[1]->compare(ptree->child[0]->child[1]))
		{
			ptree->copy_tree(ptree->child[0]);
			PRE_until(ptree);
		}
	}

	//加左右子树的化简

}
