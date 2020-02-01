#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Prototypen
void spielfeldzeigen(char spielfeld[3][3]);
bool spielzug(char spielfeld[3][3], int spieler);
int checkEnd(char spielfeld[3][3]);
void spielfeldInitialisieren();
void zweispielersiel();

// Global Variables
char spieler1[30];
char spieler2[30];
char zeichenS1;
char zeichenS2;
int spielerAmZug = 0;
int gesamtZuege = 0;
bool gameRunning = true;
char spielfeld[3][3];

int main() {
      printf("Willkommen zu Tic-Tac-Toe\n");
  while (true) {
    printf(
        "Wenn sie wissen wollen, wie Tic-Tac-Toe funktioniert, googlen sie\n");
    printf(
        "Wenn sie ein 2-Spieler Spiel starten wollen, geben sie \'s\' ein.\n");
    printf("Wenn sie gegen den Computer spielen wollen, geben sie \'c\' ein\n");
    printf("Wenn sie das spiel beenden wollen, geben sie \'e\' ein\n");
    char buf0[1024] = "";
    scanf("%99s", &buf0[0]);
    if (strlen(buf0) > 0) {
      char auswahl = buf0[0];
      if (auswahl == 's') {
        zweispielersiel();
      } else if (auswahl == 'c') {
        // TODO: Kommt noch
      } else if (auswahl == 'e') {
        printf("Bye Bye\n");
        return 0;
      } else {
        printf("Unbekannte Eingabe %c. Beende.\n", auswahl);
        return 0;
      }
    } else {
      printf("Keine Eingabe gefunden. Beende. Eingabe: %s\n", buf0);
      return 0;
    }
  }
}

void zweispielersiel() {
  spielfeldInitialisieren();
  // Spieler Name und Zeichen einlesen
  char buf1[1024] = "";
  char buf2[1024] = "";
  printf("Spieler 1, bitte geben sie ihren Namen ein (Max. 30 Buchstaben): ");
  scanf("%99s", &spieler1[0]);
  printf("Spieler 1, bitte geben sie ihr Zeichen ein (Nur ein Buchstabe): ");
  scanf("%99s", &buf1[0]);
  // TODO: String eingaben gegen Escape Characters absichern
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
  // Auswuerfeln welcher Spieler anfaengt
  printf("Lasset die Spiele Beginnen. ");
  srand(time(NULL));
  if ((rand() % ((99 + 1) - 1)) + 1 > 50) {
    spielerAmZug = 1;
    printf("Spieler %s beginnt!\n", spieler1);
  } else {
    spielerAmZug = 2;
    printf("Spieler %s beginnt!\n", spieler2);
  }

  // Solange kein Gewinner feststeht abwechselnd Spielzuege taetigen
  int winner = 0;
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
    winner = checkEnd(spielfeld);
    if (winner > 0) {
      if (winner == 1) {
        printf("Glueckwunsch %s, du hast gewonnen\n", spieler1);
      } else if (winner == 2) {
        printf("Glueckwunsch %s, du hast gewonnen\n", spieler2);
      }
      gameRunning = false;
    } else {
      if (gesamtZuege == 9) {
        printf("Unentschiedenn");
        gameRunning = false;
      }
    }
  }
}

void spielfeldInitialisieren() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      spielfeld[i][j] = ' ';
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
    printf("Spieler %s, bitte waehle eine Koordinate fuer deinen Zug (Zeichen: %c): ",
           spieler1, zeichenS1);
  } else {
    printf("Spieler %s, bitte waehle eine Koordinate fuer deinen Zug (Zeiche: %c): ",
           spieler2, zeichenS2);
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
  if (spielfeld[y][x] != ' ') {
    printf("Feld %d|%d ist schon besetzt. Bitte waehle ein anderes Feld fuer "
           "deinen Zug!\n",
           x + 1, y + 1);
    return false;
  }
  char zeichen;
  if (spieler == 1) {
    spielfeld[y][x] = zeichenS1;
  } else if (spieler == 2) {
    spielfeld[y][x] = zeichenS2;
  } else {
    printf("Spieler am Zug: %d - Irgendwas ist hier falsch!", spieler);
    return false;
  }
  spielerAmZug = (spielerAmZug % 2) + 1;
  gesamtZuege++;
  return true;
}

int checkEnd(char spielfeld[3][3]) {
  if ((spielfeld[0][0] == spielfeld[0][1] &&
       spielfeld[0][0] == spielfeld[0][2]) ||
      (spielfeld[0][0] == spielfeld[1][0] &&
       spielfeld[0][0] == spielfeld[2][0]) ||
      (spielfeld[0][0] == spielfeld[1][1] &&
       spielfeld[0][0] == spielfeld[2][2])) {
    if (spielfeld[0][0] == zeichenS1) {
      // Spieler 1 gewinnt
      return 1;
    } else if (spielfeld[0][0] == zeichenS2) {
      // Spieler 2 gewinnt
      return 2;
    } else if (spielfeld[0][0] == ' ') {
      return 0;
    } else {
      printf("Unbekannter Gewinner: %c\n", spielfeld[0][0]);
    }
  } else if ((spielfeld[0][1] == spielfeld[1][1] &&
              spielfeld[0][1] == spielfeld[2][1]) ||
             (spielfeld[1][0] == spielfeld[1][1] &&
              spielfeld[1][0] == spielfeld[1][2]) ||
             (spielfeld[0][2] == spielfeld[1][1] &&
              spielfeld[0][2] == spielfeld[2][0])) {
    if (spielfeld[1][1] == zeichenS1) {
      // Spieler 1 gewinnt
      return 1;
    } else if (spielfeld[1][1] == zeichenS2) {
      // Spieler 2 gewinnt
      return 2;
    } else if (spielfeld[1][1] == ' ') {
      return 0;
    } else {
      printf("Unbekannter Gewinner: %c\n", spielfeld[1][1]);
    }
  } else if ((spielfeld[2][0] == spielfeld[2][1] &&
              spielfeld[2][0] == spielfeld[2][2]) ||
             (spielfeld[0][2] == spielfeld[1][2] &&
              spielfeld[0][2] == spielfeld[2][2])) {
    if (spielfeld[2][2] == zeichenS1) {
      // Spieler 1 gewinnt
      return 1;
    } else if (spielfeld[2][2] == zeichenS2) {
      // Spieler 2 gewinnt
      return 2;
    } else if (spielfeld[2][2] == ' ') {
      return 0;
    } else {
      printf("Unbekannter Gewinner: %c\n", spielfeld[2][2]);
    }
  } else {
    // Kein Gewinner bisher
    return 0;
  }
}