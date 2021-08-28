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

    
   if (bGameOver)
   {
        ClearScreen();
        SetupGame();
   }
   else // Checking PlayerGuess
   {
        if (Input == HiddenWord)
        {
            PrintLine(TEXT("Victory! Well done, you won!"));
            EndGame();
        }
        else
        {
            --Lives;
            PrintLine(TEXT("Lost a life!"));
            if (Lives > 0)
            {
                if (Input.Len() != HiddenWord.Len())
                {    
                    PrintLine(TEXT("Sorry, try again. \nYou have %i lives left."), Lives);
                }           
            }
            else
            {
                PrintLine(TEXT("You have no lives left!"));
                EndGame();
            }
    }
}

   

    PrintLine(Input);
}

void UBullCowCartridge::SetupGame()
{
    // Welcome message
    PrintLine(TEXT("Welcome to the Bull-Cow Game!"));

    HiddenWord = TEXT("take");
    Lives = HiddenWord.Len();
    bGameOver = false;
    
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len()); 
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Type in your guess and \npress enter to continue...")); // Prompting player for guess
   
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again..."));
}
