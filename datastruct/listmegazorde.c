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
	
	printList(merge(startNode,startNodeTwo));
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
 */
nodePointer merge(nodePointer firstList, nodePointer secondList)
{
	nodePointer newList = NULL;
	nodePointer mergeList = NULL;
	if(firstList != NULL){
		newList = firstList;
		mergeList = secondList;
	}else if(secondList != NULL){
		newList = secondList;
		mergeList = firstList;
	}

	nodePointer tempNode = NULL;
	while(!isEmpty(mergeList)){
		tempNode = mergeList->nextNode;
		mergeList->nextNode = NULL;
		insertSort(newList,mergeList);	
		mergeList = tempNode;
	}
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
		printf(" NULL\n");
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
	nodePointer nextNode = NULL;
	while(currentNode != NULL){
		nextNode = currentNode->nextNode;
		if(nextNode != NULL){
			if((element->value >= currentNode->value) & (element->value <= (currentNode->nextNode)->value)){
				nodePointer tempNode = NULL;
				tempNode = currentNode->nextNode;
				currentNode->nextNode = element;
				element->nextNode = tempNode;
				return;
			}
			currentNode = nextNode;
		}else{
			currentNode->nextNode = element;
			return;
		}
	}

}

