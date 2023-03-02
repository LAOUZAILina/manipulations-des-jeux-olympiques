#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#define max 100
#include <conio.h>
#include <windows.h>

struct t_maillon
{
  char nomath[25];//le champ valeur du maillon est de type char est nomm� nomath
  struct t_maillon* adr;
}t_maillon;

typedef struct t_maillon* ptr;


/****************la machine abstraite************************************/
// Procédure qui alloue un maillon et retourne son adresse dans p
void allouer (ptr*p) //allouer un espace et retourner son adresse
{
  *p=(struct t_maillon*) malloc (sizeof(struct t_maillon));
  (*p)->adr=NULL;
 }


// Procédure qui détruit le maillon pointé par p
 void liberer(ptr p)//lib�rer l'espace deja allou�
 {free(p);}


//Fonction qui retourne le contenu du champ (adr) du maillon pointé par p
 ptr suivant (ptr p)
{return (p->adr);}


// Fonction qui retourne le contenu du champ (val) du maillon pointé par p
char* valeur(ptr p)
{return (p->nomath);}


//Procédure qui affecte v dans le champ (val)du maillon pointé par p
void aff_val(ptr p,char val[])
{strcpy(p->nomath,val);}


// Procédure qui affecte q dans le champ (adr) du maillon pointé par p
void aff_adr(ptr p,ptr q)
{p->adr = q;}


//declaration des tableaux
ptr tab_jo[32][234];
char tableau_pays[234][50];
char tableau_sports[32][25];


/************procédure creer tab_sports****************/
void  creer_tab_sports()
//une procedure qui crée un tableau des epreuves
{
 int i=0;
 char c [25];
 FILE *fic=NULL;
 fic = fopen("Sports.txt", "r");
 if (fic==NULL)
  {
     printf("ce fichier n'existe pas");
  }
 else
  {
    while((fgets(c,25,fic)!= NULL) &&(i<33))  /*on lit le fichier tant qu'on ne recoit pas null*/
      {
        strcpy(tableau_sports[i],c);   /*on affecte chaque ligne dans une case du tableau*/
        i++;
      }
  }
 fclose(fic);
}

/***********procedure creer tab_pays**************************/
void  creer_tab_pays()
//une procedure qui crée un tableau depuis un fichier
{
 int i=0;
 char c [50];
 FILE *fic=NULL;
 fic = fopen("pays1.txt", "r");
 if (fic==NULL)
   {
     printf("ce fichier n'existe pas");
   }
 else
   {
     while(fgets(c,50,fic)!= NULL && i<234) /*on lit le fichier tant qu'on ne recoit pas null*/
       {
         strcpy(tableau_pays[i],c);
         i++;
       }
   }
 fclose(fic);
}



/*********************procedure GenLLc********************/
ptr GenLLC (int n)
{
  ptr p,q,tete;
  int nb, i,j;
  int loulou;
  char nomath[25];
  char nom[25];
  int lettre;
  char m[26]="abcdefghijklmnopqrstuvwxyz";
  tete=NULL;
  for(i=1; i<=n; i++)
    {
       allouer (&p);
       nb=5+rand()%5;
       for (j=0 ; j <nb ; j++)
        {
          lettre=rand()%26;
          nomath[j]=m[lettre];
        }
        aff_val(p,nomath);
        aff_adr(p,NULL);
        if (tete==NULL)
         {
            tete=p;
         }
        else
        {
            aff_adr(q,p);
        }
        q=p;
    }
  return tete;
}

/*********************procedure1:creer_tabjo*****************/
void creer_tabjo()
{
 int nb_ath;
 ptr t_de_llc;
 int l;
 int cl;
 creer_tab_pays();
 creer_tab_sports();
 for(l=0; l<33;l++)
    {
      for (cl=0; cl<234;cl++)
        {
           int nb_ath=rand()%11;
           tab_jo[l][cl]=GenLLC(nb_ath);
        }
    }
}


/*************************fonction4:sansath*******************/
bool sansath(int ne)
{
 int i;
 int sans=false;
 i=0;
 while ((tab_jo[ne-1][i]==NULL)&&(i<234))
  {i=i+1;}
 if (i>=234)
 {
      sans =true;
 }

 return sans;
}


