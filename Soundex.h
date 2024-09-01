#ifndef SOUNDEX_H
#define SOUNDEX_H

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Define the maximum length for Soundex code
#define SOUND_EX_LENGTH 4

// Get the Soundex code for a given character
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

// Fetch the first character of a given string
char fetch_firstchar(const char *name) {
    if (name[0] == '\0') return '\0';
    return toupper(name[0]);
}

// Append Soundex code to the result string
void appendSoundex(char *soundex, char code, char *prevCode, int *sIndex) {
    if (code != '0' && code != *prevCode) {
        soundex[(*sIndex)++] = code;
        *prevCode = code;
    }
}

// Initialize the Soundex string with the first character
void initializeSoundex(const char *name, char firstChar, char *soundex) {
    soundex[0] = firstChar;
    char secondex = getSoundexCode(name[1]);
    if (secondex != '0') {
        soundex[1] = secondex;
    }
    soundex[2] = '\0';
}

// Process the Soundex code from the name
void processSoundex(const char *name, char firstChar, char *soundex) {
    initializeSoundex(name, firstChar, soundex);
    char prevCode = soundex[1];
    int sIndex = (prevCode != '\0') ? 2 : 1;

    for (size_t i = 2; i < strlen(name) && sIndex < SOUND_EX_LENGTH; ++i) {
        char code = getSoundexCode(name[i]);
        appendSoundex(soundex, code, &prevCode, &sIndex);
    }
    soundex[sIndex] = '\0';
}

// Pad the Soundex string to the required length
void paddingSoundex(char *soundex) {
    size_t length = strlen(soundex);
    if (length < SOUND_EX_LENGTH) {
        memset(soundex + length, '0', SOUND_EX_LENGTH - length);
        soundex[SOUND_EX_LENGTH] = '\0';
    }
}

// Generate the Soundex code for a given name
void generateSoundex(const char *name, char *soundex) {
    if (name[0] == '\0') {
        soundex[0] = '\0';
        return;
    }

    char firstChar = fetch_firstchar(name);
    processSoundex(name, firstChar, soundex);
    paddingSoundex(soundex);
}

#endif // SOUNDEX_H
