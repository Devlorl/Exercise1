#include <iostream>
#include <vector>
#include <iostream>

using namespace std;

typedef bool (*Compfunc)(int, int);

class Array {
public:
	Array() {};
	Array(int s) : size(s) {
		cout << "Created array successfully!\n";
	};
	~Array() {};
	//Get infor
	void Input();
	void Output();
	//Selection
	int get_Size();
	int get_Element(int);

	//Search
	int linear_Search(int);
	int binary_Search(int);
	int interpolation_Search(int);

	void Swap(int&, int&);
	bool Ascending(int, int);
	bool Descending(int, int);

	//Sort
	void selection_Sort(Compfunc Sort);
	void insertion_Sort(Compfunc Sort);
	void bubble_Sort(Compfunc Sort);
	void quick_Sort(int, int, bool, Compfunc Sort);
	void heap_Sort(Array& a, bool);
	void shell_Sort(Array& a, bool);
	void radix_Sort(Array& a, bool);

protected:
	void heapify(Array& a, int, int, bool);
	int findMax(Array& a);
private:
	int a[100];
	int size;
};

void Array::Input() {
	for (int i = 0; i < this->size; i++) {
		cout << "A[" << i << "] = ";
		cin >> this->a[i];
	}
}

void Array::Output() {
	for (int i = 0; i < this->size; i++) {
		cout << "A[" << i << "] = " << this->a[i] << "\t";
	}
}

int Array::get_Size() {
	return this->size;
}

int Array::get_Element(int x) {
	for (int i = 0; i < this->size; i++) {
		if (this->a[i] == x) {
			return this->a[i];
		}
	}
	return -1;
}

//Linear Search
int Array::linear_Search(int x) {
	int vt = 0;
	while (vt < this->size && a[vt] != x) {
		vt++;
	}
	if (vt == this->size)
		return -1;
	return vt;
}

//Binary Search
int Array::binary_Search(int x) {
	int left = 0, right = this->size - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (a[mid] == x) {
			return mid;
		}
		else if (a[mid] > x) {
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	return -1;	// Not found.
}

//Interpolation search
int Array::interpolation_Search(int x) {
	int left = 0;
	int right = this->size - 1;

	while (left <= right && x >= this->a[left] && x <= this->a[right]) {
		int pos = left + ((x - this->a[left]) * (right - left)) / (this->a[right] - this->a[left]);

		if (this->a[pos] == x) {
			return pos;
		}
		if (this->a[pos] < x) {
			left = pos + 1;
		}
		else {
			right = pos - 1;
		}
	}
	return -1;
}

//Swap & Asc - Dsc
void Array::Swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

bool Ascending(int l, int r) {
	return l > r;
}

bool Descending(int l, int r) {
	return l < r;
}


//Sorted Method
void Array::selection_Sort(Compfunc Sort) {
	for (int i = 0; i < this->size - 1; i++) {
		for (int j = i + 1; j < this->size; j++) {
			if (Sort(this->a[i], this->a[j])) {
				Swap(this->a[i], this->a[j]);
			}
		}
	}
}

void Array::insertion_Sort(Compfunc Sort) {
	int key, j;
	for (int i = 1; i < this->size; i++) {
		key = this->a[i];
		j = i - 1;
		while (j >= 0 && Sort(this->a[j], key)) {
			this->a[j + 1] = this->a[j];
			j -= 1;
		}
		this->a[j + 1] = key;
	}
}

void Array::bubble_Sort(Compfunc Sort) {
	for (int i = 0; i < this->size - 1; i++) {
		for (int j = this->size - 1; j > i; j--) {
			if (Sort(this->a[j-1], this->a[j])) {
				Swap(this->a[j], this->a[j - 1]);
			}
		}
	}
}

void Array::quick_Sort(int left, int right, bool check_type, Compfunc Sort) {
	int pivot = this->a[(left + right) / 2];
	int i = left, j = right;
	while (i <= j) {
		//If check_type is true -> Ascending
		if (check_type == true) {
			while (this->a[i] < pivot) {
				i++;
			}
			while (this->a[j] > pivot) {
				j--;
			}
		}
		else {
			while (this->a[i] > pivot) {
				i++;
			}
			while (this->a[j] < pivot) {
				j--;
			}
		}
		if (i <= j) {
			Swap(this->a[i], this->a[j]);
			i++;
			j--;
		}
	}
	if (left < j) {
		quick_Sort(left, j, check_type, Sort);
	}
	if (i < right) {
		quick_Sort(i, right, check_type, Sort);
	}
}

void Array::heapify(Array& a, int n, int root, bool check_type) {
	int largest = root;
	int left = 2 * root + 1;
	int right = 2 * root + 2;
	//If check_type == true -> Ascending
	if (check_type == true) {
		if (left < n && this->a[left] > this->a[largest])
			largest = left;
		if (right < n && this->a[right] > this->a[largest])
			largest = right;
	}
	else {
		if (left < n && this->a[left] < this->a[largest])
			largest = left;
		if (right < n && this->a[right] < this->a[largest])
			largest = right;
	}
	if (largest != root) {
		Swap(this->a[root], this->a[largest]);
		heapify(a, n, largest, check_type);
	}
}

void Array::heap_Sort(Array& a, bool check_type) {
	int n = this->size;
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(a, n, i, check_type);
	}
	for (int i = n - 1; i > 0; i--) {
		Swap(this->a[0], this->a[i]);
		heapify(a, i, 0, check_type);
	}
}

