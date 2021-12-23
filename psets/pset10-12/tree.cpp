//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]

/// File: tree.cpp, treeDriver.cpp, tree.h, treenode.h
/// implements a binary tree and/or binary search tree(BST).* and
/// AVL(Adelson-Velskii and Landis) tree.
///
/// A binary search tree BST is a type of binary tree where the nodes
/// are arranged in order: for each node, all elements in its left
/// subtree are less to to node and all the elements in its right
/// subtree are greater than the node. Many operations are the same
/// either in a binary tree or in a binary search tree.
///
/// - Some functions work for a binary tree and/or for a BST.
/// - The code works on the node structure 'tree' that makes up the tree.
/// - The algorithm, typically recursive, that iterates over the tree
/// - Using a pointer to a pointer as an argument have been avoided.
///   Instead the function is to return a new root node after an
///   insertion or deletion, then it returns the root node as a
///   returned value.
///
/// 04/20/2014	Created by idebtor@gmail.com
/// 04/15/2016	treeprint() added for clearer visualization of tree
/// 05/01/2016	Added AVL tree
/// 04/02/2019	C++ version, utilized stl::vector and stl::queue partially
/// 04/30/2020	Added tasty mode print, LCA, [BT] functions
/// 05/05/2020	findPath() & findPathBack() created
/// 10/31/2020  the 'range' argument is removed in rand_extended()
///
/// Usage:
///   tree left = new TreeNode(1);
///   tree right = new TreeNode(2);
///   tree root - new TreeNode(3, left, right);
/// or
///   tree root = grow(nullptr, 2);
///   root = grow(root, 1);
///   root = grow(root, 3);	// a new node is added
///   root = trim(root, 5);	// if first node is removed,
///          

#include <iostream>
#include <cassert>
#include <climits>
#include <ctime>
#include <vector>
#include <queue>
#include <set>
#include "tree.h"
#include <algorithm>

using namespace std;

void treeprint(tree t);        // print the tree on console graphically

// returns the degree of a node, not a tree
int degree(tree t) {//완료
	int d = 0;
	if (t->left != nullptr) d++;
	if (t->right != nullptr) d++;
	return d;
}

// returns the max depth of a tree. It is the same as the number of edges 
// along the longest path from the root node down to the farthest leaf node.
// height = -1 for empty tree, 0 for root only tree
int height(tree node) {//완료
	if (empty(node)) return -1;
    int left = height(node -> left);
    int right = height(node -> right);
    return max(left,right) +1;
}

// Computes the size of the binary tree dyamically by
// traversing the nodes recursively.
int size(tree node) {//완료
	if (empty(node)) return 0;
	return size(node -> left) + size(node -> right) + 1;
}

bool empty(tree t) {//완료
	return t == nullptr;
}

int value(tree t) {//완료
	if (!empty(t)) return t->key;
	return 0;
}
 
// frees all nodes while traversing the tree like postorder
tree clear(tree t) {
	if (empty(t)) return nullptr;
	
    clear(t->left);
    clear(t->right);
    delete t;
	return nullptr;
}

// does there exist a node with given key?
// search a key in binary search tree(BST) recursively.
bool contains(tree node, int key) {
	if (empty(node)) return false;
    //돌아오는 조건.
    if(node -> key == key) return true;
	//들어가는 조건.
    else if(node -> key > key){
        return contains(node->left, key);
    }
    else
        return contains(node->right, key);
}

// does there exist a node with given key?
// search a key in binary tree(BT) recursively.
bool containsBT(tree node, int key) {//완료
	if (empty(node)) return false;
    if(key == node -> key) return true;
    
    return containsBT(node -> left,key) || containsBT(node -> right,key);
}

// does there exist a key-value pair with given key?
// search a key in binary search tree(BST) iteratively
bool containsIteration(tree node, int key) {
	if (empty(node)) return false;
	DPRINT(cout << ">containsIteration root key=" << node->key << endl;);
	while (node) {
		if (key == node->key) return true;
		node = key < node->key ? node->left : node->right;
	}
	return false;
}

