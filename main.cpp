#include "lab.h"
#include <assert.h>

int main(void) {

  static const char letters[] =
  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

  lab::HashTable a;
  a.load("collection_1.txt");
  lab::entry new_entry;

  srand((unsigned)time(NULL));
  
  for (int i = 0; i < 10000; i++) {
    std::string random_word;
    random_word.reserve(LEN);
    for (int i = 0; i < rand() % (LEN-20) + 1; i++) {
      random_word += letters[rand() % (sizeof(letters) - 1)];
    }
    strcpy(new_entry.word, random_word.c_str());
    new_entry.repeats = rand() % LEN + 1;
    a.add(new_entry);
  }

  a.save("collection_2.txt");

  std::cout << "\nEverything's fine\n";
  return 0;
}