/*********************procedure5:listjo**********************/
void listjo()
{
   int n,z,cpt=1,compteur=1;
   ptr q;
   for (z=0;z<33;z++)
    {
      if (sansath(z)==0)
        {
            textcolor(13);
            printf("%s\n",tableau_sports[z]);
            printf("*****************************************************\n");
            for (n=0;n<234;n++)
            {
                textcolor(13);
                printf(" \n");
                printf(" le pays num %d est %s\n",compteur,tableau_pays[n]);
                textcolor(13);
                printf("_____________________________________________________\n");
                q=tab_jo[z][n];
                compteur++;
                while (q!=NULL)
                {
                    textcolor(15);
                    printf(" -----> l'athlete num %d est : %s\n",cpt,valeur(q));
                    q=suivant(q);
                    cpt++;
                }
                cpt=1;
                getch();
                printf("_____________________________________________________\n");

            }
            compteur=1;
        }
    }
}


/************************procedure:LongLLc*****************/
int LongLLC (ptr L)
{
    ptr p = L;
    int cpt = 0;

    while (p!= NULL)
    {
        cpt++;
        p=suivant(p);
    }
    return cpt;
}


/***********************procedure2:inserath******************************/
void inserath (char nomathlete[25] , int nump,int nume)
{
  ptr pi,q,w;
  if ((nume<33) && (nump<234)&& (LongLLC (tab_jo[nume][nump])<10))
  {
      pi=tab_jo[nume-1][nump-1];
      int booleen=0;
      while (pi!=NULL && booleen==0)
        if(strcmp(valeur(pi),nomathlete)==0)
         {
           printf("cet athlete existe deja dans la liste !!");
           booleen=1;
         }
      else
      {
          pi=suivant(pi);
      }
      if(booleen==0)  // le nom de l'athlete ne figure pas dans la liste
      {
        allouer(&w);
        aff_val(w,nomathlete);
        aff_adr(w,tab_jo[nume-1][nump-1]);   //chainer le nouveau maiilon avec la tete
        tab_jo[nume-1][nump-1]=w;//le nouveau maillon devient la nouvelle tt
      }
  }
  else
  {
   printf("on s'excuse la liste est au complet !!");
  }
  listjo();
}


/************************procedure8:supp_ligne***********************/
void supp_ligne(int f)
{
    int g,h;
    if (sansath(f-1)==1)
      {
        for (g=f-1;g<32;g++)
         {
            strcpy(tableau_sports[g],tableau_sports[g+1]);
            for (h=0;h<233;h++)
              {
                tab_jo[g][h]=tab_jo[g+1][h];
              }
         }
         listjo();
      }
      else
      {
          printf("suppression impossible car cet epreuve n'est pas vide");
      }

}



/********************procedure:access_val2**************************/
void access_val2(ptr tete,char nomath[25],ptr *prec,ptr *p)
{
    bool trouv;
    *p=tete;
    trouv=false;
    *prec = NULL;
    while ((*p!=NULL)&&(!trouv))
    {
        if (strcmp(nomath,valeur(*p))==0)
        {
            trouv=true;
        }
        else
        {
            *prec=*p;
            *p=suivant(*p);

        }
    }
}


/*****************************procedure7:supp_ath******************/
void supp_ath(int ns,int np)
{

    ptr p,prec;
    char ath[25];
    scanf("%s",ath);
    access_val2(tab_jo[ns-1][np-1],ath,&prec,&p);
    if (p!=NULL)
    {
      if (prec==NULL)
      {
          tab_jo[ns-1][np-1]=suivant(tab_jo[ns-1][np-1]);
      }
      else
      {
          aff_adr(prec,suivant(p));
      }
      liberer(p);
    }
    else
    {
        printf("ath non existant");
    }
    listjo();
}


/*********************procedure3:lisathpays*******************************/
void listathpays (char pays[50])
{
 int d=0;
 ptr q;
 int z=0;
 int num_de_pays=0;
 while((strcmp(tableau_pays[d],pays)!=0)&&(d<234))
 {
    d++;
 }
 printf("%d\n",d+1);
 if (strcmp(tableau_pays[d],pays)==0)
 {
  num_de_pays=d;
  for (z=0;z<33;z++)
   {
    q=tab_jo[z][num_de_pays];
    int cpt=1;
    if (q!=NULL)
     {
       textcolor(13);
       printf("%s\n",tableau_sports[z]);
     }
    while (q!=NULL)
     {
        textcolor(15);
        printf("  l'athlete num %d est :%s \n",cpt,valeur(q));
        cpt++;
        q=suivant(q);
     }
     getch();
   }
 }
 else
 {
   printf("ce pays n'existe pas !!!!!!!!!");
 }
}


/************************procedure6:suppays*************/
void suppays(char pays[50])

