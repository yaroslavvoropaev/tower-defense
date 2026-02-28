#include <iostream>

#include "Loader.h"
#include "View.h"

int main() {

    std::unique_ptr<TowerDefense::ILoader> loader = std::make_unique<TowerDefense::Loader>();
    auto &presenter = loader->get_presenter();
    TowerDefense::View view(presenter);
    try {
        view.run();
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
