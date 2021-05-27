#include "linkedlist.hpp"

int main() {
    linkedList<int> L;
    L.insert(1);
    L.dump(std::cerr);

    L.insert(2);
    L.dump(std::cerr);
    
    L.insert(3);
    L.dump(std::cerr);
    
    L.insert(4);
    L.dump(std::cerr);
    
    L.insert(1, 5);
    L.dump(std::cerr);
    
    L.insert(5, 6);
    L.dump(std::cerr);

    std::cout << L.eject() << '\n';
    L.dump(std::cerr);
}
