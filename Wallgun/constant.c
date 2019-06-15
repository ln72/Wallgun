/**
constant.c
상수를 정의하는 파일이다. 나중에는 조건부 컴파일로 처리해 보자.
**/

#include "header.h"

const char* _BulletShape[WEAPONNUM][4] = {"＊","＊","＊","＊","┃","┃","━","━","||","||","〓","〓","⊙","⊙","⊙","⊙","┃","┃","━","━"
    ,"↑ ","↓ ","←","→","↑ ","↓ ","←","→","↑ ","↓ ","←","→","★","★","★","★"};
const int _BulletSpeed[WEAPONNUM] = {5, 1, 3, 9, 0, 4, 6, 5, 8};
const int _BulletDamage[WEAPONNUM] = {5, 12, 4, 80, 85, 20, 2, 40, 70};
const boolean _IfWeaponAuto[WEAPONNUM] = {FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE};
const int _WeaponCool[WEAPONNUM] = {20, 16, 3, 130, 60, 11, 13, 17, 300};
const int _BulletColor[WEAPONNUM] = {0x0e, 0x0e, 0x0e, 0x06, 0x0e, 0x06, 0x0d, 0x08, 0x0b};

const int _Score[MAXMONSTER] = {5, 6, 100};

const int _ActorColor[MAXACTOR] = {0x0c, 0x09, 0x0e, 0x0b};
const int _UPKEY[MAXACTOR] = {0x57, 0x49, 0x68};
const int _DOWNKEY[MAXACTOR] = {0x53, 0x4b, 0x65};
const int _LEFTKEY[MAXACTOR] = {0x41, 0x4a, 0x64};
const int _RIGHTKEY[MAXACTOR] = {0x44, 0x4c, 0x66};
const int _SHOTKEY[MAXACTOR] = {0x47, 0x50, 0x6b};

const char* _SpriteShape[SPRITENUM] = {"●", "●", "●", "＋", "Ａ", "Ｍ", "Ｇ", "Ｓ", "Ｂ", "Ｂ", "Ｂ", "＋", "§"};
const int _SpriteColor[SPRITENUM] = {0x04, 0x0c, 0x0e, 0x6c, 0x6e, 0x6e, 0x6e, 0x6e, 0x6a, 0x6d, 0x67, 0xae, 0xae};

const char* _MonsterShape[MONSTERNUM][4] = {"＃","＃","＃","＃","△","▽","◁","▷","★","★","★","★","◈","◈","◈","◈"};
const int _MonsterSpeed[MONSTERNUM] = {49, 21, 35, 67};
const int _MonsterColor[MONSTERNUM] = {0x02, 0x02, 0x0c, 0x4d};
const int _MonsterHp[MONSTERNUM] = {13, 6, 170, 2000};
const int _MonsterAtt[MONSTERNUM] = {2, 1, 2, 6};
const int _MonsterCool[MONSTERNUM] = {200, 250, 200, 550};
const int _MonsterAI[MONSTERNUM] = {0, 0, 0, 0};
