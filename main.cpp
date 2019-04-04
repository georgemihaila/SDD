#include "pch.h"
#include <iostream>
#include <stdio.h>
using namespace std;

#define null NULL
const char* filename = "in.txt";

struct Student {
	char* name;
	int age;
};

#pragma region SLL

struct SLL {
	Student* data;
	SLL* next;
};

Student* createStudent(const char* buffer, int age) {
	Student* student = (Student*)malloc(sizeof(Student*));
	student->name = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy(student->name, buffer);
	student->age = age;
	return student;
}

SLL* createNode(Student* s) {
	SLL* node = (SLL*)malloc(sizeof(SLL));
	node->next = nullptr;
	node->data = s;
	return node;
}

SLL* createNode(const char* buffer, int age) {
	return createNode(createStudent(buffer, age));
}

SLL* headInsert(SLL* source, SLL* node) {
	if (source != null)
		node->next = source;
	return node;
}

SLL* tailInsert(SLL* source, SLL* node) {
	if (source != null) {
		SLL* temp = source;
		while (temp->next != null)
			temp = temp->next;
		temp->next = node;
	}
	else {
		source = node;
	}
	return source;
}

SLL* insertAt(SLL* source, SLL* node, int index) {
	int c = -1;
	SLL* current = source;
	while (++c != index)
		current = current->next;
	node->next = current->next;
	current->next = node;
	return source;
}

SLL* removeAt(SLL* source, int index) {
	if (index == 0) {
		SLL* copy = source->next;
		source->next = null;
		free(source);
		source = copy;
	}
	else {
		int c = 0;
		SLL* prev = source;
		while (++c < index)
			prev = prev->next;
		SLL* tail = prev->next->next;
		SLL* head = prev;
		free(prev->next);
		head->next = tail;
		source = head;
	}
	return source;
}

void printSLL(SLL* list) {
	while (list != null) {
		cout << list->data->name << " - " << list->data->age << endl;
		list = list->next;
	}
}

#pragma endregion 

#pragma region DLL

struct DLL {
	Student* data;
	DLL* next;
	DLL* prev;
};

DLL* createDLLNode(const char* buffer, int age) {
	Student* student = createStudent(buffer, age);
	DLL* node = (DLL*)malloc(sizeof(DLL));
	node->data = student;
	node->next = nullptr;
	node->prev = nullptr;
	return node;
}

DLL* dllHeadInsert(DLL* head, DLL* node) {
	if (head != null) {
		node->next = head;
		head->prev = node;
	}
	return node;
}

DLL* dllTailInsert(DLL* head, DLL* node) {
	if (head != null) {
		DLL* temp = head;
		while (temp->next != nullptr)
			temp = temp->next;
		node->prev = temp;
		temp->next = node;
		return head;
	}
	else {
		return node;
	}
}

DLL* dllReplaceAt(DLL* head, DLL* node, int index) {
	if (head != null) {
		if (index == 0) {
			node->next = head;
			head->prev = node;
			head = node;
		}
		else {
			int c = 0;
			DLL* previous = head;
			while (++c < index)
				previous = previous->next;
			node->next = previous->next->next;
			node->prev = previous;
			previous->next->next->prev = node;
			free(previous->next);
			previous->next = node;
		}
	}
	return head;
}

DLL* dllInsertAt(DLL* head, DLL* node, int index) {
	if (head != null) {
		if (index == 0) {
			node->next = head;
			head->prev = node;
			head = node;
		}
		else {
			int c = 0;
			DLL* current = head;
			while (++c < index)
				current = current->next;
			node->next = current->next;
			node->prev = current;
			current->next->prev = node;
			current->next = node;
		}
	}
	return head;
}

void printDLL(DLL* head) {
	if (head != null) {
		do {
			cout << head->data->name << " - " << head->data->age << endl;
			head = head->next;
		} while (head != null);
	}
}

#pragma endregion 

#pragma region HashTable

struct HashNode {
	Student* data;
	HashNode* next;
};

struct HashTable {
	HashNode** vector;
	int size;
};

int getHashCode(int number, HashTable* table) {
	return number % table->size;
}

HashTable* createHashTable(int size) {
	HashTable* table = (HashTable*)malloc(sizeof(HashTable));
	table->size = size;
	table->vector = (HashNode**)malloc(sizeof(HashNode) * size);
	for (int i = 0; i < size; i++) {
		table->vector[i] = (HashNode*)malloc(sizeof(HashNode));
		table->vector[i] = null;
	}
	return table;
}

