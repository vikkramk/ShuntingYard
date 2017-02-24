#include <iostream>
#include <cctype>
#include <cstddef>


//Struct for char holding node
struct Node {
	Node (char data) {
		next = NULL;
		this->data = data;
	}

	Node* next;
	char data;
};

//Stack providing push, pop, and peek for Node
class Stack {
	public:
		Stack();
		~Stack();
		char pop();
		void push(char c);
		char peek();
	private:
		Node* head;
};

Stack::Stack() {
	head = NULL;
}

Stack::~Stack() {
	while (head != NULL) {
		Node next = head->next;
		delete head;
		head = ref;
	}
}

char Stack::pop() {
	char c = head->data;
	head = head->next;
	return c;
}

void Stack::push(char c) {
	Node* newhead = new Node(c);
	newhead->next = head;
	head = newhead;
}

char Stack::peek() {
	return head->data;
}


//Get the operator precedence for an operator
int opPrecedence(char c) {
	char operators[256] = {};

	if (c > 256)
		return 0;

	operators['+'] = 1;
	operators['-'] = 1;
	operators['*'] = 2;
	operators['/'] = 2;
	operators['^'] = 3;

	return operators[c];
}


//Main function
int main() {
	char tokens[80];
	Stack stack = new Stack();

	std::cin >> tokens;
	while (*tokens++ != '\0') {	//Iterate through characters
		if (isdigit(*tokens)) {
			std::cout << *tokens;
		}
		else if (opPrecedence(*tokens)!=0) {
			while (opPrecedence(stack->peek()) > opPrecedence(*tokens)) {
				std::cout << stack->pop();
			}
			stack->push(*tokens);
		}
		if (tokens* == '(') {
			stack->push(*tokens);
		}
		if (tokens* == ')') {
			while (stack->peek() != '(')
				std::cout << stack->pop();
			stack->pop();
		}
		while (stack->peek() != NULL) {
				std::cout << stack->pop();
		}
	}
}