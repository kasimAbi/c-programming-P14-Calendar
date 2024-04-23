#include"header.h"		// mit header.h verbinden.

int main(void)
{
	FILE* meine_datei;		// Deklaration/Initialisierungen
	int wahl = 0;
	int ok = 0;
	char eingabe[GROESSE];
	Student studenten_daten;

	while (wahl != 5)
	{
		//menü
		printf("was moechten sie tun?\n (1) zum einlesen\n (2) zum anzeigen der daten\n (3) aendern der zensur\n (4) datensatz loeschen\n (5) Programm beenden.\nihre wahl:\t");
		fgets(eingabe, GROESSE, stdin);
		wahl = pruefen_ob_zahl(eingabe);
		switch (wahl)
		{
		case 1: 		
			while (ok != 2)
			{
				datei_einlesen(&studenten_daten);
				printf("moechten sie beenden?\ndann bitte eine 2 eingeben:\t");
				fgets(eingabe, GROESSE, stdin);
				ok = pruefen_ob_zahl(eingabe);		// funktionsaufrufe
				printf("\n\n");
			}
			break;
		case 2:
			daten_anzeigen();
			break;
		case 3: 
			zensuren_aendern();
			break;
		case 4:
			datensatz_loeschen();
			break;
		default:
			printf("sie haben etwas falsches eingegeben.\n\n");
			fgets(eingabe, GROESSE, stdin);
		}
		system("cls");		// löscht kommandozeile
	}
	return 0;
}