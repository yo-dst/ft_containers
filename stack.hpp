#ifndef _stack_hpp_
#define _stack_hpp_

#include "vector.hpp"

namespace ft
{
	template <typename T, typename Container = ft::vector<T> >
	class stack
	{
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

		protected:
			container_type c;

		public:
			explicit stack(const container_type & ctnr = container_type())
				: c(ctnr)
			{}

			~stack() {}

			bool				empty(void) const 				{ return c.empty(); }
			size_type 			size(void) const 				{ return c.size(); }
			value_type & 		top(void)						{ return c.back(); }
			value_type const & 	top(void) const 				{ return c.back(); }
			void 				push(const value_type & val) 	{ c.push_back(val); }
			void 				pop(void) 						{ c.pop_back(); }

		private:
			template <typename _T, typename _C>
    		friend bool operator==(const stack<_T, _C> & x, const stack<_T, _C> & y);

			template <typename _T, typename _C>
			friend bool operator<(const stack<_T, _C> & x, const stack<_T, _C> & y);
	};

	template <typename T, typename Container>
	bool operator==(const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs )
	{
		return lhs.c == rhs.c;
	}
 	
	template <typename T, typename Container>
	bool operator!=(const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs )
	{
		return !(lhs == rhs);
	}

	template <typename T, typename Container>
	bool operator<( const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs )
	{
		return (lhs.c < rhs.c);
	}

	template <typename T, typename Container>
	bool operator<=( const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs )
	{
		return (lhs == rhs || lhs < rhs);
	}

	template <typename T, typename Container>
	bool operator>( const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs )
	{
		return !(lhs <= rhs);
	}

	template <typename T, typename Container>
	bool operator>=( const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs )
	{
		return !(lhs < rhs);
	}
}

#endif