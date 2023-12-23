#include <iostream>
#include <map>
#include <chrono>
#include "allocator.hpp"
#include "list.hpp"

// Функция вычисления факториала
int factorial(int i){
    if (i <= 1){
        return 1;
    }
    return i * factorial(i - 1);
}

// Без аллокатора
void test_1(){
    auto begin = std::chrono::high_resolution_clock::now();

    std::map<int, int> map;
    for (size_t i = 0; i < 100000; i++){
        map.emplace(i, i);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "test_1 (без аллокатора): " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "\n";
}

// С аллокатором
void test_2(){
    auto begin = std::chrono::high_resolution_clock::now();

    std::map<int, int, std::less<int>,Allocator<std::pair<const int,int>, 100000>> map;
    for (size_t i = 0; i < 100000; i++){
        map.emplace(i, i);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "test_2 (с аллокатором): " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "\n";
}

// Функция печати информации о списке
void print(const List<int, Allocator<int, 10>>& myList){
    List<int, Allocator<int, 10>> list = myList;
    std::cout << "Первый элемент списка: " << *(list.begin()) << "\n";
    std::cout << "Количество элементов в списке: " << list.get_size() << "\n";
    std::cout << "Элементы списка: ";
    for (List<int, Allocator<int, 10>>::Iterator it = list.begin(); it != list.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << "\n" << "\n";
}



int main(){

// Тесты
    test_1();
    test_2();
    std::cout << "\n";

// std::map
    std::cout << "std::map" << "\n";
    std::map<int, int> map;
    for (size_t i = 0; i < 10; i++){
        int res = factorial(i);
        map.emplace(i, res);
    }
    for(const auto& [a,b]: map){
        std::cout << a << " " << b << "\n";
    }
    std::cout << "\n";

// Двунаправленный список
    std::cout << "Двунаправленный список:" << "\n" << "\n";
    List<int, Allocator<int, 10>> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    print(list);

    list.push_front(0);
    print(list);

    list.pop_back();
    list.pop_front();
    print(list);

    list.insert(1, 9);
    print(list);

    list.erase(2);
    print(list);

    return 0;
}