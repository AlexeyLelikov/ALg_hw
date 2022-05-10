/*
Дано множество целых чисел из [0..10^9] размера n.
Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
10%  перцентиль
медиана
90%  перцентиль
Требования: к дополнительной памяти: O(n).
Среднее время работы: O(n)
6.4
Реализуйте стратегию выбора опорного элемента “случайный элемент”.
Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
*/
#include <iostream>
#include <cstdlib>
#include <cassert> // для assert()

template<class T>
class array {
    int lenght = 0;
    T* arr = NULL;
public:
    array() {
        arr = new T[lenght];
    }
    array(int n) {
        lenght = n;
        arr = new T[n];
    }
    ~array() {
        delete[] arr;
    }
    T& operator[](const int& index) {
        return arr[index];
    }
    int size(){
        return lenght;
    }
    
};
template<class T>
std::ostream& operator << (std::ostream& out,array<T>& a)
{
    for (int i = 0; i < a.size(); ++i) {
        out << a[i] << " ";
    }
    return out;
}
template<class T>
std::istream& operator>> (std::istream& in, array<T>& a)
{
    for (int i = 0; i < a.size(); ++i) {
        in >> a[i];
    }
    return in;
}

template<class T>
int Partition(array<T>& arr, int left, int right) {
    
    if (left == right) {
        return left;
    }
    //Реализация стратегии выбора опорного элемента “случайный элемент”.
    int indx_rand = left + rand() % (right - left);
    T pivot = arr[indx_rand];
    std::swap(arr[indx_rand], arr[left]);
    int i = right;
    int j = right;
    //Проход от конца массива к началу
    for ( ; j > left; j--) {
        if (arr[j] >= pivot)
        {
            std::swap(arr[i], arr[j]);
            --i;
        } 
    }
    std::swap(arr[i], arr[left]);
    return i;
}

template<class T>
T KPosition(array<T>& arr, int k, int left, int right) {
    while (true) {
        int pos = Partition(arr, left, right);
        if (pos < k) {
            left = pos + 1;
        }
        else if (pos > k) {
            right = pos - 1;
        }
        else {
            return arr[k];
        }
    }
}
// Тест на заданном массиве {1 .. 10}
template<class T>
void unit_test_simple() {
    // test 1
    int n = 10;
    T mas[10] = {1,2,3,4,5,6,7,8,9,10};
    array<T> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = mas[i];
    }
    int median = n / 2;
    int p90 = (n * 9) / 10;
    int p10 = (n * 1) / 10;
    assert(KPosition<T>(arr, p10, 0, n - 1) == 2);
    assert(KPosition<T>(arr, median, 0, n - 1) == 6);
    assert(KPosition<T>(arr, p90, 0, n - 1) == 10);
    std::cout << "test 1 OK" << "\n";
    int shared_mas[10] = { 7,3,5,2,10,4,6,9,1,8 };
    for (int i = 0; i < n; i++) {
        arr[i] = shared_mas[i];
    }
    assert(KPosition<T>(arr, p10, 0, n - 1) == 2);
    assert(KPosition<T>(arr, median, 0, n - 1) == 6);
    assert(KPosition<T>(arr, p90, 0, n - 1) == 10);
    std::cout << "test 1 shared OK" << "\n";
}

// Тест на массиве {1 .. 11}
template<class T>
void unit_test_2() {
    // test 1
    int n = 11;
    T mas[11] = { 1,2,3,4,5,6,7,8,9,10,11};
    array<T> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = mas[i];
    }
    int median = n / 2;
    int p90 = (n * 9) / 10;
    int p10 = (n * 1) / 10;
    assert(KPosition<T>(arr, p10, 0, n - 1) == 2);
    assert(KPosition<T>(arr, median, 0, n - 1) == 6);
    assert(KPosition<T>(arr, p90, 0, n - 1) == 10);
    std::cout << "test 2 OK" << "\n";
    int shared_mas[11] = { 7,11,3,5,2,10,4,6,9,1,8 };
    for (int i = 0; i < n; i++) {
        arr[i] = shared_mas[i];
    }
    assert(KPosition<T>(arr, p10, 0, n - 1) == 2);
    assert(KPosition<T>(arr, median, 0, n - 1) == 6);
    assert(KPosition<T>(arr, p90, 0, n - 1) == 10);
    std::cout << "test 2 shared OK" << "\n";
}

int main()
{   
    unit_test_simple<int>();
    unit_test_2<int>();
    int n = 0;
    std::cin >> n;
    array<int> arr(n);
    std::cin >> arr;
    int median = n / 2;
    int p90 = (n * 9) / 10;
    int p10 = (n * 1) / 10;
    int Elem_p10 = KPosition<int>(arr, p10, 0, n - 1);
    int Elem_median = KPosition<int>(arr, median, 0, n - 1);
    int Elem_p90 = KPosition<int>(arr, p90, 0, n - 1);
    std::cout << Elem_p10 << "\n";
    std::cout << Elem_median << "\n";
    std::cout << Elem_p90;
    return 0;
}
