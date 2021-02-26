#include <iostream>  // cout

// подключаем свой заголовочный файл
// поиск заголовочного файла осуществляется в папках проекта (а не в системных директориях)
#include "structs.hpp"

// директива #pragma once (см. заголовочный файл) не позволит повторно подключить заголовочный файл
#include "structs.hpp"

using namespace std;

int main() {

  {
    Student student;  // { id = -1, age = 0, full_name = "", avg_score = "мусор" }

    // инициализация
    student = {0, 24, "Ramil Safin", 92.6};

    // доступ к полям (оператор .)
    const int ID = student.id;  // чтение
    student.avg_score -= 0.3;   // запись

    // копирование
    Student const student_copy = student;  // { id = 0, age = 24, full_name = "Ramil Safin", avg_score = 92.3 }

    // указатель и ссылка

    Student *ptr_to_student = &student;

    // оператор обращения к полям структуры через указатель (->)
    ptr_to_student->age = 32;  // эквивалентно (*ptr_to_student).avg_score = new_score;

    update_score(ptr_to_student, 86);

    print_details(student);

    Student &ref_to_student = student;

    update_score(ref_to_student, 90);

    print_details(ref_to_student);
  }

  {  // вложенные структуры

    Faculty faculty;

    faculty.name = "ITIS";

    faculty.students = {
        {0, 24, "Student 0", 90.2},
        {1, 23, "Student 1", 92.3},
        {2, 24, "Student 2", 85.9}
    };

    int const age = faculty.students[0].age;
  }

  {  // приватные публичные поля и методы структуры

    University uni;  // вызов конструктора по-умолчанию (создание объекта класса uni)

    // uni.name_ = "";  // <- ошибка компиляции (поле name_ приватное)

    // вызов методов объекта, неявный указатель this

    string name = uni.GetName();  // копия поля name_

    int const ranking = uni.GetRanking();

    string &name_ref = uni.GetNameRef();  // ссылка на поле name_
    name_ref = "";  // ОК

    string const &name_const_ref = uni.GetNameConstRef();  // ссылка на неизменяемое поле name_
    // name_const_ref = "";  // <- ошибка компиляции

    // uni.private_function();  // <- ошибка компиляции

    auto& this_ref = uni.GetThisRef();
    // компилятор записывает эту строку примерно так:
    // GetThisRef(&uni) - т.е. компилятор передает указатель на объект (Python: self, Java: this)
  }

  {  // конструкторы и деструкторы

    University u1;  // конструктор по-умолчанию (объект на стеке)

    u1.~University();  // ручной вызов деструктора (высвобождение памяти, выделенной в объекте)

    University u2("KFU");  // explicit конструктор по name
    // University u2_str = string("KFU");  // <- ошибка компиляции (неявное приведение типа string к University)

    University u3(1);  // не explicit конструктор по ranking
    University u3_int = 1;    // вызов конструктора с ranking (неявное преобразование типа int в University)

    University u4("KFU", 1);  // конструктор по name и ranking
  }

  {  // создание объектов структуры на куче, деструктор

    auto *u_ptr = new University("KFU", 1);

    string name = u_ptr->GetName();

    delete u_ptr;  // ручной вызов деструктора и освобождение памяти
  }

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
  std::cout << "Student: " << "ID = " << student.id << "\tName: " << student.full_name << endl;
}

// методы struct University из заголовочного файла

int University::GetRanking() const {
  return ranking_;
}