{
  int d=0,i,e,s=0,num_de_pays;
  ptr p,q;
  bool finddd=false;
  while((finddd==false )&&(d<234))
    {
      if (strcmp(tableau_pays[d],pays)==0)
        {
           finddd=true;
           num_de_pays=d;
           printf("%d",num_de_pays);
        }
      else
        {
       d++;
        }
    }
  if (finddd=true)
    {
       // supprimons
       //first of all: liberons l'espace
       for (i=0;i<33;i++)
        {
          p=tab_jo[i][d];
          while (p!=NULL)
           {
             q=suivant(p);
             liberer(p);
             p=q;
           }
        }
        // now faisons le decalage
       if (d!=233)
       {
       for (e=num_de_pays ; e<233;e++)
        {
          strcpy(tableau_pays[e],tableau_pays[e+1]);
          while (s<32)
           {
             tab_jo[s][e]=tab_jo[s][e+1];
             s++;
           }
        }
       }
       tab_jo[32][233]=0;
    }
  else
   {
     printf("ce pays n'existe pas !!");
   }

}



/************   Procedure ClrScr  ****************/

void ClrScr()
{
    system("cls||clear");
}

/************   Procedure Entete  ****************/

void Entete ()
{
    printf("***********************************************************************************************************\n");
    printf("***************************************TP1_ALSDD_lina_zineb************************************************\n");
    printf("***********************************************************************************************************\n\n");
}



void Menu ()
{
    ;
    ClrScr();

    srand(time(NULL));
    ClrScr();
    Entete();
    textcolor(13);
    printf("____________________________________________________________________________________________________________\n");
    textcolor(15);
    printf("|                             TP1_ALSDD   :   inscriptions au jeux olympiques                              |\n");
    printf("|     <laouzai lina >      <ghodbane zineb>        <1CPI_G08>        <ESI-Alger>     <2021/2022>           |\n");
    textcolor(13);
    printf("|__________________________________________________________________________________________________________|\n\n");
    printf("============================================================================================================\n");
    printf("____________________________________________________________________________________________________________\n");
    textcolor(15);
    printf("|          Veuillez choisir quelle action realiser :                                                       |\n");
    textcolor(13);
    printf("|  En general:                                                                                             |\n");
    textcolor(15);
    printf("|                                                                                                          |\n");
    printf("|               1)  creer le tableau des inscriptions tab-jo                                               |\n");
    printf("|               2)  lister tous le contenu de tab_jo (les participants de chaque epreuve de chaque pays  ) |\n");
    textcolor(13);
    printf("|  pour les pays:                                                                                          |\n");
    textcolor(15);
    printf("|                                                                                                          |\n");
    printf("|               3)  lister les participants des epreuves d'un pays de votre choix                          |\n");
    printf("|               4)  Supprimer un pays apres son annonce pour des raisons budgetaires ou polytiques         |\n");
    textcolor(13);
    printf("| pour les athletes:                                                                                       |\n");
    textcolor(15);
    printf("|                                                                                                          |\n");
    printf("|               5)  inserer un nouveau participant                                                         |\n");
    printf("|               6)  supprimer un athlete                                                                   |\n");
    textcolor(13);
    printf("| pour les epreuves:                                                                                       |\n");
    textcolor(15);
    printf("|                                                                                                          |\n");
    printf("|               7)  tester si une preuve est vide sans aucun participant                                   |\n");
    printf("|               8)  supprimer tout une epreuve si elle est vide                                            |\n");
    printf("|               9)  Quitter                                                                                |\n");
    textcolor(13);
    printf("|                                                                                                          |\n");
    textcolor(15);
    printf("|          Votre choix ----->                                                                              |\n");
    textcolor(13);
    printf("|__________________________________________________________________________________________________________|\n");
    textcolor(15);
}


