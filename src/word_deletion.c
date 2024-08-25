#include "../include/word_deletion.h"
#include <string.h>

/***********************************************************************************
* Function name: deleteWord
* Input: Dictionary *dictionaries, int numOfDictionaries
* Output: None
* Function Operation: The function will delete a word from the dictionary
***********************************************************************************/
void deleteWord(Dictionary *dictionaries, int numOfDictionaries) {
    // Print the list of dictionaries
    printf("Choose a dictionary:\n");
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

    int chosenDictionary;
    scanf("%d", &chosenDictionary);
    getchar();  // Consume newline character

    printf("Enter a word in %s:\n", dictionaries[chosenDictionary - 1].languages[0]);
    char wordToDelete[100];
    fgets(wordToDelete, sizeof(wordToDelete), stdin);
    wordToDelete[strcspn(wordToDelete, "\n")] = 0;  // Remove the newline character

    printf("Are you sure? (y/n)\n");
    char yesOrNo = getchar();
    getchar();  // Consume newline character

    if (yesOrNo != 'y') {
        printf("The deletion of the word has been canceled.\n");
        return;
    }

    Word *current = dictionaries[chosenDictionary - 1].wordList;
    Word *previous = NULL;

    while (current != NULL) {
        if (strcmp(current->translations[0], wordToDelete) == 0) {
            if (previous == NULL) {
                // Deleting the first word
                dictionaries[chosenDictionary - 1].wordList = current->next;
            } else {
                previous->next = current->next;
            }
            free(current->translations);
            free(current);
            printf("The word has been deleted successfully!\n");
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("The word was not found in the dictionary.\n");
}
