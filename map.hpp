#ifndef _map_hpp_
#define _map_hpp_

#include <functional> // * for std::binary_function
#include "utility.hpp"
#include "tree.hpp"

namespace ft
{
	template <
		typename Key,
        typename T,
        typename Compare = std::less<Key>,
        typename Alloc = std::allocator<ft::pair<Key const, T> >
    >
	class map
	{
		public:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<key_type const, mapped_type> 		value_type;
			typedef Compare										key_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference; 
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef size_t										size_type;
			typedef ptrdiff_t									difference_type;

		public:
			class value_compare
				: public std::binary_function<value_type, value_type, bool>
			{
				friend class map;
				protected:
					key_compare comp;

					value_compare(key_compare c)
						: comp(c)
					{}

				public:
					bool operator()(const value_type & x, const value_type & y) const
					{
						return comp(x.first, y.first);
					}
			};

		private:
			typedef ft::Tree<value_type, value_compare, allocator_type>	_tree;

			_tree _base;

		public:
			typedef typename _tree::iterator				iterator;
			typedef typename _tree::const_iterator			const_iterator;
			typedef typename _tree::reverse_iterator		reverse_iterator;
			typedef typename _tree::const_reverse_iterator	const_reverse_iterator;

		public:
			map(void)
				: _base(value_compare(key_compare()))
			{}

			explicit map(key_compare const & comp, allocator_type const & alloc = allocator_type())
				: _base(value_compare(comp))
			{
				(void)alloc;
			}

			map(map const & other)
				: _base(other._base)
			{}

			template <typename InputIt>
			map(InputIt first, InputIt last, const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type())
				: _base(value_compare(comp))
			{
				(void)alloc;
				insert(first, last);
			}

			~map(void)
			{}

			map & operator=(map const & other)
			{
				_base = other._base;
				return *this;
			}

			size_type size(void) const
			{
				return _base.size();
			}

			size_type max_size(void) const
			{
				return _base.max_size();
			}

			iterator begin(void)
			{
				return _base.begin();
			}

			const_iterator begin(void) const
			{
				return _base.begin();
			}

			iterator end(void)
			{
				return _base.end();
			}

			const_iterator end(void) const
			{
				return _base.end();
			}

			reverse_iterator rbegin(void)
			{
				return _base.rbegin();
			}

			const_reverse_iterator rbegin(void) const
			{
				return _base.rbegin();
			}

			reverse_iterator rend(void)
			{
				return _base.rend();
			}

			bool empty(void) const
			{
				return _base.empty();
			}

			mapped_type & at(key_type const & key)
			{
				try {
					mapped_type & val = _base.at(ft::make_pair(key, mapped_type())).second;
					return val;
				} catch (...) {
					throw std::out_of_range("map");
				}
			}

			mapped_type const & at(key_type const & key) const
			{
				try {
					mapped_type const & val = _base.at(ft::make_pair(key, mapped_type())).second;
					return val;
				} catch (...) {
					throw std::out_of_range("map");
				}
			}

			const_reverse_iterator rend(void) const
			{
				return _base.rend();
			}

			void clear(void)
			{
				_base.clear();
			}

			value_compare value_comp(void) const
			{
				return value_compare(key_compare());
			}

			key_compare key_comp(void) const
			{
				return key_compare();
			}

			mapped_type & operator[](key_type const & k)
			{
				value_type val = ft::make_pair(k, mapped_type());
				ft::pair<iterator, bool> p = insert(val);
				return p.first->second;
			}

			ft::pair<iterator, bool> insert(value_type const & value)
			{
				bool wasInserted;
				wasInserted = _base.insert(value);
				return ft::make_pair(_base.find(value), wasInserted);
			}

			iterator insert(iterator hint, const value_type & value)
			{
				(void)hint;
				return insert(value).first;
			}

			template <typename Iter>
			void insert(Iter first, Iter last)
			{
				for (; first != last; ++first)
					insert(*first);
			}

			void debug(void) {
				_base.debug();
			}

			void erase(iterator pos)
			{
				_base.erase(*pos);
			}

			void erase(iterator first, iterator last)
			{
				while (first != last)
					erase(first++);
			}

			size_type erase(key_type const & key)
			{
				iterator pos = _base.find(ft::make_pair(key, mapped_type()));
				if (pos.base() == end())
					return 0;
				erase(pos);
				return 1;
			}
			
			void swap(map & other)
			{
				_base.swap(other._base);
			}

			size_type count(key_type const & key) const
			{
				const_iterator pos = find(key);
				if (pos == end())
					return 0;
				return 1;
			}

			iterator find(key_type const & key)
			{
				return _base.find(ft::make_pair(key, mapped_type()));
			}

			const_iterator find(key_type const & key) const
			{
				return _base.find(ft::make_pair(key, mapped_type()));
			}

			ft::pair<iterator, iterator> equal_range(key_type const & key)
			{
				return ft::make_pair(lower_bound(key), upper_bound(key));
			}

			ft::pair<const_iterator, const_iterator> equal_range(key_type const & key) const
			{
				return ft::make_pair(lower_bound(key), upper_bound(key));
			}

			iterator lower_bound(key_type const & key)
			{
				return _base.lower_bound(ft::make_pair(key, mapped_type()));
			}

			iterator upper_bound(key_type const & key)
			{
				return _base.upper_bound(ft::make_pair(key, mapped_type()));
			}

			const_iterator lower_bound(key_type const & key) const
			{
				return _base.lower_bound(ft::make_pair(key, mapped_type()));
			}

			const_iterator upper_bound(key_type const & key) const
			{
				return _base.upper_bound(ft::make_pair(key, mapped_type()));
			}

			allocator_type get_allocator() const
			{
				return allocator_type();
			}

			friend bool operator==(map const & lhs, map const & rhs)
			{
				return lhs._base == rhs._base;
 			}

			friend bool operator!=(map const & lhs, map const & rhs)
			{
				return lhs._base != rhs._base;
 			}

			friend bool operator<(map const & lhs, map const & rhs)
			{
				return lhs._base < rhs._base;
 			}

			friend bool operator<=(map const & lhs, map const & rhs)
			{
				return lhs._base <= rhs._base;
 			}

			friend bool operator>(map const & lhs, map const & rhs)
			{
				return lhs._base > rhs._base;
 			}

			friend bool operator>=(map const & lhs, map const & rhs)
			{
				return lhs._base >= rhs._base;
 			}
	};
}

template <class Key, class T, class Compare, class Alloc>
void swap(ft::map<Key,T,Compare,Alloc> & lhs, ft::map<Key,T,Compare,Alloc> & rhs)
{
	lhs.swap(rhs);
}

#endif