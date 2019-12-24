#ifndef H_MARKOV_CHAIN_CHAR
#define H_MARKOV_CHAIN_CHAR

#include <vector>
#include <string>

#define MARKOV_INT std::size_t

class markov_chain_char
{
public:

    markov_chain_char(unsigned int seed = 0);
    ~markov_chain_char();

    void add_state(char state, MARKOV_INT start = 0);
    void set_transition(char stateFrom, char stateTo, MARKOV_INT n);

    void add_sample(std::vector<char> tab);
    void add_sample(std::string tab);

    std::vector<char> generate_vector(MARKOV_INT size);
    std::string generate_string(MARKOV_INT size);

    void write_markov_chain(std::string filePath);
    void read_markov_chain(std::string filePath);

private:
    std::vector<std::vector<MARKOV_INT>> matrix;
    std::vector<MARKOV_INT> sumMatrix;

    std::vector<char> stateNameMatrix;
    
    std::vector<MARKOV_INT> startMatrix;
    MARKOV_INT sumStartMatrix;

    MARKOV_INT find(char element);
    MARKOV_INT string_2_markov_int(std::string s, MARKOV_INT startPos = 0, MARKOV_INT endPos = -1);

    MARKOV_INT get_start(void);
    char get_next(MARKOV_INT state);
};

#endif