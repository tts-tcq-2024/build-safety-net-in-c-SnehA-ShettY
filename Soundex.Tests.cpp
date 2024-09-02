#include <gtest/gtest.h>
#include "Soundex.h"

// Test getSoundexCode function for all branches
TEST(SoundexTest, GetSoundexCode) {
    // Test valid letters
    EXPECT_EQ(getSoundexCode('A'), '0');
    EXPECT_EQ(getSoundexCode('B'), '1');
    EXPECT_EQ(getSoundexCode('C'), '2');
    EXPECT_EQ(getSoundexCode('Z'), '2');

    // Test lowercase letters to check conversion to uppercase
    EXPECT_EQ(getSoundexCode('a'), '0');
    EXPECT_EQ(getSoundexCode('b'), '1');

    // Test non-alphabet characters
    EXPECT_EQ(getSoundexCode('1'), '0');
    EXPECT_EQ(getSoundexCode('@'), '0');
    EXPECT_EQ(getSoundexCode(' '), '0');
}

// Test fetch_firstchar function
TEST(SoundexTest, FetchFirstChar) {
    EXPECT_EQ(fetch_firstchar("Example"), 'E');
    EXPECT_EQ(fetch_firstchar("soundex"), 'S');
    EXPECT_EQ(fetch_firstchar(""), '\0');
}

// Test appendSoundex function for all branches
TEST(SoundexTest, AppendSoundex) {
    char soundex[5] = "A";
    char prevCode = '1';
    int length = 1;

    // Test appending different code
    appendSoundex(soundex, '2', &prevCode, &length);
    EXPECT_STREQ(soundex, "A2");
    EXPECT_EQ(length, 2);

    // Test appending the same code (shouldn't append)
    appendSoundex(soundex, '2', &prevCode, &length);
    EXPECT_STREQ(soundex, "A2");
    EXPECT_EQ(length, 2);

    // Test appending '0' code (shouldn't append)
    appendSoundex(soundex, '0', &prevCode, &length);
    EXPECT_STREQ(soundex, "A2");
    EXPECT_EQ(length, 2);

    // Test appending another different code
    appendSoundex(soundex, '3', &prevCode, &length);
    EXPECT_STREQ(soundex, "A23");
    EXPECT_EQ(length, 3);
}

// Test initializeSoundex function
TEST(SoundexTest, InitializeSoundex) {
    char soundex[5] = "";
    int length = 0;

    // Test with valid name
    initializeSoundex("Smith", 'S', soundex, &length);
    EXPECT_STREQ(soundex, "S5");
    EXPECT_EQ(length, 2);

    // Test with name starting with 'A' (Soundex '0' should not append)
    initializeSoundex("Adams", 'A', soundex, &length);
    EXPECT_STREQ(soundex, "A");
    EXPECT_EQ(length, 1);
}

// Test processSoundex function for full coverage
TEST(SoundexTest, ProcessSoundex) {
    char soundex[5] = "";
    int length = 0;

    // Test with a typical name
    processSoundex("Smith", 'S', soundex, &length);
    EXPECT_STREQ(soundex, "S53");
    EXPECT_EQ(length, 3);

    // Test with a short name that requires padding
    processSoundex("Li", 'L', soundex, &length);
    EXPECT_STREQ(soundex, "L3");
    EXPECT_EQ(length, 2);

    // Test with a name where all letters are the same Soundex code
    processSoundex("Bbbb", 'B', soundex, &length);
    EXPECT_STREQ(soundex, "B1");
    EXPECT_EQ(length, 2);
}

// Test paddingSoundex function for full coverage
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

    strcpy(soundex, "S5");
    paddingSoundex(soundex);
    EXPECT_STREQ(soundex, "S500");
}

// Test generateSoundex function for all scenarios
TEST(SoundexTest, GenerateSoundex) {
    char soundex[5] = "";

    // Test typical names
    generateSoundex("Smith", soundex);
    EXPECT_STREQ(soundex, "S530");

    generateSoundex("Smythe", soundex);
    EXPECT_STREQ(soundex, "S530");

    // Test name requiring padding
    generateSoundex("Li", soundex);
    EXPECT_STREQ(soundex, "L300");

    // Test name with non-alphabet characters
    generateSoundex("O'Brien", soundex);
    EXPECT_STREQ(soundex, "O165");

    // Test name starting with 'A' and checking padding
    generateSoundex("Ashcraft", soundex);
    EXPECT_STREQ(soundex, "A261");

    // Test name with repeating Soundex codes
    generateSoundex("Tymczak", soundex);
    EXPECT_STREQ(soundex, "T522");

    // Test empty string
    generateSoundex("", soundex);
    EXPECT_STREQ(soundex, "");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
