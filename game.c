#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define AMOUNT 21
//---------------------------------------------------------------------------------------------------------------------
// a1.c
//
// My implementation of game "Hangman". In Hangman there are at least two players where one thinks of a word and the 
// other(s) try to guess it by suggesting letters. The player(s) only have a limited number of available guesses.
// When the player(s) do not have any guesses left, they loose the game and win if the word was found before that.
//
// Group: Group 3
//
// Author: 12134500
//---------------------------------------------------------------------------------------------------------------------
//



void fillEmptySpaces(char string_to_fill[AMOUNT], char word[AMOUNT]);
void arrayOutput(char array_to_output[AMOUNT], char word[AMOUNT]);
void initializingGame(char word_to_look_for[AMOUNT], char used_letters[AMOUNT],char difference[AMOUNT]);
void getGuess(int attemps);
void displayWon(void);
void displayLost(char word_to_look_for[AMOUNT]);
int isLetterMatched(char letter, char input[AMOUNT], char presence[AMOUNT]);
int wasLetterUsed(char arrayOfUsedLetters[AMOUNT], char letterToAdd);
int isAllGuessed(char word1[AMOUNT]);


//---------------------------------------------------------------------------------------------------------------------
///
/// Main function. Takes in a word to be guessed and letter(s), checks if the letter is inside. 
/// If true, the algorithm is repeated until the word is fully guessed. If false, attempts are 
/// decreased one by one until none are left. If attempts reach 0, then you lose.
///
//
int main(void)
{
    char word_to_look_for[AMOUNT];
    char used_letters[AMOUNT];
    char difference[AMOUNT];
    int attemps = 5;
    int new_match;
    int old_match = 0;
    initializingGame(word_to_look_for, used_letters, difference);//booting up...
    while (attemps > 0)
    {
      int quit = 0;
      char letter[AMOUNT];
      scanf("%20s", letter);
      int guessLength = strlen(letter); //getting the guess length for comfort
      for (int i = 0; i < guessLength; i++)
      {
        char guess = letter[i]; 
        if (wasLetterUsed(used_letters, guess)) // checking if letter was used
        {
          printf("Letter %c was used already!", toupper(guess));
          getGuess(attemps);
          continue;
        } 
        new_match = old_match + isLetterMatched(guess, word_to_look_for, difference);
        if (new_match == old_match) //chesking if old and new guesses are the same(no match within the word found)
        {
          attemps--;
          arrayOutput(difference, word_to_look_for);
          if (attemps == 0)// when attempts are zero, display loss function
          {
            displayLost(word_to_look_for);
            quit = 1;
            break;
          }
          getGuess(attemps); // if not zero, continue the game
          continue;
        }
        else
        {
          arrayOutput(difference, word_to_look_for);
          if (isAllGuessed(difference) == 1)//checking if indication array all ones, when true, display win function
          {
            displayWon();
            quit = 1;
            break;
          }
          getGuess(attemps);//if not, continue, attempts don`t decrease
          continue;
        }
        old_match = new_match;//updating old_match
      }
      if(quit)//indicator to break from while loop
      {
        break;
      }   
    }
}  



//---------------------------------------------------------------------------------------------------------------------
///
/// fills the array with underscores, ads new null determinator to the end
///
/// @param string_to_fill an array to fill
/// @param word used as length parametr
///
/// @return filled array
//
void fillEmptySpaces(char string_to_fill[AMOUNT], char word[AMOUNT])
{
  int i;
  for(i = 0;word[i] != '\0'; i++) 
  {
    string_to_fill[i] = '_';
  }
  string_to_fill[i] = '\0';
}



//---------------------------------------------------------------------------------------------------------------------
///
/// compares word, which is being guessed, to an array, which indicates already guessed letters
/// prints out only guessed letters as visible
///
/// @param array_to_output an array to output
/// @param word an indication array filled with 1 on places, where letters were guessed
///
/// @return original word with only guessed letters as visible
//
void arrayOutput(char array_to_output[AMOUNT], char word[AMOUNT])
{
   for(int i = 0;array_to_output[i] != '\0'; i++)
        {
          if(array_to_output[i] == 1)
          {
            printf("%c ",  toupper(word[i]));
          }
          else
          {
            printf("_ ");
          }
        }  
} 



//---------------------------------------------------------------------------------------------------------------------
///
/// checks, if entered letter is inside the word
/// modifies the indication array on places, where the guess letter is found
///
/// @param letter entered letter
/// @param input original word
/// @param presence indication array filled with ones
///
/// @return number of matches
//
int isLetterMatched(char letter, char input[AMOUNT], char presence[AMOUNT])
  {
    int num_Matches = 0;
    for(int i = 0;input[i] != '\0'; i++)
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



//---------------------------------------------------------------------------------------------------------------------
///
///checks, if entered letter was already used
///if not, modifies an array of used letters
///
/// @param arrayOfUsedLetters string with previously entered guesses
/// @param letterToAdd new guess
///
/// @return 1, if letter was used, 0, if not
//
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
    for(int i = 0;i < AMOUNT; i++)
    {
      if(arrayOfUsedLetters[i]=='\0')
      {
        arrayOfUsedLetters[i] = letterToAdd;
        arrayOfUsedLetters[i + 1] = '\0';
        return 0;
      }
    }
  }
  return 1;
}



//---------------------------------------------------------------------------------------------------------------------
///
///start game, fills arrays with underscores
///
/// @param word_to_look_for original word
/// @param used_letters array of used letters
/// @param difference indication array filled with ones
///
/// @return printf`s
//
void initializingGame(char word_to_look_for[AMOUNT], char used_letters[AMOUNT],char difference[AMOUNT])
{
  printf("Word to look for:\n > ");
  scanf("%s", word_to_look_for);
  fillEmptySpaces(difference, word_to_look_for);
  fillEmptySpaces(used_letters, used_letters);
  printf("Attempts left: 5\nEnter a letter:\n > ");
}



//---------------------------------------------------------------------------------------------------------------------
///
///compares every element of indication array with 1
///if true, returns 1, indicating that the word is guessed
///
/// @param word1 indication array with ones
///
/// @return 1 if matched, 0 if not
//
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



//function, that prints attempts and asks forr new letter
void getGuess(int attemps)
{
  printf("\nAttempts left: %d\nEnter a letter:\n > ", attemps);
}



//prints lost messenge
void displayLost(char word_to_look_for[AMOUNT])
{
  printf("\nLOST! The Word was %s\n", word_to_look_for);
}



//prints won messenge
void displayWon(void)
{
  printf("\nCongratulations, you won!\n");
}
