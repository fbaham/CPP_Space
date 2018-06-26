#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ESCAPE 27

void gotoxy(int x, int y){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);
}

void ocultar_cursor(bool visible){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 50;
	cci.bVisible = visible;
	SetConsoleCursorInfo(hCon, &cci);
}

void pintar_limites(){
	for(int x = 1 ; x < 78; x++){
		gotoxy(x,2); printf("%c",205 );
		gotoxy(x,30); printf("%c",205 );
	}

	for(int y = 3 ; y < 30 ; y++){
		gotoxy(1,y); printf("%c", 186);
		gotoxy(77,y); printf("%c", 186);
	}

	gotoxy(1,2); printf("%c", 201);
	gotoxy(1,30); printf("%c", 200);
	gotoxy(77,2); printf("%c", 187);
	gotoxy(77,30); printf("%c", 188);
}

class NAVE{
	// private
	int x, y;
	int salud;
	int vidas;
public:
	// not private
	NAVE(int _x, int _y, int _salud, int _vidas): x(_x), y(_y), salud(_salud), vidas(_vidas){}
	void pintar();
	void borrar();
	void mover();
	void pintar_salud();
	void muerte();
};

void NAVE::pintar(){
	gotoxy(x, y); printf("  %c", 30);
	gotoxy(x, y + 1); printf(" %c%c%c", 40, 207, 41);
	gotoxy(x, y + 2); printf("%c%c %c%c", 30, 190, 190, 30);
}

void NAVE::borrar(){
	gotoxy(x, y); printf("     ");
	gotoxy(x, y + 1); printf("     ");
	gotoxy(x, y + 2); printf("     ");
}

void NAVE::mover(){
	if (kbhit())
		{
			char tecla = getch();
			borrar();
			if(tecla == IZQUIERDA && x > 2) x--;
			if(tecla == DERECHA && x + 6 < 78) x++;
			if(tecla == ARRIBA && y > 3) y--;
			if(tecla == ABAJO && y + 3 < 30) y++;
			if(tecla == 'e') salud--;
			pintar();
			pintar_salud();
		}
}

void NAVE::pintar_salud(){
	gotoxy(80, 3); printf("Salud");
	gotoxy(85,3); printf("     ");
	for (int i = 0; i < salud; ++i)
	{
		gotoxy(86 + i, 3); printf("%c", 3);
	}
	gotoxy(80, 4); printf("Vidas %d", vidas);
}

void NAVE::muerte(){
	if(salud == 0){
		borrar();
		gotoxy(x, y); printf("*****");
		gotoxy(x, y + 1); printf("*****");
		gotoxy(x, y + 2); printf("*****");
		Sleep(200);
		borrar();
		gotoxy(x, y); printf("* * *");
		gotoxy(x, y + 1); printf(" * * ");
		gotoxy(x, y + 2); printf("* * *");
		Sleep(200);
		borrar();

		vidas --;
		salud = 4;

		pintar_salud();
		pintar();
	}
}

class Asteroid {
	int x, y;
public:
	Asteroid(int _x, int _y): x(_y), y(_y){}
	void pintar();
	void mover();
};

void Asteroid::pintar(){
	gotoxy(x, y); printf("%c", 184);
}

void Asteroid::mover(){
	gotoxy(x, y); printf(" ");
	y++;
	if(y > 29){
		x = rand()%77;
		y = 4;
	}
	pintar();
}

int main(){
	ocultar_cursor(FALSE);
	pintar_limites();
	NAVE N(7, 7, 4, 5);
	N.pintar();
	N.pintar_salud();
	Asteroid asteroid(10, 4);
	bool game_over = false;
	while(!game_over){
		asteroid.mover();
		N.muerte();
		N.mover();
		Sleep(30);
	}

	return 0;
}
