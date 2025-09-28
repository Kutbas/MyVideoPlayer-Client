cmake_minimum_required(VERSION 3.19)
project(MyVideoPlayer-Client LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}
)

qt_standard_project_setup()

qt_add_executable(MyVideoPlayer-Client
    WIN32 MACOSX_BUNDLE
    main.cpp
    videoplayer.cpp
    videoplayer.h
    videoplayer.ui
    startuppage.h startuppage.cpp
    images.qrc
    pageswitchbutton.h pageswitchbutton.cpp
    util.h
    homepagewidget.h homepagewidget.cpp homepagewidget.ui
    searchlineedit.h searchlineedit.cpp
    videobox.h videobox.cpp videobox.ui
    playpage.h playpage.cpp playpage.ui
    playslider.h playslider.cpp playslider.ui
    volume.h volume.cpp volume.ui
    playspeed.h playspeed.cpp playspeed.ui
    barrageedit.h barrageedit.cpp
    myselfwidget.h myselfwidget.cpp myselfwidget.ui
    myselfwidget.h myselfwidget.cpp myselfwidget.ui
)

# 添加 qrc 资源
qt_add_resources(IMAGE_RESOURCES images.qrc)
target_sources(MyVideoPlayer-Client PRIVATE ${IMAGE_RESOURCES})

target_link_libraries(MyVideoPlayer-Client
    PRIVATE
        Qt::Core
        Qt::Widgets
)
target_link_libraries(MyVideoPlayer-Client PRIVATE Qt6::Widgets)
target_link_libraries(MyVideoPlayer-Client PRIVATE Qt6::Widgets)
target_link_libraries(MyVideoPlayer-Client PRIVATE Qt6::Widgets)
target_link_libraries(MyVideoPlayer-Client PRIVATE Qt6::Widgets)

include(GNUInstallDirs)

install(TARGETS MyVideoPlayer-Client
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET MyVideoPlayer-Client
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
