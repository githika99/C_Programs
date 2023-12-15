#include <stdint.h>
#include <stdlib.h>
#include "trie.h"
#include "code.h"

TrieNode *trie_node_create(uint16_t index) {
    //node's code is set to index
    //node's children's are NULL
    // Allocate memory for a TrieNode
    TrieNode *node = (TrieNode *) malloc(sizeof(TrieNode));
    //malloc for children and code
    for (int i = 0; i < ALPHABET; i++)
        node->children[i] = NULL;
    node->code = index;
    return node;
}

void trie_node_delete(TrieNode *n) {
    free(n);
}

TrieNode *trie_create(void) {
    //initializes a trie
    //root's code is EMPTY_CODE
    //returns the root if succesful, returns NULL if not succesful
    TrieNode *node = (TrieNode *) malloc(sizeof(TrieNode));
    for (int i = 0; i < ALPHABET; i++)
        node->children[i] = NULL;
    node->code = EMPTY_CODE;
    return node;
}

void trie_reset(TrieNode *root) {
    //resets a trie to just the root
    //root's value is preserved, but all root's children are NULL
    for (int i = 0; i < ALPHABET; i++)
        root->children[i] = NULL;
}

void trie_delete(TrieNode *n) {
    //delete every children of n
    //then delete n

    //delete's a sub-trie starting at root n
    //requires recursive call to delete all of n's children (using trie_node_delete)
    //after this, set n's children to NULL
    //do we delete n as well?
    for (int i = 0; i < ALPHABET; i++) {
        if (n->children[i] != NULL) {
            trie_delete(n->children[i]);
        }
    }
    free(n);
    //set children to NULL
}

TrieNode *trie_step(TrieNode *n, uint8_t sym) {
    //checks if word is in the trie
    //returns a pointer to the child node representing the symbol sym (node of last character in sym)
    //if sym is not in the trie n, return NULL
    int position = sym - 48; //gets ASCII num of sym[i]
    if (n->children[position] == NULL)
        return NULL;
    return n->children[position];
}
