#include <iostream>
#include <string>
#include <vector>

#include <chrono>
#include <random>  // random_device, mt19937

using namespace std;

int main() {

  { // генерация случайных величин по определенному закону распределения

    random_device rand_device;  // источник псевдо-случайных данных (например, /dev/urandom в Linux)

    mt19937 engine(rand_device());  // инициализируем генератор случайным число

    cout << engine() << endl;  // генерирует 32-битные числа

    // а что если нам нужны числа от 0 до 10?

    uniform_int_distribution<> uniform_dist(0, 10);

    for (int counter = 0; counter < 20; counter++) {
      cout << uniform_dist(engine) << ' ';
    }

    cout << endl;

    normal_distribution<double> norm_dist(0, 1);

    for (int counter = 0; counter < 10; counter++) {
      cout << norm_dist(engine) << ' ';
    }

    cout << endl;
  }

  {  // работа с таймерами

    // using <псевдоним> = <название типа>
    // задаем сокращенные названия для типов
    using chrono_clock_t = std::chrono::high_resolution_clock;

    auto const start_time_point = chrono_clock_t::now();  // вызов статического метода now()

    vector<string> strings;
    strings.reserve(2000000);

    for (int index = 0; index < 2000000; index++) {
      strings.emplace_back("String #" + to_string(index));
    }

    auto const end_time_point = chrono_clock_t::now();

    // разница во времени
    auto const delta = end_time_point - start_time_point;

    // хотим вывести в секундах
    auto const seconds = chrono::duration_cast<chrono::seconds>(delta).count();
    cout << "Time elapsed(secs):" << seconds << endl;

    // или в миллисекундах
    auto const milliseconds = chrono::duration_cast<chrono::milliseconds>(delta).count();
    cout << "Time elapsed (ms): " << milliseconds << endl;
  }

  return 0;
}