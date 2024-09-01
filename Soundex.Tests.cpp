#include <gtest/gtest.h>
#include <cstring>



// Unit test for getSoundexCode
TEST(SoundexTest, GetSoundexCode) {
    EXPECT_EQ(getSoundexCode('A'), '0');
    EXPECT_EQ(getSoundexCode('B'), '1');
    EXPECT_EQ(getSoundexCode('C'), '2');
    EXPECT_EQ(getSoundexCode('D'), '3');
    EXPECT_EQ(getSoundexCode('E'), '0'); // 'E' maps to '0'
    EXPECT_EQ(getSoundexCode('F'), '1');
    EXPECT_EQ(getSoundexCode('G'), '2');
    EXPECT_EQ(getSoundexCode('H'), '0'); // 'H' maps to '0'
    EXPECT_EQ(getSoundexCode('K'), '2');
    EXPECT_EQ(getSoundexCode('L'), '4');
    EXPECT_EQ(getSoundexCode('M'), '5');
    EXPECT_EQ(getSoundexCode('N'), '5');
    EXPECT_EQ(getSoundexCode('O'), '0'); // 'O' maps to '0'
    EXPECT_EQ(getSoundexCode('P'), '1');
    EXPECT_EQ(getSoundexCode('Q'), '0'); // 'Q' maps to '0'
    EXPECT_EQ(getSoundexCode('R'), '6');
    EXPECT_EQ(getSoundexCode('S'), '2');
    EXPECT_EQ(getSoundexCode('T'), '3');
    EXPECT_EQ(getSoundexCode('U'), '0'); // 'U' maps to '0'
    EXPECT_EQ(getSoundexCode('V'), '1');
    EXPECT_EQ(getSoundexCode('W'), '0'); // 'W' maps to '0'
    EXPECT_EQ(getSoundexCode('X'), '2');
    EXPECT_EQ(getSoundexCode('Y'), '0'); // 'Y' maps to '0'
    EXPECT_EQ(getSoundexCode('Z'), '2');
}

// Unit test for fetch_firstchar
TEST(SoundexTest, FetchFirstChar) {
    EXPECT_EQ(fetch_firstchar("example"), 'E');
    EXPECT_EQ(fetch_firstchar(""), '\0'); // Empty string
    EXPECT_EQ(fetch_firstchar("a"), 'A');
}

// Unit test for appendSoundex
TEST(SoundexTest, AppendSoundex) {
    char soundex[5] = "S";
    char prevCode = 'S';
    int length = 1;

    appendSoundex(soundex, '1', &prevCode, &length);
    EXPECT_STREQ(soundex, "S1");
    appendSoundex(soundex, '1', &prevCode, &length);
    EXPECT_STREQ(soundex, "S1"); // Should not append the same code

    appendSoundex(soundex, '2', &prevCode, &length);
    EXPECT_STREQ(soundex, "S12");
}

// Unit test for initializeSoundex
TEST(SoundexTest, InitializeSoundex) {
    char soundex[5] = "";
    int length = 0;

    initializeSoundex("example", 'E', soundex, &length);
    EXPECT_STREQ(soundex, "E0"); // Assuming 'E' should map to '0'
}

// Unit test for processSoundex
TEST(SoundexTest, ProcessSoundex) {
    char soundex[5] = "";
    int length = 0;

    processSoundex("example", 'E', soundex, &length);
    EXPECT_STREQ(soundex, "E0"); // Adjust expected result as per implementation
}

// Unit test for paddingSoundex
TEST(SoundexTest, PaddingSoundex) {
    char soundex[5] = "E";
    paddingSoundex(soundex);
    EXPECT_STREQ(soundex, "E000");

    char soundex2[5] = "E12";
    paddingSoundex(soundex2);
    EXPECT_STREQ(soundex2, "E120");
}

// Unit test for generateSoundex
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