// returns a node with a key given if found in BST, otherwise nullptr.
tree find(tree node, int key) {//완료//binary search tree는 왼쪽은 root보다 작은값, 오른쪽은 큰값.
	if (empty(node)) return nullptr;

	if (key == node->key) return node;
	if (key < node->key)
		return find(node->left, key);
	return find(node->right, key);
}

// returns a node with a key given if found in BT, otherwise nullptr.
tree findBT(tree root, int key) {//완료
	if (empty(root)) return nullptr;
    if(key == root -> key) return root;
    
    tree x = findBT(root -> left, key);
    if(x != nullptr) return x;
    
    return findBT(root->right,key);
}

// returns true if the node x is found and the path from node x to root
// Do not call finaPath() and reverse it. 
bool findPathBack(tree root, tree x, vector<int>& path) {//완료
	if (root == nullptr) return false;
    
    if(root->key == x->key) {
        path.push_back(root->key);
        return true;
    }
    if(findPathBack(root->left,x,path)||findPathBack(root->right,x,path)){
        path.push_back(root->key);
        return true;
    }
    else{
        return false;
    }

	return false;
}  // path from node x to root is produced.

// returns true if the node x is found and a vector loaded with a path 
// from root to the node x
// Do not call finaPathBack() and reverse it. 
bool findPath(tree node, tree x, vector<int>& path) {//완료
	DPRINT(cout << ">findPath size=" << path.size() << endl;);
	if (empty(node)) return false;

    path.push_back(node->key);
    if(node->key == x->key) return true;
    
    if(findPath(node->left,x,path)||findPath(node->right,x,path)){
        return true;
    }
    else{
        path.pop_back();
        return false;
    }
    
	DPRINT(cout << "<findPath not found, pop:" << node->key << endl;);
}

// returns a node with a key given if found in BT, otherwise nullptr.
tree findParent(tree t, int key, tree parent) {
	if (empty(t)) return nullptr;

	if (t->key == key) return parent;

	tree node = findParent(t->left, key, t);
	if (node != nullptr) return node;
	return findParent(t->right, key, t);
}

// inserts a new node with the key in given binary search tree and
// returns the new node such that client use it properly.
tree grow(tree node, int key) {
	DPRINT(cout << ">grow key=" << key << endl;);
	if (node == nullptr) return new TreeNode(key);

    if(key < node ->key){
        node -> left = grow(node ->left,key);
    }
    else if(key > node -> key){
       node -> right = grow(node -> right, key);
    }
	// do nothing, the duplicate key is not allowed
	DPRINT(cout << "<grow returns key=" << node->key << endl;);
	return node;    // eventually returns the original root node
    //이걸 보게 되면 각 조건에서 걸리게 되면 바로 바로 return을 하지 않고, 마지막까지 와서 그 해당 노드를 리턴하게 되어있다. 해당 노드를 리턴함.
}

// inserts a node with the key and returns the root of the binary tree.
// Traversing it in level order, find the first empty node in the tree.
//
// The idea is to do iterative level order traversal of the given tree 
// using queue. 
// First, push the root to the queue. Then, while the queue is not empty,
// Get the front() node on the queue. Check that the left or right is nullptr.
// If the left child of the node is empty, make new key as left child of 
// the node.– breakand return;  else add it to queue to process later 
// since it is not nullptr. If the right child is empty, make new key 
// as right child of the node.– breakand return; else add it to queue 
// to process later since it is not nullptr.  Make sure that you pop 
// the queue finished. Do this until you find a node whose either 
// left or right is empty.
tree growBT(tree root, int key) {//완료
	DPRINT(cout << ">growBT key=" << key << endl;);
    if(root == nullptr)
        return new TreeNode(key);
    tree curr = nullptr;
    queue<tree> q;
    q.push(root);
    while(!q.empty()){
        curr = q.front();
        if(curr -> left == nullptr){
            curr -> left = new TreeNode(key);
            break;
        }
        else q.push(curr -> left);
        if(curr -> right == nullptr){
            curr -> right = new TreeNode(key);
            break;
        }
        else q.push(curr -> right);
        q.pop();
    }
    DPRINT(cout << "<growBT" << endl;);
	return root;    // eventually returns the original root node
}

