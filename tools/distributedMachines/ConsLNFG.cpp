/*author : 刘晓芳*/

#include"ConsLNFG.h"

/*LNFGNode member functions and other function used*/
//判断是否能在and结构中找到一个直接EMPTY节点
bool findEmptyNodeInAnd(CTreeNode* ptree)
{
	CTreeNode* temp1;
	temp1 = ptree;//从ptree根节点开始遍历and操作符
	bool find = false;
	adjust_right_child_and(temp1);//调整使得右子树不是and节点
	while (temp1->type == AND_STA && temp1->child[0]->type == AND_STA)
	{
		if (temp1->child[1]->type == EMPTY_EXP)
		{
			find = true; return find;
		}//找到以后直接返回，因为我们仅仅在意是否含有EMPTY，而不是含有多少
		temp1 = temp1->child[0];//未找到的话,则继续分析左子树
		adjust_right_child_and(temp1);//调整使得右子树不是and节点
	}
	if (temp1->type == AND_STA && temp1->child[0]->type != AND_STA)//单层and结构的处理
	{
		if (temp1->child[1]->type == EMPTY_EXP)
		{
			find = true; return find;
		}
		if (temp1->child[0]->type == EMPTY_EXP)
		{
			find = true; return find;
		}
	}
	return find;
}

//判断是否能在and结构中找到一个直接next节点
bool findNextNodeInAnd(CTreeNode* ptree)
{
	CTreeNode* temp1;
	temp1 = ptree;//从ptree根节点开始遍历and操作符
	bool find = false;
	adjust_right_child_and(temp1);//调整使得右子树不是and节点
	while (temp1->type == AND_STA && temp1->child[0]->type == AND_STA)
	{
		if (temp1->child[1]->type == NEXT_STA)
		{
			find = true; return find;
		}//找到以后直接返回，因为我们仅仅在意是否含有next，而不是含有多少
		temp1 = temp1->child[0];//未找到的话,则继续分析左子树
		adjust_right_child_and(temp1);//调整使得右子树不是and节点
	}
	if (temp1->type == AND_STA && temp1->child[0]->type != AND_STA)//单层and结构的处理
	{
		if (temp1->child[1]->type == NEXT_STA)
		{
			find = true; return find;
		}
		if (temp1->child[0]->type == NEXT_STA)
		{
			find = true; return find;
		}
	}
	return find;
}
////构造函数
LNFGNode::LNFGNode()
{
	m_isTrueEmpty = false;
	this->node = new  CTreeNode(AND_STA, "AND", 0);
	this->node->copy_tree(node);
	mark = false;
	AddE = 0;
	AddN = 0;
	already_draw = false;
}
////构造函数
LNFGNode::LNFGNode(CTreeNode* node)
{
	m_isTrueEmpty = false;
	this->node = new CTreeNode(AND_STA, "AND", 0);
	this->node->copy_tree(node);
	mark = false;
	AddE = 0;
	AddN = 0;
	already_draw = false;
}
//拷贝构造函数
LNFGNode::LNFGNode(const LNFGNode& ln)
{
	m_isTrueEmpty = false;
	this->node = new CTreeNode(AND_STA, "AND", 0);
	this->node->copy_tree(ln.node);
	this->mark = ln.mark;
	this->AddE = ln.AddE;
	this->AddN = ln.AddN;
	this->terminal = ln.terminal;
	this->future = ln.future;
}
//LNFGNode destruction
LNFGNode::~LNFGNode()
{
	delete this->node;
	terminal.clear();
	future.clear();
}

////分析这个节点并得到terminal part的数目AddE
void LNFGNode::setAddE()
{
	if (this->node->type == OR_STA)//含有多个析取部分
	{
		CTreeNode* temp1;
		temp1 = this->node;//从根节点开始，每遇到一个EMPTY就加一个terminal部分
		adjust_right_child_or(temp1);
		while (temp1->type == OR_STA && temp1->child[0]->type == OR_STA)
		{
			if (temp1->child[1]->type != AND_STA)
			{
				if (temp1->child[1]->type == EMPTY_EXP)
				{
					addTerminal(temp1->child[1]);
				}
				temp1 = temp1->child[0];
				adjust_right_child_or(temp1);
				continue;
			}
			if (findEmptyNodeInAnd(temp1->child[1]))
			{
				addTerminal(temp1->child[1]);
			}
			temp1 = temp1->child[0];
			adjust_right_child_or(temp1);
		}
		if (temp1->type == OR_STA && temp1->child[0]->type != OR_STA)//单层or结构的处理
		{
			if (temp1->child[1]->type == EMPTY_EXP)
				addTerminal(temp1->child[1]);
			if (temp1->child[1]->type == AND_STA && findEmptyNodeInAnd(temp1->child[1]))
				addTerminal(temp1->child[1]);
			if (temp1->child[0]->type == EMPTY_EXP)
				addTerminal(temp1->child[0]);
			if (temp1->child[0]->type == AND_STA && findEmptyNodeInAnd(temp1->child[0]))
				addTerminal(temp1->child[0]);
		}
	}
	else//没有or操作，即只有一项需要分析
	{
		if (this->node->type == EMPTY_EXP)
		{
			addTerminal(this->node);
		}
		if (this->node->type == AND_STA && findEmptyNodeInAnd(this->node))
		{
			addTerminal(this->node);
		}
	}
}

////分析这个节点并得到nonterminal part的数目AddN
void LNFGNode::setAddN()
{
	if (this->node->type == OR_STA)
	{
		CTreeNode* temp1;
		temp1 = this->node;//从根节点开始，每遇到一个next就加一个terminal部分
		adjust_right_child_or(temp1);
		while (temp1->type == OR_STA && temp1->child[0]->type == OR_STA)
		{
			if (temp1->child[1]->type != AND_STA)
			{
				if (temp1->child[1]->type == NEXT_STA)
				{
					addFuture(temp1->child[1]);
				}
				temp1 = temp1->child[0];
				adjust_right_child_or(temp1);
				continue;
			}
			if (findNextNodeInAnd(temp1->child[1]))
			{
				addFuture(temp1->child[1]);
			}
			temp1 = temp1->child[0];
			adjust_right_child_or(temp1);
		}
		if (temp1->type == OR_STA && temp1->child[0]->type != OR_STA)//单层or结构的处理
		{
			if (temp1->child[1]->type == NEXT_STA)
				addFuture(temp1->child[1]);
			if (temp1->child[1]->type == AND_STA && findNextNodeInAnd(temp1->child[1]))
				addFuture(temp1->child[1]);
			if (temp1->child[0]->type == NEXT_STA)
				addFuture(temp1->child[0]);
			if (temp1->child[0]->type == AND_STA && findNextNodeInAnd(temp1->child[0]))
				addFuture(temp1->child[0]);
		}
	}
	else//没有or操作，即只有一项需要分析
	{
		if (this->node->type == NEXT_STA)
		{
			addFuture(this->node);
		}
		if (this->node->type == AND_STA && findNextNodeInAnd(this->node))
		{
			addFuture(this->node);
		}
	}
}

////标记mark为true，即已经分析了这个节点
void LNFGNode::markToTrue()
{
	mark = true;
}

//add terminal part
void LNFGNode::addTerminal(CTreeNode* ptree)
{
	CTreeNode* temp1 = new CTreeNode(AND_STA, "AND", 0);
	temp1->copy_tree(ptree);
	terminal.push_back(temp1);//将temp1加入到集合terminal中
	//delete temp1;
	AddE++;
}


//add future part
void LNFGNode::addFuture(CTreeNode* ptree)
{
	CTreeNode *temp1 = new CTreeNode(AND_STA, "AND", 0);
	temp1->copy_tree(ptree);
	future.push_back(temp1);//将temp1加入到集合terminal中
	//delete temp1;
	AddN++;
}


//judge if ln if fin equal to this node
bool LNFGNode::finEqual(LNFGNode* ln)
{
	CTreeNode *temp1, *temp2;
	temp1 = new CTreeNode(AND_STA, "", 0);

	temp2 = new CTreeNode(AND_STA, "", 0);

	temp1->copy_tree(this->node);

	temp2->copy_tree(ln->node);
	bool res = temp1->compare2(temp2);//调用CtreeNode的成员函数，进行fin等价的比较
	delete temp1;
	delete temp2;
	return res;
}

