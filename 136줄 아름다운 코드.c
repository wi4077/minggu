#include <stdio.h>
#include <stdlib.h>

struct listNode{ /* 자기 참조 구조체 */
   char data;
   struct listNode *nextPtr;
};

typedef struct listNode LISTNODE;
typedef LISTNODE *LISTNODEPTR;

void insert(LISTNODEPTR *, char);
char del(LISTNODEPTR *, char);
int isEmpty(LISTNODEPTR);
void printList(LISTNODEPTR);
void instructions(void);


void main(void){
	LISTNODEPTR startPtr = NULL;
	int choice;
	char item;
	instructions();   /* display the menu */
	printf("? ");
	scanf("%d", &choice);
	while(choice !=3){
		switch(choice){
			case 1: printf("Enter a character: ");
    	        scanf("\n%c", &item);
    	    	insert(&startPtr, item);
    	        printList(startPtr);
    	        break;
    		case 2:
    			if (!isEmpty(startPtr)) { /*is Empty가 0이 아니면 동작*/ /*구조체가 있으면 동작*/
        			printf("Enter character to be deleted: ");
        			scanf("\n%c", &item);
        			if (del(&startPtr, item)){
           				printf("%c deleted.\n", item);
        				printList(startPtr);
        			}
        			else printf("%c not found.\n\n", item);
    				}
    			else printf("List is empty.\n\n");
    		break;
    		default:
    			printf("Invalid choice.\n\n");
    		instructions();
    		break;
    	}
	printf("? ");
	scanf("%d", &choice);
	}
	printf("End of run.\n");
}


void instructions(void){   /* Print the instructions */
   	printf("Enter your choice:\n");
    printf(" 1 to insert an element into the list.\n");
    printf(" 2 to delete an element from the list.\n");
    printf(" 3 to end.\n");
}


int isEmpty(LISTNODEPTR sPtr){ /* 구조체의 유무 판단 */
   	return sPtr == NULL;
}

 
 void insert(LISTNODEPTR *sPtr, char value){ /* 정렬된 순서로 리스트에 새로운 값 삽입 */
  	LISTNODEPTR newPtr, previousPtr, currentPtr;

	newPtr = (LISTNODE *)malloc(sizeof(LISTNODE));
  	if (newPtr !=NULL) {  /*is space available */
     	newPtr -> data = value;
     	newPtr -> nextPtr = NULL;
     	previousPtr = NULL;
     	currentPtr = *sPtr;
     	while (currentPtr != NULL && value > currentPtr -> data) {
           	previousPtr= currentPtr;
           	currentPtr = currentPtr -> nextPtr;
     	}
    	if (previousPtr == NULL) {
       		newPtr -> nextPtr = *sPtr;
    		*sPtr = newPtr;
    	}else{ 
			previousPtr -> nextPtr = newPtr;
        	newPtr -> nextPtr = currentPtr;
    	} 
  	}else printf("%c not inserted.", value);
  		printf(" No memory available.\n");
}


char del(LISTNODEPTR *sPtr, char value){   /* 리스트 원소 제거 */
	LISTNODEPTR previousPtr, currentPtr, tempPtr;
	if(value == (*sPtr) -> data) { /*첫번째 구조체의 value에 내가 삭제하고 싶은 값이 있는가*/
    	tempPtr = *sPtr;
    	*sPtr = (*sPtr) -> nextPtr; 
    	free(tempPtr);  
		return value; 
	}else{ /*아닌 경우*/
   		previousPtr = *sPtr;
   		currentPtr = (*sPtr) -> nextPtr;
   		while (currentPtr != NULL && currentPtr -> data != value) { /* value값을 찾을때까지 계속 찾음 */
        	previousPtr = currentPtr;
        	currentPtr = currentPtr -> nextPtr;
   		}
   		if (currentPtr != NULL) {
    		tempPtr = currentPtr;
    		previousPtr->nextPtr = currentPtr->nextPtr;
    		free(tempPtr);  
			return value;
   		}
  	}
 	return '\0';
}


void printList (LISTNODEPTR currentPtr){   /* 리스트 출력 */
   	if (currentPtr == NULL)
      	printf("List is empty :\n\n");
   	else {
    	printf("The list is:\n");
      	while (currentPtr != NULL) {
        	printf("%c ==> ", currentPtr -> data);
        	currentPtr = currentPtr -> nextPtr;
      	}
      	printf("NULL\n\n");
   	}
}
