Q.Write a C program for subtraction of one Polynomial from another using doubly linked list.

#include <stdio.h>
#include <stdlib.h>

// Define the structure of a node in the doubly linked list
typedef struct Node {
    int coefficient;
    int exponent;
    struct Node* prev;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int coef, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coefficient = coef;
    newNode->exponent = exp;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the list
void insertNode(Node** head, int coef, int exp) {
    Node* newNode = createNode(coef, exp);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

// Function to display the polynomial
void displayPolynomial(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->coefficient > 0 && temp != head)
            printf("+ ");
        if (temp->coefficient != 0) {
            printf("%dx^%d ", temp->coefficient, temp->exponent);
        }
        temp = temp->next;
    }
    printf("\n");
}

// Function to subtract two polynomials
Node* subtractPolynomials(Node* poly1, Node* poly2) {
    Node *result = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exponent > poly2->exponent) {
            insertNode(&result, poly1->coefficient, poly1->exponent);
            poly1 = poly1->next;
        } else if (poly1->exponent < poly2->exponent) {
            insertNode(&result, -poly2->coefficient, poly2->exponent);
            poly2 = poly2->next;
        } else {
            int diff = poly1->coefficient - poly2->coefficient;
            if (diff != 0) {
                insertNode(&result, diff, poly1->exponent);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    // If there are remaining terms in poly1
    while (poly1 != NULL) {
        insertNode(&result, poly1->coefficient, poly1->exponent);
        poly1 = poly1->next;
    }

    // If there are remaining terms in poly2
    while (poly2 != NULL) {
        insertNode(&result, -poly2->coefficient, poly2->exponent);
        poly2 = poly2->next;
    }

    return result;
}

int main() {
    Node* poly1 = NULL;
    Node* poly2 = NULL;

    // Input first polynomial: 3x^3 + 5x^2 + 2x + 1
    insertNode(&poly1, 3, 3);
    insertNode(&poly1, 5, 2);
    insertNode(&poly1, 2, 1);
    insertNode(&poly1, 1, 0);

    // Input second polynomial: 4x^3 + 2x^2 + x
    insertNode(&poly2, 4, 3);
    insertNode(&poly2, 2, 2);
    insertNode(&poly2, 1, 1);

    // Display both polynomials
    printf("Polynomial 1: ");
    displayPolynomial(poly1);

    printf("Polynomial 2: ");
    displayPolynomial(poly2);

    // Subtract the second polynomial from the first
    Node* result = subtractPolynomials(poly1, poly2);

    // Display the result
    printf("Result of subtraction: ");
    displayPolynomial(result);

    return 0;
}

