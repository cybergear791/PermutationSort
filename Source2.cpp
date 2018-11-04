//AI Project3
//Created by Nick flouty and Joey Robinson
// Uses A* search to sort an out of order permutation (4 3 2 1 5) to an ordered using pancake flip.

#include <iostream>
#include <string> //for getting users input.
#include <time.h> //for time
#include <stack>
#include <vector>
#include <queue>
#include <algorithm>
#include "BST2.h"
using namespace std;


struct Node
{
	// Node has two fields - key which is a permutation and parent which is an int.
	vector<int> key;
	long int parent;
	double f; //priority	f = g + h
	double g; //g value represents distance from start to current node; int idk = node.gvalue + weight(node, n); Then we would insert into the tree insert(h(n), g(n)), equiv to insert(n.label, idk);
};

vector<int> pancake(vector<int> input, int s, int e)	//swaps the block of code in string		
{
	int tempy;
	while (s < e)
	{
		tempy = input[s];
		input[s] = input[e];
		input[e] = tempy;
		s++;
		e--;
	}
	return input;
}
vector<int> reverse(vector<int> input, int s, int e)	//swaps the block of code in string		
{
	int tempy;
	tempy = input[s];
	input[s] = input[e];
	input[e] = tempy;
	s++;
	e--;
	return input;
}

bool InOrderS(vector<int> temp) 	//returns true if string is in incremental order 1,2,3,4,5
{
	for (int i = 0; i < temp.size() - 1; i++)
	{
		if (temp[i] >= temp[i + 1])
			return false;
	}
	return true;
}


void pushback(vector<int> key, long int parent, vector<Node*> &Pointers)
{
	Node* temp = new Node;
	temp->key = key;
	temp->parent = parent;
	Pointers.push_back(temp);
}
void insert(Node* temp, long int &max, long int &visits, BinarySearchTree<Node*> &Q)
{
	//Q.push(temp);
	visits++;
	long int size = Q.treeSize();
	if (size > max)
		max = size;
	
	Q.insert(temp, temp->key, temp->f);
}

void printOutput(vector<Node*> Pointers, long int indx) {

	// prints out the path in reverse order from goal to start

	//cout << Goal << endl;

	while (indx != -1)
	{
		for (int i = 0; i < Pointers[indx]->key.size(); i++)
			cout << Pointers[indx]->key[i] << " ";
		cout << endl;

		indx = Pointers[indx]->parent;
	}
}
bool should_be_pancake(vector<int> start, int s, int e)
{
	int count = 0;
	while (start[s] - 1 == start[e])
	{
		count++;
		s++;
		e++;
	}
	return (count > 3);
}
bool Reverse_DifByOne(vector<int> start, int a, int b)
{
	int count = 0;
	while (start[a] - 1 == start[b])
	{
		count++;
		a++;
		b--;
	}
	return (count > 0);
}
bool Breakpoints_DifferenceByOne(int a, int b)		//For Breakpoints()
{
	if (a > b)
	{
		a--;
		if (a == b)
			return true;
	}
	else
	{
		b--;
		if (a == b)
			return true;
	}
	return false;
}
int Breakpoints(vector<int> key)
{
	int breakpoints = 0;
	int i = 0;
	while (i < key.size() - 1)
	{
		if (!Breakpoints_DifferenceByOne(key[i], key[i + 1]))
			breakpoints++;
		i++;
	}
	return breakpoints;
}
vector<vector<int>> Possibilities(int n, vector<int> start)
{
	vector<vector<int>> possibilities;
	int i = 0;
	while (i < start.size() - 1)
	{
		int j = i;
		int count = 0;
		while (j + 1 < start.size() && Breakpoints_DifferenceByOne(start[j], start[j + 1]))
		{
			count++;
			j++;
		}

		if (count == 0)
		{
			while (j + 2 < start.size() && start[i] - 1 != start[j + 1])
			{
				j++;
			}
		}
		
		if(count > 0)
		{
			possibilities.push_back(pancake(start, i, j));
			i = j + 1;
		}
		else
		{
			possibilities.push_back(pancake(start, i + 1, j + 1));
			i = j + 2;
		}

	}//end while(i < start.size() - 1)

	return possibilities;
}

