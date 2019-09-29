/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA
 * Name: Masato Lin
 * USC email: masatoli@usc.edu
 * Comments (you want us to know):
 *
 *
 ******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>
//#include <math.h>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these 
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
    for (int i=52-1;i>0;i--){
        int j = rand() % (i+1);
        int temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
    

}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{
    cout << type[id%13] << '-' << suit[id/13];
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id)
{
    return value[id%13];
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
    for (int i=0;i<numCards;i++) {
        printCard(hand[i]);
        cout << ' ';
    }
}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
    int sum = 0;
    int aces = 0;
    for (int i=0;i<numCards;i++) {
        if (cardValue(hand[i]) == 11) {
            aces++;
        }
        sum += cardValue(hand[i]);
    }
    if (sum>21 && aces>0){
        while (sum>21 && aces>0) {
            sum -= 10;
            aces--;
        }
    }
    return sum;
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------
    //variables
    char cont = 'y';
    while (cont == 'y') {
        //variables
        int pcardNumber = 2;
        int dcardNumber = 2;
        int pcardCopy = pcardNumber;
        char prompt = 'h';
        bool gameEnd = false;
        
        //sets the card deck
        for (int i=0;i<52;i++){
            cards[i] = i;
        }
    
        //shuffles and prints out the cards
        shuffle (cards);
    
        //deals first 4 cards
        int j=0;
        for (int i=0;i<2;i++) {
            phand[i] = cards[j];
            j++;
            dhand[i] = cards[j];
            j++;
            
        }
    
        //prints dealer
        cout << "Dealer: ? ";
        printCard (dhand[1]);
        cout << endl;
    
        while (prompt == 'h') {
            
            //prints player
            cout << "Player: ";
            printHand (phand,pcardNumber);
            cout << endl;
        
            //player bust
            if (getBestScore(phand,pcardNumber)>21) {
                cout << "Player busts" << endl;
                cout << "Lose " << getBestScore(phand,pcardNumber);
                cout << ' ' << getBestScore(dhand,dcardNumber) << endl;
                gameEnd = true;
                break;
            }
            
            //player gets 21
            else if (getBestScore(phand,pcardNumber)==21) {
                pcardCopy = pcardNumber;
                break;
            }
        
            //prompt to continue
            else {
                cout << "Type 'h' to hit and 's' to stay:" << endl;
                cin >> prompt;
            }
            
            if (prompt == 'h') {
                //adds cards if player continues
                phand[pcardNumber] = cards[pcardNumber+2];
                pcardNumber++;
                pcardCopy = pcardNumber;
            }
        }
        if (gameEnd == false) {
            
            //dealer adds cards until it's over 16
            while (getBestScore(dhand,dcardNumber)<17) {
                pcardCopy++;
                dhand[dcardNumber] = cards[pcardCopy+1];
                dcardNumber++;
                
            }
    
            //if dealer busts
            if (getBestScore(dhand,dcardNumber)>21) {
                cout << "Dealer: ";
                printHand (dhand,dcardNumber);
                cout << endl;
                cout << "Dealer busts" << endl;
                cout << "Win " << getBestScore(phand,pcardNumber);
                cout << ' ' << getBestScore(dhand,dcardNumber) << endl;
            }
    
            //if player's score is less that dealer's
            else if (getBestScore(dhand,dcardNumber)>getBestScore(phand,pcardNumber)) {
                cout << "Dealer: ";
                printHand (dhand,dcardNumber);
                cout << endl;
                cout << "Lose " << getBestScore(phand,pcardNumber);
                cout << ' ' << getBestScore(dhand,dcardNumber) << endl;
            }
    
            //if player's score is greater than dealer's
            else if (getBestScore(dhand,dcardNumber)<getBestScore(phand,pcardNumber)) {
                cout << "Dealer: ";
                printHand (dhand,dcardNumber);
                cout << endl;
                cout << "Win " << getBestScore(phand,pcardNumber);
                cout << ' ' << getBestScore(dhand,dcardNumber) << endl;
            }
            
            //if the player gets 21
            else if (getBestScore(phand,pcardNumber)==21) {
                cout << "Win " << getBestScore(phand,pcardNumber);
                cout << ' ' << getBestScore(dhand,dcardNumber) << endl;
            }
    
            //if they tie
            else if (getBestScore(dhand,dcardNumber)==getBestScore(phand,pcardNumber)) {
                cout << "Dealer: ";
                printHand (dhand,dcardNumber);
                cout << endl;
                cout << "Tie " << getBestScore(phand,pcardNumber);
                cout << ' ' << getBestScore(dhand,dcardNumber) << endl;
            }
        }
        
        //restarts if player answers yes
        cout << endl;
        cout <<"Play again? [y/n]" << endl;
        cin >> cont;
        cout << endl;
    }
  return 0;
}
