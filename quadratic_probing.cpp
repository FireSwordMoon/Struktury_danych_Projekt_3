#include "quadratic_probing.hpp"
#include <cmath>

QuadraticProbingHT::QuadraticProbingHT(int cap) : HashTable(cap) {
    table.assign(capacity, -1);
}

HashTable* QuadraticProbingHT::clone() const {
    return new QuadraticProbingHT(*this);
}

void QuadraticProbingHT::insert(int key) {
    int h = std::abs(key) % capacity;
    for (int i = 0; i < capacity; i++) {
        long long offset = (long long)i * i;
        int idx = (h + offset) % capacity;
        if (table[idx] <= -1) {
            table[idx] = key;
            return;
        }
        if (table[idx] == key) return;
    }
}

bool QuadraticProbingHT::search(int key) {
    int h = std::abs(key) % capacity;
    for (int i = 0; i < capacity; i++) {
        long long offset = (long long)i * i;
        int idx = (h + offset) % capacity;
        if (table[idx] == -1) return false;
        if (table[idx] == key) return true;
    }
    return false;
}

void QuadraticProbingHT::remove(int key) {
    int h = std::abs(key) % capacity;
    for (int i = 0; i < capacity; i++) {
        long long offset = (long long)i * i;
        int idx = (h + offset) % capacity;
        if (table[idx] == -1) return;
        if (table[idx] == key) {
            table[idx] = -2;
            return;
        }
    }
}

int QuadraticProbingHT::get_insert_probes(int key) {
    int h = std::abs(key) % capacity;
    int probes = 1;
    for (int i = 0; i < capacity; i++) {
        long long offset = (long long)i * i;
        int idx = (h + offset) % capacity;
        if (table[idx] <= -1) return probes;
        probes++;
    }
    return probes;
}

int QuadraticProbingHT::get_search_probes(int key) {
    int h = std::abs(key) % capacity;
    int probes = 1;
    for (int i = 0; i < capacity; i++) {
        long long offset = (long long)i * i;
        int idx = (h + offset) % capacity;
        if (table[idx] == -1) return probes;
        if (table[idx] == key) return probes;
        probes++;
    }
    return probes;
}

std::string QuadraticProbingHT::get_name() { return "sondowanie_kwadratowe"; }