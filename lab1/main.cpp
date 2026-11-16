#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Класс "Часть"
class Book {
private:
    string title;
    string author;
    int year;
    
    // Статическое поле для подсчёта количества объектов
    static int count; 

public:
    // Конструктор
    Book(string t, string a, int y) : title(t), author(a), year(y) {
        count++;
        cout << "Книга \"" << title << "\" создана. Всего книг: " << count << endl;
    }

    // Деструктор
    ~Book() {
        count--;
        cout << "Книга \"" << title << "\" уничтожена. Осталось книг: " << count << endl;
    }

    // Статический метод для получения количества
    static int getCount() {
        return count;
    }
    
};

// Инициализация статического поля
int Book::count = 0;


// Класс "Целое"
class Library {
private:
    //Указатели на книги
    vector<Book*> books; 

public:
    Library() {
        cout << "Библиотека создана." << endl;
    }

    // Метод для добавления книги
    void addBook(Book* b) {
        books.push_back(b);
    }

    // Деструктор
    ~Library() {
        // Книги существуют отдельно от библиотеки и не удаляются
        books.clear();
        cout << "Библиотека уничтожена. Книги остались." << endl;
    }
};

int main() {
    cout << "--- Создаем книги ---" << endl;
    // Создаем книги
    Book* book1 = new Book("Война и мир", "Л. Толстой", 1869);
    Book* book2 = new Book("Преступление и наказание", "Ф. Достоевский", 1866);

    cout << "\n--- Создаем библиотеку и вносим книги ---" << endl;
    {
        Library* myLib = new Library();
        myLib->addBook(book1);
        myLib->addBook(book2);

        cout << "\n--- Уничтожаем библиотеку ---" << endl;
        delete myLib; // Вызывается деструктор Library
    }

    cout << "\n--- Библиотека уничтожена, книги - нет ---" << endl;
    cout << "Сейчас внесено книг: " << Book::getCount() << endl;
    cout << "Книги существуют, не были удалены вместе с библиотекой." << endl;

    // Удаление созданных книг
    cout << "\n--- Удаление книг ---" << endl;
    delete book1;
    delete book2;

    return 0;
}