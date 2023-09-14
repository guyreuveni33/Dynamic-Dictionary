/***********************
* Guy Haim Reuveni
***********************/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char **translations;
    struct Word *next;
} Word;
typedef struct {
    char **languages;
    int numOfLanguages;
    Word *wordList;
} Dictionary;

void freeTheNode(Word *current);

/***********************************************************************************
* Function name: flagCheack
* Input: int *flagOfNoOption, int *numOfDictionaries,int *flagForNotPrintMenu
* Output: None
* Function Operation: the function check if there is any dictionaries, and if there is no need to print the menu
* again in case the user chose a wrong option
***********************************************************************************/
void flagCheack(int *flagOfNoOption, int *numOfDictionaries, int *flagForNotPrintMenu) {
    if (*numOfDictionaries == 0) {
        printf("This option is not available right now, try again:\n");
        //this will make sure the user won't use options that are not available
        *flagOfNoOption = 0;
        *flagForNotPrintMenu = 1;
    }
}

/***********************************************************************************
* Function name: newDictionary
* Input: int *numOfDictionaries, Dictionary *dictionaries
* Output: None
* Function Operation: the function will add a new dictionary according to the user input
***********************************************************************************/
void newDictionary(int *numOfDictionaries, Dictionary *dictionaries) {
    char seperator[2] = ",";
    //in this line we allocated memory in size of char, in order to insert the languages name inside
    char *languageOptions = (char *) malloc(sizeof(char));
    //in this line we are checking if the allocation has failed, and if so - print a message
    if (languageOptions == NULL) {
        printf("The creation of the dictionary has failed!\n");
        return;
    }
    char character;
    int sizeOfLanguageOptions = 0;
    printf("Define a new dictionary:\n");
    scanf(" %c", &character);
    while (character != '\n') {
        //this insert the user input inside the allocated memory
        languageOptions[sizeOfLanguageOptions] = character;
        languageOptions = realloc(languageOptions, sizeOfLanguageOptions + 2);
        //in this line we are checking if the allocation has failed, and if so - print a message
        if (languageOptions == NULL) {
            printf("The creation of the dictionary has failed!\n");
            return;
        }
        //this line count the number of character the user typed
        sizeOfLanguageOptions++;
        scanf("%c", &character);
    }
    //in this line we allocated one more space in order to insert '\0'
    languageOptions = realloc(languageOptions, sizeOfLanguageOptions + 2);
    //in this line we are checking if the allocation has failed, and if so - print a message
    if (languageOptions == NULL) {
        printf("The creation of the dictionary has failed!\n");
        return;
    }
    char *token;
    int tokenCounter = 0;
    //this line insert '\0' in the last place
    languageOptions[sizeOfLanguageOptions] = '\0';
    //this line allocate space for the languages
    dictionaries->languages = (char **) malloc(sizeof(char *));
    //in this line we are checking if the allocation has failed, and if so - print a message
    if (dictionaries->languages == NULL) {
        printf("The creation of the dictionary has failed!\n");
        return;
    }
    //this will break the whole type of the user, by ','
    token = strtok(languageOptions, seperator);
    //this will insert the broken word inside the dictionary
    dictionaries->languages[tokenCounter++] = token;
    //this will keep broke the same word that the first token got, and will break it also by ','
    token = strtok(NULL, seperator);
    while (token != NULL) {
        //this will count the number of the words
        //this will reallocate memory for every language
        dictionaries->languages = realloc(dictionaries->languages, sizeof(char *) * (tokenCounter + 1));
        //in this line we are checking if the allocation has failed, and if so - print a message
        if (dictionaries->languages == NULL) {
            printf("The creation of the dictionary has failed!\n");
            return;
        }
        //this will insert the language inside the space we allocated earlier
        dictionaries->languages[tokenCounter++] = token;
        //this will keep broke the same word that the first token got, and will break it also by ','
        token = strtok(NULL, seperator);
    }
    //this raise the number of the dictionary counter
    *numOfDictionaries = *numOfDictionaries + 1;
    //this inserting the number of languages in their place by the struct
    dictionaries->numOfLanguages = tokenCounter;
    //this inserting NULL in their place by the struct
    dictionaries->wordList = NULL;
    printf("The dictionary has been created successfully!\n");
}

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
        wordKeeper->translations = realloc(wordKeeper->translations, sizeof(char*) * (tokenCounter + 1));
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

