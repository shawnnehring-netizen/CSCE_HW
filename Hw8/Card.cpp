#include<cctype>
#include<stdexcept>
#include "Card.h"
using std::string;

Card::Card(string rank, string suit) : rank{rank}, suit{suit}, timesPlayed{0} {
    for (char c: rank){
        if (!isalnum(c)){
            throw std::invalid_argument("rank");
        }
    }
    for (char c: suit){
        if (!isalnum(c)){
            throw std::invalid_argument("suit");
        }
    }
}

string Card::getRank(){
    return rank;
}

string Card::getSuit(){
    return suit;
}

int Card::getTimesPlayed(){
    return timesPlayed;
}

bool Card::canBePlayed(string currentRank, string currentSuit){
    if ((currentRank == rank && currentSuit == suit) || rank == "8"){
        return true;
    }
    else{
        return false;
    }
    //  played had rank currentRank and suit currentSuit
}

//You don't need to modify this
void Card::play(){
    timesPlayed++;
}