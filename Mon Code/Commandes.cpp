#include <iostream>
#include <iomanip>
#include <conio.h>

#include "db.h"
#include "Manipulateurs.h"
#include "Commandes.h"

#include "../../C21-CVM/console(v1.9).h"

using namespace std;

#pragma warning (disable:6031)	//_getch()

// DÉFINITION DES FONCTIONS D'AFFICHAGES
void affichage(size_t no, Participant& p)
{
	clrscr();
	cvmSetColor(cvmColor::VERT);
	gotoxy(4, 0);	cout << "LE RÉPARTITEUR DE DÉPENSES";
	gotoxy(4, 1);	cout << "--------------------------"; cvmResetColor();
	gotoxy(4, 4);	cout << "Informations personelles (#" << no << ")";
	gotoxy(9, 6);	cout << "Nom" << setw(11) << ": " << p.prenom << " " << p.nom;
	gotoxy(9, 8);	cout << "Adresse" << setw(7) << ": " << p.adresse.noCivique << " " << p.adresse.rue << ", " << p.adresse.ville << ", " << p.adresse.codePostal;
	gotoxy(9, 9);	cout << "Téléphone   : " << p.adresse.telephone;
	gotoxy(4, 12);	cout << "Liste des dépenses (Max 10)";
}

void affichage_Depenses(Participant& p)
{
	int y = 14;
	double montantDepense = 0;

	if (p.nbDepenseActuel >= 1)
	{
		for (int i = 0; i < p.nbDepenseActuel; ++i)
		{
			gotoxy(4, 14); cout << "     "; // EFFACER L'ANCIEN MESSAGE

			gotoxy(9, y++);
			cout << (i+1)<< ". " << mani_date(p.liste_depense[i].dateHeureDepense) << " - " << mani_temps(p.liste_depense[i].dateHeureDepense)
				<< "    " << p.liste_depense[i].montant << " $  " << p.liste_depense[i].description;
		}
		gotoxy(33, y);		cout << "-----------";
		gotoxy(35, y += 1); sommeDepenseParticipant(montantDepense, p); cout << " $";
	}
	else
	{
		gotoxy(4, 14); cout << "Aucune dépense";
	}
}

void affichage_QuitterCommande()
{
	mani_message("Dépenses enregistrées !", cvmColor::JAUNE, 4, 28);
	_getch();
	clrscr();
}

void affichage_QuitterCommandeDepense()
{
	mani_message("Dépenses supprimées enregistrées !", cvmColor::JAUNE, 4, 28);
	_getch(); clrscr();
}

// DÉFINITION DES FONCTIONS DE VALIDATION ET DE SOMMATION
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

double sommeDepenseParticipant(double MontantDepense,Participant& p)
{
	for (int i = 0; i < p.nbDepenseActuel; ++i)
	{
		MontantDepense += p.liste_depense[i].montant;
	}
	cout << " " << MontantDepense;
	return mani_round(MontantDepense, 2);
}

double sommeQuotePart(double Total, size_t no)
{
	return mani_round(Total / no, 2);
}

// DÉFINITION DES FONCTIONS D'INPUT
void input_Depense_Description(Participant& participant)
{ 
	mani_deleteMessage(4, 28);
	gotoxy(4, 25); cout << "Montant: ";		participant.liste_depense[participant.nbDepenseActuel].montant = lireUnMontantValide(MontantDep_Max);
	gotoxy(4, 26); cout << "Description: "; mani_clean(); mani_lireString(Longeur_Descript, participant.liste_depense[participant.nbDepenseActuel].description);

	participant.liste_depense[participant.nbDepenseActuel].dateHeureDepense = time(NULL);
	cvmResetColor();
	mani_deleteMessage(4, 25);  mani_deleteMessage(4, 26);
}

int lire_no_Supprimer(int nbDepenses)
{
	bool noDepense = false;
	int input,x = 4, y = 28;

	gotoxy(x, y); cout << "Dépense no (0 pour annuler) : ";
	x = wherex(), y = wherey();

	do
	{
		gotoxy(x, y); clreoscr();
		cin >> input;

		if (cin.fail() || input > nbDepenses)
		{
			mani_clean();
		}
		else
		{
			noDepense = true;
		}

	} while (!noDepense);
	return input;
}

// FONCTIONS DE MODIFICATION DE VALEUR
void supprimer_Client(int participant,Participant& p)
{
	for (int c = participant-1; c < p.nbDepenseActuel; ++c)
		p.liste_depense[c] = p.liste_depense[c + 1];
	p.liste_depense[--p.nbDepenseActuel] = {};
}

