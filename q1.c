#include <stdio.h>
#include <stdlib.h>

// Node structure for representing a term in a polynomial
struct Node {
    int coeff;   // Coefficient of the term
    int exp;     // Exponent of the term
    struct Node* next;  // Pointer to the next node in the circular list
};

// Function to create a new node
struct Node* createNode(int coeff, int exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = newNode;  // Initially points to itself (circular link)
    return newNode;
}

// Function to insert a node in the circular linked list
void insertNode(struct Node** head, int coeff, int exp) {
    struct Node* newNode = createNode(coeff, exp);
    
    if (*head == NULL) {
        // If list is empty, point to itself
        *head = newNode;
    } else {
        struct Node* temp = *head;
        // Traverse to the last node
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode; // Link last node to the new node
        newNode->next = *head; // Make the new node point to the head
    }
}

// Function to display the polynomial
void displayPolynomial(struct Node* head) {
    if (head == NULL) {
        printf("Polynomial is empty\n");
        return;
    }
    struct Node* temp = head;
    do {
        printf("%dx^%d", temp->coeff, temp->exp);
        temp = temp->next;
        if (temp != head) {
            printf(" + ");
        }
    } while (temp != head);
    printf("\n");
}

// Function to add two polynomials
struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node *result = NULL, *temp1 = poly1, *temp2 = poly2;

    // Loop until both polynomials are processed
    do {
        // Add terms from poly1
        if (result == NULL || temp1->exp > temp2->exp) {
            insertNode(&result, temp1->coeff, temp1->exp);
            temp1 = temp1->next;
        }
        // Add terms from poly2
        else if (temp2->exp > temp1->exp) {
            insertNode(&result, temp2->coeff, temp2->exp);
            temp2 = temp2->next;
        }
        // If exponents are the same, add the coefficients
        else {
            int sumCoeff = temp1->coeff + temp2->coeff;
            if (sumCoeff != 0) {
                insertNode(&result, sumCoeff, temp1->exp);
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    } while (temp1 != poly1 || temp2 != poly2);

    return result;
}

// Main function to test the program
int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    
    // Polynomial 1: 5x^3 + 4x^2 + 2x + 1
    insertNode(&poly1, 5, 3);
    insertNode(&poly1, 4, 2);
    insertNode(&poly1, 2, 1);
    insertNode(&poly1, 1, 0);

    // Polynomial 2: 3x^3 + 2x^2 + 6x + 4
    insertNode(&poly2, 3, 3);
    insertNode(&poly2, 2, 2);
    insertNode(&poly2, 6, 1);
    insertNode(&poly2, 4, 0);
    
    // Display the polynomials
    printf("Polynomial 1: ");
    displayPolynomial(poly1);

    printf("Polynomial 2: ");
    displayPolynomial(poly2);

    // Add the polynomials
    struct Node* result = addPolynomials(poly1, poly2);
    
    // Display the result
    printf("Resultant Polynomial after Addition: ");
    displayPolynomial(result);

    return 0;
}

