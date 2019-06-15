/**
main.c
프로그램의 전체적인 작동을 관리한다.
전체적인 큰 덩어리 함수를 여기 선언한다.
그래픽이나 엔터티에 관한 세부적인 함수는 각각의 헤더 파일에 정의한다.
**/

#include "header.h"
#include "constant.h"

int Score = 0;

int main()
{
    srand((unsigned)time(NULL));
    int i, j, k;
    int tim = 20000;
    setcursortype(NOCURSOR);
    Actor[0].x = 2; Actor[0].y = 1; Actor[0].Speed = 5; Actor[0].Curhp = 200; Actor[0].Maxhp = 200;
    Actor[0].exist = TRUE; Actor[0].WeaType = 0;
    //Actor[1].x = 20; Actor[1].y = 10; Actor[1].Speed = 8; Actor[1].Curhp = 200; Actor[1].Maxhp = 200;
    //Actor[1].exist = TRUE; Actor[1].WeaType = 1;
    Actor[2].x = 40; Actor[2].y = 17; Actor[2].Speed = 5; Actor[2].Curhp = 200; Actor[2].Maxhp = 200;
    Actor[2].exist = TRUE; Actor[2].WeaType = 0;
    PutEntityxy(Actor[0].x, Actor[0].y);
    PutEntityxy(Actor[2].x, Actor[2].y);
    //여기까지 초기 설정
    while(1){
    Bullet_Contact();
    Monster_Death();
    for(i=0; i<MAXACTOR; i++){
        if(Actor[i].Curhp <= 0 && Actor[i].exist==TRUE){
            Actor[i].exist = FALSE; PutEntityxy(Actor[i].x, Actor[i].y);
        }
    }
    //액터의 죽음 부분
    for(i=0; i<MAXACTOR; i++){
        if(Actor[i].exist) break;
        else if(i==MAXACTOR-1){
            clrscr(); printf("Game Over\nScore : %d", Score); Sleep(4000); return 0;
        }
    }
    //게임 오버 판정 부분
    Bullet_Move();
    Bullet_Contact();
    Actor_Act();
    for(i=0; i<MAXBULLET; i++){
            if(Bullet[i].exist==FALSE) continue;
            if(Bullet[i].x<=LLIM||Bullet[i].x>=RLIM||Bullet[i].y>=DLIM||Bullet[i].y<=ULIM){
                Bullet[i].exist = FALSE; PutEntityxy(Bullet[i].x, Bullet[i].y);
            }
        }
    //불릿의 소멸 부분
    Sprite_Act();
    SpawnMon(0, 300, 2);
    SpawnMon(1, 360, 2);
    SpawnMon(2, 800, 1);
    if(tim==0){
        Monster[0].exist = FALSE;
        SpawnMon(3, 0, 1); tim = -1;
    }
    AppearSprite(3, 1000, 1000, 1);
    AppearSprite(4, 1000, 1400, 1);
    //스프라이트, 몬스터 스폰 부분
    Sleep(10);
    //100fps
    for(i=0; i<MAXMONSTER; i++)
        if(Monster[i].exist&&Monster[i].NfSpeed==0&&Monster[i].State[0]==0) AI_1_Move(i);
    //AI적용함수 호출문, AI적용함수와 합칠 가능성 있음.
    gotoxy(84, 1); SetColor(DEFAULTCOLOR); printf("Player 1 HP : %-3d / %-3d | ARM : ", Actor[0].Curhp, Actor[0].Maxhp);
    if(Actor[0].WeaType>0) printf("%-3d", Actor[0].CurBul); else printf("∞");
    gotoxy(84, 2); SetColor(DEFAULTCOLOR); printf("Player 2 HP : %-3d / %-3d | ARM : ", Actor[2].Curhp, Actor[2].Maxhp);
    if(Actor[2].WeaType>0) printf("%-3d", Actor[2].CurBul); else printf("∞");
   // gotoxy(55, 3); SetColor(DEFAULTCOLOR); printf("Player 3 HP : %d ", Actor[2].Curhp);
    gotoxy(84, 4); SetColor(DEFAULTCOLOR); printf("Score : %d", Score);
    gotoxy(84, 5); SetColor(DEFAULTCOLOR); if(tim>0) printf("Time : %d   ", tim/50); else printf("Boss Appears!");
    CountSub();
    tim--;
    //화면 출력과 같은 카운팅 함수들
    }
}
//프로그램 실행부분

