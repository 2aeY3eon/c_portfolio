#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

typedef struct LIBRARY {
	char title[30];
	char auth[30];
	char publ[30];
	int num;
	char borr='y';
} Library;
Library bookList[1000];
char search[100];
int K;
int bookcnt=0;

void bubble_sort();
char book_search(char *book_info, char *search, int *result);
void book_borrow();
void book_return();
void book_regist();
int book_change(int temp);
int save_file();
int load_file();

int main()
{
	
	int i, j, m=0, n, check, wh;
	char a;
	
	system("cls");
	printf("도서관에 오신 것을 환영합니다. \n");

	while(1)
	{
		printf("\n수행하실 작업을 선택해 주십시오. \n");
		puts(" 1. 도서 등록 "); 
		puts(" 2. 도서 검색 ");
		puts(" 3. 도서 대여 ");
		puts(" 4. 도서 반납 ");
		puts(" 5. 도서 교체 ");
		puts(" 6. 도서 정보 저장 ");
		puts(" 7. 도서 정보 불러오기 ");
		puts(" 8. 나가기");
		printf(" 입력 : ");
		scanf("%d", &i);
		printf("\n");

		switch(i) {

		case 1:
			getchar();
			book_regist();
			break;

		case 2:
			do {
				wh=0;
				j=0;
				puts("\n다음 중 어떤 항목으로 검색하시겠습니까? 단, 검색은 영문 대소문자를 구분합니다. 띄어쓰기는 '_' 로 입력하십시오. ");
				puts(" 1) 도서 번호 ");
				puts(" 2) 제목 ");
				puts(" 3) 저자 ");
				puts(" 4) 출판사 ");
				printf(" 입력 : "); 
				scanf("%d", &j);
				printf("\n");
				getchar();



				switch(j) {

				case 1:
					printf("몇 번 도서를 검색하시겠습니까? \n입력 : ");
					scanf("%d", &K);
					for(int temp=0; temp<bookcnt; temp++) {
						if(bookList[temp].num == K) {
							printf("\n%d번 도서의 정보입니다. \n", bookList[temp].num);
							printf("  제목 : %s\n  저자 : %s\n  출판사 : %s\n", bookList[temp].title, bookList[temp].auth,bookList[temp].publ);
							printf("  대출 가능 여부 : %c\n\n", bookList[temp].borr);
							break;
						}
					}
					break;

				case 2:
					printf("검색어를 입력해 주십시오. \n입력 : ");
					fgets(search, sizeof(search), stdin);
					search[strlen(search) -1]='\0'; 

					printf("결과를 출력합니다. \n");
					for(int temp=0; temp<=bookcnt; temp++)
					{	
						book_search(bookList[temp].title, search, &m);
						if(m==1)
						{
							printf("\n%d번 도서의 정보입니다. \n", bookList[temp].num);
							printf("  제목 : %s\n  저자 : %s\n  출판사 : %s\n", bookList[temp].title, bookList[temp].auth,bookList[temp].publ);
							printf("  대출 가능 여부 : %c\n", bookList[temp].borr);
							m = 0;
						}
					}
					break;

				case 3: 
					printf("검색어를 입력해 주십시오. \n");
					fgets(search, sizeof(search), stdin);
					search[strlen(search) -1]='\0'; 

					printf("결과를 출력합니다. \n");
					for(int temp=0; temp<=bookcnt; temp++)
					{	
						book_search(bookList[temp].auth, search, &m);
						if(m == 1)
						{
							printf("\n%d번 도서의 정보입니다. \n", bookList[temp].num);
							printf("  제목 : %s\n  저자 : %s\n  출판사 : %s\n", bookList[temp].title, bookList[temp].auth,bookList[temp].publ);
							printf("  대출 가능 여부 : %c\n", bookList[temp].borr);
							m = 0;
						}
					}
					break;
				
				case 4:
					printf("검색어를 입력해 주십시오 : ");
					fgets(search, sizeof(search), stdin);
					search[strlen(search) -1]='\0';

					printf("결과를 출력합니다. \n");
					for(int temp=0; temp<=bookcnt; temp++)
					{	
						book_search(bookList[temp].publ, search, &m);
						if(m == 1)
						{
							printf("\n%d번 도서의 정보입니다. \n", bookList[temp].num);
							printf("  제목 : %s\n  저자 : %s\n  출판사 : %s\n", bookList[temp].title,bookList[temp].auth, bookList[temp].publ);
							printf("  대출 가능 여부 : %c\n", bookList[temp].borr);
							m = 0;
						}
					}
					break;

				default:
					system("cls");
					printf("수행할 수 없는 작업입니다. \n\n");
					break;
				}

				printf("\n더 검색하시겠습니까? [Y/N] :");
				j=0;
				scanf(" %c", &a);
				switch(a) {
				case 'Y':
				case 'y':
					wh=1;
					break;
				case 'N':
				case 'n':
					wh=0;
					break;
				default:
					wh=0;
					printf("수행할 수 없는 작업입니다. \n\n");
					break;
				}
			} while(wh);
			system("cls");
			break;

		case 3:
			printf("대출할 도서의 번호를 입력해 주십시오. ");
			scanf("%d", &K);
			book_borrow();
			break;

		case 4:
			printf("반납할 도서의 번호를 입력해 주십시오. ");
			scanf("%d", &K);
			book_return();
			break;

		case 5:
			printf("교체할 도서의 번호를 선택해 주십시오.  ");
			scanf("%d", &n);
			for(int temp=0; temp<bookcnt; temp++) {
				if(bookList[temp].num==n) {
					book_change(temp);
					break;
				}
				else if(bookList[temp].num!=n && temp==bookcnt-1) {
					system("cls");
					printf("도서 교체에 실패하였습니다.\n");
				}
			}
			break;

		case 6:
			check = save_file();
			break;

		case 7:
			load_file();
			break;

		case 8:
			system("cls");
			printf("도서관을 이용해 주셔서 감사합니다. \n");
			return 0;
			break;

		default:
			system("cls");
			printf("수행할 수 없는 작업입니다. \n\n");
			getchar();
			break;
		}

		if(check==-1) {
			printf("도서 저장을 실패했습니다.\n\n");
			check=0;
		}
		i=0;
	}
}

