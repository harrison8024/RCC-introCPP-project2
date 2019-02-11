/* 
 * File:   main.cpp
 * Author: Harrison Chen
 * Created on January 21, 2019, 03:00 PM
 * Purpose: Project 1 Blackjack V4 - fixed game logic bugs and checked for a
 *                                   soft 21. change some display layout
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

//Create vector for card with rank, suit and value
struct Card{    
    int rank;    //stores the rank of the card
    string suit; //stores the suit of the card
    int value;   //stores the value of the card
};

//Create class of Game the holds all the function 
class Game {
private:
    
public:
    // Function to Create a Deck:
    //parameters take in the deck and the number of poker deck wish to create
    void crtDck(vector<Card> &deck, int nDeck = 1){ 
        //rank Names
        string rankArr[4] = {"Heart", "Diamond", "Spade", "Club"};
        
        // Loop for creating suits, rank, and value
        int i = 0;
        for(int it = 0; it < nDeck; it++){
            deck.push_back(Card());
            for(int j = 0; j < 4; j++){
                for(int k = 1; k < 14; k++){
                    deck[i].rank = k;
                    deck[i].suit = rankArr[j]; 
                    if(k > 10){
                        deck[i].value = 10;
                    } else {
                        deck[i].value = k;
                    }
                    i++;
                }
            }
        }
    }
    
    // Function to Deal a Card and remove a card from deck
    void deal(vector<Card>& deck, vector<Card>& hand){
        int ranNum;
        ranNum = rand() % (deck.size() - 2);
        hand.push_back(deck[ranNum]); //added the cards chosen to the hand
        deck.erase(deck.begin() + ranNum); //erase the card from the deck
    }
    
    //Function that show the player's hand
    void shwPlyr(vector<Card> &hand){
        cout << endl << "Player's Hand :" << endl;
        for(int i = 0; i < hand.size(); i++){
            cout << "[" << hand[i].rank << " " << hand[i].suit << "]" << endl;
        }
    }
    
    //Function that show the house's hand
    void shwHous(vector<Card> &hand){
        cout << endl << "House's Hand :" << endl;
        for(int i = 0; i < hand.size(); i++){
            cout << "[" << hand[i].rank << " " << hand[i].suit << "]" << endl;
        }
    }
    
    //Function that Checks for Blackjack
    bool checkBJ(vector<Card>& hand){
        int sum = 0;
        bool aceP = false;
        for(int i = 0; i < hand.size(); i++){
            if(hand[i].value == 1){ //check if ace is present
                aceP = true;
            }
            sum += hand[i].value; //sum of all the cards
        }
        if(aceP && sum == 11){ // check if the sum is 11 and there is a ace
            return true; //BJ
        } else {
            return false; //Not BJ
        }
    }
    
    //Function that check if the sum of the cards are over 21
    bool chkOvr(vector<Card>& hand){
        int sum = 0;
        for(int i = 0; i < hand.size(); i++){
            sum += hand[i].value;
        }
        if(sum > 21){
            return true;
        } else {
            return false;
        }
    }
    
    //Function that will compare the player's and the house's hand
    int compHd(vector<Card>& player, vector<Card>& house){
        bool aceP = false;
        int sumP = 0;
        int sumH = 0;
        for(int i = 0; i < player.size(); i++){
            if(player[i].value == 1){
                aceP = true;
            }
            sumP += player[i].value;
        }
        for(int i = 0; i < house.size(); i++){
            if(player[i].value == 1){
                aceP = true;
            }
            sumH += house[i].value;
        }
        if(aceP && (sumP + 10) <= 21){
            sumP += 10;
        }
        if(aceP && (sumH + 10) <= 21){
            sumH += 10;
        }
        if(sumP > sumH){
            return 1;
        }else if(sumP < sumH){
            return 2;
        }else {
            return 3;
        }
    }
    
    //Function that will determine if the house will hit or stand
    bool housHit(vector<Card>& house){
        int sum = 0;
        for(int i = 0; i < house.size(); i++){
            sum += house[i].value;
        }
        if(sum < 17){
            return true;
        } else {
            return false;
        }
    }
    
    //Function that clears the hand
    void clearHd(vector<Card>& hand){
        hand.clear();
    }
    
    
};

// Execution Begins Here:
int main(int argc, char** argv) {
    // Set random number seed
    srand(time(0));
    
    // Declare Variables
    char input;
    int ranNum, 
        nDeck, 
        result, // 0 = player gets 1.5X payout, 1 = player gets 1X payout, 2 = player lost, 3 = draw
        bet;
    nDeck = 2;
    vector<Card> deck(52 * nDeck);
    vector<Card> plyrHd(0);
    vector<Card> housHd(0);
    
    //Start Game
    Game game;
    game.crtDck(deck, nDeck);
    cout << "Welcome to BlackJack!" << endl;
    cout << "Beat the dealer by getting a count as close to 21 as possible, without going over 21." << endl << endl;
    cout << "Enter any key to start, if you want to exit the game anytime of the game just enter 'x'" << endl;
    cin >> input;
    while(input != 'x'){
        cout << "Place Your bets or enter 'x' to exit." << endl;
        cin >> input;
        if(input == 'x'){
            continue;
        }
        //Deals two initial cards to player
        game.deal(deck, plyrHd);
        game.deal(deck, plyrHd);
        
        //Deals one initial cards to house
        game.deal(deck, housHd);
        
        //Display all the cards
        game.shwHous(housHd);
        game.shwPlyr(plyrHd);
        
        //Game logic starts
        if(game.checkBJ(plyrHd)){  //Check if player has BJ
            cout << endl << "Player got 21 Won!" << endl;
            result = 0; //result of 1.5X payout
        } else {
            bool endGm = false; //Declare a boolean for endGame flag
            do{
                //Asking player to hit or stand
                cout << endl << "Enter 'h' to Hit or 's' to Stand" << endl;
                char HorS;
                cin >> HorS;
                switch(HorS){
                    //If player choose hit
                    case 'h':
                        game.deal(deck, plyrHd); //Deal another card to player
                        game.shwPlyr(plyrHd);    //Display player's hand
                        if(game.chkOvr(plyrHd)){ //Check if sum of player's hand is over 21
                            cout << endl << "Your hand is over 21, you lost the bet!" << endl;
                            endGm = true;
                            result = 2;
                        }
                        break;
                        
                    //If player choose stand
                    case 's':
                        game.deal(deck, housHd);  //Deal second card to house's hand
                        game.shwHous(housHd);     //Display house's hand
                        if(game.checkBJ(housHd)){ //Check if house has BJ
                            cout << endl << "The house has Blackjack, You lost the bet!" << endl;
                            result = 2;
                        } else {
                            //if house does not have BJ
                            while(game.housHit(housHd)){ //Check if house need to hit
                                game.deal(deck, housHd); //Deals another card to house
                                game.shwHous(housHd);    //Display house's hand
                            }
                            game.shwPlyr(plyrHd);
                            if(game.chkOvr(housHd)){
                                cout << endl << "The house's hand has busted, You win!" << endl;
                                result = 1;
                            } else {
                                //Compared the player's hand against the house's hand
                                result = game.compHd(plyrHd, housHd);
                                switch(result){
                                    case 1: //Player's hand > house's hand
                                        cout << endl << "You win!" << endl;
                                        break;
                                    case 2: //House's hand > player's hand
                                        cout << endl << "House win!" << endl;
                                        break;
                                    case 3: //Tie
                                        cout << endl << "Draw" << endl;                                  
                                }
                            }
                        }
                        endGm = true; //End game logic loop
                        break;
                    case 'x': //press x to exit
                        endGm = true; //End game logic loop
                        break;
                    default: //invalid input, try again
                        cout << endl << "Your input is not valid, please Enter 'h' to Hit or 's' to Stand" << endl;
                        break;
                }
            }while(!endGm); //if endGm = true then the game logic loops end
            game.clearHd(plyrHd);
            game.clearHd(housHd);
        }
    }
    
    cout << endl << "Thank you for playing!";  
    // Exit stage right or left!
    return 0;
}



