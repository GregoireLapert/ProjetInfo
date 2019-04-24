#include "proto.h"
#include <allegro.h>

void jeu(int clear1, int clear2, int clear3, int boss)
{
    int retour=0;
                            /***** BOUCLE DE JEU *****/
    while (retour!=1)
    {
        if(clear1==0)
            clear1=Niveau(1,boss);
        if(clear1==1 && clear2==0)
            clear2=Niveau(2,boss);
        if(clear2==1)
            clear3=Niveau(3,boss);
        if(clear3==1)
            retour=1;
        if(clear1==-1 || clear2==-1 || clear3==-1)
        {
            clear_bitmap(screen);
            rest(200);
            rectfill(screen,SCREEN_W/2-200,SCREEN_H/2-50,SCREEN_W/2+200,SCREEN_H/2+50,makecol(255,255,255));
            textprintf_centre_ex(screen,font,SCREEN_W/2,SCREEN_H/2-30,makecol(0,0,0),-1,"REESSAYER ?");
            textprintf_centre_ex(screen,font,SCREEN_W/2,SCREEN_H/2,makecol(0,0,0),-1,"Oui : O");
            textprintf_centre_ex(screen,font,SCREEN_W/2,SCREEN_H/2+20,makecol(0,0,0),-1,"Retourner au menu principal : X");
            while(!key[KEY_O] && !key[KEY_X])
            {
                if(key[KEY_O])
                {
                    if(clear1==-1)
                        clear1=0;
                    else if(clear2==-1)
                        clear2=0;
                    else if(clear3==-1)
                        clear3=0;
                }
                else if(key[KEY_X])
                    retour=1;
            }
        }
        else retour=1;
    }
}

void tutoriel()
{
    BITMAP*fleches=load_bitmap("images\\fleches.bmp",NULL);
    BITMAP*espace=load_bitmap("images\\espace.bmp",NULL);
    BITMAP*touchew=load_bitmap("images\\w.bmp",NULL);
    BITMAP*texte=create_bitmap(SCREEN_W,SCREEN_H);

    if (!fleches)
    {
        allegro_message("pas pu trouver/charger fleches.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    if (!espace)
    {
        allegro_message("pas pu trouver/charger espace.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    if (!touchew)
    {
        allegro_message("pas pu trouver/charger w.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    clear_bitmap(screen);

    textprintf_centre_ex(texte,font,SCREEN_W/(2*1.5),120,makecol(255,255,255),-1,"COMMANDES");
    textprintf_ex(texte,font,180,180,makecol(255,255,255),-1,"Utiliser les flèches directionnelles");
    textprintf_ex(texte,font,180,200,makecol(255,255,255),-1,"pour se déplacer");
    textprintf_ex(texte,font,180,260,makecol(255,255,255),-1,"Appuyer sur espace pour tirer vos lasers");
    textprintf_ex(texte,font,180,320,makecol(255,255,255),-1,"Appuyer sur W pour utiliser des missiles");

    stretch_blit(texte,screen,0,0,texte->w,texte->h,0,0,texte->w*1.5,texte->h*1.5);

    masked_blit(fleches,screen,0,0,70,220,fleches->w,fleches->h);
    masked_blit(espace,screen,0,0,70,320,espace->w,espace->h);
    masked_blit(touchew,screen,0,0,115,450,touchew->w,touchew->h);

    textprintf_centre_ex(screen,font,SCREEN_W/2,60,makecol(255,255,255),-1,"A cause de la pollution, l'atmosphère s'est trouée. En plus de laisser passer");
    textprintf_centre_ex(screen,font,SCREEN_W/2,80,makecol(255,255,255),-1,"les astéroïdes, divers mutations ont été repérées.");
    textprintf_centre_ex(screen,font,SCREEN_W/2,100,makecol(255,255,255),-1,"Vous êtes le pilote AGC et avez pour mission de lutter contre ces menaces.");
    textprintf_ex(screen,font,460,565,makecol(255,255,255),-1,"Appuyer sur espace pour continuer...");

    while(!key[KEY_SPACE]) rest(10);

    destroy_bitmap(fleches);
    destroy_bitmap(espace);
    destroy_bitmap(touchew);
}