void Bullet_Contact()
{
    int i, j, k;
    for(i=0; i<MAXBULLET; i++){
        if(Bullet[i].exist==FALSE) continue;
        for(j=0; j<MAXMONSTER; j++){
            if(Monster[j].exist==FALSE) continue;
            if(Monster[j].x==Bullet[i].x&&Monster[j].y==Bullet[i].y&&Bullet[i].Who>=0){
                Monster[j].Curhp -= _BulletDamage[Bullet[i].WeaType];
                Bullet[i].exist = FALSE;
                if(Bullet[i].WeaType==6)
                    Bullet[i].exist = TRUE;
                PutEntityxy(Monster[j].x, Monster[j].y);
                if(Bullet[i].WeaType==5) Monster[j].State[0] = 200;
                if(Bullet[i].WeaType==3){
                    for(k=0; k<MAXMONSTER; k++){ if(Monster[k].exist==FALSE) continue;
                        if(abs(Monster[k].x-Bullet[i].x)==2&&abs(Monster[k].y-Bullet[i].y)==0||abs(Monster[k].x-Bullet[i].x)==0&&abs(Monster[k].y-Bullet[i].y)==1)
                            Monster[k].Curhp -= 40;
                    }
                    for(k=0; k<MAXACTOR; k++){ if(Actor[k].exist==FALSE) continue;
                        if(abs(Actor[k].x-Bullet[i].x)==2&&abs(Actor[k].y-Bullet[i].y)==0||abs(Actor[k].x-Bullet[i].x)==0&&abs(Actor[k].y-Bullet[i].y)==1)
                            Actor[k].Curhp -= 40;
                    }
                    SpawnSprite(0, 12, Bullet[i].x, Bullet[i].y);
                    SpawnSprite(1, 10, Bullet[i].x+2, Bullet[i].y);
                    SpawnSprite(1, 10, Bullet[i].x-2, Bullet[i].y);
                    SpawnSprite(1, 10, Bullet[i].x, Bullet[i].y+1);
                    SpawnSprite(1, 10, Bullet[i].x, Bullet[i].y-1);
                }
                if(Bullet[i].WeaType==7){
                    for(k=0; k<MAXMONSTER; k++){ if(Monster[k].exist==FALSE) continue;
                        switch(Bullet[i].Dir){
                        case UP: if(Bullet[i].x==Monster[k].x&&Bullet[i].y-Monster[k].y>0&&Bullet[i].y-Monster[k].y<3) Monster[k].Curhp -= 25; break;
                        case DOWN: if(Bullet[i].x==Monster[k].x&&Bullet[i].y-Monster[k].y<0&&Bullet[i].y-Monster[k].y>-3) Monster[k].Curhp -= 25; break;
                        case LEFT: if(Bullet[i].y==Monster[k].y&&Bullet[i].x-Monster[k].x>0&&Bullet[i].x-Monster[k].x<5) Monster[k].Curhp -= 25; break;
                        case RIGHT: if(Bullet[i].y==Monster[k].y&&Bullet[i].x-Monster[k].x<0&&Bullet[i].x-Monster[k].x>-5) Monster[k].Curhp -= 25;
                        }
                    }
                    for(k=0; k<MAXACTOR; k++){ if(Actor[k].exist==FALSE) continue;
                        switch(Bullet[i].Dir){
                        case UP: if(Bullet[i].x==Actor[k].x&&Bullet[i].y-Actor[k].y>0&&Bullet[i].y-Actor[k].y<3) Actor[k].Curhp -= 25; break;
                        case DOWN: if(Bullet[i].x==Actor[k].x&&Bullet[i].y-Actor[k].y<0&&Bullet[i].y-Actor[k].y>-3) Actor[k].Curhp -= 25; break;
                        case LEFT: if(Bullet[i].y==Actor[k].y&&Bullet[i].x-Actor[k].x>0&&Bullet[i].x-Actor[k].x<5) Actor[k].Curhp -= 25; break;
                        case RIGHT: if(Bullet[i].y==Actor[k].y&&Bullet[i].x-Actor[k].x<0&&Bullet[i].x-Actor[k].x>-5) Actor[k].Curhp -= 25;
                        }
                    }
                    switch(Bullet[i].Dir){
                    case UP: SpawnSprite(0, 12, Bullet[i].x, Bullet[i].y); SpawnSprite(1, 8, Bullet[i].x, Bullet[i].y-1); SpawnSprite(1, 8, Bullet[i].x, Bullet[i].y-2); break;
                    case DOWN: SpawnSprite(0, 12, Bullet[i].x, Bullet[i].y); SpawnSprite(1, 8, Bullet[i].x, Bullet[i].y+1); SpawnSprite(1, 8, Bullet[i].x, Bullet[i].y+2);break;
                    case LEFT: SpawnSprite(0, 12, Bullet[i].x, Bullet[i].y); SpawnSprite(1, 8, Bullet[i].x-2, Bullet[i].y); SpawnSprite(1, 8, Bullet[i].x-4, Bullet[i].y);break;
                    case RIGHT: SpawnSprite(0, 12, Bullet[i].x, Bullet[i].y); SpawnSprite(1, 8, Bullet[i].x+2, Bullet[i].y); SpawnSprite(1, 8, Bullet[i].x+4, Bullet[i].y);break;
                    }
                }
                if(Bullet[i].WeaType==8){
                    for(k=0; k<MAXMONSTER; k++){ if(Monster[k].exist==FALSE) continue;
                        if(abs(Monster[k].x-Bullet[i].x)/2+abs(Monster[k].y-Bullet[i].y)<3)
                            Monster[k].Curhp -= 50;
                        if(abs(Monster[k].x-Bullet[i].x)/2+abs(Monster[k].y-Bullet[i].y)<2)
                            Monster[k].Curhp -= 70;
                    }
                    for(k=0; k<MAXACTOR; k++){ if(Actor[k].exist==FALSE) continue;
                        if(abs(Actor[k].x-Bullet[i].x)/2+abs(Actor[k].y-Bullet[i].y)<3)
                            Actor[k].Curhp -= 50;
                        if(abs(Actor[k].x-Bullet[i].x)/2+abs(Actor[k].y-Bullet[i].y)<2)
                            Actor[k].Curhp -= 70;
                    }
                    SpawnSprite(0, 16, Bullet[i].x, Bullet[i].y);
                    SpawnSprite(1, 12, Bullet[i].x+2, Bullet[i].y);
                    SpawnSprite(1, 12, Bullet[i].x-2, Bullet[i].y);
                    SpawnSprite(1, 12, Bullet[i].x, Bullet[i].y+1);
                    SpawnSprite(1, 12, Bullet[i].x, Bullet[i].y-1);
                    SpawnSprite(2, 8, Bullet[i].x+4, Bullet[i].y);
                    SpawnSprite(2, 8, Bullet[i].x-4, Bullet[i].y);
                    SpawnSprite(2, 8, Bullet[i].x, Bullet[i].y+2);
                    SpawnSprite(2, 8, Bullet[i].x, Bullet[i].y-2);
                    SpawnSprite(2, 8, Bullet[i].x+2, Bullet[i].y+1);
                    SpawnSprite(2, 8, Bullet[i].x+2, Bullet[i].y-1);
                    SpawnSprite(2, 8, Bullet[i].x-2, Bullet[i].y+1);
                    SpawnSprite(2, 8, Bullet[i].x-2, Bullet[i].y-1);
                }
            }
        }
    }
    for(i=0; i<MAXBULLET; i++){
        if(Bullet[i].exist==FALSE) continue;
        for(j=0; j<MAXACTOR; j++){
            if(Actor[j].exist==FALSE) continue;
            if(Actor[j].x==Bullet[i].x&&Actor[j].y==Bullet[i].y&&Bullet[i].Who!=j){
                Actor[j].Curhp -= _BulletDamage[Bullet[i].WeaType];
                Bullet[i].exist = FALSE;
                PutEntityxy(Actor[j].x, Actor[j].y);
                if(Bullet[i].WeaType==6)
                    Bullet[i].exist = TRUE;
                if(Bullet[i].WeaType==3){
                    for(k=0; k<MAXMONSTER; k++){ if(Monster[k].exist==FALSE) continue;
                        if(abs(Monster[k].x-Bullet[i].x)==2&&abs(Monster[k].y-Bullet[i].y)==0||abs(Monster[k].x-Bullet[i].x)==0&&abs(Monster[k].y-Bullet[i].y)==1)
                            Monster[k].Curhp -= 40;
                    }
                    for(k=0; k<MAXACTOR; k++){ if(Actor[k].exist==FALSE) continue;
                        if(abs(Actor[k].x-Bullet[i].x)==2&&abs(Actor[k].y-Bullet[i].y)==0||abs(Actor[k].x-Bullet[i].x)==0&&abs(Actor[k].y-Bullet[i].y)==1)
                            Actor[k].Curhp -= 40;
                    }
                    SpawnSprite(0, 12, Bullet[i].x, Bullet[i].y);
                    SpawnSprite(1, 10, Bullet[i].x+2, Bullet[i].y);
                    SpawnSprite(1, 10, Bullet[i].x-2, Bullet[i].y);
                    SpawnSprite(1, 10, Bullet[i].x, Bullet[i].y+1);
                    SpawnSprite(1, 10, Bullet[i].x, Bullet[i].y-1);
                }
                if(Bullet[i].WeaType==7){
                    for(k=0; k<MAXMONSTER; k++){ if(Monster[k].exist==FALSE) continue;
                        switch(Bullet[i].Dir){
                        case UP: if(Bullet[i].x==Monster[k].x&&Bullet[i].y-Monster[k].y>0&&Bullet[i].y-Monster[k].y<3) Monster[k].Curhp -= 25; break;
                        case DOWN: if(Bullet[i].x==Monster[k].x&&Bullet[i].y-Monster[k].y<0&&Bullet[i].y-Monster[k].y>-3) Monster[k].Curhp -= 25; break;
                        case LEFT: if(Bullet[i].y==Monster[k].y&&Bullet[i].x-Monster[k].x>0&&Bullet[i].x-Monster[k].x<5) Monster[k].Curhp -= 25; break;
                        case RIGHT: if(Bullet[i].y==Monster[k].y&&Bullet[i].x-Monster[k].x<0&&Bullet[i].x-Monster[k].x>-5) Monster[k].Curhp -= 25;
                        }
                    }
                    for(k=0; k<MAXACTOR; k++){ if(Actor[k].exist==FALSE) continue;
                        switch(Bullet[i].Dir){
                        case UP: if(Bullet[i].x==Actor[k].x&&Bullet[i].y-Actor[k].y>0&&Bullet[i].y-Actor[k].y<3) Actor[k].Curhp -= 25; break;
                        case DOWN: if(Bullet[i].x==Actor[k].x&&Bullet[i].y-Actor[k].y<0&&Bullet[i].y-Actor[k].y>-3) Actor[k].Curhp -= 25; break;
                        case LEFT: if(Bullet[i].y==Actor[k].y&&Bullet[i].x-Actor[k].x>0&&Bullet[i].x-Actor[k].x<5) Actor[k].Curhp -= 25; break;
                        case RIGHT: if(Bullet[i].y==Actor[k].y&&Bullet[i].x-Actor[k].x<0&&Bullet[i].x-Actor[k].x>-5) Actor[k].Curhp -= 25;
                        }
                    }
                    switch(Bullet[i].Dir){
                    case UP: SpawnSprite(0, 12, Bullet[i].x, Bullet[i].y); SpawnSprite(1, 8, Bullet[i].x, Bullet[i].y-1); SpawnSprite(1, 8, Bullet[i].x, Bullet[i].y-2); break;
                    case DOWN: SpawnSprite(0, 12, Bullet[i].x, Bullet[i].y); SpawnSprite(1, 8, Bullet[i].x, Bullet[i].y+1); SpawnSprite(1, 8, Bullet[i].x, Bullet[i].y+2);break;
                    case LEFT: SpawnSprite(0, 12, Bullet[i].x, Bullet[i].y); SpawnSprite(1, 8, Bullet[i].x-2, Bullet[i].y); SpawnSprite(1, 8, Bullet[i].x-4, Bullet[i].y);break;
                    case RIGHT: SpawnSprite(0, 12, Bullet[i].x, Bullet[i].y); SpawnSprite(1, 8, Bullet[i].x+2, Bullet[i].y); SpawnSprite(1, 8, Bullet[i].x+4, Bullet[i].y);break;
                    }
                }
                if(Bullet[i].WeaType==8){
                    for(k=0; k<MAXMONSTER; k++){ if(Monster[k].exist==FALSE) continue;
                        if(abs(Monster[k].x-Bullet[i].x)/2+abs(Monster[k].y-Bullet[i].y)<3)
                            Monster[k].Curhp -= 50;
                        if(abs(Monster[k].x-Bullet[i].x)/2+abs(Monster[k].y-Bullet[i].y)<2)
                            Monster[k].Curhp -= 70;
                    }
                    for(k=0; k<MAXACTOR; k++){ if(Actor[k].exist==FALSE) continue;
                        if(abs(Actor[k].x-Bullet[i].x)/2+abs(Actor[k].y-Bullet[i].y)<3)
                            Actor[k].Curhp -= 50;
                        if(abs(Actor[k].x-Bullet[i].x)/2+abs(Actor[k].y-Bullet[i].y)<2)
                            Actor[k].Curhp -= 70;
                    }
                    SpawnSprite(0, 16, Bullet[i].x, Bullet[i].y);
                    SpawnSprite(1, 12, Bullet[i].x+2, Bullet[i].y);
                    SpawnSprite(1, 12, Bullet[i].x-2, Bullet[i].y);
                    SpawnSprite(1, 12, Bullet[i].x, Bullet[i].y+1);
                    SpawnSprite(1, 12, Bullet[i].x, Bullet[i].y-1);
                    SpawnSprite(2, 8, Bullet[i].x+4, Bullet[i].y);
                    SpawnSprite(2, 8, Bullet[i].x-4, Bullet[i].y);
                    SpawnSprite(2, 8, Bullet[i].x, Bullet[i].y+2);
                    SpawnSprite(2, 8, Bullet[i].x, Bullet[i].y-2);
                    SpawnSprite(2, 8, Bullet[i].x+2, Bullet[i].y+1);
                    SpawnSprite(2, 8, Bullet[i].x+2, Bullet[i].y-1);
                    SpawnSprite(2, 8, Bullet[i].x-2, Bullet[i].y+1);
                    SpawnSprite(2, 8, Bullet[i].x-2, Bullet[i].y-1);
                }

            }
        }
    }
}
//불릿과 액터, 몬스터 사이 충돌에 의한 상호작용

