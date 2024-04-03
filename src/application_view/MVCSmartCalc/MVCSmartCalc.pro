QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
ICON = img/calc.jpeg

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../controller/bank_calc_controller.cc \
    ../../controller/controller.cc \
    ../../model/bank_calc/calc_credit.cc \
    ../../model/since_calc/calc_calculation.cc \
    ../../model/since_calc/calc_graf_calculation.cc \
    ../../model/since_calc/calc_model.cc \
    ../../model/since_calc/calc_parsing.cc \
    ../../model/since_calc/calc_revers_polish_notation.cc \
    ../../model/since_calc/calc_validation.cc \
    creditwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ../../controller/bank_calc_controller.h \
    ../../controller/controller.h \
    ../../model/bank_calc/calc_credit.h \
    ../../model/since_calc/calc_model.h \
    creditwindow.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    creditwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#DISTFILES += \
#    img/calc.jpeg
