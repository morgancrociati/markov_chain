CC = g++
CO = 

all: markov_chain_char_test

%.o: %.cpp %.hpp
	$(CC) $(CO) -c $<

markov_chain_char_test: markov_chain_char.o markov_chain_char_test.o
	$(CC) $(CO) -o $@ $^

clean:
	rm *.o