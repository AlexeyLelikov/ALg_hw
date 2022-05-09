#include <iostream>
#include <cassert> // для assert();

template<class T>
T max(T a, T b) { return a > b ? a : b; }
template<class T>
T min(T a, T b) { return a < b ? a : b; }

template<class T>
struct Node {
	T m_id;
	T m_value;
	Node operator=(Node v1)
	{
		this->m_id = v1.m_id, this->m_value = v1.m_value;
		return *this;
	}
};

template<class T>
class vector {
private:
	int m_size;
	int m_capacity;
	Node<T>* arr;
	void resize(int size)
	{
		int new_capacity = m_capacity * 2;
		Node<T>* new_arr = new Node<T>[new_capacity];

		for (int i = 0; i < m_size; ++i) {
			new_arr[i] = arr[i];
		}
		delete[] arr;


		arr = new_arr;
		m_capacity = new_capacity;
	}
public:
	vector()
	{
		m_size = 0;
		m_capacity = 1;

		arr = new Node<T>[1];
	}
	vector(int size)
	{
		m_size = 0;
		m_capacity = size;
		if (size != 0) {
			arr = new Node<T>[size];
		}
		else {
			arr = 0;
		}
	}
	vector(const vector<T>& mas)
	{
		m_size = mas.m_size;
		m_capacity = mas.m_capacity;
		arr = NULL;
		if (m_size != 0) {
			arr = new Node<T>[m_size];
		}
		else {
			arr = 0;
		}
		for (int i = 0; i < m_size; ++i) {
			arr = mas.arr;
		}
	}
	~vector() {
		delete[] arr;
	}
	void push_back(T val1, T val2)
	{
		if (m_size + 1 > m_capacity)
		{
			resize(m_size + 1);
			m_size = m_size + 1;
		}
		else {
			m_size = m_size + 1;
		}
		arr[m_size - 1].m_id = val1;
		arr[m_size - 1].m_value = val2;
	}
	int size() const
	{
		return m_size;
	}
	T& operator[] (int i)
	{
		return arr[i].m_value;
	}
	T& getid(int i)
	{
		return arr[i].m_id;
	}
	T& getvalue(int i)
	{
		return arr[i].m_value;
	}
	void changeid(T& x, int i) {
		arr[i].m_id = x;
	}
	void changevalue(T& x, int i) {
		arr[i].m_value = x;
	}
};

template<class T>
std::ostream& operator << (std::ostream& out, vector<T>& a)
{
	for (int i = 0; i < a.size(); ++i)
		out << a[i] << " ";
	return out;
}

template<class T>
class Heap {
private:
	int lenght = 0;
	vector<T> m_heap;
	void filter_up(vector<T>& arr, int n, int i)
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
			T buf_id = m_heap.getid(i);
			T buf_value = m_heap.getvalue(i);
			m_heap.changeid(m_heap.getid(largest), i);
			m_heap.changevalue(m_heap.getvalue(largest), i);
			m_heap.changeid(buf_id, largest);
			m_heap.changevalue(buf_value, largest);
			filter_up(arr, n, largest);
		}
	}
	void HeapSort() {
		for (int i = lenght - 1; i >= 0; i--) {
			// Переместить текущий корень в конец
			T buf_id = m_heap.getid(0);
			T buf_value = m_heap.getvalue(0);
			m_heap.changeid(m_heap.getid(i), 0);
			m_heap.changevalue(m_heap.getvalue(i), 0);
			m_heap.changeid(buf_id, i);
			m_heap.changevalue(buf_value, i);
			// вызовите максимальный  на уменьшенной куче
			filter_up(m_heap, i, 0);
		}
	}
public:
	void deleteRoot()
	{
		// Получить последний элемент
		int lastid = m_heap.getid(lenght - 1);
		int lastvalue = m_heap.getvalue(lenght - 1);
		// Заменить корень первым элементом
		m_heap.changeid(lastid, 0);
		m_heap.changevalue(lastvalue, 0);
		// Уменьшаем размер кучи на 1
		lenght = lenght - 1;
		filter_up(m_heap, lenght, 0);
	}
	Heap(vector<T>& arr, int K) {
		lenght = K;
		T max_el = arr.getvalue(0);
		for (int i = 0; i < arr.size(); i++) {
			if (i < K) {
				max_el = max<T>(max_el, arr.getvalue(i));
				m_heap.push_back(arr.getid(i), arr.getvalue(i));
			}
			else if (arr.getvalue(i) > max_el) {
				HeapSort();
				m_heap.changeid(arr.getid(i),K - 1);
				m_heap.changevalue(arr.getvalue(i), K - 1);
			}
		}
		for (int i = lenght / 2 - 1; i >= 0; i--)
			filter_up(m_heap, K, i);
	}
	~Heap() {}
	T getHeapElemID(int index) {
		return m_heap.getid(index);
	}
};

template<class T>
T* KmaxElementofHeap(Heap<T>& heap,int K) {
	T* result = new T[K];
	for (int i = K - 1; i >= 0; --i) {
		result[i] = heap.getHeapElemID(0);
		heap.deleteRoot();
	}
	return result;
}



int main()
{
	int N = 0;
	std::cin >> N;
	int K = 0;
	std::cin >> K;
	vector<int> arr(N);
	int id = 0;
	int value = 0;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> id;
		std::cin >> value;
		arr.push_back(id, value);
	}
	Heap<int> heap(arr,K);
	int* max_id = KmaxElementofHeap(heap,K);
	// вывод результата
	for (int i = 0; i < K; ++i) {
		std::cout << max_id[i] << " ";
	}
	delete[] max_id;
	return 0;
}

