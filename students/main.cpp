#include <iostream>
#include <vector>

#define STUDENTS 5
#define ANALYSE_DAYS 12
#define EXPELL 8
using namespace std;

int main()
{
    vector<bitset<STUDENTS>> attendance;
    //Each bit represents a student. Each array value represents a day.
    //attendance[0] is about a first day. attendance[0][0] is about a first student, etc.
    cout << "How many days are there?" << endl;
    int days;
    cin >> days;
    string input;
    cout << "Enter the data for each day encoded in " << STUDENTS << " zeros and ones" << endl;
    for (int i=0; i<days; i++){
        cout << "Enter the data for the day #" << i << ":" <<endl;
        cin >> input;
        attendance.push_back(std::bitset<STUDENTS>(input));
    }

    if (days < ANALYSE_DAYS){
        cout << "Not enouth days to analyse" << endl;
        return 1;
    }
    int start_day = days - ANALYSE_DAYS;
    // Count result for every student in twelve days
    vector<unsigned int> result(STUDENTS, 0);
    for (auto i = start_day; i<days; i++){
        for (auto n = 0; n < STUDENTS; n++)
            result[n] += attendance[i][n];
        }
    for (auto i = 0; i<STUDENTS; i++){
        if (result[i] == ANALYSE_DAYS) cout << "Student #" << STUDENTS - i << " has attended all the classes during last "
                                         << ANALYSE_DAYS<< " days." << endl;
        if (result[i] < EXPELL) cout << "Expell student #" << STUDENTS - i << " for low attendance." << endl;
    }
    return 0;
}
