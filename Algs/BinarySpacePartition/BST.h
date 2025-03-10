#pragma once

#include <vector>
#include <memory>
#include <utility>
#include <functional>

#include "Object.h"
#include "SplitPlane.h"

namespace bst
{


class bst
{
    struct node
    {
        node(const node* parent, const Object* obj) 
            : p(parent)
            , object(obj) 
        {};
    
        const Object* object{nullptr};

        const node* p{nullptr};
        std::unique_ptr<node> l{nullptr};
        std::unique_ptr<node> r{nullptr};
    };

public:

    void insert(const Object& object)
    {
        _objects.push_back(std::make_unique<Object>(object));
        _insert(_objects.rbegin()->get());
    }

    void for_all_inorder(std::function<void(const Object&)> action)
    {
        return _inorder_action(_head, action);
    }

    void for_all_inorder_reverse(std::function<void(const Object&)> action)
    {
        return _reverse_inorder_action(_head, action);
    }

    void for_all_preorder(std::function<void(const Object&)> action)
    {
        return _preorder_action(_head, action);
    }

private:
    void _insert(const Object* obj)
    {
        if (!obj) return;
        _insert(_head, nullptr, obj);
    }

    void _insert(std::unique_ptr<node>& current_node, const node* parent_node, const Object* obj)
    {
        if (!current_node)
            current_node.reset(new node(parent_node, obj));

        std::unique_ptr<SplitPlane> splitPlane(current_node->object->createSplitPlane());
        if (splitPlane->isInFront(*obj))
            _insert(current_node->r, current_node.get(), obj);
        else if (splitPlane->isInBack(*obj))
            _insert(current_node->l, current_node.get(), obj);
        else
        {
            auto [sub_obj_1, sub_obj_2] = splitPlane->split(*obj);
            insert(*sub_obj_1);
            insert(*sub_obj_2);
            delete sub_obj_1;
            delete sub_obj_2;
        }
    }

    void _inorder_action(std::unique_ptr<node>& curr_node, std::function<void(const Object&)> action)
    {
        if (!curr_node) return;
        _inorder_action(curr_node->l, action);
        action(*curr_node->object);
        _inorder_action(curr_node->r, action);
    }

    void _reverse_inorder_action(std::unique_ptr<node>& curr_node, std::function<void(const Object&)> action)
    {
        if (!curr_node) return;
        _reverse_inorder_action(curr_node->r, action);
        action(*curr_node->object);
        _reverse_inorder_action(curr_node->l, action);
    }

    void _preorder_action(std::unique_ptr<node>& curr_node, std::function<void(const Object&)> action)
    {
        if (!curr_node) return;
        action(*curr_node->object);
        _preorder_action(curr_node->r, action);
        _preorder_action(curr_node->l, action);
    }

private:
    std::vector<std::unique_ptr<Object>> _objects{};
    std::unique_ptr<node> _head{nullptr};
};

}