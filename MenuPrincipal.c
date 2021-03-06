#include "proto.h"
#include <allegro.h>

/***** Cette page contient tous les ssprgs du menu *****/

void MenuPrincipal(int*choix, SAMPLE*bouton, SAMPLE*valider)
{
    BITMAP*texte=create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP*texte2=create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP*buffer=create_bitmap(SCREEN_W,SCREEN_H);
    clear_to_color(texte,makecol(255,0,255));
    clear_to_color(texte2,makecol(255,0,255));

    *choix=0;
    int oui=0;

    ///Affichage
    AffMP();

    while(*choix==0)
    {
        if(mouse_x>350 && mouse_x<460 && mouse_y>270 && mouse_y<300)
        {
            if(oui==0)
            {
                play_sample(bouton,40,128,1000,0);
                textprintf_ex(texte2,font,285/2,220/2,makecol(220,140,255),-1,"JOUER");
                stretch_blit(texte2,buffer,0,0,texte->w,texte->h,0,0,buffer->w*2.5,buffer->h*2.5);
                draw_sprite(screen,buffer,0,0);
                oui=1;
            }
            if(mouse_b&1)
            {
                play_sample(valider,40,128,1000,0);
                *choix=1;
            }
        }
        else if(mouse_x>330 && mouse_x<480 && mouse_y>350 && mouse_y<370)
        {
            if(oui==0)
            {
                play_sample(bouton,40,128,1000,0);
                textprintf_ex(texte2,font,270/2,280/2,makecol(220,140,255),-1,"OPTIONS");
                stretch_blit(texte2,buffer,0,0,texte->w,texte->h,0,0,buffer->w*2.5,buffer->h*2.5);
                draw_sprite(screen,buffer,0,0);
                oui=2;
            }
            if(mouse_b&1)
            {
                play_sample(valider,40,128,1000,0);
                *choix=2;
            }
        }
        else if(mouse_x>330 && mouse_x<480 && mouse_y>420 && mouse_y<450)
        {
            if(oui==0)
            {
                play_sample(bouton,40,128,1000,0);
                textprintf_ex(texte2,font,270/2,340/2,makecol(220,140,255),-1,"QUITTER");
                stretch_blit(texte2,buffer,0,0,texte->w,texte->h,0,0,buffer->w*2.5,buffer->h*2.5);
                draw_sprite(screen,buffer,0,0);
                oui=3;
            }
            if(mouse_b&1)
            {
                play_sample(valider,40,128,1000,0);
                rest(400);
                *choix=3;
            }
        }
        else if(key[KEY_ESC])
        {
            rectfill(screen,SCREEN_W/2-100,SCREEN_H/2-50,SCREEN_W/2+100,SCREEN_H/2+50,makecol(255,255,255));
            textprintf_centre_ex(screen,font,SCREEN_W/2,SCREEN_H/2,makecol(0,0,0),-1,"Quitter ?");
            while(!key[KEY_O] && !key[KEY_X] && !key[KEY_ESC])
            {
                if(key[KEY_O] || key[KEY_ESC])
                *choix=3;
                else if(key[KEY_X])
                {
                    clear_to_color(texte,makecol(255,0,255));
                    clear_to_color(texte2,makecol(255,0,255));
                }
            }
        }
        else{
            if(oui==1)
                textprintf_ex(texte2,font,285/2,220/2,makecol(255,255,255),-1,"JOUER");
            else if(oui==2)
                textprintf_ex(texte2,font,270/2,280/2,makecol(255,255,255),-1,"OPTIONS");
            else if(oui==3)
                textprintf_ex(texte2,font,270/2,340/2,makecol(255,255,255),-1,"QUITTER");
            if(oui!=0)
            {
                stretch_blit(texte2,buffer,0,0,texte->w,texte->h,0,0,buffer->w*2.5,buffer->h*2.5);
                draw_sprite(screen,buffer,0,0);
                clear_to_color(texte,makecol(255,0,255));
                clear_to_color(texte2,makecol(255,0,255));
                oui=0;
            }
        }
    }
    destroy_bitmap(texte2);
    destroy_bitmap(texte);
    destroy_bitmap(buffer);
}

