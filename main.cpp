#include <iostream>
#include "Engine.h"
#include "MainWindow.h"

int main(){
    MainWindow main_window;
    Engine engine( main_window);
    engine.run();


    return 0;
}
