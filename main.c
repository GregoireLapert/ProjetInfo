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

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    SAMPLE*music=load_sample("music.wav");

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
    int fin,choix;
    t_listeActeurs* ancre=creerListe(80);//
    recupBitmapDecor(ancre);





    while(fin!=1)
    {

        /********** Mettre tout en commentaire sauf "jeu()" si tester sans menu **********/

        ///Menu principal
        if(choix!=4)
            MenuPrincipal(&choix);
        if(choix==1)
            MenuJouer(&choix);
        else if(choix==3)
            fin=1;
        ///Jeu
        else if(choix==4)
        {
            jeu();
            choix=-1;
        }

    }

    destroy_sample(music);

    return 0;
}
END_OF_MAIN();

