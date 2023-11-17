//
// Created by lukee on 11/17/2023.
//

#include "ui.h"
#include <iostream>

bool ui::GetUserNeeds(){

    std::cout << "Hello, What game sensitivity reference would you like to use?\n";
    std::cout << "1. Minecraft\n"; // mc sens is 22 times csgo's and apex's
    std::cout << "2. Csgo/cs2\n";
    std::cout << "3. Apex Legends\n";
    std::cout << "\n\n>> ";

    std::cin >> CurrentGame;

#ifdef _WIN32
    system("cls");
#elif __APPLE__
    system("clear");
#endif


    std::cout << "What would you like to transfer your sensitivity to?\n";
    std::cout << "1. Minecraft\n";
    std::cout << "2. Csgo/cs2\n";
    std::cout << "3. Apex Legends\n";
    std::cout << "\n\n>> ";

    std::cin >> NewGame;

    if (NewGame == CurrentGame || CurrentGame > 3 || CurrentGame < 1
        || NewGame > 3     || NewGame     < 1){

        std::cout << "Input is incorrect" << std::endl;
        return false;
    }
    return true;
}