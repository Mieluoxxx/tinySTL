#include <iostream>

template <typename T>
class myVector {
private:
    T     *elements;      // 指针
    size_t capacity;      // 容量
    size_t current_size;  // 目前大小

public:
    myVector() : elements(nullptr), capacity(0), current_size(0) {}
    ~myVector() { delete[] elements; }

    // 拷贝构造函数
    myVector(const myVector &other)
        : capacity(other.capacity), current_size(other.current_size) {
        elements = new T[capacity];  // 分配内存
        std::copy(other.elements, other.elements + current_size,
                  elements);  // 复制元素
    }

    // 赋值运算符重载
    myVector &operator=(const myVector &other) {
        if (this != other) {
            delete[] elements;  // 释放原来的内存
            capacity     = other.capacity;
            current_size = other.current_size;
            elements     = new T[capacity];
            std::copy(other.elements, other.elements + current_size, elements);
        }
        return *this;
    }

    // 尾部插入元素
    void push_back(const T &input) {
        if (current_size == capacity) {
            reverse(capacity == 0 ? 1 : capacity * 2);
        }
        elements[current_size++] = input;
    }

    // 尾部删除元素
    void pop_back() {
        if (current_size) {
            current_size--;
        }
    }

    void insert(const size_t index, const T &input) {
        if (index > current_size) throw std::out_of_range("Index out of range");
        if (current_size == capacity) {
            reverse(capacity == 0 ? 1 : capacity * 2);
        }
        for (size_t i = current_size; i > index; i--) {
            elements[i] = elements[i - 1];
        }
        elements[index] = input;
        current_size++;
    }

    // 清空容器
    void clear() { current_size = 0; }

    // 当vector本身有const时，操作符也要有const属性
    T       *begin() { return elements; }
    const T *begin() const { return elements; }

    T       *end() { return elements + current_size; }
    const T *end() const { return elements + current_size; }

    size_t size() const { return current_size; }

    // 访问元素
    T &operator[](size_t index) {
        if (index >= current_size) std::cout << "Index overstep" << std::endl;
        return elements[index];
    }
    const T &operator[](size_t index) const {
        if (index >= current_size) std::cout << "Index overstep" << std::endl;
        return elements[index];
    }

    // 打印
    void printElement() const {
        for (size_t i = 0; i < current_size; i++) {
            std::cout << elements[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    // 内存分配函数
    void reverse(size_t newCapacity) {
        if (newCapacity > capacity) {
            T *newElements = new T[newCapacity];
            std::copy(elements, elements + current_size, newElements);
            delete[] elements;
            elements = newElements;
            capacity = newCapacity;
        }
    }
};

int main() {
    myVector<int> testvec;
    testvec.push_back(0);
    std::cout << testvec.size() << std::endl;
    testvec.insert(1, 2);
    std::cout << testvec.size() << std::endl;
    std::cout << testvec[1] << std::endl;
    testvec.push_back(3);
    testvec.push_back(4);
    std::cout << "---" << std::endl;
    for (auto ele : testvec) std::cout << ele << std::endl;
    return 0;
}