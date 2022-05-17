#pragma once
#include <iostream>
#include <iomanip>

using namespace std;

enum color { red, black }; //color for RBTRee

template <typename typeInfo>


class List {
private:
	class Node {
	public:
		Node* next;
		Node* prev;
		typeInfo info;
	};

	size_t size;

public:

	Node* head;
	Node* tail;

	List() {
		head = tail = NULL;
		Node* buffer = new Node; // Create temporary node
		buffer->prev = NULL;
		buffer->next = NULL;
		size = 0;
	};

	~List() {
		clear();
	};

	void push_back(typeInfo info) {
		Node* cur = new Node;
		cur->info = info;
		if (head == NULL) {
			head = tail = cur;
			size++;
		}
		else {
			tail->next = cur;
			cur->prev = tail;
			tail = cur;
			size++;
		}
	};

	void push_front(typeInfo info) {
		Node* cur = new Node;
		cur->info = info;
		cur->next = NULL;
		cur->prev = NULL;
		if (head == NULL) { //the list is empty
			head = tail = cur;
			size++;
		}
		else {
			cur->next = head;
			head->prev = cur;
			head = cur;
			size++;
		}
	};

	void pop_back() {
		if (isEmpty() == 0)
			throw "The list is already empty";
		else {
			Node* del = new Node;
			if (head != NULL) { //the list is not empty
				if (head == tail) { //there is one item in the list
					head = tail = NULL;
					size--;
				}
				else {
					del = tail;
					tail = tail->prev;
					delete del;
					tail->next = NULL;
					size--;
				}
			}
		}
	};

	void pop_front() {
		if (isEmpty() == true)
			throw "The list is already empty";
		else {
			Node* del = new Node;
			if (head != NULL) { //the list is not empty
				if (head == tail) { //there is one item in the list
					head = tail = NULL;
					size--;
				}
				else {
					del = head;
					head = head->next;
					delete del;
					head->prev = NULL;
					size--;
				}
			}
		}
	};

	size_t get_size() {
		if (size >= 0)
			return size;
		else throw invalid_argument("Empty List");
	};

	void clear() {
		while (size != 0) {
			pop_front();
		}
	};

	bool isEmpty() { return get_size() == 0; };

	friend std::ostream& operator<< (std::ostream& out, List& list) {
		size_t listSize = list.get_size();
		for (size_t i = 0; i < listSize; i++) {
			cout << list.at(i) << endl;
		}
		return out;
	}

	void reverse() {
		Node* left = head, * right = head;
		while (right->next != NULL) right = right->next;
		while (left != right && left->prev != right) {
			swap(left->info, right->info);
			left = left->next;
			right = right->prev;
		}
	}

	bool check(typeInfo info) {
		Node* current = head;
		if (isEmpty() == 1) return false;
		if (current->info == info) return true;

		while (current != tail) {
			if (current->info == info) return true;
			current = current->next;
		}
		if (tail->info == info) return true;
		return false;
	}

	typeInfo at(int index) { //getting an item by index
		if (index < 0 || index > size) {
			throw out_of_range("Incorrect index");
		}
		else {
			int i = 0;
			Node* buf = head;
			while (i < index) {
				buf = buf->next;
				i++;
			}
			return buf->info;
		}
	}
};

template <typename keyType, typename valueType>

class Map {
private:
	class Node { //for RBTree
	public:
		keyType key;
		valueType value;
		color color; //red or black
		Node* parent; // pointer to the parent
		Node* left; // pointer to left child
		Node* right; // pointer to right child
	};
	int size;
	Node* root; //pointer to the root of the tree
	Node* nil; //pointer to a leaf node

	void leftTurn(Node* x) {
		Node* y = x->right;
		x->right = y->left;
		if (y->left != nil)
			y->left->parent = x;

		y->parent = x->parent;

		if (x->parent == NULL)
			root = y;
		else {
			if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
		}

		y->left = x;
		x->parent = y;
	}

