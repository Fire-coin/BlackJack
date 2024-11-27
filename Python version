import time
import random

class Card:
    def __init__(self, value, symbol) -> None:
        self.value = value
        self.symbol = symbol
    
    def getSymbol(self):
        return self.symbol
    
    def getValue(self):
        return self.value


def shuffleDeck(arr):
    temp = []
    while arr != []:
        val = random.choice(arr)
        temp.append(val)
        arr.remove(val)
    return temp


def showCards(temp, dealerFirst):
    symbols = "A23456789XJQK"
    suits = "♥♦♣♠"
    arr = temp.copy()
    n = len(arr)
    suit = ""
    
    if (dealerFirst):
        n -=1
        arr.pop()
    
    print("####### " * n, end= "")
    
    print("#######") if dealerFirst else print()
    
    for i in arr:
        suit = suits[i.getSymbol() - 1]
        print("#" + suit + "    # ", end= "")
    
    print("#######") if dealerFirst else print()
    
    
    print("#     # " * n, end= "")
    print("#######") if dealerFirst else print()
    
    for i in arr:
        symbol = symbols[i.getValue() - 1]
        print("#  " + symbol + "  # ", end= "")
    
    print("#######") if dealerFirst else print()
    
    
    print("#     # " * n, end= "")
    print("#######") if dealerFirst else print()
        
    for i in arr:
        suit = suits[i.getSymbol() - 1]
        print("#    " + suit + "# ", end= "")
    
    print("#######") if dealerFirst else print()
    
    
    print("####### " * n, end= "")
    if (dealerFirst):
        print("#######")
    print()


def dealCard(arr, personCards):
    if (arr == []):
        return -1
    temp = arr[-1]
    personCards.append(temp)
    arr.pop()
    
    return 0


def countCards(arr):
    aces = 0
    s = 0
    for i in arr:
        if i.getValue() == 1:
            aces += 1
        else:
            if i.getValue() > 10:
                s += 10
            else:
                s += i.getValue()
    
    for i in range(aces):
        if (s < 11):
            s += 11
        else:
            s += 1

    return s


arr = []
balance = int(input("Enter balance: "))
decks = 4


for i in range(52 * decks):
    arr.append(Card(i % 13 + 1, (i // 13) % 4))

reserve = arr.copy()
arr = shuffleDeck(arr)

while (balance > 0):
    playerCards = []
    dealerCards = []
    playerCount = 0
    dealerCount = 0
    bet = int(input("Enter bet: "))
    while (bet > balance or bet < 0):
        print("Invalid bet")
        bet = int(input("Enter bet: "))
    
    balance -= bet
    
    firstDeal = True
    playerChoice = 0
    
    h = dealCard(arr, dealerCards)
    if (h == -1): arr = shuffleDeck(reserve)
    h = dealCard(arr, playerCards)
    if (h == -1): arr = shuffleDeck(reserve)
    h = dealCard(arr, dealerCards)
    if (h == -1): arr = shuffleDeck(reserve)
    h = dealCard(arr, playerCards)
    if (h == -1): arr = shuffleDeck(reserve)
    
    playerCount = countCards(playerCards)
    dealerCount = countCards(dealerCards)
    
    while (playerChoice != 2 and playerCount < 21 and playerChoice != 3 and dealerCount < 21):
        showCards(dealerCards, True)
        showCards(playerCards, False)
        
        if (firstDeal and balance >= bet):
            playerChoice = int(input("Hit: 1;  Stand: 2;  Double: 3 \n"))
        else:
            playerChoice = int(input("Hit: 1;  Stand: 2 \n"))
        
        if (playerChoice == 1):
            h = dealCard(arr, playerCards)
            if (h == -1): arr = shuffleDeck(reserve)
            playerCount = countCards(playerCards)
        elif playerChoice == 3 and (not firstDeal or balance < bet):
            print("Cannot put double")
            playerChoice = 1
        firstDeal = False
    
    if (playerChoice == 3):
        h = dealCard(arr, playerCards)
        if (h == -1): arr = shuffleDeck(reserve)
        playerCount = countCards(playerCards)
        balance -= bet
        bet *= 2
    showCards(dealerCards, False)
    showCards(playerCards, False)
    print("\n\n\n\n")
    while (dealerCount < 17 and playerCount <= 21):
        time.sleep(1)
        h = dealCard(arr, dealerCards)
        if (h == -1): arr = shuffleDeck(reserve)
        dealerCount = countCards(dealerCards)
        showCards(dealerCards, False)
        showCards(playerCards, False)
        print("\n\n\n\n")
    
    if (playerCount == 21):
        if dealerCount != 21:
            if len(playerCards) == 2:
                print("BlackJack")
                balance += bet * 2.5
            else:
                print("You won!")
                balance += bet * 2
    elif playerCount < 21:
        if (playerCount > dealerCount):
            print("You won!")
            balance += bet * 2
        elif playerCount == dealerCount:
            print("Push")
            balance += bet
        else:
            if (dealerCount > 21):
                print("Dealer busted, you won!")
                balance += bet * 2
            else:
                print("Dealer won!")
    else:
        print("You busted!")

    print("Dealer:", dealerCount, "Player:", playerCount)
    print("Balance:", balance)

print("You are broke now!")
