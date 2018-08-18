#include <iostream>															// C���������� ���������� ������� �����/������

struct Node																	// �������� ��������� ���� Node
{	
	int info;																// ���������� ���� int 
	char* t;																// ��������� �� ������ ���� char
	Node *left;																// ��������� �� ������ "������������" ))
	Node *right;															// ��������� �� ������� "������������"
	Node *parent;															// ��������� �� "��������" 
};

Node* createFreeNode(int , char *, Node*);									// ������� �������� ����� ������
void addNode(Node**, int, char *);											// ������� ���������� ���� � ������														
void printTree(Node *, char*, int);											// ������� ������ ������ �� �����
Node* findMax(Node * );														// ������� ������ � ����� ����� Max �������� ����(�� �������)
void delTree(Node* );														// ������� �������� ������(������������ ������)
Node *findNode(Node *, int);												// ������� ������ ���� �� ��������
void deleteNode(Node *);													// ������� �������� ���� (����� �����)
Node* minNode(Node* );														// ������� ������ min ���� � ������
Node* maxNode(Node* );														// ������� ������ max ���� � ������														
Node * nextUntilDelet(Node*);												// ������� ������ ���� ������� ������� �� ���������(���� � ���������� ���� ���� 2-� "������������")
int delTheTask(Node *);														// �������  �������� ���� �� ����� ��� �������(�� �������)
void printLeaf(Node *, int, int, int*);
int max(int, int);
int hightTree(Node*, int);


Node* createFreeNode(int info, char *ptrT, Node* parent)					//  ������� �������� ����� ������
{
	Node* tmpRoot = new Node;												// �������� ������ �� ����� ����
	tmpRoot->left = tmpRoot->right = NULL;									// ������������� ��������� �� ������ � ������� "������������" == NULL
	tmpRoot->info = info;													// ���������� � info "����" ���� int
	tmpRoot->t = _strdup(ptrT);												// ���������� � t ����� ������ �� ������� ��������� ��������� ptrT
	tmpRoot->parent = parent;												// ���������� � parent ��������� �� "��������"
	return tmpRoot;															// ���������� ��������� �� ��������� ���� 
}
 
void addNode(Node **head,  int num, char *t)								// ������� ���������� ���� � ������	
{
	Node* tmp = NULL;														// �������� ��������� ���� Node
	if (*head == NULL)														// ������� ���� ��� ����� ������
	{
		*head = createFreeNode(num, t, NULL);								// ������ ����� ���� � "���������" == NULL(�.�. ��� ������)
		return;																// ����� �� �������
	}
	tmp = *head;															// ���� ������ ��� ����, ����������� tmp ��������� �� ������ ������
	while (tmp) {															// ����������� ����
		if (num > tmp->info)												// �������, ���� �������� ���� > ��� �������� � ����� 
		{
			if (tmp->right)													// �������, ���� ���� ��������� �� ������ �����
			{
				tmp = tmp->right;											// ������������ ��������� �� tmp �� ���� ������� ��������� ������ 
				continue;													// ���������� ���������� �����
			}
			else
			{																// ���� ���� ������ ���(�� �� ������)
				tmp->right = createFreeNode(num, t, tmp);					// ������ ����� ���� � ��������� ��� � ����������(�� ������� ��������� tmp)											
				return;														// ����� �� �������
			}
		}
		if (num < tmp->info)												// �������, ���� �������� ���� < ��� �������� � ����� 														
		{
			if (tmp->left)													// �������, ���� ���� ��������� �� ����� �����
			{
				tmp = tmp->left;											// ������������ ��������� tmp �� ���� ������� ��������� ������
				continue;													// ���������� ���������� �����
			}
			else                                                            // ���� ���� � ���� ���(�� �� ������)
			{																		
				tmp->left = createFreeNode(num, t, tmp);					// ������ ����� ���� � ��������� ��� � ����������(�� ������� ��������� tmp)													
				return;														// ����� �� �������														
			}
		}
	}
}
void printTree(Node *root, char* branch, int level) {						// ������� ������ ������ �� �����(����� ������ ����)								
	if (root) {
		printf("lvl %d %s = %d -- %s\n", level, branch, root->info, root->t);// ����� �������� ����� � ������ � ��������� ����� ������ � ������(�������) ������
		printTree(root->left, "left", level + 1);							// ����������� ������� ������ �� ����� ����� ����� ����� ������
		printTree(root->right, "right", level + 1);							// ����������� ������� ������ �� ����� ����� ������ ����� ������
	}
}
int max(int a, int b)														// ������� ������ ������������� �� 2-��(��� ������ ������� ������)
{
	if (a > b)
		return a;
	else
		return b;
}
int hightTree(Node* root, int hight)										
{
	if (root == NULL)
		return hight;
	else
		return max(hightTree(root->left, hight + 1), hightTree(root->right, hight + 1));	// ����������� ������� ����� ������� ������  ��������
}
void printLeaf(Node *root, int level, int* ptrA)											// ������� ������ "�������" ������
{
	
	if (root)
	{	
		if (!root->left && !root->right) {	ptrA[level] = ptrA[level] + 1;	}				// ���� � ���� ��� "�����" ������� ���������� ������� �� ������ ������ +1
		printLeaf(root->left, level + 1, ptrA);												// ����������� ����� ��� ������ ������
		printLeaf(root->right, level + 1, ptrA);											// ����������� ����� ��� ������� ������
		
	}
}
Node* findMax(Node * root)													// ������� ������ � ����� ����� Max �������� ����(�� �������)														
{
	Node* pMax = root->left;												// ������������� ��������� �� ������ ������� �� ����� � ����� �����
	while (pMax->right)														// ������� ���� � ��������� ���� ������ "�����������"
	{
		pMax = pMax->right;													// ������������� ��������� �� ����(�.� �� ������ �����������)
	}
	return pMax;															// ���������� ��������� �� ������������ ���� � ����� �����
}
void delTree(Node *tree)													// ������� �������� ������(������������ ������)
{
	if (tree != NULL) {														// �������, ���� ���� ������ ������
		delTree(tree->left);												// ����������� ������ ��� ����� ����� ������
		delTree(tree->right);												// ����������� ������ ��� ������ ����� ������
		delete tree;														// ������� ��������� �� ���� ������															
	}
}

