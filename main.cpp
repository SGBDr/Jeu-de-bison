#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <math.h>
#include <SDL/SDL.h>

void dessin(int car[11][10],SDL_Surface *screen,SDL_Surface *r, SDL_Surface *a, SDL_Surface *b, SDL_Surface *c);
void init(int car[11][10]);
bool coord(SDL_Rect a, SDL_Rect b);
bool test(int car[11][10], SDL_Rect a, SDL_Rect b);
bool test1(int car[11][10], SDL_Rect a, SDL_Rect b);

int main ( int argc, char** argv ){
    int car[11][10];
    int clk = 0;
    SDL_Init( SDL_INIT_VIDEO );-
    SDL_Surface* screen = SDL_SetVideoMode(550, 500, 16,SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_Surface* bmp = SDL_LoadBMP("map.bmp");
    SDL_Surface* bis = SDL_LoadBMP("bis.bmp");
    SDL_Surface* chi = SDL_LoadBMP("chien.bmp");
    SDL_Surface* che = SDL_LoadBMP("chef.bmp");
    SDL_Surface* sel = SDL_LoadBMP("p.bmp");
    SDL_Surface* se = SDL_LoadBMP("pl.bmp");
    SDL_SetColorKey(bis, SDL_SRCCOLORKEY, SDL_MapRGB(bis->format, 255,255,255));
    SDL_SetColorKey(chi, SDL_SRCCOLORKEY, SDL_MapRGB(chi->format, 255,255,255));
    SDL_SetColorKey(che, SDL_SRCCOLORKEY, SDL_MapRGB(che->format, 255,255,255));
    SDL_SetColorKey(sel, SDL_SRCCOLORKEY, SDL_MapRGB(sel->format, 255,255,255));
    SDL_SetColorKey(se, SDL_SRCCOLORKEY, SDL_MapRGB(se->format, 255,255,255));
    SDL_Rect p;
    p.x = 0;
    p.y = 0;
    SDL_BlitSurface(bmp, 0, screen, &p);
    SDL_Flip(screen);
    init(car);
    dessin(car, screen, bmp, bis, chi, che);
    int s1 = 0, s2 = 0;
    SDL_Rect a, b;
    bool ty = false;
    SDL_WM_SetCaption("Joueur 1 Choisissez un bison.", NULL);
    bool done = false;
    while (!done){
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            switch (event.type){
            case SDL_QUIT:
                done = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                int x = event.button.x, y = event.button.y;
                if(clk == 0){
                    if(s1 == 0){
                        a.x = x/50;
                        a.y = y/50;
                        SDL_Rect e;
                        e.x = a.x*50;
                        e.y = a.y*50;
                        SDL_BlitSurface(sel, 0, screen, &e);
                        SDL_Flip(screen);
                        s1 = 1;
                        SDL_WM_SetCaption("Joueur choisis nouvelle position du bison Bison", NULL);
                    }else if(s1 == 1){
                        b.x = x/50;
                        b.y = y/50;
                        ty = test1(car, a, b);
                        if(!ty){
                            SDL_Rect e;
                            e.x = b.x*50;
                            e.y = b.y*50;
                            SDL_BlitSurface(se, 0, screen, &e);
                            SDL_Flip(screen);
                            SDL_WM_SetCaption("Impossible de s'y Deplacer pour ce Bison, Choisir a nouveau un Bison", NULL);
                        }
                        s1 = 0;
                    }
                    if(ty){
                        clk = 1;
                        dessin(car, screen, bmp, bis, chi, che);
                        SDL_WM_SetCaption("Joueur 2 choisissez votre perso a deplacer", NULL);
                        ty = false;
                    }
                }else if(clk == 1){
                    if(s2 == 0){
                        a.x = x/50;
                        a.y = y/50;
                        SDL_Rect e;
                        e.x = a.x*50;
                        e.y = a.y*50;
                        SDL_BlitSurface(sel, 0, screen, &e);
                        SDL_Flip(screen);
                        s2 = 1;
                        SDL_WM_SetCaption("Nouvelle Position ?", NULL);
                    }else{
                        b.x = x/50;
                        b.y = y/50;
                        ty = test(car, a, b);
                        if(!ty){
                            SDL_Rect e;
                            e.x = b.x*50;
                            e.y = b.y*50;
                            SDL_BlitSurface(se, 0, screen, &e);
                            SDL_Flip(screen);
                            SDL_WM_SetCaption("Impossible de s'y deplacer. fetes un nouveaux choix", NULL);
                        }
                        s2 = 0;
                    }
                    if(ty){
                        clk = 0;
                        dessin(car, screen, bmp, bis, chi, che);
                        SDL_WM_SetCaption("Joueur 1 Choisissez un bison.", NULL);
                        ty = false;
                    }
                }
                break;
            }
        }

    }
    SDL_FreeSurface(bmp);
    return 0;
}