void book_regist()
{
	int n, q=0, temp, choice;
	char yn;
	printf("등록할 도서의 도서 번호를 입력해 주십시오. \n");
	printf("도서 번호 : ");
	scanf("%d", &n);

	for(temp=0; temp<bookcnt; temp++) {
		if(bookList[temp].num == n) {
			getchar();
			printf("입력하신 도서 번호가 이미 등록되어 있습니다.\n");
			printf("도서 정보를 새로 등록하시겠습니까? [Y/N] : ");
			scanf("%c", &yn);
			switch(yn) {
			case 'Y':
			case 'y':
				q=1;
				break;
			case 'N':
			case 'n':
				system("cls");
				return;
			}
			break;
		}			
	}

	if(q==1)
		choice = temp;
	else if(q==0) {
		choice = bookcnt;
		bookcnt++;
	}


	bookList[choice].num = n;
	printf("제목 : ");
	getchar();
	fgets(bookList[choice].title, sizeof(bookList[choice].title), stdin);
	bookList[choice].title[strlen(bookList[choice].title) -1]='\0';

	printf("저자 : ");
	fgets(bookList[choice].auth, sizeof(bookList[choice].auth), stdin);
	bookList[choice].auth[strlen(bookList[choice].auth) -1]='\0';

	printf("출판사 : ");
	fgets(bookList[choice].publ, sizeof(bookList[choice].publ), stdin);
	bookList[choice].publ[strlen(bookList[choice].publ) -1]='\0';

	bookList[choice].borr='y';

	system("cls");
	printf("성공적으로 등록되었습니다.\n");
	
}

int save_file()
{
	char fname[1001];
	
	printf("저장할 파일 이름을 입력 하세요.(최대 500글자)\n입력(Ex: \"TextFile.txt\"): ");
	getchar();
	fgets(fname, sizeof(fname), stdin);
	fname[strlen(fname) -1]='\0';

	FILE * fp=fopen(fname, "wt");
	
	if(fp==NULL) {
		puts("\t\tSave Failed\n");  
		return -1;
	}

	bubble_sort();
	fprintf(fp, "Total: %d\n\n", bookcnt); 
	for(int temp=0; temp<bookcnt; temp++) {
		fprintf(fp, "Book Number: %d\n", bookList[temp].num);
		fprintf(fp, "Title: %s\n", bookList[temp].title);
		fprintf(fp, "Author: %s\n", bookList[temp].auth);
		fprintf(fp, "Publisher: %s\n", bookList[temp].publ);
		fprintf(fp, "Borrow: %c\n\n", bookList[temp].borr);
	}
	system("cls");
	fclose(fp);
	printf("성공적으로 저장되었습니다.\n\n");
	return 0;
}

