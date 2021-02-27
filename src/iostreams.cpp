#include <string>  // getline
#include <sstream> // stringstream
#include <iostream>
#include <iomanip>  // setprecision
#include <fstream>  // ofstream, ifstream
#include <vector>

using namespace std;

// абсолютный путь до папки проекта
constexpr char PROJECT_SOURCE_DIR[] = PROJECT_DIR;

/*
 * stream (поток) - потенциально неограниченный поток данных (байт)
 * input stream - входной поток (чтение данных)
 * output stream - выходной поток (запись данных)
 */

int main() {

  {  // стандартные потоки ввода и вывода (cin и cout)

    // Стандартный поток — это предварительно подключенный поток,
    // который предоставляется программе её окружением (ОС).

    // cout - стандартный вывод, глобальный объект класса ostream
    // для вывода данных в поток используется оператор << (вставки)
    // оператор << умеет работать со множеством типов аргументов
    cout << "Output string, number " << 3 << " and many more!" << endl;

    // на самом операторы представляют из себя методы
    cout.operator<<(3);
    cout.operator<<(endl);

    // cerr - стандартный вывод ошибок (может быть выделен красным в терминале)
    cerr << "[ERROR] Invalid argument is passed!" << endl;

    // cin - стандартный поток ввода (по умолчанию это клавиатура)
    // для ввода данных в поток используется оператор >> (извлечения)

    // переменные, куда будем записывать данные, прочитанные из потока cin
    int id;
    string name;
    double score;

    cout << "Please, enter <id> <space> <name> <space> <score>:" << endl;

    // чтение данных, разделенных пробелом
    cin >> id >> name >> score;  // прочли 3 значения

    cout << "ID: " << id << ", name: " << name << ", score: " << score << endl;
  }

  {  // форматированный вывод

    double const d1 = 1.0123456789;

    cout << fixed;  // выводить в формате с фиксированной точностью после запятой

    cout << d1 << endl;  // 1.012346
    cout << setprecision(1) << d1 << endl;  // 1.0
    cout << setprecision(3) << d1 << endl;  // 1.012

  }

  {  // работа с файлами - вывод и ofstream

    string file_name = PROJECT_SOURCE_DIR + string{"/output.txt"};

    ofstream out_rewrite(file_name, ios_base::out);  // открытие потока на перезапись файла (ios_base::out)

    if (out_rewrite) {  // проверка, что поток успешно открылся для записи
      out_rewrite << "Once upon a time, there was a boy" << endl;
      out_rewrite << "Numbers: " << 1 << ',' << 2 << endl;

      out_rewrite << "Array: [";

      for (auto const e: {1, 2, 3}) {
        out_rewrite << e;
      }

      out_rewrite << "]" << endl;
    }

    out_rewrite.close();  // автоматически закроется при выходе из области видимости
    // так как вызовется деструктор потока

    ofstream out_append(file_name, ios_base::app);  // открытие потока на добавление (ios_base::app)

    out_append << "<APPENDED TAG>" << endl;
  }

  {  // работа с файлами - ввод и ifstream

    string file_name = PROJECT_SOURCE_DIR + string{"/input.txt"};

    ifstream in_stream(file_name);

    if (in_stream) { // поток успешно открылся на чтение

      vector<string> lines;
      lines.reserve(10);  // хорошая практика резеврировать навскидку размер массива

      // построчное чтение данных (функция string::getline)
      for (string line; getline(in_stream, line); /* ничего */) {  // читаем строку, пока есть, что читать
        cout << "Read: " << line << endl;
        lines.push_back(line);  // добавляем в массив для дальнейшей обработки
      }

      // обработка (парсинг)

      for (auto const &line: lines) {
        istringstream ss(line);  // оборачиваем строку в класс istringstream

        double d1{};
        double d2{};
        ss >> d1 >> d2;  // прочесть 2 значения

        cout << "Read: " << d1 << " and " << d2 << endl;
      }
    }
  }

  return 0;
}
