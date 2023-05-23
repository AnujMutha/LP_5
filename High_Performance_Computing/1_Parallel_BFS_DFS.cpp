#include<bits/stdc++.h>
using namespace std;
#include <omp.h>
 
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
void bfs(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        cout << node->val << " ";
        if (node->left) {
            q.push(node->left);
        }
        if (node->right) {
            q.push(node->right);
        }
    }
}

void dfs(TreeNode* root) {
    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
        TreeNode* node = s.top();
        s.pop();
        cout << node->val << " ";
        if (node->right) {
            s.push(node->right);
        }
        if (node->left) {
            s.push(node->left);
        }
    }
}
 
 
void parallel_bfs(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int qSize = q.size();
        #pragma omp parallel for
        for (int i = 0; i < qSize; i++) {
            TreeNode* node;
            #pragma omp critical
            {
                node = q.front();
                q.pop();
                cout << node->val << " ";
            }
            if (node->left)  q.push(node->left);        
            if (node->right) q.push(node->right);
        }
    }
}
 
void parallel_dfs(TreeNode* root) {
    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
        int sSize = s.size();
        #pragma omp parallel for
        for (int i = 0; i < sSize; i++) {
            TreeNode* node;
            #pragma omp critical
            {
                node = s.top();
                s.pop();
                cout << node->val << " ";
            }
            if (node->right) s.push(node->right);
            if (node->left) s.push(node->left);
        }
    }
}
 

void createTree(TreeNode*& root) {
    int val;
    std::cout << "Enter the value for the current node: ";
    std::cin >> val;
    root = new TreeNode(val);

    char choice;
    std::cout << "Do you want to add a left child to the node with value " << val << "? (y/n): ";
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        createTree(root->left);
    }

    std::cout << "Do you want to add a right child to the node with value " << val << "? (y/n): ";
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        createTree(root->right);
    }
}

 
int main() {
    TreeNode* root = nullptr;
    createTree(root);
 
    cout << "BFS traversal: ";
    auto start = chrono::high_resolution_clock::now();
    bfs(root);
    auto end = chrono::high_resolution_clock::now();
    cout << "\nBFS took " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds." << endl;
    cout << endl;
 
    cout << "Parallel BFS traversal: ";
    start = chrono::high_resolution_clock::now();
    parallel_bfs(root);
    end = chrono::high_resolution_clock::now();
    cout << "\nParallel BFS took " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds." << endl;
 
    cout << "---------------------------------------------------------"<<endl;
 
    cout << "DFS traversal: ";
    start = chrono::high_resolution_clock::now();
    dfs(root);
    end = chrono::high_resolution_clock::now();
    cout << "\nDFS took " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds." << endl;
    cout << endl;
 
    cout << "Parallel DFS traversal: ";
    start = chrono::high_resolution_clock::now();
    parallel_dfs(root);
    end = chrono::high_resolution_clock::now();
    cout << "\nParallel DFS took " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds." << endl;
 
 
    return 0;
}