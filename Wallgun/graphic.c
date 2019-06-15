/**
graphic.c
�׷���(���)�� ���õ� �Լ��� �����Ѵ�.
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
// Ŀ�� Ÿ�� ���� �Լ�, Turboc.h���� ������;

void clrscr()
{
	system("cls");
}
//clrscr �Լ� ���� ������

void SetColor(int Color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
}
void Colorputsxy(const char* A, int B, short x, short y){
    gotoxy(x,y); SetColor(B); puts(A);
}
//���� ���� �Լ�, ������ ����� ���ڿ� ��� �Լ�

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
            case UP: Colorputsxy("��", _ActorColor[i], x, y); return;
            case DOWN: Colorputsxy("��", _ActorColor[i], x, y); return;
            case LEFT: Colorputsxy("��", _ActorColor[i], x, y); return;
            case RIGHT: Colorputsxy("��", _ActorColor[i], x, y); return;
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
    Colorputsxy("��", DEFAULTCOLOR, x, y);
}
//x,y ��ǥ�� ����Ƽ ǥ�� ���¸� �����ϴ� �Լ��̴�. ���� �̰͸� ����
