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
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(main PRIVATE sfml-graphics sfml-window sfml-system)

# ---- TGUI ----
# IMPORTANT: il faut installer la version qui correspond à ton code (TGUI 1.x)
find_package(TGUI 1 REQUIRED)

# Le nom de la target dépend de l'installation. La plus courante avec TGUI 1.x:
#   TGUI::TGUI
# Si ta configuration CMake ne fournit pas cette target, je te donne la variante juste après.
target_link_libraries(main PRIVATE TGUI::TGUI)

# ---- Assets ----
add_custom_command(TARGET main POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/texture
          $<TARGET_FILE_DIR:main>/texture
)
