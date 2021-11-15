#include <stdio.h>
#define LOSE -1000
#define WIN 1000
#define EMPTY 12
int MAX_KIER[]={8,8,4,4,8,3,8,8,4,4,8,3,0};
int MAX_ODL[]={2,8,8,8,2,2,2,8,8,8,2,2,0};
int WX[12][8]={{0,1,1,1,0,-1,-1,-1},{0,1,1,1,0,-1,-1,-1},{0,1,0,-1},{1,1,-1,-1},{1,2,2,1,-1,-2,-2,-1},{-1,0,1},{0,1,1,1,0,-1,-1,-1},{0,1,1,1,0,-1,-1,-1},{0,1,0,-1},{1,1,-1,-1},{1,2,2,1,-1,-2,-2,-1},{-1,0,1} };
int WY[12][8]={{-1,-1,0,1,1,1,0,-1},{-1,-1,0,1,1,1,0,-1},{-1,0,1,0},{-1,1,1,-1},{-2,-1,1,2,2,1,-1,-2},{-1,-1,-1},{-1,-1,0,1,1,1,0,-1},{-1,-1,0,1,1,1,0,-1},{-1,0,1,0},{-1,1,1,-1},{-2,-1,1,2,2,1,-1,-2},{1,1,1} };

int ocena(char plansza[8][8])
{
    int w=0;
    int wart[13]={LOSE, -9, -5, -3, -3, -1, WIN, 9, 5, 3, 3, 1, 0};
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            w+=wart[plansza[i][j]];
        }
    }
    return w;
}

int najlepszy_ruch(char plansza[8][8],int tryb,int *x, int *y,int *o,int *k)
{

    int px,py,dir,dist,dx,dy,kpom,opom,xpom,ypom,wmax=2*LOSE,wmin= 2 * WIN;
    int wynik=ocena(plansza);
    if(tryb==0 || 2*wynik > WIN || 2 * wynik < LOSE)
    {return wynik;}
    if(tryb%2==0)
    {
        for(px=0; px<8;px++) //dwie pętle sprawdzaja kazde pole oraz if szukajacy figur komputera
        {
            for(py=0; py<8;py++)
            {
                if(plansza[px][py]>=6 && plansza[px][py]<12)//sprawdza czy na polu stoi figura komputera
                {

                    for(dir=0;dir<MAX_KIER[plansza[px][py]];dir++)//petla mozliwosci ruchow
                    {
                        for (dist = 1; dist < MAX_ODL[plansza[px][py]]; dist++)//petla dystansu o ile moze sie przesunac
                        {
                            dx=(dist-1)*WX[plansza[px][py]][dir];
                            dy=(dist-1)*WY[plansza[px][py]][dir];
                            if(dist>=2 && plansza[px+dx][py+dy] != EMPTY)
                            {
                                break;
                            }
                            dx=dist*WX[plansza[px][py]][dir];
                            dy=dist*WY[plansza[px][py]][dir];
                            if(0<=px+dx && px+dx<8 && 0<=py+dy && py+dy<8)
                            {
                                if(plansza[px][py]!=11 || ((dx==0 && plansza[px + dx][py + dy] == EMPTY) || (dx != 0 && plansza[px + dx][py + dy] < 6))){
                                    if(plansza[px + dx][py + dy]<6 || plansza[px + dx][py + dy] == EMPTY) {
                                        int cobylo = plansza[px+dx][py+dy];
                                        int fig_akt=plansza[px][py];
                                        plansza[px + dx][py + dy] = plansza[px][py];
                                        plansza[px][py] = EMPTY;
                                        if(plansza[px+dx][py+dy]==11 && py+dy==7)
                                        {
                                            plansza[px+dx][py+dy]=7;
                                        }
                                        wynik = najlepszy_ruch(plansza, tryb - 1, &xpom, &ypom, &opom, &kpom);

                                        if (wmax < wynik) {
                                            wmax = wynik;
                                            *x = px;
                                            *y = py;
                                            *o = dist;
                                            *k = dir;
                                        }

                                        plansza[px][py]=fig_akt;
                                        plansza[px+dx][py+dy]=cobylo;

                                    }
                                }
                            }

                        }
                    }
                }
            }
        }
        return wmax;
    }
    if(tryb%2)
    {
        for(px=0; px<8;px++) //dwie pętle sprawdzaja kazde pole oraz if szukajacy figur gracza
        {
            for(py=0; py<8;py++)
            {
                if(plansza[px][py]<6)
                {
                    for(dir=0;dir<MAX_KIER[plansza[px][py]];dir++)
                    {
                        for (dist = 1; dist < MAX_ODL[plansza[px][py]]; dist++)
                        {
                            dx=(dist-1)*WX[plansza[px][py]][dir];
                            dy=(dist-1)*WY[plansza[px][py]][dir];
                            if(dist>=2 && plansza[px+dx][py+dy] != EMPTY)
                            {
                                break;
                            }
                            dx=dist*WX[plansza[px][py]][dir];
                            dy=dist*WY[plansza[px][py]][dir];
                            if(0<=px+dx && px+dx<8 && 0<=py+dy && py+dy<8)
                            {
                                if(plansza[px][py]!=11 || ((dx==0 && plansza[px + dx][py + dy] == EMPTY) || (dx != 0 && plansza[px + dx][py + dy] >= 6))){
                                    if(plansza[px + dx][py + dy]>=6 || plansza[px + dx][py + dy] == EMPTY) {
                                        int cobylo = plansza[px+dx][py+dy];
                                        int fig_akt=plansza[px][py];
                                        plansza[px + dx][py + dy] = plansza[px][py];
                                        plansza[px][py] = EMPTY;
                                        if(plansza[px+dx][py+dy]==5 && py+dy==0)
                                        {
                                            plansza[px+dx][py+dy]=1;
                                        }
                                        wynik = najlepszy_ruch(plansza, tryb - 1, &xpom, &ypom, &opom, &kpom);

                                        if (wmin > wynik) {
                                            wmin = wynik;
                                            *x = px;
                                            *y = py;
                                            *o = dist;
                                            *k = dir;
                                        }
                                        plansza[px][py]=fig_akt;
                                        plansza[px+dx][py+dy]=cobylo;

                                    }
                                }
                            }

                        }
                    }
                }
            }
        }
        return wmin;
    }

}
void board(char tab[8][8])
{
    char fig[20]= "KHWGSPkhwgsp";
    for (int i = 0; i < 8; i++)
    {

        printf("_____________________________________________     \n");
        //printf("|     |     |     |     |     |     |     |     | \n");
        printf("|  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  | \n", fig[tab[i][0]], fig[tab[i][1]], fig[tab[i][2]], fig[tab[i][3]], fig[tab[i][4]], fig[tab[i][5]], fig[tab[i][6]], fig[tab[i][7]]);
        //printf("|     |     |     |     |     |     |     |     | \n");
    }
    printf("_____________________________________________     \n");
}

