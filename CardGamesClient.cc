#include<iostream>
#include<vector>

//To-Do:
//Display Feld recherchieren das pro Spiel variiert werden kann
//verdeckt und offens status von Karten visuell regeln
//Spiel-Logik für Single Player implementieren
//Grafiken besorgen und einbinden
//Muktiplayerframework recherchieren und auf Heimserver aufstezten
//Muktiplayer-Logik implementieren 
//Turn system and server updates
//Main-Menu entwerfen und implementieren


template<typename GameType>
class Card;

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

    std::vector<Card<Schafkopf>> deck;
    void fillDeck(){
        for(int s=0; s<suits; s++){
            for(int r=0; r<ranks; r++){
                deck.push_back(Card<Schafkopf>(static_cast<Suit>(s), static_cast<Rank>(r)));
            }
        }
    }
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
