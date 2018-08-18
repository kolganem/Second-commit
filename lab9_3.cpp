#include <iostream>															// Cтандартная библиотека потоков ввода/вывода

struct Node																	// Описание структуры типа Node
{	
	int info;																// Переменная типа int 
	char* t;																// Указатель на строку типа char
	Node *left;																// Указатель на левого "родственника" ))
	Node *right;															// Указатель на правого "родственника"
	Node *parent;															// Указатель на "родителя" 
};

Node* createFreeNode(int , char *, Node*);									// Функция создания корня дерева
void addNode(Node**, int, char *);											// Функция добавления узла в дерево														
void printTree(Node *, char*, int);											// Функция вывода дерева на экран
Node* findMax(Node * );														// Функция поиска в левой ветви Max значения узла(по заданию)
void delTree(Node* );														// Функция удаления дерева(освобождения памяти)
Node *findNode(Node *, int);												// Функция поиска узла по значению
void deleteNode(Node *);													// Функция удаления узла (общая форма)
Node* minNode(Node* );														// Функция поиска min узла в дереве
Node* maxNode(Node* );														// Функция поиска max узла в дереве														
Node * nextUntilDelet(Node*);												// Функция поиска узла который следует за удаляемым(если у удаляемого узла есть 2-а "родственника")
int delTheTask(Node *);														// Функция  удаления узла со всеми его связями(по заданию)
void printLeaf(Node *, int, int, int*);
int max(int, int);
int hightTree(Node*, int);


Node* createFreeNode(int info, char *ptrT, Node* parent)					//  Функция создания корня дерева
{
	Node* tmpRoot = new Node;												// Выделяем память на новый узел
	tmpRoot->left = tmpRoot->right = NULL;									// Устанавливаем указатель на левого и правого "родственника" == NULL
	tmpRoot->info = info;													// Записываем в info "ключ" типа int
	tmpRoot->t = _strdup(ptrT);												// Записываем в t копию строки на которую указывает указатель ptrT
	tmpRoot->parent = parent;												// Записываем в parent указатель на "родителя"
	return tmpRoot;															// Возвращаем указатель на созданный узел 
}
 
void addNode(Node **head,  int num, char *t)								// Функция добавления узла в дерево	
{
	Node* tmp = NULL;														// Объявили указатель типа Node
	if (*head == NULL)														// Условие если нет корня дерева
	{
		*head = createFreeNode(num, t, NULL);								// Создаём новый узел с "родителем" == NULL(т.к. это корень)
		return;																// Выход из функции
	}
	tmp = *head;															// Если корень уже есть, присваиваем tmp указатель на корень дерева
	while (tmp) {															// Бесконечный цикл
		if (num > tmp->info)												// Условие, если введённый ключ > чем значение в корне 
		{
			if (tmp->right)													// Условие, если есть указатель на правую ветку
			{
				tmp = tmp->right;											// Переставляем указатель на tmp на узел который находится справа 
				continue;													// Продолжаем выполнения цикла
			}
			else
			{																// Если узла справа нет(он не создан)
				tmp->right = createFreeNode(num, t, tmp);					// Создаём новый узел и соединяем его с предыдущим(на который указывает tmp)											
				return;														// Выход из функции
			}
		}
		if (num < tmp->info)												// Условие, если введённый ключ < чем значение в корне 														
		{
			if (tmp->left)													// Условие, если есть указатель на левую ветку
			{
				tmp = tmp->left;											// Переставляем указатель tmp на узел который находится справа
				continue;													// Продолжаем выполнения цикла
			}
			else                                                            // Если узла с лева нет(он не создан)
			{																		
				tmp->left = createFreeNode(num, t, tmp);					// Создаём новый узел и соединяем его с предыдущим(на который указывает tmp)													
				return;														// Выход из функции														
			}
		}
	}
}
void printTree(Node *root, char* branch, int level) {						// Функция вывода дерева на экран(обход сверху вниз)								
	if (root) {
		printf("lvl %d %s = %d -- %s\n", level, branch, root->info, root->t);// Вывод значения ключа и строки с указанием ветки дерева и уровня(глубины) дерева
		printTree(root->left, "left", level + 1);							// Рекурсивная функция вывода на экран узлов левой ветви дерева
		printTree(root->right, "right", level + 1);							// Рекурсивная функция вывода на экран узлов правой ветви дерева
	}
}
int max(int a, int b)														// Функция выбора максимаотного из 2-ух(для поиска глубины дерева)
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
		return max(hightTree(root->left, hight + 1), hightTree(root->right, hight + 1));	// Рекурсивная функция поика глубины дерева  уровнями
}
void printLeaf(Node *root, int level, int* ptrA)											// Функция печати "листьев" дерева
{
	
	if (root)
	{	
		if (!root->left && !root->right) {	ptrA[level] = ptrA[level] + 1;	}				// Если у узла нет "детей" счётчик количества листьев на данном уровне +1
		printLeaf(root->left, level + 1, ptrA);												// Рекурсивный вызов для левого дерева
		printLeaf(root->right, level + 1, ptrA);											// Рекурсивный вызов для правого дерева
		
	}
}
Node* findMax(Node * root)													// Функция поиска в левой ветви Max значения узла(по заданию)														
{
	Node* pMax = root->left;												// Устанавливаем указатель на первый элемент от корня в левой ветви
	while (pMax->right)														// Условие если у указателя есть правый "родственник"
	{
		pMax = pMax->right;													// Устанавливаем указатель на него(т.к он больше предыдущего)
	}
	return pMax;															// Возвращаем указатель на максимальный узел в левой ветви
}
void delTree(Node *tree)													// Функция удаления дерева(освобождения памяти)
{
	if (tree != NULL) {														// Условие, пока есть корень дерева
		delTree(tree->left);												// Освобождаем память для левой ветви дерева
		delTree(tree->right);												// Освобождаем память для правой ветви дерева
		delete tree;														// Удаляем указатель на узел дерева															
	}
}

