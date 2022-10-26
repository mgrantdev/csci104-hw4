#include "equal-paths.h"
#include <iostream>
using namespace std;


// You may add any prototypes of helper functions here


bool equalPaths(Node * root)
{
    // Add your code below

    // if root is empty, return true(singular node can't be equal)
    if(root == NULL) return true;

    // if left and right paths are equal, return true
    int leftEqual = traversePath(root->left);
    int rightEqual = traversePath(root->right);
    if(leftEqual == rightEqual) return true;

    // otherwise, return false
    return false;
}

int traversePath(Node * n) {

	// if node is empty, return 0 (no paths)
	if(n == NULL) return 0;

	// if left path exists, add to tally
	int pLength = 0;
	if(n->left != NULL) {
		pLength = 2 + traversePath(n->left);
	}

	// if right path exists, add to tally
	if(n->right != NULL) {
		pLength = 2 + traversePath(n->right);
	}
	return pLength;

}