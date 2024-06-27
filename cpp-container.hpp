#pragma once
#include <iostream>
#include <string>

template <typename T>
class Container {
public:
/* CONSTRUCTORS AND DESTRUCTORS */
	Container() :
		resize_count_{ DEFAULT_RESIZE_COUNT_ },
		capacity_{ DEFAULT_CAPACITY_ },
		data_{ Initialize(0) },
		size_{ 0 }
	{
		// Default Consructor
	}
	Container(const Container& other) :
		resize_count_{ other.resize_count_ },
		capacity_{ other.capacity_ },
		data_{ CopyFromSource(other.data_,other.size_) },
		size_{ other.size_ }
	{
		// Copy Constructor
	}
	Container(Container&& other) :
		resize_count_{ other.resize_count_ },
		capacity_{ other.capacity_ },
		data_{ other.data_ },
		size_{ other.size_ }
	{
		// Move Constructor
		other.data_ = nullptr;
		other.size_ = 0;
		other.resize_count_ = DEFAULT_RESIZE_COUNT_;
		other.capacity_ = DEFAULT_CAPACITY_;
	}
	Container(const std::initializer_list<T>& list) :
		resize_count_{ DEFAULT_RESIZE_COUNT_ },
		capacity_{ DEFAULT_CAPACITY_ },
		data_{ CopyFromSource(list) },
		size_{ list.size() }
	{
		// Parametrized Constructor with initializer_list
	}
	Container(const size_t size, const T& with = {}) :
		resize_count_{ DEFAULT_RESIZE_COUNT_ },
		capacity_{ DEFAULT_CAPACITY_ },
		data_{ CopyFromSource(size,with) },
		size_{ size }
	{
		// Parametrized Constructor with constant item value
	}
	~Container() {
		// Destructor
		Clear();
	}
/* OPERATORS */
	Container& operator=(Container&& other) {
		// Move assignment operator
		if (this != &other) {
			Clear();
			data_ = other.data_;
			size_ = other.size_;
			resize_count_ = other.resize_count_;
			capacity_ = other.capacity_;
			other.data_ = nullptr;
			other.size_ = 0;
			other.resize_count_ = DEFAULT_RESIZE_COUNT_;
			other.capacity_ = DEFAULT_CAPACITY_;
		}
		return *this;
	}
	Container& operator=(const Container& other) {
		// Copy assignment operator
		if (this != &other) {
			Clear();
			resize_count_ = other.resize_count_;
			capacity_ = other.capacity_;
			data_ = CopyFromSource(other.data_, other.size_);
			size_ = other.size_;
		}
		return *this;
	}
	T& operator[](const size_t index) {
		// Subscripting operator: returns constant ref to an item in array
		if (index < size_) {
			return data_[index];
		}
		else {
			throw std::out_of_range("Out of range");
		}
	}
/* PUBLIC METHODS */
	const T& At(const size_t index) const {
		// Returns constant ref to item in array
		if (index < size_) {
			return data_[index];
		}
		else {
			throw std::out_of_range("Out of range");
		}
	}	
	size_t Size() const {
		// Get size of array
		return size_;
	}
	void PushBack(const T& item) {
		// Insert item at the end of array
		Resize(size_ + 1);
		data_[size_] = item;
	}
	void Resize(const size_t new_size) {
		if (size_ == 0 || data_ == nullptr) {
			resize_count_ = DEFAULT_RESIZE_COUNT_;
			capacity_ = DEFAULT_CAPACITY_;
			size_ = new_size;
			Initialize(new_size);
			return;
		}
		if (UpdateCapacity(new_size) != UpdateCapacityResult::INCREASED) {
			size_ = new_size;
			return;
		}
		T* ptr = CopyFromSource(data_, (new_size > size_ ? size_ : new_size));
		if (ptr == nullptr) {
			throw std::runtime_error("Memory not allocated");
		}
		delete[] data_;
		data_ = ptr;
		size_ = new_size;
	}
	void Clear() {
		// Clear data 
		delete[] data_;
		data_ = nullptr;
		size_ = 0;
		resize_count_ = DEFAULT_RESIZE_COUNT_;
		capacity_ = DEFAULT_CAPACITY_;
	}	
private:
	const unsigned short RESIZE_MULT_{ 2 };
	const unsigned int DEFAULT_RESIZE_COUNT_{ 10 };
	const unsigned int DEFAULT_CAPACITY_{ 10 };
	enum class UpdateCapacityResult {
		NOT_CHANGED,
		INITIALIZED,
		INCREASED,
		DECREASED
	};

	unsigned int resize_count_{ DEFAULT_RESIZE_COUNT_ };
	size_t capacity_{ DEFAULT_CAPACITY_ };
	T* data_{ nullptr };
	size_t size_{ 0 };

	T* CopyFromSource(const T* source, const size_t source_size) {
		T* destination = new T[capacity_];
		for (size_t index{ 0 }; index < source_size; ++index) {
			destination[index] = source[index];
		}
		return destination;
	}
	T* CopyFromSource(const std::initializer_list<T>& list) {
		UpdateCapacity(list.size());
		T* destination = new T[capacity_];
		size_t index{ 0 };
		for (const auto& item : list) {
			destination[index] = item;
			++index;
		}
		return destination;
	}
	T* CopyFromSource(const size_t size, const T& with = {}) {
		UpdateCapacity(size);
		T* destination = new T[capacity_];
		for (size_t index {0}; index < size; ++index) {
			destination[index] = with;
		}
		return destination;
	}
	T* Initialize(const size_t init_size) {
		UpdateCapacity(init_size);
		return new T[capacity_];
	}
	UpdateCapacityResult UpdateCapacity(const size_t feature_size) {
		if (feature_size == 0) {
			capacity_ = DEFAULT_CAPACITY_;
			resize_count_ = DEFAULT_RESIZE_COUNT_;
			return UpdateCapacityResult::INITIALIZED;
		}
		else if (feature_size > capacity_) {
			capacity_ = feature_size + resize_count_; //45
			resize_count_ *= RESIZE_MULT_; //40
			return UpdateCapacityResult::INCREASED;
		}
		else if ((feature_size + resize_count_) < capacity_) {
			capacity_ = feature_size + DEFAULT_RESIZE_COUNT_;
			resize_count_ = DEFAULT_RESIZE_COUNT_;
			return UpdateCapacityResult::DECREASED;
		}
		return UpdateCapacityResult::NOT_CHANGED;
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Container<T>& right) {
	using std::literals::string_literals::operator""s;
	size_t size = right.Size();
	os << "Size: "s << size << '\n';
	os << "--------------------------------"s << '\n';
	for (size_t index{ 0 }; index < size; ++index) {
		os << '<' << (index+1) << "> "s << right.At(index) << '\n';
	}
	os << "--------------------------------" << '\n';
	return os;
}