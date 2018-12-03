#pragma once

#include <map>

class RefManager
{
public:
    static std::map<void*, int> refRegistry;
};

template <typename T>
class MSmartPointer
{
public:
    MSmartPointer(void) = delete;
    MSmartPointer(T* pointer)
    {
        mPointer = pointer;
        ref(mPointer);
    };
    template <typename U>
    MSmartPointer(U* pointer)
    {
        mPointer = pointer;
        ref(mPointer);
    }
    MSmartPointer(const MSmartPointer& src)
    {
        mPointer = src.mPointer;
        ref(mPointer);
    };
    template <typename U>
    MSmartPointer(const MSmartPointer<U>& src)
    {
        mPointer = src.get();
        ref(mPointer);
    };
    ~MSmartPointer(void)
    {
        unref(mPointer);
    };
    MSmartPointer& operator=(T* pointer)
    {
        if (mPointer != pointer)
        {
            unref(mPointer);
            mPointer = pointer;
            ref(mPointer);
        }
        return (*this);
    }
    template <typename U>
    MSmartPointer& operator=(U* pointer)
    {
        if (mPointer != pointer)
        {
            unref(mPointer);
            mPointer = pointer;
            ref(mPointer);
        }
        return (*this);
    };
    MSmartPointer& operator=(const MSmartPointer& rhs)
    {
        if (this != &rhs)
        {
            unref(mPointer);
            mPointer = rhs.mPointer;
            ref(mPointer);
        }
        return (*this);
    };
    template <typename U>
    MSmartPointer& operator=(const MSmartPointer<U>& rhs)
    {
        if (this != &rhs)
        {
            unref(mPointer);
            mPointer = rhs.get();
            ref(mPointer);
        }
        return (*this);
    };
    T* operator->(void) const
    {
        return mPointer;
    };
    T* get(void) const
    {
        return mPointer;
    };
    int ref(void) const
    {
        auto it = RefManager::refRegistry.find(mPointer);
        if (it != std::end(RefManager::refRegistry))
        {
            return it->second;
        }
        return 0;
    };
protected:
    void ref(T* pointer)
    {
        if (pointer == nullptr)
        {
            return;
        }

        auto it = RefManager::refRegistry.find(pointer);
        if (it != std::end(RefManager::refRegistry))
        {
            it->second += 1;
        }
        else
        {
            RefManager::refRegistry.insert(std::make_pair(pointer, 1));
        }
    };
    void unref(T* pointer)
    {
        if (pointer == nullptr)
        {
            return;
        }

        auto it = RefManager::refRegistry.find(pointer);
        if (it != std::end(RefManager::refRegistry))
        {
            it->second -= 1;
            if (it->second < 1)
            {
                delete pointer;
                RefManager::refRegistry.erase(it);
            }
        }
    };
private:
    T* mPointer = nullptr;
};