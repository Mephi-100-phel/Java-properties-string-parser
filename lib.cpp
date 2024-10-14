#include "lib.h"
#include <algorithm>
#include <limits>

namespace lib {

short getStructFromStr(Student& student) {
  std::cout << "Введите строковое представление экземпляра структуры" << std::endl;
  std::string input_str;
  std::getline(std::cin, input_str);
  if (std::cin.eof()) {
    return EOF;
  }
  if (input_str.empty()) {
    std::cout << "EMPTY_STR" << std::endl;
    return 1;
  }
  std::cout << "Введите способ обработки:\nstd::string - \"s\"\nchar* - \"c\"\nchar*+size_t - \"cs\"" << std::endl;
  std::string mode;
  std::cin >> mode;
  if (std::cin.eof()) {
    return EOF;
  }
  if (mode.empty()) {
    std::cout << "EMPTY_STR" << std::endl;
    return 1;
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  char *temp_str = nullptr;
  try {
    if (mode == "s") {
      __fillStudent(student, input_str);
    } else if (mode == "c") {
      __fillStudent(student, input_str.c_str());
    } else if (mode == "cs") {
      size_t str_len = input_str.length();
      temp_str = new char[str_len];
      std::copy_n(input_str.c_str(), str_len, temp_str);
      __fillStudent(student, temp_str, str_len);
      delete [] temp_str;
    } else {
      throw std::runtime_error("INVALID_MODE");
    }
  } catch (const std::runtime_error& err) {
    if (temp_str != nullptr) {
      delete [] temp_str;
    }
    std::cout << err.what() << "\nПовторите ввод\n" << std::endl;
    return 1;
  }
  return 0;
}

void __fillStudent(Student& student, const char *str) {
  if (str == nullptr || str[0] != '{' || str[strlen(str) - 1] != '}') {
    throw std::runtime_error("INVALID_INPUT");
  }
  size_t str_len = strlen(str);
  char *input_str = new char[str_len + 1];
  strcpy(input_str, str);
  char *field = nullptr;
  char *temp_str_ptr = strstr(input_str, "name=");
  if (!temp_str_ptr) {
    delete [] input_str;
    throw std::runtime_error("NAME_NOT_FOUND");
  } else if (temp_str_ptr[5] != '\"') {
    delete [] input_str;
    throw std::runtime_error("INVALID_NAME");
  } else {
    try {
      field = new char[str_len];
    } catch (const std::bad_alloc &err) {
      delete [] input_str;
      throw;
    }
    strcpy(field, temp_str_ptr + 6);
    if (field[0] == '\"') {
      delete [] input_str;
      delete [] field;
      throw std::runtime_error("INVALID_NAME");
    } else {
      student.name += strtok(field, "\"\'\n");
    }
    delete [] field;
  }
  temp_str_ptr = strstr(input_str, "group=");
  if (!temp_str_ptr) {
    delete [] input_str;
    throw std::runtime_error("GROUP_NOT_FOUND");
  } else if (temp_str_ptr[6] != '\"') {
    delete [] input_str;
    throw std::runtime_error("INVALID_GROUP");
  } else {
    try {
      field = new char[str_len];
    } catch (const std::bad_alloc &err) {
      delete [] input_str;
      throw;
    }
    strcpy(field, temp_str_ptr + 7);
    strcat(student.group, strtok(field, "\"\'\n"));
    delete [] field;
    student.group[7] = '\0';
    if (((student.group[0] != 'B') && (student.group[0] != 'M') && (student.group[0] != 'A') && (student.group[0] != 'S')) || (student.group[3] != '-')) {
      delete [] input_str;
      throw std::runtime_error("INVALID_GROUP");
    }
  }
  temp_str_ptr = strstr(input_str, "grade=");
  if (!temp_str_ptr) {
    delete [] input_str;
    throw std::runtime_error("GRADE_NOT_FOUND");
  } else {
    temp_str_ptr += 6;
    try {
      field = new char[str_len];
    } catch (const std::bad_alloc &err) {
      delete [] input_str;
      throw;
    }
    strcpy(field, temp_str_ptr);
    temp_str_ptr = strtok(field, "\'\",\n}");
    if (temp_str_ptr[0] == ' ' || temp_str_ptr[0] == '\0') {
      delete [] field;
      delete [] input_str;
      throw std::runtime_error("INVALID_GRADE");
    }
    student.grade = atof(temp_str_ptr);
    delete [] field;
    if (student.grade > 5.0f || student.grade < 0.0f) {
      delete [] input_str;
      throw std::runtime_error("INVALID_GRADE");
    }
  }
  delete [] input_str;
}

void __fillStudent(Student& student, const char *str, size_t len) {
  if (str == nullptr || str[0] != '{' || str[len - 1] != '}') {
    throw std::runtime_error("INVALID_INPUT");
  }
  char *input_str = new char[len + 1];
  input_str[len] = '\0';
  memcpy(input_str, str, len);
  char *field = nullptr;
  char *temp_str_ptr = strstr(input_str, "name=");
  if (!temp_str_ptr) {
    delete [] input_str;
    throw std::runtime_error("NAME_NOT_FOUND");
  } else if (temp_str_ptr[5] != '\"') {
    delete [] input_str;
    throw std::runtime_error("INVALID_NAME");
  } else {
    try {
      field = new char[len];
    } catch (const std::bad_alloc &err) {
      delete [] input_str;
      throw;
    }
    strcpy(field, temp_str_ptr + 6);
    if (field[0] == '\"') {
      delete [] input_str;
      delete [] field;
      throw std::runtime_error("INVALID_NAME");
    } else {
      student.name += strtok(field, "\"\'\n");
    }
    delete [] field;
  }
  temp_str_ptr = strstr(input_str, "group=");
  if (!temp_str_ptr) {
    delete [] input_str;
    throw std::runtime_error("GROUP_NOT_FOUND");
  } else if (temp_str_ptr[6] != '\"') {
    delete [] input_str;
    throw std::runtime_error("INVALID_GROUP");
  } else {
    try {
      field = new char[8];
    } catch (const std::bad_alloc &err) {
      delete [] input_str;
      throw;
    }
    strncpy(field, temp_str_ptr + 7, 7);
    field[7] = '\0';
    strcpy(student.group, strtok(field, "\"\'\n"));
    delete [] field;
    if (((student.group[0] != 'B') && (student.group[0] != 'M') && (student.group[0] != 'A') && (student.group[0] != 'S')) || (student.group[3] != '-')) {
      delete [] input_str;
      throw std::runtime_error("INVALID_GROUP");
    }
  }
  temp_str_ptr = strstr(input_str, "grade=");
  if (!temp_str_ptr) {
    delete [] input_str;
    throw std::runtime_error("GRADE_NOT_FOUND");
  } else {
    temp_str_ptr += 6;
    try {
      field = new char[len];
    } catch (const std::bad_alloc &err) {
      delete [] input_str;
      throw;
    }
    strcpy(field, temp_str_ptr);
    temp_str_ptr = strtok(field, "\'\",\n}");
    if (temp_str_ptr[0] == ' ' || temp_str_ptr[0] == '\0') {
      delete [] field;
      delete [] input_str;
      throw std::runtime_error("INVALID_GRADE");
    }
    student.grade = atof(temp_str_ptr);
    delete [] field;
    if (student.grade > 5.0f || student.grade < 0.0f) {
      delete [] input_str;
      throw std::runtime_error("INVALID_GRADE");
    }
  }
  delete [] input_str;
}

void __fillStudent(Student& student, const std::string& input_str) {
  if (input_str.front() != '{' || input_str.back() != '}') {
    throw std::runtime_error("INVALID_INPUT");
  }
  size_t index = input_str.find("name=");
  if (index == std::string::npos) {
    throw std::runtime_error("NAME_NOT_FOUND");
  }
  if (input_str[index + 5] != '\"') {
    throw std::runtime_error("INVALID_NAME");
  }
  index += 6;
  student.name = input_str.substr(index, input_str.find("\"", index) - index);
  if (student.name.empty()) {
    throw std::runtime_error("INVALID_NAME");
  }
  index = input_str.find("group=");
  if (index == std::string::npos) {
    throw std::runtime_error("GROUP_NOT_FOUND");
  }
  if (input_str[index + 6] != '\"') {
    throw std::runtime_error("INVALID_GROUP");
  }
  index += 7;
  if (((input_str[index] != 'B') && (input_str[index] != 'S') && (input_str[index] != 'M') && (input_str[index] != 'A')) 
        || (input_str[index + 3] != '-') || ((input_str.find("\"", index) - index) > 7)) {
    throw std::runtime_error("INVALID_GROUP");
  }
  input_str.copy(student.group, 7, index);
  index = input_str.find("grade=");
  if (index == std::string::npos) {
    throw std::runtime_error("GRADE_NOT_FOUND");
  }
  index += 6;
  size_t end_index = input_str.find("}", index);
  float grade = 0.0f;
  try {
    grade = std::stof(input_str.substr(index, end_index));
  } catch(const std::invalid_argument &err) {
    throw std::runtime_error("INVALID_GRADE");
  } catch(const std::out_of_range &err) {
    throw std::runtime_error("INVALID_GRADE");
  }
  if (grade > 5.0f || grade < 0.0f) {
    throw std::runtime_error("INVALID_GRADE");
  }
  student.grade = grade;
}

void printStudent(const Student& student) {
  std::cout << __structToStr(student) << std::endl;
  std::cout << __structToProperties(student) << std::endl;
}

std::string __structToStr(const Student& student) {
  return "student.name=" + student.name + "\nstudent.group=" 
          + student.group + "\nstudent.grade=" + std::to_string(student.grade) + "\n";
}

std::string __structToProperties(const Student& student) {
  return "{name=\"" + student.name + "\", group=\"" 
          + student.group + "\", grade=" + std::to_string(student.grade) + "}";
}

};
