// INCLUDES STANDARDS
#include <iostream>
#include <iomanip>
#include <conio.h>

// INCLUDES PARTICULIERS
#include "Menu.h"
#include "../../../C21-CVM/console(v1.9).h"

using namespace std;

#pragma warning (disable:6031)	//_getch()
#pragma warning (disable:26812) //enum class

void ui_menu_Titre()
{
	cvmSetColor(cvmColor::VERT);
	gotoxy(4, 0);	cout << "LE RÉPARTITEUR DE DÉPENSES";
	gotoxy(4, 1);	cout << "--------------------------";
	cvmResetColor();
}

void ui_afficherMenuPrincipal()
{
	const int margeMenu = 4;

	ui_menu_Titre();
	gotoxy(74, 0); cout << nbParticipant << " participant" << "\n\n\n\n";

	cout << setw(margeMenu) << " " << "1. Ajouter un participant" << "\n\n";
	cout << setw(margeMenu) << " " << "2. Afficher le dossier d'un participant" << "\n\n";
	cout << setw(margeMenu) << " " << "3. Ajouter des dépenses" << "\n\n";
	cout << setw(margeMenu) << " " << "4. Supprimer des dépenses" << "\n\n";
	cout << setw(margeMenu) << " " << "5. Afficher l'état des comptes" << "\n\n";
	cout << setw(margeMenu) << " " << "6. Afficher un scénario de règlements" << "\n\n";
	cout << setw(margeMenu) << " " << "D. Supprimer tous les participants" << "\n\n";
	cout << setw(margeMenu) << " " << "Q. Quitter" << "\n\n\n\n\n\n";

	cvmSetColor(cvmColor::JAUNE);
	cout << setw(margeMenu) << " " << "Entrez votre choix : ";
	cvmResetColor();
}

Commandes ui_lireUnChoixValideDuMenuPrincipal()
{
	Commandes cmd = quitter;

	char choix;
	bool valide = false;

	cvmSetColor(cvmColor::JAUNE);

	do
	{
		choix = _getch();
		switch (choix)
		{
		case '1': cmd = ajouterParticipant;		cout << "1";					valide = true; break;
		case '2': cmd = afficherDossier;		cout << "2";					valide = true; break;
		case '3': cmd = ajouterDépenses;		cout << "3";					valide = true; break;
		case '4': cmd = suprimerDépenses;		cout << "4";					valide = true; break;
		case '5': cmd = afficherÉtats;			cout << "5";					valide = true; break;
		case '6': cmd = afficherScénario;		cout << "6";					valide = true; break;
		case 'd': cmd = SupprimerParticipants;	cout << "D";					valide = true; break;
		case 'q': cmd = quitter;				cout << "Q";					valide = true; break;
		}

	} while (!valide);

	cvmResetColor();
	return cmd;
}


