#ifndef ASSOCIATE
#define ASSOCIATE
#include "std_lib_facilities.h"
#include "Graph.h"

void start()
{
	cout << endl;
	cout << "Hello, this Program is Designed by Lance. We can Do some Magic Things and Here are some Choices:" << endl
		<< "1 : Input or Add Points to the Graph" << endl
		<< "2 £ºCut the Graph into Pieces" << endl
		<< "3 : Find Available Points" << endl
		<< "4 : Find the Nearest Way" << endl << endl;
	return;
}

int Rand_Graph()
{
	int mode;
	int count;
	cout << "Please Input Your Mode , '0' to Create New Graph , '1' to Add Points : " << endl;

	cin >> mode;

	if (mode == 0)
	{
		cout << "Please Input the Number of the Lines : " << endl;
		cin >> count;
		Graph pic(count);
		pic.Input_random_Graph(count);

		return 1;
	}
	if (mode == 1)
	{
		cout << "Please Input the Number of the Lines : " << endl;
		cin >> count;
		Graph pic(count);
		pic.Add_random_Graph(count);

		return 2;
	}
	else
	{
		cout << "Input Error" << endl;
		return 0;
	}
}

#endif