/*LNFGEdge member functions*/
//LNFGEdge构造函数，不许含有这三个参数
LNFGEdge::LNFGEdge(CTreeNode * p, CTreeNode * r, CTreeNode* q)
{
	m_endTrueEMPTY = false;
	this->start = new CTreeNode(AND_STA, "AND", 0);
	this->start->copy_tree(p);
	this->end = new CTreeNode(AND_STA, "AND", 0);
	this->end->copy_tree(r);
	this->edgeSpec = new CTreeNode(AND_STA, "AND", 0);
	this->edgeSpec->copy_tree(q);
	this->alreadyDraw = false;
}
//LNFGEdge的析构函数
LNFGEdge::~LNFGEdge()
{
	delete start;
	delete end;
	delete edgeSpec;
}

/*LNFG 类及相关函数*/

//将ptree中的析取项得到并产生LNFG节点，之后加入set中
void getDisPart(LNFGNode_set* node_set, CTreeNode *ptree)
{
	if (ptree->type != OR_STA)//仅有一个析取项
	{
		LNFGNode* ln = new LNFGNode(ptree);
		node_set->push_back(ln);
		//delete ln;
	}
	else//含有多个析取项
	{
		CTreeNode *temp1;
		temp1 = ptree;
		adjust_right_child_or(temp1);
		while (temp1->type == OR_STA && temp1->child[0]->type == OR_STA)
		{
			LNFGNode* ln = new LNFGNode(temp1->child[1]);
			node_set->push_back(ln);
			// delete ln;
			temp1 = temp1->child[0];
			adjust_right_child_or(temp1);
		}
		if (temp1->type == OR_STA && temp1->child[0]->type != OR_STA)
		{
			LNFGNode* ln = new LNFGNode(temp1->child[1]);
			node_set->push_back(ln);
			//	delete ln;
			LNFGNode* ln1 = new LNFGNode(temp1->child[0]);
			node_set->push_back(ln1);
			//	delete ln1;
		}
	}
}
LNFG::LNFG()
{

}

//构造函数：默认必须含有参数
LNFG::LNFG(CTreeNode* ptree)
{
	this->Node = new LNFGNode(ptree);
	getDisPart(&(this->V0), ptree);
	getDisPart(&(this->CL), ptree);
	this->cl_active = false;
	this->cl1_active = false;
	//	this->EL.clear();
	//	this->L.clear();
	k = 1;
}

//析构函数：释放资源
LNFG::~LNFG()
{
	delete Node;
	V0.clear();
	CL.clear();
	CL1.clear();
	EL.clear();
	L.clear();
}

//从CL并CL1中得到一个未被处理的节点,返回iteration的序号
int LNFG::get_R_form_CL_or_CL1()
{
	LNFGNode_set::iterator iter;
	int i = 0;
	for (iter = CL.begin(); iter != CL.end(); iter++)
	{
		if ((*iter)->mark == false && ((*iter)->node->type != EMPTY_EXP))
		{
			this->cl_active = true;
			this->cl1_active = false;
			return i;
		}
		i++;
	}
	i = 0;
	for (iter = CL1.begin(); iter != CL1.end(); iter++)
	{
		if ((*iter)->mark == false && ((*iter)->node->type != EMPTY_EXP))
		{
			this->cl1_active = true;
			this->cl_active = false;
			return i;
		}
		i++;
	}
	return -1;
}


//给出所构造的LNFG，即点集，边集合标记集
/*
void LNFG::showLNFG()
{
	//	currently we just use text to show LNFG
	CNFMachine cnf;
	CStdioFile file;
	file.Open(".\\result", CFile::modeCreate | CFile::modeReadWrite);

	//显示初始节点集合
	file.WriteString("初始节点集合: \n");
	LNFGNode_set::iterator iter_start;
	for (iter_start = V0.begin(); iter_start != V0.end(); iter_start++)
	{

		string show_str = " ";
		cnf.showout = "";
		show_str += cnf.show((*iter_start)->node);
		show_str += "\n";
		file.WriteString(show_str);
	}

	//显示节点的集合
	file.WriteString("节点集合: \n");
	LNFGNode_set::iterator iter;
	for (iter = CL.begin(); iter != CL.end(); iter++)
	{
		string show_str1 = " ";
		cnf.showout = "";
		show_str1 += cnf.show((*iter)->node);
		show_str1 += "\n";
		file.WriteString(show_str1);
	}
	//  	//显示辅助节点的集合
	//  	file.WriteString("辅助节点集合: \n");
	//  	LNFGNode_set::iterator iterh;
	//  	for(iterh=CL1.begin();iterh!=CL1.end();iterh++)
	//  	{
	//  		string show_str1=" ";
	//  		cnf.showout="";
	//   		show_str1+=cnf.show((*iterh)->node);
	//   		show_str1+="\n";
	//   		file.WriteString(show_str1);
	//   	}
	LNFGEdge_set::iterator iter1;
	//显示边的集合
	file.WriteString("边的集合: \n");
	for (iter1 = EL.begin(); iter1 != EL.end(); iter1++)
	{
		cnf.showout = "";
		string show_start = cnf.show((*iter1)->start);
		cnf.showout = "";
		string show_state = cnf.show((*iter1)->edgeSpec);
		cnf.showout = "";
		string show_end = cnf.show((*iter1)->end);
		string show_str = " (";
		show_str += show_start;
		show_str += ",";
		show_str += show_state;
		show_str += ",";
		show_str += show_end;
		show_str += ")\n";
		file.WriteString(show_str);
	}
	//显示标记集合
	LNFGNode_set_of_set::iterator iter2;
	int label_num = 1;
	file.WriteString("标记集合 : \n");
	for (iter2 = L.begin(); iter2 != L.end(); iter2++)
	{
		string show_L_name = "L";
		show_L_name += (char)('0' + label_num);
		show_L_name += ": \n";
		file.WriteString(show_L_name);
		LNFGNode_set::iterator iter3;
		for (iter3 = iter2->begin(); iter3 != iter2->end(); iter3++)
		{
			string show_str = " ";
			cnf.showout = "";
			show_str += cnf.show((*iter3)->node);
			show_str += " \n";
			file.WriteString(show_str);
		}
		label_num++;
	}
	file.Close();
}
*/
//将CL和CL1合并到CL中（while循环之后的部分）
void LNFG::MergeCL()
{
	LNFGNode_set::iterator iter;
	for (iter = CL1.begin(); iter != CL1.end(); iter++)
	{
		CL.push_back(*iter);
	}
}
//判断ＥＭＰＴＹ节点是否在CL中
bool LNFG::EMPTY_in_CL()
{
	LNFGNode_set::iterator iter;
	for (iter = CL.begin(); iter != CL.end(); iter++)
	{
		if ((*iter)->node->type == EMPTY_EXP)
		{
			return true;
		}
	}
	return false;
}
//处理terminal part
void LNFG::handleAddE(LNFGNode* R, CTreeNode* NodeOrig)
{
	if (R->AddE == 0)
	{
		return;
	}
	else
	{
		treenode_set::iterator iter;
		for (iter = R->terminal.begin(); iter != R->terminal.end(); iter++)
		{
			if ((*iter)->type == EMPTY_EXP)//true empty
			{
				CTreeNode* temp = new CTreeNode(EMPTY_EXP, "EMPTY", 0);
				CTreeNode* temp1 = new CTreeNode(TRUE_EXP, "TRUE", 0);
				if (EMPTY_in_CL() == false)
				{
					LNFGNode* ln = new LNFGNode(temp);
					// 	ln->m_isTrueEmpty=true;
					CL.push_back(ln);

				}
				LNFGEdge* le = new LNFGEdge(NodeOrig, temp, temp1);
				// 	le->m_endTrueEMPTY=true;
				EL.push_back(le);
			}
			if ((*iter)->child[0] != NULL && (*iter)->child[0]->type != FALSE_EXP)
			{
				CTreeNode* temp = new CTreeNode(EMPTY_EXP, "EMPTY", 0);
				if (EMPTY_in_CL() == false)
				{
					LNFGNode* ln = new LNFGNode(temp);
					CL.push_back(ln);
					//delete ln;
				}
				LNFGEdge* le = new LNFGEdge(NodeOrig, temp, (*iter)->child[0]);
				EL.push_back(le);
				//	delete le;
				//	delete temp;
			}
		}
		R->AddE = 0;
	}
}
//判断ptree是否能在set中找到相同的公式,另外如果ptree重写之后可以找到也返回真值
bool treenode_in_LNFGset(CTreeNode* ptree, LNFGNode_set set)
{
	LNFGNode_set::iterator iter;
	for (iter = set.begin(); iter != set.end(); iter++)
	{
		if (ptree->compare((*iter)->node))
		{
			return true;
		}
	}
	return false;
}

