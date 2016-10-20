#include "FastSolution.h"



FastSolution::FastSolution( SudokuSolution *solution ) : SolutionTechnique( solution ) { }

bool FastSolution::use()
{
	return fill();
}

bool FastSolution::fill()
{
	int solutions = 0;

	fill_rec( solutions );

	if( solutions != 1 )
		return true;

	return false;
}

bool FastSolution::fill_rec(int &found)
{
	// Searching for spot with lowest possible numbers to fill (degree)
	int line;
	int column;
	int degree = 10;
	for(int i=0; i<9; i++)
		for(int j=0; j<9; j++)
		{
			std::vector<int> * possible = this->sheet->getPossibleValues(i, j);
		
			// Spot has a number
			if( possible == NULL ) 
				continue;

			// Spot with lower degree
			if( possible->size() < degree )
			{
				degree = possible->size();
				line = i;
				column = j;
				
				// Does this spot has a degree of 0? (the sheet won't complete)
				if(degree == 0)
					return true;
			}
			delete possible;

		}
	
	// Check sheet filled => Recursion Stop
	if( degree == 10 )
	{
		found++;
		if(found > 1)
			return false; 	// Only stop after finding a second solution
		return true;		// or checking all possibilities	
	}

	// Try all numbers that spot allows to be filled with (random order)
	std::vector<int> * possible = this->sheet->getPossibleValues(line, column);
	bool failed = true;
	while( failed && possible->size() > 0 )
	{
		int rand = 0;
		this->sheet->setVisibleValue( possible->at( rand ), line, column);
		
		possible->erase( possible->begin() +rand);
		
		// After inserting the value, try to find the next one => Recursive call
		failed = this->fill_rec(found);
	}
	delete possible;
	
	// Failed will stay true if all possible number in this spot resulted
	//   in a sheet that won't complete

	// resset the spot if unsuccessful
	if( failed )
		this->sheet->setVisibleValue( 0, line, column);

	return failed;
}
