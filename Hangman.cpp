#include <iostream>  // For input/output operations
#include <vector>    // For using the vector container
#include <string>    // For string manipulations
#include <ctime>     // For random number generation based on time
#include <cstdlib>   // For rand() and srand()
#include <cctype>    // For character handling functions like tolower() and isalpha()

using namespace std;

// Function to display the current state of the guessed word
// Parameters: 
//   - word: The word being guessed by the player
//   - guessed: A vector of booleans indicating which letters have been guessed
void displayWord(const string& word, const vector<bool>& guessed) {
    for (size_t i = 0; i < word.size(); ++i) {
        // Display the letter if guessed, otherwise display an underscore
        if (guessed[i])
            cout << word[i] << " ";
        else
            cout << "_ ";
    }
    cout << endl;
}

// Function to check if the word is completely guessed
// Parameters: 
//   - guessed: A vector of booleans indicating which letters have been guessed
// Returns:
//   - true if all letters are guessed, false otherwise
bool isWordGuessed(const vector<bool>& guessed) {
    for (size_t i = 0; i < guessed.size(); ++i) {
        // If any letter is not guessed, return false
        if (!guessed[i])
            return false;
    }
    return true;
}

// Main function to run the Hangman game
// Parameters: 
//   - wordList: A list of words to be randomly selected for the game
void playHangman(const vector<string>& wordList) {
    // Randomly select a word from the list
    srand(static_cast<unsigned int>(time(0))); // Seed the random generator
    string word = wordList[rand() % wordList.size()]; // Select a random word

    vector<bool> guessed(word.size(), false); // Tracks guessed letters (true/false)
    vector<char> wrongGuesses;               // Tracks incorrect guesses
    int maxAttempts = 6;                     // Maximum number of wrong guesses allowed

    cout << "Welcome to Hangman!" << endl;

    while (wrongGuesses.size() < maxAttempts) { // Loop until the user exhausts attempts
        // Display the current state of the guessed word
        cout << "\nCurrent Word: ";
        displayWord(word, guessed);

        // Display wrong guesses and remaining attempts
        cout << "Wrong Guesses: ";
        for (size_t i = 0; i < wrongGuesses.size(); ++i) {
            cout << wrongGuesses[i] << " ";
        }
        cout << "\nAttempts Left: " << maxAttempts - wrongGuesses.size() << endl;

        // Get the player's guess
        char guess;
        cout << "Enter your guess: ";
        cin >> guess;
        guess = tolower(guess); // Convert the guess to lowercase for consistency

        // Check if the input is a valid alphabetical letter
        if (!isalpha(guess)) {
            cout << "Invalid input. Please enter a single letter." << endl;
            continue; // Skip to the next iteration
        }

        // Check if the guessed letter is in the word
        bool correct = false;
        for (size_t i = 0; i < word.size(); ++i) {
            if (tolower(word[i]) == guess) { // Compare lowercase letters
                if (!guessed[i]) {           // Only update if the letter wasn't guessed before
                    guessed[i] = true;
                    correct = true;
                }
            }
        }

        if (correct) {
            cout << "Good guess!" << endl;
            // Check if the entire word is guessed
            if (isWordGuessed(guessed)) {
                cout << "\nCongratulations! You've guessed the word: " << word << endl;
                return; // End the game with a win
            }
        } else {
            // Check if the wrong guess was already made
            bool alreadyGuessed = false;
            for (size_t i = 0; i < wrongGuesses.size(); ++i) {
                if (wrongGuesses[i] == guess) {
                    alreadyGuessed = true;
                    break;
                }
            }
            if (!alreadyGuessed) {
                wrongGuesses.push_back(guess); // Add the wrong guess to the list
                cout << "Incorrect guess." << endl;
            } else {
                cout << "You already guessed that letter." << endl;
            }
        }
    }

    // If the user exhausts all attempts
    cout << "\nGame Over! The word was: " << word << endl;
}

int main() {
    // List of words for the game
    string wordArray[] = {
        "programming", "hangman", "developer", "algorithm", "computer",
        "science", "education", "software", "engineer", "debugging"
    };
    // Initialize vector from the word array
    vector<string> wordList(wordArray, wordArray + sizeof(wordArray) / sizeof(string));

    // Game loop for replay functionality
    char playAgain;
    do {
        playHangman(wordList); // Start a new game
        cout << "\nDo you want to play again? (y/n): ";
        cin >> playAgain;
        playAgain = tolower(playAgain); // Normalize input
    } while (playAgain == 'y'); // Continue if the user chooses to play again

    cout << "Thank you for playing Hangman!" << endl;
    return 0;
}