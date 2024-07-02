//
// Created by alejg on 5/11/2024.
//
#include <SFML/graphics.hpp>
#include <map>
#include <vector>
#include <sstream>
#include <map>
#include <fstream>
using namespace std;

#ifndef WATERTRACKERPROJECT_WELCOMEWINDOW_H
#define WATERTRACKERPROJECT_WELCOMEWINDOW_H
class WelcomeWindow{
    sf::Texture backgroundTexture;
    sf::Sprite backgroundImage;
    sf::Texture waterTexture;
    sf::Sprite waterDroplet;
    sf::Sprite waterDroplet1;
    sf::Sprite waterDroplet2;
    sf::Sprite waterDroplet3;
    sf::Sprite waterDropletRestart;
    sf::Sprite waterDropletRestart2;
    sf::Sprite waterDropletLeaderboard;
public:
    string name;
    string weight;
    bool numEnter = false;
    bool numEnter2 = false;
    bool welcomeWindowClosed = false;
    float weightNum;
    float ounces;
    int cups;
    bool isDropletPressed = false;
    int percentage;
    int cupsAdded = 0;
    int cupsLeft;
    bool isGoalReached = false;
    bool mainMenu = false;
    bool leaderboardRequested = false;
    map<int, string> leaderboard;
    void drawWindow(){
        sf::RenderWindow window(sf::VideoMode(800, 600), "Water Tracker");
        backgroundTexture.loadFromFile("files/images/background.jpg");
        backgroundImage.setTexture(backgroundTexture);
        while (window.isOpen()){
            sf::Event event;
            while(window.pollEvent(event)){

                if (event.type == sf::Event::Closed){
                    window.close();
                    writeToLeaderboard(name, percentage);
                }

                else if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode < 128 && isalpha(event.text.unicode)) {
                        if (name.size() < 12 && numEnter == false) {
                            char pressedChar = static_cast<char>(event.text.unicode);
                            if (name.size() < 1) {
                                pressedChar = toupper(pressedChar);
                                name += pressedChar;
                            } else {
                                pressedChar = tolower(pressedChar);
                                name += pressedChar;
                            }
                        }
                    }
                    else if (weight.size() < 3 && numEnter2 == true) {
                        char pressedChar = static_cast<char>(event.text.unicode);
                        if (isdigit(pressedChar)){
                            weight += pressedChar;
                        }
                    }
                }

                else if (event.type == sf::Event::MouseButtonPressed){
                    if (event.mouseButton.button == sf::Mouse::Left){
                        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                        if (waterDroplet.getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
                            isDropletPressed = true;
                        }
                        if (waterDroplet3.getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
                            if (cupsLeft == 1 || cupsLeft > 1){
                                cupsAdded++;
                            }
                        }
                        else if (waterDroplet1.getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
                            if (cupsLeft == 2 || cupsLeft > 2){
                                cupsAdded += 2;
                            }
                        }
                        else if (waterDroplet2.getGlobalBounds().contains(mousePosition.x, mousePosition.y)){
                            if (cupsLeft == 3 || cupsLeft > 3){
                                cupsAdded += 3;
                            }
                        }
                        else if (waterDropletRestart.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            welcomeWindowClosed = false;
                            name.clear();
                            weight.clear();
                            numEnter = false;
                            isDropletPressed = false;
                            isGoalReached = false;
                            cupsAdded = 0;
                        }
                        else if (waterDropletLeaderboard.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            leaderboardRequested = true;
                            writeToLeaderboard(name, percentage);
                        }
                        else if (waterDropletRestart2.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            welcomeWindowClosed = false;
                            name.clear();
                            weight.clear();
                            numEnter = false;
                            isDropletPressed = false;
                            isGoalReached = false;
                            cupsAdded = 0;
                            leaderboardRequested = !leaderboardRequested;
                        }
                    }
                }

                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
                    if (name.size() != 0 && numEnter == false){
                        name.pop_back();
                    }
                    if (weight.size() != 0 && numEnter2 == true){
                        weight.pop_back();
                    }
                }

                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    if (name.size() != 0){
                        numEnter = true;
                        numEnter2 = numEnter;
                    }
                    if (weight.size() != 0){
                        numEnter2 = false;
                        if (numEnter2 == false){
                            welcomeWindowClosed = true;
                        }
                    }
                }
            }
            if (leaderboardRequested){
                window.draw(backgroundImage);
                displayEndWaterButtons(window);
                displayLeaderboard(window);
                window.display();
            }
            if (welcomeWindowClosed == true && !leaderboardRequested){
                if (isDropletPressed){
                    if (cupsAdded == 0){
                        percentage = 0;
                    }
                    else{
                        percentage = ((cupsAdded) / static_cast<float>(cups)) * 100;
                    }
                    cupsLeft = cups - cupsAdded;
                    if (cupsLeft == 0){
                        isGoalReached = true;
                    }
                    window.draw(backgroundImage);
                    if (!isGoalReached){
                        displayWaterButton(window);
                        displayMessage3(window);
                        window.display();
                    }
                    else if (isGoalReached){
                        displayMessage3(window);
                        displayEndWaterButtons(window);
                        displayMessage4(window);
                        window.display();
                    }
                }
                else{
                    window.draw(backgroundImage);
                    displayWaterButton(window);
                    displayMessage2(window);
                    window.display();
                    cout << cups << endl;
                }
            }
            else if (!leaderboardRequested){
                window.draw(backgroundImage);
                displayMessage(window);
                displayName(window);
                displayWeight(window);
                window.display();
            }
            //window.clear(sf::Color::White);

        }
    }

    void displayMessage(sf::RenderWindow& window){
        sf::Font font;
        sf::Text welcomeText;
        sf::Text enterNameText;
        sf::Text enterWeightText;
        font.loadFromFile("files/minimal.otf");

        welcomeText.setFont(font);
        enterNameText.setFont(font);
        enterWeightText.setFont(font);

        welcomeText.setString("Water Tracker");
        welcomeText.setCharacterSize(70);
        welcomeText.setFillColor(sf::Color::Blue);
        welcomeText.setStyle(sf::Text::Bold);

        enterNameText.setString("Enter Your Name:");
        enterNameText.setCharacterSize(35);
        enterNameText.setFillColor(sf::Color::Blue);
        enterNameText.setStyle(sf::Text::Bold);

        enterWeightText.setString("Enter Your Weight In Lbs:");
        enterWeightText.setCharacterSize(35);
        enterWeightText.setFillColor(sf::Color::Blue);
        enterWeightText.setStyle(sf::Text::Bold);

        // sets position of the text relative to window width and height
        float textX = (window.getSize().x - welcomeText.getLocalBounds().width) / 2;
        float textY = (window.getSize().y - welcomeText.getLocalBounds().height) / 4; // Adjust this factor to change vertical position
        welcomeText.setPosition(textX, textY - 80); // subtracting here shifts the pixels up

        float textX2 = (window.getSize().x - enterNameText.getLocalBounds().width) / 2;
        float textY2 = (window.getSize().y - enterNameText.getLocalBounds().height) / 4; // Adjust this factor to change vertical position
        enterNameText.setPosition(textX2, textY2 + 30);

        float textX3 = (window.getSize().x - enterWeightText.getLocalBounds().width) / 2;
        float textY3 = (window.getSize().y - enterWeightText.getLocalBounds().height) / 4; // Adjust this factor to change vertical position
        enterWeightText.setPosition(textX3, textY3 + 120);

        window.draw(welcomeText);
        window.draw(enterNameText);
        window.draw(enterWeightText);

    }

    void displayName(sf::RenderWindow& window){
        sf::Font font;
        sf::Text nameText;
        sf::Text weightText;
        font.loadFromFile("files/minimal.otf");
        if (numEnter == true){
            string displayedText = name;
            nameText.setFont(font);
            nameText.setString(displayedText);
            nameText.setCharacterSize(35);
            nameText.setFillColor(sf::Color::Black);
            nameText.setStyle(sf::Text::Bold);

            float textX = (window.getSize().x - nameText.getLocalBounds().width) / 2;
            float textY = (window.getSize().y - nameText.getLocalBounds().height) / 4;
            nameText.setPosition(textX, textY + 60);

            window.draw(nameText);
        }
        else{
            string displayedText = name + "|"; //adds a cursor to the typing
            nameText.setFont(font);
            nameText.setString(displayedText);
            nameText.setCharacterSize(35);
            nameText.setFillColor(sf::Color::Black);
            nameText.setStyle(sf::Text::Bold);

            float textX = (window.getSize().x - nameText.getLocalBounds().width) / 2;
            float textY = (window.getSize().y - nameText.getLocalBounds().height) / 4;
            nameText.setPosition(textX, textY + 60);

            window.draw(nameText);
        }

    }

    void displayWeight(sf::RenderWindow& window){
        sf::Font font;
        sf::Text weightText;
        font.loadFromFile("files/minimal.otf");
        if (numEnter2 == true){
            string displayedText2 = weight + "|";

            weightText.setFont(font);
            weightText.setString(displayedText2);
            weightText.setCharacterSize(35);
            weightText.setFillColor(sf::Color::Black);
            weightText.setStyle(sf::Text::Bold);

            float textX = (window.getSize().x - weightText.getLocalBounds().width) / 2;
            float textY = (window.getSize().y - weightText.getLocalBounds().height) / 4;
            weightText.setPosition(textX, textY + 150);

            window.draw(weightText);
        }
        else{
            string displayedText2 = weight;

            weightText.setFont(font);
            weightText.setString(displayedText2);
            weightText.setCharacterSize(35);
            weightText.setFillColor(sf::Color::Black);
            weightText.setStyle(sf::Text::Bold);

            float textX = (window.getSize().x - weightText.getLocalBounds().width) / 2;
            float textY = (window.getSize().y - weightText.getLocalBounds().height) / 4;
            weightText.setPosition(textX, textY + 150);

            window.draw(weightText);
        }

    }

    void displayMessage2(sf::RenderWindow& window){
        weightNum = stof(weight);
        ounces = weightNum / 2;
        cups = ounces / 8.0;

        sf::Font font;
        sf::Text welcomeText;
        sf::Text amountText;
        sf::Text amountText2;
        sf::Text closingText;
        sf::Text closingText2;
        sf::Text letsGoText;
        font.loadFromFile("files/minimal.otf");

        welcomeText.setFont(font);
        amountText.setFont(font);
        amountText2.setFont(font);
        closingText.setFont(font);
        closingText2.setFont(font);
        letsGoText.setFont(font);

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

        closingText2.setString("Click this droplet to get started with tracking!");
        closingText2.setCharacterSize(35);
        closingText2.setFillColor(sf::Color::Black);
        closingText2.setStyle(sf::Text::Bold);

        letsGoText.setString("Lets\nGo!");
        letsGoText.setCharacterSize(40);
        letsGoText.setFillColor(sf::Color::Black);
        letsGoText.setStyle(sf::Text::Bold);

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

        float textX6 = (window.getSize().x - letsGoText.getLocalBounds().width) / 2;
        float textY6 = (window.getSize().y - letsGoText.getLocalBounds().height) / 4; // Adjust this factor to change vertical position
        letsGoText.setPosition(textX6, textY6 + 285);

        window.draw(welcomeText);
        window.draw(amountText);
        window.draw(amountText2);
        window.draw(closingText);
        window.draw(closingText2);
        window.draw(letsGoText);

    }

    void displayMessage3(sf::RenderWindow& window){
        sf::Font font;
        sf::Font font2;
        sf::Text text;
        sf::Text cups;
        sf::Text percent;
        sf::Text add1;
        sf::Text add2;
        sf::Text add3;
        sf::Text ofDailyGoal;
        font.loadFromFile("files/minimal.otf");
        font2.loadFromFile("files/YukitaSans-Regular.otf");

        text.setFont(font);
        percent.setFont(font2);
        cups.setFont(font);
        add1.setFont(font);
        add2.setFont(font);
        add3.setFont(font);
        ofDailyGoal.setFont(font);

        text.setString("You have   cups left");
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::Black);
        text.setStyle(sf::Text::Bold);

        percent.setString(to_string(percentage) + "%");
        percent.setCharacterSize(70);
        percent.setFillColor(sf::Color::Blue);
        percent.setStyle(sf::Text::Bold);

        cups.setString(to_string(cupsLeft));
        cups.setCharacterSize(50);
        cups.setFillColor(sf::Color::Blue);
        cups.setStyle(sf::Text::Bold);

        add1.setString("Add 1\n cup");
        add1.setCharacterSize(25);
        add1.setFillColor(sf::Color::Black);
        add1.setStyle(sf::Text::Bold);

        add2.setString("Add 2\n cups");
        add2.setCharacterSize(25);
        add2.setFillColor(sf::Color::Black);
        add2.setStyle(sf::Text::Bold);

        add3.setString("Add 3\n cups");
        add3.setCharacterSize(25);
        add3.setFillColor(sf::Color::Black);
        add3.setStyle(sf::Text::Bold);

        ofDailyGoal.setString("of daily goal");
        ofDailyGoal.setCharacterSize(35);
        ofDailyGoal.setFillColor(sf::Color::Black);
        ofDailyGoal.setStyle(sf::Text::Bold);

        float textX = (window.getSize().x - text.getLocalBounds().width) / 2;
        float textY = (window.getSize().y - text.getLocalBounds().height) / 4;
        text.setPosition(textX, textY - 120);

        float textX2 = (window.getSize().x - percent.getLocalBounds().width) / 2;
        float textY2 = (window.getSize().y - percent.getLocalBounds().height) / 4;
        percent.setPosition(textX2, textY2 + 50);

        float textX3 = (window.getSize().x - cups.getLocalBounds().width) / 2;
        float textY3 = (window.getSize().y - cups.getLocalBounds().height) / 4;
        cups.setPosition(textX3 + 12, textY3 - 120);

        float textX4 = (window.getSize().x - add1.getLocalBounds().width) / 2;
        float textY4 = (window.getSize().y - add1.getLocalBounds().height) / 4;
        add1.setPosition(textX4 - 255, textY4 + 290);

        float textX5 = (window.getSize().x - add2.getLocalBounds().width) / 2;
        float textY5 = (window.getSize().y - add2.getLocalBounds().height) / 4;
        add2.setPosition(textX5, textY5 + 290);

        float textX6 = (window.getSize().x - add3.getLocalBounds().width) / 2;
        float textY6 = (window.getSize().y - add3.getLocalBounds().height) / 4;
        add3.setPosition(textX6 + 250, textY6 + 290);

        float textX7 = (window.getSize().x - ofDailyGoal.getLocalBounds().width) / 2;
        float textY7 = (window.getSize().y - ofDailyGoal.getLocalBounds().height) / 4;
        ofDailyGoal.setPosition(textX7, textY7 + 120);

        window.draw(text);
        window.draw(percent);
        window.draw(cups);
        if (!isGoalReached){
            window.draw(add1);
            window.draw(add2);
            window.draw(add3);
        }
        window.draw(ofDailyGoal);

    }

    void displayMessage4(sf::RenderWindow& window){
        sf::Font font;
        sf::Text congrats;
        sf::Text congratsMessage;
        sf::Text backToMenu;
        sf::Text leaderboard;
        font.loadFromFile("files/minimal.otf");

        congrats.setFont(font);
        congratsMessage.setFont(font);
        backToMenu.setFont(font);
        leaderboard.setFont(font);

        congrats.setString("CONGRATULATIONS");
        congrats.setCharacterSize(80);
        congrats.setFillColor(sf::Color::Blue);
        congrats.setStyle(sf::Text::Bold);

        congratsMessage.setString("You have reached your daily goal!");
        congratsMessage.setCharacterSize(35);
        congratsMessage.setFillColor(sf::Color::Black);
        congratsMessage.setStyle(sf::Text::Bold);

        backToMenu.setString("Main\nMenu");
        backToMenu.setCharacterSize(25);
        backToMenu.setFillColor(sf::Color::Black);
        backToMenu.setStyle(sf::Text::Bold);

        leaderboard.setString("Leader\nboard");
        leaderboard.setCharacterSize(25);
        leaderboard.setFillColor(sf::Color::Black);
        leaderboard.setStyle(sf::Text::Bold);

        float textX = (window.getSize().x - congrats.getLocalBounds().width) / 2;
        float textY = (window.getSize().y - congrats.getLocalBounds().height) / 4;
        congrats.setPosition(textX, textY + 160);

        float textX2 = (window.getSize().x - congratsMessage.getLocalBounds().width) / 2;
        float textY2 = (window.getSize().y - congratsMessage.getLocalBounds().height) / 4;
        congratsMessage.setPosition(textX2, textY2 + 240);

        float textX3 = (window.getSize().x - backToMenu.getLocalBounds().width) / 2;
        float textY3 = (window.getSize().y - backToMenu.getLocalBounds().height) / 4;
        backToMenu.setPosition(textX3 - 100, textY3 + 340);

        float textX4 = (window.getSize().x - leaderboard.getLocalBounds().width) / 2;
        float textY4 = (window.getSize().y - leaderboard.getLocalBounds().height) / 4;
        leaderboard.setPosition(textX4 + 102, textY4 + 340);

        window.draw(congrats);
        window.draw(congratsMessage);
        window.draw(backToMenu);
        window.draw(leaderboard);

    }

    void displayWaterButton(sf::RenderWindow& window){
        waterTexture.loadFromFile("files/images/water.png");
        waterDroplet.setTexture(waterTexture);
        waterDroplet1.setTexture(waterTexture);
        waterDroplet2.setTexture(waterTexture);
        waterDroplet3.setTexture(waterTexture);

        if (!isDropletPressed){
            waterDroplet.setScale(0.4, 0.4);
            float textX = (window.getSize().x - waterDroplet.getGlobalBounds().width) / 2;
            float textY = (window.getSize().y - waterDroplet.getGlobalBounds().height) / 4; // Using global bounds due to change in size
            waterDroplet.setPosition(textX, textY + 270);

            window.draw(waterDroplet);
        }
        else{
            waterDroplet3.setScale(0.35, 0.35);
            float textX3 = (window.getSize().x - waterDroplet3.getGlobalBounds().width) / 2;
            float textY3 = (window.getSize().y - waterDroplet3.getGlobalBounds().height) / 4; // Using global bounds due to change in size
            waterDroplet3.setPosition(textX3 - 250, textY3 + 270);

            waterDroplet1.setScale(0.35, 0.35);
            float textX = (window.getSize().x - waterDroplet1.getGlobalBounds().width) / 2;
            float textY = (window.getSize().y - waterDroplet1.getGlobalBounds().height) / 4; // Using global bounds due to change in size
            waterDroplet1.setPosition(textX, textY + 270);

            waterDroplet2.setScale(0.35, 0.35);
            float textX2 = (window.getSize().x - waterDroplet2.getGlobalBounds().width) / 2;
            float textY2 = (window.getSize().y - waterDroplet2.getGlobalBounds().height) / 4; // Using global bounds due to change in size
            waterDroplet2.setPosition(textX2 + 250, textY2 + 270);

            window.draw(waterDroplet1);
            window.draw(waterDroplet2);
            window.draw(waterDroplet3);
        }
    }

    void displayEndWaterButtons(sf::RenderWindow& window){
        if (leaderboardRequested){
            waterDropletRestart2.setTexture(waterTexture);
            waterDropletRestart2.setScale(0.35, 0.35);
            float textX = (window.getSize().x - waterDropletRestart2.getGlobalBounds().width) / 2;
            float textY = (window.getSize().y - waterDropletRestart2.getGlobalBounds().height) / 4; // Using global bounds due to change in size
            waterDropletRestart2.setPosition(textX, textY + 320);

            window.draw(waterDropletRestart2);

            sf::Text backToMenu;
            sf::Font font;
            font.loadFromFile("files/minimal.otf");
            backToMenu.setFont(font);
            backToMenu.setString("Main\nMenu");
            backToMenu.setCharacterSize(25);
            backToMenu.setFillColor(sf::Color::Black);
            backToMenu.setStyle(sf::Text::Bold);

            float textX3 = (window.getSize().x - backToMenu.getLocalBounds().width) / 2;
            float textY3 = (window.getSize().y - backToMenu.getLocalBounds().height) / 4;
            backToMenu.setPosition(textX3, textY3 + 340);

            window.draw(backToMenu);
        }
        else{
            waterDropletRestart.setTexture(waterTexture);
            waterDropletLeaderboard.setTexture(waterTexture);

            waterDropletRestart.setScale(0.35, 0.35);
            float textX = (window.getSize().x - waterDropletRestart.getGlobalBounds().width) / 2;
            float textY = (window.getSize().y - waterDropletRestart.getGlobalBounds().height) / 4; // Using global bounds due to change in size
            waterDropletRestart.setPosition(textX - 100, textY + 320);

            waterDropletLeaderboard.setScale(0.35, 0.35);
            float textX2 = (window.getSize().x - waterDropletLeaderboard.getGlobalBounds().width) / 2;
            float textY2 = (window.getSize().y - waterDropletLeaderboard.getGlobalBounds().height) / 4; // Using global bounds due to change in size
            waterDropletLeaderboard.setPosition(textX2 + 100, textY2 + 320);

            window.draw(waterDropletRestart);
            window.draw(waterDropletLeaderboard);

        }
    }

    void writeToLeaderboard(const string& name, const int& sPercentage){
        ofstream file("files/leaderboard.txt", ios::app);
        if (!file.is_open()){
            cerr << "Error: Unable to load file " << endl;
        }
        file << '\n';
        file << sPercentage << ", " << name;
    }

    void displayLeaderboard(sf::RenderWindow& window) {
        fstream file("files/leaderboard.txt");
        if (!file.is_open()) {
            cerr << "Error: Unable to load file " << endl;
        }

        string line, lPercentage, lName;
        while(getline(file, line)){
            stringstream s(line);
            getline(s, lPercentage, ',');
            getline(s, lName);

            int newPercentage = stoi(lPercentage);

            leaderboard[newPercentage] = lName;
        }
        file.close();

        sf::Font font;
        sf::Text leaderboardText;
        sf::Text leaderboardNames;
        font.loadFromFile("files/minimal.otf");

        leaderboardText.setFont(font);
        leaderboardNames.setFont(font);

        leaderboardText.setString("Leaderboard");

        string leaderBoard;
        int rank = 1;
        map<int, string>::reverse_iterator it; //reverse iterator
        for (it = leaderboard.rbegin(); it != leaderboard.rend(); it++){
            if (rank < 6){
                leaderBoard += to_string(rank++) + ". " + '\t' + to_string(it->first) + '\t' + it->second + '\n' + '\n';
            }
        }

        leaderboardNames.setString(leaderBoard);

        leaderboardText.setCharacterSize(50);
        leaderboardNames.setCharacterSize(35);

        leaderboardText.setFillColor(sf::Color::Blue);
        leaderboardNames.setFillColor(sf::Color::Black);

        leaderboardText.setStyle(sf::Text::Bold | sf::Text::Underlined);
        leaderboardNames.setStyle(sf::Text::Bold);

        float textX = (window.getSize().x - leaderboardText.getGlobalBounds().width) / 2;
        float textY = (window.getSize().y - leaderboardText.getGlobalBounds().height) / 4; // Using global bounds due to change in size
        leaderboardText.setPosition(textX, textY - 120);

        float textX2 = (window.getSize().x - leaderboardNames.getGlobalBounds().width) / 2;
        float textY2 = (window.getSize().y - leaderboardNames.getGlobalBounds().height) / 4; // Using global bounds due to change in size
        leaderboardNames.setPosition(textX2, textY2 + 30);

        window.draw(leaderboardText);
        window.draw(leaderboardNames);
    }

};
#endif //WATERTRACKERPROJECT_WELCOMEWINDOW_H
