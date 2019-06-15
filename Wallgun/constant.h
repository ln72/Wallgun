/**
constant.h
상수를 정의하는 헤더이다. 나중에는 조건부 컴파일로 처리해 보자.
**/

extern char* _BulletShape[WEAPONNUM][4];
extern int _BulletSpeed[WEAPONNUM];
extern int _BulletDamage[WEAPONNUM];
extern boolean _IfWeaponAuto[WEAPONNUM];
extern int _WeaponCool[WEAPONNUM];
extern int _BulletColor[WEAPONNUM];

extern int _Score[MAXMONSTER];

extern int _ActorColor[MAXACTOR];
extern int _UPKEY[MAXACTOR];
extern int _DOWNKEY[MAXACTOR];
extern int _LEFTKEY[MAXACTOR];
extern int _RIGHTKEY[MAXACTOR];
extern int _SHOTKEY[MAXACTOR];

extern char* _SpriteShape[SPRITENUM];
extern int _SpriteColor[SPRITENUM];

extern char* _MonsterShape[MONSTERNUM][4];
extern int _MonsterSpeed[MONSTERNUM];
extern int _MonsterColor[MONSTERNUM];
extern int _MonsterHp[MONSTERNUM];
extern int _MonsterAtt[MONSTERNUM];
extern int _MonsterCool[MONSTERNUM];
extern int _MonsterAI[MONSTERNUM];
