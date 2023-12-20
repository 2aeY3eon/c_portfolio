#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>


void Loading();
int CalLoc(int k);
void SetDefaultAirline();
void ChooseAirline();
void MakeSeatEmpty(int num, int start, int end);
void MakeAirlineEmpty(int num);
void ShowSeat();
char CheckYN();

void MainMenu();
void ManageMenu();
void M_SetAirline();
void AddAirline();
void DelAirline();
void M_SetSeatHeight();
void M_SetDestination();
void M_SetVIP();
void VIPMenu();
void VIPAdd();
void VIPDel();

void CustomerMenu();
void AirlineInfo();
void ResMenu();
void ResSeat();
void ResSeatCancel();
void ResShow();
void SaveData();
void LoadData();

typedef struct seatinfo
{
	char usings[5];
	char name[50];
	char phonenum[100];
	char rrn[100];
	
} SInfo;

typedef struct apinfo
{
	char airline[1000];
	SInfo seats[1000][6];
	char destination[500];
	char vip[1000][50];
	int seatx; // 좌석 세로 길이
	int using;
	int customercnt;
	int vipcnt;
} APInfo;

APInfo AirP[100];


int N, Arlcnt=0, Arlrealcnt=0, Y, X; // N:선택한 항공사 번호, Arlcnt: 추가된 모든 항공사 개수, Arlrealcnt: 사용 가능한 항공사 개수

int main()
{
	int morc;

	system("cls");

	Loading();
	MainMenu();
}