void Monster_Death()
{
    int i;
    for(i=0; i<MAXMONSTER; i++){
        if(Monster[i].exist==FALSE) continue;
        if(Monster[i].Curhp <= 0){
            Monster[i].exist = FALSE; Score += _Score[Monster[i].Type]; PutEntityxy(Monster[i].x, Monster[i].y);
            if(Monster[i].Type == 0)
                switch(random(30)){
                case 0: SpawnSprite(3, 1000, Monster[i].x, Monster[i].y); break;
                case 1: SpawnSprite(4, 1000, Monster[i].x, Monster[i].y); break;
                }
            else if(Monster[i].Type == 1)
                switch(random(60)){
                case 0: SpawnSprite(3, 1000, Monster[i].x, Monster[i].y); break;
                case 1: case 2:
                case 3: SpawnSprite(5, 1000, Monster[i].x, Monster[i].y); break;
                case 4: SpawnSprite(6, 1000, Monster[i].x, Monster[i].y); break;
                }
            else if(Monster[i].Type == 2)
                switch(random(14)){
                case 0: case 1: case 2: case 3:
                case 4: SpawnSprite(6, 1000, Monster[i].x, Monster[i].y); break;
                case 5:
                case 6: SpawnSprite(7, 1000, Monster[i].x, Monster[i].y); break;
                case 7: SpawnSprite(8, 1000, Monster[i].x, Monster[i].y); break;
                case 8: SpawnSprite(9, 1000, Monster[i].x, Monster[i].y); break;
                case 9: SpawnSprite(10, 1000, Monster[i].x, Monster[i].y); break;
                case 10:
                case 11: SpawnSprite(11, 1000, Monster[i].x, Monster[i].y); break;
                case 12:
                case 13: SpawnSprite(12, 1000, Monster[i].x, Monster[i].y); break;
                }
            else if(Monster[i].Type == 3){
            gotoxy(Monster[i].x, Monster[i].y); SetColor(0x4c); printf("※");
            gotoxy(84, 5); SetColor(DEFAULTCOLOR); printf("You Win. Score : %d",Score); Sleep(10000); exit(0);
            }
        }
    }
}
//몬스터의 죽음과 아이템 드롭 판정