bool test(int car[14][10], SDL_Rect a, SDL_Rect b){
    int c = car[a.x][a.y];
    if(c == 2){
        if(car[b.x][b.y] == 0){
            if(b.x != a.x && b.y != a.y){
                car[a.x][a.y] = 0;
                car[b.x][b.y] = 2;
                return true;
            }
        }
    }else if(c == 3){
        if(car[b.x][b.y] == 0 || car[b.x][b.y] == 1){
            if(coord(a, b)){
                car[a.x][a.y] = 0;
                car[b.x][b.y] = 3;
                return true;
            }
        }
    }

    return false;
}

bool test1(int car[11][10], SDL_Rect a, SDL_Rect b){
    int c = car[a.x][a.y];
    if(c == 1){
        if(car[b.x][b.y] == 0 && abs(a.y - b.y) == 1 && a.x == b.x){
            int i = 0;
           car[a.x][a.y] = 0;
           car[b.x][b.y] = 1;
           return true;
        }
    }
    return false;
}

bool coord(SDL_Rect a, SDL_Rect b){
    if(a.x == b.x && abs(a.y - b.y) == 1)return true;
    if(abs(a.y - b.y) == 1 && abs(a.x - b.x) == 1)return true;
    if(a.y == b.y && abs(a.x - b.x) == 1)return true;
    return false;
}

void dessin(int car[11][10],SDL_Surface *screen,SDL_Surface *r, SDL_Surface *a, SDL_Surface *b, SDL_Surface *c){
    int i = 0 , j = 0 ;
    SDL_Rect p;
    p.x = 0;
    p.y = 0;
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
    SDL_BlitSurface(r, 0, screen, &p);
    SDL_Flip(screen);
    for(i = 0 ; i < 11 ; i++){
        for(j = 0 ; j < 10 ; j++){
            if(car[i][j] == 1){
                p.x = i*50;
                p.y = j*50;
                SDL_BlitSurface(a, 0, screen, &p);
                SDL_Flip(screen);
            }else if(car[i][j] == 2){
                p.x = i*50;
                p.y = j*50;
                SDL_BlitSurface(b, 0, screen, &p);
                SDL_Flip(screen);
            }else if(car[i][j] == 3){
                p.x = i*50;
                p.y = j*50;
                SDL_BlitSurface(c, 0, screen, &p);
                SDL_Flip(screen);
            }
        }
    }
}

void init(int car[11][10]){
    int i = 0 , j = 0 ;
    for(i = 0 ; i < 11 ; i++){
        for(j = 0 ; j < 10 ; j++){
            car[i][j] = 0;
        }
    }
    car[0][0] = 1;
    car[1][0] = 1;
    car[2][0] = 1;
    car[3][0] = 1;
    car[4][0] = 1;
    car[5][0] = 1;
    car[6][0] = 1;
    car[7][0] = 1;
    car[8][0] = 1;
    car[9][0] = 1;
    car[10][0] = 1;
    car[3][7] = 2;
    car[4][7] = 2;
    car[6][7] = 2;
    car[7][7] = 2;
    car[5][7] = 3;
}
