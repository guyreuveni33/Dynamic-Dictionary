#include "../include/export_csv.h"
#include <stdio.h>
#include <string.h>

void exportDictionaryToCSV(Dictionary *dictionaries, int numOfDictionaries) {
    if (numOfDictionaries == 0) {
        printf("No dictionaries available to export.\n");
        return;
    }

    int chosenDictionary;
    printf("Choose a dictionary to export:\n");
    for (int i = 0; i < numOfDictionaries; i++) {
        printf("%d. ", (i + 1));
        for (int j = 0; j < dictionaries[i].numOfLanguages; j++) {
            printf("%s", dictionaries[i].languages[j]);
            if (j != (dictionaries[i].numOfLanguages) - 1)
                printf(",");
        }
        printf("\n");
    }
    scanf("%d", &chosenDictionary);
    chosenDictionary--; // Adjust index for zero-based array

    // Initialize fileName and construct the base file name
    char fileName[256] = ""; // Initialize an empty string

    // Concatenate all language names into fileName
    for (int i = 0; i < dictionaries[chosenDictionary].numOfLanguages; i++) {
        strcat(fileName, dictionaries[chosenDictionary].languages[i]);
        if (i != dictionaries[chosenDictionary].numOfLanguages - 1) {
            strcat(fileName, "_"); // Use underscore to separate language names
        }
    }

    // Append the suffix " dictionary.csv"
    strcat(fileName, " dictionary.csv");

    // Create the full file path pointing to the "exported_dictionaries" directory in your project
    char fullPath[512];
    snprintf(fullPath, sizeof(fullPath), "../exported_dictionaries/%s", fileName);

    // Open the file for writing (this will overwrite any existing file)
    FILE *file = fopen(fullPath, "w");
    if (file == NULL) {
        printf("Failed to create the file.\n");
        return;
    }

    // Write the header row with the language names
    for (int i = 0; i < dictionaries[chosenDictionary].numOfLanguages; i++) {
        fprintf(file, "%s", dictionaries[chosenDictionary].languages[i]);
        if (i != dictionaries[chosenDictionary].numOfLanguages - 1) {
            fprintf(file, ",");
        }
    }
    fprintf(file, "\n");

    // Write each word and its translations
    Word *currentWord = dictionaries[chosenDictionary].wordList;
    while (currentWord != NULL) {
        for (int i = 0; i < dictionaries[chosenDictionary].numOfLanguages; i++) {
            fprintf(file, "%s", currentWord->translations[i]);
            if (i != dictionaries[chosenDictionary].numOfLanguages - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
        currentWord = currentWord->next;
    }

    fclose(file);
    printf("Dictionary has been successfully exported to %s!\n", fullPath);
}
