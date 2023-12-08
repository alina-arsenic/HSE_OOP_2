#ifndef __LAB_H__
#define __LAB_H__

#include <cstring>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#define LEN 50
#define MAX_HASH 10301

namespace lab {
  typedef struct {
  unsigned int index;
  size_t repeats;
  char word[LEN];
} entry;

class HashTable {
public:
  HashTable();
  HashTable(const HashTable &other);
  ~HashTable();

  void reset();  // удаляет все значения
  size_t count();  // количество значений
  void save(const char *path);  // сохранить содержимое в файл по пути
  void load(const char *path);  // загрузить из файла по пути

  void add(entry &new_entry);  // добавить запись
  void remove(entry &new_entry);  // удалить запись при ее наличии
  bool isNotEmpty(unsigned int index);  // проверить наличие записи по ключу

  bool operator==(const HashTable &other);  // равенство
  std::vector<lab::entry>::iterator operator[](unsigned int index);  // принять ключ вернуть запись
  HashTable operator&&(const HashTable &other);  // создает новую таблицу из пересечения двух

  unsigned int wordCountByRepeats(unsigned int repeats);

private:
  std::vector<entry> *data;

  unsigned int hash_function(entry &new_entry);
  std::vector<entry>::iterator find_hash(unsigned int index);
};

} // namespace lab

#endif // __LAB_H__