void Array::shell_Sort(Array& a, bool check_type) {
	int n = this->size;
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i++) {
			int temp = this->a[i];
			int j;
			if (check_type == true) {
				for (j = i; j >= gap && this->a[j - gap] > temp; j -= gap) {
					this->a[j] = this->a[j - gap];
				}
			}
			else {
				for (j = i; j >= gap && this->a[j - gap] < temp; j -= gap) {
					this->a[j] = this->a[j - gap];
				}
			}
			this->a[j] = temp;
		}
	}
}

int Array::findMax(Array& a) {
	int max = this->a[0];
	for (int i = 1; i < this->size; i++) {
		if (this->a[i] > max) {
			max = this->a[i];
		}
	}
	return max;
}

void Array::radix_Sort(Array& a, bool check_type) {
	const int n = a.get_Size();
	int max = findMax(a);
	for (int exp = 1; max / exp > 0; exp *= 10) {
		std::vector<int> output(n);
		int count[10] = {0};

		for (int i = 0; i < n; i++) {
			int index = (check_type == true) ? ((this->a[i] / exp) % 10) : (9 - ((this->a[i] / exp) % 10));
			count[index]++;
		}

		for (int i = 1; i < 10; i++) {
			count[i] += count[i - 1];
		}

		for (int i = n - 1; i >= 0; i--) {
			int index = (check_type == true) ? ((this->a[i] / exp) % 10) : (9 - ((this->a[i] / exp) % 10));
			output[count[index] - 1] = this->a[i];
			count[index]--;
		}

		for (int i = 0; i < n; i++) {
			this->a[i] = output[i];
		}
	}
}

//Selection Search & Sorted method
void search_Location(Array a, int x, const string& type) {
	if (type == "Linearsearch") {
		cout << "\nSearch " << x << " by Linear search:\n";
		if (a.linear_Search(x) != -1) {
			cout << "Find the number " << x << " at position " << a.linear_Search(x) << " in the array!\n";
		}
		else {
			cout << "Element " << x << " was not found in the array!\n";
		}
	}
	else if (type == "Binarysearch") {
		cout << "\nSearch " << x << " by Binary search:\n";
		if (a.binary_Search(x) != -1) {
			cout << "Find the number " << x << " at position " << a.binary_Search(x) << " in the array!\n";
		}
		else {
			cout << "Element " << x << " was not found in the array!\n";
		}
	}
	else if (type == "Interpolationsearch") {
		cout << "\nSearch " << x << " by Interpolation search:\n";
		if (a.interpolation_Search(x) != -1) {
			cout << "Find the number " << x << " at position " << a.interpolation_Search(x) << " in the array!\n";
		}
		else {
			cout << "Element " << x << " was not found in the array!\n";
		}
	}
	else {
		std::cout << "\nInvalid method!" << std::endl;
	}
}

