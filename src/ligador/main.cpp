#include "ligador.h"

int main(int argc, char *argv[]) {
    if(argc > 1) {
        link(argv + 1, argc - 1);
    }
    return 0;
}