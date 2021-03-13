#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "../utils/Node.h"
#include "../utils/Visitor.h"

using namespace std;

class CodeRetriever: public Visitor<Node <vector <string> > > {
public:
	void visit(Node<vector <string> >* node) {
		getCode(node, "");
	}

	void printCodes() {
		for (map<string, string>::const_iterator it = codes.begin(); 
			it != codes.end(); it++)
			cout << it->first << ":" << it->second << endl;
	}

	map<string, string> getCodes() {
		return codes;
	}

private:
	void getCode(Node<vector <string> >* node, string code) {
		if (node == nullptr)
			return;

		if (node->isLeaf()) {
			codes[node->getData()[0]] = code;
			return;
		}

		getCode(node->getLChild(), code + "0");
		getCode(node->getRChild(), code + "1");
	}

	map<string, string> codes;
};