void supprimer_Depenses_Total(Participant& p)
{
	for (int i = 0; i < p.nbDepenseActuel; ++i)
	{
		p.liste_depense[i] = {};
	}
	p.nbDepenseActuel = 0;
}

// FONCTIONS DE VÉRIFICATION D'INPUT 
void noDepenseValideEtAffichage(size_t no, int noInput, Participant& p)
{
	if (noInput != 0)
	{
		supprimer_Client(noInput, p);
		clrscr();
		cvmResetColor();
		affichage(no, p);
		affichage_Depenses(p);
	}
}

// DÉFINITION DES COMMANDES PRINCIPALES
void CMD_AjouterUnParticipant()
{
	Participant participant;
	size_t no = db_size() + 1;

	clrscr();
	mani_clean;

	// AFFICHAGE DU MENU 
	cvmSetColor(cvmColor::VERT);
	gotoxy(4, 0);	cout << "LE RÉPARTITEUR DE DÉPENSES";
	gotoxy(4, 1);	cout << "--------------------------"; cvmResetColor();
	gotoxy(4, 4);	cout << "Création du participant #" << no;
	gotoxy(4, 7);	cout << "Informations personnelles";
	gotoxy(4, 8);	cout << "-------------------------";
	gotoxy(4, 10);	cout << "Prénom" << setw(16) << ": "; mani_lireString(Longeur_Prenom, participant.prenom);
	gotoxy(4, 11);	cout << "Nom" << setw(19) << ": ";	  mani_lireString(Longeur_Nom, participant.nom);
	gotoxy(4, 13);	cout << "Adresse"; gotoxy(4, 14); cout << "-------";
	gotoxy(4, 16);	cout << "Numéro civique" << setw(8) << ": "; mani_lireString(Longeur_NoCivique, participant.adresse.noCivique);
	gotoxy(4, 17);	cout << "Rue" << setw(19) << ": ";	  mani_lireString(Longeur_Rue, participant.adresse.rue);
	gotoxy(4, 18);	cout << "Ville" << setw(17) << ": ";  mani_lireString(Longeur_Ville, participant.adresse.ville);
	gotoxy(4, 19);	cout << "Code Postal" << setw(11) << ": ";	 mani_lireString(Longeur_CodeP, participant.adresse.codePostal);
	gotoxy(4, 20);	cout << "Numéro de téléphone : ";	  mani_lireString(Longeur_NoTel, participant.adresse.telephone);

	// INITIALISATIONS DES COMPTES
	for (int i = 0; i < nbDepenseMax; i++)
	{
		participant.liste_depense[i].montant = 0;
	}
	participant.nbDepenseActuel = 0; // INITIALISATION DES DÉPENSES À O POUR LE COMPTE CRÉER

	db_write(no, &participant);
	clrscr();
}

void CMD_AfficherUnParticipant()
{
	Participant participant;
	size_t no, dbsize = db_size();

	cvmSetColor(cvmColor::JAUNE);
	gotoxy(4, 28); cout << "Numéro du participant : "; cin >> no;

	mani_clean();

	if (cin.fail() || no <= 0 || no > dbsize)
	{
		cin.clear(); clrscr();
	}
	else
	{
		db_read(no, &participant);
		affichage(no,participant);
		affichage_Depenses(participant);
		mani_appuyerSurUneTouchePourContinuer(4, 28);
		clrscr();
	}
}

