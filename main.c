
#include <allegro.h>
#include <time.h>


/**********************/
/*     STRUCTURES     */
/**********************/

// chaque acteur qui se d�place
typedef struct acteur
{

    // position du coin sup. gauche
    int x,y;

    // vecteur deplacement
    int dx,dy;

    // largeur hauteur
    int tx,ty;

    // couleur (ne sera plus pertinent avec des sprites import�s...)
    int couleur;

    // type (ici 2 types mais on peut en mettre plus):
    //   0 laser
    //   1 missile (acc�l�ration horizontale)
    int type;

    // comportement :
    //   0 normal d�placement
    //   1 explosion
    int comportement;
    int cptexplo; // temps depuis l'explosion

    // vivant :
    //   0 mort (doit disparaitre de la liste)
    //   1 vivant
    int vivant;

} t_acteur;

// Une collection de acteurs
typedef struct listeActeurs
{
    // nombre maxi d'�l�ments
    // =taille du tableau de pointeurs
    int max;

    // nombre effectif de pointeurs utilis�s
    // (les autres sont � NULL)
    int n;

    // le tableau de pointeurs (allou� dynamiquement)
    t_acteur **tab;

} t_listeActeurs;


// Sp�cifique � cet exemple : un vaisseau et une cible

// Un �l�ment � d�placement interactif
typedef struct joueur{
    int x,y;     // position
    int tx,ty;   // taille
    int vit;     // vitesse des d�placements (nombre de pixels)
    int cpttir0; // tempo armement 0
    int cpttir1; // tempo armement 1
    BITMAP *img; // sprite (image charg�e)
} t_joueur;

// Un �l�ment � d�placement automatique al�atoire
typedef struct ennemi{
    int x,y;     // position
    int dx,dy;   // vecteur d�placement
    int tx,ty;   // taille
    BITMAP *img; // sprite (image charg�e)
} t_ennemi;


/*********************/
/*     PROTOTYPES    */
/*********************/

// Allouer et initialiser un acteur
// pour ce projet il faut x y de d�part et type
//   ( � adapter selon besoins )
t_acteur * creerActeur(int x,int y,int type);

// Allouer et initialiser une liste (vide) de acteurs
t_listeActeurs * creerListeActeurs(int maxacteurs);

// Retourne un bool�en vrai si il reste de la place
// dans la liste, faux sinon
int libreListeActeurs(t_listeActeurs *la);

// Allouer et ajouter un acteur � la liste
// et retourner l'adresse de ce nouveau acteur
// retourne NULL en cas de probl�me
// pour ce projet il faut x y de d�part et type
//   ( � adapter selon besoins )
t_acteur * ajouterActeur(t_listeActeurs *la,int x,int y,int type);

// Enlever et lib�rer un acteur qui �tait dans la liste en indice i
void enleverActeur(t_listeActeurs *la,int i);



// Actualiser un acteur (bouger ...)
void actualiserActeur(t_acteur *acteur);

// G�rer l'�volution de l'ensemble des acteurs
void actualiserListeActeurs(t_listeActeurs *la);


// Dessiner un acteur sur la bitmap bmp
void dessinerActeur(BITMAP *bmp,t_acteur *acteur);

// Dessiner sur une bitmap l'ensemble des acteurs
void dessinerListeActeurs(BITMAP *bmp,t_listeActeurs *la);


// Un acteur a �t� touch� ou a touch� une cible : modifier son �tat
// ici on indique qu'il passe en comportement 1 (explosion)
// et le vecteur vitesse est divis� en norme (ralentissement)
void destinActeur(t_acteur *acteur);

// G�rer collision (�ventuelle) entre un acteur (un tir) et un ennemi
void collisionActeur(t_ennemi *ennemi,t_acteur *acteur);

// G�rer les collisions entre les acteurs (tous les tirs) et un ennemi
void collisionListeActeurs(t_ennemi *ennemi,t_listeActeurs *la);


