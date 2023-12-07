OBJS = goyani_prince_hw4.o
EXE = map_generator
CC = gcc 
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
FLAG = -Wall $(DEBUG)

$(EXE): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXE) -lm

goyani_prince_assn3.o: goyani_prince_hw4.h
	$(CC) $(CFLAGS) goyani_prince_hw4.c -lm

clean:
	rm *.o $(EXE) -v