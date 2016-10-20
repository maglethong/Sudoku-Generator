#ifndef _SUDOKUSHEET_H_
#define _SUDOKUSHEET_H_

#include "Random.h"

#include <iostream>
#include <vector>
#include <utility>



class SudokuSheet
{
	private:
		int sheet[9][9];				// The actual game sheet
		bool visible[9][9];				// Marks what of the sheet is actually visible
		Random *r;						// Random generator
//		long id;						// 
//		String version;					// 



	public:
		// Constructors/Destructors
		SudokuSheet();					// Empty constructor
		~SudokuSheet();
		
		// Getters
		std::vector<int> *getPossibleValues(int line, int column);
		int getVisibleValue(int line, int column);
		long getRandomSeed();

		// Setters
		void setSheet(int sheet[9][9]);

		// Generation
		void generate(long seed);		// Generates the sudoku sheet

		// Other
		void print();					// Print the sheet

	private:
		// Other
		void fill();					// Fill an empty sheet
			bool fill_rec();
		void remove(int amount);		// Hides numbers of a full sheet
		void rank();					// Ranks a finished sheet

		// Possible values for a specific empty position in the sheet
		std::vector<int> *possibleValues(int line, int column, bool onlyVisible);
		std::vector<int> *possibleValues(int line, int column);
};

#endif