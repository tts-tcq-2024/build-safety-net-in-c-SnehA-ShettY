#ifndef SOUNDEX_H
#define SOUNDEX_H

#include <ctype.h>
#include <string.h>

char getSoundexCode(char c) {
    c = toupper(c);
    const char *groups = "BFPVCGJKQSXZDTLMNR";
    const char *codes  = "111122222222334556";
    
    const char *pos = strchr(groups, c);
    return pos ? codes[pos - groups] : '0';
}

void generateSoundex(const char *name, char *soundex) {
    if (!name || !*name) {
        soundex[0] = '\0';
        return;
    }

    soundex[0] = toupper(name[0]);
    int sIndex = 1;

    for (int i = 1; name[i] != '\0' && sIndex < 4; ++i) {
        char code = getSoundexCode(name[i]);
        if (code != '0' && code != soundex[sIndex - 1]) {
            soundex[sIndex++] = code;
        }
    }

    while (sIndex < 4) {
        soundex[sIndex++] = '0';
    }

    soundex[4] = '\0';
}

#endif // SOUNDEX_H
