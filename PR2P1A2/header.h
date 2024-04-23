#pragma once		

#ifndef header_h		// wenn nicht definiert.
#define header_h

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>		// Bibliotheken
#include<ctype.h>
#include<string>
#include<stdlib.h>

#define DATNAME "datei.txt"		// dateinamen
#define DATNAME2 "datei2.txt"
#define GROESSE 20			// definierte zahl

struct Student		// struktur
{
	char name[GROESSE];
	char vorname[GROESSE];
	int matrikelnummer;
	float zensuren[3];
};

void datei_einlesen(Student *studenten_daten);		// funktionsdeklarationen
void daten_anzeigen(void);
void zensuren_aendern(void);
void datensatz_loeschen(void);
int pruefen_ob_zahl(char[GROESSE]);
int pruefen_ob_zeichen(char[GROESSE]);
float pruefen_komma_zahl(char[GROESSE]);

#endif // !header_h
