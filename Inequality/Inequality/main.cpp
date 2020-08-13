/**
 *  Inequality Puzzle
 *  The inequality puzzle is a 5x5 grid of cells. Some of the cells are filled
 *  in with numbers and some of the cells are connected with inequalities. The
 *  solution to the inequality puzzle is found by filling in all of the empty
 *  cells such that all of following contraints remain true:
 *
 *  Constraints:
 *  1. Each row must contain all of the digits 1 through 5
 *  2. Each column must contain all of the digits 1 through 5
 *  3. All inequalties are true.
 *
 *  (An example puzzle with it's is included as in image in this folder)
 */

#include <iostream>
#include <fstream>
#include <sstream>

using std::string;
using std::istream;
using std::ostringstream;
using std::ifstream;
using std::cout;
using std::endl;

const int size = 5;

enum Constraint{
    greater, less, none
};

Constraint oppositeConstraint(Constraint constraint) {
    switch (constraint) {
        case greater:
            return less;
        case less:
            return greater;
        case none:
        default:
            return constraint;
    }
}

struct Coordinate {
    int row, column;
    
    Coordinate(int row, int column) {
        this->row = row;
        this->column = column;
    }
};

class Puzzle {
    
    Constraint horizonalConstraints[size][size - 1];
    Constraint verticalConstraints[size][size - 1];
    
    Constraint constraintFor(char c) {
        switch (c) {
            case '<':
                return less;
            case '>':
                return greater;
            case '|':
            default:
                return none;
        }
    }
    
public:
    //empty cells are zero
    int grid[size][size];
    
    Puzzle(istream &is) {
        string line1, line2;
        is >> line1 >> line2;
        
        // Initialize the grid
        for (int row = 0; row < size; row++) {
            for (int column = 0; column < size; column++) {
                grid[row][column] = line1[row * size + column] - '0';
            }
        }
        
        // Initialize the horizonal constraints
        for (int row = 0; row < size; row++) {
            for (int column = 0; column < size - 1; column++) {
                Constraint symbol = constraintFor(line2[row * (size - 1) + column]);
                horizonalConstraints[row][column] = symbol;
            }
        }
        
        // Initialize the vertical constraints
        const int start = size * (size - 1);
        for (int row = 0; row < size; row++) {
            for (int column = 0; column < size - 1; column++) {
                Constraint symbol = constraintFor(line2[start + row * (size - 1) + column]);
                verticalConstraints[row][column] = symbol;
            }
        }
    }
    
    Constraint getConstraintFor(Coordinate coordinate1, Coordinate coordinate2) {
        if (!(coordinate1.row >= 0 && coordinate1.row < size &&
             coordinate1.column >= 0 && coordinate1.column < size &&
             coordinate2.row >= 0 && coordinate2.row < size &&
             coordinate2.column >= 0 && coordinate2.column < size)) {
            return none;
        }
        
        if (coordinate1.row == coordinate2.row) {
            if (coordinate1.column + 1 == coordinate2.column) {
                return horizonalConstraints[coordinate1.row][coordinate1.column];
            } else if (coordinate1.column - 1 == coordinate2.column) {
                return oppositeConstraint(horizonalConstraints[coordinate1.row][coordinate1.column - 1]);
            } else {
                return none;
            }
        } else if (coordinate1.column == coordinate2.column) {
            if (coordinate1.row + 1 == coordinate2.row) {
                return verticalConstraints[coordinate1.column][coordinate1.row];
            } else if (coordinate1.row - 1 == coordinate2.row) {
                return oppositeConstraint(verticalConstraints[coordinate1.column][coordinate1.row-1]);
            } else {
                return none;
            }
        } else {
            return none;
        }
    }

    string toString() const {
        ostringstream oss;
        for (int row = 0; row < size; row++) {
            for(int column = 0; column < size; column++) {
                oss << grid[row][column];
            }
        }
        return oss.str();
    }
};

Puzzle solve(Puzzle puzzle) {
    return puzzle; // <-- Solve the puzzle here
}

int main(int argc, const char * argv[]) {
    ifstream ifs;
    for (string filename : { "00", "01", "02", "03", "04", "05" }) {
        
        ifs.open("tests/" + filename + ".in");
        Puzzle puzzle(ifs);
        ifs.close();
        
        Puzzle solved = solve(puzzle);
        
        ifs.open("tests/" + filename + ".out");
        string solution;
        ifs >> solution;
        ifs.close();
        
        if (solved.toString() == solution) {
            cout << "Solved! " << solved.toString() << endl;
        } else {
            cout << "Incorrect solution!" << endl;
            cout << "Your solutions: " << solved.toString() << endl;
            cout << "Correct solution: " << solution << endl;
        }
    }
    return 0;
}
