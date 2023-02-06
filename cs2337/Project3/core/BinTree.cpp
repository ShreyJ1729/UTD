// #include "BinTree.h"
// #include <iostream>
// #include "Term.h"
// #include <vector>
// #include <cmath>

// using namespace std;


// BST::BST()
// {
//     this->root = nullptr;
// }

// BST::BST(Node *root)
// {
//     this->root = root;
// }

// Node *BST::Insert(Payload data)
// {
//     if (!this->root)
//     {
//         // cout << "defining root" << endl;
//         this->root = new Node(data);
//         return this->root;
//     }

//     Insert_Helper(this->root, data);
// }

// Node *BST::Insert_Helper(Node *top, Payload data)
// {
//     if (top == nullptr)
//     {
//         top = new Node(data);
//         return top;
//     }

//     if (data.exponent > top->data.exponent)
//     {
//         // cout << "going right" << endl;
//         top->right = Insert_Helper(top->right, data);
//     }
//     else if (data.exponent < top->data.exponent)
//     {
//         // cout << "going left" << endl;
//         top->left = Insert_Helper(top->left, data);
//     }
//     return top;
// }

// void BST::Integrate(BST *integrated, Node *top)
// {
//     if (!top) return;
//     Integrate(integrated, top->left);
//     Payload data = top->data;
//     Payload intData = Payload(Fraction(data.coefficient.num, data.exponent+1), data.exponent + 1);
//     integrated->Insert(intData);
//     Integrate(integrated, top->right);
// }

// double BST::Evaluate(Node *top, int x)
// {
//     double total = 0;
//     if (!top) return 0;
//     total += Evaluate(top->left, x);
//     total += (top->data.coefficient.num / top->data.coefficient.denum) * pow(x, top->data.exponent);
//     total += Evaluate(top->right, x);
//     return total;
// }


// vector<Payload>* BST::Inorder(bool reverse)
// {
//     vector<Payload> *poly = new vector<Payload>();

//     if (!this->root)
//     {
//         return poly;
//     }
//     Inorder_Helper(reverse ? this->root->right : this->root->left, reverse, poly);
//     poly->push_back(this->root->data);
//     // cout << "(" << printFrac(this->root->data.coefficient) << ")x^" << this->root->data.exponent << endl;
//     Inorder_Helper(reverse ? this->root->left : this->root->right, reverse, poly);
//     return poly;
// }

// void BST::Inorder_Helper(Node *top, bool reverse, vector<Payload> *poly)
// {
//     if (!top)
//     {
//         return;
//     }
//     Inorder_Helper(reverse ? top->right : top->left, reverse, poly);
//     // cout << "(" << printFrac(top->data.coefficient) << ")x^" << top->data.exponent << endl;
//     poly->push_back(top->data);
//     Inorder_Helper(reverse ? top->left : top->right, reverse, poly);
// }

// Node *BST::Search_Helper(Node *top, int expo)
// {
//     // Key is greater than root's key
//     // if (top->data.exponent < expo)
//         return Search_Helper(top->right, expo);

//     // Key is smaller than root's key
//     return Search_Helper(top->left, expo);
// }

// Node *BST::Search(int expo)
// {
//     // Base Cases: root is null or key is present at root
//     if (!this->root || this->root->data.exponent == expo)
//         return this->root;

//     return Search_Helper(this->root, expo);
// }

// void BST::Remove(Node *node)
// {
// }
