#include <iostream>
#include <limits.h>
#include <queue>
#include <functional>
#include <stack>
#include <algorithm>


// with parent
template<class T>
class bst
{
public:
    struct Node
    {
        T val;
        Node *l { nullptr };
        Node *r { nullptr };
        Node *parent { nullptr };

        Node(T _val) : val(_val) {}
    };

    struct Iterator
    {
        Node* _node{nullptr};

        Iterator(Node* node) :_node(node){};

        Iterator operator--()
        {
            if (_node->l)
            {
                _node = _node->l;
                while (_node->r)
                    _node = _node->r;
                return *this;
            }

            while (_node->parent && _node == _node->parent->l)
                _node = _node->parent;
            _node = _node->parent;
            return *this;
        }

        bool operator==(const Iterator& other)
        { 
            return _node == other._node; 
        }
        bool operator!=(const Iterator& other)
        {
            return !(*this == other);
        }
    };

    bst() = default;
    bst(std::vector<T>& vals)
    {
        std::sort(vals.begin(), vals.end());
        batch_insert(vals, 0, vals.size());
    }

    void batch_insert(const std::vector<T>& sorted_vals, int l, int r)
    {
        if (l < r)
        {
            int mid_pos = (l + r) / 2;
            insert(sorted_vals[mid_pos]);
            batch_insert(sorted_vals, l, mid_pos);
            batch_insert(sorted_vals, mid_pos + 1, r);
        }
    }

    ~bst() { _destroy_node(root); }

    Iterator begin(){
        return Iterator(min());
    }
    Iterator end() {
        return Iterator(nullptr);
    }
    Iterator rbegin(){
        return Iterator(max());
    }
    Iterator rend(){
        return Iterator(nullptr);
    }

    bool is_valid() const 
    {
        if (!root) return true;
        auto min_val = min(root)->val;
        auto max_val = max(root)->val;

        return is_valid(root, min_val, max_val);
    }

    void insert(const T& val)
    {
        if (!root)
            root = new Node(val);
        else
            insert(root, val);
    }

    void remove(const T& val)
    {
        if (auto remove_node = find(val))
            remove(remove_node);
    }

    void print()
    {
        if (!root) return;
        print("", root, false);
    }

    void flip()
    {
        return flip(root);
    }

    void flip_iterative()
    {
        if (!root) return;
        std::stack<Node*> st{};
        st.push(root);
        while (!st.empty())
        {
            auto node = st.top();
            st.pop();
            std::swap(node->l, node->r);
            if (node->l) st.push(node->l);
            if (node->r) st.push(node->r);
        }
    }

    Node* min() const { return min(root);}
    Node* max() const { return max(root);}

private:
    bool is_valid(Node* node, const T& min, const T& max) const
    {
        if (!node) return true;
        return min <= node->val && node->val <= max
            && is_valid(node->l, min, node->val) 
            && is_valid(node->r, node->val, max);
    }

    void insert(Node* &node, const T& val)
    {
        if (val == node->val) return;
        Node* &branch = val < node->val ? node->l : node->r;
        if (branch)
            insert(branch, val);
        else
        {
            Node *newNode = new Node(val);
            newNode->parent = node;
            branch = newNode;
        }
    }

    void remove(Node* remove_node)
    {
        auto parent = remove_node->parent;
        if (remove_node->l && remove_node->r)
        {
            if (auto decr_node = max(remove_node->l))
            {
                std::swap(decr_node->val, remove_node->val);
                remove(decr_node);
                return;
            }
        }
        else if (remove_node->l || remove_node->r)
        {
            Node* &remove_node_ptr_ref = parent->l == remove_node ? parent->l : parent->r;
            Node* replacement_node = remove_node->l ? remove_node->l : remove_node->r;
            Node* temp_node = remove_node;

            remove_node_ptr_ref = replacement_node;
            replacement_node->parent = parent;
            delete temp_node;
        }
        else
        {
            Node* &remove_node_ptr_ref = parent->l == remove_node ? parent->l : parent->r;
            delete remove_node;
            remove_node_ptr_ref = nullptr;
        }
    }


    Node* find(const T& val)
    {
        return find(root, val);
    }
    Node* find(Node* node, const T& val)
    {
        if (!node) return nullptr;
        if (val < node->val) return find(node->l, val);
        if (val > node->val) return find(node->r, val);
        return node;
    }

    Node* min(Node* node) const
    {
        if (!node) return nullptr;
        return node->l ? min(node->l) : node;
    }
    Node* max(Node* node) const
    {
        if (!node) return nullptr;
        return node->r ? max(node->r) : node;
    }

