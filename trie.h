#ifndef TRIE_H
#define TRIE_H
#include <QString>
#include <QChar>

class TrieNode{
public:
    bool isEndOfWord;
    TrieNode* children[26];

    TrieNode();
};

class Trie
{
private:
    TrieNode* root;
public:
    Trie();
    void insert(const QString& word);

};

#endif // TRIE_H
