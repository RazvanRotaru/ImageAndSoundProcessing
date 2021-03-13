#pragma once

#include "../utils/Visitor.h"
#include "EvenlySplitter.h"
#include "PrintVisitor.h"
#include "CodeRetriever.h"
#include "../utils/Node.h"
#include "../utils/DataContainer.h"

class ShannonFanoSolver : public Visitor<DataContainer> {
public:
	
	ShannonFanoSolver(std::string v) {
		this->verbose = false;
		if (v.compare("-v") == 0 || v.compare("--verbose") == 0)
			this->verbose = true;
	}
    
	void visit(DataContainer* s) {
        Node< std::vector<std::string> >* root = 
                        new Node< std::vector<std::string> >(s->getTypes());
		
		EvenlySplitVisitor* v = new EvenlySplitVisitor(s->getValues());
		root->accept(v);
		delete v;
		
		if (verbose) {
			PrintVisitor *p = new PrintVisitor();
			root->accept(p);
			delete p;
		}
		
		CodeRetriever *c = new CodeRetriever();
		root->accept(c);
		map<std::string, std::string> codes = c->getCodes();
		delete c;

        s->writeOutput(codes);
		s->printResult(codes);
    }

private:
	bool verbose;
};