macro(AddCBLib LIB_NAME)
    add_library(${LIB_NAME} ${ARGN})
    target_link_libraries(${LIB_NAME} ${COINBILL_TARGET_LIBRARIES})
endmacro()