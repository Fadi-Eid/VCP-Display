#include "display.hpp"

int main() {

    PixelDisplay display(256, 256);
    while(display.running) {
        display.refresh();
    }
    
    return 0;
}
