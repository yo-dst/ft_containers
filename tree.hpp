#ifndef _tree_hpp_
#define _tree_hpp_

#include <exception>
#include <algorithm>
#include <memory>
#include <csignal>
#include "iterator.hpp"
#include "utility.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"

#define RED true
#define BLACK false

namespace ft
{
	// *****************************************
	// * Node
	// *****************************************
	template <typename DataType>
	struct Node
	{
		DataType		data;
		bool			color;
		Node *		parent;
		Node *		left;
		Node * 		right;

		Node(DataType const & data, bool color, Node * parent, Node * left, Node * right)
			: data(data), color(color), parent(parent), left(left), right(right)
		{}

		~Node(void)
		{}

		bool hasNoChild(void) const
		{ return (left == nullptr && right == nullptr); }

		bool hasTwoChild(void) const
		{ return (left != nullptr && right != nullptr); }

		bool hasOneChild(void) const
		{ return (!hasNoChild() && !hasTwoChild()); }

		Node * getChild(void)
		{ return (left != nullptr ? left : right); }

		void printPtr(std::string const & pfx, void * ptr) {
			std::cout << pfx << ":" << ptr << std::endl;
		}

		void debug(std::string const & pfx = "Node")
		{
			std::cout << "----\n";
			std::cout << pfx << std::endl;
			std::cout << data << std::endl;
			std::cout << "color: " << color << std::endl;
			printPtr("parent", parent);
			printPtr("left", left);
			printPtr("right", right);
		}""
	};

	template <class DataType>
	Node<DataType> * _getSuccessor(Node<DataType> * node)
	{
		if (!node)
			return nullptr;
		if (node->right)
		{
			node = node->right;
			while (node && node->left)
				node = node->left;
			return node;
		}
		Node<DataType> * parent = node->parent;
		while (parent && parent->left != node)
		{
			node = parent;
			parent = parent->parent;
		}
		return parent;
	}

	template <class DataType>
	Node<DataType> * _getPredecessor(Node<DataType> * node)
	{
		if (!node)
			return nullptr;
		if (node->left)
		{
			node = node->left;
			while (node->right)
				node = node->right;
			return node;
		}
		Node<DataType> * parent = node->parent;
		while (parent && parent->right != node)
		{
			node = parent;
			parent = parent->parent;
		}
		return parent;
	}

	// * return false if node is root
	template <class DataType>
	bool isLeftChild(Node<DataType> * node)
	{
		if (node == nullptr || node->parent == nullptr)
			return false;
		if (node->parent->left == node)
			return true;
		return false;
	}

	template <class DataType>
	bool isRightChild(Node<DataType> * node)
	{
		if (node == nullptr || node->parent == nullptr)
			return false;
		return !isLeftChild(node);
	}

	// *****************************************
	// * TreeIterator
	// *****************************************
	template <typename DataType>
	class TreeIterator
	{
		public:
			typedef DataType 					value_type;
			typedef ptrdiff_t 					difference_type;
			typedef value_type *				pointer;
			typedef value_type &  				reference;
			typedef bidirectional_iterator_tag	iterator_category;

			typedef Node<value_type>			node_type;
			typedef node_type *					node_pointer;

		private:
			node_pointer 	_curr;

		public:
			// * ---- constructor(s) ----
			TreeIterator(void)
				: _curr(nullptr)
			{}

			TreeIterator(node_pointer ptr)
				: _curr(ptr)
			{}

			TreeIterator(TreeIterator const & src)
				: _curr(src.base())
			{}

			// * ---- operator(s) ----
			value_type & operator*(void) const
			{
				return _curr->data;
			}

			pointer operator->(void) const
			{
				return &_curr->data;
			}

			TreeIterator & operator++()
			{
				_curr = _getSuccessor(_curr);
				if (!_curr)
					std::raise(SIGSEGV);
				return *this;
			}

			TreeIterator & operator--()
			{
				_curr = _getPredecessor(_curr);
				if (!_curr)
					std::raise(SIGSEGV);
				return *this;
			}

			TreeIterator operator++(int)
			{
				TreeIterator tmp = *this;
				*this = operator++();
				return tmp;
			}

			TreeIterator operator--(int)
			{
				TreeIterator tmp = *this;
				*this = operator--();
				return tmp;
			}

			// ---- member function(s) ----
			node_pointer base(void) const
			{
				return _curr;
			}

			friend bool operator==(TreeIterator<DataType> const & lhs, TreeIterator<DataType> const & rhs)
			{
				return lhs.base() == rhs.base();
			}

