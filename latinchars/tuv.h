#ifndef TUV_H
#define TUV_H
#include <cstddef>
#include <cstdlib>

template <class T> class Vector {
    int n;
    T *a;
public:
    explicit Vector(size_t amount){
        a = (T*) malloc(amount*sizeof(T));
        n=amount;
    };
    ~Vector(){
        free(a);
    }
    // Доступ по индексу
    T& operator[](size_t index){
        if (a) return a[index];
    };
    // Размер```s
    size_t size(){
        return n;
    };
};

template <class T> class Itor {
public:
    // Указатель на первый элемент
    virtual T* first() = 0;
    // Указатель на следующий элемент
    virtual T* next() = 0;
};

template <class T> class Vector_itor: public Itor<T> {
Vector<T> *v;
size_t index;
public:
Vector_itor (Vector <T>& vv){
    v = &vv;
    index = 0;
};
    T* first(){
        index=0;
        return &(*v)[0];
    };
    T* next(){
        return &(*v)[index++];
    };
};
#endif // TUV_H
