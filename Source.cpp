#include <iostream>
#include<queue>
#include<stack>
using namespace std;
struct Node {
	int data;
	Node* left;
	Node* right;
};

class Tree {
public:
	Node* root = NULL;

	Node* newnode(int data) {
		Node* n = new Node();
		n->data = data;
		n->left = NULL;
		n->right = NULL;
		return n;
	}
	Node* Insert(Node* root, int data) {
		if (root == NULL) {
			root = this->newnode(data);
		}
		else if (root->data == data) {
			return 0;
		}
		else if (data <= root->data) {
			root->left = Insert(root->left, data);
		}
		else {
			root->right = Insert(root->right, data);
		}
		return root;
	}
	Node* Min(Node* root) {
		if (root->left != NULL)
			Min(root->left);
		else
			return root;
	}

	Node* Max(Node* root) {
		if (root->right != NULL)
			Max(root->right);
		else
			return root;
	}
	void PreOrder(Node* root) {
		if (root != NULL)
		{
			cout << root->data << " ";
			PreOrder(root->left);
			PreOrder(root->right);
		}
	}

	void InOrder(Node* root) {
		if (root != NULL)
		{
			InOrder(root->left);
			cout << root->data << " ";
			InOrder(root->right);
		}
	}

	void PostOrder(Node* root) {
		if (root != NULL)
		{
			PostOrder(root->left);
			PostOrder(root->right);
			cout << root->data << " ";
		}
	}
	int Height(Node* root)
	{
		if (root == NULL)
			return 0;
		queue<Node*> q;
		q.push(root);
		int hight = 0;
		while (1)
		{
			int NumberOfNode = q.size();
			if (NumberOfNode == 0)
				return hight;
			hight++;
			while (NumberOfNode > 0)
			{
				Node* node = q.front();
				q.pop();
				if (node->left != NULL)
					q.push(node->left);
				if (node->right != NULL)
					q.push(node->right);
				NumberOfNode--;
			}
		}
	}

	Node* search(Node* root, int data) {
		Node* result;
		if (root == NULL)
			result = NULL;
		else if (root->data == data)
			result = root;
		else if (data < root->data)
			result = search(root->left, data);
		else
			result = search(root->right, data);
		return result;
	}
	Node* Predecessor(Node* root, int pre) {
		Node* predecessor;
		if (root == NULL) {
			return 0;
		}
		while (root != NULL) {
			if (root->data == pre) {
				if (root->right)
				{
					predecessor = root->right;
					while (predecessor->left)
					{
						predecessor = predecessor->left;
					}
				}
			}
			else if (root->data < pre) {
				predecessor = root;
				root = root->right;
			}
			else
				return root;
		}
	}
	Node* successor(Node* root, int suc) {				
		Node* current = search(root, suc);
		if (current->right != NULL)
		{
			return Min(current->right);
		}
		else {
			Node* succ = NULL;
			Node* last = root;
			while (last != current)
			{
				if (current->data < last->data)
				{
					succ = last;
					last = last->left;
				}
				else {
					last = last->right;
				}
			}
			return succ;
		}
	}
	
	bool isComplete(Node* root)
	{
		if (root == NULL)
			return true;

		queue<Node*> q;
		q.push(root);
		bool flag = false;

		while (!q.empty())
		{
			Node* temp = q.front();
			q.pop();

			if (temp->left)
			{
				if (flag == true)
					return false;

				q.push(temp->left);
			}
			else
				flag = true;

			if (temp->right)
			{
				if (flag == true)
					return false;

				q.push(temp->right);
			}
			else
				flag = true;
		}
		return true;
	}
};
	int main() {
		Tree t;

		t.root = t.Insert(t.root, 6);
		t.root = t.Insert(t.root, 2);
		t.root = t.Insert(t.root, 7);
		t.root = t.Insert(t.root, 1);
		t.root = t.Insert(t.root, 9);
		t.root = t.Insert(t.root, 3);

		t.InOrder(t.root);
		cout << endl;

		cout << "Height is: " << t.Height(t.root) << endl;
		Node* min = t.Min(t.root);
		cout << "Min : " << min->data << endl;
		Node* max = t.Max(t.root);
		cout << "Max : " << max->data << endl;

		if (t.isComplete(t.root) == true)
			cout << "Given binary tree is a Complete Binary Tree";
		else
			cout << "Given binary tree is not a Complete Binary Tree";

		cout << endl;
		Node* predecessor = t.Predecessor(t.root, 2);
		cout << "Predecessor " << predecessor->data << endl;

		Node* successor = t.successor(t.root, 1);
		cout << "Successor " << successor->data << endl;

		return 0;
	}