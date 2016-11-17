cmake_minimum_required(VERSION 3.2)
project(libui VERSION 1.0.0)

set(COMMON_SOURCES
  common/areaevents.c
  common/control.c
  common/controlsigs.h
  common/debug.c
  common/matrix.c
  common/shouldquit.c
  common/table.c
  common/uipriv.h
  common/userbugs.c
  )

set(DARWIN_SOURCES
  darwin/alloc.m
  darwin/area.m
  darwin/areaevents.m
  darwin/autolayout.m
  darwin/box.m
  darwin/button.m
  darwin/checkbox.m
  darwin/colorbutton.m
  darwin/combobox.m
  darwin/control.m
  darwin/datetimepicker.m
  darwin/debug.m
  darwin/draw.m
  darwin/drawtext.m
  darwin/editablecombo.m
  darwin/entry.m
  darwin/fontbutton.m
  darwin/form.m
  darwin/grid.m
  darwin/group.m
  darwin/image.m
  darwin/label.m
  darwin/main.m
  darwin/map.m
  darwin/menu.m
  darwin/multilineentry.m
  darwin/progressbar.m
  darwin/radiobuttons.m
  darwin/scrollview.m
  darwin/separator.m
  darwin/slider.m
  darwin/spinbox.m
  darwin/stddialogs.m
  darwin/tab.m
  darwin/table.m
  darwin/text.m
  darwin/uipriv_darwin.h
  darwin/util.m
  darwin/window.m
  darwin/winmoveresize.m
  )

set(UNIX_SOURCES
  unix/alloc.c
  unix/area.c
  unix/box.c
  unix/button.c
  unix/checkbox.c
  unix/child.c
  unix/colorbutton.c
  unix/combobox.c
  unix/control.c
  unix/datetimepicker.c
  unix/debug.c
  unix/draw.c
  unix/draw.h
  unix/drawmatrix.c
  unix/drawpath.c
  unix/drawtext.c
  unix/editablecombo.c
  unix/entry.c
  unix/fontbutton.c
  unix/form.c
  unix/graphemes.c
  unix/grid.c
  unix/group.c
  unix/label.c
  unix/main.c
  unix/menu.c
  unix/multilineentry.c
  unix/progressbar.c
  unix/radiobuttons.c
  unix/separator.c
  unix/slider.c
  unix/spinbox.c
  unix/stddialogs.c
  unix/tab.c
  unix/text.c
  unix/uipriv_unix.h
  unix/util.c
  unix/window.c
  )

set(WINDOWS_SOURCES
  windows/alloc.cpp
  windows/area.cpp
  windows/areadraw.cpp
  windows/areaevents.cpp
  windows/areascroll.cpp
  windows/areautil.cpp
  windows/box.cpp
  windows/button.cpp
  windows/checkbox.cpp
  windows/colorbutton.cpp
  windows/colordialog.cpp
  windows/combobox.cpp
  windows/container.cpp
  windows/control.cpp
  windows/d2dscratch.cpp
  windows/datetimepicker.cpp
  windows/debug.cpp
  windows/draw.cpp
  windows/drawmatrix.cpp
  windows/drawpath.cpp
  windows/drawtext.cpp
  windows/dwrite.cpp
  windows/editablecombo.cpp
  windows/entry.cpp
  windows/events.cpp
  windows/fontbutton.cpp
  windows/fontdialog.cpp
  windows/form.cpp
  windows/graphemes.cpp
  windows/grid.cpp
  windows/group.cpp
  windows/init.cpp
  windows/label.cpp
  windows/main.cpp
  windows/menu.cpp
  windows/multilineentry.cpp
  windows/parent.cpp
  windows/progressbar.cpp
  windows/radiobuttons.cpp
  windows/separator.cpp
  windows/sizing.cpp
  windows/slider.cpp
  windows/spinbox.cpp
  windows/stddialogs.cpp
  windows/tab.cpp
  windows/tabpage.cpp
  windows/text.cpp
  windows/utf16.cpp
  windows/utilwin.cpp
  windows/window.cpp
  windows/winpublic.cpp
  windows/winutil.cpp
  )

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-Wall -Wextra -pedantic -Wno-unused-parameter -Wno-switch)
endif()

if(MSVC)
  add_compile_options(-W4 -wd4100 -bigobj -nologo -RTC1 -RTCc -RTCs -RTCu)
  set(CMAKE_SHARED_LINKER_FLAGS /MANIFEST:NO)
endif()

if(APPLE)
  set(UI_SOURCES ${DARWIN_SOURCES})
  set(CMAKE_INSTALL_RPATH "@executable_path/../lib")
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  set(LINUX TRUE)
  set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
  include(FindPkgConfig)
  pkg_search_module(GTK REQUIRED gtk+-3.0)
  set(UI_SOURCES ${UNIX_SOURCES})
endif()

if(WIN32)
  set(UI_SOURCES ${WINDOWS_SOURCES})
endif()

add_library(ui ${COMMON_SOURCES} ${UI_SOURCES})
set_target_properties(ui PROPERTIES
  VERSION ${PROJECT_VERSION_MINOR}
  SOVERSION ${PROJECT_VERSION_MAJOR})
target_compile_definitions(ui PRIVATE
  libui_EXPORTS)
target_compile_options(ui PRIVATE
  "$<$<PLATFORM_ID:Linux>:${GTK_CFLAGS}>")
target_link_libraries(ui PRIVATE
  "$<$<PLATFORM_ID:Linux>:${GTK_LDFLAGS}>"
  "$<$<PLATFORM_ID:Darwin>:-framework Foundation -framework AppKit>"
  "$<$<PLATFORM_ID:Windows>:user32;kernel32;gdi32;comctl32;uxtheme;msimg32;comdlg32;d2d1;dwrite;ole32;oleaut32;oleacc;uuid>")

add_executable(controlgallery examples/controlgallery/main.c)
target_link_libraries(controlgallery PRIVATE ui)

add_executable(histogram examples/histogram/main.c)
target_link_libraries(histogram PRIVATE ui)

add_executable(tests
  test/drawtests.c
  test/images.c
  test/main.c
  test/menus.c
  test/page1.c
  test/page10.c
  test/page11.c
  test/page12.c
  test/page13.c
  test/page14.c
  test/page15.c
  test/page16.c
  test/page2.c
  test/page3.c
  test/page4.c
  test/page5.c
  test/page6.c
  test/page7.c
  test/page7a.c
  test/page7b.c
  test/page7c.c
  test/page8.c
  test/page9.c
  test/spaced.c
  test/test.h
  )
target_link_libraries(tests PRIVATE ui)

install(TARGETS ui
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
install(FILES ui.h uitable.h DESTINATION include/ui)