			friend bool operator!=(TreeIterator<DataType> const & lhs, TreeIterator<DataType> const & rhs)
			{
				return !(lhs == rhs);
			}
	};

	template <typename DataType>
	class TreeConstIterator
	{
		public:
			typedef DataType 					value_type;
			typedef ptrdiff_t 					difference_type;
			typedef value_type const *			pointer;
			typedef value_type const &  		reference;
			typedef bidirectional_iterator_tag	iterator_category;

			typedef Node<DataType>			node_type;
			typedef node_type *					node_pointer;

		private:
			node_pointer 	_curr;

		public:
			// * ---- constructor(s) ----
			TreeConstIterator(void)
				: _curr(nullptr)
			{}

			TreeConstIterator(node_pointer ptr)
				: _curr(ptr)
			{}

			TreeConstIterator(TreeConstIterator const & src)
				: _curr(src.base())
			{}

			TreeConstIterator(TreeIterator<DataType> const & src)
				: _curr(src.base())
			{}

			// * ---- operator(s) ----
			value_type const & operator*(void) const
			{
				return _curr->data;
			}

			pointer operator->(void) const
			{
				return &_curr->data;
			}

			TreeConstIterator & operator++()
			{
				_curr = _getSuccessor(_curr);
				if (!_curr)
					std::raise(SIGSEGV);
				return *this;
			}

			TreeConstIterator & operator--()
			{
				_curr = _getPredecessor(_curr);
				if (!_curr)
					std::raise(SIGSEGV);
				return *this;
			}

			TreeConstIterator operator++(int)
			{
				TreeConstIterator tmp = *this;
				*this = operator++();
				return tmp;
			}

			TreeConstIterator operator--(int)
			{
				TreeConstIterator tmp = *this;
				*this = operator--();
				return tmp;
			}

			// ---- member function(s) ----
			node_pointer base(void) const
			{
				return _curr;
			}

			friend bool operator==(TreeConstIterator<DataType> const & lhs, TreeConstIterator<DataType> const & rhs)
			{
				return lhs.base() == rhs.base();
			}

			friend bool operator!=(TreeConstIterator<DataType> const & lhs, TreeConstIterator<DataType> const & rhs)
			{
				return !(lhs == rhs);
			}
	};

	// *****************************************
	// * Tree (which is a Red-Black-Tree)
	// *****************************************
	template <typename DataType, typename DataCompare, typename DataAllocator>
	class Tree
	{
		public:
			typedef DataType								data_type;
			typedef DataCompare								data_compare;
			typedef DataAllocator							data_allocator;
			typedef Node<data_type>						node_type;
			typedef node_type *								node_pointer;
			typedef TreeIterator<data_type>					iterator;
			typedef TreeConstIterator<data_type>				const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef size_t									size_type;

			typedef typename data_allocator::template rebind<node_type>::other	node_allocator;
			
		private:
			node_pointer	_root;
			node_pointer	_end;
			data_compare	_comp;

		public:
			Tree(data_compare const & c)
				: _comp(c)
			{
				_end = _newNode(data_type(), BLACK, nullptr, nullptr, nullptr);
				_root = _end;
			}

			Tree(Tree const & other)
				: _comp(other._comp)
			{
				_end = _newNode(data_type(), BLACK, nullptr, nullptr, nullptr);
				_root = _end;
				const_iterator it = other.begin();
				const_iterator ite = other.end();
				for (; it != ite; ++it)
					insert(*it);
			}

			~Tree(void)
			{
				clear();
				_deleteNode(_end);
			}

			Tree & operator=(Tree const & other)
			{
				clear();
				const_iterator cit = other.begin();
				const_iterator cite = other.end();
				for (; cit != cite; ++cit)
					insert(*cit);
				return *this;
			}

			size_type max_size(void) const
			{
				node_allocator alloc;
				return alloc.max_size();
			}

			data_type & at(data_type const & key)
			{
				iterator pos = find(key);
				if (pos == _end)
					throw std::out_of_range("Tree");
				return *pos;
			}

			data_type const & at(data_type const & key) const
			{
				const_iterator pos = find(key);
				if (pos == _end)
					throw std::out_of_range("Tree");
				return *pos;
			}

