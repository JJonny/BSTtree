#include <iostream>

using namespace std;

// add some string 1

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
	while (tmp->right)
	{
		tmp = tmp->right;
	}

	return tmp;
}

Node *getMaxNode(Node *tmp)
{
	while (tmp->right)
	{
		tmp = tmp->right;
	}

	return tmp;
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
	if (head == nullptr)
	{
		return;
	}
		
	while (head)
	{
		if (value == head->data)		
		{
			remove(head);
			return;
		}
		else if (value > head->data)
		{
			head = head->right;
		}
		else if (value < head->data)
		{
			head = head->left;
		}
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

int main()
{		
	const int n = 14;
	int ms[n] = { 50, 48, 49, 43, 44, 20, 3, 23, 24, 59, 63, 61, 68, 25 };

	Node *tree = nullptr;

	for (int i = 0; i < n; ++i)
	{
		insert(&tree, ms[i]);
	}

	int delValue = 43;
	//deleteNode(tree, delValue);

	travers(tree);




	return 0;
}