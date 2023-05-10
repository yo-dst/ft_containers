#ifndef _vector_hpp_
#define _vector_hpp_

#include <iostream>
#include <exception>
#include <algorithm>
#include "type_traits.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"

namespace ft
{
	template <typename T, typename Allocator = std::allocator<T> >
	class vector
	{
		public:
			// ---- member type(s) ----
			typedef Allocator										allocator_type;
			typedef typename allocator_type::value_type				value_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename allocator_type::size_type				size_type;
			typedef	typename allocator_type::difference_type		difference_type;
			typedef	ft::random_access_iterator<pointer>				iterator;
			typedef ft::random_access_iterator<const_pointer>		const_iterator;
			typedef	ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		private:
			allocator_type	_alloc;
			pointer 		_data;
			size_type		_capacity;
			size_type		_size;

		public:
			// ---- constructor(s) ----
			explicit vector(allocator_type const & alloc = allocator_type())
				: _alloc(alloc), _data(nullptr), _capacity(0), _size(0)
			{}

			explicit vector(size_type n, value_type const & val = value_type(), allocator_type const & alloc = allocator_type())
				: _alloc(alloc), _data(nullptr), _capacity(0), _size(0)
			{
				_data = _allocate(n);
				_capacity = n;
				_construct_at_end(n, val);
			}

			template <typename InputIterator>
			vector(typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type first,
				InputIterator last,
				const allocator_type & alloc = allocator_type())
				: _alloc(alloc), _data(nullptr), _capacity(0), _size(0)
			{
				difference_type n = ft::distance(first, last);
				_data = _allocate(n);
				_capacity = n;
				_construct_at_end(first, last);
			}
			
			vector(vector const & src)
				: _alloc(src._alloc), _data(nullptr), _capacity(0), _size(0)
			{
				_data = _allocate(src._capacity);
				_capacity = src._capacity;
				_construct_at_end(src.begin(), src.end());
			}

			// ---- destructor ----
			~vector(void)
			{
				clear();
				_deallocate(_data, _capacity);
				_data = nullptr;
				_capacity = 0;
			}

			// ---- operator(s) ----
			vector & operator=(vector const & rhs)
			{
				clear();
				if (_capacity < rhs._size)
					_realloc(rhs._capacity);
				_construct_at_end(rhs.begin(), rhs.end());
				return *this;
			}

			reference 		operator[](size_type n) 		{ return *(_data + n); }
			const_reference operator[](size_type n) const 	{ return *(_data + n); }

			// ---- member function(s) ----
            iterator		begin(void)			{ return iterator(_data); }
			const_iterator	begin(void) const	{ return const_iterator(_data); }
			iterator		end(void)			{ return iterator(_data + _size); }
			const_iterator	end(void) const		{ return const_iterator(_data + _size); }

			reverse_iterator		rbegin(void)		{ return reverse_iterator(end()); }
			const_reverse_iterator	rbegin(void) const	{ return const_reverse_iterator(end()); }
			reverse_iterator		rend(void)			{ return reverse_iterator(begin()); }
			const_reverse_iterator	rend(void) const	{ return const_reverse_iterator(begin()); }

			size_type		size(void) const			{ return _size; }
			size_type		max_size(void) const		{ return _alloc.max_size(); }
			size_type		capacity(void) const		{ return _capacity; }
			allocator_type	get_allocator(void) const	{ return _alloc; }

			reference		front(void)			{ return *_data; }
			const_reference	front(void) const	{ return *_data; }
			reference		back(void)			{ return *(_data + _size - 1); }
			const_reference	back(void) const	{ return *(_data + _size - 1); }

			void	clear(void) { _destroy_at_end(_size); }

			bool	empty(void) const { return (_size == 0 ? true : false); }

			reference at(size_type n)
			{
				if (n >= _size)
					throw std::out_of_range("vector");
				else
					return *(_data + n);
			}

			const_reference at(size_type n) const
			{
				if (n >= _size)
					throw std::out_of_range("vector");
				else
					return *(_data + n);
			}

			template <class InputIterator>
			typename enable_if<!is_integral<InputIterator>::value, void>::type
			assign(InputIterator first, InputIterator last)
			{
				clear();
				size_type newSize = ft::distance(first, last);
				if (newSize > _capacity)
					_realloc(newSize);
				_construct_at_end(first, last);
			}

			void assign(size_type n, const_reference val)
			{
				clear();
                if (n > _capacity)
                    _realloc(n);
                _construct_at_end(n, val);	
			}

			void push_back(const_reference val)
			{
				if (_size == _capacity)
					_grow(_size + 1);
				_construct_at_end(1, val);
			}

			void pop_back(void)
			{
				if (_size != 0)
					_destroy_at_end(1);
			}

			iterator insert(iterator position, const_reference val)
			{
				difference_type offset = ft::distance(begin(), position); 
				if (_size + 1 > _capacity)
				{
					_grow(_size + 1);
					position = begin() + offset;
				}
				vector tmp;
				tmp.reserve(_capacity);
				tmp._construct_at_end(begin(), position);
				tmp._construct_at_end(1, val);
				tmp._construct_at_end(position, end());
				this->swap(tmp);
				position = begin() + offset;
				return position;
			}

			void insert(iterator position, size_type n, const_reference val)
			{
				if (_size + n > _capacity)
				{
					difference_type offset = ft::distance(begin(), position); 
					_grow(_size + n);
					position = begin() + offset;
				}
				vector tmp;
				tmp.reserve(_capacity);
				tmp._construct_at_end(begin(), position);
				tmp._construct_at_end(n, val);
				tmp._construct_at_end(position, end());
				this->swap(tmp);
			}