void Loading()
{
	char loding[15][10] = { ' ' };
	char block[15][10] = { "■" };
	for(int i=0; i<15; i++)
	{
		Sleep(285);
		Beep(698.4565, 100);
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		printf("로딩중...\n");
		for(int j=0; j<15; j++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
			printf("%s", &loding[j]);
		}
		printf("\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		printf("\n");
		strcpy(loding[i], block[0]);
	}
	Sleep(150);
	Beep(987.7666, 100);
	Sleep(150); 
}

void SetDefaultAirline()
{
	int idx;
	idx=CalLoc(Arlcnt);                             
	strcpy(AirP[Arlcnt].airline, "기본항공");
	AirP[Arlcnt].using=1;
	AirP[Arlcnt].seatx=10;
	AirP[Arlcnt].customercnt=0;
	AirP[Arlcnt].vipcnt=0;
	strcpy(AirP[Arlcnt].destination, "제주도");
	MakeSeatEmpty(Arlcnt, 0, AirP[Arlcnt].seatx);
	Arlcnt++;
	Arlrealcnt++;
}

int CalLoc(int k)
{
	// k=항공사 순서 번호 | a=cnt 
	int i, cnt=0;
	for(i=0; i<Arlcnt; i++) {
		if(AirP[i].using==0) {
			continue;
		}
		else if(cnt==k) {
			break;
		}
		cnt++;
	}
	return i;
}

void ChooseAirline()
{
	int cnt=0, n;
	while(1) {
		for(int i=0; i<Arlcnt; i++) {
			if(cnt==Arlrealcnt) {
				break;
			}
			if(AirP[i].using!=0) { 
				printf("[%d]%s\n", cnt+1, AirP[i].airline);
				cnt++;
			}
		}
			
		printf("입력 : ");
		scanf("%d", &n);
		N=CalLoc(n-1);
		if(N<=Arlrealcnt-1  && 0<=N) 
			break;
		else {
			printf("다시 입력해주세요\n");
			getchar();
		}
	} 

}

void MakeSeatEmpty(int num, int start, int end)
{
	int temp;
	if(start>end) {
		temp=start;
		start=end;
		end=temp;
	}
	for(int i=start; i<end; i++) {
		for(int j=0; j<6; j++) {
			if(strcmp(AirP[num].seats[i][j].usings, "■") == 0) {
				AirP[num].customercnt--;
			}
			strcpy(AirP[num].seats[i][j].usings, "□");
			AirP[num].seats[i][j].name[0]='\0';
			AirP[num].seats[i][j].phonenum[0]='\0';
			AirP[num].seats[i][j].rrn[0]='\0';
		}
	}
}

void MakeAirlineEmpty(int num)
{
	AirP[num].airline[0]='\0';
	AirP[num].destination[0]='\0';
	for(int i=0; i<AirP[num].vipcnt; i++) {
		AirP[num].vip[i][0]='\0';
	}
	MakeSeatEmpty(num, 0, AirP[num].seatx);
	AirP[num].seatx=0;
	AirP[num].using=0;
	AirP[num].customercnt=0;
	AirP[num].vipcnt=0;
	
}	

void ShowSeat()
{
	puts("   |           좌석           |");
	puts("   | A | B | C |  | D | E | F |");
	for(int i=0; i<AirP[N].seatx; i++) {
		if(i<10) {
			printf(" %d |", i);
		}
		else if(i<100) {
			printf("%d |", i);
		}
		else if(i<1000) {
			printf("%d|", i);
		}
		for(int j=0; j<3; j++) {
			for(int v=0; v<AirP[N].vipcnt; v++) {
				if(strcmp(AirP[N].vip[v], AirP[N].seats[i][j].name)==0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				}
			}
			printf(" %s", AirP[N].seats[i][j].usings);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf("|");
		}
		printf("  |");
		for(int j=3; j<6; j++) {
			for(int v=0; v<AirP[N].vipcnt; v++) {
				if(strcmp(AirP[N].vip[v], AirP[N].seats[i][j].name)==0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				}
			}
			printf(" %s", AirP[N].seats[i][j].usings);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf("|");
		}
		printf("\n");
	}
}	

void MainMenu()
{
	int morc;
	while(1) {
		printf("━━━━━━  메인 메뉴 ━━━━━━\n");
		puts("[0] 종료");
		puts("[1] 관리자 메뉴");
		puts("[2] 고객 메뉴");
		printf("선택: ");
		scanf("%d", &morc);
		getchar();
		switch(morc) {
		case 0:
			exit(0);
			break;
		case 1:
			ManageMenu();
			break;
		case 2:
			CustomerMenu();
			break;
		default:
			printf("잘못된 입력값입니다. 다시 입력해주십시오. \n");
			break;
		}
	}

}

void ManageMenu()
{
	int ins, a=0, err;
	printf("-- Manage Menu ------------------\n");
	puts("0. 뒤로가기");
	puts("1. 항공사 설정");
	puts("2. 좌석 공간 설정");
	puts("3. 목적지 설정");
	puts("4. VIP 고객 설정");
	puts("5. 예약된 좌석 조회");
	puts("6. 항공사 정보 저장하기");	
	puts("7. 항공사 정보 불러오기");
	
	do {
		a=0;
		printf("입력: ");
		scanf("%d", &ins);

		switch(ins) {
		case 0:
			break;
		case 1:
			M_SetAirline();
			break;
		case 2:
			M_SetSeatHeight();
			break;
		case 3:
			M_SetDestination();
			break;
		case 4:
			M_SetVIP();
			break;
		case 5:
			ResShow();	
			break;
		case 6:
			SaveData();
			break;
			
		case 7:
			LoadData();
			break;
		default:
			a=1;
			printf("잘못된 입력값입니다. 다시 입력해주십시오.");
			break;
		}
	} while(a);
}

void M_SetAirline()
{
	int ins, a=0;
	char temps[500];
	printf("--[M] 항공사 설정 ------------------\n");
	puts("0. 취소");
	puts("1. 항공사 추가");
	puts("2. 항공사 삭제");
	do {
		a=0;
		printf("입력: ");
		scanf("%d", &ins);
		switch(ins) {
		case 0:
			return;
			break;
	
		case 1:
			getchar();
			AddAirline();
			break;
		case 2:
			getchar();
			DelAirline();
			break;
		default:
			a=1;
			printf("잘못된 입력값입니다. 다시 입력해주십시오.\n");
		}
	} while(a);
	
}

void AddAirline()
{
	puts("추가하실 항공사의 이름을 입력하세요.");
	printf("입력: ");

	fgets(AirP[Arlcnt].airline, sizeof(AirP[Arlcnt].airline), stdin);
	AirP[Arlcnt].airline[strlen(AirP[Arlcnt].airline)-1]='\0';
	while(1) {
		if(AirP[Arlcnt].airline[strlen(AirP[Arlcnt].airline)-1]!=' ') {
				break;
		}
		else if(AirP[Arlcnt].airline[strlen(AirP[Arlcnt].airline)-1]==' ') {
			AirP[Arlcnt].airline[strlen(AirP[Arlcnt].airline)-1]='\0';
		}
	}

	puts("추가하실 항공사의 목적지를 입력하세요.");
	printf("입력: ");

	fgets(AirP[Arlcnt].destination, sizeof(AirP[Arlcnt].destination), stdin);
	AirP[Arlcnt].destination[strlen(AirP[Arlcnt].destination)-1]='\0';
	while(1) {
		if(AirP[Arlcnt].destination[strlen(AirP[Arlcnt].destination)-1]!=' ') {
				break;
		}
		else if(AirP[Arlcnt].destination[strlen(AirP[Arlcnt].destination)-1]==' ') {
			AirP[Arlcnt].destination[strlen(AirP[Arlcnt].destination)-1]='\0';
		}
	}

	AirP[Arlcnt].using=1;
	AirP[Arlcnt].seatx=10;
	AirP[Arlcnt].customercnt=0;
	MakeSeatEmpty(Arlcnt, 0, AirP[Arlcnt].seatx);
	Arlcnt++;
	Arlrealcnt++;
	printf("성공적으로 추가되었습니다.\n");
}

void DelAirline()
{
	int cf=1;
	char yn;
	if(Arlrealcnt==0) {
		puts("추가된 항공사가 없습니다!");
		return;
	}

	char temps[100];
	puts("어떤 항공사를 삭제하시겠습니까?");
	ChooseAirline();
	printf("정말 '%s' 을(를) 삭제하시겠습니까? [Y/N]\n", AirP[N].airline);
	getchar();
	do {
		cf=0;
		printf("입력: ");
		scanf("%c", &yn);
		switch(yn) {
		case 'y':
		case 'Y':
			MakeAirlineEmpty(N);
			break;
		case 'n':
		case 'N':
			printf("삭제를 취소합니다.\n");
			return;
			break;
		default:
			cf=1;
			printf("잘못된 입력값입니다. 다시 입력해주십시오.\n");
			break;
		}
	} while(cf);

	Arlrealcnt--;
	MakeAirlineEmpty(N);
	printf("성공적으로 삭제되었습니다.\n");
}

void M_SetSeatHeight()
{
	int tempx;
	int idx;
	
	if(Arlrealcnt==0) {
		puts("추가된 항공사가 없습니다!");
		return;
	}

	printf("어떤 항공의 좌석 공간을 설정하시겠습니까?\n");
	ChooseAirline();
	
	while(1) {
		printf("좌석 공간: 가로 6칸 x 세로 N칸\n");
		printf("N( 0≤N≤1000 )을 입력하세요(현재 N: %d)\n", AirP[N].seatx);
		printf("입력: ");
		scanf("%d", &tempx);

		if(tempx<=1000 && tempx>=0) {
			break;
		}
		else {
			puts("입력하신 값이 범위를 벗어납니다!");
			puts("다시 입력해 주십시오.");
		}
	}

	MakeSeatEmpty(N, AirP[N].seatx, tempx);
	AirP[N].seatx=tempx;
}

void M_SetDestination()
{
	int idx;
	char temps[500];

	if(Arlrealcnt==0) {
		puts("추가된 항공사가 없습니다!");
		return;
	}

	printf("어떤 항공의 목적지를 설정하시겠습니까?\n");
	ChooseAirline();
	getchar();

	if(strcmp(AirP[N].destination, "") == 0) {
		strcpy(temps, "None");
	}
	
	printf("목적지의 이름을 입력하십시오(현재 목적지:\'%s\')\n", AirP[N].destination);
	printf("입력: ");

	fgets(temps, sizeof(temps), stdin);
	temps[strlen(temps)-1]='\0';
	while(1) {
		if(temps[strlen(temps)-1]!=' ') {
				break;
		}
		else if(temps[strlen(temps)-1]==' ') {
			temps[strlen(temps)-1]='\0';
		}
	}

	strcpy(AirP[N].destination, temps);

	printf("성공적으로 변경되었습니다.\n");
}

void M_SetVIP()
{
	int vm;
	int idx;
	char temps[500];

	if(Arlrealcnt==0) {
		puts("추가된 항공사가 없습니다!");
		return;
	}

	printf("어떤 항공의 VIP를 설정하시겠습니까?\n");
	ChooseAirline();
	getchar();



	printf("VIP의 이름을 입력하십시오: ");
	fgets(temps, sizeof(temps), stdin);
	temps[strlen(temps)-1]='\0';
	while(1) {
		if(temps[strlen(temps)-1]!=' ') {
			break;
		}
		else if(temps[strlen(temps)-1]==' ') {
			temps[strlen(temps)-1]='\0';
		}
	}

	strcpy(AirP[N].vip[AirP[N].vipcnt], temps);
	AirP[N].vipcnt++;
}

void VIPMenu()
{
	int vm;
	puts("-- VIP 메뉴 ------------------");
	puts("0. 돌아가기");
	puts("1. VIP 추가");
	puts("2. VIP 삭제");
	printf("입력: ");
	scanf("%d", &vm);

	switch(vm) {
	case 0:
		return;
		break;
	case 1:
		VIPAdd();
		break;
	case 2:
		VIPDel();
		break;
	}
}

void VIPAdd()
{
	char temps[1000];
	for(int i=0; i<AirP[N].vipcnt; i++) {
		printf("VIP 고객 리스트:\n");
		printf("[i]\t%s", AirP[N].vip[i]);
	}

	printf("VIP의 이름을 입력하십시오: ");
	fgets(temps, sizeof(temps), stdin);
	temps[strlen(temps)-1]='\0';
	while(1) {
		if(temps[strlen(temps)-1]!=' ') {
			break;
		}
		else if(temps[strlen(temps)-1]==' ') {
			temps[strlen(temps)-1]='\0';
		}
	}

	for(int i=0; i<AirP[N].vipcnt; i++) {
		if(strcmp(temps, AirP[N].vip[i])==0) {
			printf("이미 등록되어있는 VIP입니다!");
			return;
		}
	}

	strcpy(AirP[N].vip[AirP[N].vipcnt], temps);
	AirP[N].vipcnt++;
}


void VIPDel()
{
	int a;
	char temps[1000];
	for(int i=0; i<AirP[N].vipcnt; i++) {
		printf("VIP 고객 리스트:\n");
		printf("[i]\t%s", AirP[N].vip[i]);
	}

	puts("몇번째 VIP를 제외하시겠습니까?");
	printf("입력: ");
	scanf("%d", &a);

	for(int i=a; i<AirP[N].vipcnt-1; i++) {
		strncpy(AirP[N].vip[i], AirP[N].vip[i+1], sizeof(AirP[N].vip[i]));
	}
		
}

void CustomerMenu()
{
	int ins, err, a=0;
	char yn;
	if(Arlrealcnt==0) {
		printf("추가되어있는 항공이 없습니다. \n기본항공을 추가하시겠습니까? [Y/N]\n");
		do {
			a=0;
			printf("입력: ");
			scanf("%c", &yn);
			switch(yn) {
			case 'y':
			case 'Y':
				SetDefaultAirline();
				break;
			case 'n':
			case 'N':
				return;
				break;
			default:
				printf("잘못된 입력값입니다. 다시 입력해주십시오.\n");
				a=1;
				break;
			}
			getchar();
		} while(a);
	}
	puts("탑승하실 항공사의 번호를 선택해주세요");
	ChooseAirline();


	while(1)  {
		printf("-- %s ------------------\n", AirP[N].airline);
		puts("0. 메인 메뉴 ");
		puts("1. 항공사 선택");
		puts("2. 항공사 정보");
		puts("3. 예약 메뉴");
		printf("입력: ");

		scanf("%d", &ins);
		getchar();

		switch(ins) {
		case 0: // 메인 메뉴
			return;
			break;

		case 1: // 항공사 선택
			puts("탑승하실 항공사의 번호를 선택해주세요");
			ChooseAirline();
			break;

		case 2: // 항공사 정보
			AirlineInfo();
			break;

		case 3: // 예약 메뉴
			ResMenu();
			break;

		default:
			printf("잘못된 입력값입니다. 다시 입력해주십시오\n");
			break;
		}
		ins=0; 
	}
}

void AirlineInfo()
{
	printf("현재 선택되어 있는 항공(%s)의 정보를 확인합니다.\n", AirP[N].airline);
	printf("항공사 이름: %s\n", AirP[N].airline);
	printf("목적지: %s\n", AirP[N].destination);
	printf("기체의 세로 좌석 길이: %d\n", AirP[N].seatx);
	printf("예약되어있는 고객의 수: %d\n", AirP[N].customercnt);
	
}

void ResMenu()
{
	int ins, a=0;
	puts("-- 예약 메뉴 ------------------");
	puts("0. 돌아가기");
	puts("1. 좌석 예약");
	puts("2. 예약 취소"); 

	do {
		a=0;
		printf("입력: ");
		scanf("%d", &ins);

		switch(ins) {
		case 0:
			return;
			break;

		case 1: // 좌석 예약
			ShowSeat();
			ResSeat();
			break;

		case 2: // 예약 취소
			ResSeatCancel();
			break;
	
		default:
			printf("잘못된 입력입니다. 다시 입력해주십시오.\n");
			a=1;
			ins=0;
			break;
		}
	} while(a);
	
}

void ResSeat()
{
	char seatloc[5];
	char name[100], pn[100];
	char x, yn;
	int sloclen, namelen, vipyn=0;
	getchar();

	printf("예약하실 좌석 위치를 입력해주세요(Ex: \"A0\"): ");
	scanf("%c", &x);
	scanf("%s", seatloc);
	getchar();
	Y=atoi(seatloc);
	X=x-65;

	if('A'<=x && x<='F') {
		if(0<=Y && Y<AirP[N].seatx) {
			if(strcmp(AirP[N].seats[Y][X].usings, "□")==0) {
				while(1) {
					namelen=22;
					sloclen=16;
					puts("정보를 입력해 주십시오");
					printf("이름: ");
					fgets(AirP[N].seats[Y][X].name, sizeof(AirP[N].seats[Y][X].name), stdin);
					AirP[N].seats[Y][X].name[strlen(AirP[N].seats[Y][X].name)-1]= '\0';
					while(1) {
						if(AirP[N].seats[Y][X].name[strlen(AirP[N].seats[Y][X].name)-1]!=' ') {
								break;
						}
						else if(AirP[N].seats[Y][X].name[strlen(AirP[N].seats[Y][X].name)-1]==' ') {
							AirP[N].seats[Y][X].name[strlen(AirP[N].seats[Y][X].name)-1]='\0';
						}
					}

			 		for(int i=0; i<AirP[N].vipcnt; i++) {
						if(strcmp(AirP[N].seats[Y][X].name, AirP[N].vip[i])==0) {
							vipyn=1;
							namelen-=5;
							break;
						}
					}

					printf("전화번호('-' 제외, 띄어쓰기 없이 11글자): ");
					fgets(AirP[N].seats[Y][X].phonenum, sizeof(AirP[N].seats[Y][X].phonenum), stdin);
					AirP[N].seats[Y][X].phonenum[strlen(AirP[N].seats[Y][X].phonenum)-1] = '\0';

					if(strlen(AirP[N].seats[Y][X].phonenum)!=11) {
						puts("정보를 올바르게 입력해 주십시오.");
						continue;
					}

					printf("주민등록번호('-' 제외, 띄어쓰기 없이 13글자): ");
					fgets(AirP[N].seats[Y][X].rrn, sizeof(AirP[N].seats[Y][X].rrn), stdin);
					AirP[N].seats[Y][X].rrn[strlen(AirP[N].seats[Y][X].rrn)-1] = '\0';
					if(strlen(AirP[N].seats[Y][X].rrn)!=13) {
						puts("정보를 올바르게 입력해 주십시오.");
						continue;
					}

					printf("┏ ━ ━ ━ ━ ━ ━ ━ ━ ━ ━ ━ ━ ━ ━ ┓ \n");
					sloclen-=strlen(seatloc);
					printf("┃ 좌석 위치: %c%d", x, Y);
					for(int i=0; i<sloclen; i++) {
						printf(" ");
					}
					printf("┃\n");
 					
					
					namelen-=strlen(AirP[N].seats[Y][X].name);
					printf("┃ 이름: %s", AirP[N].seats[Y][X].name);
					for(int i=0; i<namelen; i++) {
						printf(" ");
					}
					if(vipyn) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
						printf("[VIP]");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					}
					printf("┃\n");
						
						
					
					printf("┃ 전화번호: ");
					for(int i=0; i<11; i++) {
						if(i==3 || i==7)
							printf("-");
						printf("%c", AirP[N].seats[Y][X].phonenum[i]);
					}
					printf("     ┃\n");
					printf("┃ 주민등록번호: ");
					for(int i=0; i<13; i++) {
						printf("%c", AirP[N].seats[Y][X].rrn[i]);
						if(i==5)
							printf("-");
					}
					printf("┃\n");
					printf("┗ ━ ━ ━ ━ ━ ━ ━ ━ ━ ━ ━ ━ ━ ━ ┛ \n");
					printf("입력된 정보가 맞습니까? [Y/N]\n");
					printf("입력: ");
					scanf("%c", &yn);
					getchar();

					switch(yn) {
					case 'y':
					case 'Y':
						break;
					case 'n':
					case 'N':
						continue;
						break;
					default:
						printf("잘못된 입력값입니다. 다시 입력해주십시오.\n");
						continue;
						break;
							
					}
					strcpy(AirP[N].seats[Y][X].usings, "■");
					AirP[N].customercnt++;
					puts("정상적으로 예약 되었습니다.");
					ShowSeat();
					break;
				}
			}
			else {
				puts("입력하신 좌석은 이미 예약이 되어있습니다.");
			}
		}
		else {
			puts("입력하신 좌석은 이 비행기에 존재하지 않습니다.");
		}
	}
	else {
		puts("입력하신 좌석은 이 비행기에 존재하지 않습니다.");
	}
}

