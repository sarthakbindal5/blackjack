#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

int cards[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
int pIndex[10];
int dIndex[10];

string cardFaceValue(int cardIndex)
{
    if(cardIndex == 0)
        return "A";
    else if(cardIndex == 1)
        return "2";
    else if(cardIndex == 2)
        return "3";
    else if(cardIndex == 3)
        return "4";
    else if(cardIndex == 4)
        return "5";
    else if(cardIndex == 5)
        return "6";
    else if(cardIndex == 6)
        return "7";
    else if(cardIndex == 7)
        return "8";
    else if(cardIndex == 8)
        return "9";
    else if(cardIndex == 9)
        return "10";
    else if(cardIndex == 10)
        return "J";
    else if(cardIndex == 11)
        return "Q";
    else if(cardIndex == 12)
        return "K";
    else
        return "";
}

int dealerDraw(int dealerScore, bool dAce, char ifIns, int ins)
{
    srand(time(NULL));
    int di = 1;
        if(dAce)
            dealerScore = 11;
        
        while(dealerScore < 17)
        {
            dIndex[di++] = rand()%13;
            cout << "\nDealer card = " << cardFaceValue(dIndex[di-1]) << endl;
            dealerScore += cards[dIndex[di-1]];
            
            if(dIndex[di-1] == 0)
            {
                dAce = true;
                dealerScore += 10;
            }
            if(dAce)
            {
                if(dealerScore > 21)
                {
                    dealerScore -= 10;
                    dAce = false;
                }
            }
//            if(dAce && (dIndex[1] == 9 || dIndex[1] == 10 || dIndex[1] == 11 || dIndex[1] == 12)) //changes to be done in this function
//            {
//                if(ifIns == 'y')
//                {
//                    cout << "You won $" << 2*ins << " as a result of your insurance bet!";
//                }
//                cout << "\nDealer has a blackjack.\n";
//                return 100;
//            }
            
            for(int count = 0; count <= di-1; count++)
            {
                cout << cardFaceValue(dIndex[count]);
                if(count != di-1)
                    cout << " -> ";
            }
            cout << endl;
            
            if(dAce)
            {
                cout << "Total dealer score = " << dealerScore-10 << "/" << dealerScore << endl;
            }
            else
                cout << "Total dealer score = " << dealerScore << endl;
            
            if(dealerScore > 21)
            {
                cout << "Dealer has busted. You win!!!\n";
                return -1;
            }
        for(int i = 1; i <= 1500000000; i++);
    }
    return dealerScore;
}

int checkWin(int dealerscore, int playerScore, int bet)
{
    if(dealerscore > playerScore)
    {
        cout << "Dealer wins. You lose $" << bet << ".\n";
        return (-bet);
    }
    else if(dealerscore < playerScore)
    {
        cout << "You win " << bet << "!!!\n";
        return bet;
    }
    else if(dealerscore == playerScore)
        cout << "Hand has drawn...\n";
    
    return 0;
}

bool isBust(int playerScore)
{
    if(playerScore > 21)
    {
        cout << "Hand has busted...\n";
        return true;
    }
    return false;
}

int betHand(int bet)
{
    srand(time(NULL));
    string choice = "h";
    int playerScore = 0, dealerScore = 0, pi = 2, ins = 0;
    bool pAce = false, dAce = false;
    char ifIns = false;
    
    //displaying first 2 cards for player
    pIndex[0] = rand()%13;
    cout << "Card 1 = " << cardFaceValue(pIndex[0]) << endl;
    playerScore += cards[pIndex[0]];
    
    pIndex[1] = rand()%13;
    cout << "Card 2 = " << cardFaceValue(pIndex[1]) << endl;
    playerScore += cards[pIndex[1]];
    
    //displaying initial score of player
    cout << "Total Score = ";
    if(pIndex[0] == 0 || pIndex[1] == 0) //i.e. either of 2 starting cards is an ace
    {
        playerScore += 10;
        pAce = true;
        cout << playerScore-10 << "/" << playerScore << endl;
    }
    else
        cout << playerScore << endl;
    
    //displaying upcard of dealer
    dIndex[0] = rand()%13;
    cout << "\nDealer up card = " << cardFaceValue(dIndex[0]) << endl;
    dealerScore += cards[dIndex[0]];
    if(dIndex[0] == 0)
        dAce = true;
    
    if(pAce && playerScore == 21 && !dAce)
    {
        cout << "BLACKJACK!!!\n";
        cout << "You win $" << (1.5*bet) << "!!!\n";
        return (1.5*bet);
    }
    cout << endl << cardFaceValue(pIndex[0]) << " -> " << cardFaceValue(pIndex[1]) << endl;
    cout << "Enter sur to Surrender your cards\n";
    if(dAce && pAce && playerScore == 21)
        cout << "Enter em to opt for even money";
//    if(dAce)
//    {
//        cout << "You can make an insurance bet (pays 2 to 1) upto a half of your initial bet.";
//        cout << "Enter y to make an insurance bet and n to not: ";
//        cin >> ifIns;
//        if(ifIns == 'y')
//        {
//            cout << "Enter the amount you want to insure (upto half your initial bet): ";
//            cin >> ins;
//            if(ins <= 0 || ins > bet/2)
//                goto ifins;
//        }
//    }
    cout << "Enter h to hit or s to stand or d to double down: ";
    cin >> choice;
    if(choice == "sur")
    {
        cout << "You have surrendered your cards.\n";
        cout << "You retain half your bet of $" << (bet/2) << ".\n";
        return (-bet/2);
    }
    if(choice == "em")
    {
        cout << "You have opted to receive even money for your blackjack.\n";
        cout << "You win $" << bet << "!\n";
        return bet;
    }
    if(choice != "h" && choice != "s" && choice != "d")
    {
        cout << "Invalid input.\n";
        goto IIAmendment;
    }
    if(choice == "h" || choice == "d")
        goto notSurr;
    
    while(choice == "h")
    {
    IIAmendment:
        for(int count = 0; count <= pi-1; count++)
        {
            cout << cardFaceValue(pIndex[count]);
            if(count != pi-1)
                cout << " -> ";
        }
        cout << endl;
        cout << "\nEnter h/H to hit or s/S: ";
        cin >> choice;
        if(choice != "h" && choice != "s")
        {
            cout << "Invalid input.\n";
            goto IIAmendment;
        }
        else if(choice == "s")
            break;
        
    notSurr:
        if(choice == "d")
            cout << "\nModified bet is $" << (2*bet) << ".\n";
        pIndex[pi++] = rand()%13;
        cout << "\nCard = " << cardFaceValue(pIndex[pi-1]) << endl;
        playerScore += cards[pIndex[pi-1]];
        if(pIndex[pi-1] == 0)
        {
            pAce = true;
            playerScore += 10;
        }
        
        if(pAce)
        {
            if(playerScore > 21)
            {
                playerScore -= 10;
                pAce = false;
            }
        }
        if(pAce)
                cout << "Total Score = " << playerScore-10 << "/" << playerScore << endl;
        else
            cout << "Total Score = " << playerScore << endl;
        
        if(choice == "d")
            break;
        
        if(playerScore == 21)
            choice = 's';
        
        if(isBust(playerScore))
            return -bet;
    }
    dealerScore = dealerDraw(dealerScore, dAce, ifIns, ins);
    if(choice == "d")
        return checkWin(dealerScore, playerScore, 2*bet);
    return checkWin(dealerScore, playerScore, bet);
}

int main(int argc, const char * argv[])
{
    int buyin = 0;
rectifybuyin:
    cout << "Enter your buy-in amount($100 - $100,000): $";
    cin >> buyin;
    if(buyin < 100 || buyin > 100000)
    {
        cout << "Invalid buy-in amount. Try again...\n";
        goto rectifybuyin;
    }
    int bet = 1, purse = buyin;
    cout << "Enter your bet for the hands (Enter 0 to exit)\n";
    for(int i = 1; true; i++)
    {
        cout << "\nCurrent balance is $" << purse << ".\n";
        cout << "Enter your bet ($10 - $1,000): $";
        cin >> bet;
        if(bet == 0)
            break;
        if(bet > purse)
        {
            cout << "Bet amount cannot be greater than balance. Please try again...\n";
            continue;
        }
        if(bet >= 10 && bet <= 1000)
            purse += betHand(bet);
        else
        {
            cout << "Invalid bet input. Try again...\n";
            continue;
        }
        if(purse == 0)
        {
            cout << "Your bankroll is over. EESH\n";
            break;
        }
    }
    cout << "\nOriginal buy-in amount was $" << buyin << ".\n";
    cout << "Exit balance is $" << purse << ".\n";
    
    if((purse - buyin) > 0)
        cout << "You profited by $" << (purse - buyin) << "!!!\n";
    else if((purse - buyin) == 0)
        cout << "No profit no loss :)\n";
    else if((purse - buyin) < 0)
        cout << "Your loss is $" << (buyin - purse) << ".\n";
    return 0;
}

//insurance, split
