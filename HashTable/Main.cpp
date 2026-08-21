#include <iostream>
#include "HashTable.h"



int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    HashTable table;

    table.Add("hong", "010-2314-2312");
    table.Add("kim", "010-2315-2312");
    table.Add("inzik", "010-9231-3202");
    
    if (!table.Add("hong", "010-2231-3132"))
    {
        std::cout << "이미 같은 키가 저장돼 있음\n";
    }

    std::cout << "\n전체 데이터\n";
    table.Print();

    //검색
    std::string number;
    if (table.Find("kim", number))
    {
        std::cout << "\n검색 결과 : kim, " << number << "\n";
    }

    //삭제
    if (table.Delete("inzik"))
    {
        std::cout << "항목 삭제\n";
    }
}