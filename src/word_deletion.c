#include "../include/word_deletion.h"
#include <string.h>

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