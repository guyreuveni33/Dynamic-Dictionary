#include "../include/add_word.h"
/***********************************************************************************
* Function name: addWord
* Input: int *numOfDictionaries, Dictionary *dictionaries
* Output: None
* Function Operation: the function will add a new word and translate for an exist dictionary according
* to the user input
***********************************************************************************/
void addWord(Dictionary *dictionaries, int numOfDictionaries) {
    char seperator[2] = ",";
    int chosenDictionary;
    //this allocates place for the word by the heap
    Word *wordKeeper = (Word *) malloc(sizeof(Word));
    if (wordKeeper == NULL) {
        printf("The addition of the word has failed!\n");
        return;
    }
    //this print the user the dictionaries he has the option to insert word to
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
    //this get the number of dictionary the user is interesting to add word to
    scanf("%d", &chosenDictionary);
    //this creates a pointer to the first place in the wordlist
    Word *temp = dictionaries[chosenDictionary - 1].wordList;
    //this print the language the user need to type the word before the translations
    printf("Enter a word in ");
    for (int i = 0; i < dictionaries[chosenDictionary - 1].numOfLanguages; i++) {
        printf("%s", dictionaries[chosenDictionary - 1].languages[i]);
        if (i != dictionaries[chosenDictionary - 1].numOfLanguages - 1)
            printf(",");
        if (i == dictionaries[chosenDictionary - 1].numOfLanguages - 1)
            printf(":");
    }
    printf("\n");
    char translateOfTheUserCharacter;
    //this allocates place by the heap for the word
    char *translationOptions = (char *) malloc(sizeof(char));
    //in this line we are checking if the allocation has failed, and if so - print a message
    if (translationOptions == NULL) {
        printf("The addition of the word has failed!\n");
        return;
    }
    int sizeOfLanguageOptions = 0;
    //in this the user insert his word and the translations
    scanf(" %c", &translateOfTheUserCharacter);
    while (translateOfTheUserCharacter != '\n') {
        translationOptions[sizeOfLanguageOptions] = translateOfTheUserCharacter;
        translationOptions = realloc(translationOptions, sizeOfLanguageOptions + 2);
        //in this line we are checking if the allocation has failed, and if so - print a message
        if (translationOptions == NULL) {
            printf("The addition of the word has failed!\n");
            return;
        }
        sizeOfLanguageOptions++;
        scanf("%c", &translateOfTheUserCharacter);
    }
    //this reallocates the space by the types of the user
    translationOptions = realloc(translationOptions, sizeOfLanguageOptions + 2);
    //in this line we are checking if the allocation has failed, and if so - print a message
    if (translationOptions == NULL) {
        printf("The addition of the word has failed!\n");
        return;
    }
    //this insert '\0' in the last place
    translationOptions[sizeOfLanguageOptions] = '\0';
    char *token;
    int tokenCounter = 0;
    //this allocates space in heap for the word and his translations
    wordKeeper->translations = (char **) malloc(sizeof(char *));
    //in this line we are checking if the allocation has failed, and if so - print a message
    if (wordKeeper->translations == NULL) {
        printf("The addition of the word has failed!\n");
        return;
    }
    //this will break the whole type of the user, by ','
    token = strtok(translationOptions, seperator);
    wordKeeper->translations[tokenCounter++] = token;
    //this will keep broke the same word that the first token got, and will break it also by ','
    token = strtok(NULL, seperator);
    while (token != NULL) {
        //this will count the number of the words
        //this will reallocate memory for the word and translations
        wordKeeper->translations = realloc(wordKeeper->translations, sizeof(char *) * (tokenCounter + 1));
        //in this line we are checking if the allocation has failed, and if so - print a message
        if (wordKeeper->translations == NULL) {
            printf("The addition of the word has failed!\n");
            return;
        }
        //this will insert the word inside the space we allocated earlier
        wordKeeper->translations[tokenCounter++] = token;
        //this will keep broke the same word that the first token got, and will break it also by ','
        token = strtok(NULL, seperator);
    }
    //this for the case of first input from the user in order to insert the word inside the dictionary
    if (temp == NULL) {
        //this insert the word inside the dictionary
        dictionaries[chosenDictionary - 1].wordList = wordKeeper;
        //this insert value of NULL for the 'next' of the word,as the last word should have
        wordKeeper->next = NULL;
        printf("The word has been added successfully!\n");
        return;
    }
    //this for a case of the second word the user insert
    while (temp->next != NULL) {
        /*in order to insert the word in the last place, temp will keep moving forward, until he will arrive
        the last word exist*/
        temp = (Word *) temp->next;
    }
    //this insert the word the user insert, for the last place.
    temp->next = wordKeeper;
    //this insert value of NULL for the 'next' of the word,as the last word should have
    wordKeeper->next = NULL;
    printf("The word has been added successfully!\n");
    return;
}