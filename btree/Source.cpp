#include <iostream>

using namespace std;

// add some string 1
// add some string 2

// add str in master branch
// some hotfix

// add new branch iss53
// add new string in iss53


struct Node
{
	int data;

	Node *right;
	Node *left;
	Node *parent;
};

Node* getFreeNode(Node* parent, int &value)
{
	Node *tmp = new Node;
	tmp->left = tmp->right = nullptr; 
	tmp->data = value;
	tmp->parent = parent;

	return tmp;
}

void insert(Node **head, int &value)
{
	if (*head == nullptr)
	{
		*head = getFreeNode(nullptr, value);
		return;
	}

	Node *tmp = *head;
	while (tmp)
	{
		if (value >= tmp->data)
		{
			if (tmp->right)
			{
				tmp = tmp->right;
				continue;
			} 
			else 
			{
				tmp->right = getFreeNode(tmp, value);				
				return;
			}
		}
		else if (value < tmp->data)
		{
			if (tmp->left)
			{
				tmp = tmp->left;
				continue;
			}
			else 
			{
				tmp->left = getFreeNode(tmp, value);
				return;
			}
		}
	}
}


Node *getMinNode(Node *tmp)
{	
	return tmp->left ? getMinNode(tmp->left) : tmp;
}

Node *getMaxNode(Node *tmp)
{
	return tmp->right ? getMaxNode(tmp->right) : tmp;
}

void remove(Node *target)
{
	if (target->left && target->right)
	{
		Node *localMax = getMaxNode(target->left);
		target->data = localMax->data;
		remove(localMax);
		return;
	}
	else if (target->left)
	{
		if (target == target->parent->left)
		{
			target->parent->left = target->left;
		}
		else
		{
			target->parent->right = target->left;
		}
	}
	else if (target->right)
	{		
		if (target == target->parent->right)
		{
			target->parent->right = target->right;
		}
		else
		{
			target->parent->left = target->right;
		}
	}
	else
	{
		if (target == target->parent->left)
		{
			target->parent->left = nullptr;					
		}
		else
		{	
			target->parent->right = nullptr;			
		}
	}
	delete target;
}

void deleteNode(Node *head, int &value)
{
	if (!head)
		return ;
	
	if (value < head->data)
	{
		deleteNode(head->left, value);
	}
	else if (value > head->data)
	{
		deleteNode(head->right, value);
	}
	else if (value == head->data)
	{
		remove(head);
		return;
	}
}

void travers(Node *root)
{
	if (root)
	{
		travers(root->left);
		cout << root->data << ' ';
		travers(root->right);
	}
}

void leftRotate(Node **root)
{
	Node *parent = nullptr;
	Node *a = nullptr;
	Node *b = nullptr;
	Node *c = nullptr;

	a = (*root);
	parent = a->parent;
	b = a->right;

	if (b == nullptr)
	{
		return;
	}
	
	c = b->left;
	b->left = a;
	a->right = c;
	if (c)
	{
		c->parent = a;
	}
	b->parent = parent;

	if (parent)
	{
		if (parent->left == a)
		{
			parent->left = b;
		}
		else
		{
			parent->right = b;
		}
	}
	a->parent = b;
	if (!parent)
	{
		*root = (*root)->parent;
	}	
}

void rigthRotate(Node **root)
{
	Node *parent = nullptr;
	Node *a = nullptr;
	Node *b = nullptr;
	Node *c = nullptr;

	b = (*root);
	parent = b->parent;
	a = b->left;
	if (a == nullptr)
	{
		return;
	}

	c = a->right;
	a->right = b;
	b->left = c;
	if (c)
	{
		c->parent = b;
	}

	a->parent = parent;
	if (parent)
	{
		if (parent->left == b)
		{
			parent->left = a;
		}
		else
		{
			parent->right = a;
		}
	}
	b->parent = a;

	(*root) = (*root)->parent;
}

Node* findNodeByValue(Node *root, int &value)
{	
	while (root)
	{
		if (value < root->data)
		{
			root = root->left;
		}
		else if (value > root->data)
		{
			root = root->right;
		}
		else if (value == root->data)
		{
			return root;
		}
	}
	return nullptr;
}

int main()
{		
	const int n = 9;
	//int ms[n] = { 50, 48, 49, 43, 44, 20, 3, 23, 24, 59, 63, 61, 68, 25 };
	int ms[n] = { 50, 30, 60, 25, 35, 55, 70, 75, 65 };

	Node *tree = nullptr;

	for (int i = 0; i < n; ++i)
	{
		insert(&tree, ms[i]);
	}

	

	int value = 60;
	//deleteNode(tree, delValue);

	Node *tmp = findNodeByValue(tree, value);
	if (tmp)
		//rigthRotate(&tmp);
		leftRotate(&tmp);
	
	//travers(tree);
	
	return 0;
}