// Sp�cifique � cet exemple : g�rer le vaisseau et la cible

// Allouer et initialiser joueur
t_joueur * creerJoueur(char *nomimage);

// Actualiser joueur (bouger interactivement et tirer...)
void actualiserJoueur(t_joueur *joueur,t_listeActeurs *la);

// Dessiner joueur sur la bitmap bmp
void dessinerJoueur(BITMAP *bmp,t_joueur *joueur);


// Allouer et initialiser ennemi
t_ennemi * creerEnnemi(char *nomimage);

// Actualiser ennemi (bouger automatiquement au hasard...)
void actualiserEnnemi(t_ennemi *ennemi);

// Dessiner ennemi sur la bitmap bmp
void dessinerEnnemi(BITMAP *bmp,t_ennemi *ennemi);



/******************************************/
/* PROGRAMME PRINCIPAL                    */
/* initialisation puis boucle d'animation */
/******************************************/

int main()
{

    // Buffer
    BITMAP *page;

    // Image de fond
    BITMAP *decor;

    // La collection des acteurs (les tirs)
    t_listeActeurs *acteurs;

    // Le vaisseau manipul� par le joueur
    t_joueur *vaisseau;

    // La cible qui se d�place automatiquement
    t_ennemi *cible;

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

    // buffer
    page=create_bitmap(SCREEN_W,SCREEN_H);

    // charger image de fond
    decor=load_bitmap("images/hotplanet.bmp",NULL);
    if (!decor)
    {
        allegro_message("pas pu trouver images/hotplanet.bmp");
        exit(EXIT_FAILURE);
    }

    // cr�er le vaisseau et la cible
    vaisseau=creerJoueur("images/spaceship.bmp");
    cible=creerEnnemi("images/deathstar.bmp");

    // pr�parer la liste des acteurs (100 maxi)
    // mais vide initialement
    acteurs=creerListeActeurs(100);

    // BOUCLE DE JEU
    while (!key[KEY_ESC])
    {
        // effacer buffer en appliquant d�cor  (pas de clear_bitmap)
        blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);

        // bouger tout le monde
        actualiserJoueur(vaisseau,acteurs);
        actualiserEnnemi(cible);
        actualiserListeActeurs(acteurs);

        // g�rer les collisions
        collisionListeActeurs(cible,acteurs);

        // afficher tout le monde
        dessinerJoueur(page,vaisseau);
        dessinerEnnemi(page,cible);
        dessinerListeActeurs(page,acteurs);

        // afficher tout �a � l'�cran
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // petite temporisation
        rest(10);
    }

    return 0;
}
END_OF_MAIN();



/************************************************/
/*     DEFINITIONS DES SOUS-PROGRAMMES          */
/************************************************/


// Allouer et initialiser un acteur
t_acteur * creerActeur(int x,int y,int type){
    t_acteur *nouv;

    // Allouer
    nouv=(t_acteur *)malloc(1*sizeof(t_acteur));

    // Initialiser ...

    // ici ce qui est commun aux acteurs
    nouv->x=x;
    nouv->y=y;
    nouv->type=type;
    nouv->comportement=0;
    nouv->cptexplo=0; // pas encore explos� mais on initialise par s�curit�
    nouv->vivant=1;

    // ici ce qui est sp�cifique aux types
    switch (type)
    {
        // laser
        case 0:
            nouv->tx=30;
            nouv->ty=5;
            nouv->dx=10;
            nouv->dy=0;
            nouv->couleur=makecol(255,255,0);
            break;

        // missile
        case 1:
            nouv->tx=40;
            nouv->ty=20;
            nouv->dx=2;
            // petite dispersion dans la trajectoire des missiles :
            nouv->dy=rand()%5-2;
            nouv->couleur=makecol(240,220,220);
            break;
    }

    return nouv;
}