void DEBUT(int *l)// graphique d'entrer
{
    int i,x,y,c;


    gotoxy(1,2);
    x=wherex();
    y=wherey();
    gotoxy(x,y);
    printf(" ______  _____  __ ");
    gotoxy(x,y+1);
    printf("|  ____|/ ____||__|");
    gotoxy(x,y+2);
    printf("| |__  | (___   __ ");
    gotoxy(x,y+3);
    printf("|  __|  \\___ \\ |  |");
    gotoxy(x,y+4);
    printf("| |____ ____) ||  |");
    gotoxy(x,y+5);
    printf("|______|_____/ |__|");
    textcolor(9);
    gotoxy(x+15,y);
    printf(" __");
    gotoxy(x+15,y+1);
    printf("|__|");
    textcolor(15);
    gotoxy(x+21,y+1);
    printf("%ccole nationale",144);
    gotoxy(x+21,y+3);
    printf("Sup%crieure",130);
    gotoxy(x+21,y+5);
    printf("d'Informatique");

    gotoxy(25,11);
    printf("Premier TP d'Algorithmique et structures de donn%ces dynamiques\n",130);
    printf("                une matrice de liste LLC\n");

    textcolor(13);
    gotoxy(4,12);
    x=wherex();
    y=wherey();
    gotoxy(x,y);
printf("__       _______      _______.            __  _______  __    __ ___   ___         \n ");
    printf(" |  |     |   ____|    /       |           |  ||   ____||  |  |  |\\  \\ /  / \n");
    printf("  |  |     |  |__      |   (----`           |  ||  |__   |  |  |  | \\  V  /  \n");
    printf("  |  |     |   __|      \\   \\         .--.  |  ||   __|  |  |  |  |  >   <   \n");
    printf("  |  `----.|  |____ .----)   |        |  `--'  ||  |____ |  `--'  | /  .  \\  \n");
    printf("  |_______||_______||_______/          \\______/ |_______| \\______/ /__/ \\__\\ \n");


    printf("");
    gotoxy(x,y+7);
    printf("");
    printf("______   __      ____    ____.___  ___..______   __   ______      __    __  _______      _______.\n");
printf("  /  __  \\ |  |     \\   \\  /   /|   \\/   ||   _  \\ |  | /  __  \\    |  |  |  ||   ____|    /       |\n");
printf(" |  |  |  ||  |      \\   \\/   / |  \\  /  ||  |_)  ||  ||  |  |  |   |  |  |  ||  |__      |   (----`\n");
printf(" |  |  |  ||  |       \\_    _/  |  |\\/|  ||   ___/ |  ||  |  |  |   |  |  |  ||   __|      \\   \\    \n");
printf(" |  `--'  ||  `----.    |  |    |  |  |  ||  |     |  ||  `--'  '--.|  `--'  ||  |____ .----)   |   \n");
printf("  \\______/ |_______|    |__|    |__|  |__|| _|     |__| \\_____\\_____\\ \\______/ |_______||_______/    \n");

    textcolor(15);

    gotoxy(8,29);
    printf("Si vous voulez lire l'aide appuyez sur %cH%c, sinon appuyez sur %cEntrer%c pour lancer le programme.",34,34,34,34);

    gotoxy(1,30);
    for (i=1 ; i <= 110 ; i++) printf("_");
    gotoxy(49,32);
    printf("REALISE PAR:");
    gotoxy(37,34);
    textcolor(13);
    printf("  LAOUZAI LINA   |  Ghodbane zineb");
    textcolor(15);
    gotoxy(54,34);
    //printf("|");
    gotoxy(43,36);
    printf("SECTION C  |  GROUPE 08");
    gotoxy(41,38);
    printf("ENCADRE PAR: Mr:kermi Adel");
    gotoxy(78,39);
    printf("ANNEE UNIVERSITAIRE : 2021/2022\n");
    for (i=1 ; i <= 110 ; i++) printf("_");
    getch();


}






/**************   Proc�dure ViderBuffer  ****************/

void ViderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}



/******************************************************/
/**************   Programme principal  ****************/
/******************************************************/


