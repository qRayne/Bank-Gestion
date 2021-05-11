#include <iostream>
#include <conio.h>
#include <ctime>
#include <string>
#include <sstream>

#include "../../C21-CVM/console(v1.9).h"
#include "Manipulateurs.h"

using namespace std;

#pragma warning (disable:6031)	//_getch()

// FONCTIONS GÉNÉRALES

void mani_clean() // vider les tampons d'input
{
	if (cin.fail()) cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	while (_kbhit()) _getch();
}

double mani_round(double v, int p) // arrondir v avec la précision p
{
	double e = pow(10, p);
	return round(v * e) / e;
}

string mani_date(time_t t)
{
	string ft;
	stringstream ss;
	tm d;

	localtime_s(&d, &t);
	ss << d.tm_mday << "/" << d.tm_mon + 1 << "/" << d.tm_year + 1900;
	ft = ss.str();
	return ft;
}

string mani_temps(time_t t)
{
	string ft;
	stringstream ss;
	tm d;

	localtime_s(&d, &t);
	ss << d.tm_hour << ":" << d.tm_min << ":" << d.tm_sec;
	ft = ss.str();
	return ft;
}


// FONCTIONS GÉNÉRALES POUR LA LECTURE D'UNE STRING, SON NETTOYAGE ET SON TRANSFERT DANS UN TABLEAU DE CHAR

string& mani_textCleaner(string& texte) // enlève les blancs et tabulations dans texte
{
	string mot;
	stringstream ss(texte);
	texte = "";
	while (ss >> mot)
		if (texte.size()) texte += " " + mot; else texte = mot;
	return texte;
}

void mani_copyStringTo(const string& s, const unsigned int size, char to[]) // copy s dans to. size est la taille de to
{
	unsigned int i;
	for (i = 0; (i < size - 1) && (i < s.size()); ++i)
		to[i] = s[i];
	to[i] = 0;
}

void mani_lireString(const int size, char to[])
{
	string texte;
	getline(cin, texte);
	mani_textCleaner(texte);
	mani_copyStringTo(texte, size, to);
}

void mani_message(string message, cvmColor c, int x, int y)
{
	cvmSetColor(c);	gotoxy(x, y); cout << message; clreol(); cvmResetColor();
}

void mani_avertissement(string warning, int x, int y, cvmColor c)
{
	mani_clean();
	mani_message(warning, c, x, y); _getch();
}

void mani_appuyerSurUneTouchePourContinuer(int x, int y)
{
	mani_avertissement("Appuyez sur une touche pour continuer ...", x, y, cvmColor::JAUNE);
}


// FONCTIONS POUR LIRE UNE RÉPONSE OUI / NON

bool mani_lireOuiNon()
{
	int choixb = 0, choix;
	mani_clean();
	cvmSetColor(cvmColor::JAUNE);
	while (true)
		switch (choix = toupper(_getch()))
		{
			case 0:	case -32: // control key
			if (_kbhit()) _getch();	break;

			case 13: // enter
			if (choixb == 'O' || choixb == 'N') return choixb == 'O'; break;

			case 'O': case 'N':
			cout << char(choixb = choix) << "\b"; break;
		}
}

bool mani_lireQuestionOuiNon(string question, cvmColor c, int x, int y)
{
	mani_message(question + " (O / N) ? : ", c, x, y);
	return mani_lireOuiNon();
}

// FONCTION POUR EFFACER LES ANCIENNES QUESTIONS
void mani_deleteMessage(int x, int y)
{
	gotoxy(x, y); clreol();
}
