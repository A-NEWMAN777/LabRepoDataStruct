
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <initializer_list>
#include <iostream>
#include <cstddef>
#include <iterator>

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& val) : data(val), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t list_size;

    void copy_from(const LinkedList& other) {
        for (Node* cur = other.head; cur; cur = cur->next) {
            append(cur->data);
        }
    }

public:
    class iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator(Node* ptr, const LinkedList* parent = nullptr)
            : node(ptr), parent(parent) {
        }
        reference operator*() const { return node->data; }
        pointer operator->() const { return &node->data; }
        iterator& operator++() {
            if (node) node = node->next;
            return *this;
        }
        iterator operator++(int) {
            iterator tmp = *this;
            if (node) node = node->next;
            return tmp;
        }
        iterator& operator--() {
            if (node) {
                node = node->prev;
            }
            else if (parent) {
                node = parent->tail;
            }
            return *this;
        }
        iterator operator--(int) {
            iterator tmp = *this;
            --(*this);
            if (tmp == NULL)
                return 0;
            else
                return tmp;
        }
        iterator operator+(difference_type n) const {
            iterator it = *this;
            while (n-- > 0 && it.node) it.node = it.node->next;
            return it;
        }
        iterator operator-(difference_type n) const {
            iterator it = *this;
            while (n-- > 0) {
                if (it.node) it.node = it.node->prev;
                else if (parent) it.node = parent->tail;
            }
            return it;
        }
        difference_type operator-(const iterator& other) const {
            difference_type dist = 0;
            Node* cur = other.node;
            while (cur && cur != node) {
                cur = cur->next;
                ++dist;
            }
            return dist;
        }
        bool operator==(const iterator& o) const { return node == o.node; }
        bool operator!=(const iterator& o) const { return node != o.node; }

    private:
        Node* node;
        const LinkedList* parent;
        friend class LinkedList;
    };
    
    LinkedList() : head(nullptr), tail(nullptr), list_size(0) {}
    LinkedList(const std::initializer_list<T>& init) : LinkedList() {
        for (const auto& v : init) append(v);
    }
    LinkedList(const LinkedList& other) : LinkedList() { copy_from(other); }
    LinkedList(LinkedList&& other) noexcept
        : head(other.head), tail(other.tail), list_size(other.list_size) {
        other.head = other.tail = nullptr;
        other.list_size = 0;
    }
    ~LinkedList() { clear(); }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            copy_from(other);
        }
        return *this;
    }
    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            list_size = other.list_size;
            other.head = other.tail = nullptr;
            other.list_size = 0;
        }
        return *this;
    }

    size_t size() const noexcept { return list_size; }
    void clear() noexcept {
        Node* cur = head;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = tail = nullptr;
        list_size = 0;
    }

    void append(const T& value) {
        Node* node = new Node(value);
        if (!tail) {
            head = tail = node;
        }
        else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        ++list_size;
    }
    void prepend(const T& value) {
        Node* node = new Node(value);
        if (!head) {
            head = tail = node;
        }
        else {
            head->prev = node;
            node->next = head;
            head = node;
        }
        ++list_size;
    }
    void insert(size_t index, const T& value) {
        if (index > list_size) throw std::out_of_range("Index out of range");
        if (index == 0) return prepend(value);
        if (index == list_size) return append(value);
        Node* cur = head;
        for (size_t i = 0; i < index; ++i) cur = cur->next;
        Node* node = new Node(value);
        Node* prev = cur->prev;
        prev->next = node;
        node->prev = prev;
        node->next = cur;
        cur->prev = node;
        ++list_size;
    }

    T& at(size_t index) {
        if (index >= list_size) throw std::out_of_range("Index out of range");
        Node* cur = head;
        for (size_t i = 0; i < index; ++i) cur = cur->next;
        return cur->data;
    }
    const T& at(size_t index) const {
        if (index >= list_size) throw std::out_of_range("Index out of range");
        Node* cur = head;
        for (size_t i = 0; i < index; ++i) cur = cur->next;
        return cur->data;
    }
    T& operator[](size_t index) { return at(index); }
    const T& operator[](size_t index) const { return at(index); }

    size_t find(const T& value) const {
        size_t idx = 0;
        for (Node* cur = head; cur; cur = cur->next, ++idx) {
            if (cur->data == value) return idx;
        }
        return list_size;
    }
    iterator find_node(const T& value) const {
        for (Node* cur = head; cur; cur = cur->next) {
            if (cur->data == value) return iterator(cur, this);
        }
        return end();
    }

    bool remove(const T& value) {
        for (Node* cur = head; cur; cur = cur->next) {
            if (cur->data == value) {
                Node* p = cur->prev;
                Node* n = cur->next;
                if (p) p->next = n; else head = n;
                if (n) n->prev = p; else tail = p;
                delete cur;
                --list_size;
                return true;
            }
        }
        return false;
    }
    void remove_all(const T& value) {
        while (remove(value)) {}
    }

    friend std::ostream& operator<<(std::ostream& os, const LinkedList& list) {
        for (auto it = list.begin(); it != list.end(); ++it) {
            os << *it;
            auto tmp = it; ++tmp;
            if (tmp != list.end()) os << " -> ";
        }
        return os;
    }

    iterator begin() const noexcept { return iterator(head, this); }
    iterator end() const noexcept { return iterator(nullptr, this); }
};

#endif

