#ifndef GRAPH
#define GRAPH

#include "std_lib_facilities.h"

class Graph
{
	int number;// line number
	map<int, vector<pair<int, double>>> Graph_dics;
	map<int, vector<pair<int, double>>> Merge_dics;
	map<int, int> Point_dics;
	map<pair<int, int>, double> Easy_Graph_dics;
	map<int, int> Points;
	vector<int> Circle;
	vector<pair<pair<int, int>, double>> Sort_Graph;
	vector<set<int>> CutGraph;
	map<int, bool>visited;
	vector<int> Avail_Points;
	map<int, int> Merge_Points;
	map<string, bool> Dis_visited;
	map<int, double> distance;
	map<int, int>prev;
	map<int, bool>known;
public:
	Graph(int x);
	void Input_random_Graph(int);
	void Add_random_Graph(int);
	void Random_Graph(ofstream&, int);
	void Read_Graph();
	void bfs(int number);
	void Cut_Graph(int n);
	void My_BFS(string, int);
	vector<int> Private_bfs(int number, map<int, vector<pair<int, double>>> Inner_dics);
	void Find_dis(int m, int n);
	void Get_merge(int m, string str1);
	void Dijkstra(int begin, int end);
	void Print_Path(int, int);
};

bool cmp(pair<pair<int, int>, double >& a, pair<pair<int, int>, double>& b)
{
	return a.second > b.second;
}

Graph::Graph(int x = 0)
{
	number = x;
}

void Graph::Input_random_Graph(int count)
{
	ofstream File_output("Random_Graph.txt", ios_base::trunc);

	Random_Graph(File_output, count);

	cout << "Inputing completed successfully ! " << endl;

	return;
}
void Graph::Add_random_Graph(int count)
{
	ofstream File_output("Random_Graph.txt", std::ios_base::app);

	Random_Graph(File_output, count);

	cout << "Adding completed successfully ! " << endl;

	return;
}
void Graph::Random_Graph(ofstream& File_output, int count)
{
	srand(time(NULL));

	number = number + count;
	int mod = number;

	if (count > 200)
		mod = count / 10;
	else if (count > 50)
		mod = count / 2;
	else
		mod = count;


	for (int i = 0; i < count; i++)
	{
		int num_1 = rand() % mod + 1;
		int num_2 = rand() % mod + 1;
		int num_3 = 0;
		if (count > 100)
			num_3 = (count % 50) + 1;
		else if (count > 10)
			num_3 = (count % 10) + 1;
		else num_3 = 0;

		int num_4 = num_3 * 2 + 1;

		double weight = (double(rand() % 80)) / 4 + 1;
		if (abs(num_1 - num_2) < num_3)
		{
			File_output << "<" << num_1 << ">" << endl;
		}
		else if (abs(num_1 - num_2) > num_3 && abs(num_1 - num_2) < num_4)
		{
			File_output << "<" << num_2 << ' '
				<< num_2 << ' ' << weight << ">" << endl;
		}
		else
		{
			File_output << "<" << num_1 << ' ' << num_2 << ' ' << weight << ">" << endl;
		}
	}

	File_output.close();


	return;
}

// to a list
void Graph::Read_Graph()
{
	cout << "The File Named \"Random_Graph.txt \" Has Been Opened" << endl;
	vector<string> vec;
	string lineStr;
	ifstream inFile("Random_Graph.txt", ios::in);
	while (getline(inFile, lineStr))
	{
		vec.push_back(lineStr);
	}

	//<3 2 4.25>
	for (int i = 0; i < vec.size(); i++)
	{
		//cout << vec[i] << "!" << endl;
		vec[i].erase(vec[i].begin());
		int begin = stod(vec[i]);
		int j = 0;
		for (j = 0; j < vec[i].size(); j++)
		{
			if (!isdigit(vec[i][j]))
				break;
		}
		vec[i].erase(vec[i].begin(), vec[i].begin() + j);
		//cout <<"hh"<< vec[i] << "!" << endl;
		if (vec[i][0] == '>')
		{
			if (Points.count(begin))
				continue;
			Point_dics[begin] = 1;
			Points[begin] = 1;
		}
		else
		{
			//cout << vec[i] << "!" << endl;
			vec[i].erase(vec[i].begin());
			//cout << vec[i] << "!" << endl;
			int end = stod(vec[i]);
			for (j = 0; j < vec[i].size(); j++)
			{
				if (!isdigit(vec[i][j]))
					break;
			}
			vec[i].erase(vec[i].begin(), vec[i].begin() + j + 1);
			//cout << vec[i] << "!" << endl;
			double length = stod(vec[i]);
			Graph_dics[begin].push_back(make_pair(end, length));
			//Graph_dics[end].push_back(make_pair(end, NULL));
			Points[begin] = 1;
			Points[end] = 1;
			Point_dics.erase(begin);
			Point_dics.erase(end);
			//cout << endl << endl;
		}
	}


	return;
}

