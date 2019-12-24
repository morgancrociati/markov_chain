#ifndef H_MARKOV_CHAIN
#define H_MARKOV_CHAIN

#include <vector>

#define MARKOV_TYPE int
#define MARKOV_INT std::size_t

class markov_chain_int
{
public:

    markov_chain_int(unsigned int seed = 0);
    ~markov_chain_int();

    void add_state(MARKOV_TYPE state, MARKOV_INT start = 0);
    void set_transition(MARKOV_TYPE stateFrom, MARKOV_TYPE stateTo, MARKOV_INT n);

    void add_sample(std::vector<MARKOV_TYPE> tab);

    std::vector<MARKOV_TYPE> generate(MARKOV_INT size);

    void write_markov_chain(std::string filePath);
    void read_markov_chain(std::string filePath);

private:
    std::vector<std::vector<MARKOV_INT>> matrix;
    std::vector<MARKOV_INT> sumMatrix;

    std::vector<MARKOV_TYPE> stateNameMatrix;
    
    std::vector<MARKOV_INT> startMatrix;
    MARKOV_INT sumStartMatrix;

    MARKOV_INT find(MARKOV_TYPE element);
    MARKOV_INT string_2_markov_int(std::string s, MARKOV_INT startPos = 0, MARKOV_INT endPos = -1);

    MARKOV_INT get_start(void);
    MARKOV_TYPE get_next(MARKOV_INT state);
};

#endif