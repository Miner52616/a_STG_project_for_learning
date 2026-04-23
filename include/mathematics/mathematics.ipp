#include <random>

template <typename T>
T get_random_from(std::vector<T> vector)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis_int(0,vector.size()-1);
    return vector[dis_int(gen)];
}