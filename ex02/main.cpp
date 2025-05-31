# include <cstdlib>
# include <iostream>
# include <ctime>
# include "Base.hpp"
# include "A.hpp"
# include "B.hpp"
# include "C.hpp"

// Randomly instantiate A, B, or C and return as Base*
Base* generate(void) {
    std::srand(std::time(0));
    int r = std::rand() % 3;
    switch (r) {
        case 0:
            std::cout << "Generated: A" << std::endl;
            return new A();
        case 1:
            std::cout << "Generated: B" << std::endl;
            return new B();
        case 2:
            std::cout << "Generated: C" << std::endl;
            return new C();
        default:
            std::cerr << "Failed to generate!" << std::endl;
            return 0;
    }
}

// Identify the actual type from a Base* pointer
void identify(Base* p) {
    if (dynamic_cast<A*>(p))
        std::cout << "Pointer identifies: A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "Pointer identifies: B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "Pointer identifies: C" << std::endl;
    else
        std::cout << "Pointer identifies: Unknown" << std::endl;
}

// Identify the actual type from a Base& reference 
void identify(Base& p) {
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "Reference identifies: A" << std::endl;
        return;
    } catch (const std::exception& e) { }

    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "Reference identifies: B" << std::endl;
        return;
    } catch (const std::exception& e) {}
        
    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "Reference identifies: C" << std::endl;
        return;
    } catch (const std::exception& e) {}
  
    std::cout << "Reference identifies: Unknown" << std::endl;
}

int main() {
    Base* obj = generate();

    identify(obj);    // via pointer
    identify(*obj);   // via reference

    delete obj;
    return 0;
}

