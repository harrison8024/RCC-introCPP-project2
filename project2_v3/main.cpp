/* 
 * File:   main.cpp
 * Author: Harrison Chen
 * Created on January 14, 2019, 10:40 PM
 * Purpose: Project 1 Blackjack V3 - Finish game logic without checking for 
 *          ace = 11, and still need work on clearing hands after each round, 
 *          and recording bets.
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
    int value;
};

class Game {
private:
    // Declare Variable
    
public:
    string rankArr[4] = {"Heart", "Diamond", "Spade", "Club"};
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
        hand.push_back(deck[ranNum]);
        deck.erase(deck.begin() + ranNum);
    }
    
    void shwPlyr(vector<Card> &hand){
        cout << "Player's Hand :" << endl;
        for(int i = 0; i < hand.size(); i++){
            cout << "[" << hand[i].rank << " " << hand[i].suit << "]" << endl;
        }
    }
    
    void shwHous(vector<Card> &hand){
        cout << "House's Hand" << endl;
        for(int i = 0; i < hand.size(); i++){
            cout << "[" << hand[i].rank << " " << hand[i].suit << "]" << endl;
        }
    }
    
    bool checkBJ(vector<Card>& hand){
        int sum = 0;
        bool aceP;
        for(int i = 0; i < hand.size(); i++){
            if(hand[i].value == 1){
                aceP = true;
            }
            sum += hand[i].value;
        }
        if(aceP && sum == 11){
            return true;
        } else {
            return false;
        }
    }
    
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
    
    int compHd(vector<Card>& player, vector<Card>& house){
        int sumP = 0;
        int sumH = 0;
        for(int i = 0; i < player.size(); i++){
            sumP += player[i].value;
        }
        for(int i = 0; i < house.size(); i++){
            sumH += house[i].value;
        }
        if(sumP > sumH){
            return 1;
        }else if(sumP < sumH){
            return 2;
        }else {
            return 3;
        }
    }
    
    bool housHit(vector<Card>& house){
        int sum = 0;
        for(int i = 0; i < house.size(); i++){
            sum += house[i].value;
        }
        cout << "sum:" << sum <<  endl;
        if(sum < 17){
            return true;
        } else {
            return false;
        }
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
    vector<Card> plyrDk(0);
    vector<Card> housDk(0);
//    Card cards[52]; // Create 52 cards in a deck/array
    
    //Start Game
    Game game;
    game.crtDck(deck, nDeck);
    cout << "Welcome to BlackJack!" << endl;
    cout << "Beat the dealer by getting a count as close to 21 as possible, without going over 21." << endl;
    cout << "Enter any key to start, if you want to exit the game anytime of the game just enter 'x'" << endl;
    cin >> input;
    while(input != 'x'){
        cout << "Place Your bets or enter 'x' to exit." << endl;
        cin >> input;
        if(input == 'x'){
            continue;
        }
        game.deal(deck, plyrDk);
        game.deal(deck, plyrDk);
        game.deal(deck, housDk);
        game.shwHous(housDk);
        game.shwPlyr(plyrDk);
        if(game.checkBJ(plyrDk)){
            cout << "Player got 21 Won!" << endl;
            result = 0;
        } else {
            bool endGm;
            do{
                cout << "Enter 'h' to Hit or 's' to Stand" << endl;
                char HorS;
                cin >> HorS;
                switch(HorS){
                    case 'h':
                        game.deal(deck, plyrDk);
                        game.shwPlyr(plyrDk);
                        if(game.chkOvr(plyrDk)){
                            cout << "Your hand is over 21, you lost the bet!" << endl;
                            endGm = true;
                            result = 2;
                        }
                        break;
                    case 's':
                        game.deal(deck, housDk);
                        game.shwHous(housDk);
                        if(game.checkBJ(housDk)){
                            cout << "The house has Blackjack, You lost the bet!" << endl;
                            result = 2;
                        } else {
                            while(game.housHit(housDk)){
                                game.deal(deck, housDk);
                                game.shwHous(housDk);
                            }
                            result = game.compHd(plyrDk, housDk);
                            switch(result){
                                case 1:
                                    cout << "Player win!" << endl;
                                    break;
                                case 2:
                                    cout << "House win!" << endl;
                                    break;
                                case 3:
                                    cout << "Draw" << endl;                                  
                            }
                        }
                        endGm = true;
                        break;
                    case 'x':
                        endGm = true;
                        break;
                    default:
                        cout << "Your input is wrong, please Enter 'h' to Hit or 's' to Stand" << endl;
                        break;
                }
            }while(!endGm);
        }
    }
    
    cout << "Thank you for playing!";
//   
    // Exit stage right or left!
    return 0;
}



