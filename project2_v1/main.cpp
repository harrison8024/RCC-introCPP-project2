/* 
 * File:   main.cpp
 * Author: Harrison Chen
 * Created on January 14, 2019, 10:40 PM
 * Purpose: Project 1 V1 - Poker deck
 */

//System Libraries
#include <iostream>  //Input/Output Library
#include <string> 
#include <cstdlib>
#include <ctime>
using namespace std;

// User Libraries

// Global Constants, no global variables are allowed 
// Math/Physics/Conversions/ Higher Dimensions - i.e, PI, e, etc...

// Function Prototypes

// Execution Begins Here:
int main(int argc, char** argv) {
    // Set random number seed
    srand(time(0));
    
    // Declare Variables
    struct card{    //Create struct for card with rank and suit
        int rank; 
        string suit;
    };
    card cards[52]; // Create 52 cards in a deck/array
    string rankArr[4] = {"Heart", "Diamond", "Spade", "Club"};
    int ranNum;
    // Initial or input i.e. set variable values
    int i = 0;
    for(int j = 0; j < 4; j++){
        for(int k = 1; k < 14; k++){
            cards[i].rank = k;
            cards[i].suit = rankArr[j]; 
            i++;
        }
    }
    // Map inputs -> outputs
    ranNum = rand() % 52;
    // Display the outputs
    cout << cards[ranNum].suit << " " << cards[ranNum].rank << endl;
    // Exit stage right or left!
    return 0;
}



