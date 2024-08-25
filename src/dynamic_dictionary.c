#include <stdio.h>
#include <stdlib.h>
#include "../include/dynamic_dictionary.h"
#include "../include/free_functions.h"
#include "../include/dictionary_creation.h"
#include "../include/word_deletion.h"
#include "../include/add_word.h"
#include "../include/word_translate.h"
#include "../include/export_csv.h"
#include "../include/import_csv.h"
#include "../include/sort_dictionary.h"

int isDictionaryLoaded(Dictionary *dictionaries, int numOfDictionaries, char **languages, int numOfLanguages) {
    for (int i = 0; i < numOfDictionaries; i++) {
        if (dictionaries[i].numOfLanguages == numOfLanguages) {
            int allLanguagesMatch = 1;
            for (int j = 0; j < numOfLanguages; j++) {
                if (strcmp(dictionaries[i].languages[j], languages[j]) != 0) {
                    allLanguagesMatch = 0;
                    break;
                }
            }
            if (allLanguagesMatch) {
                return 1; // Dictionary with the same languages is already loaded
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
    } else {
        *flagOfNoOption = 1;
    }
}void run_dynamic_dictionary() {
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
                    "8. Sort a dictionary's words alphabetically.\n"
                    "9. Exit.\n");
        }

        char input[10];  // Buffer to store user input
        if (fgets(input, sizeof(input), stdin) != NULL) {
            if (sscanf(input, "%d", &choiceOfUser) == 1 && choiceOfUser >= 1 && choiceOfUser <= 9) {
                switch (choiceOfUser) {
                    case 1:
                        dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                        if (dictionaries == NULL) {
                            printf("Memory allocation failed!\n");
                            exit(EXIT_FAILURE);
                        }
                        dictionaries[numOfDictionaries].wordList = NULL;
                        newDictionary(&numOfDictionaries, &dictionaries[numOfDictionaries]);
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
                            if (dictionaries == NULL && numOfDictionaries > 0) {
                                printf("Memory allocation failed!\n");
                                exit(EXIT_FAILURE);
                            }
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
                        if (fgets(input, sizeof(input), stdin) != NULL && sscanf(input, "%d", &loadChoice) == 1) {
                            switch (loadChoice) {
                                case 1: {
                                    char *langs[] = {"english", "spanish", "italian"};
                                    if (!isDictionaryLoaded(dictionaries, numOfDictionaries, langs, 3)) {
                                        dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                                        if (dictionaries == NULL) {
                                            printf("Memory allocation failed!\n");
                                            exit(EXIT_FAILURE);
                                        }
                                        loadDictionaryFromCSV(&dictionaries[numOfDictionaries], "../english_spanish_italian.csv", &numOfDictionaries);
                                        flagOfNoOption = 1;
                                    } else {
                                        printf("English-Spanish-Italian dictionary is already loaded.\n");
                                    }
                                    break;
                                }
                                case 2: {
                                    char *langs[] = {"german", "dutch"};
                                    if (!isDictionaryLoaded(dictionaries, numOfDictionaries, langs, 2)) {
                                        dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                                        if (dictionaries == NULL) {
                                            printf("Memory allocation failed!\n");
                                            exit(EXIT_FAILURE);
                                        }
                                        loadDictionaryFromCSV(&dictionaries[numOfDictionaries], "../german_dutch.csv", &numOfDictionaries);
                                        flagOfNoOption = 1;
                                    } else {
                                        printf("German-Dutch dictionary is already loaded.\n");
                                    }
                                    break;
                                }
                                case 3: {
                                    char *langs[] = {"english", "indonesian"};
                                    if (!isDictionaryLoaded(dictionaries, numOfDictionaries, langs, 2)) {
                                        dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                                        if (dictionaries == NULL) {
                                            printf("Memory allocation failed!\n");
                                            exit(EXIT_FAILURE);
                                        }
                                        loadDictionaryFromCSV(&dictionaries[numOfDictionaries], "../english_indonesian.csv", &numOfDictionaries);
                                        flagOfNoOption = 1;
                                    } else {
                                        printf("English-Indonesian dictionary is already loaded.\n");
                                    }
                                    break;
                                }
                                case 4: {
                                    char *langs[] = {"french", "spanish"};
                                    if (!isDictionaryLoaded(dictionaries, numOfDictionaries, langs, 2)) {
                                        dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                                        if (dictionaries == NULL) {
                                            printf("Memory allocation failed!\n");
                                            exit(EXIT_FAILURE);
                                        }
                                        loadDictionaryFromCSV(&dictionaries[numOfDictionaries], "../french_spanish.csv", &numOfDictionaries);
                                        flagOfNoOption = 1;
                                    } else {
                                        printf("French-Spanish dictionary is already loaded.\n");
                                    }
                                    break;
                                }
                                case 5: {
                                    char *langs[] = {"italian", "portuguese", "french"};
                                    if (!isDictionaryLoaded(dictionaries, numOfDictionaries, langs, 3)) {
                                        dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                                        if (dictionaries == NULL) {
                                            printf("Memory allocation failed!\n");
                                            exit(EXIT_FAILURE);
                                        }
                                        loadDictionaryFromCSV(&dictionaries[numOfDictionaries], "../italian_portuguese_french.csv", &numOfDictionaries);
                                        flagOfNoOption = 1;
                                    } else {
                                        printf("Italian-Portuguese-French dictionary is already loaded.\n");
                                    }
                                    break;
                                }
                                case 6:
                                    // Load all dictionaries with the same check
                                {
                                    char *langs1[] = {"english", "spanish", "italian"};
                                    if (!isDictionaryLoaded(dictionaries, numOfDictionaries, langs1, 3)) {
                                        dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                                        if (dictionaries == NULL) {
                                            printf("Memory allocation failed!\n");
                                            exit(EXIT_FAILURE);
                                        }
                                        loadDictionaryFromCSV(&dictionaries[numOfDictionaries], "../english_spanish_italian.csv", &numOfDictionaries);
                                    }
                                    char *langs2[] = {"german", "dutch"};
                                    if (!isDictionaryLoaded(dictionaries, numOfDictionaries, langs2, 2)) {
                                        dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                                        if (dictionaries == NULL) {
                                            printf("Memory allocation failed!\n");
                                            exit(EXIT_FAILURE);
                                        }
                                        loadDictionaryFromCSV(&dictionaries[numOfDictionaries], "../german_dutch.csv", &numOfDictionaries);
                                    }
                                    char *langs3[] = {"english", "indonesian"};
                                    if (!isDictionaryLoaded(dictionaries, numOfDictionaries, langs3, 2)) {
                                        dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                                        if (dictionaries == NULL) {
                                            printf("Memory allocation failed!\n");
                                            exit(EXIT_FAILURE);
                                        }
                                        loadDictionaryFromCSV(&dictionaries[numOfDictionaries], "../english_indonesian.csv", &numOfDictionaries);
                                    }
                                    char *langs4[] = {"french", "spanish"};
                                    if (!isDictionaryLoaded(dictionaries, numOfDictionaries, langs4, 2)) {
                                        dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                                        if (dictionaries == NULL) {
                                            printf("Memory allocation failed!\n");
                                            exit(EXIT_FAILURE);
                                        }
                                        loadDictionaryFromCSV(&dictionaries[numOfDictionaries], "../french_spanish.csv", &numOfDictionaries);
                                    }
                                    char *langs5[] = {"italian", "portuguese", "french"};
                                    if (!isDictionaryLoaded(dictionaries, numOfDictionaries, langs5, 3)) {
                                        dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                                        if (dictionaries == NULL) {
                                            printf("Memory allocation failed!\n");
                                            exit(EXIT_FAILURE);
                                        }
                                        loadDictionaryFromCSV(&dictionaries[numOfDictionaries], "../italian_portuguese_french.csv", &numOfDictionaries);
                                    }
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
                        } else {
                            printf("Invalid input. Please enter a number.\n");
                        }
                        flagForNotPrintMenu = 0;
                        break;
                    case 8:  // Sort a specific dictionary's words alphabetically
                        flagCheck(&flagOfNoOption, &numOfDictionaries, &flagForNotPrintMenu);
                        if (flagOfNoOption == 1) {
                            sortWordsInDictionary(dictionaries, numOfDictionaries);
                            flagForNotPrintMenu = 0;
                        }
                        break;
                    case 9:
                        freeAllDictionaries(dictionaries, numOfDictionaries);
                        printf("Bye!\n");
                        break;
                    default:
                        printf("Invalid choice. Try again.\n");
                        flagForNotPrintMenu = 1;
                        break;
                }
            } else {
                printf("Invalid choice. Try again.\n");
                flagForNotPrintMenu = 1;
            }
        } else {
            printf("Error reading input. Please try again.\n");
            flagForNotPrintMenu = 1;
        }

    } while (choiceOfUser != 9);
}