//集合set中存在和ptree final等价的节点则返回true
int LNFG::existFinEqual(CTreeNode* ptree, LNFGNode_set set)
{
	LNFGNode* ln = new LNFGNode(ptree);

	LNFGNode_set::iterator iter;
	int i = 0;
	for (iter = set.begin(); iter != set.end(); iter++)
	{
		if ((*iter)->finEqual(ln))
		{
			delete ln;
			return i;
		}
		i++;
	}
	return -1;
}
//处理nonterminal part	
void LNFG::handleAddN(LNFGNode* R, CTreeNode* NodeOrig)
{
	if (R->AddN == 0)
	{
		return;
	}
	else
	{
		treenode_set::iterator iter;
		for (iter = R->future.begin(); iter != R->future.end(); iter++)
		{
			if ((*iter)->type == NEXT_STA)
			{
				CTreeNode* temp = new CTreeNode(EMPTY_EXP, "EMPTY", 0);
				CTreeNode* temp1 = new CTreeNode(TRUE_EXP, "TRUE", 0);
				if (treenode_in_LNFGset((*iter)->child[0], CL))//Qfj属于CL,直接增加边;另外一种情况，如果重写后的形式属于CL，也算是属于CL（因为这个点必然是在以前的某一处被重写替换了）
				{
					LNFGEdge* le = new LNFGEdge(NodeOrig, (*iter)->child[0], temp1);
					if ((*iter)->child[0]->type == EMPTY_EXP)
					{
						le->m_endTrueEMPTY = true;
					}
					EL.push_back(le);
				}
				else
				{

					int iter_no1 = existFinEqual((*iter)->child[0], CL);
					if (iter_no1 != -1)
					{
						int iter_no2 = existFinEqual((*iter)->child[0], CL1);
						if (iter_no2 != -1)
						{
							LNFGEdge* le = new LNFGEdge(NodeOrig, CL[iter_no1]->node, temp1);//加边
							if ((*iter)->child[0]->type == EMPTY_EXP)
							{
								le->m_endTrueEMPTY = true;
							}
							EL.push_back(le);
						}
						else
						{
							LNFGNode* ln = new LNFGNode((*iter)->child[0]);//加节点
							if ((*iter)->child[0]->type == EMPTY_EXP)
							{
								ln->m_isTrueEmpty = true;
							}
							CL1.push_back(ln);
							//delete ln;
							LNFGEdge* le = new LNFGEdge(NodeOrig, (*iter)->child[0], temp1);//加边
							if ((*iter)->child[0]->type == EMPTY_EXP)
							{
								le->m_endTrueEMPTY = true;
							}
							EL.push_back(le);
						}
					}
					else//Qcj不在CL中
					{
						LNFGNode* ln = new LNFGNode((*iter)->child[0]);//加节点
						if ((*iter)->child[0]->type == EMPTY_EXP)
						{
							ln->m_isTrueEmpty = true;
						}
						CL.push_back(ln);
						//delete ln;
						LNFGEdge* le = new LNFGEdge(NodeOrig, (*iter)->child[0], temp1);//加边
						if ((*iter)->child[0]->type == EMPTY_EXP)
						{
							le->m_endTrueEMPTY = true;
						}
						EL.push_back(le);
						//delete le;
					}
				}
				continue;
			}
			if ((*iter)->child[0] != NULL && (*iter)->child[0]->type != FALSE_EXP)
			{
				if (treenode_in_LNFGset((*iter)->child[1]->child[0], CL))//Qfj是否属于CL//直接增加边
				{
					LNFGEdge* le = new  LNFGEdge(NodeOrig, (*iter)->child[1]->child[0], (*iter)->child[0]);
					if ((*iter)->child[1]->child[0]->type == EMPTY_EXP)
					{
						le->m_endTrueEMPTY = true;
					}
					EL.push_back(le);
				}
				else
				{
					int iter_no1 = existFinEqual((*iter)->child[1]->child[0], CL);
					if (iter_no1 != -1)//Qcj存在CL中fin等价
					{
						int iter_no2 = existFinEqual((*iter)->child[1]->child[0], CL1);
						if (iter_no2 != -1)
						{
							LNFGEdge* le = new LNFGEdge(NodeOrig, CL[iter_no1]->node, (*iter)->child[0]);//加边
							if ((*iter)->child[1]->child[0]->type == EMPTY_EXP)
							{
								le->m_endTrueEMPTY = true;
							}
							EL.push_back(le);
						}
						else
						{
							LNFGNode* ln = new LNFGNode((*iter)->child[1]->child[0]);//加节点
							if ((*iter)->child[1]->child[0]->type == EMPTY_EXP)
							{
								ln->m_isTrueEmpty = true;
							}
							CL1.push_back(ln);
							//delete ln;
							LNFGEdge* le = new LNFGEdge(NodeOrig, (*iter)->child[1]->child[0], (*iter)->child[0]);//加边
							if ((*iter)->child[1]->child[0]->type == EMPTY_EXP)
							{
								le->m_endTrueEMPTY = true;
							}
							EL.push_back(le);
						}
					}
					else//Qcj不在CL中
					{

						LNFGNode* ln = new LNFGNode((*iter)->child[1]->child[0]);//加节点
						if ((*iter)->child[1]->child[0]->type == EMPTY_EXP)
						{
							ln->m_isTrueEmpty = true;
						}
						CL.push_back(ln);
						//delete ln;
						LNFGEdge* le = new LNFGEdge(NodeOrig, (*iter)->child[1]->child[0], (*iter)->child[0]);//加边
						if ((*iter)->child[1]->child[0]->type == EMPTY_EXP)
						{
							le->m_endTrueEMPTY = true;
						}
						EL.push_back(le);
						//delete le;
					}
				}
			}
		}
		R->AddN = 0;
	}
}
//判断一个树是否作为边的起始节点
bool treeAsStart(CTreeNode* ptree, LNFGEdge_set set)
{
	LNFGEdge_set::iterator iter;
	for (iter = set.begin(); iter != set.end(); iter++)
	{
		if (ptree->compare((*iter)->start))
		{
			return true;
		}
	}
	return false;
}
//去掉单独的非EMPTY点
void LNFG::deleteIsolateNode()
{
	int isolateNodeNo = existIsolateNode();
	if (isolateNodeNo == -1)
	{
		return;
	}
	else
	{
		//删除相关边
		deleteRelevantEdge(isolateNodeNo);
		//删除标记集合中的等价点
		deleteSameNodeInL(isolateNodeNo);
		//删除点(V0和CL)
		deleteSameNodeInV0(isolateNodeNo);
		LNFGNode_set::iterator iter;
		int i = 0;
		for (iter = CL.begin(); iter != CL.end(); iter++)
		{
			if (i == isolateNodeNo)
			{
				break;
			}
			i++;
		}
		CL.erase(iter);
	//	showLNFG();//
		//迭代
		deleteIsolateNode();
	}

}
//从标记名字得到标记的数字
int get_num_form_name(string name)
{
	int num = 0;
	int iter = 1;
	for (; iter != name.length(); iter++)
	{
		num = num * 10 + (name[iter] - '0');
	}
	return num;
}
//向Lk中增加节点
void LNFG::Add_node_to_L(LNFGNode* R, int k)
{
	LNFGNode_set_of_set::iterator iter;
	iter = L.begin();
	for (int i = 1; i<k; i++)//迭代至第k个集合 
	{
		iter++;
	}
	(*iter).push_back(R);
}
//判断and合取项是否含有len()，skip，empty等明确终止项，zxm add 2014.02.15
bool LNFG::isTerminal(CTreeNode* ptree)
{
	if (ptree->type == AND_STA)
	{
		if (ptree->child[0]->type == LEN_STA || ptree->child[0]->type == SKIP_EXP || ptree->child[0]->type == EMPTY_EXP ||
			ptree->child[1]->type == LEN_STA || ptree->child[1]->type == SKIP_EXP || ptree->child[1]->type == EMPTY_EXP)
		{
			return true;
		}
		else if ((ptree->child[0]->type == AND_STA&&isTerminal(ptree->child[0])) ||
			(ptree->child[1]->type == AND_STA&&isTerminal(ptree->child[1])))
		{
			return true;
		}
		else if ((ptree->child[0]->type == NEXT_STA&& isTerminal(ptree->child[0]) || (ptree->child[1]->type == NEXT_STA && isTerminal(ptree->child[1]))))
		{
			return true;
		}
		else
			return false;
	}
	else
	{
		CTreeNode *temp;
		temp = ptree;
		while (temp->type == NEXT_STA)
		{
			temp = temp->child[0];
		}
		if (temp->type == LEN_STA || temp->type == SKIP_EXP || temp->type == EMPTY_EXP)
		{
			return true;
		}
		else if (temp->type == AND_STA && isTerminal(temp))
		{
			return true;
		}
		else
			return false;
	}
}


