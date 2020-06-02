set(IMPL_HEADERS
	headers/utils.hpp
	headers/octreeNode.hpp
        headers/octree.hpp
	headers/octreeColorQuantizer.hpp
	)

set(IMPL_SOURCES
        src/utils.cpp
        src/octreeNode.cpp
        src/octree.cpp
        src/octreeColorQuantizer.cpp
	)

include_directories(headers)

add_library(impl SHARED ${IMPL_HEADERS} ${IMPL_SOURCES})
target_link_libraries(impl ${OpenCV_LIBS})
install(TARGETS impl LIBRARY DESTINATION lib)
