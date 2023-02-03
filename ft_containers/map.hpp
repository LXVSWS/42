#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "iterator.hpp"
#include "utils.hpp"

namespace ft
{
	template < typename Key, typename T, typename Compare = std::less<Key>, typename Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		private:
			struct Node
			{
				ft::pair<const Key, T>* val;
				Node* par;
				Node* left;
				Node* right;
			};
			Node* root;
			Node* _end;
			Compare compare;
			Alloc allocator;
			size_t _size;
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<const key_type, mapped_type> value_type;
			typedef Compare key_compare;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef ft::bidirectional_iterator<value_type, Node> iterator;
			typedef ft::bidirectional_iterator<const value_type, Node> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;

			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map;

				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) \
			: compare(comp), allocator(alloc), _size(0)
			{
				root = new Node;
				_end = root;
			}
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), \
			const allocator_type& alloc = allocator_type()) : compare(comp), allocator(alloc), _size(0)
			{
				root = new Node;
				_end = root;
				for (const_iterator it = first ; it != last ; ++it)
					insert(*it);
			}
			map(const map& x) : compare(x.compare), allocator(x.allocator), _size(0)
			{
				root = new Node;
				_end = root;
				for (const_iterator it = x.begin() ; it != x.end() ; ++it)
					insert(*it);
			}
			~map()
			{
				Node *tmp[_size];
				size_t i = 0;
				for (iterator it = begin() ; it != end() ; ++it)
				{
					allocator.destroy(&*it);
					allocator.deallocate(&*it, 1);
					tmp[i++] = it.base();
				}
				for (size_t j = 0 ; j < i ; ++j)
					delete tmp[j];
				if (_end)
					delete _end;
			}
			map& operator=(const map& x)
			{
				clear();
				for (const_iterator it = x.begin() ; it != x.end() ; ++it)
					insert(*it);
				return (*this);
			}
			iterator begin()
			{
				Node* leaf = root;
				while (leaf->left)
					leaf = leaf->left;
				iterator i(leaf);
				return (i);
			}
			const_iterator begin() const
			{
				Node* leaf = root;
				while (leaf->left)
					leaf = leaf->left;
				const_iterator i(leaf);
				return (i);
			}
			iterator end()
			{
				iterator i(_end);
				return (i);
			}
			const_iterator end() const
			{
				const_iterator i(_end);
				return (i);
			}
			reverse_iterator rbegin()
			{
				reverse_iterator i(_end);
				return (i);
			}
			const_reverse_iterator rbegin() const
			{
				const_reverse_iterator i(_end);
				return (i);
			}
			reverse_iterator rend()
			{
				reverse_iterator i(begin());
				return (i);
			}
			const_reverse_iterator rend() const
			{
				const_reverse_iterator i(begin());
				return (i);
			}
			bool empty() const
			{
				if (!_size)
					return (true);
				return (false);
			}
			size_type size() const
			{
				return (_size);
			}
			size_type max_size() const
			{
				return (allocator.max_size());
			}
			mapped_type& operator[](const key_type& k)
			{
				for (iterator it = begin() ; it != end() ; ++it)
				{
					if (k == it->first)
						return (it->second);
				}
				pair<iterator, bool> ret = insert(ft::make_pair(k, mapped_type()));
				iterator it = ret.first;
				return (it->second);
			}
			mapped_type& at(const key_type& k)
			{
				for (iterator it = begin() ; it != end() ; ++it)
				{
					if (k == it->first)
						return (it->second);
				}
				throw std::out_of_range("Exception::InvalidKey");
			}
			const mapped_type& at(const key_type& k) const
			{
				for (iterator it = begin() ; it != end() ; ++it)
				{
					if (k == it->first)
						return (it->second);
				}
				throw std::out_of_range("Exception::InvalidKey");
			}
			pair<iterator, bool> insert(const value_type& val)
			{
				if (!_size)
				{
					root->right = new Node;
					_end = root->right;
					_end->par = root;
					root->val = allocator.allocate(1);
					allocator.construct(root->val, val);
					_size++;
					return (ft::make_pair<iterator, bool>(iterator(root), true));
				}
				Node* tmp = root;
				while (1)
				{
					bool ab = key_compare()(val.first, tmp->val->first);
					bool ba = key_compare()(tmp->val->first, val.first);
					if (!ab && !ba)
						return (ft::make_pair<iterator, bool>(iterator(tmp), false));
					else if (ab && !tmp->left)
					{
						tmp->left = new Node;
						tmp->left->val = allocator.allocate(1);
						allocator.construct(tmp->left->val, val);
						tmp->left->par = tmp;
						_size++;
						return (ft::make_pair<iterator, bool>(iterator(tmp->left), true));
					}
					else if (!ab && !tmp->right)
					{
						tmp->right = new Node;
						tmp->right->val = allocator.allocate(1);
						allocator.construct(tmp->right->val, val);
						tmp->right->par = tmp;
						_size++;
						return (ft::make_pair<iterator, bool>(iterator(tmp->right), true));
					}
					else if (!ab && tmp->right == _end)
					{
						tmp->right->right = new Node;
						_end = tmp->right->right;
						_end->par = tmp->right;
						tmp->right->val = allocator.allocate(1);
						allocator.construct(tmp->right->val, val);
						tmp->right->par = tmp;
						_size++;
						return (ft::make_pair<iterator, bool>(iterator(tmp->right), true));
					}
					else if (ab && tmp->left)
						tmp = tmp->left;
					else if (!ab && tmp->right)
						tmp = tmp->right;
				}
			}
			iterator insert(iterator position, const value_type& val)
			{
				if (!_size)
				{
					root->right = new Node;
					_end = root->right;
					_end->par = root;
					root->val = allocator.allocate(1);
					allocator.construct(root->val, val);
					_size++;
					return (iterator(root));
				}
				Node* tmp = position.base();
				if (!tmp || !tmp->val)
				{
					pair<iterator, bool> ret(insert(val));
					return (ret.first);
				}
				bool ab = key_compare()(val.first, tmp->val->first);
				bool ba = key_compare()(tmp->val->first, val.first);
				if (!ab && !ba)
					return (iterator(tmp));
				else if (ab && !tmp->left)
				{
					tmp->left = new Node;
					tmp->left->val = allocator.allocate(1);
					allocator.construct(tmp->left->val, val);
					tmp->left->par = tmp;
					_size++;
					return (iterator(tmp->left));
				}
				else if (!ab && tmp->right == _end)
				{
					tmp->right->right = new Node;
					_end = tmp->right->right;
					_end->par = tmp->right;
					tmp->right->val = allocator.allocate(1);
					allocator.construct(tmp->right->val, val);
					tmp->right->par = tmp;
					_size++;
					return (iterator(tmp->right));
				}
				pair<iterator, bool> ret(insert(val));
				return (ret.first);
			}
			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				for (iterator it = first ; it != last ; ++it)
					insert(*it);
			}
			void erase(iterator position)
			{
				Node* node = position.base();
				if (!node || !node->val || node == _end)
					return ;
				iterator it = position;
				Node* before = (--it).base();
				iterator itt = position;
				Node* next = (++itt).base();
				if (before && next)
				{
					if (before->left == node)
						before->left = next;
					else if (before->right == node)
						before->right = next;
					next->par = before;
				}
				else if (!before && next)
				{
					next->par = NULL;
					root = next;
				}
				allocator.destroy(node->val);
				allocator.deallocate(node->val, 1);
				delete node;
				_size--;
			}
			size_type erase(const key_type& k)
			{
				iterator it = find(k);
				if (it.base() && it != end())
				{
					erase(it);
					return (1);
				}
				return (0);
			}
			void erase(iterator first, iterator last)
			{
				for (iterator it = first ; it != last ; ++it)
					erase(it);
			}
			void swap(map& x)
			{
				if (x == *this)
					return ;
				Node *tmp_root = x.root;
				Node *tmp_end = x._end;
				size_t tmp_size = x._size;
				x.root = root;
				x._end = _end;
				x._size = _size;
				root = tmp_root;
				_end = tmp_end;
				_size = tmp_size;
			}
			void clear()
			{
				Node *tmp[_size];
				size_t i = 0;
				for (iterator it = begin() ; it != end() ; ++it)
				{
					allocator.destroy(&*it);
					allocator.deallocate(&*it, 1);
					tmp[i++] = it.base();
				}
				for (size_t j = 0 ; j < i ; ++j)
					delete tmp[j];
				if (_end)
					delete _end;
				_size = 0;
				root = new Node;
				_end = root;
			}
			key_compare key_comp() const
			{
				return (compare);
			}
			value_compare value_comp() const
			{
				return (value_compare(key_compare()));
			}
			iterator find(const key_type& k)
			{
				for (iterator it = begin() ; it != end() ; ++it)
				{
					if (k == it->first)
						return (it);
				}
				return (end());
			}
			const_iterator find(const key_type& k) const
			{
				for (const_iterator it = begin() ; it != end() ; ++it)
				{
					if (k == it->first)
						return (it);
				}
				return (end());
			}
			size_type count(const key_type& k) const
			{
				for (const_iterator it = begin() ; it != end() ; ++it)
				{
					if (k == it->first)
						return (1);
				}
				return (0);
			}
			iterator lower_bound(const key_type& k)
			{
				for (iterator it = begin() ; it != end() ; ++it)
				{
					if (k == it->first || !(key_compare()(it->first, k)))
						return (it);
				}
				return (end());
			}
			const_iterator lower_bound(const key_type& k) const
			{
				for (const_iterator it = begin() ; it != end() ; ++it)
				{
					if (k == it->first || !(key_compare()(it->first, k)))
						return (it);
				}
				return (end());
			}
			iterator upper_bound(const key_type& k)
			{
				for (iterator it = begin() ; it != end() ; ++it)
				{
					if (k == it->first)
						return (++it);
					else if (key_compare()(k, it->first))
						return (it);
				}
				return (end());
			}
			const_iterator upper_bound(const key_type& k) const
			{
				for (const_iterator it = begin() ; it != end() ; ++it)
				{
					if (k == it->first)
						return (++it);
					else if (key_compare()(k, it->first))
						return (it);
				}
				return (end());
			}
			pair<const_iterator, const_iterator> equal_range(const key_type& k) const
			{
				return (ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
			}
			pair<iterator, iterator> equal_range(const key_type& k)
			{
				return (ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
			}
			allocator_type get_allocator() const
			{
				return (allocator);
			}
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::map<Key,T,Compare,Alloc>::const_iterator lit = lhs.begin();
		typename ft::map<Key,T,Compare,Alloc>::const_iterator rit = rhs.begin();
		while (lit != lhs.end())
		{
			if (lit->first != rit->first || lit->second != rit->second)
				return (false);
			++lit, ++rit;
		}
		return (true);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (true);
		typename ft::map<Key,T,Compare,Alloc>::const_iterator lit = lhs.begin();
		typename ft::map<Key,T,Compare,Alloc>::const_iterator rit = rhs.begin();
		while (lit != lhs.end())
		{
			if (lit->first != rit->first || lit->second != rit->second)
				return (true);
			++lit, ++rit;
		}
		return (false);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
	{
		return (!ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
	{
		return (!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap(ft::map<Key,T,Compare,Alloc>& x, ft::map<Key,T,Compare,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
