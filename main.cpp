/*Implementation of the Shunting Yard Algorithm
* Converts infix to postfix notation
* Uses a linked list stack
* Enter a line with spaces between tokens
*/

#include <iostream>
#include <cctype>
#include <cstddef>
#include <cstring>


//Struct for char-holding node
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
	//Delete the nodes
	while (head != NULL) {
		Node* next = head->next;
		delete head;
		head = next;
	}
}

//Pop from the head
char Stack::pop() {
	if (head == NULL)
		return '\0';
	char c = head->data;
	head = head->next;
	return c;
}

//Push by making a new head
void Stack::push(char c) {
	Node* newhead = new Node(c);
	newhead->next = head;
	head = newhead;
}

//Peek at head
char Stack::peek() {
	if (head != NULL)
		return head->data;
	else
		return '\0';
}


//Get the precedence for an operator from a lookup table
int opPrecedence(char c) {
	char operators[256] = {0};

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
	Stack ops;
	char line[80];
	char* lineptr = line;
	bool finished = false;

	std::cin.getline(line, 80);

	while (!finished) {
		//Get the next token
		char token[80];
		int i;
		for (i = 0; *lineptr != ' ' && *lineptr != '\0'; i++, lineptr++) {
			token[i] = *lineptr;
		}
		token[i] = '\0';

		//Set to be done if reaching end of line
		finished = (*(lineptr++) == '\0');

		//Print numbers
		if (isdigit(token[0])) {
			std::cout << token << std::flush;
		}
		//Deal with an operator
		else if (opPrecedence(token[0])!=0) {
			//Print all ops on stack with a higher precedence
			while (opPrecedence(ops.peek()) > opPrecedence(token[0])) {
				std::cout << ops.pop() << std::flush;
			}
			//Push this operator
			ops.push(token[0]);
		}
		//Push if a left paren
		if (token[0] == '(') {
			ops.push(*token);
		}
		//Deal with right paren
		if (token[0] == ')') {
			//Pop all ops until the left paren
			while (ops.peek() != '(')
				std::cout << ops.pop() << std::flush;
			//Dispose of left paren
			ops.pop();
		}

		//Space the tokens
		std::cout << " " << std::flush;
	}

	//Print rest of the ops of stack
	while (ops.peek() != '\0') {
		std::cout << ops.pop() << " " << std::flush;
	}

	std::cout << std::endl;	//Newline

	return 0;
}