#include <stdbool.h>

void printHelp(bool printStdErr);
void printErrorHeader();
void printTableDescription();
void resetTerm();
void exitProg(int exitCode);
int countDigits(unsigned long num);
int delay;
unsigned long number;
unsigned long result;