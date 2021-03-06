find_path(ZLIB_INCLUDE_DIR zlib.h)
find_library(ZLIB_LIBRARY NAMES libz.a z)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ZLIB DEFAULT_MSG ZLIB_INCLUDE_DIR ZLIB_LIBRARY)

add_library(p::zlib INTERFACE IMPORTED)
set_property(TARGET p::zlib PROPERTY INTERFACE_INCLUDE_DIRECTORIES
    ${ZLIB_INCLUDE_DIR})
set_property(TARGET p::zlib PROPERTY INTERFACE_LINK_LIBRARIES
    ${ZLIB_LIBRARY})

message("ZLIB_INCLUDE_DIR: ${ZLIB_INCLUDE_DIR}")
message("ZLIB_LIBRARY: ${ZLIB_LIBRARY}")
