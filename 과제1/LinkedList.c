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
int search(list* lptr, char* value);
void print_list(list* lptr);

int main()
{
	list* mylist=(list*)malloc(sizeof(list));
	init(mylist);
	FILE* f = fopen("test.txt","r");
	char tmp[50];

	if (f == NULL)
	{
	          printf("��Ʈ�� ������ �����߻�\n");
	          return 1;
	}
	else
	{
		printf("���� ���� ����\n");
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
		printf("�˻��� �ܾ �Է��ϼ���. (����:0) : ");
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
		printf("��ġ ���� ����\n");
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

int search(list* lptr, char* value)
{
	nptr tmp = lptr->head;
	int i=1;
	while(tmp != NULL)
	{
		if(!strcmp(value,tmp->value)) break;
		i++;
		tmp = tmp->next;
	}
	if(i>lptr->count)
	{
		printf("%s��(��) �������� �ʽ��ϴ�.\n",value);
		return 0;
	}
	else
	{
		printf("%s��(��) list�� %d��°�� �����մϴ�.\n",value,i);
		return i;
	}
}

void print_list(list* lptr)
{
	nptr tmp = lptr -> head;
	printf("list �� : ");
	while(tmp!=NULL)
	{
		printf("%s ", tmp -> value);
		tmp = tmp -> next;
	}
	printf("\n");
	printf("list�� %d���� ����(��) �ֽ��ϴ�.\n", lptr->count);
}
