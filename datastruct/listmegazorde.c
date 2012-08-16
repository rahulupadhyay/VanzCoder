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


void concateList(nodePointer,nodePointer);
void merge(nodePointer,nodePointer,nodePointer);
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
	startNodeTwo->value = 3;
	startNodeTwo->nextNode = NULL;
	insertSort(startNode, startNodeTwo);
	printList(startNode);
	if(startNodeTwo != NULL){
		startNodeTwo->value = 9;
		nodePointer scdNode = malloc(sizeof(ListNode));
		scdNode->value = 2;
		scdNode->nextNode = NULL;
		startNodeTwo->nextNode = scdNode;
	}
	return 0;
}
/**
 *This function contace the second list on the first one.
 *
 * */
void concateList(nodePointer mainList, nodePointer secondList)
{
	nodePointer currentNode = mainList;
		
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
 * FIXME - This functions doesn't works how expected
 * */
void merge(nodePointer newList, nodePointer firstList, nodePointer secondList)
{
	if(newList != NULL){
		nodePointer currentNode = firstList;
		while(currentNode != NULL){
			insertSort(newList, currentNode);
			currentNode = currentNode->nextNode;
		}
		currentNode = secondList;
		while(currentNode != NULL){
			insertSort(newList,currentNode);
			currentNode = currentNode->nextNode;
		}
	}
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
}

/**
 *This function insert a element in a list.
 * */
void insertSort(nodePointer list,nodePointer element )
{
	nodePointer currentNode = list;
	while(currentNode != NULL){
		if(element->value >= currentNode->value){
			nodePointer tempNode = NULL;
			if(currentNode->nextNode != NULL){
				tempNode = currentNode->nextNode;
			}
			currentNode->nextNode = element;
			if(tempNode != NULL){
				element->nextNode = tempNode;
			}
			return;
		}else{
			if(currentNode->nextNode != NULL){
				currentNode = currentNode->nextNode;
			}
		}
	}
}

