/* This file contains all the declaration of the classes and functions
that serves as the backend of the game*/

#pragma once
#include <string>


// This is done to make types more in accordance to the unreal standards
using int32 = int;
using FString = std::string;


// all Variables initialized to zero.
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus 
{
	Invalid,
	OK, 
	NO_Isogram,
	Wrong_Length,
	Not_lowercase
};

class FBullCowGame 
{
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; 

	void Reset();
	FBullCowCount SubmitValidGuess(FString);
	
// Please try and ignore this and focus on the interface above
private:
	// see constructors for initial values
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIswon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
