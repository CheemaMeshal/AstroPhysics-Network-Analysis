//Project done by Meshal Cheema(19I-1977), Mehreen Athar(19I-1712) and Abdullah Faisal(19I-1911)
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include <windows.h>
#include <stdlib.h>
#define Tnodes2 5242
int diameter = 0;
#define K -1
int GRAPH_array[28980][2];
using namespace std;
struct node {

	int data;
	node* next;

	node(int dt)
	{
		data = dt;
		next = NULL;
	}
	node()
	{
	}
	void insert(int dt)
	{
		data = dt;
	}
};
struct list {

	node* head;
	int vertix;
	list()
	{
		head = NULL;
	}
	node* beginaddress() {
		return head;
	}

	node* endaddress() {
		node* temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		return temp;
	}
	void insert(node* ptr)
	{
		if (head == NULL)
		{
			head = new node(0);
			head->data = ptr->data;
			head->next = NULL;
		}
		else
		{
			node* temp = head;

			while (temp->next != NULL)
			{
				temp = temp->next;
			}

			temp->next = new node(0);
			temp->next->data = ptr->data;
			temp->next->next = NULL;
			temp = NULL;
		}
	}

	void display()
	{
		node* temp = head;

		while (temp != NULL)
		{
			cout << temp->data << endl;
			temp = temp->next;
		}
	}

	int top()
	{
		return head->data;
	}
};


struct queue
{
	int numitems;
	node* hd;

	queue()
	{
		hd = NULL;
		numitems = 0;
	}

	~queue()
	{

	}