			// * return false if data is duplicate
			bool insert(data_type const & data) {
				node_pointer node = _newNode(data, RED, nullptr, nullptr, nullptr);

				node_pointer y = nullptr;
				node_pointer x = _root;

				while (x != nullptr && x != _end) {
					y = x;
					if (_comp(node->data, x->data)) {
						x = x->left;
					} else if (_comp(x->data, node->data)) {
						x = x->right;
					} else {
						_deleteNode(node);
						return false;
					}
				}

				node->parent = y;
				if (y == nullptr) {
					_root = node;
					node->right = _end;
					_end->parent = node;
				} else if (_comp(node->data, y->data)) {
					y->left = node;
				} else {
					if (y->right == _end) {
						node->right = _end;
						_end->parent = node;
					}
					y->right = node;
				}

				if (node->parent == nullptr) {
					node->color = BLACK;
				} else if (node->parent->parent != nullptr) {
					_insertFix(node);
				}
				return true;
			}

			// * jajajajaja oopsi
			void erase(data_type const & data)
			{
				_root = _erase(_root, data);
			}

			void showInOrder(void) const 
			{
				_showInOrder(_root);
			}

			bool empty(void) const
			{
				return _root == _end;
			}

			void clear(void)
			{
				_root = _clear(_root);
				_end->parent = nullptr;
				_root = _end;
			}

			iterator find(data_type const & data)
			{
				return iterator(_find(_root, data));
			}

			const_iterator find(data_type const & data) const
			{
				return const_iterator(_find(_root, data));
			}

			size_type size(void) const
			{
				return _size(_root);
			}

			iterator begin(void)
			{
				node_pointer minNode = _getMin(_root);
				if (!minNode)
					return end();
				else
					return iterator(minNode);
			}

			const_iterator begin(void) const
			{
				node_pointer minNode = _getMin(_root);
				const_iterator res = minNode;
				if (!minNode)
					return end();
				else
					return res;
			}

			iterator end(void)
			{
				return iterator(_end);
			}

			const_iterator end(void) const
			{
				return const_iterator(_end);
			}

			reverse_iterator rbegin(void)
			{
				return reverse_iterator(end());
			}

			const_reverse_iterator rbegin(void) const
			{
				return reverse_iterator(end());
			}

			reverse_iterator rend(void)
			{
				return reverse_iterator(begin());
			}

			const_reverse_iterator rend(void) const
			{
				return const_reverse_iterator(begin());
			}

			void swap(Tree & other)
			{
				std::swap(_root, other._root);
				std::swap(_end, other._end);
			}

			iterator lower_bound(data_type const & data)
			{
				iterator it = begin();
				iterator ite = end();
				while (it != ite && _comp(*it, data))
					++it;
				return it;
			}

			const_iterator lower_bound(data_type const & data) const
			{
				const_iterator it = begin();
				const_iterator ite = end();
				while (it != ite && _comp(*it, data))
					++it;
				return it;
			}

			iterator upper_bound(data_type const & data)
			{
				iterator it = lower_bound(data);
				if (it != end() && it == find(data))
					return ++it;
				return it;
			}

			const_iterator upper_bound(data_type const & data) const
			{
				const_iterator it = lower_bound(data);
				if (it != end() && it == find(data))
					return ++it;
				return it;
			}

		private:
			node_pointer _newNode(data_type const & data, bool color, node_pointer parent, node_pointer left, node_pointer right)
			{
				node_allocator alloc;
				node_pointer node;
				node = alloc.allocate(1);
				alloc.construct(node, node_type(data, color, parent, left, right));
				return node;
			}

			void _deleteNode(node_pointer node)
			{
				if (node == nullptr)
					return ;
				node_allocator alloc;
				alloc.destroy(node);
				alloc.deallocate(node, 1);
			}

			node_pointer _getMin(node_pointer root) const
			{
				if (root == _end)
					return nullptr;
				while (root->left)
					root = root->left;
				return root;
			}

			node_pointer _getMax(node_pointer root) const
			{
				if (root == _end)
					return nullptr;
				while (root->right && root->right != _end)
					root = root->right;
				return root;
			}

			void _rbTransplant(node_pointer u, node_pointer v)
			{
				if (u->parent == nullptr)
					_root = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}

			void _rotateLeft(node_pointer x)
			{
			
				node_pointer y = x->right;
				x->right = y->left;
				if (y->left)
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == nullptr)
					_root = y;
				else if (isLeftChild(x))
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			void _rotateRight(node_pointer x)
			{
			
				node_pointer y = x->left;
				x->left = y->right;
				if (y->right != nullptr)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == nullptr)
					_root = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right = x;
				x->parent = y;
			}

