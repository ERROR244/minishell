#include "libft.h"

Node* insertNode(Node* node, void* value)
{
    Node*   newNode = malloc(sizeof(Node));
    Node*   head = node;

    newNode->addr = value;
    newNode->next = NULL;
    if (node == NULL)
        return (newNode);
    while (node && node->next)
        node = node->next;
    node->next = newNode;
    return (head);
}

void deleteList(Node* node)
{
    Node* curr;

    while (node)
    {
        curr = node->next;
        free(node->addr);
        free(node);
        node = curr;
    }
}

void *ft_malloc(size_t size, Node *node)
{
    void *block = malloc(size);

    if (block == NULL)
    {
        deleteList(node);
        exit(EXIT_FAILURE); 
    }


    insertNode(node, block);
    return (block);
}