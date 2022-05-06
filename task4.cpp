/*
 Имеется лог-файл, в котором хранятся пары для N пользователей (Идентификатор пользователя, посещаемость сайта).
Напишите программу, которая выбирает K пользователей, которые чаще других заходили на сайт, и выводит их в порядке возрастания посещаемости. Количество заходов и идентификаторы пользователей не повторяются.
Требования: время работы O(N * logK), где N - кол-во пользователей. Ограничение на размер кучи O(K).
Формат входных данных: Сначала вводятся N и K, затем пары (Идентификатор пользователя, посещаемость сайта).
Формат выходных данных: Идентификаторы пользователей в порядке возрастания посещаемости
*/

#include <iostream>
#include <cassert> // для assert()

// контейнер динамический массив
template<class T1, class T2>
class vector {
private:
	int m_size;
	int m_capacity;
	T1* m_id;
	T2* m_value;
	void resize(int size)
	{
		int new_capacity = m_capacity * 2;
		T1* new_id = new T1[new_capacity];
		T2* new_value = new T2[new_capacity];

		for (int i = 0; i < m_size; ++i) {
			new_id[i] = m_id[i];
			new_value[i] = m_value[i];
		}
		delete[] m_id;
		delete[] m_value;

		m_id = new_id;
		m_value = new_value;
		m_capacity = new_capacity;
	}
public:
	vector()
	{
		m_size = 0;
		m_capacity = 1;
		m_id = new T1[1];
		m_value = new T2[1];
	}
	vector(int size)
	{
		m_size = 0;
		m_capacity = size;
		if (size != 0) {
			m_id = new T1[size];
			m_value = new T2[size];
		}
		else {
			m_id = 0;
			m_value = 0;
		}
	}
	vector(const vector<T1, T2>& mas)
	{
		m_size = mas.m_size;
		m_capacity = mas.m_capacity;
		m_id = NULL;
		m_value = NULL;
		if (m_size != 0) {
			m_id = new T1[m_size];
			m_value = new T2[m_size];
		}
		else {
			m_id = 0;
			m_value = 0;
		}
		for (int i = 0; i < m_size; ++i) {
			m_id = mas.m_id;
			m_value = mas.m_value;
		}
	}
	~vector() {
		delete[] m_id;
		delete[] m_value;

	}
	void push_back(T1 val1, T2 val2)
	{
		if (m_size + 1 > m_capacity)
		{
			resize(m_size + 1);
			m_size = m_size + 1;
		}
		else {
			m_size = m_size + 1;
		}
		m_id[m_size - 1] = val1;
		m_value[m_size - 1] = val2;
	}
	int size() const
	{
		return m_size;
	}
	T1& operator[] (int i)
	{
		return m_id[i];
	}
	T1& getid(int i) 
	{
		return m_id[i];
	}
	T2& getvalue(int i) 
	{
		return m_value[i];
	}
	void changeid(T1& x, int i) {
		m_id[i] = x;
	}
	void changevalue(T2& x, int i) {
		m_value[i] = x;
	}
};

template<class T1, class T2>
std::ostream& operator << (std::ostream& out, vector<T1, T2>& a)
{
	for (int i = 0; i < a.size(); ++i)
		out << a[i] << " ";
	return out;
}

template<class T1, class T2>
class Heap {
private:
	int lenght = 0;
	vector<T1, T2> m_heap;
	void filter_up(vector<T1, T2>& arr, int n, int i)
	{
		int largest = i;
		int l = 2 * i + 1;
		int r = 2 * i + 2;

		if (l < n && m_heap.getvalue(l) > m_heap.getvalue(largest))
			largest = l;

		if (r < n && m_heap.getvalue(r) > m_heap.getvalue(largest))
			largest = r;

		if (largest != i)
		{
			T1 buf_id = m_heap.getid(i);
			T2 buf_value = m_heap.getvalue(i);
			m_heap.changeid(m_heap.getid(largest), i);
			m_heap.changevalue(m_heap.getvalue(largest), i);
			m_heap.changeid(buf_id, largest);
			m_heap.changevalue(buf_value, largest);
			filter_up(arr, n, largest);
		}
	}
	void deleteRoot()
	{
		// Получить последний элемент
		int lastid = m_heap.getid(lenght - 1);
		int lastvalue = m_heap.getvalue(lenght - 1);
		// Заменить корень первым элементо
		m_heap.changeid(lastid, 0);
		m_heap.changevalue(lastvalue, 0);
		// Уменьшаем размер кучи на 1
		lenght = lenght - 1;
		filter_up(m_heap, lenght, 0);
	}
public:
	Heap(vector<T1, T2>& arr, int N) {
		lenght = N;
		for (int i = 0; i < lenght; i++) {
			m_heap.push_back(arr.getid(i), arr.getvalue(i));
		}
		for (int i = lenght / 2 - 1; i >= 0; i--)
			filter_up(m_heap, N, i);
	}
	~Heap() {}

	T1* KmaxElementofHeap(int K = lenght) {
		T1* result = new T1[K];
		for (int i = K - 1; i >= 0; --i) {
			result[i] = m_heap.getid(0);
			deleteRoot();
		}
		return result;
	}
};
void unit_test() { // тест из контеста (с выводом 80 1 100)
	// ввод
	// 100 36
	// 80 3
	// 1 5
	int mas_id[3] = { 100, 80, 1 };
	int mas_value[3] = { 36, 3, 5 };
	vector<int, int> arr(3);
	for (int i = 0; i < 3; ++i)
	{
		arr.push_back(mas_id[i], mas_value[i]);
	}
	Heap<int, int> heap(arr, 3);
	int* result = heap.KmaxElementofHeap(3);
	int answer[3] = { 80,1,100 };
	for (int i = 0; i < 3; ++i) {
		assert(result[i] == answer[i]);
	}
	delete [] result;
	std::cout << "Test1 OK" << "\n";
}

void unit_test_2() { // тест  (с выводом 3 1 5)
	// ввод 
	// 4 3
	// 1 532
	// 3 123
	// 5 8493
	// 2 12
	int mas_id[4] = { 1, 3, 5, 2};
	int mas_value[4] = { 532, 123, 8493, 12 };
	vector<int, int> arr(4);
	for (int i = 0; i < 3; ++i)
	{
		arr.push_back(mas_id[i], mas_value[i]);
	}
	Heap<int, int> heap(arr, 4);
	int* result = heap.KmaxElementofHeap(3);
	int answer[3] = { 3,1,5 };
	for (int i = 0; i < 3; ++i) {
		assert(result[i] == answer[i]);
	}
	delete[] result;
	std::cout << "Test2 OK" << "\n";
}

int main()
{
	unit_test();
	unit_test_2();
	int N = 0;
	std::cin >> N;
	int K = 0;
	std::cin >> K;
	vector<int, int> arr(N);
	int id = 0;
	int value = 0;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> id;
		std::cin >> value;
		arr.push_back(id, value);
	}
	Heap<int, int> heap(arr,N);
	int* max_id = heap.KmaxElementofHeap(K);
	// вывод результата
	for (int i = 0; i < K; ++i) {
		std::cout << max_id[i] << " ";
	}
	delete[] max_id;
	return 0;
}