int load_file()
{
	int temp, tens, lbcnt=0, lbnum, ovlapcnt=0, ovlapped;
	Library ovlapB[1001]; // 중복된 도서 정보
	char tempc;
	char tempStr[1001];
	char fname[1001]; // 파일 이름
	
	printf("불러올 파일 이름을 입력 하세요.(최대 500글자)\n입력(Ex: \"TextFile.txt\"): ");
	getchar();
	fgets(fname, sizeof(fname), stdin);
	fname[strlen(fname) -1]='\0';

	FILE * fp=fopen(fname, "rt");
	
	if(fp==NULL) {
		puts("\t\tLoad Failed\n");
		return -1;
	}
	fseek(fp, 7, SEEK_SET);
	fgets(tempStr, sizeof(tempStr), fp); // Total값 가져오기 
	tempStr[strlen(tempStr)-1]='\0'; // tempStr \n 제거

	lbcnt = atoi(tempStr); // (char)Total->int

	fseek(fp, 2, SEEK_CUR);

	for(int i=0; i<lbcnt; i++) {

		/* lbcnt = 도서 개수 = total값 (Load Book CouNT); */
		/* lbnum = 도서 번호 (Load Book NUMber) */

		ovlapped=0;

		fseek(fp, 13, SEEK_CUR);
		fgets(tempStr, sizeof(tempStr), fp); // 도서 번호 가져오기
		tempStr[strlen(tempStr)-1]='\0';
		lbnum = atoi(tempStr);

		for(temp=0; temp<bookcnt; temp++) {
			if(bookList[temp].num == lbnum) {
				ovlapB[ovlapcnt].num = temp;
				ovlapped=1;

				fseek(fp, 7, SEEK_CUR);
				fgets(tempStr, sizeof(tempStr), fp); // 도서 제목 정보
				tempStr[strlen(tempStr)-1]='\0';
				strncpy(ovlapB[ovlapcnt].title, tempStr, sizeof(ovlapB[ovlapcnt].title));

				fseek(fp, 8, SEEK_CUR);
				fgets(tempStr, sizeof(tempStr), fp); // 도서 저자 정보
				tempStr[strlen(tempStr)-1]='\0';
				strncpy(ovlapB[ovlapcnt].auth, tempStr, sizeof(ovlapB[ovlapcnt].auth));

				fseek(fp, 11, SEEK_CUR);
				fgets(tempStr, sizeof(tempStr), fp); // 도서 출판사 정보
				tempStr[strlen(tempStr)-1]='\0';
				strncpy(ovlapB[ovlapcnt].publ, tempStr, sizeof(ovlapB[ovlapcnt].publ));

				fseek(fp, 8, SEEK_CUR);
				fscanf(fp, "%c", &tempc); // 도서 빌림 여부
				ovlapB[ovlapcnt].borr = tempc;

				fseek(fp, 4, SEEK_CUR);
				ovlapcnt++;
			}
				
		}
		if(ovlapped==0) {
			bookList[bookcnt].num = lbnum;

			fseek(fp, 7, SEEK_CUR);
			fgets(tempStr, sizeof(tempStr), fp); // 도서 제목 정보
			tempStr[strlen(tempStr)-1]='\0';
			strncpy(bookList[bookcnt].title, tempStr, sizeof(bookList[bookcnt].title));

			fseek(fp, 8, SEEK_CUR);
			fgets(tempStr, sizeof(tempStr), fp); // 도서 저자 정보
			tempStr[strlen(tempStr)-1]='\0';
			strncpy(bookList[bookcnt].auth, tempStr, sizeof(bookList[bookcnt].auth));

			fseek(fp, 11, SEEK_CUR);
			fgets(tempStr, sizeof(tempStr), fp); // 도서 출판사 정보
			tempStr[strlen(tempStr)-1]='\0';
			strncpy(bookList[bookcnt].publ, tempStr, sizeof(bookList[bookcnt].publ));

			fseek(fp, 8, SEEK_CUR);
			fscanf(fp, "%c", &tempc); // 도서 빌림 여부
			bookList[bookcnt].borr = tempc;

			fseek(fp, 4, SEEK_CUR);
			bookcnt++;
		}
	}
	if(ovlapcnt>0) {
		printf("파일에 중복된 도서번호의 정보가 [%d]개 있습니다.\n도서를 덮어쓰기 하시겠습니까? [Y/N] : ", ovlapcnt);
		scanf("%c", &tempc);

		switch(tempc) {
		case 'Y':
		case 'y':
			for(int i=0; i<ovlapcnt; i++) {
				temp=ovlapB[i].num;
				strncpy(bookList[temp].title, ovlapB[i].title, sizeof(bookList[temp].title));
				strncpy(bookList[temp].auth, ovlapB[i].auth, sizeof(bookList[temp].auth));
				strncpy(bookList[temp].publ, ovlapB[i].publ, sizeof(bookList[temp].publ));
				bookList[temp].borr = ovlapB[i].borr;
			}
			system("cls");
	 		printf("성공적으로 덮어쓰기 되었습니다.\n");
			break;
		case 'N':
		case 'n':
			break;
		}
	}
	else {
		system("cls");
		printf("성공적으로 불러와졌습니다.\n\n");
	}
	bubble_sort();
	return 0;
}

