
#ifndef __SYMBOID_SDK_BASICS_LIST_H__
#define __SYMBOID_SDK_BASICS_LIST_H__

namespace Sy {

/// Concept = link to other element of same type.

template <class Element>
struct DefaultElementTraits
{
    typedef Element* ElementPtr;
    static void release(ElementPtr element) { delete element; }
};

/// Concept = single linked list scheme.
template <class Element, template <class> class ElementTraits = DefaultElementTraits>
class List : protected ElementTraits<Element>
{
protected:
    typedef typename ElementTraits<Element>::ElementPtr ElementPtr;

public:
    class Node
    {
    protected:
        Node() : mPrev(nullptr), mNext(nullptr) {}
        virtual ~Node() {}
    public:
        ElementPtr mPrev;
        ElementPtr mNext;
    };

public:
    List()
        : mHead(nullptr)
        , mTail(nullptr)
    {
    }
    virtual ~List() {}

private:
    ElementPtr mHead;
    ElementPtr mTail;

public:
    const ElementPtr first() const { return mHead; }
    ElementPtr first() { return mHead; }
    const ElementPtr last() const { return mTail; }
    ElementPtr last() { return mTail; }
    bool isEmpty() const { return mHead == nullptr; }

public:
    void pushFront(ElementPtr newElement)
    {
        if (newElement != nullptr)
        {
            // new element's succeeding will be the current head
            newElement->mNext = mHead;
            // new head will be th new element
            mHead = newElement;
            // if list was empty ...
            if (mHead->mNext == nullptr)
            {
                // ... tail must be set
                mTail = newElement;
            }
        }
    }

    ElementPtr popFront()
    {
        // popped element at front is the head
        ElementPtr poppedElement = mHead;
        // head must set to its succeeding element
        if (mHead != nullptr)
        {
            mHead = mHead->mNext;
        }
        // if list is becoming empty ...
        if (mHead == nullptr)
        {
            // ... tail must also be set to null
            mTail = nullptr;
        }
        return poppedElement;
    }

    void pushBack(ElementPtr newElement)
    {
        if (newElement != nullptr)
        {
            if (mTail != nullptr)
            {
                mTail->mNext = newElement;
                newElement->mNext = nullptr;
                mTail = newElement;
            }
            else
            {
                pushFront(newElement);
                newElement->mNext = nullptr;
            }
        }
    }

    void revert()
    {
        ElementPtr prevElement = nullptr;
        ElementPtr element = mHead;
        while (element != nullptr)
        {
            ElementPtr nextElement = element->mNext;
            element->mNext = prevElement;
            prevElement = element;
            element = nextElement;
        }
        mTail = mHead;
        mHead = prevElement;
    }

public:
    void deleteElements()
    {
        /*
        ElementPtr element = mHead;
        while (element != nullptr)
        {
            ElementPtr nextElement = element->mNext;
            PtrTraits<Element>::release(element);
            element = nextElement;
        }
        */
        while (!isEmpty())
        {
            ElementPtr element = popFront();
            ElementTraits<Element>::release(element);
        }
        mHead = nullptr;
        mTail = nullptr;
    }
    bool deleteElement(ElementPtr element)
    {
        bool success = false;
        if (element != nullptr)
        {
            ElementPtr prevElement = nullptr;
            ElementPtr it = mHead;
            while (it != nullptr && prevElement == nullptr)
            {
                if (it->mNext == element)
                {
                    prevElement = it;
                }
                it = it->mNext;
            }
            if (prevElement != nullptr)
            {
                prevElement->mNext = element->mNext;
                if (prevElement->mNext == nullptr)
                {
                    mTail = prevElement;
                }
                ElementTraits<Element>::release(element);
                success = true;
            }
            else if (mHead == element)
            {
                mHead = mHead->mNext;
                if (mHead == nullptr || mHead->mNext == nullptr)
                {
                    mTail = mHead;
                }
                ElementTraits<Element>::release(element);
                success = true;
            }
        }
        return success;
    }
};

} // namespace Sy

#define sy_list_for(iterator,list) \
    for (auto iterator = (list).first(); iterator != nullptr; iterator = iterator->mNext)

#define sy_list_for_cond(iterator,list,condition) \
    for (auto iterator = (list).first(); iterator != nullptr && (condition); iterator = iterator->mNext)

#endif // __SYMBOID_SDK_BASICS_LIST_H__