int main() {
    //przyjmujÄc: 0-krĂłl, 1-hetman, 2-wieĹźa, 3-goniec, 4-skoczek,
//5-pionek, 6-krĂłl_k, 7-hetman_k, 8-wieĹźa_k, 9-goniec_k,
//10-skoczek_k, 11-pionek_k, 12-pole puste


    char plansza[8][8] = {8, 11, 12, 12, 12, 12, 5, 2,
                          10, 11, 12, 12, 12, 12, 5, 4,
                          9, 11, 12, 12, 12, 12, 5, 3,
                          6, 11, 12, 12, 12, 12, 5, 0,
                          7, 11, 12, 12, 12, 12, 5, 1,
                          9, 11, 12, 12, 12, 12, 5, 3,
                          10, 11, 12, 12, 12, 12, 5, 4,
                          8, 11, 12, 12, 12, 12, 5, 2,};

    int x, y, o, k, dx, dy, x2, y2, czy;
    while (1) {

        najlepszy_ruch(plansza, 4, &x, &y, &o, &k);
        dx = o * WX[plansza[x][y]][k];
        dy = o * WY[plansza[x][y]][k];
        plansza[x + dx][y + dy] = plansza[x][y];
        plansza[x][y] = EMPTY;
        if (plansza[x + dx][y + dy] == 11 && y + dy == 7)
            plansza[x + dx][y + dy] = 7;
        board(plansza);
        czy = najlepszy_ruch(plansza, 2, &x, &y, &o, &k);
        if (czy >= WIN) {
            printf("YOU LOSE");
            return 1;
        }
        printf("ENTER MOVE");
        scanf("%d%d%d%d", &x, &y, &x2, &y2);
        plansza[x2][y2] = plansza[x][y];
        plansza[x][y] = EMPTY;
        if (plansza[x2][y2] == 5 && y2 == 0) {
            plansza[x2][y2] = 1;
        }
        board(plansza);
        czy = najlepszy_ruch(plansza, 2, &x, &y, &o, &k);
        if (czy <= LOSE) {
            printf("YOU WIN");
            return 0;
        }


    }

}