void Options(int*choix, SAMPLE*music, SAMPLE*bouton, SAMPLE*valider, int* volume, int* son)
{
    BITMAP*fond=load_bitmap("fondmenu.bmp",NULL);
    BITMAP*texte=create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP*texte2=create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP*buffer=create_bitmap(SCREEN_W,SCREEN_H);
    clear_to_color(texte,makecol(255,0,255));
    clear_to_color(texte2,makecol(255,0,255));

    if(!fond)
    {
        allegro_message("N'a pas pu charger fondmenu.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    *choix=0;
    int oui=0,i;
    int onoff=1;

    blit(fond,screen,100,0,0,0,fond->w,fond->h);

    textprintf_ex(texte,font,205/2.5,90/2.5,makecol(255,255,255),-1,"OPTIONS");
    stretch_blit(texte,texte2,0,0,texte->w,texte->h,0,0,texte->w*1.5,texte->h*1.5);
    textprintf_ex(texte2,font,200/2,220/2,makecol(255,255,255),-1,"MUSIQUE : ON/OFF");
    textprintf_ex(texte2,font,200/2,280/2,makecol(255,255,255),-1,"VOLUME");
    textprintf_ex(texte2,font,270/2,340/2,makecol(255,255,255),-1,"RETOUR");
    stretch_blit(texte2,buffer,0,0,texte->w,texte->h,0,0,buffer->w*2.5,buffer->h*2.5);
    draw_sprite(screen,buffer,0,0);
    clear_to_color(texte,makecol(255,0,255));
    clear_to_color(texte2,makecol(255,0,255));

    rest(300);

    while(*choix==0)
    {
        for(i=0;i<*volume;i++)
            rectfill(screen,400+30*i,348,420+30*i,368,makecol(220,149,255));
        for(i=*volume;i<5;i++)
            rectfill(screen,400+30*i,348,420+30*i,368,makecol(255,255,255));

        if(mouse_x>260 && mouse_x<570 && mouse_y>270 && mouse_y<300)
        {
            if(oui==0)
            {
                play_sample(bouton,40,128,1000,0);
                textprintf_ex(texte2,font,200/2,220/2,makecol(220,140,255),-1,"MUSIQUE : ON/OFF");
                stretch_blit(texte2,buffer,0,0,texte->w,texte->h,0,0,buffer->w*2.5,buffer->h*2.5);
                draw_sprite(screen,buffer,0,0);
                oui=1;
            }
            if(mouse_b&1)
            {
                play_sample(valider,40,128,1000,0);
                rest(100);
                if(onoff==1)
                {
                    stop_sample(music);
                    onoff=0;
                }
                else
                {
                    play_sample(music,*son,128,1000,10);
                    onoff=1;
                }
            }
        }
        else if(mouse_x>260 && mouse_x<570 && mouse_y>348 && mouse_y<368)
        {
            if(mouse_b&1)
            {
                play_sample(valider,40,128,1000,0);
                stop_sample(music);

                if(mouse_x>400 && mouse_x<420)
                {
                    *volume=1;
                    *son=6;
                }
                else if(mouse_x>430 && mouse_x<450)
                {
                    *volume=2;
                    *son=13;
                }
                else if(mouse_x>460 && mouse_x<480)
                {
                    *volume=3;
                    *son=20;
                }
                else if(mouse_x>490 && mouse_x<510)
                {
                    *volume=4;
                    *son=27;
                }
                else if(mouse_x>520 && mouse_x<550)
                {
                    *volume=5;
                    *son=32;
                }
                play_sample(music,*son,128,1000,10);

                rest(100);
            }
        }
        else if(mouse_x>340 && mouse_x<470 && mouse_y>420 && mouse_y<450)
        {
            if(oui==0)
            {
                play_sample(bouton,40,128,1000,0);
                textprintf_ex(texte2,font,270/2,340/2,makecol(220,140,255),-1,"RETOUR");
                stretch_blit(texte2,buffer,0,0,texte->w,texte->h,0,0,buffer->w*2.5,buffer->h*2.5);
                draw_sprite(screen,buffer,0,0);
                oui=3;
            }
            if(mouse_b&1)
            {
                play_sample(valider,40,128,1000,0);
                *choix=-1;
                rest(200);
            }
        }
        else{
            if(oui==1)
                textprintf_ex(texte2,font,200/2,220/2,makecol(255,255,255),-1,"MUSIQUE : ON/OFF");
            else if(oui==3)
                textprintf_ex(texte2,font,270/2,340/2,makecol(255,255,255),-1,"RETOUR");
            if(oui!=0)
            {
                stretch_blit(texte2,buffer,0,0,texte->w,texte->h,0,0,buffer->w*2.5,buffer->h*2.5);
                draw_sprite(screen,buffer,0,0);
                clear_to_color(texte,makecol(255,0,255));
                clear_to_color(texte2,makecol(255,0,255));
                oui=0;
            }
        }
    }
    destroy_bitmap(fond);
    destroy_bitmap(texte2);
    destroy_bitmap(texte);
    destroy_bitmap(buffer);
}

void MenuJouer(int*choix, SAMPLE*bouton, SAMPLE*valider)
{
    BITMAP*texte=create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP*texte2=create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP*buffer=create_bitmap(SCREEN_W,SCREEN_H);
    clear_to_color(texte,makecol(255,0,255));
    clear_to_color(texte2,makecol(255,0,255));

    int oui=0;
    *choix=0;

    ///Affichage
    AffMJ();
    rest(400);

    while(*choix==0)
    {
        if(mouse_x>260 && mouse_x<570 && mouse_y>270 && mouse_y<300)
        {
            if(oui==0)
            {
                play_sample(bouton,40,128,1000,0);
                textprintf_ex(texte2,font,210/2,220/2,makecol(220,140,255),-1,"NOUVELLE PARTIE");
                stretch_blit(texte2,buffer,0,0,texte->w,texte->h,0,0,buffer->w*2.5,buffer->h*2.5);
                draw_sprite(screen,buffer,0,0);
                oui=1;
            }
            if(mouse_b&1)
            {
                play_sample(valider,40,128,1000,0);
                tutoriel();
                *choix=4;
            }
        }
        else if(mouse_x>260 && mouse_x<570 && mouse_y>350 && mouse_y<370)
        {
            if(oui==0)
            {
                play_sample(bouton,40,128,1000,0);
                textprintf_ex(texte2,font,210/2,280/2,makecol(220,140,255),-1,"CHOIX DU NIVEAU");
                stretch_blit(texte2,buffer,0,0,texte->w,texte->h,0,0,buffer->w*2.5,buffer->h*2.5);
                draw_sprite(screen,buffer,0,0);
                oui=2;
            }
            if(mouse_b&1)
            {
                play_sample(valider,40,128,1000,0);
                MenuNiveau(choix,bouton,valider);
            }
        }
        else if(mouse_x>340 && mouse_x<470 && mouse_y>420 && mouse_y<450)
        {
            if(oui==0)
            {
                play_sample(bouton,40,128,1000,0);
                textprintf_ex(texte2,font,270/2,340/2,makecol(220,140,255),-1,"RETOUR");
                stretch_blit(texte2,buffer,0,0,texte->w,texte->h,0,0,buffer->w*2.5,buffer->h*2.5);
                draw_sprite(screen,buffer,0,0);
                oui=3;
            }
            if(mouse_b&1)
            {
                play_sample(valider,40,128,1000,0);
                *choix=-1;
                rest(200);
            }
        }
        else{
            if(oui==1)
                textprintf_ex(texte2,font,210/2,220/2,makecol(255,255,255),-1,"NOUVELLE PARTIE");
            else if(oui==2)
                textprintf_ex(texte2,font,210/2,280/2,makecol(255,255,255),-1,"CHOIX DU NIVEAU");
            else if(oui==3)
                textprintf_ex(texte2,font,270/2,340/2,makecol(255,255,255),-1,"RETOUR");
            if(oui!=0)
            {
                stretch_blit(texte2,buffer,0,0,texte->w,texte->h,0,0,buffer->w*2.5,buffer->h*2.5);
                draw_sprite(screen,buffer,0,0);
                clear_to_color(texte,makecol(255,0,255));
                clear_to_color(texte2,makecol(255,0,255));
                oui=0;
            }
        }
    }
    destroy_bitmap(texte2);
    destroy_bitmap(texte);
    destroy_bitmap(buffer);
}

void MenuNiveau(int*choix, SAMPLE*bouton, SAMPLE*valider)
{
    BITMAP*texte=create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP*texte2=create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP*buffer=create_bitmap(SCREEN_W,SCREEN_H);
    clear_to_color(texte,makecol(255,0,255));
    clear_to_color(texte2,makecol(255,0,255));

    int oui=0,lock=1;

    AffMM();
    rest(400);

    while(lock!=0)
    {
        if(mouse_x>350 && mouse_x<460 && mouse_y>245 && mouse_y<275)
        {
            if(oui==0)
            {
                play_sample(bouton,40,128,1000,0);
                textprintf_ex(texte2,font,260/2,200/2,makecol(220,140,255),-1,"NIVEAU 1");
                stretch_blit(texte2,buffer,0,0,texte->w,texte->h,0,0,buffer->w*2.5,buffer->h*2.5);
                draw_sprite(screen,buffer,0,0);
                oui=1;
            }
            if(mouse_b&1)
            {
                play_sample(valider,40,128,1000,0);
                *choix=4;
                lock=0;
            }
        }
        else if(mouse_x>340 && mouse_x<470 && mouse_y>310 && mouse_y<340)
        {
            if(oui==0)
            {
                play_sample(bouton,40,128,1000,0);
                textprintf_ex(texte2,font,260/2,250/2,makecol(220,140,255),-1,"NIVEAU 2");
                stretch_blit(texte2,buffer,0,0,texte->w,texte->h,0,0,buffer->w*2.5,buffer->h*2.5);
                draw_sprite(screen,buffer,0,0);
                oui=2;
            }
            if(mouse_b&1)
            {
                play_sample(valider,40,128,1000,0);
                *choix=5;
                lock=0;
            }
        }
        else if(mouse_x>340 && mouse_x<470 && mouse_y>370 && mouse_y<400)
        {
            if(oui==0)
            {
                play_sample(bouton,40,128,1000,0);
                textprintf_ex(texte2,font,260/2,300/2,makecol(220,140,255),-1,"NIVEAU 3");
                stretch_blit(texte2,buffer,0,0,texte->w,texte->h,0,0,buffer->w*2.5,buffer->h*2.5);
                draw_sprite(screen,buffer,0,0);
                oui=3;
            }
            if(mouse_b&1)
            {
                play_sample(valider,40,128,1000,0);
                *choix=6;
                lock=0;
            }
        }
        else if(mouse_x>340 && mouse_x<470 && mouse_y>430 && mouse_y<460)
        {
            if(oui==0)
            {
                play_sample(bouton,40,128,1000,0);
                textprintf_ex(texte2,font,270/2,350/2,makecol(220,140,255),-1,"RETOUR");
                stretch_blit(texte2,buffer,0,0,texte->w,texte->h,0,0,buffer->w*2.5,buffer->h*2.5);
                draw_sprite(screen,buffer,0,0);
                oui=4;
            }
            if(mouse_b&1)
            {
                play_sample(valider,40,128,1000,0);
                *choix=0;
                lock=0;
                rest(200);
                AffMJ();
            }
        }
        else{
            if(oui==1)
                textprintf_ex(texte2,font,260/2,200/2,makecol(255,255,255),-1,"NIVEAU 1");
            else if(oui==2)
                textprintf_ex(texte2,font,260/2,250/2,makecol(255,255,255),-1,"NIVEAU 2");
            else if(oui==3)
                textprintf_ex(texte2,font,260/2,300/2,makecol(255,255,255),-1,"NIVEAU 3");
            else if(oui==4)
                textprintf_ex(texte2,font,270/2,350/2,makecol(255,255,255),-1,"RETOUR");
            if(oui!=0)
            {
                stretch_blit(texte2,buffer,0,0,texte->w,texte->h,0,0,buffer->w*2.5,buffer->h*2.5);
                draw_sprite(screen,buffer,0,0);
                clear_to_color(texte,makecol(255,0,255));
                clear_to_color(texte2,makecol(255,0,255));
                oui=0;
            }
        }

        ///Cheatcodes boss
        if(key[KEY_1])
        {
            *choix=41;
            lock=0;
        }
        else if(key[KEY_2])
        {
            *choix=51;
            lock=0;
        }
        else if(key[KEY_3])
        {
            *choix=61;
            lock=0;
        }
    }
    destroy_bitmap(texte);
    destroy_bitmap(texte2);
    destroy_bitmap(buffer);
}

void AffMJ()
{
    BITMAP*fond=load_bitmap("fondmenu.bmp",NULL);
    BITMAP*texte=create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP*texte2=create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP*buffer=create_bitmap(SCREEN_W,SCREEN_H);
    clear_to_color(texte,makecol(255,0,255));
    clear_to_color(texte2,makecol(255,0,255));

    if(!fond)
    {
        allegro_message("N'a pas pu charger fondmenu.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    blit(fond,screen,100,0,0,0,fond->w,fond->h);

    textprintf_ex(texte,font,220/2.5,90/2.5,makecol(255,255,255),-1,"JOUER");
    stretch_blit(texte,texte2,0,0,texte->w,texte->h,0,0,texte->w*1.5,texte->h*1.5);
    textprintf_ex(texte2,font,210/2,220/2,makecol(255,255,255),-1,"NOUVELLE PARTIE");
    textprintf_ex(texte2,font,210/2,280/2,makecol(255,255,255),-1,"CHOIX DU NIVEAU");
    textprintf_ex(texte2,font,270/2,340/2,makecol(255,255,255),-1,"RETOUR");
    stretch_blit(texte2,buffer,0,0,texte->w,texte->h,0,0,buffer->w*2.5,buffer->h*2.5);
    draw_sprite(screen,buffer,0,0);
    clear_to_color(texte,makecol(255,0,255));
    clear_to_color(texte2,makecol(255,0,255));

    destroy_bitmap(fond);
    destroy_bitmap(texte);
    destroy_bitmap(texte2);
    destroy_bitmap(buffer);
}

void AffMP()
{
    BITMAP*fond=load_bitmap("fondmenu.bmp",NULL);
    BITMAP*texte=create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP*texte2=create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP*buffer=create_bitmap(SCREEN_W,SCREEN_H);
    clear_to_color(texte,makecol(255,0,255));
    clear_to_color(texte2,makecol(255,0,255));

    if(!fond)
    {
        allegro_message("N'a pas pu charger fondmenu.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    blit(fond,screen,100,0,0,0,fond->w,fond->h);

    textprintf_ex(texte,font,195/2.5,90/2.5,makecol(255,255,255),-1,"AGC-TYPE");
    stretch_blit(texte,texte2,0,0,texte->w,texte->h,0,0,texte->w*1.5,texte->h*1.5);
    textprintf_ex(texte2,font,285/2,220/2,makecol(255,255,255),-1,"JOUER");
    textprintf_ex(texte2,font,270/2,280/2,makecol(255,255,255),-1,"OPTIONS");
    textprintf_ex(texte2,font,270/2,340/2,makecol(255,255,255),-1,"QUITTER");
    stretch_blit(texte2,buffer,0,0,texte->w,texte->h,0,0,buffer->w*2.5,buffer->h*2.5);
    draw_sprite(screen,buffer,0,0);

    destroy_bitmap(fond);
    destroy_bitmap(texte);
    destroy_bitmap(texte2);
    destroy_bitmap(buffer);
}

void AffMM()
{
    BITMAP*fond=load_bitmap("fondmenu.bmp",NULL);
    BITMAP*texte=create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP*texte2=create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP*buffer=create_bitmap(SCREEN_W,SCREEN_H);
    clear_to_color(texte,makecol(255,0,255));
    clear_to_color(texte2,makecol(255,0,255));

    if(!fond)
    {
        allegro_message("N'a pas pu charger fondmenu.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    blit(fond,screen,100,0,0,0,fond->w,fond->h);

    textprintf_ex(texte,font,130/2.5,90/2.5,makecol(255,255,255),-1,"CHOIX DU NIVEAU");
    stretch_blit(texte,texte2,0,0,texte->w,texte->h,0,0,texte->w*1.5,texte->h*1.5);
    textprintf_ex(texte2,font,260/2,200/2,makecol(255,255,255),-1,"NIVEAU 1");
    textprintf_ex(texte2,font,260/2,250/2,makecol(255,255,255),-1,"NIVEAU 2");
    textprintf_ex(texte2,font,260/2,300/2,makecol(255,255,255),-1,"NIVEAU 3");
    textprintf_ex(texte2,font,270/2,350/2,makecol(255,255,255),-1,"RETOUR");
    stretch_blit(texte2,buffer,0,0,texte->w,texte->h,0,0,buffer->w*2.5,buffer->h*2.5);
    draw_sprite(screen,buffer,0,0);

    destroy_bitmap(fond);
    destroy_bitmap(texte);
    destroy_bitmap(texte2);
    destroy_bitmap(buffer);
}

