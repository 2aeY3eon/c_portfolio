#include <stdio.h>
#include <string.h>

typedef struct clas { 
	//int Grade[100][6];
	int **Grade;
	int stdCnt;
	int total;
	int delStdCnt;

} Class;

void FreeAll(Class * class_arr, int total_class);

void CreateClass(Class * class, int total_class);
void ClassMenu(int class_idx, Class * class);
void ClassInfo(int class_idx, Class * class);

void InsertGrade(int * Grade, int stdNum);
void DeleteGrade(int * Grade, int stdIdx, int * delStdCnt);
void PrintGrade(int **Grade, int stdCnt);

void RankMenu(Class * class_arr, int total_class);
void TotalRank(int * total_arr, int total_class);
void AverageTotal(int * total_arr, int total_class);

char Sub[5][5] = { "국어", "수학", "사회", "과학", "영어" };

int main()
{
	Class * class_arr = (Class*)malloc(sizeof(Class));
	int class_idx, sel;
	int total_class = 0;
	
	while(1) {
	
	puts("------ 메인 메뉴 ------");
	puts("[0] 종료");
	puts("[1] 반 생성");
	puts("[2] 반 선택");
	puts("[3] 반 순위");
	

	printf("입력: ");
	scanf("%d", &sel);

	switch(sel) {
	case 0:
		printf("프로그램을 종료합니다.\n");

		FreeAll(class_arr, total_class);
		exit();
		break;

	case 1:
		class_arr = (Class*)realloc(class_arr, sizeof(Class)*(total_class+1));
		CreateClass(&(class_arr[total_class]), total_class);
		total_class++;

		printf("%d반이 성공적으로 생성되었습니다. \n", total_class);
		break;

	case 2:
		if(total_class == 0) {
			puts("생성된 반이 없습니다 !");
			break;
		}

		for(int cnt=0; cnt<total_class; cnt++) {
			printf("[%d] %d반\n", cnt+1, cnt+1);
		}

		printf("select class: ");
		scanf("%d", &class_idx);

		if(class_idx<=0 || class_idx>total_class) {
			puts("존재하지 않는 반입니다!");
			break;
		}

		class_idx--;

		ClassMenu(class_idx, &(class_arr[class_idx]));
		break;

	case 3:
		RankMenu(class_arr, total_class);
		break;
	
	default:
		puts("잘못된 입력값입니다.");
		break;

	}
	}
	
	
}

void FreeAll(Class * class_arr, int total_class)
{
	for(int i=0; i<total_class; i++) {
		for(int j=0; j<class_arr[i].stdCnt; j++) {
			 free(class_arr[i].Grade[j]);
		}
		free(class_arr[i].Grade);
	}
	free(class_arr);
}

void CreateClass(Class * class, int total_class)
{
	class->Grade = (int**)malloc(sizeof(class->Grade));

	class->stdCnt = 0;
	class->total = 0;
	class->delStdCnt = 0;
}

void ClassMenu(int class_idx, Class * class)
{
	int sel, stdsel, temp;
	int sublen = sizeof(Sub)/(sizeof(char)*5);

	while(1) {

	printf("--------- %d반 ---------\n", class_idx+1);
	puts("[0] 뒤로 가기");
	puts("[1] 반 정보");
	puts("[2] 성적 등록");
	puts("[3] 성적 삭제");
	printf("입력: ");
	scanf("%d", &sel);

	switch(sel) {
	case 0:
		return;
	case 1:
		ClassInfo(class_idx, class);
		break;
		
	case 2:
		class->Grade = (int**)realloc(class->Grade, 6*sizeof(int)*(class->stdCnt+1)); 
		class->Grade[class->stdCnt] = (int*)malloc(6 * sizeof(int));

		InsertGrade(class->Grade[class->stdCnt], class->stdCnt); 

		class->stdCnt++;

		temp=0;
		for(int cnt=0; cnt<class->stdCnt; cnt++) {
			temp += class->Grade[cnt][5];
		}
		class->total = temp;


		PrintGrade(class->Grade, class->stdCnt);
		break; 

	case 3:
		printf("몇 번 학생의 성적을 삭제하시겠습니까? \n");
		printf("입력: ");
		scanf("%d", &stdsel);

		DeleteGrade(class->Grade[stdsel-1], stdsel, &(class->delStdCnt));


		temp=0;
		for(int cnt=0; cnt<class->stdCnt; cnt++) {
			temp += class->Grade[cnt][5];
		}
		class->total = temp;

		PrintGrade(class->Grade, class->stdCnt);
		break;
	default:
		printf("잘못된 입력값입니다. \n");
		break;
	}

	}
}

void ClassInfo(int class_idx, Class * class)
{
	printf("----- %d반의 정보 ------\n", class_idx+1);
	printf("학생 수: %d명\n", class->stdCnt - class->delStdCnt);
	printf("반 학생들의 총 점수 합계: %d\n", class->total);
}

void InsertGrade(int * Grade, int stdIdx)
{
	int sublen = sizeof(Sub)/(sizeof(char)*5);
	int total=0;

	Grade[5]=0;

	for(int cnt=0; cnt<sublen;) {
		printf("학생 %d의 [%s] 점수를 입력하세요: ", stdIdx+1, (Sub)[cnt]);
		scanf("%d", &Grade[cnt]);

		if(Grade[cnt] >= 0 && Grade[cnt] <= 100) {
			Grade[5] += Grade[cnt];
			cnt++;
		}
		else {
			printf("\n점수를 다시 입력해주십시오\n");
		}
	}
}

