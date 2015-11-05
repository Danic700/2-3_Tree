
#include "TwoThreeTree.h"


void main()
{
	TwoThreeTree tree;

	tree.insertData(1, string("This is Tal"));
	tree.insertData(2, string("This is Danny"));
	tree.insertData(3, string("This is Iris"));
	tree.insertData(4, string("This is Ned Stark"));
	tree.insertData(6, string("This is Daenerys Stormborn Targaryen"));
	tree.insertData(5, string("This is Cersei Lannister"));
	tree.insertData(7, string("This is Tywin Lannister"));
	tree.insertData(8, string("This is Tyrion Lannister"));
	tree.insertData(12, string("This is Arya Stark"));
	tree.insertData(10, string("This is Sansa Stark"));
	tree.insertData(9, string("This is Bran Stark"));
	tree.insertData(11, string("This is Robb Stark"));
	tree.insertData(16, string("This is Catelyn Stark"));
	tree.insertData(14, string("This Robert Baratheon"));
	tree.insertData(13, string("This is Renly Baratheon"));
	tree.insertData(15, string("This is Stannis Baratheon"));
	tree.insertData(100, string("This is Margerie Tyrell"));
	tree.insertData(50, string("This is Hodor"));
	tree.insertData(90, string("This is Oleanna Tyrell"));

	

	//tree.insertData(0.5, string("This is Viserys Targaryen"));
	//tree.insertData(-1, string("This Rheagar Targaryen"));
	//tree.printData();
	
	try
	{
		tree.deleteData(8);

		tree.printKeys();
	    cout<<endl;

		cout<<tree.find(3)->getData()<<endl;
		tree.insertData(9, string("This i Hodor"));
		tree.deleteData(3);
		cout<<tree.find(7)->getData()<<endl;
		
	tree.printKeys();
	cout<<endl;

	}
	catch(TwoThreeNode * node)
	{

		cout<<"Item not found!"<<endl;
	
	}

	tree.printKeys();
	cout<<endl;
	//tree.printData();

}