// creates the complete binary tree from the array in level order traversal.
// When the parent is present at index i, then its two children will be at
// index(2i + 1), and (2i + 2).Thus we can insert leftand right nodes using
// its parent nodes.The first element of the array will be the root of CBT.
tree growBT(tree root, int *arr, int i, int n) {
	DPRINT(cout << ">growBT arr n=" << n << endl;);

	if (i < n) {
		root = new TreeNode(arr[i]);
		root->left = growBT(root->left, arr, 2 * i + 1, n);
		root->right = growBT(root->right, arr, 2 * i + 2, n);
	}
	DPRINT(cout << "<growBT arr" << endl;);
	return root;    // eventually returns the original root node
}

///////////////////////////////////////////////////////////////////
// trim
///////////////////////////////////////////////////////////////////
// removes the node with the key in a tree and returns the new root
tree trim(tree node, int key) {
	if (empty(node)) return node;	 // base case
	DPRINT(cout << ">trim: now we are at: " << node->key << endl;);
    //들어가는 조건들.key보다 작거나 크면 계속들어간다./
	if (key < node->key) // if node to trim is in left subtree.
		node->left = trim(node->left, key);
	else if (key > node->key) // node to trim is in right subtree.
		node->right = trim(node->right, key);
	// found the key: delete the node now 
	// node with two childeren: replace it with the scuccessor or predecessor
    else {//key랑 같으면!! child수 세기
        //no child
        if(node -> right == nullptr && node ->left == nullptr){
            delete node;
            return nullptr;
        }
        //one child
        else if(node -> right == nullptr){
            tree temp = node;
            node = node -> left;
            delete temp;
            return node;
        }
        else if(node -> left == nullptr){
            tree temp = node;
            node = node -> right;
            delete temp;
            return node;
        }
        //two child
        else{
            if(height(node -> left) < height(node -> right)){
                tree suc = succ(node);
                node -> key = suc -> key;
                node -> right = trim(node -> right, suc -> key);
            }
            else{
                tree pre = pred(node);
                node -> key = pre -> key;
                node -> left = trim(node -> left, pre -> key);//node의 왼쪽부터 시작해서 지우고 와라~ pre나 suc은 one child이다.
            }
        }
	}

	DPRINT(if (node != nullptr) cout << "<trim returns: key=" << node->key << endl;);
	DPRINT(if (node == nullptr) cout << "<trim returns: nullptr)\n";);
	return node;
}

// returns a successor of the tree
tree succ(tree node) {//완료
	//들어가는 거랑 돌아오는 조건들이 있음.
    
    //일단 succ랑 pred는 onechild를 가지고 있거나 child를 가지고 있을 수 없다.
    //찾은 node의 오른쪽중 가장 작은거.(element중 걔보다 제일 조금만 큰놈)-> 본인이 nullptr이 아니거나, 본인의 Right가 nullptr이 아니면 바로 minimum찾기.=왼쪽으로 갈떄까지가.
    //그렇지 않으면 돌아와.
    if(node !=nullptr && node -> right != nullptr){//제일 처음 비교하는 거임.
        return minimum(node ->right);
    }
	return nullptr;
}

// returns a predeccessor of the tree
tree pred(tree node) {//완료
    if(node !=nullptr && node -> left != nullptr){//제일 처음 비교하는 거임.
        return maximum(node ->left);
    }
    return nullptr;
}

// Given a binary search tree, return the min or max key in the tree.
// Don't need to traverse the entire tree.
tree maximum(tree node) {//완료			// returns max node
	if (node->right == nullptr) return node;
	return maximum(node->right);
}

tree minimum(tree node) {//완료			// returns min node
	if (node->left == nullptr) return node;
	return minimum(node->left);
}

// Given a binary tree, return the max key in the tree.
tree maximumBT(tree node) {//완료
	if (node == nullptr) return node;
	
    tree max = node;//root 즉 1과 비교를 히는 것임.
    if(node->left != nullptr){
        tree x = maximumBT(node->left);
        if(x->key > max->key) max = x;
    }
    if(node->right != nullptr){
        tree y = maximumBT(node->right);
        if(y->key > max->key) max = y;
    }
	return max;
}

tree minimumBT(tree node) {//완료		// returns min node
	if (node == nullptr) return node;
	
    tree min = node;
    tree x = minimumBT(node->left);
    tree y = minimumBT(node->right);
    if(x!=nullptr && y!=nullptr){
        if(x->key < min->key) min = x;
        if(y->key < min->key) min = y;
    }
    return min;
}

