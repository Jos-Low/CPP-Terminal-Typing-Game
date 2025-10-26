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

    std::string Pick_Word(const std::string& filename);
    void Display_Grid() const;
    bool Guess_Check(std::string guess, int round);

public:
    Wordle();
    int play();
};
