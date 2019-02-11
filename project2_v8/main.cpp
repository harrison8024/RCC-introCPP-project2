/* 
 * File:   main.cpp
 * Author: Harrison Chen
 * Created on February 09, 2019, 10:30 PM
 * Purpose: Project 1 Blackjack V7 - Adding hand Summary
 */

//System Libraries
#include <iostream> //Input/Output Library
#include <string>   //String Library
#include <cstdlib>  //C standad Library
#include <ctime>    //time library for random
#include <vector>   //vector library
#include <iomanip>  //Output formating
using namespace std; //namespace standard

// User Libraries

// Global Constants, no global variables are allowed 
// Math/Physics/Conversions/ Higher Dimensions - i.e, PI, e, etc...

//constant 
static const int COL = 13; //Column number for 2d array
static const int ROW = 4;  //Row number for 2d array

//Create vector for card with rank, suit and value
struct Card{    
    string rank; //stores the rank of the card
    string suit; //stores the suit of the card
    int value;   //stores the value of the card
};

// Function Prototypes
void crtDck(vector<Card> &, int);   //Function that creates card and place into deck
void deal(vector<Card> &, vector<Card> &);   // Function to Deal a Card and remove a card from deck
void shwPlyr(vector<Card> &);       //Function that show the player's hand
void shwHous(vector<Card> &);       //Function that show the house's hand
bool checkBJ(vector<Card> &);       //Function that Checks for Blackjack
bool chkOvr(vector<Card> &);        //Function that check if the sum of the cards are over 21
int  compHd(vector<Card> &, vector<Card> &, int [], int [], int); //Function that will compare the player's and the house's hand
bool housHit(vector<Card> &);       //Function that will determine if the house will hit or stand
void clearHd(vector<Card>&);        //Function that clears the hand
int  plcBet(char);                  //Function that determines how many chips the player bets
void payout(int, int, int &);       //Function that calculates the payout
void staMenu(int, int [], int [], int[][COL]);  //Function for stats Menu
void addAllC(vector<Card> &, int[][COL]); //Function for adding cards to 2d array
void initCA(int[][COL]); //Function to initialize 2d array

// Execution Begins Here:
int main(int argc, char** argv) {
    // Set random number seed
    srand(static_cast<unsigned int>(time(0)));
    // Declare Variables
    char input; //variable for input
    int ranNum, //random generated number
        nDeck,  //number of deck that is used in a game
        result, // 0 = player gets 1.5X payout, 1 = player gets 1X payout, 2 = player lost, 3 = draw
        chips,  //Number of chips a player has
        gmCnt,  //Number of Games played
        winCnt, //Number of Games Won
        bet;    //Players bet
    float winPrc; //Wining percentage
    nDeck = 2;  // Using two deck of cards to play
    chips = 100; // Starting with 100 chips
    gmCnt = 0;  // setting game count to 0
    winCnt = 0; //setting win count to 0
    winPrc = 0; //setting win percentage to 0
    vector<Card> deck(52 * nDeck); // Creating vector to store all the cards
    vector<Card> plyrHd(0); // Vector to hold the player's hand
    vector<Card> housHd(0); //Vector to hold the house's hand
    int plyrHdA[100]; //player hand Array
    int housHdA[100]; //House hand Array
    int cardTotA[ROW][COL]; // Total cards Array - 2D
    

    
    //Start Game
    crtDck(deck, nDeck); // create the deck with the vector and number of deck you want
    initCA(cardTotA); // Initializing the total card array with 0's
    cout << "Welcome to BlackJack!" << endl; // Welcome prompt
    cout << "Beat the dealer by getting a count as close to 21 as possible, without going over 21." << endl << endl;
    cout << "Enter any key to start, if you want to exit the game anytime of the game just enter 'x'" << endl;
    cin >> input; // waiting for input
    while(input != 'x'){ // game loop will exit if input is x
        cout << endl << "Round: " << gmCnt+1 << " | Chip: " << chips << " | Games Won: " << winCnt << " | Win Percentage: " << winPrc << "%" << endl; //display game stats
        cout << endl << "Place Your bets by selecting the letters below. Enter 'x' to exit. Enter 'i' for Statistical Analysis."  << endl;
        cout << endl << "a: 10" << endl << "b: 20" << endl << "c: 50" << endl << "d: 100" << endl; 
        cin >> input; // waiting for use to input bet selection
        if(input == 'x'){ //if user enter x then break the current loop
            continue;
        }
        if(input != 'a' && input != 'b' && input != 'c' && input != 'd' && input != 'i'){ //if invalid input breaks the loop
            cout << "invalid input" << endl;
            continue;
        }
        if(input == 'i'){ // if user enter i call stats Menu function
            staMenu(gmCnt, plyrHdA, housHdA, cardTotA);
            continue; //breaks the loop after quitting the stats menu
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
                            endGm = true; // will end the game loop
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
                                winCnt++; //add one the win count
                                result = 1;
                            } else {
                                //Compared the player's hand against the house's hand
                                result = compHd(plyrHd, housHd, plyrHdA, housHdA, gmCnt);
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
            addAllC(plyrHd, cardTotA);
            addAllC(housHd, cardTotA);
            clearHd(plyrHd); //clear player's hand
            clearHd(housHd); //clear house's hand
        }
        payout(bet, result, chips); // determine the payout of game
        // Game over when funds are insufficient
        if(chips <= 0){
            cout << endl << "You have 0 chips, game over!" << endl;
            input = 'x';
        }
        gmCnt++; //add one to game count
        winPrc = 100.0f * winCnt / gmCnt; //Calculate the wining percentage
    }
    
    cout << endl << "Thank you for playing!";  
    // Exit stage right or left!
    exit(0);
}

