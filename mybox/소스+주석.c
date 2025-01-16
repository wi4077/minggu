#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list {
	char name[10];
	struct list *next;
} table[13]; //�ؽ� ���̺�

typedef struct list LIST;

void hashtable(); //�ؽ����̺� �ۼ� �Լ� ����
void Out_put(); //�ؽ����̺� ��� �Լ� ����
void hash_search(); //�ؽ����̺� �˻� �Լ� ����
int division_method(char *); //division_method ��� �Լ� ����
LIST *galloc(); //�����޸��Ҵ�� �뷮�� ������ ��ó�ϱ� ���� �Լ� ����

void main() {
	hashtable(); //�ؽ����̺� �Լ� ȣ��
	Out_put(); //�ؽ����̺� ��� �Լ� ȣ��
	hash_search(); //�ؽ����̺� �˻� �Լ� ȣ��
}

/* �ؽ����̺� �ۼ� �Լ� */
void hashtable() { 
	FILE *f; //����������
	char name[20];
	int key; //division method�� ��� ��(index)
	LIST *data, *p,*collision;

	f = fopen("E:\\�б�\\�ؽ�\\ConsoleApplication1\\names.txt","r"); //���Ͽ���

	while (fscanf(f, "%s", name) != EOF) { //������ �� ������ �ݺ�
		key = division_method(name); //key�� index�� ���� 
		data = &table[key]; //�迭�ε����� �ּ� 
		//collision �κ�
		if (data->name[0] == '\0') { //collision �߻����Ѱ��
			strcpy(data->name, name); //�� �濡 �� ���� data�� ���� 
			data->next = NULL; 
		}
		else { //collision �߻���
			collision = galloc(); //���������� �Ҵ� 
			p = data; //p�� �ε��� �ּҸ� ���� 

			while (p->next != NULL) //���� ���������� �ݺ� 
				p = p->next; //p�� �������� ����Ŵ 

			p->next = collision; //������ ���� 
		
			strcpy(collision->name, name); //collision ����ü�� name�濡 �̸� ���� 
			collision->next = NULL; // collision ����ü�� next�濡 �� �Է� 
		}
	}
	fclose(f); //���� �ݱ�
}

/* division method ��� �Լ� */
int division_method(char *name) {
	int hash_index = 0; 

	while(*name!=NULL) // ���ڿ��� ������ ������ �ݺ�
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
	LIST *p; //����ü�� ������ 
	int i;

	for (i = 0; i<13; i++) { //�ؽ����̺��� ũ�⸸ŭ �ݺ�
		printf("%2d : ", i);
		p = &table[i]; //p�� ���̺��� �ּҸ� ���� 

		for (p->name; p != NULL; p = p->next) { //���̺��� ù��° �ּҺ��� ���� ���������� ��ĭ�� �Űܰ� 
			printf("%s", p->name); // �̸���� 

			  if(p->next != NULL) //����� ����ü�� ������ 
				  printf("->");
		}
		printf("->NULL\n"); 
	}
}

/* �ؽ����̺� �˻� �Լ� */
void hash_search() { //��ã������ ��� ã�Ҵ���, ���° �ּҿ��� ã�Ҵ��� 
	LIST *p;
	char searchName[11]; //�˻��� �̸��� ��� �迭 
	int searchNameKey; //�˻��� �̸��� division�� 
	int count;

	while (strcmp(searchName, "$") != 0) { //$�� �Է¹��������� 
		count = 1;

		printf("\n�˻��� �ڷḦ �Է��ϼ���, ���Ḧ ���Ͻø� $�� ��������.\n");
		printf("�˻��� �ڷ� : ");
		scanf("%s", searchName);

		if (searchName[0] == '$') { //$�� �ԷµǸ� break 
			printf("�˻��� ����Ǿ����ϴ�.\n");
			break;
		}

		searchNameKey = division_method(searchName); //division method�� key�� ���
		p = &table[searchNameKey]; 
		for (p->name; p != NULL; p = p->next) { // p�� ����Ű�� ����ü�� name�� ���� �ɶ����� �����͸� �ű�� ���ƶ� 
			if (strcmp(p->name, searchName) == 0) { //p�� ����Ű�� ����ü�� name�� �Էµ� �̸��� ������ 
				printf(" %s (��)�� %d�� �ּҿ��� %d������ ã�ҽ��ϴ�.\n", searchName,searchNameKey, count);
				break;
			}
			else
				count++; //���� ������ �˻� �� ������ ī��Ʈ ���� 
		}
		if ( p == NULL) //�˻��� ������ �ߴµ� ������ ���� ���  
			printf("%d�� �ּҿ��� %d�� �˻��� ��� %s (��)�� ���� ���� �ʽ��ϴ�. \n",searchNameKey, count, searchName);
	}
}
