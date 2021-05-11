#include <iostream>
#include <iomanip>
#include <conio.h>

#include "db.h"
#include "Manipulateurs.h"
#include "Commandes.h"

#include "../../C21-CVM/console(v1.9).h"

using namespace std;

#pragma warning (disable:6031)	//_getch()

// D�FINITION DES FONCTIONS SECONDAIRES AU PROGRAMME
void affichage(size_t no, Participant& p)
{
	clrscr();
	cvmSetColor(cvmColor::VERT);
	gotoxy(4, 0);	cout << "LE R�PARTITEUR DE D�PENSES";
	gotoxy(4, 1);	cout << "--------------------------"; cvmResetColor();
	gotoxy(4, 4);	cout << "Informations personelles (#" << no << ")";
	gotoxy(9, 6);	cout << "Nom" << setw(11) << ": " << p.prenom << " " << p.nom;
	gotoxy(9, 8);	cout << "Adresse" << setw(7) << ": " << p.adresse.noCivique << " " << p.adresse.rue << ", " << p.adresse.ville << ", " << p.adresse.codePostal;
	gotoxy(9, 9);	cout << "T�l�phone   : " << p.adresse.telephone;
	gotoxy(4, 12);	cout << "Liste des d�penses (Max 10)";
}

void affichage_Depenses(Participant* p)
{
	double MontantDepense = 0;
	int y = 14;

	if (p->nbDepenseActuel >= 1)
	{
		for (int i = 0; i < p->nbDepenseActuel; ++i)
		{

			gotoxy(4, 14); cout << "     ";	// EFFACE L'ANCIEN MESSAGE
			gotoxy(9, y++); cout << i + 1 << ". " << mani_date(p->liste_depense[i].dateHeureDepense) 
								 << " - " << mani_temps(p->liste_depense[i].dateHeureDepense)
								 << "    " << p->liste_depense[i].montant << " $  " 
								 << p->liste_depense[i].description;
			
		}
		gotoxy(33, y);		cout << "-----------";
		/*gotoxy(35, y += 1);	sommeDepenseParticipant(MontantDepense, p);*/
	}
	else
	{
		gotoxy(4, 14); cout << "Aucune d�pense";
	}
}

double lireUnMontantValide(double max)
{
	bool montantValide = false;
	double montantDepense;
	int x = wherex(); int y = wherey();

	do
	{
		mani_clean();

		gotoxy(x, y); clreoscr();
		gotoxy(x, y); cin >> montantDepense;

		if (cin.fail())
			cin.clear();
		else if (montantDepense >= 0 && montantDepense <= max)
			montantValide = true;

	} while (!montantValide);
	
	return mani_round(montantDepense, 2);
}

double sommeDepenseParticipant(double MontantDepense,Participant* p)
{
	for (int i = 0; i < p->nbDepenseActuel; ++i)
	{
		MontantDepense += p->liste_depense[i].montant;
	}
	cout << " " << MontantDepense << " $";
	return mani_round(MontantDepense, 2);
}

