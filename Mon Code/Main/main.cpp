// INCLUDES STANDARDS
#include <iostream>
#include <iomanip>
#include <conio.h>

// INCLUDES PARTICULIERS
#include "../Database/db.h"
#include "../Menu/Menu.h"
#include "../../../C21-CVM/console(v1.9).h"

using namespace std;

size_t nbParticipant = 0;

int main()
{
	SetConsoleCP(1252);					// À FAIRE: dans les propriétés de la console, police(font) = LUCIDA CONSOLE
	SetConsoleOutputCP(1252);			// Permet d'écrire enfin vos string avec les accents !!!

	Commandes cmd;
	do
	{
		ui_afficherMenuPrincipal();
		cmd = ui_lireUnChoixValideDuMenuPrincipal();
		clrscr();


		switch (cmd)
		{
			case ajouterParticipant: break;
		}

	} while (cmd != quitter);
}
