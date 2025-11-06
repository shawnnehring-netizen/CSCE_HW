#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include "Game.h"
using std::string, std::vector;

Game::Game(): players({}), suits({}), ranks({}), 
    deck({}), drawPile({}), discardPile({}) {}

void Game::loadDeckFromFile(string filename){
    // TODO: initialize suits, ranks, deck, and drawPile from the given file
    std::ifstream deck_in(filename);
    std::string line = "";
    int step = 0;
    if (!(deck_in.is_open())){
      throw std::runtime_error("cant open");
    }
    while(getline(deck_in,line)){
        if (step == 0){
            std::string suit = "";
            for(char c: line){
                if(c == ' '){
                    suits.push_back(suit);
                    suit = "";
                    continue;
                }
                suit+=c;
            }
            suits.push_back(suit);
            step = 1;
        }
        else if (step == 1){
            std::string rank = "";
            for(char c: line){
                if(c == ' '){
                    suits.push_back(rank);
                    rank = "";
                    continue;
                }
                rank+=c;
            }
            suits.push_back(rank);
            step = 2;
        }
        else{
            std::string word = "";
            std::string rank1 = "";
            std::string suit1 = "";
            bool suit_ch = false;
            bool rank_ch = false;
            int here = 0;
            for(char c: line){
                if(c == ' ' && here == 0){
                    rank1 = word;
                    word = "";
                    here += 1;
                    continue;
                }
                else if(c == ' ' && here == 0){
                    throw std::runtime_error("string too long");
                }
                word+=c;
            }
            suit1 = word;
            if (rank1.size() == 0 || suit1.size() == 0){
                throw std::runtime_error("string too small");
            }
            for(unsigned int i = 0; i < suits.size(); i++){
                if(suits[i] == suit1){
                    suit_ch = true;
                    break;
                }
            }
            for(unsigned int i = 0; i < ranks.size(); i++){
                if(ranks[i] == rank1){
                    rank_ch = true;
                    break;
                }
            }
            if (!(suit_ch && rank_ch)){
                throw std::runtime_error("not valid suit or rank");
            }
            try{
                Card *new_card = new Card(rank1,suit1);
                deck.push_back(new_card);
                drawPile.insert(drawPile.begin(),new_card);
            }
            catch(...){
                throw std::runtime_error("invalid card");
            }
        }

    }

}

void Game::addPlayer(bool isAI){
    Player *new_play = new Player(isAI);
    players.push_back(new_play);
    // TODO: add a new player to the game
}

void Game::drawCard(Player* p){
    if(drawPile.size() == 0){
        if(discardPile.size() == 1){
            throw std::runtime_error("nothing to draw");
        }
        else if(discardPile.size() >= 2){
            for (unsigned int i = 0; i < discardPile.size(); i++){
                drawPile.push_back(discardPile[i]);
            }
        }
    }
    Card* draw_card = drawPile.back();
    p->addToHand(draw_card);
    // TODO: Move the top card of the draw pile to Player p's hand
    // If the draw pile is empty, flip the discard pile to create a new one
}

Card* Game::deal(int numCards){
    Card *dis_card = drawPile.back();
    drawPile.erase(drawPile.end());
    discardPile.push_back(dis_card);
    for(int j = 0; j < numCards; j++){
        for(unsigned int i = 0; i < players.size(); i++){
            drawCard(players[i]);
        }
    }
    return dis_card;
    // TODO: Flip the top card of the draw pile to be the initial discard
    // then deal numCards many cards to each player
}

string Game::mostPlayedSuit(){
    int sum = 0;
    std::string most = "";
    int max = 0;
    for (unsigned int i = 0; i < suits.size();i++){
        sum = 0;
        for (unsigned int j = 0; j < deck.size(); j++){
            if (suits[i] == deck[j]->getSuit()){
                sum += deck[j]->getTimesPlayed();
            }
        }
        if (sum > max){
            max = sum;
            most = suits[i];
        }
        else if(sum == max){
            most = most + " " + suits[i];
        }
    }
    return most;
    // TODO: Return the suit which has been played the most times
    // if there is a tie, choose any of the tied suits
}

int Game::runGame(){
    //deck
    std::cout << "Choose a file to load the deck from:" << std::endl;
    std::string deck = "";
    std::cin >> deck;
    loadDeckFromFile(deck);
    //player count
    std::cout << "Enter number of players:" << std::endl;
    int play_count = 0;
    while(true){
        std::cin >> play_count;
        if(!(isdigit(play_count) && play_count > 0)){
            std::cout << "Please enter a positive number" << std::endl;
            continue;
        }
        break;
    }
    //player ai or not
    for(int i = 0; i < play_count; i++){
        while(true){
            char play_iden = ' ';
            std::cout << "Is player " << i << " an AI? (y/n)" << std::endl;
            std::cin >> play_iden;
            if (play_iden == 'y'){
                addPlayer(true);
                break;
            }
            if (play_iden == 'n'){
                addPlayer(false);
                break;
            }
            else{
                std::cout << "Please enter y or n" << std::endl;
                continue;
            }
        }
    }
    //number of cards dealt
    int num_cards = 0;
    std::cout << "How many cards should each player start with?" << std::endl;
    while(true){
        std::cin >> num_cards;
        if (!(isdigit(num_cards) && num_cards > 0)){
            std::cout << "Please enter a positive number" << std::endl;
            continue;
        }
        else{
            break;
        }
    }
    Card* dis_card = deal(num_cards);
    std::cout << "The initial discard is " << dis_card->getRank() << " " << dis_card->getSuit() << std::endl;

    // TODO: Run the game and return the number of the winning player
    return 0;
}

//Destructor--Deallocates all the dynamic memory we allocated
//You shouldn't touch this
Game::~Game(){
    for (unsigned int i = 0; i < deck.size(); i++){
        delete deck.at(i);
    }
    for (unsigned int i = 0; i < players.size(); i++) {
        delete players.at(i);
    }
}