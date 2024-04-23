#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string>
#include<time.h>

int stunden_funktion(int);
int minuten_funktion(int);
int sekunden_funktion(int);
int tag_funktion(int);
int monat_funktion(int);
int jahr_funktion(int);

int main()
{
	int jahr, monat, tag, beenden = 0;		// Deklarationen
	int stunden, minuten, sekunden;
	int sek;

	while (beenden != 1)
	{
		// +7200 sekunden wegen zeit utc zu mez. 3600 sekunden sind eine stunde.
		sek = time(0) + 7200;			// Sekunden bestimmen seit 1.1.1970

		// printf("%i\n", sek);
		stunden = stunden_funktion(sek);		// Funktionsaufrufe
		minuten = minuten_funktion(sek);
		sekunden = sekunden_funktion(sek);
		jahr = jahr_funktion(sek);
		monat = monat_funktion(sek);
		tag = tag_funktion(sek);
		printf("Datum: %i:%i:%i\n", tag, monat, jahr);
		printf("Zeit: %i:%i:%i\n\n", stunden, minuten, sekunden);
		getchar();
		system("cls");
	}
	getchar();
	return 0;
}

int stunden_funktion(int sek)		// funktion zu stunden
{
	return (sek / 3600 % 24);		
}

int minuten_funktion(int sek)		// funktion zu minuten
{
	return (sek / 60) % 60;				
}

int sekunden_funktion(int sek)		// funktion zu sekunden
{
	return sek % 60;
}

int tag_funktion(int sek)			// funktion für welchen tag ausrechnen
{
	int jahre = 0;				// initalisierungen/ Deklarationen
	int anzahl_schaltjahre = 0;
	int tage = 0;
	int vergangene_tage = 0;
	int ok = 0;
	int monat = 0;

	// 3600 * 24 damit man die anzahl der vergangenen tage seit 1970 bekommt.
	vergangene_tage = sek / 86400;
	// ab 1973 die schaltjahre bestimmen. +1 am ende weil ein schaltjahr da schon war. 1972 februar also.
	anzahl_schaltjahre = ((vergangene_tage - 3 * 365 + 1) / (4 * 365 + 1)) + 1;
	// 31536000 für ein ganzes jahr. das + die tage in den schaltjahren
	jahre = sek / (31536000 + anzahl_schaltjahre * 86400);
	if ((1972 + jahre) % 100 == 0 && (1972 + jahre) % 400 != 0)
	{
		anzahl_schaltjahre--;
		jahre = sek / (31536000 + anzahl_schaltjahre * 86400);
		tage = (vergangene_tage - anzahl_schaltjahre) % 365 + 1;
		ok = 1;
	}
	else
	{
		tage = (vergangene_tage - anzahl_schaltjahre) % 365 + 1;
	}
	if (tage <= 31)
	{
		;
	}
	// für die normalen jahre
	// printf("Kalenderwoche: %i\n", (tage / 7) + 1);
	if ((jahre + 1972) % 4 != 0 && ok != 1)
	{
		if (tage >= 32 && tage <= 59)
		{
			tage -= 31;
		}
		else if (tage >= 60 && tage <= 90)
		{
			// 31 - 28. das heißt die tage von februar und januar werden abgezogen
			tage -= 59;
		}
		else if (tage >= 91 && tage <= 120)
		{
			// wie oben nur das von märz auch abgezogen wird.
			tage -= 90;
		}
		else if (tage >= 121 && tage <= 151)
		{
			tage -= 120;
		}
		else if (tage >= 152 && tage <= 181)
		{
			tage -= 151;
		}
		else if (tage >= 182 && tage <= 212)
		{
			tage -= 181;
		}
		else if (tage >= 213 && tage <= 243)
		{
			tage -= 212;
		}
		else if (tage >= 244 && tage <= 273)
		{
			tage -= 243;
		}
		else if (tage >= 274 && tage <= 304)
		{
			tage -= 273;
		}
		else if (tage >= 306 && tage <= 334)
		{
			tage -= 304;
		}
		else if (tage >= 336 && tage <= 365)
		{
			tage -= 334;
		}
		else
		{
			printf("\n\nfehler!\n\n");
		}
	}
	else
	{
		// mit 29 tagen im februar
		if (tage >= 32 && tage <= 60)
		{
			tage -= 31;
		}
		else if (tage >= 61 && tage <= 91)
		{
			// wie oben auch. tage von februar und januar werden abgezogen.
			tage -= 60;
		}
		else if (tage >= 91 && tage <= 121)
		{
			tage -= 91;
		}
		else if (tage >= 121 && tage <= 152)
		{
			tage -= 121;
		}
		else if (tage >= 152 && tage <= 182)
		{
			tage -= 152;
		}
		else if (tage >= 182 && tage <= 213)
		{
			tage -= 182;
		}
		else if (tage >= 213 && tage <= 244)
		{
			tage -= 213;
		}
		else if (tage >= 244 && tage <= 274)
		{
			tage -= 244;
		}
		else if (tage >= 274 && tage <= 305)
		{
			tage -= 274;
		}
		else if (tage >= 306 && tage <= 335)
		{
			tage -= 305;
		}
		else if (tage >= 336 && tage <= 366)
		{
			tage -= 335;
		}
		else
		{
			printf("\n\nfehler!\n\n");
		}
	}
	return tage;
}

