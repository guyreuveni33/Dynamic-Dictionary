#include "../include/word_translate.h"

/***********************************************************************************
* Function name: findWord
* Input: Dictionary *dictionaries, int numOfDictionaries
* Output: None
* Function Operation: the function will find a word in the dictionary according to the user input
***********************************************************************************/
void findWord(Dictionary *dictionaries, int numOfDictionaries) {
    printf("Choose a dictionary:\n");
    //this print the user the dictionaries he has the option to search word
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
    int choosenDictionary, flagSearcher = 0, sizeOfWordSearch = 0, counterWordInTranslations = 1;
    //this get the number of dictionary the user is interesting to find word from
    scanf("%d", &choosenDictionary);
    printf("Enter a word in ");
    printf("%s:", dictionaries[choosenDictionary - 1].languages[0]);
    printf("\n");
    //this allocates space in the heap memory for the word
    char *wordToSearch = (char *) malloc(sizeof(char));
    //in this line we are checking if the allocation has failed, and if so - print a message
    if (wordToSearch == NULL) {
        printf("The search has failed successfully!\n");
        return;
    }
    char character;
    //this get the input from the user
    scanf(" %c", &character);
    while (character != '\n') {
        //this insert the chartcter inside the word in the place according to the counter
        wordToSearch[sizeOfWordSearch] = character;
        //this reallocates the space by the demand
        wordToSearch = realloc(wordToSearch, sizeOfWordSearch + 2);
        //in this line we are checking if the allocation has failed, and if so - print a message
        if (wordToSearch == NULL) {
            printf("The search has failed successfully!\n");
            return;
        }
        sizeOfWordSearch++;
        scanf("%c", &character);
    }
    //this reallocates the size by one in order to insert '/0'
    wordToSearch = realloc(wordToSearch, sizeOfWordSearch + 2);
    //in this line we are checking if the allocation has failed, and if so - print a message
    if (wordToSearch == NULL) {
        printf("The search has failed successfully!\n");
        return;
    }
    //this insert '\0' in the last place
    wordToSearch[sizeOfWordSearch] = '\0';
    //this creates a pointer for the dictionary wordlist
    Word *searchRun = dictionaries[choosenDictionary - 1].wordList;
    //this create a pointer and allocate space in sizeof char for him
    Word *flagLocation = (char *) malloc(sizeof(char));
    //in this line we are checking if the allocation has failed, and if so - print a message
    if (flagLocation == NULL) {
        printf("The search has failed successfully!\n");
        return;
    }
    //this inserting '\0' for the pointer value
    flagLocation = '\0';
    //this for case there is only one word
    if (searchRun->next == NULL) {
        //this compare the words, and will return 0 if their value in the ASCII table is the same
        if (strcmp(searchRun->translations[0], wordToSearch) == 0) {
            //This line save the place of the word we need to search
            flagLocation = searchRun;
            //this line turn on the flag in order to not get un need iteration
            flagSearcher = 1;
        }
    }
    //this line check for the word in all the dictionary expect the last word
    while (searchRun->next != NULL) {
        //this compare the words, and will return 0 if their value in the ASCII table is the same
        if (strcmp(searchRun->translations[0], wordToSearch) == 0) {
            //this line save the place of the word we need to search
            flagLocation = searchRun;
            //this line turn on the flag in order to not get un need iteration
            flagSearcher = 1;
        }
        //this will move the pointer forward
        searchRun = searchRun->next;
    }
    //This line check the last word in the dictionary
    if (strcmp(searchRun->translations[0], wordToSearch) == 0) {
        //This line save the place of the word we need to search
        flagLocation = searchRun;
        //this line turn on the flag in order to not get un need iteration
        flagSearcher = 1;
    }
    //this if won't happen in if the flag turned on - there are such word as the user searched
    if (flagSearcher == 1) {
        //this prints the translations of the searched word
        printf("The translations are:\n");
        for (int i = 1; i < dictionaries[choosenDictionary - 1].numOfLanguages; i++) {
            printf("%s: ", dictionaries[choosenDictionary - 1].languages[i]);
            Word *thePrinterOfTranslate;
            thePrinterOfTranslate = dictionaries[choosenDictionary - 1].wordList;
            printf("%s", flagLocation->translations[i]);
            if (i != dictionaries[choosenDictionary - 1].numOfLanguages - 1)
                printf(", ");
        }
        printf("\n");
    }
    //This will be print only if there are no such word like the word the user tried to search
    if (flagSearcher == 0) {
        printf("There are no translations for \"%s\" in this dictionary.\n", wordToSearch);
    }
    free(wordToSearch);
}