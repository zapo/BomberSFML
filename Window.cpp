/* 
 * File:   Window.cpp
 * Author: zapo
 * 
 * Created on 12 janvier 2011, 09:27
 */

#include "Window.h"
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace std;

using namespace BMSfml;


Window::Window(int width, int height, int colors, string title) {

    this->width = width;
    this->height = height;
    this->colors = colors;
    this->title = title;

}

Window::Window(const Window& orig) {
}

Window::~Window() {
}

void Window::run() {

    this->sfWindow = new sf::RenderWindow(sf::VideoMode(this->width, this->height, this->colors), this->title);

    // Start game loop
    while (this->sfWindow->IsOpened())
    {
        // Process events
        sf::Event event;
        while (this->sfWindow->GetEvent(event))
        {
            // Close window : exit
            switch (event.Type) {
                case sf::Event::Closed:
                    this->sfWindow->Close();
                    break;
            }
        }

        // Clear the screen (fill it with black color)
        this->sfWindow->Clear();

        // Display window contents on screen
        this->sfWindow->Display();
    }

}

void Window::addEvent(sf::Event event, EventHandler handler) {

}



