#ifndef TREE_H
#define TREE_H

#include "types.h"

/// @file
/// Implements basic functions to be used with all inherited tree structs
/// @brief Abstract tree implementation.

/// Abstract tree node, prefer usage of inherited structs
typedef struct node {
    Item item;
    struct node *l, *r;
} Node;

/// Pointer to tree node
typedef Node* Tree;

/// Encapsulates functions into the tree namespace
struct tree_methods {
    /// @brief Deletes a node and its contents
    /// @param leaf Node to be deleted
    /// @return NULL pointer
    Tree (*kill)(Tree leaf);

    /// @brief Prints all values of a tree
    /// @param root Tree to be printed
    void (*print)(Tree root);

    /// Order of execution:
    ///     -# Calls function on current node
    ///     -# Tries to access left node if possible
    ///     -# When no longer possible, resumes from previous node
    ///     -# Tries to access right node if possible
    ///     -# When no longer possible, resumes from previous node
    ///
    /// May be used to recreate a tree if needed
    /// @brief Transverses the tree and calls a function as it goes
    /// @param root Tree to be transversed
    /// @param function A function that takes a @ref Tree "tree" as a parameter and returns void
    void (*preorder)(Tree root, void function(Tree));

    /// Order of execution:
    ///     -# Tries to access left node if possible
    ///     -# When no longer possible, calls function on current node
    ///     -# Tries to access right node if possible
    ///     -# When no longer possible, resumes from previous node
    ///
    /// May be used to obtain the values of a tree in order in O(n)
    /// @brief Transverses the tree and calls a function as it goes
    /// @param root Tree to be transversed
    /// @param function A function that takes a @ref Tree "tree" as a parameter and returns void
    void (*inorder)(Tree root, void function(Tree));

    /// Order of execution:
    ///     -# Tries to access left node if possible
    ///     -# When no longer possible, tries to access right node
    ///     -# When no longer possible, calls function on current node
    ///     -# Resumes from previous node
    ///
    /// May be used if you need to access a node's children values before the node's own
    /// @brief Transverses the tree and calls a function as it goes
    /// @param root Tree to be transversed
    /// @param function A function that takes a @ref Tree "tree" as a parameter and returns void
    void (*postorder)(Tree root, void function(Tree));

    /// @brief Searchs a tree for a node containing an @ref Item
    /// @param root Tree to be searched in
    /// @param item Item to be searched for
    /// @return Tree node containing item
    Tree (*search)(Tree root, Item item);

    /// @brief Calculates a tree's height
    /// @param root Tree to be measured
    int (*height)(Tree root);

    /// @brief Searches tree for its greatest value node
    /// @param root Tree to be searched
    /// @return Node containing the tree's greatest value
    Tree (*max)(Tree root);

    /// @brief Searches tree for its lowest value node
    /// @param root Tree to be searched
    /// @return Node containing the tree's lowest value
    Tree (*min)(Tree root);

    /// @brief Returns number of children
    /// @param node Node to be measured
    /// @return Number of children
    int (*children)(Tree node);
};

extern const struct tree_methods tree;

#endif