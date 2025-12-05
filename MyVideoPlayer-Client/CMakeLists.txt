# cmake_minimum_required(VERSION 3.19)
# project(MyVideoPlayer-Client LANGUAGES CXX)

# find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
# find_package(Qt6 REQUIRED COMPONENTS Widgets)
# find_package(Qt6 REQUIRED COMPONENTS Widgets)
# find_package(Qt6 REQUIRED COMPONENTS Widgets)
# find_package(Qt6 REQUIRED COMPONENTS Widgets)
# find_package(Qt6 REQUIRED COMPONENTS Widgets)
# find_package(Qt6 REQUIRED COMPONENTS Widgets)
# find_package(Qt6 REQUIRED COMPONENTS Widgets)
# find_package(Qt6 REQUIRED COMPONENTS Core)

# INCLUDE_DIRECTORIES(
# 	${PROJECT_SOURCE_DIR}
# )

# qt_standard_project_setup()

# qt_add_executable(MyVideoPlayer-Client
#     WIN32 MACOSX_BUNDLE
#     main.cpp
#     videoplayer.cpp
#     videoplayer.h
#     videoplayer.ui
#     startuppage.h startuppage.cpp
#     images.qrc
#     pageswitchbutton.h pageswitchbutton.cpp
#     util.h
#     homepagewidget.h homepagewidget.cpp homepagewidget.ui
#     searchlineedit.h searchlineedit.cpp
#     videobox.h videobox.cpp videobox.ui
#     playpage.h playpage.cpp playpage.ui
#     playslider.h playslider.cpp playslider.ui
#     volume.h volume.cpp volume.ui
#     playspeed.h playspeed.cpp playspeed.ui
#     barrageedit.h barrageedit.cpp
#     myselfwidget.h myselfwidget.cpp myselfwidget.ui
#     myselfwidget.h myselfwidget.cpp myselfwidget.ui
#     avatarbutton.h avatarbutton.cpp
#     modifymyselfdialog.h modifymyselfdialog.cpp modifymyselfdialog.ui
#     newpassworddialog.h newpassworddialog.cpp newpassworddialog.ui
#     uploadvideopage.h uploadvideopage.cpp uploadvideopage.ui
#     adminwidget.h adminwidget.cpp adminwidget.ui
#     checktable.h checktable.cpp checktable.ui
#     roletable.h roletable.cpp roletable.ui
#     checktableitem.h checktableitem.cpp checktableitem.ui
#     roletableitem.h roletableitem.cpp roletableitem.ui
#     editadmindialog.h editadmindialog.cpp editadmindialog.ui
#     pagebutton.h pagebutton.cpp
#     paginator.h paginator.cpp
#     login.h login.cpp login.ui
#     toast.h toast.cpp
#     mpv/mpv/client.h mpv/mpv/render.h mpv/mpv/render_gl.h mpv/mpv/stream_cb.h
#     mpv/mpv/mpvplayer.h mpv/mpv/mpvplayer.cpp
# )

# # 添加 qrc 资源
# qt_add_resources(IMAGE_RESOURCES images.qrc)
# target_sources(MyVideoPlayer-Client PRIVATE ${IMAGE_RESOURCES})

# target_link_libraries(MyVideoPlayer-Client
#     PRIVATE
#         Qt::Core
#         Qt::Widgets
# )
# target_link_libraries(MyVideoPlayer-Client PRIVATE Qt6::Widgets)
# target_link_libraries(MyVideoPlayer-Client PRIVATE Qt6::Widgets)
# target_link_libraries(MyVideoPlayer-Client PRIVATE Qt6::Widgets)
# target_link_libraries(MyVideoPlayer-Client PRIVATE Qt6::Widgets)
# target_link_libraries(MyVideoPlayer-Client PRIVATE Qt6::Widgets)
# target_link_libraries(MyVideoPlayer-Client PRIVATE Qt6::Widgets)
# target_link_libraries(MyVideoPlayer-Client PRIVATE Qt6::Core)

# include(GNUInstallDirs)

