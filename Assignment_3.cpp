#include<string>
#include<iostream>
#include<sstream>
#include <fstream>
#include<stdio.h>
using namespace std;

class Node
{
public:
	string data;
	Node* next;
	Node* prev;
	Node(string valu)
	{
		data = valu;
		next = NULL;
		prev = NULL;
	}
	Node()
	{
		next = NULL;
		prev = NULL;
	}

};
class LinkedList
{
	int size = 0;
	Node* head = NULL;
	Node* tail = NULL;
	Node* newn = NULL;
	Node* index;
	Node* del;
public:
	void insert(string valu)
	{
		Node* newn = new Node;
		newn->data=valu;
		if (head == NULL && tail == NULL)
		{
			head = newn;
			tail = newn;
			size++;
		}
		else
		{
			tail->next=newn;
			newn->prev=tail;
			tail = newn;
			size++;
		}
	}
	void print()
	{
		int x = 0;
		index = head;
		while (index->next != NULL)
		{
			x++;
			cout <<x<<"."<< index->data << "\n";
			index = index->next;
		}
	}
};
class node
{
public:
	string Data;
	LinkedList Url;
	node* left;
	node* right;
	node(string S,string U)
	{
		Data = S;
		//cout << S << " " << U << endl;
		Url.insert(U);
		left = NULL;
		right = NULL;
	}
	node()
	{
		left = NULL;
		right = NULL;
    }
};
class Tree
{
	void insertion(node*& root, string S, string U)
	{
		if (root == NULL)
		{
			root = new node(S, U);
		}
		else if (root->Data > S)
		{
			if (root->left != NULL)
			{
				insertion(root->left, S, U);
			}
			else
			{
				root->left = new node (S, U);
			}
		}
		else if (root->Data < S)
		{
			if (root->right != NULL)
			{
				insertion(root->right, S, U);
			}
			else
			{
				root->right = new node (S, U);
			}
		}
	}
	void print(node* root)
	{
		if (root == NULL)
		{
			return;
		}
		print(root->left);

		cout << "Name: " << root->Data << "." << endl;

		print(root->right);
	}
	void makedeletion(node*& root)
	{
		if (root->right == NULL)
		{
			newn = root;
			root = root->left;
			delete newn;
		}
		else if (root->left == NULL)
		{
			newn = root;
			root = root->right;
			delete newn;
		}
		else
		{
			newn = root->right;
			while (newn->left != NULL)
			{
				newn = newn->left;
			}
			newn->left = root->left;
			newn = root;
			root = root->right;
			delete newn;
		}
	}
	void delet(node*& root, string N)
	{
		if (root == NULL)
			return;
		else if (root->Data > N)
			delet(root->left, N);
		else if (root->Data < N)
			delet(root->right, N);
		else
			makedeletion(root);
	}
	void printIn(node* root)
	{
		if (root == NULL)
		{
			return;
		}
		printIn(root->left);

		cout << "Name: " << root->Data << "." << endl;

		printIn(root->right);
	}
	void printPost(node* root)
	{
		if (root == NULL)
		{
			return;
		}
		printPost(root->left);
		printPost(root->right);
		cout << "Name: " << root->Data << "." << endl;

	}
	void printpre(node* root)
	{
		if (root == NULL)
		{
			return;
		}
		cout << "Name: " << root->Data << "." << endl;
		printpre(root->left);
		printpre(root->right);
	}
    public:
	node* Root = NULL;
	node* search(node* root, string key)
	{
		if (root == NULL)
		{
			return NULL;
		}
		if (root->Data == key)
		{
			return root;
		}
		else if (root->Data > key)
		{
			return search(root->left, key);
		}
		else if (root->Data < key)
		{
			return search(root->right, key);
		}

	}
	node* newn = NULL;
	void insert( string S,string U)
	{
		insertion(Root, S, U);
	}
	void display()
	{
		print(Root);
	}
	void remove(string N)
	{
		delet(Root, N);
	}
	void displayInOrder()
	{
		printIn(Root);
	}
	void displayPreOrder()
	{
		printpre(Root);
	}
	void displayPostOrder()
	{
		printPost(Root);
	}

};

void read_file(Tree*& T,const char* name)
{
	fstream read;
	read.open(name, ios::in);
	if (!read)
		cout << "Error opening File:\n";
	else
	{
		int x = 0;
		string url;
		while (!read.eof())
		{
			    string url;
			    getline(read, url);
				string U;
				for (int i = 2; i < url.length();i++)
				{
					U = U + url[i];
				}
			    string S;
				getline(read, S);
				string Array[50];
				int y = 0;
				string NN = S;
				stringstream ss(NN);
				string Ss;
				while (getline(ss, Ss, ' '))
				{
					Array[y] = Ss;
					y++;
				}
				for (int i = 0; i < y; i++)
				{
					if (!(T->search(T->Root, Array[i])))
						T->insert(Array[i],U);
					else
					{
						node* tem = T->search(T->Root, Array[i]);
						tem->Url.insert(U);
					}
				}
		}
	}
	cout << "File Loaded Successfully.\n";
}
void searchw(Tree* T)
{
	string a;
	cout << "Entre word to search:\n>";
	cin >> a;
	node* tem = T->search(T->Root, a);
	if (tem)
		tem->Url.print();
	else
		cout << "Word Not Found:\n";
}
int main()
{
	Tree* T;
	T = new Tree;
	string name,word;
	cout << "Entre name of file:\n>";
	cin >> name;
	read_file(T,name.c_str());
	searchw(T);
}