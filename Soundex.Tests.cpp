#include <gtest/gtest.h>
#include "Soundex.h"

// Test getSoundexCode function for MCDC coverage
TEST(SoundexMCDCTest, GetSoundexCode) {
    // Condition 1: c >= 'A'
    // Condition 2: c <= 'Z'
    // True branch: Both conditions are true
    EXPECT_EQ(getSoundexCode('A'), '0'); // True, True
    EXPECT_EQ(getSoundexCode('Z'), '2'); // True, True

    // False branch: Either condition is false
    EXPECT_EQ(getSoundexCode('1'), '0'); // False, False
    EXPECT_EQ(getSoundexCode('['), '0'); // False, True (Non-alphabet character)
    EXPECT_EQ(getSoundexCode('@'), '0'); // True, False
}

// Test fetch_firstchar function for MCDC coverage
TEST(SoundexMCDCTest, FetchFirstChar) {
    // Condition 1: name[0] == '\0'
    // True branch: Name is empty
    EXPECT_EQ(fetch_firstchar(""), '\0'); // True

    // False branch: Name is not empty
    EXPECT_EQ(fetch_firstchar("Test"), 'T'); // False
}

// Test appendSoundex function for MCDC coverage
TEST(SoundexMCDCTest, AppendSoundex) {
    char soundex[5] = "A";
    char prevCode = '1';
    int length = 1;

    // Condition 1: code != '0'
    // Condition 2: code != *prevCode

    // Both conditions are true
    appendSoundex(soundex, '2', &prevCode, &length);
    EXPECT_STREQ(soundex, "A2"); // True, True
    EXPECT_EQ(length, 2);

    // First condition false, second true
    appendSoundex(soundex, '0', &prevCode, &length);
    EXPECT_STREQ(soundex, "A2"); // False, True
    EXPECT_EQ(length, 2);

    // First condition true, second false
    appendSoundex(soundex, '2', &prevCode, &length);
    EXPECT_STREQ(soundex, "A2"); // True, False
    EXPECT_EQ(length, 2);
}

// Test initializeSoundex function for MCDC coverage
TEST(SoundexMCDCTest, InitializeSoundex) {
    char soundex[5] = "";
    int length = 0;

    // Condition: secondex != '0'
    // True branch: Code is not '0'
    initializeSoundex("Smith", 'S', soundex, &length);
    EXPECT_STREQ(soundex, "S5"); // True

    // False branch: Code is '0'
    initializeSoundex("Ada", 'A', soundex, &length);
    EXPECT_STREQ(soundex, "A"); // False
}

// Test processSoundex function for MCDC coverage
TEST(SoundexMCDCTest, ProcessSoundex) {
    char soundex[5] = "";
    int length = 0;

    // Conditions:
    // - name[i] != '\0'
    // - *length < 4

    // Both conditions are true
    processSoundex("Smith", 'S', soundex, &length);
    EXPECT_STREQ(soundex, "S53"); // True, True

    // First condition true, second false (processed name with 3 chars)
    length = 3;
    processSoundex("Smith", 'S', soundex, &length);
    EXPECT_STREQ(soundex, "S530"); // True, False

    // First condition false (short name), second true
    length = 0;
    processSoundex("Li", 'L', soundex, &length);
    EXPECT_STREQ(soundex, "L3"); // False, True
}

// Test paddingSoundex function for MCDC coverage
TEST(SoundexMCDCTest, PaddingSoundex) {
    char soundex[5] = "S5";

    // Condition: strlen(soundex) < 4
    // True branch: Length < 4
    paddingSoundex(soundex);
    EXPECT_STREQ(soundex, "S500"); // True

    // False branch: Length == 4
    strcpy(soundex, "S530");
    paddingSoundex(soundex);
    EXPECT_STREQ(soundex, "S530"); // False
}

// Test generateSoundex function for MCDC coverage
TEST(SoundexMCDCTest, GenerateSoundex) {
    char soundex[5] = "";

    // Condition 1: name[0] == '\0'
    // Condition 2: length < 4 (from processSoundex)

    // Test empty string
    generateSoundex("", soundex);
    EXPECT_STREQ(soundex, ""); // True (Condition 1)

    // Test typical name
    generateSoundex("Smith", soundex);
    EXPECT_STREQ(soundex, "S530"); // False, True (Condition 2)

    // Test name requiring padding
    generateSoundex("Li", soundex);
    EXPECT_STREQ(soundex, "L300"); // False, True (Condition 2)

    // Test name with repeating Soundex codes
    generateSoundex("Bbbb", soundex);
    EXPECT_STREQ(soundex, "B100"); // False, True (Condition 2)
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
