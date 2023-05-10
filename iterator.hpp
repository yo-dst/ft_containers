#ifndef _iterator_hpp_
#define _iterator_hpp_

#include <iostream>
#include <cstddef>

namespace ft {
	// ---- iterator tags ----
	typedef std::input_iterator_tag			input_iterator_tag;
	typedef std::output_iterator_tag		output_iterator_tag;
	typedef std::forward_iterator_tag		forward_iterator_tag;
	typedef std::bidirectional_iterator_tag	bidirectional_iterator_tag;
	typedef std::random_access_iterator_tag	random_access_iterator_tag;

	// ---- iterator_traits ----
	template <typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <typename T>
	struct iterator_traits<T *>
	{
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T *							pointer;
		typedef T &							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template <typename T>
	struct iterator_traits<T const *>
	{
		typedef ptrdiff_t					difference_type;
		typedef T const						value_type;
		typedef T const *					pointer;
		typedef T const &					reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	// ---- iterator ----
	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

	// ---- reverse iterator ----
	template <class Iterator>
	class reverse_iterator: public ft::iterator<typename iterator_traits<Iterator>::iterator_category,
                      						typename iterator_traits<Iterator>::value_type,
                      						typename iterator_traits<Iterator>::difference_type,
                      						typename iterator_traits<Iterator>::pointer,
                     						typename iterator_traits<Iterator>::reference>
	{
		public:
			// ---- member type(s) ----
			typedef Iterator                                            iterator_type;
			typedef typename iterator_traits<Iterator>::difference_type difference_type;
			typedef typename iterator_traits<Iterator>::reference       reference;
			typedef typename iterator_traits<Iterator>::pointer         pointer;

		private:
			iterator_type _curr;
		
		public:
			// ---- constructor(s) ----
			reverse_iterator(void) 														: _curr(iterator_type()) 	{}
			explicit reverse_iterator(iterator_type it) 								: _curr(it) 				{}
			template <class Iter> reverse_iterator(reverse_iterator<Iter> const & src) 	: _curr(src.base()) 		{}

			// ---- operator(s) ----
			reference			operator*(void) const 				{ iterator_type tmp = _curr; return *(--tmp); }				
			reverse_iterator 	operator+(difference_type n) const 	{ return reverse_iterator(_curr - n); }
			reverse_iterator & 	operator++() 						{ _curr--; return *this; }
			reverse_iterator 	operator++(int) 					{ reverse_iterator tmp(*this); _curr--; return tmp; }
			reverse_iterator & 	operator+=(difference_type n) 		{ _curr -= n; return *this; }
			reverse_iterator 	operator-(difference_type n) const 	{ return reverse_iterator(_curr + n); }
			reverse_iterator & 	operator--() 						{ _curr++; return *this; }
			reverse_iterator 	operator--(int) 					{ reverse_iterator tmp(*this); _curr++; return tmp; }
			reverse_iterator & 	operator-=(difference_type n) 		{ _curr += n; return *this; }
			pointer 			operator->(void) const 				{ return &(operator*()); }
			reference 			operator[](difference_type n) const { return *(*this + n); }

			operator reverse_iterator<iterator_type const>() const
			{ return reverse_iterator<iterator_type const>(_curr); }

			// ---- member function(s) ---- 
			iterator_type 	base(void) const { return _curr; }
	};


	template <class Iter>
	reverse_iterator<Iter>
	operator-(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& rhs)
	{ return reverse_iterator<Iter>(rhs.base() + n); }

	template <class Iter>
	reverse_iterator<Iter>
	operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& rhs)
	{ return reverse_iterator<Iter>(rhs.base() - n); }

	template <typename Iter1, typename Iter2>
	typename reverse_iterator<Iter1>::difference_type
	operator-(reverse_iterator<Iter1> const & lhs, reverse_iterator<Iter2> const & rhs)
	{ return rhs.base() - lhs.base(); }

	template <typename Iter1, typename Iter2>
	typename reverse_iterator<Iter1>::difference_type
	operator+(reverse_iterator<Iter1> const & lhs, reverse_iterator<Iter2> const & rhs)
	{ return lhs.base() + rhs.base(); }

	template <typename Iter1, typename Iter2>
	bool operator==(const reverse_iterator<Iter1> & lhs, const reverse_iterator<Iter2> & rhs)
	{ return (lhs.base() == rhs.base()); }

	template <typename Iter1, typename Iter2>
	bool operator!=(reverse_iterator<Iter1> const & lhs, reverse_iterator<Iter2> const & rhs)
	{ return !(lhs == rhs); }

	template <typename Iter1, typename Iter2>
	bool operator<(reverse_iterator<Iter1> const & lhs, reverse_iterator<Iter2> const & rhs)
	{ return (lhs.base() > rhs.base()); }

	template <typename Iter1, typename Iter2>
	bool operator<=(reverse_iterator<Iter1> const & lhs, reverse_iterator<Iter2> const & rhs)
	{ return (lhs == rhs || lhs < rhs); }

	template <typename Iter1, typename Iter2>
	bool operator>(reverse_iterator<Iter1> const & lhs, reverse_iterator<Iter2> const & rhs)
	{ return !(lhs <= rhs); }

