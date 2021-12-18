#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <gmpxx.h>

using namespace std;

typedef mpz_class mz;

struct node {
  node *l, *r;
  int v;
};

void printNodes(node *root, bool top = true) {
  if(root->l != nullptr) {
    cout << '[';
    printNodes(root->l, false);
    cout << ',';
    printNodes(root->r, false);
    cout << ']';
  } else {
    cout << root->v;
  }
  if(top)
    cout << endl;
}

void addToPrev(node *root, node *end) {
  stack<node *> s;
  s.push(root);
  node *prev = nullptr;
  while(!s.empty()) {
    node *n = s.top();
    s.pop();
    if(n == end) {
      if(prev != nullptr)
        prev->v += end->v;
      return;
    }
    if(n->l != nullptr) {
      s.push(n->r);
      s.push(n->l);
    } else {
      prev = n;
    }
  }
}

void addToNext(node *root, node *end) {
  stack<node *> s;
  s.push(root);
  node *prev = nullptr;
  while(!s.empty()) {
    node *n = s.top();
    s.pop();
    if(n->l != nullptr) {
      s.push(n->r);
      s.push(n->l);
    } else {
      if(prev == end) {
        n->v += end->v;
        return;
      }
      prev = n;
    }
  }
}

bool reduceNode(node *root) {
  stack<pair<node *, int> > s;
  s.push({root, 0});
  while(!s.empty()) {
    auto p = s.top();
    s.pop();
    node *n = p.first;
    int d = p.second;
    if(n->l != nullptr) {
      if(d == 4) {
        addToPrev(root, n->l);
        addToNext(root, n->r);
        delete n->l;
        delete n->r;
        n->l = nullptr;
        n->r = nullptr;
        n->v = 0;
        return true;
      } else {
        s.push({n->r, d+1});
        s.push({n->l, d+1});
      }
    }
  }
  stack<node *> s2;
  s2.push(root);
  while(!s2.empty()) {
    node *n = s2.top();
    s2.pop();
    if(n->l != nullptr) {
      s2.push(n->r);
      s2.push(n->l);
    } else {
      if(n->v > 9) {
        node *l = new node;
        l->l = nullptr;
        l->r = nullptr;
        l->v = n->v/2;
        node *r = new node;
        r->l = nullptr;
        r->r = nullptr;
        r->v = (n->v+1)/2;
        n->v = -1;
        n->l = l;
        n->r = r;
        return true;
      }
    }
  }
  return false;
}

node *addNodes(node *l, node *r) {
  node *root = new node;
  root->l = l;
  root->r = r;
  root->v = -1;

  while(reduceNode(root));

  return root;
}

node *parse(string s) {
  node *root = new node;
  if(s[0] == '[') {
    int count = 0;
    int index = 0;
    for(int i = 0; i < s.size(); i++) {
      if(s[i] == '[')
        count++;
      else if(s[i] == ']')
        count--;
      else if(s[i] == ',' && count == 1) {
        index = i;
        break;
      }
    }
    root = addNodes(parse(s.substr(1,index-1)), parse(s.substr(index+1,s.size()-index-2)));
  } else {
    root->v = stoi(s);
    root->l = nullptr;
    root->r = nullptr;
  }
  return root;
}

mz nodeValue(node *root) {
  if(root->l != nullptr) {
    return 3*nodeValue(root->l) + 2*nodeValue(root->r);
  } else {
    return root->v;
  }
}

node *copyNodes(node *orig) {
  node *root = new node;
  if(orig->l != nullptr) {
    root->l = copyNodes(orig->l);
    root->r = copyNodes(orig->r);
    root->v = -1;
  } else {
    root->l = nullptr;
    root->r = nullptr;
    root->v = orig->v;
  }
  return root;
}

void freeNodes(node *root) {
  if(root->l != nullptr) {
    freeNodes(root->l);
    freeNodes(root->r);
  } else {
    delete root;
  }
}

int main() {
  string input;
  vector<node *> l;
  while(getline(cin, input)) {
    l.push_back(parse(input));
  }

  node *root = copyNodes(l[0]);
  for(int i = 1; i < l.size(); i++) {
    node *n = copyNodes(l[i]);
    root = addNodes(root, n);
  }

  cout << nodeValue(root) << endl;
  freeNodes(root);

  mz max = 0;
  for(int i = 0; i < l.size(); i++) {
    for(int j = 0; j < l.size(); j++) {
      if(i == j)
        continue;
      node *n1 = copyNodes(l[i]);
      node *n2 = copyNodes(l[j]);
      node *n = addNodes(n1, n2);
      mz val = nodeValue(n);
      freeNodes(n);
      if(val > max)
        max = val;
    }
  }

  for(node *n: l)
    freeNodes(n);

  cout << max << endl;

  return 0;
}

