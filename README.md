# Solving 9x9 Sudoku with SAT Reductions
## Written by Aidan Boyle
This project contains 2 executables, sud2sat and sat2sud. sud2sat takes a partially solved sudoku board as input, where blanks are represented by
0, ., * or ? and the nonblanks are positive integers ranging from 1,...,9.
Note that the input can contain any number of space or newline characters
After reading from STDIN, sud2sat converts the board into a CNF boolean formula, as outlined
in the paper *Sudoku as a SAT problem* by Inês Lynce and Joël Ouaknine, such that
the boolean formula created is satisfiable if and only if the board has a solution. The boolean formula is written to STDOUT
in the standard SAT-challenge (DIMACS) format. From here the CNF description can then 
be used as input to the SAT solver, minisat. sat2sud takes as STDIN the assigned variables files
created by minisat, and then prints to STDOUT the solved sudoku Board. The source code has also been added
which can be executed via commands 
#### g++ -o sud2sat -std=c++17 buildSudoku.cpp
#### g++ -o sat2sud -std=c++17 solveSudoku.cpp

An example execution is a follows
#### ./sud2sat < puzzle.txt > puzzle.CNF
#### minisat puzzle.cnf assign.txt > stat.txt
#### ./sat2sud < assign.txt > solution.txt
assign.txt is the file containing the variable assignments that make the boolean formula 
in the CNF formula satisfiable.
