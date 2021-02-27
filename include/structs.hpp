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
  // поля структуры:
  int id;            // id = <мусор>
  int age;
  std::string name;  // name = ""
  double avg_score;
};

// вложенность стуктур
struct Faculty {
  std::string name;               // name = ""
  std::vector<Student> students;  // students = []
};

// объявление функций в заголовочном файле (прототипы функций)

void update_score(Student &student, double new_score);

void update_score(Student *student, double new_score);

void print_details(Student const &student);

struct University {
 public:  // публичный спецификатор доступа - поля и методы являются открытыми для использования

  // конструктор по-умолчанию - специальный тип метода, который выполняется при создании объекта структуры
  University() : ranking_{0} /* список инициализации полей */ {
    std::cout << "University()" << std::endl;
    pointer_ = new int{1};  // выделение памяти в куче (нужно будет высвободить память)
  }

  // деструктор - специальный тип метода, который выполняется при удалении объекта структуры
  ~University() {
    std::cout << "~University()" << std::endl;

    delete pointer_;     // освобождение выделенной памяти перед уничтожением объекта
    pointer_ = nullptr;  // не забываем обнулить указатель!!!
  }

  // explicit конструктор - запрет неявного преобразования string в University
  explicit University(std::string const &name);

  // implicit конструктор, запрета на неявное преобразование int в University нет
  /* explicit */ University(int ranking);

  // конструктор от 2 параметров
  University(std::string const &name, int ranking);

  // публичные методы

  // const методы - гарантируют, что поля структуры не изменятся
  int GetId() const;

  std::string GetName() const;

  // возвращаемое значение - это копия поля
  int GetRanking() const;  // <- объявление метода, определение лежит в файле struct.cpp

  // возвращение ссылки
  std::string &GetNameRef();

  // ссылка на константу (константная ссылка)
  std::string const &GetNameConstRef() const;

  // ключевое слово this - неявный указатель на объект структуры
  University &GetThisRef(/* University* this */);

  // статический метод структуры
  static int CurrentID() {
    // можем работать только со статическими полями
    return University::ID_;  // можно просто return ID_
  }

 public: // публичные поля

  static int ID_;  // статическое поле - общее для всех объектов структуры
  // если не инициализировать ID_, то он будет хранить "мусор"

 private: // приватный спецификатор доступа - поля и методы являются закрытыми для использования вне структуры

  // правила наименования полей: добавление _ в конец названия (Google C++ Style Guide)
  int id_;
  std::string name_;
  std::vector<Faculty> faculties_;
  int ranking_;

  int *pointer_{nullptr};  // инициализация nullptr

  // приватные методы (вызов которых возможен только внутри структуры)
  void private_function() {}
  void private_const_function() const {}
};

// инициализация статического поля структуры
// осущетствляется за пределами структуры (либо в заголовочном файле, либо в cpp файле)
int University::ID_ = 0;
