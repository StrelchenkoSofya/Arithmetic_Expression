#pragma once
#include<iostream>

template<typename T>
class queue {
    T* arr;
    int size;
    int s, f;
public:
    queue(int size = 1) : size(size) {
        if (size < 0)throw - 1;
        arr = new T[size];
        s = 0;
        f = size - 1;
    }
    queue(const queue& q) {
        size = q.size;
        s = q.s;
        f = q.f;
        arr = new T[size];
        for (int i = s; i != next(f); i = next(i)) {
            arr[i] = q.arr[i];
        }
    }
    queue& operator=(const queue& t) {
        if (this == &t) return *this;
        size = t.size;
        s = t.s;
        f = t.f;
        arr = new T[size];
        for (size_t i = s; i != next(f); i = next(i)) {
            arr[i] = t.arr[i];
        }
        return *this;
    }
    bool operator==(const queue& t) const {
        if (s != t.s)return false;
        if (f != t.f)return false;
        if (size != t.size)return false;
        for (size_t i = s; i != next(f); i = next(i)) {
            if (arr[i] != t.arr[i])return false;
        }
        return true;
    }
    bool operator!=(const queue& t) const {
        return !(*this == t);
    }
    T* get_mem() { return arr; }
    int get_size() { return size; }
    int next(int i) const {
        return(i + 1) % size;
    }
    bool isEmpty() {
        return s == next(f);
    }
    bool isFull() {
        return s == next(next(f));
    }
    void push(T value) {
        if (isFull()) {
            throw - 1;
        }
        f = next(f);
        arr[f] = value;
    }
    T pop(){
        if (isEmpty()) {
            throw - 1;
        }
        T res = arr[s];
        s = next(s);
        return res;
    }
    ~queue() {
        delete[]arr;
    }
    void print() {
        size_t n = next(f);
        for (size_t i = s; i != n; i = next(i)) {
            std::cout << pop() << ' ';
        }
    }
};