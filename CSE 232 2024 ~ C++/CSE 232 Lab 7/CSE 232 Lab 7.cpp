#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

std::string Two_D_Vector_To_String(std::vector<std::vector<char>> vec) {
    std::stringstream os;
    for (int i = 0; i < static_cast<int>(vec.size()); i++) {
        for (int j = 0; j < static_cast<int>(vec.at(i).size()); j++) {
            os << vec.at(i).at(j) << " ";
        }
        os << "\n";
    }
    return os.str();
}

vector<vector<char>> Counting_Spiral(int length) {
    //vector<vector<char>> spiral(length, vector<char>(length, ' '));

    std::vector<std::vector<char> > spiral(
        length,
        std::vector<char>(length, '0'));

    int number = (length * length) - 1;

    int upperBound = 0;
    int leftBound = 0;
    int rightBound = (length - 1);
    int lowerBound = (length - 2);
    int x;
    int y;

    x = y = length - 1;
    while (true) {
        for (;x >= leftBound;x--) {
            spiral.at(y).at(x) = (number % 10) + '0';
            number--;
        }
        x++;
        y--;
        leftBound++;
        for (;y >= upperBound;y--) {
            spiral.at(y).at(x) = (number % 10) + '0';
            number--;
        }
        y++;
        x++;
        upperBound++;
        for (;x <= rightBound;x++) {
            spiral.at(y).at(x) = (number % 10) + '0';
            number--;
        }
        x--;
        y++;
        rightBound--;
        for (;y <= lowerBound;y++) {
            spiral.at(y).at(x) = (number % 10) + '0';
            number--;
        }
        x--;
        y--;
        lowerBound--;
        if (rightBound == leftBound)
            break;
    }
    return spiral;
}

int main() {
  int length;
  cin >> length;
  vector<vector<char>> result = Counting_Spiral(length);
  cout << Two_D_Vector_To_String(result);
  return 0;
}