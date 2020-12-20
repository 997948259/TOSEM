#if !defined(__function_H__)
#define __function_H__


#include<vector>
#include <string>
#include "ConsLNFG.h"
#include "Machine.h"
#include <queue>

string IntTostring(int num);
int find_edge_by_point(LNFGEdge_set set, LNFGNode* ln);
int find_node_from_edge(LNFGNode_set set, CTreeNode* ptree);
int get_node_no_of_cl(LNFGNode_set set, LNFGNode* ln);
bool makeNO(LNFG *lnfg);
string drawLNFG(LNFG *lnfg);
//string drawLNFGNode(LNFG *lnfg);
//string drawLNFGEdge(LNFG *lnfg);
void ModelCheck();
void TraceCheck();

void GetLabelOfNode(LNFGNode* ln, int_set* label, LNFG *lnfg);

void drawPic(LNFG *lnfg);

#endif