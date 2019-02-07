#include<iostream>

using namespace std;


template <class Type>
class myStack{
public:
    void push(Type);
    Type pop();
    void display();
    myStack(int n){
        Size = n;
        elements = new Type[n];
        stackPointer = 0;
    }
    bool isEmpty();
    bool isFull();
    ~myStack(){
        delete [] elements;
    }

private:
    int stackPointer;
    Type *elements;
    int Size;
};

/*function description: adds an element to the top of the stack.
parameters: Type x -> data given by the user to add into the stack
return value: void
*/
template <class Type>
void myStack<Type>::push(Type x){
    try{
        if(this->isFull()){  //test if stack is full
			cout << "stack is full" << endl;
            throw 1;
        }
        else{
            elements[stackPointer] = x;  //adding data to top of stack
            stackPointer++;              //increase stack size
        }
    }
    catch(int&){   //catch exception if stack is full
        throw 1;
    }
}

/*function description: takes the top element out of the stack
 * parameters: none
 * return value: Type -> corresponds to the data type of the data stored in the stack
 * */
template <class Type>
Type myStack<Type>::pop(){
    Type temp;   //temporary variable to hold data popped from the stack
    try{
        if(this->isEmpty())  //test for empty stack
            throw 1;
        temp = elements[stackPointer-1];  //temp gets the value of the top element in the stack
        //cout << "Popped element: " << temp << endl;
        stackPointer--;  //decrease the size of the stack
        return temp;
    }
    catch(int&){   //catch exception if stack is empty
        throw 1;
    }
}

/*function description: displays all data in the stack
 * parameters: none
 * return value: void
 * */
template <class Type>
void myStack<Type>::display(){
    cout << "Stack: ";
    for(int i=0;i<stackPointer;i++)    //print all elements
        cout << elements[i] << ",";
    cout << "\b \n";  //delete the  last comma and end the line
}

/*function description: tests if the stack is empty
 * parameters: none
 * return value: void
 * */
template <class Type>
bool myStack<Type>::isEmpty(){
    if(stackPointer == 0)
        return true;
    else
        return false;

}

/*function description: tests if the stack is full
 * parameters: none
 * return value: void
 * */
template <class Type>
bool myStack<Type>::isFull(){
    if(stackPointer > Size-1)
        return true;
    else
        return false;
}

