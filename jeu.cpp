#include "jeu.h"
#include "maps.h"
#include <iostream>
#include <assert.h>

// Nous utilisons une bibliotheque de maps pour designer les maps correspondant les niveaux du jeu
extern const char terrain_1[17][21];
extern const char terrain_2[17][21];
extern const char terrain_3[17][21];
extern const char terrain_4[17][21];
extern const char terrain_fin[17][21];


// Fantome
Fantome::Fantome()
{
    posX = 0; posY = 0;
    dir = BAS;
}

int Fantome::getPosX() const
{
    return posX;
}

int Fantome::getPosY() const
{
    return posY;
}


//Pacman
Pacman::Pacman()
{
    PosPacX =0; PosPacY =0;
    PointVie =3;
}

// Retourner les dimenssions des pacmans
int Pacman::getPosPacX() const
{
    return PosPacX;
}

int Pacman::getPosPacY() const
{
    return PosPacY;
}

// Retourner Point de Vie
int Pacman::Get_PointVie() const
{
    return PointVie;
}

void Pacman::Set_PointVie(const int a)
{
    PointVie = a;
}

//Jeu
Jeu::Jeu()
{
    terrain = NULL;
    largeur = 0; hauteur = 0;
    NbGomme = 0;
    niveau = 1;
    NbJoueur = 1;
}

Jeu::~Jeu()
{
    if (terrain!=NULL)
        delete[] terrain;
}

// Initialiser Pacman
void Jeu::Pacman_Init(Pacman *p)
{
    int x,y;
    p->Set_PointVie(3);

    do {
        x = rand()%largeur;
        y = rand()%hauteur;
    } while (terrain[y*largeur+x]!=VIDE);

    p->PosPacX = x;
    p->PosPacY = y;
}

bool Jeu::init()            // Niveau 1
{
	int x, y;
	list<Fantome>::iterator itFantome;
	Set_Niveau(1);
	Get_NbJoueur();

        char terrain_defaut[17][21];

        largeur = 20;
        hauteur = 17;

        for(int i=0;i<hauteur;i++) {
            for(int j=0;j<largeur;j++) {
                terrain_defaut[i][j] = terrain_1[i][j];
            }
        }

        terrain = new Case[largeur*hauteur];

        for(y=0;y<hauteur;++y)
            for(x=0;x<largeur;++x)
                if (terrain_defaut[y][x]=='#')
                    terrain[y*largeur+x] = MUR;
                else if (terrain_defaut[y][x]=='.')
                    terrain[y*largeur+x] = VIDE;
                else if (terrain_defaut[y][x]=='/')
                    terrain[y*largeur+x] = GOMME;
                else if (terrain_defaut[y][x]=='|')
                    terrain[y*largeur+x] = PORTE;
                else if (terrain_defaut[y][x]==';')
                    terrain[y*largeur+x] = COVER;
                else terrain[y*largeur+x] = BONUS;

        fantomes.resize(3);

        for (itFantome=fantomes.begin(); itFantome!=fantomes.end(); itFantome++)
        {
            do {
                x = rand()%largeur;
                y = rand()%hauteur;
            } while (terrain[y*largeur+x]!=VIDE);

            itFantome->posX = x;
            itFantome->posY = y;
            itFantome->dir = (Direction)(rand()%4);
        }

        do {
            x = rand()%largeur;
            y = rand()%hauteur;
        } while (terrain[y*largeur+x]!=VIDE);

            Pacman_Init(&Pacman1);
            Pacman_Init(&Pacman2);
        return true;
}

bool Jeu::niveau2()             // Niveau 2 (Pour passer au niveau 2, il faut terminer le niveau 1)
{
    int x, y;
	list<Fantome>::iterator itFantome;
	Set_Niveau(Get_Niveau() + 1); // Augmenter le niveau
    Get_NbJoueur();
    char terrain_defaut[17][21];

        largeur = 20;
        hauteur = 17;

        switch(Get_Niveau()) // Pour choisir le niveau
        {
        case 2:
            for(int i=0;i<hauteur;i++) {        // Utiliser boucle for pour inserser le terrain de maps
                for(int j=0;j<largeur;j++) {
                    terrain_defaut[i][j] = terrain_2[i][j];
                }
            }
            fantomes.resize(7);
            break;
        case 3:
            for(int i=0;i<hauteur;i++) {
                for(int j=0;j<largeur;j++) {
                    terrain_defaut[i][j] = terrain_3[i][j];
                }
            }
            fantomes.resize(8);
            break;
        case 4:
            for(int i=0;i<hauteur;i++) {
                for(int j=0;j<largeur;j++) {
                    terrain_defaut[i][j] = terrain_4[i][j];
                }
            }
            fantomes.resize(9);
            break;
        case 5:
            for(int i=0;i<hauteur;i++) {
                for(int j=0;j<largeur;j++) {
                    terrain_defaut[i][j] = terrain_fin[i][j];
                }
            }
            fantomes.resize(0);
            break;

        }

        terrain = new Case[largeur*hauteur];

        for(y=0;y<hauteur;++y)
            for(x=0;x<largeur;++x)
                if (terrain_defaut[y][x]=='#')
                    terrain[y*largeur+x] = MUR;
                else if (terrain_defaut[y][x]=='.')
                    terrain[y*largeur+x] = VIDE;
                else if (terrain_defaut[y][x]=='/')
                    terrain[y*largeur+x] = GOMME;
                else if (terrain_defaut[y][x]=='|')
                    terrain[y*largeur+x] = PORTE;
                else if (terrain_defaut[y][x]==';')
                    terrain[y*largeur+x] = COVER;
                else terrain[y*largeur+x] = BONUS;

        for (itFantome=fantomes.begin(); itFantome!=fantomes.end(); itFantome++)
        {
            do {
                x = rand()%largeur;
                y = rand()%hauteur;
            } while (terrain[y*largeur+x]!=VIDE);

            itFantome->posX = x;
            itFantome->posY = y;
            itFantome->dir = (Direction)(rand()%4);
        }

        do {
            x = rand()%largeur;
            y = rand()%hauteur;
        } while (terrain[y*largeur+x]!=VIDE);

            Pacman_Init(&Pacman1);
            Pacman_Init(&Pacman2);

        return true;
}
void Jeu::evolue()
{
    int testX, testY;
	list<Fantome>::iterator itFantome;
	Set_NBGommes();

    int depX[] = {-1, 1, 0, 0};
    int depY[] = {0, 0, -1, 1};

    for (itFantome=fantomes.begin(); itFantome!=fantomes.end(); itFantome++)
    {
        testX = itFantome->posX + depX[itFantome->dir];
        testY = itFantome->posY + depY[itFantome->dir];

        if ((terrain[testY*largeur+testX] !=MUR) && (terrain[testY*largeur+testX] !=PORTE))
        {
            itFantome->posX = testX;
            itFantome->posY = testY;
        }
        else
            // Changement de direction
            itFantome->dir = (Direction)(rand()%4);
    }
}


