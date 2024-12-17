#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <chrono>
#include <thread>

enum symbols {heart, diamond, clover, spades};
class Card {
    private:
        short int value;
        symbols symbol;
        
    public:
        Card();
        Card(int val, symbols sym);

        short int getValue() const {return value;}
        symbols getSymbol() const {return symbol;}
};

Card::Card() {
    value = 0;
    symbol = symbols(0);
}

Card::Card(int val, symbols sym) {
    value = val;
    symbol = sym;
}

std::vector<Card> shuffleDeck(std::vector<Card>& arr);

std::vector<Card> removeByIndex(std::vector<Card>& arr, int index);

void showCards(const std::vector<Card>& arr, bool dealerFirst);

std::vector<Card> slice(std::vector<Card>::iterator start, int size);

int dealCard(std::vector<Card>& arr, std::vector<Card>& personCards);

int countCards(const std::vector<Card>&);

void wait(int x);


int main() {
    srand(time(NULL));
    std::vector<Card> arr;
    int balance;
    int decks = 4;
    std::cout << "Enter balance: ";
    std::cin >> balance;
    // Setting up unshuffled deck
    for (int i = 0; i < 52 * decks; i++) {
        arr.push_back(Card(i % 13 + 1, symbols((i / 13) % 4)));
    }

    int h;
    std::vector<Card> reserve = arr;
    arr = shuffleDeck(arr);
    while (balance > 0) {
        std::vector<Card> playerCards, dealerCards;
        int playerCount = 0, dealerCount = 0;
        int bet;
        std::cout << "Enter bet: ";
        std::cin >> bet;
        while (bet > balance || bet < 0) {
            std::cout << "Invalid bet\n";
            std::cout << "Enter bet: ";
            std::cin >> bet;
        }
        balance -= bet;

        bool firstDeal = true;
        int playerChoice = 0;

        h = dealCard(arr, dealerCards);
        if (h == -1) {arr = shuffleDeck(reserve);}
        h = dealCard(arr, playerCards);
        if (h == -1) {arr = shuffleDeck(reserve);}
        h = dealCard(arr, dealerCards);
        if (h == -1) {arr = shuffleDeck(reserve);}
        h = dealCard(arr, playerCards);
        if (h == -1) {arr = shuffleDeck(reserve);}
        playerCount = countCards(playerCards);
        dealerCount = countCards(dealerCards);

        while (playerChoice != 2 && playerCount < 21 && playerChoice != 3 && dealerCount < 21) {
            showCards(dealerCards, true);
            showCards(playerCards, false);

            if (firstDeal && balance >= bet) {
                std::cout << "Hit: 1; Stand: 2; Double: 3 \n";
            } else {
                std::cout << "Hit: 1; Stand: 2 \n";
            }
            std::cin >> playerChoice;

		if (playerChoice == 1) {
                h = dealCard(arr, playerCards);
                if (h == -1) {arr = shuffleDeck(reserve);}
                playerCount = countCards(playerCards);
            } else if (playerChoice == 3 && (!firstDeal || balance < bet)) {
                std::cout << "Cannot put double\n";
                playerChoice = 1;
            }
            firstDeal = false;

        }	
        if (playerChoice == 3) {
            h = dealCard(arr, playerCards);
            if (h == -1) {arr = shuffleDeck(reserve);}
            playerCount = countCards(playerCards);
            bet *= 2;
            balance -= bet;
        }
        showCards(dealerCards, false);
        showCards(playerCards, false);
        std::cout << "\n\n\n\n";
        while (dealerCount < 17 && playerCount <= 21) {
            wait(1000);
            h = dealCard(arr, dealerCards);
            if (h == -1) {arr = shuffleDeck(reserve);}
            dealerCount = countCards(dealerCards);
            showCards(dealerCards, false);
            showCards(playerCards, false);
            std::cout << "\n\n\n\n";
        }
        if (playerCount == 21) {
            if (dealerCount != 21) {
                if (playerCards.size() == 2) {
                    std::cout << "BlackJack!\n";
                    balance += bet * 2.5;
                } else {
                    std::cout << "You won!\n";
                    balance += bet * 2;
                }
            } else {
				std::cout << "Push\n";
				balance += bet;
			}
        } else if (playerCount < 21) {
            if (playerCount > dealerCount) {
                std::cout << "You won!\n";
                balance += bet * 2;
            } else if (playerCount == dealerCount) {
                std::cout << "Push\n";
                balance += bet;
            } else {
                if (dealerCount > 21) {
                    std::cout << "Dealer busted, you won!\n";
                    balance += bet * 2;
                } else {
                    std::cout << "Dealer won!\n";
                }
            }
        } else {
            std::cout << "You busted!\n";
        }

        std::cout << "Dealer: " << dealerCount << ", player: " << playerCount << "\n";
        std::cout << "Your balance: " << balance << "\n";
    }
    std::cout << "You are broke now!\n";

    return 0;
}


