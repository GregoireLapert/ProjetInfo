#include "proto.h"
#include <allegro.h>

void jeu()
{
    int xPage=0,retour=0,xFond=0;
    t_listeActeurs* ancre=creerListe(80);
    //déclaration des bitmap a utiliser//
    BITMAP *page=NULL;//scroll du fond
    page=load_bitmap("back1.bmp",NULL);
    clear_bitmap(screen);
    //fond = bitmap de 10k pixel de long de décor
    BITMAP* fond=fondDecor(ancre,screen);
    //fond de 10 k pixel de buffer
    BITMAP* bufferColi=fondBuffer(ancre,screen);
    BITMAP* screenBuffer=create_bitmap(800,600);//buffer de screen
    if (!page)
    {
        allegro_message("pas pu trouver/charger back.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    BITMAP* buffer1=NULL;
    buffer1=create_bitmap(SCREEN_W,SCREEN_H);

    if (!buffer1)
    {
        allegro_message("pas pu trouver/charger back.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // BOUCLE DE JEU
    while (retour==0)
    {
        testMort(ancre);
        deplacementPersonnage(ancre);
        deplacementIntervenant(ancre);
        tirPersonnage(ancre);
        Affichage(&xPage,&xFond,screenBuffer,page,fond,bufferColi,ancre);


        if(key[KEY_P])
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
}
/*
int fibonnaci(int u)
{
    int i=0;
    int c=u;
    for(i=0;i<c;i++)
    {
        u+=u+1;
    }
    return u;
}*/



