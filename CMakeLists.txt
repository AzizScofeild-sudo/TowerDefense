cmake_minimum_required(VERSION 3.16)
project(projet_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-Wall -Wextra -pedantic)
endif()

# Sources
file(GLOB SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")
if(NOT SOURCES)
  message(FATAL_ERROR "Aucun fichier .cpp trouvé dans src/. Créez src/main.cpp au minimum.")
endif()

add_executable(main ${SOURCES})
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include)

# ---- SFML ----
# Installe d'abord la lib: sudo apt install libsfml-dev
# Ajoute/retire les composants dont tu as besoin (graphics, window, system, audio, network)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Lien avec les modules SFML nécessaires
target_link_libraries(main PRIVATE sfml-graphics sfml-window sfml-system)