#include "lab.h"

lab::HashTable::HashTable() {
    data = new std::vector<entry>;
    data->reserve(100);
}

lab::HashTable::HashTable(const HashTable &other) {
    data = new std::vector<entry>;
    data->reserve(other.data->size());
    copy(other.data->begin(), other.data->end(), back_inserter(*data));
}

lab::HashTable::~HashTable() {
    delete data;
}

void lab::HashTable::reset() {
    delete data;
    data = new std::vector<entry>;
    data->reserve(100);
}

size_t lab::HashTable::count() {
    return data->size();
}

void lab::HashTable::save(const char *path) {
  std::ofstream file(path);
  if (file.is_open()) {
    for (auto i = data->begin(); i < data->end(); i++) {
        file << i->index << " " << i->word << " " << i->repeats << "\n";
    }
    file.close();
  } else {
    throw std::invalid_argument("Unable to open file");
  }
}

void lab::HashTable::load(const char *path) {
  std::ifstream file(path);
  if (file.is_open()) {
        this->reset();
        char s[LEN*2];
        file.getline(s, LEN*2, '\n');
        lab::entry entry;
        while (s[0]) {
            sscanf(s,"%u %s %lu", &entry.index, entry.word, &entry.repeats);
            data->push_back(entry);
            file.getline(s, LEN*2, '\n');
        }
    file.close();
  } else {
    throw std::invalid_argument("Unable to open file");
  }
}

void lab::HashTable::add(entry &new_entry) {
    unsigned int index = hash_function(new_entry);
    new_entry.index = index;
    data->insert(find_hash(index), new_entry);
}

void lab::HashTable::remove(entry &new_entry) {
    unsigned int index = hash_function(new_entry);
    auto i = find_hash(index);
    while (i->index == index && strcmp(new_entry.word, i->word) != 0) i++;
    if (strcmp(new_entry.word, i->word) == 0) data->erase(i);
}

bool lab::HashTable::isNotEmpty(unsigned int index) {
    auto i = find_hash(index);
    return i->index == index;
}

bool lab::HashTable::operator==(const HashTable &other) {
    bool result = false;
    if (data->size() == other.data->size()) {
        result = true;
        auto i = data->begin();
        auto j = other.data->begin();
        while (i < data->end() && j < other.data->end()) {
            if (!(strcmp(i->word, j->word) == 0 && i->index == j->index
            && i->repeats == j->repeats)) {
                result = false;
                break;
            }
            i++; j++;
        }
    }
    return result;
}

std::vector<lab::entry>::iterator lab::HashTable::operator[](unsigned int index) {
    return find_hash(index);
}

lab::HashTable lab::HashTable::operator&&(const HashTable &other) {
    HashTable result;
    auto i = data->begin();
    auto j = other.data->begin();
    while (i < data->end() && j < other.data->end()) {
        if (i->index == j->index) {
            auto k = j;
            while (i->index == k->index) {
                if (strcmp(i->word, k->word) == 0 && i->repeats == k->repeats) {
                    entry new_entry;
                    new_entry.index = i->index;
                    new_entry.repeats = i->repeats;
                    strcpy(new_entry.word, i->word);
                    result.data->push_back(new_entry);
                    break;
                }
                k++;
            }
            i++;
        } else {
            if (j->index < i->index) j++;
            else i++;
        }
    }
    return result;
}

unsigned int lab::HashTable::hash_function(entry &new_entry) {
    long unsigned int sum = new_entry.word[0];
    for (int i = 1; i < strlen(new_entry.word); i++) {
        sum *= new_entry.word[i];
    }
    return sum % MAX_HASH;
}

std::vector<lab::entry>::iterator lab::HashTable::find_hash(unsigned int hash) {
    std::vector<lab::entry>::iterator pos;
    if (hash <= data->begin()->index) {
        pos = data->begin();
    } else if (hash > (data->end()-1)->index) {
        pos = data->end();
    } else if (hash == (data->end()-1)->index) {
        pos = data->end()-1;
    } else {
        unsigned int delta = data->size()/2;
        pos = data->begin() + delta;
        while (!((pos-1)->index <= hash && pos->index >= hash)) {
            if (delta > 1) delta /= 2;
            hash < pos->index ? pos -= delta : pos += delta;
        }
        while ((pos-1)->index == hash) pos -= 1;
    }
    return pos;
}
