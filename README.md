# L02_cpp_basics_demo

![Build status](https://github.com/Algorithms-and-Data-Structures-2021/L02_cpp_basics_demo/actions/workflows/cmake.yml/badge.svg)

Демо код занятия №02 - Основы C++ (Часть 2)

Рассматриваемые темы:
- Константность времени выполнения и компиляции, ключевые слова `const` и `constexpr`.
- Классы перечисления `enum class`.
- Структуры, указатели на структуры, операторы обращения `.` и `->`.
- Спецификаторы доступа `public` и `private`.
- Конструкторы и методы структуры. Делигирующий конструктор. Список инициализации полей. Деструктор.
- Статические поля и методы структуры.
- Ключевое слово `this`.
- Заголовочные файлы. Объявление и определение методов структуры. Инициализация статических полей.
- Строки в стиле Си, класс `std::string`.
- Библиотеки `chrono` и `random`.
- Работа с потоками вводи и вывода. Стандартные потоки. Работа с файлами.

## Как запустить проект?

Самый простой способ запуска проекта - это использование онлайн IDE.

**Внимание!** Необходимо авторизоваться в Repl.it со своего GitHub аккаунта. 

[![Work in Repl.it](https://classroom.github.com/assets/work-in-replit-14baed9a392b3a25080506f3b7b6d57f295ec2978f6f33ec97e36a161684cbe9.svg)](https://repl.it/github/Algorithms-and-Data-Structures-2021/L02_cpp_basics_demo)

Если Вы хотите внести изменения в проект и сохранить их у себя в репозитории, то Вам необходимо выполнить `Fork` проекта.
Подробные инструкции можно прочесть по [ссылке](https://docs.github.com/en/github/getting-started-with-github/fork-a-repo).

1. Клонируете проект к себе на компьютер в терминале (консоли):
```shell
git clone https://github.com/Algorithms-and-Data-Structures-2021/L02_cpp_basics_demo.git
```
или через среду разработки, клиента Git (например, [Git for Windows](https://git-scm.com/download/win) или [GitHub Desktop](https://desktop.github.com/)).

2. Импортируете/открываете проект в среде разработки (как CMake проект, см. [здесь](https://www.jetbrains.com/help/clion/quick-cmake-tutorial.html)).

3. Запуск программы осуществляется в среде разработки.

Ручная сборка проекта в терминале:
```shell
mkdir -p build && cd build
cmake ..
cmake --build .
```
