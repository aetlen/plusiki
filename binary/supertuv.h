#ifndef SUPERTUV_H
#define SUPERTUV_H
//AND, OR, XOR, NOT
template <class T>
class AND{
public:
    T operator()(T a, T b){
        return a & b;
    }
};

template <class T>
class OR{
public:
    T operator()(T a, T b){
        return a | b;
    }
};

template <class T>
class XOR{
public:
    T operator()(T a, T b){
        return a ^ b;
    }
};

template <class T>
class NOT{
public:
    T operator()(T a){
        return ~a;
    }
};

#endif // SUPERTUV_H
