#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>
#include<set>
#include <exception>
using namespace std;

struct Date {
    Date() {
        year = 0;
        month = 0;
        day = 0;
        my_date = "0000-00-00";
    }
    Date(int new_year, int new_month, int new_day, string str) {
        if (new_month < 1 || new_month > 12) {
            throw invalid_argument("Month value is invalid: " + to_string(new_month));
        }
        if (new_day < 1 || new_day > 31) {
            throw domain_error("Day value is invalid: " + to_string(new_day));
        }
        year = new_year;
        month = new_month;
        day = new_day;
        my_date = str;
    }

    Date& operator=(const Date &date) {
        year = date.year;
        month = date.month;
        day = date.day;
        my_date = date.my_date;
        return *this;
    }

    int year, month, day;
    string my_date;
};

void get_date(string& str_date, Date& date) {
    istringstream stream(str_date);

    bool flag = true;
    int tmp_year = 0, tmp_month = 0, tmp_day = 0;
    string tmp_str, test_str, er;
    char str[2];

    flag = flag && (stream >> tmp_year);
    flag = flag && (stream.peek() == '-');
    stream.ignore(1);

    int month;
    flag = flag && (stream >> tmp_month);
    flag = flag && (stream.peek() == '-');
    stream.ignore(1);

    int day;
    flag = flag && (stream >> tmp_day);
    flag = flag && stream.eof();

    string str_year = to_string(tmp_year), str_month = to_string(tmp_month), str_day = to_string(tmp_day);
    while(str_year.size() < 4) {
        str_year = "0" + str_year;
    }
    while(str_month.size() < 2) {
        str_month = "0" + str_month;
    }
    while(str_day.size() < 2) {
        str_day = "0" + str_day;
    }
    tmp_str = str_year + "-" + str_month + "-" + str_day;

    if (!flag)
    {
        throw logic_error("Wrong date format: " + str_date);
    }
    date = {tmp_year, tmp_month, tmp_day, tmp_str};
}

ostream& operator<<(ostream& stream, Date& date) {
    stream  << setfill('0') << setw(4) << to_string(date.year);
    stream << "-";
    stream << setfill('0') << setw(2) << to_string(date.month);
    stream << "-";
    stream << setfill('0') << setw(2) << to_string(date.day);
    return stream;
}

/*
bool operator<(Date& date_left, Date& date_right) {
    if (date_left.year < date_right.year) {
        return true;
    } else if (date_left.year == date_right.year && date_left.month < date_right.month) {
        return true;
    } else return date_left.year == date_right.year && date_left.month == date_right.month && date_left.day < date_right.day;

}

bool operator==(Date& date_left, Date& date_right) {
    return date_left.year == date_right.year && date_left.month == date_right.month && date_left.day == date_right.day;
}
*/

void print_all(const map<string, set<string>>& date) {
    for (auto& c : date) {
        if (date.count(c.first) != 0) {
            int index = 0;
            for (auto &s : c.second) {
                if (index != 0) {
                    cout << endl;
                }
                cout << c.first << " " << s;
                index++;
            }
        }
        cout << endl;
    }
}

void print_set(const set<string>& date) {
    int index = 0;
    for (const auto& c : date) {
        if (index != 0) {
            cout << endl;
        }
        cout << c;
        index++;
    }
    cout << endl;
}

int main() {
    map<string, set<string>> database;
    string event, str, command, test;
    set<string> many_events;
    Date date;
    while(getline(cin, command)) {
        stringstream in(command);
        in >> str;
        if (command == "") {
            continue;
        } else if (str == "Add") {
            int flag = 0;
            Date tmp;
            try {
                in >> test;
                get_date(test, date);
                tmp = date;
            }
            catch (invalid_argument& ex) {
                flag = 1;
                cout << ex.what();
            }
            catch (domain_error& ex) {
                flag = 1;
                cout << ex.what();
            }
            catch (logic_error& ex) {
                flag = 1;
                cout << ex.what();
            }
            if (flag != 1) {
                in >> event;
                date = tmp;
                database[date.my_date].insert(event);
            }

        } else if (str == "Del") {
            Date tmp;
            int flag =0;
            try {
                in >> test;
                get_date(test, date);
                tmp = date;
            }
            catch (invalid_argument& ex) {
                flag = 1;
                cout << ex.what();
            }
            catch (domain_error& ex) {
                flag = 1;
                cout << ex.what();
            }
            catch (logic_error& ex) {
                flag = 1;
                cout << ex.what();
            }
            if (flag == 0) {
                date = tmp;
                if (!in.eof()) {
                    in >> event;
                    if (database[date.my_date].count(event) != 0) {
                        database[date.my_date].erase(event);
                        cout << "Deleted successfully" << endl;
                    } else {
                        cout << "Event not found" << endl;
                    }
                } else {
                    cout << "Deleted " << database[date.my_date].size() << " events" << endl;
                    database.erase(date.my_date);
                }
            }
        } else if (str == "Find") {
            Date tmp;
            int flag = 0;
            try {
                in >> test;
                get_date(test, date);
                tmp = date;
            }
            catch (invalid_argument &ex) {
                flag = 1;
                cout << ex.what();
            }
            catch (domain_error &ex) {
                flag = 1;
                cout << ex.what();
            }
            catch (logic_error& ex) {
                flag = 1;
                cout << ex.what();
            }
            if (flag == 0) {
                date = tmp;
                print_set(database[date.my_date]);
            }
        } else if (str == "Print") {
            print_all(database);
        } else {
            cout << "Unknown command: " + str << endl;
        }

    }
    return 0;
}