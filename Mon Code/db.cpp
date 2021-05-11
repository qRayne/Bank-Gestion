#include <fstream>
#include <Windows.h>
#include <iostream>

// INCLUDES PARTICULIERS 
#include "db.h"

using namespace std;

const string filename = "C:/Users/Rayan/Desktop/CVM/Session Hiver 2020-2021/Programmation 2/C21-CVM/Travail Finale/Mon Code/repartiteur.db";

static fstream f;

void db_create()
{
	if (f.is_open())
		f.close();
	f.open(filename, ios::in | ios::out | ios::binary | ios::trunc); // recréer le fichier vide
}

void db_open()
{
	f.open(filename, ios::in | ios::out | ios::binary);
	if (!f.is_open())
		db_create();								// si le fichier n'est pas trouvé le créer
}

bool db_isopen() { return f.is_open(); }

void db_close() { f.close(); }

int db_size()
{
	f.seekg(0, ios::end);
	return (size_t)f.tellg() / sizeof(Participant);
}

void db_read(size_t noParticipant, Participant* p)
{
	f.seekg((noParticipant - 1) * sizeof(Participant), ios::beg);
	f.read((char*)p, sizeof(Participant));
}

void db_write(size_t noParticipant, Participant* p)
{
	f.seekg((noParticipant - 1) * sizeof(Participant), ios::beg);
	f.write((char*)p, sizeof(Participant));
}