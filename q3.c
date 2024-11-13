Q.Write a C program for the evaluation a polynomial for some real value of x stored in a doubly
circular linked list.

#include <stdio.h>
#include <stdlib.h>

// Node structure for doubly circular linked list
typedef struct Node {
    double coefficient;  // Coefficient of the term
    int exponent;        // Exponent of the term
    struct Node* next;   // Pointer to the next node
    struct Node* prev;   // Pointer to the previous node
} Node;

// Function to create a new node
Node* createNode(double coefficient, int exponent) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coefficient = coefficient;
    newNode->exponent = exponent;
    newNode->next = newNode;  // Point to itself initially
    newNode->prev = newNode;  // Point to itself initially
    return newNode;
}

// Function to insert a new node at the end of the circular doubly linked list
void insertNode(Node** head, double coefficient, int exponent) {
    Node* newNode = createNode(coefficient, exponent);

    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* last = (*head)->prev;  // Get the last node
        last->next = newNode;
        newNode->prev = last;
        newNode->next = *head;
        (*head)->prev = newNode;
    }
}

// Function to evaluate the polynomial at a given value of x
double evaluatePolynomial(Node* head, double x) {
    if (head == NULL) return 0.0;

    double result = 0.0;
    Node* current = head;

    do {
        result += current->coefficient * pow(x, current->exponent);
        current = current->next;
    } while (current != head);

    return result;
}

// Function to print the polynomial (for debugging)
void printPolynomial(Node* head) {
    if (head == NULL) {
        printf("Polynomial is empty.\n");
        return;
    }

    Node* current = head;
    do {
        printf("%0.2fx^%d ", current->coefficient, current->exponent);
        if (current->next != head) printf("+ ");
        current = current->next;
    } while (current != head);
    printf("\n");
}

int main() {
    Node* polynomial = NULL;

    // Example: P(x) = 3x^3 + 2x^2 + 5x + 1
    insertNode(&polynomial, 3.0, 3);
    insertNode(&polynomial, 2.0, 2);
    insertNode(&polynomial, 5.0, 1);
    insertNode(&polynomial, 1.0, 0);

    // Print the polynomial
    printf("Polynomial: ");
    printPolynomial(polynomial);

    // Evaluate the polynomial for x = 2.0
    double x = 2.0;
    double result = evaluatePolynomial(polynomial, x);

    printf("P(%0.2f) = %0.2f\n", x, result);

    // Free memory (not implemented here for brevity)

    return 0;
}

