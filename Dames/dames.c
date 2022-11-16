#include <stdio.h>
#include <conio.c>
#include "dames_header.h"

/*VARIABLE GLOBALE POUR LA RAPIDITE DES MENUS*/
int   rapidite=5;

/*STRUCTURE POUR LA POSITION DU CURSEUR DES PIONS ET DE QUELQUES TRUCS DIVERS*/
typedef struct
{
  int X;
  int Y;
  int A;
  int B;
} POS;

/*FONCTION PRINCIPALE*/
int main()
{
  /*DEFINITION DES VARIABLES*/
  POS   curseur; //POSITION DU CURSEUR
  POS   pions; //POSITION DES PIONS
  POS   manger; //TRUCS DIVERS
  int   increment; //POUR LES BOUCLES
  int   increment2; //POUR LES BOUCLES
  int   increment3; //POUR LES BOUCLES
  int   increment4; //POUR LES BOUCLES
  int   sortie=1; //POUR LA BOUCLE PRINCIPALE
  int   action=0; //POUR LES ACTIONS UTILISATEURS
  int   tour=1; //DEFINIT LE TOUR DU JOUEUR
  int   choix=0; //POUR LE MENU
  int   dame; //UTILE POUR LES DAMES
  int   menu; //POUR LE MENU
  int   coups=0; //COMPTE LE NOMBRE DE DEPLACEMENTS DE PION
  int   couleurs[4]={10,12,14,13}; //POUR LES COULEURS
  char  touche; //POUR LES ENTREES UTILISATEURS
  char  damier[10][10];//POUR LA POSITION DES PIONS

  /*INITIALISATION*/
  initialise(damier);//INITIALISE LA POSITION DES PIONS
  curseur.X=0;
  curseur.Y=0;
  curseur.A=0;
  curseur.B=0;
  pions.X=0;
  pions.Y=0;
  pions.A=0;
  pions.B=0;

  /*DESSIN DE L'INTERFACE*/
  textcolor(15);//ECRIS EN BLANC
  /*ECRIS LES NUMEROS CASES*/
  for (increment=1 ; increment<=10 ; increment++)
  {
    gotoxy(increment*4,1);
    printf("%d",increment);
    sleep(30);
  }
  /*ECRIS LES LETTRES DE CASES*/
  for (increment='A' ; increment<='J' ; increment++)
  {
    gotoxy(1,((increment-65)*2)+3);
    printf("%c",increment);
    sleep(30);
  }
  textcolor(couleurs[0]);
  /*DESSINE LE TABLEAU*/
  for (increment=0 ; increment<=10 ; increment++)
  {
    tableau(2,2,increment,increment,3,1);
    sleep(50);
  }
  /*ECRIS LE PETIT TEXTE D'AIDE*/
  gotoxy(44,18);
  printf("Pour jouer, utilisez les touches");
  gotoxy(44,19);
  printf("%c %c %c %c pour faire bouger le",24,25,26,27);
  gotoxy(44,20);
  printf("curseur, enter pour choisir un");
  gotoxy(44,21);
  printf("pion et une case, espace pour");
  gotoxy(44,22);
  printf("annuler le pion choisi et escape");
  gotoxy(44,23);
  printf("pour afficher le menu.");
  gotoxy(1,24);
  /*ECRIS AUCUN PION N'EST CHOISI EN BAS A GAUCHE*/
  textcolor(couleurs[tour]);
  printf("Aucun pion choisi");
  /*ECRIS AUCUN PION N'EST CHOISI DANS UNE BOITE*/
  textcolor(couleurs[3]);
  dessine_menu(19,1);
  gotoxy(47,6);
  textcolor(couleurs[tour]);
  printf("Aucun pion choisi");

  /*BOUCLE PRINCIPALE => DEBUT JOUABLE*/
  while (sortie!=0)
  {
    /*DESSINE TOUS LES PIONS*/
    for (increment=0 ; increment<=9 ; increment++)
    {
      for (increment2=0 ; increment2<=9 ; increment2++)
      {
        gotoxy((increment2*4)+4,(increment*2)+3);
        if ((damier[increment2][increment]=='\x05')||(damier[increment2][increment]=='\x01')) textcolor(couleurs[1]);
        else textcolor(couleurs[2]);
        printf("%c",damier[increment2][increment]);
      }
    }
    /*INITIALISE MANGER.A ET MANGER.B*/
    manger.A=0;
    manger.B=0;
    /*COMPTE LE NOMBRE DE PIONS RESTANT CHEZ CHAQUE JOUEUR*/
    for (increment=0 ; increment<=9 ; increment++)
    {
      for (increment2=0 ; increment2<=9 ; increment2++)
      {
        if ((damier[increment2][increment]=='\x01')
        ||  (damier[increment2][increment]=='\x05')) manger.A++;
        if ((damier[increment2][increment]=='\x02')
        ||  (damier[increment2][increment]=='\x06')) manger.B++;
      }
    }
    /*AFFICHE LE NOMBRE DE PIONS RESTANT CHEZ CHAQUE JOUEUR*/
    textcolor(couleurs[0]);
    gotoxy(44,1);
    printf("coups n\xF8 %d  ",coups);
    gotoxy(44,2);
    printf("%d pions joueur 1         ",manger.A);
    gotoxy(44,3);
    printf("%d pions joueur 2         ",manger.B);
    /*SI UN DES JOUEURS A PERDU TOUS SES PION*/
    if ((manger.A==0)||(manger.B==0))
    {
      /*DESSINE UNE BOITE AVEC UN MESSAGE AVERTISSANT LE
      JOUEUR QU'IL A GAGNE*/
      choix=1;
      textcolor(couleurs[3]);
      dessine_menu(28,3);
      if (manger.A==0) tour=2;
      else tour=1;
      textcolor(couleurs[tour]);
      gotoxy(47,6);
      printf("BRAVO ! joueur %d a gagn\x82 !",tour);
      gotoxy(47,7);
      printf("Voulez vous rejouer ?");
      /*PETIT MENU POUR OUI OU NON*/
      while (choix!=0)
      {
        gotoxy(47,8);
        /*OUI*/
        if (choix==1) textcolor(couleurs[0]);
        else textcolor(couleurs[tour]);
        printf("Oui               ");
        /*NON*/
        if (choix==2) textcolor(couleurs[0]);
        else textcolor(couleurs[tour]);
        printf("Non");
        /*PREND LA TOUCHE PRESSEE*/
        touche=getch();
        /*SI GAUCHE*/
        if (touche==GAUCHE)
        {
          if (choix==2) choix=1;
        }
        /*SI DROITE*/
        if (touche==DROITE)
        {
          if (choix==1) choix=2;
        }
        /*SI ENTER*/
        if (touche==ENTER)
        {
          /*SI OUI REINITIALISE TOUT*/
          if (choix==1)
          {
            for (increment=0 ; increment<=9 ; increment++)
            {
              for (increment2=0 ; increment2<=32 ; increment2++)
              {
                gotoxy(45+increment2,5+increment);
                printf(" ");
              }
            }
            gotoxy((curseur.X*4)+3,(curseur.Y*2)+3);
            printf(" ");
            gotoxy((curseur.X*4)+5,(curseur.Y*2)+3);
            printf(" ");
            initialise(damier);
            curseur.X=0;
            curseur.Y=0;
            curseur.A=0;
            curseur.B=0;
            pions.X=0;
            pions.Y=0;
            pions.A=0;
            pions.B=0;
            coups=0;
            choix=0;
            tour=1;
          }
          /*SI NON QUITTE*/
          else
          {
            rapidite=0;
            choix=0;
            sortie=0;
          }
        }//FIN DU SI DE LA TOUCHE ENTER
      }//FIN DE LA BOUCLE
    }//FIN DU SI SIUN JOUEUR GAGNAIT
    /*DESSINE LE CURSEUR*/
    textcolor(couleurs[3]);
    gotoxy((curseur.A*4)+3,(curseur.B*2)+3);
    printf(" ");
    gotoxy((curseur.A*4)+5,(curseur.B*2)+3);
    printf(" ");
    gotoxy((curseur.X*4)+3,(curseur.Y*2)+3);
    printf("[");
    gotoxy((curseur.X*4)+5,(curseur.Y*2)+3);
    printf("]");
    /*PREND LA TOUCHE QUE SI SORTIE != 0*/
    if (sortie!=0) touche=getch();
    switch(touche)
    {
      /*GAUCHE*/
      case GAUCHE: curseur.A=curseur.X;
                   curseur.B=curseur.Y;
                   curseur.X--;
                   if (curseur.X==-1) curseur.X=0;
                   break;
      /*DROITE*/
      case DROITE: curseur.A=curseur.X;
                   curseur.B=curseur.Y;
                   curseur.X++;
                   if (curseur.X==10) curseur.X=9;
                   break;
      /*HAUT*/
      case HAUT:   curseur.A=curseur.X;
                   curseur.B=curseur.Y;
                   curseur.Y--;
                   if (curseur.Y==-1) curseur.Y=0;
                   break;
      /*BAS*/
      case BAS:    curseur.A=curseur.X;
                   curseur.B=curseur.Y;
                   curseur.Y++;
                   if (curseur.Y==10) curseur.Y=9;
                   break;
      /*ENTER*/
      case ENTER:  /*TOUCHE ENTER PLUS LOIN POUR AMELIORER LA VISIBILITE*/
                   switch (action)
                   {
                     case 0: action=1;
                             break;
                     case 4: action=2;
                             break;
                     case 5: action=3;
                             break;
                   }
                   break;
      /*ESPACE POUR ANNULER LE PION CHOISI*/
      case ESPACE: if ((action==4)||(action==5))
                   {
                     for (increment=0 ; increment<=5 ; increment++)
                     {
                       for (increment2=0 ; increment2<=33 ; increment2++)
                       {
                         gotoxy(45+increment2,5+increment);
                         printf(" ");
                       }
                     }
                     textcolor(couleurs[3]);
                     dessine_menu(19,1);
                     gotoxy(47,6);
                     textcolor(couleurs[tour]);
                     printf("Aucun pion choisi");
                     gotoxy(1,24);
                     printf("Aucun pion choisi");
                     action=0;
                   }
                   break;
      /*ESCAPE POUR AFFICHER LE MENU*/
      case ESCAPE: textcolor(couleurs[3]);
                   /*EFFACE LA BOITE DE DIALOGUE PRECEDANTE*/
                   for (increment=0 ; increment<=9 ; increment++)
                   {
                     for (increment2=0 ; increment2<=32 ; increment2++)
                     {
                       gotoxy(45+increment2,5+increment);
                       printf(" ");
                     }
                   }
                   /*DESSINE UNE NOUVELLE BOITE*/
                   dessine_menu(30,8);
                   choix=0;
                   menu=1;
                   /*MENU*/
                   while (menu!=0)
                   {
                     gotoxy(47,6);
                     if (choix==0) textcolor(couleurs[3]);
                     else textcolor(couleurs[0]);
                     printf("Reprendre le jeu");
                     gotoxy(47,7);
                     if (choix==1) textcolor(couleurs[3]);
                     else textcolor(couleurs[0]);
                     printf("Nouvelle partie");
                     gotoxy(47,8);
                     if (choix==2) textcolor(couleurs[3]);
                     else textcolor(couleurs[0]);
                     printf("Couleur du jeu           ");
                     textcolor(couleurs[0]);
                     printf("\xDB\xDB\xDB");
                     gotoxy(47,9);
                     if (choix==3) textcolor(couleurs[3]);
                     else textcolor(couleurs[0]);
                     printf("Couleur joueur 1         ");
                     textcolor(couleurs[1]);
                     printf("\xDB\xDB\xDB");
                     gotoxy(47,10);
                     if (choix==4) textcolor(couleurs[3]);
                     else textcolor(couleurs[0]);
                     printf("Couleur joueur 2         ");
                     textcolor(couleurs[2]);
                     printf("\xDB\xDB\xDB");
                     gotoxy(47,11);
                     if (choix==5) textcolor(couleurs[3]);
                     else textcolor(couleurs[0]);
                     printf("Couleur du curseur       ");
                     textcolor(couleurs[3]);
                     printf("\xDB\xDB\xDB");
                     gotoxy(47,12);
                     if (choix==6) textcolor(couleurs[3]);
                     else textcolor(couleurs[0]);
                     printf("Rapidite du menu           ");
                     textcolor(couleurs[0]);
                     printf("%-2d",rapidite);
                     gotoxy(47,13);
                     if (choix==7) textcolor(couleurs[3]);
                     else textcolor(couleurs[0]);
                     printf("Quitter");
                     /*PREND LA TOUCHE PRESSEE*/
                     touche=getch();
                     /*SI BAS*/
                     if (touche==BAS)
                     {
                       choix++;
                       if (choix==8) choix=0;
                     }
                     /*SI HAUT*/
                     if (touche==HAUT)
                     {
                       choix--;
                       if (choix==-1) choix=7;
                     }
                     /*SI ENTER ET VEUT REPRENDRE LE JEU*/
                     if ((touche==ENTER)&&(choix==0))
                     {
                       menu=0;
                       for (increment=0 ; increment<=9 ; increment++)
                       {
                         for (increment2=0 ; increment2<=31 ; increment2++)
                         {
                           gotoxy(45+increment2,5+increment);
                           printf(" ");
                         }
                       }
                     }
                     /*SI ENTER ET VEUT FAIRE UNE NOUVELLE PARTIE*/
                     if ((touche==ENTER)&&(choix==1))
                     {
                       /*REINITIALISE TOUT*/
                       menu=0;
                       for (increment=0 ; increment<=9 ; increment++)
                       {
                         for (increment2=0 ; increment2<=32 ; increment2++)
                         {
                           gotoxy(45+increment2,5+increment);
                           printf(" ");
                         }
                       }
                       gotoxy((curseur.X*4)+3,(curseur.Y*2)+3);
                       printf(" ");
                       gotoxy((curseur.X*4)+5,(curseur.Y*2)+3);
                       printf(" ");
                       initialise(damier);
                       curseur.X=0;
                       curseur.Y=0;
                       curseur.A=0;
                       curseur.B=0;
                       pions.X=0;
                       pions.Y=0;
                       pions.A=0;
                       pions.B=0;
                       coups=0;
                       tour=1;
                     }
                     /*SI ENTER ET VEUT QUITTER*/
                     if ((touche==ENTER)&&(choix==7))
                     {
                       menu=0;
                       sortie=0;
                     }
                     /*SI GAUCHE*/
                     if (touche==GAUCHE)
                     {
                       /*TOUTES LES COULEURS*/
                       if (choix==2)
                       {
                         couleurs[0]--;
                         if (couleurs[0]==0) couleurs[0]=15;
                         menu=2;
                       }
                       if (choix==3)
                       {
                         couleurs[1]--;
                         if (couleurs[1]==0) couleurs[1]=15;
                         menu=2;
                       }
                       if (choix==4)
                       {
                         couleurs[2]--;
                         if (couleurs[2]==0) couleurs[2]=15;
                         menu=2;
                       }
                       if (choix==5)
                       {
                         couleurs[3]--;
                         if (couleurs[3]==0) couleurs[3]=15;
                         textcolor(couleurs[3]);
                         gotoxy((curseur.X*4)+3,(curseur.Y*2)+3);
                         printf("[");
                         gotoxy((curseur.X*4)+5,(curseur.Y*2)+3);
                         printf("]");
                         tableau(45,5,1,1,30,8);
                       }
                       /*RAPIDITE DU JEU*/
                       if (choix==6)
                       {
                         rapidite--;
                         if (rapidite==-1) rapidite=99;
                       }
                     }
                     /*SI DROITE*/
                     if (touche==DROITE)
                     {
                       /*TOUTES LSE COULEURS*/
                       if (choix==2)
                       {
                         couleurs[0]++;
                         if (couleurs[0]==16) couleurs[0]=1;
                         menu=2;
                       }
                       if (choix==3)
                       {
                         couleurs[1]++;
                         if (couleurs[1]==16) couleurs[1]=1;
                         menu=2;
                       }
                       if (choix==4)
                       {
                         couleurs[2]++;
                         if (couleurs[2]==16) couleurs[2]=1;
                         menu=2;
                       }
                       if (choix==5)
                       {
                         couleurs[3]++;
                         if (couleurs[3]==16) couleurs[3]=1;
                         textcolor(couleurs[3]);
                         gotoxy((curseur.X*4)+3,(curseur.Y*2)+3);
                         printf("[");
                         gotoxy((curseur.X*4)+5,(curseur.Y*2)+3);
                         printf("]");
                         tableau(45,5,1,1,30,8);
                       }
                       /*RAPIDITE DU JEU*/
                       if (choix==6)
                       {
                         rapidite++;
                         if (rapidite==100) rapidite=0;
                       }
                     }
                     /*SI UNE COULEUR A ETE CHANGEE REDESSINE TOUT*/
                     if (menu==2)
                     {
                       textcolor(couleurs[0]);
                       tableau(2,2,10,10,3,1);
                       sleep(50);
                       gotoxy(44,18);
                       printf("Pour jouer, utilisez les touches");
                       gotoxy(44,19);
                       printf("%c %c %c %c pour faire bouger le",24,25,26,27);
                       gotoxy(44,20);
                       printf("curseur, enter pour choisir un");
                       gotoxy(44,21);
                       printf("pion et une case, espace pour");
                       gotoxy(44,22);
                       printf("annuler le pion choisi et escape");
                       gotoxy(44,23);
                       printf("pour afficher le menu.");
                       gotoxy(44,1);
                       textcolor(couleurs[0]);
                       printf("coups n\xF8 %-2d ",coups);
                       gotoxy(44,1);
                       printf("coups n\xF8 %d  ",coups);
                       gotoxy(44,2);
                       printf("%d pions joueur 1         ",manger.A);
                       gotoxy(44,3);
                       printf("%d pions joueur 2         ",manger.B);
                       for (increment=0 ; increment<=9 ; increment++)
                       {
                         for (increment2=0 ; increment2<=9 ; increment2++)
                         {
                           gotoxy((increment2*4)+4,(increment*2)+3);
                           if (damier[increment2][increment]=='\x05') textcolor(couleurs[1]);
                           else textcolor(couleurs[2]);
                           printf("%c",damier[increment2][increment]);
                         }
                       }
                       textcolor(couleurs[tour]);
                       gotoxy(1,24);
                       printf("Aucun pion choisi");
                       menu=1;
                     }
                   }
                   break;
    }
    /*SI LE JOUEUR BOUGE UN PION*/
    if ((action==2)||(action==3))
    {
      /*EFFACE L'ANCIEN MENU*/
      textcolor(couleurs[3]);
      for (increment=0 ; increment<=5 ; increment++)
      {
        for (increment2=0 ; increment2<=33 ; increment2++)
        {
          gotoxy(45+increment2,5+increment);
          printf(" ");
        }
      }
      /*SI LA CASE CHOISIE EST DEJA OCCUPEE*/
      if ( (damier[curseur.X][curseur.Y]!=' ') && ((action==2)||(action==3)) )
      {
        dessine_menu(31,1);
        gotoxy(47,6);
        textcolor(couleurs[tour]);
        printf("Cette case est deja occup\x82\x20\be !");
        action=action+2;
      }
      /*SINON*/
      if ( (damier[curseur.X][curseur.Y]==' ') && ((action==2)||(action==3)) )
      {
        /*SI IL VEUT BOUGER UN PION*/
        if (action==2)
        {
          /*SI IL VEUT BOUGER UN PION*/
          if (((curseur.X==pions.X+1)||(curseur.X==pions.X-1))
          && ( ((curseur.Y==pions.Y+1)&&(tour==1)) || ((curseur.Y==pions.Y-1)&&(tour==2)) ))
          {
            damier[pions.X][pions.Y]=' ';
            if (tour==1) damier[curseur.X][curseur.Y]='\x05';
            else damier[curseur.X][curseur.Y]='\x06';
            dessine_menu(31,2);
            gotoxy(47,6);
            textcolor(couleurs[tour]);
            printf("Joueur %d met le pion %c%d en %c%d",tour,pions.Y+65,pions.X+1,curseur.Y+65,curseur.X+1);
            gotoxy(47,7);
            printf("Tour joueur %d",(tour==1)?(tour=2):(tour=1));
            gotoxy(1,24);
            textcolor(couleurs[tour]);
            printf("Aucun pion choisi");
            /*VERIFIE SI LE JOUEUR DOIT GAGNER UNE DAME*/
            for (increment=0 ; increment<=9 ; increment=increment+9)
            {
              for (increment2=0 ; increment2<=9 ; increment2++)
              {
                if (((damier[increment2][increment]=='\x05')&&(increment==9))
                ||((damier[increment2][increment]=='\x06')&&(increment==0)))
                {
                  for (increment3=0 ; increment3<=5 ; increment3++)
                  {
                    for (increment4=0 ; increment4<=33 ; increment4++)
                    {
                      gotoxy(45+increment4,5+increment3);
                      printf(" ");
                    }
                  }
                  if (increment==9) damier[increment2][increment]='\x01';
                  if (increment==0) damier[increment2][increment]='\x02';
                  textcolor(couleurs[3]);
                  dessine_menu(20,2);
                  gotoxy(47,6);
                  if (tour==1) textcolor(couleurs[2]);
                  else textcolor(couleurs[1]);
                  printf("Bravo ! Le joueur %d",(tour==1)?1:2);
                  gotoxy(47,7);
                  printf("gagne une dame !");
                }
              }
            }
            coups++;
            action=0;
          }
          /*SI VEUT MANGER UN PION*/
          if (((curseur.X==pions.X+2)||(curseur.X==pions.X-2))
          &&((curseur.Y==pions.Y+2)||(curseur.Y==pions.Y-2))
          &&(action==2))
          {
            /*DETERMINE LA DIRECTION DANS LAQUELLE
            LE PION DOIT AVANCER POUR MANGER LE PION*/
            if (curseur.X==pions.X+2) pions.A=1;
            else pions.A=-1;
            if (curseur.Y==pions.Y+2) pions.B=1;
            else pions.B=-1;
            /*SI VEUT MANGER UN DES SES PROPRES PIONS*/
            if (( (((damier[pions.X+pions.A][pions.Y+pions.B]=='\x05')||
            (damier[pions.X+pions.A][pions.Y+pions.B]=='\x01'))&&(tour==1))
            ||    (((damier[pions.X+pions.A][pions.Y+pions.B]=='\x06')||
            (damier[pions.X+pions.A][pions.Y+pions.B]=='\x02'))&&(tour==2)) )
            &&(action==2))
            {
              dessine_menu(21,2);
              gotoxy(47,6);
              textcolor(couleurs[tour]);
              printf("On ne mange pas ses");
              gotoxy(47,7);
              printf("propres pions !");
              action=4;
            }
            /*SI VEUT MANGER UN PION ENNEMI*/
            if (( (((damier[pions.X+pions.A][pions.Y+pions.B]=='\x05')||
            (damier[pions.X+pions.A][pions.Y+pions.B]=='\x01'))&&(tour==2))
            ||    (((damier[pions.X+pions.A][pions.Y+pions.B]=='\x06')||
            (damier[pions.X+pions.A][pions.Y+pions.B]=='\x02'))&&(tour==1)) )
            &&(action==2))
            {
              damier[pions.X+pions.A][pions.Y+pions.B]=' ';
              damier[curseur.X][curseur.Y]=damier[pions.X][pions.Y];
              damier[pions.X][pions.Y]=' ';
              dessine_menu(28,3);
              gotoxy(47,6);
              textcolor(couleurs[tour]);
              printf("Joueur %d mange le pion %c%d",tour,pions.Y+pions.B+65,pions.X+pions.A+1);
              gotoxy(47,7);
              printf("avec le pion %c%d",pions.Y+65,pions.X+1);
              gotoxy(47,8);
              printf("Tour joueur %d",(tour==1)?(tour=2):(tour=1));
              gotoxy(1,24);
              textcolor(couleurs[tour]);
              printf("Aucun pion choisi");
              /*VERIFIE SI LE JOUEUR DOIT GAGNER UNE DAME*/
              for (increment=0 ; increment<=9 ; increment=increment+9)
              {
                for (increment2=0 ; increment2<=9 ; increment2++)
                {
                  if (((damier[increment2][increment]=='\x05')&&(increment==9))
                  ||((damier[increment2][increment]=='\x06')&&(increment==0)))
                  {
                    for (increment3=0 ; increment3<=5 ; increment3++)
                    {
                      for (increment4=0 ; increment4<=33 ; increment4++)
                      {
                        gotoxy(45+increment4,5+increment3);
                        printf(" ");
                      }
                    }
                    if (increment==9) damier[increment2][increment]='\x01';
                    if (increment==0) damier[increment2][increment]='\x02';
                    textcolor(couleurs[3]);
                    dessine_menu(20,2);
                    gotoxy(47,6);
                    if (tour==1) textcolor(couleurs[2]);
                    else textcolor(couleurs[1]);
                    printf("Bravo ! Le joueur %d",(tour==1)?1:2);
                    gotoxy(47,7);
                    printf("gagne une dame !");
                  }
                }
              }
              coups++;
              action=0;
            }
          }
          /*SI AUCUN DES CHOIS PRECEDANTS N'EST BON*/
          else if (action==2)
          {
            dessine_menu(31,4);
            gotoxy(47,6);
            textcolor(couleurs[tour]);
            printf("Impossible de mettre ce pion");
            gotoxy(47,7);
            printf("sur cette case vous ne pouvez");
            gotoxy(47,8);
            printf("bouger que en diagonale et en");
            gotoxy(47,9);
            printf("avant !");
            action=4;
          }
        }
        /*SI LE PION EST UNE DAME*/
        if (action==3)
        {
          dame=0;
          increment2=0;
          /*DETERMINE LA DIRECTION DANS LAQUELLE LE
          JOUEUR VEUT FAIRE AVANCER LA DAME*/
          if (curseur.X<pions.X) pions.A=-1;
          else pions.A=1;
          if (curseur.Y<pions.Y) pions.B=-1;
          else pions.B=1;
          for (increment=1 ; dame<=0 ; increment++)
          {
            /*SI TOUTES LES CASES SONT VIDES*/
            if (((pions.X+(increment*pions.A))==curseur.X )&&((pions.Y+(increment*pions.B))==curseur.Y )) dame=1;
            /*SI SAUTE AU-DESSUS D'UN DE SES PROPRES PIONS*/
            if (( (((damier[pions.X+(increment*pions.A)][pions.Y+(increment*pions.B)]=='\x05')||
            (damier[pions.X+(increment*pions.A)][pions.Y+(increment*pions.B)]=='\x01'))&&(tour==1))
            ||    (((damier[pions.X+(increment*pions.A)][pions.Y+(increment*pions.B)]=='\x06')||
            (damier[pions.X+(increment*pions.A)][pions.Y+(increment*pions.B)]=='\x02'))&&(tour==2)) )
            &&(dame==0)) dame=2;
            /*SI SAUTE AU-DESSUS DE PIONS ENNEMIS*/
            if (( (((damier[pions.X+(increment*pions.A)][pions.Y+(increment*pions.B)]=='\x05')||
            (damier[pions.X+(increment*pions.A)][pions.Y+(increment*pions.B)]=='\x01'))&&(tour==2))
            ||    (((damier[pions.X+(increment*pions.A)][pions.Y+(increment*pions.B)]=='\x06')||
            (damier[pions.X+(increment*pions.A)][pions.Y+(increment*pions.B)]=='\x02'))&&(tour==1)) )
            &&(dame==0))
            {
              increment2++;
              manger.X=pions.X+(increment*pions.A);
              manger.Y=pions.Y+(increment*pions.B);
            }
          }
          if (increment2!=0) dame=0;
          /*POUR AVANCER NORMALEMENT*/
          if (dame==1)
          {
            damier[pions.X][pions.Y]=' ';
            if (tour==1) damier[curseur.X][curseur.Y]='\x01';
            else damier[curseur.X][curseur.Y]='\x02';
            dessine_menu(31,2);
            gotoxy(47,6);
            textcolor(couleurs[tour]);
            printf("Joueur %d met la dame %c%d en %c%d",tour,pions.Y+65,pions.X+1,curseur.Y+65,curseur.X+1);
            gotoxy(47,7);
            printf("Tour joueur %d",(tour==1)?(tour=2):(tour=1));
            gotoxy(1,24);
            textcolor(couleurs[tour]);
            printf("Aucun pion choisi");
            coups++;
            action=0;
          }
          /*SI SAUTE AU-DESSUS D'UN DE SES PROPRES PIONS*/
          if (dame==2)
          {
            dessine_menu(21,2);
            gotoxy(47,6);
            textcolor(couleurs[tour]);
            printf("On ne mange pas ses");
            gotoxy(47,7);
            printf("propres pions !");
            action=5;
          }
          /*SI SAUTE AU-DESSUS DE PLUSIEURS PIONS ENNEMIS*/
          if (increment2>1)
          {
            dessine_menu(30,2);
            gotoxy(47,6);
            textcolor(couleurs[tour]);
            printf("On ne peut pas manger");
            gotoxy(47,7);
            printf("plusieurs pions \x85 la fois !");
            action=5;
          }
          /*SI SAUTE AU-DESSUS DE UN SEUL PION ENNEMI*/
          if (increment2==1)
          {
            damier[manger.X][manger.Y]=' ';
            damier[curseur.X][curseur.Y]=damier[pions.X][pions.Y];
            damier[pions.X][pions.Y]=' ';
            dessine_menu(28,3);
            gotoxy(47,6);
            textcolor(couleurs[tour]);
            printf("Joueur %d mange le pion %c%d",tour,manger.Y+65,manger.X+1);
            gotoxy(47,7);
            printf("avec la dame %c%d",pions.Y+65,pions.X+1);
            gotoxy(47,8);
            printf("Tour joueur %d",(tour==1)?(tour=2):(tour=1));
            gotoxy(1,24);
            textcolor(couleurs[tour]);
            printf("Aucun pion choisi");
            coups++;
            action=0;
          }
        }
      }
    }
    /*SI VEUT CHOISIR UN PION A BOUGER*/
    if (action==1)
    {
      /*EFFACE L'ANCIENNE BOITE DE DIALOGUE*/
      textcolor(couleurs[3]);
      for (increment=0 ; increment<=5 ; increment++)
      {
        for (increment2=0 ; increment2<=33 ; increment2++)
        {
          gotoxy(45+increment2,5+increment);
          printf(" ");
        }
      }
      /*SI CHOISIT UNE CASE VIDE*/
      if ((damier[curseur.X][curseur.Y]==' ')&&(action==1))
      {
        dessine_menu(29,1);
        gotoxy(47,6);
        textcolor(couleurs[tour]);
        printf("Aucun pion sur cette case !");
        action=0;
      }
      /*SI CHOISIT UN PION ENNEMI*/
      if ((((damier[curseur.X][curseur.Y]=='\x01')||(damier[curseur.X][curseur.Y]=='\x05'))
      &&(tour==2))||
      (((damier[curseur.X][curseur.Y]=='\x02')||(damier[curseur.X][curseur.Y]=='\x06'))
      &&(tour==1))&&(action==1))
      {
        dessine_menu(28,1);
        gotoxy(47,6);
        textcolor(couleurs[tour]);
        printf("Ce pion n'est pas \x85 vous !");
        action=0;
      }
      /*SI CHOISIT UN DES SES PROPRES PIONS*/
      if (((damier[curseur.X][curseur.Y]=='\x05')&&(tour==1))
      ||((damier[curseur.X][curseur.Y]=='\x06')&&(tour==2))
      &&(action==1))
      {
        pions.X=curseur.X;
        pions.Y=curseur.Y;
        dessine_menu(29,3);
        gotoxy(47,6);
        textcolor(couleurs[tour]);
        printf("Vous avez choisi le pion %c%d",curseur.Y+65,curseur.X+1);
        gotoxy(47,7);
        printf("Choisissez votre case");
        gotoxy(47,8);
        printf("de destination");
        gotoxy(1,24);
        textcolor(couleurs[tour]);
        printf("Pion choisi : %c%d ",curseur.Y+65,curseur.X+1);
        action=4;
      }
      /*SI CHOISIT UNE DAME*/
      if (((damier[curseur.X][curseur.Y]=='\x01')&&(tour==1))
      ||((damier[curseur.X][curseur.Y]=='\x02')&&(tour==2))
      &&(action==1))
      {
        pions.X=curseur.X;
        pions.Y=curseur.Y;
        dessine_menu(29,3);
        gotoxy(47,6);
        textcolor(couleurs[tour]);
        printf("Vous avez choisi la dame %c%d",curseur.Y+65,curseur.X+1);
        gotoxy(47,7);
        printf("Choisissez votre case");
        gotoxy(47,8);
        printf("de destination");
        action=5;
      }
    }
  }
  /*FIN*/
  return 0;
}

