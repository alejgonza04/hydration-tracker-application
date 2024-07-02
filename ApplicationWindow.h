//
// Created by alejg on 5/12/2024.
//
#include <SFML/graphics.hpp>
#include <string>
#include <cmath>
using namespace std;
#ifndef WATERTRACKERPROJECT_APPLICATIONWINDOW_H
#define WATERTRACKERPROJECT_APPLICATIONWINDOW_H
class ApplicationWindow{
    sf::Texture waterTexture;
    sf::Sprite waterDroplet;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundImage;
public:
    string name;
    string weight;
    float weightNum;
    float ounces;
    int cups;
    bool isDropletPressed = false;

    void drawWindow(bool welcomeWindowClosed, string name, string weight){
        if (welcomeWindowClosed == true){
            sf::RenderWindow window(sf::VideoMode(800, 600), "Water Tracker");
            backgroundTexture.loadFromFile("files/images/background.jpg");
            backgroundImage.setTexture(backgroundTexture);
            while(window.isOpen()){
                sf::Event event;
                while(window.pollEvent(event)){
                    if (event.type == sf::Event::Closed){
                        window.close();
                    }

                    else if (event.type == sf::Event::MouseButtonPressed){
                        if (event.mouseButton.button == sf::Mouse::Left){
                            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                            if (waterDroplet.getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
                                isDropletPressed = true;
                            }
                        }
                    }
                }
                if (isDropletPressed == true){
                    //window.clear(sf::Color::White);
                    window.draw(backgroundImage);
                    window.display();
                }
                else{
                    //window.clear(sf::Color::White);
                    window.draw(backgroundImage);
                    displayMessage(window);
                    displayWaterButton(window);
                    window.display();
                }
            }
        }
    }

    void displayMessage(sf::RenderWindow& window){
        weightNum = stof(weight);
        ounces = weightNum / 2;
        cups = ounces / 8.0;

        sf::Font font;
        sf::Text welcomeText;
        sf::Text amountText;
        sf::Text amountText2;
        sf::Text closingText;
        sf::Text closingText2;
        font.loadFromFile("files/minimal.otf");

        welcomeText.setFont(font);
        amountText.setFont(font);
        amountText2.setFont(font);
        closingText.setFont(font);
        closingText2.setFont(font);

        welcomeText.setString("Welcome, " + name);
        welcomeText.setCharacterSize(50);
        welcomeText.setFillColor(sf::Color::Blue);
        welcomeText.setStyle(sf::Text::Bold);

        amountText.setString("Based on your weight, you should drink:");
        amountText.setCharacterSize(35);
        amountText.setFillColor(sf::Color::Black);
        amountText.setStyle(sf::Text::Bold);

        amountText2.setString(to_string(cups));
        amountText2.setCharacterSize(90);
        amountText2.setFillColor(sf::Color::Blue);
        amountText2.setStyle(sf::Text::Bold);

        closingText.setString("cups of water per day\n   to stay hydrated.");
        closingText.setCharacterSize(35);
        closingText.setFillColor(sf::Color::Black);
        closingText.setStyle(sf::Text::Bold);

        closingText2.setString("Click this droplet to get started with tracking");
        closingText2.setCharacterSize(35);
        closingText2.setFillColor(sf::Color::Black);
        closingText2.setStyle(sf::Text::Bold);

        float textX = (window.getSize().x - welcomeText.getLocalBounds().width) / 2;
        float textY = (window.getSize().y - welcomeText.getLocalBounds().height) / 4; // Adjust this factor to change vertical position
        welcomeText.setPosition(textX, textY - 120); // subtracting here shifts the pixels up

        float textX2 = (window.getSize().x - amountText.getLocalBounds().width) / 2;
        float textY2 = (window.getSize().y - amountText.getLocalBounds().height) / 4; // Adjust this factor to change vertical position
        amountText.setPosition(textX2, textY2 - 60);

        float textX3 = (window.getSize().x - amountText2.getLocalBounds().width) / 2;
        float textY3 = (window.getSize().y - amountText2.getLocalBounds().height) / 4; // Adjust this factor to change vertical position
        amountText2.setPosition(textX3, textY3 - 30);

        float textX4 = (window.getSize().x - closingText.getLocalBounds().width) / 2;
        float textY4 = (window.getSize().y - closingText.getLocalBounds().height) / 4; // Adjust this factor to change vertical position
        closingText.setPosition(textX4, textY4 + 60);

        float textX5 = (window.getSize().x - closingText2.getLocalBounds().width) / 2;
        float textY5 = (window.getSize().y - closingText2.getLocalBounds().height) / 4; // Adjust this factor to change vertical position
        closingText2.setPosition(textX5, textY5 + 170);

        window.draw(welcomeText);
        window.draw(amountText);
        window.draw(amountText2);
        window.draw(closingText);
        window.draw(closingText2);

    }

    void displayWaterButton(sf::RenderWindow& window){
        waterTexture.loadFromFile("files/images/water.png");
        waterDroplet.setTexture(waterTexture);
        waterDroplet.setScale(0.4, 0.4);

        float textX = (window.getSize().x - waterDroplet.getGlobalBounds().width) / 2;
        float textY = (window.getSize().y - waterDroplet.getGlobalBounds().height) / 4; // Using global bounds due to change in size
        waterDroplet.setPosition(textX, textY + 270);

        window.draw(waterDroplet);
    }

    void displayUI(sf::RenderWindow& window){

    }

};

#endif //WATERTRACKERPROJECT_APPLICATIONWINDOW_H
