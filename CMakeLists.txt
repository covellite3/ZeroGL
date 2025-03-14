###################################################################
#           CMakeLists.txt writted by Corentin Asso.              #
#                     Date february 3 2023.                       #
###################################################################
cmake_minimum_required(VERSION 3.22.1)
include(CMakePrintHelpers)


###
# * Make sure to have a build folder at the root of the project :
#
# * How to run cmake, examples :
# - $ cmake -S . -B build/
# - $ cmake -DRELEASE=ON -S . -B build/
# - $ cmake -DSDL2_DIR="/usr/lib/.../.../SDL2/" -S . -B build/
#
# * How to compile project
# - cmake --build build/
#
# * List of options:
# - RELEASE=ON/OFF	<- Enable release version, debug version otherwise.
###


######################
### PROJECT'S NAME ###
######################
project("ZeroGL")


#########################
### PROJECT'S FOLDERS ###
#########################
set(BIN_DIR "bin")	# Directory for binaries (executable).
set(DOC_DIR "doc")	# Directory for documentation (doxygene).
set(LIB_DIR "lib")	# Directory for libraries.
set(OBJ_DIR "obj")	# Directory for compiled sources (object files or '.o' files).
set(SRC_DIR "src")	# Directory for C++ sources files. (.cpp)
set(INCL_DIR "incl")	# Directory for C++ headers files. (.hpp, .tcc)
set(TOOLS_DIR "tools")	# Directory for developers tool in the forme of scriptes.


##################
### COMPILATOR ###
##################
# TODO Choose compilator.


###########################
### COMPILATION OPTIONS ###
###########################
#add_compile_options(-ggdb -Wall -Wextra -pedantic -Werror)
#add_compile_options(-ggdb -Wall -Wextra -pedantic -Werror -Wconversion -Wuninitialized)
add_compile_options(-ggdb -Wall -Wextra -pedantic -Werror -Wconversion -Wshadow -Wuninitialized)
#add_compile_options(-ggdb -Wall -Wextra -pedantic -Werror -Wconversion -Wshadow -Wuninitialized -Wno-unused-parameter)


##############
### OpenMP ###
##############
find_package(OpenMP)
if (OPENMP_FOUND)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
	message(STATUS "### OPENMP SUPPORTED ###")
else()
	message(STATUS "### OPENMP NOT SUPPORTED ###")
endif()


#################
### LIBRARIES ###
#################
# Libraries names
set(LIST_LIB_NAMES
	OpenGL
	glut
	GLEW
	GLESv1 GLESv1_CM GLESv1_CM_nvidia GLESv2 GLESv2_nvidia
	pthread
	#SDL SDL2
	sfml-network sfml-window sfml-graphics sfml-system
	#glfw
)

# Hints to where libs are
set(HINTS
	${HINTS}
	/usr/include/
	/usr/local/lib/cmake/
	/usr/lib/x86_64-linux-gnu/ 
	#!!!#   HERE ADD YOUR SEARCH FOLDERS FOR LIBS   #!!!#
) 
cmake_print_variables(HINTS)

# Search for librairies
foreach(LIB_NAME ${LIST_LIB_NAMES})
	message(STATUS "[  IMPORT ${LIB_NAME}  ]")
	cmake_print_variables(${LIB_NAME}_DIR)
	find_library(${LIB_NAME}_LIB ${LIB_NAME} HINTS ${HINTS} PATHS ${LIB_NAME}_DIR)
	cmake_print_variables(${LIB_NAME}_LIB)
	if(${LIB_NAME}_LIB)
		message(STATUS " ###  FOUND  ### ")
		set(LIBRARIES ${LIBRARIES} ${${LIB_NAME}_LIB})
		set(LIST_LIB_FOUND ${LIST_LIB_FOUND} ${LIB_NAME})
	else()
		message(STATUS " ### MISSING ###")
		set(LIST_LIB_MISSING ${LIST_LIB_MISSING} ${LIB_NAME})
	endif()
	message(STATUS "[ /IMPORT ${LIB_NAME}  ]")
	message(STATUS "")
endforeach()

# Print found and missing libraries
message(STATUS "[  SUMMARY  ]")
message(STATUS "LIBS FOUND: ${LIST_LIB_FOUND}")
message(STATUS "LIBS MISSING: ${LIST_LIB_MISSING}")
message(STATUS "[ /SUMMARY  ]")
message(STATUS "")


###############
### OPTIONS ###
###############
message(STATUS "[  OPTIONS  ]")

### BUILD MODE : Release OR Debug ###
if(RELEASE)
	set(CMAKE_BUILD_TYPE Release)
else()
	set(CMAKE_BUILD_TYPE Debug)
endif()
cmake_print_variables(RELEASE CMAKE_BUILD_TYPE)
message(STATUS "[ /OPTIONS  ]")
message(STATUS "")


################
### BINARIES ###
################
# List of binaries names
set(LIST_BIN_NAMES
	#unittest
	#example
	#example_cube
	debug
)
# Subdirectories starting from SRC_DIR containing
# the sources files with 'main.cpp' for each
# executables (binaries).
set(unittest_MAIN_PATH test)
set(example_MAIN_PATH example1)
set(example_cube_MAIN_PATH example2)
set(debug_MAIN_PATH example3)
foreach(BIN_NAME ${LIST_BIN_NAMES})
	##############
	### BINARY ###
	##############
	set(BIN_NAME ${BIN_NAME})
	set(MAIN_PATH ${PROJECT_SOURCE_DIR}/${SRC_DIR}/${${BIN_NAME}_MAIN_PATH}/main.cpp)
	message(STATUS "[  BINARY: ${BIN_NAME}  ]")
	message(STATUS "+ MAIN:\n-- +-- ${MAIN_PATH}")


	################################
	### FETCH SOURCES IN SRC_DIR ###
	################################
	# Get all files in SRC_DIR and his subfolders
	# with the extension '.cpp'.
	file(GLOB_RECURSE SRCS ${PROJECT_SOURCE_DIR}/${SRC_DIR}/*.cpp)
	# Exclude other executable's main.cpp
	list(FILTER SRCS EXCLUDE REGEX "/main.cpp$")
	# Since we excluded all 'main.cpp',
	# we must put back the one for this binary.
	list(APPEND SRCS ${MAIN_PATH})
	message(STATUS "+ SOURCES:")
	# Just some string formating to make the
	# list of sources file more readable.
	string(REPLACE ";"  "\n-- +-- " BUFF_FORMAT_STRING "${SRCS}")
	message(STATUS "+-- ${BUFF_FORMAT_STRING}")


	#################################
	### FETCH HEADERS IN INCL_DIR ###
	#################################
	include_directories(${PROJECT_SOURCE_DIR}/${INCL_DIR})


	##########################
	### COMPILATION BINARY ###
	##########################
	add_executable(${BIN_NAME} ${SRCS})
	target_link_libraries(${BIN_NAME} ${LIBRARIES})
	set_target_properties(${BIN_NAME} PROPERTIES CXX_STANDARD 20)
	set_target_properties(${BIN_NAME}
	    PROPERTIES
	    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/${LIB_DIR}"
	    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/${LIB_DIR}"
	    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/${BIN_DIR}"	
	)
	message(STATUS "[ /BINARY: ${BIN_NAME}  ]")
	message(STATUS "")
endforeach()
