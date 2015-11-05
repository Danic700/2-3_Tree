
#include "TwoThreeNode.h"

TwoThreeNode * TwoThreeNode::find(TreeKey inKey)
{
	if(isLeaf)
	{
		if(inKey == key)
			return this;
		else throw NULL;
	
	}
	else
	{
		

		if(right != NULL && inKey >= min3)
			return right->find(inKey);

		else if(inKey >= min2)
			return mid->find(inKey);
		else
			return left->find(inKey);

	}
}

TwoThreeNode * TwoThreeNode::insertData(TwoThreeNode *newNode)
{
	

	if(isLastLevel())
	{
		
		if(numChildren <= 2)
		{
			
			insertInPlace(newNode);
			return NULL;

		}
		else
			return splitOnInsert(newNode);
	}
	
	int pos = findPath(newNode);
	
	
	TwoThreeNode *another = NULL;
	
	if(pos == goRight)
		another = right->insertData(newNode);

	else if(pos == goMiddle)
		another = mid->insertData(newNode);

	else
		another = left->insertData(newNode);

	updateMins(newNode);

	if(another == NULL)
		return NULL;

	
	if(numChildren <= 2)
	{
		insertInPlace(another);
		return NULL;
	}
	else
		return splitOnInsert(another);

	
}

//here newNode is a leaf
int TwoThreeNode::findPath(TwoThreeNode * newNode)
{
	
	if(right != NULL && newNode->key >= min3)
		return goRight;
	else if(newNode->key >= min2)
		return goMiddle;
	else
		return goLeft;

}

int TwoThreeNode::findPath(TreeKey k )
{
	
	if(right != NULL && k >= min3)
		return goRight;
	else if(k >= min2)
		return goMiddle;
	else
		return goLeft;


}

void TwoThreeNode::insertInPlace(TwoThreeNode * newNode)
{
	
	numChildren++;

	//the node is a leaf
	if(newNode->isLeaf)
	{
		//adding leaves to the root - specific case
		if(left == NULL || mid == NULL)
		{
			if(left != NULL)
			{
				if(newNode->key < left->key)
				{
					mid = left;
					left = newNode;
				}
				else
					mid = newNode;

				min1 = left->key;
				min2 = mid->key;
			}
			else
			{
				left = newNode;
				min1 = newNode->key;
			}
		}
		
		//the general case
		else 
		{
			if(newNode->key > mid->key)
			{
				right = newNode;
				/*min3 = newNode->key;*/
			}
			
			else if(newNode->key > left->key)
			{
				//swapLeaves(right, mid);
				right = mid;
				mid = newNode;
				/*min3 = right->key;
				min2 = mid->key;*/
			}
			else
			{
				right = mid;
				mid = left;
				left = newNode;
			}
			
			min1 = left->key;
			min2 = mid->key;
			min3 = right->key;
		}
	}
	else //we add a brother
	{
		if(newNode->min1 < left->min1)
		{
			right = mid;
			mid = left;
			left = newNode;
		}
		else if(newNode->min1 < mid->min1)
		{
			right = mid;
			mid = newNode;
		
		}
		else
			right = newNode;

		
		min1 = left->min1;
		min2 = mid->min1;
		min3 = right->min1;
	}

}	
	

void TwoThreeNode::swapMins(TreeKey k1, TreeKey k2)
{
	TreeKey tmp = k1;

	k1 = k2;

	k2 = tmp;


}

bool TwoThreeNode::isLastLevel()
{
	
	if(left == NULL || (left != NULL && left->isLeaf == true))
		return true;
	else
		return false;

}

TwoThreeNode * TwoThreeNode::splitOnInsert(TwoThreeNode *newNode)
{

	TwoThreeNode *brother = new TwoThreeNode();

	brother->numChildren = 2;
	brother->isLeaf = false;

	//brother->left = left;

	if(newNode->isLeaf)
	{
		if(right != NULL && newNode->key > right->key)
		{
			brother->left = left;
			brother->mid = mid;
			left = right;
			mid = newNode;
		}
		else if(newNode->key > mid->key)
		{
			brother->left = left;
			brother->mid = mid;
			left = newNode;
			mid = right;
		}
		else if(newNode->key > left->key)
		{
			brother->left = left;
			brother->mid = newNode;

			left = mid;
			mid = right;
		}
		else
		{
			brother->left = newNode;

			brother->mid = left;
		}

		brother->min1 = brother->left->key;
		brother->min2 = brother->mid->key;
		min1 = left->key;	
		min2 = mid->key;

	}
	else
	{
		//cout<<"im here!!";

		if(newNode->min1 < left->min1)
		{
			

			brother->left = newNode;
			brother->mid = left;

			left = mid;
			mid = right;
		}
		else if(newNode->min1 < mid->min1)
		{
			

			brother->left = left;
			brother->mid = newNode;
			left = mid;
			mid = right;
		}
		else
		{
			
			brother->left = left;
			brother->mid = mid;
			left = newNode;
			mid = right;
		}

		brother->min1 = brother->left->min1;
		brother->min2 = brother->mid->min1;
		
		min1 = left->min1;
		min2 = mid->min1;
	}
	
	right = NULL;
	
	numChildren--;
	
	//min3 = -1;
	
	
	return brother;

}

//here newNode is a leaf
void TwoThreeNode::updateMins(TwoThreeNode *newNode)
{

	if(newNode->key < min1)
		min1 = newNode->key;
	
	else if(newNode->key < min2)
		min2 = newNode->key;

	else if(right != NULL && newNode->key < min3)
		min3 = newNode->key;

}

