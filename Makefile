# Source Files (all)
CFILES		=	./src/SudokuSheet.cc ./src/SudokuSolution.cc ./src/Random.cc ./src/SolutionTechnique.cc ./src/FastSolution.cc
MAIN		=	./src/main.cc
# Includes directory
INCLUDES	=	./inc
# Binary output location
BIN			=	./bin/sudoku
# Zip file name after compacting
ZIP			=	Sudoku
# Description Files
DESCRIPTION	=	./doc

all:
	@g++ -I$(INCLUDES) -o $(BIN) $(MAIN) $(CFILES)

run:	
	@$(BIN)

run0:
	@$(BIN) 0

zip:
	@zip -r $(ZIP) inc src Makefile
	@zip $(ZIP) bin
	@zip -r $(ZIP) $(DESCRIPTION)

clear:
	@touch dummy~
	@touch $(ZIP).zip $(BIN)
	@rm $(ZIP).zip $(BIN)
	@find ./ -name *~ | xargs rm -v