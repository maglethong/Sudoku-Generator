#include "SudokuSolution.h"



SudokuSolution::SudokuSolution( SudokuSheet* rawSheet )
{
	this->sheet = rawSheet;

	for(int i=0; i<9; i++)
		for(int j=0; j<9; j++)
		{
			this->visibleSheet[i][j] = rawSheet->getVisibleValue(i, j);
			this->possibleValues[i][j] = rawSheet->getPossibleValues(i, j);
		}
}

SudokuSolution::~SudokuSolution()
{
	for(int i=0; i<9; i++)
		for(int j=0; j<9; j++)
			if( this->possibleValues[i][j] != NULL )
				delete this->possibleValues[i][j];
}

// Getters
int SudokuSolution::getVisibleValue(int line, int column)
{
	return this->visibleSheet[line][column];
}

std::vector<int> * SudokuSolution::getPossibleValues(int line, int column)
{
	// Empty?
	if( this->possibleValues[line][column] == NULL )
		return NULL;

	std::vector<int> *newVec = new std::vector<int>();
	// Copy desired vector
	for(int i=0; i<this->possibleValues[line][column]->size(); i++)
		newVec->push_back( this->possibleValues[line][column]->at(i) );

	return newVec;
}

// Setters
void SudokuSolution::setVisibleValue(int value, int line, int column)
{
	// Accaptable values
	if( value < 0 || value > 9 )
		return;

	// Spot has no previous value
	if( this->visibleSheet[line][column] == 0 )
	{
		// Setting new value
		this->visibleSheet[line][column] = value;
		delete this->possibleValues[line][column];
		this->possibleValues[line][column] = NULL;

		// Removing 'value' from possible values of same line/column
		for(int i=0; i<9; i++)
		{
			this->removeFrom(value, this->possibleValues[i][column]);
			this->removeFrom(value, this->possibleValues[line][i]);
		}
		// ... and now from same square
		int sl = (line/3) *3;	// square starts at line 'sl'
		int sc = (column/3) *3;	// and starts at column 'sc'
		for(int i=0; i<3; i++)
			for(int j=0; j<3; j++)
				this->removeFrom(value, this->possibleValues[sl +i][sc +j]);


	// Spot has a previous value
	}
	else
	{
		// Setting its value to 0
		this->visibleSheet[line][column] = 0;

		// Resseting line/column of this spot
		for(int i=0; i<9; i++)
		{
			// column
			if( this->possibleValues[i][column] != NULL )
				delete this->possibleValues[i][column];
			this->possibleValues[i][column] = this->verifyPossibleValues(i,column);
			// line
			if( this->possibleValues[line][i] != NULL )
				delete this->possibleValues[line][i];
			this->possibleValues[line][i] = this->verifyPossibleValues(line, i);
		}

		// Resseting same square as this spot
		int sl = (line/3) *3;	// square starts at line 'sl'
		int sc = (column/3) *3;	// and starts at column 'sc'
		for(int i=0; i<3; i++)
			for(int j=0; j<3; j++)
			{
				if(this->possibleValues[sl +i][sc +j] != NULL)
					delete this->possibleValues[sl +i][sc +j];
				this->possibleValues[sl +i][sc +j] = 
										this->verifyPossibleValues(sl +i, sc +j);
			}

		// Setting wanted value
		if( value != 0 )
			this->setVisibleValue(value, line, column);
	}
}

void SudokuSolution::print()
{
	std::cout << "Solution Sheet:" << "\n";
	for(int i=0; i<9; i++)
	{
		for(int j=0; j<9; j++)
		{
			if(this->visibleSheet[i][j] == 0)
				std::cout << '-' << ' ';
			else
				std::cout << this->visibleSheet[i][j] << ' ';
		
		}
		std::cout << "\n";
	}
	std::cout << "Solution Sheet Possible Degree:" << "\n";
	for(int i=0; i<9; i++)
	{
		for(int j=0; j<9; j++)
		{
			if(this->possibleValues[i][j] == NULL)
				std::cout << '-' << ' ';
			else
				std::cout << this->possibleValues[i][j]->size() << ' ';
		}
		std::cout << "\n";
	}

}

std::vector<int> * SudokuSolution::verifyPossibleValues(int line, int col)
{
	// Already has something
	if( this->visibleSheet[line][col] != 0 )
		return NULL;

	// List of inpossible numbers
	bool present[9];
	for(int i=0; i<9; i++)
		present[i] = false;
	
	// Ruling out same line/collumn
	for(int i=0; i<9; i++)
	{
		// Line
		if( (this->visibleSheet[i][col] >= 1 && this->visibleSheet[i][col] <= 9) )
			present[ this->visibleSheet[i][col] -1] = true;
		// Collumn
		if( (this->visibleSheet[line][i] >= 1 && this->visibleSheet[line][i] <= 9))
			present[ this->visibleSheet[line][i] -1] = true;
	}

	// Rulling out same square
	int sl = (line/3) *3;	// square starts at line 'sl'
	int sc = (col/3) *3;	// and start at col 'sc'
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			if( this->visibleSheet[i +sl][j +sc] >= 1 &&
											this->visibleSheet[i +sl][j +sc] <= 9 )
				present[ this->visibleSheet[i +sl][j +sc] -1] = true;

	// Passing to return vector
	std::vector<int> *ret = new std::vector<int>();
	for(int i=0; i<9; i++)
		if( !present[i] )
			ret->push_back(i +1);

	return ret;
}

void SudokuSolution::removeFrom(int value, std::vector<int> *vec)
{
	if(vec == NULL)
		return;

	for(int i=0; i<vec->size(); i++)
		if(vec->at(i) == value)
		{
			int tmp = vec->at(i);
			vec->at(i) = vec->at( vec->size()-1 );
			vec->at( vec->size()-1 ) = tmp;
			vec->pop_back();
		}
}

bool SudokuSolution::possesses(int value, std::vector<int> *vec)
{
	if(vec == NULL)
		return false;

	for(int i=0; i<vec->size(); i++)
		if(vec->at(i) == value)
			return true;

	return false;
}