void sort_Array(Array& a,const string& method,const string& type) {
	int s = a.get_Size();
	if (method == "Selectionsort") {
		if (type == "Ascending") {
			a.selection_Sort(Ascending);
		}
		else {
			a.selection_Sort(Descending);
		}
	}
	else if (method == "Insertionsort") {
		if (type == "Ascending") {
			a.insertion_Sort(Ascending);
		}
		else {
			a.insertion_Sort(Descending);
		}
	}
	else if (method == "Bubblesort") {
		if (type == "Ascending") {
			a.bubble_Sort(Ascending);
		}
		else {
			a.bubble_Sort(Descending);
		}
	}
	else if(method == "Quicksort") {
		if (type == "Ascending") {
			a.quick_Sort(0, s - 1, true, Ascending);
		}
		else {
			a.quick_Sort(0, s - 1, false, Descending);
		}
	}
	else if (method == "Heapsort") {
		if (type == "Ascending") {
			a.heap_Sort(a, true);
		}
		else {
			a.heap_Sort(a, false);
		}
	}
	else if (method == "Shellsort") {
		if (type == "Ascending") {
			a.shell_Sort(a, true);
		}
		else {
			a.shell_Sort(a, false);
		}
	}
	else if (method == "Radixsort") {
		if (type == "Ascending") {
			a.radix_Sort(a, true);
		}
		else {
			a.radix_Sort(a, false);
		}
	}
	else {
		std::cout << "\nInvalid method!" << std::endl;
	}
}


int main() {
	cout << "Name: Dinh Duc\t\t Class: 22T_DT2\n";
	cout << "MSSV: 102220098\n\n";
	int s;
	cout << "Enter the size of Array: ";
	cin >> s;

	//Initialize array with size s
	Array a(s);

	//Get inforation of array
	a.Input();
	cout << "\nArray is:\n";
	a.Output();

	//Get size of array
	cout << "\n\nSize of array is: " << a.get_Size();

	//Get element
	int e;
	cout << "\n\nEnter the number you want to search: ";
	cin >> e;
	if (a.get_Element(e) != -1) {
		cout << "\nFind the number " << e << " in the array!\n";
	}
	else {
		cout << "\nNumber " << e << " was not found in the array!\n";
	}

	//Search method
	int l;
	cout << "\nEnter the position of the element you want to find in the array: ";
	cin >> l;

	search_Location(a, l, "Linearsearch");	// Search by Linear search

	search_Location(a, l, "Binarysearch");	// Search by Binary search

	search_Location(a, l, "Interpolationsearch");	// Search by Interpolation search

	//Sort method
	sort_Array(a, "Selectionsort", "Descending");	// Descending with Selection sort
	cout << "\n\nArray after descending with Selection sort is:\n";
	a.Output();

	sort_Array(a, "Insertionsort", "Ascending");	// Ascending with Insertion sort
	cout << "\n\nArray after ascending with Insertion sort is:\n";
	a.Output();

	sort_Array(a, "Bubblesort", "Descending");	// Descending with Bubble sort
	cout << "\n\nArray after descending with Bubble sort is:\n";
	a.Output();

	sort_Array(a, "Quicksort", "Ascending");	// Ascending with Quick Sort
	cout << "\n\nArray after ascending with Quick sort is:\n";
	a.Output();

	sort_Array(a, "Heapsort", "Ascending");	// Ascending with Heap sort
	cout << "\n\nArray after ascending with Heap sort is:\n";
	a.Output();

	sort_Array(a, "Shellsort", "Descending");	// Descending with Shell sort
	cout << "\n\nArray after descending with Shell sort is:\n";
	a.Output();

	sort_Array(a, "Radixsort", "Ascending");	// Ascending with Radix sort
	cout << "\n\nArray after ascending with Radix sort is:\n";
	a.Output();

	return 0;
}