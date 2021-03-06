#include <iostream>  // cout
#include <array>

using namespace std;

// Строго типизированное перечесление - контекст для описания диапазона значений,
// которые представлены в виде именованных констант (aka перечислителей).

// enum class <название перечисления> : <базовый тип перечислителей>
enum class StudentType : int {
  // перечислители:
  LAZY = 0,
  ALWAYS_SLEEPY,      // 1
  ALWAYS_HUNGRY,      // 2
  SUPER_CLEVER_NERD,  // 3
  NONE                // 4

  // Каждому имени в перечислении присваивается целочисленное значение,
  // которое соответствует определенному месту в порядке значений в перечислении.
};

enum class ShowProgressBar : bool {
  NO = false,
  YES = true
};

void download_zip(bool show_progress_bar) {
  if (show_progress_bar) {
    cout << "[bool] Showing a progress bar ... " << endl;
  }
}

void download_zip(ShowProgressBar show_progress_bar) {
  if (show_progress_bar == ShowProgressBar::YES) {
    cout << "[enum class] Showing a progress bar ... " << endl;
  }
}

void download_zip(bool show_progress_bar, bool enable_verbose, bool enable_crc_checking) {
  // блок кода
}

int main() {

  {
    StudentType type;  // хранит "мусор" (требуется инициализация)

    // используется оператор разрешения области ::
    type = StudentType::ALWAYS_HUNGRY;  // ОК

    if (type == StudentType::ALWAYS_HUNGRY) {
      // блок кода
    }

    switch (type) {
      case StudentType::ALWAYS_HUNGRY:
        // блок кода
        break;
      default:
        /* блок кода */;
    }
  }

  {
    // явное приведение типов - оператор static_cast

    StudentType type = static_cast<StudentType>(0);  // type = StudentType::LAZY

    int type_index = static_cast<int>(type);                        // type_index = 0

    type_index = static_cast<int>(StudentType::SUPER_CLEVER_NERD);  // type_index = 3
  }

  {  // use-case: использование перечислений как замену bool флагов

    download_zip(true);  // true? что это значит? смотрим в документацию функции

    // а что если таких флагов гораздо больше?
    download_zip(true, false, true);  // мда...

    download_zip(ShowProgressBar::YES);  // аха, показываем прогресс

  }

  {  // еще примеры

    constexpr StudentType DEFAULT_STUDENT_TYPE = StudentType::NONE;

    const StudentType sleepy_type = StudentType::ALWAYS_SLEEPY;

    array<StudentType, 3> types_arr = {
        StudentType::LAZY,
        StudentType::ALWAYS_SLEEPY,
        StudentType::ALWAYS_HUNGRY
    };
  }

  return 0;
}