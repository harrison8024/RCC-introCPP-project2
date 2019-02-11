/* 
 * File:   main.cpp
 * Author: Harrison Chen
 * Created on January 14, 2019, 10:40 PM
 * Purpose: Project 1 Blackjack V2 - Deal cards, remove cards, and create multiple deck
 */

//System Libraries
#include <iostream>  //Input/Output Library
#include <string> 
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

// User Libraries

// Global Constants, no global variables are allowed 
// Math/Physics/Conversions/ Higher Dimensions - i.e, PI, e, etc...

// Function Prototypes
struct Card{    //Create vector for card with rank and suit
    int rank; 
    string suit;
};

class Game {
private:
    // Declare Variable
    string rankArr[4] = {"Heart", "Diamond", "Spade", "Club"};
    
public:
    // Function to Create a Deck
    void crtDck(vector<Card> &deck, int nDeck = 1){
        // Loop for creating suits and rank
        int i = 0;
        for(int it = 0; it < nDeck; it++){
            deck.push_back(Card());
            for(int j = 0; j < 4; j++){
                for(int k = 1; k < 14; k++){
                    deck[i].rank = k;
                    deck[i].suit = rankArr[j]; 
                    i++;
                }
            }
        }
    }
    
    // Function to Deal a Card and remove a card from deck
    void deal(vector<Card>& deck){
        int ranNum;
        ranNum = rand() % (deck.size() - 2);
        cout << "Cards left in deck : " << deck.size() << endl; 
        cout << "Position: " <<  ranNum << endl;
        cout << deck[ranNum].suit << " " << deck[ranNum].rank << endl;
        deck.erase(deck.begin() + ranNum);
    }
    
};

// Execution Begins Here:
int main(int argc, char** argv) {
    // Set random number seed
    srand(time(0));
    
    // Declare Variables
    int ranNum, nDeck;
    nDeck = 2;
    vector<Card> deck(52 * nDeck);
//    Card cards[52]; // Create 52 cards in a deck/array
    
    //Start Game
    Game game;
    game.crtDck(deck, nDeck);
    
    for(int i = 0; i < (52 * nDeck); i++){
        cout << i << ":" << endl;
        game.deal(deck);
    }

//   
    // Exit stage right or left!
    return 0;
}



