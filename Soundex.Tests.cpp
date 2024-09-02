#include <gtest/gtest.h>
#include "Soundex.h"  
#include <assert.h>

// Test for getSoundexCode (MCDC: Condition testing for character range)
TEST(SoundexTest, GetSoundexCode) {
    // Test conditions where c is within 'A'-'Z'
    EXPECT_EQ(getSoundexCode('A'), '0'); // Test 'A'
    EXPECT_EQ(getSoundexCode('B'), '1'); // Test 'B'
    EXPECT_EQ(getSoundexCode('C'), '2'); // Test 'C'
    
    // Test conditions where c is not within 'A'-'Z'
    EXPECT_EQ(getSoundexCode('1'), '0'); // Non-alpha character
    EXPECT_EQ(getSoundexCode(' '), '0'); // Space character
    EXPECT_EQ(getSoundexCode('@'), '0'); // Special character
}

// Test for fetch_firstchar (MCDC: Condition testing for empty and non-empty strings)
TEST(SoundexTest, FetchFirstChar) {
    EXPECT_EQ(fetch_firstchar("example"), 'E'); // Non-empty string
    EXPECT_EQ(fetch_firstchar("a"), 'A');       // Single character string
    EXPECT_EQ(fetch_firstchar(""), '\0');       // Empty string
}

// Test for appendSoundex (MCDC: Conditions where code should or should not be appended)
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

// Test for initializeSoundex (MCDC: Conditions where second character's Soundex code matters)
TEST(SoundexTest, InitializeSoundex) {
    char soundex[5] = "";
    int length = 0;

    initializeSoundex("example", 'E', soundex, &length);
    EXPECT_STREQ(soundex, "E0"); // Adjust as needed

    char soundex2[5] = "";
    length = 0;
    initializeSoundex("Example", 'E', soundex2, &length);
    EXPECT_STREQ(soundex2, "E0"); // Adjust based on expected output
}

// Test for processSoundex (MCDC: Conditions affecting length and processing loop)
TEST(SoundexTest, ProcessSoundex) {
    char soundex[5] = "";
    int length = 0;

    processSoundex("example", 'E', soundex, &length);
    EXPECT_STREQ(soundex, "E0"); // Adjust based on actual implementation
    
    char soundex2[5] = "";
    length = 0;
    processSoundex("Ex", 'E', soundex2, &length);
    EXPECT_STREQ(soundex2, "E0"); // Edge case: short string
}

// Test for paddingSoundex (MCDC: Conditions where padding is needed or not)
TEST(SoundexTest, PaddingSoundex) {
    char soundex[5] = "A";
    paddingSoundex(soundex);
    EXPECT_STREQ(soundex, "A000");

    char soundex2[5] = "A12";
    paddingSoundex(soundex2);
    EXPECT_STREQ(soundex2, "A120");
}

// Test for generateSoundex (MCDC: Combining conditions for complete Soundex generation)
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

