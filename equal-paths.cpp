#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here


bool equalPaths(Node * root)
{
    // Add your code below

    // if root is empty, return false (singular node can't be equal)
    if(root == NULL) return false;

    // if left and right paths are equal, return true
    bool leftEqual = equalPaths(root->left);
    bool rightEqual = equalPaths(root->right);
    if(leftEqual == rightEqual) return true;

    // otherwise, return false
    return false;
}

