#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;


// Convert (i,j,k) into a decimal number by thinking
// of (i,j,k) as a base 9 number, but in the conversion
// we subtract 1 from each variable because the sudoku array
// is indexed by 0,...,8, and we add 1 to the decimal number
// since board values are strictly positive
int base9Conversion(int x,int y, int z){
	return 81 *(x - 1) + 9 *(y - 1) + z; 
}

// Builds the clauses of the CNF cooresonding to the requirement
// that each entry contains at least one number, i.e. no square is blank 
void atLeastOne(vector<vector<int>> &SudokuBoard){
	string curr;
	string numToString;
	for (int x = 1; x < 10; ++x){
		for(int y = 1; y < 10; ++y){
			curr = "";
			for (int z = 1; z < 10; ++z){
				if (SudokuBoard[x - 1][y - 1] == z){ // If position (x,y) of the board is not blank, it is already defined
					curr = to_string(base9Conversion(x,y,z));
					break;                       // hence this clause is already satisfiable 
				} 
				numToString = to_string(base9Conversion(x,y,z));
				if (curr != ""){
					curr += " " + numToString;
				} else {
					curr += numToString;
				}
			}
			cout << curr << " 0" << endl;
		}	
	}
}

// Builds the clauses cooresponding to the requirement
// that each number appears at most once in each row
void atMostOnceRow(vector<vector<int>> &SudokuBoard){
	string numToString;
	for (int y = 1; y < 10; ++y){
		for (int z = 1; z < 10; ++z){
			for (int x = 1; x < 9; ++x){
				for (int i = x + 1; i < 10; ++i){
					if (SudokuBoard[x-1][y -1] == z){ // If position (x,y) of the board is not blank, it is already defined
						numToString = to_string(0 - base9Conversion(i,y,z)) + " 0"; // hence if we negate said variable it will be false
					} else if (SudokuBoard[i-1][y-1] == z){                             // so we only care about the other variable
						numToString = to_string(0 - base9Conversion(x,y,z)) + " 0";
					} else {
						numToString = to_string(0 - base9Conversion(x,y,z)) + " ";
						numToString += to_string(0 - base9Conversion(i,y,z)) + " 0"; 
					}
					cout << numToString << endl;
				}
			}
		}	
	}
}

// Builds the clauses cooresponding to the requirement 
// that each number appears at most once in each column
void atMostOnceCol(vector<vector<int>> &SudokuBoard){
   	string numToString;
        for (int x = 1; x < 10; ++x){
                for (int z = 1; z < 10; ++z){
                        for (int y = 1; y < 9; ++y){
                                for (int i = y + 1; i < 10; ++i){
                                        if (SudokuBoard[x-1][y -1] == z){ // If position (x,y) of the board is not blank, it is already defined, and
                                                numToString = to_string(0 - base9Conversion(x,i,z)) + " 0"; // hence its negation will be false so we
                                        } else if (SudokuBoard[x-1][i-1] == z){                             // only care about the other variable
                                                numToString = to_string(0 - base9Conversion(x,y,z)) + " 0";
                                        } else {
                                                numToString = to_string(0 - base9Conversion(x,y,z)) + " ";
                                                numToString += to_string(0 - base9Conversion(x,i,z)) + " 0";
                                        }
                                        cout << numToString << endl;
                                }
                        }
                }
        }
}

// Builds the first set of clauses cooresponding to the requirement
// that each number appears at most once in each 3x3 grid
void eachNumMostOnceGrid1(vector<vector<int>> &SudokuBoard){
	string numToString;
	for (int z = 1; z < 10; ++z){
		for (int i = 0; i < 3; ++i){
			for (int j = 0; j < 3; ++j){
				for (int x = 1; x < 4; ++x){
					for (int y = 1; y < 4; ++y){
						for (int k = y + 1; k < 4; ++k){
							if (SudokuBoard[3*i + x - 1][3 * j + y - 1] == z){ // position (3i + x, 3j + y) is already defined
								numToString = to_string(0 - base9Conversion(3 * i + x, 3 * j + k, z)) + " 0"; // so we dont care about it here
							} else if (SudokuBoard[3 * i + x - 1][3 * j + k - 1] == z){
								numToString = to_string(0 - base9Conversion(3*i + x, 3*j + y, z)) + " 0";
							} else {
								numToString = to_string(0 - base9Conversion(3*i + x, 3*j + y, z)) + " ";
								numToString += to_string(0 - base9Conversion(3*i + x, 3*j + k, z)) + " 0";
							}
							cout << numToString << endl;
						}
					}
				}
			}
		}
	}
}

