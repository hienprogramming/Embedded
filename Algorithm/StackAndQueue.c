// #include <stdio.h>
// #include <stdlib.h>

// /*
//     1. Stack: Last In, First Out -> LIFO
//     Common Operations
//     Push: Add an element to the top of the stack.
//     Pop: Remove and return the top element of the stack.
//     Peek/Top: View the top element without removing it.
//     2. Queue: First In, First Out -> FIFO
//     Enqueue: Add an element to the rear of the queue.
//     Dequeue: Remove and return the element at the front of the queue.
//     Front: View the element at the front without removing it.
// */

// /*          Push(3)         Push(1)
//         |          |    |          |
//         |          |    |          |
//         |__________|    |          |
//         |          |    |__________|
//         |    3     |    |    2     |             
// top ->  |__________|    |__________|
// */


// #define MAX 10 // Maximum size of the stack

// typedef struct {
//     int data[MAX];
//     int top; // Index of the top element
// } Stack;

// // Initialize the stack
// void initStack(Stack *s) {
//     s->top = -1;
// }

// // Check if the stack is full
// int isFull(Stack *s) {
//     return s->top == MAX - 1;
// }

// // Check if the stack is empty
// int isEmpty(Stack *s) {
//     return s->top == -1;
// }

// // Push an element onto the stack
// void push(Stack *s, int value) {
//     if (isFull(s)) {
//         printf("Stack Overflow!\n");
//         return;
//     }
//     s->data[++s->top] = value;
//     printf("Pushed %d onto the stack.\n", value);
// }

// // Pop an element from the stack
// int pop(Stack *s) {
//     if (isEmpty(s)) {
//         printf("Stack Underflow!\n");
//         return -1; // Return -1 if the stack is empty
//     }
//     return s->data[s->top--];
// }

// // Peek at the top element
// int peek(Stack *s) {
//     if (isEmpty(s)) {
//         printf("Stack is empty!\n");
//         return -1;
//     }
//     return s->data[s->top];
// }

// void Manage_Stack()
// {
//     Stack s;
//     initStack(&s);

//     push(&s, 10);
//     push(&s, 20);
//     push(&s, 30);

//     printf("Top element is: %d\n", peek(&s));
//     printf("Popped element is: %d\n", pop(&s));
//     printf("Top element after pop is: %d\n", peek(&s));
// }


// // Queue

// typedef struct {
//     int data[MAX];
//     int front; // Index of the front element
//     int rear;  // Index of the rear element
// } Queue;
// // Initialize the queue
// void initQueue(Queue *q) {
//     q->front = -1;
//     q->rear = -1;
// }

// // Check if the queue is empty
// int isEmpty_Queue(Queue *q) {
//     return q->front == -1;
// }

// // Check if the queue is full
// int isFull_Queue(Queue *q) {
//     return (q->rear + 1) % MAX == q->front;
// }

// // Enqueue an element
// void enqueue(Queue *q, int value) {
//     if (isFull_Queue(q)) {
//         printf("Queue Overflow!\n");
//         return;
//     }
//     if (isEmpty_Queue(q)) {
//         q->front = 0;
//     }
//     q->rear = (q->rear + 1) % MAX;
//     q->data[q->rear] = value;
//     printf("Enqueued %d into the queue.\n", value);
// }

// // Dequeue an element
// int dequeue(Queue *q) {
//     if (isEmpty_Queue(q)) {
//         printf("Queue Underflow!\n");
//         return -1;
//     }
//     int value = q->data[q->front];
//     if (q->front == q->rear) {
//         q->front = q->rear = -1; // Reset the queue when it becomes empty
//     } else {
//         q->front = (q->front + 1) % MAX;
//     }
//     return value;
// }

// // View the front element
// int front(Queue *q) {
//     if (isEmpty_Queue(q)) {
//         printf("Queue is empty!\n");
//         return -1;
//     }
//     return q->data[q->front];
// }

// void Manage_Queue()
// {
//     Queue q;
//     initQueue(&q);

//     enqueue(&q, 10);
//     enqueue(&q, 20);
//     enqueue(&q, 30);

//     printf("Front element is: %d\n", front(&q));
//     printf("Dequeued element is: %d\n", dequeue(&q));
//     printf("Front element after dequeue is: %d\n", front(&q));
// }

// int main() {
//     printf("/*-------Manage_Stack-------*/\n");

//     printf("/*-------Manage_Queue-------*/\n");
//     Manage_Queue();
//     return 0;
// }
 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
uint8_t Return(uint8_t *a, uint8_t *b)
{
    return (*a > *b) ? (*a + *b) : (*b - *a);
}
 
void main()
{
    uint8_t a = 5, b = 4;
    uint8_t value = Return(&a, &b);
    printf("value is: %d", value);
}