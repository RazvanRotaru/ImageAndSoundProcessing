#pragma once

template <class T>
class Node {
public:
	Node(T data) {
		this->data = data;
		this->level = 0;

		parent = nullptr;
		lChild = nullptr;
		rChild = nullptr;
	}
	
	Node(Node* parent, T data) {
		this->data = data;
		this->parent = parent;
		this->level = parent->level + 1;

		lChild = nullptr;
		rChild = nullptr;
	}

	~Node() {
		if (parent != nullptr)
			delete parent;
		if (lChild != nullptr)
			delete lChild;
		if (rChild != nullptr)
			delete rChild;
	}

	void addLChild(T data) {
		Node* child = new Node<T>(this, data);
		lChild = child;
	}

	void addRChild(T data) {
		Node* child = new Node<T>(this, data);
		rChild = child;
	}

	void accept(Visitor<Node <T> >* v) {
		v->visit(this);
	}

	T getData() {
		return data;
	}

	int getLevel() {
		return level;
	}

	Node<T>* getLChild() {
		return lChild;
	}

	Node<T>* getRChild() {
		return rChild;
	}

	bool isRoot() {
		return parent == nullptr;
	}

	bool isLeaf() {
		return lChild == nullptr && rChild == nullptr;
	}

protected:
	Node<T>* parent;

	Node<T>* lChild;
	Node<T>* rChild;

	int level;
	T data;
};
