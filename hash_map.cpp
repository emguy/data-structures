//FILE hash_map.cpp
#include "hash_map.h"
#include <iostream> //std::cout
#include <cstdio>   //sprintf

namespace {
template<typename K>
int get_hashcode(K key);

template<>
int get_hashcode<int>(int key) {
    return key >= 0 ? key : -key;
}

template<>
int get_hashcode<char>(char key) {
    return (int) key;
}

template<>
int get_hashcode<std::string>(std::string key) {
    int result = 0;
    for (size_t i = 0; i < key.size() && i < 10; ++i) {
        result = result * 31 + (key[i] % 31);
    }
    return result;
}
}

namespace {
template<typename T>
std::string tostr(const T& val);
template<>
std::string tostr<int>(const int& val) {
    char s[20];
    sprintf(s, "%d", val);
    return std::string(s);
}

template<>
std::string tostr<std::string>(const std::string& val) {
    return val;
}

template<>
std::string tostr<char>(const char& val) {
    return "" + val;
}
}

template<typename K, typename V>
std::string hash_map<K, V>::node::to_string() const {
    return tostr<K>(key) + "->" + tostr<V>(value);
}

template<typename K, typename V>
hash_map<K, V>::hash_map(int cap) : size(0), buckets(cap, NULL) {
}

template<typename K, typename V>
int hash_map<K, V>::get_index(const K& key) const {
    return get_hashcode<K>(key) % buckets.size();
}

template<typename K, typename V>
bool hash_map<K, V>::contains_key(const K& key) const {
    int index = get_index(key);
    hash_map<K, V>::node* cur = buckets[index];
    while (cur) {
        if (cur->key == key) {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

template<typename K, typename V>
int hash_map<K, V>::delete_key(const K& key) {
    int index = get_index(key);
    hash_map<K, V>::node* cur = buckets[index];
    if (!cur) {
        return 0;
    }
    if (cur->key == key) {
        buckets[index] = cur->next;
        --size;
        delete cur;
        return 1;
    }
    while (cur->next) {
        if (cur->next->key == key) {
            hash_map<K, V>::node* p = cur->next;
            cur->next = p->next;
            --size;
            delete p;
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}

template<typename K, typename V>
bool hash_map<K, V>::contains_value(const V& value) const {
    for (size_t index = 0; index < buckets.size(); ++index) {
        hash_map<K, V>::node* cur = buckets[index];
        while (cur) {
            if (cur->value == value) {
                return true;
            }
            cur = cur->next;
        }
    }
    return false;
}

template<typename K, typename V>
V& hash_map<K, V>::operator[](const K& key) {
    int index = get_index(key);
    hash_map<K, V>::node* cur = buckets[index];
    while (cur) {
        if (cur->key == key) {
            return cur->value;
        }
        cur = cur->next;
    }
    V value;
    node* new_node = new node(key, value);
    new_node->next = buckets[index];
    buckets[index] = new_node;
    ++size;
    return new_node->value;
}

template<typename K, typename V>
void hash_map<K, V>::rehash(const int cap) {
    std::vector<node*> tmp = buckets;
    size = 0;
    buckets.resize(cap);
    for (size_t index = 0; index < buckets.size(); ++index) {
        buckets[index] = NULL;
    }
    for (size_t index = 0; index < tmp.size(); ++index) {
        hash_map<K, V>::node* cur = tmp[index];
        while (cur) {
            (*this)[cur->key] = cur->value;
            cur = cur->next;
        }
    }
}

template<typename K, typename V>
void hash_map<K, V>::print() const {
    std::cout << "--------------------------------------\n";
    std::cout << "*** Total of " << size << " elements ***\n";
    std::cout << "*** \n";
    for (size_t index = 0; index < buckets.size(); ++index) {
        std::cout << index << ": ";
        hash_map<K, V>::node* cur = buckets[index];
        while (cur) {
            std::cout << cur->to_string();
            std::cout << ", ";
            cur = cur->next;
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------------\n\n";
}

int main() {
    //only implemented for string, char, and int
    hash_map<std::string, std::string> h(10);
    h["Tom"]    = "902";
    h["Mary"]   = "912";
    h["Emily"]  = "922";
    h["Jim"]    = "932";
    h["Jammie"] = "942";
    h["Brown"]  = "952";
    h["Timmy"]  = "962";
    h["Kavin"]  = "972";
    h["Bowman"] = "982";
    h["Sara"]   = "992";
    h["Tifany"] = "102";
    h["Steve"]  = "132";
    h["Peter"]  = "152";
    h["Jocob"]  = "162";
    h["Mike"]   = "172";
    h["Mike"]   = "999"; // <---- update
    h.print();

    h.rehash(20);
    h.print();

    h.delete_key("Emily");
    h.delete_key("Mary");
    h.delete_key("Jammie");
    h.print();
}
