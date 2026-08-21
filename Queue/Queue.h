#pragma once
#include <iostream>

//큐 클래스 템플릿
template<typename T, size_t capacity = 100>
class Queue 
{
public:
    Queue()
        : front(0), rear(0)
    { }

    //큐를 초기화하는 함수
    void Clear()
    {
        front = 0;
        rear = 0;
    }

    //큐 뒤에 데이터 추가하는 함수
    bool Enqueue(const T& value)
    {
        //큐가 가득 찼으면 실패
        if(IsFull())
        {
            return false;
        }

        //rear를 다음 위치로 이동한 뒤 데이터 저장
        rear = (rear + 1) % bufferSize;
        data[rear] = value;

        //성공 반환
        return true;
    }
    //큐 앞에서 데이터 제거하는 함수
    bool Dequeue(T& outValue)
    {
        //비었으면 실패
        if (IsEmpty())
        {
            return false;
        }

        //front를 첫번째 데이터 위치로 이동
        front = (front + 1) % bufferSize;

        //데이터 출력
        outValue = data[front];

        //데이터 출력 후 기존 위치 초기화
        data[front] = T();

        //성공 반환
        return true;
    }

    //맨 앞에 있는 데이터 확인하는 함수(제거 안함)
    bool Front(T& outValue) const
    {
        //비었으면 실패
        if (IsEmpty())
        {
            return false;
        }

        //출력할 위치 인덱스 구하기
        int frontIndex = (front + 1) % bufferSize;
        outValue = data[frontIndex];

        //성공 반환
        return true;
    }

    //큐에 저장된 데이터 출력하는 함수
    void Print() const
    {
        std::cout << "큐 내용 : ";
        
        //첫번째 데이터가 저장된 인덱스
        int index = (front + 1) % bufferSize;

        //루프를 순회하면서 데이터 출력
        while (index != ((rear + 1) % bufferSize))
        {
            std::cout << " " << data[index];
            
            //다음 데이터 출력을 위해 인덱스 업데이트
            index = (index + 1) % bufferSize;
        }

        //개행(엔터) 출력
        std::cout << "\n";

    }

    //getter
    size_t Count() const { return capacity; }

    //큐가 비었는지 확인하는 함수
    bool IsEmpty() const { return front == rear; }

    //큐가 가득 찼는지 확인하는 함수
    bool IsFull() const { return ((rear + 1) % bufferSize) == front; }
private:

    //버퍼 크기 저장
    const int bufferSize = capacity + 1;

    //데이터 출력 위치를 관리하는 변수
    int front = 0;

    //데이터가 추가되는 위치를 관리하는 변수
    int rear = 0;



    //내부 데이터를 저장하는 정적 배열
    //원형 큐 구현할 때는 비어있는 상태와 가득찬 상태를 구분하기 위해
    //한칸을 비워둬야 해서 + 1해준다.
    //비어있는 상태 -> front와 rear가 같은 위치를 가리키는 경우
    //가득 찬 상태 ->rear + 1 = front인 상태
    T data[capacity + 1] = {};
};