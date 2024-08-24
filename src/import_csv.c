#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/import_csv.h"

void loadDictionaryFromCSV(Dictionary *dictionary, const char *fileName, int *numOfDictionaries) {
    printf("Loading dictionary from %s...\n", fileName);

    FILE *file = fopen(fileName, "r");
    if (!file) {
        printf("Could not open file %s\n", fileName);
        return;
    }

    dictionary->wordList = NULL;  // Initialize the word list to NULL
    dictionary->numOfLanguages = 0; // Reset the number of languages
    Word *lastWord = NULL;  // Pointer to the last word in the list

    char line[256];

    // Reading the first line for the language names
    if (fgets(line, sizeof(line), file)) {
        // Count the number of languages (columns) based on commas
        dictionary->numOfLanguages = 1;
        for (char *p = line; *p != '\0'; p++) {
            if (*p == ',') {
                dictionary->numOfLanguages++;
            }
        }

        // Allocate memory for languages and store them
        dictionary->languages = (char **)malloc(dictionary->numOfLanguages * sizeof(char *));
        char *token = strtok(line, ",\n");
        for (int i = 0; i < dictionary->numOfLanguages; i++) {
            dictionary->languages[i] = strdup(token);
            token = strtok(NULL, ",\n");
        }
    }

    // Reading the rest of the lines for the translations
    while (fgets(line, sizeof(line), file)) {
        Word *newWord = (Word *)malloc(sizeof(Word));
        if (newWord == NULL) {
            printf("Failed to allocate memory for a new word!\n");
            fclose(file);
            return;
        }

        // Allocate memory for the translations array
        newWord->translations = (char **)malloc(dictionary->numOfLanguages * sizeof(char *));
        if (newWord->translations == NULL) {
            printf("Failed to allocate memory for translations!\n");
            free(newWord);
            fclose(file);
            return;
        }

        // Parse the CSV line into the translations array
        char *token = strtok(line, ",\n");
        for (int i = 0; i < dictionary->numOfLanguages; i++) {
            if (token != NULL) {
                newWord->translations[i] = strdup(token);
                token = strtok(NULL, ",\n");
            } else {
                newWord->translations[i] = strdup("");
            }
        }

        newWord->next = NULL;

        // Link the new word to the list
        if (dictionary->wordList == NULL) {
            dictionary->wordList = newWord;
        } else {
            lastWord->next = newWord;
        }
        lastWord = newWord;
    }

    fclose(file);
    (*numOfDictionaries)++;
    printf("Dictionary loaded successfully from %s!\n", fileName);
}
