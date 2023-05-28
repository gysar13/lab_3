#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Структура для хранения узла дерева
struct Node {
    int freq;   // Частота узла
    Node* left; // Левый потомок
    Node* right; // Правый потомок
    Node(int freq) : freq(freq), left(nullptr), right(nullptr) {} // Конструктор для инициализации узла
};

// Структура для сравнения двух узлов дерева по частоте
struct CompareNodes {
    bool operator()(const Node* left, const Node* right) {
        return left->freq > right->freq; // Сравниваем по частоте, чтобы в приоритетной очереди узлы были упорядочены по возрастанию частоты
    }
};

// Функция построения дерева с кратчайшими путями
Node* buildShortestPathTree(vector<int> freq) {
    priority_queue<Node*, vector<Node*>, CompareNodes> pq; // Приоритетная очередь, в которую будем добавлять узлы
    for (int f : freq) {
        pq.push(new Node(f)); // Добавляем в очередь узлы с заданными частотами
    }

    while (pq.size() > 1) { // Пока в очереди не останется только один узел
        Node* left = pq.top(); // Извлекаем узел с наименьшей частотой
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        Node* parent = new Node(left->freq + right->freq); // Создаем новый узел, который будет объединять два извлеченных узла
        parent->left = left;
        parent->right = right;
        pq.push(parent); // Добавляем новый узел в очередь
    }

    return pq.top(); // Возвращаем корень дерева с кратчайшими путями
}

// Функция для вывода дерева на экран в виде строки
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
