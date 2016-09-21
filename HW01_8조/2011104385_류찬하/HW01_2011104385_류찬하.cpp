#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _node //��� ����ü ����
{
	char* value; //��� ����
	struct _node* next; //���� ��� �ּ�
}node;

typedef node* nptr; //��� ������ ����

typedef struct _list //����Ʈ ����ü ����
{
	int count; //��� ����
	nptr head; //ù��° ���
}list;

void init(list* lptr);  //���� �ʱ�ȭ �Լ�
void insert(list* lptr, char* value, int position); //��ġ�� ��� ����
void search(list* lptr, char* value); //����Ʈ���� Ư���� �˻�
void print_list(list* lptr); //����Ʈ ���� ǥ��
int check(int i, char* value); //�ѱ�, ����, ���� üũ (�ѿ����ڰ� �ƴ� �ÿ� true ����)

int main()
{
	char file[100]; //���ϸ� ����� char �迭
	list* mylist=(list*)malloc(sizeof(list)); //����Ʈ ����
	init(mylist); //����Ʈ �ʱ�ȭ

	printf("���� ��θ� �Է��ϼ���. : ");
	scanf("%s", file); //���� ��ġ �Է�
	FILE *f = fopen(file,"r"); //���� ����
	char tmp[50]; //���� �� ���ڿ� ��ĵ�� �ӽ����� �迭

	if (f == NULL) //���� ���� üũ
	{
  	printf("��Ʈ�� ������ �����߻�\n");
    return 1; //������ �״�� ����
	}
	else
	{
		printf("���� ���� ����\n");
	}

	while(1)
	{
		if (feof(f) == 0) //������ ������ üũ
		{
			fscanf(f, "%s", tmp); //���� ���� ��ĵ
			//printf("%s\n",tmp);
			int start=0, end=0; //Ư������ ���ſ�, ���۰� �� ��ġ
			for(int i=0; i<strlen(tmp); i++) //��ĵ�� ���ڿ� üũ
			{
				if (check(i, tmp)) //�ѿ����� ���� �����Ͻ� ���ڸ��� �ձ��� ���
					end = i-1;
				if (i == strlen(tmp)-1) //������ �����Ͻ�
				{
					end = strlen(tmp); //���ڿ��� ���� �������� ������ ����
					if (check(i, tmp)) // �������� �ѿ����� ���� �����Ͻ� �װ� ����
						end-=2;
				}
				if (start != end) //ó���� ������ �ٸ��ٸ� ������ ���ߴٴ� ���̰� Ư�����ڰ� �����߰ų� ���ڿ��� ��
				{
					char tmp2[50]; //�ӽ� ����� �迭
					memcpy(tmp2,tmp+start,end-start+1); //Ư�����ڰ� ���� �κ��� �ӽ������ �迭�� ����
					insert(mylist, tmp2, (mylist->count)+1); //����Ʈ ����
					end+=2; //���� +2, Ư��������ġ�� �ǳʶٱ� ����
					start = end; //���۰� �ʱ�ȭ
				}
			}
		}
		else break;
	}

	fclose(f); //���� ����
	print_list(mylist); //����Ʈ ���尪 Ȯ�ο�

	while(1)
	{
		printf("�˻��� �ܾ �Է��ϼ���. (����:0) : "); //�˻� �ܾ� �Է� 0�Է½� ����
		scanf("%s",tmp);
		if (strcmp(tmp,"0")) //�Էµ� ���ڰ� 0���� Ȯ��
			search(mylist, tmp); //����Ʈ���� tmp�� �˻�
		else break;
	}
	return 0;
}

void init(list* lptr)
{
	lptr -> count = 0; //�ʱ�ȭ(���� 0��)
	lptr -> head = NULL;//�ʱ�ȭ(������ NULL��)
}

void insert(list* lptr, char* value, int position)
{
	if(position < 1 || position > (lptr -> count)+1) //��ġ�� �����̰ų� ������������ ū���Ͻ� �����߻�
	{
		printf("��ġ ���� ����\n");
		return;
	}
	nptr new_nptr = (node*)malloc(sizeof(node)); //���ο� ��� ������ ����
	char* new_value = (char*)malloc(sizeof(char)*strlen(value)); //�Է¹��� ���ڿ���ŭ ���ο� ���ڿ� ����
	new_nptr -> value = strcpy(new_value,value); //�� �Է�

	if(position == 1) //ù����Ͻ�
	{
		new_nptr->next = lptr->head;
		lptr->head = new_nptr;
	}
	else
	{
		nptr tmp = lptr->head;
		int i;
		for (i=1;i<position-1;i++) //������ ��� �ּ� ã�� ���� �۾�
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
	printf("%s��(��) ",value);
	while(tmp != NULL)
	{
		if(!strcmp(value,tmp->value))
			{
				cnt++; //���� ���� ī����
				if (cnt == 1)
				{
					printf("list�� %d��°",i); //��ġ ���
				}
				else
				{
					printf(", %d��°",i);
				}
			}
		i++;
		tmp = tmp->next;
	}

	if(cnt == 0)
	{
		printf("list�� �������� �ʽ��ϴ�.\n");
	}
	else
	{
		printf("�� �����ϸ�, %d�� �����մϴ�.\n",cnt);
	}
}

void print_list(list* lptr)
{
	nptr tmp = lptr -> head;
	printf("list �� : ");
	while(tmp!=NULL) //��� ����Ʈ�� ���
	{
		printf("%s ", tmp -> value);
		tmp = tmp -> next;
	}
	printf("\n");
	printf("list�� %d���� ����(��) �ֽ��ϴ�.\n", lptr->count);
}

int check(int i, char* value)
{
	if(value[i]>=33 && value[i] <= 47) return 1; //Ư������
	if(value[i]>=58 && value[i] <= 64) return 1; //Ư������
	if(value[i]>=91 && value[i] <= 96) return 1; //Ư������
	if(value[i]>=123 && value[i] <= 126) return 1; //Ư������
	if(value[i]>=48 && value[i] <= 57) return 0; //���� �ҹ���
	if(value[i]>=65 && value[i] <= 95) return 0; //���� �빮��
	if(value[i]>=97 && value[i] <= 122) return 0; //����
	if(value[i]>=12592 || value[i] <= 12687) return 0; //�ѱ�
	return 1;
}
