#include "wordle.hpp"
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

const std::string Wordle::YELLOW = "\033[33m";
const std::string Wordle::GREEN  = "\033[32m";
const std::string Wordle::RESET  = "\033[0m";

Wordle::Wordle()
{
    srand(static_cast<unsigned int>(time(0)));
    Grid.clear();
    Grid = std::vector<std::vector<std::string>>(6, std::vector<std::string>(5, "[ ]"));
    word_to_guess = Pick_Word("wordle.txt").substr(0,5);
    //std::cout << "DEBUG: " << word_to_guess << '\n';
}

std::string Wordle::Pick_Word(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Failed to open " << filename << "\n";
        return "";
    }

    std::string line, chosen;
    int count = 0;

    while (std::getline(file, line))
    {
        ++count;
        if (rand() % count == 0)
            chosen = line;
    }

    std::transform(chosen.begin(), chosen.end(), chosen.begin(),
        [](unsigned char c) { return std::toupper(c); });
    return chosen;
}

void Wordle::Display_Grid() const
{
    int c {};
    int pos {};
    for (const auto& row : Grid)
    {
        for (const auto& cell : row)
            std::cout << cell;
        // Print letters left box
        if (c == 2 || c == 3)
        {
            std::cout << "\t\t| ";
            for (int i {}; i < 13; ++i)
            {
                std::cout << letters_left.at(pos);
                pos++;
            }
            std::cout << " |";
        }
        else if (c == 1 || c == 4)
            std::cout << "\t\t|" << std::string(15, '-') << '|';

        std::cout << '\n';
        c++;
    }
}

bool Wordle::Guess_Check(std::string guess, int round)
{
    std::vector<bool> matched(5, false);

    for (int i = 0; i < 5; ++i)
    {
        auto index = std::find(letters_left.begin(), letters_left.end(), guess.at(i));
        if (index != letters_left.end())
            *index = '-';

        if (guess[i] == word_to_guess[i])
        {
            std::string letter = "[" + GREEN + guess.substr(i, 1) + RESET + "]";
            Grid[round][i] = letter;
            matched[i] = true;
        }
        else
        {
            Grid[round][i] = "[ ]";
        }
    }

    for (int i = 0; i < 5; ++i)
    {
        if (guess[i] != word_to_guess[i])
        {
            for (int j = 0; j < 5; ++j)
            {
                if (!matched[j] && guess[i] == word_to_guess[j])
                {
                    std::string letter = "[" + YELLOW + guess.substr(i, 1) + RESET + "]";
                    Grid[round][i] = letter;
                    matched[j] = true;
                    break;
                }
            }

            if (Grid[round][i] == "[ ]")
            {
                Grid[round][i] = "[" + guess.substr(i, 1) + "]";
            }
        }
    }

    return (guess == word_to_guess);
}

int Wordle::play()
{
    Display_Grid();

    int round = 0;
    while (round < 6)
    {
        std::string guess;
        std::cout << "Guess the word: ";
        std::cin >> guess;

        while (guess.size() != 5)
        {
            Display_Grid();
            std::cout << "Must be length 5, try again: ";
            std::cin >> guess;
        }

        std::transform(guess.begin(), guess.end(), guess.begin(),
            [](unsigned char c) { return std::toupper(c); });

        if (Guess_Check(guess, round))
        {
            Display_Grid();
            std::cout << "YOU GUESSED IT!\n";
            return 0;
        }

        Display_Grid();
        ++round;
    }

    std::cout << "The word was: " << word_to_guess << '\n';
    return 0;
}