//给当前的ptree（主操作符必为chop）增加final标记
void LNFG::Add_fin_to_chop(LNFGNode* R, CTreeNode* ptree, int_set* nums)
{
	//***********************增加不需要加fin标记的情况判断************************// zxm add 2014.02.15
	if ((ptree->child[0]->type == AND_STA || ptree->child[0]->type == NEXT_STA) && isTerminal(ptree->child[0]))
	{
		return;
	}
	else if (ptree->child[0]->type == SKIP_EXP || ptree->child[0]->type == LEN_STA || ptree->child[0]->type == EMPTY_EXP)
	{
		return;
	}
	if (ptree->child[0]->type == AND_STA && ptree->child[0]->child[1]->type == FIN_EXP)//该项已经被标记
	{
		string label = ptree->child[0]->child[1]->child[0]->name_str;
		int l_num = get_num_form_name(label);
		(*nums).push_back(l_num);
	}
	else if (ptree->type == FIN_EXP && ptree->child[0]->name_str[0] == 'l')////////????????????主操作符为chop？？？？？？
	{
		string label = ptree->child[0]->name_str;
		int l_num = get_num_form_name(label);
		(*nums).push_back(l_num);
	}
	else if (ptree->child[0]->type == FIN_EXP && ptree->child[0]->child[0]->name_str[0] == 'l')
	{
		string label = ptree->child[0]->child[0]->name_str;
		int l_num = get_num_form_name(label);
		(*nums).push_back(l_num);
	}
	else
	{
		//得到lk
		CTreeNode* temp1 = new CTreeNode(IDENT_EXP, "", 0);
		temp1->name_str = "l";
		string name_num;
		std::stringstream ss;
		ss << this->k;
		ss >> name_num;
		temp1->name_str += name_num;

		CTreeNode *temp3 = new CTreeNode(FIN_EXP, "FIN", 0);
		temp3->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp3->child[0]->copy_tree(temp1);
		delete temp1;
		//得到合取式
		CTreeNode* temp2 = new CTreeNode(AND_STA, "AND", 0);
		temp2->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp2->child[1] = new CTreeNode(AND_STA, "AND", 0);
		temp2->child[0]->copy_tree(ptree->child[0]);
		temp2->child[1]->copy_tree(temp3);
		//此处重写
		if (ptree->child[0]->type == TRUE_EXP)
		{
			ptree->child[0]->copy_tree(temp3);
		}
		else
			ptree->child[0]->copy_tree(temp2);
		delete temp2;
		delete temp3;
		//增加集合，改变k值
		LNFGNode_set ln_set;
		L.push_back(ln_set);
		(*nums).push_back(k);
		k++;
		//	temp
	}
}
//判断一个LNFG点是否在一个LNFG集合中,并返回序号
int node_in_set_replace(LNFGNode* R_cp, LNFGNode_set set)
{
	// 	CNFMachine cnf;
	// 	string Str=cnf.show(R_cp->node);//由于原来程序的compare函数有一定的问题，我们暂时先用string的比较来代替它。
	LNFGNode_set::iterator iter;
	int i = 0;
	for (iter = set.begin(); iter != set.end(); iter++)
	{
		// 		cnf.showout="";//////////////////////
		// 		string str2=cnf.show((*iter)->node);///////////////////////
		//if ((*iter)->node->compare(R_cp->node))
		if (R_cp->node->compare((*iter)->node))
		{
			return i;
		}
		i++;
	}
	return -1;
}
//删去and结构中的EMPTY部分
void deleteEmptyNodeInAnd(CTreeNode* ptree)
{
	CTreeNode* temp;
	temp = ptree;
	adjust_right_child_and(temp);
	while (temp->type == AND_STA && temp->child[0]->type == AND_STA)
	{
		if (temp->child[1]->type == EMPTY_EXP)
		{
			temp->copy_tree(temp->child[0]);
		}
		else
		{
			temp = temp->child[0];
		}
		adjust_right_child_and(temp);
	}
	if (temp->type == AND_STA && temp->child[0]->type != AND_STA)
	{
		if (temp->child[1]->type == EMPTY_EXP)
			temp->copy_tree(temp->child[0]);
		if (temp->child[0]->type == EMPTY_EXP)
			temp->copy_tree(temp->child[1]);
	}
}
//供rewriteOneDisPart函数调用，处理每一部分的合取式
void rewriteOneConPart(CTreeNode* ptree)
{
	CTreeNode* temp1;
	if (ptree->type == CHOP_STA)
	{
		if (ptree->child[0]->type == AND_STA && ptree->child[0]->child[0]->type == EMPTY_EXP &&  ptree->child[0]->child[1]->type == FIN_EXP)//empty&&fin(lk);q--->lk&&q
		{
			temp1 = new CTreeNode(AND_STA, "AND", 0);
			temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
			temp1->child[0]->copy_tree(ptree->child[0]->child[1]->child[0]);
			temp1->child[1] = new CTreeNode(AND_STA, "AND", 0);
			temp1->child[1]->copy_tree(ptree->child[1]);
			ptree->copy_tree(temp1);
			delete temp1;
			return;
		}
		if (ptree->child[0]->type == AND_STA && ptree->child[0]->child[1]->type == EMPTY_EXP &&  ptree->child[0]->child[0]->type == FIN_EXP)//fin(lk)&&empty;q--->lk&&q
		{
			temp1 = new CTreeNode(AND_STA, "AND", 0);
			temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
			temp1->child[0]->copy_tree(ptree->child[0]->child[0]->child[0]);
			temp1->child[1] = new CTreeNode(AND_STA, "AND", 0);
			temp1->child[1]->copy_tree(ptree->child[1]);
			ptree->copy_tree(temp1);
			delete temp1;
			return;
		}
		if (ptree->child[0]->type == AND_STA && findEmptyNodeInAnd(ptree->child[0]))
		{
			deleteEmptyNodeInAnd(ptree->child[0]);
			ptree->type = AND_STA;
		}
	}
}
//处理next部分，事实上仅有next部分需重写
void rewriteNextPart(CTreeNode* ptree)
{
	if (ptree->type != AND_STA)
	{
		rewriteOneConPart(ptree);
	}
	else
	{
		CTreeNode* temp = ptree;
		adjust_right_child_and(temp);
		while (temp->type == AND_STA && temp->child[0]->type == AND_STA)
		{
			rewriteOneConPart(temp->child[1]);
			temp = temp->child[0];
			adjust_right_child_and(temp);
		}
		if (temp->type == AND_STA && temp->child[0]->type != AND_STA)
		{
			rewriteOneConPart(temp->child[1]);
			rewriteOneConPart(temp->child[0]);
		}
	}
}
//处理每一项析取部分，含empty则不处理，含next则需要处理内部的chop
void rewriteOneDisPart(CTreeNode* ptree)
{
	if (ptree->type != AND_STA)
	{
		;
	}
	else
	{
		CTreeNode* temp;
		temp = ptree;
		if (temp->child[1]->type == EMPTY_EXP)
		{
			return;
		}
		if (temp->child[1]->type == NEXT_STA)
		{
			rewriteNextPart(temp->child[1]->child[0]);
		}
	}
}
//在求得范式之后，应该将EMPTY&&p;q的形式重写为p&&q,   （（今后normalform工具完善之后，就应该把这个函数删去））
void LNFG::rewriteEmptyChop(LNFGNode* R)
{
	if (R->node->type != OR_STA)//仅一项合取
	{
		rewriteOneDisPart(R->node);
	}
	else
	{
		CTreeNode* temp = R->node;
		adjust_right_child_or(temp);
		while (temp->type == OR_STA && temp->child[0]->type == OR_STA)
		{
			rewriteOneDisPart(temp->child[1]);
			temp = temp->child[0];
			adjust_right_child_or(temp);
		}
		if (temp->type == OR_STA && temp->child[0]->type != OR_STA)
		{
			rewriteOneDisPart(temp->child[1]);
			rewriteOneDisPart(temp->child[0]);
		}
	}
}

