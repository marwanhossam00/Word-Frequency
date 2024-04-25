#include "trie.h"


TrieNode::TrieNode()
{
    isEndOfWord = false;
    for(int i = 0; i < 26; i++){
        children[i] = nullptr;
    }
}

Trie::Trie()
{
    root = new TrieNode();
}

// void Trie::insert(const QString &word)
// {
//     TrieNode* current = root;
//     for(QChar c: word){
//         char myStdChar = c.toChar();
//         int index = myStdChar - 'a';
//         if(current->children[index] == nullptr){
//             current->children[index] = new TrieNode();
//         }
//         current = current->children[index];
//     }
//     current->isEndOfWord = true;
// }
