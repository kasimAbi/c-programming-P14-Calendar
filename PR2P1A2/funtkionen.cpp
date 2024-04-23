#include"header.h"		// mit header.h verbinden


void datei_einlesen(Student *studenten_daten)
{
	char eingabe[GROESSE];
	char filler[GROESSE];
	int ok = 0, zahl = 0, fehler = 0, anzahl = 0;
	float note = 0.0;
	int laenge;
	FILE* meine_datei = fopen(DATNAME, "a+");		//zum schreiben (und lesen). dateipositionszeiger ganz unten.
	system("cls");
	while (ok != 2)		// 2 ist eine beliebige zahl hätte auch 10 nehmen können dann muss cih halt nur beim schluss was berücksichtigen
	{
		do
		{
			fscanf(meine_datei, "%s", &eingabe);
			anzahl++;
		} while (!feof(meine_datei));
		anzahl--;		// weil es sonst einmal zu viel etwas eingibt.
		laenge = 0;		// werte zurücksetzen.
		fehler = 0;
		printf("geben sie die Matrikelnummer des Studenten ein:\t");
		fgets(eingabe, GROESSE, stdin);
		laenge = strlen(eingabe) - 1;		// für später prüfen ob 8 zeichen.
		ok = pruefen_ob_zahl(eingabe);
		if (ok != 0 && laenge == 8 && anzahl != 0)
		{
			rewind(meine_datei);		// dateipositionszeiger zurücksetzen.
			do			// zum überprüfen ob die matrikelnummer schon vorhanden ist.
			{
				fscanf(meine_datei, "%s", &filler);
				zahl = pruefen_ob_zahl(filler);
				if (zahl == ok)
				{
					printf("Diese Matrikelnummer existiert bereits.\n");
					fehler = 1;
				}
			} while (!feof(meine_datei));
			if (fehler == 1)
			{
				ok = 0;
			}
		}
		if (ok != 0 && laenge == 8)		// laenge ist für die anzahl der zahlen.
		{
			studenten_daten->matrikelnummer = ok;		// schreibt wert von ok in matrikelnumemr rein bei struct da.
			ok = 0;		// damit es in die schleife rein kann.
			while (ok == 0)
			{
				printf("geben sie den namen des Studenten ein:\t");
				fgets(eingabe, GROESSE, stdin);
				ok = pruefen_ob_zeichen(eingabe);
				if (ok == 1)
				{
					ok = 3;		// damit es in die nächste schleife springen kann.
				}
				else
				{
					ok = 0;		// damit es die schleife nciht verlässt.
				}
				while (ok == 3)
				{
					strcpy(studenten_daten->name, eingabe);
					printf("geben sie den vornamen des Studenten ein:\t");
					fgets(eingabe, GROESSE, stdin);
					laenge = strlen(eingabe) - 1;
					ok = pruefen_ob_zeichen(eingabe);
					if (ok == 1 && laenge > 2)
					{
						strcpy(studenten_daten->vorname, eingabe);
						ok = 2;		// damit die schleife verlassen werden kann.
					}
					else
					{
						ok = 3;		// damit es die schleife nciht verlässt.
					}
				}
			}
		}
		else
		{
			printf("Sie haben einen fehler gemacht.\n\n");
		}
	}
	ok = 0;		// damit es in die schleife rein kann.
	while (ok != 1)
	{
		printf("Geben sie ihre Mathe Note ein:\t");
		fgets(eingabe, GROESSE, stdin);
		note = pruefen_komma_zahl(eingabe);
		if (note >= 1.0 && note <= 5.0)
		{
			studenten_daten->zensuren[0] = note;

			ok = 1;		// damit es die schleife verlässt.
		}
	}
	ok = 0;			// damit es in die schleife rein kann.
	while (ok != 1)
	{
		printf("Geben sie ihre Programmieren Note ein:\t");
		fgets(eingabe, GROESSE, stdin);
		note = pruefen_komma_zahl(eingabe);
		if (note >= 1.0 && note <= 5.0)
		{
			studenten_daten->zensuren[1] = note;
			ok = 1;		// damit es die schleife verlässt.
		}
	}
	ok = 0;			// damit es in die schleife rein kann.
	while (ok != 1)	
	{
		printf("Geben sie ihre Algo Note ein:\t");
		fgets(eingabe, GROESSE, stdin);
		note = pruefen_komma_zahl(eingabe);
		if (note >= 1.0 && note <= 5.0)		// kontrolliert ob die note gueltig ist.
		{
			studenten_daten->zensuren[2] = note;
			ok = 1;		// damit es die schleife verlässt.
			fprintf(meine_datei, "%i\n", studenten_daten->matrikelnummer);		// alle eingaben in datei hinzufügen.
			fprintf(meine_datei, "%s", studenten_daten->name);
			fprintf(meine_datei, "%s", studenten_daten->vorname);
			fprintf(meine_datei, "%f\n", studenten_daten->zensuren[0]);
			fprintf(meine_datei, "%f\n", studenten_daten->zensuren[1]);
			fprintf(meine_datei, "%f\n", studenten_daten->zensuren[2]);
		}
	}
	fclose(meine_datei);		// schließt datei.
}