//function BFS
void Graph::bfs(int number)
{
	string str;
	cout << "In Order to Shorten the Time , Please Input The Graph The Point " << number << " is in" << endl;
	cout << "---- There is One Example : G1 ----" << endl;
	cout << "---- If the Number Represents a Solo_Point , Please Input \"Solo_Points\" ..." << endl;

	cin >> str;
	str = str + ".txt";

	if (str == "Solo_Points.txt")
	{
		vector<string> vec;
		string lineStr;
		ifstream inFile("Solo_Points.txt", ios::in);
		while (getline(inFile, lineStr))
		{
			vec.push_back(lineStr);
		}
		for (int i = 0; i < vec.size(); i++)
		{
			vec[i].erase(vec[i].begin());
			if (stod(vec[i]) == number)
			{
				cout << "It is a Solo_Point , and it Can Get to ";
				cout << number << endl;
				return;
			}
		}
		cout << "Oops! The Number is Not Cntained in the Solo_Graph ..." << endl;
		cout << "Please Try Another Number ! " << endl;

		return;
	}

	for (auto i = Graph_dics.begin(); i != Graph_dics.end(); i++)
	{
		visited[i->first] = false;
	}
	My_BFS(str, number);
	int count = 0;

	cout << "\nThe Sequence That " << number << " Can Get to is : \n" << endl;

	for (int i = 0; i < Avail_Points.size(); i++)
	{
		// cout points
		cout << fixed << std::left << setw(5) << Avail_Points[i] << ' ';
		{
			count++;
			if (count % 15 == 0) cout << endl;
		}
	}
	cout << endl;

	return;
}
void Graph::My_BFS(string Graph_Name, int Search_Num)
{
	vector<string> vec;
	string lineStr;
	ifstream inFile(Graph_Name.c_str(), ios::in);
	while (getline(inFile, lineStr))
	{
		vec.push_back(lineStr);
	}
	map<int, vector<pair<int, double>>> Inner_dics;
	int i = 1;
	// inner point
	for (i = 1; i < vec.size() && vec[i][0] != '-'; i++)
	{
		if (vec[i].size() == 0)
			continue;
		vec[i].erase(vec[i].begin());
		int begin = stod(vec[i]);
		int j = 0;
		for (j = 0; j < vec[i].size(); j++)
		{
			if (!isdigit(vec[i][j]))
				break;
		}
		vec[i].erase(vec[i].begin(), vec[i].begin() + j);
		vec[i].erase(vec[i].begin());
		int end = stod(vec[i]);
		for (j = 0; j < vec[i].size(); j++)
		{
			if (!isdigit(vec[i][j]))
				break;
		}
		vec[i].erase(vec[i].begin(), vec[i].begin() + j + 1);
		double length = stod(vec[i]);
		Inner_dics[begin].push_back(make_pair(end, length));
	}

	//for (auto i = Inner_dics.begin(); i != Inner_dics.end(); i++)
	//{
	//	cout << i->first << endl;
	//	for (int j = 0; j < i->second.size(); j++)
	//		cout << i->second[j].first << ' ';
	//	cout << endl;
	//}


	vector<int> pre = Private_bfs(Search_Num, Inner_dics);

	//for (int i = 0; i < pre.size(); i++)
	//	cout << pre[i] << ' ';
	//cout << endl;

	i = i + 1;

	if (pre.size() == 0)
	{
		pre.push_back(Search_Num);
		if (visited[Search_Num] == false)
		{
			Avail_Points.push_back(Search_Num);
			visited[Search_Num] = true;
		}
	}

	//cout << vec[i] << endl;

	for (i; i < vec.size(); i++)
	{
		vec[i].erase(vec[i].begin());
		vector<int>::iterator iter = find(pre.begin(), pre.end(), stod(vec[i]));
		if (iter == pre.end())
		{
			continue;
		}
		int j = 0;
		for (j = 0; j < vec[i].size(); j++)
		{
			if (!isdigit(vec[i][j]))
				break;
		}
		vec[i].erase(vec[i].begin(), vec[i].begin() + j + 2);
		int File_index = stod(vec[i]);
		//cout << File_index << endl;
		for (j = 0; j < vec[i].size(); j++)
		{
			if (!isdigit(vec[i][j]))
				break;
		}
		vec[i].erase(vec[i].begin(), vec[i].begin() + j + 1);
		int Next_Point = stod(vec[i]);
		//cout << Next_Point << endl;
		if (visited[Next_Point])
			continue;
		//cout << "Next Open G" << File_index << endl;
		string new_idx = "G" + to_string(File_index) + ".txt";
		My_BFS(new_idx, Next_Point);
	}

	return;
}
vector<int> Graph::Private_bfs(int number, map<int, vector<pair<int, double>>> Inner_dics)
{
	vector<int> res;
	int Vers = Inner_dics.size();
	int currentNode;
	queue<int> q;
	int count = 0;
	if (!Inner_dics.count(number))
		return vector<int>{};
	q.push(number);
	while (!q.empty())
	{
		currentNode = q.front();
		q.pop();
		if (visited[currentNode] == true)
			continue;
		Avail_Points.push_back(currentNode);
		res.push_back(currentNode);
		visited[currentNode] = true;
		for (auto i = Inner_dics[currentNode].begin(); i != Inner_dics[currentNode].end(); i++)
		{
			if (visited[i->first] == false)
				q.push(i->first);
		}
	}

	return res;
}
void Graph::Cut_Graph(int n)
{
	int AcceptedVers = 0;

	double Sum_Of_Edge = 0;

	if (n == 0)
	{
		cout << "Your Input is Wrong, Please Quit and Try Again ! " << endl;
		return;
	}

	if (n == 1)
	{
		cout << "Each Point is Divided Into One Graph. And it is not Meaningful to Do So ..." << endl
			<< "Please Quit and Try Again ! " << endl;
		return;
	}

	if (!Point_dics.empty())
	{
		ofstream File_output("Solo_Points.txt", ios_base::trunc);
		for (auto i = Point_dics.begin(); i != Point_dics.end(); i++)
		{
			AcceptedVers++;
			Points[i->first] = 2;
			File_output << "<" << i->first << ">" << endl;
		}
		File_output.close();
	}

	for (auto i = Graph_dics.begin(); i != Graph_dics.end(); i++)
	{
		int begin = i->first;
		vector<pair<int, double>> temp = i->second;
		for (int k = 0; k < temp.size(); k++)
		{
			if (temp[k].first == begin)
			{
				Circle.push_back(begin);
				continue;
			}
			if (Easy_Graph_dics.count(make_pair(begin, temp[k].first)))
			{
				Easy_Graph_dics[make_pair(begin, temp[k].first)] += temp[k].second;
			}
			else if (Easy_Graph_dics.count(make_pair(temp[k].first, begin)))
			{
				Easy_Graph_dics[make_pair(temp[k].first, begin)] += temp[k].second;
			}
			else
			{
				Easy_Graph_dics[make_pair(begin, temp[k].first)] = temp[k].second;
			}
		}
	}

	//cout << "test ! " << endl;
	//for (auto i = Easy_Graph_dics.begin(); i != Easy_Graph_dics.end(); i++)
	//{
	//	cout << i->first.first << ' ' << i->first.second << ' ' << i->second << endl;
	//}
	cout << "Program Processing , Please Wait ... " << endl << endl;


	Sort_Graph.assign(Easy_Graph_dics.begin(), Easy_Graph_dics.end());
	sort(Sort_Graph.begin(), Sort_Graph.end(), cmp);

	//for (auto i = Sort_Graph.begin(); i != Sort_Graph.end(); i++)
	//{
	//	cout << i->first.first << ' ' << i->first.second << ' ' << i->second << endl;
	//}

	cout << "Answer : " << endl << endl;


	for (int i = 0; i < Sort_Graph.size(); i++)
	{
		int begin = Sort_Graph[i].first.first;
		int end = Sort_Graph[i].first.second;
		//cout << "Examine : " << begin << ' ' << end << endl;
		bool Contained1 = false;
		bool Contained2 = false;
		int j = 0;
		set<int>::iterator find1; set<int>::iterator find2;
		int pos1 = -1, pos2 = -1;

		for (j = 0; j < CutGraph.size(); j++)
		{
			find1 = CutGraph[j].find(begin);
			find2 = CutGraph[j].find(end);
			if (find1 != CutGraph[j].end())
			{
				Contained1 = true;
				pos1 = j;
			}
			if (find2 != CutGraph[j].end())
			{
				Contained2 = true;
				pos2 = j;
			}
		}
		if (Contained1 == false && Contained2 == false)
		{
			//cout << "--case1--" << endl;
			set<int> temp;
			//cout << begin << '-' << end << endl;
			temp.insert(begin); temp.insert(end);
			Points[begin] = 2;
			Points[end] = 2;
			CutGraph.push_back(temp);
			AcceptedVers += 2;
		}
		else if (Contained1 && Contained2)
		{
			//cout << "--case2--" << endl;
			if (CutGraph[pos1].size() + CutGraph[pos2].size() < n + 1)
			{
				if (pos1 != pos2)
				{
					CutGraph[pos1].insert(CutGraph[pos2].begin(), CutGraph[pos2].end());
					CutGraph.erase(CutGraph.begin() + pos2);
				}
			}
			else if (CutGraph[pos1].size() + CutGraph[pos2].size() > n)
			{
				if (pos1 != pos2)
				{
					//cout << "--case2--sum" << endl;
					Sum_Of_Edge = Sum_Of_Edge + Sort_Graph[i].second;
				}
				continue;
			}
		}
		else if (Contained1 && !Contained2)
		{
			//cout << "--case3--" << endl;
			if (CutGraph[pos1].size() + 1 < n + 1)
			{
				CutGraph[pos1].insert(end);
				Points[end] = 2;
				//cout << '-' <<end<<'-' << endl;
				AcceptedVers++;
			}
			else
			{
				//cout << "--case3--sum" << endl;
				Sum_Of_Edge = Sum_Of_Edge + Sort_Graph[i].second;
				//if (i == n - 1)
				//{
				//	set<int> temp;
				//	temp.insert(end);
				//	Points[end] = 2;
				//	//cout << '-' << end << '-' << endl;
				//	CutGraph.push_back(temp);
				//	AcceptedVers++;
				//}
				continue;
			}
		}
		else if (!Contained1 && Contained2)
		{
			//cout << "--case4-" << endl;
			if (CutGraph[pos2].size() + 1 < n + 1)
			{
				CutGraph[pos2].insert(begin);
				Points[begin] = 2;
				//cout << '-' << begin << '-' << endl;
				AcceptedVers++;
			}
			else
			{
				//cout << "--case4--sum" << endl;
				Sum_Of_Edge = Sum_Of_Edge + Sort_Graph[i].second;
				//if (i == n - 1)
				//{
				//	set<int> temp;
				//	temp.insert(begin);
				//	Points[begin] = 2;
				//	//cout << '-' << begin << '-' << endl;
				//	CutGraph.push_back(temp);
				//	AcceptedVers++;
				//}
				continue;
			}
		}
	}

	//cout << "Solo Ones" << endl;
	for (auto i = Points.begin(); i != Points.end(); i++)
	{
		if (i->second == 1)
		{
			set<int> temp;
			temp.insert(i->first);
			Points[i->first] = 2;
			//cout << '-' << i->first << '-' << endl;
			CutGraph.push_back(temp);
			AcceptedVers++;
		}
	}


	//cout << "AcceptedVers : " << AcceptedVers << endl;

	cout << "These Solo_Points Have Been Put Into Solo_Points.txt : " << endl << endl;
	for (auto i = Point_dics.begin(); i != Point_dics.end(); i++)
	{
		cout << i->first << ' ';
	}
	cout << endl << endl;


	cout << "These Points Have Been Put Into One Devided Graph : " << endl << endl;
	for (int i = 0; i < CutGraph.size(); i++)
	{
		cout << "G" << i << " : ";
		for (set<int>::iterator it = CutGraph[i].begin(); it != CutGraph[i].end(); ++it)
		{
			cout << *it << " ";
		}
		cout << endl << endl;
	}

	cout << "We Randomly Generated " << Points.size() << " Points." << endl;
	cout << "And The Algorithm Have Cut " << AcceptedVers << " Points" << endl;

	cout << "And The Least Sum_Of_Edge Calculated By This Type Of Greedy Algorithm is : ";
	cout.setf(ios::fixed, ios::floatfield);
	cout<< Sum_Of_Edge << endl;

	//go cutting
	//map<int, vector<pair<int, double>>> Graph_dics;
	//vector<set<int>> CutGraph;
	for (int i = 0; i < CutGraph.size(); i++)//Ã¿¸ö×ÓÍ¼
	{
		string Inner = "", Interacting = "";
		string str = "G" + to_string(i) + ".txt";
		ofstream File_output;
		File_output.open(str.c_str(), ios_base::trunc);
		for (set<int>::iterator it = CutGraph[i].begin(); it != CutGraph[i].end(); ++it)
		{
			int index = *it;
			vector<pair<int, double>> temp = Graph_dics[index];
			for (int j = 0; j < temp.size(); j++)
			{
				if (CutGraph[i].find(temp[j].first) != CutGraph[i].end())
				{
					Inner = Inner + "<" + to_string(*it) + " " + to_string(temp[j].first) + " " + to_string(temp[j].second) + ">\n";
				}
				else
				{
					for (int k = 0; k < CutGraph.size(); k++)
					{
						if (k == i)
							continue;
						if (CutGraph[k].find(temp[j].first) != CutGraph[k].end())
						{
							Interacting = Interacting + "<" + to_string(*it) + " G" + to_string(k) + ":" + to_string(temp[j].first) + " " + to_string(temp[j].second) + ">\n";
						}
					}
				}
			}
		}
		File_output << "--Inner Lines-- : " << endl;
		File_output << Inner;
		//cout << Inner;
		File_output << "\n--Interacting Lines-- :  " << endl;
		File_output << Interacting;
		//cout << Interacting;
		File_output.close();
	}

	cout << endl;
	return;
}