	bool isEmpty()
	{
		if (hd == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int size()
	{
		return numitems;
	}

	int front()
	{
		bool check = isEmpty();

		if (check == 1)
		{
			cout << "Error! Queue empty." << endl;
			return -1;
		}
		else
		{
			return hd->data;
		}
	}

	void enqueue(int dt)
	{
		if (hd == NULL)
		{
			hd = new node(0);
			hd->next = NULL;
			hd->data = dt;
			numitems = numitems + 1;
		}
		else
		{
			node* tempnode = hd;
			while (tempnode->next != NULL)
			{
				tempnode = tempnode->next;
			}

			tempnode->next = new node(0);
			tempnode = tempnode->next;
			tempnode->next = NULL;
			tempnode->data = dt;
			numitems = numitems + 1;
		}
	}

	void dequeue()
	{
		node* nw = hd->next;
		delete hd;
		hd = nw;
	}
};


struct UGraph {

	list* ptr;
	int size_of_nodes = 0;
	int size;
	int size_of_art_nodes = 0;
	//int size=0;
	node* Src = NULL;
	node* Des = NULL;
	UGraph(int s)
	{
		//size_no_nodes = size -10;
		ptr = new list[s];
		size_of_nodes = s - 1;
		size = s;
		size_of_art_nodes = s- 1;
		for (int i = 0; i < s; i++)
		{
			ptr[i].head = new node(0);
			ptr[i].head->data = -1;
			ptr[i].head->next = NULL;
		}
	}

	void include(int src, int dest)
	{
		if (ptr[0].top() == -1)
		{
			ptr[0].head->data = src;
			ptr[0].head->next = new node(0);
			ptr[0].head->next->data = dest;

			ptr[1].head->data = dest;
			ptr[1].head->next = new node(0);
			ptr[1].head->next->data = src;
		}

		else
		{
			int i = 0;
			int c1 = -1;
			int c2 = -1;
			int tmp = ptr[i].head->data;

			while (tmp != -1)
			{
				if (tmp == src)
				{
					c1 = i;
				}

				if (tmp == dest)
				{
					c2 = i;
				}

				i = i + 1;
				tmp = ptr[i].head->data;
			}

			if (c1 == -1)
			{
				ptr[i].head = new node(0);
				ptr[i].head->data = src;
				ptr[i].head->next = new node(0);
				ptr[i].head->next->data = dest;
			}

			if (c1 != -1 && c2 == -1)
			{
				ptr[i].head = new node(0);
				ptr[i].head->data = dest;
				ptr[i].head->next = new node(0);
				ptr[i].head->next->data = src;
			}

			if (c1 == -1 && c2 == -1)
			{
				ptr[i + 1].head = new node(0);
				ptr[i + 1].head->data = dest;
				ptr[i + 1].head->next = new node(0);
				ptr[i + 1].head->next->data = src;
			}

			if (c1 != -1)
			{
				int check = 0;

				node* ppt = ptr[c1].head;

				while (ppt->next != NULL)
				{
					if (ppt->data == dest)
					{
						check = 1;
					}

					ppt = ppt->next;
				}

				if (check == 1)
				{
					// Node already exists
				}
				else
				{
					ppt->next = new node(0);
					ppt->next->data = dest;
				}
			}


			if (c2 != -1)
			{
				int check = 0;

				node* ppt = ptr[c2].head;

				while (ppt->next != NULL)
				{
					if (ppt->data == src)
					{
						check = 1;
					}

					ppt = ppt->next;
				}

				if (check == 1)
				{
					// Node already exists
				}
				else
				{
					ppt->next = new node(0);
					ppt->next->data = src;
				}
			}
		}
	}
	void create_ver(int val)
	{
		int i = 0;
		while (i < size_of_nodes) {

			if (ptr[i].head == NULL) {
				ptr[i].head = new node;
				ptr[i].head->data = val;
				ptr[i].head->next = NULL;
				return;
			}
			i++;
		}
	}



	void  Find_Art_nodes(int i, bool  Visited[], int disjoint[], int  arrayC[], int arrayP[], bool art_node[])
	{
		static int x = 0;
		int childss = 0;
		Visited[i] = true;
		disjoint[i] = arrayC[i] = x++;
		node* M;
		M = ptr[i].beginaddress();

		while (M != ptr[i].endaddress()->next)
		{

			int y = M->data;
			if (!Visited[y])
			{
				childss++;
				arrayP[y] = i;
				Find_Art_nodes(y, Visited, disjoint, arrayC, arrayP, art_node);
				arrayC[i] = min(arrayC[i], arrayC[y]);
				if (arrayP[i] == K && childss > 1)
				{
					art_node[i] = true;
				}
				if (arrayP[i] != K && arrayC[y] >= disjoint[i])
				{
					art_node[i] = true;
				}
			}
			else if (y != arrayP[i])
			{
				arrayC[i] = min(arrayC[i], disjoint[y]);
			}
			M = M->next;
		}
	}
	void Articulation_func()
	{
		int* arrayP = new int[size_of_nodes];
		int* arrayC = new int[size_of_nodes];
		bool* art_node = new bool[size_of_nodes];
		bool* Visited = new bool[size_of_nodes];
		int* disjoint = new int[size_of_nodes];
		int i = 0;
		while (i < size_of_art_nodes)
		{
			arrayP[i] = K;
			Visited[i] = false;
			art_node[i] = false;
			i++;
		}
		i = 0;
		while (i < size_of_art_nodes)
		{
			if (Visited[i] == false)
			{
				Find_Art_nodes(i, Visited, disjoint, arrayC, arrayP, art_node);
			}
			i++;
		}
		i = 0;
		while (i < size_of_art_nodes)
		{
			if (art_node[i] == true)
			{
				cout << i << " ";
			}
			i++;
		}

	}
	void display()
	{
		int i = 0;
		int tmp = ptr[i].head->data;

		while (tmp != -1)
		{
			node* ppt = ptr[i].head;

			while (ppt != NULL)
			{
				if (ppt->next == NULL)
				{
					cout << ppt->data;
					ppt = ppt->next;
				}
				else
				{
					cout << ppt->data << " -> ";
					ppt = ppt->next;
				}
			}

			cout << endl;

			i = i + 1;
			tmp = ptr[i].head->data;
		}
	}


	int* BFS(int dt)
	{
		int* visited = new int(size);

		for (int k = 0; k < size; k++)
		{
			visited[k] = -1;
		}

		int z = 0;
		int temp = 0;
		int check = 0;
		int index = 0;

		queue qtr;

		qtr.enqueue(dt);

		while (qtr.isEmpty() != true)
		{
			z = 0;

			temp = qtr.front();

			//Finding node in graph
			for (int i = 0; ptr[i].head->data != -1; i++)
			{
				if (ptr[i].head->data == temp)
				{
					z = i;
				}
			}

			node* tmp = ptr[z].head->next;

			//Checking neighbor in array otherwise adding in queue
			while (tmp != NULL)
			{
				check = 0;
				int trr = tmp->data;

				//Checking if neighbor already in visited
				for (int m = 0; visited[m] != -1; m++)
				{
					if (visited[m] == trr)
					{
						check = 1;
					}
				}

				if (check == 1)
				{

				}
				else
				{
					qtr.enqueue(trr);
				}
				tmp = tmp->next;
			}

			visited[index] = temp;
			index = index + 1;
			qtr.dequeue();
		}

		cout << endl << endl << "Data in returning array of visited" << endl;

		for (int a = 0; visited[a] != -1; a++)
		{
			cout << visited[a] << endl;
		}

		return visited;
	}


	int** Out()
	{
		int** dptr = new int* [size];

		for (int i = 0; i < size; i++)
		{
			dptr[i] = new int[size];
		}

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				dptr[i][j] = -1;
			}
		}

		for (int i = 0; ptr[i].head->data != -1; i++)
		{
			dptr[i] = BFS(ptr[i].head->data);
		}

		return dptr;
	}

