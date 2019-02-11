/* 
 * File:   main.cpp
 * Author: Harrison Chen
 * Created on February 08, 2019, 11:30 PM
 * Purpose: Project 1 Blackjack V7 - adding statistic menu
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


//Create vector for card with rank, suit and value
struct Card{    
    int rank;    //stores the rank of the card
    string suit; //stores the suit of the card
    int value;   //stores the value of the card
};

// Function Prototypes
void crtDck(vector<Card> &, int);  
void deal(vector<Card> &, vector<Card> &);   
void shwPlyr(vector<Card> &);   
void shwHous(vector<Card> &);   
bool checkBJ(vector<Card> &);   
bool chkOvr(vector<Card> &);  
int  compHd(vector<Card> &, vector<Card> &);
bool housHit(vector<Card> &);   
void clearHd(vector<Card>&);   
int  plcBet(char);   
void payout(int, int, int &);
void staMenu();

// Execution Begins Here:
int main(int argc, char** argv) {
    // Set random number seed
    srand(time(0));
    
    // Declare Variables
    char input;
    int ranNum, //random generated number
        nDeck,  //number of deck that is used in a game
        result, // 0 = player gets 1.5X payout, 1 = player gets 1X payout, 2 = player lost, 3 = draw
        chips,  //Number of chips a player has
        gmCnt,
        winCnt,
        winPrc,
        bet;    //Players bet
    nDeck = 2;
    chips = 100;
    gmCnt = 0;
    winCnt = 0;
    winPrc = 0;
    vector<Card> deck(52 * nDeck);
    vector<Card> plyrHd(0);
    vector<Card> housHd(0);
    
    //Start Game
    crtDck(deck, nDeck);
    cout << "Welcome to BlackJack!" << endl;
    cout << "Beat the dealer by getting a count as close to 21 as possible, without going over 21." << endl << endl;
    cout << "Enter any key to start, if you want to exit the game anytime of the game just enter 'x'" << endl;
    cin >> input;
    system("clear");
    while(input != 'x'){
        cout << endl << "Round: " << gmCnt+1 << " | Chip: " << chips << " | Games Won: " << winCnt << " | Win Percentage: " << winPrc << "%" << endl;
        cout << endl << "Place Your bets by selecting the letters below. Enter 'x' to exit. Enter 'i' for Statistical Analysis."  << endl;
        cout << endl << "a: 10" << endl << "b: 20" << endl << "c: 50" << endl << "d: 100" << endl;
        cin >> input;
        if(input == 'x'){
            continue;
        }
        if(input != 'a' && input != 'b' && input != 'c' && input != 'd' && input != 'i'){
            cout << "invalid input" << endl;
            continue;
        }
        if(input == 'i'){
            staMenu();
            continue;
        }
        bet = plcBet(input); //bet is placed
        if(bet > chips){
            cout << "Cannot place bet, not enough chips" << endl;
        }
        cout << endl << "Your bet is: " << bet << endl;
        //Deals two initial cards to player
        deal(deck, plyrHd);
        deal(deck, plyrHd);
        
        //Deals one initial cards to house
        deal(deck, housHd);
        
        //Display all the cards
        shwHous(housHd);
        shwPlyr(plyrHd);
        
        //Game logic starts
        if(checkBJ(plyrHd)){  //Check if player has BJ
            cout << endl << "Player got 21 Won!" << endl;
            winCnt++;
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
                        deal(deck, plyrHd); //Deal another card to player
                        cout << endl << "The dealer has deal another card to your hand" << endl;
                        shwPlyr(plyrHd);    //Display player's hand
                        if(chkOvr(plyrHd)){ //Check if sum of player's hand is over 21
                            cout << endl << "Your hand is over 21, you lost the bet!" << endl;
                            endGm = true;
                            result = 2;
                        }
                        break;
                        
                    //If player choose stand
                    case 's':
                        deal(deck, housHd);  //Deal second card to house's hand
                        cout << endl << "The dealer has revealed his cards." << endl;
                        shwHous(housHd);     //Display house's hand
                        if(checkBJ(housHd)){ //Check if house has BJ
                            cout << endl << "The house has Blackjack, You lost the bet!" << endl;
                            result = 2;
                        } else {
                            //if house does not have BJ
                            while(housHit(housHd)){ //Check if house need to hit
                                deal(deck, housHd); //Deals another card to house
                                cout << endl << "The dealer deals another card to the house" << endl;
                                shwHous(housHd);    //Display house's hand
                            }
                            shwPlyr(plyrHd);
                            if(chkOvr(housHd)){
                                cout << endl << "The house's hand has busted, You win!" << endl;
                                winCnt++;
                                result = 1;
                            } else {
                                //Compared the player's hand against the house's hand
                                result = compHd(plyrHd, housHd);
                                switch(result){
                                    case 1: //Player's hand > house's hand
                                        cout << endl << "------You win!------" << endl;
                                        winCnt++;
                                        break;
                                    case 2: //House's hand > player's hand
                                        cout << endl << "-----House win!-----" << endl;
                                        break;
                                    case 3: //Tie
                                        cout << endl << "--------Draw--------" << endl;                                  
                                }
                            }
                        }
                        endGm = true; //End game logic loop
                        break;
                    case 'x': //press x to exit
                        input = 'x';
                        endGm = true; //End game logic loop
                        break;
                    default: //invalid input, try again
                        cout << endl << "Your input is not valid, please Enter 'h' to Hit or 's' to Stand" << endl;
                        break;
                }
            }while(!endGm); //if endGm = true then the game logic loops end
            clearHd(plyrHd);
            clearHd(housHd);
        }
        payout(bet, result, chips);
        if(chips <= 0){
            cout << endl << "You have 0 chips, game over!" << endl;
            input = 'x';
        }
        gmCnt++;
        winPrc = 100.0f * winCnt / gmCnt;
    }
    
    cout << endl << "Thank you for playing!";  
    // Exit stage right or left!
    return 0;
}

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
    bool aceP = false;
    for(int i = 0; i < house.size(); i++){
        if(house[i].value == 1){
            aceP = true;
        }
        sum += house[i].value;
    }
    if(sum + 10 < 21){
        sum += 10;
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

//Function that determines how many chips the player bets
int plcBet(char select){
    switch(select){
        case 'a':
            return 10;
            break;
        case 'b':
            return 20;
            break;
        case 'c':
            return 50;
        case 'd':
            return 100;
        default:
            return 0;
    }
}

//Function that calculates the payout
void payout(int bet, int result, int& plyr){
    switch(result){
        case 0:
            plyr += (bet * 1.5);
            break;
        case 1:
            plyr += bet;
            break;
        case 2:
            plyr -= bet;
            break;
        case 3:
            break;
    }
}

void staMenu(){
    char in;
    bool invalid = true;
    do{
        cout << "Statistic Menu" << endl;
        cout << endl << "1. Hand Summary" << endl;
        cout << "2. Card Summary" << endl;
        cout << "3. Exit Menu" << endl;    
        cin >> in;
        switch(in){
            case '1':
                cout << "-----Hand Summary-----"<< endl;
                invalid = false;
                break;
            case '2':
                cout <<"" << endl;
                invalid = false;
                break;
            case '3':
                cout << "Exit Statistic Menu" << endl;
                invalid = false;
                break;
            default:
                cout << "Invalid Input "<< endl;
        }
    }while(invalid);
}