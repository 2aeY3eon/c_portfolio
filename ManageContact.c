#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int InsertM();
void Delete();
void Search();
void PrintAll();
int Save();

void NewInsert();
int LoadFile();

typedef struct continfo
{
	int del;
	char name[1000];
	char telnum[1000];
} ContInfo;

int telcnt=0;
ContInfo cont[1000];

int main()
{
	system("cls");
	int n, check;
	while(1) {
		puts("***** MENU *****");
		puts("1. Insert Menu");
		puts("2. Delete");
		puts("3. Search");
		puts("4. Print All");
		puts("5. Save");
		puts("6. Exit");
		printf("Choose the item: ");
		scanf("%d", &n);
		printf("\n");

		switch(n) {
			case 1:
				InsertM();
				break;
			case 2:
				Delete();
				break;
			case 3:
				Search();
				break;
			case 4:
				PrintAll();
				break;
			case 5:
				check=Save();
				break;
			case 6:
				return 0;
				break;
			default:
				system("cls");
				printf("\t\tFailed to Found\n\n");
				getchar();
				break;
		}
		if(check==-1)
			return -1;
		n=0;
	}
}

int InsertM() {
	system("cls");
	int n;
	while(1) {
		puts("***** INSERT MENU *****");
		puts("1. New Insert");
		puts("2. Load File");
		puts("3. Main Menu");
		puts("4. Exit");
		printf("Choose the item: ");
		scanf("%d", &n);
		printf("\n");

		switch(n) {
			case 1:
				NewInsert();
				break;
			case 2:
				LoadFile();
				break;
			case 3:
				system("cls");
				return 0;
				break;
			case 4:
				exit(0);
				break;
			default:
				system("cls");
				printf("\t\tFailed to Found\n\n");
				getchar();
				break;
		}
		n=0;
	}
}

void Delete() {
	system("cls");
	int any, q=0;
	char cmp[20];

	getchar();
	printf("[ DELETE ]\n");

	printf("Input Name: ");
	gets(cmp);
	system("cls");

	for(int i=0; i<telcnt; i++) {
		if(cont[i].del==0 && strcmp(cont[i].name, cmp) == 0) {
			cont[i].del=1;
			q=1;
			printf("\t\tData Deleted\n");
		}
	}
	if(q==0)
		printf("\t\tFailed to Delete\n");
	printf("\n");
}

void Search() {
	system("cls");
	int any, q=0;
	char cmp[20];

	getchar();
	printf("[ SEARCH ]\n");

	printf("Input Name: ");
	gets(cmp);
	system("cls");

	for(int i=0; i<telcnt; i++) {
		if(cont[i].del==0 && strcmp(cont[i].name, cmp) == 0) {
			q=1;
			printf("\tTel: %s\n\n", cont[i].telnum);
		}
	}
	if(q==0)
		printf("\t\tFailed to Search\n\n");
}

void PrintAll() {
	system("cls");
	int r=0;

	for(int i=0; i<telcnt; i++) {
		if(cont[i].del==0) {
			r++;
			printf("%d. ---", r);
			printf("\tName: %s\n", cont[i].name);
			printf("\tTel: %s\n\n", cont[i].telnum);
		}
	}
}

int Save() {
	system("cls");
	char fname[1000];

	getchar();
	printf("[ SAVE ]\n");

	printf("Insert File Name: ");
	gets(fname);

	FILE * fp=fopen(fname, "wt");

	system("cls");

	if(fp==NULL) {
		puts("\t\tSave Failed\n");  
		return -1;
	}

	for(int i=0; i<telcnt; i++) {
		if(cont[i].del==0) {
			fprintf(fp, "[%d] Name: %s\n[%d] Tel: %s\n\n", i+1, cont[i].name, i+1, cont[i].telnum);
		}
	}

	

	puts("\t\tData Saved\n");
	printf("\n");
	fclose(fp);
}

void NewInsert() {
	system("cls");
	char tn[20];

	getchar();
	printf("[ INSERT ]\n");

	printf("Input Name: ");
	gets(cont[telcnt].name);

	printf("Input Tel Number: ");
	gets(cont[telcnt].telnum);

	cont[telcnt].del=0;
	telcnt++;

	system("cls");
	printf("\t\tData Inserted\n\n");
}

int LoadFile() {
	system("cls");

	int x=0, h=0;

	char tmpch;
	char tmpstr[1000];
	char fname[1000];

	getchar();
	printf("[ LOAD ]\n");

	printf("Insert File Name: ");
	gets(fname);

	FILE * fp=fopen(fname, "rt");

	system("cls");

	if(fp==NULL) {
		puts("\t\tLoad Failed\n");
		return -1;
	}

	fseek(fp, 10, SEEK_SET);
	while(1) {
		if(h>0) 
			fseek(fp, 12, SEEK_CUR);

		for(int i=0;; i++) {
			tmpch=fgetc(fp);

			if(tmpch=='\n') {
				break;
			}

			if(tmpch==EOF) {
				x=1;
				break;
			}

			else {
				cont[telcnt].name[i]=tmpch;
			}
		}

		fseek(fp, 9, SEEK_CUR);

		for(int i=0;; i++) {
			tmpch=fgetc(fp);

			if(tmpch=='\n') {
				break;
			}

			else if(tmpch==EOF) {
				x=1;
				break;
			}

			else {
				cont[telcnt].telnum[i]=tmpch;
			}
		}

		if(x==1)
			break;
		telcnt++;
		h++;
	}
	printf("\t\tData Loaded\n");
	fclose(fp);
	printf("\n");
}