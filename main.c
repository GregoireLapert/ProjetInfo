
#include <allegro.h>
#include <time.h>
#include "proto.h"

int main()
{

    // Il y aura du hasar
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
    t_listeActeurs* ancre=creerListe(20);





    // BOUCLE DE JEU
    while (!key[KEY_ESC])
    {
       testMort(ancre);
       deplacementPersonnage(ancre);
       deplacementIntervenant(ancre);
       tirPersonnage(ancre);

        affiche(ancre);

                // petite temporisation
        rest(30);
    }


    free(ancre);
    return 0;
}
END_OF_MAIN();