//重写fin之后，更新边的集合
void LNFG::updateEL(LNFGNode* R_cp, LNFGNode* R)
{
	LNFGEdge_set::iterator iter;
	CNFMachine cnf;
	for (iter = EL.begin(); iter != EL.end(); iter++)
	{
		cnf.showout = "";
		string str1 = "";
		str1 += cnf.show((*iter)->start);
		cnf.showout = "";
		string str2 = "";
		str2 += cnf.show(R_cp->node);
		cnf.showout = "";
		string str3 = "";
		str3 += cnf.show((*iter)->end);
		if (str1 == str2 || (*iter)->start->compare(R_cp->node))
		{

			delete (*iter)->start;
			(*iter)->start = new CTreeNode(AND_STA, "AND", 0);
			(*iter)->start->copy_tree(R->node);
		}
		if (str3 == str2 || (*iter)->end->compare(R_cp->node))
		{
			delete (*iter)->end;
			(*iter)->end = new CTreeNode(AND_STA, "AND", 0);
			(*iter)->end->copy_tree(R->node);
		}
	}
}

//重写公式，增加final标记
void LNFG::rewriteFin(LNFGNode* R)
{
	// 	CTreeNode* pOrig=new CTreeNode(AND_STA,"AND",0);
	// 	pOrig->copy_tree(ptree);
	LNFGNode R_cp(R->node);
	int_set ist;
	if (R->node->type != AND_STA)//仅一项合取
	{
		if (R->node->type == CHOP_STA)
		{
			Add_fin_to_chop(R, R->node, &ist);
		}
		if (R->node->type == FIN_EXP)
		{
			Add_fin_to_chop(R, R->node, &ist);
		}
	}
	else//遍历and树，每遇到一个chop子公式即重写R
	{
		CTreeNode* temp1;
		temp1 = R->node;
		adjust_right_child_and(temp1);
		while (temp1->type == AND_STA && temp1->child[0]->type == AND_STA)
		{
			if (temp1->child[1]->type == CHOP_STA)
			{
				Add_fin_to_chop(R, temp1->child[1], &ist);
			}
			if (temp1->child[1]->type == FIN_EXP)
			{
				Add_fin_to_chop(R, temp1->child[1], &ist);
			}
			temp1 = temp1->child[0];
			adjust_right_child_and(temp1);
		}
		if (temp1->type == AND_STA && temp1->child[0]->type != AND_STA)
		{
			if (temp1->child[1]->type == CHOP_STA)
			{
				Add_fin_to_chop(R, temp1->child[1], &ist);
			}
			if (temp1->child[1]->type == FIN_EXP)
			{
				Add_fin_to_chop(R, temp1->child[1], &ist);
			}
			if (temp1->child[0]->type == CHOP_STA)
			{
				Add_fin_to_chop(R, temp1->child[0], &ist);
			}
			if (temp1->child[0]->type == FIN_EXP)
			{
				Add_fin_to_chop(R, temp1->child[0], &ist);
			}
		}
	}
	//重写完成之后，加入相应的各个L集合中
	int_set::iterator iter_int;
	for (iter_int = ist.begin(); iter_int != ist.end(); iter_int++)
	{
		LNFGNode* addNode = new LNFGNode(R->node);
		Add_node_to_L(addNode, (*iter_int));
	}
	//最后需要更新V0和CL、CL1
	if (!ist.empty())
	{
		int rep_num;
		/*	LNFGNode_set::iterator iter_rep;*/
		if (this->cl_active)
		{
			rep_num = node_in_set_replace(&R_cp, CL);
			if (rep_num != -1)
			{
				delete CL[rep_num];
				CL[rep_num] = new LNFGNode(R->node);
				CL[rep_num]->markToTrue();
			}
		}
		else
		{
			rep_num = node_in_set_replace(&R_cp, CL1);
			if (rep_num != -1)
			{
				delete CL1[rep_num];
				CL1[rep_num] = new LNFGNode(R->node);
				CL1[rep_num]->markToTrue();
			}

		}
		rep_num = node_in_set_replace(&R_cp, V0);
		if (rep_num != -1)
		{
			delete V0[rep_num];
			V0[rep_num] = new LNFGNode(R->node);
			V0[rep_num]->markToTrue();
		}
		//需要更新EL
		updateEL(&R_cp, R);
	}
}

//算法种的一次while循环
void LNFG::loopOnce(int iter_no)
{
	LNFGNode* ln;
	if (this->cl_active)
	{
		ln = new LNFGNode(CL[iter_no]->node);
	}
	else
	{
		ln = new LNFGNode(CL1[iter_no]->node);
	}
	CNFMachine cnf;
	//1.公式R的预处理过程
	//	LNFGNode* ln=new LNFGNode((*iter)->node);
	cnf.PRE(ln->node);
	if (this->cl_active&&!ln->node->compare(CL[iter_no]->node))
	{
		//也需要更新EL和L
		updateEL(CL[iter_no], ln);
		int rep_num = node_in_set_replace(CL[iter_no], V0);
		if (rep_num != -1)
		{
			delete V0[rep_num];
			V0[rep_num] = new LNFGNode(ln->node);
			V0[rep_num]->markToTrue();
		}
		delete CL[iter_no];
		CL[iter_no] = new LNFGNode(ln->node);
		CL[iter_no]->markToTrue();


	}
	if (this->cl1_active&&!ln->node->compare(CL1[iter_no]->node))
	{
		//也需要更新EL和L
		updateEL(CL1[iter_no], ln);
		delete CL1[iter_no];
		CL1[iter_no] = new LNFGNode(ln->node);
		CL1[iter_no]->markToTrue();

	}
	//	showLNFG();
	if (ln->node->type != FALSE_EXP)
	{
		//2.重写公式R
		rewriteFin(ln);
		//		showLNFG();//delete later!!!!
		//3.求得公式的normalform
		cnf.NF(ln->node);

		cnf.POST(ln->node);

		//2013.6.20新加部分：empty&&p;q--->p&&q	
		rewriteEmptyChop(ln);
		// 		string test="";
		// 		cnf.showout="";
		// 		test+=cnf.show(ln->node);
		//4.设置AddE和AddN的值
		ln->setAddE();
		ln->setAddN();
		//5.处理terminal和nonterminal部分
		if (this->cl_active)
		{
			this->handleAddN(ln, CL[iter_no]->node);
			this->handleAddE(ln, CL[iter_no]->node);
		}
		else
		{
			this->handleAddN(ln, CL1[iter_no]->node);
			this->handleAddE(ln, CL1[iter_no]->node);
		}
	}
	//this->showLNFG();
}

