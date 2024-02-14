#include <iostream>
#include <array>
#include <string>
#include <conio.h>

const int taille_max = 4;

void init_jeu(int &nb_tentatives, int &nb_couleurs, int &nb_manches)
{
    nb_couleurs = 4;
    char rep;
    std::cout<<" Voulez-vous une explication du deroulement du jeu ? (o/n)"; std::cin>>rep;std::cout<<std::endl;
    if(rep=='o')
    {
        std::cout<<"Le jeu se deroule entre deux joueurs : "<<std::endl;
        std::cout<<"Le premier decide du code couleur secret "<<std::endl;
        std::cout<<"Et le deuxieme possede un nombre de tentatives choisis pour deviner l'ordre des couleurs "<<std::endl;
        std::cout<<"Apres la saisie de la reponse, le premier joueur donne un indice qui indique le nombre de couleurs correctes ainsi que leurs ordres "<<std::endl;
        std::cout<<"Vous pouvez choisir le nombre de manches a jouer, ainsi que la difficulte "<<std::endl;
        std::cout<<"Les couleurs disponibles sont : "<<std::endl;
        std::cout<<"Rouge(R) , Bleu(B), Jaune(J), Violet(V), Marron(M), Orange(O) "<<std::endl;
        std::cout<<"Si la manche se termine avant que le code ne soit devine, le premier joueur gagne, dans le cas contraire, le deuxieme joueur emporte la manche "<<std::endl<<std::endl;
    }
    char difficulte;
    std::cout<<"Quelle difficulte ? (facile(f),moyen(m),difficile(d)) "; std::cin>>difficulte;
    while(difficulte!='f' and difficulte!='m' and difficulte!='d')
    {
        std::cout<<"Saisie incorrecte ! Quelle difficulte ? (facile(f),moyen(m),difficile(d)) " ; std::cin>>difficulte;
    }
    if(difficulte=='f')
        nb_tentatives=10;
    else if(difficulte=='m')
        nb_tentatives=8;
    else if(difficulte=='d')
        nb_tentatives=6;
    std::cout<<"Vous avez donc "<<nb_tentatives<<" tentatives pour trouver la reponse !  "<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Nombre de manches ? "; std::cin>>nb_manches; std::cout<<std::endl;
    std::cout<<"Que le jeu commence ! " ; std::cout<<std::endl<<std::endl;
}

void saisie_joueurs(std::string &j1, std::string &j2)
{
    std::cout<<"Quel est le nom du premier joueur ? "; std::cin>>j1;
    std::cout<<"Quel est le nom du deuxieme joueur ? "; std::cin>>j2;
}

void saisie_code(std::string &code, std::string j1)
{
    code="";
    std::cout<<j1<<" est en train de saisir le code secret : ";
    while(code.length() != taille_max)
    {
        code += getch();
    }
    std::cout<<std::endl;
}

bool verif(std::string code, std::string reponse)
{
    if(reponse.length()!=code.length())
        return false;
    else if(reponse != code)
        return false;
    else return true;
}

void jeu(std::string &code, std::string j2, std::string j1, int nb_tentatives, std::string &gagnant)
{
    int tour=0;
    std::string reponse;
    saisie_code(code,j1);
    while(tour<=nb_tentatives)
    {
        tour++;
        std::cout<<j2<<" a vous de jouer : "; std::cin>>reponse;
        if(verif(code,reponse))
        {
            std::cout<<j2<<" a gagne en "<<tour<<" tours !"<<std::endl;
            gagnant = j2;
            return;
        }
        else
        {
            std::string indice;
            std::cout<<"reponse incorrecte, "<<j1<<" va saisir l'indice :";
            std::cin>>indice;
        }
    }
    std::cout<<j2<<" a perdu ! "<<j1<<" est donc le gagnant de cette manche ";
    gagnant=j1;
}