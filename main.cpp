#include <iostream>
#include <SFML/graphics.hpp>
#include <SFML/config.hpp>
using namespace std;
#include "WelcomeWindow.h"
#include "ApplicationWindow.h"

int main() {
    WelcomeWindow welcomeWindow;
    welcomeWindow.drawWindow();

    /*ApplicationWindow applicationWindow;
    applicationWindow.name = welcomeWindow.name;
    applicationWindow.weight = welcomeWindow.weight;
    applicationWindow.drawWindow(welcomeWindow.welcomeWindowClosed, welcomeWindow.name, welcomeWindow.weight);*/

}
