##
### Find all files in a folder
file(GLOB_RECURSE GAME_PROTOTYPE_00
		CONFIGURE_DEPENDS
		"src/*.*"
		# "src/*.cpp"
		)

### Main proyect ###
add_executable(
	${PROJECT_NAME}
	
	${GAME_PROTOTYPE_00}
	# ${PROJECT_SOURCE_DIR}/0000/main_cmake/src/testing.cxx
	# ${PROJECT_SOURCE_DIR}/0000/main_cmake/src/testing_impl.cxx
	
	main.cpp
	)

# target_compile_definitions(file_name PRIVATE #DEFINE)
# target_compile_definitions(main.cpp PRIVATE FRENCH)

### Add LINKS
target_link_libraries(
						${PROJECT_NAME} PUBLIC
						## Options
						# project_options
						# project_warnings
						## Conan
						CONAN_PKG::docopt.cpp
						CONAN_PKG::fmt
						CONAN_PKG::spdlog
#						CONAN_PKG::glew # OpenGL
#						CONAN_PKG::glad # OpenGL
						CONAN_PKG::nlohmann_json
						# CONAN_PKG::imgui-sfml
						# CONAN_PKG::sdl2
						## MY LIBRARIES

						# Component
						#  Engine
					)

### Add LINKS
