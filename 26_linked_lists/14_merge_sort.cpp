/*
    TOPIC: Merge Sort
    
    - Sort an unsorted Linked Lists

*/



#include <iostream>
using namespace std;

class Node{
public:
    int data;
    Node *next;

    // constructor
    Node(int d)
    {
        data = d;
        next = NULL;
    }
};


// pass a pointer by reference (because we want to make changes to the original head pointer)
void insertAtHead(Node *&head, int d)
{
    if(head == NULL)
    {
        head = new Node(d);
        return;
    }

    Node *n = new Node(d);
    n->next = head;
    head = n;
}



// function to find length of linked list
int length(Node*head)
{
    int cnt = 0;
    while(head != NULL)
    {
        cnt++;
        head = head->next;
    }
    return cnt;
}



// function to insert data at last position of linked list
void insertAtTail(Node*&head, int data)
{
    // corner case
    if(head == NULL)
    {
        // Node *n =  new Node(data);
        // head = n;
        head = new Node(data);
        return;
    }
    Node *tail = head;             // using temp pointer
    // Moving head towards tail
    while(tail->next != NULL)
    {
        tail = tail->next;
    }
    // create & attach new node
    tail->next = new Node(data);
}



// function to insert data at middle of linked list
void insertAtMiddle(Node*&head, int data, int pos)
{
    //corner case
    if(head==NULL or pos==0)
    {
        insertAtHead(head, data);
        return;
    }
    else if (pos >= length(head))
    {
        insertAtTail(head, data);
        return;
    }
    // take pos-1 jumps
    int i=1;
    Node *temp = head;
    while(i < pos)
    {
        temp = temp->next;
        i++;
    }
    // create a new node
    Node *n = new Node(data);
    n->next = temp->next;
    temp->next = n;
}

