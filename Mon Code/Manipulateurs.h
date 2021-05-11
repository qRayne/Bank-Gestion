#pragma once

#include <string>

#include "../../../C21-CVM/console(v1.9).h"

using namespace std;

// FONCTIONS GÉNÉRALES

void mani_clean();
double mani_round(double v, int p = 2);
string mani_date(time_t t);
string mani_temps(time_t t);

// FONCTIONS GÉNÉRALES POUR LA LECTURE D'UNE STRING, SON NETTOYAGE ET SON TRANSFERT DANS UN TABLEAU DE CHAR

string& mani_textCleaner(string& texte); // enlève les blancs et tabulations
void mani_copyStringTo(const string& s, const unsigned int size, char to[]);
void mani_lireString(const int size, char to[]);

// FONCTIONS POUR LES MESSAGES
void mani_message(string message, cvmColor c, int x, int y);
void mani_avertissement(string warning, int x, int y, cvmColor c = cvmColor::JAUNE); 
void mani_appuyerSurUneTouchePourContinuer(int x,int y);

// FONCTIONS POUR LIRE UNE RÉPONSE OUI OU NON À UNE QUESTION
bool mani_lireQuestionOuiNon(string question, cvmColor c, int x, int y);

// FONCTIONS POUR EFFACE LES MESSAGES
void mani_deleteMessage(int x, int y);