void Bullet_Move()
{
    int i;
    for(i=0; i<MAXBULLET; i++){
            if(Bullet[i].exist==FALSE) continue;
            if(Bullet[i].NfSpeed==0){
                switch(Bullet[i].Dir){
                case UP: Bullet[i].y--; PutEntityxy(Bullet[i].x, Bullet[i].y+1); break;
                case DOWN: Bullet[i].y++; PutEntityxy(Bullet[i].x, Bullet[i].y-1); break;
                case LEFT: Bullet[i].x-=2; PutEntityxy(Bullet[i].x+2, Bullet[i].y); break;
                case RIGHT: Bullet[i].x+=2; PutEntityxy(Bullet[i].x-2, Bullet[i].y);break;
                }
                if(Bullet[i].WeaType==2&&random(30)==0){
                    if(Bullet[i].Dir==UP||Bullet[i].Dir==DOWN) Bullet[i].x+=2*(2*random(2)-1);
                    else Bullet[i].y+=2*random(2)-1;
                }
                PutEntityxy(Bullet[i].x, Bullet[i].y);
                Bullet[i].NfSpeed += Bullet[i].Speed;
            }
    }
}
//불릿의 이동 판정

void Actor_Act()
{
    static boolean IFONE[MAXACTOR];
    int aN, i;
    for(aN=0; aN<MAXACTOR; aN++){
    if(Actor[aN].exist){
        if(Actor[aN].NfSpeed == 0){
    if(IsKeyDown(_UPKEY[aN])&&Actor[aN].y>ULIM+1&&IfActormove(Actor[aN].x,Actor[aN].y-1)){
        Actor[aN].y--; Actor[aN].Dir = UP;
        PutEntityxy(Actor[aN].x, Actor[aN].y+1);
        PutEntityxy(Actor[aN].x, Actor[aN].y);
        Actor[aN].NfSpeed += Actor[aN].Speed;
    }
    if(IsKeyDown(_DOWNKEY[aN])&&Actor[aN].y<DLIM-1&&IfActormove(Actor[aN].x,Actor[aN].y+1)){
        Actor[aN].y++; Actor[aN].Dir = DOWN;
        PutEntityxy(Actor[aN].x, Actor[aN].y-1);
        PutEntityxy(Actor[aN].x, Actor[aN].y);
        Actor[aN].NfSpeed += Actor[aN].Speed;
    }
    if(IsKeyDown(_LEFTKEY[aN])&&Actor[aN].x>LLIM+2&&IfActormove(Actor[aN].x-2,Actor[aN].y)){
        Actor[aN].x-=2; Actor[aN].Dir = LEFT;
        PutEntityxy(Actor[aN].x+2, Actor[aN].y);
        PutEntityxy(Actor[aN].x, Actor[aN].y);
        Actor[aN].NfSpeed += Actor[aN].Speed;
    }
    if(IsKeyDown(_RIGHTKEY[aN])&&Actor[aN].x<RLIM-2&&IfActormove(Actor[aN].x+2,Actor[aN].y)){
        Actor[aN].x+=2; Actor[aN].Dir = RIGHT;
        PutEntityxy(Actor[aN].x-2, Actor[aN].y);
        PutEntityxy(Actor[aN].x, Actor[aN].y);
        Actor[aN].NfSpeed += Actor[aN].Speed;
    }
    }
    if(IsKeyDown(_UPKEY[aN])) Actor[aN].Dir = UP;
    if(IsKeyDown(_DOWNKEY[aN])) Actor[aN].Dir = DOWN;
    if(IsKeyDown(_LEFTKEY[aN])) Actor[aN].Dir = LEFT;
    if(IsKeyDown(_RIGHTKEY[aN])) Actor[aN].Dir = RIGHT;
        if(Actor[aN].NfCool == 0){
            if(IsKeyDown(_SHOTKEY[aN])&&(IFONE[aN]||_IfWeaponAuto[Actor[aN].WeaType])){
                for(i=0; i<MAXBULLET&&Bullet[i].exist==TRUE; i++) {;}
                if(Bullet[i].exist==FALSE){
                    IFONE[aN] = FALSE;
                    Bullet[i].exist = TRUE;
                    Bullet[i].x = Actor[aN].x;
                    Bullet[i].y = Actor[aN].y;
                    Bullet[i].WeaType = Actor[aN].WeaType;
                    Bullet[i].Dir = Actor[aN].Dir;
                    Bullet[i].Who = aN;
                    Bullet[i].Speed = _BulletSpeed[Bullet[i].WeaType];
                    Actor[aN].NfCool += _WeaponCool[Bullet[i].WeaType];
                    Actor[aN].CurBul -= 1;
                }
            }
        }
        if(!IsKeyDown(_SHOTKEY[aN])) IFONE[aN] = TRUE;
        if(Actor[aN].CurBul==0&&Actor[aN].WeaType>0) Actor[aN].WeaType = 0;
        }
        }
}
//액터의 행동에 관한 함수, 분리할 계획 있음

