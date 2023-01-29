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
			//typedef ft::value_comp() value_compare;
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
				size_type i = allocator.max_size();
				if (i == 2305843009213693951)
					return (461168601842738790);
				else if (i == 2305843009213693951)
					return (461168601842738790);
				else if (i == 1152921504606846975)
					return (384307168202282325);
				return (i);
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
			const mapped_type& at (const key_type& k) const
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
				(void)position;
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
				if (!position.base())
					return ;
				Node* node = position.base();
				Node* par = node->par;
				Node* left = node->left;
				Node* right = node->right;
				allocator.destroy(node->val);
				allocator.deallocate(node->val, 1);
				delete node;
				if (par)
					(void)par;
				if (left)
					(void)left;
				if (right)
					(void)right;
				--_size;
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
			allocator_type get_allocator() const
			{
				return (allocator);
			}
	};
}

#endif
