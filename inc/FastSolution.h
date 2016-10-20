#ifndef _FASTSOLUTION_H_
#define _FASTSOLUTION_H_

#include "SolutionTechnique.h"



class FastSolution : public SolutionTechnique
{
	public:
		FastSolution( SudokuSolution *solution );
		bool use(); // Returns false if found only one solution

	private:
		bool fill();
			bool fill_rec(int &found);
};

#endif