//构造LNFG函数
void LNFG::construct()
{
	int iter_no = get_R_form_CL_or_CL1();
	if (iter_no<0)
	{
		if (!CL.empty() && CL[0]->node->type == EMPTY_EXP)
		{
			CL[0]->m_isTrueEmpty = true;
		}
		else
		{
			cout << "incorrect formula!" << endl;
		}
	}
	else
	{
		while (iter_no >= 0)//while循环
		{
			if (this->cl_active)
			{
				CL[iter_no]->markToTrue();
			}
			else
			{
				CL1[iter_no]->markToTrue();
			}
			loopOnce(iter_no);//一次循环的执行
			iter_no = get_R_form_CL_or_CL1();
			//this->showLNFG();
		}
		MergeCL();
		MergeEgdeOfSameLoc();
		deleteIsolateNode();
	}

	//this->showLNFG();
}

void LNFG::GetLabelOfNode(LNFGNode* ln, int_set* label)//得到节点ln所属的标记集合的标号集
{
	LNFGNode_set_of_set::iterator iter1;
	int label_num = 1;

	for (iter1 = L.begin(); iter1 != L.end(); iter1++)
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
static string IntTostring(int num)//使用stringstream将int类型的数据转换为string类型的数据
{
	string str;
	string str1;
	stringstream ss;
	ss << num;
	ss >> str1;
	str = str1.c_str();
	return str;
}
string LNFG::addNodeInfo(string NodeInfo, LNFGNode *ln)//增加节点信息
{
	CNFMachine cnf;
	NodeInfo += "Node";
	string NodeStr;
	NodeStr = IntTostring(ln->nodeNo);
	NodeInfo += NodeStr;
	NodeInfo += ":";
	cnf.showout = "";
	NodeInfo += cnf.show(ln->node);

	int_set label_set;
	GetLabelOfNode(ln, &label_set);
	if (!label_set.empty())
	{
		NodeInfo += "#";//分隔公式和标记部分
		int_set::iterator iter_label;
		for (iter_label = label_set.begin(); iter_label != label_set.end(); iter_label++)
		{
			string label_num = IntTostring((*iter_label));
			NodeInfo += "l";
			NodeInfo += label_num;
			NodeInfo += " ";
		}
	}
	NodeInfo += "@";
	return NodeInfo;
}

string LNFG::addEdgeInfo(string edgeInfo, int edgeId, LNFGEdge *le, int startId, int endId)//增加边的信息
{
	CNFMachine cnf;
	edgeInfo += "Edge";
	string EdgeStr = IntTostring(edgeId);
	string startStr = IntTostring(startId);
	string endStr = IntTostring(endId);
	edgeInfo += EdgeStr;
	edgeInfo += ":";
	cnf.showout = "";
	edgeInfo += cnf.show(le->edgeSpec);
	edgeInfo += "#Node";
	edgeInfo += startStr;
	edgeInfo += "->";
	edgeInfo += "Node";
	edgeInfo += endStr;
	edgeInfo += "@";
	return edgeInfo;
}

string LNFG::addTerminalEdgeInfo(string edgeInfo, int edgeId, int startId, int EndId)//增加终止边的信息
{
	edgeInfo += "Edge";
	string EdgeStr = IntTostring(edgeId);
	string startStr = IntTostring(startId);
	string endStr = IntTostring(EndId);
	edgeInfo += EdgeStr;
	edgeInfo += ":";
	edgeInfo += "TRUE#";
	edgeInfo += "Node";
	edgeInfo += startStr;
	edgeInfo += "->";
	edgeInfo += "Node";
	edgeInfo += endStr;
	edgeInfo += "@";
	return edgeInfo;
}

string LNFG::addTerminalNodeInfo(string nodeInfo, int nodeId)//增加终止节点的信息
{
	nodeInfo += "Node";
	string NodeStr;
	NodeStr = IntTostring(nodeId);
	nodeInfo += NodeStr;
	nodeInfo += ":";
	nodeInfo += "EPSILON";
	nodeInfo += "@";
	return nodeInfo;
}

int LNFG::existIsolateNode()
{
	LNFGNode_set::iterator iter;
	int i = 0;
	for (iter = CL.begin(); iter != CL.end();)
	{
		if ((*iter)->node->type != EMPTY_EXP && treeAsStart((*iter)->node, EL) == false)
		{
			return i;
		}
		else
		{
			iter++; i++;
		}
	}
	return -1;
}

void LNFG::deleteRelevantEdge(int index)
{
	LNFGEdge_set::iterator iter;
	for (iter = EL.begin(); iter != EL.end();)
	{
		if ((*iter)->end->compare(CL[index]->node))
		{
			EL.erase(iter);
		}
		else
			iter++;
	}
}

void LNFG::deleteSameNodeInL(int index)
{
	LNFGNode_set_of_set::iterator iter2;
	for (iter2 = L.begin(); iter2 != L.end(); iter2++)
	{
		LNFGNode_set::iterator iter3;
		for (iter3 = iter2->begin(); iter3 != iter2->end();)
		{
			if ((*iter3)->node->compare(CL[index]->node))
			{
				(*iter2).erase(iter3);
			}
			else
				iter3++;
		}
	}
}

void LNFG::deleteSameNodeInV0(int index)
{
	LNFGNode_set::iterator iter;
	for (iter = V0.begin(); iter != V0.end(); iter++)
	{
		if ((*iter)->node->compare(CL[index]->node))
		{
			V0.erase(iter);
		}
		if (V0.empty())
		{
			break;
		}
	}
}
//added by LXF 2013/08/19 17:09:07
void LNFG::MergeEgdeOfSameLoc()
{
	if (EL.size() <= 1)
	{
		return;
	}
	//由于起点相同且终点相同的边必定会是编号相邻的边。所以不需要二重循环来找这样的一对边
	LNFGEdge_set::iterator iter;
	iter = EL.begin(); iter++;
	CTreeNode* temp1;
	CNFMachine cnf;
	int i = 1;

	while (iter != EL.end())
	{
		if (EL[i]->start->compare(EL[i - 1]->start) && EL[i]->end->compare(EL[i - 1]->end))
		{//和后一个边具有相同的起始和终止节点
			temp1 = new CTreeNode(OR_STA, "OR", 0);
			temp1->child[0] = new CTreeNode(AND_STA, "AND", 0);
			temp1->child[0]->copy_tree(EL[i - 1]->edgeSpec);
			temp1->child[1] = new CTreeNode(AND_STA, "AND", 0);
			temp1->child[1]->copy_tree(EL[i]->edgeSpec);
			cnf.PRE(temp1);
			EL[i - 1]->edgeSpec->copy_tree(temp1);
			delete temp1;
			EL.erase(iter);
		}
		else
		{
			iter++; i++;
		}
	}
}
int tarjanIndex = 0;
static int firstUnpartitioned(vector<simpleNode*> set)
{
	vector<simpleNode*>::iterator iter;
	int i = 0;
	for (iter = set.begin(); iter != set.end(); iter++)
	{
		if ((*iter)->partitioned != true)
		{
			return i;
		}
		else
			i++;
	}
	return -1;
}
/*//增加，删除自环  zxm2014.03.24
//修改tarjan算法后，此函数不需要使用
bool LNFG::deletealoopInSimGraph()
{
vector<simpleEdge*>::iterator iter;
bool sign=false;
for (iter=simGraphofLNFG.edgeSet.begin();iter!=simGraphofLNFG.edgeSet.end();)
{
if((*iter)->start==(*iter)->end)
{
vector<simpleNode*> newLoop;//新建循环
newLoop.push_back(simGraphofLNFG.nodeSet[((*iter)->start)-1]);
loopSet.push_back(newLoop);
simGraphofLNFG.edgeSet.erase(iter);
sign=true;
continue;
}
iter++;
}
return sign;
}
*/
bool LNFG::loopSearchInLNFG()
{
	bool existLoop = false;
	getSimpleGraphOfLNFG();

	//删除入度为零和岀度为零的节点
	deleteIrrelevantNodes();
	if (simGraphofLNFG.nodeSet.size() == 0)
	{
		return existLoop;
	}
	else
	{
		existLoop = true;
	}
	//Tarjan算法求得强连通子图,完成点的划分

	tarjanOfSimGraph(simGraphofLNFG.nodeSet[0]);

	int unpartitionedNo = firstUnpartitioned(simGraphofLNFG.nodeSet);
	while (unpartitionedNo != -1)
	{
		tarjanIndex = 0;
		tarjanOfSimGraph(simGraphofLNFG.nodeSet[unpartitionedNo]);
		unpartitionedNo = firstUnpartitioned(simGraphofLNFG.nodeSet);
	}
	//完成边的划分
	partitionSimEdges();
	/*	showSimpleGraph(subSimGraphs[0]);*/
	//dfs
	vector<simpleGarph*>::iterator iter;
	for (iter = subSimGraphs.begin(); iter != subSimGraphs.end(); iter++)//分别对每一个子图dfs
	{
		if ((*iter)->nodeSet.size() == 1)//图中仅有一个节点，查看自环
		{
			if ((*iter)->edgeSet.size() == 1 && (*iter)->edgeSet[0]->start == (*iter)->nodeSet[0]->No && (*iter)->edgeSet[0]->end == (*iter)->nodeSet[0]->No)
			{
				/*	vector<simpleNode*> newLoop;//新建循环
				newLoop.push_back((*iter)->nodeSet[0]);
				loopSet.push_back(newLoop);//新循环加入到循环集合中*/
				loopSet.push_back((*iter));
			}
		}
		else//多个点
		{
			/*
			dfsStack.push_back((*iter)->nodeSet[0]);
			dfsSubOneGraph(*iter);
			*/
			/*    修改      zxm  2014.05.06*/
			/*vector<simpleNode*> newLoop;//新建循环
			vector<simpleNode*>::iterator iter_node;
			for(iter_node=((*iter)->nodeSet).begin();iter_node!=((*iter)->nodeSet).end();iter_node++)
			{
			newLoop.push_back(*iter_node);
			}
			//	newLoop.push_back((*iter)->nodeSet);
			loopSet.push_back(newLoop);//新循环加入到循环集合中*/
			loopSet.push_back((*iter));
		}
	}
	//showSimpleLoops();

}

void LNFG::getSimpleGraphOfLNFG()
{
	LNFGNode_set::iterator iter1;
	for (iter1 = CL.begin(); iter1 != CL.end(); iter1++)
	{
		simpleNode* node = new simpleNode();
		node->No = (*iter1)->nodeNo;
		node->labelSet = (*iter1)->labelSet;
		simGraphofLNFG.nodeSet.push_back(node);
	}

	LNFGEdge_set::iterator iter2;
	for (iter2 = EL.begin(); iter2 != EL.end(); iter2++)
	{
		simpleEdge* edge = new simpleEdge();
		edge->start = (*iter2)->startNo;
		edge->end = (*iter2)->endNo;
		simGraphofLNFG.edgeSet.push_back(edge);
	}
}

void LNFG::deleteIrrelevantNodes()
{
	bool nodeDeleted = false;
	calculateDegreeOfNodes();
	vector<simpleNode*>::iterator iter;
	for (iter = simGraphofLNFG.nodeSet.begin(); iter != simGraphofLNFG.nodeSet.end();)
	{
		if ((*iter)->inDegree == 0)
		{
			nodeDeleted = true;
			deleteRelevantOutEdge((*iter)->No);
			simGraphofLNFG.nodeSet.erase(iter);
			continue;
		}
		if ((*iter)->outDegree == 0)
		{
			nodeDeleted = true;
			deleteRelevantInEdge((*iter)->No);
			simGraphofLNFG.nodeSet.erase(iter);
			continue;
		}
		iter++;
	}
	if (simGraphofLNFG.nodeSet.size() == 0)
	{
		return;
	}
	else
	{
		if (nodeDeleted == true)
		{
			deleteIrrelevantNodes();
		}
	}

}

void LNFG::calculateDegreeOfNodes()
{
	vector<simpleEdge*>::iterator iter;
	vector<simpleNode*>::iterator iter1;
	for (iter1 = simGraphofLNFG.nodeSet.begin(); iter1 != simGraphofLNFG.nodeSet.end(); iter1++)
	{
		(*iter1)->inDegree = 0;
		(*iter1)->outDegree = 0;
	}
	for (iter = simGraphofLNFG.edgeSet.begin(); iter != simGraphofLNFG.edgeSet.end(); iter++)
	{
		int startNode = nodeNoToNode((*iter)->start, &simGraphofLNFG);
		if (startNode != -1)
		{
			simGraphofLNFG.nodeSet[startNode]->outDegree++;
		}
		int endNode = nodeNoToNode((*iter)->end, &simGraphofLNFG);
		if (endNode != -1)
		{
			simGraphofLNFG.nodeSet[endNode]->inDegree++;
		}
	}
}

int LNFG::nodeNoToNode(int nodeNo, simpleGarph* graph)
{
	vector<simpleNode*>::iterator iter;
	int i = 0;
	for (iter = graph->nodeSet.begin(); iter != graph->nodeSet.end(); iter++)
	{
		if ((*iter)->No == nodeNo)
		{
			return i;
		}
		else
			i++;
	}
	return -1;
}

void LNFG::deleteRelevantOutEdge(int nodeNo)
{
	vector<simpleEdge*>::iterator iter;
	for (iter = simGraphofLNFG.edgeSet.begin(); iter != simGraphofLNFG.edgeSet.end();)
	{
		if ((*iter)->start == nodeNo)
		{
			simGraphofLNFG.edgeSet.erase(iter);
			continue;
		}
		else
			iter++;
	}
}

void LNFG::deleteRelevantInEdge(int nodeNo)
{
	vector<simpleEdge*>::iterator iter;
	for (iter = simGraphofLNFG.edgeSet.begin(); iter != simGraphofLNFG.edgeSet.end();)
	{
		if ((*iter)->end == nodeNo)
		{
			simGraphofLNFG.edgeSet.erase(iter);
			continue;
		}
		else
			iter++;
	}
}
/*
void LNFG::showSimpleGraph(simpleGarph* simGraph)
{
	CStdioFile file;
	file.Open(".\\resultSimple", CFile::modeCreate | CFile::modeReadWrite);

	//显示节点的集合
	file.WriteString("节点集合: \n");
	vector<simpleNode*>::iterator iter;
	for (iter = simGraph->nodeSet.begin(); iter != simGraph->nodeSet.end(); iter++)
	{
		string show_str1 = IntTostring((*iter)->No);
		show_str1 += "\n";
		file.WriteString(show_str1);
	}
	vector<simpleEdge*>::iterator iter1;
	//显示边的集合
	file.WriteString("边的集合: \n");
	for (iter1 = simGraph->edgeSet.begin(); iter1 != simGraph->edgeSet.end(); iter1++)
	{
		string show_str = "(";
		show_str += IntTostring((*iter1)->start);
		show_str += ",";
		show_str += IntTostring((*iter1)->end);
		show_str += ")\n";
		file.WriteString(show_str);
	}
	file.Close();
}
*/

/*
zxm增加，判断一个结点是否在栈中2014.3.24
*/
bool isInStack(simpleNode *node, stack<simpleNode*> tjstack){
	stack<simpleNode*> temp;//临时变量存储弹出的数据
	simpleNode* tnode;
	bool sign = false;
	while (!tjstack.empty())
	{
		tnode = tjstack.top();
		if (tnode->No == node->No)
		{
			sign = true;
			while (!temp.empty())
			{
				tjstack.push(temp.top());
				temp.pop();
			}
			break;
		}
		temp.push(tnode);
		tjstack.pop();
	}
	while (!temp.empty())
	{
		tjstack.push(temp.top());
		temp.pop();
	}
	return sign;
}

void LNFG::tarjanOfSimGraph(simpleNode *node)
{
	node->DFN = node->Low = ++tarjanIndex;
	node->visited = true;
	tarjanStack.push(node);
	vector<simpleEdge*>::iterator iter;
	for (iter = simGraphofLNFG.edgeSet.begin(); iter != simGraphofLNFG.edgeSet.end(); iter++)
	{
		if ((*iter)->start == node->No)//以node为起始点
		{

			int endNode = nodeNoToNode((*iter)->end, &simGraphofLNFG);
			/*if (simGraphofLNFG.nodeSet[endNode]->visited==true)//判断条件出错
			{
			node->Low=(node->Low<=simGraphofLNFG.nodeSet[endNode]->DFN)?node->Low:simGraphofLNFG.nodeSet[endNode]->DFN;
			}
			else
			{
			tarjanOfSimGraph(simGraphofLNFG.nodeSet[endNode]);
			node->Low=(node->Low<=simGraphofLNFG.nodeSet[endNode]->Low)?node->Low:simGraphofLNFG.nodeSet[endNode]->Low;
			}*/
			if (isInStack(simGraphofLNFG.nodeSet[endNode], tarjanStack))//////zxm修改2014.3.24
			{
				node->Low = (node->Low <= simGraphofLNFG.nodeSet[endNode]->DFN) ? node->Low : simGraphofLNFG.nodeSet[endNode]->DFN;
			}
			else if (simGraphofLNFG.nodeSet[endNode]->visited == false)
			{
				tarjanOfSimGraph(simGraphofLNFG.nodeSet[endNode]);
				node->Low = (node->Low <= simGraphofLNFG.nodeSet[endNode]->Low) ? node->Low : simGraphofLNFG.nodeSet[endNode]->Low;
			}
		}
	}
	if (node->DFN == node->Low)
	{
		simpleGarph* newPartition = new simpleGarph();
		simpleNode* newNode;
		do
		{
			newNode = tarjanStack.top();
			tarjanStack.pop();
			newNode->partitioned = true;
			newPartition->nodeSet.push_back(newNode);

		} while (node->No != newNode->No);
		subSimGraphs.push_back(newPartition);
	}
}

void LNFG::partitionSimEdges()
{
	vector<simpleEdge*>::iterator iter;
	for (iter = simGraphofLNFG.edgeSet.begin(); iter != simGraphofLNFG.edgeSet.end();)
	{
		//如果start和end同时处在某个子图中，则将边加入到这个子图
		vector<simpleGarph*>::iterator iter1;
		for (iter1 = subSimGraphs.begin(); iter1 != subSimGraphs.end(); iter1++)
		{
			bool startInGraph = false;
			bool endInGraph = false;
			vector<simpleNode*>::iterator iter2;
			for (iter2 = (*iter1)->nodeSet.begin(); iter2 != (*iter1)->nodeSet.end(); iter2++)
			{
				if ((*iter2)->No == (*iter)->start)
				{
					startInGraph = true;
				}
				if ((*iter2)->No == (*iter)->end)
				{
					endInGraph = true;
				}
			}
			if (startInGraph == true && endInGraph == true)
			{
				(*iter1)->edgeSet.push_back(*iter);
			}
			else
			{
				;
			}
		}
		iter++;
	}
}

/*void LNFG::dfsSubOneGraph(simpleGarph *graph)
{
simpleNode* topNode=dfsStack.back();//向量中的back现模拟栈的栈顶
vector<simpleEdge*>::iterator iter;
for (iter=graph->edgeSet.begin();iter!=graph->edgeSet.end();iter++)
{
if ((*iter)->start==topNode->No)//topNode的出边
{
int terminalNodeLoc=nodeInStack((*iter)->end);
if (terminalNodeLoc!=-1)//边的末端在栈中
{
//从terminalNodeLoc形成一个环，将加入loopSet中
simpleNode_set newLoop;
for (int i=terminalNodeLoc;i<dfsStack.size();i++)
{
newLoop.push_back(dfsStack[i]);
}
loopSet.push_back(newLoop);
}
else
{
//新节点入栈
simpleNode* terminalNode;
terminalNode=graph->nodeSet[nodeNoToNode((*iter)->end,graph)];
dfsStack.push_back(terminalNode);
dfsSubOneGraph(graph);
}
}
}
simpleNode_set::iterator iter1;
for (iter1=dfsStack.begin();iter1!=dfsStack.end();iter1++);
iter1--;
dfsStack.erase(iter1);
}
*/
/*
void LNFG::showSimpleLoops()
{
	vector<simpleGarph*>::iterator iter;
	simpleNode_set::iterator iter1;
	string loopRes = "";
	int i = 1;
	for (iter = loopSet.begin(); iter != loopSet.end(); iter++)
	{
		loopRes += "Loop";
		loopRes += IntTostring(i);
		loopRes += ":{ ";
		for (iter1 = (*iter)->nodeSet.begin(); iter1 != (*iter)->nodeSet.end(); iter1++)
		{
			loopRes += IntTostring((*iter1)->No);
			loopRes += " ";
		}
		loopRes += "}";
		loopRes += "\r\n";
		i++;
	}
	CStdioFile file;
	file.Open("resultLoop", CFile::modeCreate | CFile::modeWrite);
	file.WriteString(loopRes);
	file.Close();
	LoopString = loopRes;
}
*/
int LNFG::nodeInStack(int topNode)
{
	simpleNode_set::iterator iter;
	int i = 0;
	for (iter = dfsStack.begin(); iter != dfsStack.end(); iter++)
	{
		if ((*iter)->No == topNode)
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

bool LNFG::DecisionProcecdure()
{
	bool satisfied1 = false;
	if (EMPTY_in_CL())
	{
		satisfied1 = true;
	}
	if (labelSetIsEmpty() == true)
	{
		satisfied1 = true;
	}
	bool existLoop = loopSearchInLNFG();//test
	if (existLoop == true)
	{
		;
	}
	else
	{
		LoopString = "";
		satisfied1 = true;//无环可满足
	}
	DecisionExplainString = "";
	bool satisfied = false;
	vector<simpleGarph*>::iterator iter;
	for (iter = loopSet.begin(); iter != loopSet.end(); iter++)
	{
		int_set interSecRes, temp;
		simpleNode_set::iterator iter1;//仅需得到最小一致标记即可
		for (iter1 = (*iter)->nodeSet.begin(); iter1 != (*iter)->nodeSet.end(); iter1++)
		{
			//int i=(*iter1)->labelSet[0];
			if (iter1 == (*iter)->nodeSet.begin())
			{
				interSecRes = (*iter1)->labelSet;
				temp = interSecRes;
			}
			else
			{
				temp.clear();
				set_intersection((*iter1)->labelSet.begin(), (*iter1)->labelSet.end(), interSecRes.begin(), interSecRes.end(), inserter(temp, temp.end()));
				interSecRes = temp;
			}
		}
		if (interSecRes.size() == 0)
		{
			satisfied_subsimGraphs.push_back((*iter));//zxm add 2014.7.1 
			satisfied = true;
			continue;
		}
		else//有相同标记
		{
			//satisfied=true;
			not_satisfied_subsimGraphs.push_back((*iter));
			DecisionExplainString += "强连通分支 { ";
			simpleNode_set::iterator iter2;
			for (iter2 = (*iter)->nodeSet.begin(); iter2 != (*iter)->nodeSet.end(); iter2++)
			{
				DecisionExplainString += IntTostring((*iter2)->No);
				DecisionExplainString += " ";
			}
			DecisionExplainString += "} same label:";
			int_set::iterator iter3;
			for (iter3 = interSecRes.begin(); iter3 != interSecRes.end(); iter3++)
			{
				DecisionExplainString += "l";
				DecisionExplainString += IntTostring(*iter3);
				DecisionExplainString += " ";
			}
			DecisionExplainString += "\r\n";

		}
	}
	//if (!(satisfied || satisfied1)){
	//	CStdioFile file;
	//	file.Open(".\\SCC.txt", CFile::modeCreate | CFile::modeReadWrite);
	//	file.WriteString(DecisionExplainString);
	//	file.Close();
	//}
	return (satisfied || satisfied1);
}

bool LNFG::labelSetIsEmpty()
{
	bool res = true;
	LNFGNode_set_of_set::iterator iter;
	for (iter = L.begin(); iter != L.end(); iter++)
	{
		if ((*iter).size() != 0)
		{
			res = false;
			break;
		}
	}
	return res;
}