// Retourne les dimensions (en nombre de cases)
int Jeu::getNbCasesX() const
{
    return largeur;
}

int Jeu::getNbCasesY() const
{
    return hauteur;
}

// Retourne la case à une position donnée
Case Jeu::getCase(int x, int y) const
{
    assert(x>=0 && x<largeur && y>=0 && y<hauteur);
    return terrain[y*largeur+x];
}


// Indique si la case à une position donnée existe et est vide
// (Pacman ou les fantomes peuvent l'occuper)
bool Jeu::posValide(int x, int y) const
{
    return (x>=0 && x<largeur && y>=0 && y<hauteur && terrain[y*largeur+x] !=MUR);
}


// Déplace Pacman dans une direction (si la case à atteindre est valide)
bool Jeu::deplacePacman(Pacman *p,Direction dir)
{
    int depX[] = {-1, 1, 0, 0};
    int depY[] = {0, 0, -1, 1};
    int testX, testY;

    testX = p->PosPacX + depX[dir];
    testY = p->PosPacY + depY[dir];

    if (posValide(testX, testY))
    {
        p->PosPacX = testX;
        p->PosPacY = testY;
        return true;
    }
    else
        return false;
}


// Mettre nombre de joueurs
 void Jeu::Set_NbJoueur(const int a)
 {
     NbJoueur = a;
 }

 // Retouer nombre de joueurs
 int Jeu::Get_NbJoueur() const
 {
     return NbJoueur;
 }


// Verifier les Collisions entre pacman et fantomes
bool Jeu :: Verifier_collisions(Pacman *p)
{
    list<Fantome>::iterator itFantome;
    for (itFantome=fantomes.begin(); itFantome!=fantomes.end(); itFantome++)
    {
        if ((p->PosPacX == itFantome->posX) && (p->PosPacY == itFantome->posY))
        {
            return true;
        }
    }
    return false;
}


// Collisions entre pacman et fantomes
void Jeu::Handle_collisions(Pacman *p)
{
    if (Verifier_collisions(p) == true)
    {
        // retourner au milieu du jeu
        p->PosPacX = 10;
        p->PosPacY = 9;
        p->PointVie = p->PointVie - 1;
        cout<<"Vous avez perdu un vie"<<endl;
        cout<<p->PointVie<<endl;
    }
}


// Bonus point de Vie
void Jeu :: Handle_Bonus(Pacman *p)
{
    if (getCase(p->PosPacX,p->PosPacY) == BONUS)
    {
        terrain[p->PosPacY*largeur+p->PosPacX] = VIDE;
        p->PointVie = p->PointVie + 1;
    }
}

// Verifier Gagner
bool Jeu::Verifier_Gagner(Pacman p)
 {
     if (Get_NBGommes() == -1)
     {
         if (getCase(p.getPosPacX(),p.getPosPacY()) == PORTE)
            return true;
     }
     else
        return false;
 }

// Set Nombre de gommes
void Jeu::Set_NBGommes()
{
    int x, y;
    int compte = -1;
    for(y=0;y<hauteur;++y)
    {
		for(x=0;x<largeur;++x)
        {
            if (getCase(x,y) == GOMME)
                compte = compte + 1;
        }
    }
    NbGomme = compte;
}

// Get Nombre de gommes
int Jeu::Get_NBGommes() const
{
    return NbGomme;
}

// Handle Gomme
void Jeu :: Handle_Gomme(Pacman p)
{
    int x,y;
    x = p.getPosPacX();
    y = p.getPosPacY();
    if (getCase(x,y) == GOMME)
    {
        terrain[y*largeur+x] = VIDE;
        cout<< "Nombre de Gommes reste :"<<Get_NBGommes()<<endl;
    }
}

// Set niveau du jeu
 void Jeu::Set_Niveau(int n)
 {
     niveau = n;
 }

 // Get niveau du jeu
 int Jeu::Get_Niveau()
 {
     return niveau;
 }




