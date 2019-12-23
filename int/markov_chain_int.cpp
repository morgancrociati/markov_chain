#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include <cassert>

#include "markov_chain.hpp"

// ----- PUBLIC -----
markov_chain::markov_chain(unsigned int seed)
{
    sumStartMatrix = 0;
    if (seed == 0)
        srand(time(NULL));
    else
        srand(seed);
}

markov_chain::~markov_chain()
{
}

void markov_chain::add_state(MARKOV_TYPE state, MARKOV_INT start)
{
    assert(find(state) == -1);
    stateNameMatrix.push_back(state);
    MARKOV_INT matrixSize = stateNameMatrix.size();

    for (MARKOV_INT i = 0; i < matrixSize - 1; i++)
        matrix[i].push_back(0);
    
    matrix.push_back(std::vector<MARKOV_INT>(matrixSize, 0));
    sumMatrix.push_back(0);

    startMatrix.push_back(start);
    sumStartMatrix += start;
}

void markov_chain::set_transition(MARKOV_TYPE stateFrom, MARKOV_TYPE stateTo, MARKOV_INT n){
    MARKOV_INT iStateFrom = find(stateFrom);
    assert(iStateFrom != -1);
    MARKOV_INT iStateTo = find(stateTo);
    assert(iStateTo != -1);
    
    sumMatrix[iStateFrom] -= matrix[iStateFrom][iStateTo];
    matrix[iStateFrom][iStateTo] = n;
    sumMatrix[iStateFrom] += n;
}

void markov_chain::add_sample(std::vector<MARKOV_TYPE> tab)
{
    MARKOV_INT i;
    MARKOV_INT state = -1;
    MARKOV_INT nextState = -1;
    MARKOV_TYPE tmp;

    //For loop iterating over all the element of our vector
    for (std::vector<MARKOV_TYPE>::iterator it = tab.begin(); it != tab.end(); it++)
    {
        tmp = *it;
        nextState = find(tmp);

        if (nextState == -1) //This state was not found in the current markov chain
        {
            add_state(tmp);
            nextState = stateNameMatrix.size() - 1;
        }

        if (state != -1) //Not the first element of the sample
        {
            matrix[state][nextState]++;
            sumMatrix[state]++;
        }
        else //First element of the sample
        {
            startMatrix[nextState]++;
            sumStartMatrix++;
        }

        state = nextState;
    }
}

std::vector<MARKOV_TYPE> markov_chain::generate(MARKOV_INT size)
{
    std::vector<MARKOV_TYPE> result;

    MARKOV_INT i;

    MARKOV_INT state = -1;

    //Get the first MARKOV_TYPE generated by our markov chain
    state = get_start();
    result.push_back(stateNameMatrix[state]);
    for (i = 0; i < size - 1; i++)
    {
        if (sumMatrix[state] == 0)
        {
            state = get_start();
            result.push_back(stateNameMatrix[state]);
        }
        else
        {
            state = get_next(state);
            result.push_back(stateNameMatrix[state]);
        }
    }

    return result;
}

// ----- PRIVATE -----
MARKOV_INT markov_chain::get_start(void)
{
    MARKOV_INT i;
    MARKOV_INT sizeMatrix = stateNameMatrix.size();
    double r = ((double)rand()) / ((double)RAND_MAX);
    double tmp = 0;
    for (i = 0; i < sizeMatrix; i++)
    {
        tmp += ((double)startMatrix[i]) / ((double)sumStartMatrix);
        if (tmp >= r || i == sizeMatrix - 1)
            return i;
    }
    return -1;
}

MARKOV_TYPE markov_chain::get_next(MARKOV_INT state)
{
    MARKOV_INT i;
    MARKOV_INT sizeMatrix = stateNameMatrix.size();
    double r = ((double)rand()) / ((double)RAND_MAX);
    double tmp = 0;
    for (i = 0; i < sizeMatrix; i++)
    {
        tmp += ((double)matrix[state][i]) / ((double)sumMatrix[state]);
        if (tmp >= r || i == sizeMatrix - 1)
            return i;
    }
    return -1;
}

MARKOV_INT markov_chain::find(MARKOV_TYPE element)
{
    MARKOV_INT i;
    MARKOV_INT sizeMatrix = stateNameMatrix.size();

    for (i = 0; i < sizeMatrix; i++)
    {
        if (stateNameMatrix[i] == element)
        {
            return i;
        }
    }
    return -1;
}