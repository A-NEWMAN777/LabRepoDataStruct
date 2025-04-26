#ifndef ORDERED_SET_H
#define ORDERED_SET_H

#include <optional>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>

template<typename T>
class OrderedSet {
private:
    struct Node {
        T val;
        Node* left;
        Node* right;
        Node(const T& v) : val(v), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insertNode(Node* n, const T& v) {
        if (!n) return new Node(v);
        if (v < n->val) n->left = insertNode(n->left, v);
        else if (v > n->val) n->right = insertNode(n->right, v);
        return n;
    }

    bool containsNode(Node* n, const T& v) const {
        if (!n) return false;
        if (v == n->val) return true;
        return v < n->val ? containsNode(n->left, v) : containsNode(n->right, v);
    }

    Node* clearNode(Node* n) {
        if (!n) return nullptr;
        clearNode(n->left);
        clearNode(n->right);
        delete n;
        return nullptr;
    }

    size_t sizeNode(Node* n) const {
        if (!n) return 0;
        return 1 + sizeNode(n->left) + sizeNode(n->right);
    }

    size_t heightNode(Node* n) const {
        if (!n) return 0;
        size_t lh = heightNode(n->left);
        size_t rh = heightNode(n->right);
        return 1 + (lh > rh ? lh : rh);
    }

    void inorder(Node* n, std::vector<T>& out) const {
        if (!n) return;
        inorder(n->left, out);
        out.push_back(n->val);
        inorder(n->right, out);
    }

    void preorder(Node* n, std::vector<T>& out) const {
        if (!n) return;
        out.push_back(n->val);
        preorder(n->left, out);
        preorder(n->right, out);
    }

    void postorder(Node* n, std::vector<T>& out) const {
        if (!n) return;
        postorder(n->left, out);
        postorder(n->right, out);
        out.push_back(n->val);
    }

    Node* buildBalanced(const std::vector<T>& vals, int lo, int hi) {
        if (lo > hi) return nullptr;
        int mid = lo + (hi - lo) / 2;
        Node* n = new Node(vals[mid]);
        n->left = buildBalanced(vals, lo, mid - 1);
        n->right = buildBalanced(vals, mid + 1, hi);
        return n;
    }

    Node* rebalanceNode(Node* n) {
        std::vector<T> vals;
        inorder(n, vals);
        clearNode(n);
        return buildBalanced(vals, 0, static_cast<int>(vals.size()) - 1);
    }

    Node* eraseNode(Node* n, const T& v, bool& removed) {
        if (!n) return nullptr;
        if (v < n->val) {
            n->left = eraseNode(n->left, v, removed);
        }
        else if (v > n->val) {
            n->right = eraseNode(n->right, v, removed);
        }
        else {
            removed = true;
            if (!n->left) {
                Node* r = n->right;
                delete n;
                return r;
            }
            if (!n->right) {
                Node* l = n->left;
                delete n;
                return l;
            }
            Node* succ = n->right;
            while (succ->left) succ = succ->left;
            n->val = succ->val;
            n->right = eraseNode(n->right, succ->val, removed);
        }
        return n;
    }

    std::optional<T> parentNode(Node* n, const T& v, Node* parent) const {
        if (!n) return std::nullopt;
        if (v == n->val) {
            return parent ? std::optional<T>(parent->val)
                : std::nullopt;
        }
        if (v < n->val) return parentNode(n->left, v, n);
        else             return parentNode(n->right, v, n);
    }

    void buildString(Node* n, std::ostringstream& oss, const std::string prefix, bool isLeft) const {
        if (!n) return;
        oss << prefix << (isLeft ? "??? " : "??? ") << n->val << "\n";
        buildString(n->left, oss, prefix + (isLeft ? "    " : "?   "), true);
        buildString(n->right, oss, prefix + (isLeft ? "    " : "?   "), false);
    }

public:
    enum class Order { IN, PRE, POST };

    OrderedSet() : root(nullptr) {}
    ~OrderedSet() { clear(); }

    OrderedSet(const OrderedSet& other) : root(nullptr) {
        for (const auto& v : other.traversal(Order::IN))
            insert(v);
    }
    OrderedSet& operator=(const OrderedSet& other) {
        if (this != &other) {
            clear();
            for (const auto& v : other.traversal(Order::IN))
                insert(v);
        }
        return *this;
    }

    OrderedSet(OrderedSet&& other) noexcept : root(other.root) {
        other.root = nullptr;
    }
    OrderedSet& operator=(OrderedSet&& other) noexcept {
        if (this != &other) {
            clear();
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }

    void insert(const T& v) { if (!contains(v)) root = insertNode(root, v); }
    bool contains(const T& v) const { return containsNode(root, v); }
    void clear() { root = clearNode(root); }
    size_t size() const { return sizeNode(root); }
    size_t get_height() const { return heightNode(root); }

    std::vector<T> traversal(Order ord) const {
        std::vector<T> out;
        if (ord == Order::IN)   inorder(root, out);
        else if (ord == Order::PRE) preorder(root, out);
        else                     postorder(root, out);
        return out;
    }

    std::optional<T> get_parent(const T& v) const {
        auto p = parentNode(root, v, nullptr);
        if (p) return p;
        if (contains(v)) return std::optional<T>(v);
        return std::nullopt;
    }

    void rebalance() { root = rebalanceNode(root); }
    bool erase(const T& v) { bool removed = false; root = eraseNode(root, v, removed); return removed; }
    
    class iterator {
        std::stack<Node*> st;
        Node* curr;
    public:
        iterator(Node* r) : curr(r) {
            while (curr) { st.push(curr); curr = curr->left; }
            advance();
        }
        T value;
        bool at_end = false;
        void advance() {
            if (st.empty()) { at_end = true; return; }
            Node* n = st.top(); st.pop();
            value = n->val;
            Node* r = n->right;
            while (r) { st.push(r); r = r->left; }
        }
        T operator*() const { return value; }
        iterator& operator++() { advance(); return *this; }
        bool operator!=(const iterator& o) const { return at_end != o.at_end; }
    };

    iterator begin() const { return iterator(root); }
    iterator end()   const { auto it = iterator(nullptr); it.at_end = true; return it; }
    
    std::string tree_string() const {
        std::ostringstream oss;
        buildString(root, oss, "", true);
        return oss.str();
    }

    OrderedSet operator+(const OrderedSet& o) const {
        OrderedSet res = *this;
        for (auto v : o.traversal(Order::IN)) res.insert(v);
        return res;
    }
    OrderedSet operator*(const OrderedSet& o) const {
        OrderedSet res;
        for (auto v : traversal(Order::IN)) if (o.contains(v)) res.insert(v);
        return res;
    }
    OrderedSet operator-(const OrderedSet& o) const {
        OrderedSet res;
        for (auto v : traversal(Order::IN)) if (!o.contains(v)) res.insert(v);
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const OrderedSet& s) {
        auto v = s.traversal(Order::IN);
        os << "[";
        for (size_t i = 0; i < v.size(); ++i) {
            os << v[i];
            if (i + 1 < v.size()) os << ", ";
        }
        os << "]";
        return os;
    }
};

#endif