#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _node //노드 구조체 정의
{
	char* value; //노드 내용
	struct _node* next; //다음 노드 주소
}node;

typedef node* nptr; //노드 포인터 정의

typedef struct _list //리스트 구조체 정의
{
	int count; //노드 갯수
	nptr head; //첫번째 노드
}list;

void init(list* lptr);  //리스 초기화 함수
void insert(list* lptr, char* value, int position); //위치에 노드 삽입
void search(list* lptr, char* value); //리스트에서 특정값 검색
void print_list(list* lptr); //리스트 내용 표시
int check(int i, char* value); //한글, 숫자, 영어 체크 (한영숫자가 아닐 시에 true 리턴)

int main()
{
	char file[100]; //파일명 저장용 char 배열
	list* mylist=(list*)malloc(sizeof(list)); //리스트 선언
	init(mylist); //리스트 초기화

	printf("파일 경로를 입력하세요. : ");
	scanf("%s", file); //파일 위치 입력
	FILE *f = fopen(file,"r"); //파일 오픈
	char tmp[50]; //파일 내 문자열 스캔용 임시저장 배열

	if (f == NULL) //파일 열림 체크
	{
  	printf("스트림 생성시 오류발생\n");
    return 1; //오류시 그대로 종료
	}
	else
	{
		printf("파일 열기 성공\n");
	}

	while(1)
	{
		if (feof(f) == 0) //파일의 끝인지 체크
		{
			fscanf(f, "%s", tmp); //파일 내용 스캔
			//printf("%s\n",tmp);
			int start=0, end=0; //특수문자 제거용, 시작과 끝 위치
			for(int i=0; i<strlen(tmp); i++) //스캔한 문자열 체크
			{
				if (check(i, tmp)) //한영숫자 외의 문자일시 그자리의 앞까지 사용
					end = i-1;
				if (i == strlen(tmp)-1) //마지막 문자일시
				{
					end = strlen(tmp); //문자열의 가장 마지막을 끝으로 지정
					if (check(i, tmp)) // 마지막이 한영숫자 외의 문자일시 그값 제외
						end-=2;
				}
				if (start != end) //처음과 끝값이 다르다면 끝값이 변했다는 것이고 특수문자가 등장했거나 문자열의 끝
				{
					char tmp2[50]; //임시 저장용 배열
					memcpy(tmp2,tmp+start,end-start+1); //특수문자가 없는 부분을 임시저장용 배열에 복사
					insert(mylist, tmp2, (mylist->count)+1); //리스트 삽입
					end+=2; //끝값 +2, 특수문자위치를 건너뛰기 위함
					start = end; //시작값 초기화
				}
			}
		}
		else break;
	}

	fclose(f); //파일 종료
	print_list(mylist); //리스트 저장값 확인용

	while(1)
	{
		printf("검색할 단어를 입력하세요. (종료:0) : "); //검색 단어 입력 0입력시 종료
		scanf("%s",tmp);
		if (strcmp(tmp,"0")) //입력된 문자가 0인지 확인
			search(mylist, tmp); //리스트에서 tmp값 검색
		else break;
	}
	return 0;
}

void init(list* lptr)
{
	lptr -> count = 0; //초기화(갯수 0개)
	lptr -> head = NULL;//초기화(포인터 NULL값)
}

void insert(list* lptr, char* value, int position)
{
	if(position < 1 || position > (lptr -> count)+1) //위치가 음수이거나 마지막값보다 큰곳일시 에러발생
	{
		printf("위치 범위 에러\n");
		return;
	}
	nptr new_nptr = (node*)malloc(sizeof(node)); //새로운 노드 포인터 선언
	char* new_value = (char*)malloc(sizeof(char)*strlen(value)); //입력받은 문자열만큼 새로운 문자열 생성
	new_nptr -> value = strcpy(new_value,value); //값 입력

	if(position == 1) //첫노드일시
	{
		new_nptr->next = lptr->head;
		lptr->head = new_nptr;
	}
	else
	{
		nptr tmp = lptr->head;
		int i;
		for (i=1;i<position-1;i++) //마지막 노드 주소 찾기 위한 작업
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
				cnt++; //등장 갯수 카운팅
				if (cnt == 1)
				{
					printf("list의 %d번째",i); //위치 출력
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
		printf("list에 존재하지 않습니다.\n");
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
	while(tmp!=NULL) //모든 리스트값 출력
	{
		printf("%s ", tmp -> value);
		tmp = tmp -> next;
	}
	printf("\n");
	printf("list에 %d개의 값이(가) 있습니다.\n", lptr->count);
}

int check(int i, char* value)
{
	if(value[i]>=33 && value[i] <= 47) return 1; //특수문자
	if(value[i]>=58 && value[i] <= 64) return 1; //특수문자
	if(value[i]>=91 && value[i] <= 96) return 1; //특수문자
	if(value[i]>=123 && value[i] <= 126) return 1; //특수문자
	if(value[i]>=48 && value[i] <= 57) return 0; //영어 소문자
	if(value[i]>=65 && value[i] <= 95) return 0; //영어 대문자
	if(value[i]>=97 && value[i] <= 122) return 0; //숫자
	if(value[i]>=12592 || value[i] <= 12687) return 0; //한글
	return 1;
}
