#include <iostream>
#include <algorithm>

using namespace std;

class Vector {
private:
    int* data;
    size_t sz;  // size количество элементов
    size_t cap; // capacity выделенная память

public:
    // Конструктор по умолчанию
    Vector() : data(nullptr), sz(0), cap(0) {}

    // Конструктор с размером
     Vector(size_t size) : data(new int[size]), sz(size), cap(size) {
        for (size_t i = 0; i < size; ++i) data[i] = 0;
    }

    // Деструктор
    ~Vector() {
        delete[] data;
    }

    // Конструктор копирования
    Vector(const Vector& other) : data(new int[other.sz]), sz(other.sz), cap(other.sz) {
        copy(other.data, other.data + other.sz, data);
    }

    // Конструктор перемещения
    Vector(Vector&& other) noexcept
        : data(other.data), sz(other.sz), cap(other.cap) {
        other.data = nullptr;
        other.sz = 0;
        other.cap = 0;
    }

    // Оператор копирующего присваивания
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector temp(other);
            swap(data, temp.data);
            swap(sz, temp.sz);
            swap(cap, temp.cap);
        }
        return *this;
    }

    // Оператор перемещающего присваивания
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data;

            data = other.data;
            sz = other.sz;
            cap = other.cap;

            other.data = nullptr;
            other.sz = 0;
            other.cap = 0;
        }
        return *this;
    }

    // reserve: выделяет память, но не меняет размер
    void reserve(size_t new_cap) {
        if (new_cap <= cap) return;

        int* new_data = new int[new_cap];
        copy(data, data + sz, new_data);

        delete[] data;
        data = new_data;
        cap = new_cap;
    }

    // shrink_to_fit: уменьшает вместимость до размера
    void shrink_to_fit() {
        if (sz == cap) return;

        if (sz == 0) {
            delete[] data;
            data = nullptr;
            cap = 0;
            return;
        }

        int* new_data = new int[sz];
        copy(data, data + sz, new_data);

        delete[] data;
        data = new_data;
        cap = sz;
    }

    void push_back(int value) {
        if (sz == cap) {
            reserve(cap == 0 ? 1 : cap * 2);
        }
        data[sz++] = value;
    }

    size_t size() const { return sz; }
    size_t capacity() const { return cap; }

    int& operator[](size_t index) { return data[index]; }
    const int& operator[](size_t index) const { return data[index]; }
};

int main() {
      Vector v; v.push_back(10); v.push_back(20); v.push_back(30);

    cout << "1. Конструктор копирования:   ";
    Vector a(v); for (size_t i = 0; i < a.size(); ++i) cout << a[i] << " ";
    cout << "| size=" << a.size() << " cap=" << a.capacity() << endl;

    cout << "2. Конструктор перемещения:   ";
    Vector b(move(a)); for (size_t i = 0; i < b.size(); ++i) cout << b[i] << " ";
    cout << "| size=" << b.size() << " cap=" << b.capacity() << endl;
    cout << "   (исходный объект после перемещения): size=" << a.size() << " cap=" << a.capacity() << endl;

    cout << "3. Оператор копирующего присваивания:   ";
    Vector c; c = b; for (size_t i = 0; i < c.size(); ++i) cout << c[i] << " ";
    cout << "| size=" << c.size() << " cap=" << c.capacity() << endl;

    cout << "4. Оператор перемещающего присваивания:   ";
    Vector d; d = move(c); for (size_t i = 0; i < d.size(); ++i) cout << d[i] << " ";
    cout << "| size=" << d.size() << " cap=" << d.capacity() << endl;
    cout << "   (исходный объект после перемещения): size=" << c.size() << " cap=" << c.capacity() << endl;

    cout << "5. Деструктор: отработал без ошибок (программа не упала)" << endl;
    return 0;
}