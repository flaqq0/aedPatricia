#ifndef PATRICIA_TREE_H
#define PATRICIA_TREE_H

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include "crow_all.h"

class PatriciaNode {
public:
    std::string keyPart;                      // Parte del prefijo almacenado
    bool isEndOfKey;                          // Marca si es el final de una clave
    std::map<char, PatriciaNode*> children;   // Hijos del nodo

    PatriciaNode(std::string key = "") : keyPart(key), isEndOfKey(false) {}
};

class PatriciaTree {
private:
    PatriciaNode* root;

    // Inserción recursiva
    void insert(PatriciaNode* node, const std::string& key, int depth);

    // Obtener prefijo común entre dos cadenas
    std::string getCommonPrefix(const std::string& a, const std::string& b);

    // Dividir un nodo cuando hay bifurcación
    void splitNode(PatriciaNode* node, const std::string& commonPrefix, const std::string& key, int depth);

    // Exportar nodos al formato Graphviz
    void exportToGraphviz(PatriciaNode* node, std::ofstream& file, std::string parentName);

public:
    PatriciaTree();                            // Constructor
    void insert(const std::string& key);       // Método público para insertar clave
    void exportToGraphviz(const std::string& fileName);  // Exportar árbol a formato .dot
};

#endif // PATRICIA_TREE_H
