#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char spieler1[30];
char spieler2[30];
char zeichenS1;
char zeichenS2;

int main() {
	printf("Willkommen zu Tic-Tac-Toe\n");
	char spielfeld[3][3];
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			spielfeld[i][j]=' ';
		}
	}
	printf("Spieler 1, bitte geben sie ihren Namen ein: ");
	scanf("%99s", &spieler1[0]);
	printf("Spieler 1, bitte geben sie ihr Zeichen ein: ");
	scanf(" %c", &zeichenS1);
	printf("Spieler 2, bitte geben sie ihren Namen ein: ");
	scanf("%99s", &spieler2[0]);
	printf("Spieler 2, bitte geben sie ihr Zeichen ein: ");
	scanf(" %c", &zeichenS2);
	printf("Lasset die Spiele Beginnen. ");
	int spielerAmZug = 0;
	srand (time (NULL));
	if((rand () % ((99 + 1) - 1)) + 1 > 50) {
		spielerAmZug=1;
		printf("Spieler %s beginnt!\n",spieler1);
	} else {
		spielerAmZug=2;
		printf("Spieler %s beginnt!\n",spieler2);
	}

	
	spielfeldzeigen(spielfeld);

	spielzug(spielfeld,1);
	spielzug(spielfeld,2);
	spielzug(spielfeld,1);	

	spielfeldzeigen(spielfeld);
}

void spielfeldzeigen(char spielfeld[3][3]) {
	printf(" ");
	char xcoords[3] = {'A','B','C'};
	for(int i=0; i<3; i++) {
		printf("%c",xcoords[i]);
	}
	printf("\n");
	for(int i=0; i<3; i++) {
		printf("%d",i+1);
		for(int j=0; j<3; j++) {
			printf("%c",spielfeld[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

void spielzug(char spielfeld[3][3], int spieler) {
	if(spieler==1) {
		printf("Spieler %s, bitte waehle eine Koordinate fuer deinen Zug: ",spieler1);
	} else {
		printf("Spieler %s, bitte waehle eine Koordinate fuer deinen Zug: ",spieler2);
	}
	char coord[2];
	scanf("%s",&coord);
	int x;
	int y;
	y = atoi(&coord[1]);
	if(coord[0] == 'A' || coord[0] == 'a') {
		x = 1;
	}
	else if(coord[0] == 'B' || coord[0] == 'b') {
		x = 2;
	}
	else if(coord[0] == 'C' || coord[0] == 'C') {
		x =  3;
	}
	else {
		printf("Invalid x-Input %c. Aborting Move",coord[0]);
		return 0;
	}
	if(y>3 || y<1) {
		printf("Invalid y-Input %c. Aborting Move",coord[1]);
		return 0;
	}
	x--;
	y--;
	char zeichen;
	if(spieler == 1) {
		zeichen = zeichenS1;
	}
	else {
		zeichen = zeichenS2;
	}
	spielfeld[x][y] = zeichen;
}
