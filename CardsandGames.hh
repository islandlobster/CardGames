#include<iostream>
#include<vector>
#include <algorithm>


template<typename GameType>
class Card;
template<typename GameType>
class Player;

class Poker {   //Regelauswahl zwischen POL und Texas Hold'Em einbauen
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
    enum class Suit { Eichel, Blatt, Herz, Schell, none};
    enum class Rank { Sieben, Acht, Neun, Zehn, Unter, Ober, König, Ass, none};
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

    int curPlayer;

    enum class SpielArt : int {
        Ramsch    = 0,
        Rufspiel  = 1,
        Heiraten  = 2,
        Solo      = 3,
        Wenz      = 4,
        Farbsolo  = 5,
        FarbWenz  = 6,
        Pass      = -1
    };

    using R = Schafkopf::Rank;
    using S = Schafkopf::Suit;
    std::vector<R> defaultCardOrder = {R::Sieben, R::Acht, R::Neun, R::König, R::Zehn, R::Ass};
    std::vector<R> wenzCardOrder = {R::Sieben, R::Acht, R::Neun, R::Ober, R::König, R::Zehn, R::Ass};

    std::vector<Card<Schafkopf>> defaultTrumpOrder = {
        Card<Schafkopf>(S::Schell, R::Unter), Card<Schafkopf>(S::Herz, R::Unter), Card<Schafkopf>(S::Blatt, R::Unter), Card<Schafkopf>(S::Eichel, R::Unter),
        Card<Schafkopf>(S::Schell, R::Ober), Card<Schafkopf>(S::Herz, R::Ober), Card<Schafkopf>(S::Blatt, R::Ober), Card<Schafkopf>(S::Eichel, R::Ober)
    };
    std::vector<Card<Schafkopf>> wenzTrumpOrder = {
        Card<Schafkopf>(S::Schell, R::Unter), Card<Schafkopf>(S::Herz, R::Unter), Card<Schafkopf>(S::Blatt, R::Unter), Card<Schafkopf>(S::Eichel, R::Unter)
    };
    int findInOrder(Card<Schafkopf>& card, std::vector<Card<Schafkopf>>& Order){
            for(int i=0; i<Order.size(); i++){
                if(card == Order[i]){return i;}
            }
            throw std::runtime_error("Card not found in order list.");
            return -1;
        }
        int findInOrder(Card<Schafkopf>& card, std::vector<Schafkopf::Rank>& Order){
            for(int i=0; i<Order.size(); i++){
                if(card.getRank() == Order[i]){return i;}
            }
            throw std::runtime_error("Card not found in order list.");
            return -1;
        }
        bool inVector(Card<Schafkopf>& card, std::vector<Card<Schafkopf>>& vec){
            bool ret = false;
            for(auto& c : vec){
                if(card == c){ret = true; break;}
            }
            return ret;
        }
        bool inVector(Card<Schafkopf>& card, std::vector<Schafkopf::Rank>& vec){
            bool ret = false;
            for(auto& r : vec){
                if(card.getRank() == r){ret = true; break;}
            }
            return ret;
        }

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
        cardVectorClear<Schafkopf>(deck);
        //refill deck
        fillDeck(deck);
        //start Round Loop until break by playerschoice
        curPlayer = 0;
        roundLoop();
    }

    bool checkHandsEmpty(){
        int countHandCards = 0;
        for(auto& p : playerList){
            countHandCards += p.cardsInHand();
        }
        return countHandCards <= 0;
    }

    Card<Schafkopf>* determineWinner(std::vector<Card<Schafkopf>>& cards, Schafkopf::Suit& trump, std::vector<Card<Schafkopf>>& trumpOrder, std::vector<Schafkopf::Rank>& cardOrder){
        Card<Schafkopf>* ret = nullptr;
        Schafkopf::Suit asked = cards[0].getSuit();
        std::vector<int> candidates;
        if(asked == trump){
            for(int i=0; i<cards.size(); i++){
                if(cards[i].getSuit() == trump|| inVector(cards[i], trumpOrder)){candidates.push_back(i);}
            }
            //pick heighest based on card order - sort candidates based on card order descending then pick first
            for(int i=0; i<cards.size(); i++){
                if(inVector(cards[candidates[i]], trumpOrder)){
                    if(inVector(cards[candidates[0]], trumpOrder)){
                        //compare positions in trumpOrder
                        if(findInOrder(cards[candidates[i]], trumpOrder) > findInOrder(cards[candidates[0]], trumpOrder)){std::swap(candidates[0], candidates[i]);}
                    }else{ 
                        std::swap(candidates[0], candidates[i]);
                    }
                }else{
                    if(inVector(cards[candidates[0]], trumpOrder)){
                        //do nothing
                    }else{
                        //compare positions in cardOrder
                        if(findInOrder(cards[candidates[i]], cardOrder) > findInOrder(cards[candidates[0]], cardOrder)){std::swap(candidates[0], candidates[i]);}
                    }
                }
            }
            ret = &cards[candidates[0]];
        }else{
            for(int i=0; i<cards.size(); i++){
                if(cards[i].getSuit() == trump|| inVector(cards[i], trumpOrder)){candidates.push_back(i);}
            }
            if(candidates.size()==0){
                for(int i=0; i<cards.size(); i++){
                    if(cards[i].getSuit() == asked){candidates.push_back(i);}
                }
            }
            //pick heigehst based on card order
            for(int i=0; i<cards.size(); i++){
                if(inVector(cards[candidates[i]], trumpOrder)){
                    if(inVector(cards[candidates[0]], trumpOrder)){
                        //compare positions in trumpOrder
                        if(findInOrder(cards[candidates[i]], trumpOrder) > findInOrder(cards[candidates[0]], trumpOrder)){std::swap(candidates[0], candidates[i]);}
                    }else{ 
                        std::swap(candidates[0], candidates[i]);
                    }
                }else{
                    if(inVector(cards[candidates[0]], trumpOrder)){
                        //do nothing
                    }else{
                        //compare positions in cardOrder
                        if(findInOrder(cards[candidates[i]], cardOrder) > findInOrder(cards[candidates[0]], cardOrder)){std::swap(candidates[0], candidates[i]);}
                    }
                }
            }
            ret = &cards[candidates[0]];
        }
        return ret;
    }

    void roundLoop(){
        bool gameRunning = true;
        while(gameRunning){
            cardVectorClear<Schafkopf>(deck);
            fillDeck(deck);
            distributeCards();
            //To-Do: check if this is parallel
            std::vector<SpielArt> bets = std::vector<SpielArt>(playerList.size());
            std::vector<bool> passed = std::vector<bool>(playerList.size(), false); //technically not neccessary but clearer
            int i = curPlayer;
            bool bettingRunning = true;
            while(bettingRunning){
                //show bets of previous players in public Canvas - aka bets[0..i-1]
                if(!passed[i]){
                    //SpielArt bet = dialog(playerList[i]); 
                    //only allow valid options based on bets[0..i-1] and
                    //if has Sau criterium

                    SpielArt bet = SpielArt::Pass; //placeholder
                    if(bet == SpielArt::Pass){
                        passed[i] = true;
                        bets[i] = SpielArt::Ramsch;
                    }
                    else{
                        if(bet > *std::max_element(bets.begin(), bets.end())){
                            if(bet == SpielArt::Heiraten){
                                //ask all other players if they would like to marry(parallel) dialog 
                                //dialog only allows if possibe else same as decline 
                                //if marriage possible and accepted, assign partners and set their bets to Heiraten then bettingRunning = false; and break;
                                //else set bet to Ramsch and continue
                            }
                            bets[i] = bet;
                        }
                        else{
                            throw std::runtime_error("Invalid bet: bet must be greater than previous bets.");
                        }
                    }
                    
                }
                i = (i + 1) % playerList.size();
                //check if only one non-passed player left -> bettingRunning = false
                if(std::count(passed.begin(), passed.end(), false) <= 1){bettingRunning = false;}
            }
            //player with max bet 
            std::vector<Player<Schafkopf>> activePlayers;
            SpielArt SpielArtRound = *std::max_element(bets.begin(), bets.end());
            std::vector<int> scoresThisRound = std::vector<int>(playerList.size(), 0);

            int i = curPlayer;
            for(auto& p : playerList){      //maybe simplify with library function
                if(bets[i] == SpielArtRound){
                    activePlayers.push_back(p);
                    break;
                }
                i++;
            }

            Schafkopf::Suit trumpClr;
            int winMargin;
            std::vector<Card<Schafkopf>> trumpOrder;
            std::vector<Schafkopf::Rank> cardOrder;
            //form teams based on bets
            switch (SpielArtRound){
            case SpielArt::Ramsch:
                //all players have been added in activePlayers and bet logic
                //set card order Ramsch (In Schafkopf the same as Standard)
                trumpClr = Schafkopf::Suit::Herz;
                cardOrder = defaultCardOrder;
                trumpOrder = defaultTrumpOrder;
                winMargin = 0;
                break;
            case SpielArt::Rufspiel:
                //run Sau dialog on activePlayers[0] to choose Sau possibly only at least one option

                //set card order Standard
                trumpClr = Schafkopf::Suit::Herz;
                cardOrder = defaultCardOrder;
                trumpOrder = defaultTrumpOrder;
                //set winMargin to 60
                winMargin = 60;
                break;
            case SpielArt::Heiraten:
                //handled during betting
                //set card order Standard
                trumpClr = Schafkopf::Suit::Herz;
                cardOrder = defaultCardOrder;
                trumpOrder = defaultTrumpOrder;
                //set winMargin to 60
                winMargin = 60;
                break;
            case SpielArt::Solo:
                //set card order Standard
                trumpClr = Schafkopf::Suit::Herz;
                cardOrder = defaultCardOrder;
                trumpOrder = defaultTrumpOrder;
                //set winMargin to 60
                winMargin = 60;
                break;
            case SpielArt::Wenz:
                //set card order Wenz
                trumpClr = Schafkopf::Suit::Herz;
                cardOrder = wenzCardOrder;
                trumpOrder = wenzTrumpOrder;
                //set winMargin to 60
                winMargin = 60;
                break;
            case SpielArt::Farbsolo:
                //run choose trump dialog on activePlayers[0]
                //set card order Standard + trump
                //set trumpClr via dialog - dummy so far
                trumpClr = Schafkopf::Suit::none;
                cardOrder = defaultCardOrder;
                trumpOrder = defaultTrumpOrder;
                //set winMargin to 60
                winMargin = 60;
                break;
            case SpielArt::FarbWenz:
                //run choose trump dialog on activePlayers[0]
                //set card order Wenz + trump
                //set trumpClr via dialog - dummy so far
                trumpClr = Schafkopf::Suit::none;
                cardOrder = wenzCardOrder;
                trumpOrder = wenzTrumpOrder;
                //set winMargin to 60
                winMargin = 60;
                break;
            }

            //placeholder for game logic + while cards in players hands
            int startStich = curPlayer;
            while(!checkHandsEmpty()){
                std::vector<Card<Schafkopf>> FLOP;
                //To-Do: system to keep track on who owns what card
                //To-Do: limit turns to 4
                int i = startStich;
                for(int n = 0; n < playerList.size(); n++, i = (i + 1) % playerList.size()){
                    //ask player to play card
                    //add played card to FLOP
                }
                //determine stich winner 
                Card<Schafkopf>* highestCard = determineWinner(FLOP, trumpClr, trumpOrder, cardOrder);
                if(highestCard == nullptr){throw std::runtime_error("highest Card is nullptr, something must have been wrong while assigning/determining card logic");}
                Player<Schafkopf>* stichWinner = highestCard->getOwner();

                int stichValue = 0; 
                for(auto& c : FLOP){
                    switch(c.getRank()){
                        case Schafkopf::Rank::Ass:
                            stichValue += 11; break;
                        case Schafkopf::Rank::Zehn:
                            stichValue += 10; break;
                        case Schafkopf::Rank::König:
                            stichValue += 4; break;
                        case Schafkopf::Rank::Ober:
                            stichValue += 3; break;
                        case Schafkopf::Rank::Unter:
                            stichValue += 2; break;
                        default:
                            break;
                    }
                }

                //set startStich to stich winner for next stich
                for(int i=0; i<playerList.size(); i++){
                    if(playerList[i]==*stichWinner){
                        startStich = i; break;
                        scoresThisRound[i] += stichValue; 
                    }
                }
                //To-Do: delete cards in FLOP since regenerated every round
                for(auto& c : FLOP){
                    c.setOwner(nullptr);
                    delete &c;
                }
                
            }

            //after round score calculation
            if(SpielArtRound == SpielArt::Ramsch){
                //substract from score of all players based on scoresThisRound
            }else{
                //add to score of activePlayers based on scoresThisRound and winMargin
            }

            //calculate scores based on active players and SpielArtRound
            //claculate winner team based on winMargin
            //update scores for outside use

            //disband teams - auto cause active players gets reset every round



            //ask players if they want to play another round
            //if not, set gameRunning = false
            //else set order for next round
            curPlayer = (curPlayer + 1) % playerList.size();
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

    Card(Suit s, Rank r): suit(s), rank(r) { isFaceUp = false; owner = nullptr;}

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

    Player<GameType>* getOwner(){return owner;}
    void setOwner(Player<GameType>* newOwner){this->owner = newOwner;}

    private:
    Suit suit;
    Rank rank;

    bool isFaceUp;

    //pos??
    Player<GameType>* owner;
};
template<typename GameType>
void cardVectorClear(std::vector<Card<GameType>*> cards){
    for(auto card : cards){
        card->setOwner(nullptr);
        delete card;
    }
    cards.clear();
}
template<typename GameType>
inline bool operator==(const Card<GameType>& a, const Card<GameType>& b) {
    return a.getRank() == b.getRank() && a.getSuit() == b.getSuit();
}

template<typename GameType>
class Player {
    public:
        Player(){set = false; assignData(); setID();}
        Player(const std::string& playerName): name(playerName) {set = true; setID();}

        void assignData(){
            if(set) return;
            else{
                //ask for name dialog
                //assign picture dialog
                set = true;
            }
        }
        void modifyData(){
            set = false;
            assignData();
        }
        bool hasCard(Card<GameType>& card){
            bool hasCard = false;
            for(auto& c : hand){
                if(c == card) {hasCard = true; break;}
            }
            return hasCard;
        }
        void giveCard(Card<GameType>* card){
            hand.push_back(card);
            card->setOwner(this); //To-Do: check pointer arithmentic here

        }
        void playCardTo(Card<GameType>& card, Card<GameType>* destination){
            for(auto it = hand.begin(); it != hand.end(); ++it){
                if(*it == card){
                    *destination = *it;
                    hand.erase(it);
                    break;
                }
            }
        }
        void removeCard(Card<GameType>& card){
            for(auto it = hand.begin(); it != hand.end(); ++it){
                if(*it == card){
                    card->owner = nullptr;
                    hand.erase(it);
                    break;
                }
            }
        }
        void emptyHand(){
            CardVectorClear<GameType>(hand);
        }
        int cardsInHand(){
            return hand.size();
        }

        int ID(){return PlayerID;}

    private:
        int PlayerID;
        std::string name;
        //picture
        std::vector<Card<GameType>> hand;
        bool set;

        void setID(){
            //interact with Database 
            //generate random ID 
            //check if available on database if not regenerate
            //assign ID
        }
};
template <typename GameType>
inline bool operator==(Player<GameType>& a, Player<GameType> b){
    return a.ID() == b.ID();
}