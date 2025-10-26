#include "typing_game.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <atomic>
#include <fcntl.h>
#include <iomanip>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"

std::atomic<int> time_left(0);
std::atomic<bool> time_up(false);

char TypingGame::get_char_nonblocking() {
    char buf = 0;
    struct termios old = {}, newt = {};

    // Get current terminal settings
    if (tcgetattr(STDIN_FILENO, &old) < 0) 
        perror("tcgetattr");

    newt = old;

    // Disable canonical mode (ICANON) turns off terminal buffer
    newt.c_lflag &= ~ICANON;

    // Disable echo (ECHO) prevents tpyed characters bring printed on screen
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Set non-blocking mode
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    int n = read(STDIN_FILENO, &buf, 1);

    // Resets to original terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    fcntl(STDIN_FILENO, F_SETFL, flags);

    if (n > 0) return buf;
    return 0;
}

std::vector<std::string> TypingGame::load_words() {
    std::ifstream file("words.txt");
    std::vector<std::string> words;
    std::string word;

    while (file >> word) {
        words.push_back(word);
    }

    return words;
}

void TypingGame::timer(int seconds) {
    time_left = seconds;
    while (time_left > 0) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        time_left--;
    }
    time_up = true;
}

void TypingGame::stats_output(int letter_score, int letter_count, int score, int total, int seconds)
{
    std::cout << std::fixed << std::setprecision(2);
    std::string seperator(50, '-');
    std::cout << '\n' << seperator;
    double accuracy = static_cast<double>(letter_score) / letter_count * 100.0;
    double WPM = (static_cast<double>(letter_score) / 4.5) * (60.0 / seconds);

    std::cout << "\nCorrect Words: " << score << '/' << total;
    std::cout << "\nCorrect Letters: " << letter_score << '/' << letter_count;

    if (accuracy <= 85.0)
        std::cout << "\nAccuracy " << RED << accuracy << "% :'(\n" << RESET;
    else
        std::cout << "\nAccuracy " << GREEN << accuracy << "% !!! XD\n" << RESET;

    std::cout << "WPM: " << WPM;
    std::cout << "\nPerformance Level: ";

    if (WPM < 40)
        std::cout << RED << "Beginner :'(";
    else if (WPM < 60)
        std::cout << RED << "Average :/";
    else if (WPM < 90)
        std::cout << GREEN << "Profficient :)";
    else if (WPM < 130)
        std::cout << GREEN << "Advanced! XD";
    else
        std::cout << GREEN << "Elite !!!";
    std::cout << '\n' << seperator << '\n';
}

int TypingGame::play() {
    srand(time(0));

    std::vector<std::string> words = load_words();
    if (words.empty()) return 1;

    int score = 0, total = 0, letter_score = 0, letter_count = 0;
    int seconds = 15;
    time_left = seconds;
    std::thread t(&TypingGame::timer, this, seconds);

    while (!time_up) {
        std::string word = words[rand() % words.size()];
        std::string progress;
        int index = 0;

        std::string space(10, '\n');
        std::cout << space;
        std::cout << "\nTime left: " << time_left << "\n" << std::flush;
        std::cout << "Type the word: " << word << std::flush;

        while (index < (int)word.size() && !time_up) {
            char c = get_char_nonblocking();
            if (c == 0) {
                continue;
            }

            progress.push_back(c);

            std::cout << "\033[F\033[2K";    // ANSI escape: moves cursor up to refresh timer
            std::cout << "Time left: " << time_left << "   \n";  
            std::cout << "Type the word: ";

            for (int i = 0; i < (int)word.size(); i++) {
                if (i < (int)progress.size()) {
                    if (progress[i] == word[i])
                    {
                        std::cout << GREEN << word[i] << RESET;
                        if (index == word.length()-1)
                            letter_score++;
                    }
                    else
                        std::cout << RED << word[i] << RESET;
                } 
                else 
                {
                    std::cout << word[i];
                }
            }

            std::cout << std::flush;
            index++;
        }
        letter_count += word.size();

        if (!time_up) {
            if (progress == word) score++;

            total++;
        }
    }

    t.join();
    stats_output(letter_score, letter_count, score, total, seconds);
    return 0;
}
