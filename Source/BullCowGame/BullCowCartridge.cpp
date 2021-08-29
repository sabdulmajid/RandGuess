// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

// BeginPlay() is an inherited method - so basically override the method (of Super) to do the same thing that the inherited method does - Meant for UE4 only.
void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();

    SetupGame();

}

// The OnInput() function clears the screen and calls the SetupGame() function to start the game.
void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{

    if (bGameOver == true) // Could also be written as 'if (bGameOver)' only; would work perfectly.
    {
        ClearScreen();
        SetupGame();
    }
    else // Checking PlayerGuess
    {
       ProcessGuess(Input);
    }

}

// The SetupGame() function welcomes the player to the game and does all of the initializing processes.
void UBullCowCartridge::SetupGame()
{
    // Welcome message
    PrintLine(TEXT("Welcome to the Bull-Cow Game!"));

    HiddenWord = TEXT("takes");
    Lives = HiddenWord.Len();
    bGameOver = false;
    
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len()); 
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Type in your guess and \npress enter to continue...")); // Prompting player for guess

    const TCHAR HW[] = TEXT("takes");
    
   
}

// The EndGame() function ends the game and prompts the player to try again.
void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again..."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    // If the guess matches, display so to the user with a celebratory message and call EndGame() function to restart game.
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("Victory! Well done, you won!"));
        EndGame();
        return;
    }

    // If there are repeating letters in the Guess, let the player know that there are none - and DO NOT deduct a live for doing so.
    if (!IsIsogram())
    {
        
        PrintLine(TEXT("No repeating letter, guess again"));
        return;
    }
    
    // When wrong word guessed of NOT same length, let player know how long the word is and show lives.
    if (Guess.Len() != HiddenWord.Len())
    {    
        PrintLine(TEXT("The hidden word is %i is letters long"), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try again. \nYou have %i live(s) left."), Lives);        
        return;
    }

    // Remove a life if the Guess does not match the HiddenWord - this will only happen if the first IF statement is not satisfied.
    PrintLine(TEXT("Lost a life!"));
    --Lives;

    // When lives reaches 0, display to the player the hidden word and call the EndGame() function to restart the game.
    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);

        EndGame();          
        return;
    }

    // Displaying the lives to the player
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
    
}
 
bool UBullCowCartridge::IsIsogram()
{
    /*  PSEUDOCODE:
        For each letter
        Start at the first element (elements[0])
        Compare against the next letter
        Until we reach [Word.Len() - 1]
        If any letters are the SAME, return FALSE
    */
    return true;
}