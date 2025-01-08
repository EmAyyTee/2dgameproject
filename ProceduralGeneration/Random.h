#include <unordered_set>
#include <vector>
#include <random>
#include <stdexcept>
#include <iterator>

template <typename T>
class Random {
public:
    static T getRandomElement(const std::unordered_set<T>& set) {
        if (set.empty()) {
            throw std::runtime_error("Cannot get a random element from an empty set");
        }

        std::vector<T> elements(set.begin(), set.end());

        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, elements.size() - 1);

        return elements[dist(gen)];
    }
};