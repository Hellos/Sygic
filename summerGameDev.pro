TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    Collisison.cpp \
    ECS/ECS.cpp \
    game.cpp \
    main.cpp \
    map.cpp \
    texturemanager.cpp \
    Vector2D.cpp


LIBS += -L C:\SDL\x86_64-w64-mingw32\lib \
-lmingw32 \
-lSDL2main \
-lSDL2 \
-lSDL2_image

INCLUDEPATH += C:\SDL\x86_64-w64-mingw32\include\SDL2


HEADERS += \
    Collisison.h \
    ECS/Animation.h \
    ECS/ColliderComponent.h \
    ECS/Components.h \
    ECS/ECS.h \
    ECS/KeyboardController.h \
    ECS/MouseController.h \
    ECS/SpriteComponent.h \
    ECS/TileComponent.h \
    ECS/TransformComponent.h \
    game.h \
    map.h \
    texturemanager.h \
    Vector2D.h
