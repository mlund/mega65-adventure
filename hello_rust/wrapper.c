// simple c wrapper that imports
// and run the main rust code
#include <stdint.h>

extern void rusty_main();

int main() {
    rusty_main();
    return 0;
}

