/* 
 * File:   main.cpp
 * Author: Harrison Chen
 * Created on February 09, 2019, 10:30 PM
 * Purpose: Project 1 Blackjack V8 
 */

//System Libraries
//Input/Output Library
//String Library
//C standad Library
//time library for random
//vector library
//Output formating
//namespace standard

// User Libraries

// Global Constants, no global variables are allowed 
// Math/Physics/Conversions/ Higher Dimensions - i.e, PI, e, etc...

//constant 
//Column number for 2d array
//Row number for 2d array

//Create vector for card with rank, suit and value
    //stores the rank of the card
    //stores the suit of the card
    //stores the value of the card


// Function Prototypes
//Function that creates card and place into deck
// Function to Deal a Card and remove a card from deck
//Function that show the player's hand
//Function that show the house's hand
//Function that Checks for Blackjack
//Function that check if the sum of the cards are over 21
//Function that will compare the player's and the house's hand
//Function that will determine if the house will hit or stand
//Function that clears the hand
//Function that determines how many chips the player bets
//Function that calculates the payout
//Function for stats Menu
//Function for adding cards to 2d array
//Function to initialize 2d array

// Execution Begins Here:

    // Set random number seed

    // Declare Variables
    //variable for input
    //random generated number
    //number of deck that is used in a game
    // 0 = player gets 1.5X payout, 1 = player gets 1X payout, 2 = player lost, 3 = draw
    //Number of chips a player has
    //Number of Games played
    //Number of Games Won
    //Players bet
    //Wining percentage
    // Using two deck of cards to play
    // Starting with 100 chips
    // setting game count to 0
    //setting win count to 0
    //setting win percentage to 0
    // Creating vector to store all the cards
    // Vector to hold the player's hand
    //Vector to hold the house's hand
    //player hand Array
    //House hand Array
    // Total cards Array - 2D
    

    
    //Start Game
    // create the deck with the vector and number of deck you want
    // Initializing the total card array with 0's
    // Welcome prompt

    // waiting for input
    // game loop will exit if input is x
        //display game stats
        
        // waiting for use to input bet selection
        //if user enter x then break the current loop
        //if invalid input breaks the loop
        // if user enter i call stats Menu function
        //display stat menu
        //breaks the loop after quitting the stats menu
        //bet is placed

        //Deals two initial cards to player
        
        //Deals one initial cards to house

        
        //Display all the cards

        
        //Game logic starts
        //Check if player has BJ
            //result of 1.5X payout
        //Declare a boolean for endGame flag
            
                //Asking player to hit or stand

                    //If player choose hit
                        //Deal another card to player
                        //Display player's hand
                        //Check if sum of player's hand is over 21
                            // will end the game loop
                  
                    //If player choose stand
                        //Deal second card to house's hand
                        //Display house's hand
                        //Check if house has BJ
                        
                            //if house does not have BJ
                            //Check if house need to hit
                                //Deals another card to house
                                //Display house's hand
                                //add one the win count

                                //Compared the player's hand against the house's hand

                                    //Player's hand > house's hand
                                   
                                    //House's hand > player's hand
                                    
                                    //Tie

                        //End game logic loop
                    //press x to exit
                        //End game logic loop
                    //invalid input, try again

            //if endGm = true then the game logic loops end
            //Add cards to 2d array
            //clear player's hand
            //clear house's hand

        // determine the payout of game
        // Game over when funds are insufficient

        //add one to game count
        //Calculate the wining percentage

    // Exit stage right or left!

//Function that creates card and place into deck
        //rank Names
        // Loop for creating suits, rank, and value

    
// Function to Deal a Card and remove a card from deck
    //added the cards chosen to the hand
    //erase the card from the deck


//Function that show the player's hand
    //loop thru all hand
    //display the card

//Function that show the house's hand
    //loop thru all hand
    //display the card


//Function that Checks for Blackjack
    //check if ace is present
    //sum of all the cards
    //check if the sum is 11 and there is a ace
        //BJ
        //Not BJ


//Function that check if the sum of the cards are over 21
    //loop thru all cards
    //sum of all the cards
    //check if sum is over

//Function that will compare the player's and the house's hand
    //loop thru player's hand
        //sum all cards
    //loop thru house's hand
        //sum all cards
    //compare hands

//Function that will determine if the house will hit or stand
    //loop thru house's hand
        //sum all cards up
    //if larger than 17
        //stand
    //else 
        //hit

//Function that clears the hand
    //erase the vector

//Function that determines how many chips the player bets
    // switch for a b c d

//Function that calculates the payout
    //switch for 4 playout

//Functions for stats Menu
    //switch for stats menu
        //loop thru both array for sum of hands
        //loop thru 2d array to display number of cards

//Function for adding cards to 2d array
    //loop thru the hands
    //find each cards and add it to 2d array

//Function to initialize 2d array with 0's
    //loop thru array
        // initialize with 0