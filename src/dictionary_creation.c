#include "../include/dictionary_creation.h"

/***********************************************************************************
* Function name: newDictionary
* Input: int *numOfDictionaries, Dictionary *dictionaries
* Output: None
* Function Operation: the function will add a new dictionary according to the user input
***********************************************************************************/
void newDictionary(int *numOfDictionaries, Dictionary *dictionaries) {
    char separator[2] = ",";
    char *languageOptions = (char *)malloc(sizeof(char));

    if (languageOptions == NULL) {
        printf("The creation of the dictionary has failed!\n");
        return;
    }

    char character;
    int sizeOfLanguageOptions = 0;
    printf("Define a new dictionary:\n");
    scanf(" %c", &character);
    while (character != '\n') {
        languageOptions[sizeOfLanguageOptions] = character;
        languageOptions = realloc(languageOptions, sizeOfLanguageOptions + 2);

        if (languageOptions == NULL) {
            printf("The creation of the dictionary has failed!\n");
            return;
        }

        sizeOfLanguageOptions++;
        scanf("%c", &character);
    }

    languageOptions = realloc(languageOptions, sizeOfLanguageOptions + 2);

    if (languageOptions == NULL) {
        printf("The creation of the dictionary has failed!\n");
        return;
    }

    char *token;
    int tokenCounter = 0;
    languageOptions[sizeOfLanguageOptions] = '\0';

    dictionaries->languages = (char **)malloc(sizeof(char *));
    if (dictionaries->languages == NULL) {
        printf("The creation of the dictionary has failed!\n");
        return;
    }

    token = strtok(languageOptions, separator);
    dictionaries->languages[tokenCounter++] = token;
    token = strtok(NULL, separator);
    while (token != NULL) {
        dictionaries->languages = realloc(dictionaries->languages, sizeof(char *) * (tokenCounter + 1));
        if (dictionaries->languages == NULL) {
            printf("The creation of the dictionary has failed!\n");
            return;
        }
        dictionaries->languages[tokenCounter++] = token;
        token = strtok(NULL, separator);
    }

    *numOfDictionaries = *numOfDictionaries + 1;
    dictionaries->numOfLanguages = tokenCounter;
    dictionaries->wordList = NULL;
    printf("The dictionary has been created successfully!\n");
}
