#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "../utils/Node.h"
#include "../utils/Visitor.h"
#include "../utils/Helper.h"

using namespace std;

class EvenlySplitVisitor : public Visitor<Node <vector <string> > > {
public:
	EvenlySplitVisitor(map<string, float> value) {
		this->value = value;
	}

	void visit(Node<vector <string> >* node) {
		if (node->getData().size() <= 1)
			return;
		
		splitEvenly(node);

		if (node->getLChild() != nullptr)
			visit(node->getLChild());
		if (node->getRChild() != nullptr)
			visit(node->getRChild());
	}

private:
	map<string, float> value;

	void splitEvenly(Node<vector <string> >* node) {
		vector<string> array = node->getData();
		
		int typesNo = array.size();
		if (typesNo <= 1)
			return;

		float desiredSum = getArraySum(array, value) / 2;

		vector< vector<bool> > mat(typesNo, vector<bool>(desiredSum + 1, false));
		solveMatrix(mat, array);

		float maxSum = getMaxSum(mat);
		vector<string> lValues, rValues; 

		lValues = reconstructSolution(mat, array, maxSum);
		node->addLChild(lValues);
		rValues = getDifference(array, lValues);
		node->addRChild(rValues);
	}

	void solveMatrix(vector <vector<bool> > &mat, vector<string> array) {
		int typesNo = mat.size();
		int desiredSum = mat[0].size();

		for (int i = 0; i < typesNo; i++)
			mat[i][0] = true;

		for (int j = 0; j <= desiredSum; j++)
			if (j == value[array[0]])
				mat[0][j] = true;

		for (int i = 1; i < typesNo; i++)
			for (int j = 1; j <= desiredSum; j++) {
				if (mat[i-1][j])
					mat[i][j] = true;
				else
					if (j >= value[array[i]])
						mat[i][j] = mat[i-1][j-value[array[i]]];
			}
	}

	float getMaxSum(vector <vector<bool> > mat) {
		int typesNo = mat.size();
		int desiredSum = mat[0].size() - 1;
		float maxSum = 0;

		for (int j = desiredSum; j > 0; j--)
			if (mat[typesNo-1][j]) {
				maxSum = j;
				break;
			}

		return maxSum;
	}

	vector<string> reconstructSolution(vector <vector<bool> > mat,
										vector<string> array, float maxSum) {
		int typesNo = mat.size();
		int j = maxSum;
		vector<string> ans;

		for (int i = typesNo - 1; i >= 0; i--) {
			if (i == 0 && mat[i][j]) {
				ans.push_back(array[i]);
				break;
			}
				
			if (mat[i][j] != mat[i-1][j]) {
				ans.push_back(array[i]);
				j -= value[array[i]];
				if (j == 0)
					break;
			}
		}

		return ans;
	}
};