// Builds the second set of clauses cooresponding to the requirements 
// that each number appears at most once in each 3x3 grid
void eachNumMostOnceGrid2(vector<vector<int>> &SudokuBoard){
        string numToString;
        for (int z = 1; z < 10; ++z){
                for (int i = 0; i < 3; ++i){
                        for (int j = 0; j < 3; ++j){
                                for (int x = 1; x < 4; ++x){
                                        for (int y = 1; y < 4; ++y){
                                                for (int k = x + 1; k < 4; ++k){
							for (int l = 1; l < 4; ++l){
                                                        	if (SudokuBoard[3*i + x - 1][3 * j + y - 1] == z){ // position (3i + x, 3j + y) is not blank so we
                                                                	numToString = to_string(0 - base9Conversion(3 * i + k, 3 * j + l, z)) + " 0"; // dont care about it here
                                                        	} else if (SudokuBoard[3 * i + k - 1][3 * j + l - 1] == z){
                                                                	numToString = to_string(0 - base9Conversion(3*i + x, 3*j + y, z)) + " 0";
                                                        	} else {
                                                                	numToString = to_string(0 - base9Conversion(3*i + x, 3*j + y, z)) + " ";
                                                                	numToString += to_string(0 - base9Conversion(3*i + k, 3*j + l, z)) + " 0";
                                                        	}
                                                        	cout << numToString << endl;
							}
                                                }
                                        }
                                }
                        }
                }
        }
}

// Builds CNF in proper DIMACS format 
void buildCNF(vector<vector<int>> &SudokuBoard){
	cout << "p cnf 729 8829" << endl;        // Minimal Encoding uses 729 propositional variables and 8829 clauses
	atLeastOne(SudokuBoard);                 // part of CNF ensuring at least one number per entry
	atMostOnceRow(SudokuBoard);              // part of CNF ensuring at most one number per row
	atMostOnceCol(SudokuBoard);              // part of CNF ensuring at most one per col
	eachNumMostOnceGrid1(SudokuBoard);       // parts of CNF ensuring each number appears at most once in  
	eachNumMostOnceGrid2(SudokuBoard);       // each 3x3 grid
}

// Sets up the board with the original grid values
// and blanks
void buildSudokuBoard(vector<vector<int>> &SudokuBoard){
	string input;
	int i = 0;      // represents index (i,j) of the 2D array SudokuBoard
	int j = 0;
	while(getline(cin, input) && i < 9){
		int count = 0;                 // represents current index on current line string of input we are considering
		while (input[count] != '\0' && i < 9){
			if (input[count] >= '0' && input[count] <= '9'){
				SudokuBoard[i][j] = input[count] - 48;    // converts ASCII charater for each digit, into actual digit
				++j;
			} else if (input[count] == '*' || input[count] == '.' || input[count] == '?'){
				++j;                                      // All blanks just remain as 0
			}	
			++count;
			if (j == 9){               // update i and j if we've finished filling in a row         
				i += 1;
				j = 0;
			}
		}

	}
}

int main(){
	vector<vector<int>> SudokuBoard;			  //initialize sudoku board to contain only zeros. 
	for (int i = 0; i < 9; ++i){
		vector<int> rows (9, 0);
		SudokuBoard.push_back(rows);
	}
	buildSudokuBoard(SudokuBoard);
	buildCNF(SudokuBoard);
}
