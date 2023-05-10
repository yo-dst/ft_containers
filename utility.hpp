#ifndef _utility_hpp_
#define _utility_hpp_

namespace ft
{
	template <class T>
	struct remove_const
	{
		typedef T type;
	};

	template <class T>
	struct remove_const<T const>
	{
		typedef T type;
	};


	template <class T1, class T2>
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

		pair(void) 												: first(first_type()), second(second_type()) 	{}
		pair(const first_type & a, const second_type & b) 		: first(a), second(b) 							{} 
		template<class U, class V> pair(pair<U, V> const & pr) 	: first(pr.first), second(pr.second) 			{}

		pair &	operator=(pair const & pr)
		{
			first = pr.first;
			second = pr.second;
			return *this;
		}

		friend std::ostream & operator<<(std::ostream & o, pair p) {
			o << p.first << ":" << p.second;
			return o;
		}
	};

	template <class T1, class T2>
	bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
	bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs==rhs); }

	template <class T1, class T2>
	bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
	bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs<lhs); }

	template <class T1, class T2>
	bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return rhs<lhs; }

	template <class T1, class T2>
	bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs<rhs); }

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{ return pair<T1, T2>(x, y); }
}

#endif