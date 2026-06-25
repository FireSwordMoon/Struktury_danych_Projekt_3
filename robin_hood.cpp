#include "robin_hood.hpp"
#include <utility>

RobinHoodHT::RobinHoodHT(int cap) : HashTable(cap) {
    table.assign(capacity, -1);
}

HashTable* RobinHoodHT::clone() const {
    return new RobinHoodHT(*this);
}

void RobinHoodHT::insert(int key) {
    int curr_key = key;
    int curr_dist = 0;
    int idx = curr_key % capacity;
    for (int i = 0; i < capacity; i++) {
        if (table[idx] <= -1) {
            table[idx] = curr_key;
            return;
        }
        if (table[idx] == curr_key) return;
        
        int existing_dist = (idx - (table[idx] % capacity) + capacity) % capacity;
        if (curr_dist > existing_dist) {
            std::swap(curr_key, table[idx]);
            curr_dist = existing_dist;
        }
        idx = (idx + 1) % capacity;
        curr_dist++;
    }
}

bool RobinHoodHT::search(int key) {
    int idx = key % capacity;
    int dist = 0;
    for (int i = 0; i < capacity; i++) {
        if (table[idx] == -1) return false;
        if (table[idx] == key) return true;
        
        int existing_dist = (idx - (table[idx] % capacity) + capacity) % capacity;
        if (dist > existing_dist && table[idx] != -2) return false;
        
        idx = (idx + 1) % capacity;
        dist++;
    }
    return false;
}

void RobinHoodHT::remove(int key) {
    int idx = key % capacity;
    int dist = 0;
    for (int i = 0; i < capacity; i++) {
        if (table[idx] == -1) return;
        if (table[idx] == key) {
            table[idx] = -2;
            return;
        }
        idx = (idx + 1) % capacity;
        dist++;
    }
}

int RobinHoodHT::get_insert_probes(int key) {
    int probes = 1;
    int curr_key = key;
    int curr_dist = 0;
    int idx = curr_key % capacity;
    for (int i = 0; i < capacity; i++) {
        if (table[idx] <= -1) return probes;
        int existing_dist = (idx - (table[idx] % capacity) + capacity) % capacity;
        if (curr_dist > existing_dist) {
            curr_dist = existing_dist;
        }
        idx = (idx + 1) % capacity;
        curr_dist++;
        probes++;
    }
    return probes;
}

int RobinHoodHT::get_search_probes(int key) {
    int probes = 1;
    int idx = key % capacity;
    int dist = 0;
    for (int i = 0; i < capacity; i++) {
        if (table[idx] == -1) return probes;
        if (table[idx] == key) return probes;
        int existing_dist = (idx - (table[idx] % capacity) + capacity) % capacity;
        if (dist > existing_dist && table[idx] != -2) return probes;
        idx = (idx + 1) % capacity;
        dist++;
        probes++;
    }
    return probes;
}

std::string RobinHoodHT::get_name() { return "robin_hood"; }