    void print(const std::string& prefix, Node* node, bool isLeft) const
    {
        if (!node) return;

        std::string curr_prefix{};
        std::string next_prefix{};

        if (node != root)
        {
            bool has_nodes_below = isLeft && node->parent->r; // root is always right

            curr_prefix = std::string(has_nodes_below ? "╠═" : "╚═")
                + std::string(isLeft ? "L" : "R")
                + std::string("═══");
            next_prefix = has_nodes_below ? "║     " : "      ";
        }

        std::cout << prefix + curr_prefix << node->val << std::endl;

        print(prefix + next_prefix, node->l, true);
        print(prefix + next_prefix, node->r, false);
    }

    void flip(Node* node)
    {
        if (!node) return;
        std::swap(node->l, node->r);
        flip(node->l);
        flip(node->r);
    }

    void _destroy_node(Node* node)
    {
        if (!node) return;
        _destroy_node(node->l);
        _destroy_node(node->r);
        delete node;
    }

    bool is_left(Node* node) const
    {
        if (!node || !node->parent) return false;
        return node == node->parent->l;
    }

private:
    Node* root { nullptr };
};








// no parents
class BST
{
public:
    struct Node
    {
        int val;
        Node* l;
        Node* r;

        Node(int _val): val(_val){}
    };


public:
    ~BST()
    {
        destroy_node(root);
    }

    bool is_valid() const
    {
        return is_valid(root, INT_MIN, INT_MAX);
    } 

    int size() const 
    {
        return size(root);
    }

    void insert(int val)
    {
        if (root)
            insert(val, root);
        else
            root = new Node(val);
    }

    void remove(int val)
    {
        if (auto to_remove_ptr_ptr = find(root, val))
            remove(*to_remove_ptr_ptr);
    }

    bool contains(int val) const
    {
        return contains(val, root);
    }

    Node* find(int val)
    {
        if (auto node_ptr = find(root, val))
        {
            return *node_ptr;
        }
        return nullptr;
    }

    Node* min_node()
    {
        if (auto min_node = min_node_ptr(root))
            return *min_node;
        return nullptr;
    }

    Node* max_node()
    {
        if (auto max_node = max_node_ptr(root))
            return *max_node;
        return nullptr;
    }

    void print()
    {
        if (!root)
            return;

        std::cout << root->val << std::endl;
        print("", root->l, true);
        print("", root->r, false);
    }

private:
    void destroy_node(Node* node)
    {
        if (!node) return;
        destroy_node(node->l);
        destroy_node(node->r);
        delete node;
        node = nullptr;
    }

    bool is_valid(Node* node, int min, int max) const
    {
        if (!node) return true;
        if (node->val < min || node->val >= max) return false;
        return is_valid(node->l, min, node->val) && is_valid(node->r, node->val, max);
    }

    int size(const Node* root) const
    {
        if (!root) return 0;
        return 1 + size(root->l) + size(root->r);
    }

    void insert(int val, Node* &node)
    {
        if (!node)
            node = new Node(val);
        else
        {
            if (val < node->val)
                insert(val, node->l);
            else
                insert(val, node->r);
        }
    }

    void remove(Node* &to_remove)
    {
        if (!to_remove) return;

        if (to_remove->l && to_remove->r)
        {
            auto to_replace_node_ptr = max_node_ptr(to_remove->l);
            to_remove->val = (*to_replace_node_ptr)->val;
            remove(*to_replace_node_ptr);
        }
        else if (to_remove->l || to_remove->r)
        {
            auto to_remove_ptr = to_remove;
            to_remove = to_remove->l ? to_remove->l : to_remove->r;
            delete to_remove_ptr;
        }
        else
        {
            delete to_remove;
            to_remove = nullptr;
        }
    }

    bool contains(int val, Node* node) const
    {
        if (!node) return false;
        if (val < node->val) return contains(val, node->l);
        if (val > node->val) return contains(val, node->r);
        return true;
    }

    Node** find(Node* &node, int val)
    {
        if (!node) return nullptr;
        if (val < node->val) return find(node->l, val);
        if (val > node->val) return find(node->r, val);
        return &node;
    }

    Node** min_node_ptr(Node* &node) const
    {
        if (!node) return nullptr;
        if (node->l)
            return min_node_ptr(node->l);
        return &node;
    }

    Node** max_node_ptr(Node* &node) const
    {
        if (!node) return nullptr;
        if (node->r)
            return max_node_ptr(node->r);
        return &node;
    }

    void print(const std::string& prefix, Node* node, bool isLeft)
    {
        if (!node) return;
        std::cout << prefix << (isLeft ? "├──" : "└──" ) << node->val << std::endl;

        print(prefix + (isLeft ? "│   " : "    "), node->l, true);
        print(prefix + (isLeft ? "│   " : "    "), node->r, false);
    }

private:
    Node* root{nullptr};
};