int main()
{
	 int choix,country,nume,nump,ne,se,ns,ligne;
	 bool stop;
	 char pays[50],athlete[25],ath[25];
	 char REPONSE;
	 int* l;


	 srand(time(NULL));
	 DEBUT(l);

    do
    {





        ClrScr();
        Menu ();
        scanf ("%d", &choix);
        switch (choix)
        {
            case 1: ClrScr();
                    Entete();
                    printf ("1.creer_tabjo \n");
                    printf ("   ------------------ \n\n");
                    creer_tabjo();
                    printf ("\n> Appuyer sur ENTREE pour continuer ... ");
                    ViderBuffer();
                    getchar();
                    break;


            case 2: ClrScr();
                    Entete();
                    printf ("5.listjo \n");
                    creer_tab_pays();
                    creer_tab_sports();
                    creer_tabjo();
                    listjo();
                    printf ("   ------------------ \n\n");
                    printf ("\n> Appuyer sur ENTREE pour continuer ... ");
                    ViderBuffer();
                    getch();

                    break;

            case 3: ClrScr();
                    Entete();
                    creer_tab_pays();
                    creer_tab_sports();
                    creer_tabjo();
                    printf ("3.listathpays \n");
                    printf ("   ------------------------------- \n\n");
                    printf ("\n> veiller Introduire le pays pour lister les atheletes de ses epreuves : ");
                    getchar();
                    fgets(pays,50,stdin);
                    listathpays(pays);
                    printf ("\n> Appuyer sur ENTREE pour continuer ... ");
                    ViderBuffer();
                    getchar();
                    break;

            case 4: ClrScr();
                    Entete();
                    printf ("4.suppays  \n");
                    printf ("   ---------------------- \n\n");
                    printf ("\n> veiller Introduire le pays que vous vouler supprimer ");
                    getchar();
                    fgets(pays,50,stdin);
                    creer_tab_pays();
                    creer_tab_sports();
                    creer_tabjo();
                    suppays(pays);
                    textcolor(13);
                    //printf ("\n> pour le tableau de pays :                                                             \n");

                       for (country=0; country<234; country+=4)
                       {

                        printf("%S\n",tableau_pays[country]);
                       }
                     textcolor(13);
                    printf ("\n> pour le tableau des jeux olympiques tabjo:                                                             \n");

                       listjo();

                    printf ("\n> Appuyer sur ENTREE pour continuer ... ");
                    ViderBuffer();
                    getchar();
                    break;

            case 5: ClrScr();
                    Entete();
                    creer_tab_pays();
                    creer_tab_sports();
                    creer_tabjo();
                    printf ("5. inserath  \n");
                    printf ("   ------------------ \n\n");
                    printf ("\veiller Introduire l'athlete a inserer :\n");
                    getchar();
                    fgets(athlete,25,stdin);
                    printf ("\veiller Introduire le numero d'epreuve que ce participant va faire parti :\n");
                    getchar();
                    scanf ("%d\n",&nume);
                    printf ("\et meme le numero de pays du participant:\n");
                    getchar();
                    scanf ("%d\n",&nump);
                    inserath(athlete,nume,nump);
                    //printf ("\n> action faite avec sucses !!  \n");
                    //printf ("voila cet athlete figure dans la nouvelle liste des participants de l'epreuve choisi du pays choisi\n");
                    listathpays(tableau_pays[nump]);
                    listjo();
                    printf ("\n> Appuyer sur ENTREE pour continuer ... ");
                    ViderBuffer();
                    getchar();
                    break;

            case 6: ClrScr();
                    Entete();
                    creer_tab_pays();
                    creer_tab_sports();
                    creer_tabjo();

                    printf ("\n> veiller Introduire le pays que l'athlete a supprimer fait parti : ");
                    getchar();
                    fgets(pays,50,stdin);
                    listathpays(pays);
                    printf("veiller introduire le numero de l'epreuve de l'athlete \n");
                    scanf("%d",&ne);
                    printf("veiller introduire le numero du pays de l'athlete \n");
                    scanf("%d",&ns);
                    printf ("\n> quel athlete souhaitez vous supprimer ??\n veiller l'entrer  : ");
                    supp_ath(ne,ns);
                    listathpays(pays);
                    printf ("\n> Appuyer sur ENTREE pour continuer ... ");
                    ViderBuffer();
                    getchar();
                    break;

            case 7: ClrScr();
                    Entete();
                    creer_tab_pays();
                    creer_tab_sports();
                    creer_tabjo();
                    printf ("7. sansath \n");
                    printf ("   ---------------- \n\n");
                    printf("veiller introduire le numero de l'epreuve a tester ");
                    scanf("%d",&se);

                    bool rep=sansath(se);
                    if (rep==false)
                    {
                        printf("cet epreuve n'est pas vide");
                    }
                    else
                    {
                        printf("cet epreuve est vide");
                    }
                    printf ("\n> Appuyer sur ENTREE pour continuer ... ");
                    ViderBuffer();
                    getchar();
                    break;

            case 8: ClrScr();
                    Entete();
                    creer_tab_pays();
                    creer_tab_sports();
                    creer_tabjo();
                    printf ("8. supligne                                                           \n");
                    printf ("   ------------------------------------------------------------------ \n\n");
                    printf("veiller introduire le numero de l'epreuve (ligne) a supprimer          \n");
                    scanf("%d",&ligne);

                    supp_ligne(ligne);
                    printf ("\n> Appuyer sur ENTREE pour continuer ...                             \n");
                    ViderBuffer();
                    getchar();
                    break;


            case 9: stop = true;
                    break;
            default:
            printf("erreur");

            break;
        }

    }while (!stop);

    return 0;
}




