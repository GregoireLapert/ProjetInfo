#include "proto.h"

int Niveau(int niveau, int xFond)
{
    int clear=0;
    int xPage=0;
    int boss=0,i;
    int TypeBoss,vieBoss=1;
    t_listeActeurs* ancre=creerListe(80);
    ///Son bonus
    SAMPLE*bonus=load_sample("valider1.wav");

    ///D�claration des bitmap a utiliser

    BITMAP *page=NULL;
    if(niveau==1)
        page=load_bitmap("images\\Decor\\background\\Fond.bmp",NULL);   ///Fond arriere
    else if(niveau==2)
        page=load_bitmap("images\\Decor\\background\\fond2.bmp",NULL);   ///Fond arriere niveau 2
    else if(niveau==3)
        page=load_bitmap("images\\Decor\\background\\test.bmp",NULL);   ///Fond arriere niveau 2
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
        allegro_message("pas pu trouver/charger fond.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    if(niveau==1)
        TypeBoss=5;
    else if(niveau==2)
        TypeBoss=6;
    else if(niveau==3)
        TypeBoss=7;


                            /***** BOUCLE DE JEU *****/
    while (clear==0)
    {
        int place=0, yes=0;

        ///Affichage aleatoire d'ennemis
        if(boss==0)
        {
            while(yes==0)
            {
                place++;
                if(niveau==1)
                {
                    ///Au debut, seul un type d'ennemi apparait
                    if(xFond<3000)
                        yes=PopEnnemis(ancre,place,100,0,0);
                    else if(xFond<6000)
                        yes=PopEnnemis(ancre,place,0,100,0);
                    else
                        yes=PopEnnemis(ancre,place,100,110,0);
                }
                else if(niveau==2)
                {
                    if(xFond<3000)
                        yes=PopEnnemis(ancre,place,100,100,0);
                    else yes=PopEnnemis(ancre,place,150,150,300);
                }
                else
                {
                    if(xFond<1000)
                        yes=PopEnnemis(ancre,place,90,0,0);
                    else if(xFond<2000)
                        yes=PopEnnemis(ancre,place,90,90,0);
                    else yes=PopEnnemis(ancre,place,90,100,150);
                }
            }
        }

        testMort(ancre,&vieBoss);
        if(ancre->tabActeur[0]==NULL)
        {
            rest(200);
            masked_blit(GameOver,screen,0,0,SCREEN_W/2-GameOver->w/2,SCREEN_H/2-GameOver->h/2,GameOver->w,GameOver->h);

            while(!key[KEY_SPACE])
                rest(5);
            clear=-1;
        }
        else if(vieBoss==0)
        {
            transition(ancre,page,xPage);

            clear=1;
        }
        else
        {
            deplacementPersonnage(ancre);
            deplacementEnnemi(ancre);
            deplacementIntervenant(ancre);
            tirPersonnage(ancre,&xPage);
            TirEnnemi(ancre);
            collisionDecor(fond,xFond,ancre);
            Affichage(&xPage,&xFond,screenBuffer,page,fond,bufferColi,ancre);
            popBoss(xFond,ancre,&boss,TypeBoss);
            AffichageBuffer(bufferColi,ancre);
            collisionTir(bufferColi,ancre,bonus);
            popBonus(xFond,ancre);
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
                    clear=-2;
            }
            rest(200);
        }
        rest(20);
    }


    destroy_bitmap(screenBuffer);
    destroy_bitmap(bufferColi);
    destroy_bitmap(GameOver);
    destroy_bitmap(page);
    for(i=0;i<15;i++)
        destroy_bitmap(ancre->decor[i]);
    destroy_sample(bonus);
    free(ancre);

    return clear;
}

void transition(t_listeActeurs*ancre, BITMAP* page, int xPage)
{
    BITMAP* screenBuffer=create_bitmap(800,600);
    int i;

    ///Le personnage quitte la map
    while(ancre->tabActeur[0]->posx<SCREEN_W)
    {
        ancre->tabActeur[0]->posx++;
        xPage=xPage+2;

        if(xPage>=page->w)
            xPage=0;

        if(xPage+SCREEN_W<page->w)
            blit(page,screenBuffer,xPage,0,0,0,SCREEN_W,SCREEN_H);
        else
        {
            blit(page,screenBuffer,xPage,0,0,0,page->w-xPage,SCREEN_H);
            blit(page,screenBuffer,0,0,page->w-xPage,0,SCREEN_W-(page->w-xPage),SCREEN_H);
        }

        masked_blit(ancre->tabActeur[0]->affiche,screenBuffer,0,0,ancre->tabActeur[0]->posx,ancre->tabActeur[0]->posy,ancre->tabActeur[0]->tx,ancre->tabActeur[0]->ty);

        blit(screenBuffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }

    for (i=0;i<256;i++)
    {
        line(screen,3*i,0,3*i,600,makecol(0,0,0));
        line(screen,3*i+1,0,3*i+1,600,makecol(0,0,0));
        line(screen,3*i+2,0,3*i+2,600,makecol(0,0,0));
        rest(1);
    }
    rest(10);
    clear_bitmap(screen);
    rest(100);
    destroy_bitmap(screenBuffer);
}

