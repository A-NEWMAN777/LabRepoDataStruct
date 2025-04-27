#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <functional>
#include <stdexcept>
#include <vector>
#include <utility>

template <typename K, typename V>
class Map {
public:
    Map(size_t initial_capacity = 8);
    ~Map() = default;

    // Insert or access value by key
    V& operator[](const K& key);

    // Check existence (does not create)
    bool contains(const K& key) const;

    // Remove key, return true if removed
    bool remove(const K& key);

    // Number of active entries
    size_t size() const { return count; }

    // Remove all entries
    void clear();

    typedef std::pair<K, V> value_type;
    class iterator;
    iterator begin() const;
    iterator end() const;

    template <typename KK, typename VV>
    friend std::ostream& operator<<(std::ostream& os, const Map<KK, VV>& m);

private:
    struct Entry { K key; V value; bool occupied = false; bool deleted = false; };
    std::vector<Entry> table;
    size_t count;
    size_t capacity;
    const float max_load_factor = 0.5f;

    // Rehash to double capacity
    void rehash();

    // Find slot for key or insertion
    size_t find_index(const K& key) const;
};


template <typename K, typename V>
Map<K, V>::Map(size_t initial_capacity)
    : table(initial_capacity), count(0), capacity(initial_capacity) {
}

template <typename K, typename V>
size_t Map<K, V>::find_index(const K& key) const {
    size_t idx = std::hash<K>{}(key) % capacity;
    size_t start = idx;
    while (true) {
        const Entry& e = table[idx];
        if (!e.occupied) {
            if (!e.deleted) return idx;
        }
        else if (!e.deleted && e.key == key) {
            return idx;
        }
        idx = (idx + 1) % capacity;
        if (idx == start) break;
    }
    return idx;
}

template <typename K, typename V>
void Map<K, V>::rehash() {
    size_t new_capacity = capacity * 2;
    std::vector<Entry> old = std::move(table);
    table.clear(); table.resize(new_capacity);
    capacity = new_capacity;
    count = 0;
    for (auto& e : old) {
        if (e.occupied && !e.deleted) {
            (*this)[e.key] = e.value;
        }
    }
}

template <typename K, typename V>
V& Map<K, V>::operator[](const K& key) {
    if (float(count + 1) / capacity > max_load_factor) rehash();
    size_t idx = find_index(key);
    if (!(table[idx].occupied && !table[idx].deleted)) {
        table[idx].key = key;
        table[idx].value = V{};
        table[idx].occupied = true;
        table[idx].deleted = false;
        ++count;
    }
    return table[idx].value;
}

template <typename K, typename V>
bool Map<K, V>::contains(const K& key) const {
    size_t idx = find_index(key);
    return table[idx].occupied && !table[idx].deleted && table[idx].key == key;
}

template <typename K, typename V>
bool Map<K, V>::remove(const K& key) {
    size_t idx = find_index(key);
    if (table[idx].occupied && !table[idx].deleted && table[idx].key == key) {
        table[idx].occupied = false;
        table[idx].deleted = true;
        --count;
        return true;
    }
    return false;
}

template <typename K, typename V>
void Map<K, V>::clear() {
    table.clear(); table.resize(capacity);
    count = 0;
}

//----------------------------------------------------------------------------
// Iterator

template <typename K, typename V>
class Map<K, V>::iterator {
public:
    iterator(const Map<K, V>* m, size_t pos) : map(m), index(pos) {}
    // Return key-value pair by value
    std::pair<K, V> operator*() const {
        const Entry& e = map->table[index];
        return { e.key, e.value };
    }
    iterator& operator++() {
        do { ++index; } while (index < map->capacity &&
            !(map->table[index].occupied && !map->table[index].deleted));
        return *this;
    }
    bool operator!=(const iterator& o) const {
        return index != o.index || map != o.map;
    }
private:
    const Map<K, V>* map;
    size_t index;
};

template <typename K, typename V>
typename Map<K, V>::iterator Map<K, V>::begin() const {
    size_t i = 0;
    while (i < capacity && !(table[i].occupied && !table[i].deleted)) ++i;
    return iterator(this, i);
}

template <typename K, typename V>
typename Map<K, V>::iterator Map<K, V>::end() const {
    return iterator(this, capacity);
}

//----------------------------------------------------------------------------
// ostream <<

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const Map<K, V>& m) {
    os << "{";
    bool first = true;
    for (size_t i = 0; i < m.capacity; ++i) {
        const auto& e = m.table[i];
        if (e.occupied && !e.deleted) {
            if (!first) os << ", ";
            os << e.key << ":" << e.value;
            first = false;
        }
    }
    os << "}";
    return os;
}

#endif