Node *findNode(Node *root, int value) {										// ������� ������ ���� �� ��������
	while (root) {															// ���� ���� ������ ������(����������� ����)
		if ((root->info > value)) {											// ������� ���� ���� �� ������ root > ��� �������� ����
			root = root->left;												// ������������� ��������� root �� "������������" �����   
			continue;														// ���������� ���������� �����
		}
		else if (root->info < value ) {										// ������� ���� ���� � ����� ������ < ��� �������� ����
			root = root->right;												// ������������� ��������� root �� "������������" �����
			continue;														// ���������� ���������� �����
		}
		else if(root->info == value){										// �������, ���� root ��������� �� ���� � ������ ��� ���������
			return root;													// ���������� ��������� �� ���� ����
		}
	}
	return NULL;															// ���� ������� ���� � ������ �� ������� ���������� NULL
}
Node * nextUntilDelet(Node* root)											// ������� ������ ���� ������� ������� �� ���������
{
		Node *par = root;													// �������� ��������� *par � ���������� ��� �� ��������� ����
		if (par->right != NULL)												// �������, ���� � ���������� ���� ���� ������ "�����������"
			return minNode(par->right);										// ���������� ����������� ���� �� ��������� "������������" ������
}

void deleteNode(Node *delNode)												// ������� �������� ���� (����� �����)
{
	Node  *tmp = NULL, *par = NULL;											// �������� ��������� �� ��������� ���� � ��� "��������"
	tmp = delNode;															// ���������� tmp 

	if (((tmp->left) == NULL) && ((tmp->right) == NULL))					// ������ ���� � ���������� ���� �� "�������������" �� ������ �� �������
	{
		par = tmp->parent;													// ���������� par �� "��������" 
		if (tmp == (par->right))											// �������, ����  ��������� �� ��������� ���� == ������� ��������� "��������"
			par->right = NULL;												// ������������� ��������� �� ��������� ���� � "��������" � NULL
		else																// �������, ���� ��������� ���� ��������� � ����� ����� ������ 
			par->left = NULL;												// ������������� ��������� �� ��������� ���� � "��������" � NULL
		delete tmp;															// ������� ������ ����
		return;																// ����� �� �������	
	}
	
	if (((tmp->left) == NULL) && ((tmp->right) != NULL))					// ������, ����� � ���������� ���� ���� ��������� ������
	{
		par = tmp->parent;													// ���������� par �� "��������" 
		if (tmp == (par->right))											// �������, ����  ��������� �� ��������� ���� == ������� ��������� "��������"
			par->right = tmp->right;										// ������ ��������� "��������" ������������� �� ������ ��������� ���������� ����
		else																// �������, ���� ��������� ���� ��������� � ����� ����� ������ 
			par->left = tmp->right;											// ����� ��������� "��������" ������������� �� ������ ��������� ���������� ����
		delete tmp;															// ������� ������ ����
		return;																// ����� �� �������
	}
		
	if (((tmp->left) != NULL) && ((tmp->right) == NULL))					// ������, ����� � ���������� ���� ���� ��������� �����
	{
		par = tmp->parent;													// ���������� par �� "��������" 
		if (tmp == (par->right))											// �������, ����  ��������� �� ��������� ���� == ������� ��������� "��������"
			par->right = tmp->left;											// ������ ��������� "��������" ������������� �� ����� ��������� ���������� ����		
		else																// �������, ���� ��������� ���� ��������� � ����� ����� ������												
			par->left = tmp->left;											// ����� ��������� "��������" ������������� �� ����� ��������� ���������� ����
		delete tmp;															// ������� ������ ����
		return;																// ����� �� �������
	}
	
	if (((tmp->left) != NULL) && ((tmp->right) != NULL))					// ������ ����� � ���������� ���� ���� 2 "������������"
	{

		par = nextUntilDelet(tmp);											// ������������� "��������" �� ���� ������� ����� ��������� ����� ���������� 												
		tmp->info = par->info;												// ���������� "����" �������� � ��������� ����
		if (par->right == NULL)												// ������� ���� � "��������" ��� "�������������" ������
			par->parent->left = NULL;										// ������������� ����� ��������� �� ��������� ������� � NULL
		else																// ���� � "��������" ���� ��������� �� ������ ����� 
			par->parent->left = par->right;									// ������������� ����� ��������� ���������� �������� �� "������������" ������ 
		delete par;															// ������� "��������"
		return;																// ����� �� �������
	}
}
Node* minNode(Node* root)													// ������� ������ min ���� � ������ c �������� root													
{
	Node *tmpMin = root;													// �������� ��������� tmpMin �� root
	while (tmpMin->left != NULL)											// ������� ���� ���� ����� ��������� �� ����
		tmpMin = tmpMin->left;												// ����������� ��������� tmpMin �� ����
	return tmpMin;															// ���������� ��������� �� min ���� ������
}

