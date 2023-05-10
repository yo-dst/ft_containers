#include "tree.hpp"
#include <functional>

namespace ft
{
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set
	{
		public:
			typedef T               						key_type;
			typedef key_type        						value_type;
			typedef size_t          						size_type;
			typedef ptrdiff_t       						difference_type;
			typedef Compare         						key_compare;
			typedef key_compare     						value_compare;
			typedef Alloc           						allocator_type;
			typedef value_type &    						reference;
			typedef value_type const &  					const_reference;
			typedef typename allocator_type::pointer		pointer;
			typedef typename allocator_type::const_pointer	const_pointer;

		private:
			typedef ft::Tree<value_type, value_compare, allocator_type>	_tree;

			_tree _base;

		public:
			typedef typename _tree::const_iterator			iterator;
			typedef typename _tree::const_iterator			const_iterator;
			typedef typename _tree::const_reverse_iterator	reverse_iterator;
			typedef typename _tree::const_reverse_iterator	const_reverse_iterator;
		
		public:
			set(void)
				: _base(value_compare())
			{}

			explicit set(Compare const & comp, const allocator_type & alloc = allocator_type())
				: _base(comp)
			{
				(void)alloc;
			}

			template <class InputIt>
			set(InputIt first, InputIt last, Compare const & comp = Compare(), allocator_type const & alloc = allocator_type())
				: _base(comp)
			{
				(void)alloc;
				for (; first != last; ++first)
					insert(*first);
			}

			set(set const & other)
				: _base(other._base)
			{}

			~set()
			{}

			set & operator=(set const & other)
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

			value_type & at(value_type const & value)
			{
				try {
					value_type & val = _base.at(value).second;
					return val;
				} catch (...) {
					throw std::out_of_range("set");
				}
			}

			value_type const & at(value_type const & value) const
			{
				try {
					value_type const & val = _base.at(value).second;
					return val;
				} catch (...) {
					throw std::out_of_range("set");
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
				return value_compare();
			}

			key_compare key_comp(void) const
			{
				return key_compare();
			}

			value_type & operator[](value_type const & value)
			{
				ft::pair<iterator, bool> p = insert(value);
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

			size_type erase(value_type const & value)
			{
				iterator pos = _base.find(value);
				if (pos.base() == end())
					return 0;
				erase(pos);
				return 1;
			}
			
			void swap(set & other)
			{
				_base.swap(other._base);
			}

			size_type count(value_type const & value) const
			{
				const_iterator pos = find(value);
				if (pos == end())
					return 0;
				return 1;
			}

			iterator find(value_type const & value)
			{
				return _base.find(value);
			}

			const_iterator find(value_type const & value) const
			{
				return _base.find(value);
			}

			ft::pair<iterator, iterator> equal_range(value_type const & value)
			{
				return ft::make_pair(lower_bound(value), upper_bound(value));
			}

			ft::pair<const_iterator, const_iterator> equal_range(value_type const & value) const
			{
				return ft::make_pair(lower_bound(value), upper_bound(value));
			}

			iterator lower_bound(value_type const & value)
			{
				return _base.lower_bound(value);
			}

			iterator upper_bound(value_type const & value)
			{
				return _base.upper_bound(value);
			}

			const_iterator lower_bound(value_type const & value) const
			{
				return _base.lower_bound(value);
			}

			const_iterator upper_bound(value_type const & value) const
			{
				return _base.upper_bound(value);
			}

			allocator_type get_allocator() const
			{
				return allocator_type();
			}

			friend bool operator==(set const & lhs, set const & rhs)
			{
				return lhs._base == rhs._base;
			}

			friend bool operator!=(set const & lhs, set const & rhs)
			{
				return lhs._base != rhs._base;
			}

			friend bool operator<(set const & lhs, set const & rhs)
			{
				return lhs._base < rhs._base;
			}

			friend bool operator<=(set const & lhs, set const & rhs)
			{
				return lhs._base <= rhs._base;
			}

			friend bool operator>(set const & lhs, set const & rhs)
			{
				return lhs._base > rhs._base;
			}

			friend bool operator>=(set const & lhs, set const & rhs)
			{
				return lhs._base >= rhs._base;
			}
	};
}

template <class T, class Compare, class Alloc>
void swap(ft::set<T, Compare, Alloc> & lhs, ft::set<T, Compare, Alloc> & rhs)
{
	lhs.swap(rhs);
}