/*FONCTION POUR DESSINER DES TABLEAUX*/
void tableau(int M,int N,int X,int Y,int A,int B)
{
  int  hauteur;
  int  largeur;
  int  cases_hau;
  int  cases_lar;

  gotoxy(M,N);
  printf("\xDA");
  for (largeur=1 ; largeur<=X ; largeur++)
  {
    for (cases_lar=1 ; cases_lar<=A ; cases_lar++) printf("\xC4");
    printf("\xC2");
  }
  printf("\b\xBF");
  for (hauteur=0 ; hauteur<Y ; hauteur++)
  {
    for (cases_hau=1 ; cases_hau<=B ; cases_hau++)
    {
      if (cases_hau==B)
      {
        gotoxy(M,N+cases_hau+(hauteur*(B+1))+1);
        printf("\xC3");
        for (largeur=1 ; largeur<=X ; largeur++)
        {
          for (cases_lar=1 ; cases_lar<=A ; cases_lar++) printf("\xC4");
          printf("\xC5");
        }
        printf("\b\xB4");
      }
      gotoxy(M,N+cases_hau+(hauteur*(B+1)));
      printf("\xB3");
      for (largeur=1 ; largeur<=X ; largeur++)
      {
        for (cases_lar=1 ; cases_lar<=A ; cases_lar++) printf(" ");
        printf("\xB3");
      }
    }
  }
  gotoxy(M,N+(Y*(B+1)));
  printf("\xC0");
  for (largeur=1 ; largeur<=X ; largeur++)
  {
    for (cases_lar=1 ; cases_lar<=A ; cases_lar++) printf("\xC4");
    printf("\xC1");
  }
  printf("\b\xD9");
}

