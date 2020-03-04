
#include <IceUtil/Monitor.h>

template<class T> class Queue : public IceUtil::Monitor<IceUtil::Mutex>
{
public:
    Queue() : _waitingReaders(0) {}

    void put(const T& item)
    {
        IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);
        _q.push_back(item);
        if(_waitingReaders)
        {
            notify();
        }
    }

    T get()
    {
        IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);
        while(_q.size() == 0)
        {
            try
            {
                ++_waitingReaders;
                wait();
                --_waitingReaders;
            }
            catch (...)
            {
                --_waitingReaders;
                throw;
            }
        }
        T item = _q.front();
        _q.pop_front();
        return item;
    }

private:
    list<T> _q;
    short _waitingReaders;
};
