#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// ��������� ��� �������� ���� ������
struct Node {
    int freq;   // ������� ����
    Node* left; // ����� �������
    Node* right; // ������ �������
    Node(int freq) : freq(freq), left(nullptr), right(nullptr) {} // ����������� ��� ������������� ����
};

// ��������� ��� ��������� ���� ����� ������ �� �������
struct CompareNodes {
    bool operator()(const Node* left, const Node* right) {
        return left->freq > right->freq; // ���������� �� �������, ����� � ������������ ������� ���� ���� ����������� �� ����������� �������
    }
};

// ������� ���������� ������ � ����������� ������
Node* buildShortestPathTree(vector<int> freq) {
    priority_queue<Node*, vector<Node*>, CompareNodes> pq; // ������������ �������, � ������� ����� ��������� ����
    for (int f : freq) {
        pq.push(new Node(f)); // ��������� � ������� ���� � ��������� ���������
    }

    while (pq.size() > 1) { // ���� � ������� �� ��������� ������ ���� ����
        Node* left = pq.top(); // ��������� ���� � ���������� ��������
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        Node* parent = new Node(left->freq + right->freq); // ������� ����� ����, ������� ����� ���������� ��� ����������� ����
        parent->left = left;
        parent->right = right;
        pq.push(parent); // ��������� ����� ���� � �������
    }

    return pq.top(); // ���������� ������ ������ � ����������� ������
}

// ������� ��� ������ ������ �� ����� � ���� ������
void printTree(Node* node, string indent = "") {
    if (node == nullptr) {
        cout << indent << "NULL\n";
        return;
    }
    cout << indent << node->freq << "\n";
    printTree(node->left, indent + "  ");
    printTree(node->right, indent + "  ");
}

int main() {
    vector<int> freq = { 10, 12, 20, 25, 30 };
    Node* root = buildShortestPathTree(freq);
    printTree(root);
    return 0;
}
