#include "SudokuSheet.h"
#include "SudokuSolution.h"

#include <iostream>
#include <cctype>



int main(int argc, char *argv[])
{
	SudokuSheet *s = new SudokuSheet();

	if(argc <= 1)
		s->generate(time(0));
	else
		s->generate( atoi(argv[1]) );

	s->print();

	delete s;

	return 0;	
}

