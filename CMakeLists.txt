cmake_minimum_required(VERSION 3.30)
project(a10_alexiordachioaiei_1)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH "/home/axolotl/Qt/6.9.0/gcc_64")



set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Charts
        REQUIRED)



include_directories(.)
include_directories(domain)
include_directories(GUI)
include_directories(repo)
include_directories(service)
include_directories(UI)




add_executable(a10_alexiordachioaiei

        domain/Movie.cpp
        domain/Movie.h
        GUI/adminGUI.cpp
        GUI/adminGUI.h
        GUI/mainGUI.cpp
        GUI/mainGUI.h
        GUI/userGUI.cpp
        GUI/userGUI.h
        repo/CSVRepo.cpp
        repo/CSVRepo.h
        repo/DefaultRepo.cpp
        repo/DefaultRepo.h
        repo/HTMLRepo.cpp
        repo/HTMLRepo.h
        repo/IRepo.cpp
        repo/IRepo.h
        repo/SQLRepo.cpp
        repo/SQLRepo.h
        service/Service.cpp
        service/Service.h
        service/Command.cpp
        service/Command.h
        UI/UI.cpp
        UI/UI.h
        letterboxd.cpp
        tests.cpp
        tests.h
        Validator.cpp
        Validator.h
        service/ICommand.cpp
        service/ICommand.h
        GUI/GraphGUI.cpp
        GUI/GraphGUI.h
        GUI/MovieTableModel.cpp
        GUI/MovieTableModel.h
        GUI/MovieTableView.cpp
        GUI/MovieTableView.h)

target_link_libraries(a10_alexiordachioaiei Qt6::Widgets Qt6::Charts)