	int* search(int dt)
	{
		int* visited = new int(size);
		int index = 0;
		int** dptr = Out();

		for (int i = 0; dptr[i][0] != -1; i++)
		{
			if (dptr[i][0] == dt)
			{

			}
			else
			{
				for (int j = 0; dptr[i][j] != -1; j++)
				{
					if (dptr[i][j] == dt)
					{
						visited[index] = dptr[i][0];
						index = index + 1;
					}
				}
			}
		}
		return visited;
	}

	int** In()
	{
		int** dptr = new int* [size];

		for (int i = 0; i < size; i++)
		{
			dptr[i] = new int[size];
		}

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				dptr[i][j] = -1;
			}
		}

		for (int i = 0; ptr[i].head->data != -1; i++)
		{
			dptr[i] = search(ptr[i].head->data);
		}

		return dptr;
	}

	void WCC()
	{
		int** dptr = Out();
		int** pptr = In();

		int** WCC = new int* [size];

		for (int i = 0; i < size; i++)
		{
			WCC[i] = new int[size];
		}

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				WCC[i][j] = -1;
			}
		}

		int index = 0;

		for (int i = 0; dptr[i][0] != -1; i++)
		{
			WCC[i][0] = dptr[i][0];
			index = 1;

			for (int j = 1; dptr[i][j] != -1; j++)
			{
				for (int k = 1; pptr[i][k] != -1; k++)
				{
					if (dptr[i][j] == pptr[i][k])
					{
						WCC[i][index] = dptr[i][j];
					}
				}
			}

			int max = 0;
			int count = 0;
			int ind = 0;

			for (int p = 0; WCC[p][0] != -1; p++)
			{
				count = 0;
				for (int a = 0; WCC[p][a] != -1; a++)
				{
					count++;
				}

				if (count > max)
				{
					max = count;
					ind = p;
				}
			}

			cout << "The largest WCC in the graph has the size: " << max << endl;


			int num = 0;

			cout << "Size distribution of WCC's: " << endl;

			cout << "Size        Number of WCC's" << endl;

			for (int q = 1; q < max; q++)
			{
				num = 0;

				for (int p = 0; WCC[p][0] != -1; p++)
				{
					count = 0;
					for (int a = 0; WCC[p][a] != -1; a++)
					{
						count++;
					}

					if (count == q)
					{
						num++;
					}
				}

				cout << q << "       " << num << endl;
			}
		}
	}

};

struct DGraph {
	int countsink = 0;
	int countisolate = 0;
	int countsources = 0;