// Given a binary tree, its node values in inorder are passed
// back through the argument v which is passed by reference.
void inorder(tree node, vector<int>& v) {//완료
	if (empty(node)) return;
    inorder(node->left , v);
    v.push_back(node->key);
    inorder(node -> right, v);
}

// returns a vector that has tree nodes in inorder instead of keys.
void inorder(tree node, vector<tree>& v) {//완료
	if (empty(node)) return;
    inorder(node->left , v);
    v.push_back(node);
    inorder(node -> right, v);
}

// Given a binary tree, its node values in postorder are passed
// back through the argument v which is passed by reference.
void postorder(tree node, vector<int>& v) {//완료
    inorder(node->left , v);
    inorder(node -> right, v);
    v.push_back(node->key);
    DPRINT(cout << ">postorder size=" << v.size() << endl;);
	DPRINT(cout << "<postorder key=" << node->key << endl;);
}

// Given a binary tree, its node values in preorder are passed
// back through the argument v which is passed by reference.
void preorder(tree node, vector<int>& v) {//완료
    v.push_back(node->key);
    inorder(node->left , v);
    inorder(node -> right, v);
    DPRINT(cout << ">preorder size=" << v.size() << endl;);
	DPRINT(cout << "<preorder key=" << node->key << endl;);
}

// returns its nodes in level-order passed back through the argument v 
// which is passed by reference. This is also called breadth-first 
// search(BFS), as the search broadened as much as possible on each 
// depth before going to the next depth(level or height).
// Use std::queue to store the nodes during traverse the tree.
// Using queue requires extra space to save nodes in the queue.
// It is proportional to the maximum number of nodes at given depth.
// This can be as much as one half of the total number nodes. O(n)
void levelorder(tree root, vector<int>& vec) {
	DPRINT(cout << ">levelorder";);
	if (empty(root)) return;
    queue<tree> que;
    if(!root) return;
    que.push(root);//일단 제일 처음 root를 넣는다.
    tree curr = nullptr;
    while(!que.empty()){//que가 empty가 아닐때까지.
        curr = que.front();
        vec.push_back(curr->key);
        if(curr->left != nullptr) que.push(curr->left);
        if(curr->right != nullptr) que.push(curr->right);
        que.pop();
    };

	DPRINT(cout << "<levelorder size=" << vec.size() << endl;);
}

// returns LCA(Least Common Ancestor) of a binary tree [BT]
tree LCA_BT(tree root, tree p, tree q) {  // recursive solution
	DPRINT(cout << ">LCA_BT" << endl;);
	// base case 1: no p or q found
	if (root == nullptr) return nullptr;
    
    if(root->key == p->key || root->key == q->key)
        return root;

    tree left_lca = LCA_BT(root->left,p,q);
    tree right_lca = LCA_BT(root->right,p,q);
    
    if(left_lca && right_lca) return root;
	

	return (left_lca != nullptr) ? left_lca : right_lca;
}

// returns LCA(Least Common Ancestor) of a binary tree [BT]
int LCA_BTiteration(tree root, tree p, tree q) {  
	DPRINT(cout << ">LCA_BTiteration" << endl;);
    
    vector<int> p_vec, q_vec;
    
    findPath(root,p,p_vec);
    findPath(root,q,q_vec);
    
    //int answer = 0;
    int i;
    for(i=0; i<p_vec.size(); i++){
        if(p_vec.at(i)!=q_vec.at(i)){
            //answer = p_vec.at(i);
            break;
        }
    }
	return p_vec[i-1];
}

