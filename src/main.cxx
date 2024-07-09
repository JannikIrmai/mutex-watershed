#include <load.hxx>
#include <mutex-watershed.hxx>
#include <time.hxx>


int main(int argc, char* argv[])
{
    if (argc != 2)
        throw std::runtime_error("There can only be one argument (filepath)!");

    std::string instance_path(argv[1]);

    Clock clock;
    auto data = load_instance<size_t, double>(instance_path);
    std::cout << "Loaded instance with " << data.first.size() << " edges in " 
        << std::setprecision(5) << std::fixed << clock.elapsed() << " seconds\n";
    clock.reset();

    double objective = mutex_watershed(data.first, data.second);

    std::cout << std::setprecision(5) << "Objective value computed by mutex-watershed: " << objective
        << " (" << clock.elapsed() << " seconds)\n";

    return 0;
}