void Graph::Find_dis(int begin, int end)
{
	string str1, str2;
	cout << "\nIn Order to Shorten the Time , Please Input The Graph The Point " << begin << " is in" << endl;
	cout << "---- There is One Example : G1 ----" << endl;
	cout << "If the Number Represents a Solo_Point , Please Input \"Solo_Points\" ..." << endl;
	cin >> str1;
	cout << "\nIn Order to Shorten the Time , Please Input The Graph The Point " << end << " is in" << endl;
	cout << "---- There is One Example : G1 ----" << endl;
	cout << "If the Number Represents a Solo_Point , Please Input \"Solo_Points\" ..." << endl;
	cin >> str2;
	if (str1 == "Solo_Points" || str2 == "Solo_Points")
	{
		cout << "Oops ! The Two Numbers Don't Connet With Each Other ... " << endl;
		cout << "Please Try Again ! " << endl;
		return;
	}


	cout << "\nLet's Firstly Try Whether These Two Points Connet With Each Other ..." << endl;
	cout << "Let's Check Whether " << end << " is in the Sequence that " << begin << " Can Get to ..." << endl;

	bfs(begin);

	if (find(Avail_Points.begin(), Avail_Points.end(), end) == Avail_Points.end())
	{
		cout << "Oops ! " << end << " is Not in the Sequence that " << begin << " Can Get to ..." << endl;
		cout << "The Two Numbers Don't Connet With Each Other ... " << endl;
		cout << "Please Try Again ! " << endl;
		return;
	}

	Get_merge(end, str1 + ".txt");

	//for (auto i = Merge_dics.begin(); i != Merge_dics.end(); i++)
	//{
	//	cout << i->first << " : " << endl;
	//	for (int j = 0; j < i->second.size(); j++)
	//	{
	//		cout << i->second[j].first << ' ' << i->second[j].second << endl;
	//	}
	//	cout << endl;
	//}

	Dijkstra(begin, end);

	return;
}
void Graph::Get_merge(int end, string str1)
{
	Dis_visited[str1] = true;
	vector<string> vec;
	vector<int> temp;
	string lineStr;
	ifstream inFile(str1.c_str(), ios::in);
	while (getline(inFile, lineStr))
	{
		vec.push_back(lineStr);
		//cout << lineStr << endl;
	}
	int i = 1;

	for (i = 1; i < vec.size() && vec[i][0] != '-'; i++)
	{
		if (vec[i].size() == 0)
			continue;
		vec[i].erase(vec[i].begin());
		//cout << vec[i] << endl;
		int my_begin = stod(vec[i]);
		int j = 0;
		for (j = 0; j < vec[i].size(); j++)
		{
			if (!isdigit(vec[i][j]))
				break;
		}
		vec[i].erase(vec[i].begin(), vec[i].begin() + j);
		vec[i].erase(vec[i].begin());
		int my_end = stod(vec[i]);
		for (j = 0; j < vec[i].size(); j++)
		{
			if (!isdigit(vec[i][j]))
				break;
		}
		vec[i].erase(vec[i].begin(), vec[i].begin() + j + 1);
		double length = stod(vec[i]);
		//if (length == 0)
		//	cout << "------------------------" << endl;
		Merge_dics[my_begin].push_back(pair<int,double>(my_end, length));
		Merge_Points[my_begin] = 1;
		Merge_Points[my_end] = 1;
		//temp.push_back(my_begin); temp.push_back(my_end);
	}
	//if (find(temp.begin(), temp.end(), end) != temp.end())
	//	return;


	i = i + 1;
	//cout << vec[i] << endl;
	for (i; i < vec.size(); i++)
	{
		if (vec[i].size() == 0)
			break;
		vec[i].erase(vec[i].begin());
		int j = 0;
		int my_Begin = stod(vec[i]);
		for (j = 0; j < vec[i].size(); j++)
		{
			if (!isdigit(vec[i][j]))
				break;
		}
		vec[i].erase(vec[i].begin(), vec[i].begin() + j + 2);
		int File_index = stod(vec[i]);
		//cout << File_index << endl;
		for (j = 0; j < vec[i].size(); j++)
		{
			if (!isdigit(vec[i][j]))
				break;
		}
		vec[i].erase(vec[i].begin(), vec[i].begin() + j + 1);
		int Next_Point = stod(vec[i]);
		//cout << Next_Point << endl;
		for (j = 0; j < vec[i].size(); j++)
		{
			if (!isdigit(vec[i][j]))
				break;
		}
		//cout << vec[i] << endl;
		vec[i].erase(vec[i].begin(), vec[i].begin() + j + 1);
		double my_Length = stod(vec[i]);
		//cout << "my_Length "<<my_Length << endl;
		//if (my_Length == 0)
		//cout << my_End << endl;
		Merge_dics[my_Begin].push_back(pair<int,double>(Next_Point, my_Length));
		Merge_Points[my_Begin] = 1;
		Merge_Points[Next_Point] = 1;
		string new_idx = "G" + to_string(File_index) + ".txt";
		if (!Dis_visited.count(new_idx))
		{
			//cout << "Next Open G" << File_index << endl;
			Get_merge(end, new_idx);
		}
	}

	return;
}

