#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dynamic_dictionary.h"
#include "dictionary_arrays.h"
#include "dynamic_dictionary.h"

void createAndPopulateDictionary2(Dictionary *dictionary, const char *lang1, const char *lang2, int numWords,
                                  char *words[][2]) {
    dictionary->numOfLanguages = 2;
    dictionary->languages = (char **) malloc(dictionary->numOfLanguages * sizeof(char *));
    dictionary->languages[0] = strdup(lang1);
    dictionary->languages[1] = strdup(lang2);
    dictionary->wordList = NULL;

    printf("Dictionary created with languages: %s, %s\n", lang1, lang2);

    for (int i = 0; i < numWords; i++) {
        Word *newWord = (Word *) malloc(sizeof(Word));
        newWord->translations = (char **) malloc(dictionary->numOfLanguages * sizeof(char *));
        newWord->translations[0] = strdup(words[i][0]);
        newWord->translations[1] = strdup(words[i][1]);
        newWord->next = dictionary->wordList;
        dictionary->wordList = newWord;
        printf("Added word: %s -> %s\n", words[i][0], words[i][1]);
    }
}

void createAndPopulateDictionary3(Dictionary *dictionary, const char *lang1, const char *lang2, const char *lang3,
                                  int numWords, char *words[][3]) {
    dictionary->numOfLanguages = 3;
    dictionary->languages = (char **) malloc(dictionary->numOfLanguages * sizeof(char *));
    dictionary->languages[0] = strdup(lang1);
    dictionary->languages[1] = strdup(lang2);
    dictionary->languages[2] = strdup(lang3);
    dictionary->wordList = NULL;

    printf("Dictionary created with languages: %s, %s, %s\n", lang1, lang2, lang3);

    for (int i = 0; i < numWords; i++) {
        Word *newWord = (Word *) malloc(sizeof(Word));
        newWord->translations = (char **) malloc(dictionary->numOfLanguages * sizeof(char *));
        newWord->translations[0] = strdup(words[i][0]);
        newWord->translations[1] = strdup(words[i][1]);
        newWord->translations[2] = strdup(words[i][2]);
        newWord->next = dictionary->wordList;
        dictionary->wordList = newWord;
        printf("Added word: %s -> %s -> %s\n", words[i][0], words[i][1], words[i][2]);
    }
}

void exportDictionary(Dictionary *dictionary, const char *fileName) {
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Failed to create the file.\n");
        return;
    }

    // Write the header row with the language names
    for (int i = 0; i < dictionary->numOfLanguages; i++) {
        fprintf(file, "%s", dictionary->languages[i]);
        if (i != dictionary->numOfLanguages - 1) {
            fprintf(file, ",");
        }
    }
    fprintf(file, "\n");

    // Write each word and its translations
    Word *currentWord = dictionary->wordList;
    while (currentWord != NULL) {
        for (int i = 0; i < dictionary->numOfLanguages; i++) {
            fprintf(file, "%s", currentWord->translations[i]);
            if (i != dictionary->numOfLanguages - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
        currentWord = currentWord->next;
    }

    fclose(file);
    printf("Dictionary has been successfully exported to %s!\n", fileName);
}

void testScript() {
    Dictionary dict1, dict2, dict3, dict4, dict5;

    // Create and populate dictionaries
    createAndPopulateDictionary3(&dict1, "english", "spanish", "italian", 1000, englishSpanishItalian);
    createAndPopulateDictionary2(&dict2, "german", "dutch", 1000, germanDutch);
    createAndPopulateDictionary2(&dict3, "english", "indonesian", 1500, englishIndonesian);
    createAndPopulateDictionary2(&dict4, "french", "spanish", 350, frenchSpanish);
    createAndPopulateDictionary3(&dict5, "italian", "portuguese", "french", 250, italianPortugueseFrench);

    // Array of dictionaries
    Dictionary dictionaries[] = {dict1, dict2, dict3, dict4, dict5};
    int numOfDictionaries = 5;

    printf("Dictionaries before sorting:\n");
    for (int i = 0; i < numOfDictionaries; i++) {
        printf("Dictionary %d: %s\n", i + 1, dictionaries[i].languages[0]);
    }

    // Sort dictionaries
    sortWordsInDictionary(dictionaries, numOfDictionaries);

    printf("\nDictionaries after sorting:\n");
    for (int i = 0; i < numOfDictionaries; i++) {
        printf("Dictionary %d: %s\n", i + 1, dictionaries[i].languages[0]);
    }

    // Export sorted dictionaries to CSV (optional, just for verification)
    // Export dictionaries to CSV
    exportDictionary(&dict1, "../english_spanish_italian.csv");
    exportDictionary(&dict2, "../german_dutch.csv");
    exportDictionary(&dict3, "../english_indonesian.csv");
    exportDictionary(&dict4, "../french_spanish.csv");
    exportDictionary(&dict5, "../italian_portuguese_french.csv");

}


int main() {
    testScript();
    return 0;
}