/***********************************************************************************
* Function name: deleteWord
* Input: Dictionary *dictionaries, int numOfDictionaries
* Output: None
* Function Operation: the function will delete a word from the dictionary
***********************************************************************************/
void deleteWord(Dictionary *dictionaries, int numOfDictionaries) {
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
    int chosenDictionary;
    //this get the number of dictionary the user is interesting to delete word from
    scanf("%d", &chosenDictionary);
    printf("Enter a word in ");
    //this print the dictionary the user will delete word from
    printf("%s:", dictionaries[chosenDictionary - 1].languages[0]);
    printf("\n");
    char character, yesOrNo;
    int counter = 0;
    Word *wordKeeper;
    //this allocates place by the heap for the word
    wordKeeper = (Word *) malloc(sizeof(Word));
    //in this line we are checking if the allocation has failed, and if so - print a message
    if (wordKeeper == NULL) {
        printf("The deletion of the word has failed!\n");
        return;
    }
    //this allocates place by the heap for the word translations
    wordKeeper->translations = (char **) malloc(sizeof(char *));
    //in this line we are checking if the allocation has failed, and if so - print a message
    if (wordKeeper->translations == NULL) {
        printf("The deletion of the word has failed!\n");
        return;
    }
    //this allocates place by the heap for the word in the 0 place
    wordKeeper->translations[0] = (char *) malloc(sizeof(char));
    //in this line we are checking if the allocation has failed, and if so - print a message
    if (wordKeeper->translations[0] == NULL) {
        printf("The deletion of the word has failed!\n");
        return;
    }
    //this get from the user the character of word he interests to delete
    scanf(" %c", &character);
    while (character != '\n') {
        //this count the number of character
        counter++;
        //this reallocates the space for the word in the heap according to the size
        wordKeeper->translations[0] = realloc(wordKeeper->translations[0], sizeof(char) * (counter + 1));
        //in this line we are checking if the allocation has failed, and if so - print a message
        if (wordKeeper->translations == NULL) {
            printf("The deletion of the word has failed!\n");
            return;
        }
        //this insert the word in the variable
        wordKeeper->translations[0][counter - 1] = character;
        scanf("%c", &character);
    }
    //this reallocates the size of the memory in order to add '/0' in the end
    wordKeeper->translations[0] = realloc(wordKeeper->translations[0], sizeof(char) * (counter + 2));
    //in this line we are checking if the allocation has failed, and if so - print a message
    if (wordKeeper->translations[0] == NULL) {
        printf("The deletion of the word has failed!\n");
        return;
    }
    //this insert '/0' in the last place
    wordKeeper->translations[0][counter] = '\0';
    //this check if the user want to delete the word for sure
    printf("Are you sure? (y/n)\n");
    scanf("%c", &yesOrNo);
    //in case the user change his mind for the deletes, he will get out from the function and will be back for the menu
    if (yesOrNo != 'y') {
        printf("The deletion of the word has been canceled.\n");
        return;
    }
    //this creates pointer of word struct
    Word *thereIsNoSuchWord;
    //the pointer will point wordlist of the chosen dictionary
    thereIsNoSuchWord = dictionaries[chosenDictionary - 1].wordList;
    //this check if the inserted word the user want to delete is exist, in case there is only one word in the wordlist
    if (thereIsNoSuchWord->next == NULL) {
        //this compare the words, and will return 0 if their value in the ASCII table is the same
        if (strcmp(wordKeeper->translations[0], thereIsNoSuchWord->translations[0]) != 0) {
            printf("The deletion of the word has failed!\n");
            return;
        }
    }
    /*this check if the inserted word the user want to delete is exist, in case there is more than one word in
    the wordlist*/
    if (thereIsNoSuchWord->next != NULL) {
        //this will run the pointer in order to check all the words
        while (thereIsNoSuchWord->next != NULL) {
            //this compare the words, and will return 0 if their value in the ASCII table is the same
            if (strcmp(wordKeeper->translations[0], thereIsNoSuchWord->translations[0]) != 0) {
                thereIsNoSuchWord = thereIsNoSuchWord->next;
            }
                //this check for the last word the pointer point to
            else if (thereIsNoSuchWord->next == NULL) {
                //this compare the words, and will return 0 if their value in the ASCII table is the same
                if (strcmp(wordKeeper->translations[0], thereIsNoSuchWord->translations[0]) != 0) {
                    printf("The deletion of the word has failed!\n");
                    return;
                }
            } else {
                //this will run the pointer forward
                thereIsNoSuchWord = thereIsNoSuchWord->next;
            }
        }
    }
    //this will create a pointer in order to check all the words
    Word *current;
    //this will create a pointer in order to keep one place behind the current pointer in the deletes order
    Word *previous;
    //this will create a pointer for the case there is need to delete the first word
    Word *firstWordForDelete;
    int counterOfDeleteCheck = 0;
    //the pointer place will be on the chosen dictionary, by the wordlist
    current = dictionaries[chosenDictionary - 1].wordList;
    //the pointer place will be on the chosen dictionary, by the wordlist
    previous = dictionaries[chosenDictionary - 1].wordList;
    //the pointer place will be on the chosen dictionary, by the wordlist
    firstWordForDelete = dictionaries[chosenDictionary - 1].wordList;
    Word *readyForDelete;
    //this will make sure the function won't get in unwanted loop
    int flagIfNotFirstWord = 0;
    //this will check if there are no word, and turn on the flag
    if (dictionaries[chosenDictionary - 1].wordList == NULL) {
        //this will turn on the flag
        flagIfNotFirstWord = 1;
        printf("The deletion of the word has failed!\n");
    }
        //this will check for a case of only one word
    else if (current->next == NULL) {
        //this compare the words, and will return 0 if their value in the ASCII table is the same
        if (strcmp(wordKeeper->translations[counterOfDeleteCheck], current->translations[0]) == 0) {
            //this will turn on the flag
            flagIfNotFirstWord = 1;
            //this inserting null for this wordlist, because there are no words to keep there
            dictionaries[chosenDictionary - 1].wordList = NULL;
            //this will free the word there is need to delete by the user demand
            free(current);
            printf("The word has been deleted successfully!\n");
        }
    }
        //this will check for a case of more than one word
    else if (firstWordForDelete->next != NULL) {
        //this compare the words, and will return 0 if their value in the ASCII table is the same
        if (strcmp(wordKeeper->translations[0], firstWordForDelete->translations[0]) == 0) {
            //this will point the pointer on the place there is demand to free
            readyForDelete = dictionaries[chosenDictionary - 1].wordList;
            //this will turn on the flag
            flagIfNotFirstWord = 1;
            //this make connection between the word without the word the user want to delete
            dictionaries[chosenDictionary - 1].wordList = dictionaries[chosenDictionary - 1].wordList->next;
            //this will free the word there is need to delete by the user demand
            free(readyForDelete);
            printf("The word has been deleted successfully!\n");
        }
    }
    if (flagIfNotFirstWord == 0) {
        //this for case of more than one word
        if (current->next != NULL) {
            while (current->next != NULL) {
                //this will run the current forward
                current = current->next;
                //this compare the words, and will return 0 if their value in the ASCII table is the same
                if (strcmp(wordKeeper->translations[0], current->translations[0]) == 0) {
                    //this make connection between the word without the word the user want to delete
                    previous->next = current->next;
                    //this will free the word there is need to delete by the user demand
                    free(current);
                    printf("The word has been deleted successfully!\n");
                }
            }
        }
    }
    free(wordKeeper);
}

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

