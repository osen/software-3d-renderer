cmake_minimum_required(VERSION 2.6)
project(QSOFT)

if(MSVC)
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Ox")
else()
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -fopenmp")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -O3")
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

#add_definitions(-DSTD_SR1_DEBUG)

if(WIN32)
  include_directories(
    ${PROJECT_SOURCE_DIR}/contrib/SDL2/include
    ${PROJECT_SOURCE_DIR}/contrib/openal-soft/include
  )
else()
  include_directories(
    /usr/X11R6/include
    /usr/local/include
  )
endif()

if(WIN32)
  link_directories(
    ${PROJECT_SOURCE_DIR}/contrib/SDL2/lib
    ${PROJECT_SOURCE_DIR}/contrib/openal-soft/lib
  )
else()
  link_directories(
    /usr/X11R6/lib
    /usr/local/lib
  )
endif()

include_directories(
  src
  ${PROJECT_SOURCE_DIR}/contrib
)

if(MSVC)
  add_definitions(-DSDL_MAIN_HANDLED)
endif()

add_library(qsoft
  src/qsoft/Texture.cpp
  src/qsoft/Renderer.cpp
  src/qsoft/Mesh.cpp
  src/qsoft/Matrix.cpp
  src/qsoft/Vertex.cpp
  src/qsoft/Vector.cpp
  src/qsoft/Debug.cpp
  src/qsoft/Util.cpp
  src/qsoft/Shadow.cpp
)

add_executable(example
  src/example/main.cpp
)
target_link_libraries(example qsoft SDL2main SDL2)

add_library(qplatform
  src/qplatform/entry.cpp
  src/qplatform/tribox.cpp
  src/qplatform/Platform.cpp
  src/qplatform/World.cpp
  src/qplatform/Component.cpp
  src/qplatform/Entity.cpp
  src/qplatform/Resource.cpp
  src/qplatform/Resources.cpp
  src/qplatform/Model.cpp
  src/qplatform/Window.cpp
  src/qplatform/Part.cpp
  src/qplatform/MaterialGroup.cpp
  src/qplatform/ModelRenderer.cpp
  src/qplatform/Texture.cpp
  src/qplatform/Environment.cpp
  src/qplatform/StaticModelCollider.cpp
  src/qplatform/Transform.cpp
  src/qplatform/Camera.cpp
  src/qplatform/Keyboard.cpp
  src/qplatform/SpriteRenderer.cpp
  src/qplatform/Gui.cpp
  src/qplatform/Audio.cpp
  src/qplatform/Sound.cpp
  src/qplatform/BoxCollider.cpp
  src/qplatform/Font.cpp
)

if(MSVC)
  target_link_libraries(qplatform qsoft openal32)
else()
  target_link_libraries(qplatform qsoft openal)
endif()

add_library(blood
  src/blood/main.cpp
  src/blood/GameScreen.cpp
  src/blood/BongoScreen.cpp
  src/blood/Player.cpp
  src/blood/SkyBox.cpp
  src/blood/Zombie.cpp
  src/blood/HitBox.cpp
  src/blood/Fade.cpp
  src/blood/BongoCat.cpp
  src/blood/Pickup.cpp
)

add_executable(sdl2_platform
  src/sdl2_platform/main.cpp
)
target_link_libraries(sdl2_platform SDL2 qplatform blood qplatform blood)

add_executable(sdl_platform
  src/sdl_platform/main.cpp
)
target_link_libraries(sdl_platform SDL qplatform blood qplatform blood)

add_executable(x11_platform
  src/x11_platform/main.cpp
)

target_link_libraries(x11_platform X11 qplatform blood qplatform blood)

