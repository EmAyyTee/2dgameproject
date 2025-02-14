cmake_minimum_required(VERSION 3.29)
project(theBidingOfOri)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG        10.1.0
)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_MakeAvailable(fmt SFML)


add_executable(main main.cpp
        MainWindow.cpp
        Engine.cpp
        engine.h
        MainWindow.h
        Character.h
        Character.cpp
        Player.h
        Player.cpp
        Animator.h
        Animator.cpp
        TextureLoader.h
        TextureLoader.cpp
        GreenSlime.h
        GreenSlime.cpp
        Button.h
        Button.cpp
        GameObject.h
        GameObject.cpp
        PlayerArrow.h
        PlayerArrow.cpp
        BetterClock.h
        BetterClock.cpp
        ProceduralGeneration/Direction2D.cpp
        ProceduralGeneration/Direction2D.h
        ProceduralGeneration/Floor.cpp
        ProceduralGeneration/ProceduralGenerationAlgorithms.cpp
        ProceduralGeneration/Random.h
        ProceduralGeneration/RandomWalkDungeonGenerator.cpp
        ProceduralGeneration/TileMap.cpp
        ProceduralGeneration/TileMapVisualiser.cpp
        CollisionHandler.h
        CollisionHandler.cpp
        PlayerHud.cpp
        PlayerHud.h
        BigGreenSlime.h
        BigGreenSlime.cpp
        SmallGreenSlime.h
        SmallGreenSlime.cpp
        TextButton.h
        TextButton.cpp
        PlayerUpgrades/PiercingUpgrade.h
        PlayerUpgrades/PiercingUpgrade.cpp
        PlayerUpgrades/DamageUpgrade.h
        PlayerUpgrades/DamageUpgrade.cpp
        PlayerUpgrades/SpeedUpgrade.h
        PlayerUpgrades/SpeedUpgrade.cpp
        PlayerUpgrades/HealthUpgrade.cpp
        PlayerUpgrades/DashUpgrade.h
        PlayerUpgrades/DashUpgrade.cpp
        NewGameButton.h
        NewGameButton.cpp
        Buttons/PlayButton.h
        Buttons/PlayButton.cpp
        Buttons/QuitButtonNew.h
        Buttons/QuitButtonNew.cpp
        Buttons/ContinueTheGameButton.h
        Buttons/ContinueTheGameButton.cpp
)
target_link_libraries(main
        fmt::fmt
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
        sfml-network
)
