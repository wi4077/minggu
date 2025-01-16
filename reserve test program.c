#include <stdio.h>
#include <stdlib.h>

struct link {
	char data[10];
	struct link *nextptr;
};
typedef struct link LINK;
typedef LINK *LINKPTR;
	LINKPTR headptr;

void linklist(void); /*��ũ�� ����Ʈ ����� �ִ� �Լ�*/
LINKPTR galloc(void); /*���� �Ҵ� �Լ�*/
void reverse(void); /*�� ��ũ�� ����Ʈ ����� �ִ� �Լ�*/
void print_linklist(void); /*��ũ�� ����Ʈ ��½�Ű�� �Լ�*/

void main(){
	linklist();
	print_linklist();
	reverse();
	print_linklist();
}

void linklist(void){ /* ��ũ�� ����Ʈ�� ����ϴ�.*/
	LINKPTR newptr, currentptr;
	char temp[10] = {0,}; /*�Է� ���� */
	printf("�����͸� �Է��ϼ���. �����Ϸ��� stop�� �Է��ϼ���.\n");
	scanf("%s",&temp);
	fflush(stdin); 
	newptr = galloc();
	strcpy(newptr->data,temp); /*����ü�� data�� ���ĺ� �ϳ��� �־��ݴϴ�.*/
	newptr->nextptr = NULL; /*����ü�� nextptr�� �ι���*/
	headptr = newptr; /*��� ������(����)�� ���� ������� ����ü�� ����ŵ�ϴ�.*/
	currentptr = newptr; /*������ �����ʹ� ���� ������� ����ü�� ����ŵ�ϴ�.*/
	
	while(1){
		char temp[10] = {0,};
		newptr = galloc();
		printf("�����͸� �Է��ϼ���. �����Ϸ��� stop�� �Է��ϼ���.\n");
		scanf("%s",&temp);
		fflush(stdin);
		strcpy(newptr->data,temp); /*�Է��� ������ ����*/
		if(strcmp(newptr->data, "stop") == 0) /*�Է��� �����Ͱ� stop�̸�*/
			break;
		newptr->nextptr = NULL;
		currentptr->nextptr = newptr; /*������ �������� nextptr�� ���� ������� ����ü�� ����Ű�� �մϴ�.*/
		currentptr = newptr; /*������ �����ʹ� ���� ������� ����ü�� ����ŵ�ϴ�.*/
	}
}

LINKPTR galloc(void){ /*���� ��� ��� �Ҵ�*/
	LINKPTR p;
	if((p = (LINK *)malloc(sizeof(LINK))) == NULL){
		exit(0);
	}
	return p;
}




void reverse(void){ /*��ũ�� ����Ʈ �ݴ�� ��������ִ� �Լ�*/
	LINKPTR prev, current, next;
	prev = NULL;
	current = next = headptr;
	while(next->nextptr != 0){ /*��ũ�� ����Ʈ �������̸� ��������*/
		next = next->nextptr; /*next�����ʹ� ����� ���� ����ü�� ����ŵ�ϴ�.*/
		current->nextptr = prev; /*current�����Ͱ� ����Ű�� ����ü�� nextptr�� prev�����Ͱ� ����Ű�� ����ü�� ����˴ϴ�.*/
		prev = current; /*prev�����ʹ� current�����ͷ� �Ű����� �ǰ�*/
		current = next; /*current�����ʹ� next�����ͷ� �Ű����ϴ�.*/
	}
	current->nextptr = prev; /*current�������� nextptr�� prev�����Ͱ� ����Ű�� ����ü*/
	headptr = next; /*��� �����ʹ� �� ������ ����ü�� ����ŵ�ϴ�.*/
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

