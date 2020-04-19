#ifndef SINGLETON_H
#define SINGLETON_H
#include <string>
#include <map>
using namespace std;
class globalStorage{
public:
    static globalStorage* getInstance(){
        static globalStorage theSingleInstance;
        return &theSingleInstance;
    }
    void save(string key, string value){
        data[key] = value;
    }
    string get(string key){
        return data[key];
    }
    string toString(){
        string res = "{";
        for (auto& [key, value] : data){
            res += '"' + key + "\":\"" + value + '"';
        };
        res += "}";
        return res;
    }
private:
    globalStorage(){};
    globalStorage(const globalStorage& root) = delete;
    globalStorage& operator=(const globalStorage&) = delete;
    map<string, string> data;
};

#endif // SINGLETON_H