void ResSeatCancel()
{
	char seatloc[100];
	char x;
	getchar();

	ShowSeat();
	printf("예약을 취소하실 좌석 위치를 입력해주세요(Ex: \"A0\"): ");
	scanf("%c", &x);
	scanf("%s", seatloc);
	Y=atoi(seatloc);
	X=x-65;

	if('A'<=x && x<='F') {
		if(0<=Y && Y<=AirP[N].seatx) {
			if(strcmp(AirP[N].seats[Y][X].usings, "■")==0) {
				strcpy(AirP[N].seats[Y][X].usings, "□");
				puts("정상적으로 좌석이 예약 취소되었습니다.");

				strcpy(AirP[N].seats[Y][X].name, "");
				strcpy(AirP[N].seats[Y][X].phonenum, "");
				strcpy(AirP[N].seats[Y][X].rrn, "");
				AirP[N].customercnt--;
				ShowSeat();
			}
			else {
				puts("입력하신 좌석은 예약이 되어있지 않습니다.");
			}
		}
		else {
			puts("입력하신 좌석은 이 비행기에 존재하지 않습니다.");
		}
	}
	else {
		puts("입력하신 좌석은 이 비행기에 존재하지 않습니다."); 
	}
}

void ResShow()
{
	char seatloc[1000];
	char x;
	int namelen, sloclen, vipyn=0;
	puts("어떤 항공사 좌석 정보를 조회하시겠습니까?");
	ChooseAirline();
	
	puts("어떤 좌석을 조회하시겠습니까?");
	ShowSeat();
	printf("조회하실 좌석 위치를 입력해주세요(Ex: \"A0\"): ");
	getchar();

	scanf("%c", &x);
	scanf("%s", seatloc);
	Y=atoi(seatloc);
	X=x-65;

	if('A'<=x && x<='F') {
		if(0<=Y && Y<=AirP[N].seatx) {
			if(strcmp(AirP[N].seats[Y][X].usings, "■")==0) {
				namelen=20;
				sloclen=16;

		 		for(int i=0; i<AirP[N].vipcnt; i++) {
					if(strcmp(AirP[N].seats[Y][X].name, AirP[N].vip[i])==0) {
						vipyn=1;
						namelen-=5;
						break;
					}
				}
				printf("┏ ━ ━ ━ ━ ━ ━ ━ ━ ━ ━ ━ ━ ━ ━ ┓ \n");
				sloclen-=strlen(seatloc);
				printf("┃ 좌석 위치: %c%d", x, Y);
				for(int i=0; i<sloclen; i++) {
					printf(" ");
				}
				printf("┃\n");
 			
				
				namelen-=strlen(AirP[N].seats[Y][X].name);
				printf("┃ 예약인: %s", AirP[N].seats[Y][X].name);
				for(int i=0; i<namelen; i++) {
					printf(" ");
				}
				if(vipyn) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
					printf("[VIP]");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				}
				printf("┃\n");
					
					
				
				printf("┃ 전화번호: ");
				for(int i=0; i<11; i++) {
					if(i==3 || i==7)
						printf("-");
					printf("%c", AirP[N].seats[Y][X].phonenum[i]);
				}
				printf("     ┃\n");
				printf("┃ 주민등록번호: ");
				for(int i=0; i<13; i++) {
					printf("%c", AirP[N].seats[Y][X].rrn[i]);
						if(i==5)
							printf("-");
				} 
				printf("┃\n");
				printf("┗ ━ ━ ━ ━ ━ ━ ━ ━ ━ ━ ━ ━ ━ ━ ┛ \n");
			}
			else {
				puts("입력하신 좌석은 예약되어있지 않아 조회가 불가능합니다.");
			}
		}
		else {
			puts("입력하신 좌석은 이 비행기에 존재하지 않습니다.");
		}
	}
	else {
		puts("입력하신 좌석은 이 비행기에 존재하지 않습니다."); 
	}
}

