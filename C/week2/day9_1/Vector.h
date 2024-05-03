// 头文件：类型的定义和 API 的声明

typedef int E;

typedef struct {
	E* elements;
	int capacity;
	int size;
} Vector;

// 构造函数
Vector* vector_create(void);

// 析构函数
void  vector_destroy(Vector* v);

void push_back(Vector* v, E val);		//在数组最后添加元素

void push_front(Vector* v, E val);		//在数组最前添加元素，所有元素依次后移

E pop_back(Vector* v);		//删除最后一个元素并且返回

E pop_front(Vector* v);		//删除第一个元素并返回

