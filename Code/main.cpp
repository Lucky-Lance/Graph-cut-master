#include "std_lib_facilities.h"
#include "Graph.h"
#include "Associate.h"

int main()
{
	start();

	int choice;
	cin >> choice;
	Graph my_graph;
	if (choice == 1)
		Rand_Graph();
	else if (choice == 2)
	{
		int number = 0;
		cout << endl << "Please Input the Most Number of One Graph : " << endl;
		cin >> number;
		my_graph.Read_Graph();
		my_graph.Cut_Graph(number);
	}
	else if (choice == 3)
	{
		int number;
		cout << "Please Input the Number You Want to Search" << endl;
		cin >> number;
		my_graph.bfs(number);
	}
	else if (choice == 4)
	{
		int begin, end;
		cout << "Please Input the Two Numbers : ";
		cin >> begin >> end;
		my_graph.Find_dis(begin, end);
	}
	else
	{
		cout << "Input Error !" << endl;
	}

	system("pause");
	return 0;
}