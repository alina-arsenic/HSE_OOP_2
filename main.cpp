#include "lab.h"
#include <assert.h>

int main(void) {

  static const char letters[] =
  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

  lab::HashTable a;
  lab::entry new_entry;

  strcpy(new_entry.word, "Kreslo");
  new_entry.repeats = 10;
  a.add(new_entry);

  strcpy(new_entry.word, "Lampa");
  new_entry.repeats = 1;
  a.add(new_entry);

  strcpy(new_entry.word, "Derevo");
  new_entry.repeats = 56;
  a.add(new_entry);

  strcpy(new_entry.word, "Vetka");
  new_entry.repeats = 7;
  a.add(new_entry);

  strcpy(new_entry.word, "Veter");
  new_entry.repeats = 5;
  a.add(new_entry);

  strcpy(new_entry.word, "Vorobei");
  new_entry.repeats = 3;
  a.add(new_entry);

  a.save("collection_1.txt");
  a.reset();
  a.save("collection_empty.txt");
  a.load("collection_1.txt");

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

  strcpy(new_entry.word, "Kreslo");
  a.remove(new_entry);
  strcpy(new_entry.word, "Bereslo");
  a.remove(new_entry);

  a.save("collection_2.txt");

  lab::HashTable b;
  b.load("collection_1.txt");
  lab::HashTable c = a && b;
  c.save("collection_3.txt");

  b.load("collection_2.txt");
  assert(a == b);

  std::cout << "\nEverything's fine\n";
  return 0;
}