// returns LCA(Least Common Ancestor) of a binary search tree
// The lowest common ancestor is defined between two nodes pand q as the 
// lowest node in T that has both pand q as descendants(where we allow a 
// node to be a descendant of itself). Given BST, two descedents p and q,
// root = [6, 2, 8, 0, 4, 7, 9, null, null, 3, 5], p=2, q=8, then output=6
// root = [6, 2, 8, 0, 4, 7, 9, null, null, 3, 5], p=2, q=4, then output=2 
// since a node can be a descendent of itself according to the LCA definition.
// Notice that both p and q exist and are unique in a given tree by definition. 
tree LCA(tree root, tree p, tree q) {  // recursive solution
	DPRINT(cout << ">LCA" << endl;);
    if(empty(root)) return nullptr;
    
    if(p -> key > root -> key && q -> key > root -> key){
         root = LCA(root -> right,p,q);
    }
    else if(p -> key < root -> key && q -> key < root -> key){
         root = LCA(root -> left,p,q);
    }
    
	

	DPRINT(cout << "<LCA" << endl;);
	return root;
}

int LCAiteration(tree root, tree p, tree q) {  // iteration solution
	DPRINT(cout << ">LCAiteration " << endl;);
    tree curr = root;
    while(curr != nullptr){
        if(p -> key > curr -> key && q -> key > curr -> key){
            curr = curr -> right;
        }
        else if(p -> key < curr -> key && q -> key < curr -> key){
            curr = curr -> left;
        }
        else return curr -> key;
    }
	DPRINT(cout << "<LCAiteration"  << endl;);
	return 0;
}

// does this binary tree satisfy symmetric order?
// is the tree rooted at x a BST with all keys between min and max?
// Another solution: Do an inorder traversal of the tree and store
// the node values in a container. If it is in sorted order,
// its a valid BST otherwise not.
bool isBST(tree x, int min, int max) {//완료
	if (empty(x)) return true;
	DPRINT(cout << ">isBST key=" << x->key << "\t min=" << min << " max=" << max << endl;);
    
    if(x -> key < min || x -> key > max) return false;
    return isBST(x -> left, min, x->key -1) && isBST(x->right,x->key +1,max);

	DPRINT(cout << "<isBST key=" << x->key << "\t min=" << min << " max=" << max << " false\n";);
	return false;
}

// returns true if the tree is a binary search tree, otherwise false.
bool isBST(tree root) {//완료
	if (empty(root)) return true;
	bool result = isBST(root, INT_MIN, INT_MAX);  
	DPRINT(cout << "<isBST result=" << result << endl;);
	return result;
}

// a helper function to get keys in BT and save them in a set.
void get_keys(tree root, set<int> &keys) {
	DPRINT(cout << " >get_keys" << endl;);
	if (root == nullptr) return;
	keys.insert(root->key);
	DPRINT(cout << " get(" << root->key << ") " << endl;);
	get_keys(root->left, keys);
	get_keys(root->right, keys);
	DPRINT(cout << " ><get_keys" << endl;);
}

//////////////////////////////////////////////////////////////////
// define helper functions here to get/set keys for BTtoBST() 

// returns a BST converted from a binary tree in-place. 
// Use a vector or set in STL. Do not use an array to store keys.

void inorder_convert(tree root,vector<int>& vec,int* index_ptr){
    
    if(root == nullptr) return;
    //일단 왼쪽에다가 정렬하기.
    inorder_convert(root->left, vec, index_ptr);
    root -> key = vec.at(*index_ptr);
    (*index_ptr)++;
    inorder_convert(root->right, vec, index_ptr);
}
void BTtoBST(tree root) {
	DPRINT(cout << ">BTtoBST" << endl;);
    //벡터에다가 정렬하기.
    vector<int> v;
    inorder(root,v);
    sort(v.begin(),v.end());
    
    //inorder로 돌아보면서 값을 카피해서 넣기.
    int i =0;
    inorder_convert(root,v,&i);

	DPRINT(cout << ">BTtoBST" << endl;);
}

///////////////// stress test - insert, trim ////////////////////

// returns an extended random number of which the max_range is from 0
// to (RAND_MAX + 1)^2 - 1. // We do this since rand() returns too 
// small range [0..RAND_MAX) where RAND_MAX is usually defined as 
// 32767 in cstdlib. Refer to the following link for details
// https://stackoverflow.com/questions/9775313/extend-rand-max-range
unsigned long rand_extended() {
	if (RAND_MAX >= 1000000) return rand();
	return rand() * RAND_MAX + rand();
}

