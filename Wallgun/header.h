/**
header.h
자료형을 모아둔다. 나중에는 조건부 컴파일을 통해 상수도 저장해 보자.
**/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
// 기본 헤더들

#define random(n) (rand() % (n))
// Turboc.h 파일의 random 함수를 그대로 가져옴. 솔직히 rand()치기 귀찮음.

#define MAXBULLET 50
#define MAXACTOR 3
#define MAXMONSTER 50
#define MAXSPRITE 50
//최대 개체의 수

#define ULIM 0
#define DLIM 28
#define LLIM 0
#define RLIM 80
//최대 화면 넓이, Limit

#define DEFAULTCOLOR 0x07
#define DAMAGEDCOLOR 0xc4
//어디다 써야 될지 까먹음;

#define WEAPONNUM 9
#define MONSTERNUM 4
#define SPRITENUM 13
#define STATENUM 1
//상태, 몬스터, 무기, 스프라이트의 수 지정

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
// 자료형 정의

void gotoxy(int x, int y);
void setcursortype(CURSOR_TYPE c);
void clrscr();
void SetColor(int Color);
void Colorputsxy(const char* A, int B, short x, short y);
void PutEntityxy(short x, short y);
//이상 graphic.c의 함수 선언

boolean IfActormove(int x, int y);
boolean IsKeyDown(int Key);
void SpawnMon(int MNum, int MCha, int MQua);
void AI_1_Move(int MNum);
void SpawnSprite(int SNum, int Cool, short x, short y);
void AppearSprite(int SNum, int SCool, int SCha, int SQua);
//이상 entity.c의 함수 선언

void CountSub();
//이상 main.c의 함수 선언
