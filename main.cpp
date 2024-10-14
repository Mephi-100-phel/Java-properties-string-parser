#include "lib.h"

using namespace lib;

int main(void) {
  Student *student = nullptr;
  try {
    student = new Student;
  } catch (const std::bad_alloc &err) {
    std::cout << err.what() << std::endl;
    return 1;
  }
  char err = 0;
  do {
    try {
      err = getStructFromStr(*student);
    } catch (const std::runtime_error& err) {
      std::cout << err.what() << std::endl;
    } catch (const std::bad_alloc &err) {
      std::cout << err.what() << std::endl;
      delete student;
      return 1;
    }
    if (err == 0) {
      printStudent(*student);
    }
    student->name.clear();
  } while (err != EOF);
  delete student;
  return 0;
}
