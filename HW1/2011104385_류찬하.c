#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	char* value;
	struct _node* next;
}node;

typedef node* nptr;

typedef struct _list
{
	int count;
	nptr head;
}list;

void init(list* lptr);
void insert(list* lptr, char* value, int position);
void search(list* lptr, char* value);
void print_list(list* lptr);

int main()
{
	list* mylist=(list*)malloc(sizeof(list));
	init(mylist);
	FILE* f = fopen("test.txt","r");
	char tmp[50];

	if (f == NULL)
	{
	          printf("스트림 생성시 오류발생\n");
	          return 1;
	}
	else
	{
		printf("파일 열기 성공\n");
	}

	while(1)
	{
		if (feof(f) == 0){
			fscanf(f, "%s", tmp);
			//printf("%s\n",tmp);
			insert(mylist, tmp, (mylist->count)+1);
		}
		else break;
	}

	fclose(f);
	print_list(mylist);

	while(1)
	{
		printf("검색할 단어를 입력하세요. (종료:0) : ");
		scanf("%s",tmp);
		if (strcmp(tmp,"0"))
			search(mylist, tmp);
		else break;
	}
	return 0;
}

void init(list* lptr)
{
	lptr -> count = 0;
	lptr -> head = NULL;
}

void insert(list* lptr, char* value, int position)
{
	if(position < 1 || position > (lptr -> count)+1)
	{
		printf("위치 범위 에러\n");
		return;
	}
	nptr new_nptr = (node*)malloc(sizeof(node));
	char* new_value = (char*)malloc(sizeof(char)*strlen(value));
	//free(new_nptr -> value);
	new_nptr -> value = strcpy(new_value,value);
	free(value);

	if(position == 1)
	{
		new_nptr->next = lptr->head;
		lptr->head = new_nptr;
	}
	else
	{
		nptr tmp = lptr->head;
		int i;
		for (i=1;i<position-1;i++)
		{
			tmp=tmp->next;
		}
		new_nptr->next = tmp->next;
		tmp->next=new_nptr;
	}
	lptr->count++;
}

void search(list* lptr, char* value)
{
	nptr tmp = lptr->head;
	int i=1, cnt=0;
	printf("%s은(는) ",value);
	while(tmp != NULL)
	{
		if(!strcmp(value,tmp->value))
			{
				cnt++;
				if (cnt == 1)
				{
					printf("list의 %d번째",i);
				}
				else
				{
					printf(", %d번째",i);
				}
			}
		i++;
		tmp = tmp->next;
	}

	if(cnt == 0)
	{
		printf("list에 존재하지 않습니다.\n",value);
	}
	else
	{
		printf("에 존재하며, %d개 존재합니다.\n",cnt);
	}
}

void print_list(list* lptr)
{
	nptr tmp = lptr -> head;
	printf("list 값 : ");
	while(tmp!=NULL)
	{
		printf("%s ", tmp -> value);
		tmp = tmp -> next;
	}
	printf("\n");
	printf("list에 %d개의 값이(가) 있습니다.\n", lptr->count);
}
