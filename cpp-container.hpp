#pragma once
#include <iostream>
#include <string>

using std::literals::string_literals::operator""s;

template <typename T>
class Container {
public:
	Container() {
		Initialize();
	}
	Container(const Container& from) {
		Initialize(from.size_);
		*this = from;
	}
	Container(const size_t size, const T& with = {}) {
		Initialize(size);
		for (size_t index = 0; index < size; ++index) {
			data_[index] = with;
		}
	}
	Container(const std::initializer_list<T>& list) {
		Initialize(list.size());
		size_t index{ 0 };
		for (const auto& item : list) {
			data_[index] = item;
			++index;
		}
	}
	~Container() {
		Clear();
	}
	Container& operator=(const Container& right) {
 		Clear();
		Initialize(right.size_);
		CopyData(data_, right.data_, right.size_);
		resize_count_ = right.resize_count_;
		capacity_ = right.capacity_;
		return *this; 
		return *this;
	}
	T& operator[](const size_t index) {
		if (index < size_) {
			return data_[index];
		}
		else {
			throw std::out_of_range("Out of range");
		}
	}
	const T& At(const size_t index) const {
		if (index < size_) {
			return data_[index];
		}
		else {
			throw std::out_of_range("Out of range");
		}
	}	
	size_t Size() const{
		return size_;
	}
	void PushBack(const T& item) {
		Resize(size_ + 1);
		data_[size_] = item;
	}
	void Resize(const size_t new_size) {
		if (!UpdateCapacity(new_size)) {
			size_ = new_size;
			return;
		}
		T* ptr = new T[capacity_];
		if (ptr == nullptr) {
			throw std::runtime_error("Memory not allocated");
		}
		CopyData(ptr, data_, (new_size > size_ ? size_ : new_size));

		delete[] data_;
		data_ = ptr;
		size_ = new_size;
	}
	void Clear() {
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

	T* data_{ nullptr };
	size_t size_{ 0 };
	size_t capacity_{ DEFAULT_CAPACITY_ };
	unsigned int resize_count_{ DEFAULT_RESIZE_COUNT_ };
	

	void Initialize(const size_t init_size = 0) {
		if (data_ != nullptr) {
			return;
		}
		UpdateCapacity(init_size);
		T* ptr = new T[capacity_];
		if (ptr == nullptr) {
			throw std::runtime_error("Memory not allocated");
		}
		size_ = init_size;
		data_ = ptr;
	}
	void CopyData(T* destination, const T* source, size_t size) {
		for (size_t index = 0; index < size; ++index) {
			destination[index] = source[index];
		}
	}
	bool UpdateCapacity(const size_t feature_size) {
		if (feature_size > capacity_) {
			capacity_ = feature_size + resize_count_;
			resize_count_ *= RESIZE_MULT_;
			return true;
		}
		else if ((feature_size + resize_count_) < capacity_) {
			capacity_ = feature_size + DEFAULT_RESIZE_COUNT_;
			resize_count_ = DEFAULT_RESIZE_COUNT_;
			return true;			
		}
		return false;
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Container<T>& right) {
	size_t size = right.Size();
	os << "Size: "s << size << std::endl;
	os << "--------------------------------"s << std::endl;
	for (size_t index{ 0 }; index < size; ++index) {
		os << '<' << (index+1) << "> "s << right.At(index) << std::endl;
	}
	os << "--------------------------------" << std::endl;
	return os;
}