/*FONCTION POUR INITIALISER UN TABLEAU*/
void initialise(char tableau[10][10])
{
  int  increment;
  int  divers;
  /*INITIALISATION DES CASES VIDES*/
  for (increment=0 ; increment<=9 ; increment++)
  {
    for (divers=0 ; divers<=9 ; divers++) tableau[divers][increment]=' ';
  }
  /*INITIALISATION PIONS ROUGES*/
  divers=0;
  for (increment=1 ; increment<=9 ; increment=increment+2)
  {
    tableau[increment][divers]='\x05';
    if ((increment==9)&&(divers==0))
    {
      increment=-2;
      divers=1;
    }
    if ((increment==8)&&(divers==1))
    {
      increment=-1;
      divers=2;
    }
  }
  /*INITIALISATION PIONS JAUNES*/
  divers=9;
  for (increment=0 ; increment<=9 ; increment=increment+2)
  {
    tableau[increment][divers]='\x06';
    if ((increment==8)&&(divers==9))
    {
      increment=-1;
      divers=8;
    }
    if ((increment==9)&&(divers==8))
    {
      increment=-2;
      divers=7;
    }
  }
}

/*FONCTION POUR DESSINER UN MENU*/
void dessine_menu(int X,int Y)
{
  int  increment;
  int  increment2=0;
  for (increment=0 ; increment2<=X ; increment++)
  {
    tableau(45,5,1,1,increment2,increment);
    if (rapidite!=0) sleep(rapidite);
    if (increment==Y)
    {
      increment=Y-1;
      increment2++;
    }
  }
}
