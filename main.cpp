#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <regex>
#include "FClub.h"

using namespace std;

// comparison of club data
bool compare_fclub (const FClub& first, const FClub& second) {
    if (first.getPoints() == second.getPoints()) {
        if (first.goalDifference() == second.goalDifference())
            return first.getWon() > second.getWon();
        return first.goalDifference() > second.goalDifference();
    }
    return first.getPoints() > second.getPoints();
}

// розбиває рядок і поміщає масив
const vector<string> explode(const string& s, const char& c)
{
    string buff{""};
    vector<string> v;

    for( auto n:s )
    {
        if( n != c ) buff += n;
        else if( n == c && buff != "" ) {
                v.push_back(buff);
                buff = "";
            }
    }
    if(buff != "") v.push_back(buff);

    return v;
}


int main() {

    const int BUFF_SIZE = 50;
    //В цей масив ми будем класти об'єкт класу FClub
    list<FClub> apl_list;
    //ітератор для доступу до членів масиву
    list<FClub>::iterator it;

    int count;
    string load_str;
    char *char_buff;

    regex e ("(\\d+):(\\d+)\\r?");      //регулярний вираз для верифікації результатів матчу
    match_results<string::const_iterator> sm; //smatch sm;

    // открыли файл для чтения
    ifstream src("premier_league.csv", ios_base::in | ios::binary);    {
        // якщо файл не відкрито
        if (!src.is_open()) {
            cout << "Warning! Файл не відкрито" << endl;
            return -1;
         }

        getline(src, load_str);
        count = stoi(load_str);
        char_buff = new char[BUFF_SIZE];       // виділяєм блок пам'яті

        for (int i = 0; i < count; i++) {

            src.getline(char_buff, BUFF_SIZE, DELIMITER);     //зчитуємо до першого символа - відсікаєм назву команди
            FClub fclub = FClub( string(char_buff) );         //зтворюємо екземпляр класу - поміщаєм назву команди

            getline(src, load_str);     //зчитуєм до кінця рядка результати матчів

            vector<string> v{ explode(load_str, DELIMITER) };  //розділяємі їх кожний окремо і отримуєм масив вектор
            for (auto match_data:v) {

                if (!regex_match(match_data, e)) {                          //перевіряємо   регулярним виразом на відповідність данних
                    cout << "Error match data!" << match_data << endl;
                    continue;
                }
                regex_match(match_data, sm, e, regex_constants::match_default); //регулярний вираз на отримання данних A, B
                int A = stoi(string(sm[1]));
                int B = stoi(string(sm[2]));

                fclub.addMatch(A, B);       //додаємо дані матчу: А - забиті B - пропущені мяч
            }

            apl_list.push_back(fclub);
        }
        cout << endl;
        delete[] char_buff;          // звільняємо блок память

       src.close();
    }

    cout << "Reade and add commands: "  << apl_list.size() << endl;

    if (apl_list.size() == 0 ) {
        cout << "No data for table!" << endl;
        return -1;
    }

    cout << "sorting table data and print table results ..."  << endl;

    apl_list.sort(compare_fclub);

    cout << "Position  Club  Played  Won  Drawn  Lost  GF:GA  Points"  << endl;

    int i = 1;
    for (it=apl_list.begin(); it!=apl_list.end(); ++it)
        cout << i++ << ' ' << *it << endl;
    cout << '\n';

    ofstream dest;
    dest.open ("results.csv", ios::out | ios::binary);
    dest << "Position" << DELIMITER << "Club" << DELIMITER << "Played" << DELIMITER << "Won" << DELIMITER
         << "Drawn" << DELIMITER << "Lost" << DELIMITER << "GF:GA"  << DELIMITER << "Points" << endl;

    cout << "Write table data to file results.csv ..."  << endl;
    i = 1;
    for (it=apl_list.begin(); it!=apl_list.end(); ++it)
        dest << i++ << DELIMITER << *it << endl;
    dest.close();

    system("pause");
}

