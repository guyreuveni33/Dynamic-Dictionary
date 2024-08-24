#ifndef FREE_FUNCTIONS_H
#define FREE_FUNCTIONS_H

#include "dynamic_dictionary.h"  // Include this to make Dictionary and Word types known

// Frees all dictionaries
void freeAllDictionaries(Dictionary *dictionaries, int numOfDictionaries);

// Frees a node in the word list
void freeTheNode(Word *current);

void deleteDictionary(Dictionary *dictionaries, int *numOfDictionaries);

#endif // FREE_FUNCTIONS_H
