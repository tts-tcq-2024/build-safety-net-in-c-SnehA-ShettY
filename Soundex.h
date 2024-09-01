#ifndef SOUNDEX_H
#define SOUNDEX_H

#include <ctype.h>
#include <string.h>

char getSoundexCode(char c) {
    c = toupper(c);
    if (c == 'B' || c == 'F' || c == 'P' || c == 'V') return '1';
    if (c == 'C' || c == 'G' || c == 'J' || c == 'K' || c == 'Q' || c == 'S' || c == 'X' || c == 'Z') return '2';
    if (c == 'D' || c == 'T') return '3';
    if (c == 'L') return '4';
    if (c == 'M' || c == 'N') return '5';
    if (c == 'R') return '6';
    return '0'; // For A, E, I, O, U, H, W, Y
}

void generateSoundex(const char *name, char *soundex) {
    if (!name || !*name) {
        soundex[0] = '\0';
        return;
    }

    soundex[0] = toupper(name[0]);
    int sIndex = 1;
    char prevCode = '0';

    for (int i = 1; name[i] != '\0' && sIndex < 4; ++i) {
        char code = getSoundexCode(name[i]);
        if (code != '0' && code != prevCode) {
            soundex[sIndex++] = code;
            prevCode = code;
        }
    }

    while (sIndex < 4) {
        soundex[sIndex++] = '0';
    }

    soundex[4] = '\0';
}

#endif // SOUNDEX_H
