#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include <numeric>


using namespace std;


bool is_number(const std::string& s);
bool is_double(const std::string& s);
void read();
void write();
void smooth();


vector<double> values; // input vector
vector<double> smooth_values; // output vector
int n; // the number of vector elements

string file; // directory of the file with data                              (1-st argument)
string in_M; // variable of M (half of the window from element or radius)    (2-nd argument)


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

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool is_double(const std::string& s)
{
    try
    {
        std::stod(s);
    }
    catch(...) //
    {
        return false;
    }
    return true;
}

void read() {
    ifstream fin(file, ios::in);
    string str;
    if (fin.is_open()) {
        while ( ! fin.eof() )
        {
            getline (fin, str); 
            
            //data validation
            if (is_double(str)) {
                values.push_back(stod(str));
            }
        }
        n = values.size();
    }
    else cout << "Cannot open file for reading" << endl;
    fin.close();
}

void smooth() {
    int M = stoi(in_M);
    int window = 2*M + 1;
    double scalar = 1/(double)window;

    double sum_in_M_range;
    double smooth_value;

    //To compensate for the delay there are loop with dynamically resizing window in the 2-th and 3-th blocks
    for (int i = 0; i < n; i++) { 
        sum_in_M_range = 0;

        if (i - M >= 0 && i + M < n) {
            sum_in_M_range = accumulate(values.begin() + i - M, values.begin() + 1 + i + M, 0.0f);
            smooth_value = sum_in_M_range * scalar;
            smooth_values.push_back(smooth_value);
        }   
        else if (i - M < 0) {
            int window_for_ends = window - abs(i-M);
            double scalar2 = 1/double(window_for_ends);

            sum_in_M_range = accumulate(values.begin(), values.begin() + i + M + 1, 0.0f);
            smooth_value = sum_in_M_range * scalar2;
            smooth_values.push_back(smooth_value);
        }   
        else if (i + M >= n) {
            int window_for_ends = window - (i + M - n + 1);
            double scalar2 = 1/double(window_for_ends);

            sum_in_M_range = accumulate(values.begin() + i - M, values.end(), 0.0f);
            smooth_value = sum_in_M_range * scalar2;
            smooth_values.push_back(smooth_value);
        }
    }
}

void write() {
    ofstream file;
    file.open("output.txt", ios::out);
    if (file.is_open()) {
        for (int i = 0; i < n; i++)
        {
            file << to_string(smooth_values[i]);
            file << "\n";
        } 
    }
    else cout << "Cannot open file for writing" << endl;
    file.close();
}

