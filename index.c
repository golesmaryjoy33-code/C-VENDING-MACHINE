#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

void insert_coin();
void possibility(int coin);
void select_obj();
void change(int change_coin);
void print_drink(int flag);
void textcolor(int foreground, int background);

//system("cls");
enum obj { vitamin = 1200, cola = 800, Letsbe = 600 };
int coin;

int main(void) {
	insert_coin();

	return 0;
}

void insert_coin() {
	
	int pcoin = 0;
	printf("\t- - - INSERT COINS! - - -\n\t");
	scanf("%d", &pcoin);
	coin += pcoin;

	select_obj();
}

void restart() {
	int op = -1;

	printf("\tYOU HAVE MORE COIN %dwon!\n\tmore? (y=1,n=0): ",coin); scanf("%d", &op);
	if (op == 1)select_obj();
	else change(coin);
}

void change(int change_coin) {
	printf("\tHERE THE CHANGE! %dwon\n\n\tGOOD BYE!\n", change_coin);
	exit(0);
}

void possibility(int coin) {

	printf("\n\t살 수 있는 품목(%d coins)\n", coin);
	if (coin >= vitamin) printf("\t비타민워터(1200won) ●: (1) \n\t콜라(800won)        ●: (2) \n\t레쓰비(600won)      ●: (3) \n");
	else if (coin >= cola) printf("\t비타민워터(1200won) ○: (1) \n\t콜라(800won)        ●: (2)\n\t레쓰비(600won)      ●: (3)\n");
	else if (coin >= Letsbe) printf("\t비타민워터(1200won) ○: (1) \n\t콜라(800won)        ○: (2)\n\t레쓰비(600won)      ●: (3)\n");
	else {
		printf("\n\t  No... \n \n\t- - - INSERT MORECOINS - - -\n");
		insert_coin();
	}
}

void select_obj() {
	int op_select = 0, price = 0;
	int flag = 0;

	printf("\n\t- - - SELECT - - - (quit: 4)\n\t"); 
	possibility(coin);
	printf("\n\t >> ");
	scanf("%d", &op_select);
	
	switch (op_select) {
		case 1: price = vitamin; break;
		case 2: price = cola; break;
		case 3: price = Letsbe; break;
		case 4: break;
	}

	if ((coin - price) >= 0) {
		printf("\n\t- - - GET DRINK! - - - \n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
		print_drink(op_select);
		coin -= price; 
	}
	else {
		printf("\n\tNOPE!\n");
	}

	printf("\n\tYOU HAVE %d coins\n", coin);
	printf("\tINPUT MORE COIN? (y=1,n=0): "); scanf("%d", &flag); printf("\n");

	if (flag == 1) {
		insert_coin();
		select_obj(coin);
	}
	else change(coin);
}

void print_drink(int flag) {
	if (flag == 1) {
		puts("");
		textcolor(3,15);
		printf("\t┏───────━┓\n");
		printf("\t┃        ┃\n");
		printf("\t┃Vitamin ┃\n");
		printf("\t┃   Water┃\n");
		printf("\t┃        ┃\n");
		printf("\t┃        ┃\n");
		printf("\t┃        ┃\n");
		printf("\t┃        ┃\n");
		printf("\t┗━────━━━┛\n");
	}

	else if (flag == 2) {
		puts("");
		textcolor(4, 15);
		printf("\t┏━────━━━┓\n");
		printf("\t┃        ┃\n");
		printf("\t┃ Coca-  ┃\n");
		printf("\t┃   Cola ┃\n");
		printf("\t┃        ┃\n");
		printf("\t┃        ┃\n");
		printf("\t┃        ┃\n");
		printf("\t┃        ┃\n");
		printf("\t┗━────━━━┛\n\n");

	}

	else if (flag == 3) {
		puts("");
		textcolor(9, 15);

		printf("\t┏━────━━━┓\n");
		printf("\t┃        ┃\n");
		printf("\t┃LET's BE┃\n");
		printf("\t┃        ┃\n");
		printf("\t┃        ┃\n");
		printf("\t┃        ┃\n");
		printf("\t┃        ┃\n");
		printf("\t┃        ┃\n");
		printf("\t┗━────━━━┛\n\n");

	}
	textcolor(0, 15);

}

void textcolor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
