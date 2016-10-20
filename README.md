About
=====

This repository was created 2 years after the initial version of this Sudoku Generator was written. The main purpose of this project was to train OOP concepts while creating something fun and useful.

The generation algorithm consists of populating a valid Sodoku Puzzle and removing digits from it ensuring there is still exactly one solution.


The Source Code
---------------

Code in this project uses tabulation characters equivalent to 4 spaces.


Compile Instructions
====================

Either use the provided Makefile or run:
```
g++ -I ./inc -o sudoku ./src/*.cc
```


Execution
=========

The current version only generates one puzzle at a time using either a provided random seed or a time-generated seed.
```
sudoku [seed]
```


References
==========

Sudoku Puzzle Game Rules: https://en.wikipedia.org/wiki/Sudoku
