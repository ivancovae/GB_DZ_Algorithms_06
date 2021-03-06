#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>

void solution00();
void solution01();
void solution02();
void menu();

// Задание выполнил Иванцов Александр Евгеньевич
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Rus");
	int select = 0;

	do
	{
		menu();
		scanf("%i", &select);
		switch (select)
		{
		case 1:
			solution00();
			break;
		case 2:
			solution01();
			break;
		case 3:
			solution02();
			break;
		case 0:
			printf("Программа закончила свое выполнение.\n");
			break;
		default:
			printf("Некорректный символ, введите значения из списка меню.\n");
		}
	} while (select != 0);
	system("pause");
	return 0;
}

void menu()
{
	printf("Меню выбора решения задания:\n\n");

	printf("1. Решение задачи 1\n");
	printf("2. Решение задачи 2\n");
	printf("3. Решение задачи 3\n");
	printf("0. Завершение выполнения программы\n");
}

void descriptionTask(char *task)
{
	printf("\n##########################################\n");
	printf("\nУсловие задачи:\n");
	printf(task);
}

void endTask()
{
	printf("\n##########################################\n\n");
}

// h(S)  =  S[0]  +  S[1] * P  +  S[2] * P^2  +  S[3] * P^3  +  ...  +  S[N] * P^N
unsigned long long getHash(const char* str)
{
	const int p = 53;
	unsigned long long hash = 0, p_pow = 1;
	for (size_t i = 0; i < strlen(str); i++)
	{
		hash += (str[i] - 'a' + 1) * p_pow;
		p_pow *= p;
	}
	return hash;
}

// Задание 1: Реализовать простейшую хеш-функцию. На вход функции подается строка, на выходе сумма кодов символов.
void solution00()
{
	descriptionTask("Реализовать простейшую хеш-функцию. На вход функции подается строка, на выходе сумма кодов символов.\n");
	// Ввод данных
	
	char str[SHRT_MAX];
	scanf("%s", str);

	// Решение
	printf("Результат: \n");
	printf("Хэш-значение: %llu", getHash(str));

	endTask();
}

#define T char

typedef struct tagNode * pNode;

typedef struct tagNode {
	T data;
	pNode left;
	pNode right;
	pNode parent;
} Node;

// Распечатка двоичного дерева в виде скобочной записи
void printTree(pNode root) {
	if (root)
	{
		printf("%d", root->data);
		if (root->left || root->right)
		{
			printf("(");
			if (root->left)
				printTree(root->left);
			else
				printf("NULL");
			printf(",");
			if (root->right)
				printTree(root->right);
			else
				printf("NULL");
			printf(")");
		}
	}
}

// Создание нового узла
pNode getFreeNode(T value, pNode parent) {
	pNode tmp = (pNode)malloc(sizeof(Node));
	tmp->left = tmp->right = NULL;
	tmp->data = value;
	tmp->parent = parent;
	return tmp;
}

// Вставка узла
void insert(pNode *head, int value) {
	pNode tmp = NULL;
	if (*head == NULL)
	{
		*head = getFreeNode(value, NULL);
		return;
	}
	tmp = *head;
	while (tmp)
	{
		if (value > tmp->data)
		{
			if (tmp->right)
			{
				tmp = tmp->right;
				continue;
			}
			else
			{
				tmp->right = getFreeNode(value, tmp);
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
				tmp->left = getFreeNode(value, tmp);
				return;
			}
		}
		else
		{
			exit(2); // дерево построено неправильно
		}
	}
}

// обход корень-левый-правый (обход в прямом порядке)
void preOrderTravers(pNode root) {
	if (root) {
		printf("%d ", root->data);
		preOrderTravers(root->left);
		preOrderTravers(root->right);
	}
}

// обход левый-корень-правый (симметричный обход)
void inOrderTravers(pNode root) {
	if (root) {
		inOrderTravers(root->left);
		printf("%d ", root->data);
		inOrderTravers(root->right);
	}
}

// обход левый–правый–корень (обход в обратном порядке)
void postOrderTravers(pNode root) {
	if (root) {
		postOrderTravers(root->left);
		postOrderTravers(root->right);
		printf("%d ", root->data);
	}
}

pNode search(pNode x, T value)
{
	if ((x == NULL) || (value == x->data))
		return x;
	if (value < x->data)
		return search(x->left, value);
	else
		return search(x->right, value);
}