// Actualiser un acteur (bouger, sortie �cran, fin explosion ...)
void actualiserActeur(t_acteur *acteur){

    // deplacement
    acteur->x=acteur->x+acteur->dx;
    acteur->y=acteur->y+acteur->dy;

    // type missile : acc�l�re en dx mais pas au dela d'une limite
    if (acteur->type==1 && acteur->dx<14)
        acteur->dx++;

    // si d�passe le bord alors disparait
    if (acteur->x+acteur->tx<0 || acteur->x>SCREEN_W || acteur->y+acteur->ty<0 || acteur->y>SCREEN_H )
        acteur->vivant=0;

    // si en cours d'explosion incr�menter cptexplo
    // et si explose depuis trop longtemps alors disparait
    if (acteur->comportement==1)
    {
        acteur->cptexplo++;
        if (acteur->cptexplo > 7)
            acteur->vivant=0;
    }
}

// Dessiner un acteur sur la bitmap bmp
void dessinerActeur(BITMAP *bmp,t_acteur *acteur){
    // Si pas d'explosion
    if (acteur->comportement==0){
        switch(acteur->type)
        {
            case 0:
                rectfill(bmp,acteur->x,acteur->y,acteur->x+acteur->tx,acteur->y+acteur->ty,acteur->couleur);
                break;
            case 1:
                ellipsefill(bmp,acteur->x,acteur->y+acteur->ty/2,2*acteur->tx/3,acteur->ty/2,makecol(255,100,25));
                ellipsefill(bmp,acteur->x,acteur->y+acteur->ty/2,acteur->tx/3,acteur->ty/3,makecol(255,200,50));
                triangle(bmp,acteur->x,acteur->y,acteur->x,acteur->y+acteur->ty,acteur->x+acteur->tx,acteur->y+acteur->ty/2,acteur->couleur);
                break;
        }
    }
    // sinon on dessine l'explosion
    // d'un diam�tre d�croissant et d'une couleur rougissante
    else {
        switch(acteur->type)
        {
            case 0:
                circlefill(bmp,acteur->x+acteur->tx/2,acteur->y+acteur->ty/2,30-4*acteur->cptexplo,makecol(255,255-15*acteur->cptexplo,255-30*acteur->cptexplo));
                break;
            case 1:
                circlefill(bmp,acteur->x+acteur->tx/2,acteur->y+acteur->ty/2,60-6*acteur->cptexplo,makecol(255-15*acteur->cptexplo,128-15*acteur->cptexplo,0));
                break;
        }
    }
}

// Allouer et initialiser une liste (vide) de acteurs
t_listeActeurs * creerListeActeurs(int maxacteurs){
    t_listeActeurs *nouv;
    int i;

    nouv=(t_listeActeurs *)malloc(1*sizeof(t_listeActeurs));

    nouv->max=maxacteurs;
    nouv->n=0;
    nouv->tab=(t_acteur **)malloc(maxacteurs*sizeof(t_acteur*));

    for (i=0;i<maxacteurs;i++)
        nouv->tab[i]=NULL;

    return nouv;
}

// Retourne un bool�en vrai si il reste de la place
// dans la liste, faux sinon
int libreListeActeurs(t_listeActeurs *la){
    return la->n < la->max;
}

// Allouer et ajouter un acteur � la liste
// et retourner l'adresse de ce nouveau acteur
// retourne NULL en cas de probl�me
// ( mais il vaut mieux d'abord v�rifier qu'il
//   y a de la place disponible avant d'appeler )
t_acteur * ajouterActeur(t_listeActeurs *la,int x,int y,int type){
    int i;
    t_acteur *acteur;

    // Liste pleine, on alloue rien et on retourne NULL...
    if (la->n >= la->max)
        return NULL;

    // Allouer un acteur initialis�
    acteur=creerActeur(x,y,type);

    // Chercher un emplacement libre
    i=0;
    while (la->tab[i]!=NULL && i<la->max)
        i++;

    // Si on a trouv� ...
    // (normalement oui car on a v�rifi� n<max)
    if (i<la->max){
        // Accrocher le acteur � l'emplacement trouv�
        la->tab[i]=acteur;
        la->n++;
    }
    // Sinon c'est qu'il y a un probl�me de coh�rence
    else
        allegro_message("Anomalie gestion ajouterActeur : liste corrompue");

    return acteur;
}

