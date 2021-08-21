# Install script for directory: C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/marce/UFRGS/close-to-gl/out/install/x64-Debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/marce/UFRGS/close-to-gl/out/build/x64-Debug/lib/SDL2d.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/marce/UFRGS/close-to-gl/out/build/x64-Debug/lib/SDL2maind.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets.cmake"
         "C:/Users/marce/UFRGS/close-to-gl/out/build/x64-Debug/lib/imgui-cmake/libs/SDL/CMakeFiles/Export/cmake/SDL2Targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "C:/Users/marce/UFRGS/close-to-gl/out/build/x64-Debug/lib/imgui-cmake/libs/SDL/CMakeFiles/Export/cmake/SDL2Targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "C:/Users/marce/UFRGS/close-to-gl/out/build/x64-Debug/lib/imgui-cmake/libs/SDL/CMakeFiles/Export/cmake/SDL2Targets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/SDL2Config.cmake"
    "C:/Users/marce/UFRGS/close-to-gl/out/build/x64-Debug/SDL2ConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL2" TYPE FILE FILES
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_assert.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_atomic.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_audio.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_bits.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_blendmode.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_clipboard.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_config_android.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_config_iphoneos.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_config_macosx.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_config_minimal.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_config_os2.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_config_pandora.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_config_psp.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_config_windows.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_config_winrt.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_config_wiz.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_copying.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_cpuinfo.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_egl.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_endian.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_error.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_events.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_filesystem.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_gamecontroller.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_gesture.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_haptic.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_hints.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_joystick.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_keyboard.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_keycode.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_loadso.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_locale.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_log.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_main.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_messagebox.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_metal.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_misc.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_mouse.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_mutex.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_name.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_opengl.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_opengl_glext.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_opengles.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_opengles2.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_opengles2_gl2.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_opengles2_gl2ext.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_opengles2_gl2platform.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_opengles2_khrplatform.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_pixels.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_platform.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_power.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_quit.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_rect.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_render.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_revision.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_rwops.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_scancode.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_sensor.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_shape.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_stdinc.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_surface.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_system.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_syswm.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_test.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_test_assert.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_test_common.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_test_compare.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_test_crc32.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_test_font.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_test_fuzzer.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_test_harness.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_test_images.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_test_log.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_test_md5.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_test_memory.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_test_random.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_thread.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_timer.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_touch.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_types.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_version.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_video.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/SDL_vulkan.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/begin_code.h"
    "C:/Users/marce/UFRGS/close-to-gl/lib/imgui-cmake/libs/SDL/include/close_code.h"
    "C:/Users/marce/UFRGS/close-to-gl/out/build/x64-Debug/lib/imgui-cmake/libs/SDL/include/SDL_config.h"
    )
endif()

