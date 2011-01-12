/* 
 * File:   main.cpp
 * Author: zapo
 *
 * Created on 11 janvier 2011, 12:45
 */


#include <cstdlib>
#include "Window.h"

using namespace std;
using namespace BMSfml;

/*
 * 
 */
int main(int argc, char** argv) {

    // Create the main rendering window
    Window window(800, 600, 32, "Test Window");

    // Run the main window loop
    window.run();

    return EXIT_SUCCESS;
}
