#include "Data.hpp"
#include "Serializer.hpp"

int main() {

    Data original;
    original.id = 101;
    original.name = "Test_01";

    // Serialize
    std::size_t raw = Serializer::serialize(&original);

    // Deserialize
    Data* recovered = Serializer::deserialize(raw);

    std::cout << "Original pointer:  " << &original << std::endl;
    std::cout << "Recovered pointer: " << recovered << std::endl;

    std::cout << "ID:   " << recovered->id << std::endl;
    std::cout << "Name: " << recovered->name << std::endl;

    if (recovered == &original) {
        std::cout << "Success: Pointers match." << std::endl;
    } else {
        std::cout << "Error: Pointers do not match." << std::endl;
    }

    return 0;
}