// shuffles an int array contents
void shuffle(int* arr, int N) {
	DPRINT(cout << ">shuffle N=" << N << endl;);
	if (N <= 1) return;

	srand((unsigned int)time(nullptr));
	DPRINT(srand(0));    // for the same sequence of rand() for debugging
	for (int i = 0; i < N; i++) {
		int x = rand_extended() % (N - 1);
		int t = arr[i];
		arr[i] = arr[x];
		arr[x] = t;
	}
	DPRINT(cout << "<shuffled" << endl;);
}

void shuffle(vector<int>& v, int N) {
    DPRINT(cout << ">shuffle N=" << N << endl;);
    if (N <= 1) return;

    srand((unsigned int)time(nullptr));
    DPRINT(srand(0));    // for the same sequence of rand() for debugging
    for (int i = 0; i < N; i++) {
        int x = rand_extended() % (N - 1);
        int t = v.at(i);
        v.at(i)= v.at(x);
        v.at(x) = t;
    }
    DPRINT(cout << "<shuffled" << endl;);
}

// returns an int array that has randomly mixed numbers
// between start to start + N
void randomN(int* arr, int N, int start) {
	DPRINT(cout << ">random N=" << N << endl;);
	for (int i = 0; i < N; i++)
		arr[i] = start + i;
	shuffle(arr, N);

#ifdef DEBUG
	cout << "randomN: ";
	for (int i = 0; i < N; i++) cout << arr[i] << " ";
	cout << "\n";
	cout << "<random" << endl;
#endif
}

// inserts N numbers of keys in the tree(AVL or BST), based
// on the current menu status.
// If it is empty, the key values to add ranges from 0 to N-1.
// If it is not empty, it ranges from (max+1) to (max+1 + N).
// For AVL tree, use BST grow() and reconstruct() once at root.
tree growN(tree root, int N, bool AVLtree) {
	DPRINT(cout << ">growN N=" << N << endl;);
	int start = empty(root) ? 0 : value(maximum(root)) + 1;

	int* arr = new (nothrow) int[N];
	assert(arr != nullptr);
	randomN(arr, N, start);

	for (int i = 0; i < N; i++) root = grow(root, arr[i]);

	////////////// use this line with AVL code completion /////////
	if (AVLtree) root = reconstruct(root);

	delete[] arr;
	DPRINT(cout << "<growN size=" << size(root) << endl;);
	return root;
}

// removes randomly N numbers of nodes in the tree(AVL or BST).
// It gets N node keys from the tree, trim one by one randomly.
// For AVL tree, use BST trim() and reconstruct() once at root.
tree trimN(tree root, int N, bool AVLtree) {
	DPRINT(cout << ">trimN N=" << N << endl;);
   
    /*
      Step 1:
     1. Get a list of all keys from the tree first.
     2. Invoke inorder() to fill a vector with keys in the tree.
     (Use a vector object in C++ to store all keys. The vector size grows as needed.)*/
    vector<int> vec;
    inorder(root,vec);//모든 키를 저장함.
    
    /*
     3. Get the size of the tree using size()*/
    int capa = vec.size();
    show_vector(vec,capa);
    /*
     4. Compare the tree size and the vector size returned from inorder() for checking.
      Step 2:
     1. Shuffle the vector with keys. – shuffle()
      
     Once you make the trim option successfully using the successor of the node, now you are ready to improve it. When you keep on deleting a node using the successor, the tree tends to be skewed since the node will be trimmed from the right subtree.
     You must make your trim() function such that it checks the heights of the left subtree and right subtree and decide whether you use either the predecessor or the successor in your trim operation to balance the tree if possible.
          9
     Last updated: 4/30/2021
     Now I C
     tree.docx
     2.
   If you don’t take this step, you end up deleting nodes sequentially from the root of the
   tree which is not our intention.
     */
    /*
      Step 3:
     1.
     Invoke trim() N times with a key from the array in sequence. Recall that, Inside a for loop, trim() may return a new root of the tree.
     */
    
    tree newroot = root;
    if(capa == size(root)){
        shuffle(vec,capa);
        show_vector(vec,capa);
        for(int i=0; i<N; i++){
            newroot = trim(newroot,vec.at(i));
        }
    }
	////////////// use this line with AVL code completion /////////
	// if (AVLtree) root = reconstruct(root);

	DPRINT(cout << "<trimN size=" << size(root) << endl;);
	return newroot;
}