HashNode* createHashNode(Student* data) {
	HashNode* node = (HashNode*)malloc(sizeof(HashNode));
	node->data = data;
	node->next = nullptr;
	return node;
}

HashNode* headInsertHN(HashNode* head, HashNode* node) {
	if (head != null) {
		node->next = head;
	}
	head = node;
	return head;
}

HashTable* insertIntoHashTable(HashTable* hashTable, Student* data) {
	int key = getHashCode(data->age, hashTable);
	hashTable->vector[key] = headInsertHN(hashTable->vector[key], createHashNode(data));
	return hashTable;
}

void printHashNodes(HashNode* nodes) {
	if (nodes != null) {
		for (HashNode* current = nodes; current != null; current = current->next) {
			cout << current->data->name << " - " << current->data->age << endl;
		}
	}
}

void printHashTable(HashTable* table) {
	for (int key = 0; key < table->size; key++) {
		cout << key << ":" << endl;
		printHashNodes(table->vector[key]);
	}
}

#pragma endregion

#pragma region Queue

struct Queue {
	int front, rear, size;
	unsigned capacity;
	Student* arr;
};

Queue* createQueue(unsigned capacity) {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->arr = (Student*)malloc(sizeof(Student) * capacity);
	queue->capacity = capacity;
	queue->front = queue->size = 0;
	queue->rear = capacity - 1;
	return queue;
}

bool isFull(Queue* queue) {
	return queue->size == queue->capacity;
}

bool isEmpty(Queue* queue) {
	return queue->size == 0;
}

Queue* enqueue(Queue* queue, Student data) {
	if (isFull(queue))
		return nullptr;
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->arr[queue->rear] = data;
	queue->size = queue->size + 1;
	return queue;
}

Student dequeue(Queue*& queue) {
	Student result = queue->arr[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size = queue->size - 1;
	return result;
}

#pragma endregion

void main() {
	try {
		FILE* file = fopen(filename, "r");

		SLL* sllHead = null;
		DLL* dllHead = null;
		HashTable* table = createHashTable(10);
		Queue* queue = createQueue(10);

		if (file != null) {
			char buffer[100];
			int age = -1;
			while (!feof(file)) {
				fscanf(file, "%s", buffer);
				fscanf(file, "%d", &age);

				SLL* sllNode = createNode(buffer, age);
				sllHead = headInsert(sllHead, sllNode);

				DLL* dllNode = createDLLNode(buffer, age);
				dllHead = dllTailInsert(dllHead, dllNode);

				table = insertIntoHashTable(table, createStudent(buffer, age));

				Student s;
				s.age = age;
				s.name = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
				strcpy(s.name, buffer);
				queue = enqueue(queue, s);
			}
		}
		else {
			cout << filename << " not found!" << endl;
		}
		cout << ">---SLL test---<" << endl;
		sllHead = insertAt(sllHead, createNode("Cosmjn", 18), 2);
		sllHead = removeAt(sllHead, 1);
		printSLL(sllHead);
		cout << ">--------------<" << endl;

		cout << ">---DLL test---<" << endl;
		dllHead = dllInsertAt(dllHead, createDLLNode("Zamolxes", 22), 1);
		dllHead = dllReplaceAt(dllHead, createDLLNode("Zamolxes", 2000), 1);
		printDLL(dllHead);
		cout << ">--------------<" << endl;

		cout << ">---HashTable test---<" << endl;
		printHashTable(table);
		cout << ">--------------------<" << endl;
	
		cout << ">---Queue test---<" << endl;
		cout << "<---Queue characteristics--->" << endl;
		cout << "Is full: " << isFull(queue) << endl;
		cout << "Capacity:" << queue->capacity << endl;
		cout << "Front:" << queue->front << endl;
		cout << "Rear:" << queue->rear << endl;
		cout << "Size:" << queue->size << endl;
		cout << "<-------------------------->" << endl;
		cout << "Full dequeue:" << endl;
		while (!isEmpty(queue)) {
			Student first = dequeue(queue);
			cout << first.name << " - " << first.age << endl;
		}
		cout << "<---Queue characteristics--->" << endl;
		cout << "Is full: " << isFull(queue) << endl;
		cout << "Capacity:" << queue->capacity << endl;
		cout << "Front:" << queue->front << endl;
		cout << "Rear:" << queue->rear << endl;
		cout << "Size:" << queue->size << endl;
		cout << "<-------------------------->" << endl;
		cout << ">----------------<" << endl;
	}
	catch (exception e) {
		cout << e.what() << endl;
	}
}