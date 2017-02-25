/*
	UVA 1556
	Author: Youssef ElGhareeb
	
	Idea: Store the file system in a tree structure, where the children are sorted lexicographically
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>

const int MXN = 1e3 + 5;
const int INF = 1e9 + 7;

int n;

struct Node {
    string s;
    vector<Node*> children;
    Node(string _s) {
        s = _s;
    }
    Node () {}
    bool operator < (const Node& node) {
        return s < node.s;
    }
    Node* get_node(string s) {
        for (vector<Node*>::iterator it = children.begin(); it != children.end(); it++) {
            Node* cur_node = *it;
            if (cur_node->s == s) return cur_node;
        }
        Node* new_node = new Node(s);
        children.push_back(new_node);
        sort(children.begin(), children.end(), [](Node*& lhs, Node*& rhs) {return lhs->s < rhs->s;});
        return new_node;
    }
};

vector<string> split(string s) {
    vector<string> res;
    string current = "";
    loop(i, s.size()) {
        if (s[i] == '\\') {
            res.push_back(current);
            current = "";
        }
        else current += s[i];
    }
    if (current != "") res.push_back(current);
    return res;
}

void populate(Node* current, vector<string>& v, int ind) {
    if (ind == v.size()) return;
    Node* child = current->get_node(v[ind]);
    populate(child, v, ind + 1);
}

void print (Node* current, int spaces = 0) {
    for(vector<Node*>::iterator it = current->children.begin(); it != current->children.end(); it++) {
        loop(j, spaces) cout<<" ";
        Node* cur = *it;
        cout<<cur->s<<endl;
        print(cur, spaces + 1);
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    while (cin>>n) {
        Node* root = new Node();
        loop(i, n) {
            string s;
            cin>>s;
            vector<string> splitted = split(s);
            populate(root, splitted, 0);
        }
        print(root);
        cout<<endl;
    }
    return 0;
}