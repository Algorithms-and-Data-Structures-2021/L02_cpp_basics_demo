#include <iostream>
#include <cstring>  // strcmp, strlen, strcp и пр.
#include <string>

using namespace std;

int main() {

  {  // C-style строки - массив симоволов с нуль-терминатором в конце

    char null_term = '\0';  // так выглядит нуль-терминатор
    // он обозначает конец строки

    char c_str[] = "123";  // размер массива = 4
    // Компилятор автоматически добавляет нуль-терминатор в конец,
    // т.е. c_str = "123\0"

    for (char const ch: c_str) {  // в т.ч. и нуль-терминатор
      cout << "char: " << ch << endl;
    }

    // изменение значения строки
    c_str[0] = '3';
    c_str[1] = '2';
    c_str[2] = '1';

    // c_str = "54321"; // <- ошибка компиляции

    cout << "c_str = " << c_str << endl;  // выведет все символы до нуль-терминатора

    // указатель на константную строку (массив символов)
    char const *str = "123";  // str = "123\0"

    // str[0] = 1;  // <- ошибка компиляции

    cout << "char const * = " << str << endl;

    // динамическое выделение памяти
    char *heap_str = new char[10]{};  // с инициализацией, heap_str = ['\0', '\0', ...]
    heap_str[0] = 'a';

    cout << "heap char * = " << heap_str << endl;

    delete[] heap_str;  // не забываем высвободить память

    // сравнение строк
    char const *s1 = "12345";
    char const *s2 = "12343";

    int const compare_res = strcmp(s1, s2);  // лексиграфическое сравнение строк в стиле Си
    // compare_res < 0  => s1 < s2
    // compare_res == 0 => s1 == s2

    // длина строки
    int const s1_len = strlen(s1);  // s1_len = 5 (без нуль-терминала)
  }

  {  // std::string - оболочка над C-style строками

    string cpp_str = "Cpp string";

    // изменение строки (оно само выделит столько памяти, сколько необходимо)
    cpp_str = "Cpp string rules the world!";

    cpp_str.insert(0, "Yeah! ");  // вставка строки

    cpp_str.erase(0, 6);  // удаление символов в диапозоне

    cpp_str.clear();  // удаление всех символов, cpp_str = ""

    string prefix = "<PREFIX>";
    cpp_str = prefix + "<POSTFIX>";  // конкатенация строк, cpp_str = "<PREFIX><POSTFIX>"

    // размер строки
    int cpp_str_size = cpp_str.size();  // cpp_str_size = 17

    // проверка на пустоту
    bool is_empty = cpp_str.empty();  // is_empty = false

    // доступ к элементам
    char ch0 = cpp_str[0];                  // без проверки на выход за пределы
    char ch0_checked = cpp_str.at(0);  // с проверкой

    string substr = cpp_str.substr(1, 6);  // substr = "PREFIX"

    // лексигарфическое сравнение строк (==, !=, >, < и пр.)
    string s1;  // s1 = ""
    string s2 = "S";

    bool s1_gt_s2 = s1 > s2;  // false

    // конвертация в Си строку
    char const *c_str = cpp_str.c_str();
  }

  {  // примеры

    int const num_students = 32;

    // функция to_string
    string const s1 = "Number of students: " + to_string(num_students);
  }

  return 0;
};