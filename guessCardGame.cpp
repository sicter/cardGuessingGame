#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;
/*** function PROTOTYPES ***/
vector <int> initDeck();
string card_name(int card);
int card_rank(int card, int aceValue);
string card_suit(int card);
void randomize();
void randomize(int number);
int randomCard(int cardsLeft);
vector<int> shuffleDeck(vector<int> deckVector);
void ranksuitnameToFile(vector<int> deck, int aceValue);
void decksToFile(vector <int> deck, vector<int> newDeck);


int main()
{
    int dealtCard1, dealtCard2, nextCard, aceValue;
    string answer, highOrLow;
    string lines = "-----------------------------------------------------";
    bool guess, checkBetween;
    int countWins = 0;
    int countLosses = 0;
    randomize();

    // INSTRUCTIONS //
    cout << "In this game, the computer plays the part of a card dealer, and the program user is the player." << endl
         << "The dealer shuffles the deck, then repeatedly does the following:" << endl << endl

         <<	"1.Deals 2 cards to the player, face up." << endl
         <<	"2.Asks the player whether or not (s)he thinks the next card will fall between the two cards showing." << endl << "(If the card equals one of the two cards showing, it is not between them.)" << endl
         <<	"3.After the player responds, deals another card." << endl
         << "4.If the player predicted correctly, (s)he wins. Otherwise, the dealer wins." << endl
         <<	"**The game ends when the deck is exhausted.**" << endl << endl;

    //*** Extra Credit: Allowing user to determine ace as high or low ***/
    cout << "Would you like Aces to be high or low? (h or l): " ;
        getline(cin, highOrLow);

    if(highOrLow == "h")
    {
        aceValue = 14;
    }
    else if(highOrLow == "l")
    {
        aceValue = 1;
    }

    cout << endl << "LET THE GAME BEGIN!" << endl << endl;

    //*** Initializing deck **/
    vector<int> startDeck = initDeck();
        ranksuitnameToFile(startDeck, aceValue); // writing the cards' name rank and suits to a file
    vector<int> newDeck = shuffleDeck(startDeck);
        decksToFile(startDeck, newDeck); // writing the deck vector elements to a file
    //*** Playing Game **/
    while(newDeck.size() >= 3) // while there are enough cards in the deck to play the game
    {
    cout << lines << endl;
    dealtCard1 = newDeck[newDeck.size()-1]; // pick card from top of vector as card
    newDeck.pop_back(); // remove from deck
    dealtCard2 = newDeck[newDeck.size()-1];
    newDeck.pop_back();
    cout << "Here are your cards:" << endl;
    cout << setw(10)<< card_name(dealtCard1) << " of " << card_suit(dealtCard1) << setw(10) << card_name(dealtCard2) << " of " << card_suit(dealtCard2)<<  endl;

    cout << "Do you think the next card will lie between these? (y/n): ";
        getline(cin, answer);
    if(answer == "y")
    {
        guess= true;
    }
    else if(answer == "n")
    {
        guess = false;
    }

    nextCard = newDeck[newDeck.size()-1];
    newDeck.pop_back();

    cout << "Here is your next card: " << endl;
    cout<< setw(10) << card_name(nextCard) << " of " << card_suit(nextCard) << endl;

    checkBetween =  ((card_rank(nextCard, aceValue) > card_rank(dealtCard1, aceValue) && card_rank(nextCard, aceValue) < card_rank(dealtCard2, aceValue)) || (card_rank(nextCard, aceValue) < card_rank(dealtCard1, aceValue) && card_rank(nextCard, aceValue) > card_rank(dealtCard2, aceValue)));

    cout << endl;

        if(guess == checkBetween)
        {
            cout << "You won!" << endl;
            countWins++;
        }
        else if(guess != checkBetween)
        {
            cout << "You lose!" << endl;
            countLosses++;
        }
        cout << lines << endl;
    }

    cout << "**************************************" << endl;
    cout << "Total Wins: " << countWins << ", " << "Total Losses: " << countLosses << endl;
    cout << "**************************************" << endl;

system("PAUSE");
return 0;
}

vector <int> initDeck()
{
    vector<int> deck(52);
    for(int i=0; i <= 51; i++)
    {
        deck[i] = i;		
    }

    return deck;
}

string card_name(int card)
{
    int cardname = card%13;
    switch(cardname)
    {
    case 0: return "2";
    case 1: return "3";
    case 2: return "4";
    case 3: return "5";
    case 4: return "6";
    case 5: return "7";
    case 6: return "8";
    case 7: return "9";
    case 8: return "10";
    case 9: return "Jack";
    case 10: return"Queen";
    case 11: return "King";
    default: return "Ace";
    }
}

int card_rank(int card, int aceValue)
{
    int cardrank = card%13;
    switch(cardrank)
    {
    case 0: return 2;
    case 1: return 3;
    case 2: return 4;
    case 3: return 5;
    case 4: return 6;
    case 5: return 7;
    case 6: return 8;
    case 7: return 9;
    case 8: return 10;
    case 9: return 11;
    case 10: return 12;
    case 11: return 13;
    default: return aceValue;
    }
} 

string card_suit(int card)
{
    int cardsuit = (static_cast<int>((card/13))%4);
    switch(cardsuit)
    {
    case 0: return "Clubs";
    case 1: return "Diamonds";
    case 2: return "Hearts";
    default: return "Spades";
    }
}


//*** EXTRA CREDIT RANDOM FUNCTIONS ***//
void randomize()
{
    int a = 16807;
    int m = 2147483647;
    int temp = a*time(0);
    int seed = static_cast<int>(temp%m);
    srand(seed);
}

void randomize(int number)
{
    int a = 16807;
    int m = 2147483647;
    int temp = a*number;
    int seed = static_cast<int>(temp%m);
    srand(seed);
}

//Random Card Generator to generate number between 0 and 51
int randomCard(int cardsLeft)
{
    int card = (rand()/(RAND_MAX+1.0))*cardsLeft;
    return card;
}

//Function to shuffle a vector
vector<int> shuffleDeck(vector<int> deckVector)//deckVector is the original deck in order
{
    int temp, n, i;
    n = 51;

    for(n = 51; n >=0 ; n--)
    {
                // following code should swap out random values for the highest vector place
        i = randomCard(51);// randomize(0) generates random number between 0 and 51
        temp = deckVector[n]; 
        deckVector[n] = deckVector[i];
        deckVector[i] = temp;
    }
        return deckVector;// this is supposed to be the shuffled deck
}

// Writing the full deck to a file to show the rank, suit, and name functions
void ranksuitnameToFile(vector<int> deck, int aceValue)
{
    ofstream fout("suitranknameTest.txt");

    for(int i = 0; i <= 51; i++)
    {
        fout << "[" << deck[i] << "] " << card_name(deck[i]) << " of " << card_suit(deck[i]) << " has rank of: " << card_rank(deck[i], aceValue) << endl;
    }

    fout.close();
}

//Writing the deck vector elements of the initialized deck and shuffled deck to a file
void decksToFile(vector<int> deck, vector<int> newDeck)
{
    ofstream fout("DeckSubprogramTest.txt");

    fout << "Initialized Deck" << endl;

    for(int i= 0; i <=51 ; i++)
    {
        fout << "[" << deck[i] << "]" << " , ";
    }

    fout <<endl << "----------------------------------------------------------------------------------------------------------" << endl;

    fout << "Shuffled Deck" << endl;

    for(int i= 0; i <=51 ; i++)
    {
        fout << "[" << newDeck[i] << "]" << " , ";
    }

    fout << endl;

    fout.close();
}
