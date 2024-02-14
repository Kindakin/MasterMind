#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>

const int TAILLE_CODE = 4;
const int NB_COULEURS = 6;
std::vector<int> code;
std::vector<int> tentative;
std::string indice3;
std::vector<std::vector<int>> solutionsProbables;
std::vector<std::vector<int>> combinaisons;
std::vector<std::vector<int>> tentativeSuivantes;


int chartoint(char lettre)
{
    int chiffre;
        if(lettre=='R')
            chiffre = 1;
        else if(lettre=='B')
            chiffre = 2;
        else if(lettre=='J')
            chiffre = 3;
        else if(lettre=='V')
            chiffre = 4;
        else if(lettre=='M')
            chiffre = 5;
        else if(lettre=='O')
            chiffre = 6;

    return chiffre;
}

std::vector<int> saisie_code()  
{
    std::string codeLettre;
    std::cin>>codeLettre;
    for(int i = 0 ; i<TAILLE_CODE ; ++i)
    {
        int chiffre = chartoint(codeLettre[i]);
        code.push_back(chiffre);
    }
    return code;
}

void debut_jeu()
{
    std::cout<<std::endl;
    std::cout<<"Bienvenue dans la 3eme Version du jeu MasterMind ! "<<std::endl;
    std::cout<<"Ici, vous allez saisir un code couleur secret de 4 caracteres parmis 6 couleurs , et l'ordinateur devra le deviner "<<std::endl<<std::endl;
    std::cout<<"Les couleurs disponibles sont : "<<std::endl;
    std::cout<<"Rouge(R) , Bleu(B), Jaune(J), Violet(V), Marron(M), Orange(O) "<<std::endl<<std::endl;
    std::cout<<"L'ordinateur vous challenge a lui donner un code qu'il ne pouvra pas deviner en moins de 6 tentatives ! "<<std::endl;
    std::cout<<"Seriez-vous capable de relever le defi ? Alors bonne chance ;) "<<std::endl<<std::endl;
    std::cout<<"Saisissez le code : "<<std::endl<<std::endl;
    code = saisie_code();
}

void intTostring(std::vector<int> code) 
{
    std::string codeLettre;
    for(int elem : code)
    {
        if(elem==1)
            codeLettre += "R";
        else if(elem==2)
            codeLettre += "B";
        else if(elem==3)
            codeLettre += "J";
        else if(elem==4)
            codeLettre += "V";
        else if(elem==5)
            codeLettre += "M";
        else if(elem==6)
            codeLettre += "O";
    }
    std::cout<<codeLettre;
}

void genere_combinaisons(std::vector<std::vector<int>>& combinaisons)
{
    int totalCombi = pow(NB_COULEURS, TAILLE_CODE);  // Calcul du nombre total de combinaisons
    
    for (int i = 0; i < totalCombi; i++) 
    {
        std::vector<int> combi;
        int num = i;
        
        // Parcours des chiffres de la combinaison
        for (int j = 0; j < TAILLE_CODE; j++) 
        {
            int digit = num % NB_COULEURS  + 1;
            combi.push_back(digit);
            num /= NB_COULEURS;
        }
        combinaisons.push_back(combi);
    }
}

std::string indication(std::vector<int> tentative, std::vector<int> code)
{
    int bon_ordre = 0 , mauvais_ordre = 0;
    // Tableaux de booléens pour éviter de compter plusieurs fois la même couleur
    bool trouve_code[4] = {false};
    bool trouve_tentative[4] = {false};
    
    // Comptage des couleurs dans le bon ordre
    for (int i = 0; i < 4; ++i) {
        if (tentative[i] == code[i]) 
        {
            bon_ordre++;
            trouve_code[i] = true;
            trouve_tentative[i] = true;
        }
    }
    
    // Comptage des couleurs correctes mais mal placées
    for (int i = 0; i < 4; ++i) {
        if (!trouve_tentative[i]) {
            for (int j = 0; j < 4; ++j) {
                if (!trouve_code[j] and tentative[i] == code[j]) 
                {
                    mauvais_ordre++;
                    trouve_code[j] = true;
                    break;
                }
            }
        }
    }
    std::string indice="";
    for(int i=0 ; i<bon_ordre ; ++i)
    {
        indice+="B";
    }
    for(int i=0 ; i<mauvais_ordre ; ++i)
    {
        indice+="W";
    }
    return indice;
}

