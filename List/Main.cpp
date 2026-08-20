#include "List.h"
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> vec;

    // 캐릭터 리스트
    List<std::string> characterList;
    characterList.PushBack("warrior");
    characterList.PushBack("knight");
    characterList.PushBack("archer");

    //복사 생성
    List<std::string> copiedList(characterList);
    copiedList[0] = "BlackKnight";

    //이동 생성
    List<std::string> copiedList2(std::move(copiedList));

    //범위 기반 루프
    for (const auto& value : characterList)
    {
        std::cout << value << "\n";
    }

    //이터레이터 기반 루프 순회
    for (auto iterator = characterList.begin(); iterator != characterList.end(); ++iterator)
    {
        std::cout << (*iterator) << "\n";
    }
}