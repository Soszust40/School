// CSE 232 Lab 1: 1-18-24
//

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int numberOfDays;
    //cout << "Number of days after 12/30/2016: "; // Type a number and press enter
    cin >> numberOfDays; // Get user input

    // KM Traveled
    double startDistanceKM = 37.33 * 149598000; //Convert start distance into Km
    int secondsPassed = numberOfDays * 24 * 60 * 60; //Convert user input into seconds
    double distancePassed = 14.33 * secondsPassed; //Multiply secondsPassed by km/s velocity
    double totalKMTraveled = startDistanceKM + distancePassed; //Add start plus distanced traveled

    // Miles Traveled
    double startDistanceMiles = 37.33 * 92955800; //Convert start distance into Miles
    double distancePassedMiles = 8.9 * secondsPassed; //Multiply secondsPassed by miles/s velocity
    double totalMilesTraveled = startDistanceMiles + distancePassedMiles; //Add start plus distanced traveled

    //Radio Round Trip
    double totalKMTripIntoMeters = (2 * (totalKMTraveled * 1000)) / 3600; //Multiply Total KM travled into round trip and get into meters and seconds
    double totalKMTripIntoLight = totalKMTripIntoMeters / 299792458; //Get M/S into hours

    // Print Answers
    std::cout << std::fixed << std::setprecision(2); //Round Answers

    cout << totalKMTraveled << endl;
    cout << totalMilesTraveled << endl;
    cout << totalKMTripIntoLight;

}
