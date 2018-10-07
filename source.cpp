#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

using namespace std;

typedef struct Node {
	int data;
	int degree;
	struct Node *Nextptr;
};

Node *ptrArray[100005];

struct Node * root = NULL;

Node * searchParentNode(int key, Node *ptr) {

	for (int i = 0; i < ptr->degree; ++i) {
		if (ptr->Nextptr[i].data == key) return ptr;
	}

	for (int i = 0; i < ptr->degree; ++i) {
		Node *s_ptr = searchParentNode(key, &(ptr->Nextptr[i]));
		if (s_ptr != NULL) return s_ptr;
	}

	return NULL;
}

void insertNode(int parent, int child) {
	
	Node* parentNode = ptrArray[parent];

	parentNode->Nextptr = (Node *)realloc(parentNode->Nextptr, sizeof(Node)*(parentNode->degree + 1));
	parentNode->Nextptr[parentNode->degree].data = child;
	parentNode->Nextptr[parentNode->degree].degree = 0;
	parentNode->Nextptr[parentNode->degree].Nextptr = NULL;
	ptrArray[child] = &(parentNode->Nextptr[parentNode->degree]);
	parentNode->degree++;


}

int main(void) {
	int num;

	scanf("%d", &num);
	
	root = (Node *)malloc(sizeof(Node));
	root->data = 1;
	root->Nextptr = NULL;
	root->degree = 0;
	ptrArray[1] = root;

	for (int i = 0; i < num-1; ++i) {
		int n1, n2;
		scanf("%d %d", &n1, &n2);

		if (ptrArray[n1] != NULL && ptrArray[n2] == NULL) {
			insertNode(n1, n2);
		}
		else if (ptrArray[n2] != NULL && ptrArray[n1] == NULL) {
			insertNode(n2, n1);
		}
	}

	for (int i = 2; i <= num; ++i) {
		Node* parent = searchParentNode(i, root);
		printf("%d\n", parent->data);
	}

	return 0;
}