void daten_anzeigen(void)
{
	FILE* meine_datei;
	char eingabe[GROESSE];
	int zahl = 0, index = 0, index2 = 0, anzahl = 0;
	float note = 0.0;
	meine_datei = fopen(DATNAME, "a+");		// öffnet eine datei zum lesen.
	rewind(meine_datei);		// dateipositionszeiger auf 1 setzen.
	do
	{
		fscanf(meine_datei, "%s", &eingabe);
		anzahl++;
	} while (!feof(meine_datei));
	anzahl--;		// weil es sonst einmal zu viel etwas eingibt.
	index = 0;
	index2 = 0;
	if (anzahl != 0)
	{
		rewind(meine_datei);	// Dateipositionszeiger auf 1 setzen.
		do
		{
			index++;		// um die reihenfolge richtig zu bestimmen.
			index2++;		// damit es alle durchgänge zählt und am ende einen fehler vermeidet. der fehler ist das er einmal etwas zu viel ausgibt.
			fscanf(meine_datei, "%s", &eingabe);
			if (index == 6)
			{
				note = pruefen_komma_zahl(eingabe);
				printf("Algo Note:\t%.1f\n\n", note);
			}
			else if (index == 5)
			{
				note = pruefen_komma_zahl(eingabe);
				printf("Prog. Note:\t%.1f\n", note);
			}
			else if (index == 4)
			{
				note = pruefen_komma_zahl(eingabe);
				printf("Mathe Note:\t%.1f\n", note);
			}
			else if (index == 3)
			{
				printf("Vorname:\t%s\n", eingabe);
			}
			else if (index == 2)
			{
				printf("Nachname:\t%s\n", eingabe);
			}
			else if (index2 > anzahl)		// damit das programm merkt das es vorbei ist und das letzte zeichen nciht doppelt ausgibt.
			{
				printf("\n");				// zum schluss ncoh einen zeilensprung.
			}
			else
			{
				printf("Matrikelnummer:\t%s\n", eingabe);
			}
			if (index == 6)
			{
				index = 0;
			}
		} while (!feof(meine_datei));		// feof = end of file
	}
	else
	{
		printf("Die Datei ist leer.\n");
	}
	fgets(eingabe, GROESSE, stdin);		// zum aufhalten des programms vorm ende.
	system("cls");
	fclose(meine_datei);		// schließt datei.
}