	void rightTurn(Node* y) {
		Node* x = y->left;
		y->left = x->right;

		if (x->right != nil)
			x->right->parent = y;

		x->parent = y->parent;

		if (y->parent == NULL)
			root = x;
		else {
			if (y == y->parent->right)
				y->parent->right = x;
			else
				y->parent->left = x;
		}

		x->right = y;
		y->parent = x;
	}

	void insertFixUp(Node* newNode) {
		Node* bufNode;

		while (newNode->parent->color == red) {
			if (newNode->parent == newNode->parent->parent->right) { //right or left???
				//first case
				bufNode = newNode->parent->parent->left;
				if (bufNode->color == red) {
					bufNode->color = black;
					newNode->parent->color = black;
					newNode->parent->parent->color = red;
					newNode = newNode->parent->parent;
				}
				else {
					//second case
					if (newNode == newNode->parent->left) {
						newNode = newNode->parent;
						rightTurn(newNode);
					}
					//third case
					newNode->parent->color = black;
					newNode->parent->parent->color = red;
					leftTurn(newNode->parent->parent);
				}
			}
			else {
				bufNode = newNode->parent->parent->right;

				if (bufNode->color == red) {
					bufNode->color = black;
					newNode->parent->color = black;
					newNode->parent->parent->color = red;
					newNode = newNode->parent->parent;
				}
				else {
					if (newNode = newNode->parent->right) {
						newNode = newNode->parent;
						leftTurn(newNode);
					}
					newNode->parent->color = black;
					newNode->parent->parent->color = red;
					rightTurn(newNode->parent->parent);
				}
			}
			if (newNode == root) break;
		}
		root->color = black;
	}

