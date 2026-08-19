#pragma once
#include <iostream>
#include <cassert>
// 템플릿 동적 배열 클래스
template<typename T>
class List
{

public:
    List()
    {
        //시작할 때 기본 크기로 저장공간 할당
        ReAllocate(defaultSize);
    }

    ~List()
    {
        delete[] data;
        data = nullptr;
    }

   
    List(const List& other) : size(other.size), capacity(other.capacity)
    {
        //저장 공간 할당
        if (other.capacity > 0)
        {
            data = new T[other.capacity];
        }

        //저장된 데이터 복사
        for (int i = 0; i < size; ++i)
        {
            data[i] = other.data[i];
        }
    }
   
    List& operator=(const List& other)
    {
        //예외처리 (같은 객체인지 확인)
        if (this == &other)
        {
            return *this;
        }

        T* newData = nullptr;

        if (other.capacity > 0)
        {
            newData = new T[other.capacity];

            //값 복사
            for (int i = 0; i < other.size; i++)
            {
                newData[i] = other.data[i];
            }
        }

        //기존의 관리하던 데이터제거
        delete[] data;

        //값 업데이트
        data = newData;
        size = other.size;
        capacity = other.capacity;

        return *this;
    }



    List(List&& other) : size(other.size), capacity(other.capacity), data(other.data)   //data 얕은 복사
    {
        //other 정리
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
   

    List& operator=(List&& other)
    {
        //예외 처리
        if (this == &other)
        {
            return *this;
        }
        //기존 데이터 제거
        delete[] data;
        data = other.data;
        size = other.size;
        capacity = other.capacity;

        //other 값 정리
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;

        return *this;
    }

    //맨 마지막 위치에 데이터 추가하는 함수
    void PushBack(const T& value)
    {
        // 1. 저장공간이 가득 찼으면 재할당
        if (size == capacity)
        {
            int newCapacity = capacity == 0 ? defaultSize : capacity * scale;
            ReAllocate(newCapacity);
        }

        // 2. 값 추가
        data[size] = value;
        ++size;
    }

    void PushBack(const T&& value)
    {
        // 1. 저장공간이 가득 찼으면 재할당
        if (size == capacity)
        {
            int newCapacity = capacity == 0 ? defaultSize : capacity * scale;
            ReAllocate(newCapacity);
        }

        // 2. 값 추가
        data[size] = std::move(value);
        ++size;
    }

    void Erase(int index)
    {
        //범위 검사
        if (index < 0 || index >= size)
        {
            //조용한 예외처리
            return;
        }

        //제거할 인덱스 뒤의 값을 앞으로 이동처리
        for (int i = index; i < size - 1; i++)
        {
            data[i] = std::move(data[i + 1]);
        }

        //값 감소 처리
        --size;
        data[size] = T{};   //기본값으로 처리, T{} 아니면 {}로 처리가능

    }

    //인덱스로 접근 가능하도록 연산자 오버로딩
    T& operator[](size_t index)
    {
        assert(index < size && "index should be less than size");
        return data[index];
    }

    const T& operator[](size_t index) const
    {
        assert(index < size && "index should be less than size");
        return data[index];
    }

    //저장된 요소를 반환하는 함수
    int Size() const { return size; }

    //저장공간 크기 값 반환 함수
    int Capacity() const { return capacity; }

    //배열이 비어있는지 확인하는 함수
    bool IsEmpty() const { return size == 0; }

    //범위 기반 루프 사용가능하도록 추가
    T* begin() { return data; }
    T* end() { return data + size; }



    
private:
    //재할당 메소드
    void ReAllocate(int newCapacity)
    {
        // 1. 새로운 공간 할당
        T* newBlock = new T[newCapacity];
        // 2. 기존 데이터 가져오기
        for (int i = 0; i < size ; ++i)
        {
            //data는 폐기 예정이기 때문에 move로 처리
            newBlock[i] = std::move(data[i]);
        }

        // 3. 기존 저장공간 폐기
        delete[] data;

        // 4. 새로운 저장공간으로 data 업데이트
        data = newBlock;

        // 5. 저장공간 크기값 업데이트
        capacity = newCapacity;
    }

private:
    //내부에서 관리하는 배열(메모리 주소)
    T* data = nullptr;

    //배열에 저장된 요소의 수
    int size = 0;

    //저장공간 크기
    int capacity = 0;

    //상수(초기 저장공간의 크기 값)
    const int defaultSize = 2;

    //상수(크기가 증가하는 배수)
    const int scale = 2;

};