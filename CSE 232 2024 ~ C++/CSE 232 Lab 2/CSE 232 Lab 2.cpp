// CSE 232 Lab 1: 1-23-24
//

#include <iostream>

int main() {
    int num;
    int count = 0;
    int sum;
    while (std::cin >> num) { //While there is input
        count = 0;
        if (num < 0) { //If input is less than zero break
            break;
        }
        while (num >= 10) { //Keep looping if greater than one digit
            sum = 0; //Rest sum

            while (num > 0) { //Looping until it runs out of digits
                sum += num % 10; //Add number to the sum
                num /= 10; //Moves onto next digit in the number
            }
            count++; //Additive Persistence
            num = sum;
        }
        std::cout << count << ' ' << num << std::endl; //Print results
    }
    return 0;
}