	list* ptr;
	int V = 5242;
	int size;
	DGraph(int s)
	{
		ptr = new list[s];
		size = s;
		for (int i = 0; i < s; i++)
		{
			ptr[i].head = new node(0);
			ptr[i].head->data = -1;
			ptr[i].head->next = NULL;
		}
	}
	void include(int src, int dest)
	{

		if (ptr[0].top() == -1)
		{
			ptr[0].head->data = src;
			ptr[0].head->next = new node(0);
			ptr[0].head->next->data = dest;

		}
		if (ptr[0].top() == -2)
		{
			ptr[0].head->data = src;
			ptr[0].head->next = new node(0);
			ptr[0].head->next->data = dest;
			countisolate++;
			countsources++;
		}

		else
		{
			int i = 0;
			int c1 = -1;
			int tmp = ptr[i].head->data;

			while (tmp != -1)
			{
				if (tmp == src)
				{
					c1 = i;
				}

				i = i + 1;
				tmp = ptr[i].head->data;

			}

			if (c1 == -1)
			{
				ptr[i].head = new node(0);
				ptr[i].head->data = src;
				ptr[i].head->next = new node(0);
				ptr[i].head->next->data = dest;
			}

			if (c1 != -1)
			{
				int check = 0;

				node* ppt = ptr[c1].head;

				while (ppt->next != NULL)
				{
					if (ppt->data == dest)
					{

						check = 1;
					}

					ppt = ppt->next;
				}

				if (check == 1)
				{

					// Node already exists
				}
				else
				{
					ppt->next = new node(0);
					ppt->next->data = dest;

				}


			}
		}
	}
	void Include(int src, int dest)
	{
		//ptr[src].insert(dest);
		//ptr[dest].insert(src);
	}
	void display()
	{
		int i = 0;
		int tmp = ptr[i].head->data;

		while (tmp != -1)
		{
			node* ppt = ptr[i].head;

			while (ppt != NULL)
			{
				if (ppt->next == NULL)
				{
					cout << ppt->data;
					ppt = ppt->next;
					//count++;
				}
				else
				{
					cout << ppt->data << " -> ";
					ppt = ppt->next;
				}
			}

			cout << endl;

			i = i + 1;
			tmp = ptr[i].head->data;
		}
	}
	int countNumofSink()
	{
		int i = 0;
		int tmp = ptr[i].head->data;
		while (tmp != -1)
		{
			node* ppt = ptr[i].head;

			while (ppt != NULL)
			{
				if (ppt->next == NULL)
				{

					ppt = ppt->next;

				}
				else
				{

					ppt = ppt->next;
				}
			}
			i = i + 1;
			tmp = ptr[i].head->data;

			if (ptr[i].head->data == NULL)
			{
				countsink++;
			}
		}

		return countsink;

	}
	void countNumofIsolates()
	{
		cout << countisolate << endl;
	}
	void countNumofsources()
	{
		cout << countsources << endl;
	}
	int Caluclate_distance(int distance_array[], bool flagset[])
	{
		int minimum = INT_MAX, indexno;
		int i = 0;

		while (i < Tnodes2)
		{
			if (flagset[i] == false && distance_array[i] <= minimum)
			{
				minimum = distance_array[i],
					indexno = i;
			}
			i++;
		}
		return indexno;
	}
	int Caluclate_max_distance(int distance_array[], bool flagset[])
	{
		int minimum = INT_MAX, indexno;
		int i = 0;

		while (i < Tnodes2)
		{
			if (flagset[i] == false && distance_array[i] <= minimum)
			{
				minimum = distance_array[i],
					indexno = i;
			}
			i++;
		}
		return indexno;
	}
	void FindMinDistance(int distance_array[])
	{
		int first_source = 0;
		int max_dist = distance_array[1];
		int min_dist = distance_array[1];
		int i = 1;
		while (i < Tnodes2)
		{
			if (min_dist > distance_array[i]) {
				min_dist = distance_array[i];
			}i++;
		}
		while (i < Tnodes2)
		{
			if (max_dist < distance_array[i]) {
				max_dist = distance_array[i];
			}i++;
		}
		cout << min_dist << endl;
		diameter = max_dist;
	}
	void FindMaxDistance(int distance_array[])
	{
		int first_source = 0;
		int max_dist = distance_array[1];
		int min_dist = distance_array[1];
		int i = 1;
		while (i < Tnodes2)
		{
			if (max_dist < distance_array[i]) {
				max_dist = distance_array[i];
			}i++;
		}

		cout << max_dist << endl;
	}
	void dijkstrafor_shortestPath(int first_source)
	{


		int distance_num[Tnodes2];//assigning max distances of nodes
		bool flagset[Tnodes2];
		int shortest[Tnodes2];//storing shortest path
		int min;
		int i = 0;
		while (i < Tnodes2)//iniilaziing distances 
		{
			shortest[0] = -1;
			distance_num[i] = INT_MAX; //it will have the shortest distnce from src to vertex
			flagset[i] = false;//will be set to true if above satisfied
			i++;
		}
		distance_num[first_source] = 0; //first distance is always zero
		i = 0;
		while (i < Tnodes2 - 1)
		{

			min = Caluclate_distance(distance_num, flagset);//finding minimum distance
			flagset[min] = true;
			int y = 0;
			while (y < Tnodes2)
			{
				if (!flagset[y] && GRAPH_array[min][y] && distance_num[min] + GRAPH_array[min][y] < distance_num[y])
				{
					shortest[y] = min;
					distance_num[y] = distance_num[min] + GRAPH_array[min][y];
				}
				y++;
			}
			i++;

		}
		FindMinDistance(distance_num);
	}
	void diameterofGraph(int first_source)
	{
		int distance_num[Tnodes2];//assigning max distances of nodes
		bool flagset[Tnodes2];
		int shortest[Tnodes2];//storing shortest path
		int min;
		int i = 0;
		while (i < Tnodes2)//iniilaziing distances 
		{
			shortest[0] = -1;
			distance_num[i] = INT_MAX; //it will have the shortest distnce from src to vertex
			flagset[i] = false;//will be set to true if above satisfied
			i++;
		}
		distance_num[first_source] = 0; //first distance is always zero
		i = 0;
		while (i < Tnodes2 - 1)
		{

			min = Caluclate_max_distance(distance_num, flagset);//finding minimum distance
			flagset[min] = true;
			int y = 0;
			while (y < Tnodes2)
			{
				if (!flagset[y] && GRAPH_array[min][y] && distance_num[min] + GRAPH_array[min][y] < distance_num[y])
				{
					shortest[y] = min;
					distance_num[y] = distance_num[min] + GRAPH_array[min][y];
				}
				y++;
			}
			i++;

		}
		FindMaxDistance(distance_num);
	}
	void indegree()
	{
		cout << endl << "Node" << "        " << "Indegree" << endl;

		for (int i = 0; ptr[i].head->data != -1; i++)
		{
			int dt = ptr[i].head->data;
			int counter = 0;

			for (int i = 0; ptr[i].head->data != -1; i++)
			{
				if (ptr[i].head->data == dt)
				{

				}
				else
				{
					node* tmp = ptr[i].head;

					while (tmp->next != NULL)
					{
						if (tmp->data == dt)
						{
							counter = counter + 1;
						}

						tmp = tmp->next;
					}

					if (tmp->data == dt)
					{
						counter = counter + 1;
					}
				}
			}
			system("Color 0C");
			if (counter == 0)
			{
				cout << dt << "        " << 0 << endl;
			}
			else
			{
				cout << dt << "        " << counter << endl;
			}
		}
	}
	int Calculate(int dt)
	{
		int counter = 0;

		for (int i = 0; ptr[i].head->data != -1; i++)
		{
			if (ptr[i].head->data == dt)
			{

			}
			else
			{
				node* tmp = ptr[i].head;

				while (tmp->next != NULL)
				{
					if (tmp->data == dt)
					{
						counter = counter + 1;
					}

					tmp = tmp->next;
				}

				if (tmp->data == dt)
				{
					counter = counter + 1;
				}
			}
		}

		if (counter == 0)
		{
			return 0;
		}
		else
		{
			return counter;
		}
	}
	void bridges_In_Graph()
	{
		int counter = 0;

		int i = 0;
		while (ptr[i].head->data != -1)
		{
			int num = Calculate(ptr[i].head->data);

			if (num == 1)
			{
				counter = counter + 1;
			}
			i++;
		}

		cout << counter << endl;
	}
	void outdegree()
	{
		cout << endl << "Node" << "        " << "Outdegree" << endl;

		for (int i = 0; ptr[i].head->data != -1; i++)
		{
			int dt = ptr[i].head->data;
			int counter = -1;

			for (int i = 0; ptr[i].head->data != -1; i++)
			{
				if (ptr[i].head->data == dt)
				{
					counter = i;
					break;
				}
			}

			if (counter == -1)
			{
				cout << dt << "        " << 0 << endl;
			}
			else
			{
				int c2 = 0;

				node* tmp = ptr[counter].head;

				while (tmp->next != NULL)
				{
					c2 = c2 + 1;
					tmp = tmp->next;
				}

				cout << dt << "        " << c2 << endl;
			}
		}
	}


