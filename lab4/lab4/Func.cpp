#include <deque>
#include <iostream>
#include <stack>
#include <queue>
#include <iostream>

class Point {
public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    bool operator<(const Point& other) const {
        if (x == other.x) {
            return y < other.y;
        }
        return x < other.x;
    }
    //bool operator<(const Point& other) const {
    //    // —начала сравниваем координаты по оси x,
    //    // если они равны, тогда сравниваем по оси y
    //    return x != other.x ? x < other.x : y < other.y;
    //}
    Point& operator=(const Point& other) {
        if (this != &other) { 
            x = other.x;
            y = other.y;
        }
        return *this;
    }
    bool operator==(const Point& other) const {
        return (x == other.x) && (y == other.y);
    }
    bool operator!=(const Point& other) const {
        return (x != other.x) || (y != other.y);
    }
    template<typename T>
    void changeCoordinates(const T& newX, const T& newY) {
        x = newX;
        y = newY;
    }
private:
    int x, y;

    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }
};

template<typename T>
void PrintDeque(const std::deque<T>& dq) {
    for (const auto& elem : dq) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void PrintStack(std::stack<T> s) {
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
}

template<typename T>
void PrintQueue(std::queue<T> q) {
    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;
}

template<typename T>
void PrintPriorityQueue(std::priority_queue<T> pq) {
    while (!pq.empty()) {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << std::endl;
}

template<typename T>
void PrintContainer(const T& container) {
    for (const auto& elem : container) {
        std::cout << elem.getX() << ", " << elem.getY() << std::endl;
    }
}

template <typename T>
void printElement(const T& element) {
    std::cout << element << " ";
}

template<typename T>
void changePointCoordinates(Point& point, const T& newX, const T& newY) {
    point.changeCoordinates(newX, newY);
}

//bool operator<(const Point& lhs, const Point& rhs) {
//    // —равниваем точки по их координатам
//    if (lhs.getX() != rhs.getX()) {
//        return lhs.getX() < rhs.getX(); // —равниваем по x
//    }
//    return lhs.getY() < rhs.getY(); // ≈сли x равны, сравниваем по y
//}