int delTheTask(Node * root)													// �������  �������� ���� �� ����� ��� �������(�� �������)
{
	Node *tmpDel = findMax(root), *tmpParDel = tmpDel->parent;				// �������� ��������� tmpDel �� max ���� � ����� �����, � tmpParDel �� ��� ��������

	if (tmpParDel == root)													// ������� ���� "��������" ���������� ���� ������ ������
	{
		Node  *tmpRight = root->right, *tmpLeft = root->left;				// �������� ��������� �� "�������" "������������" �� ����� ������		
		
		delete root;														// ������� ������ ������
		root = tmpRight;													// ���������� ������ ������ �� tmpRight
		root->parent = NULL;												// �������� ����� ���������� � NULL
		
		printf("Parent of a deleted node == root, root is delete!!!\n");
		printTree(root, "root", 0);											// ����� �� ����� ������
		return 1;															// ���������� 1
	}
	if(tmpDel->left)														// �������, ���� � ���������� ���� ���� ����� "�����������"
		deleteNode(tmpDel->left);											// ������� ������ "������������" ))

	deleteNode(tmpDel);														// ������� ��� ����
	
	deleteNode(tmpParDel);													// ������� "������������" ����											
	
	return 0;																// ���������� 0
}


int main() {

	Node* root = NULL;														// �������� ��������� �� ������ ������
	int x, y = 0, z;														// ���������� ���� int ��� �������� ������ ������
	char t[21];																// ������ ���� char ��� �������� ������
	printf("Please, enter number of nodes in the tree:");
	scanf("%d", &z);														// ������� ���������� ����� ������
	
	printf("Please, enter %d norepeating nubmers and text < 20 symbols:", z);
	for (int i = 0; i < z; i++)												// ���� ��� ����� 
	{	
		scanf("%d", &x);													// ������� �������� ����� ����												
		scanf("%s", t);														// ������� ������
		addNode(&root, x, t);												// �������� ����� ���� � �������� �������
	}
	printf("Tree before:\n");
	printTree(root, "root", 0);												// ����� �� ����� ������ �� �����������

	printf("\nMax in left branch = %d -- %s\n", (findMax(root))->info, (findMax(root))->t); // ����� max ���� � ����� ����� ������
	
	/*
	printf("\nPlease, enter key to search -- ");
	std::cin >> y;															// ��������� �������� ���������� ����
	if (findNode == NULL) { printf("Node not found in the tree"); }			// �������� ������ �� �������� ����
	else deleteNode(findNode(root, y));										// �������� ���� �� �����

	printTree(root, "root", 0);												// ����� �� ����� ������ 										
	*/
	/*if (delTheTask(root))													// ������� ���� ������� ������ ������ � ������� ������� 1 
	{
		system("pause");
		return 0;															// ��������� ���������� ���������
	}
	else 
	{
		printf("\nTree after delete\n");	
		printTree(root, "root", 0);											// ���� ������� ������� 0 ������� ������ �� �����
	}
	*/
	int q = 0;
	q = hightTree(root, 0);													// ��������� ���������� q �������� ������� ������
	int *ptrA;
	ptrA = new int[q];														// ����������� �������� ������

	for (int i = 0; i < q; i++)												// �������� �������� � ���������� ������ ����� ���������
		ptrA[i] = 0;

	printLeaf(root, 0, ptrA);												// ����� ������� �������� ������� � ������

	for (int j = 0; j < q; j++)
		std::cout << "Level (" << j << ") has -- " << ptrA[j] << " leaves" << std::endl;	// ����� �� ����� ������ � ���������� ������� �� ������
	
	delete[] ptrA;															// ����������� ������

	delTree(root);															// ����������� ������

	system("pause");
}
