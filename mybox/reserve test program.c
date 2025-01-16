#include <stdio.h>
#include <stdlib.h>

struct link {
	char data[10];
	struct link *nextptr;
};
typedef struct link LINK;
typedef LINK *LINKPTR;
	LINKPTR headptr;

void linklist(void); /*링크드 리스트 만들어 주는 함수*/
LINKPTR galloc(void); /*동적 할당 함수*/
void reverse(void); /*역 링크드 리스트 만들어 주는 함수*/
void print_linklist(void); /*링크드 리스트 출력시키는 함수*/

void main(){
	linklist();
	print_linklist();
	reverse();
	print_linklist();
}

void linklist(void){ /* 링크드 리스트를 만듭니다.*/
	LINKPTR newptr, currentptr;
	char temp[10] = {0,}; /*입력 받을 */
	printf("데이터를 입력하세요. 종료하려면 stop을 입력하세요.\n");
	scanf("%s",&temp);
	fflush(stdin); 
	newptr = galloc();
	strcpy(newptr->data,temp); /*구조체의 data에 알파벳 하나씩 넣어줍니다.*/
	newptr->nextptr = NULL; /*구조체의 nextptr에 널문자*/
	headptr = newptr; /*헤더 포인터(고정)는 새로 만들어진 구조체를 가리킵니다.*/
	currentptr = newptr; /*현재의 포인터는 새로 만들어진 구조체를 가리킵니다.*/
	
	while(1){
		char temp[10] = {0,};
		newptr = galloc();
		printf("데이터를 입력하세요. 종료하려면 stop을 입력하세요.\n");
		scanf("%s",&temp);
		fflush(stdin);
		strcpy(newptr->data,temp); /*입력한 데이터 복사*/
		if(strcmp(newptr->data, "stop") == 0) /*입력한 데이터가 stop이면*/
			break;
		newptr->nextptr = NULL;
		currentptr->nextptr = newptr; /*현재의 포인터의 nextptr이 새로 만들어진 구조체를 가리키게 합니다.*/
		currentptr = newptr; /*현재의 포인터는 새로 만들어진 구조체를 가리킵니다.*/
	}
}

LINKPTR galloc(void){ /*동적 기억 장소 할당*/
	LINKPTR p;
	if((p = (LINK *)malloc(sizeof(LINK))) == NULL){
		exit(0);
	}
	return p;
}




void reverse(void){ /*링크드 리스트 반대로 연결시켜주는 함수*/
	LINKPTR prev, current, next;
	prev = NULL;
	current = next = headptr;
	while(next->nextptr != 0){ /*링크드 리스트 마지막이면 빠져나옴*/
		next = next->nextptr; /*next포인터는 연결된 다음 구조체를 가리킵니다.*/
		current->nextptr = prev; /*current포인터가 가리키는 구조체의 nextptr은 prev포인터가 가리키는 구조체와 연결됩니다.*/
		prev = current; /*prev포인터는 current포인터로 옮겨지게 되고*/
		current = next; /*current포인터는 next포인터로 옮겨집니다.*/
	}
	current->nextptr = prev; /*current포인터의 nextptr은 prev포인터가 가리키는 구조체*/
	headptr = next; /*헤더 포인터는 맨 마지막 구조체를 가리킵니다.*/
}



void print_linklist(void){
	LINKPTR ptr;
	ptr = headptr;
	printf("headptr ->");
	while(ptr != NULL){
		printf("%s ->",ptr->data);
		ptr = ptr->nextptr;
	}
	printf("NULL\n\n");
}

