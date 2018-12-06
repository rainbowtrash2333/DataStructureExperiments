// 栈
class Char_Stack {
private:
	char * base;
	char * top;
	int size;
	int StackSize;
public:
	Char_Stack(int StackSize) {
		base = new char[StackSize];
		top = base;
		size = 0;
		this->StackSize = StackSize;
	}


	//清空stack
	bool clear() {
		size = 0;
		base = top;
	}
	//是否为空栈
	bool isEmpty() {
		return size == 0;
	}
	char getBase() {
		if (!isEmpty())
			return *base;
		return 0;
	}
	//栈长
	int getSize() {
		return size;
	}
	


	bool push(char e) {
		if (StackSize != size) {
			*top++ = e;
			++size;
			return true;
		}
		return false;
	}
	bool pop(char & e) {
		if (!isEmpty()) {
			--top;
			e = *top;
			--size;
			return true;
		}
		return false;
	}

};

//队列
class Char_Queue {
private:
	char * base;
	int front;
	int rear;
	int MAXQSIZE;
public:
	Char_Queue(int MAXQSIZE) {
		base = new char[MAXQSIZE];
		front = rear = 0;
		this->MAXQSIZE = MAXQSIZE;
	}
	bool isEmpty() {
		return front == rear;
	}
	bool enQueue(char e) {
		if (rear == MAXQSIZE)
			return false;
		else {
			base[rear++] = e;
			return true;
		}
	}
	//bool enQueue(string s) {
	//	for (int i = 0; i < s.size(); i++)
	//	{
	//		if (!enQueue(s[i]))
	//			return false;
	//	}
	//	return true;
	//}

	bool deQueue(char & e) {
		if (isEmpty())
			return false;
		else {
			e = base[front++];

			return true;
		}
	}
	int getSize() {
		return rear - front;
	}
};

