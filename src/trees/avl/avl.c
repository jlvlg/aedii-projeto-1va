#include <stdlib.h>
#include "util.h"
#include "types.h"
#include "tree.h"
#include "avl.h"

static AVL rotate(AVL root) {
    Tree tree_root = root;
    if (root->bf > 0) {
        if (((AVL) tree_root->r)->bf > 0) {
            root = tree.simple_rotation_left(tree_root);
            ((AVL) ((Tree) root)->l)->bf = root->bf == 0 ? -1 : 0;
            root->bf = root->bf == 0 ? 1 : 0;
            return root;
        } else {
            root = tree.double_rotation_left(tree_root);
        }
    } else {
        if (((AVL) tree_root->l)->bf > 0) {
            root = tree.double_rotation_right(tree_root);
        } else {
            root = tree.simple_rotation_right(tree_root);
            ((AVL) ((Tree) root)->r)->bf = root->bf == 0 ? 1 : 0;
            root->bf = root->bf == 0 ? -1 : 0;
            return root;
        }
    }
    ((AVL) ((Tree) root)->l)->bf = root->bf == 1 ? -1 : 0;
    ((AVL) ((Tree) root)->r)->bf = root->bf == -1 ? 1 : 0;
    root->bf = 0;
    return root;
}

static AVL balance(AVL root, int *changes, int right, int rem) {
    if (*changes) {
        *changes = (rem ^ right ? root->bf++ : root->bf--) == rem;
    }
    if (abs(root->bf) > 1)
        return rotate(root);
    return root;
}

static AVL create(Item item) {
    AVL leaf = util.safe_malloc(sizeof(AVL_Node));
    Tree tree_leaf = leaf;
    tree_leaf->item = item;
    tree_leaf->l = tree_leaf->r = NULL;
    leaf->bf = 0;
    return leaf;
}

static AVL insert(AVL root, AVL leaf, int *changes) {
    Tree tree_root = root, tree_leaf = leaf;
    int cmp;

    if (leaf == NULL)
        return root;

    if (root == NULL) {
        *changes = 1;
        return leaf;
    }

    cmp = types.cmp(tree_leaf->item, tree_root->item) > 0;

    if (cmp) {
        tree_root->r = insert(tree_root->r, leaf, changes);
    } else {
        tree_root->l = insert(tree_root->l, leaf, changes);
    }

    return balance(root, changes, cmp, 0);
}

static AVL remove(AVL root, Item item, int *changes) {
    Tree tree_root = root;
    int cmp, children;

    if (root == NULL)
        return NULL;

    cmp = types.cmp(item, tree_root->item);

    switch (cmp) {
        case 0: 
            *changes = 1;
            children = tree.children(tree_root);
            switch (children) {
                case 0:
                    return (AVL) tree.kill(tree_root);
                case 1: {
                    AVL temp = tree_root->l != NULL ? tree_root->l : tree_root->r;
                    tree.kill(tree_root);
                    return temp;
                }
                case 2:
                    types.destroy(tree_root->item);
                    tree_root->item = types.copy(tree.max(tree_root->l)->item);
                    tree_root->l = remove(tree_root->l, tree_root->item, changes);
                    return balance(root, changes, 0, 1);
            }
        case -1:
            tree_root->l = remove(tree_root->l, item, changes);
            break;
        case 1:
            tree_root->r = remove(tree_root->r, item, changes);
    }

    return balance(root, changes, cmp == 1, 1);
}

static AVL trim(AVL root, AVL branch) {
    Tree tree_branch = branch;
    int growth;
    if (root != NULL) {
        if (branch != NULL) {
            trim(root, tree_branch->l);
            trim(root, tree_branch->r);
            remove(root, tree_branch->item, &growth);
        }
    }
    return NULL;
}

const struct avl_methods avl = {
    .create = create,
    .insert = insert,
    .remove = remove,
    .trim = trim
};