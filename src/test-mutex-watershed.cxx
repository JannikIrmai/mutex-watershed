#include <mutex-watershed.hxx>
#include <stdexcept>


template<typename T>
void assert_equal(const T& a, const T& b)
{
    if (a != b)
        throw std::logic_error(std::to_string(a) + " != " + std::to_string(b));
}



int main()
{
    std::vector<std::array<size_t, 2>> edges;
    std::vector<int> costs;

    // 1
    edges = {{0, 1}, {1, 2}, {0, 2}};
    costs = {2, -1, 3};
    assert_equal(mutex_watershed(edges, costs), 0);

    // 2
    edges = {{0, 1}, {1, 2}, {0, 2}};
    costs = {2, -3, 1};
    assert_equal(mutex_watershed(edges, costs), -2);

    return 0;
}