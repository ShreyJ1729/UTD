#ifndef BINTREE_H
#define BINTREE_H
#include "Node.h"
#include <cmath>
#include <vector>

using namespace std;

string printFrac(Fraction frac)
{
    if (frac.denum == 1)
        return to_string(frac.num);
    else
        return to_string(frac.num) + "/" + to_string(frac.denum);
}

class BST
{
public:
    Node *root;

    BST()
    {
        this->root = nullptr;
    }
    BST(Node *root)
    {
        this->root = root;
    }

    Node *Insert(Payload data)
    {
        if (!this->root)
        {
            // cout << "defining root" << endl;
            this->root = new Node(data);
            return this->root;
        }

        Insert_Helper(this->root, data);
    }

    Node *Insert_Helper(Node *top, Payload data)
    {
        if (top == nullptr)
        {
            top = new Node(data);
            return top;
        }

        if (data.exponent > top->data.exponent)
        {
            // cout << "going right" << endl;
            top->right = Insert_Helper(top->right, data);
        }
        else if (data.exponent < top->data.exponent)
        {
            // cout << "going left" << endl;
            top->left = Insert_Helper(top->left, data);
        }
        return top;
    }
    Node *Search(int expo)
    {
        // Base Cases: root is null or key is present at root
        if (!this->root || this->root->data.exponent == expo)
            return this->root;

        return Search_Helper(this->root, expo);
    }
    Node *Search_Helper(Node *top, int expo)
    {
        // Key is greater than root's key
        if (top->data.exponent < expo)
            return Search_Helper(top->right, expo);

        // Key is smaller than root's key
        return Search_Helper(top->left, expo);
    }

    vector<Payload> *Inorder(bool reverse)
    {
        vector<Payload> *poly = new vector<Payload>();

        if (!this->root)
        {
            return poly;
        }
        Inorder_Helper(reverse ? this->root->right : this->root->left, reverse, poly);
        poly->push_back(this->root->data);
        // cout << "(" << printFrac(this->root->data.coefficient) << ")x^" << this->root->data.exponent << endl;
        Inorder_Helper(reverse ? this->root->left : this->root->right, reverse, poly);
        return poly;
    }

    void Inorder_Helper(Node *top, bool reverse, vector<Payload> *poly)
    {
        if (!top)
        {
            return;
        }
        Inorder_Helper(reverse ? top->right : top->left, reverse, poly);
        // cout << "(" << printFrac(top->data.coefficient) << ")x^" << top->data.exponent << endl;
        poly->push_back(top->data);
        Inorder_Helper(reverse ? top->left : top->right, reverse, poly);
    }

    void Remove(Node *node) {}

    void Integrate(BST *integrated, Node *top)
    {
        if (!top)
            return;
        Integrate(integrated, top->left);
        Payload data = top->data;
        Payload intData = Payload(Fraction(data.coefficient.num, data.exponent+1), data.exponent + 1);
        integrated->Insert(intData);
        Integrate(integrated, top->right);
    }

    double Evaluate(Node *top, int x)
    {
        double total = 0;
        if (!top)
            return 0;
        total += Evaluate(top->left, x);
        total += (top->data.coefficient.num / top->data.coefficient.denum) * pow(x, top->data.exponent);
        total += Evaluate(top->right, x);
        return total;
    }
};

#endif
