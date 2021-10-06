#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Fonction d'initialisation avant l'éxécution du main (mémoire, ...).
 */
int start2() {
    
}

/**
 * Affichage de nombre positifs ou négatifs ou zéro sur le terminal,
 * puis fait un retour à la ligne.
 */
void printNb(int n) { // Nb positifs et zéro pour l'instant
    if (n != 0) {
        int c;
        c = n % 10;
        n = n/10;
        printNb(n);
        putchar(c + '0');
    } else {
        putchar('0');
    }
}

/**
 * Lit un nombre positif dans le terminal.
 */
int readNb() {
    int c;
    int nb = NULL;
    int digitsCounter = 0;
    while((c = getchar()) &&  c <= '0' && c >= '9') {
        digitsCounter++;
        int digit = c - '0';
        nb += digit*pow((float)10, (float)digit);
    }
    return nb;
}
