#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Prototypen
void spielfeldzeigen(char spielfeld[3][3]);
bool spielzug(char spielfeld[3][3], int spieler);
bool checkEnd(char spielfeld[3][3]);

// Global Variables
char spieler1[30];
char spieler2[30];
char zeichenS1;
char zeichenS2;
int spielerAmZug = 0;
bool gameRunning = true;

int main() {
  printf("Willkommen zu Tic-Tac-Toe\n");
  char spielfeld[3][3];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      spielfeld[i][j] = ' ';
    }
  }
  char buf1[1024] = "";
  char buf2[1024] = "";
  printf("Spieler 1, bitte geben sie ihren Namen ein (Max. 30 Buchstaben): ");
  scanf("%99s", &spieler1[0]);
  printf("Spieler 1, bitte geben sie ihr Zeichen ein (Nur ein Buchstabe): ");
  scanf("%99s", &buf1[0]);
  if (strlen(buf1) > 0) {
    zeichenS1 = buf1[0];
  }
  printf("Spieler 2, bitte geben sie ihren Namen ein (Max. 30 Buchstaben): ");
  scanf("%99s", &spieler2[0]);
  printf("Spieler 2, bitte geben sie ihr Zeichen ein (Nur ein Buchstabe): ");
  scanf("%99s", &buf2[0]);
  if (strlen(buf2) > 0) {
    zeichenS2 = buf2[0];
  }
  printf("Lasset die Spiele Beginnen. ");
  srand(time(NULL));
  if ((rand() % ((99 + 1) - 1)) + 1 > 50) {
    spielerAmZug = 1;
    printf("Spieler %s beginnt!\n", spieler1);
  } else {
    spielerAmZug = 2;
    printf("Spieler %s beginnt!\n", spieler2);
  }

  while (gameRunning) {
    bool zugerfolgreich = false;
    if (spielerAmZug == 1) {
      zugerfolgreich = spielzug(spielfeld, 1);
    } else if (spielerAmZug == 2) {
      zugerfolgreich = spielzug(spielfeld, 2);
    } else {
      printf("Spieler am Zug: %d - Irgendwas stimmt hier nicht", spielerAmZug);
      return 42;
    }
    if (zugerfolgreich) {
      spielfeldzeigen(spielfeld);
    }
	if(checkEnd(spielfeld)) {
		//TODO: Spiel ist zuende. Sieger Kueren
		 
	}
  }
}

void spielfeldzeigen(char spielfeld[3][3]) {
  printf(" ");
  char xcoords[3] = {'A', 'B', 'C'};
  for (int i = 0; i < 3; i++) {
    printf("%c", xcoords[i]);
  }
  printf("\n");
  for (int i = 0; i < 3; i++) {
    printf("%d", i + 1);
    for (int j = 0; j < 3; j++) {
      printf("%c", spielfeld[i][j]);
    }
    printf("\n");
  }
  printf("\n\n");
}

bool spielzug(char spielfeld[3][3], int spieler) {
  if (spieler == 1) {
    printf("Spieler %s, bitte waehle eine Koordinate fuer deinen Zug: ",
           spieler1);
  } else {
    printf("Spieler %s, bitte waehle eine Koordinate fuer deinen Zug: ",
           spieler2);
  }
  char coord[2];
  scanf("%s", &coord);
  int x;
  int y;
  y = atoi(&coord[1]);
  if (coord[0] == 'A' || coord[0] == 'a') {
    x = 1;
  } else if (coord[0] == 'B' || coord[0] == 'b') {
    x = 2;
  } else if (coord[0] == 'C' || coord[0] == 'C') {
    x = 3;
  } else {
    printf("Invalid x-Input %c. Aborting Move", coord[0]);
    return false;
  }
  if (y > 3 || y < 1) {
    printf("Invalid y-Input %c. Aborting Move", coord[1]);
    return false;
  }
  x--;
  y--;
  if (spielfeld[x][y] != ' ') {
    printf("Feld %d|%d ist schon besetzt. Bitte waehle ein anderes Feld fuer "
           "deinen Zug!\n",
           x + 1, y + 1);
    return false;
  }
  char zeichen;
  if (spieler == 1) {
    spielfeld[x][y] = zeichenS1;
  } else if (spieler == 2) {
    spielfeld[x][y] = zeichenS2;
  } else {
    printf("Spieler am Zug: %d - Irgendwas ist hier falsch!", spieler);
    return false;
  }
  spielerAmZug = (spielerAmZug % 2) + 1;
  return true;
}

bool checkEnd(char spielfeld[3][3]) {}