#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list {
	char name[10];
	struct list *next;
} table[13]; /*�ؽ� ���̺�*/

typedef struct list LIST;

void hashtable(); /*�ؽ����̺� �ۼ� �Լ� ����*/
void Out_put(); /*�ؽ����̺� ��� �Լ� ����*/
void hash_search(); /*�ؽ����̺� �˻� �Լ� ����*/
int division_method(char *); /*division_method ��� �Լ� ����*/
void collision_solve(LIST *, LIST *);
LIST *galloc(); /*�����޸��Ҵ�� �뷮�� ������ ��ó�ϱ� ���� �Լ� ����*/

void main() {
	hashtable(); /*�ؽ����̺� �Լ� ȣ��*/
	printf("1");
	Out_put(); /*�ؽ����̺� ��� �Լ� ȣ��*/
	hash_search(); /*�ؽ����̺� �˻� �Լ� ȣ��*/
}


/* �ؽ����̺� �ۼ� �Լ� */
void hashtable() { 
	FILE *f; /*����������*/
	char name[20];
	int key, count; /*division method�� ��� ��(index)*/
	LIST *data, *p,*collision;
	printf("1");
	f = fopen("F:\\�б�\\C��� �⸻���\\names.txt","r"); /*���Ͽ���*/

	while (fscanf(f, "%s", name) != EOF) { /*������ �� ������ �ݺ�*/
		
		key = division_method(name); /*key�� index�� ���� */
		data = &table[key]; /*�迭�ε����� �ּ� */
		/*collision �κ�*/
		if (data->name == '\0') { /*collision �߻����Ѱ��*/
			strcpy(data->name, name); /*�� �濡 �� ���� data�� ���� */
			data->next = NULL; 
		}
		else { /*collision �߻���*/
			collision = galloc(); /*���������� �Ҵ� */
			strcpy(collision->name, name);
			collision_solve(collision, data);
		
		}
	}
	fclose(f); //���� �ݱ�
}

/* division method ��� �Լ� */
int division_method(char *name) {
	int hash_index = 0; 

	while(*name != NULL) /* ���ڿ��� ������ ������ �ݺ�*/
		hash_index += *name++;
	return (-1)*hash_index%13;
}

/* �����޸��Ҵ�(malloc)�� �뷮�� ������ ��ó�ϱ� ���� �Լ� */
LIST *galloc() {
	LIST *p;

	if ((p = (LIST *)malloc(sizeof(LIST))) == NULL) {
		printf("allocation error");
		exit(0);
	}

	return p;
}

/* �ؽ����̺� ��� �Լ� */
void Out_put() {
	LIST *p; /*����ü�� ������ */
	int i;

	for (i = 0; i<13; i++) { /*�ؽ����̺��� ũ�⸸ŭ �ݺ�*/
		printf("%2d : ", i);
		p = &table[i]; /*p�� ���̺��� �ּҸ� ���� */

		for (p->next->name; p->next != NULL; p = p->next) /*���̺��� ù��° �ּҺ��� ���� ���������� ���� �ε����� */
			printf(" %s ->", p->next->name); /* �̸���� */
		printf(" NULL\n"); 
	}
	printf("\n");
}

void collision_solve(LIST * collision, LIST *head){
	LIST *prev, *post; /*������ ���� ���󰡴� ������ (��, ��)*/ 
	prev = post = head; 
	while (strcmp (post->name, collision->name) <= 0)  { /*�����Ϸ��� �̸��� ũ��*/
		prev = post;
		post = post->next;
		if (post == NULL) 
			break;
	}
	
	if ( post == head)  { /*�� �տ� �����ϴ� ���*/
		collision->next = post;
		head = collision;
	}
	else if (post == NULL) { /*�� �ڿ� �����ϴ� ���*/
		collision->next = NULL;
		prev->next = collision;
	}
	collision->next = post; /*while ���������� ������ ����*/
	prev->next = collision; 

	
}
/* �ؽ����̺� �˻� �Լ� */
void hash_search() { /*��ã������ ��� ã�Ҵ���, ���° �ּҿ��� ã�Ҵ���*/ 
	LIST *p;
	char searchName[11]; /*�˻��� �̸��� ��� �迭 */
	int searchNameKey; /*�˻��� �̸��� division�� */
	int count;

	do{ /*$�� �Է¹��������� */
		count = 0;

		printf("\n�˻��� �ڷḦ �Է��ϼ���, ���Ḧ ���Ͻø� $�� ��������.\n");
		printf("�˻��� �ڷ� : ");
		scanf("%s", searchName);

		if (searchName[0] == '$') { /*$�� �ԷµǸ� break */
			printf("�˻��� ����Ǿ����ϴ�.\n");
			break;
		}

		searchNameKey = division_method(searchName); /*division method�� key�� ���*/
		p = &table[searchNameKey]; 
		for (p->name; strcmp(p->name, searchName)!=1; p = p->next) { /* p�� ����Ű�� ����ü�� name�� ���� �ɶ����� �����͸� ���� �ε�����*/
			if (strcmp(p->name, searchName) == 0) { /*p�� ����Ű�� ����ü�� name�� ���Ͽ��� �ҷ��� �̸��� ������ */
				printf(" %s (��)�� %d�� �ּҿ��� ",searchName,searchNameKey);
				printf("%d������ ã�ҽ��ϴ�.\n",  count);
				break;
			}
				count++; //���� ������ �˻� �� ������ ī��Ʈ ���� 
		}
		if ( strcmp(p->name, searchName) == 1){ //�˻��� ������ �ߴµ� ������ ���� ���  
			printf("%d�� �ּҿ��� %d�� �˻��� ��� ",searchNameKey, count);
			printf("%s (��)�� ���� ���� �ʽ��ϴ�. \n", searchName);
		}
	}while (strcmp(searchName, "$") != 0);
}
