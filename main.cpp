#include "Engine.h"
#include "MainMenuWindow.h"
#include "MainWindow.h"

int main(){
    MainWindow main_window;
    MainMenuWindow main_menu_window;
    Engine engine;
    engine.run(main_window, main_menu_window);


    return 0;
}
