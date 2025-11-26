#include<iostream>
#include<vector>


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

    void fillDeck(std::vector<Card<Schafkopf>>& deckCopy){
        for(int s=0; s<suits; s++){
            for(int r=0; r<ranks; r++){
                deckCopy.push_back(Card<Schafkopf>(static_cast<Suit>(s), static_cast<Rank>(r)));
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
    std::vector<Card<Schafkopf>> deck;

    public:
            
    void addPlayer(Player<Schafkopf> p){
        if(runPlayerCheck()){playerList.push_back(p);}
        else{throw std::runtime_error("Cannot add more players to the game.");}
    }

    //add more game logic here
    //Game Logic blue-print:
    //initualize game
    void startGame(){
        //do pregame checks
        //
        deck.clear();
        fillDeck(deck);
    }
    //shuffle and distribute cards
    void distributeCards(){
        for(auto& p : playerList){
            p.emptyHand();
        }
        //deal cards to players
        for(int i=deck.size()-1; i>=0; i--){
            playerList[i % playerList.size()].giveCard(deck[i]);
            //give card deck[i] to playerList[i % playerList.size()] and remove from deck
            deck.pop_back();
        }
    }
    //pregame setup
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
        void giveCard(Card<GameType>& card){
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
            hand.clear();
        }

    private:
        std::string name;
        //picture
        std::vector<Card<GameType>> hand;
        bool set;
};