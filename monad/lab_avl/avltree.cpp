/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    if(t == NULL)
        return;
    if(t->right == NULL) 
        return;
    Node* t2 = t->right;
    t->right = t2->left;
    t2->left = t;
    t->height = max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    t2->height = max(heightOrNeg1(t2->left), heightOrNeg1(t2->right)) + 1;
    t = t2;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // Implemented for you:

    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    if(t == NULL) 
        return;
    if(t->left == NULL) 
        return;
    Node* t2 = t->left;
    t->left = t2->right;
    t2->right = t;
    t->height = max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    t2->height = max(heightOrNeg1(t2->left), heightOrNeg1(t2->right)) + 1;
    t = t2;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here

    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(subtree == NULL)
        return;
    if(heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right) > 1)
    {
        if(heightOrNeg1(subtree->left->left) >= heightOrNeg1(subtree->left->right))
            rotateRight(subtree);
        else
            rotateLeftRight(subtree);
    }
    else if(heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left) > 1)
    {
        if(heightOrNeg1(subtree->right->right) > heightOrNeg1(subtree->right->left))
            rotateLeft(subtree);
        else
            rotateRightLeft(subtree);
    }
    
    subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL){
        subtree = new Node(key, value);
    }
    else if(subtree->key > key)
        insert(subtree->left, key, value);
    else if(subtree->key < key)
        insert(subtree->right, key, value);
        
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } 
    else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            Node* orig = subtree;
            subtree = NULL;
            delete orig;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            
            Node* iop = subtree->left;
            Node* prev = subtree->left;
            while(iop->right != NULL){
                prev = iop;
                iop = iop->right;
            }
            swap(iop, subtree);
            remove(iop, key);
            prev->right = NULL;   
            
        } else {
            /* one-child remove */
            // your code here
            Node* orig = subtree;
            if(subtree->left != NULL) 
                subtree = subtree->left;
            if(subtree->right != NULL)
                subtree = subtree->right;
            delete orig;
        }
        // your code here 
    }
    rebalance(subtree);
}


