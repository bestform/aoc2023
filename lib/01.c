//
// Created by bestf on 12/26/2023.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "01.h"

int intForLine(char* line) {
    auto l = strlen(line);

    int first = -1;
    int last = -1;

    for (int i = 0; i < l; i++) {
        char c = line[i];

        if(!isdigit(c)) {
            continue;
        }
        // we subtract the ascii value of '0' from the ascii value of the character.
        // this way we end up with the number that is represented by the char.
        // this only works, if isdigit(char) is true, of course. So 0-9 is possible.
        int c_int = c - '0';

        if (first == -1) {
            first = c_int;
            last = c_int;
            continue;
        }

        last = c_int;
    }

    return 10*first + last;
}

writtenNumberResult searchForWrittenNumber(const char* line, int pos, unsigned long long len) {
    // one two three four five six seven eight nine ten
    char buffer[6] = {0};
    for (int i = 0; i < 5; i++) {
        // check for end of line
        int posToAdd = i + pos;
        if (posToAdd > len - 1) {
            break;
        }
        // add one char
        buffer[i] = line[posToAdd];

        // check for number
        if (strcmp(buffer, "zero") == 0) {
            writtenNumberResult result = {1, 0, 4};
            return result;
        }
        if (strcmp(buffer, "one") == 0) {
            writtenNumberResult result = {1, 1, 3};
            return result;
        }
        if (strcmp(buffer, "two") == 0) {
            writtenNumberResult result = {1, 2, 3};
            return result;
        }
        if (strcmp(buffer, "three") == 0) {
            writtenNumberResult result = {1, 3, 4};
            return result;
        }
        if (strcmp(buffer, "four") == 0) {
            writtenNumberResult result = {1, 4, 4};
            return result;
        }
        if (strcmp(buffer, "five") == 0) {
            writtenNumberResult result = {1, 5, 4};
            return result;
        }
        if (strcmp(buffer, "six") == 0) {
            writtenNumberResult result = {1, 6, 3};
            return result;
        }
        if (strcmp(buffer, "seven") == 0) {
            writtenNumberResult result = {1, 7, 5};
            return result;
        }
        if (strcmp(buffer, "eight") == 0) {
            writtenNumberResult result = {1, 8, 5};
            return result;
        }
        if (strcmp(buffer, "nine") == 0) {
            writtenNumberResult result = {1, 9, 4};
            return result;
        }
    }
    writtenNumberResult result = {0};
    return result;
}

int intForLineB(char* line) {
    auto l = strlen(line);

    int first = -1;
    int last = -1;

    for (int i = 0; i < l; i++) {
        char c = line[i];

        if(!isdigit(c)) {
            writtenNumberResult result = searchForWrittenNumber(line, i, l);
            if (result.found == 0) {
                continue;
            }

            //i += result.skip;

            if (first == -1) {
                first = result.number;
                last = result.number;
                continue;
            }

            last = result.number;

            continue;
        }
        // we subtract the ascii value of '0' from the ascii value of the character.
        // this way we end up with the number that is represented by the char.
        // this only works, if isdigit(char) is true, of course. So 0-9 is possible.
        int c_int = c - '0';

        if (first == -1) {
            first = c_int;
            last = c_int;
            continue;
        }

        last = c_int;
    }

    return 10*first + last;
}