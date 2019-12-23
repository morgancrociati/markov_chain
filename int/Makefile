CC = g++
CO = 

all: markov_chain_int.o

%.o: %.cpp %.hpp
	$(CC) $(CO) -c $<

markov_chain_int.o: markov_chain_int.cpp markov_chain_int.hpp
	$(CC) $(CO) -c $<