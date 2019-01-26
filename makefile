####################################################################################
# NAME: makefile
# PURPOSE: to easily build an executable for the program
# UNIT: Unix and C Programming
# REFERENCE: none
# LAST MOD: 27th may 2018
# COMMENTS: none
####################################################################################

#variables to control makefile operation
CC = gcc
CFLAG = -Wall -ansi -pedantic
OBJ = linkedList.o tvguide.o interface.o fileIO.o comparison.o
EXEC = test

#makefile operations
$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

tvguide.o : tvguide.c linkedList.h interface.h fileIO.h data.h tvguide.h comparison.h
	$(CC) $(CFLAG) -c -g tvguide.c

linkedList.o : linkedList.c linkedList.h boolean.h
	$(CC) $(CFLAG) -c -g linkedList.c

interface.o : interface.c interface.h data.h
	$(CC) $(CFLAG) -c -g interface.c

fileIO.o : fileIO.c fileIO.h linkedList.h data.h
	$(CC) $(CFLAG) -c -g fileIO.c

comparison.o : comparison.c comparison.h data.h
	$(CC) $(CFLAG) -c -g comparison.c

#cleaner
clean :
	rm -f $(OBJ) $(EXEC)