// Enlever et lib�rer un acteur qui �tait dans la liste en indice i
void enleverActeur(t_listeActeurs *la,int i){

    // V�rifier qu'il y a bien un acteur accroch� en indice i
    if (la->tab[i]!=NULL)
    {
        // lib�rer la m�moire du acteur
        free(la->tab[i]);

        // marquer l'emplacement comme libre
        la->tab[i]=NULL;
        la->n--;

    }
}

// G�rer l'�volution de l'ensemble des acteurs
void actualiserListeActeurs(t_listeActeurs *la){
    int i;

    // actualiser chaque acteur
    // si un acteur n'est plus vivant, l'enlever de la liste
    for (i=0;i<la->max;i++)
        if (la->tab[i]!=NULL){
            actualiserActeur(la->tab[i]);
            if (!la->tab[i]->vivant){
                enleverActeur(la,i);
            }
        }
}

// Dessiner sur une bitmap l'ensemble des acteurs
void dessinerListeActeurs(BITMAP *bmp,t_listeActeurs *la){
    int i;

    for (i=0;i<la->max;i++)
        if (la->tab[i]!=NULL)
            dessinerActeur(bmp,la->tab[i]);

}


// Un acteur a �t� touch� ou a touch� une cible : modifier son �tat
// ici on indique qu'il passe en comportement 1 (explosion)
// et le vecteur vitesse est divis� en norme (ralentissement)
void destinActeur(t_acteur *acteur){
    acteur->dx/=2;
    acteur->dy/=2;
    acteur->comportement=1;
    acteur->cptexplo=0;
}

// G�rer collision (�ventuelle) entre un acteur (un tir) et un ennemi
void collisionActeur(t_ennemi *ennemi,t_acteur *acteur){
    int vx,vy,d2;

    // si il n'explose d�j� pas !
    if ( acteur->comportement==0 )
    {
        // si il est dans la cible alors appeler destinActeur (explosion)

        // calcul du vecteur entre acteur et centre cible
        vx = acteur->x+acteur->tx/2 - (ennemi->x+ennemi->tx/2);
        vy = acteur->y+acteur->ty/2 - (ennemi->y+ennemi->ty/2);

        // calcul distance au carr� au centre de la cible (Pythagore)
        // (on reste sur le carr� pour �viter de calculer la racine)
        d2 = vx*vx + vy*vy;

        // si dans le disque alors destin...
        if ( d2 < ennemi->tx * ennemi->tx / 4 )
            destinActeur(acteur);
    }
}

// G�rer les collisions entre les acteurs (tous les tirs) et un ennemi
void collisionListeActeurs(t_ennemi *ennemi,t_listeActeurs *la){

    int i;

    // regarder pour chaque acteur...
    for (i=0;i<la->max;i++)
        if (la->tab[i]!=NULL)
            collisionActeur(ennemi,la->tab[i]);

}


// Allouer et initialiser un joueur
t_joueur * creerJoueur(char *nomimage){
    t_joueur *nouv;

    // Allouer
    nouv = (t_joueur *)malloc(1*sizeof(t_joueur));

    // Initialiser

    nouv->img=load_bitmap(nomimage,NULL);
    if (!nouv->img)
    {
        allegro_message("pas pu trouver %s",nomimage);
        exit(EXIT_FAILURE);
    }

    nouv->tx = nouv->img->w;
    nouv->ty = nouv->img->h;

    nouv->x = SCREEN_W/4-nouv->tx/2;
    nouv->y = SCREEN_H/2-nouv->ty/2;
    nouv->vit = 5;

    nouv->cpttir0 = 0;
    nouv->cpttir1 = 0;

    return nouv;
}

