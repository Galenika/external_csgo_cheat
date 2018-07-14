#pragma once

template< class t >
class c_singleton
{
public:
	c_singleton() = default;
	virtual ~c_singleton() = default;

	t operator()()
	{
		static T instance{};
		return instance;
	}
};