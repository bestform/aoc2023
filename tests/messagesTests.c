//
// Created by bestf on 12/26/2023.
//


#include <malloc.h>
#include <string.h>
#include "unity/src/unity.h"
#include "../lib/messages.h"
#include "../lib/01.h"
#include "../lib/reader.h"


void setUp() {}

void tearDown() {}

void test_make_message() {
    char* output = NULL;
    makeMessage("Matthias", &output);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Hallo, Matthias", output, strlen(output));
    free(output);
}

void test_01() {
    TEST_ASSERT_EQUAL_INT(12, intForLine("1abc2"));
    TEST_ASSERT_EQUAL_INT(38, intForLine("pqr3stu8vwx"));
    TEST_ASSERT_EQUAL_INT(15, intForLine("a1b2c3d4e5f"));
    TEST_ASSERT_EQUAL_INT(77, intForLine("treb7uchet"));
}

void test_01b() {
    TEST_ASSERT_EQUAL_INT(29, intForLineB("two1nine"));
    TEST_ASSERT_EQUAL_INT(83, intForLineB("eightwothree"));
    TEST_ASSERT_EQUAL_INT(13, intForLineB("abcone2threexyz"));
    TEST_ASSERT_EQUAL_INT(24, intForLineB("xtwone3four"));
    TEST_ASSERT_EQUAL_INT(42, intForLineB("4nineeightseven2"));
    TEST_ASSERT_EQUAL_INT(14, intForLineB("zoneight234"));
    TEST_ASSERT_EQUAL_INT(76, intForLineB("7pqrstsixteen"));
}

void test_reader() {
    fileContents result = linesOfFile("fixtures/lines.txt");
    char* expected[] = {
            [0] = "line1\n",
            [1] = "line2\n",
            [2] = "line3",
    };


    TEST_ASSERT_EQUAL_INT(3, result.len);

    for(int i = 0; i < result.len; i++) {
        TEST_ASSERT_EQUAL_CHAR_ARRAY(expected[i], result.lines[i], strlen(result.lines[i]));
    }

    freeFileContents(&result);
}

int main(void) {
    UNITY_BEGIN();
    //RUN_TEST(test_01);
    RUN_TEST(test_reader);
    //RUN_TEST(test_01b);

    return UNITY_END();
}