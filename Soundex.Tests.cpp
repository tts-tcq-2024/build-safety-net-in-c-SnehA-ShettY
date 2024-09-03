#include <gtest/gtest.h>
#include <cstring>
#include "Soundex.h"

// Test get_Soundex_Code function
TEST(SoundexTest, GetSoundexCode) {
    EXPECT_EQ(get_Soundex_Code('A'), '0');
    EXPECT_EQ(get_Soundex_Code('B'), '1');
    EXPECT_EQ(get_Soundex_Code('C'), '2');
    EXPECT_EQ(get_Soundex_Code('D'), '3');
    EXPECT_EQ(get_Soundex_Code('E'), '0');
    EXPECT_EQ(get_Soundex_Code('F'), '1');
    EXPECT_EQ(get_Soundex_Code('G'), '2');
    EXPECT_EQ(get_Soundex_Code('H'), '0');
    EXPECT_EQ(get_Soundex_Code('Z'), '2');
}

// Test fetch_first_char function
TEST(SoundexTest, FetchFirstChar) {
    EXPECT_EQ(fetch_first_char("Example"), 'E');
    EXPECT_EQ(fetch_first_char("soundex"), 'S');
    EXPECT_EQ(fetch_first_char(""), '\0');
}

// Test append_Soundex function
TEST(SoundexTest, AppendSoundex) {
    char soundex[5] = "A";
    char prevCode = '1';
    int length = 1;

    append_Soundex(soundex, '2', &prevCode, &length);
    EXPECT_STREQ(soundex, "A2");
    EXPECT_EQ(length, 2);

    append_Soundex(soundex, '3', &prevCode, &length);
    EXPECT_STREQ(soundex, "A23");
    EXPECT_EQ(length, 3);

    append_Soundex(soundex, '3', &prevCode, &length);  // Should not append same code
    EXPECT_STREQ(soundex, "A23");
    EXPECT_EQ(length, 3);
}

// Test initialize_Soundex function
TEST(SoundexTest, InitializeSoundex) {
    char soundex[5] = "";
    int length = 0;

    initialize_Soundex("Smith", 'S', soundex, &length);
    EXPECT_STREQ(soundex, "S5");
    EXPECT_EQ(length, 2);
}

// Test process_Soundex function
TEST(SoundexTest, ProcessSoundex) {
    char soundex[5] = "";
    int length = 0;

    process_Soundex("Smith", 'S', soundex, &length);
    EXPECT_STREQ(soundex, "S53");
    EXPECT_EQ(length, 3);
}

// Test padding_Soundex function
TEST(SoundexTest, PaddingSoundex) {
    char soundex[5] = "S5";

    padding_Soundex(soundex);
    EXPECT_STREQ(soundex, "S500");

    strcpy(soundex, "S53");
    padding_Soundex(soundex);
    EXPECT_STREQ(soundex, "S530");

    strcpy(soundex, "S530");
    padding_Soundex(soundex);
    EXPECT_STREQ(soundex, "S530");
}

// Test generate_Soundex function
TEST(SoundexTest, GenerateSoundex) {
    char soundex[5] = "";

    generate_Soundex("Smith", soundex);
    EXPECT_STREQ(soundex, "S530");

    generate_Soundex("Smythe", soundex);
    EXPECT_STREQ(soundex, "S530");

    generate_Soundex("Ashcraft", soundex);
    EXPECT_STREQ(soundex, "A261");

    generate_Soundex("Tymczak", soundex);
    EXPECT_STREQ(soundex, "T520");

    generate_Soundex("", soundex);
    EXPECT_STREQ(soundex, "");
}