	template <typename Iter1, typename Iter2>
	bool operator>=(reverse_iterator<Iter1> const & lhs, reverse_iterator<Iter2> const & rhs)
	{ return !(lhs < rhs); }

	// ---- random_access_iterator ----
	template <typename T>
	class random_access_iterator
		: public ft::iterator<random_access_iterator_tag, T>
	{
		public:
			// ---- member type(s) ----
			typedef typename iterator_traits<T>::value_type			value_type;
			typedef typename iterator_traits<T>::difference_type 	difference_type;
			typedef typename iterator_traits<T>::reference       	reference;
			typedef typename iterator_traits<T>::pointer         	pointer;

		private:
			pointer _curr;

		public:
			// ---- constructor(s) ----
			random_access_iterator(void) : _curr(nullptr) {}
			random_access_iterator(pointer ptr) : _curr(ptr) {}
			random_access_iterator(random_access_iterator const & src) : _curr(src.base()) {}

			// ---- operator(s) ----
			reference					operator*(void) const 				{ return *_curr; }				
			random_access_iterator 		operator+(difference_type n) const 	{ return random_access_iterator(_curr + n); }
			random_access_iterator & 	operator++() 						{ _curr++; return *this; }
			random_access_iterator 		operator++(int) 					{ random_access_iterator tmp(*this); _curr++; return tmp; }
			random_access_iterator & 	operator+=(difference_type n) 		{ _curr += n; return *this; }
			random_access_iterator 		operator-(difference_type n) const 	{ return random_access_iterator(_curr - n); }
			random_access_iterator & 	operator--() 						{ _curr--; return *this; }
			random_access_iterator 		operator--(int) 					{ random_access_iterator tmp(*this); _curr--; return tmp; }
			random_access_iterator & 	operator-=(difference_type n) 		{ _curr -= n; return *this; }
			pointer 					operator->(void) const 				{ return _curr; }
			reference 					operator[](difference_type n) const { return *(*this + n); }

			operator random_access_iterator<value_type const *>() const
			{ return random_access_iterator<value_type const *>(_curr); }

			// ---- member function(s) ----
			pointer	base(void) const { return _curr; }
	};

	template <class Iter>
	random_access_iterator<Iter>
	operator-(typename random_access_iterator<Iter>::difference_type n, const random_access_iterator<Iter>& rhs)
	{ return random_access_iterator<Iter>(rhs.base() - n); }

	template <class Iter>
	random_access_iterator<Iter>
	operator+(typename random_access_iterator<Iter>::difference_type n, const random_access_iterator<Iter>& rhs)
	{ return random_access_iterator<Iter>(rhs.base() + n); }

	template <typename Iter1, typename Iter2>
	typename random_access_iterator<Iter1>::difference_type
	operator-(random_access_iterator<Iter1> const & lhs, random_access_iterator<Iter2> const & rhs)
	{ return lhs.base() - rhs.base(); }

	template <typename Iter1, typename Iter2>
	typename random_access_iterator<Iter1>::difference_type
	operator+(random_access_iterator<Iter1> const & lhs, random_access_iterator<Iter2> const & rhs)
	{ return lhs.base() + rhs.base(); }

	template <typename Iter1, typename Iter2>
	bool operator==(const random_access_iterator<Iter1>& lhs, const random_access_iterator<Iter2>& rhs)
	{ return (lhs.base() == rhs.base()); }

	template <typename Iter1, typename Iter2>
	bool operator!=(random_access_iterator<Iter1> const & lhs, random_access_iterator<Iter2> const & rhs)
	{ return (lhs.base() != rhs.base()); }

	template <typename Iter1, typename Iter2>
	bool operator<(random_access_iterator<Iter1> const & lhs, random_access_iterator<Iter2> const & rhs)
	{ return (lhs.base() < rhs.base()); }

	template <typename Iter1, typename Iter2>
	bool operator<=(random_access_iterator<Iter1> const & lhs, random_access_iterator<Iter2> const & rhs)
	{ return (lhs.base() <= rhs.base()); }

	template <typename Iter1, typename Iter2>
	bool operator>(random_access_iterator<Iter1> const & lhs, random_access_iterator<Iter2> const & rhs)
	{ return (lhs.base() > rhs.base()); }

	template <typename Iter1, typename Iter2>
	bool operator>=(random_access_iterator<Iter1> const & lhs, random_access_iterator<Iter2> const & rhs)
	{ return (lhs.base() >= rhs.base()); }


	template <typename Iterator>
	static typename iterator_traits<Iterator>::difference_type
	_distance(Iterator first, Iterator last, input_iterator_tag)
	{
		typename iterator_traits<Iterator>::difference_type n = 0;
		for (; first != last; first++)
			n++;
		return n;
	}

	template <typename Iterator>
	static typename iterator_traits<Iterator>::difference_type
	_distance(Iterator first, Iterator last, random_access_iterator_tag)
	{
		return last - first;
	}

	template <typename Iterator>
	typename iterator_traits<Iterator>::difference_type
	distance(Iterator first, Iterator last)
	{
		return _distance(first, last, typename iterator_traits<Iterator>::iterator_category());
	}
}

#endif