			template <class InputIterator>
            typename enable_if<!is_integral<InputIterator>::value, void>::type
    		insert(iterator position, InputIterator first, InputIterator last)
			{
				difference_type n = ft::distance(first, last);
				if (_size + n > _capacity)
				{
					difference_type offset = ft::distance(begin(), position); 
					_grow(_size + n);
					position = begin() + offset;
				}
				vector tmp;
				tmp.reserve(_capacity);
				tmp._construct_at_end(begin(), position);
				tmp._construct_at_end(first, last);
				tmp._construct_at_end(position, end());
				this->swap(tmp);
			}

			iterator erase(iterator position)
			{	
				difference_type offset = ft::distance(begin(), position);
				vector tmp;
				tmp.reserve(_capacity);
				tmp._construct_at_end(begin(), position);
				tmp._construct_at_end(position + 1, end());
				this->swap(tmp);
				position = begin() + offset;
				return position;
			}

			iterator erase(iterator first, iterator last)
			{
				difference_type offset = ft::distance(begin(), first);
				vector tmp;
				tmp.reserve(_capacity);
				tmp._construct_at_end(begin(), first);
				tmp._construct_at_end(last, end());
				this->swap(tmp);
				return iterator(begin() + offset);
			}

			void swap(vector & x)
			{
				std::swap(_data, x._data);
				std::swap(_capacity, x._capacity);
				std::swap(_size, x._size);
				std::swap(_alloc, x._alloc);
			}

			void resize(size_type n, value_type val = value_type())
			{
				if (n == _size)
					return ;
				if (n < _size)
					_destroy_at_end(_size - n);
				else
				{
					if (n > _capacity)
						_grow(n);
					_construct_at_end(n - _size, val);
				}
			}
			
			void reserve(size_type n)
			{
				if (n <= _capacity)
					return ;
				if (n > max_size())
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				else
					_realloc(n);
			}

		private:
			pointer _allocate(size_type n) 							{ return _alloc.allocate(n); }
			void	_deallocate(pointer ptr, size_type n)			{ _alloc.deallocate(ptr, n); }
			void	_construct(pointer ptr, const_reference val) 	{ _alloc.construct(ptr, val); }
			void	_destroy(pointer ptr) 							{ _alloc.destroy(ptr); }

			template <typename InputIterator>
			typename enable_if<!is_integral<InputIterator>::value, void>::type
            _construct_at_end(InputIterator first, InputIterator last)
			{
				pointer ptr = _data + _size;
				_size += ft::distance(first, last);
				for (; first != last; first++)
					_construct(ptr++, *first);
			}

			void _construct_at_end(size_type n, const_reference val)
			{
				pointer ptr = _data + _size;
				for (size_type i = 0; i < n; i++)
					_construct(ptr++, val);
				_size += n;
			}

			void _destroy_at_end(size_type n)
			{
				pointer ptr = _data + _size;
				for (size_type i = 0; i < n; i++)
					_destroy(--ptr);
				_size -= n;
			}

			void _realloc(size_type newCapacity)
			{
				size_type newSize = (_size < newCapacity ? _size : newCapacity);
				pointer newData = _allocate(newCapacity);
				for (size_type i = 0; i < newSize; i++)
					newData[i] = _data[i];
				clear();
				_deallocate(_data, _capacity);
				_data = newData;
				_size = newSize;
				_capacity = newCapacity;
			}

			void _grow(size_type minCapacityRequired)
			{
				_realloc(minCapacityRequired > _capacity * 2 ? minCapacityRequired : _capacity * 2);
			}

			// ---- friend(s) ----
			template <typename _T, typename _Allocator>
			friend std::ostream & operator<<(std::ostream &, vector<_T, _Allocator> const &);
	};

	// ---- non-member function(s) ----
	template <typename T, typename Allocator>
	bool operator==(vector<T, Allocator> const & lhs, vector<T, Allocator> const & rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <typename T, typename Allocator>
	bool operator!=(ft::vector<T, Allocator> const & lhs, ft::vector<T, Allocator> const & rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, typename Allocator>
	bool operator<(ft::vector<T, Allocator> const & lhs, ft::vector<T, Allocator> const & rhs)
	{
		return (lhs != rhs && ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <typename T, typename Allocator>
	bool operator>(ft::vector<T, Allocator> const & lhs, ft::vector<T, Allocator> const & rhs)
	{
		return (rhs < lhs);
	}

	template <typename T, typename Allocator>
	bool operator<=(ft::vector<T, Allocator> const & lhs, ft::vector<T, Allocator> const & rhs)
	{
		return !(lhs > rhs);
	}

	template <typename T, typename Allocator>
	bool operator>=(ft::vector<T, Allocator> const & lhs, ft::vector<T, Allocator> const & rhs)
	{
		return !(lhs < rhs);
	}

	template <typename T, typename Allocator>
	void swap(ft::vector<T, Allocator> & x, ft::vector<T, Allocator> & y)
	{
		x.swap(y);
	}

	template <typename _T, typename _Allocator>
	std::ostream & operator<<(std::ostream & ostrm, ft::vector<_T, _Allocator> const & rhs)
	{
	std::cout << "capacity:\t" << rhs.capacity() << std::endl;
	std::cout << "size:\t\t" << rhs.size() << std::endl;
	std::cout << "data: ";
	typename ft::vector<_T, _Allocator>::const_iterator it(rhs.begin());
	typename ft::vector<_T, _Allocator>::const_iterator end(rhs.end());
	for (; it != end; it++)
		std::cout << *it << " ";
	std::cout << std::endl << "--------" << std::endl;
	return ostrm;
	}
}

#endif