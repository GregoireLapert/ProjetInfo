
#include <allegro.h>
#include <time.h>
#include "proto.h"

int main()
{

    // Il y aura du hasard
    srand(time(NULL));

    // Lancer allegro et le mode graphique
    allegro_init();
    install_keyboard();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    t_listeActeurs* ancre=creerListe(5);
    ajoutActeur(ancre,500,300,1);
    ajoutActeur(ancre,400,200,1);
    ajoutIntervenant(ancre,0,0,1);




    // BOUCLE DE JEU
    while (!key[KEY_ESC])
    {
       testMort(ancre);
        affiche(ancre);

                // petite temporisation
        rest(10);
    }


    free(ancre);
    return 0;
}
END_OF_MAIN();