// D�FINITION DES COMMANDES PRINCIPALES
void CMD_AjouterUnParticipant()
{
	Participant participant;
	size_t no = db_size() + 1;

	clrscr();
	mani_clean;

	// AFFICHAGE DU MENU 
	cvmSetColor(cvmColor::VERT);
	gotoxy(4, 0);	cout << "LE R�PARTITEUR DE D�PENSES";
	gotoxy(4, 1);	cout << "--------------------------"; cvmResetColor();
	gotoxy(4, 4);	cout << "Cr�ation du participant #" << no;
	gotoxy(4, 7);	cout << "Informations personnelles";
	gotoxy(4, 8);	cout << "-------------------------";
	gotoxy(4, 10);	cout << "Pr�nom" << setw(16) << ": "; mani_lireString(Longeur_Prenom, participant.prenom);
	gotoxy(4, 11);	cout << "Nom" << setw(19) << ": ";	  mani_lireString(Longeur_Nom, participant.nom);
	gotoxy(4, 13);	cout << "Adresse"; gotoxy(4, 14); cout << "-------";
	gotoxy(4, 16);	cout << "Num�ro civique" << setw(8) << ": "; mani_lireString(Longeur_NoCivique, participant.adresse.noCivique);
	gotoxy(4, 17);	cout << "Rue" << setw(19) << ": ";	  mani_lireString(Longeur_Rue, participant.adresse.rue);
	gotoxy(4, 18);	cout << "Ville" << setw(17) << ": ";  mani_lireString(Longeur_Ville, participant.adresse.ville);
	gotoxy(4, 19);	cout << "Code Postal" << setw(11) << ": ";	 mani_lireString(Longeur_CodeP, participant.adresse.codePostal);
	gotoxy(4, 20);	cout << "Num�ro de t�l�phone : ";	  mani_lireString(Longeur_NoTel, participant.adresse.telephone);

	// INITIALISATIONS DES COMPTES
	for (int i = 0; i < nbDepenseMax; i++)
	{
		participant.liste_depense[i].montant = 0;
	}
	participant.nbDepenseActuel = 0; // INITIALISATION DES D�PENSES � O POUR LE COMPTE CR�ER

	db_write(no, &participant);
	clrscr();
}

void CMD_AfficherUnParticipant()
{
	Participant participant;
	size_t no, dbsize = db_size();

	cvmSetColor(cvmColor::JAUNE);
	gotoxy(4, 28); cout << "Num�ro du participant : "; cin >> no;

	mani_clean();

	if (cin.fail() || no <= 0 || no > dbsize)
	{
		cin.clear(); clrscr();
	}
	else
	{
		db_read(no, &participant);
		affichage(no,participant);
		affichage_Depenses(&participant);
		mani_appuyerSurUneTouchePourContinuer(4, 28);
		clrscr();
	}
}

void CMD_AjouterDesDepenses()
{
	Participant participant;
	size_t no, dbsize = db_size();
	bool Ajout_Depense = false; // VARIABLE POUR LE DO WHILE 
	int i = 1;

	mani_clean();

	cvmSetColor(cvmColor::JAUNE);
	gotoxy(4, 28); cout << "Num�ro du participant : "; cin >> no;

	if (cin.fail() || no <= 0 || no > dbsize)
	{
		cin.clear(); clrscr();
	}
	else
	{
		db_read(no, &participant);
		affichage(no, participant);
		affichage_Depenses(&participant);
		mani_clean();

		if (participant.nbDepenseActuel == 10)
		{
			mani_message("Le maximum de 10 d�penses est d�j� atteint !", cvmColor::JAUNE, 4, 28);
			_getch();
			clrscr();
		}
		else
		{
			if (mani_lireQuestionOuiNon("D�sirez-vous ajouter une d�pense", cvmColor::JAUNE, 4, 28))
			{
				mani_deleteMessage(4, 28);
				gotoxy(4, 25); cout << "Montant: ";		participant.liste_depense[0].montant = lireUnMontantValide(MontantDep_Max);
				gotoxy(4, 26); cout << "Description: "; mani_clean(); mani_lireString(Longeur_Descript, participant.liste_depense[0].description);

				participant.liste_depense[0].dateHeureDepense = time(NULL);
				participant.nbDepenseActuel++;

				cvmResetColor();
				affichage_Depenses(&participant);
				mani_deleteMessage(4, 25);  mani_deleteMessage(4, 26);
				db_write(no, &participant);

				if (mani_lireQuestionOuiNon("D�sirez-vous ajouter une autre d�pense", cvmColor::JAUNE, 4, 28))
				{
					mani_deleteMessage(4, 28);
					gotoxy(4, 25); cout << "Montant: ";		participant.liste_depense[1].montant = lireUnMontantValide(MontantDep_Max);
					gotoxy(4, 26); cout << "Description: "; mani_clean(); mani_lireString(Longeur_Descript, participant.liste_depense[1].description);

					participant.liste_depense[1].dateHeureDepense = time(NULL);
					participant.nbDepenseActuel++;

					cvmResetColor();
					affichage_Depenses(&participant);
					mani_deleteMessage(4, 25);  mani_deleteMessage(4, 26);
					db_write(no, &participant);
				}
				else
				{
					mani_message("D�penses enregistr�es !", cvmColor::JAUNE, 4, 28); 
					_getch();
					clrscr();
				}
			}
			else
			{
				clrscr();
			}
			
		}
	}
}

