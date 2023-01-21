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
				root->val = allocator.allocate(1);
			}
			/*
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), \
			const allocator_type& alloc = allocator_type()) {}
			map(const map& x) {}
			*/
			~map()
			{
				allocator.destroy(root->val);
				allocator.deallocate(root->val, 1);
				delete root;
			}
			void insert(const value_type& val) // return type : pair<iterator, bool>
			{
				if (!_size)
					allocator.construct(root->val, val);
				else
				{
					Node* leaf = root;
					bool ab = key_compare()(val.first, leaf->val->first);
					bool ba = key_compare()(leaf->val->first, val.first);

					if (!ab && !ba)
						std::cout << "equivalent" << std::endl;
					else if (ab)
						std::cout << "value less than root" << std::endl;
					else
						std::cout << "value bigger than root" << std::endl;
				}
				_size++;
			}
			iterator begin()
			{
				Node* leaf = root;
				while (leaf->left)
					leaf = leaf->left;
				iterator i(leaf->val, leaf->par, leaf->left, leaf->right);
				return (i);
			}
	};
}

#endif