	int* BFS(int dt)
	{
		int* visited = new int(size);

		for (int k = 0; k < size; k++)
		{
			visited[k] = -1;
		}

		int z = 0;
		int temp = 0;
		int check = 0;
		int index = 0;

		queue qtr;

		qtr.enqueue(dt);

		while (qtr.isEmpty() != true)
		{
			z = 0;

			temp = qtr.front();

			//Finding node in graph
			for (int i = 0; ptr[i].head->data != -1; i++)
			{
				if (ptr[i].head->data == temp)
				{
					z = i;
				}
			}

			node* tmp = ptr[z].head->next;

			//Checking neighbor in array otherwise adding in queue
			while (tmp != NULL)
			{
				check = 0;
				int trr = tmp->data;

				//Checking if neighbor already in visited
				for (int m = 0; visited[m] != -1; m++)
				{
					if (visited[m] == trr)
					{
						check = 1;
					}
				}

				if (check == 1)
				{

				}
				else
				{
					qtr.enqueue(trr);
				}
				tmp = tmp->next;
			}

			visited[index] = temp;
			index = index + 1;
			qtr.dequeue();
		}

		cout << endl << endl << "Data in returning array of visited" << endl;

		for (int a = 0; visited[a] != -1; a++)
		{
			cout << visited[a] << endl;
		}

		return visited;
	}


