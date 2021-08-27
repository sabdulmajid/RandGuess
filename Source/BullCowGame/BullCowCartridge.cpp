// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame(); // Setting up the game

    PrintLine(TEXT("The HiddenWord is: %s. \nIt is %i characters long."), *HiddenWord, HiddenWord.Len()); // Debug line

}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    

    
    /*
    If game over, then ClearScreen() and SetupGame().
    Else check PlayerGuess 
    */
   if (bGameOver)
   {
        ClearScreen();
        SetupGame();
   }
   else
   {
        if (Input == HiddenWord)
        {
            PrintLine(TEXT("Victory! Well done, you won!"));
            // bGameOver = true;
        }
        else
        {
            if (Input.Len() != HiddenWord.Len())
            {
                PrintLine(TEXT("Try again, the hidden word is %i characters long."), HiddenWord.Len()); // Magic number hardcoded!
            }

            PrintLine(TEXT("You lost! Nice try!"));
            // bGameOver = true;
    }
   }

   

    PrintLine(Input);
}

void UBullCowCartridge::SetupGame()
{
    // Welcome message
    PrintLine(TEXT("Welcome to the Bull-Cow Game!"));

    HiddenWord = TEXT("take");
    Lives = 4;
    bGameOver = false;
    
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len()); 
    PrintLine(TEXT("Type in your guess. \nPress enter to continue...")); // Prompting player for guess
   
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again..."))
}