void CMD_AjouterDesDepenses()
{
	Participant participant;
	size_t no, dbsize = db_size();
	bool quitCommande = false;

	mani_clean();

	cvmSetColor(cvmColor::JAUNE);
	gotoxy(4, 28); cout << "Numéro du participant : "; cin >> no;

	if (cin.fail() || no <= 0 || no > dbsize)
	{
		cin.clear(); clrscr();
	}
	else
	{
		db_read(no, &participant);
		affichage(no, participant);
		affichage_Depenses(participant);
		mani_clean();

		if (participant.nbDepenseActuel == 10)
		{
			mani_message("Le maximum de 10 dépenses est déjà atteint !", cvmColor::JAUNE, 4, 28);
			_getch(); clrscr();
		}
		else
		{
			if (mani_lireQuestionOuiNon("Désirez-vous ajouter une dépense", cvmColor::JAUNE, 4, 28))
			{
				input_Depense_Description(participant);
				participant.nbDepenseActuel++;
				affichage_Depenses(participant);
				db_write(no, &participant);

				do
				{
					if (mani_lireQuestionOuiNon("Désirez-vous ajouter une autre dépense", cvmColor::JAUNE, 4, 28))
					{
						input_Depense_Description(participant);
						participant.nbDepenseActuel++;
						affichage_Depenses(participant);
						db_write(no, &participant);

						if (participant.nbDepenseActuel == 10)
						{
							quitCommande = true;
							affichage_QuitterCommande();
						}
					}
					else
					{
						quitCommande = true;
						affichage_QuitterCommande();
					}
				} while (participant.nbDepenseActuel < nbDepenseMax && !quitCommande);
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
	size_t no,dbsize = db_size();
	int indDep;		// INDICE AUQUEL LA DÉPENSE DOIT ÊTRE SUPPRIMÉ
	bool quitterCommande = false;

	mani_clean();

	cvmSetColor(cvmColor::JAUNE);
	gotoxy(4, 28); cout << "Numéro du participant : "; cin >> no;

	if (cin.fail() || no <= 0 || no > dbsize)
	{
		cin.clear(); clrscr();
	}
	else
	{
		db_read(no, &participant);
		affichage(no, participant);
		affichage_Depenses(participant);
		mani_clean();

		if (participant.nbDepenseActuel == 0)
		{
			mani_message("Ce participant n'a pas de dépense à son dossier!", cvmColor::JAUNE, 4, 28);
			_getch(); clrscr();
		}
		else
		{
			if (mani_lireQuestionOuiNon("Désirez-vous supprimer une dépense", cvmColor::JAUNE, 4, 28))
			{
				indDep = lire_no_Supprimer(participant.nbDepenseActuel);
				noDepenseValideEtAffichage(no,indDep, participant);
				db_write(no, &participant);

				do
				{
					if (mani_lireQuestionOuiNon("Désirez-vous supprimer une autre dépense", cvmColor::JAUNE, 4, 28))
					{
						indDep = lire_no_Supprimer(participant.nbDepenseActuel);
						noDepenseValideEtAffichage(no,indDep, participant);
						db_write(no, &participant);

						if (participant.nbDepenseActuel == 0)
						{
							quitterCommande = true;
							affichage_QuitterCommandeDepense();
						}
					}
					else
					{
						quitterCommande = true;  
						affichage_QuitterCommandeDepense();
					}
				} while (!quitterCommande || indDep == 0);
			}
			else
			{
				clrscr();
			}
		}
	}
}

void CMD_AfficherEtatDesComptes()
{
	Participant participant;
	size_t dbsize = db_size();
	double montantDepense = 0, MontantTotal = 0, QuotePart = 0;
	int y = 4;
	clrscr();
	mani_clean();

	cvmSetColor(cvmColor::VERT);
	gotoxy(4, 0);	cout << "LE RÉPARTITEUR DE DÉPENSES";
	gotoxy(4, 1);	cout << "--------------------------"; cvmResetColor();
	gotoxy(74, 0);	cout << db_size() << " participant" << "\n\n\n\n";

	if (dbsize >= 1)
	{
		for (unsigned no = 1; no <= dbsize; no++)
		{
			db_read(no, &participant);
			gotoxy(8, y += 2);	cout << no << ") " << participant.prenom << " " << participant.nom;
			gotoxy(56, y);		cout << "Dépenses :      "; MontantTotal += sommeDepenseParticipant(montantDepense, participant); cout << "  $";
			gotoxy(4, 3); cout << "ÉTAT DES COMPTES  (date: " << mani_date(time(NULL)) << " - " << mani_temps(time(NULL)) << ")   quote-part : ";
		}
		gotoxy(53, y += 3); cout << "Grand Total :       " << MontantTotal << "  $";
		mani_appuyerSurUneTouchePourContinuer(4, y += 2);
	}
	else
	{
		gotoxy(4, 3); cout << "ÉTAT DES COMPTES  (date: " << mani_date(time(NULL)) << " - " << mani_temps(time(NULL)) << ")   quote-part : " << QuotePart << "   $";
		gotoxy(53, 7); cout << "Grand Total :       " << MontantTotal << "   $";
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
	
	if (mani_lireQuestionOuiNon("Voulez-vous supprimer seulement les dépenses des participants", cvmColor::JAUNE, 4, 26))
	{
		if (dbsize > 0)
		{
			for (unsigned no = 1; no <= dbsize; no++)
			{
				db_read(no, &participant);
				supprimer_Depenses_Total(participant);
				db_write(no, &participant);
			}
		}
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
	gotoxy(18, 15);

	string message1[sizeMessage1] = { "M","E","R","C","I"," ","D","'"," ","A","V","O","I","R"," ","U","T","I","L","I","S","É"," ", "C","E"," ","P","R","O","G","R","A","M","M","E"};

	for (int i = 0; i < sizeMessage1; ++i)
	{
		Sleep(35); cout << " " << message1[i];
	}

	Sleep(2000);
}