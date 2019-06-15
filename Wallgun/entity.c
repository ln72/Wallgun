/**
entity.c
엔터티 간의 상호작용에 대한 함수를 정의한다. 엔터티는 몹, 플레이어, 스프라이트, 불릿 이 4개이다.
**/

#include "header.h"
#include "constant.h"

boolean IfActormove(int x, int y){
    int i;
    for(i=0; i<MAXMONSTER; i++){
        if(Monster[i].exist==FALSE) continue;
        if(Monster[i].x==x&&Monster[i].y==y) return 0;
    }
    for(i=0; i<MAXACTOR; i++){
        if(Actor[i].exist==FALSE) continue;
        if(Actor[i].x==x&&Actor[i].y==y) return 0;
    }
    return 1;
}
//그 칸으로 액터가 움직일 수 있냐? 라는 함수

boolean IsKeyDown(int Key){
    return ((GetAsyncKeyState(Key) & 0x8000) != 0);
}
//이동 관련 함수

void SpawnMon(int MNum, int MCha, int MQua){
    int i, j;
    if(MCha==0 || random(MCha)==0)
        for(i=0; i<MAXMONSTER; i++){
            if(Monster[i].exist==FALSE){
            Monster[i].exist = TRUE;
            Monster[i].Maxhp = _MonsterHp[MNum];
            Monster[i].Curhp = _MonsterHp[MNum];
            Monster[i].Speed = _MonsterSpeed[MNum];
            Monster[i].NfSpeed = random(_MonsterSpeed[MNum]) + 1;
            Monster[i].NfCool = _MonsterCool[MNum];
            Monster[i].Type = MNum;
            Monster[i].Att = _MonsterAtt[MNum];
            Monster[i].State[0] = 0;
            while(1){
                Monster[i].x = random(RLIM/2)*2 + LLIM;
                Monster[i].y = random(DLIM) + ULIM;
                for(j=0; j<MAXACTOR; j++)
                if(Actor[j].x==Monster[i].x&&Actor[j].y==Monster[i].y&&Actor[j].exist) break;
                if(j==MAXACTOR) break;
                else continue;
            }
            PutEntityxy(Monster[i].x, Monster[i].y);
            MQua--; if(MQua==0) break;
            }
        }
}
//몬스터 스폰 함수

void AI_1_Move(int MNum){
    int i, Min=RLIM+DLIM, MinN;
    int Orx = Monster[MNum].x, Ory = Monster[MNum].y;
    for(i=0; i<MAXACTOR; i++){
        if(Actor[i].exist==FALSE) continue;
        if(Min > abs(Actor[i].x-Monster[MNum].x)+abs(Actor[i].y-Monster[MNum].y)){
            Min = abs(Actor[i].x-Monster[MNum].x)+abs(Actor[i].y-Monster[MNum].y);
            MinN = i;
        }
    }
    if(abs(Actor[MinN].x-Monster[MNum].x)<3&&abs(Actor[MinN].y-Monster[MNum].y)<2){
        Actor[MinN].Curhp -= Monster[MNum].Att;
        return;
    }
    if(abs(Actor[MinN].x-Monster[MNum].x)/2>abs(Actor[MinN].y-Monster[MNum].y)){
        if((Actor[MinN].x>Monster[MNum].x)&&IfActormove(Monster[MNum].x+2, Monster[MNum].y)){
           Monster[MNum].x+=2; Monster[MNum].Dir=RIGHT;
        }
        else if((Actor[MinN].x<Monster[MNum].x)&&IfActormove(Monster[MNum].x-2, Monster[MNum].y)){
            Monster[MNum].x-=2; Monster[MNum].Dir=LEFT;
        }
    }
    else{
        if((Actor[MinN].y>Monster[MNum].y)&&IfActormove(Monster[MNum].x, Monster[MNum].y+1)){
            Monster[MNum].y++;Monster[MNum].Dir=DOWN;
        }
        else if((Actor[MinN].y<Monster[MNum].y)&&IfActormove(Monster[MNum].x, Monster[MNum].y-1)){
           Monster[MNum].y--; Monster[MNum].Dir=UP;
        }
    }
    if(Monster[MNum].Type==3){
        for(i=0; i<MAXBULLET; i++){ if(Bullet[i].exist==TRUE) continue;
            Bullet[i].exist=TRUE;
            Bullet[i].Dir=RIGHT;
            Bullet[i].Who=-1;
            Bullet[i].Speed=3;
            Bullet[i].WeaType=8;
            Bullet[i].x=Monster[MNum].x+2;
            Bullet[i].y=Monster[MNum].y;
            break;
        }
        for(i=0; i<MAXBULLET; i++){ if(Bullet[i].exist==TRUE) continue;
            Bullet[i].exist=TRUE;
            Bullet[i].Dir=LEFT;
            Bullet[i].Who=-1;
            Bullet[i].Speed=3;
            Bullet[i].WeaType=8;
            Bullet[i].x=Monster[MNum].x-2;
            Bullet[i].y=Monster[MNum].y;
            break;
        }
        for(i=0; i<MAXBULLET; i++){ if(Bullet[i].exist==TRUE) continue;
            Bullet[i].exist=TRUE;
            Bullet[i].Dir=DOWN;
            Bullet[i].Who=-1;
            Bullet[i].Speed=3;
            Bullet[i].WeaType=8;
            Bullet[i].x=Monster[MNum].x;
            Bullet[i].y=Monster[MNum].y+1;
            break;
        }
        for(i=0; i<MAXBULLET; i++){ if(Bullet[i].exist==TRUE) continue;
            Bullet[i].exist=TRUE;
            Bullet[i].Dir=UP;
            Bullet[i].Who=-1;
            Bullet[i].Speed=3;
            Bullet[i].WeaType=8;
            Bullet[i].x=Monster[MNum].x;
            Bullet[i].y=Monster[MNum].y-1;
            break;
        }
    }
    PutEntityxy(Orx, Ory);
    PutEntityxy(Monster[MNum].x, Monster[MNum].y);
    Monster[MNum].NfSpeed += Monster[MNum].Speed;
}
//몬스터 AI적용 함수
void SpawnSprite(int SNum, int Cool, short x, short y){
    int i;
    for(i=0; i<MAXSPRITE; i++){ if(Sprite[i].exist==TRUE) continue;
        Sprite[i].exist = TRUE;
        Sprite[i].NfCool = Cool;
        Sprite[i].x = x;
        Sprite[i].y = y;
        Sprite[i].Type = SNum;
        PutEntityxy(x, y);
        return;
    }
}
//스프라이트를 생성하는 함수

void AppearSprite(int SNum, int SCool, int SCha, int SQua){
    int i, j;
    if(random(SCha)==0)
        for(i=0; i<MAXSPRITE; i++){
            if(Sprite[i].exist==FALSE){
            Sprite[i].exist = TRUE;
            Sprite[i].Type = SNum;
            Sprite[i].NfCool = SCool;
           while(1){
                Sprite[i].x = random(RLIM/2-1)*2 + LLIM+ 2;
                Sprite[i].y = random(DLIM-1) + ULIM + 1;
                for(j=0; j<MAXSPRITE; j++)
                if(Sprite[j].x==Sprite[i].x&&Sprite[j].y==Sprite[i].y&&Sprite[j].exist&&i!=j) break;
                if(j==MAXSPRITE) break;
                else continue;
            }
            PutEntityxy(Sprite[i].x, Sprite[i].y);
            SQua--; if(SQua==0) return;
            }
        }
}
//스프라이트를 확률로 생성하는 함수

