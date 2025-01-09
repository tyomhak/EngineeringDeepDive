#include <iostream>
#include <limits.h>
#include <queue>

class BST
{
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

    void insert(int val)
    {
        if (root)
            insert(val, root);
        else
            root = new Node(val);
    }

    bool contains(int val) const
    {
        return contains(val, root);
    }

    Node* find(int val)
    {
        return find(root, val);
    }

    

    bool is_valid() const
    {
        return is_valid(root, INT_MIN, INT_MAX);
    }   

    void remove(int val)
    {
        if (!root) return;
        Node* parent_node = nullptr;

        while (parent_node)
        {
            if (parent_node->l && parent_node->l->val == val ||
                parent_node->r && parent_node->r->val == val)
                break;
            else
            {
                if (val < parent_node->val)
                    parent_node = parent_node->l;
                else
                    parent_node = parent_node->r;
            }
        }
        if (!parent_node)
            return;

        Node* to_remove = parent_node->l->val == val ? parent_node->l : parent_node->r;
        if (to_remove)
        {
            if (to_remove->l && to_remove->r)
            {

            }
            else if (!to_remove->l && !to_remove->r)
            {
                if (parent_node->l == to_remove)
                    parent_node->l = nullptr;
                else
                    parent_node->r = nullptr;

                delete to_remove;
            }
        }
    } 

private:
    void insert(int val, Node* node)
    {
        if (val < node->val)
        {
            if (node->l)
                return insert(val, node->l);
            node->l = new Node(val);
        }
        else
        {
            if (node->r)
                return insert(val, node->r);
            node->r = new Node(val);
        }
    }

    bool is_valid(Node* node, int min, int max) const
    {
        if (!node) return true;
        if (node->val < min || node->val >= max) return false;
        return is_valid(node->l, min, node->val) && is_valid(node->r, node->val, max);
    }

    bool contains(int val, Node* node) const
    {
        if (!node) return false;
        if (val < node->val) return contains(val, node->l);
        if (val > node->val) return contains(val, node->r);
        return true;
    }

    void destroy_node(Node* node)
    {
        if (!node) return;
        destroy_node(node->l);
        destroy_node(node->r);
        delete node;
        node = nullptr;
    }

    Node* find(Node* root, int val)
    {
        if (!root) return nullptr;
        if (val < root->val) return find(root->l, val);
        if (val > root->val) return find(root->r, val);
        return root;
    }

    Node* min_node(Node* start_node)
    {
        while (start_node && start_node->l)
            start_node = start_node->l;
        return start_node;
    }

    Node* max_node(Node* start_node)
    {
        while (start_node && start_node->r)
            start_node = start_node->r;
        return start_node;
    }

    void remove_node_2_subtree(Node* to_remove, Node* parent)
    {
        Node* replacement{nullptr};
        Node* replacement_parent{nullptr};

        if (to_remove->l)
        {

        }
        else
        {

        }

        
    }

    void remove_node_1_subtree(Node* to_remove, Node* parent)
    {
        if (!to_remove) return;
        if (to_remove->l || to_remove->r)
        {
            Node* to_replace = to_remove->l ? to_remove->l : to_remove->r;
            if (parent->l == to_remove)
                parent->l = to_replace;
            else
                parent->r = to_replace;
            delete to_remove;
        }
        
        if (parent->l == to_remove)
            delete parent->l;
        else
            delete parent->r;
    }

private:
    Node* root{nullptr};
};


