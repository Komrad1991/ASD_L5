#pragma once
#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>

template <
    typename T,
    typename Cont = std::vector<T>,
    typename Comp = std::less<T>
>
class myQueue
{
    Comp myComp;
    Cont myCont;
public:
    myQueue(Cont c = Cont(), Comp cmp = Comp()) :myComp(cmp), myCont(c)
    {
        std::sort(myCont.begin(), myCont.end(), myComp);
    }

    void insert(T elem)
    {
        myCont.insert(std::upper_bound(myCont.begin(), myCont.end(), elem, myComp),elem);
    }

    T top()
    {
        return myCont.back();
    }

    Cont container()
    {
        return myCont;
    }

    void pop()
    {
        myCont.pop_back();
    }

    myQueue concat(const myQueue& other)
    {
        Cont shared(myCont);
        shared.insert(shared.end(), other.begin(), other.end());
        //std::sort(shared.begin(), shared.end(), myComp);
        return myQueue(shared);
    }

    template <
        typename T,
        typename Cont = std::vector<T>,
        typename Comp = std::less<T>
    >
    friend std::ostream& operator<<(std::ostream& os, const myQueue& q)
    {
        for (const auto& x : q.container())
        {
            os << x << " ";
        }
        os << "\n";
        return os;
    }
};

template <
    typename T,
    typename Cont = std::vector<T>,
    typename Comp = std::less<T>
>
class myBinQueue
{
    Comp myComp;
    Cont myCont;
public:
    myBinQueue(Cont c = Cont(), Comp cmp = Comp()) :myComp(cmp), myCont(c)
    { 
            for (int i = myCont.size() - 1; i >= 0; i--)
            {
                sift_down(i);
            }
    }

    void insert(T elem)
    {
        myCont.push_back(elem);
        sift_up(myCont.size()-1);
    }

    T top()
    {
        return myCont.front();
    }

    Cont container()
    {
        return myCont;
    }

    void pop()
    {
        if (myCont.empty()) return;
        myCont[0] = myCont.back();
        myCont.pop_back();
        if (!myCont.empty()) {
            sift_down(0);
        }
    }

    myBinQueue concat(const myBinQueue& other)
    {
        Cont shared(myCont);
        shared.insert(shared.end(), other.begin(), other.end());
        //std::sort(shared.begin(), shared.end(), myComp);
        return myBinQueue(shared);
    }

    template <
        typename T,
        typename Cont = std::vector<T>,
        typename Comp = std::less<T>
    >
    friend std::ostream& operator<<(std::ostream& os, const myBinQueue& q)
    {
        for (const auto& x : q.container())
        {
            os << x << " ";
        }
        os << "\n";
        return os;
    }
private:
    size_t left(size_t ind)
    {
        return 2 * ind + 1;
    }
    size_t right(size_t ind)
    {
        return 2 * ind + 2;
    }
    size_t parent(size_t ind)
    {
        return (ind - 1) / 2;
    }
    void sift_down(size_t ind)
    {
        auto largest = ind;
        if (left(ind) < myCont.size() && myComp(myCont[largest], myCont[left(ind)]))
        {
            largest = left(ind);
        }
        if (right(ind) < myCont.size() && myComp(myCont[largest], myCont[right(ind)]))
        {
            largest = right(ind);
        }
        if (largest != ind)
        {
            std::swap(myCont[ind], myCont[largest]);
            sift_down(largest);
        }
    }
    void sift_up(size_t ind)
    {
        while (ind > 0 && myComp(myCont[parent(ind)], myCont[ind]))
        {
            std::swap(myCont[parent(ind)], myCont[ind]);
            ind = parent(ind);
        }
    }
};