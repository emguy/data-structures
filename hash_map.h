//FILE hash_map.h
#ifndef HASH_MAP_H
#define HASH_MAP_H
#include <vector>
#include <string>

#ifndef NULL
#define NULL ((void *) 0)
#endif

template<typename K, typename V>
class hash_map {
public:
    hash_map(int = DEFAULT_CAPACITY);
    ~hash_map() {}
    int get_size() const { return size; }
    bool is_empty() const { return size == 0; }
    void rehash(const int);
    V& operator[](const K&);
    int delete_key(const K&);
    bool contains_key(const K&) const;
    bool contains_value(const V&) const;
    void print() const;
    struct node {
        const K key;
        V value;
        node* next;
        node(K key, V value) : key(key), value(value), next(NULL) {};
        std::string to_string() const;
    };
private:
    int size;
    std::vector<node*> buckets;
    int get_index(const K&) const;
    static const int DEFAULT_CAPACITY = 32;
};

#endif
