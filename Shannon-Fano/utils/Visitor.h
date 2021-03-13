#pragma once

template <class T>
class Visitor {
public:
	virtual void visit(T* x) {}
};