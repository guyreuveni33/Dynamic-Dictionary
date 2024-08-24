#include <stdio.h>
#include <stdlib.h>
#include "../include/dynamic_dictionary.h"
#include "../include/free_functions.h"
#include "../include/dictionary_creation.h"
#include "../include/word_deletion.h"
#include "../include/add_word.h"
#include "../include/word_translate.h"
#include "../include/export_csv.h"
#include "../include/import_csv.h"  // Include the header for importing CSVint compareWords(const void *a, const void *b) {

int compareWords(const void *a, const void *b) {
    const Word *wordA = *(const Word **)a;
    const Word *wordB = *(const Word **)b;

    // Compare based on the first translation (e.g., English)
    return strcmp(wordA->translations[0], wordB->translations[0]);
}
void sortWordsInDictionary(Dictionary *dictionary) {
    int numWords = 0;
    Word *current = dictionary->wordList;

    // Count the number of words
    while (current != NULL) {
        numWords++;
        current = current->next;
    }

    // Create an array of pointers to Word structs
    Word **wordArray = (Word **)malloc(numWords * sizeof(Word *));
    current = dictionary->wordList;
    for (int i = 0; i < numWords; i++) {
        wordArray[i] = current;
        current = current->next;
    }

    // Sort the words using qsort and the compareWords function
    qsort(wordArray, numWords, sizeof(Word *), compareWords);

    // Rebuild the linked list with the sorted words
    dictionary->wordList = wordArray[0];
    current = dictionary->wordList;
    for (int i = 1; i < numWords; i++) {
        current->next = wordArray[i];
        current = current->next;
    }
    current->next = NULL;

    // Free the temporary array
    free(wordArray);
}


int isDictionaryLoaded(Dictionary *dictionaries, int numOfDictionaries, const char *fileName) {
    for (int i = 0; i < numOfDictionaries; i++) {
        if (dictionaries[i].languages != NULL) {
            // Check if the dictionary was loaded by comparing its file name
            if (strcmp(dictionaries[i].languages[0], fileName) == 0) {
                return 1; // Dictionary is already loaded
            }
        }
    }
    return 0; // Dictionary is not loaded
}

void flagCheck(int *flagOfNoOption, int *numOfDictionaries, int *flagForNotPrintMenu) {
    if (*numOfDictionaries == 0) {
        printf("This option is not available right now, try again:\n");
        *flagOfNoOption = 0;
        *flagForNotPrintMenu = 0;
    }
}

