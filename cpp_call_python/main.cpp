#include <pybind11/embed.h>
#include <iostream>

namespace py = pybind11;

int main() {
    py::scoped_interpreter guard{}; // 自动初始化和关闭解释器

    py::module_ mymodule = py::module_::import("main");
    py::object result = mymodule.attr("multiply")(6, 7);

    int value = result.cast<int>();
    std::cout << "Result from Python: " << value << std::endl;

    return 0;
}