# install(TARGETS MyVideoPlayer-Client
#     BUNDLE  DESTINATION .
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
# )

# qt_generate_deploy_app_script(
#     TARGET MyVideoPlayer-Client
#     OUTPUT_SCRIPT deploy_script
#     NO_UNSUPPORTED_PLATFORM_ERROR
# )
# install(SCRIPT ${deploy_script})

# # set(MPV_DLL ${PROJECT_SOURCE_DIR}/mpv/dll/libmpv-2.dll)
# set(MPV_DLL_DIR ${PROJECT_SOURCE_DIR}/mpv/dll)

# # 如果 .dll.a 文件在 dll 目录中
# set(MPV_IMPORT_LIB ${MPV_DLL_DIR}/libmpv.dll.a)

# # 链接 mpv 导入库
# target_link_libraries(MyVideoPlayer-Client
#     PRIVATE
#     Qt6::Widgets
#     Qt6::Gui
#     Qt6::Core
#     ${MPV_IMPORT_LIB}  # 添加这一行！
# )

# # add_custom_command(TARGET MyVideoPlayer-Client POST_BUILD
# #     COMMAND ${CMAKE_COMMAND} -E copy_if_different
# #         ${MPV_DLL}
# #         $<TARGET_FILE_DIR:MyVideoPlayer-Client>
# #     COMMENT "Copying mpv DLL to output directory"
# # )
cmake_minimum_required(VERSION 3.19)
project(MyVideoPlayer-Client LANGUAGES CXX)

# 查找 Qt6 包 - 只需要一次
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Gui)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)

include_directories(
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
    avatarbutton.h avatarbutton.cpp
    modifymyselfdialog.h modifymyselfdialog.cpp modifymyselfdialog.ui
    newpassworddialog.h newpassworddialog.cpp newpassworddialog.ui
    uploadvideopage.h uploadvideopage.cpp uploadvideopage.ui
    adminwidget.h adminwidget.cpp adminwidget.ui
    checktable.h checktable.cpp checktable.ui
    roletable.h roletable.cpp roletable.ui
    checktableitem.h checktableitem.cpp checktableitem.ui
    roletableitem.h roletableitem.cpp roletableitem.ui
    editadmindialog.h editadmindialog.cpp editadmindialog.ui
    pagebutton.h pagebutton.cpp
    paginator.h paginator.cpp
    login.h login.cpp login.ui
    toast.h toast.cpp
    mpv/mpv/client.h mpv/mpv/render.h mpv/mpv/render_gl.h mpv/mpv/stream_cb.h
    mpv/mpv/mpvplayer.h mpv/mpv/mpvplayer.cpp
    bulletscreenitem.h bulletscreenitem.cpp
    model/datacenter.h model/datacenter.cpp
    model/data.h
    model/data.cpp
)

# 添加 qrc 资源
qt_add_resources(IMAGE_RESOURCES images.qrc)
target_sources(MyVideoPlayer-Client PRIVATE ${IMAGE_RESOURCES})

# 设置 mpv 库路径
set(MPV_DLL_DIR ${PROJECT_SOURCE_DIR}/mpv/dll)
set(MPV_IMPORT_LIB ${MPV_DLL_DIR}/libmpv.dll.a)

# 链接所有库 - 只需要一次调用
target_link_libraries(MyVideoPlayer-Client
    PRIVATE
    Qt6::Widgets
    Qt6::Gui
    Qt6::Core
    ${MPV_IMPORT_LIB}
)
target_link_libraries(MyVideoPlayer-Client PRIVATE Qt6::Widgets)
target_link_libraries(MyVideoPlayer-Client PRIVATE Qt6::Core)

# 可选：启用后复制 DLL 文件
# set(MPV_DLL ${PROJECT_SOURCE_DIR}/mpv/dll/libmpv-2.dll)
# add_custom_command(TARGET MyVideoPlayer-Client POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         "${MPV_DLL}"
#         "$<TARGET_FILE_DIR:MyVideoPlayer-Client>"
#     COMMENT "Copying mpv DLL to output directory"
# )

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
