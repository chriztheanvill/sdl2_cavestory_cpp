macro(run_conan)
    # Download automatically, you can also just copy the conan.cmake file
    if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        message(STATUS "+++ CONAN Installing!!!")
        message(
                STATUS
                "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
        file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake")
    else ()
        message(STATUS "+++ CONAN ALREADY INSTALLED!!!")
        # message(STATUS "Conan Path: ${CMAKE_BINARY_DIR}\n")

    endif ()

    include(${CMAKE_BINARY_DIR}/conan.cmake)

    conan_add_remote(NAME bincrafters URL
	https://bincrafters.jfrog.io/artifactory/api/conan/public-conan)

    conan_cmake_run(
            REQUIRES
            ${CONAN_EXTRA_REQUIRES}
            # // ------------------------------ //
            #
            ### Conan Packages ###
            #
            catch2/2.13.7 ### Stable	
            # catch2/3.0.0@catchorg/stable ### Testing
            #		
            docopt.cpp/0.6.3
            fmt/8.0.1    ### Format Console text
            spdlog/1.9.2
            glad/0.1.34    ### openGL
            glew/2.2.0    ### openGL
            nlohmann_json/3.10.0  ### JSON
            sol2/3.2.3    ### Lua Sol2
            #
            ### Enable glad and glfw if you have problems.
            #
            # glad/0.1.33
            # glfw/3.3.2@bincrafters/stable
            #
            # // ------------------------------ //
            #
            # sdl2/2.0.10@bincrafters/stable
            # glew/2.1.0@bincrafters/stable
            # mesa-glu/9.0.1@bincrafters/stable
            #
            # // ------------------------------ //
            #
            OPTIONS
            ${CONAN_EXTRA_OPTIONS}
            BASIC_SETUP
            CMAKE_TARGETS # individual targets to link to
            BUILD
            missing
    )
endmacro()