	void removeFixUp(Node* x) {
		Node* w;

		while (x != root && x->color == black) {
			if (x == x->parent->left) {
				w = x->parent->right; //brother
				if (w->color == red) {
					w->color = black;
					x->parent->color = red;
					leftTurn(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == black && w->right->color == black) {
					w->color = red;
					x = x->parent;
				}
				else {
					if (w->right->color == black) {
						w->left->color = black;
						w->color = red;
						rightTurn(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = black;
					w->right->color = black;
					leftTurn(x->parent);
					x = root;
				}
			}
			else {
				w = x->parent->left;
				if (w->color == red) {
					x->color = black;
					x->parent->color = red;
					rightTurn(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == black && w->right->color == black) {
					w->color = red;
					x = x->parent;
				}
				else {
					if (w->right->color == 0) {
						w->left->color = black;
						w->color = red;
						leftTurn(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = black;
					w->right->color = black;
					rightTurn(x->parent);
					x = root;
				}
			}
		}
		x->color = black;
	}

	void getListOfKeys(Node* node, List<keyType>* listKeys) {
		if (node != nil && node != NULL) {
			listKeys->push_back(node->key);
			getListOfKeys(node->left, listKeys);
			getListOfKeys(node->right, listKeys);
		}
	}

	void getListOfValues(Node* node, List<valueType>* listValues) {
		if (node != nil && node != NULL) {
			listValues->push_back(node->value);
			getListOfValues(node->left, listValues);
			getListOfValues(node->right, listValues);
		}
	}

	void deleteNode(Node* node) {
		if (node != nil && node != NULL) {
			if (node->right != nil && node->right != NULL)
				deleteNode(node->right);
			if (node->left != nil && node->left != NULL)
				deleteNode(node->left);
			delete node;
		}
	}

	void printNode(Node* node) {
		string colorStr;

		if (node == NULL)
			return;

		if (node->color == black) colorStr = "black";
		else colorStr = "red";

		if (node->parent == NULL)
			cout << node->key << "(" << colorStr << ") is root" << endl;
		else {
			if (node->parent->left == node)
			{
				cout << node->key << "(" << colorStr << ") is " << node->parent->key << "'s " << "left child" << endl;
			}
			else
			{
				cout << node->key << "(" << colorStr << ") is " << node->parent->key << "'s " << "right child" << endl;
			}
		}

		if (node->left != nil) printNode(node->left);
		if (node->right != nil) printNode(node->right);
	}

	Node* findNode(Node* node, keyType key) {
		if (key == node->key) return node;
		if (node == nil) throw out_of_range("Couldn't find key in the RBTree");
		if (key < node->key) return findNode(node->left, key);
		else return findNode(node->right, key);
	}

public:
	Map() { //constructor
		size = 0;
		nil = new Node;
		nil->color = black;
		nil->left = NULL;
		nil->right = NULL;
		root = nil;
	}

	~Map() {
		clear();
	}

	void insert(keyType key, valueType value) {
		size++;

		Node* newNode = new Node;
		newNode->key = key;
		newNode->value = value;
		newNode->left = nil;
		newNode->right = nil;
		newNode->color = red;
		newNode->parent = NULL;

		Node* x = root;
		Node* y = NULL;

		while (x != nil) {
			y = x;
			if (newNode->key < x->key)
				x = x->left;
			else
				x = x->right;
		}
		newNode->parent = y;

		if (y == NULL) root = newNode;
		else if (newNode->key < y->key) y->left = newNode;
		else y->right = newNode;

		if (newNode->parent == NULL) newNode->color = black;
		else if (newNode->parent->parent != NULL) insertFixUp(newNode);
	}

	void remove(keyType key) {
		if (root == NULL) throw invalid_argument("List is empty");
		else {
			Node* nodeToBeDeleted = nil;
			Node* x;
			Node* y;
			Node* bufNode;

			nodeToBeDeleted = find(key);
			color originalColor = nodeToBeDeleted->color;
			y = nodeToBeDeleted;

			if (nodeToBeDeleted->left == nil) {
				x = nodeToBeDeleted->right;
				// Moving x to the nodeToBeDeleted location
				if (nodeToBeDeleted->parent == NULL) root = x;
				else if (nodeToBeDeleted == nodeToBeDeleted->parent->left) nodeToBeDeleted->parent->left = x;
				else nodeToBeDeleted->parent->right = x;
				x->parent = nodeToBeDeleted->parent;
			}
			else if (nodeToBeDeleted->right == nil) {
				x = nodeToBeDeleted->left;
				//Moving x to the nodeToBeDeleted location
				if (nodeToBeDeleted->parent == nil) root = x;
				else if (nodeToBeDeleted == nodeToBeDeleted->parent->left) nodeToBeDeleted->parent->left = x;
				else nodeToBeDeleted->parent->right = x;
				x->parent = nodeToBeDeleted->parent;
			}
			else {
				y = nodeToBeDeleted->right;
				while (y->left != nil) { //minimum
					y = y->left;
				}
				originalColor = y->color;
				x = y->right;
				if (y->parent == nodeToBeDeleted) {
					x->parent = y;
				}
				else {
					bufNode = y->right;
					//Moving y->right to the y location
					if (y->parent == NULL) root = bufNode;
					else if (y == y->parent->left) y->parent->left = bufNode;
					else y->parent->right = bufNode;
					bufNode->parent = y->parent;
				}
				//Moving y to the nodeToBeDeleted location
				if (nodeToBeDeleted->parent == NULL) root = y;
				else if (nodeToBeDeleted == nodeToBeDeleted->parent->left) nodeToBeDeleted->parent->left = y;
				else nodeToBeDeleted->parent->right = y;
				y->parent = nodeToBeDeleted->parent;

				y->left->parent = y;
				y->color = nodeToBeDeleted->color;
			}
			delete nodeToBeDeleted;
			size--;

			if (originalColor == black) removeFixUp(x);
		}
	}

	Node* find(keyType key) {
		return findNode(root, key);
	}

	void clear() {
		deleteNode(root);
		root = NULL;
		size = 0;
	}

	List <keyType> get_keys() {
		List<keyType>* listKeys = new List<keyType>;
		getListOfKeys(root, listKeys);
		return *listKeys;
	}

	List<valueType> get_values() {
		List<valueType>* listValues = new List<valueType>;
		getListOfValues(root, listValues);
		return *listValues;
	}

	void print() {
		if (root == NULL)
			throw invalid_argument("Map is empty");
		else
			printNode(root);
	}

	int mapSize() {
		return size;
	}
};
