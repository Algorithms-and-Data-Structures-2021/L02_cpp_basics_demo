#pragma once  // директива препроцессора
// используется для избежания повторного подключения заголовочного файла

#include <string>
#include <vector>
#include <iostream>

// Не советуется использовать пространства имен в заголовочных файлах!
// Заголовочные файлы могут быть использованы во многих файлах с исходным кодом,
// что потенциально может вызвать проблемы коллизии имен.
// using namespace std;  // <- ошибки нет, все функции и объекты из std будут доступны в текущем пространстве имен

// struct <название>
struct Student {
  // публичные поля структуры:
  int id;            // id = <мусор>
  int age;
  std::string name;  // name = ""
  double avg_score;
};

// объявление функций в заголовочном файле (прототипы функций)
// здесь можно добавить и определения функций - но так не принято

void update_score(Student &student, double new_score);

void update_score(Student *student, double new_score);

void print_details(Student const &student);

// структура University

struct University {
 public:  // публичный спецификатор доступа - поля и методы являются открытыми для использования

  // конструктор по-умолчанию - специальный тип метода, который выполняется при создании объекта структуры
  University() : University("", 0) /* делегирующий конструктор */ {

    pointer_ = new int{1};  // выделение памяти в куче (нужно будет высвободить память)

    // если берется указатель и не выделяется память через оператор new,
    // то высвобождать ничего не надо
    // pointer_ = &ranking_;

    std::cout << "University()" << std::endl;
  }

  // деструктор - специальный тип метода, который выполняется при удалении объекта структуры
  ~University() {
    std::cout << "~University()" << std::endl;

    delete pointer_;     // освобождение выделенной памяти перед уничтожением объекта
    pointer_ = nullptr;  // не забываем обнулить указатель!!!
  }

  // explicit конструктор - запрет неявного преобразования string в University
  explicit University(std::string const &name); // <- объявление конструктора, определение лежит в struct.cpp

  // implicit конструктор - запрета на неявное преобразование int в University нет
  /* explicit */ University(int ranking);  // <- определение может лежать и в заголовнчом файле, за пределами структуры

  // конструктор от 2 параметров
  University(std::string const &name, int ranking);

  // публичные методы

  // const методы - гарантируют, что поля структуры не изменятся
  int GetId() const;

  // возвращение копии поля
  std::string GetName() const;

  int GetRanking() const;

  // возвращение ссылки
  std::string &GetNameRef();

  // возвращение ссылки на константу
  std::string const &GetNameConstRef() const;

  // ключевое слово this - неявный указатель на объект структуры
  University &GetThisRef(/* University* this */);

  void SetRanking(int ranking);

  void SetName(std::string const &name);

  // статический метод структуры
  static int CurrentID();

 public: // публичные поля

  static int ID_;  // статическое поле - общее для всех объектов структуры
  // если не инициализировать ID_, то он будет хранить "мусор"

 private: // приватный спецификатор доступа - поля и методы являются закрытыми для использования вне структуры

  // правила наименования полей: добавление _ в конец названия (Google C++ Style Guide)
  int id_;
  std::string name_;
  int ranking_;

  int *pointer_{nullptr};  // инициализация nullptr

  // приватные методы (вызов которых возможен только внутри структуры)
  void private_function();
  void private_const_function() const;
};

// определения методов и инициализация статических полей University

University::University(int ranking) : University("", ranking) {
  std::cout << "University(ranking)" << std::endl;
}

int University::CurrentID() {
  // можем работать только со статическими полями
  return University::ID_;  // можно просто return ID_
}

// инициализация статического поля структуры
int University::ID_ = 0;