int monat_funktion(int sek)
{
	// alles genauso wir bei tag nur das statt die tage der monat bestimmt wird.
	int jahre = 0;
	int anzahl_schaltjahre = 0;
	int tage = 0;
	int vergangene_tage = 0;
	int ok = 0;
	int monat = 0;

	// 3600 * 24 damit man die anzahl der vergangenen tage seit 1970 bekommt.
	vergangene_tage = sek / 86400;
	anzahl_schaltjahre = ((vergangene_tage - 3 * 365 + 1) / (4 * 365 + 1)) + 1;
	jahre = sek / (31536000 + anzahl_schaltjahre * 86400);
	if ((1972 + jahre) % 100 == 0 && (1972 + jahre) % 400 != 0)
	{
		anzahl_schaltjahre--;
		jahre = sek / (31536000 + anzahl_schaltjahre * 86400);
		tage = (vergangene_tage - anzahl_schaltjahre) % 365 + 1;
		ok = 1;
	}
	else
	{
		tage = (vergangene_tage - anzahl_schaltjahre) % 365 + 1;
	}
	if (tage <= 31)
	{
		// statt tag wird monat bestimmt.
		monat = 1;
	}
	if ((jahre + 1972) % 4 != 0 && ok != 1)
	{
		// mit 28 tagen im februar
		if (tage >= 32 && tage <= 59)
		{
			monat = 2;
		}
		else if (tage >= 60 && tage <= 90)
		{
			monat = 3;
		}
		else if (tage >= 91 && tage <= 120)
		{
			monat = 4;
		}
		else if (tage >= 121 && tage <= 151)
		{
			monat = 5;
		}
		else if (tage >= 152 && tage <= 181)
		{
			monat = 6;
		}
		else if (tage >= 182 && tage <= 212)
		{
			monat = 7;
		}
		else if (tage >= 213 && tage <= 243)
		{
			monat = 8;
		}
		else if (tage >= 244 && tage <= 273)
		{
			monat = 9;
		}
		else if (tage >= 274 && tage <= 304)
		{
			monat = 10;
		}
		else if (tage >= 306 && tage <= 334)
		{
			monat = 11;
		}
		else if (tage >= 336 && tage <= 365)
		{
			monat = 12;
		}
		else
		{
			printf("\n\nfehler!\n\n");
		}
	}
	else 
	{
		// mit 29 tagen im februar
		if (tage >= 32 && tage <= 60)
		{
			monat = 2;
		}
		else if (tage >= 61 && tage <= 91)
		{
			monat = 3;
		}
		else if (tage >= 91 && tage <= 121)
		{
			monat = 4;
		}
		else if (tage >= 121 && tage <= 152)
		{
			monat = 5;
		}
		else if (tage >= 152 && tage <= 182)
		{
			monat = 6;
		}
		else if (tage >= 182 && tage <= 213)
		{
			monat = 7;
		}
		else if (tage >= 213 && tage <= 244)
		{
			monat = 8;
		}
		else if (tage >= 244 && tage <= 274)
		{
			monat = 9;
		}
		else if (tage >= 274 && tage <= 305)
		{
			monat = 10;
		}
		else if (tage >= 306 && tage <= 335)
		{
			monat = 11;
		}
		else if (tage >= 336 && tage <= 366)
		{
			monat = 12;
		}
		else
		{
			printf("\n\nfehler!\n\n");
		}
	}
	return monat;
}

int jahr_funktion(int sek)
{
	int jahre = 0;
	int anzahl_schaltjahre = 0;
	int tage = 0;

	// 3600 * 24 damit man die anzahl der vergangenen jahre seit 1970 bekommt.
	tage = sek / 86400;
	// ab 1973 die schaltjahre bestimmen. +1 am ende weil ein schaltjahr da schon war. 1972 februar also.
	anzahl_schaltjahre = ((tage - 3 * 365 + 1) / (4 * 365 + 1)) + 1;
	// 31536000 für ein ganzes jahr. das + die tage in den schaltjahren
	jahre = sek / (31536000 + anzahl_schaltjahre * 86400);
	if ((1972 + jahre) % 100 == 0 && (1972 + jahre) % 400 != 0)
	{
		anzahl_schaltjahre--;
		jahre = sek / (31536000 + anzahl_schaltjahre * 86400);
	}
	return 1972 + jahre;
}