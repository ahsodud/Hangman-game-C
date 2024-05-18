#include <assert.h>
#include <stdio.h>
#include <string.h>

#define AMOUNT 21

void fillEmptySpaces(char string_to_fill[AMOUNT], char word[AMOUNT]);
void arrayOutput(char array_to_output[AMOUNT], char word[AMOUNT]);
void initializingGame(char word_to_look_for[AMOUNT], char used_letters[AMOUNT], char difference[AMOUNT]);
void getGuess(int attemps);
void displayWon(void);
void displayLost(char word_to_look_for[AMOUNT]);
int isLetterMatched(char letter, char input[AMOUNT], char presence[AMOUNT]);
int wasLetterUsed(char arrayOfUsedLetters[AMOUNT], char letterToAdd);
int isAllGuessed(char word1[AMOUNT]);

void test_fillEmptySpaces() {
    char string_to_fill[AMOUNT];
    char word[AMOUNT] = "HELLO";
    fillEmptySpaces(string_to_fill, word);
    assert(strcmp(string_to_fill, "_____") == 0);
}

void test_arrayOutput() {
    char array_to_output[AMOUNT] = {1, 0, 1, 0, 0, '\0'};
    char word[AMOUNT] = "HELLO";
    printf("Expected output: H _ L _ _ \nActual output:   ");
    arrayOutput(array_to_output, word);
    printf("\n");
}

void test_isLetterMatched() {
    char word[AMOUNT] = "HELLO";
    char presence[AMOUNT] = {0};
    int matches = isLetterMatched('L', word, presence);
    assert(matches == 2);
    assert(presence[2] == 1);
    assert(presence[3] == 1);
}

void test_wasLetterUsed() {
    char used_letters[AMOUNT] = "AEIOU";
    int result = wasLetterUsed(used_letters, 'A');
    assert(result == 1);
    result = wasLetterUsed(used_letters, 'B');
    assert(result == 0);
    assert(strcmp(used_letters, "AEIOUB") == 0);
}

void test_isAllGuessed() {
    char word[AMOUNT] = {1, 1, 1, 1, 1, '\0'};
    assert(isAllGuessed(word) == 1);
    word[1] = 0;
    assert(isAllGuessed(word) == 0);
}

int main() {
    test_fillEmptySpaces();
    test_arrayOutput();
    test_isLetterMatched();
    test_wasLetterUsed();
    test_isAllGuessed();

    printf("All tests passed!\n");
    return 0;
}

//---------------------------------------------------------------------------------------------------------------------

void fillEmptySpaces(char string_to_fill[AMOUNT], char word[AMOUNT])
{
  int i;
  for(i = 0; word[i] != '\0'; i++) 
  {
    string_to_fill[i] = '_';
  }
  string_to_fill[i] = '\0';
}

void arrayOutput(char array_to_output[AMOUNT], char word[AMOUNT])
{
   for(int i = 0; array_to_output[i] != '\0'; i++)
        {
          if(array_to_output[i] == 1)
          {
            printf("%c ", toupper(word[i]));
          }
          else
          {
            printf("_ ");
          }
        }  
} 

int isLetterMatched(char letter, char input[AMOUNT], char presence[AMOUNT])
{
    int num_Matches = 0;
    for(int i = 0; input[i] != '\0'; i++)
    {
      input[i] = toupper(input[i]);
      if(presence[i] == 1)
      {
        continue;
      }
      if (toupper(letter) == toupper(input[i]))
      {
        presence[i] = 1;
        num_Matches++;
      }
    }
    return num_Matches;
}

int wasLetterUsed(char arrayOfUsedLetters[AMOUNT], char letterToAdd)
{
  int arePresent = 0;
  for(int i = 0; arrayOfUsedLetters[i] != '\0'; i++)
  {
    if(toupper(letterToAdd) == toupper(arrayOfUsedLetters[i]))
    {
      return 1;
    }
  }
  if (arePresent == 0)
  {
    for(int i = 0; i < AMOUNT; i++)
    {
      if(arrayOfUsedLetters[i] == '\0')
      {
        arrayOfUsedLetters[i] = letterToAdd;
        arrayOfUsedLetters[i + 1] = '\0';
        return 0;
      }
    }
  }
  return 1;
}

void initializingGame(char word_to_look_for[AMOUNT], char used_letters[AMOUNT], char difference[AMOUNT])
{
  printf("Word to look for:\n > ");
  scanf("%s", word_to_look_for);
  fillEmptySpaces(difference, word_to_look_for);
  fillEmptySpaces(used_letters, used_letters);
  printf("Attempts left: 5\nEnter a letter:\n > ");
}

int isAllGuessed(char word1[AMOUNT])
{
  for (int i = 0; word1[i] != '\0'; i++)
  {
    if(word1[i] == 1)
    {
      continue;
    }
    else
    {
      return 0;
    }
  }
  return 1;
}

void getGuess(int attemps)
{
  printf("\nAttempts left: %d\nEnter a letter:\n > ", attemps);
}

void displayLost(char word_to_look_for[AMOUNT])
{
  printf("\nLOST! The Word was %s\n", word_to_look_for);
}

void displayWon(void)
{
  printf("\nCongratulations, you won!\n");
}
