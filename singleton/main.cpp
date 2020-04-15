#include <iostream>
#include <map>
#include <cstring>
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
    globalStorage(){}
    globalStorage(const globalStorage& root) = delete;
    globalStorage& operator=(const globalStorage&) = delete;
    map<string, string> data;
};

int main()
{
    globalStorage* storage = globalStorage::getInstance();
    storage->save("Ключ", "Значение"); // Сохраняем данные
    storage->save("Другой ключ", "Другое значение");
    storage->save("Ключ", "Новое значение"); // Обновляем данные
    storage->get("Ключ"); // Возвращает "Новое значение"
    cout << globalStorage::getInstance()->toString();
    return 0;
}
