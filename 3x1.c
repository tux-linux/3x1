#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "3x1.h"

int main(int argc, char *argv[]) {
    if(argc == 1) {
        printHelp(true);
        printErrorHeader();
        fprintf(stderr, "Error: please specify an argument.\n");
        exitProg(1);
    }
    else {
        if(strcmp(argv[1], "help") == 0) {
            printHelp(false);
            printf("\n");
            exitProg(0);
        }
        else {
            char * delayEnv;
            delayEnv = getenv("DELAY");
            if(delayEnv != NULL) {
                delay = strtol(delayEnv, NULL, 10);
            }
            else {
                // Default delay is 500,000 microseconds, or half a second
                delay = 500000;
            }
            number = strtol(argv[1], NULL, 10);
            printf("Selected number is %lu.\n", number);
            printTableDescription();
            while(1) {
                // Checking if number is even or odd
                if(number % 2 == 0) {
                    // Number is even
                    result = number / 2;
                    // Prevent garbled formatting when number is only one digit long
                    if(countDigits(number) <= 1) {
                        printf("\x1b[34mEVEN\x1b[0m\t %lu / 2 \t\t= \x1b[1m%lu\x1b[0m\n", number, result);
                    }
                    else {
                        printf("\x1b[34mEVEN\x1b[0m\t %lu / 2 \t= \x1b[1m%lu\x1b[0m\n", number, result);
                    }
                    number = result;
                    if(number == 1) {
                        printf("\x1b[1m---- Loop reached ----\x1b[0m\n");
                        break;
                    }
                }
                else {
                    // Number is odd
                    result = 3 * number + 1;
                    printf("\x1b[96mODD\x1b[0m\t 3 * %lu + 1 \t= \x1b[1m%lu\x1b[0m\n", number, result);
                    number = result;
                    if(number == 1) {
                        printf("\x1b[1m---- Loop reached ----\x1b[0m\n");
                        break;
                    }
                }
                usleep(delay);
            }
            exitProg(0);
        }
    }
}

void printHelp(bool printStdErr) {
    char helpText[] = "* \t    Collatz conjecture demonstration program    \t *\n* Copyright (C) 2021, Nicolas Mailloux <nicolecrivain@gmail.com> *\n* \t\tLicensed under the MIT license\t\t\t *\n\nDescription: takes integer (unsigned long) as its only argument and applies the '3n + 1' problem to it.\nUsage: 3x1 <UNSIGNED LONG>\nA delay between operations may be specified in the DELAY environment variable.\nDefault is set to 500,000 microseconds (half a second)";
    if(printStdErr == true) {
        fprintf(stderr, helpText);
    }
    else {
        fprintf(stdout, helpText);
    }
}

void printTableDescription() {
    printf("\x1b[1mType\t Operation\tResult\x1b[0m\n");
}

void printErrorHeader() {
    fprintf(stderr, "\n\n----------------\nAn error occured\n----------------\n\n");
}

int countDigits(unsigned long num) {
    int count = 0;
    while(num != 0) {
        count++;
        num /= 10;
    }
    return count;
}

void resetTerm() {
    // Reset terminal colors
    printf("\x1b[0m");
}

void exitProg(int exitCode) {
    resetTerm();
    exit(exitCode);
}
