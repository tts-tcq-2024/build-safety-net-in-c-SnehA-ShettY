#include <gtest/gtest.h>
#include <cstring>
#include "Soundex.h"


// Test for getSoundexCode
TEST(SoundexTest, GetSoundexCode) {
    EXPECT_EQ(getSoundexCode('A'), '0');
    EXPECT_EQ(getSoundexCode('B'), '1');
    EXPECT_EQ(getSoundexCode('C'), '2');
    EXPECT_EQ(getSoundexCode('D'), '3');
    EXPECT_EQ(getSoundexCode('E'), '0');
    EXPECT_EQ(getSoundexCode('F'), '1');
    EXPECT_EQ(getSoundexCode('G'), '2');
    EXPECT_EQ(getSoundexCode('Z'), '2');
    EXPECT_EQ(getSoundexCode(' '), '0'); // non-alphabetic characters
}

// Test for fetch_firstchar
TEST(SoundexTest, FetchFirstChar) {
    EXPECT_EQ(fetch_firstchar("example"), 'E');
    EXPECT_EQ(fetch_firstchar("a"), 'A');
    EXPECT_EQ(fetch_firstchar(""), '\0'); // Empty string
}

// Test for appendSoundex
TEST(SoundexTest, AppendSoundex) {
    char soundex[5] = "A";
    char prevCode = 'A';
    int length = 1;

    appendSoundex(soundex, '1', &prevCode, &length);
    EXPECT_STREQ(soundex, "A1");
    
    appendSoundex(soundex, '1', &prevCode, &length);
    EXPECT_STREQ(soundex, "A1"); // Should not append duplicate code

    appendSoundex(soundex, '2', &prevCode, &length);
    EXPECT_STREQ(soundex, "A12");
}

// Test for initializeSoundex
TEST(SoundexTest, InitializeSoundex) {
    char soundex[5] = "";
    int length = 0;

    initializeSoundex("example", 'E', soundex, &length);
    EXPECT_STREQ(soundex, "E0"); // Example has 'E' and '0' for second character
}

// Test for processSoundex
TEST(SoundexTest, ProcessSoundex) {
    char soundex[5] = "";
    int length = 0;

    processSoundex("example", 'E', soundex, &length);
    EXPECT_STREQ(soundex, "E0"); // Adjust according to the expected result
}

// Test for paddingSoundex
TEST(SoundexTest, PaddingSoundex) {
    char soundex[5] = "A";
    paddingSoundex(soundex);
    EXPECT_STREQ(soundex, "A000");

    char soundex2[5] = "A12";
    paddingSoundex(soundex2);
    EXPECT_STREQ(soundex2, "A120");
}

// Test for generateSoundex
TEST(SoundexTest, GenerateSoundex) {
    char soundex[5];

    generateSoundex("Singh", soundex);
    EXPECT_STREQ(soundex, "S520");

    generateSoundex("Kumar", soundex);
    EXPECT_STREQ(soundex, "K560");

    generateSoundex("Sharma", soundex);
    EXPECT_STREQ(soundex, "S650");

    generateSoundex("Patel", soundex);
    EXPECT_STREQ(soundex, "P340");

    generateSoundex("Gupta", soundex);
    EXPECT_STREQ(soundex, "G130");

    generateSoundex("", soundex);
    EXPECT_STREQ(soundex, "");
}

