#include "SolutionTechnique.h"



SolutionTechnique::SolutionTechnique( SudokuSolution *solution )
{
	this->sheet = solution;
	this->timesUsed = 0;	
}

SolutionTechnique::~SolutionTechnique(){}

int SolutionTechnique::getTimesUsed()
{
	return timesUsed;
}

void SolutionTechnique::ressetUses()
{
	this->timesUsed = 0;
}
	
void SolutionTechnique::addUse()
{
	this->timesUsed++;	
}
