#pragma once  // директива препроцессора
// используется для избежания повторного подключения заголовочного файла

#include <string>
#include <vector>
#include <iostream>

// Не советуется использовать пространства имен в заголовочных файлах!
// Заголовочные файлы могут быть использованы во многих
// файлах с исходным кодом, что потенциально может вызвать проблемы коллизии имен.
// using namespace std;

// struct <название>
struct Student {
  // поля структуры:
  int id{-1};             // id = -1
  int age{};              // age = 0
  std::string full_name;  // full_name = ""
  double avg_score;       // avg_score = "мусор"
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

  // конструктор по-умолчанию
  University() : ranking_{0} /* инициализация полей структуры */ {

    pointer_ = new int{1};  // выделение памяти в куче (нужно будет высвободить память)

    std::cout << "University()" << std::endl;
  }

  // explicit - запрет неявного преобразования string в University
  explicit University(std::string const &name) : name_{name}, ranking_{0} {
    std::cout << "explicit University(name)" << std::endl;
  }

  /* explicit */ University(int ranking) : ranking_{ranking} {
    std::cout << "University(ranking)" << std::endl;
  }

  University(std::string const &name, int ranking)
      : name_{name}, ranking_{ranking} {
    std::cout << "University(name, ranking)" << std::endl;
  }

  // методы

  // const методы - гарантируют, что поля структуры не изменятся
  std::string GetName() const {
    // name_ = "KFU";  // <- ошибка компиляции
    return name_;
  }

  // возвращаемое значение - это копия поля
  int GetRanking() const;  // <- объявление метода, определение лежит в файле struct.cpp

  // возвращение ссылки
  std::string &GetNameRef() /* const - нельзя, нет гарантии, что name_ не изменится */ {
    ranking_ = 0;  // можно изменять поля объекта, но не стоит, это плохой код
    return name_;  // по ссылке можно будет изменять поле name_ у объекта типа University
  }

  // ссылка на константу (константная ссылка)
  std::string const &GetNameConstRef() const /* const - уже есть гарантии неизменности name_ */ {
    // private_function();  // <- ошибка компиляции
    private_const_function();

    return name_;
  }

  // ключевое слово this - неявный указатель на объект структуры
  University &GetThisRef() {

    std::string name = this->name_;
    // эквивалентно: std::string name = name_;

    return *this;  // разыменуем и получаем адрес объекта в памяти
    // который можем вернуть как ссылку (можно и указатель вернуть)
  }

  // деструктор
  ~University() {

    delete pointer_;  // освобождение выделенной памяти перед уничтожением объекта

    pointer_ = nullptr;  // не забываем!!!

    std::cout << "~University()" << std::endl;
  }

 private: // приватный спецификатор доступа - поля и методы являются закрытыми для использования вне структуры

  // правила наименования полей: добавление _ в конец названия (Google C++ Style Guide)
  std::string name_;
  std::vector<Faculty> faculties_;
  int ranking_;

  int *pointer_{nullptr};

  // приватные методы, вызов которых возможен только внутри структуры
  void private_function() {}
  void private_const_function() const {}
};

