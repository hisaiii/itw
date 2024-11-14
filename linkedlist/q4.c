Q.Write a C program for the addition of two 2-variable Polynomials. The polynomials are stored in the
circular linked lists.

#include <stdio.h>
#include <stdlib.h>

// Structure for the node of the circular linked list
struct Node {
    int coeff;  // Coefficient of the term
    int x_exp;  // Exponent of x
    int y_exp;  // Exponent of y
    struct Node* next;  // Pointer to the next node
};

// Function to create a new node
struct Node* createNode(int coeff, int x_exp, int y_exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->x_exp = x_exp;
    newNode->y_exp = y_exp;
    newNode->next = newNode;  // Circular link to itself initially
    return newNode;
}

// Function to insert a node at the end of the circular linked list
void insertNode(struct Node** head, int coeff, int x_exp, int y_exp) {
    struct Node* newNode = createNode(coeff, x_exp, y_exp);

    if (*head == NULL) {
        *head = newNode;  // First node becomes the head
    } else {
        struct Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;  // Circular link
    }
}

// Function to display the polynomial from the circular linked list
void displayPolynomial(struct Node* head) {
    if (head == NULL) {
        printf("Polynomial is empty.\n");
        return;
    }

    struct Node* temp = head;
    do {
        if (temp->coeff != 0) {
            if (temp->x_exp == 0 && temp->y_exp == 0)
                printf("%d", temp->coeff);
            else if (temp->y_exp == 0)
                printf("%dx^%d", temp->coeff, temp->x_exp);
            else if (temp->x_exp == 0)
                printf("%dy^%d", temp->coeff, temp->y_exp);
            else
                printf("%dx^%dy^%d", temp->coeff, temp->x_exp, temp->y_exp);

            if (temp->next != head)
                printf(" + ");
        }
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

// Function to add two polynomials represented by circular linked lists
struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node *result = NULL;

    struct Node *ptr1 = poly1;
    struct Node *ptr2 = poly2;

    // Traverse both polynomials
    do {
        struct Node* temp1 = ptr1;
        struct Node* temp2 = ptr2;

        // Compare and add terms with the same exponent of x and y
        if (temp1->x_exp == temp2->x_exp && temp1->y_exp == temp2->y_exp) {
            // Add the coefficients if exponents are the same
            insertNode(&result, temp1->coeff + temp2->coeff, temp1->x_exp, temp1->y_exp);
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        } else if (temp1->x_exp < temp2->x_exp || (temp1->x_exp == temp2->x_exp && temp1->y_exp < temp2->y_exp)) {
            // Insert the node from poly1 if it has a smaller exponent
            insertNode(&result, temp1->coeff, temp1->x_exp, temp1->y_exp);
            ptr1 = ptr1->next;
        } else {
            // Insert the node from poly2 if it has a smaller exponent
            insertNode(&result, temp2->coeff, temp2->x_exp, temp2->y_exp);
            ptr2 = ptr2->next;
        }
    } while (ptr1 != poly1 || ptr2 != poly2);

    return result;
}

// Main function
int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;

    // Inserting terms for first polynomial
    insertNode(&poly1, 4, 3, 2); // 4x^3y^2
    insertNode(&poly1, 3, 2, 1); // 3x^2y
    insertNode(&poly1, 2, 1, 1); // 2xy
    insertNode(&poly1, 1, 0, 0); // 1

    // Inserting terms for second polynomial
    insertNode(&poly2, 5, 3, 2); // 5x^3y^2
    insertNode(&poly2, 3, 2, 1); // 3x^2y
    insertNode(&poly2, 1, 1, 1); // xy
    insertNode(&poly2, 2, 0, 0); // 2

    printf("First Polynomial: \n");
    displayPolynomial(poly1);

    printf("Second Polynomial: \n");
    displayPolynomial(poly2);

    // Add the polynomials
    struct Node* result = addPolynomials(poly1, poly2);

    printf("Resultant Polynomial: \n");
    displayPolynomial(result);

    return 0;
}