void supprime_code(std::vector<std::vector<int>> &combinaisons, std::vector<int> tentative)
{
    int index;
    for (auto it = combinaisons.begin(); it != combinaisons.end(); it++) 
    {
        index = std::distance(combinaisons.begin(), it);

        if (combinaisons[index] == tentative) {
            combinaisons.erase(combinaisons.begin() + index);
            break;
        }
    }
}

void triCodes(std::vector<std::vector<int>> &combinaisons, std::vector<int> tentative, std::string indice) 
{

    int index;
    std::vector<std::vector<int>>::iterator it = combinaisons.begin();

    while (it != combinaisons.end()) 
     {
        index = distance(combinaisons.begin(), it);

        if (indice != indication(tentative, combinaisons[index])) 
        {
            it = combinaisons.erase(combinaisons.begin() + index);
        } 
        else 
        {
            it++;
        }
    }
}

int scoreMAX(std::map<std::string, int> dictio) 
{

    int max = 0;
    for (auto elem : dictio) 
    {
        if (elem.second > max) 
        {
            max = elem.second;
        }
    }

    return max;
}

int scoreMIN(std::map<std::vector<int>, int> dictio)

 {
    int min = std::numeric_limits<int>::max();
    for (auto elem : dictio) 
    {
        if (elem.second < min) 
        {
            min = elem.second;
        }
    }

    return min;
}

std::vector<std::vector<int>> minmax() 
{
    std::map<std::string, int> scoreCount;
    std::map<std::vector<int>, int> score;
    std::vector<std::vector<int>> essaiSuivants;
    int max, min;

    for (unsigned int i = 0; i < combinaisons.size(); ++i) 
    {

        for (unsigned int j = 0; j < solutionsProbables.size(); ++j) // ici on cherche l'indice avec la plus grande occurrence
        {                  // et donc c'est comme si on cherchait l'indice avec le plus de chance d'etre trouvé pour cette tentative

            std::string pegScore = indication(combinaisons[i], solutionsProbables[j]);
            if (scoreCount.count(pegScore) > 0) {
                scoreCount.at(pegScore)++;
            } else {
                scoreCount.emplace(pegScore, 1);
            }
        }

        max = scoreMAX(scoreCount);
        score.emplace(combinaisons[i], max); // ici on garde le score de la combinaison en question, c'est à dire on garde le max 
        scoreCount.clear();
    }

    min = scoreMIN(score);

    for (auto elem : score) {
        if (elem.second == min) {
            essaiSuivants.push_back(elem.first); // ici on va garder toute les combinaisons dont le score min est MIN
        }
    }

    return essaiSuivants;
}

std::vector<int> tentativeSuivante(std::vector<std::vector<int>> tentativeSuivantes) 
{
    std::vector<int> suivant;
    for (unsigned int i = 0; i < tentativeSuivantes.size(); ++i) 
    {
        bool found = false;
        for (unsigned int j = 0; j < solutionsProbables.size(); ++j) 
        {
            if (solutionsProbables[j] == tentativeSuivantes[i]) 
            {
                suivant = tentativeSuivantes[i];
                found = true;
                break;
            }
        }
        if (found==true) 
        {
            break;
        }
    }

    if (suivant.empty()) 
    {
        for (unsigned int i = 0; i < tentativeSuivantes.size(); ++i)
        {
            bool found = false;
            for (unsigned int j = 0; j < combinaisons.size(); ++j) 
            {
                if (combinaisons[j] == tentativeSuivantes[i]) 
                {
                    suivant = tentativeSuivantes[i];
                    found = true;
                    break;
                }
            }
            if (found==true) 
            {
                break;
            }
        }
    }
    return suivant;
}