	int** Out()
	{
		int** dptr = new int* [size];

		for (int i = 0; i < size; i++)
		{
			dptr[i] = new int[size];
		}

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				dptr[i][j] = -1;
			}
		}

		for (int i = 0; ptr[i].head->data != -1; i++)
		{
			dptr[i] = BFS(ptr[i].head->data);
		}

		return dptr;
	}

	int* search(int dt)
	{
		int* visited = new int(size);
		int index = 0;
		int** dptr = Out();

		for (int i = 0; dptr[i][0] != -1; i++)
		{
			if (dptr[i][0] == dt)
			{

			}
			else
			{
				for (int j = 0; dptr[i][j] != -1; j++)
				{
					if (dptr[i][j] == dt)
					{
						visited[index] = dptr[i][0];
						index = index + 1;
					}
				}
			}
		}
		return visited;
	}

	int** In()
	{
		int** dptr = new int* [size];

		for (int i = 0; i < size; i++)
		{
			dptr[i] = new int[size];
		}

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				dptr[i][j] = -1;
			}
		}

		for (int i = 0; ptr[i].head->data != -1; i++)
		{
			dptr[i] = search(ptr[i].head->data);
		}

		return dptr;
	}

	void SCC()
	{
		int** dptr = Out();
		int** pptr = In();

		int** SCC = new int* [size];

		for (int i = 0; i < size; i++)
		{
			SCC[i] = new int[size];
		}

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				SCC[i][j] = -1;
			}
		}

		int index = 0;

		for (int i = 0; dptr[i][0] != -1; i++)
		{
			SCC[i][0] = dptr[i][0];
			index = 1;

			for (int j = 1; dptr[i][j] != -1; j++)
			{
				for (int k = 1; pptr[i][k] != -1; k++)
				{
					if (dptr[i][j] == pptr[i][k])
					{
						SCC[i][index] = dptr[i][j];
					}
				}
			}

			int max = 0;
			int count = 0;
			int ind = 0;

			for (int p = 0; SCC[p][0] != -1; p++)
			{
				count = 0;
				for (int a = 0; SCC[p][a] != -1; a++)
				{
					count++;
				}

				if (count > max)
				{
					max = count;
					ind = p;
				}
			}

			cout << "The largest SCC in the graph has the size: " << max << endl;


			int num = 0;

			cout << "Size distribution of SCC's: " << endl;

			cout << "Size        Number of SCC's" << endl;

			for (int q = 1; q < max; q++)
			{
				num = 0;

				for (int p = 0; SCC[p][0] != -1; p++)
				{
					count = 0;
					for (int a = 0; SCC[p][a] != -1; a++)
					{
						count++;
					}

					if (count == q)
					{
						num++;
					}
				}

				cout << q << "       " << num << endl;
			}
		}
	}
};

string* Parser(char delimeter, string& line)//&passes the aadress of string line *returns us an array without giving size
{
	//cout << "hello" << endl;
	string token;
	string* array_of_tokens = new string[20]; //dynamincally allocating size of 20 strings
	int count = 0;
	int length = line.length(); //calculating total length of the string
	for (int i = 0; i < line.size(); i++) //loop that iterates until end of line
	{
		if (line[i] != delimeter) { //if there aint a , token will store the words separated by a coma
			token += line[i];

		}
		if (line[i] == delimeter)//if a , then storing the word coined above
		{
			array_of_tokens[count] = token; //at first index,then at second index, so on
			token.clear();//clearing so we can store the next word in token
			count++;//incrementing indexes as 1,2,3,4
		}
		array_of_tokens[count] = token;

	}
	return array_of_tokens; //returning our tkenized string,we need not any [], because of a pointer to the function

}//returning toeknized string

