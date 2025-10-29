#include "typing_game.hpp"
#include "wordle.hpp"
#include <iostream>
#include <cctype>
#include <limits>

std::string Print_Menu()
{
    std::cout << '\n' << std::string(50, '-') << '\n';
    std::cout << "\t-C++ Terminal Word Games Menu-\n\n";
    std::cout << "\t1: Typing Game\t     2: Wordle\n";
    std::cout << std::string(50, '-') << '\n';

    std::string choice {};
    std::cout << "\t       Select Game: "; 
    std::cin >> choice;
    
    return choice;
}

void typing_game()
{
    char retry {};
    while (std::toupper(retry) != 'N')
    {
        TypingGame game;
        if (game.play() == 0)
        {
            std::cout << "Would you like to rety? (Y/N): ";
            std::cin >> retry;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            retry = std::toupper(retry);

            while (retry != 'Y' && retry != 'N')
            {
                std::cout << "Invalid input, try again (Y/N): ";
                std::cin >> retry;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                retry = std::toupper(retry);
            }
        }
        if (retry == 'N')
            break;
    }
}

void wordle()
{
    char retry {};
    while (std::toupper(retry) != 'N')
    {
        Wordle game;
        if (game.play() == 0)
        {
            std::cout << "Would you like to rety? (Y/N): ";
            std::cin >> retry;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            retry = std::toupper(retry);

            while (retry != 'Y' && retry != 'N')
            {
                std::cout << "Invalid input, try again (Y/N): ";
                std::cin >> retry;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                retry = std::toupper(retry);
            }
        }
        if (retry == 'N')
            break;
    }
}

int main()
{
    std::string game_selected = Print_Menu();
    while (!(game_selected == "1" || game_selected == "2"))
    {
        std::cout << "\t   Invalid Input Try Again";
        game_selected = Print_Menu();
    }

    std::cout << "\n\n\n\n\n\n";

    if (game_selected == "1")
        typing_game();

    else
        wordle();
}
