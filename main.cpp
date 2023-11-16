//
// Created by Tuke on 11/15/2023.
//

#include <iostream>

int main(){

    int CurrentGame;
    int NewGame;
    float CurrentGame_sens;
    float NewGame_sens;
    float Target_sens;
    std::cout << "Hello, What game sensitivity reference would you like to use?" << std::endl;
    std::cout << "1. Minecraft" << std::endl; // mc sens is 22 times csgo's and apex's
    std::cout << "2. Csgo" << std::endl;
    std::cout << "3. Apex Legends" << std::endl;
    std::cout << ">> ";

    std::cin >> CurrentGame;

    std::cout << "What would you like to transfer your sensitivity to?" << std::endl;
    std::cout << "1. Minecraft" << std::endl;
    std::cout << "2. Csgo" << std::endl;
    std::cout << "3. Apex Legends" << std::endl;
    std::cout << ">> ";

    std::cin >> NewGame;

    if (NewGame == CurrentGame || CurrentGame > 3 || CurrentGame < 1
                               || NewGame > 3     || NewGame     < 1){

        std::cout << "Input is incorrect" << std::endl;
        return 1;
    }

    // treat input

    switch (CurrentGame) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            std::cout << "Error";
    }

    return 0;
}