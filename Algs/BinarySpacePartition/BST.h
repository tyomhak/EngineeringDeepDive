
#include <vector>
#include <memory>
#include <utility>

namespace bst
{

class SplitPlane;

class Object
{
public:
    virtual ~Object() = default;

    virtual auto getSplitPlane() const -> const SplitPlane& = 0;
    virtual auto split(const SplitPlane& splitPlane) const -> std::pair<Object, Object> = 0;
};

class SplitPlane
{
public:
    virtual ~SplitPlane() = default;


    virtual auto split(const Object& object) const -> std::pair<Object, Object> = 0;
    virtual auto isInFront(const Object& object) const -> bool = 0;
    virtual auto isInBack(const Object& object) const -> bool = 0;
};




class Object2D : public Object
{
public:

    virtual auto getSplitPlane() const -> const SplitPlane& override;

};

class SplitPlane2D : public SplitPlane
{
public:
    virtual auto split(const Object& object) const -> std::pair<Object, Object> override
    {
        return object.split(*this);
    }
};





class bst
{
    struct node
    {
        node(const Object* obj) : object(obj) {};
    
        const Object* object{nullptr};

        std::unique_ptr<node> l{nullptr};
        std::unique_ptr<node> r{nullptr};
    };

public:

    void insert(const Object& object)
    {
        _objects.push_back(object);
        _insert(&(*_objects.rbegin()));
    }

private:
    void _insert(const Object* obj)
    {
        if (obj)
            _insert(_head, obj);
    }

    void _insert(std::unique_ptr<node>& currentNode, const Object* obj)
    {
        if (!currentNode)
            return currentNode.reset(new node(obj));

        auto splitPlane = currentNode->object->getSplitPlane();
        if (splitPlane.isInFront(*obj))
            _insert(currentNode->r, obj);
        else if (splitPlane.isInBack(*obj))
            _insert(currentNode->l, obj);
        else
        {
            auto [sub_obj_1, sub_obj_2] = splitPlane.split(*obj);
            insert(sub_obj_1);
            insert(sub_obj_2);
        }
    }

private:
    std::vector<Object> _objects{};
    std::unique_ptr<node> _head{nullptr};
};





}