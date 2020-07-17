#include <iostream>
#include <fstream> 
#include <cstring> 
#include <string>
#include <sstream>
#include <vector>

using namespace std;


bool is_number(const std::string& s);

void read();

void write();

void smooth();

vector<string> values;
vector<double> smooth_values;
string file;
string in_M;

int main(int arg_count, char *args[]) {
    if (arg_count == 3) {
        file = (string)args[1];
        in_M = (string)args[2];
        if (is_number(in_M)) {
            read();
            //smooth();
            //write();


        }
        else cout << "last argument must be natural number";
    }
    else if (arg_count == 2)
    {
        cout << "no argument of the number of window.. exiting the programm";
    }
    else {
        cout << "... no arguments.. exiting the programm";
    }

    return 0;
}

bool is_number(const std::string& s) //some code from stackoverflow
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void read() {
    ifstream fin(file, ios::in);
    string str;

    while ( ! fin.eof() )
    {
    getline (fin, str);
    values.push_back(str);
    } 
}

void smooth() {

}

void write() {

}

