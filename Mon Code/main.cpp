#include <iostream>
#include <conio.h>
#include <iomanip>

#include "db.h"
#include "Commandes.h"

#include "../../../C21-CVM/console(v1.9).h"

using namespace std;

#pragma warning (disable:6031)	//_getch()
#pragma warning (disable:26812) //enum class

// LES FONCTIONS POUR LE MENU PRINCIPAL 

enum Commandes { ajouterParticipant, afficherDossier, ajouterD�penses, suprimerD�penses, afficher�tats, afficherSc�nario, SupprimerParticipants, quitter };

void ui_afficherMenuPrincipal()
{
	const int margeMenu = 4;

	cvmSetColor(cvmColor::VERT);
	gotoxy(4, 0);	cout << "LE R�PARTITEUR DE D�PENSES";
	gotoxy(4, 1);	cout << "--------------------------"; cvmResetColor();
	gotoxy(74, 0);	cout << db_size() << " participant" << "\n\n\n\n";

	cout << setw(margeMenu) << " " << "1. Ajouter un participant" << "\n\n";
	cout << setw(margeMenu) << " " << "2. Afficher le dossier d'un participant" << "\n\n";
	cout << setw(margeMenu) << " " << "3. Ajouter des d�penses" << "\n\n";
	cout << setw(margeMenu) << " " << "4. Supprimer des d�penses" << "\n\n";
	cout << setw(margeMenu) << " " << "5. Afficher l'�tat des comptes" << "\n\n";
	cout << setw(margeMenu) << " " << "6. Afficher un sc�nario de r�glements" << "\n\n";
	cout << setw(margeMenu) << " " << "D. Supprimer tous les participants" << "\n\n";
	cout << setw(margeMenu) << " " << "Q. Quitter" << "\n\n\n\n\n\n";

	cvmSetColor(cvmColor::JAUNE);
	cout << setw(margeMenu) << " " << "Entrez votre choix : ";
}

Commandes lireUnChoixValideDuMenuPrincipal()
{
	char choix;
	bool valide = false;
	Commandes cmd = quitter;

	do
	{
		switch (choix = toupper(_getch()))
		{
			case '1': cmd = ajouterParticipant;		valide = true; break;
			case '2': cmd = afficherDossier;		valide = true; break;
			case '3': cmd = ajouterD�penses;		valide = true; break;
			case '4': cmd = suprimerD�penses;		valide = true; break;
			case '5': cmd = afficher�tats;			valide = true; break;
			case '6': cmd = afficherSc�nario;		valide = true; break;
			case 'D': cmd = SupprimerParticipants;	valide = true; break;
			case 'Q': cmd = quitter;				valide = true; break;
		}
	} while (!valide);

	cout << choix;
	cvmResetColor();
	return cmd;
}

int main()
{
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);

	Commandes cmd;
	db_open();
	do
	{
		ui_afficherMenuPrincipal();
		cmd = lireUnChoixValideDuMenuPrincipal();
		switch (cmd)
		{
			case ajouterParticipant:	CMD_AjouterUnParticipant();				break;
			case afficherDossier:		CMD_AfficherUnParticipant();			break;
			case ajouterD�penses:		CMD_AjouterDesDepenses();				break;
			case suprimerD�penses:		CMD_SupprimerDesDepenses();				break;
			case afficher�tats:			CMD_AfficherEtatDesComptes();			break;
			//case afficherSc�nario:		CMD_AfficherUnScenarionDeReglements();	break;
			case SupprimerParticipants:	CMD_SupprimerTousLesParticipants();		break;
			case quitter:				CMD_QuitterLeProgramme();				break;	
		}
	} while (cmd != quitter);
	db_close();
}

