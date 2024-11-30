#include <iostream>
#include <string>

int TestResult(int result, int expected) {
    if (result == expected) {
        return 1; //Pass
    }
    else {
        return 0; //Fail
    }
}

int RunTests() {
    int correctNumber = 0;
    //Fully Correct
    correctNumber += TestResult(IsSecurePassword("abc123DEF!$@"), 6); // All criteria met in two ways
    //Some Points
    correctNumber += TestResult(IsSecurePassword("a"), 1); // One Lowercase
    correctNumber += TestResult(IsSecurePassword("A"), 1); // One Uppercase
    correctNumber += TestResult(IsSecurePassword("1"), 1); // One Digit
    correctNumber += TestResult(IsSecurePassword("!"), 1); // One Sign
    correctNumber += TestResult(IsSecurePassword("aaaaaaaaaa"), 2); // One Lowercase + 10
    correctNumber += TestResult(IsSecurePassword(">>"), 0); // Bad sign
    correctNumber += TestResult(IsSecurePassword(">>>>>>>>>>"), 1); // Bad sign + 10
    correctNumber += TestResult(IsSecurePassword("abAB@$12"), 5); // Bonus
    return correctNumber;
}

int main() {
    int correct = RunTests();
    if (correct == 9) { std::cout << "Pass"; } //Passed all tests
    else { std::cout << "Fail"; }
    return 0;
}