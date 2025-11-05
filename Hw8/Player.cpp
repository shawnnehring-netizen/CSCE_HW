#include<iostream>
#include<sstream>
#include "Player.h"
using std::vector, std::string, std::size_t;

Player::Player(bool isAI) : isAI(isAI) {

}

void Player::addToHand(Card* c){
    hand.push_back(c);
}

size_t Player::getHandSize(){
    return hand.size();
}

std::string Player::getHandString(){
    std::string line = "";
    for (unsigned int i = 0; i< hand.size(); i++){
        std::string new_line = hand[i]->getRank() + " " + hand[i]->getSuit();
        if (i == 0){
            line += new_line;
        }
        else{
            line += (", " + new_line);
        }
    }
    return line;
}

Card* Player::playCard(vector<string> const& suits, string& currentRank, string& currentSuit){
    Card * played = nullptr;
    std::string rank = "";
    std::string suit = "";
    if (isAI){
        for (unsigned int i = 0; i<hand.size();i++){
            if ((*hand[i]).getRank() == "8"){
                    hand[i]->play();
                    played = hand[i];
                    currentRank = played->getRank();
                    currentSuit = played->getSuit();
                    hand.erase(hand.begin() + i);
                    return played;
            }
            if (hand[i]->getRank() == currentRank && hand[i]->getSuit() == currentSuit){
                hand[i]->play();
                played = hand[i];
                currentRank = played->getRank();
                currentSuit = played->getSuit();
                hand.erase(hand.begin() + i);
                return played;
            }
        }
        return nullptr;
    }
    else{
        std::cout<<"What would you like to play? (enter \"draw card\" to draw a card)";
        while(true){
            std::cin >> rank >> suit;
            if (rank == "" && suit == ""){
                return nullptr;
            }
            bool here = false;
            int index = 0;
            Card* try_card = &Card(rank, suit);
            for (unsigned int i = 0; i<hand.size();i++){
                if (hand[i]->getRank() == try_card->getRank() && hand[i]->getSuit() == try_card->getSuit()){
                    here = true;
                    index = i;
                }
            }
            if (!here){
                std::cout << "That's not a card you have. Try again.";
                continue;
            }
            if (!try_card->canBePlayed(currentRank,currentSuit)){
                std::cout << "You can't play that card. Try again.";
                continue;
            }
            if (try_card->getRank() == "8"){
                std::string new_suit = "";
                std::cout << "What suit would you like to declare?";
                while(true){
                    bool suit_yeah = false;
                    std::cin >> new_suit;
                    for (unsigned int i = 0; i<suits.size();i++){
                        if (new_suit == suits[i]){
                            suit_yeah = true;
                        }
                    }
                    if (!suit_yeah){
                        std::cout << "That's not a suit in this deck. Try again.";
                        continue;
                    }
                }
                try_card->play();
                currentRank = try_card->getRank();
                currentSuit = new_suit;
                hand.erase(hand.begin() + index);
                return try_card;
            }
            try_card->play();
            currentRank = try_card->getRank();
            currentSuit = try_card->getSuit();
            hand.erase(hand.begin() + index);
            return try_card;

        }


    }
    // TODO: Choose a card to play and return the chosen card. Update currentRank and currentSuit.
}