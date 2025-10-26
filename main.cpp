#include "typing_game.hpp"
#include "wordle.hpp"
#include <iostream>

std::string Print_Menu()
{
    std::cout << '\n' << std::string(50, '-') << '\n';
    std::cout << "\t-C++ Terminal Word Games Menu-\n\n";
    std::cout << "\t1: Typing Game\t     2: Wordle\n";
    std::cout << std::string(50, '-') << '\n';

    std::string choice {};
    std::cout << "\t     Select Game: "; 
    std::cin >> choice;
    
    return choice;
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
    {
        std::cout << "Selected Typing Game";
        TypingGame game;
        game.play();
    }
    else
    {
        Wordle game;
        if (game.play() == 0)
            return 0;
    }
}
