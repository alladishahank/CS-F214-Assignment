#include<stdio.h>
#include<iostream>
#include<cstdlib>
#define maxSize 50

char infix[] = "a+b*c+d";
char prefixExp[] = "++a*bcd";
int curr = 0;

/// @brief Node is a class to denote each individual node of the tree.
///
/// Each node is basically a doubly linked list. It contains one char variable to hold the value of the given atom
/// and 2 pointers, each pointing to the left and right node.
class node{
public:
    /// @brief Holds the data, i.e. any operator or operand in the expression.
    char data;
    /// @brief Points to the value on the left side of the node.
    node *left;
    /// @brief Points to the value on the right side of the node.
    node *right;
};

/// @brief Stack is a class for creating a stack. In
///
/// In this program the Stack class is used to convert the given infix formula to prefix form.
class Stack{
private:
    int top;
    char array[maxSize]{};
public:
    /// @brief Creates the stack from scratch.
    Stack (){
        top = -1;
    }
    /// @brief Checks whether the stack is empty or not.
    /// @return True if it is empty, or false if it has some members.
    bool isEmpty () const{
        if (top == -1)
            return true;
        else
            return false;
    }
    /// @brief Checks whether the stack is full or not.
    /// @return True if it is true, or false if it has some space left.
    bool isFull () const{
        if (top == 49)
            return true;
        else
            return false;
    }
    /// @brief Removes the topmost value of the stack.
    void pop (){
        top--;
    }
    /// @brief Pushes arguments to the stack
    /// @param c Argument to be pushed to the stack. Adds it to the top of the stack.
    void push (char c){
        if (isFull ())
            return;
        else{
            top++;
            array[top] = c;
        }
    }
    /// @brief To get the value of the topmost value of the stack.
    /// @return Value at the top.
    char getTopVal (){
        return array[top];
    }
    /// @brief To get the size of the stack.
    /// @return Value of the top.
    int getStackSize () const{
        return top;
    }
};

/// @brief Function created to check whether a given character is an operator or not
/// @param pos Variable which gives the index of the required character in the given expression.
/// @param string Variable that holds the entire expression.
/// @return The function returns 1 if it is any of the operators +,*,~,(,) or >.
int isOperator (int pos, const char string[]){
    if (string[pos] == '+' || string[pos] == '*' || string[pos] == '~' || string[pos] == '>' || string[pos] == ')' || string[pos] == '(')
        return 1;
    else
        return 0;
}

/// @brief Function to assign precedence to each of the operators.
/// @param a char variable that holds the value of the operator.
/// @return The function returns the precedence assigned to the given operator.
int checkPrecedence (char a){
    switch (a){
        case '~':
            return 4;
        case '*':
            return 3;
        case '+':
            return 2;
        case '>':
            return 1;
        case '(':
            return 0;
        case ')':
            return 0;
        default:
            return 0;
    }
}

/// @brief Function created to determine the length of a given string.
/// @param string char variable that is given as input.
/// @return The function returns the length of the given string input.
int getLen (const char string[]){
    int count = 0;
    while (string[count] != 0 && count != maxSize - 1){
        count++;
    }
    return count;
}

/// @brief Function created to reverse a given string.
/// @param string char variable that is given as input.
/// @return The function returns the reverse of the given string input.
void reverseString (char string[]){
    char temp;
    int len = getLen (string);
    for (int i = 0; i < len / 2; i++){
        temp = string[i];
        string[i] = string[len - i - 1];
        string[len - i - 1] = temp;
    }
}

/// @brief Function to convert an infix formula to a prefix formula using stacks.
/// After converting, the function prints the prefix form of the formula.
/// @param infix infix is the infix formula given as input that we want to convert to prefix form.

