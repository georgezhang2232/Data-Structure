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
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* curr = t->right;
    t->right = curr->left;
    curr->left = t;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right)) + 1;
    t = curr;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* curr = t->left;
    t->left = curr->right;
    curr->right = t;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right)) + 1;
    t = curr;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    int balanceTop = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if (balanceTop == 2){
      int balanceRight = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
      if (balanceRight == 1){
        rotateLeft(subtree);
      }
      else if (balanceRight == -1){
        rotateRightLeft(subtree);
      }
    }

    if (balanceTop == -2){
      int balanceLeft = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
      if (balanceLeft == -1){
        rotateRight(subtree);
      }
      else if (balanceLeft == 1){
        rotateLeftRight(subtree);
      }
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
    if (subtree == NULL){
      subtree = new Node(key, value);
    }
    else if (key < subtree->key){
      insert (subtree->left, key, value);
    }
    else if (key > subtree->key){
      insert (subtree->right, key, value);
    }
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
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);

    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* iop = subtree->left;
            while (iop->right != NULL) {
              iop = iop->right;
            }
            swap(subtree, iop);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
            Node* left = subtree->left;
            Node* right = subtree->right;
            delete subtree;
            if (left == NULL) {
              subtree = right;
            }
            else {
              subtree = left;
            }
        }
        // your code here

    }
    if (subtree != NULL){
      rebalance(subtree);
    }
}
