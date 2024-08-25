#ifndef DYNAMIC_DICTIONARY_H
#define DYNAMIC_DICTIONARY_H

#include <stdio.h>
#include <stdlib.h>

// Struct Definitions
typedef struct Word {
    char **translations;
    struct Word *next;
} Word;

typedef struct {
    char **languages;
    int numOfLanguages;
    Word *wordList;
} Dictionary;

// Function Declarations

// Checks if there are dictionaries and manages the menu display
void flagCheck(int *flagOfNoOption, int *numOfDictionaries, int *flagForNotPrintMenu);

void run_dynamic_dictionary();

#endif // DYNAMIC_DICTIONARY_H