int main() {
    int numOfDictionaries = 0;
    //in this line we set NULL value for the dictionaries we created
    Dictionary *dictionaries = NULL;
    int choiceOfUser, flagOfNoOption = 0, flagForNotPrintMenu = 0;
    do {
        //in this line we check if there is any need to print the menu again
        if (flagForNotPrintMenu == 0) {
            printf("Welcome to the dictionaries manager!\n"
                   "Choose an option:\n"
                   "1. Create a new dictionary.\n"
                   "2. Add a word to a dictionary.\n"
                   "3. Delete a word from a dictionary.\n"
                   "4. Find a word in a dictionary.\n"
                   "5. Delete a dictionary.\n"
                   "6. Exit.\n");
        }
        //in this line the user insert his input
        scanf("%d", &choiceOfUser);
        switch (choiceOfUser) {
            case 1:
                //this line is for the case of first time
                if (numOfDictionaries != 0) {
                    dictionaries = realloc(dictionaries, (numOfDictionaries + 1) * sizeof(Dictionary));
                    dictionaries[numOfDictionaries].wordList = NULL;
                    //in this line we are checking if the allocation has failed, and if so - print a message
                    if (dictionaries == NULL) {
                        printf("The creation of the dictionary has failed!\n");
                        break;
                    }
                    //this line is for the second dictionary and next
                } else {
                    dictionaries = (Dictionary *) malloc(sizeof(Dictionary));
                    dictionaries[0].wordList = NULL;
                    //in this line we are checking if the allocation has failed, and if so - print a message
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
                flagCheack(&flagOfNoOption, &numOfDictionaries,
                           &flagForNotPrintMenu);
                if (flagOfNoOption == 1) {
                    addWord(dictionaries, numOfDictionaries);
                    flagForNotPrintMenu = 0;
                }
                break;
            case 3:
                flagCheack(&flagOfNoOption, &numOfDictionaries,
                           &flagForNotPrintMenu);
                //in this line we check if the user have access to this option
                if (flagOfNoOption == 1) {
                    deleteWord(dictionaries, numOfDictionaries);
                    flagForNotPrintMenu = 0;
                }
                break;
            case 4:
                flagCheack(&flagOfNoOption, &numOfDictionaries,
                           &flagForNotPrintMenu);
                //in this line we check if the user have access to this option
                if (flagOfNoOption == 1) {
                    findWord(dictionaries, numOfDictionaries);
                    flagForNotPrintMenu = 0;
                }
                break;
            case 5:
                flagCheack(&flagOfNoOption, &numOfDictionaries,
                           &flagForNotPrintMenu);
                //in this line we check if the user have access to this option
                if (flagOfNoOption == 1) {
                    deleteDictionary(dictionaries, &numOfDictionaries);
                    //this reallocates the space of the dictionaries to the right value in the memory
                    dictionaries = realloc(dictionaries, (numOfDictionaries) * sizeof(Dictionary));
                    flagForNotPrintMenu = 0;
                }
                break;
            case 6:
                freeAllDictionaries(dictionaries, numOfDictionaries);
                printf("Bye!");
                break;
            default:
                printf("Wrong option, try again:\n");
                break;
        }
    } while (choiceOfUser != 6);
}
