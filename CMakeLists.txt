cmake_minimum_required(VERSION 3.8)

# Coinbill project, we are using C/C++.
project(CoinBill C CXX)

# We are using OpenSSL for cryption, Boost for socket.
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system)

# Initialize default directories.
set(COINBILL_TOP_DIR ${CMAKE_SOURCE_DIR})
set(COINBILL_LIB_DIR ${COINBILL_TOP_DIR}/lib/)
set(COINBILL_INC_DIR ${COINBILL_TOP_DIR}/include/)
set(COINBILL_OUT_DIR ${COINBILL_TOP_DIR}/output/)
set(COINBILL_CMAKE_DIR ${COINBILL_TOP_DIR}/cmake/)

include(${COINBILL_CMAKE_DIR}/CoinBill-Lib.cmake)

# Initialize output directories.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${COINBILL_OUT_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${COINBILL_OUT_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${COINBILL_OUT_DIR}/bin)

# Initialize target directories / libraries.
set(COINBILL_TARGET_LIBRARIES ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
set(COINBILL_TARGET_INCLUDE_DIRS ${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR})
set(COINBILL_TARGET_LIBRARY_DIRS ${Boost_LIBRARY_DIRS} )

# Target type defines.
if(WIN32)
    list(APPEND COINBILL_TARGET_DEFINES -DCOINBILL_WINDOWS)
elseif(APPLE)
    list(APPEND COINBILL_TARGET_DEFINES -DCOINBILL_MAC_OS)
elseif(UNIX)
    list(APPEND COINBILL_TARGET_DEFINES -DCOINBILL_UNIX)
endif()

# Boost defines.
if(Boost_FOUND)
    option(USE_BOOST_ASIO "Use socket library for boost asio." TRUE)
    if(USE_BOOST_ASIO)
        list(APPEND COINBILL_TARGET_DEFINES -DCOINBILL_USE_BOOST_ASIO)
    endif()
endif()

# Add and initialize subdirectories.
add_subdirectory(${COINBILL_LIB_DIR}/Network/)
add_subdirectory(${COINBILL_LIB_DIR}/Support/)


# Now compile it.
AddCoinbill_Exe(CoinBillExec ${COINBILL_LIB_DIR}/CoinBill.cpp)
target_link_libraries(CoinBillExec CoinBillNetwork CoinBillSupport ${COINBILL_TARGET_LIBRARIES})