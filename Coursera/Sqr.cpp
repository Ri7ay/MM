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
#include <limits>
#include <utility>

using namespace std;

template <class First, class Second>
pair<First, Second> operator*(const pair<First, Second>& p_firsr, const pair<First, Second>& p_second);

template <class T>
T Sqr(const T& num);

template <class First, class Second>
ostream& operator<<(ostream& stream, const pair<First, Second>& p);

template <class Key, class Value>
map<Key, Value> operator*(const map<Key, Value>& m_first, const map<Key, Value>& m_second);

template <class Key, class Value>
ostream& operator<<(ostream& stream, const map<Key, Value>& m);

template <class T>
vector<T> operator*(const vector<T>& v_first, const vector<T>& v_second);

template <class T>
ostream& operator<<(ostream& stream, const vector<T>& v);

template <class T>
ostream& operator<<(ostream& stream, const set<T>& s);

template <class T>
set<T> operator*(const set<T>& s_first, const set<T>& s_second);

template <class First, class Second>
pair<First, Second> operator*(const pair<First, Second>& p_firsr, const pair<First, Second>& p_second) {
    First first = p_firsr.first * p_second.first;
    Second second = p_firsr.second * p_second.second;
    return make_pair(first, second);
}

template <class Key, class Value>
map<Key, Value> operator*(const map<Key, Value>& m_first, const map<Key, Value>& m_second) {
    map<Key, Value> tmp;
    for (const auto& c : m_first) {
        if (m_second.count(c.first) != 0) {
            tmp[c.first] = c.second * m_second.at(c.first);
        }
    }
    return tmp;
}

template <class T>
vector<T> operator*(const vector<T>& v_first, const vector<T>& v_second) {
    vector<T> tmp;
    for (int i = 0; i < min(v_first.size(), v_second.size()); i++) {
        tmp.push_back(v_first[i] * v_second[i]);
    }
    return tmp;
}

template <class T>
set<T> operator*(const set<T>& s_first, const set<T>& s_second) {
    set<T> tmp;
    for (const auto& c : s_first) {
        tmp.insert(c * c);
    }
    return tmp;
}

template <class T>
T Sqr(const T& num) {
    return num * num;
}

template <class First, class Second>
ostream& operator<<(ostream& stream, const pair<First, Second>& p) {
    stream << p.first << " " << p.second;
    return stream;
}

template <class Key, class Value>
ostream& operator<<(ostream& stream, const map<Key, Value>& m) {
    for (const auto& c: m) {
        cout  << c.first << " : " << c.second << endl;
    }
    return stream;
}

template <class T>
ostream& operator<<(ostream& stream, const vector<T>& v) {
    for (const auto& c : v) {
        cout << c << " ";
    }
    return stream;
}

template <class T>
ostream& operator<<(ostream& stream, const set<T>& s) {
    for (const auto&c : s) {
        cout << c << " ";
    }
    return stream;
}
int main() {
    pair<int, int> p{3, 5};
    map<int , int> m{{1, 2}, {3, 4}, {5, 6}};
    set<int> s{1, 2, 3, 3, 4, 5, 6};
    vector<int> v = {1, 2, 3 ,4, 5, 6};
    cout << Sqr(p) << endl;
    cout << Sqr(m);
    cout << Sqr(v) << endl;
    cout << Sqr(s) << endl;
    return 0;
}
