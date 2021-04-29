#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <sstream>
#include <math.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "Card.h"

using namespace cv;
using namespace std;

#define CARDS_ON_TABLE 12
std::vector<Card*> cards;
int enteredNumbers[3];

//this function prints all cards of the given vector in the commandline.
void printVector(std::vector<Card*> cards) {
    for (Card* c : cards) {
        std::cout << c->toString();
    }
    std::cout << " " << std::endl;
}

//this function prints all cards of the given array in the commandline.
void printArray(Card* cards[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << cards[i]->toString();
    }
}

/*
* This function returns true when:
* - Matchamount = 0 (no card matches)
* - Matchamount = 3 (all card match)
*/
bool getSetReturn(int matchAmount) {
    if (matchAmount == 0 || matchAmount == 3) {
        return true;
    }
    else {
        return false;
    }
}

/*
* This function checks the colors of the selected cards.
*/
bool checkColor(Card* set[3]) {
    int matchAmount = 0;
    if (set[0]->getColor() == set[1]->getColor()) {
        matchAmount++;
    }
    if (set[1]->getColor() == set[2]->getColor()) {
        matchAmount++;
    }
    if (set[0]->getColor() == set[2]->getColor()) {
        matchAmount++;
    }
    return getSetReturn(matchAmount);
}

/*
* This function checks the numbers of the selected cards.
*/
bool checkNumber(Card* set[3]) {
    int matchAmount = 0;
    if (set[0]->getNumber() == set[1]->getNumber()) {
        matchAmount++;
    }
    if (set[1]->getNumber() == set[2]->getNumber()) {
        matchAmount++;
    }
    if (set[0]->getNumber() == set[2]->getNumber()) {
        matchAmount++;
    }
    return getSetReturn(matchAmount);
}

/*
* This function checks the shapes of the selected cards.
*/
bool checkShape(Card* set[3]) {
    int matchAmount = 0;
    if (set[0]->getShape() == set[1]->getShape()) {
        matchAmount++;
    }
    if (set[1]->getShape() == set[2]->getShape()) {
        matchAmount++;
    }
    if (set[0]->getShape() == set[2]->getShape()) {
        matchAmount++;
    }
    return getSetReturn(matchAmount);
}

/*
* This function checks the shadings of the selected cards.
*/
bool checkShading(Card* set[3]) {
    int matchAmount = 0;
    if (set[0]->getShading() == set[1]->getShading()) {
        matchAmount++;
    }
    if (set[1]->getShading() == set[2]->getShading()) {
        matchAmount++;
    }
    if (set[0]->getShading() == set[2]->getShading()) {
        matchAmount++;
    }
    return getSetReturn(matchAmount);
}

/*
* This function checks if the selected cards form a correct set.
*/
bool checkSet(Card* set[3]) {
    if (checkNumber(set) && checkColor(set) && checkShading(set) && checkShape(set)) {
        std::cout << "It's a set!" << std::endl;
        printArray(set, 3);
        return true;
    }
    else {
        std::cout << "It isn't a set!" << std::endl;
        return false;
    }
}

/*
* This function returns the color (Scalar object) of an given card.
*/
Scalar getShapeColor(Card* card) {
    Scalar currentColor;
    switch (card->getColor())
    {
    case 0: //blue
        currentColor = Scalar(255, 0, 0);
        break;
    case 1: //green
        currentColor = Scalar(0, 255, 0);
        break;
    case 2: //red
        currentColor = Scalar(0, 0, 255);
        break;
    default:
        break;
    }
    return currentColor;
}

/*
* This function returns the shading of an given card.
*/
int getShapeShading(Card* card) {
    int shading;
    switch (card->getShading())
    {
    case 0: //filled
        shading = -1;
        break;
    case 1: //thin edge
        shading = 1;
        break;
    case 2: //fat edge
        shading = 5;
        break;
    default:
        break;
    }
    return shading;
}

/*
* This function converts a given int to a string and returns it.
*/
string convertIntToString(int index) {
    stringstream stream;
    stream << index;
    string s;
    stream >> s;
    return s;
}

