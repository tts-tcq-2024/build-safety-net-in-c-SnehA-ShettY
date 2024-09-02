#include <gtest/gtest.h>
#include <cstring>
#include "Soundex.h"

// Test getSoundexCode function
TEST(SoundexTest, GetSoundexCode) {
    EXPECT_EQ(getSoundexCode('A'), '0');
    EXPECT_EQ(getSoundexCode('B'), '1');
    EXPECT_EQ(getSoundexCode('C'), '2');
    EXPECT_EQ(getSoundexCode('D'), '3');
    EXPECT_EQ(getSoundexCode('E'), '0');
    EXPECT_EQ(getSoundexCode('F'), '1');
    EXPECT_EQ(getSoundexCode('G'), '2');
    EXPECT_EQ(getSoundexCode('H'), '0');
    EXPECT_EQ(getSoundexCode('Z'), '2');
}

// Test fetch_firstchar function
TEST(SoundexTest, FetchFirstChar) {
    EXPECT_EQ(fetch_firstchar("Example"), 'E');
    EXPECT_EQ(fetch_firstchar("soundex"), 'S');
    EXPECT_EQ(fetch_firstchar(""), '\0');
}

// Test appendSoundex function
TEST(SoundexTest, AppendSoundex) {
    char soundex[5] = "A";
    char prevCode = '1';
    int length = 1;

    appendSoundex(soundex, '2', &prevCode, &length);
    EXPECT_STREQ(soundex, "A2");
    EXPECT_EQ(length, 2);

    appendSoundex(soundex, '3', &prevCode, &length);
    EXPECT_STREQ(soundex, "A23");
    EXPECT_EQ(length, 3);

    appendSoundex(soundex, '3', &prevCode, &length);  // Should not append same code
    EXPECT_STREQ(soundex, "A23");
    EXPECT_EQ(length, 3);
}

// Test initializeSoundex function
TEST(SoundexTest, InitializeSoundex) {
    char soundex[5] = "";
    int length = 0;

    initializeSoundex("Smith", 'S', soundex, &length);
    EXPECT_STREQ(soundex, "S5");
    EXPECT_EQ(length, 2);
}

// Test processSoundex function
TEST(SoundexTest, ProcessSoundex) {
    char soundex[5] = "";
    int length = 0;

    processSoundex("Smith", 'S', soundex, &length);
    EXPECT_STREQ(soundex, "S53");
    EXPECT_EQ(length, 3);
}

// Test paddingSoundex function
TEST(SoundexTest, PaddingSoundex) {
    char soundex[5] = "S5";

    paddingSoundex(soundex);
    EXPECT_STREQ(soundex, "S500");

    strcpy(soundex, "S53");
    paddingSoundex(soundex);
    EXPECT_STREQ(soundex, "S530");

    strcpy(soundex, "S530");
    paddingSoundex(soundex);
    EXPECT_STREQ(soundex, "S530");
}

