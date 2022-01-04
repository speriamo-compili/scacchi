#include <iostream>
#include "header_files\Cell.h"
using namespace std;

int main() {
    for (int i = 0; i <= 25; i++) {
        for (int j = 0; j <= 8; j++) {
            string s = string(1, 'a' + i) + string(1, '0' + j);
            cout << s << " -> ";
            try {
                Cell my_cell{s};
                cout << "VALID " << "{" << my_cell.getCol() << "," << my_cell.getRow() << "}\n";
            } catch (Cell::InvalidCell) {
                cout << "INVALID\n";
            }
        }
    }
}