void SaveData()
{
	int temp;
	char fname[1000];
	mkdir("sjq140folder");
	chdir("sjq140folder");

	getchar();
	puts("저장될 파일의 이름을 입력해주세요.");
	printf("입력: ");
	fgets(fname, sizeof(fname), stdin);
	fname[strlen(fname)-1]='\0';
	while(1) {
		if(fname[strlen(fname)-1]!=' ') {
			break;
		}
		else if(fname[strlen(fname)-1]==' ') {
			fname[strlen(fname)-1]='\0';
		}
	}

	FILE * fp=fopen(fname, "wt");

	if(fp==NULL) {
		puts("저장에 실패했습니다.");
		return;
	}

	fprintf(fp, "%d\n", Arlrealcnt);
	for(int i=0; i<Arlrealcnt; i++) {
		fprintf(fp, "%s\n", AirP[i].airline);
	}

	for(int i=0; i<Arlcnt; i++) {
		if(AirP[i].using==0) {
			continue;
		}

		temp=0;
		fprintf(fp, "%s\n", AirP[i].airline);
		fprintf(fp, "%d\n", AirP[i].seatx);
		fprintf(fp, "%s\n", AirP[i].destination);
		fprintf(fp, "%d\n", AirP[i].vipcnt);
		for(int j=0; j<AirP[i].vipcnt; j++) {
			fprintf(fp, "%s\n", AirP[i].vip[j]);
		}
		fprintf(fp, "%d\n", AirP[i].using);
		fprintf(fp, "%d\n", AirP[i].customercnt);

		for(int p=0; p<6; p++) {
			for(int q=0; q<AirP[i].seatx; q++) {
				if(strcmp("■", AirP[i].seats[q][p].usings)==0 && temp<AirP[N].customercnt) {
					fprintf(fp, "%c%d\n", p+65, q);
					fprintf(fp, "%s\n", AirP[i].seats[q][p].name);
					fprintf(fp, "%s\n", AirP[i].seats[q][p].phonenum);
					fprintf(fp, "%s\n", AirP[i].seats[q][p].rrn);
					temp++;
				}
			}
		}
	}
	fclose(fp);
	chdir("/s");
	printf("성공적으로 저장되었습니다.\n");
}

