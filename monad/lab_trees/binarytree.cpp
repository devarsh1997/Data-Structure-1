/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    mirrorHelp(root);
    // your code here
}

template <typename T>
void BinaryTree<T>::mirrorHelp(Node*& n)
{
    if(n == NULL) return;
    Node* temp = n->left;
    n->left = n->right;
    n->right = temp;
    mirrorHelp(n->left);
    mirrorHelp(n->right);
    // your code here
}


/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const 
{
    return isOrderedHelp(root);
}

template <typename T>
bool BinaryTree<T>::isOrderedHelp(Node* n) const
{
    vector<T>out(inOrderTraversal(n));
    for(int i = 0; i < (int)out.size() - 1; i++)
    {
        if(out[i] >= out[i+1]) return false;
    }
    return true;
}

template <typename T>
vector<T> BinaryTree<T>::inOrderTraversal(Node* n1) const
{
    vector<T> v;
    inOrderTraversalHelp(n1, v);
    return v;
}

template <typename T>
void BinaryTree<T>:: inOrderTraversalHelp(Node* n2, vector<T>& vec) const
{
    if(n2 != NULL)
    {
        inOrderTraversalHelp(n2->left, vec);
        vec.push_back(n2->elem);
        inOrderTraversalHelp(n2->right, vec);
    }
}


/**
 * Prints out all the possible paths from the root of the tree to any leaf node.
 * That is, all sequences starting at the root node and continuing downwards,
 * ending at a leaf node. Paths ending in a left node should be printed before
 * paths ending in a node further to the right.
 */
template <typename T>
void BinaryTree<T>::printPaths() const
{
    vector<T>v;
    printPathsHelp(root, v);
    // your code here
}

template <typename T>
void BinaryTree<T>::printPathsHelp(Node* n, vector<T>& vec) const
{
    if(n == NULL) return;
    if(n != NULL) vec.push_back(n->elem);
    printPathsHelp(n->left, vec);
    printPathsHelp(n->right, vec); 
    if(n->left == NULL && n->right == NULL)
    {
        cout << "Path: ";
        for(int i = 0; i < (int)vec.size(); i++)
        {
            cout << vec[i] << " ";
        }
        cout << endl;
    }
    vec.pop_back();
    
}



/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    vector<T> v;
    sumDistancesHelp(root, v);
    int sum = 0;
    for(int i = 0; i < (int)v.size(); i++)
    {
        sum = sum + v[i];
    }
    return sum;
}

template <typename T>
void BinaryTree<T>::sumDistancesHelp(Node* n, vector<T>& vec) const
{
    if(n != NULL){
        sumDistancesHelp(n->left, vec);
        vec.push_back(distance(root, n, 0));
        sumDistancesHelp(n->right, vec);
    } 
    
}
template <typename T>
int BinaryTree<T>::distance(Node* start, Node* n, int length) const
{
    if(start == NULL) return 0;
    if(start == n) return length;
    int result = distance(start->left, n, length + 1);
    if(result != 0) return result;
    result = distance(start->right, n, length + 1);
    return result;
    
    
    // your code here
}