Node *findNode(Node *root, int value) {										// Функция поиска узла по значению
	while (root) {															// Пока есть корень дерева(бесконечный цикл)
		if ((root->info > value)) {											// Условие если ключ по адресу root > чем введённый ключ
			root = root->left;												// Устанавливаем указатель root на "родственника" слева   
			continue;														// Продолжаем выполнения цикла
		}
		else if (root->info < value ) {										// Условие если ключ в корне дерева < чем введённый ключ
			root = root->right;												// Устанавливаем указатель root на "родственника" слева
			continue;														// Продолжаем выполнения цикла
		}
		else if(root->info == value){										// условие, если root указывает на узел с нужным нам значением
			return root;													// Возвращаем указатель на этот узел
		}
	}
	return NULL;															// Если искомго узла в дереве не найдено возвращаем NULL
}
Node * nextUntilDelet(Node* root)											// Функция поиска узла который следует за удаляемым
{
		Node *par = root;													// Объявили указатель *par и установили его на удаляемый узел
		if (par->right != NULL)												// Условие, если у удаляемого узла есть правый "родственник"
			return minNode(par->right);										// Возвращаем минимальный узел из поддерева "родственника" справа
}

void deleteNode(Node *delNode)												// Функция удаления узла (общая форма)
{
	Node  *tmp = NULL, *par = NULL;											// Объявили указатели на удаляемый узел и его "родителя"
	tmp = delNode;															// Установили tmp 

	if (((tmp->left) == NULL) && ((tmp->right) == NULL))					// Случай если у удаляемого узла не "родственников" на левого ни правого
	{
		par = tmp->parent;													// Установили par на "родителя" 
		if (tmp == (par->right))											// Условие, если  указатель на удаляемый узел == правому указателю "родителя"
			par->right = NULL;												// Устанавливаем указатель на удаляемый узел у "родителя" в NULL
		else																// Условие, если удаляемый узел находится в левой ветке дерева 
			par->left = NULL;												// Устанавливаем указатель на удаляемый узел у "родителя" в NULL
		delete tmp;															// Удаляем данный узел
		return;																// Выход из функции	
	}
	
	if (((tmp->left) == NULL) && ((tmp->right) != NULL))					// Случай, когда у удаляемого узла есть поддерево справа
	{
		par = tmp->parent;													// Установили par на "родителя" 
		if (tmp == (par->right))											// Условие, если  указатель на удаляемый узел == правому указателю "родителя"
			par->right = tmp->right;										// Правый указатель "родителя" устанавливаем на правый указатель удаляемого узла
		else																// Условие, если удаляемый узел находится в левой ветке дерева 
			par->left = tmp->right;											// Левый указатель "родителя" устанавливаем на правый указатель удаляемого узла
		delete tmp;															// Удаляем данный узел
		return;																// Выход из функции
	}
		
	if (((tmp->left) != NULL) && ((tmp->right) == NULL))					// Случай, когда у удаляемого узла есть поддерево слева
	{
		par = tmp->parent;													// Установили par на "родителя" 
		if (tmp == (par->right))											// Условие, если  указатель на удаляемый узел == правому указателю "родителя"
			par->right = tmp->left;											// Правый указатель "родителя" устанавливаем на левый указатель удаляемого узла		
		else																// Условие, если удаляемый узел находится в левой ветке дерева												
			par->left = tmp->left;											// Левый указатель "родителя" устанавливаем на левый указатель удаляемого узла
		delete tmp;															// Удаляем данный узел
		return;																// Выход из функции
	}
	
	if (((tmp->left) != NULL) && ((tmp->right) != NULL))					// Случай когда у удаляемого узла есть 2 "родственника"
	{

		par = nextUntilDelet(tmp);											// Устанавливаем "родителя" на узел который будет следующим после удаляемого 												
		tmp->info = par->info;												// Записываем "ключ" родителя в удаляемый узел
		if (par->right == NULL)												// Условие если у "родителя" нет "родственников" справа
			par->parent->left = NULL;										// Устанавливаем левый указатель на удаляемый элемент в NULL
		else																// Если у "родителя" есть указатель на правую ветвь 
			par->parent->left = par->right;									// Устанавливаем левый указатель удаляемого элемента на "родственника" справа 
		delete par;															// Удаляем "родителя"
		return;																// Выход из функции
	}
}
Node* minNode(Node* root)													// Функция поиска min узла в дереве c вершиной root													
{
	Node *tmpMin = root;													// Объявили указатель tmpMin на root
	while (tmpMin->left != NULL)											// Условие пока есть левый указатель на узел
		tmpMin = tmpMin->left;												// Передвигаем указатель tmpMin на него
	return tmpMin;															// Возвращаем указатель на min узел дерева
}

