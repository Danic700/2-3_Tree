#ifndef _TWO_THREE_TREE
#define _TWO_THREE_TREE


class TwoThreeNode;

#include "TwoThreeNode.h"



class TwoThreeTree{

	TwoThreeNode * root;

public:

	TwoThreeTree(){root = new TwoThreeNode(); root->isLeaf = false; root->isRoot = true;}
	
	
	TwoThreeNode *find(TreeKey );
	void insertData(TreeKey, string );
	void deleteData(TreeKey );
	
	void printKeys();
	void printData();




};


#endif