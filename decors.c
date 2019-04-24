 #include "proto.h"

                /****** Sous-programmes pour les decors ******/

///Cree un decor
t_decor* constructeurdecor(int x,int y,int numDecor,t_listeActeurs* ancre)
{
    t_decor* nouveau=(t_decor*)malloc(sizeof(t_decor));
    nouveau->posx=x;
    nouveau->posy=y;
    nouveau->affiche=ancre->decor[numDecor];

    return nouveau;
}

///Genere un decor aleatoire
void generateurDecor(t_listeActeurs *ancre)
{
    int compteurZone=0;         ///écran a été divisé en 3 partie selon la posx(200 pixel chaque) car les 200 premiers pixel sont la copie de la dernière bitmap pour éviter les sauts
    int compteurNbParZone=0;    ///on met 5 élément de décor par zone
    int compteurElement=0;      ///max de 15 element de décor en tout
    int u=0;
    int posx=0;
    int posy=0;                 ///bug donc alterne entre haut et bas

    for(compteurZone=1;compteurZone<=3;compteurZone++)
    {
        for(compteurNbParZone=0;compteurNbParZone<170;compteurNbParZone++)
        {
            posx=200+(compteurElement*50);/**compteurZone+(fibonnaci(u)%100);**/ ///on place un element dans sa zone +- 200 pixel

            if(compteurElement%2!=0)
                posy=0;
            else
                posy=550;

            u=rand()%15;
            ancre->tabDecor[compteurElement]=constructeurdecor(posx,posy,u,ancre);
            compteurElement+=1;
        }
    }
}

///Copie les 200 premiers pixels de l'ancien fond pour créer une continuité partiel et pas de bug de generation de décor
BITMAP* fondDecor(t_listeActeurs *ancre,BITMAP* ancienFond)
{
    int i=0;
    BITMAP* nouveau=create_bitmap(10000,600);
    clear_to_color(nouveau,makecol(255,0,255));
    generateurDecor(ancre);

    for(i=0;i<510;i++)
    {
        if(ancre->tabDecor[i]->posy==0)
            draw_sprite_v_flip(nouveau,ancre->tabDecor[i]->affiche,ancre->tabDecor[i]->posx,ancre->tabDecor[i]->posy);

        if(ancre->tabDecor[i]->posy==550)
            draw_sprite(nouveau,ancre->tabDecor[i]->affiche,ancre->tabDecor[i]->posx,ancre->tabDecor[i]->posy);
    }
    return nouveau;
}

///Creer une bitmap buffer de collisions (avec les decors).
BITMAP *fondBuffer(t_listeActeurs* ancre,BITMAP* ancienFond)
{
    int i=0;
    BITMAP* nouveau=create_bitmap(10000,600);
    clear_bitmap(nouveau);

    for(i=0;i<510;i++)
    {
        if(ancre->tabDecor[i]->posy==0)
        {
            BITMAP* transition=create_bitmap(ancre->tabDecor[i]->affiche->w,ancre->tabDecor[i]->affiche->h);
            clear_to_color(transition,makecol(255,0,255));
            draw_sprite_v_flip(transition,ancre->tabDecor[i]->affiche,ancre->tabDecor[i]->posx,ancre->tabDecor[i]->posy);
            blit(transition,nouveau,0,0,ancre->tabDecor[i]->posx,ancre->tabDecor[i]->posy,ancre->tabDecor[i]->affiche->w,ancre->tabDecor[i]->affiche->h);
        }

        if(ancre->tabDecor[i]->posy==550)
        {
            blit(ancre->tabDecor[i]->affiche,nouveau,0,0,ancre->tabDecor[i]->posx,ancre->tabDecor[i]->posy,ancre->tabDecor[i]->affiche->w,ancre->tabDecor[i]->affiche->h);
        }

    }
    return nouveau;
}

///Recupere les bitmaps des decors.
void recupBitmapDecor(t_listeActeurs *ancre)
{
    int i=0;
    for(i=0;i<15;i++)
    {
        switch(i)
        {
            case 0:
                ancre->decor[i]=load_bitmap("images\\Decor\\image\\a.bmp",NULL);
                 ancre->explo[i]=load_bitmap("images\\exploa.bmp",NULL);
                break;

            case 1:
                ancre->decor[i]=load_bitmap("images\\Decor\\image\\b.bmp",NULL);
                 ancre->explo[i]=load_bitmap("images\\explob.bmp",NULL);
                break;

            case 2:
                ancre->decor[i]=load_bitmap("images\\Decor\\image\\c.bmp",NULL);
                  ancre->explo[i]=load_bitmap("images\\exploc.bmp",NULL);
                break;

            case 3:
                ancre->decor[i]=load_bitmap("images\\Decor\\image\\d.bmp",NULL);
                 ancre->explo[i]=load_bitmap("images\\explod.bmp",NULL);
                break;

            case 4:
                ancre->decor[i]=load_bitmap("images\\Decor\\image\\e.bmp",NULL);
                ancre->explo[i]=load_bitmap("images\\exploe.bmp",NULL);
                break;

            case 5:
                ancre->decor[i]=load_bitmap("images\\Decor\\image\\f.bmp",NULL);
                 ancre->explo[i]=load_bitmap("images\\explof.bmp",NULL);
                break;

            case 6:
                   ancre->explo[i]=load_bitmap("images\\explog.bmp",NULL);
                ancre->decor[i]=load_bitmap("images\\Decor\\image\\g.bmp",NULL);
                break;

            case 7:
                ancre->decor[i]=load_bitmap("images\\Decor\\image\\h.bmp",NULL);
                  ancre->explo[i]=load_bitmap("images\\exploh.bmp",NULL);
                break;

            case 8:
                ancre->decor[i]=load_bitmap("images\\Decor\\image\\i.bmp",NULL);
                   ancre->explo[i]=load_bitmap("images\\exploi.bmp",NULL);
                break;

            case 9:
                ancre->decor[i]=load_bitmap("images\\Decor\\image\\j.bmp",NULL);
                break;

            case 10:
                ancre->decor[i]=load_bitmap("images\\Decor\\image\\k.bmp",NULL);
                break;

            case 11:
                ancre->decor[i]=load_bitmap("images\\Decor\\image\\l.bmp",NULL);
                break;

            case 12:
                ancre->decor[i]=load_bitmap("images\\Decor\\image\\m.bmp",NULL);
                break;

            case 13:
                ancre->decor[i]=load_bitmap("images\\Decor\\image\\n.bmp",NULL);
                break;

            case 14:
                ancre->decor[i]=load_bitmap("images\\Decor\\image\\o.bmp",NULL);
                break;
        }

    }
}

