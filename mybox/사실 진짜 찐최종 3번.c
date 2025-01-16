#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list {
	char name[10];
	struct list *next;
} table[13]; /*해시 테이블*/

typedef struct list LIST;

void hashtable(); /*해시테이블 작성 함수 선언*/
void Out_put(); /*해시테이블 출력 함수 선언*/
void hash_search(); /*해시테이블 검색 함수 선언*/
int division_method(char *); /*division_method 계산 함수 선언*/
void collision_solve(LIST *, LIST *);
LIST *galloc(); /*동적메모리할당시 용량이 없을때 대처하기 위한 함수 선언*/

void main() {
	hashtable(); /*해시테이블 함수 호출*/
	printf("1");
	Out_put(); /*해시테이블 출력 함수 호출*/
	hash_search(); /*해시테이블 검색 함수 호출*/
}


/* 해시테이블 작성 함수 */
void hashtable() { 
	FILE *f; /*파일포인터*/
	char name[20];
	int key, count; /*division method의 결과 값(index)*/
	LIST *data, *p,*collision;
	printf("1");
	f = fopen("F:\\학교\\C언어 기말고사\\names.txt","r"); /*파일열기*/

	while (fscanf(f, "%s", name) != EOF) { /*파일의 끝 전까지 반복*/
		
		key = division_method(name); /*key는 index를 가짐 */
		data = &table[key]; /*배열인덱스의 주소 */
		/*collision 부분*/
		if (data->name == '\0') { /*collision 발생안한경우*/
			strcpy(data->name, name); /*앞 방에 뒷 방의 data를 복사 */
			data->next = NULL; 
		}
		else { /*collision 발생시*/
			collision = galloc(); /*동적기억장소 할당 */
			strcpy(collision->name, name);
			collision_solve(collision, data);
		
		}
	}
	fclose(f); //파일 닫기
}

/* division method 계산 함수 */
int division_method(char *name) {
	int hash_index = 0; 

	while(*name != NULL) /* 문자열이 끝나기 전까지 반복*/
		hash_index += *name++;
	return (-1)*hash_index%13;
}

/* 동적메모리할당(malloc)시 용량이 없을때 대처하기 위한 함수 */
LIST *galloc() {
	LIST *p;

	if ((p = (LIST *)malloc(sizeof(LIST))) == NULL) {
		printf("allocation error");
		exit(0);
	}

	return p;
}

/* 해시테이블 출력 함수 */
void Out_put() {
	LIST *p; /*구조체형 포인터 */
	int i;

	for (i = 0; i<13; i++) { /*해시테이블의 크기만큼 반복*/
		printf("%2d : ", i);
		p = &table[i]; /*p는 테이블의 주소를 가짐 */

		for (p->next->name; p->next != NULL; p = p->next) /*테이블의 첫번째 주소부터 널을 만날때까지 다음 인덱스로 */
			printf(" %s ->", p->next->name); /* 이름출력 */
		printf(" NULL\n"); 
	}
	printf("\n");
}

void collision_solve(LIST * collision, LIST *head){
	LIST *prev, *post; /*정렬을 위해 따라가는 포인터 (앞, 뒤)*/ 
	prev = post = head; 
	while (strcmp (post->name, collision->name) <= 0)  { /*삽입하려는 이름이 크면*/
		prev = post;
		post = post->next;
		if (post == NULL) 
			break;
	}
	
	if ( post == head)  { /*맨 앞에 삽입하는 경우*/
		collision->next = post;
		head = collision;
	}
	else if (post == NULL) { /*맨 뒤에 삽입하는 경우*/
		collision->next = NULL;
		prev->next = collision;
	}
	collision->next = post; /*while 빠져나오면 포인터 연결*/
	prev->next = collision; 

	
}
/* 해시테이블 검색 함수 */
void hash_search() { /*못찾았을때 몇번 찾았는지, 몇번째 주소에서 찾았는지*/ 
	LIST *p;
	char searchName[11]; /*검색할 이름을 담는 배열 */
	int searchNameKey; /*검색할 이름의 division값 */
	int count;

	do{ /*$를 입력받을때까지 */
		count = 0;

		printf("\n검색할 자료를 입력하세요, 종료를 원하시면 $를 누르세요.\n");
		printf("검색할 자료 : ");
		scanf("%s", searchName);

		if (searchName[0] == '$') { /*$가 입력되면 break */
			printf("검색이 종료되었습니다.\n");
			break;
		}

		searchNameKey = division_method(searchName); /*division method로 key값 얻기*/
		p = &table[searchNameKey]; 
		for (p->name; strcmp(p->name, searchName)!=1; p = p->next) { /* p가 가리키는 구조체의 name이 널이 될때까지 포인터를 다음 인덱스로*/
			if (strcmp(p->name, searchName) == 0) { /*p가 가리키는 구조체의 name과 파일에서 불러온 이름이 같으면 */
				printf(" %s (은)는 %d번 주소에서 ",searchName,searchNameKey);
				printf("%d번만에 찾았습니다.\n",  count);
				break;
			}
				count++; //같을 때까지 검색 할 때마다 카운트 증가 
		}
		if ( strcmp(p->name, searchName) == 1){ //검색을 끝까지 했는데 나오지 않은 경우  
			printf("%d번 주소에서 %d번 검색한 결과 ",searchNameKey, count);
			printf("%s (은)는 존재 하지 않습니다. \n", searchName);
		}
	}while (strcmp(searchName, "$") != 0);
}
