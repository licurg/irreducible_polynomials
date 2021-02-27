cmake_minimum_required(VERSION 3.17)
project(irreducible_polynomials)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "D:/src/qt_binaries/5.12.10/5.12.10/mingw73_64")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(QT_VERSION 5)

set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

add_subdirectory(src)