//Function that creates card and place into deck
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
                    switch(k){
                        case 1:
                            deck[i].rank = 'A';
                            break;
                        case 11:
                            deck[i].rank = 'J';
                            break;
                        case 12:
                            deck[i].rank = 'Q';
                            break;
                        case 13:
                            deck[i].rank = 'K';
                            break;
                        default:
                            deck[i].rank = to_string(k);
                            break;
                    }
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
int compHd(vector<Card>& player, vector<Card>& house, int plyrHdA[], int housHdA[], int gmCnt){
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
    plyrHdA[gmCnt] = sumP;
    housHdA[gmCnt] = sumH;
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

//Functions for stats Menu
void staMenu(int gmCnt, int plyrHdA[], int housHdA[], int cardTotA[][COL]){
    char in;
    bool invalid = true;
    do{
        cout << "-----Statistic Menu-----" << endl;
        cout << endl << "1. Hand Summary" << endl;
        cout << "2. Card Summary" << endl;
        cout << "3. Exit Menu" << endl;    
        cin >> in;
        switch(in){
            case '1':
                cout << "-------Hand Summary-----"<< endl;
                cout << "*Note: 0 means either it was a Black Jack or Bust during that game." << endl;
                cout << "Player's Hand: ";
                for(int i = 0; i < gmCnt; i++){
                    cout << setw(3) << plyrHdA[i];
                }
                cout << endl;
                cout << "House's Hand:  ";
                for(int i = 0; i < gmCnt; i++){
                    cout << setw(3) << housHdA[i];
                }
                cout << endl;
                     
                invalid = false;
                break;
            case '2':
                cout << "-------Card Summary-----" << endl;
                cout << "Suit    A 2 3 4 5 6 7 8 9 T J Q K" << endl;
                    for(int i = 0; i < 4; i++){
                        switch(i){
                            case 0:
                                cout << "Heart   ";
                                break;
                            case 1:
                                cout << "Diamond ";
                                break;
                            case 2:
                                cout << "Club    ";
                                break;
                            case 3:
                                cout << "Spade   ";
                                break;
                        }
                        for(int j = 0; j < 13; j++){
                            cout << cardTotA[i][j] << " ";
                        }
                        cout << endl;
                    }
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

//Function for adding cards to 2d array
void addAllC(vector<Card> & hand, int card[][COL]){
    int row, col;
    string rank, suit;
    for(int i = 0; i < hand.size(); i++){
        suit = hand[i].suit;

        if(suit == "Heart"){
            row = 0;
        }else if(suit == "Diamond"){
                row = 1;
        }else if(suit == "Club"){
                row = 2;
        }else if(suit == "Spade"){
                row = 3;
        }
        rank = hand[i].rank;
        if(rank == "A"){
            col = 0;
        }else if(rank == "J"){
            col = 10;
        }else if(rank == "Q"){
            col = 11;
        }else if(rank == "K"){
            col = 12;
        } else {
            col = stoi(rank);
        }
        card[row][col] +=1;
    }
}

void initCA(int a[][COL]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            a[i][j] = 0;
        }
    }
}