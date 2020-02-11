#include <iostream>
#include <vector>
#include <cmath>

#define NUM 100

using namespace std;

class Output{
public:
    void operator() (const double value) const{
        cout << static_cast<unsigned int>(value) << " ";
    }
};


int main()
{
    //Функтор вывода
    Output out;
    //Вектора
    vector<unsigned int> vals, new_vals(NUM,0);
    for (unsigned int i = 1; i<=NUM; i++)
        vals.push_back(i*i);
    //Вывести значение исходного вектора
    for_each(vals.begin(), vals.end(), out);
    //Вывести перенос строки
    cout << endl;
    //Заполнить new_vals корнями
    transform(vals.begin(), vals.end(), new_vals.begin(), [](unsigned int &n){return sqrt(n);});
    //Вывести значние нового вектора
    for_each(new_vals.begin(), new_vals.end(), out);
    return 0;
}