void CMD_SupprimerDesDepenses()
{
	Participant participant;
	size_t no, dbsize = db_size();

	mani_clean();

	cvmSetColor(cvmColor::JAUNE);
	gotoxy(4, 28); cout << "Num�ro du participant : "; cin >> no;

	

	_getch();
}

void CMD_AfficherEtatDesComptes()
{
	Participant participant;
	size_t dbsize = db_size();
	double quote_part = 0, montantDepense = 0;
	int y = 4;

	clrscr();
	mani_clean();

	cvmSetColor(cvmColor::VERT);
	gotoxy(4, 0);	cout << "LE R�PARTITEUR DE D�PENSES";
	gotoxy(4, 1);	cout << "--------------------------"; cvmResetColor();
	gotoxy(74, 0);	cout << db_size() << " participant" << "\n\n\n\n";
	gotoxy(4, 3); cout << "�TAT DES COMPTES  (date: " << mani_date(time(NULL)) << " - " << mani_temps(time(NULL)) << ")   quote-part : " << quote_part;

	if (dbsize >= 1)
	{
		/*quote_part = montantTotalDepens�sdetouslesparticipant / dbsize */
		for (unsigned no = 1; no <= dbsize; no++)
		{
			db_read(no, &participant);
			gotoxy(8, y += 2);	cout << no << ") " << participant.prenom << " " << participant.nom; 
			gotoxy(56, y);		cout << "D�penses :       "; sommeDepenseParticipant(montantDepense, &participant);
		}
		gotoxy(53, y += 3); cout << "Grand Total :       "; /*montant total de tous les participant*/
		mani_appuyerSurUneTouchePourContinuer(4, y+=2);
	}
	else
	{
		gotoxy(53, 7); cout << "Grand Total :       "; /*quote_part = 0.00 $*/
		mani_appuyerSurUneTouchePourContinuer(4, 9);
	}

	clrscr();
}

void CMD_AfficherUnScenarionDeReglements()
{

}

void CMD_SupprimerTousLesParticipants()
{
	Participant participant;
	size_t no, dbsize = db_size();

	mani_clean();
	
	if (mani_lireQuestionOuiNon("Voulez-vous supprimer seulement les d�penses des participants", cvmColor::JAUNE, 4, 26))
	{
		/*EFFACE LES D�PENSES DE TOUS LES PARTICIPANTS*/
	}
	else
		if (mani_lireQuestionOuiNon("Voulez-vous supprimer tous les participants", cvmColor::JAUNE, 4, 28))
			db_create();	// PAS BESOIN DE ELSE DANS CE CAS
		
	clrscr();
}

void CMD_QuitterLeProgramme()
{
	const int sizeMessage1 = 35;

	clrscr();
	cvmSetColor(cvmColor::ROUGE);
	gotoxy(20, 15);

	string message1[sizeMessage1] = { "M","E","R","C","I"," ","D","'"," ","A","V","O","I","R"," ","U","T","I","L","I","S","�"," ", "C","E"," ","P","R","O","G","R","A","M","M","E"};

	for (int i = 0; i < sizeMessage1; ++i)
	{
		Sleep(35); cout << " " << message1[i];
	}

	_getch();
}



