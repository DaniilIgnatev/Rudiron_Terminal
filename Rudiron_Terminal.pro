QT += quick
QT += serialport

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/ioptionsmodeldelegate.cpp \
    Model/optionsmodel.cpp \
    UART/uart.cpp \
    UART/uartpackage.cpp \
    VM/logvm.cpp \
    VM/optionsvm.cpp \
    VM/terminalvm.cpp \
    VM/transmittervm.cpp \
        main.cpp \

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Model/ioptionsmodeldelegate.hpp \
    Model/ioptionsmodeldelegateholder.hpp \
    Model/ioutputdelegate.hpp \
    Model/ioutputdelegateholder.hpp \
    Model/optionsmodel.hpp \
    TypeDefs.hpp \
    UART/uart.hpp \
    UART/uartpackage.hpp \
    VM/logvm.hpp \
    VM/optionsvm.hpp \
    VM/terminalvm.hpp \
    VM/transmittervm.hpp \

INCLUDEPATH += \
    UART \
    VM \
    Model \
