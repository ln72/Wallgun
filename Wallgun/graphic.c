/**
graphic.c
그래픽(출력)에 관련된 함수를 정의한다.
**/

#include "header.h"
#include "constant.h"

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X=x;
	Cur.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);
}
//gotoxy

void setcursortype(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO CurInfo;

	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize=1;
		CurInfo.bVisible=FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize=100;
		CurInfo.bVisible=TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize=20;
		CurInfo.bVisible=TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);
}
// 커서 타입 지정 함수, Turboc.h에서 베껴옴;

void clrscr()
{
	system("cls");
}
//clrscr 함수 역시 베껴옴

void SetColor(int Color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
}
void Colorputsxy(const char* A, int B, short x, short y){
    gotoxy(x,y); SetColor(B); puts(A);
}
//색깔 지정 함수, 지정된 색깔로 문자열 출력 함수

void PutEntityxy(short x, short y)
{
    int i, j;
    for(i=0; i<MAXSPRITE; i++){
        if(Sprite[i].exist==FALSE||Sprite[i].x!=x||Sprite[i].y!=y) continue;
        Colorputsxy(_SpriteShape[Sprite[i].Type], _SpriteColor[Sprite[i].Type], x, y);
        return;
    }
    for(i=0; i<MAXACTOR; i++){
        if(Actor[i].exist==FALSE||Actor[i].x!=x||Actor[i].y!=y) continue;
        switch(Actor[i].Dir){
            case UP: Colorputsxy("▲", _ActorColor[i], x, y); return;
            case DOWN: Colorputsxy("▼", _ActorColor[i], x, y); return;
            case LEFT: Colorputsxy("◀", _ActorColor[i], x, y); return;
            case RIGHT: Colorputsxy("▶", _ActorColor[i], x, y); return;
        }
    }
    for(i=0; i<MAXMONSTER; i++){
        if(Monster[i].exist==FALSE||Monster[i].x!=x||Monster[i].y!=y) continue;
        Colorputsxy(_MonsterShape[Monster[i].Type][Monster[i].Dir], _MonsterColor[Monster[i].Type], x, y);
        return;
    }
    for(i=0; i<MAXBULLET; i++){
        if(Bullet[i].exist==FALSE||Bullet[i].x!=x||Bullet[i].y!=y) continue;
        Colorputsxy(_BulletShape[Bullet[i].WeaType][Bullet[i].Dir], _BulletColor[Bullet[i].WeaType], x, y);
        return;
    }
    Colorputsxy("　", DEFAULTCOLOR, x, y);
}
//x,y 좌표의 엔터티 표현 상태를 갱신하는 함수이다. 거의 이것만 쓸듯
