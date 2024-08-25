#include "sort_dictionary.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int compareWords(const void *a, const void *b) {
    const Word *wordA = *(const Word **)a;
    const Word *wordB = *(const Word **)b;

    // Compare based on the first translation (e.g., English)
    return strcmp(wordA->translations[0], wordB->translations[0]);
}

void sortWordsInDictionary(Dictionary *dictionaries, int numOfDictionaries) {
    if (numOfDictionaries == 0) {
        printf("No dictionaries available to sort.\n");
        return;
    }

    printf("Choose a dictionary to sort:\n");
    for (int i = 0; i < numOfDictionaries; i++) {
        for (int j = 0; j < dictionaries[i].numOfLanguages; j++) {
            if (j == 0)
                printf("%d. ", (i + 1));
            printf("%s", dictionaries[i].languages[j]);
            if (j != (dictionaries[i].numOfLanguages) - 1)
                printf(",");
        }
        printf("\n");
    }

    int sortChoice;
    char input[10];
    if (fgets(input, sizeof(input), stdin) != NULL && sscanf(input, "%d", &sortChoice) == 1) {
        if (sortChoice >= 1 && sortChoice <= numOfDictionaries) {
            Dictionary *dictionary = &dictionaries[sortChoice - 1];

            int numWords = 0;
            Word *current = dictionary->wordList;

            // Count the number of words
            while (current != NULL) {
                numWords++;
                current = current->next;
            }

            if (numWords == 0) {
                printf("The selected dictionary is empty. Nothing to sort.\n");
                return;
            }

            // Create an array of pointers to Word structs
            Word **wordArray = (Word **)malloc(numWords * sizeof(Word *));
            current = dictionary->wordList;
            for (int j = 0; j < numWords; j++) {
                wordArray[j] = current;
                current = current->next;
            }

            // Sort the words using qsort and the compareWords function
            qsort(wordArray, numWords, sizeof(Word *), compareWords);

            // Rebuild the linked list with the sorted words
            dictionary->wordList = wordArray[0];
            current = dictionary->wordList;
            for (int j = 1; j < numWords; j++) {
                current->next = wordArray[j];
                current = current->next;
            }
            current->next = NULL;

            // Free the temporary array
            free(wordArray);

            printf("Dictionary %s sorted alphabetically.\n", dictionary->languages[0]);
        } else {
            printf("Invalid choice. No dictionary sorted.\n");
        }
    } else {
        printf("Invalid input. No dictionary sorted.\n");
    }
}
