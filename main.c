#include <allegro.h>
#include <time.h>
#include "proto.h"

int main()
{
    srand(time(NULL));

    /// Lancer allegro et le mode graphique
    allegro_init();
    install_keyboard();
    install_mouse();
    install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);
    set_uformat(U_ASCII);

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    SAMPLE*music=load_sample("music.wav");
    SAMPLE*bouton=load_sample("bouton1.wav");
    SAMPLE*valider=load_sample("valider1.wav");

    if(!bouton)
    {
        allegro_message("N'a pas pu trouver bouton1.wav");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    if(!valider)
    {
        allegro_message("N'a pas pu trouver valider1.wav");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    if(!music)
    {
        allegro_message("N'a pas pu trouver music.wav");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    /********** Mettre ce ligne si tester sans musique **********/
    play_sample(music,20,128,1000,10);
    /************************************************************/

    show_mouse(screen);
    int fin,choix=789;
    int volume=3;
    int son=20;

    while(fin!=1)
    {

        /********** Mettre tout en commentaire sauf "jeu()" si tester sans menu **********/

        ///Menu principal
        if(choix==1)
            MenuJouer(&choix,bouton,valider);
        else if(choix==2)
            Options(&choix,music,bouton,valider,&volume,&son);
        else if(choix==3)
            fin=1;
        ///Jeu
        else if(choix==4)
        {
            jeu(0,0,0,0);
            choix=-1;
        }
        else if(choix==5)
        {
            jeu(1,0,0,0);
            choix=-1;
        }
        else if(choix==6)
        {
            jeu(1,1,0,0);
            choix=-1;
        }
        else if(choix==41)
        {
            jeu(0,0,0,9300);
            choix=-1;
        }
        else if(choix==51)
        {
            jeu(1,0,0,9300);
            choix=-1;
        }
        else if(choix==61)
        {
            jeu(1,1,0,9300);
            choix=-1;
        }
        else MenuPrincipal(&choix,bouton,valider);
    }

    destroy_sample(music);
    destroy_sample(bouton);
    destroy_sample(valider);

    return 0;
}
END_OF_MAIN();

