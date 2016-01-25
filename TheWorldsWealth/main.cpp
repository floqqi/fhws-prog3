#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "utils.h"
#include "Person.h"

using namespace std;

double sumOfNetWorth(const vector<Person> *people) {
    double sum = 0;

    for (unsigned long i = 0; i < people->size(); ++i) {
        sum += people->at(i).netWorth;
    }

    return sum;
}

double middleAge(const vector<Person> *people) {
    double age = 0;

    for (unsigned long i = 0; i < people->size(); ++i) {
        age += people->at(i).age;
    }

    return age / people->size();
}

double middleNetWorth(const vector<Person> *people) {
    double worth = 0;

    for (unsigned long i = 0; i < people->size(); ++i) {
        worth += people->at(i).netWorth;
    }

    return worth / people->size();
}

bool compareNetWorth(const Person &p1, const Person &p2) {
    return p1.netWorth > p2.netWorth;
}

typedef vector<pair<string, vector<Person>>> countryVector;

countryVector topCountries(const vector<Person> *people) {
    countryVector countries;

    for (unsigned long i = 0; i < people->size(); i++) {
        Person p = people->at(i);

        int matchIndex = -1;
        for (unsigned long j = 0; j < countries.size(); ++j) {
            auto entry = countries[j];

            if (entry.first == p.country) {
                matchIndex = static_cast<int>(j);
            }
        }

        if (matchIndex == -1) {
            // no match found -> generate one
            pair<string, vector<Person>> personPair;
            personPair.first = p.country;
            personPair.second.push_back(p);
            countries.push_back(personPair);
            continue;
        }

        // match found -> copy, modify and replace
        auto match = countries[matchIndex];
        match.second.push_back(p);
        countries[matchIndex] = match;
    }

    return countries;
};

bool compareSumOfNetWorth(const pair<string, vector<Person>> &p1, const pair<string, vector<Person>> &p2) {
    return sumOfNetWorth(&p1.second) > sumOfNetWorth(&p2.second);
}

int main() {
    vector<Person> people;

    ifstream input_stream("/Users/fkraus/Projects/prog3/TheWorldsWealth/WorldWealthList.txt");
    if (!input_stream) cerr << "Can't open input file!";

    string line, country;
    int lineNumber = 0;
    while (getline(input_stream, line)) {
        ++lineNumber;
        if (lineNumber == 1 || lineNumber == 2) {
            continue;
        }

        if (endsWith(line, "Top\r")) {
            country = line.substr(0, line.find("Top\r"));
            country = trim(country);
            continue;
        }


        Person p;
        p.country = country;

        int nAttr = 0;
        size_t pos;
        string delimiter = "\t", token;
        while ((pos = line.find(delimiter)) != string::npos) {
            token = line.substr(0, pos);
            token = trim(token);

            try {
                switch (nAttr) {
                    case 0:
                        p.rank = stoi(token);
                        break;
                    case 1:
                        p.name = token;
                        break;
                    case 2:
                        p.citizenship = token;
                        break;
                    case 3:
                        p.age = stoi(token);
                        break;
                    case 4:
                        p.netWorth = string_to_double(token);
                        break;
                    case 5:
                        p.sourceOfWealth = token;
                        break;
                    default:
                        break;
                }
            } catch (invalid_argument) { }

            line.erase(0, pos + delimiter.length());
            ++nAttr;
        }

        people.push_back(p);
    }

    cout << "Anzahl an Personen = " << people.size() << endl;
    cout << "Summe des Kapitals = $" << sumOfNetWorth(&people) << " Billion" << endl;
    cout << "Mittleres Alter = " << middleAge(&people) << endl;
    cout << "Mittlere Kapitalsumme = $" << middleNetWorth(&people) << " Billion" << endl << endl;

    cout << "Top 10 Personen…" << endl;
    sort(people.begin(), people.end(), compareNetWorth);
    for (unsigned long i = 0; i < 10; ++i) {
        cout << i + 1 << ". " << people.at(i).name << " ($" << people.at(i).netWorth << " Billion)" << endl;
    }
    cout << endl;

    cout << "Top Länder…" << endl;
    countryVector cv = topCountries(&people);
    sort(cv.begin(), cv.end(), compareSumOfNetWorth);
    for (unsigned long i = 0; i < cv.size(); ++i) {
        auto cp = cv.at(i);
        cout << i + 1 << ". " << cp.first << " (Summe = $" << sumOfNetWorth(&cp.second) <<
        " Billion; Personen = " << cp.second.size() << ")" << endl;
    }

    return 0;
}