int main()
{
	string filename = "CA-GrQc.txt";
	string temp;
	int edges = 0;
	int nodes = 0;
	ifstream fin;
	fin.open(filename);

	if (!fin.is_open())
	{
		cout << "Error! File not found." << endl;
	}
	//Removing top comments while getting number of nodes and edges
	else
	{
		for (int i = 0; i < 2; i++)
		{
			getline(fin, temp);
		}

		for (int i = 0; i < 3; i++)
		{
			getline(fin, temp, ' ');
		}

		nodes = std::stoi(temp);

		//cout << "Nodes: " << nodes << endl;

		getline(fin, temp, ' ');
		getline(fin, temp);

		edges = std::stoi(temp);

		//cout << "Edges: " << edges << endl;

		getline(fin, temp);
	}
	int nds = nodes + 10;
	UGraph tempo(nds);
	UGraph art(nodes + 1);
	DGraph tmp(nds);
	DGraph g(nds);




	// Creating both directed and undirected graph one node at a time
	int fromnode, tonode;
	while (!fin.eof())
	{

		getline(fin, temp, '\t');
		fromnode = std::stoi(temp);

		getline(fin, temp);
		tonode = std::stoi(temp);
		tempo.include(fromnode, tonode);
		tmp.include(fromnode, tonode);
		//art.include(fromnode, tonode);



	}
	fin.close();
	cout << endl << endl;
	cout << setw(69) << "*****DATA STRUCTURES PROJECT******" << endl << endl;
	cout << setw(67) << "<BY ABDULLAH MEHREEN & MESHAL>" << endl << endl;
	int option = -1;
	while (option != 0)
	{
		system("Color 0A");
		cout << "CHOOSE FROM THE FOLLOWING" << endl << endl;
		system("Color 0C"); cout << "1) Display Edges" << endl << endl;
		system("Color 0B"); cout << "2) Display Edges" << endl << endl;
		system("Color 0B"); cout << "3) Show undirected Graph" << endl << endl;
		system("Color 0B"); cout << "4) Show Directed Graph" << endl << endl;
		system("Color 0D"); cout << "5) Display Source Nodes" << endl << endl;
		system("Color 0B"); cout << "6) Display Sink Nodes" << endl << endl;
		system("Color 0D"); cout << "7) Display Isolated Nodes" << endl << endl;
		system("Color 0D"); cout << "8) Display Articulated Nodes" << endl << endl;
		system("Color 0D"); cout << "9) Display Bridge Edges" << endl << endl;
		system("Color 0D"); cout << "10) Display the shortest path length distribution" << endl << endl;
		system("Color 0B"); cout << "11) Daimeter of a graph" << endl << endl;
		system("Color 0B"); cout << "12) Display In-Degree" << endl << endl;
		system("Color 0B"); cout << "13) Display Out-Degree" << endl << endl;
		system("Color 0B"); cout << "14) Display SCC Information" << endl << endl;
		system("Color 0C"); cout << "15) Display WCC Information" << endl << endl;
		system("Color 0D"); cout << "0) Exit " << endl << endl;
		system("Color 0D");
		cout << endl << "Enter Your option : ";
		cin >> option;
		switch (option)
		{
		case 1:
		{cout << setw(35) << "NODES =  " << nodes << endl << endl;; }break;
		case 2:
		{cout << setw(35) << "EDGES =  " << edges << endl << endl; }break;
		case 3:
		{
			cout << setw(35) << "UNDIRECTED GRAPH " << endl;
			tempo.display();
			cout << endl << endl;
		}break;
		case 4:
		{
			cout << setw(35) << "DIRECTED GRAPH" << endl;
			tmp.display();
			cout << endl << endl;
		}break;
		case 5:
		{
			cout << setw(35) << "SOURCE NODES =  ";
			cout << tmp.countNumofSink() << endl;

		}break;
		case 6:
		{
			cout << setw(35) << "SINK NODES =  ";
			cout << tmp.countNumofSink() << endl;

		}break;
		case 7:
		{
			cout << setw(35) << "ISOLATED NODES =  ";
			tmp.countNumofIsolates();

		}break;
		case 8:
		{
			cout << setw(35) << "ARTICULATED NODES =  ";

			ifstream File;
			int  count_no_of_lines = 0;//for total num of lines in a file
			string  line;
			File.open(filename);//opening file
			if (!File)//if file aint
			{
				cout << "File you are trying to excess is not found" << endl;
				exit(1);
			}
			while (getline(File, line))//will calculate no of lines of file
			{
				count_no_of_lines++; //incrementing after counting every line
			}
			File.close();

			string** tokenedDATA = NULL;//pointer to a poiner to a string
			tokenedDATA = new string * [count_no_of_lines]; //indirect assignment for **
			int i = 0, j = 0;
			char delimeter = '	';  //for differentiating on the basis of ,
			File.open(filename);
			while (getline(File, line))
			{

				if (line[0] == '#')  // Skip any comment lines
				{

				}
				else
				{
					tokenedDATA[i] = Parser(delimeter, line);
					i++;

				}

			}
			File.close();
			int GRAPH_array[28980][2];
			for (int i = 0; i < count_no_of_lines - 4; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					GRAPH_array[i][j] = stoi(tokenedDATA[i][j]);
				}

			}
			int max_ver = 5242;
			int temp;
			int sor = 0, dest = 0;
			char ans = 'y';
			UGraph g(max_ver + 1);
			temp = stoi(tokenedDATA[0][0]);
			g.create_ver(stoi(tokenedDATA[0][0]));
			for (int i = 0; i < count_no_of_lines - 4; i++)
			{
				if (temp != stoi(tokenedDATA[i][0]))
				{
					g.create_ver(stoi(tokenedDATA[i][0]));
					temp = stoi(tokenedDATA[i][0]);
				}
			}

			for (int i = 0; i < count_no_of_lines - 4; i++)
			{

				//g.include(GRAPH_array[i][0], GRAPH_array[i][1]);
			}
			// g.show_graph_str();
			g.Articulation_func();
			/* UGraph g1(6);
			 g1.include(1, 4);
			 g1.include(1, 2);
			 g1.include(1, 3);
			 g1.include(4, 2);
			 g1.include(3, 5);

			 g1.Articulation_func();*/
		}break;
		case 9:
		{
			cout << setw(35) << "BRIDGE NODES =  ";
			tmp.bridges_In_Graph();
		}break;
		case 10:
		{
			cout << setw(60) << "Shortest Path Length Distribution =  ";
			ifstream File;
			int  count_no_of_lines = 0;//for total num of lines in a file
			string   line;
			File.open(filename);//opening file
			if (!File)//if file aint
			{
				cout << "File you are trying to excess is not found" << endl;
				exit(1);
			}
			while (getline(File, line))//will calculate no of lines of file
			{
				count_no_of_lines++; //incrementing after counting every line
			}
			File.close();

			string** tokenedDATA = NULL;//pointer to a poiner to a string
			tokenedDATA = new string * [count_no_of_lines]; //indirect assignment for **
			int i = 0, j = 0;
			char delimeter = '	';  //for differentiating on the basis of ,
			File.open(filename);
			while (getline(File, line))
			{

				if (line[0] == '#')  // Skip any comment lines
				{

				}
				else
				{
					tokenedDATA[i] = Parser(delimeter, line);
					i++;

				}

			}
			File.close();

			for (int i = 0; i < count_no_of_lines - 4; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					GRAPH_array[i][j] = stoi(tokenedDATA[i][j]);
				}

			}
			DGraph a(nds);

			for (int i = 0; i < count_no_of_lines - 4; i++)
			{

				a.include(GRAPH_array[i][0], GRAPH_array[i][1]);


			}

			a.dijkstrafor_shortestPath(0);
		}break;
		case 11:
		{
			cout << setw(60) << "Diameter =  ";
			ifstream File;
			int  count_no_of_lines = 0;//for total num of lines in a file
			string  line;
			File.open(filename);//opening file
			if (!File)//if file aint
			{
				cout << "File you are trying to excess is not found" << endl;
				exit(1);
			}
			while (getline(File, line))//will calculate no of lines of file
			{
				count_no_of_lines++; //incrementing after counting every line
			}
			File.close();

			string** tokenedDATA = NULL;//pointer to a poiner to a string
			tokenedDATA = new string * [count_no_of_lines]; //indirect assignment for **
			int i = 0, j = 0;
			char delimeter = '	';  //for differentiating on the basis of ,
			File.open(filename);
			while (getline(File, line))
			{

				if (line[0] == '#')  // Skip any comment lines
				{

				}
				else
				{
					tokenedDATA[i] = Parser(delimeter, line);
					i++;

				}

			}
			File.close();
			//int GRAPH_array[28980][2];
			for (int i = 0; i < count_no_of_lines - 4; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					GRAPH_array[i][j] = stoi(tokenedDATA[i][j]);
				}

			}
			DGraph a(nds);

			for (int i = 0; i < count_no_of_lines - 4; i++)
			{

				a.include(GRAPH_array[i][0], GRAPH_array[i][1]);


			}
			a.diameterofGraph(0);
		}break;
		case 12:
		{
			cout << setw(35) << "INDEGREE =  " << endl;
			tmp.indegree();
		}break;
		case 13:
		{
			cout << setw(35) << "INDEGREE =  " << endl;
			tmp.outdegree();
		}break;
		case 14:
		{
			tmp.SCC();
		}break;
		case 15:
		{
		 tempo.WCC();
		}break;
		case 0: {cout << "THANKS FOR YOUR TIME" << endl; exit(1); }
		default: {cout << "Your Option is Invalid"; }

		}
		system("pause");
		system("cls");
	}
}