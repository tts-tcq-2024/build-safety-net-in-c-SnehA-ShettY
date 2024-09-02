#include <stdio.h>
#include <ctype.h>
#include <string.h>  

char getSoundexCode(char c) {  
    static const char soundexCodes[] = {
        '0', '1', '2', '3', '0', '1', '2', '0', '0', '2', '2', '4', '5', '5', '0', '1', '2', '6', '2', '3', '0', '1', '0', '2', '0', '2'
    };

    c = toupper(c);
    if (c >= 'A' && c <= 'Z') {
        return soundexCodes[c - 'A'];
    }
    return '0';
}

char fetch_firstchar(const char *name) {
    if (name[0] == '\0') return '\0';
    return toupper(name[0]);
}

void appendSoundex(char *soundex, char code, char *prevCode, int *length) {
    if (code != '0' && code != *prevCode) {
        soundex[(*length)++] = code;
        *prevCode = code;
    }
}

void initializeSoundex(const char *name, char firstChar, char *soundex, int *length) {
    soundex[(*length)++] = firstChar;
    char secondex = getSoundexCode(name[1]);
    if (secondex != '0') {
        soundex[(*length)++] = secondex;
    }
}

void processSoundex(const char *name, char firstChar, char *soundex, int *length) {
    int i;
    initializeSoundex(name, firstChar, soundex, length);
    char prevCode = soundex[1];
    for (i = 2; name[i] != '\0' && *length < 4; ++i) {
        char code = getSoundexCode(name[i]);
        appendSoundex(soundex, code, &prevCode, length);
    }
}

void paddingSoundex(char *soundex) {
    while (strlen(soundex) < 4) {
        strcat(soundex, "0");
    }
}

void generateSoundex(const char *name, char *soundex) {
    if (name[0] == '\0') {
        soundex[0] = '\0';
        return;
    }

    char firstChar = fetch_firstchar(name);
    int length = 0;
    processSoundex(name, firstChar, soundex, &length);
    soundex[length] = '\0'; // Null-terminate the soundex string
    paddingSoundex(soundex);
}

int main() {
    char name[] = "Example";
    char soundex[5]; // Enough space for 4 characters plus null terminator

    generateSoundex(name, soundex);
    printf("Soundex of %s: %s\n", name, soundex);

    return 0;
}
