#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef NULL
#define NULL   ((void *) 0)
#endif

typedef struct __node {
    char* data;
    struct __node* next;
} node;

typedef node* ndp;

typedef struct __list {
    int num;
    ndp head;
} list;

void init(list* lp);
void insert(list* lp, char* data, int position);
char search(list* lp, char* value);
void print_list(list* lp);

void init(list* lp){
	lp->num=0;
	lp->head=NULL;
}

void insert(list* lp, char* data, int position){
	if(position<1 || position>(lp->num)+1){
		printf("Position�� ������ ���\n");
		return;
	}
	ndp new_ndp=(node*)malloc(sizeof(node));
	new_ndp->data=data;
	if(position==1){
		new_ndp->next=lp->head;
		lp->head=new_ndp;
	}
	else{
		ndp tmp=lp->head;
		int i;
		for(i=1;i<position-1;i++){
			tmp=tmp->next;
		}
		new_ndp->next=tmp->next;
		tmp->next=new_ndp;
	}
	lp->num++;
}

char search(list* lp, char* data){
	ndp tmp = lp ->head;
	int i=1, j=0;
		printf("%s��(��) ",data);
		while(tmp != NULL){
			if(!strcmp(data,tmp->data)){
					j++;
					if (j == 1){
						printf("list�� %d��°",i);
					}else{
						printf(", %d��°",i);
					}
				}
			i++;
			tmp = tmp->next;
		}
}

void print_list(list* lp){
	ndp tmp=lp->head;
	printf("List value: ");
	while(tmp!=NULL){
		printf("%d",tmp->data);
		tmp=tmp->next;
	}
	printf("\n");
	printf("Total: %d��.\n ",lp->num);
}


int main() {
	list* mylist=(list*)malloc(sizeof(list));
	init(mylist);
	char filename[255];
	printf("���� ��ġ:");
	scanf("%s",filename);
	FILE* fp =fopen(filename,"r");
	char cmd[255];

	if(fp==NULL){
		printf("��ο���\n");
		return 0;
	}
	else{
		printf("����\n");
	}
	while(1){
		if(feof(fp)==0){
			fscanf(fp,"%d",cmd);
			insert(mylist,cmd,(mylist->num)+1);
		}else break;
	}
	fclose(fp);
	print_list(mylist);
	printf("�˻��� �ܾ� �Է�:");
	scanf("%s",cmd);
	search(mylist,cmd);
	print_list(mylist);
	return 0;

}