void Graph::Dijkstra(int begin, int end)
{
	//cout << begin <<" "<< end << endl; 

	double u = 0, i = 0, j = 0, min = INT_MAX;


	for (auto k = Merge_Points.begin(); k != Merge_Points.end(); k++)
	{
		known[k->first] = false;
		distance[k->first] = INT_MAX;
	}

	distance[begin] = 0;

	for (i = 0; i < Merge_Points.size(); ++i)
	{
		min = INT_MAX;
		for (auto j = Merge_Points.begin(); j != Merge_Points.end(); j++)
		{
			if (!known[j->first] && (distance[j->first] < min))
			{
				min = distance[j->first];
				u = j->first;
			}
		}
		known[u] = true;
		for (auto p = Merge_dics[u].begin(); p != Merge_dics[u].end(); p++)
		{
			if (!known[p->first] && distance[p->first] > (min + p->second))
			{
				distance[p->first] = min + p->second;
				prev[p->first] = u;
			}
		}
	}

	//for (auto i = distance.begin(); i != distance.end(); i++)
	//{
	//	cout << i->first << ' ' << i->second << endl;
	//}

	cout << endl;
	cout << "The Distance Between " << begin << " and " << end << " is : "
		<< fixed << setprecision(4) << distance[end] << endl;

	cout <<"The Shortest Way That "<< begin << " Leads to " << end << " is : " << endl;

	Print_Path(begin, end);
	return;
}
void Graph::Print_Path(int Print_Start, int Print_End)
{
	if (Print_Start == Print_End)
	{
		cout << Print_Start;
		return;
	}
	Print_Path(Print_Start, prev[Print_End]);
	cout << " - " << Print_End;
}

#endif