/*
 *The source contais a lot os functions manipulating list
 *
 * */
#include<stdio.h>
#include<stdlib.h>

struct node
{
	int value;
	struct node *nextNode;
};

typedef struct node ListNode;
typedef ListNode *nodePointer;


int concateList(nodePointer,nodePointer);
nodePointer merge(nodePointer,nodePointer);
void printList(nodePointer);
int isEmpty(nodePointer);
void insertSort(nodePointer,nodePointer);

int main(void)
{
	nodePointer startNode = NULL;
	nodePointer startNodeTwo = NULL;

	startNode = malloc(sizeof(ListNode));	
	if(startNode != NULL){
		startNode->value = 1;
		nodePointer scdNode = malloc(sizeof(ListNode));
		scdNode->value = 5;
		scdNode->nextNode = NULL;
		startNode->nextNode = scdNode;
	}
	printList(startNode);

	startNodeTwo = malloc(sizeof(ListNode));
	if(startNodeTwo != NULL){
		startNodeTwo->value = 9;
		nodePointer scdNode = malloc(sizeof(ListNode));
		scdNode->value = 2;
		scdNode->nextNode = NULL;
		startNodeTwo->nextNode = scdNode;
	}
	printList(startNodeTwo);
	printf("Vai chamar o merge");
	nodePointer newList = merge(startNode, startNodeTwo);
	printList(newList);
	printf("Executation finish!");
	return 0;
}

/**
 *This function contace the second list on the first one.
 *
 * */
int concateList(nodePointer mainList, nodePointer secondList)
{
	nodePointer currentNode = mainList;
	nodePointer tempNode;
	
	if(currentNode != NULL){
		while(currentNode->nextNode != NULL){
			currentNode = currentNode->nextNode;
		}
		if(secondList != NULL){
			currentNode->nextNode = secondList;
		}
	}

}

/**
 * This function merge two list on a third one. The elements are insert in order
 *
 * */
nodePointer merge(nodePointer firstList, nodePointer secondList)
{
	printf("entrou no merge");
	nodePointer newList = malloc(sizeof(ListNode));
	if(newList != NULL){
		nodePointer currentNode = firstList;
		printf("O valor do primeiro elemento eh -> %d", currentNode->value);
		while(currentNode != NULL){
			insertSort(newList, currentNode);
			currentNode = currentNode->nextNode;
		}
		printf("Elementos da primeira lista foram adicionados");
		currentNode = secondList;
		while(currentNode != NULL){
			insertSort(newList,currentNode);
			currentNode = currentNode->nextNode;
		}
		printf("Elementos da segunda lista foram adicionados");
	}
	printf("final do merge");
	return newList;
}


/*
 *The function verify if a list is empty
 * */
int isEmpty(nodePointer list)
{
	return list == NULL;
}

/*
 *Print all elements of the list
 * */
void printList(nodePointer list)
{
	nodePointer currentNode = list;
	if(!isEmpty(list)){
		printf("\nThe list's values are: ");	
		while(currentNode != NULL){
			int value = currentNode->value;
			printf("%d -> ", value);
			currentNode = currentNode->nextNode;
		}
		printf(" NULL");
	}else{
		printf("The list is empty, idiot!");
	}
	printf("\nVai sair do print\n");
}

/**
 *This function insert a element in a list.
 * */
void insertSort(nodePointer list,nodePointer element )
{
	nodePointer currentNode = list;
	if(currentNode != NULL){
		while(1){
			if(currentNode->nextNode  == NULL){
				currentNode->nextNode = element;
				return;
			}
		}
	}
}

