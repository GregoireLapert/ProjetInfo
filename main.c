
#include <allegro.h>
#include <time.h>
#include "proto.h"



int main()
{
    int x=0;

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
    t_listeActeurs* ancre=creerListe(80);
    
    
    
    BITMAP *page=NULL;
    page=load_bitmap("back1.bmp",NULL);
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
    while (!key[KEY_ESC])
    {

       testMort(ancre);
       deplacementPersonnage(ancre);
       deplacementIntervenant(ancre);
       tirPersonnage(ancre);
       Affichage(&x,page, screen, ancre);   
        
        
        
     
    // petite temporisation
        rest(30);
    }
     

    free(ancre);
    return 0;
}
END_OF_MAIN();

