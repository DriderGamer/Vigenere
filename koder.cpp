// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <wchar.h>
#include <ctype.h>

FILE *kodolt;
FILE *dekodolt;

char nyilt_szoveg[256];
char nyilt_szoveg_2[256];
char kulcsszo[5];
char kulcsszo_2[5];
char kodolt_szoveg[256];

int VigenereKodol(char* inputText, char* keyword, char* outputText)
{
	char vtabla_mem[26][26];
	FILE *vtabla;

	int x = 0;
	int y = 0;

	char keywordlong[256];

	int klength=0;
	vtabla = fopen("vtabla.dat", "r");

	for (klength = 0; klength < 6 && keyword[klength] != 0; klength++)
	{
	}

	int o = 0;
	for (o = 0; o < 256 && inputText[o] != '\0' && inputText[o] != 10;)
	{
		for (int k = 0; k < klength-1 && inputText[o] != '\0' && inputText[o] != 10; k++, o++)
		{
			keywordlong[o] = keyword[k];

		}
	}

	char scanchar;
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			fscanf(vtabla, "%c", &scanchar);
			vtabla_mem[i][j] = scanchar;
		}
		fscanf(vtabla, "%c", &scanchar);
	}


	for (int i = 0; i < 256 && inputText[i] != '\0' && inputText[i] != 10; i++)
	{
		x = inputText[i]-65;
		//printf("%d ",x);
		y = keywordlong[i]-65;
		//printf("%d ",y);
		outputText[i] = vtabla_mem[x][y];
	}
	fclose(vtabla);

	return 0;
}

int VigenereDekodol(char* inputText, char* keyword, char* outputText)
{
	char vtabla_mem[26][26];
	FILE *vtabla;

	int x = 0;
	int y = 0;

	char keywordlong[256];

	int klength = 0;
	vtabla = fopen("vtabla.dat", "r");

	for (klength = 0; klength < 6 && keyword[klength] != 0; klength++)
	{
	}

	int o = 0;
	for (o = 0; o < 256 && inputText[o] != '\0' && inputText[o] != 10;)
	{
		for (int k = 0; k < klength - 1 && inputText[o] != '\0' && inputText[o] != 10; k++, o++)
		{
			keywordlong[o] = keyword[k];

		}
	}

	char scanchar;
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			fscanf(vtabla, "%c", &scanchar);
			vtabla_mem[i][j] = scanchar;
		}
		fscanf(vtabla, "%c", &scanchar);
	}


	for (int i = 0; i < 256 && inputText[i] != '\0' && inputText[i] != 10; i++)
	{
		int kX = 0;

		y = keywordlong[i] - 65;

		for (kX = 0; kX < 26 && vtabla_mem[kX][y] != inputText[i] ; kX++)
		{

		}

		outputText[i] = kX + 65;
	}
	fclose(vtabla);

	return 0;
}

int convertText(char* inputText, char* outputText)
{
	int g = 0;
	for (int z = 0, g = 0; (z < 256) && (g < 256) && inputText[z] != '\0'; z++, g++)
	{
		switch (inputText[z])
		{
			case -75: outputText[g] = 'A'; break;	// Á
			case -96: outputText[g] = 'A'; break;	// á
			case -112: outputText[g] = 'E'; break;	// É
			case -126: outputText[g] = 'E'; break;	// é
			case -102: outputText[g] = 'U'; break;	// Ü
			case -127: outputText[g] = 'U'; break;	// ü
			case -21: outputText[g] = 'U'; break;	// Û
			case -5: outputText[g] = 'U'; break;	// û
			case -23: outputText[g] = 'U'; break;	// Ú
			case -93: outputText[g] = 'U'; break;	// ú
			case -32: outputText[g] = 'O'; break;	// Ó
			case -94: outputText[g] = 'O'; break;	// ó
			case -103: outputText[g] = 'O'; break;	// Ö
			case -108: outputText[g] = 'O'; break;	// ö
			case -118: outputText[g] = 'O'; break;	// Õ
			case -117: outputText[g] = 'O'; break;	// õ
			case -42: outputText[g] = 'I'; break;	// Í
			case -95: outputText[g] = 'I'; break;	// í
			case '?': g--; break;
			case '.': g--; break;
			case '!': g--; break;
			case ',': g--; break;
			case ' ': g--; break;
			default: outputText[g] = toupper(inputText[z]); break;
		}
	}

	return 0;
}

int main(int argc, char *argv[])
{
	char decision;
	if (argc >= 2) {
		decision = argv[1][0];
	}
	else
		decision = 'c';

	if (decision == 'c')
	{
		kodolt = fopen("kodolt.dat", "w");
		printf("Kerem a nyilt szoveget!\n");
	}
	else
	{
		dekodolt = fopen("dekodolt.dat", "w");
		printf("Kerem a kodolt szoveget!\n");
	}

	fgets(nyilt_szoveg, 256, stdin);

	convertText(nyilt_szoveg, nyilt_szoveg_2);

	printf("%s\n", nyilt_szoveg_2);

	printf("Kerem a kulcsszot!\n");
	fgets(kulcsszo, 7, stdin);

	convertText(kulcsszo, kulcsszo_2);

	printf("%s", kulcsszo_2);

	if (decision == 'c')
	{
		VigenereKodol(nyilt_szoveg_2, kulcsszo_2, kodolt_szoveg);
		printf("\nKodolt szoveg: %s", kodolt_szoveg);
		fprintf(kodolt, "%s", kodolt_szoveg);
		fclose(kodolt);
	}
	else
	{
		VigenereDekodol(nyilt_szoveg_2, kulcsszo_2, kodolt_szoveg);
		printf("\nDekodolt szoveg: %s", kodolt_szoveg);
		fprintf(dekodolt, "%s", kodolt_szoveg);
		fclose(dekodolt);
	}
	
	getchar();
    return 0;
}