void run_dynamic_dictionary() {
    int numOfDictionaries = 0;
    Dictionary *dictionaries = NULL;
    int choiceOfUser, flagOfNoOption = 0, flagForNotPrintMenu = 0;
    printf("Welcome to the dictionaries manager!\n");

    do {
        if (flagForNotPrintMenu == 0) {
            printf(
                    "Choose an option:\n"
                    "1. Create a new dictionary.\n"
                    "2. Add a word to a dictionary.\n"
                    "3. Delete a word from a dictionary.\n"
                    "4. Find a word in a dictionary.\n"
                    "5. Delete a dictionary.\n"
                    "6. Export dictionary to CSV.\n"
                    "7. Load dictionary from CSV.\n"
                    "8. Sort dictionaries alphabetically.\n"
                    "9. Exit.\n");
        }
        scanf("%d", &choiceOfUser);
        switch (choiceOfUser) {
            case 1:
                if (numOfDictionaries != 0) {
                    dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                    dictionaries[numOfDictionaries].wordList = NULL;
                    if (dictionaries == NULL) {
                        printf("The creation of the dictionary has failed!\n");
                        break;
                    }
                } else {
                    dictionaries = (Dictionary *) malloc(sizeof(Dictionary));
                    dictionaries[0].wordList = NULL;
                    if (dictionaries == NULL) {
                        printf("The creation of the dictionary has failed!\n");
                        break;
                    }
                }
                newDictionary(&numOfDictionaries, &dictionaries[(numOfDictionaries)]);
                flagOfNoOption = 1;
                flagForNotPrintMenu = 0;
                break;
            case 2:
                flagCheck(&flagOfNoOption, &numOfDictionaries, &flagForNotPrintMenu);
                if (flagOfNoOption == 1) {
                    addWord(dictionaries, numOfDictionaries);
                    flagForNotPrintMenu = 0;
                }
                break;
            case 3:
                flagCheck(&flagOfNoOption, &numOfDictionaries, &flagForNotPrintMenu);
                if (flagOfNoOption == 1) {
                    deleteWord(dictionaries, numOfDictionaries);
                    flagForNotPrintMenu = 0;
                }
                break;
            case 4:
                flagCheck(&flagOfNoOption, &numOfDictionaries, &flagForNotPrintMenu);
                if (flagOfNoOption == 1) {
                    findWord(dictionaries, numOfDictionaries);
                    flagForNotPrintMenu = 0;
                }
                break;
            case 5:
                flagCheck(&flagOfNoOption, &numOfDictionaries, &flagForNotPrintMenu);
                if (flagOfNoOption == 1) {
                    deleteDictionary(dictionaries, &numOfDictionaries);
                    dictionaries = realloc(dictionaries, (numOfDictionaries) * sizeof(Dictionary));
                    flagForNotPrintMenu = 0;
                }
                break;
            case 6:
                flagCheck(&flagOfNoOption, &numOfDictionaries, &flagForNotPrintMenu);
                if (flagOfNoOption == 1) {
                    exportDictionaryToCSV(dictionaries, numOfDictionaries);
                    flagForNotPrintMenu = 0;
                }
                break;
            case 7:  // New case for loading dictionary from CSV
                printf("Choose a dictionary to load:\n");
                printf("1. English-Spanish-Italian\n");
                printf("2. German-Dutch\n");
                printf("3. English-Indonesian\n");
                printf("4. French-Spanish\n");
                printf("5. Italian-Portuguese-French\n");
                printf("6. Load all dictionaries\n");
                printf("7. Back to main menu\n");
                int loadChoice;
                scanf("%d", &loadChoice);

                switch (loadChoice) {
                    case 1:
                        if (!isDictionaryLoaded(dictionaries, numOfDictionaries, "english_spanish_italian")) {
                            dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                            loadDictionaryFromCSV(&dictionaries[numOfDictionaries], "../english_spanish_italian.csv",
                                                  &numOfDictionaries);
                            flagOfNoOption = 1;
                        } else {
                            printf("English-Spanish-Italian dictionary is already loaded.\n");
                        }
                        break;
                    case 2:
                        if (!isDictionaryLoaded(dictionaries, numOfDictionaries, "german_dutch")) {
                            dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                            loadDictionaryFromCSV(&dictionaries[numOfDictionaries], "../german_dutch.csv",
                                                  &numOfDictionaries);
                            flagOfNoOption = 1;
                        } else {
                            printf("German-Dutch dictionary is already loaded.\n");
                        }
                        break;
                    case 3:
                        if (!isDictionaryLoaded(dictionaries, numOfDictionaries, "english_indonesian")) {
                            dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                            loadDictionaryFromCSV(&dictionaries[numOfDictionaries], "../english_indonesian.csv",
                                                  &numOfDictionaries);
                            flagOfNoOption = 1;
                        } else {
                            printf("English-Indonesian dictionary is already loaded.\n");
                        }
                        break;
                    case 4:
                        if (!isDictionaryLoaded(dictionaries, numOfDictionaries, "french_spanish")) {
                            dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                            loadDictionaryFromCSV(&dictionaries[numOfDictionaries], "../french_spanish.csv",
                                                  &numOfDictionaries);
                            flagOfNoOption = 1;
                        } else {
                            printf("French-Spanish dictionary is already loaded.\n");
                        }
                        break;
                    case 5:
                        if (!isDictionaryLoaded(dictionaries, numOfDictionaries, "italian_portuguese_french")) {
                            dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                            loadDictionaryFromCSV(&dictionaries[numOfDictionaries], "../italian_portuguese_french.csv",
                                                  &numOfDictionaries);
                            flagOfNoOption = 1;
                        } else {
                            printf("Italian-Portuguese-French dictionary is already loaded.\n");
                        }
                        break;
                    case 6:
                        if (!isDictionaryLoaded(dictionaries, numOfDictionaries, "english_spanish_italian")) {
                            dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                            loadDictionaryFromCSV(&dictionaries[numOfDictionaries], "../english_spanish_italian.csv",
                                                  &numOfDictionaries);
                        }
                        if (!isDictionaryLoaded(dictionaries, numOfDictionaries, "german_dutch")) {
                            dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                            loadDictionaryFromCSV(&dictionaries[numOfDictionaries], "../german_dutch.csv",
                                                  &numOfDictionaries);
                        }
                        if (!isDictionaryLoaded(dictionaries, numOfDictionaries, "english_indonesian")) {
                            dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                            loadDictionaryFromCSV(&dictionaries[numOfDictionaries], "../english_indonesian.csv",
                                                  &numOfDictionaries);
                        }
                        if (!isDictionaryLoaded(dictionaries, numOfDictionaries, "french_spanish")) {
                            dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                            loadDictionaryFromCSV(&dictionaries[numOfDictionaries], "../french_spanish.csv",
                                                  &numOfDictionaries);
                        }
                        if (!isDictionaryLoaded(dictionaries, numOfDictionaries, "italian_portuguese_french")) {
                            dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                            loadDictionaryFromCSV(&dictionaries[numOfDictionaries], "../italian_portuguese_french.csv",
                                                  &numOfDictionaries);
                        }
                        flagOfNoOption = 1;
                        break;
                    case 7:
                        printf("Returning to main menu without loading any dictionary...\n");
                        break;
                    default:
                        printf("Invalid option, returning to main menu...\n");
                        break;
                }
                flagForNotPrintMenu = 0;
                break;

            case 8:  // New case for sorting words in a dictionary
                flagCheck(&flagOfNoOption, &numOfDictionaries, &flagForNotPrintMenu);
                if (flagOfNoOption == 1) {
                    printf("Choose a dictionary to sort:\n");
                    for (int i = 0; i < numOfDictionaries; i++) {
                        printf("%d. %s\n", i + 1, dictionaries[i].languages[0]);
                    }
                    int sortChoice;
                    scanf("%d", &sortChoice);
                    if (sortChoice >= 1 && sortChoice <= numOfDictionaries) {
                        sortWordsInDictionary(&dictionaries[sortChoice - 1]);
                        printf("Dictionary sorted alphabetically by the first word in the first language.\n");
                    } else {
                        printf("Invalid choice.\n");
                    }
                    flagForNotPrintMenu = 0;
                }
                break;

            case 9:
                freeAllDictionaries(dictionaries, numOfDictionaries);
                printf("Bye!\n");
                break;

            default:
                printf("Wrong option, try again:\n");
                break;
        }
    } while (choiceOfUser != 9);
}