////////////////////////// AVL Tree ///////////////////////////////
bool balanced(tree node) {//완료
	int factor = balanceFactor(node);
	return (factor >= -1 && factor <= 1) ? true : false;
}

// returns the balance factor or (height of left - height of right)
int balanceFactor(tree node) { //완료
	DPRINT(cout << " bf" << endl;);
	if (empty(node)) return 0;
    int left = height(node -> left);
    int right = height(node -> right);
	return left -right;
}

// returns true if the tree is AVL tree.
// this is a helper function for isAVL().
bool _isAVL(tree root) {//완료
	if (!balanced(root)) return false;
	if (root->left != nullptr && !_isAVL(root->left))  return false;
	if (root->right != nullptr && !_isAVL(root->right)) return false;
	return true;
}
bool isAVL(tree root) {//완료
	if (empty(root)) return true;
	if (!isBST(root)) return false;
	return _isAVL(root);
}

tree rotateLL(tree A) {//완료
	DPRINT(cout << "\t[LL]case at " << A->key << endl;);
	cout << "\t[LL]case at " << A->key << endl;
    tree B = A -> left;
    A -> left = B -> right;
    B -> right = A;
	return B;
}

tree rotateRR(tree A) {//완료
	DPRINT(cout << "\t[RR]case at " << A->key << endl;);
	cout << "\t[RR]case at " << A->key << endl;
    tree B = A -> right;
    A -> right = B -> left;
    B -> left = A;
	return B;
}

tree rotateLR(tree A) {//완료
	DPRINT(cout << "\t[LR]case at " << A->key << endl;);
	cout << "\t[LR]case at " << A->key << endl;
    tree B = A -> left;
    A -> left = rotateRR(B);
    return rotateLL(A);
}

tree rotateRL(tree A) {//완료
	DPRINT(cout << "\t[RL]case at " << A->key << endl;);
	cout << "\t[RL]case at " << A->key << endl;
    tree B  = A -> right;
    A -> right = rotateLL(B);
    return rotateRR(A);
}

// rebalnces at the node only, not recursively, and
// returns the node that may be different from the input node
tree rebalance(tree node) {//완료
	DPRINT(cout << ">rebalance at:" << node->key << endl;);

	// get balance factor first
    int bf = balanceFactor(node);
    if( bf == 2){
        if(balanceFactor(node -> left) == 1){
            return rotateLL(node);
        }
        else return rotateLR(node);
    }
    else if( bf == -2){
        if(balanceFactor(node -> right) == -1){
            return rotateRR(node);
        }
        else return rotateRL(node);
    }
	//일단 balacefactor을 파악한다.언제까지파악하는지/
    /*
    //Q.이걸 이론상으로는 돌아가면서 차례 차례 검사하기로 했지않냐.
     */
	DPRINT(cout << "<no rebalance " << endl;);
	return node;
}

// rebuilds an AVL/BST tree with a list of keys sorted.
// v – an array of keys sorted, n – the array size
tree buildAVL(int* v, int n) {  // recreation method
	if (n <= 0) return nullptr;
	DPRINT(cout << ">buildAVL v[0]=" << v[0] << " n=" << n << " mid=" << n / 2 << endl;);
    int mid = n/2;
    tree root = new TreeNode(v[mid]);//v의 중간값으로 노드를 만들어 그걸 root로 해줌. 그리고,
    root -> left = buildAVL(v,mid);//왼쪽으로 가서 왼쪽의 중간값을 기존 root의 왼쪽으로.
    root -> right= buildAVL(v+mid+1,n-mid-1);
	return root;
}

// rebuilds an AVL/BST tree using a list of nodes sorted, no memory allocations
// v – an array of nodes sorted, n – the array size
tree buildAVL(tree* v, int n) {  // recycling method
	if (n <= 0) return nullptr;
	DPRINT(cout << ">buildAVL v[0]=" << v[0] << " n=" << n << " mid=" << n / 2 << endl;);
    int mid = n/2;
    
    tree root = v[mid];
    
    root -> left = buildAVL(v,mid);//왼쪽으로 가서 왼쪽의 중간값을 기존 root의 왼쪽으로.
    root -> right= buildAVL(v+mid+1,n-mid-1);

	DPRINT(cout << "<buildAVL" << n << endl;);
	return root;
}

