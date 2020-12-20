/*author : ������*/

#include"ConsLNFG.h"

/*LNFGNode member functions and other function used*/
//�ж��Ƿ�����and�ṹ���ҵ�һ��ֱ��EMPTY�ڵ�
bool findEmptyNodeInAnd(CTreeNode* ptree)
{
	CTreeNode* temp1;
	temp1 = ptree;//��ptree���ڵ㿪ʼ����and������
	bool find = false;
	adjust_right_child_and(temp1);//����ʹ������������and�ڵ�
	while (temp1->type == AND_STA && temp1->child[0]->type == AND_STA)
	{
		if (temp1->child[1]->type == EMPTY_EXP)
		{
			find = true; return find;
		}//�ҵ��Ժ�ֱ�ӷ��أ���Ϊ���ǽ��������Ƿ���EMPTY�������Ǻ��ж���
		temp1 = temp1->child[0];//δ�ҵ��Ļ�,���������������
		adjust_right_child_and(temp1);//����ʹ������������and�ڵ�
	}
	if (temp1->type == AND_STA && temp1->child[0]->type != AND_STA)//����and�ṹ�Ĵ���
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

//�ж��Ƿ�����and�ṹ���ҵ�һ��ֱ��next�ڵ�
bool findNextNodeInAnd(CTreeNode* ptree)
{
	CTreeNode* temp1;
	temp1 = ptree;//��ptree���ڵ㿪ʼ����and������
	bool find = false;
	adjust_right_child_and(temp1);//����ʹ������������and�ڵ�
	while (temp1->type == AND_STA && temp1->child[0]->type == AND_STA)
	{
		if (temp1->child[1]->type == NEXT_STA)
		{
			find = true; return find;
		}//�ҵ��Ժ�ֱ�ӷ��أ���Ϊ���ǽ��������Ƿ���next�������Ǻ��ж���
		temp1 = temp1->child[0];//δ�ҵ��Ļ�,���������������
		adjust_right_child_and(temp1);//����ʹ������������and�ڵ�
	}
	if (temp1->type == AND_STA && temp1->child[0]->type != AND_STA)//����and�ṹ�Ĵ���
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
////���캯��
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
////���캯��
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
//�������캯��
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

////��������ڵ㲢�õ�terminal part����ĿAddE
void LNFGNode::setAddE()
{
	if (this->node->type == OR_STA)//���ж����ȡ����
	{
		CTreeNode* temp1;
		temp1 = this->node;//�Ӹ��ڵ㿪ʼ��ÿ����һ��EMPTY�ͼ�һ��terminal����
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
		if (temp1->type == OR_STA && temp1->child[0]->type != OR_STA)//����or�ṹ�Ĵ���
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
	else//û��or��������ֻ��һ����Ҫ����
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

////��������ڵ㲢�õ�nonterminal part����ĿAddN
void LNFGNode::setAddN()
{
	if (this->node->type == OR_STA)
	{
		CTreeNode* temp1;
		temp1 = this->node;//�Ӹ��ڵ㿪ʼ��ÿ����һ��next�ͼ�һ��terminal����
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
		if (temp1->type == OR_STA && temp1->child[0]->type != OR_STA)//����or�ṹ�Ĵ���
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
	else//û��or��������ֻ��һ����Ҫ����
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

////���markΪtrue�����Ѿ�����������ڵ�
void LNFGNode::markToTrue()
{
	mark = true;
}

//add terminal part
void LNFGNode::addTerminal(CTreeNode* ptree)
{
	CTreeNode* temp1 = new CTreeNode(AND_STA, "AND", 0);
	temp1->copy_tree(ptree);
	terminal.push_back(temp1);//��temp1���뵽����terminal��
	//delete temp1;
	AddE++;
}


//add future part
void LNFGNode::addFuture(CTreeNode* ptree)
{
	CTreeNode *temp1 = new CTreeNode(AND_STA, "AND", 0);
	temp1->copy_tree(ptree);
	future.push_back(temp1);//��temp1���뵽����terminal��
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
	bool res = temp1->compare2(temp2);//����CtreeNode�ĳ�Ա����������fin�ȼ۵ıȽ�
	delete temp1;
	delete temp2;
	return res;
}

/*LNFGEdge member functions*/
//LNFGEdge���캯��������������������
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
//LNFGEdge����������
LNFGEdge::~LNFGEdge()
{
	delete start;
	delete end;
	delete edgeSpec;
}

/*LNFG �༰��غ���*/

//��ptree�е���ȡ��õ�������LNFG�ڵ㣬֮�����set��
void getDisPart(LNFGNode_set* node_set, CTreeNode *ptree)
{
	if (ptree->type != OR_STA)//����һ����ȡ��
	{
		LNFGNode* ln = new LNFGNode(ptree);
		node_set->push_back(ln);
		//delete ln;
	}
	else//���ж����ȡ��
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

//���캯����Ĭ�ϱ��뺬�в���
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

//�����������ͷ���Դ
LNFG::~LNFG()
{
	delete Node;
	V0.clear();
	CL.clear();
	CL1.clear();
	EL.clear();
	L.clear();
}

//��CL��CL1�еõ�һ��δ������Ľڵ�,����iteration�����
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


//�����������LNFG�����㼯���߼��ϱ�Ǽ�
/*
void LNFG::showLNFG()
{
	//	currently we just use text to show LNFG
	CNFMachine cnf;
	CStdioFile file;
	file.Open(".\\result", CFile::modeCreate | CFile::modeReadWrite);

	//��ʾ��ʼ�ڵ㼯��
	file.WriteString("��ʼ�ڵ㼯��: \n");
	LNFGNode_set::iterator iter_start;
	for (iter_start = V0.begin(); iter_start != V0.end(); iter_start++)
	{

		string show_str = " ";
		cnf.showout = "";
		show_str += cnf.show((*iter_start)->node);
		show_str += "\n";
		file.WriteString(show_str);
	}

	//��ʾ�ڵ�ļ���
	file.WriteString("�ڵ㼯��: \n");
	LNFGNode_set::iterator iter;
	for (iter = CL.begin(); iter != CL.end(); iter++)
	{
		string show_str1 = " ";
		cnf.showout = "";
		show_str1 += cnf.show((*iter)->node);
		show_str1 += "\n";
		file.WriteString(show_str1);
	}
	//  	//��ʾ�����ڵ�ļ���
	//  	file.WriteString("�����ڵ㼯��: \n");
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
	//��ʾ�ߵļ���
	file.WriteString("�ߵļ���: \n");
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
	//��ʾ��Ǽ���
	LNFGNode_set_of_set::iterator iter2;
	int label_num = 1;
	file.WriteString("��Ǽ��� : \n");
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
//��CL��CL1�ϲ���CL�У�whileѭ��֮��Ĳ��֣�
void LNFG::MergeCL()
{
	LNFGNode_set::iterator iter;
	for (iter = CL1.begin(); iter != CL1.end(); iter++)
	{
		CL.push_back(*iter);
	}
}
//�жϣţͣУԣٽڵ��Ƿ���CL��
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
//����terminal part
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
//�ж�ptree�Ƿ�����set���ҵ���ͬ�Ĺ�ʽ,�������ptree��д֮������ҵ�Ҳ������ֵ
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

//����set�д��ں�ptree final�ȼ۵Ľڵ��򷵻�true
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
//����nonterminal part	
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
				if (treenode_in_LNFGset((*iter)->child[0], CL))//Qfj����CL,ֱ�����ӱ�;����һ������������д�����ʽ����CL��Ҳ��������CL����Ϊ������Ȼ������ǰ��ĳһ������д�滻�ˣ�
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
							LNFGEdge* le = new LNFGEdge(NodeOrig, CL[iter_no1]->node, temp1);//�ӱ�
							if ((*iter)->child[0]->type == EMPTY_EXP)
							{
								le->m_endTrueEMPTY = true;
							}
							EL.push_back(le);
						}
						else
						{
							LNFGNode* ln = new LNFGNode((*iter)->child[0]);//�ӽڵ�
							if ((*iter)->child[0]->type == EMPTY_EXP)
							{
								ln->m_isTrueEmpty = true;
							}
							CL1.push_back(ln);
							//delete ln;
							LNFGEdge* le = new LNFGEdge(NodeOrig, (*iter)->child[0], temp1);//�ӱ�
							if ((*iter)->child[0]->type == EMPTY_EXP)
							{
								le->m_endTrueEMPTY = true;
							}
							EL.push_back(le);
						}
					}
					else//Qcj����CL��
					{
						LNFGNode* ln = new LNFGNode((*iter)->child[0]);//�ӽڵ�
						if ((*iter)->child[0]->type == EMPTY_EXP)
						{
							ln->m_isTrueEmpty = true;
						}
						CL.push_back(ln);
						//delete ln;
						LNFGEdge* le = new LNFGEdge(NodeOrig, (*iter)->child[0], temp1);//�ӱ�
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
				if (treenode_in_LNFGset((*iter)->child[1]->child[0], CL))//Qfj�Ƿ�����CL//ֱ�����ӱ�
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
					if (iter_no1 != -1)//Qcj����CL��fin�ȼ�
					{
						int iter_no2 = existFinEqual((*iter)->child[1]->child[0], CL1);
						if (iter_no2 != -1)
						{
							LNFGEdge* le = new LNFGEdge(NodeOrig, CL[iter_no1]->node, (*iter)->child[0]);//�ӱ�
							if ((*iter)->child[1]->child[0]->type == EMPTY_EXP)
							{
								le->m_endTrueEMPTY = true;
							}
							EL.push_back(le);
						}
						else
						{
							LNFGNode* ln = new LNFGNode((*iter)->child[1]->child[0]);//�ӽڵ�
							if ((*iter)->child[1]->child[0]->type == EMPTY_EXP)
							{
								ln->m_isTrueEmpty = true;
							}
							CL1.push_back(ln);
							//delete ln;
							LNFGEdge* le = new LNFGEdge(NodeOrig, (*iter)->child[1]->child[0], (*iter)->child[0]);//�ӱ�
							if ((*iter)->child[1]->child[0]->type == EMPTY_EXP)
							{
								le->m_endTrueEMPTY = true;
							}
							EL.push_back(le);
						}
					}
					else//Qcj����CL��
					{

						LNFGNode* ln = new LNFGNode((*iter)->child[1]->child[0]);//�ӽڵ�
						if ((*iter)->child[1]->child[0]->type == EMPTY_EXP)
						{
							ln->m_isTrueEmpty = true;
						}
						CL.push_back(ln);
						//delete ln;
						LNFGEdge* le = new LNFGEdge(NodeOrig, (*iter)->child[1]->child[0], (*iter)->child[0]);//�ӱ�
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
//�ж�һ�����Ƿ���Ϊ�ߵ���ʼ�ڵ�
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
//ȥ�������ķ�EMPTY��
void LNFG::deleteIsolateNode()
{
	int isolateNodeNo = existIsolateNode();
	if (isolateNodeNo == -1)
	{
		return;
	}
	else
	{
		//ɾ����ر�
		deleteRelevantEdge(isolateNodeNo);
		//ɾ����Ǽ����еĵȼ۵�
		deleteSameNodeInL(isolateNodeNo);
		//ɾ����(V0��CL)
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
		//����
		deleteIsolateNode();
	}

}
//�ӱ�����ֵõ���ǵ�����
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
//��Lk�����ӽڵ�
void LNFG::Add_node_to_L(LNFGNode* R, int k)
{
	LNFGNode_set_of_set::iterator iter;
	iter = L.begin();
	for (int i = 1; i<k; i++)//��������k������ 
	{
		iter++;
	}
	(*iter).push_back(R);
}
//�ж�and��ȡ���Ƿ���len()��skip��empty����ȷ��ֹ�zxm add 2014.02.15
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


//����ǰ��ptree������������Ϊchop������final���
void LNFG::Add_fin_to_chop(LNFGNode* R, CTreeNode* ptree, int_set* nums)
{
	//***********************���Ӳ���Ҫ��fin��ǵ�����ж�************************// zxm add 2014.02.15
	if ((ptree->child[0]->type == AND_STA || ptree->child[0]->type == NEXT_STA) && isTerminal(ptree->child[0]))
	{
		return;
	}
	else if (ptree->child[0]->type == SKIP_EXP || ptree->child[0]->type == LEN_STA || ptree->child[0]->type == EMPTY_EXP)
	{
		return;
	}
	if (ptree->child[0]->type == AND_STA && ptree->child[0]->child[1]->type == FIN_EXP)//�����Ѿ������
	{
		string label = ptree->child[0]->child[1]->child[0]->name_str;
		int l_num = get_num_form_name(label);
		(*nums).push_back(l_num);
	}
	else if (ptree->type == FIN_EXP && ptree->child[0]->name_str[0] == 'l')////////????????????��������Ϊchop������������
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
		//�õ�lk
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
		//�õ���ȡʽ
		CTreeNode* temp2 = new CTreeNode(AND_STA, "AND", 0);
		temp2->child[0] = new CTreeNode(AND_STA, "AND", 0);
		temp2->child[1] = new CTreeNode(AND_STA, "AND", 0);
		temp2->child[0]->copy_tree(ptree->child[0]);
		temp2->child[1]->copy_tree(temp3);
		//�˴���д
		if (ptree->child[0]->type == TRUE_EXP)
		{
			ptree->child[0]->copy_tree(temp3);
		}
		else
			ptree->child[0]->copy_tree(temp2);
		delete temp2;
		delete temp3;
		//���Ӽ��ϣ��ı�kֵ
		LNFGNode_set ln_set;
		L.push_back(ln_set);
		(*nums).push_back(k);
		k++;
		//	temp
	}
}
//�ж�һ��LNFG���Ƿ���һ��LNFG������,���������
int node_in_set_replace(LNFGNode* R_cp, LNFGNode_set set)
{
	// 	CNFMachine cnf;
	// 	string Str=cnf.show(R_cp->node);//����ԭ�������compare������һ�������⣬������ʱ����string�ıȽ�����������
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
//ɾȥand�ṹ�е�EMPTY����
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
//��rewriteOneDisPart�������ã�����ÿһ���ֵĺ�ȡʽ
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
//����next���֣���ʵ�Ͻ���next��������д
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
//����ÿһ����ȡ���֣���empty�򲻴�����next����Ҫ�����ڲ���chop
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
//����÷�ʽ֮��Ӧ�ý�EMPTY&&p;q����ʽ��дΪp&&q,   �������normalform��������֮�󣬾�Ӧ�ð��������ɾȥ����
void LNFG::rewriteEmptyChop(LNFGNode* R)
{
	if (R->node->type != OR_STA)//��һ���ȡ
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

//��дfin֮�󣬸��±ߵļ���
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

//��д��ʽ������final���
void LNFG::rewriteFin(LNFGNode* R)
{
	// 	CTreeNode* pOrig=new CTreeNode(AND_STA,"AND",0);
	// 	pOrig->copy_tree(ptree);
	LNFGNode R_cp(R->node);
	int_set ist;
	if (R->node->type != AND_STA)//��һ���ȡ
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
	else//����and����ÿ����һ��chop�ӹ�ʽ����дR
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
	//��д���֮�󣬼�����Ӧ�ĸ���L������
	int_set::iterator iter_int;
	for (iter_int = ist.begin(); iter_int != ist.end(); iter_int++)
	{
		LNFGNode* addNode = new LNFGNode(R->node);
		Add_node_to_L(addNode, (*iter_int));
	}
	//�����Ҫ����V0��CL��CL1
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
		//��Ҫ����EL
		updateEL(&R_cp, R);
	}
}

//�㷨�ֵ�һ��whileѭ��
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
	//1.��ʽR��Ԥ�������
	//	LNFGNode* ln=new LNFGNode((*iter)->node);
	cnf.PRE(ln->node);
	if (this->cl_active&&!ln->node->compare(CL[iter_no]->node))
	{
		//Ҳ��Ҫ����EL��L
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
		//Ҳ��Ҫ����EL��L
		updateEL(CL1[iter_no], ln);
		delete CL1[iter_no];
		CL1[iter_no] = new LNFGNode(ln->node);
		CL1[iter_no]->markToTrue();

	}
	//	showLNFG();
	if (ln->node->type != FALSE_EXP)
	{
		//2.��д��ʽR
		rewriteFin(ln);
		//		showLNFG();//delete later!!!!
		//3.��ù�ʽ��normalform
		cnf.NF(ln->node);

		cnf.POST(ln->node);

		//2013.6.20�¼Ӳ��֣�empty&&p;q--->p&&q	
		rewriteEmptyChop(ln);
		// 		string test="";
		// 		cnf.showout="";
		// 		test+=cnf.show(ln->node);
		//4.����AddE��AddN��ֵ
		ln->setAddE();
		ln->setAddN();
		//5.����terminal��nonterminal����
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

//����LNFG����
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
		while (iter_no >= 0)//whileѭ��
		{
			if (this->cl_active)
			{
				CL[iter_no]->markToTrue();
			}
			else
			{
				CL1[iter_no]->markToTrue();
			}
			loopOnce(iter_no);//һ��ѭ����ִ��
			iter_no = get_R_form_CL_or_CL1();
			//this->showLNFG();
		}
		MergeCL();
		MergeEgdeOfSameLoc();
		deleteIsolateNode();
	}

	//this->showLNFG();
}

void LNFG::GetLabelOfNode(LNFGNode* ln, int_set* label)//�õ��ڵ�ln�����ı�Ǽ��ϵı�ż�
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
static string IntTostring(int num)//ʹ��stringstream��int���͵�����ת��Ϊstring���͵�����
{
	string str;
	string str1;
	stringstream ss;
	ss << num;
	ss >> str1;
	str = str1.c_str();
	return str;
}
string LNFG::addNodeInfo(string NodeInfo, LNFGNode *ln)//���ӽڵ���Ϣ
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
		NodeInfo += "#";//�ָ���ʽ�ͱ�ǲ���
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

string LNFG::addEdgeInfo(string edgeInfo, int edgeId, LNFGEdge *le, int startId, int endId)//���ӱߵ���Ϣ
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

string LNFG::addTerminalEdgeInfo(string edgeInfo, int edgeId, int startId, int EndId)//������ֹ�ߵ���Ϣ
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

string LNFG::addTerminalNodeInfo(string nodeInfo, int nodeId)//������ֹ�ڵ����Ϣ
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
	//���������ͬ���յ���ͬ�ı߱ض����Ǳ�����ڵıߡ����Բ���Ҫ����ѭ������������һ�Ա�
	LNFGEdge_set::iterator iter;
	iter = EL.begin(); iter++;
	CTreeNode* temp1;
	CNFMachine cnf;
	int i = 1;

	while (iter != EL.end())
	{
		if (EL[i]->start->compare(EL[i - 1]->start) && EL[i]->end->compare(EL[i - 1]->end))
		{//�ͺ�һ���߾�����ͬ����ʼ����ֹ�ڵ�
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
/*//���ӣ�ɾ���Ի�  zxm2014.03.24
//�޸�tarjan�㷨�󣬴˺�������Ҫʹ��
bool LNFG::deletealoopInSimGraph()
{
vector<simpleEdge*>::iterator iter;
bool sign=false;
for (iter=simGraphofLNFG.edgeSet.begin();iter!=simGraphofLNFG.edgeSet.end();)
{
if((*iter)->start==(*iter)->end)
{
vector<simpleNode*> newLoop;//�½�ѭ��
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

	//ɾ�����Ϊ��͌��Ϊ��Ľڵ�
	deleteIrrelevantNodes();
	if (simGraphofLNFG.nodeSet.size() == 0)
	{
		return existLoop;
	}
	else
	{
		existLoop = true;
	}
	//Tarjan�㷨���ǿ��ͨ��ͼ,��ɵ�Ļ���

	tarjanOfSimGraph(simGraphofLNFG.nodeSet[0]);

	int unpartitionedNo = firstUnpartitioned(simGraphofLNFG.nodeSet);
	while (unpartitionedNo != -1)
	{
		tarjanIndex = 0;
		tarjanOfSimGraph(simGraphofLNFG.nodeSet[unpartitionedNo]);
		unpartitionedNo = firstUnpartitioned(simGraphofLNFG.nodeSet);
	}
	//��ɱߵĻ���
	partitionSimEdges();
	/*	showSimpleGraph(subSimGraphs[0]);*/
	//dfs
	vector<simpleGarph*>::iterator iter;
	for (iter = subSimGraphs.begin(); iter != subSimGraphs.end(); iter++)//�ֱ��ÿһ����ͼdfs
	{
		if ((*iter)->nodeSet.size() == 1)//ͼ�н���һ���ڵ㣬�鿴�Ի�
		{
			if ((*iter)->edgeSet.size() == 1 && (*iter)->edgeSet[0]->start == (*iter)->nodeSet[0]->No && (*iter)->edgeSet[0]->end == (*iter)->nodeSet[0]->No)
			{
				/*	vector<simpleNode*> newLoop;//�½�ѭ��
				newLoop.push_back((*iter)->nodeSet[0]);
				loopSet.push_back(newLoop);//��ѭ�����뵽ѭ��������*/
				loopSet.push_back((*iter));
			}
		}
		else//�����
		{
			/*
			dfsStack.push_back((*iter)->nodeSet[0]);
			dfsSubOneGraph(*iter);
			*/
			/*    �޸�      zxm  2014.05.06*/
			/*vector<simpleNode*> newLoop;//�½�ѭ��
			vector<simpleNode*>::iterator iter_node;
			for(iter_node=((*iter)->nodeSet).begin();iter_node!=((*iter)->nodeSet).end();iter_node++)
			{
			newLoop.push_back(*iter_node);
			}
			//	newLoop.push_back((*iter)->nodeSet);
			loopSet.push_back(newLoop);//��ѭ�����뵽ѭ��������*/
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

	//��ʾ�ڵ�ļ���
	file.WriteString("�ڵ㼯��: \n");
	vector<simpleNode*>::iterator iter;
	for (iter = simGraph->nodeSet.begin(); iter != simGraph->nodeSet.end(); iter++)
	{
		string show_str1 = IntTostring((*iter)->No);
		show_str1 += "\n";
		file.WriteString(show_str1);
	}
	vector<simpleEdge*>::iterator iter1;
	//��ʾ�ߵļ���
	file.WriteString("�ߵļ���: \n");
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
zxm���ӣ��ж�һ������Ƿ���ջ��2014.3.24
*/
bool isInStack(simpleNode *node, stack<simpleNode*> tjstack){
	stack<simpleNode*> temp;//��ʱ�����洢����������
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
		if ((*iter)->start == node->No)//��nodeΪ��ʼ��
		{

			int endNode = nodeNoToNode((*iter)->end, &simGraphofLNFG);
			/*if (simGraphofLNFG.nodeSet[endNode]->visited==true)//�ж���������
			{
			node->Low=(node->Low<=simGraphofLNFG.nodeSet[endNode]->DFN)?node->Low:simGraphofLNFG.nodeSet[endNode]->DFN;
			}
			else
			{
			tarjanOfSimGraph(simGraphofLNFG.nodeSet[endNode]);
			node->Low=(node->Low<=simGraphofLNFG.nodeSet[endNode]->Low)?node->Low:simGraphofLNFG.nodeSet[endNode]->Low;
			}*/
			if (isInStack(simGraphofLNFG.nodeSet[endNode], tarjanStack))//////zxm�޸�2014.3.24
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
		//���start��endͬʱ����ĳ����ͼ�У��򽫱߼��뵽�����ͼ
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
simpleNode* topNode=dfsStack.back();//�����е�back��ģ��ջ��ջ��
vector<simpleEdge*>::iterator iter;
for (iter=graph->edgeSet.begin();iter!=graph->edgeSet.end();iter++)
{
if ((*iter)->start==topNode->No)//topNode�ĳ���
{
int terminalNodeLoc=nodeInStack((*iter)->end);
if (terminalNodeLoc!=-1)//�ߵ�ĩ����ջ��
{
//��terminalNodeLoc�γ�һ������������loopSet��
simpleNode_set newLoop;
for (int i=terminalNodeLoc;i<dfsStack.size();i++)
{
newLoop.push_back(dfsStack[i]);
}
loopSet.push_back(newLoop);
}
else
{
//�½ڵ���ջ
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
		satisfied1 = true;//�޻�������
	}
	DecisionExplainString = "";
	bool satisfied = false;
	vector<simpleGarph*>::iterator iter;
	for (iter = loopSet.begin(); iter != loopSet.end(); iter++)
	{
		int_set interSecRes, temp;
		simpleNode_set::iterator iter1;//����õ���Сһ�±�Ǽ���
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
		else//����ͬ���
		{
			//satisfied=true;
			not_satisfied_subsimGraphs.push_back((*iter));
			DecisionExplainString += "ǿ��ͨ��֧ { ";
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
