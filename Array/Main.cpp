#include <iostream>
#include <cstdint>
#include <cassert>
#include <algorithm>
#include <array>

//배열 클래스
template<typename T, size_t size>
class Array
{
public:
	//배열 연산자 오버로딩
	T& operator [](size_t index)
	{
		assert(index < size && "index should be less than size");
		return data[index];
	}
	const T& operator [](size_t index) const
	{
		assert(index < size && "index should be less than size");
		return data[index];
	}
	T* begin()
	{
		return data;
	}
	T* end()
	{
		return data + size;
	}

	T* Data() {return data;}
	const T* Data() const { return data; }
	size_t Length() const { return size; }

	
	
private:
	T data[size];
};

int main()
{
	//STL의 array
	std::array<int, 20> array;
	//Array 객체 생성
	Array<int, 5> intArray;
	//std::fill(
	//	intArray.Data(), 
	//	intArray.Data() + intArray.Length(), 
	//	20
	//);

	std::fill(
		intArray.begin(),
		intArray.end(),
		100
	);

	//범위 기반 루프
	for (const auto& value : intArray)
	{
		std::cout << value << "\n";
	}

	//intArray[0] = 10;
	//intArray[5] = 30;
	//int intNumber = intArray[0];
	//const int& constNumber = intArray[0];


	//정적 배열
	//size가 const가 아니면 size가 바뀔 수 있기 때문에 에러 발생함.
	const int size = 5;
	//int array[size] = {};

	array[0] = 10;
	array[1] = 20;
	array[2] = 30;
	
	int number = array[0];

	//동적 배열(힙에 할당되는 배열)
	uint32_t dSize = 10;
	int* dArray = new int[dSize] {};
}