/*
* This function draws the cards and handles the input of the user.
*/
bool drawCards(Card* cardsOnTable[]) {
    Mat table(610, 410, CV_8UC3, Scalar(0, 0, 0));
    for (int row = 0; row < 4; row++) {
        for (int column = 0; column < 3; column++) {
            int currentColumnLocation = (column * 200) + 10;
            int currentRowLocation = (row * 100) + 10;
            int currentIndex = column + (row * 3);

            rectangle(table, Point(currentRowLocation, currentColumnLocation), Point((row * 100) + 100, (column * 200) + 200), Scalar(255, 255, 255), FILLED); //draw the empty white cards.
            putText(table, convertIntToString(currentIndex), Point(currentRowLocation + 10, currentColumnLocation + 180), FONT_HERSHEY_DUPLEX, 0.5, Scalar(0, 0, 0)); //draw the card numbers
            std::vector < Point > points;
            for (int number = 0; number < cardsOnTable[currentIndex]->getNumber(); number++) {
                switch (cardsOnTable[currentIndex]->getShape()) {
                case 0: //rectangle
                    rectangle(table, Point(currentRowLocation + 10, currentColumnLocation + ((50 * number) + 10)), Point(currentRowLocation + 80, currentColumnLocation + ((50 * number) + 50)), getShapeColor(cardsOnTable[currentIndex]), getShapeShading(cardsOnTable[currentIndex]));
                    break;

                case 1: //oval
                    ellipse(table, Point(currentRowLocation + 45, currentColumnLocation + ((50 * number) + 30)), Point(35, 15), 0, 0, 360, getShapeColor(cardsOnTable[currentIndex]), getShapeShading(cardsOnTable[currentIndex]));
                    break;

                case 2: //triangle
                    points.push_back(Point(currentRowLocation + 10, currentColumnLocation + (50 * number) + 10));
                    points.push_back(Point(currentRowLocation + 80, currentColumnLocation + (50 * number) + 10));
                    points.push_back(Point(currentRowLocation + 45, currentColumnLocation + (50 * number) + 45));

                    if (cardsOnTable[currentIndex]->getShading() == 0) { //when filled
                        fillPoly(table, points, getShapeColor(cardsOnTable[currentIndex]));
                    }
                    else { //when not filled
                        polylines(table, points, true, getShapeColor(cardsOnTable[currentIndex]), getShapeShading(cardsOnTable[currentIndex]));
                    }

                    points.clear();
                    break;

                default:
                    break;
                }
            }
        }
    }
    imshow("Table", table); //draw everything

    Card* chosenSet[3];
    string enteredNumber = "";
    int totalNumber = 0;

    //handle userinput
    std::cout << "Enter 3 values!" << std::endl;
    for (int i = 0; i < 3; i++) {
        int c = (int)waitKey(0);
        while (c != 13) {
            totalNumber = (totalNumber * 10) + (c - 48);
            enteredNumber += convertIntToString(c - 48);
            std::cout << c - 48;
            c = (int)waitKey(0);
        }
        std::cout << std::endl;
        enteredNumbers[i] = totalNumber;
        totalNumber = 0;
    }

    for (int i = 0; i < 3; i++) {
        chosenSet[i] = cardsOnTable[enteredNumbers[i]];
    }

    //check if selected cards form a correct set
    if (checkSet(chosenSet) == true) {
        return true;
    }
    else {
        return false;
    }
}

/*
* This function created all cards. Every card occurs once.
*/
void createCards() {
    for (int number = 1; number <= 3; number++) {
        for (int shape = 0; shape < 3; shape++) {
            for (int shading = 0; shading < 3; shading++) {
                for (int color = 0; color < 3; color++) {
                    Card* card = new Card(number, shape, shading, color);
                    cards.push_back(card);
                }
            }
        }
    }
}


int main() {
    Card* cardsOnTable[CARDS_ON_TABLE];
    
    createCards();
    
    //print all cards created cards in the console
    std::cout << "Number of cards: " << cards.size() << std::endl;
    std::cout << "----- Sorted vector -----" << std::endl;
    printVector(cards);

    //shuffle all cards and print them in the console.
    std::shuffle(std::begin(cards), std::end(cards), std::default_random_engine());
    std::cout << "Number of cards: " << cards.size() << std::endl;
    std::cout << "----- Shuffled vector -----" << std::endl;
    printVector(cards);

    //take 12 cards from the stock and put them on the 'table'.
    for (int i = 0; i < CARDS_ON_TABLE; i++) {
        Card* card = cards.back();
        std::cout << "Card: " << i << " - " << card->toString();
        //table.push_back(card);
        Card* tmp = new Card(card->getNumber(), card->getShape(), card->getShading(), card->getColor());
        cardsOnTable[i] = tmp;
        delete card; card = nullptr;
        cards.pop_back();
    }

    //print the cards which are on the table
    std::cout << "----- Table -----" << std::endl;
    printArray(cardsOnTable, CARDS_ON_TABLE);

    //handle user input and refill the table when correct set is selected.
    while (cards.size() > 3) {
        std::cout << "Number of cards: " << cards.size() << std::endl;
        if (drawCards(cardsOnTable) == true) {
            for (int i = 0; i < 3; i++) {
                Card* card = cards.back();
                Card* tmp = new Card(card->getNumber(), card->getShape(), card->getShading(), card->getColor());
                cardsOnTable[enteredNumbers[i]] = tmp;
                delete card; card = nullptr;
                cards.pop_back();
            }
        }
    }
    
    return 0;
}