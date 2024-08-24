#include "../include/free_functions.h"

/***********************************************************************************
* Function name: freeAllDictionaries
* Input: Dictionary *dictionaries
* Output: None
* Function Operation: the function will delete all the dictionaries
***********************************************************************************/

void freeAllDictionaries(Dictionary *dictionaries, int numOfDictionaries) {
    for (int i = 0; i < numOfDictionaries; i++) {
        //this function will delete the words from the dictionary
        freeTheNode(dictionaries[i].wordList);
        //this will delete the languages from the dictionary
        free(dictionaries[i].languages[0]);
        //this will insert null to the languages in the [0]
        dictionaries[i].languages[0] = NULL;
        //this will delete the languages from the dictionary
        free(dictionaries[i].languages);
        //this will insert null to the languages in the [0]
        dictionaries[i].languages = NULL;
    }
    //this will free the dictionary
    free(dictionaries);
    //this will insert null value for the dictionaries
    dictionaries = NULL;
}

/***********************************************************************************
* Function name: freeTheNode
* Input: Word *current
* Output: None
* Function Operation: the function will delete all the words with recursive
***********************************************************************************/
void freeTheNode(Word *current) {
    //this will stop the loop of the recursive
    if (current == NULL)
        return;
    //this will work and run the pointer by recursive
    freeTheNode(current->next);
    //this will free place in the heap
    free(current->translations[0]);
    //this will insert null value
    current->translations = NULL;
    //this will free the place of the pointer
    free(current->translations);
    //this will insert null value
    current->translations = NULL;
    //this will free the place of the pointer
    free(current);
    //this will insert null value
    current = NULL;
}


/***********************************************************************************
* Function name: deleteDictionary
* Input: Dictionary *dictionaries, int *numOfDictionaries
* Output: None
* Function Operation: the function will delete dictionary
***********************************************************************************/
void deleteDictionary(Dictionary *dictionaries, int *numOfDictionaries) {
    printf("Choose a dictionary:\n");
    //this print the user the dictionaries he has the option to search word
    for (int i = 0; i < *numOfDictionaries; i++) {
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
    char yesOrNo;
    //this get the number of dictionary the user is interesting to delete
    scanf("%d", &chosenDictionary);
    //this check if the user want to delete the dictionary for sure
    printf("Are you sure? (y/n)\n");
    scanf(" %c", &yesOrNo);
    if (yesOrNo != 'y') {
        printf("The deletion of the dictionary has been canceled.\n");
        return;
    }
    //this creates pointer from word kind
    Word *current;
    //this point the pointer on the dictionary the user chose
    current = dictionaries[chosenDictionary - 1].wordList;
    Word *pointerForDelete;
    pointerForDelete = dictionaries[chosenDictionary - 1].wordList;
    Dictionary *previous;
    //this creates space in the heap for the dictionary that will be deleted
    Dictionary *dictionaryForDelete = (Dictionary *) malloc(sizeof(Dictionary));
    //in this line we are checking if the allocation has failed, and if so - print a message
    if (dictionaryForDelete == NULL) {
        printf("The deletion of the dictionary has failed!\n");
        return;
    }
    //this point the pointer on the chosen dictionary
    *dictionaryForDelete = dictionaries[chosenDictionary - 1];
    free(dictionaries[chosenDictionary - 1].languages[0]);
    dictionaries[chosenDictionary - 1].languages[0] = NULL;
    free(dictionaries[chosenDictionary - 1].languages);
    dictionaries[chosenDictionary - 1].languages = NULL;
    freeTheNode(dictionaries[chosenDictionary - 1].wordList);


    //this deletes the dictionary by free his space
    free(dictionaryForDelete);
    //this set the values of each dictionary so the palace of the deleted dictionary won't affect the order
    for (int i = chosenDictionary; i < *numOfDictionaries; i++) {
        dictionaries[i - 1] = dictionaries[i];
    }
    printf("The dictionary has been deleted successfully!\n");
    dictionaries[*numOfDictionaries - 1] = *dictionaryForDelete;
    //this reset the number of the dictionary
    *numOfDictionaries = *numOfDictionaries - 1;
    //in this line we are checking if the allocation has failed, and if so - print a message
    if (dictionaryForDelete == NULL) {
        printf("The deletion of the dictionary has failed!\n");
        return;
    }
}