// pass by value (because we don't want to change the original head pointer)
void print(Node *head)
{
    while(head != NULL)
    {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << endl;
}



// function to delete data at start of linked list
void deleteAtHead(Node*&head)
{
    if(head == NULL)
    {
        return;
    }
    Node*temp = head->next;   // temp pointer is static. So it will be deleted at the end of function call 
    delete head;              // delete the Node whose address is stored in "head" pointer
    head = temp;
}



// function to delete data at end of linked list
void deleteAtTail(Node*&head)
{
    if(head == NULL)
    {
        return;
    }
    Node *tail = head;
    Node *prev;
    // moving towards the end of linked list
    while(tail->next != NULL)
    {
        prev = tail;
        tail = tail->next;
    }
    delete tail;                  // delete the Node whose address is stored in "tail" pointer
    // delete prev->next;         // prev->nex & tail are pointing towards same address
    prev->next = NULL;
}



// function to delete data at end of linked list
void deleteAtMiddle(Node*&head, int pos)
{
    if(head==NULL)
    {
        return;
    }
    else if(pos >= length(head))
    {
        return;
    }
    // jump towards pos
    Node *temp = head;
    Node *prev;
    int i = 1;
    while(i <= pos)
    {
        prev = temp;
        temp = temp->next;
        i++;
    }
    prev->next = temp->next;
    delete temp;              // delete the Node whose address is stored in "temp" pointer
}


// Search Operation
// Linear Search
bool search(Node*head, int key)
{
    Node*temp = head;
    while(temp != NULL)
    {
        if(temp->data == key)
        {
            return true;
        }
        temp = temp->next;
    }
    // if key not found
    return false;
}


// Linear Search (recursively)
bool searchRecursive(Node*head, int key)
{
    //base case
    if(head == NULL)
    { 
        return false;
    }
    //rec case
    if(head->data == key)
    {
        return true;
    }
    return searchRecursive(head->next, key);
}


// Linked List User Input
void take_input(Node*&head)
{
    //
}

// Linked List User Input
Node* take_input_2()
{
    Node *head = NULL;

    int data;
    cin >> data;

    while(data != -1)
    {
        insertAtHead(head, data);
        // insertAtTail(head, data);
        cin >> data;
    }
    return head;
    /* NOTE: Since we are adding elements at "head" of linked list.
             So, we will be getting linked list in the reverse order.
    */
}


// Linked List User Input [When taking Input from a file]
Node* take_input_file()
{
    Node *head = NULL;

    int data;
    // cin >> data;

    while(cin >> data)
    // while(data != -1)
    {
        insertAtHead(head, data);
        // cin >> data;
    }
    return head;
    /* NOTE: Since we are adding elements at "head" of linked list.
             So, we will be getting linked list in the reverse order.
    */
}


/* 
    - Using "<<" for getting output
      Eg: cout << head;   
          This will print the address of head.
          But we want to print entire linked list uing "cout". 
          So, we will use operator overloading.
      
      NOTE:    cout << head;
               |         |
            ostream    Node
             object    object

         So, "<<" operator will take 2 parameter.
              One is Ostream object (for "cout")
              Second is Node object (for "head")
*/


// // Opertor Overloading (i.e for cases like: cout << head;)
// void operator<<(ostream &os, Node *head)
// {
//     print(head);
//     return;
// }


// Cascading of Operators (i.e for cases like: cout << head << head2;)
ostream& operator<<(ostream &os, Node *head)   // Both Return & Pass are by Reference
{
    print(head);
    return os;     // returning "cout" by reference

    /* 
        => cout << head << head2;
          |-----------|
           return cout

        =>        cout << head2;
                  |------------|
                    return cout

        =>               cout;  [OUTPUT]
        
        NOTE: We will get "cout; as output.
              "cout;" is a valid statement in C++ & writing it doesnot do anything.
    */
}


// Cascading of Operators (i.e for cases like: cin >> head >> head2;)
istream& operator>>(istream &is, Node *&head)
{
    head = take_input_2();
    return is;
}


// reverse a linked list  [Complexity: O(N) time + O(1) space]
void reverse(Node *&head)
{
    Node *curr = head;  // for current node
    Node *prev = NULL;  // for previous node
    Node *nxt;          // for next node

    while(curr != NULL)
    {
        nxt = curr->next;     // save the next node
        curr->next = prev;    // make the current node point to previous node
        prev = curr;          // update previous node (for the next iteration)
        curr = nxt;           // update current node (for the next iteration)
    }

    head = prev;              // update head
}


// recursively reverse a linked list  [Complexity: O(N) time + O(N) space]
Node* recursive_reverse(Node *head)
{
    // smallest linked list or when actual linked list is null
    if(head->next == NULL or head == NULL)
    {
        return head;
    }
    // rec case
    Node *smallhead = recursive_reverse(head->next);

    // Node *temp = smallhead;        // Before  Optimization    [Complexity: O(N^2) time] i.e O(N) for both recursion & Loop 
    // while(temp->next != NULL)
    // {
    //     temp = temp->next;
    // } 
    Node *temp = head->next;          // After Optimization      [Complexity: O(N) time]

    temp->next = head;
    head->next = NULL;
    return smallhead;

    /*  
    // NOTE: This is also correct.

    Node *smallhead = recursive_reverse(head->next);

    head->next->next = head;

    head->next = NULL;
    return smallhead;
     */
}


// Finding the mid point of linked list
Node* midpoint(Node *head)
{
    // linked list with 0 or 1 node
    if(head == NULL or head->next == NULL)
    {
        return head;
    }

    Node *slow = head;
    Node *fast = head->next;

    while(fast != NULL and fast->next != NULL)   // checking 2 cases for fast pointer bcz fast takes 2 steps
    {
        fast = fast->next->next;      // moving 2 steps
        slow = slow->next;            // moving 1 step
    }

    return slow;       // returning the position where slow pointer stops (i.e mid point)
}


// Finding the kth node from the end of linked list
Node* kthNode(Node *head, int k)
{
    if(head == NULL)
    {
        return head;
    }

    Node *fast = head;
    Node *slow = head;

    while(fast->next != NULL)
    {
        // moving  k steps
        if(k-1)
        {
            fast = fast->next;
            k--;
        }
        else
        {
            // moving 1 steps
            fast = fast->next;
            slow = slow->next;
        }
    }
    return slow;
}


// funtion to merge two linked lists
Node* merge(Node* a, Node* b)
{
    // base case
    if(a == NULL)
    {
        return b;
    }
    if(b == NULL)
    {
        return a;
    }
    // rec case
    Node *c;       // take a new head pointer

    if(a->data < b->data)
    {
        c = a;
        c->next = merge(a->next, b);     // return, merge of "pending a" with "b"
    } 
    else{
        c = b;
        c->next = merge(a, b->next);     // return, merge of "a" with "pending b"
    }
    return c;     // return the head pointer
    
    /*
        Eg: a :   1  ->  2  ->  4  ->  8  ->  9 ->  NULL
            b :   0  ->  5  ->  7  -> NULL

            Now, merge(a,b)
            
                c : 0  ->
                          | 1  ->  2  ->  4  ->  8  ->  9  ->  NULL       // a
                          | 5  ->  7  ->  NULL                            // pending of b

                c : 0 -> 1 -> 
                              | 2  ->  4  ->  8  ->  9  ->  NULL          // pending of a
                              | 5  ->  7  ->  NULL                        // b
                  
                c : 0 -> 1 -> 2 ->
                                   | 4  ->  8  ->  9  ->  NULL            // pending of a
                                   | 5  ->  7  ->  NULL                   // b
                
                c : 0 -> 1 -> 2 -> 4 ->
                                        | 8  ->  9  ->  NULL              // pending of a
                                        | 5  ->  7  ->  NULL              // b
                
                c : 0 -> 1 -> 2 -> 4 -> 5 ->
                                             | 8  ->  9  ->  NULL         // a
                                             | 7  ->  NULL                // pending of b
                
                c : 0 -> 1 -> 2 -> 4 -> 5 -> 7 -> 
                                                  | 8 -> 9 -> NULL        // a
                                                  | NULL                  // pending of b


                c : 0 -> 1 -> 2 -> 4 -> 5 -> 7 -> 8 -> 9 -> NULL

    */
}

// merge sort in linked list  [Time Complexity: NLogN (same as in array)]
Node* mergeSort(Node* head)
{
    // base case: For 0 or 1 Node in linked list
    if(head == NULL or head->next == NULL)
    {
        return head;
    }
    // res case:
    // 1. divide/break
    Node *mid = midpoint(head);   // Time Complexity: O(N)   (Note: array takes O(1) to find midpoint)
    Node *a = head;               // "a" points at beginning of Linked list
    Node *b = mid->next;          // "b" points next to "mid node" of Linked list (till end)
    mid->next = NULL;             // to make "a" points till "mid" (i.e to remove linked nodes after "mid")

    // 2. Recursive sort the two parts
    a = mergeSort(a);
    b = mergeSort(b);

    // 3. merge
    Node* newhead = merge(a,b);

    return newhead;
    
    /* 
        Eg:     a(head)   b(mid->next)
                |         |
            =>  1 -> 0 -> 3 ->  4
                     |
                    mid

            =>  After, mid->next = NULL;

            =>  1 -> 0      3 -> 4
                |           |
                a           b

    */
 
}


int main()
{
    Node *head = NULL;

    cout << "Enter Elements [Press -1 to Exit]: ";
    cin >> head;

    cout << "Linked List: ";
    // print(head);
    cout << head;

    head = mergeSort(head);            // sort linked list

    cout << "Linked List [Sorted]: ";
    cout << head;

    return 0;
}


/* 
OUTPUT:

    Enter Elements [Press -1 to Exit] : 14 3 10 5 1 6 -1
    Linked List                       : 6 -> 1 -> 5 -> 10 -> 3 -> 14
    Linked List [Sorted]              : 1 -> 3 -> 5 -> 6 -> 10 -> 14 

*/