#ifndef SOUNDEX_H
#define SOUNDEX_H
 
#include "Soundex.h"
 
#include <stdio.h>
#include <ctype.h>
#include <string.h>  
 
char get_Soundex_Code(char c) {  
    static const char soundexCodes[] = {
        '0', '1', '2', '3', '0', '1', '2', '0', '0', '2', '2', '4', '5', '5', '0', '1', '2', '6', '2', '3', '0', '1', '0', '2', '0', '2'
    };
 
    c = toupper(c);
    if (c >= 'A' && c <= 'Z') {
        return soundexCodes[c - 'A'];
    }
    return '0';
}
 
char fetch_first_char(const char *name) {
    if (name[0] == '\0') return '\0';
    return toupper(name[0]);
}
 
void append_Soundex(char *soundex, char code, char *prevCode, int *length) {
    if (code != '0' && code != *prevCode) {
        soundex[(*length)++] = code;
        *prevCode = code;
    }
}
 
void initialize_Soundex(const char *name, char firstChar, char *soundex, int *length) {
    soundex[(*length)++] = firstChar;
    char secondex = get_Soundex_Code(name[1]);
    if (secondex != '0') {
        soundex[(*length)++] = secondex;
    }
}
 
void process_Soundex(const char *name, char firstChar, char *soundex, int *length) {
    int i;
    initialize_Soundex(name, firstChar, soundex, length);
    char prevCode = soundex[1];
    for (i = 2; name[i] != '\0' && *length < 4; ++i) {
        char code = get_Soundex_Code(name[i]);
        append_Soundex(soundex, code, &prevCode, length);
    }
}
 
void padding_Soundex(char *soundex) {
    while (strlen(soundex) < 4) {
        strcat(soundex, "0");
    }
}
 
void generate_Soundex(const char *name, char *soundex) {
    if (name[0] == '\0') {
        soundex[0] = '\0';
        return;
    }
 
    char firstChar = fetch_first_char(name);
    int length = 0;
    process_Soundex(name, firstChar, soundex, &length);
    soundex[length] = '\0'; // Null-terminate the soundex string
    padding_Soundex(soundex);
}
#endif // SOUNDEX_H
