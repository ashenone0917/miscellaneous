// ConsoleApplication3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <map>
using namespace std;
void temp(double size) {
    double size_ = size;
    size_ += 1024 * 5 * 70;
    int n = 10;
}

class A {
public:
    A& operator=(A& a_) {
        number = a_.number;
        return *this;
    }
protected:
    int number = 10;
};

class B : public A {
public:
    B(int t,int t2) {
        numberb = t;
        number = t2;
    }
    B& operator=(B& b_) {
        __super::operator=(b_);
        numberb = b_.numberb;
        return *this;
    }
private:
    int numberb = 10;
};

class Point {
public:
    constexpr Point(int n = 0, int m = 0) noexcept
        :x(n), y(m) {

    };

    constexpr int GetX() const noexcept {
        return x;
    }
    int x, y;
};

template<typename T>
bool isWString(T& t) {
    if (typeid(t) == typeid(std::wstring)) {
        std::cout << "is wstring" << std::endl;
        return true;
    }
    else {
        std::cout << "not wstring is " << typeid(t).name() << std::endl;
        return false;
    }
}

int main()
{
    auto stemp1 = std::shared_ptr<int>(new int(3));
    std::weak_ptr<int> weakPtr = stemp1;
    {
        auto temp1 = weakPtr.lock();
        stemp1.reset();
        if (weakPtr.expired()) {
            int m = 10;
        }
        else {
            int n = 100;
        }
        auto temp2 = weakPtr.lock();
        int m = 10;
    }

    auto temp22 = weakPtr.lock();
    if (weakPtr.expired()) {
        int m = 10;
    }
    std::wstring wstemp;
    std::string stemp;

    isWString(wstemp);
    isWString(stemp);
    constexpr int n = 10;
    constexpr Point point(n, 10);
    int temp1[point.GetX()];

    B b1(100,101);
    B b2(200,202);
    b1 = b2;
    A aa;
    auto astring = typeid(aa).name();
    temp(10);
    std::map<int, std::map<int,int>> temp;
    auto iter = temp.begin();
    iter->second.find(1);
    std::cout << "Hello World!\n";
}
