#include <iostream>

using namespace std;

template <class T>
class List{
public:
    struct Link{
        Link* pre;
        Link* suc;
        T* data;
    };
    List(){
        first = nullptr;
    };
    void put(T* dat){
        // Not the first element;
        if (cur){
            Link* new_element = new Link();
            cur->suc = new_element;
            new_element->pre = cur;
            new_element->suc = nullptr;
            new_element->data = dat;
            cur = cur->suc;
        }
        //First element
        else{
            Link* new_element = new Link();
            new_element->pre = nullptr;
            new_element->suc = nullptr;
            first = new_element;
            cur = new_element;
            new_element->data = dat;
        }
    };
    T* get(){
        if (!cur) return nullptr;
        T* res = cur->data;
        Link* tmp = cur;
        if (cur!=first){
            cur = tmp->pre;
            tmp->pre->suc = nullptr;
            delete(tmp);
        }
        else{
            delete(cur);
            cur = first = nullptr;
        }
        return res;
    }
    Link* cur;
    private:
    Link* first;
};

template <class T>
class Itor {
public:
    // Указатель на первый элемент
    virtual T* first() = 0;
    // Указатель на следующий элемент
    virtual T* next() = 0;
};

template <class T>
class List_itor{
public:
    List_itor(List<T> *l){
        tmp = l;
    }
    T* next(){
       link = link->suc;
       if (link) return link->data;
       else return nullptr;
    };
    T* first(){
       for (link = tmp->cur; link->pre !=nullptr; link = link->pre);
       return link->data;
    };
private:
    List<int>::Link* link;
    List<T>* tmp;
};

int main()
{
    List<int> l;
    int a = 1, b = 2, c = 3;
#if 0
    l.put(&a); l.put(&b); l.put(&c);
    cout << *l.get() << *l.get() << *l.get() << endl;
#endif
    l.put(&a); l.put(&b); l.put(&c);
    auto it = List_itor<int>(&l);

    for (int* i = it.first(); i != nullptr; i = it.next()){
        cout << *i;
    }
    return 0;
}
