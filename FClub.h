//
// Created by OLE on 02.05.2018.
//

#ifndef APLTABLE_FCLUB_H
#define APLTABLE_FCLUB_H

#include <iostream>
#include <string>

using namespace std;
const char DELIMITER = ',';

class FClub {

public:
//Конструктор
    FClub(const string & fc_name ) {
        name = fc_name;
        played = 0;
        points = 0;
        goals_for = 0;
        goals_against = 0;
        won = drawn = lost = 0;
    }

//    string getName() const {
//        return name;
//    }
//
    void addMatch( int & A, int & B) {
        played++;
        goals_for += A;
        goals_against += B;

        if (A > B) {
            points += 3;
            won += 1;
        }
        else  if (A == B) {
            points += 1;
            drawn += 1;
        }
        else lost += 1;
    }

    int goalDifference() const {
        return goals_for - goals_against;
    }

    int getWon() const {
        return won;
    }

    int getPoints() const {
        return points;
    }

    friend ostream &operator<<(ostream&, const FClub&);

private:
    string name;
    int played, points;
    int goals_for, goals_against;
    int won, drawn, lost;


};

ostream &operator<<(ostream& os, const FClub& fc) {
    os << fc.name << DELIMITER << fc.played << DELIMITER << fc.won << DELIMITER << fc.drawn << DELIMITER << fc.lost
        << DELIMITER << fc.goals_for << ":" << fc.goals_against << DELIMITER << fc.points;
    return os;
}


#endif //APLTABLE_FCLUB_H
