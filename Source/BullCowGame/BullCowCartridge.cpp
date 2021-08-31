#include "BullCowCartridge.h"
#include "HiddenWordList.h"
#include "Math/UnrealMathUtility.h"


// BeginPlay() is an inherited method - so basically override the method (of Super) to do the same thing that the inherited method does - Meant for UE4 only.
;void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();

    FBullCowCount Count;

    Isograms = GetValidWords(Words);

    SetupGame();   
}

// The OnInput() function clears the screen and calls the SetupGame() function to start the game.
void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if (bGameOver == true) // Could also be written as 'if (bGameOver)' only; would work perfectly.
    {
        ClearScreen();
        SetupGame();
    }
    else // Checking PlayerGuess
    {
       ProcessGuess(PlayerInput);
    }
}

// The SetupGame() function welcomes the player to the game and does all of the initializing processes.
void UBullCowCartridge::SetupGame()
{
    PrintLine(TEXT("Welcome to the Bull-Cow Game!"));

    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len();
    bGameOver = false;
    
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len()); 
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Type in your guess and \npress enter to continue...")); // Prompting player for guess
    PrintLine(TEXT("The hidden word is: %s"), *HiddenWord); // Debugging line to make it easier to develop the game
}

// The EndGame() function ends the game and prompts the player to try again.
void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again..."));
}

// The ProcessGuess() function runs the Guess through a series of IF statements to see whether they satisfy the game requirements.
void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    /*  
        PSEUDOCODE:
        Check if the inputted guess is an isogram
        Check if the inputted guess is right number of characters

        Remove a live if the guess is incorrect

        Check if the lives are GREATER than 0
        If so, then prompt to guess again and show remaining lives left
        If not, then call GameOver() and also show HiddenWord
        Prompt the player to play again
    */


    // If the guess matches, display so to the user with a celebratory message and call EndGame() function to restart game.
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("Victory! Well done, you won!"));
        EndGame();
        return;
    }
    
    // When wrong word guessed of NOT same length, let player know how long the word is and show lives.
    if (Guess.Len() != HiddenWord.Len())
    {    
        PrintLine(TEXT("The hidden word is %i is letters long"), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try again. \nYou have %i live(s) left."), Lives);        
        return;
    }

    // If there are repeating letters in the Guess, let the player know that there are none - and DO NOT deduct a live for doing so.
    if (!IsIsogram(Guess))
    {        
        PrintLine(TEXT("No repeating letters, guess again!"));
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


    FBullCowCount Score = GetBullCows(Guess);
    PrintLine(TEXT("You have %i Bulls and %i Cows left!"), Score.Bulls, Score.Cows);

    // Displaying the lives to the player
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}
 
// A function which checks whether the inputted word has repeating letters in it.
bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    /*  
        PSEUDOCODE:
        For each letter
        Start at the first element (elements[0])
        Compare against the next letter
        Until we reach [Word.Len() - 1]
        If any letters are the SAME, return FALSE
    */

    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }   
        }
    }

    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8)
        {
            if (IsIsogram(Word))
            {
                ValidWords.Emplace(Word);
            }
            
        }
    }
    return ValidWords;

}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{

    /*  
        PSEUDOCODE:
        For every: index of the Guess is the same as the index of the HiddenWord, increment BullCount
        If not a Bull, then increment CowCount
        Do this until the both the words are completely analyzed 
        Return the two Out Parameters: BullCount and CowCount
    */

    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }
        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}