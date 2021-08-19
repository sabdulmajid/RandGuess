// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Welcome message
    PrintLine(TEXT("Welcome to the Bull-Cow Game!"));
    PrintLine(TEXT("Guess the 4 letter word!")); // Magic number hardcoded!
    PrintLine(TEXT("Please enter to continue..."));

    // Setting up the game
    HiddenWord = TEXT("take");

    // Settings lives

    // Prompting player for guess
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    
    if (Input == HiddenWord)
    {
        PrintLine(TEXT("Victory! Well done, you won!"));

    }
    else
    {
        PrintLine(TEXT("You lost! Nice try!"));
    }
    
    PrintLine(Input);
}