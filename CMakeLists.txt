cmake_minimum_required (VERSION 3.8)

set (MODULE_NAME "entity")
set (MODULE_VERSION "1.0.0")

project (${MODULE_NAME} CXX)

include (GNUInstallDirs)

if ("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")

	message (FATAL_ERROR "In-tree builds are neither supported nor recommended.  See README.md for building information.")

endif ()

add_library (${MODULE_NAME} SHARED)

target_sources (${MODULE_NAME}
PRIVATE
	"private/entity.cpp"
	"private/entity-index.cpp"
)

target_include_directories (${MODULE_NAME}
PUBLIC
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>"
	"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
PRIVATE
	"$<BUILD_INTERFACE:${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}>"
)

set_target_properties (${MODULE_NAME}
PROPERTIES
	CXX_STANDARD 17
	CXX_EXTENSIONS OFF
	PREFIX ""
	SUFFIX ".mod"
	PUBLIC_HEADER "public/entity.h"
)

install (
	TARGETS ${MODULE_NAME}
	EXPORT ${MODULE_NAME}-targets

	INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
	LIBRARY  DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	ARCHIVE  DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	RUNTIME  DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

install (
	EXPORT ${MODULE_NAME}-targets
	NAMESPACE gengine::

	FILE ${MODULE_NAME}-config.cmake
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${MODULE_NAME}"
)
