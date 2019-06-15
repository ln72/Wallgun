/**
header.h
�ڷ����� ��Ƶд�. ���߿��� ���Ǻ� �������� ���� ����� ������ ����.
**/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
// �⺻ �����

#define random(n) (rand() % (n))
// Turboc.h ������ random �Լ��� �״�� ������. ������ rand()ġ�� ������.

#define MAXBULLET 50
#define MAXACTOR 3
#define MAXMONSTER 50
#define MAXSPRITE 50
//�ִ� ��ü�� ��

#define ULIM 0
#define DLIM 28
#define LLIM 0
#define RLIM 80
//�ִ� ȭ�� ����, Limit

#define DEFAULTCOLOR 0x07
#define DAMAGEDCOLOR 0xc4
//���� ��� ���� �����;

#define WEAPONNUM 9
#define MONSTERNUM 4
#define SPRITENUM 13
#define STATENUM 1
//����, ����, ����, ��������Ʈ�� �� ����

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
enum Direction {UP,DOWN,LEFT,RIGHT};

struct Actor{
boolean exist;
short Type;
short WeaType;
enum Direction Dir;
int Maxhp;
int Curhp;
short x, y;
int Speed;
int NfSpeed;
int NfCool;
int CurBul;
}Actor[MAXACTOR];

struct Bullet{
boolean exist;
short Who;
short WeaType;
enum Direction Dir;
short x, y;
int Speed;
int NfSpeed;
}Bullet[MAXBULLET];

struct Monster{
boolean exist;
short Type;
enum Direction Dir;
int Maxhp;
int Curhp;
short x, y;
int Speed;
int NfSpeed;
int NfCool;
int Att;
int State[STATENUM];
}Monster[MAXMONSTER];

struct Sprite{
boolean exist;
short Type;
short x, y;
int NfCool;
}Sprite[MAXSPRITE];
// �ڷ��� ����

void gotoxy(int x, int y);
void setcursortype(CURSOR_TYPE c);
void clrscr();
void SetColor(int Color);
void Colorputsxy(const char* A, int B, short x, short y);
void PutEntityxy(short x, short y);
//�̻� graphic.c�� �Լ� ����

boolean IfActormove(int x, int y);
boolean IsKeyDown(int Key);
void SpawnMon(int MNum, int MCha, int MQua);
void AI_1_Move(int MNum);
void SpawnSprite(int SNum, int Cool, short x, short y);
void AppearSprite(int SNum, int SCool, int SCha, int SQua);
//�̻� entity.c�� �Լ� ����

void CountSub();
//�̻� main.c�� �Լ� ����
