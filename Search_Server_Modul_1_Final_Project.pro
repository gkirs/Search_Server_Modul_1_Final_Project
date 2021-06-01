TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    document.cpp \
    main.cpp \
    read_input_functions.cpp \
    request_queue.cpp \
    search_server.cpp \
    string_processing.cpp

HEADERS += \
    document.h \
    paginator.h \
    read_input_functions.h \
    request_queue.h \
    search_server.h \
    string_processing.h
