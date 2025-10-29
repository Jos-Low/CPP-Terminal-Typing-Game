#pragma once

#include <iostream>
#include <vector>
#include <string>

class Wordle
{
private:
    static const std::string YELLOW;
    static const std::string GREEN;
    static const std::string RESET;
    std::vector<std::vector<std::string>> Grid;
    std::string word_to_guess;
    std::vector<char> letters_left = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    std::string Pick_Word(const std::string& filename);
    void Display_Grid() const;
    bool Guess_Check(std::string guess, int round);

public:
    Wordle();
    int play();
};
