// import_csv.h

#ifndef IMPORT_CSV_H
#define IMPORT_CSV_H

#include "dynamic_dictionary.h"  // Ensure this includes the definition of Dictionary

void loadDictionaryFromCSV(Dictionary *dictionary, const char *fileName, int *numOfDictionaries);

#endif // IMPORT_CSV_H