void zensuren_aendern(void)
{
	FILE* meine_datei;	
	meine_datei = fopen(DATNAME, "a+");		// öffnet eine datei zum lesen.
	FILE* meine_datei_2;
	if (!meine_datei)
	{
		printf("Datei konnte nicht geoeffnet werden.\n\n");
		return;
	}
	int mtr_nr, beenden = 0, wahl = 0, anzahl = 0, anzal = 0, index = 0, test_mtr_nr = 0, ok = 0;		// deklarationen/initialisierungen.
	int zahl = 0;
	Student temp;
	float neue_note = 0.0;
	char eingabe[GROESSE];	

	rewind(meine_datei);
	do
	{
		fscanf(meine_datei, "%s", &eingabe);		// um den dateipostitionszeiger zu bewegen.
		anzahl++;
	} while (!feof(meine_datei));
	anzahl--;
	if (anzahl != 0)
	{
		while (beenden != 1)
		{
			index = 0;
			ok = 0;
			system("cls");
			rewind(meine_datei);		// dateipostionszeiger zurücksetzen.
			do
			{
				index++;
				fscanf(meine_datei, "%s", &eingabe);		// damit der dateipositionszeiger voranschreitet.
				zahl = pruefen_ob_zahl(eingabe);
				if (index == 1 && zahl != 0)	// prüft ob die zahl auch eine matrikelnummer ist.
				{
					printf("Matrikelnummer:\t %s\n", eingabe);
				}
				else if (index == 2)
				{
					printf("Nachname:\t %s\n", eingabe);
				}
				else if (index == 3)
				{
					printf("Vorname:\t %s\n\n", eingabe);
				}
				if (index == 6)
				{
					index = 0;
				}
			} while (!feof(meine_datei));
			printf("Geben sie die Matrikelnummer des Schuelers an,\ndessen Note geaendert werden soll:\t");
			fgets(eingabe, GROESSE, stdin);
			mtr_nr = pruefen_ob_zahl(eingabe);		// mtr_nr soll matrikelnumemr sein, die der user eingibt.
			index = 0;
			ok = 0;
			// zur kontrolle ob die mtr nr dabei ist.
			rewind(meine_datei);		// dateipostionszeiger zurücksetzen.
			do
			{
				// damit ich das gleich kontrollieren kann ob auch die eingegebene mtr nr richtig ist.	
				fscanf(meine_datei, "%i", &temp.matrikelnummer);		
				// damit der dateipositionszeiger sich bewegt(vorwärts).
				fscanf(meine_datei, "%s", &temp.name);
				fscanf(meine_datei, "%s", &temp.vorname);
				fscanf(meine_datei, "%f", &temp.zensuren[0]);
				fscanf(meine_datei, "%f", &temp.zensuren[1]);
				fscanf(meine_datei, "%f", &temp.zensuren[2]);
				if (!feof(meine_datei))
				{
					if (mtr_nr == temp.matrikelnummer)
					{
						ok = 1;
					}
				}
			} while (!feof(meine_datei) && ok != 1);
			if (ok == 1)
			{
				while (beenden != 1)
				{
					printf("Welche Note moechten sie denn aendern?\n (1) Mathe\n (2) Prog.\n (3) Algo\nIhre wahl:\t");
					fgets(eingabe, GROESSE, stdin);
					wahl = pruefen_ob_zahl(eingabe);
					if (wahl >= 1 && wahl <= 3)
					{
						printf("in welche note soll diese note gaendert werden?\naendern in:\t");
						fgets(eingabe, GROESSE, stdin);
						neue_note = pruefen_komma_zahl(eingabe);
						if (neue_note >= 1.0 && neue_note <= 5.0)
						{
							meine_datei_2 = fopen(DATNAME2, "w+");
							if (!meine_datei_2)
							{
								printf("Datei konnte nicht geoeffnet werden.\n\n");
								return;
							}
							// damit ich eine datei in die andere speichern kann und die anschließend lösche.
							rewind(meine_datei);		// dateipostionszeiger zurücksetzen.
							rewind(meine_datei_2);
							while (!feof(meine_datei))
							{
								fscanf(meine_datei, "%i", &temp.matrikelnummer);	
								fscanf(meine_datei, "%s", &temp.name);
								fscanf(meine_datei, "%s", &temp.vorname);
								fscanf(meine_datei, "%f", &temp.zensuren[0]);
								fscanf(meine_datei, "%f", &temp.zensuren[1]);
								fscanf(meine_datei, "%f", &temp.zensuren[2]);
								// die geaenderte note die der user eingibt.
								if (!feof(meine_datei))
								{
									if (mtr_nr == temp.matrikelnummer)
									{
										temp.zensuren[wahl - 1] = neue_note;
									}
								}
								fprintf(meine_datei_2, "%i\n", temp.matrikelnummer);	
								fprintf(meine_datei_2, "%s\n", temp.name);
								fprintf(meine_datei_2, "%s\n", temp.vorname);
								fprintf(meine_datei_2, "%f\n", temp.zensuren[0]);
								fprintf(meine_datei_2, "%f\n", temp.zensuren[1]);
								fprintf(meine_datei_2, "%f\n", temp.zensuren[2]);
							} 
							fclose(meine_datei);
							// speichert die 2.te datei in die erste und löscht sie anschließend wieder.
							meine_datei = fopen(DATNAME, "w+");
							if (!meine_datei)
							{
								printf("Datei konnte nicht geoeffnet werden.\n\n");
								return;
							}
							rewind(meine_datei);
							rewind(meine_datei_2);		// dateipostionszeiger zurücksetzen.
							index = 0;
							ok = 0;
							do
							{
								index += 6;
								fscanf(meine_datei_2, "%i", &temp.matrikelnummer);	
								fscanf(meine_datei_2, "%s", &temp.name);
								fscanf(meine_datei_2, "%s", &temp.vorname);
								fscanf(meine_datei_2, "%f", &temp.zensuren[0]);
								fscanf(meine_datei_2, "%f", &temp.zensuren[1]);
								fscanf(meine_datei_2, "%f", &temp.zensuren[2]);

								fprintf(meine_datei, "%i\n", temp.matrikelnummer);	
								fprintf(meine_datei, "%s\n", temp.name);
								fprintf(meine_datei, "%s\n", temp.vorname);
								fprintf(meine_datei, "%f\n", temp.zensuren[0]);
								fprintf(meine_datei, "%f\n", temp.zensuren[1]);
								fprintf(meine_datei, "%f\n", temp.zensuren[2]);
								if (index >= anzahl)			// sonst macht das problem einmal zu viel alles. also die schleife.
								{
									ok = 1;		// das ist eine end bedingung für die schleife.
								}
							} while (!feof(meine_datei_2) && ok != 1);
							fclose(meine_datei_2);
							remove(DATNAME2);		// löscht datei 2
						}
					}
					else
					{
						printf("FEHLER!\nbitte neu eingeben.\n\n");
						fgets(eingabe, GROESSE, stdin);
						system("cs");
					}
					printf("wenn sie die noten von diesem schüler nciht mehr aendern moechten,\ndann geben sie eine 1 ein:\t");
					fgets(eingabe, GROESSE, stdin);
					beenden = pruefen_ob_zahl(eingabe);
				}
			}
			else
			{
				printf("Ungueltige Matrikelnummer!\n");
			}
			printf("moechten sie von einem anderen schüler seine noten aendern?\nwenn NEIN bitte eine 1 eingeben:\t");
			fgets(eingabe, GROESSE, stdin);
			beenden = pruefen_ob_zahl(eingabe);
		}
		system("cls");
	}
	else
	{
		printf("Es sind keine Daten verfuegbar.\n");
	}
	fclose(meine_datei);		// schließt datei.
}