void infixToPrefix (char infix[])
{
    int len = getLen (infix);
    reverseString(infix);
    Stack stack;
    char prefix[maxSize];
    int count = 0;
    for (int i = 0; i < len; i++){
        if (infix[i] == '(')
            infix[i] = ')';
        else if (infix[i] == ')')
            infix[i] = '(';
    }
    for (int i = 0; i < len; i++){
        if (isOperator (i, infix) == 0){
            prefix[count] = infix[i];
            count++;
        }
        else if (infix[i] == '(')
            stack.push (infix[i]);
        else if (infix[i] == ')'){
            while (stack.getTopVal () != '(' && !stack.isEmpty ()){
                prefix[count] = stack.getTopVal();
                stack.pop ();
                count++;
            }
            if (stack.getTopVal () == '(')
                stack.pop ();
        }
        else if (isOperator (i, infix) == 1){
            if (stack.isEmpty ())
                stack.push (infix[i]);
            else{
                int precIn = checkPrecedence (infix[i]);
                int precStack = checkPrecedence (stack.getTopVal());
                if (precIn == precStack)
                    stack.push (infix[i]);
                else if (precIn == precStack && infix[i] == '~'){
                    while ((checkPrecedence (infix[i]) ==checkPrecedence (stack.getTopVal ()))&& (infix[i] == '~')){
                        prefix[count] = stack.getTopVal ();
                        count++;
                        stack.pop ();
                    }
                    stack.push (infix[i]);
                }
                else if (checkPrecedence (infix[i]) >checkPrecedence (stack.getTopVal ())){
                    stack.push (infix[i]);
                }
                else
                {
                    while ((!stack.isEmpty ())&& (checkPrecedence (infix[i]) <checkPrecedence (stack.getTopVal ()))){
                        prefix[count] = stack.getTopVal ();
                        count++;
                        stack.pop ();
                    }
                    stack.push (infix[i]);
                }
            }
        }
    }
    while (!stack.isEmpty ()){
        prefix[count] = stack.getTopVal ();
        count++;
        stack.pop ();
    }
    reverseString(prefix);
    printf ("Prefix: %s\n", prefix);
}

/// @brief Function to create the parse tree. 
///
/// This function creates the parse tree by creating nodes whenever required for the expression given. If it encounters an operator then it creates a new node for which it gets new left and right values.
/// If it encounters an operand it assigns it as a final node by giving the left and right values as NULL. 
/// If it encounters a negation sign, it creates only a value for the left side.
/// @return Returns the final parse tree.
node * parseTree(){
    int len = getLen(prefixExp);
    if(curr >= len)
        return nullptr;
    struct node * newNode = (node*)malloc(sizeof(node));
    newNode->data = prefixExp[curr];
    if(prefixExp[curr] == '>' || prefixExp[curr] == '+' || prefixExp[curr] == '*'){
        ++curr;
        newNode->left = parseTree();
        newNode->right = parseTree();
        return newNode;
    }
    else if(prefixExp[curr] == '~'){
        ++curr;
        newNode->left = parseTree();
        return newNode;
    }
    else{
        newNode->left = nullptr;
        newNode->right = nullptr;
        curr++;
        return newNode;
    }
    return 0;
}

/// @brief function to do an in-order traversal of the tree.
///
/// First it does a traversal of the left side value, then it prints the current value, and then it goes through the right side subtree.
/// @param nodee Variable passed. It is of node structure, which means that it has 1 value and 2 pointers. 
void inorderTraversal (struct node *root){
    if (root == nullptr)
        return;
    else
    {
        inorderTraversal (root->left);
        printf ("%c", (root->data));
        inorderTraversal (root->right);
    }
}

/// @brief Max calculator function
/// @param a First argument
/// @param b Second argument
/// @return Simple function created to output the greater of 2 arguments.
int max (int a, int b){
    if(a > b)
        return a;
    else
        return b;
}

/// @brief  Function to calculate the height of the entire tree.
///
/// This function uses a recursive algorithm to calculate the height of the parse tree by going through each branch of the tree and seeing which one has a greater depth.
/// @param root Input node structure that we want to find the height of.
/// @return The value returned is the height of the binary parse tree.
int height (struct node *root){
    if (root == nullptr)
        return -1;
    else
        return max (height (root->left), height (root->right)) + 1;
}

/// @brief Function to print the root node and height of the tree.
void makeTree() {
    struct node* root;
    root = parseTree();
    printf("\n");
    inorderTraversal(root);
    printf("\n");
    printf("root node: %c \n", root->data);
    printf("height of tree: %d \n", height(root));
}

/// @brief Function created to solve a given expression and gives a 1 or 0 depending on the answer.
/// @param a First operand
/// @param b Second operand
/// @param op Operator
/// @return Outputs the final answer.
int solve(int a, int b, char op){
    if(op == '+')
        return a||b;
    if(op == '*')
        return a&&b;
    if(op == '>')
        return (((!a)&&(!b))+b);
    else
        return 0;
}

int truthValue(struct node* root){
    if(root!=nullptr){
        if((root->data) == '0' || (root->data) == '1')
            return (root->data)-'0';
        int leftV = truthValue(root->left);
        int rightV = truthValue(root->right);
        return solve(leftV,rightV,root->data);
    }
    else
        return 0;
}

/// @brief This is the main function, the beginning of the program.
int main (){
    printf("Infix: %s\n",infix);
    infixToPrefix(infix);
    node *s = nullptr;
    printf("Infix after in order traversing: ");
    makeTree ();
}