void DeleteGrade(int * Grade, int stdIdx, int * delStdCnt)
{
	int sublen = sizeof(Sub)/(sizeof(char)*5);
	char sel;
	
	getchar();
	printf("정말 [학생%d]의 성적을 삭제하시겠습니까? [Y/N] \n", stdIdx);
	printf("입력: ");
	scanf("%c", &sel);
	
	switch(sel) {
	case 'Y':
	case 'y':

		Grade[0] = -1;
		Grade[5] = 0;

		(*delStdCnt)++;

		break;
	case 'N':
	case 'n':
		break;
	defualt:
		break;
	}
}

void PrintGrade(int **Grade, int stdCnt)
{
	int sublen = sizeof(Sub)/(sizeof(char)*5);

	printf("학생/과목│");
	for(int cnt=0; cnt<sublen; cnt++) {
		printf("  %s│", (Sub)[cnt]);
	}
	printf("   평균 │\n");
	printf("─────────┼──────┼──────┼──────┼──────┼──────┼────────┤\n");

	for(int i=0; i<stdCnt; i++) {
		if(Grade[i][0]!=-1) {
			//total[i] = 0;
			printf("학생%-3d  │", i+1);
			for(int j=0; j<sublen; j++) {
				printf(" %3d점│", Grade[i][j]);
				//total[i] += Grade[i][j];
			}

			printf(" %5.1f점│\n", (float)Grade[i][5] / 5);
			printf("─────────┼──────┼──────┼──────┼──────┼──────┼────────┤\n");
		}
		else {
			continue;
		}
	}
}

void RankMenu(Class * class_arr, int total_class)
{
	int sel;

	while(1) {

	puts("------- 반 순위 -------");
	puts("[0] 돌아가기");
	puts("[1] 총점 순위");
	puts("[2] 평균 순위");
	
	printf("입력: ");
	scanf("%d", &sel);

	switch(sel) {
	case 0:
		return;
		break;
	case 1:
		int * total_arr = (int*)malloc(sizeof(int) * total_class);

		for(int idx=0; idx<total_class; idx++) {
			total_arr[idx] = class_arr[idx].total;
		}

		TotalRank(total_arr, total_class);
		free(total_arr);

		break;
	case 2:
		int * average_arr = (int*)malloc(sizeof(int) * total_class);

		for(int idx=0; idx<total_class; idx++) {
			if(class_arr[idx].stdCnt != 0) {
				average_arr[idx] = class_arr[idx].total/class_arr[idx].stdCnt;
			} else {
				average_arr[idx] = 0;
			}
		}

		AverageTotal(average_arr, total_class);
		free(average_arr);

		break;
	default:
		puts("잘못된 입력값입니다.");
		break;
	
	}
	}
}	

void TotalRank(int * total_arr, int total_class)
{
	int temp;
	int * cl_num_arr = (int*)malloc(sizeof(int) * total_class);

	for(int i=0; i<total_class; i++) {	
		cl_num_arr[i] = i+1;
	}

	printf("%d %d %d\n", total_class, total_arr[0], cl_num_arr[0]);
	printf("%d %d %d\n", total_class, total_arr[1], cl_num_arr[1]);

	for(int i=0; i<total_class-1; i++) {
		for(int j=0; j<total_class-1-i; j++) {
			if(total_arr[j] < total_arr[j+1]) {
				temp = total_arr[j+1];
				total_arr[j+1] = total_arr[j];
				total_arr[j] = temp;
			
				temp = cl_num_arr[j+1];
				cl_num_arr[j+1] = cl_num_arr[j];
				cl_num_arr[j] = temp;
			}
		}
	}

	puts("------ 총점 순위 ------");
	for(int idx=0; idx<total_class; idx++) {
		printf("%d등 : %d반 ( 총점 %d점 )\n", idx+1, cl_num_arr[idx], total_arr[idx]);
	}
	puts("-----------------------");

	free(cl_num_arr);


}

void AverageTotal(int * average_arr, int total_class)
{
	int temp;
	int * cl_num_arr = (int*)malloc(sizeof(int) * total_class);

	for(int i=0; i<total_class; i++) {
		cl_num_arr[i] = i+1;
	}

	for(int i=0; i<total_class-1; i++) {
		for(int j=0; j<total_class-1-i; j++) {
			if(average_arr[j] < average_arr[j+1]) {
				temp = average_arr[j+1];
				average_arr[j+1] = average_arr[j];
				average_arr[j] = temp;
			
				temp = cl_num_arr[j+1];
				cl_num_arr[j+1] = cl_num_arr[j];
				cl_num_arr[j] = temp;
			}
		}
	}

	puts("------ 평균 순위 ------");
	for(int idx=0; idx<total_class; idx++) {
		printf("%d등 : %d반 ( 평균 %d점 )\n", idx+1, cl_num_arr[idx], average_arr[idx]);
	}
	puts("-----------------------");

	free(cl_num_arr);
	
}