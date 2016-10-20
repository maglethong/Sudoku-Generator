#ifndef _SUDOKUSOLUTION_H_
#define _SUDOKUSOLUTION_H_

#include "SudokuSheet.h"

#include <vector>



class SudokuSolution
{
	private:
		std::vector<int> *possibleValues[9][9];
		int visibleSheet[9][9];
		SudokuSheet *sheet;

	public:
		SudokuSolution( SudokuSheet* rawSheet );
		~SudokuSolution();

		// Getters
		int getVisibleValue(int line, int column);
		std::vector<int> *getPossibleValues(int line, int column);

		// Setters
		void setVisibleValue(int value, int line, int column);

		// Other
		void print();

	private:
		// Re-check possible values of position
		std::vector<int> *verifyPossibleValues(int line, int column);

		// Vector manipulation
		void removeFrom(int value, std::vector<int> *vec);
		bool possesses(int value, std::vector<int> *vec);
};

#endif