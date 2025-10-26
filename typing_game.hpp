#pragma once
#include <string>
#include <vector>

class TypingGame
{
    public:
        int play();
    private:
        std::vector<std::string> load_words();
        char get_char_nonblocking();
        void timer(int seconds);
        void stats_output(int letter_score, int letter_count, int score, int total, int seconds);
};