void A(vector<int> start, int n, long int &visits, long int &max, long int &expanded)
{
	//vector<Node*> Closed;	//contains nodes that have been expanded or removed from the queue
	vector<Node*> Pointers;

	BinarySearchTree<Node*> Q; //OPEN. contains nodes that have been generated but not expanded. 

	pushback(start, -1, Pointers);		//Step 1: pushback([start, -1]) to Pointers; // -1 signifies that start node has no parent

	double h = (.5) * (Breakpoints(start));		//1/2 * number of breakpoints
	double f = h;			//initialize estimate
	//insert(start, Pointers.size() - 1, Q, visits, max, f, 0);       //Step 2: insert([start, Pointers.size() - 1, f value is h] onto Queue;
	Node* temp = new Node;
	temp->f = f;
	temp->g = 0;
	temp->key = start;
	temp->parent = Pointers.size() - 1;
	insert(temp, max, visits, Q);

	while (!Q.isEmpty())
	{
		Node* currentNode = Q.deleteMin();		//remove u from Open with smallest f
		expanded++;
		//Closed.push_back(currentNode);		// insert u into Closed.

		if (InOrderS(currentNode->key)) {
			cout << "From Goal -> Start" << endl;
			printOutput(Pointers, currentNode->parent);
			return;
		}


		vector<vector<int>> possibilities = Possibilities(n, currentNode->key);		// 'Succ'


		int i = 0;
		while (i < possibilities.size())	// for each v 'pos' in Succ(u) 'currentnode'
		{
			if (Pointers[currentNode->parent]->parent == -1 || possibilities[i] != Pointers[Pointers[currentNode->parent]->parent]->key)
			{
				double h = (.5) * Breakpoints(possibilities[i]);
				int g = currentNode->g + 1;
				double f = h + g;
				/*This was for graph search.
				//insert(possibilities[i], Pointers.size(), Q, visits, max, f, g);				//Expanding node
				//Node* v = remove(Q);
				if (contains(Q, v))		//if v is in Open
					if (currentNode->g < v->g)
					{
						pushback(possibilities[i], currentNode->parent, Pointers);		// parent(v) <- u
						v->f = h + currentNode->g;
						//insert(possibilities[i], Pointers.size(), Q, visits, max, f, v->g);	//changing f value
					}
				else if (is_in(Closed, v))
					if (currentNode->g < v->g)
					{
						pushback(possibilities[i], currentNode->parent, Pointers);		// parent(v) <- u
						f = h + currentNode->g;
						insert(possibilities[i], Pointers.size(), Q, visits, max, f, v->g);	//changing f value and inserting
						Closed.erase(Closed.begin() + index(Closed,v));					// Remove v from Closed
					}
				else
				{
					pushback(possibilities[i], currentNode->parent, Pointers);
					f = h + currentNode->g;
					insert(possibilities[i], Pointers.size(), Q, visits, max, f, v->g);
				} */
				pushback(possibilities[i], currentNode->parent, Pointers);						//parent value should be the index of ITS PARENT in Pointers
				Node* temp = new Node;
				temp->f = f;
				temp->g = g;
				temp->key = possibilities[i];
				temp->parent = Pointers.size() - 1;
				insert(temp, max, visits, Q);
			}
			i++;
		}
	}
}



int main()
{
	string input;
	cout << "Enter a permutation (seperated by commas, no spaces ex.1,2,3): ";
	cin >> input;

	//int size = (input.length() / 2) + 1;

	vector<int> start;
	int i = 0;
	while (i < input.length())
	{
		string temp;
		while (isdigit(input[i]))
		{
			temp += input[i];
			i++;
		}
		start.push_back(atoi(temp.c_str()));
		i++;
	}
	long int visits = 0;
	long int max = 0;
	long int expanded = 0;
	float duration2 = clock();
	A(start, start.size(), visits, max, expanded);			//function call
	duration2 = clock() - duration2; //cpu time. 

	cout << endl << "CPU time: " << duration2 / CLOCKS_PER_SEC << " seconds." << endl;
	cout << "Total number of visited states: " << visits << endl;
	cout << "Max size of queue: " << max << endl;
	cout << "Total number of expanded nodes: " << expanded << endl;


	system("PAUSE");
}

