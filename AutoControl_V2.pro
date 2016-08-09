#-------------------------------------------------
#
# Project created by YuanYuan 2012-09-17T11:06:38
#
#-------------------------------------------------

QT += core gui\
      sql\


TARGET = AutoControl_V2
TEMPLATE = app


SOURCES += main.cpp\
        autocontrol_v2.cpp \
    posix_qextserialport.cpp \
    qextserialbase.cpp \
    adddevice.cpp \
    threefivedev.cpp \
    irdev.cpp \
    smartcar.cpp \
    set.cpp \
    connectset.cpp \
    cguangxian.cpp \
    cqiti.cpp \
    csmog.cpp \
    crain.cpp \
    ckey.cpp \
    cwenshidu.cpp \
    ckongqi.cpp \
    input.cpp \
    telset.cpp \
    timerfun.cpp \
    smartshelf.cpp \
    inshelf.cpp \
    yanshiban.cpp \
    viewadddevice.cpp \
    viewirdevice.cpp \
    viewthreefivedevice.cpp \
    zhiwen.cpp \
    ftcombine.cpp \
    intesandtable.cpp \
    inteagricul.cpp \
    vkey.cpp \
    button.cpp \
    inteshelf.cpp \
    intehomefurn.cpp \
    testwifi.cpp \
    testcom.cpp \
    testgprs.cpp \
    testgps.cpp \
    gpsinfo.cpp \
    testthreeg.cpp \
    testbasic.cpp \
    curve.cpp \
    ftshtline.cpp

HEADERS  += autocontrol_v2.h \
    posix_qextserialport.h \
    qextserialbase.h \
    adddevice.h \
    threefivedev.h \
    irdev.h \
    smartcar.h \
    set.h \
    connectset.h \
    cguangxian.h \
    cqiti.h \
    csmog.h \
    crain.h \
    ckey.h \
    cwenshidu.h \
    ckongqi.h \
    input.h \
    telset.h \
    timerfun.h \
    smartshelf.h \
    inshelf.h \
    yanshiban.h \
    viewadddevice.h \
    viewirdevice.h \
    viewthreefivedevice.h \
    zhiwen.h \
    ftcombine.h \
    intesandtable.h \
    inteagricul.h \
    button.h \
    vkey.h \
    inteshelf.h \
    intehomefurn.h \
    testwifi.h \
    testcom.h \
    testgprs.h \
    testgps.h \
    gpsinfo.h \
    testthreeg.h \
    testbasic.h \
    curve.h \
    ftshtline.h \
    Queue.h

FORMS    += autocontrol_v2.ui \
    adddevice.ui \
    threefivedev.ui \
    irdev.ui \
    smartcar.ui \
    set.ui \
    connectset.ui \
    cguangxian.ui \
    cqiti.ui \
    csmog.ui \
    crain.ui \
    ckey.ui \
    cwenshidu.ui \
    ckongqi.ui \
    input.ui \
    telset.ui \
    timerfun.ui \
    smartshelf.ui \
    inshelf.ui \
    yanshiban.ui \
    viewadddevice.ui \
    viewirdevice.ui \
    viewthreefivedevice.ui \
    zhiwen.ui \
    ftcombine.ui \
    intesandtable.ui \
    inteagricul.ui \
    inteshelf.ui \
    intehomefurn.ui \
    testwifi.ui \
    testcom.ui \
    testgprs.ui \
    testgps.ui \
    testthreeg.ui \
    testbasic.ui \
    ftshtline.ui

RESOURCES += \
    AutoControl_V2.qrc

OTHER_FILES +=
