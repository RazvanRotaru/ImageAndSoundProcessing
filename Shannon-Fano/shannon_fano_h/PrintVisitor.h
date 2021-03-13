#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../utils/Node.h"
#include "../utils/Visitor.h"


class PrintVisitor : public Visitor<Node <std::vector <std::string> > > {
public:
	void visit(Node<vector <std::string> >* node) {
		if (node->isRoot())
			std::cout << "ROOT: ";
		printData(node);

		if (node->getLChild() != nullptr) {
			std::cout << "L" << node->getLevel() << ": ";
			visit(node->getLChild());
		}
		
		if (node->getRChild() != nullptr) {
			std::cout << "R" << node->getLevel() << ": ";
			visit(node->getRChild());
		}
	}
private:
	void printData(Node<std::vector <std::string> >* node) {
		int spacings = node->getLevel();
		for (int i = 0; i < spacings; i++)
			cout << "--";
		
		cout << "> [";
		std::vector<std::string> data = node->getData();
		int size = data.size();
		for (int i = 0; i < size; i++) {
			std::cout << data[i];
			if (i < size - 1)
				std::cout << ", ";
		}
		std::cout << "]" << std::endl;	
	}
};