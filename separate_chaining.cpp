#include "separate_chaining.hpp"
#include <algorithm>

SeparateChainingHT::SeparateChainingHT(int cap) : HashTable(cap) {
    table.resize(capacity);
}

HashTable* SeparateChainingHT::clone() const {
    return new SeparateChainingHT(*this);
}

void SeparateChainingHT::insert(int key) {
    int h = key % capacity;
    auto it = std::find(table[h].begin(), table[h].end(), key);
    if (it == table[h].end()) {
        table[h].push_back(key);
    }
}

bool SeparateChainingHT::search(int key) {
    int h = key % capacity;
    auto it = std::find(table[h].begin(), table[h].end(), key);
    return it != table[h].end();
}

void SeparateChainingHT::remove(int key) {
    int h = key % capacity;
    auto it = std::find(table[h].begin(), table[h].end(), key);
    if (it != table[h].end()) {
        table[h].erase(it);
    }
}

int SeparateChainingHT::get_insert_probes(int key) {
    int h = key % capacity;
    int probes = table[h].size();
    if (probes == 0) return 1;
    return probes;
}

int SeparateChainingHT::get_search_probes(int key) {
    int h = key % capacity;
    int probes = 0;
    for (int val : table[h]) {
        probes++;
        if (val == key) return probes;
    }
    if (probes == 0) return 1;
    return probes;
}

std::string SeparateChainingHT::get_name() { return "lancuchowanie"; }