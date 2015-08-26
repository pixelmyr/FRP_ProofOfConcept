#ifndef WATCHED_PTR_H
#define WATCHED_PTR_H

#include <vector>
#include <functional>

template <typename T>
class WatchedPtr
{
public:
	WatchedPtr()
		: _ptr(nullptr),
		_dirty(false)
	{
		_listeners = new std::vector<std::function<void(T *)> *>();
	}

	WatchedPtr(T *ptr)
		: _ptr(ptr),
		_dirty(false)
	{
		_listeners = new std::vector<std::function<void(T *)> *>();
	}

	WatchedPtr(const WatchedPtr &other)
		: _dirty(other._dirty),
		_listeners(other._listeners),
		_ptr(other._ptr)
	{
	}

	~WatchedPtr()
	{
		if (_dirty)
			_notify();
	}

	void Reset(T *ptr)
	{
		_ptr = ptr;

		_notify();
	}

	operator T*()
	{
		_dirty = true;

		return _ptr;
	}

	operator const T*()
	{
		return _ptr;
	}

	void AddListener(std::function<void(T *)> *func)
	{
		_listeners->push_back(func);
	}

private:
	T *_ptr;

	bool _dirty;

	std::vector<std::function<void(T *)> *> *_listeners;

	void _notify()
	{
		for (auto itr = _listeners->begin(), itrEnd = _listeners->end(); itr != itrEnd; ++itr)
		{
			(*(*itr))(_ptr);
		}
	}
};

#endif