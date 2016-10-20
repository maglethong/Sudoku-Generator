#include "SudokuSheet.h"

#include "SudokuSolution.h"
#include "SolutionTechnique.h"
#include "FastSolution.h"



	// ==================================================================== //
	//																		//
	//						Constructors / Destructor						//
	//																		//
	// ==================================================================== //

SudokuSheet::SudokuSheet()
{
	this->r = NULL;

	for(int i=0; i<9; i++)
		for(int j=0; j<9; j++)
		{
			this->sheet[i][j] = -1;
			this->visible[i][j] = true;
		}
}

SudokuSheet::~SudokuSheet()
{
	if(this->r != NULL)
		delete this->r;
}

	// ==================================================================== //
	//																		//
	//									Getters								//
	//																		//
	// ==================================================================== //
std::vector<int> * SudokuSheet::getPossibleValues(int line, int column)
{
	return possibleValues(line, column, true);	
}

int SudokuSheet::getVisibleValue(int line, int column)
{
	if( this->visible[line][column] )
		return this->sheet[line][column];
	return 0;
}

long SudokuSheet::getRandomSeed()
{
	return r->getSeed();
}

	// ==================================================================== //
	//																		//
	//									Setters								//
	//																		//
	// ==================================================================== //

void SudokuSheet::setSheet(int sheet[9][9])
{
	for(int i=0; i<9; i++)
		for(int j=0; j<9; j++)
		{
			this->sheet[i][j] = sheet[i][j];
			if(sheet[i][j] == 0 || sheet[i][j] == -1)
				this->visible[i][j] = false;
			else	
				this->visible[i][j] = true;
		}
}

	// ==================================================================== //
	//																		//
	//								Public Methods							//
	//																		//
	// ==================================================================== //

void SudokuSheet::generate(long seed)
{
	// Creating new Random generator
	if(this->r != NULL)
		delete this->r;

	this->r = new Random(seed);

	// Filling sheet
	this->fill();

	// Removing some numbers
	this->remove(81 - 22);
}

void SudokuSheet::print()
{
	std::cout << "Whole Sheet:" << "\n";
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++)
			if(this->sheet[i][j] == -1)
				std::cout << '-' << ' ' ;
			else	
				std::cout << this->sheet[i][j] << ' ';
		std::cout << "\n";
	}

	std::cout << "Visible Sheet:" << "\n";
	for(int i=0; i<9; i++)
	{
		for(int j=0; j<9; j++)
			if( this->visible[i][j] && this->sheet[i][j] != -1 )
				std::cout << this->sheet[i][j] << ' ';
			else
				std::cout << '-' << ' ';
		std::cout << "\n";
	}
}

	// ==================================================================== //
	//																		//
	//								Private Methods							//
	//																		//
	// ==================================================================== //
void SudokuSheet::fill()
{
	// Filling top left spot
	this->sheet[0][0] = this->r->nextInt(1, 9);

	// Filling first line and column
	for(int i=1; i<9; i++)
	{
		std::vector<int> * possible;

		// Line
		possible = possibleValues(0, i);
		this->sheet[0][i] = possible->at(
									this->r->nextInt(0, possible->size() -1) );
		delete possible;

		// Column
		possible = possibleValues(i, 0);
		this->sheet[i][0] = possible->at(
									this->r->nextInt(0, possible->size() -1) );
		delete possible;
	}

	// Filling the rest with recursive method
	this->fill_rec();
}

bool SudokuSheet::fill_rec()
{
	// Searching for spot with lowest possible numbers to fill (degree)
	int line;
	int column;
	int degree = 10;
	for(int i=1; i<9; i++)
		for(int j=1; j<9; j++)
		{
			std::vector<int> * possible = this->possibleValues(i, j);
		
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
		return false;
	
	// Try all numbers that spot allows to be filled with (random order)
	std::vector<int> * possible = this->possibleValues(line, column);
	bool failed = true;
	while( failed && possible->size() > 0 )
	{
		int rand = this->r->nextInt(0, possible->size() -1);
		this->sheet[line][column] = possible->at( rand );
		
		possible->erase( possible->begin() +rand);
		
		// After inserting the value, try to find the next one => Recursive call
		failed = this->fill_rec();
	}
	delete possible;
	
	// Failed will stay true if all possible number in this spot resulted
	//   in a sheet that wont complete

	// resset the spot if unsuccessful
	if( failed )
		sheet[line][column] = -1;

	return failed;
}

void SudokuSheet::remove(int amount)
{
	std::vector< std::pair<int, int> > available;

	// Fill vector with all available positions
	for(int i=0; i<9; i++)
		for(int j=0; j<9; j++)
			available.push_back( std::make_pair(i, j) );
	

	// Remove desired amount of numbers [turn them invisible]
	int force = -1;
	while( amount > 0 && available.size() > 0 )
	{
		// Pseudo - randomize [try to maintain symmetry]
		int rand;
		if( force == -1 ){
			rand = this->r->nextInt(0, available.size()-1);
			force = available.size() -1 -rand; //! TODO [better symmetry force]
		}else{
			rand = force;
			force = -1;
		}
		int line = available[rand].first;
		int column = available[rand].second;

		// Remove from possible spots to hide
		available.erase( available.begin() +rand );

		// Hide the spot
		this->visible[line][column] = false;

		// Create a solution to check if the puzzle is still solvable just once
		SudokuSolution *sol = new SudokuSolution( this );
		SolutionTechnique *tech = new FastSolution( sol );
		
		// If removing this spot generates an unsolvable puzzle, put it back
		if( tech->use() )
			this->visible[line][column] = true;
		else
			amount--;

		delete tech;
		delete sol;
	}

	// Really removed the amount asked?
	if( amount > 0 )
	{
		std::cout << "Did not remove maximum!\n";
		return; // error
	}
}


std::vector<int> *SudokuSheet::possibleValues(int line, int col, bool onlyVisible)
{
	// Already has something                      & = && in this case (but faster) 
	if( ( this->sheet[line][col] != -1 && !onlyVisible) ||
									( onlyVisible & this->visible[line][col] ) )
		return NULL;

	// List of inpossible numbers
	bool present[9];
	for(int i=0; i<9; i++)
		present[i] = false;
	
	// Ruling out same line/collumn
	for(int i=0; i<9; i++)
	{
		// Line
		if( (this->sheet[i][col] >= 0 && this->sheet[i][col] <= 9) &&
										(!onlyVisible || this->visible[i][col])	)
			present[sheet[i][col] -1] = true;
		// Collumn
		if( (this->sheet[line][i] >= 0 && this->sheet[line][i] <= 9) &&
									(!onlyVisible || this->visible[line][i])	)
			present[sheet[line][i] -1] = true;
	}

	// Rulling out same square
	int sl = (line/3) *3;	// square starts at line 'sl'
	int sc = (col/3) *3;	// and start at col 'sc'
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			if( (this->sheet[i +sl][j +sc] >=0 && this->sheet[i +sl][j +sc] <= 9)&&
								(!onlyVisible || this->visible[i +sl][j +sc])	)
				present[sheet[i +sl][j +sc] -1] = true;

	// Passing to return vector
	std::vector<int> *ret = new std::vector<int>();
	for(int i=0; i<9; i++)
		if( !present[i] )
			ret->push_back(i +1);

	return ret;
}

std::vector<int> *SudokuSheet::possibleValues(int line, int col)
{
	return possibleValues(line, col, false);	
}
