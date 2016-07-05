#pragma once

template<class SubClass>
class Singleton
{
public:
	static SubClass * instance()
	{
		if (!p)
			p = new SubClass();
		return p;
	}
protected:
	static SubClass *p;

	Singleton() {}
	~Singleton() { delete p; p = 0; }
};
template <class SubClass>
SubClass * Singleton<SubClass>::p = 0;