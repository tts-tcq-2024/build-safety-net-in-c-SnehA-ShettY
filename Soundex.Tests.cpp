#include <gtest/gtest.h>
#include <cstring>
#include "Soundex.h"

// Test get_Soundex_Code function
TEST(SoundexTest, get_Soundex_Code) {
    EXPECT_EQ('1', get_Soundex_Code('B'));
    EXPECT_EQ('1', get_Soundex_Code('F'));
    EXPECT_EQ('1', get_Soundex_Code('P'));
    EXPECT_EQ('1', get_Soundex_Code('V'));

    EXPECT_EQ('2', get_Soundex_Code('C'));
    EXPECT_EQ('2', get_Soundex_Code('G'));
    EXPECT_EQ('2', get_Soundex_Code('J'));
    EXPECT_EQ('2', get_Soundex_Code('K'));
    EXPECT_EQ('2', get_Soundex_Code('Q'));
    EXPECT_EQ('2', get_Soundex_Code('S'));
    EXPECT_EQ('2', get_Soundex_Code('X'));
    EXPECT_EQ('2', get_Soundex_Code('Z'));

    EXPECT_EQ('3', get_Soundex_Code('D'));
    EXPECT_EQ('3', get_Soundex_Code('T'));

    EXPECT_EQ('4', get_Soundex_Code('L'));

    EXPECT_EQ('5', get_Soundex_Code('M'));
    EXPECT_EQ('5', get_Soundex_Code('N'));

    EXPECT_EQ('6', get_Soundex_Code('R'));

    EXPECT_EQ('0', get_Soundex_Code('A'));
    EXPECT_EQ('0', get_Soundex_Code('E'));
    EXPECT_EQ('0', get_Soundex_Code('I'));
    EXPECT_EQ('0', get_Soundex_Code('O'));
    EXPECT_EQ('0', get_Soundex_Code('U'));

    EXPECT_EQ('0', get_Soundex_Code('H'));
    EXPECT_EQ('0', get_Soundex_Code('W'));
    EXPECT_EQ('0', get_Soundex_Code('Y'));

    EXPECT_EQ(get_Soundex_Code('b'), get_Soundex_Code('B'));
    EXPECT_EQ(get_Soundex_Code('c'), get_Soundex_Code('C'));
    EXPECT_EQ(get_Soundex_Code('d'), get_Soundex_Code('D'));
    EXPECT_EQ(get_Soundex_Code('r'), get_Soundex_Code('R'));
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
