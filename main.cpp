#include <iostream>
#include "Main.h"

int main(int argc, char *argv[]) {
    auto myMain = new server_side::boot::Main();
    myMain->main(argc,argv);
    return 0;
}
