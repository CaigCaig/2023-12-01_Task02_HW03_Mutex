#include <iostream>
#include <Windows.h>
#include <mutex>


using namespace std::chrono_literals;
using namespace std;

class Data_l {
private:
    int x;
    mutex m;
public:
    Data_l() { x = 0; }
    void Set(int n) { x = n;}
    int Get(void)
    {
        lock_guard<mutex> l(m);
        return x;
    }
};

class Data_sl {
private:
    int x;
    mutex m;
public:
    Data_sl() { x = 0; }
    void Set(int n) { x = n; }
    int Get(void)
    {
        scoped_lock(m);
        return x;
    }
};

class Data_ul {
private:
    int x;
    mutex m;
public:
    Data_ul() { x = 0; }
    void Set(int n) { x = n; }
    int Get(void)
    {
        unique_lock<mutex> ul(m);
        return x;
    }
};

void swap_l(Data_l& lhs, Data_l& rhs)
{
    int t = 0;
    t = lhs.Get();
    lhs.Set(rhs.Get());
    rhs.Set(t);
}

void swap_sl(Data_sl& lhs, Data_sl& rhs)
{
    int t = 0;
    t = lhs.Get();
    lhs.Set(rhs.Get());
    rhs.Set(t);
}

void swap_ul(Data_ul& lhs, Data_ul& rhs)
{
    int t = 0;
    t = lhs.Get();
    lhs.Set(rhs.Get());
    rhs.Set(t);
}

int main()
{
    Data_l data_l1, data_l2;
    data_l1.Set(5);
    data_l2.Set(10);
    cout << "data_l1 = " << data_l1.Get() << "; data_l2 = " << data_l2.Get() << endl;
    swap_l(data_l1, data_l2);
    cout << "Swap lock: data1 = " << data_l1.Get() << "; data2 = " << data_l2.Get() << endl << endl;

    Data_sl data_sl1, data_sl2;
    data_sl1.Set(3);
    data_sl2.Set(6);
    cout << "data_sl1 = " << data_sl1.Get() << "; data_sl2 = " << data_sl2.Get() << endl;
    swap_sl(data_sl1, data_sl2);
    cout << "Swap scoped_lock: data_sl1 = " << data_sl1.Get() << "; data_sl2 = " << data_sl2.Get() << endl << endl;

    Data_ul data_ul1, data_ul2;
    data_ul1.Set(100);
    data_ul2.Set(200);
    cout << "data_ul1 = " << data_ul1.Get() << "; data_ul2 = " << data_ul2.Get() << endl;
    swap_ul(data_ul1, data_ul2);
    cout << "Swap unique_lock: data_ul1 = " << data_ul1.Get() << "; data_ul2 = " << data_ul2.Get() << endl << endl;
    system("pause");
    return 0;
}

/*
Защищённый обмен данными
Создайте класс Data, содержащий в качестве полей скалярные данные и мьютекс.
Создайте функцию swap, которая принимает ссылки на два объекта класса Data и обменивает их местами.
В функциях нужно сначала захватить мьютексы обоих объектов, а затем выполнить обмен данными.
Реализуйте три варианта этой функции: при помощи lock, scoped_lock и unique_lock.
*/