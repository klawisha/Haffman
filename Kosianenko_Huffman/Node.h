#pragma once
#include <cstddef>

class Node
{
public:
	int _integer;
	char _char;
	Node* left, * right;

	Node() { left = right = NULL; }

	Node(Node* L, Node* R)
	{
		left = L;
		right = R;
		_integer = L->_integer + R->_integer;
	}

};



