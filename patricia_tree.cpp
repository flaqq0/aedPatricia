#include "patricia_tree.h"
#include "crow_all.h"

// Constructor del Patricia Tree
PatriciaTree::PatriciaTree() : root(new PatriciaNode()) {}

// Método público para insertar claves
void PatriciaTree::insert(const std::string& key) {
    insert(root, key, 0);
}

// Método recursivo para insertar una clave
void PatriciaTree::insert(PatriciaNode* node, const std::string& key, int depth) {
    if (depth == key.length()) {
        node->isEndOfKey = true;
        return;
    }

    char nextChar = key[depth];
    if (node->children.find(nextChar) == node->children.end()) {
        node->children[nextChar] = new PatriciaNode(key.substr(depth));
        node->children[nextChar]->isEndOfKey = true;
        return;
    }

    PatriciaNode* child = node->children[nextChar];
    std::string commonPrefix = getCommonPrefix(child->keyPart, key.substr(depth));
    if (commonPrefix == child->keyPart) {
        insert(child, key, depth + child->keyPart.length());
    } else {
        splitNode(child, commonPrefix, key, depth);
    }
}

// Obtener prefijo común entre dos cadenas
std::string PatriciaTree::getCommonPrefix(const std::string& a, const std::string& b) {
    int i = 0;
    while (i < a.length() && i < b.length() && a[i] == b[i]) {
        i++;
    }
    return a.substr(0, i);
}

// Dividir nodo cuando hay bifurcación
void PatriciaTree::splitNode(PatriciaNode* node, const std::string& commonPrefix, const std::string& key, int depth) {
    std::string remainingChildKey = node->keyPart.substr(commonPrefix.length());
    PatriciaNode* newChild = new PatriciaNode(remainingChildKey);
    newChild->children = node->children;
    newChild->isEndOfKey = node->isEndOfKey;

    node->keyPart = commonPrefix;
    node->children.clear();
    node->children[remainingChildKey[0]] = newChild;
    node->isEndOfKey = false;

    if (depth + commonPrefix.length() < key.length()) {
        std::string remainingKey = key.substr(depth + commonPrefix.length());
        node->children[remainingKey[0]] = new PatriciaNode(remainingKey);
        node->children[remainingKey[0]]->isEndOfKey = true;
    } else {
        node->isEndOfKey = true;
    }
}

// Exportar árbol al formato Graphviz
void PatriciaTree::exportToGraphviz(const std::string& fileName) {
    std::ofstream file(fileName);
    file << "digraph PatriciaTree {\n";
    exportToGraphviz(root, file, "root");
    file << "}\n";
    file.close();
}

// Exportar nodos al formato Graphviz
void PatriciaTree::exportToGraphviz(PatriciaNode* node, std::ofstream& file, std::string parentName) {
    if (!node) return;

    std::string nodeLabel = node->keyPart;
    if (node->isEndOfKey) nodeLabel += " [END]";
    std::string nodeName = "\"" + parentName + "\"";

    file << nodeName << " [label=\"" << nodeLabel << "\"];\n";
    for (auto& child : node->children) {
        std::string childName = parentName + child.first;
        file << nodeName << " -> \"" << childName << "\" [label=\"" << child.first << "\"];\n";
        exportToGraphviz(child.second, file, childName);
    }
}