// Задание 2: Переписать программу, реализующую двоичное дерево поиска.
//				а) Добавить в него обход дерева различными способами;
//				б) Реализовать поиск в двоичном дереве поиска;
//				в) *Добавить в программу обработку командной строки, с помощью которой можно указывать, из какого файла считывать данные, каким образом обходить дерево.
void solution01()
{
	descriptionTask("Переписать программу, реализующую двоичное дерево поиска.\n\tа) Добавить в него обход дерева различными способами;\n\tб) Реализовать поиск в двоичном дереве поиска;\n\tв) *Добавить в программу обработку командной строки, с помощью которой можно указывать, из какого файла считывать данные, каким образом обходить дерево.\n");
	// Ввод данных
	int isExit = 0;
	Node * Tree = NULL;
	char filename[SHRT_MAX];

	printf("\nВведите файл, из которого будут считаны данные: ");
	scanf("%s", filename);

	FILE * file = fopen(filename, "r");
	if (file == NULL)
	{
		puts("Не удалось открыть файл!");
		isExit = 1;
	}

	if (isExit == 0)
	{
		int count;
		fscanf(file, "%d", &count); // Считываем количество записей
		int i;
		for (i = 0; i < count; i++)
		{
			int value;
			fscanf(file, "%d", &value);
			insert(&Tree, value);
		}
		fclose(file);
		printTree(Tree);
		int mode = 0;
		printf("\nВведите номер обхода(1-PreOrder, 2-InOrder, 3-PostOrder):");
		scanf("%d", &mode);
		if (mode < 1 && mode > 3)
			mode = 1;

		switch (mode)
		{
		case 1:
			printf("\nPreOrderTravers:");
			preOrderTravers(Tree);
			break;
		case 2:
			printf("\nInOrderTravers:");
			inOrderTravers(Tree);
			break;
		case 3:
			printf("\nPostOrderTravers:");
			postOrderTravers(Tree);
			break;
		default:
			break;
		}

		pNode node = search(Tree, 6);
	}

	endTask();
}

typedef struct tagStudent * pStudent;

// структура информации о студенте
typedef struct tagStudent {
	char *name;
	char *surname;
	int age;
	int tableNumber;
} Student;

typedef struct tagStudentNode * pStudentNode;

// структура узла двоичного дерева
typedef struct tagStudentNode {
	pStudent data;
	pStudentNode left;
	pStudentNode right;
	pStudentNode parent;
} StudentNode;

// Создание нового узла
pStudentNode getFreeStudentNode(pStudent student, pStudentNode parent) {
	pStudentNode tmp = (pStudentNode)malloc(sizeof(StudentNode));
	tmp->left = tmp->right = NULL;
	tmp->data = student;
	tmp->parent = parent;
	return tmp;
}

// Вставка узла
void insertStudent(pStudentNode *head, pStudent student) {
	pStudentNode tmp = NULL;
	if (*head == NULL)
	{
		*head = getFreeStudentNode(student, NULL);
		return;
	}
	tmp = *head;
	while (tmp)
	{
		if (student->tableNumber > tmp->data->tableNumber)
		{
			if (tmp->right)
			{
				tmp = tmp->right;
				continue;
			}
			else
			{
				tmp->right = getFreeStudentNode(student, tmp);
				return;
			}
		}
		else if (student->tableNumber < tmp->data->tableNumber)
		{
			if (tmp->left)
			{
				tmp = tmp->left;
				continue;
			}
			else
			{
				tmp->left = getFreeStudentNode(student, tmp);
				return;
			}
		}
		else
		{
			exit(2); // дерево построено неправильно
		}
	}
}

// поиск студента по имени и фамилии
pStudent searchStudentNameAndSurname(pStudentNode x, char *name, char *surname)
{
	if (x) {
		if ((*x->data->name == *name) && (*x->data->surname == *surname))
			return x->data;

		pStudent student;
		student = searchStudentNameAndSurname(x->left, name, surname);

		if (student)
			return student;

		student = searchStudentNameAndSurname(x->right, name, surname);

		if (student)
			return student;
	}
	return NULL;
}

// поиск студента по возрасту
pStudent searchStudentAge(pStudentNode x, int age)
{
	if (x) {
		if (x->data->age == age)
			return x->data;

		pStudent student;
		student = searchStudentAge(x->left, age);

		if (student)
			return student;

		student = searchStudentAge(x->right, age);

		if (student)
			return student;
	}
	return NULL;
}

typedef struct tagtableNumber * pTableNumber;

typedef struct tagtableNumber {
	int number;
	pTableNumber next;
} TableNumber;

typedef struct tagNumbers {
	pTableNumber head;
	int size;
	int maxSize;
} Numbers;

void initNumbers(Numbers *numbers)
{
	numbers->maxSize = 100;
	numbers->size = 0;
	numbers->head = NULL;
}

// печать дерева студентов
void printStudentTree(pStudentNode root) {
	if (root)
	{
		printf("%s %s (%d)", root->data->name, root->data->surname, root->data->age);
		if (root->left || root->right)
		{
			printf("(");
			if (root->left)
				printStudentTree(root->left);
			else
				printf("NULL");
			printf(",");
			if (root->right)
				printStudentTree(root->right);
			else
				printf("NULL");
			printf(")");
		}
	}
}