void datensatz_loeschen(void)
{
	FILE* meine_datei = fopen(DATNAME, "a+");		// öffnet datei zum lesen/schreiben und dateipositionszeiger ist ganz unten.
	FILE* meine_datei_2;
	Student temp;		// struktur erstellen
	int beenden = 1, mtr_nr = 0, ok = 0, index = 0;		// Deklaration/Initialisierung
	char eingabe[GROESSE];
	while (beenden != 0)
	{
		ok = 0;
		system("cls");
		rewind(meine_datei);		// dateipostionszeiger zurücksetzen.
		do
		{
			// damit ich das gleich kontrollieren kann ob auch die eingegebene mtr nr richtig ist.	
			fscanf(meine_datei, "%i", &temp.matrikelnummer);
			// damit der dateipositionszeiger sich bewegt(vorwärts).
			fscanf(meine_datei, "%s", &temp.name);
			fscanf(meine_datei, "%s", &temp.vorname);
			fscanf(meine_datei, "%f", &temp.zensuren[0]);
			fscanf(meine_datei, "%f", &temp.zensuren[1]);
			fscanf(meine_datei, "%f", &temp.zensuren[2]);
			if (!feof(meine_datei))
			{
				printf("Matrikelnummer:\t%i\n", temp.matrikelnummer);
				printf("Nachname:\t%s\n", temp.name);
				printf("Vorname:\t%s\n\n", temp.vorname);
			}
		} while (!feof(meine_datei));
		printf("Geben sie die Matrikelnummer ein die sie loeschen wollen:\t");
		fgets(eingabe, GROESSE, stdin);
		mtr_nr = pruefen_ob_zahl(eingabe);
		rewind(meine_datei);		// dateipostionszeiger zurücksetzen.
		do
		{
			// damit ich das gleich kontrollieren kann ob auch die eingegebene mtr nr richtig ist.	
			fscanf(meine_datei, "%i", &temp.matrikelnummer);
			// damit der dateipositionszeiger sich bewegt(vorwärts).
			fscanf(meine_datei, "%s", &temp.name);
			fscanf(meine_datei, "%s", &temp.vorname);
			fscanf(meine_datei, "%f", &temp.zensuren[0]);
			fscanf(meine_datei, "%f", &temp.zensuren[1]);
			fscanf(meine_datei, "%f", &temp.zensuren[2]);
			if (!feof(meine_datei))
			{
				if (mtr_nr == temp.matrikelnummer)
				{
					ok = 1;
				}
			}
		} while (!feof(meine_datei));
		if (ok == 1)
		{
			ok = 0;
			meine_datei_2 = fopen(DATNAME2, "a+");
			if (!meine_datei_2)
			{
				printf("Datei konnte nicht geoeffnet werden.\n\n");
				return;
			}
			// damit ich eine datei in die andere speichern kann und die anschließend lösche.
			rewind(meine_datei);		// dateipostionszeiger zurücksetzen.
			rewind(meine_datei_2);
			while (!feof(meine_datei))
			{
				fscanf(meine_datei, "%i", &temp.matrikelnummer);
				fscanf(meine_datei, "%s", &temp.name);
				fscanf(meine_datei, "%s", &temp.vorname);
				fscanf(meine_datei, "%f", &temp.zensuren[0]);
				fscanf(meine_datei, "%f", &temp.zensuren[1]);
				fscanf(meine_datei, "%f", &temp.zensuren[2]);
				// in datei 2 speichern.
				if (!feof(meine_datei))
				{
					if (mtr_nr != temp.matrikelnummer)
					{
						fprintf(meine_datei_2, "%i\n", temp.matrikelnummer);
						fprintf(meine_datei_2, "%s\n", temp.name);
						fprintf(meine_datei_2, "%s\n", temp.vorname);
						fprintf(meine_datei_2, "%f\n", temp.zensuren[0]);
						fprintf(meine_datei_2, "%f\n", temp.zensuren[1]);
						fprintf(meine_datei_2, "%f\n", temp.zensuren[2]);
					}
				}
			}
			fclose(meine_datei);
			// speichert die 2.te datei in die erste und löscht sie anschließend wieder.
			fclose(meine_datei_2);
			remove(DATNAME);		// löscht datei und datei 2 wird dann hauptdatei.
			rename(DATNAME2,DATNAME);
		}
		else
		{
			system("cls");
			printf("Diese Matrikelnummer ist nicht vorhanden.\n\n");
		}
		printf("wenn sie weitere schüler loeschen moechten,\ndann bitte KEINE 0 eingeben.");
		fgets(eingabe, GROESSE, stdin);
		beenden = pruefen_ob_zahl(eingabe);
	}
	system("cls");
}