#include<iostream>
#include<vector>
#include <algorithm>


template<typename GameType>
class Card;
template<typename GameType>
class Player;

class Poker {
public:
    enum class Suit { Hearts, Diamonds, Clubs, Spades };
    enum class Rank { Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };
    int suits = 4;
    int ranks = 13;

    std::vector<Card<Poker>> deck;
    void fillDeck(){
        for(int s=0; s<suits; s++){
            for(int r=0; r<ranks; r++){
                deck.push_back(Card<Poker>(static_cast<Suit>(s), static_cast<Rank>(r)));
            }
        }
    }
};
    
class Skat {
public:
    enum class Suit { Eichel, Grün, Rot, Schell};
    enum class Rank { Sieben, Acht, Neun, Zehn, Unter, Ober, König, Ass };
    int suits = 4;
    int ranks = 8;

    std::vector<Card<Skat>> deck;
    void fillDeck(){
        for(int s=0; s<suits; s++){
            for(int r=0; r<ranks; r++){
                deck.push_back(Card<Skat>(static_cast<Suit>(s), static_cast<Rank>(r)));
            }
        }
    }
};
class Rommee {
public:
    enum class Suit { Kreuz, Pik, Herz, Karo };
    enum class Rank { Zwei, Drei, Vier, Fünf, Sechs, Sieben, Acht, Neun, Zehn, Bube, Dame, König, Ass };
    int suits = 4;
    int ranks = 13;

    std::vector<Card<Rommee>> deck;
    void fillDeck(){
        for(int s=0; s<suits; s++){
            for(int r=0; r<ranks; r++){
                deck.push_back(Card<Rommee>(static_cast<Suit>(s), static_cast<Rank>(r)));
            }
        }
    }
};
class Schafkopf {
public:
    enum class Suit { Eichel, Blatt, Herz, Schell };
    enum class Rank { Sieben, Acht, Neun, Zehn, Unter, Ober, König, Ass };
    int suits = 4;
    int ranks = 8;

    void fillDeck(std::vector<Card<Schafkopf>*>& deckCopy){
        for(int s=0; s<suits; s++){
            for(int r=0; r<ranks; r++){
                deckCopy.push_back(new Card<Schafkopf>(static_cast<Suit>(s), static_cast<Rank>(r)));
            }
        }
    }


private:
    int maxPlayers = 4;
    int minPlayers = 4;
    std::vector<Player<Schafkopf>> playerList;
    bool runPlayerCheck(){
        if(minPlayers<=playerList.size() && playerList.size()<=maxPlayers) {return true;}else{return false;}
    }
    std::vector<int> scores;
    std::vector<Card<Schafkopf>*> deck;

    void distributeCards(){
        for(auto& p : playerList){
            p.emptyHand();
        }
        //shuffle deck
        std::random_shuffle(deck.begin(), deck.end());
        //deal cards to players
        dealCards(8); //4*8 = 32
    }
    void dealCards(int amntPerPlayer){
        for(int i=deck.size()-1; i>=deck.size()-(amntPerPlayer*playerList.size()); i--){
            playerList[i % playerList.size()].giveCard(deck[i]);
            //give card deck[i] to playerList[i % playerList.size()] and remove from deck
            deck.pop_back();
        }
    }

    public:
            
    void addPlayer(Player<Schafkopf> p){
        if(runPlayerCheck()){playerList.push_back(p);}
        else{throw std::runtime_error("Cannot add more players to the game.");}
    }

    void startGame(){
        //do pregame checks
        if(runPlayerCheck()){}
        else{throw std::runtime_error("Not enough players to start the game.");}
        //run meta checks, deck exists, points, etc
        
        //empty deck aka delte pointers
        CardVectorClear<Schafkopf>(deck);
        //refill deck
        fillDeck(deck);
        //start Round Loop until break by playerschoice
    }

    void roundLoop(){
        bool gameRunning = true;
        while(gameRunning){
            CardVectorClear<Schafkopf>(deck);
            fillDeck(deck);
            distributeCards();
            //ask player for bets in order
            //form teams based on bets
            //set winMargin by bet and set Sau

            //turn-by-turn play until all cards played
            //calculate scores
            //claculate winner team based on winMargin and Sau
            //update scores for outside use
            //disband teams

            //ask players if they want to play another round
            //if not, set gameRunning = false
            //else set order for next round

            
        }
    }
    //turn-by-turn Game
    //win condition
    //set/keep score
};


template<typename GameType>
class Card {
    public:
    using Suit = typename GameType::Suit;
    using Rank = typename GameType::Rank;

    Card(Suit s, Rank r): suit(s), rank(r) { isFaceUp = false; }

    Suit getSuit() const { return suit; }
    Rank getRank() const { return rank; }

    void flip() { isFaceUp = !isFaceUp; }

    void Display() const {
        // Implementation for displaying the card
        if(isFaceUp) {
            // Display the card face at pos
            //get Graphic typename GameType::Card_Face<Suit, Rank>
        } else {
            // Display the card back at pos
            //get Graphic typename GameType::Card_Back
        }
    }

    private:
    Suit suit;
    Rank rank;

    bool isFaceUp;

    //pos??
    //owner??
};
template<typename GameType>
void CardVectorClear(std::vector<Card<GameType>*> cards){
    for(auto card : cards){
        delete card;
    }
    cards.clear();
}

template<typename GameType>
class Player {
    public:
        Player(){set = false;}

        void assignData(){
            if(set) return;
            else{
                //ask for name
                //assign picture
                set = true;
            }
        }
        bool hasCard(Card<GameType>& card){
            bool hasCard = false;
            for(auto& c : hand){
                if(c.getSuit() == card.getSuit() && c.getRank() == card.getRank()) {hasCard = true; break;}
            }
            return hasCard;
        }
        void giveCard(Card<GameType>* card){
            hand.push_back(card);
            //card must be deleted from source deck after giving

        }
        void removeCard(Card<GameType>& card){
            for(auto it = hand.begin(); it != hand.end(); ++it){
                if(it->getSuit() == card.getSuit() && it->getRank() == card.getRank()){
                    hand.erase(it);
                    break;
                }
            }
        }
        void emptyHand(){
            CardVectorClear<GameType>(hand);
        }

    private:
        std::string name;
        //picture
        std::vector<Card<GameType>> hand;
        bool set;
};