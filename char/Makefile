CC = g++
CO = 

all: markov_chain_char.o

%.o: %.cpp %.hpp
	$(CC) $(CO) -c $<

markov_chain_char.o: markov_chain_char.cpp markov_chain_char.hpp
	$(CC) $(CO) -c $<