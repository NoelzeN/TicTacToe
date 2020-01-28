#include <stdio.h>
#include <string.h>

void spielfeldzeigen(char spielfeld[3][3]) {
	printf(" ");
	char xcoords[3] = {'A','B','C'};
	for(int i=0; i<3; i++) {
		printf("%c",xcoords[i]);
	}
	printf("\n");
	for(int i=0; i<3; i++) {
		printf("%d",i);
		for(int j=0; j<3; j++) {
			printf("%c",spielfeld[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}


int main() {
	printf("Willkommen zu Tic-Tac-Toe\n");
	char *spielfeld[3][3];
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			spielfeld[i][j]='o';
		}
	}
	spielfeldzeigen(spielfeld);
	spielzug(spielfeld,1);
	spielfeldzeigen(spielfeld);
}

void spielzug(char spielfeld[3][3], int spieler) {
	printf("Spieler %d, bitte waehle eine Koordinate fuer deinen Zug: ");
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
	x--;
	y--;
	char zeichen;
	if(spieler == 1) {
		zeichen = 'o';
	}
	else {
		zeichen = 'x';
	}
	spielfeld[x][y] = &zeichen;
}