void LoadData() //중복 항공사 제거
{
	int temp, xloc, yloc, alcnt, a=0, ovcnt=0, ovyes=0, TN;
	char yn;
	char ovlapst[100][1000];
	char temps[1000];

	mkdir("sjq140folder");
	chdir("sjq140folder");

	getchar();
	puts("불러올 파일의 이름을 입력해주세요.");
	printf("입력: ");
	fgets(temps, sizeof(temps), stdin);
	temps[strlen(temps)-1]='\0';
	while(1) {
		if(temps[strlen(temps)-1]!=' ') {
			break;
		}
		else if(temps[strlen(temps)-1]==' ') {
			temps[strlen(temps)-1]='\0';
		}
	}

	FILE * fp=fopen(temps, "rt");

	if(fp==NULL) {
		puts("불러오기에 실패했습니다.");
		return;
	}

	fscanf(fp, "%d", &alcnt);
	fgetc(fp);

	for(int i=0; i<alcnt; i++) {
		fgets(temps, sizeof(temps), fp);
		temps[strlen(temps)-1]='\0';

		for(int j=0; j<Arlcnt; j++) {
			if(strcmp(AirP[j].airline, temps) == 0) {
				strncpy(ovlapst[ovcnt], temps, sizeof(ovlapst[ovcnt]));
				ovcnt++;
			}
		}
	}

	if(ovcnt) {
		printf("현재 불러오시려는 항공사 중 [%d]개의 항공사가 중복됩니다.\n", ovcnt);
		printf("중복되는 항공사의 정보를 기존 항공사에 덮어씌우시겠습니까? [Y/N]\n");
		printf("입력: ");
		do {
			a=0;
			scanf("%c", &yn);
			switch(yn) {

			case 'Y':
			case 'y':
				ovyes=1;
				break;
			case 'N':
			case 'n':
				break;
			default:
				printf("잘못된 입력값입니다. 다시 입력해주십시오.");
				a=1;
				break;
			}
		} while(a);
	}

	for(int cnt=0; cnt<alcnt; cnt++) {
		a=0;

		fgets(temps, sizeof(temps), fp);
		temps[strlen(temps)-1]='\0';

		if(ovyes) {
			for(int i=0; i<ovcnt; i++) {
				if(strcmp(ovlapst[i], temps) == 0) {
					TN=CalLoc(cnt);
					a=1;
				}
			}
		}

		if(ovyes && a==1) {
			MakeAirlineEmpty(TN);
		
			strncpy(AirP[TN].airline, temps, sizeof(AirP[TN].airline)); // 항공사 이름 저장
				
			fscanf(fp, "%d", &AirP[TN].seatx); // 비행기 세로 길이 저장
			fgetc(fp);
			MakeSeatEmpty(TN, 0, AirP[TN].seatx); // 임시
			
			fgets(AirP[TN].destination, sizeof(AirP[TN].destination), fp); // 목적지 저장
			AirP[TN].destination[strlen(AirP[TN].destination)-1]='\0';
		
			fscanf(fp, "%d", &AirP[TN].vipcnt); // vip 인원 수 저장
			fgetc(fp);
		
			for(int i=0; i<AirP[TN].vipcnt; i++) { // vip 이름 저장
				fgets(AirP[TN].vip[i], sizeof(AirP[TN].vip[i]), fp);
				AirP[TN].vip[i][strlen(AirP[TN].vip[i])-1]='\0';
			}

			fscanf(fp, "%d", &AirP[TN].using); // 항공사 사용 여부 저장
			fgetc(fp);
			fscanf(fp, "%d", &AirP[TN].customercnt); // 비행기 예약자 수 저장
			fgetc(fp);
			for(int i=0; i<AirP[TN].customercnt; i++) { // 비행기 예약자 정보 저장
				fgets(temps, sizeof(temps), fp); // 예약한 좌석 위치 저장
				temps[strlen(temps)-1]='\0';

				xloc=temps[0]-65;
				temps[0]='0';
				yloc=atoi(temps);

				fgets(AirP[TN].seats[yloc][xloc].name, sizeof(AirP[TN].seats[yloc][xloc].name), fp); // 예약자 이름 저장
				AirP[TN].seats[yloc][xloc].name[strlen(AirP[TN].seats[yloc][xloc].name)-1]='\0';

				fgets(AirP[TN].seats[yloc][xloc].phonenum, sizeof(AirP[TN].seats[yloc][xloc].phonenum), fp); // 예약자 전화번호 저장
				AirP[TN].seats[yloc][xloc].phonenum[strlen(AirP[TN].seats[yloc][xloc].phonenum)-1]='\0';

				fgets(AirP[TN].seats[yloc][xloc].rrn, sizeof(AirP[TN].seats[yloc][xloc].rrn), fp); // 예약자 주민등록번호 저장
				AirP[TN].seats[yloc][xloc].rrn[strlen(AirP[TN].seats[yloc][xloc].rrn)-1]='\0';

				strcpy(AirP[TN].seats[yloc][xloc].usings, "■");
			}

			continue;
		}
			
			
			

		strncpy(AirP[Arlcnt].airline, temps, sizeof(AirP[Arlcnt].airline)); // 항공사 이름 저장
				
		fscanf(fp, "%d", &AirP[Arlcnt].seatx); // 비행기 세로 길이 저장
		fgetc(fp);
		MakeSeatEmpty(Arlcnt, 0, AirP[Arlcnt].seatx); // 임시
		
		fgets(AirP[Arlcnt].destination, sizeof(AirP[Arlcnt].destination), fp); // 목적지 저장
		AirP[Arlcnt].destination[strlen(AirP[Arlcnt].destination)-1]='\0';
	
		fscanf(fp, "%d", &AirP[Arlcnt].vipcnt); // vip 인원 수 저장
		fgetc(fp);
	
		for(int i=0; i<AirP[Arlcnt].vipcnt; i++) { // vip 이름 저장
			fgets(AirP[Arlcnt].vip[i], sizeof(AirP[Arlcnt].vip[i]), fp);
			AirP[Arlcnt].vip[i][strlen(AirP[Arlcnt].vip[i])-1]='\0';
		}
		
		fscanf(fp, "%d", &AirP[Arlcnt].using); // 항공사 사용 여부 저장
		fgetc(fp);
		fscanf(fp, "%d", &AirP[Arlcnt].customercnt); // 비행기 예약자 수 저장
		fgetc(fp);
		for(int i=0; i<AirP[Arlcnt].customercnt; i++) { // 비행기 예약자 정보 저장
			fgets(temps, sizeof(temps), fp); // 예약한 좌석 위치 저장
			temps[strlen(temps)-1]='\0';
			xloc=temps[0]-65;
			temps[0]='0';
			yloc=atoi(temps);

			fgets(AirP[Arlcnt].seats[yloc][xloc].name, sizeof(AirP[Arlcnt].seats[yloc][xloc].name), fp); // 예약자 이름 저장
			AirP[Arlcnt].seats[yloc][xloc].name[strlen(AirP[Arlcnt].seats[yloc][xloc].name)-1]='\0';
					
			fgets(AirP[Arlcnt].seats[yloc][xloc].phonenum, sizeof(AirP[Arlcnt].seats[yloc][xloc].phonenum), fp); // 예약자 전화번호 저장
			AirP[Arlcnt].seats[yloc][xloc].phonenum[strlen(AirP[Arlcnt].seats[yloc][xloc].phonenum)-1]='\0';
			
			fgets(AirP[Arlcnt].seats[yloc][xloc].rrn, sizeof(AirP[Arlcnt].seats[yloc][xloc].rrn), fp); // 예약자 주민등록번호 저장
			AirP[Arlcnt].seats[yloc][xloc].rrn[strlen(AirP[Arlcnt].seats[yloc][xloc].rrn)-1]='\0';
	
			strcpy(AirP[Arlcnt].seats[yloc][xloc].usings, "■");
		}	
		Arlcnt++;
		Arlrealcnt++;
	}

	fclose(fp);
	chdir("/s");
	printf("성공적으로 불러와졌습니다.\n");
}