void TwoThreeNode::updateMins(TreeKey k)
{

	if(k == min1 && left != NULL)
		min1 = left->min1;

	else if(k == min2 && mid != NULL)
		min2 = mid->min1;

	else if(right != NULL && k == min3)
		min3 = right->min1;

	/*if(k < min1)
		min1 = k;
	
	else if(k < min2)
		min2 = k;

	else if(right != NULL && k < min3)
		min3 = k;*/


}

void  TwoThreeNode::swapLeaves(TwoThreeNode *L1, TwoThreeNode *L2)
{

	TwoThreeNode * tmp = L1;

	L1 = L2;

	L2 = tmp;

}

void TwoThreeNode::printKeys()
{
	
	
	if(isLeaf)
		cout<<key<<' ';
	else
	{
		
		if(left != NULL)
			left->printKeys();
		
		if(mid != NULL)
			mid->printKeys();
		
		if(right != NULL)
			right->printKeys();


	}

}

void TwoThreeNode::printData()
{
	
	if(isLeaf)
		cout<<Data<<' ';
	else
	{
		
		if(left != NULL)
			left->printData();
		
		if(mid != NULL)
			mid->printData();
		
		if(right != NULL)
			right->printData();
	}

}

TwoThreeNode * TwoThreeNode::deleteData(TreeKey k, TwoThreeNode *uncle)
{

	if(isLastLevel())
	{
		
		if(left->key == k)
			left = NULL;					//delete left;
		else if(mid->key == k)
			mid = NULL;								//delete mid;
		else if(right->key == k)
			right = NULL;									//delete right;

		numChildren--;

		if(numChildren == 2)
		{
			twoChildrenLeft();
			return NULL;
		}
		else
		{

			if(uncle != NULL && uncle->numChildren == 3)
			{
				borrowFromUncle(uncle);
				return NULL;
			}
			else if(uncle != NULL)
			{
				transferToUncle(uncle);
				//deleteNode;
				return this;
			}
			else if(uncle == NULL)
				return this;
		}
	}
	
	
	int pos = findPath(k);
	
	
	TwoThreeNode *another = NULL;
	
	
	if(pos == goRight)
		another = right->deleteData(k, mid);
	
	else if(pos == goMiddle)
		another = mid->deleteData(k, left); //or right??
	
	else
		another = left->deleteData(k, mid);
	
	
	updateMins(k);
	
	
	if(another == NULL)
		return NULL;
	
	
	if(another == left)
		left = NULL;				//delete left;
	else if(another == mid)
		mid = NULL;					//delete mid;
	else
		right = NULL;					//delete right;
	
	numChildren--;
	
	
	if(numChildren == 2)
	{
		twoChildrenLeft();
		return NULL;
	}
	else //one child left
	{
		if(uncle != NULL && uncle->numChildren == 3)
		{
			borrowFromUncle(uncle);
			return NULL;
		}
		else if(uncle != NULL)
		{
			transferToUncle(uncle);
			return this;
		}
		else if(uncle == NULL)
			return this;
	}
}

void TwoThreeNode::twoChildrenLeft()
{
	
	min3 = DELETED;
	
	
	if(right == NULL){}
	
	
	else if(mid == NULL)
		mid = right;
	
	else if(left == NULL)
	{
		left = mid;
		mid = right;
	}
	
	if(isLastLevel())
	{
		min1 = left->key;
		min2 = mid->key;
	}
	
	else
	{
		min1 = left->min1;
		min2 = mid->min1;
	}

	right = NULL;
}



void TwoThreeNode::borrowFromUncle(TwoThreeNode * uncle)
{
	if(uncle->min1 < min1)
	{
		
		if(left == NULL)
			left = uncle->right;
		
		else if(mid == NULL)
		{
			mid = left;
			left = uncle->right;
		}
	}
	else
	{
		if(left == NULL)
		{
			left = mid;
			mid = uncle->left;

		}
		else if(mid == NULL)
			mid = uncle->left;

		uncle->left = uncle->mid;
		uncle->mid = uncle->right;
	}
	
	if(isLastLevel())
	{
		uncle->min1 = uncle->left->key;
		uncle->min2 = uncle->mid->key;
		min1 = left->key;
		min2 = mid->key;
	}
	else
	{
		uncle->min1 = uncle->left->min1;
		uncle->min2 = uncle->mid->min1;
		min1 = left->min1;
		min2 = mid->min1;
	}

	uncle->min3 = DELETED;
	uncle->right = NULL;

	min3 = DELETED;
	right = NULL;

	uncle->numChildren--;
	numChildren++;

}


void TwoThreeNode::transferToUncle(TwoThreeNode * uncle)
{
	if(uncle->min1 < min1)
	{
		
		if(left == NULL)
			uncle->right = mid;

		else if(mid == NULL)
			uncle->right = left;

	}
	else
	{
		uncle->right = uncle->mid;
		uncle->mid = uncle->left;

		if(left == NULL)
			uncle->left = mid;
		else if(mid == NULL)
			uncle->left = left;
	}
	if(uncle->isLastLevel())
	{
		
		uncle->min1 = uncle->left->key;
		uncle->min2 = uncle->mid->key;
		uncle->min3 = uncle->right->key;
	}
	else
	{
		uncle->min1 = uncle->left->min1;
		uncle->min2 = uncle->mid->min1;
		uncle->min3 = uncle->right->min1;
	}


	uncle->numChildren++;

	//is this necessary?
	left = mid = right = NULL;
	min1 = min2 = min3 = DELETED;
	
	numChildren--;
}

//TwoThreeNode * deleteNode(TwoThreeNode * node)
//{
//
//
//
//
//}