			node_pointer _erase(node_pointer root, data_type const & data)
			{
				if (!root || root == _end)
					return root;
				if (_comp(data, root->data))
					root->left = _erase(root->left, data);
				else if (_comp(root->data, data))
					root->right = _erase(root->right, data);
				else
				{
					if (root->hasNoChild())
					{
						_deleteNode(root);
						return nullptr;
					}
					else if (root->hasOneChild())
					{
						node_pointer child = root->getChild();
						if (child)
							child->parent = root->parent;
						_deleteNode(root);
						return child;
					}
					else
					{
						node_pointer node = root->right == _end ? _getMax(root->left) : _getMin(root->right);
						node_pointer tmp = root;
						root = _newNode(node->data, node->color, root->parent, root->left, root->right);
						root->left->parent = root;
						root->right->parent = root;
						_deleteNode(tmp);
						if (root->right == _end)
							root->left = _erase(root->left, node->data);
						else
							root->right = _erase(root->right, node->data);
					}
				}
				return root;
			}

			void _insertFix(node_pointer k)
			{
			
				node_pointer u;
				while (k->parent->color == RED)
				{
					if (k->parent == k->parent->parent->right)
					{
					
						u = k->parent->parent->left;
						if (u != nullptr && u->color == RED)
						{
						
							u->color = BLACK;
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							k = k->parent->parent;
						}
						else
						{
						
							if (k == k->parent->left)
							{
								k = k->parent;
								_rotateRight(k);
							}
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							_rotateLeft(k->parent->parent);
						}
					}
					else
					{
					
						u = k->parent->parent->right;
						if (u != nullptr && u->color == RED)
						{
							u->color = BLACK;
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							k = k->parent->parent;
						}
						else
						{
							if (k == k->parent->right)
							{
								k = k->parent;
								_rotateLeft(k);
							}
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							_rotateRight(k->parent->parent);
						}
					}
					if (k == _root)
						break;
				}
				_root->color = BLACK;
			}

			void _showInOrder(node_pointer root) const
			{
				if (root == nullptr || root == _end)
					return ;
				_showInOrder(root->left);
				std::cout << root->data.first << ": " << root->data.second << std::endl;
				_showInOrder(root->right);
			}

			node_pointer _find(node_pointer root, data_type const & data) const
			{
				if (root == nullptr || root == _end)
					return _end;
				if (_comp(data, root->data))
					return _find(root->left, data);
				else if (_comp(root->data, data))
					return _find(root->right, data);
				else
					return root;
			}

			node_pointer _clear(node_pointer root)
			{
				if (!root || root == _end)
					return nullptr;
				root->left = _clear(root->left);
				root->right = _clear(root->right);
				_deleteNode(root);
				return nullptr;
			}

			size_type _size(node_pointer root, size_type i = 0) const
			{
				if (!root || root == _end)
					return i;
				i++;
				i += _size(root->left);
				i += _size(root->right);
				return i;
			}
	};

	template <typename DataType, typename DataCompare, typename DataAlloc>
	bool operator==(const Tree<DataType, DataCompare, DataAlloc> & lhs, const Tree<DataType, DataCompare, DataAlloc> & rhs)
	{
		typedef typename Tree<DataType, DataCompare, DataAlloc>::const_iterator const_iterator;
		if (lhs.size() != rhs.size())
			return false;
		const_iterator it1 = lhs.begin();
		const_iterator ite = lhs.end();
		const_iterator it_rhs = rhs.begin();
		while (it1 != ite)
		{
			if (*it1 != *it_rhs)
				return false;
			++it1;
			++it_rhs;
		}
		return true;
	}

	template <typename DataType, typename DataCompare, typename DataAlloc>
	bool operator!=(const Tree<DataType, DataCompare, DataAlloc> & lhs, const Tree<DataType, DataCompare, DataAlloc> & rhs)
	{
		return !(lhs == rhs);
	}

	template <typename DataType, typename DataCompare, typename DataAlloc>
	bool operator<(const Tree<DataType, DataCompare, DataAlloc> & lhs, const Tree<DataType, DataCompare, DataAlloc> & rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename DataType, typename DataCompare, typename DataAlloc>
	bool operator<=(const Tree<DataType, DataCompare, DataAlloc> & lhs, const Tree<DataType, DataCompare, DataAlloc> & rhs)
	{
		return (lhs == rhs || lhs < rhs);
	}

	template <typename DataType, typename DataCompare, typename DataAlloc>
	bool operator>(const Tree<DataType, DataCompare, DataAlloc> & lhs, const Tree<DataType, DataCompare, DataAlloc> & rhs)
	{
		return !(lhs <= rhs);
	}

	template <typename DataType, typename DataCompare, typename DataAlloc>
	bool operator>=(const Tree<DataType, DataCompare, DataAlloc> & lhs, const Tree<DataType, DataCompare, DataAlloc> & rhs)
	{
		return !(lhs < rhs);
	}
}

#endif