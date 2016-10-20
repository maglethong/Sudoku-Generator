#ifndef _SOLUTIONTECHNIQUE_H_
#define _SOLUTIONTECHNIQUE_H_

#include "SudokuSolution.h"



class SolutionTechnique
{
	private:
		int timesUsed;

	public:
		SolutionTechnique( SudokuSolution *solution );
		~SolutionTechnique();
		int getTimesUsed();
		virtual bool use() = 0;
		void ressetUses();
	
	protected:
		SudokuSolution *sheet;
		void addUse();
};

#endif