#include "proto.h"

int Niveau1()
{
    int clear=0;
    int xPage=0,xFond=0;
    int boss=0,i;
    t_listeActeurs* ancre=creerListe(80);

    ///Declaration des bitmap a utiliser
    BITMAP *page=load_bitmap("images\\Decor\\background\\Fond.bmp",NULL);   ///Fond arriere
    clear_bitmap(screen);
    BITMAP* fond=fondDecor(ancre,screen);   ///fond = bitmap de 10k pixel de long de d�cor
    BITMAP* bufferColi=fondBuffer(ancre,screen);    ///fond de 10 k pixel de buffer
    BITMAP* screenBuffer=create_bitmap(800,600);    ///buffer de screen
    BITMAP* GameOver=load_bitmap("images\\gameover.bmp",NULL);

    if (!GameOver)
    {
        allegro_message("pas pu trouver/charger gameover.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    if (!page)
    {
        allegro_message("pas pu trouver/charger back.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    BITMAP* bufferColi=fondBuffer(ancre,screen);    ///fond de 10 k pixel de buffer
    BITMAP* screenBuffer=create_bitmap(800,600);    ///buffer de screen

    while(clear==0)
    {
        int place=0, yes=0;
        ///Affichage aleatoire d'ennemis
        if(boss==0)
        {
            while(yes==0)
            {
                place++;
                yes=PopEnnemis(ancre,place,90,100,0);
            }
        }

        testMort(ancre);

        if(ancre->tabActeur[0]==NULL)
        {
            rest(200);
            masked_blit(GameOver,screen,0,0,SCREEN_W/2-GameOver->w/2,SCREEN_H/2-GameOver->h/2,GameOver->w,GameOver->h);

            while(!key[KEY_SPACE])
                rest(5);
            clear=-1;
        }
        else
        {
            deplacementPersonnage(ancre);
            deplacementEnnemi(ancre);
            deplacementIntervenant(ancre);
            tirPersonnage(ancre);
            TirEnnemi(ancre);
            collisionDecor(fond,xFond,ancre);
            Affichage(&xPage,&xFond,screenBuffer,page,fond,bufferColi,ancre);
            popBoss(xFond,ancre,&boss,5);
        }


        ///Pause
        if(key[KEY_P] || key[KEY_ESC])
        {
            rectfill(screen,SCREEN_W/2-200,SCREEN_H/2-50,SCREEN_W/2+200,SCREEN_H/2+50,makecol(255,255,255));
            textprintf_centre_ex(screen,font,SCREEN_W/2,SCREEN_H/2-30,makecol(0,0,0),-1,"PAUSE");
            textprintf_centre_ex(screen,font,SCREEN_W/2,SCREEN_H/2,makecol(0,0,0),-1,"Reprendre : P");
            textprintf_centre_ex(screen,font,SCREEN_W/2,SCREEN_H/2+20,makecol(0,0,0),-1,"Retourner au menu principal : O");
            rest(200);
            while(!key[KEY_O] && !key[KEY_P])
            {
                if(key[KEY_P])
                    break;
                else if(key[KEY_O])
                    retour=1;
            }
            rest(200);
        }
        rest(30);
    }

    free(ancre);
    destroy_bitmap(GameOver);
    destroy_bitmap(page);
    for(i=0;i<15;i++)
        destroy_bitmap(ancre->decor[i]);
}
