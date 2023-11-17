//
// Created by lukee on 11/17/2023.
//

#include "ui.h"
#include <iostream>
bool ui::GetUserNeeds(){

    std::cout << "Hello, What game sensitivity reference would you like to use?" << std::endl;
    std::cout << "1. Minecraft" << std::endl; // mc sens is 22 times csgo's and apex's
    std::cout << "2. Csgo/cs2" << std::endl;
    std::cout << "3. Apex Legends" << std::endl;
    std::cout << ">> ";

    std::cin >> CurrentGame;

    std::cout << "What would you like to transfer your sensitivity to?" << std::endl;
    std::cout << "1. Minecraft" << std::endl;
    std::cout << "2. Csgo/cs2" << std::endl;
    std::cout << "3. Apex Legends" << std::endl;
    std::cout << ">> ";

    std::cin >> NewGame;

    if (NewGame == CurrentGame || CurrentGame > 3 || CurrentGame < 1
        || NewGame > 3     || NewGame     < 1){

        std::cout << "Input is incorrect" << std::endl;
        return false;
    }
    return true;
}