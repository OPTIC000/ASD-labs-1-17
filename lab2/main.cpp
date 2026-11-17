#include <iostream>
#include <string>

using namespace std;

// класс Pair
template <typename T1, typename T2>
class Pair {
private:
    T1 first;
    T2 second;

public:
    // Конструктор
    Pair(const T1& f, const T2& s) : first(f), second(s) {}

    // getFirst
    const T1& getFirst() const {
        return first;
    }

    // getSecond
    const T2& getSecond() const {
        return second;
    }

    // setFirst
    void setFirst(const T1& f) {
        first = f;
    }

    // setSecond
    void setSecond(const T2& s) {
        second = s;
    }
};

int main() {
    // Проверка
    Pair<string, int> myPair("Возраст", 20);
    
    cout << "Первое значение: " << myPair.getFirst() << endl;
    cout << "Второе значение: " << myPair.getSecond() << endl;
    
    // Изменение значения
    myPair.setFirst("Координаты");
    myPair.setSecond(10);
    
    cout << "--- После изменения ---" << endl;
    cout << "Первое значение: " << myPair.getFirst() << endl;
    cout << "Второе значение: " << myPair.getSecond() << endl;

    return 0;
}
