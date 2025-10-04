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

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

std::atomic<int> time_left(0);
std::atomic<bool> time_up(false);

char get_ch()
{
    char buf = 0;
    struct termios old = {};

    if (tcgetattr(STDIN_FILENO, &old) < 0) perror("tcgetattr");

    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &old) < 0) perror("tcsetattr");

    if (read(STDIN_FILENO, &buf, 1) < 0) perror("read");

    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;

    if (tcsetattr(STDIN_FILENO, TCSADRAIN, &old) < 0) perror("tcsetattr");

    return buf;
}

std::vector<std::string> load_words()
{
    std::ifstream file("words.txt");
    std::vector<std::string> words;
    std::string word;

    if (!file)
    {
        std::cerr << "Error opening words file\n";
        return {};
    }
    while (file >> word)
    {
        words.push_back(word);
    }
    return words;
}

void timer(int seconds)
{
    time_left = seconds;
    while (time_left > 0)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        time_left--;
    }
    time_up = true;
}

int main() {
    srand(time(0));

    std::vector<std::string> words = load_words();
    if (words.empty()) return 1;

    int score = 0, total = 0;
    int seconds = 10;
    time_left = seconds;
    std::thread t(timer, seconds);

    while (!time_up) {
        std::string word = words[rand() % words.size()];
        std::string progress = "";
        int index = 0;

        std::cout << "\nTime left: " << time_left << "\n" << std::flush;
        std::cout << "Type the word: " << word << std::flush;

        while (index < word.size() && !time_up) {
            char c = get_ch();
            progress.push_back(c);

            std::cout << "\rTime left: " << time_left;
            std::cout << "\rType the word: ";

            for (int i = 0; i < (int)word.size(); i++) {
                if (i < (int)progress.size()) {
                    if (progress[i] == word[i])
                        std::cout << GREEN << word[i] << RESET;
                    else
                        std::cout << RED << word[i] << RESET;
                } 
                else {
                    std::cout << word[i];
                }
            }
            std::cout << std::flush;
            index++;
        }

        if (!time_up) {
            if (progress == word) score++;
            total++;
        }
    }

    t.join();

    if (score < total)
        std::cout << "\n\nCorrect Words: " << score << "/" << total << " :'(\n";
    else
        std::cout << "\n\nCorrect Words: " << score << "/" << total << " ! ! !\n";
}
