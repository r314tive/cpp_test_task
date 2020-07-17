#include <iostream>
#include <fstream> 
#include <string>
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
            smooth();
            write();
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

//some code from stackoverflow
bool is_number(const std::string& s)
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
    //deleting first non-numeric string from Test.txt
    values.erase(values.begin(), values.begin()+1); 
}

void smooth() {
    int M = stoi(in_M);
    int window = 2*stoi(in_M) + 1;
    int n = (int)values.size();

    for (int i = 0; i < n; i++) {
        double sum_in_M_range = 0;

        for (int j = i-M; j < i+M; j++)
        {
            if (j >= 0 && j < n) {
                sum_in_M_range += stod(values[i]);
            }
        }
        smooth_values.push_back(sum_in_M_range/(double)window);
        
    }
    
}

void write() {
    ofstream file;
    file.open("output.txt", ios::out);
    for (int i = 0; i < (int)smooth_values.size(); i++)
    {
        file << to_string(smooth_values[i]);
        file << "\n";
    } 
    file.close();
}