// Actualiser joueur (bouger interactivement et tirer...)
void actualiserJoueur(t_joueur *joueur,t_listeActeurs *la){

    // D�placements instantan�s (pas d'inertie)
    // gestion d'un blocage dans une zone �cran (moiti� gauche)
    if (key[KEY_LEFT]){
        joueur->x -= joueur->vit;
        if (joueur->x<0)
            joueur->x=0;
    }

    if (key[KEY_RIGHT]){
        joueur->x += joueur->vit;
        if (joueur->x+joueur->tx > SCREEN_W/2)
            joueur->x=SCREEN_W/2-joueur->tx;
    }

    if (key[KEY_UP]){
        joueur->y -= joueur->vit;
        if (joueur->y<0)
            joueur->y=0;
    }

    if (key[KEY_DOWN]){
        joueur->y += joueur->vit;
        if (joueur->y+joueur->ty > SCREEN_H)
            joueur->y=SCREEN_H-joueur->ty;
    }

    // Gestion du tir...

    // incr�menter la tempo des tirs
    joueur->cpttir0++;
    joueur->cpttir1++;

    // si le joueur appui sur la gachette et arme ok...
    // espace = laser
    if (key[KEY_SPACE] && joueur->cpttir0>=5){
        ajouterActeur(la,joueur->x+joueur->tx,joueur->y+joueur->ty/2,0);
        joueur->cpttir0 = 0;
    }
    // entr�e = missile
    if (key[KEY_ENTER] && joueur->cpttir1>=10){
        ajouterActeur(la,joueur->x+joueur->tx,joueur->y+joueur->ty/2,1);
        joueur->cpttir1 = 0;
    }
}

// Dessiner joueur sur la bitmap bmp
void dessinerJoueur(BITMAP *bmp,t_joueur *joueur){
    draw_sprite(bmp,joueur->img,joueur->x,joueur->y);
}


// Allouer et initialiser ennemi
t_ennemi * creerEnnemi(char *nomimage){
    t_ennemi *nouv;

    // Allouer
    nouv = (t_ennemi *)malloc(1*sizeof(t_ennemi));

    // Initialiser

    nouv->img=load_bitmap(nomimage,NULL);
    if (!nouv->img)
    {
        allegro_message("pas pu trouver %s",nomimage);
        exit(EXIT_FAILURE);
    }

    nouv->tx = nouv->img->w;
    nouv->ty = nouv->img->h;

    nouv->x = 3*SCREEN_W/4-nouv->tx/2;
    nouv->y = SCREEN_H/2-nouv->ty/2;
    nouv->dx=0;
    nouv->dy=0;

    return nouv;
}

// Actualiser ennemi
// (bouger automatiquement au hasard dans la moiti� droite...)
void actualiserEnnemi(t_ennemi *ennemi){

    // proba de changement de d�placement : une chance sur 20
    if ( rand()%20==0 ){
        // Nouveau vecteur d�placement
        ennemi->dx = rand()%11-5;
        ennemi->dy = rand()%11-5;
    }

    // contr�le des bords : ici on d�cide de rebondir sur les bords
    if  (  ( ennemi->x < SCREEN_W/2 && ennemi->dx < 0 ) ||
           ( ennemi->x + ennemi->tx > SCREEN_W && ennemi->dx > 0) )
        ennemi->dx = -ennemi->dx;

    if  (  ( ennemi->y < 0 && ennemi->dy < 0 ) ||
           ( ennemi->y + ennemi->ty > SCREEN_H && ennemi->dy > 0) )
        ennemi->dy = -ennemi->dy;

    // calculer nouvelle position
    // nouvelle position = position actuelle + deplacement
    ennemi->x = ennemi->x + ennemi->dx;
    ennemi->y = ennemi->y + ennemi->dy;

}

// Dessiner ennemi sur la bitmap bmp
void dessinerEnnemi(BITMAP *bmp,t_ennemi *ennemi){
    draw_sprite(bmp,ennemi->img,ennemi->x,ennemi->y);
}