// reconstructs a new AVL tree in O(n), Actually it is O(n) + O(n).
// Use the recreation method if the size is less than or equal to 10 
// Use the recycling method if the size is greater than 10.
// recreation method: creates all nodes again from keys 
// recycling method: reuses all the nodes, no memory allocation needed
tree reconstruct(tree root) {
	DPRINT(cout << ">reconstruct " << endl;);
	if (empty(root)) return nullptr;

	if (size(root) > 10) {
        vector<tree> v_tree;
        inorder(root,v_tree);
        root = buildAVL(v_tree.data(),(int)v_tree.size());
        // recycling method 매우 효율적(node자체를 sort해서 링크만 바꿔줌.)
		                      // use new inorder() that returns nodes sorted
		                      // O(n), v.data() - the array of nodes(tree) sorted
		// root = buildAVL(v.data(), (int)v.size()); // O(n)
	}
	else {
        vector<int> v_key;
        inorder(root,v_key);
        root = buildAVL(v_key.data(),(int)v_key.size());
        // recreation method 조금 비효율적.
		                      // use inorder() that returns keys sorted
	                          // O(n), v.data() - the array of keys(int) sorted
		                      // clear root 
		// root = buildAVL(v.data(), (int)v.size()); // O(n)
	}
	DPRINT(cout << "<reconstruct " << endl;);
	return root;
}

// inserts a key into the AVL tree and rebalance it.
tree growAVL(tree node, int key) {//완료
	DPRINT(cout << ">growAVL key=" << key << endl;);
	if (empty(node)) return new TreeNode(key);

    if(key < node ->key){
        node -> left = growAVL(node ->left,key);
    }
    else if(key > node -> key){
       node -> right = growAVL(node -> right, key);
    }
    //여기서도 모든노드가 이 아래에 rebalance를 거치고 가게 된다.따라서 매번 검사하고 바꾸는 것임.
	return rebalance(node);      // O(log n)
}

// removes a node with key in the AVL tree and rebalance it.
tree trimAVL(tree node, int key) {//완료
	DPRINT(cout << ">trimAVL key=" << key << " at " << node->key << endl;);

	// step 1 - BST trim as usual
	if (empty(node)) return node;	// base case

	// then node to trim must be in left subtree.
	if (key < node->key)
		node->left = trimAVL(node->left, key);
	// then node to trim must be in right subtree.
	else if (key > node->key)
		node->right = trimAVL(node->right, key);
	// node with two childeren: replace it with the successor or predecessor
    else {//key랑 같으면!! child수 세기
        //no child
        if(node -> right == nullptr && node ->left == nullptr){
            delete node;
            return nullptr;
        }
        //one child
        else if(node -> right == nullptr){
            tree temp = node;
            node = node -> left;
            delete temp;
            return node;
        }
        else if(node -> left == nullptr){
            tree temp = node;
            node = node -> right;
            delete temp;
            return node;
        }
        //two child
        else{
            if(height(node -> left) < height(node -> right)){
                tree suc = succ(node);
                node -> key = suc -> key;
                node -> right = trimAVL(node -> right, suc -> key);
            }
            else{
                tree pre = pred(node);
                node -> key = pre -> key;
                node -> left = trimAVL(node -> left, pre -> key);//node의 왼쪽부터 시작해서 지우고 와라~ pre나 suc은 one child이다.
            }
        }
    }
	if (node == nullptr) return node;   // redundant code, but useful

	// step 2 - get rebalanced at this node
	DPRINT(if (node != nullptr)
		cout << "<trimAVL key=" << key << " is done, now rebalance at " << node->key << endl;);
	return rebalance(node);
}


///////////////////// helper functions /////////////////////////////////
// prints elements present in a vector in a line, show_n items per line 
void show_vector(vector<int> vec, int show_n) {//완료
	int size = (int) vec.size();
	if (size < show_n)
		for (auto i : vec) cout << i << " ";
	else {
		for (int i = 0; i < show_n / 2; ++i)
			cout << vec[i] << " ";
		cout << "... ";
		for (int i = size - show_n / 2; i < size; ++i)
			cout << vec[i] << " ";
	}
}

