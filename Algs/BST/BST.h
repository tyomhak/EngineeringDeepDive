#include <iostream>
#include <limits.h>
#include <queue>

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

    Node** find(Node* &root, int val)
    {
        if (!root) return nullptr;
        if (val < root->val) return find(root->l, val);
        if (val > root->val) return find(root->r, val);
        return &root;
    }

    Node** min_node_ptr(Node* &node)
    {
        if (!node) return nullptr;
        while (node->l)
            node = node->l;
        return &node;
    }

    Node** max_node_ptr(Node* &node)
    {
        if (!node) return nullptr;
        while (node->r)
            node = node->r;
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