void Sprite_Act()
{
    int i, j;
    for(i=0; i<MAXSPRITE; i++) if(Sprite[i].NfCool==0&&Sprite[i].exist) {
            Sprite[i].exist = FALSE;
            PutEntityxy(Sprite[i].x, Sprite[i].y);
    }
    for(i=0; i<MAXSPRITE; i++){ if(Sprite[i].exist==FALSE) continue;
        if(Sprite[i].Type==3)
        for(j=0; j<MAXACTOR; j++){
            if(Sprite[i].x==Actor[j].x&&Sprite[i].y==Actor[j].y){
                Actor[j].Curhp = Actor[j].Maxhp;
                Sprite[i].exist = FALSE;
            }
        }
        if(Sprite[i].Type==4)
        for(j=0; j<MAXACTOR; j++){
            if(Sprite[i].x==Actor[j].x&&Sprite[i].y==Actor[j].y){
                Actor[j].WeaType = 1;
                Actor[j].CurBul = 30;
                Sprite[i].exist = FALSE;
            }
        }
        if(Sprite[i].Type==5)
        for(j=0; j<MAXACTOR; j++){
            if(Sprite[i].x==Actor[j].x&&Sprite[i].y==Actor[j].y){
                Actor[j].WeaType = 2;
                Actor[j].CurBul = 175;
                Sprite[i].exist = FALSE;
            }
        }
        if(Sprite[i].Type==6)
        for(j=0; j<MAXACTOR; j++){
            if(Sprite[i].x==Actor[j].x&&Sprite[i].y==Actor[j].y){
                if(random(7)){
                    Actor[j].WeaType = 3;
                    Actor[j].CurBul = 8;
                    Sprite[i].exist = FALSE;
                }
                else{
                    Actor[j].WeaType = 8;
                    Actor[j].CurBul = 6;
                    Sprite[i].exist = FALSE;
                }

            }
        }
        if(Sprite[i].Type==7)
        for(j=0; j<MAXACTOR; j++){
            if(Sprite[i].x==Actor[j].x&&Sprite[i].y==Actor[j].y){
                Actor[j].WeaType = 4;
                Actor[j].CurBul = 20;
                Sprite[i].exist = FALSE;
            }
        }
        if(Sprite[i].Type==8)
        for(j=0; j<MAXACTOR; j++){
            if(Sprite[i].x==Actor[j].x&&Sprite[i].y==Actor[j].y){
                Actor[j].WeaType = 5;
                Actor[j].CurBul = 48;
                Sprite[i].exist = FALSE;
            }
        }
        if(Sprite[i].Type==9)
        for(j=0; j<MAXACTOR; j++){
            if(Sprite[i].x==Actor[j].x&&Sprite[i].y==Actor[j].y){
                Actor[j].WeaType = 6;
                Actor[j].CurBul = 48;
                Sprite[i].exist = FALSE;
            }
        }
        if(Sprite[i].Type==10)
        for(j=0; j<MAXACTOR; j++){
            if(Sprite[i].x==Actor[j].x&&Sprite[i].y==Actor[j].y){
                Actor[j].WeaType = 7;
                Actor[j].CurBul = 48;
                Sprite[i].exist = FALSE;
            }
        }
        if(Sprite[i].Type==11)
        for(j=0; j<MAXACTOR; j++){
            if(Sprite[i].x==Actor[j].x&&Sprite[i].y==Actor[j].y){
                Actor[j].Maxhp += 100;
                Actor[j].Curhp = Actor[j].Maxhp;
                Sprite[i].exist = FALSE;
            }
        }
        if(Sprite[i].Type==12)
        for(j=0; j<MAXACTOR; j++){
            if(Sprite[i].x==Actor[j].x&&Sprite[i].y==Actor[j].y){
                Actor[j].Speed--;
                if(Actor[j].Speed<3) Actor[j].Speed=3;
                Sprite[i].exist = FALSE;
            }
        }
    }
}
//스프라이트의 행동에 관한 함수, 분리할 계획 있음

void CountSub()
{
    int i;
    int aN;
    for(aN=0; aN<MAXACTOR; aN++){
    if(Actor[aN].NfSpeed>0)
        Actor[aN].NfSpeed--;
    if(Actor[aN].NfCool>0)
        Actor[aN].NfCool--;
    }
    for(i=0; i<MAXBULLET; i++)
        if(Bullet[i].NfSpeed>0||Bullet[i].WeaType==-2)
            Bullet[i].NfSpeed--;
    for(i=0; i<MAXMONSTER; i++){
        if(Monster[i].NfSpeed>0)
            Monster[i].NfSpeed--;
        if(Monster[i].State[0]>0)
            Monster[i].State[0]--;
    }

    for(i=0; i<MAXSPRITE; i++)
        if(Sprite[i].NfCool>0)
            Sprite[i].NfCool--;
}
//카운팅 변수 감소시키는 함수