int delTheTask(Node * root)													// Функция  удаления узла со всеми его связями(по заданию)
{
	Node *tmpDel = findMax(root), *tmpParDel = tmpDel->parent;				// Объявили указатель tmpDel на max узел в левой ветви, и tmpParDel на его родителя

	if (tmpParDel == root)													// Условие если "родитель" удаляемого узла корень дерева
	{
		Node  *tmpRight = root->right, *tmpLeft = root->left;				// Объявили указатель на "правого" "родственника" от корня дерева		
		
		delete root;														// Удалили корень дерева
		root = tmpRight;													// Установили корень дерева на tmpRight
		root->parent = NULL;												// Родителя корня установили в NULL
		
		printf("Parent of a deleted node == root, root is delete!!!\n");
		printTree(root, "root", 0);											// Вывод на экран дерево
		return 1;															// Возвратили 1
	}
	if(tmpDel->left)														// Условие, если у удаляемого узла есть левый "родственник"
		deleteNode(tmpDel->left);											// Удаляем левого "родственника" ))

	deleteNode(tmpDel);														// Удаляем сам узел
	
	deleteNode(tmpParDel);													// Удаляем "родственника" узла											
	
	return 0;																// Возвращаем 0
}


int main() {

	Node* root = NULL;														// Объявили указатель на корень дерева
	int x, y = 0, z;														// Переменный типа int для хранения данный ключей
	char t[21];																// Массив типа char для хранения строки
	printf("Please, enter number of nodes in the tree:");
	scanf("%d", &z);														// Считали количество узлов дерева
	
	printf("Please, enter %d norepeating nubmers and text < 20 symbols:", z);
	for (int i = 0; i < z; i++)												// Цикл для ввода 
	{	
		scanf("%d", &x);													// Считали значение ключа узла												
		scanf("%s", t);														// Считали строку
		addNode(&root, x, t);												// Добавили новый узел с введённый данными
	}
	printf("Tree before:\n");
	printTree(root, "root", 0);												// Вывод на экран дерева до манипуляций

	printf("\nMax in left branch = %d -- %s\n", (findMax(root))->info, (findMax(root))->t); // Вывод max узла в левой ветви дерева
	
	/*
	printf("\nPlease, enter key to search -- ");
	std::cin >> y;															// Считываем значение удаляемого узла
	if (findNode == NULL) { printf("Node not found in the tree"); }			// Проверка найден ли введённый узел
	else deleteNode(findNode(root, y));										// Удаление узла по ключу

	printTree(root, "root", 0);												// Вывод на экран дерева 										
	*/
	/*if (delTheTask(root))													// Условие если удаляли корень дерева и функция вернула 1 
	{
		system("pause");
		return 0;															// Завершаем выполнение программы
	}
	else 
	{
		printf("\nTree after delete\n");	
		printTree(root, "root", 0);											// Если функция вернула 0 выводим дерево на экран
	}
	*/
	int q = 0;
	q = hightTree(root, 0);													// Присвоили переменной q значение глубины дерева
	int *ptrA;
	ptrA = new int[q];														// Динамически выделили память

	for (int i = 0; i < q; i++)												// Обнулили значения в выделенной памяти через указатель
		ptrA[i] = 0;

	printLeaf(root, 0, ptrA);												// Вызов функции подсчёта листьев у дерева

	for (int j = 0; j < q; j++)
		std::cout << "Level (" << j << ") has -- " << ptrA[j] << " leaves" << std::endl;	// Вывод на экран уровня и количества листьев на уровне
	
	delete[] ptrA;															// Освобождаем память

	delTree(root);															// Освобожлаем память

	system("pause");
}