std::vector<Card> removeByIndex(std::vector<Card>& arr, int index) {
    std::vector<Card> temp;
    for (int i = 0; i < arr.size(); i++) {
        if (i != index) {
            temp.push_back(arr[i]);
        }
    }
    return temp;
}


std::vector<Card> shuffleDeck(std::vector<Card>& arr) {
    std::vector<Card> temp;
    int n = arr.size();
    while (n > 0) {
        int index = rand() % n;
        temp.push_back(arr[index]);
        arr = removeByIndex(arr, index);
        n--;
    }
    return temp;
}


void showCards(const std::vector<Card>& arr, bool dealerFirst) {
    int n = arr.size();
    int i = 0;
    std::string symbol;

    if (dealerFirst) {
        n--;
    }
    

    for (i = 0; i < n; i++) {
        std::cout << "####### ";
    }
    if (dealerFirst) {
        std::cout << "#######";
    }
    std::cout << "\n";

    for (i = 0; i < n; i++) {
        switch (arr[i].getSymbol()) {
        case spades: std::cout << "#♠    # ";
            break;
        
        case heart: std::cout << "#♥    # ";
            break;
        
        case diamond: std::cout << "#♦    # ";
            break;
        
        case clover: std::cout << "#♣    # ";
            break;
        
        default:
            std::cout << "Invalid symbol\n";
            break;
        }
    }
    if (dealerFirst) {
        std::cout << "#######";
    }
    std::cout << "\n";


    for (i = 0; i < n; i++) {
        std::cout << "#     # ";
    }
    if (dealerFirst) {
        std::cout << "#######";
    }
    std::cout << "\n";

    for (i = 0; i < n; i++) {
        switch (arr[i].getValue()) {
            case 1: symbol = "A";
                break;
            case 10: symbol = "X";
                break;
            case 11: symbol = "J";
                break;
            case 12: symbol = "Q";
                break;
            case 13: symbol = "K";
                break;
            
            default: symbol = std::to_string(arr[i].getValue());
                break;
                
        }
        std::cout << "#  " << symbol << "  # ";
    }
    if (dealerFirst) {
        std::cout << "#######";
    }
    std::cout << "\n";

    for (i = 0; i < n; i++) {
        std::cout << "#     # ";
    }
    if (dealerFirst) {
        std::cout << "#######";
    }
    std::cout << "\n";

    for (i = 0; i < n; i++) {
        switch (arr[i].getSymbol()) {
        case spades: std::cout << "#    ♠# ";
            break;
        
        case heart: std::cout << "#    ♥# ";
            break;
        
        case diamond: std::cout << "#    ♦# ";
            break;
        
        case clover: std::cout << "#    ♣# ";
            break;
        
        default:
            std::cout << "Invalid symbol\n";
            break;
        }
    }
    if (dealerFirst) {
        std::cout << "#######";
    }
    std::cout << "\n";

    for (i = 0; i < n; i++) {
        std::cout << "####### ";
    }
    if (dealerFirst) {
        std::cout << "#######";
    }
    std::cout << "\n";
}


std::vector<Card> slice(std::vector<Card>::iterator start, int size) {
    std::vector<Card> temp;
    for (auto it = start; it != start + size; it++) {
        temp.push_back(*it);
    }
    return temp;
}


int dealCard(std::vector<Card>& arr, std::vector<Card>& personCards) {
    if (arr.empty()) {
        return -1;
    }	
    Card temp;
    temp = arr[arr.size() - 1]; // Getting last element of array
    personCards.push_back(temp);
    int newVal = temp.getValue();
    arr.pop_back(); // Removing element from array

    return 0;
}


int countCards(const std::vector<Card>& arr) {
    int aces = 0;
    int sum = 0;
    for (int i = 0; i < arr.size(); i++) {	
        if (arr[i].getValue() == 1) {
            aces++;
        } else {
            if (arr[i].getValue() > 10) {
                sum += 10;
            } else {
                sum += arr[i].getValue();
            }
        }
    }

    for (int i = 0; i < aces; i++) {
        if (sum < 11) {
            sum += 11;
        } else {
            sum++;
        }
    }

    return sum;
}

void wait(int x) {
    std::this_thread::sleep_for(std::chrono::milliseconds(x));
}
