#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
using namespace std;

// Convert val back into triple (i,j,k)
// Where (i,j,k) represents coordinate (i,j)
// of the Sudoku board having value k
pair<pair<int,int>, int> findVal(int val){ 
	val -= 1;                         // In the oringal conversion from (i,j,k) -> val we added 1, so we subtract it here      
	int x = 0;
	int y = 0;
	if (val >= 81){
		x = val/81;
		val = val % 81;
	}
	if (val >= 9){
		y = val/9;
		val = val % 9;
	}
	pair<int,int> coords{x,y};
       	pair<pair<int, int>, int> output{coords,val + 1};	
	return output;
}

// Initializes the board to contain all zeroes
void fillZeroes(vector<vector<int>> &board){
	for (int i = 0; i < 9; ++i){
		vector<int> rows;
		for (int j = 0; j < 9; ++j){
			rows.push_back(0);
		}
		board.push_back(rows);
	}
}

int main(){
	string sat;
	getline(cin, sat);
	if (sat == "UNSAT"){
		cout << "No Solution Exists" << endl;
	}
	int var;
	vector<vector<int>> SolvedBoard;
	fillZeroes(SolvedBoard);
	while (cin >> var){
		if (var <= 0){
			continue;
		}
		pair<pair<int,int>, int> coords = findVal(var);
		SolvedBoard[coords.first.first][coords.first.second] = coords.second; // sets up board to be ready to print
	}
	for (auto it = SolvedBoard.begin(); it != SolvedBoard.end(); ++it){
		int count = 0;                                              // We need to keep track of when we need to print spaces
		for (auto it2 = it->begin(); it2 != it->end(); ++it2){
			if (count == 2 || count == 5){
				cout << *it2 << " ";
			} else {
				cout << *it2;
			}
			++count;
		}
		cout << endl;
	}	
}