char book_search(char *book_info, char *search, int *result)
{
	int i, j;
	char a;
	i = 0;
	j = 0;
	bubble_sort();
	while(*search)
	{
		if(*search == *book_info)
		{
			book_info++;
			search++;
			i++;
			j++;
		}
		else
		{
			search=search-i;
			if(*book_info == '\0')
			{
				break;
			}
			else
			{
				book_info++;
				j++;
			}
			i = 0;
		}
	}
	if(*search == '\0')
	{
		*result = 1;
		search = search - i;
	}
	book_info = book_info-j;
	i = 0;
	j = 0;
	return 0;
}
void book_borrow()
{
	system("cls");
	for(int i=0; i<bookcnt; i++) {
		if(bookList[i].num == K) {
			if(bookList[i].borr == 'y') {
				bookList[i].borr = 'n';
				printf("도서가 대출되었습니다. \n");
			}
			else{
				printf("해당 도서는 대출할 수 있는 도서가 아닙니다. \n");
			}
			break;
		}
		else if(i==bookcnt-1) {
			printf("해당 도서는 등록되어있지 않습니다. \n");
			break;
		}
	}
}
void book_return()
{
	system("cls");
	for(int i=0; i<bookcnt; i++) {
		if(bookList[i].num == K) {
			if(bookList[i].borr == 'n') {
				bookList[i].borr = 'y';
				printf("도서가 반납되었습니다. \n");
			}
			else{
				printf("해당 도서는 반납할 수 있는 도서가 아닙니다. \n");
			}
			break;
		}
		else if(i==bookcnt-1) {
			printf("해당 도서는 등록되어있지 않습니다. \n");
			break;
		}
	}
}

int book_change(int chnum)
{
	char b;
	printf("이전에 저장되어 있던 도서의 정보는 사라집니다. 계속 하시겠습니까? [Y/N] : ");
	scanf(" %c", &b);
	switch(b) {
	case 'Y':
	case 'y':
		getchar();
		printf("새로운 도서의 정보를 입력해 주십시오. \n");
		printf("제목 : ");
		fgets(bookList[chnum].title, sizeof(bookList[chnum].title), stdin);
		bookList[chnum].title[strlen(bookList[chnum].title)-1] = '\0';

		printf("저자 : ");
		fgets(bookList[chnum].auth, sizeof(bookList[chnum].auth), stdin);
		bookList[chnum].auth[strlen(bookList[chnum].auth)-1] = '\0';

		printf("출판사 : ");
		fgets(bookList[chnum].publ, sizeof(bookList[chnum].publ), stdin);
		bookList[chnum].publ[strlen(bookList[chnum].publ)-1] = '\0';

		bookList[chnum].borr='y';
		system("cls");
		printf("성공적으로 입력되었습니다.\n");
		break;

	case 'N':
	case 'n':
		system("cls");
		printf("작업이 취소되었습니다. \n");
		break;

	default:
		system("cls");
		printf("잘못된 작업입니다. \n");
		break;
	}
	return 0;
}

void bubble_sort()
{
	int temp;
	char tempc;
	char tempStr[1000];

	for(int i=0; i<bookcnt-1; i++) {
		for(int j=0; j<bookcnt-1; j++) {
			if(bookList[j].num>bookList[j+1].num) {
				tempc = bookList[j].borr;
				bookList[j].borr = bookList[j+1].borr;
				bookList[j+1].borr = tempc;

				strncpy(tempStr, bookList[j].title, sizeof(tempStr));
				strncpy(bookList[j].title, bookList[j+1].title, sizeof(bookList[j].title));
				strncpy(bookList[j+1].title, tempStr, sizeof(bookList[j+1].title));

				strncpy(tempStr, bookList[j].auth, sizeof(tempStr));
				strncpy(bookList[j].auth, bookList[j+1].auth, sizeof(bookList[j].auth));
				strncpy(bookList[j+1].auth, tempStr, sizeof(bookList[j+1].auth));

				strncpy(tempStr, bookList[j].publ, sizeof(tempStr));
				strncpy(bookList[j].publ, bookList[j+1].publ, sizeof(bookList[j].publ));
				strncpy(bookList[j+1].publ, tempStr, sizeof(bookList[j+1].publ));

				temp = bookList[j].num;
				bookList[j].num = bookList[j+1].num;
				bookList[j+1].num = temp;
			}
		}
	}

}
