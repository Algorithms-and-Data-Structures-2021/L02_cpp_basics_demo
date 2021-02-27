#include <iostream>  // cout

// подключаем свой заголовочный файл
// поиск заголовочного файла осуществляется в папках проекта (а не в системных директориях)
#include "structs.hpp"

// директива #pragma once (см. заголовочный файл) не позволит повторно подключить заголовочный файл
#include "structs.hpp"

using namespace std;

int main() {

  {
    Student student;  // { id = <мусор>, age = <мусор>, name = "", avg_score = <мусор> }

    // инициализация структуры (aggregate initialization)
    student = {0, 24, "Ramil Safin", 92.6};

    // доступ к полям (оператор .)
    const double avg_score = student.avg_score;  // чтение
    student.avg_score = avg_score - 0.3;         // запись

    // копирование
    Student const student_copy = student;  // { id = 0, age = 24, name = "Ramil Safin", avg_score = 92.3 }

    // student_copy.name = "";  // <- ошибка компиляции

    // указатель и ссылка

    Student *ptr_to_student = &student;

    // оператор обращения к полям структуры через указатель (->)
    ptr_to_student->age = 32;  // эквивалентно (*ptr_to_student).age = 32;
    update_score(ptr_to_student, 86);

    Student &ref_to_student = student;

    ref_to_student.age += 1;

    update_score(ref_to_student, 90);
    print_details(ref_to_student /* ссылка на const */);
  }

  {  // вложенные структуры

    Faculty faculty;

    // инициализация (aggregate initialization)
    faculty = {
        "ITIS",
        {
            {0, 24, "Student 0", 90.2},
            {1, 23, "Student 1", 92.3},
            {2, 25, "Student 2", 85.9}
        }
    };

    // доступ к вложенным полям структуры
    int const age = faculty.students[0].age;
  }

  {  // конструкторы и деструкторы

    { // вошли в новую область видимости

      University u1;            // конструктор по-умолчанию (объект создается на стеке)
      u1.~University();         // ручной вызов деструктора (объект НЕ удаляется со стека)

      // здесь мы ещё можем продолжать использовать u1

    }  // вышли из области видимости => автоматический вызов деструктора u1

    University u2("KFU");  // explicit конструктор по name

    // University u2_str = string("KFU");  // <- ошибка компиляции (неявное приведение типа string к University)
    University u2_str = static_cast<University>(string("KFU"));  // явное приведение типа

    University u3(1);  // НЕ explicit конструктор по ranking
    University u3_int = 1;    // ОК, вызов конструктора с ranking (неявное преобразование типа int в University)

    University u4("KFU", 1);  // конструктор по name и ranking
  }

  {  // приватные/публичные поля и методы структуры

    University uni;  // вызов конструктора по-умолчанию (создание объекта класса uni)

    // uni.name_ = "";  // <- ошибка компиляции (поле name_ приватное)

    // вызов публичных методов
    string name = uni.GetName();          // копия поля name_

    string &name_ref = uni.GetNameRef();  // ссылка на поле name_
    name_ref = "";                        // ОК, теперь uni.name_ = ""

    string const &name_const_ref = uni.GetNameConstRef();  // ссылка на неизменяемое поле name_
    // name_const_ref = "";                                // <- ошибка компиляции

    // вызов приватных функций - невозможен
    // uni.private_function();  // <- ошибка компиляции

  }

  {  // неявный указатель this

    University uni;

    auto &this_ref = uni.GetThisRef();
    // компилятор записывает строку кода выше примерно следующим образом:
    // GetThisRef(&uni) - т.е. компилятор передает указатель на объект неявным аргументом
    // Ex.: Python: self (явный), Java: this (неявный)
  }

  {  // статические методы и поля

    int ID = University::ID_;  // получение значения статического поля структуры (объект не обязательно создавать)

    int curr_id = University::CurrentID();  // вызов статического метода структуры

    // можно получить доступ к публичному статическому полю и через объект
    University u;
    curr_id = u.ID_;
  }

  {  // создание объектов структуры на куче, деструктор

    auto *u_ptr = new University("KFU", 1);

    string name = u_ptr->GetName();

    delete u_ptr;  // ручной вызов деструктора и освобождение памяти

  }  // при выходе из области видимости деструктор не вызовется (высвободится лишь память под указатель u_ptr)

  return 0;
}

// определение функций, объявленных в заголовочном файле structs.hpp
void update_score(Student &student, double new_score) {
  student.avg_score = new_score;
}

void update_score(Student *student, double new_score) {
  student->avg_score = new_score;
}

void print_details(const Student &student) {
  // student нужен только для чтения данных: id и пр.
  std::cout << "Student: " << "ID = " << student.id << "\tName: " << student.name << endl;
}

// определение методов University из заголовочного файла

// <название структуры>::<навзание метода>(<параметры>) : <список инициализации полей> { <тело метода> }
// :: - оператор разрешение области, используется для идентификации и устранения неоднозначности идентификаторов

University::University(const string &name) : University(name, 0) /* делигирующий конструктор */ {
  std::cout << "explicit University(name)" << std::endl;
}

University::University(int ranking) : University("", ranking) {
  std::cout << "University(ranking)" << std::endl;
}

University::University(const string &name, int ranking) : name_{name}, ranking_{ranking} {
  // генерация идентификатора на базе статического поля структуры
  id_ = ID_++;  // эквивалентно: id_ = ID_ и ID_ += 1
}

int University::GetId() const {
  return id_;
}

std::string University::GetName() const {
  // name_ = "KFU";  // <- ошибка компиляции
  return name_;
}

int University::GetRanking() const {
  return ranking_;
}

std::string &University::GetNameRef() /* const - нельзя, нет гарантии, что name_ не изменится */ {
  ranking_ = 0;  // можно изменять поля объекта, но не стоит, это плохой код
  return name_;  // по ссылке можно будет изменять поле name_ у объекта типа University
}

std::string const &University::GetNameConstRef() const /* const - уже есть гарантии неизменности name_ */ {
  // private_function();  // <- ошибка компиляции
  private_const_function();

  return name_;
}

University &University::GetThisRef() {

  std::string name = this->name_;
  // эквивалентно: std::string name = name_;

  return *this;  // разыменуем указатель и получаем адрес объекта в памяти
  // который можем вернуть как ссылку (можно и указатель вернуть)
}
