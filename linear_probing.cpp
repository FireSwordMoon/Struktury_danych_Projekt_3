#include "linear_probing.hpp"

// puste pole to minus jeden a usuniete to minus dwa
LinearProbingHT::LinearProbingHT(int cap) : HashTable(cap) {
    table.assign(capacity, -1);
}

HashTable* LinearProbingHT::clone() const {
    return new LinearProbingHT(*this);
}

void LinearProbingHT::insert(int key) {
    int h = key % capacity;
    for (int i = 0; i < capacity; i++) {
        int idx = (h + i) % capacity;
        if (table[idx] <= -1) {
            table[idx] = key;
            return;
        }
        if (table[idx] == key) return;
    }
}

bool LinearProbingHT::search(int key) {
    int h = key % capacity;
    for (int i = 0; i < capacity; i++) {
        int idx = (h + i) % capacity;
        if (table[idx] == -1) return false;
        if (table[idx] == key) return true;
    }
    return false;
}

void LinearProbingHT::remove(int key) {
    int h = key % capacity;
    for (int i = 0; i < capacity; i++) {
        int idx = (h + i) % capacity;
        if (table[idx] == -1) return;
        if (table[idx] == key) {
            table[idx] = -2;
            return;
        }
    }
}

int LinearProbingHT::get_insert_probes(int key) {
    int h = key % capacity;
    int probes = 1;
    for (int i = 0; i < capacity; i++) {
        int idx = (h + i) % capacity;
        if (table[idx] <= -1) return probes;
        probes++;
    }
    return probes;
}

int LinearProbingHT::get_search_probes(int key) {
    int h = key % capacity;
    int probes = 1;
    for (int i = 0; i < capacity; i++) {
        int idx = (h + i) % capacity;
        if (table[idx] == -1) return probes;
        if (table[idx] == key) return probes;
        probes++;
    }
    return probes;
}

std::string LinearProbingHT::get_name() { return "sondowanie_liniowe"; }