// добавление элемента
void addElement(Numbers *queue, int number)
{
	if (queue->size == queue->maxSize)
	{
		printf("Номера закончились, необходимо увеличить количество табличных номеров.\n");
		return;
	}
	pTableNumber tmp = (pTableNumber)malloc(sizeof(TableNumber));
	// Задание 2: Добавить в программу «реализация стека на основе односвязного списка» проверку на выделение памяти.
	//	Если память не выделяется, то выводится соответствующее сообщение. 
	//	Постарайтесь создать ситуацию, когда память не будет выделяться (добавлением большого количества данных). Не удалось, полагаю это из-за ограничения в 2ГБ на приложение для Windows 10.
	if (tmp == NULL) // если выделение памяти не выполнилось
	{
		printf("Выделение памяти для нового элемента не удалось.\n");
		return;
	}
	tmp->number = number;
	tmp->next = NULL;
	if (queue->size == 0)
	{
		queue->head = tmp;
		queue->head->next = NULL;
		queue->size++;
		return;
	}
	pTableNumber ptn = queue->head;
	while (ptn->next != NULL) { ptn = ptn->next; }
	ptn->next = tmp;

	queue->size++;
}

// удаление элемента
void deleteElement(Numbers *lst, int number)
{
	pTableNumber current = lst->head;
	pTableNumber next;
	while (current && current->next->number != number)
		current = current->next;
	next = current->next;
	if (current)
	{
		current->next = next->next;
		next->next = NULL;
		free(next);
		lst->size--;
	}
}

// найти свободный номер 
int addFreeNumber(Numbers *lst)
{
	pTableNumber current = lst->head;
	int number = 0;
	while (current)
	{
		if (current->number == number)
		{
			number++;
			current = lst->head;
		}
		current = current->next;
	}
	// для теста имитация нефрагментированной доски номера уже не попорядку, а случайно освободившиеся, используется для разветвления дерева студентов
	int randNum = rand() % SHRT_MAX;
	number = randNum;
	// -------------

	return number;
}


// Задание 3: *Разработать базу данных студентов из полей «Имя», «Возраст», «Табельный номер», в которой использовать все знания, полученные на уроках.
//				Считайте данные в двоичное дерево поиска.Реализуйте поиск по какому - нибудь полю базы данных(возраст, вес).
void solution02()
{
	descriptionTask("*Разработать базу данных студентов из полей «Имя», «Возраст», «Табельный номер», в которой использовать все знания, полученные на уроках.\n\tСчитайте данные в двоичное дерево поиска.Реализуйте поиск по какому - нибудь полю базы данных(возраст, вес).\n");
	// Ввод данных
	
	int isExit = 0;
	pStudentNode Tree = NULL;
	char filename[SHRT_MAX];
	Numbers numbers;
	initNumbers(&numbers);

	printf("\nВведите файл, из которого будут считаны данные: ");
	scanf("%s", filename);

	FILE * file = fopen(filename, "r");
	if (file == NULL)
	{
		puts("Не удалось открыть файл!");
		isExit = 1;
	}

	if (isExit == 0)
	{
		int count;
		fscanf(file, "%d", &count); // Считываем количество записей
		int i;
		for (i = 0; i < count; i++)
		{
			char name[SHRT_MAX];
			fscanf(file, "%s", name);
			char * copyName = malloc(strlen(name) + 1);
			strcpy(copyName, name);

			char surname[SHRT_MAX];
			fscanf(file, "%s", surname);
			char * copySurname = malloc(strlen(surname) + 1);
			strcpy(copySurname, surname);
			int age;
			fscanf(file, "%d", &age);

			pStudent student = (pStudent)malloc(sizeof(Student));
			student->age = age;
			student->name = copyName;
			student->surname = copySurname;
			int num = addFreeNumber(&numbers);
			addElement(&numbers, num);

			student->tableNumber = num;
			insertStudent(&Tree, student);
		}
		fclose(file);
		printStudentTree(Tree);

		// Проверка по имени и фамилии
		pStudent pstud = searchStudentNameAndSurname(Tree, "Дориан", "Сидоров");
		if (pstud)
			printf("\nДориан Сидоров найден и ему %i лет\n", pstud->age);

		// Проверка по возрасту, возврат первого с возрастом найденного
		pStudent pstudaage = searchStudentAge(Tree, 19);
		if (pstudaage)
			printf("\n%d по списку студент с возрастом %d - %s %s\n", pstudaage->tableNumber, 19, pstudaage->name, pstudaage->surname);
	}

	endTask();
}