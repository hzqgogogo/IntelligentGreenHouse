QT += network sql xml
TARGET = IntelligentGreenHouse
TEMPLATE = app

SOURCES += main.cpp \
            frmmain.cpp \
            usercontrol/frminputbox.cpp \
            usercontrol/frmmessagebox.cpp \
            usercontrol/qcustomplot.cpp \
            api/iconhelper.cpp \
            api/app.cpp \
            api/appinit.cpp \
            api/showdatetime.cpp \
            frmdata.cpp \
            qtsoap.cpp \
            sensordata.cpp \
            frmconfig.cpp \
            frmmore.cpp \
            frmlogin.cpp \
            webdata.cpp

HEADERS += frmmain.h \
            usercontrol/frminputbox.h \
            usercontrol/frmmessagebox.h \
            usercontrol/qcustomplot.h \
            api/myhelper.h \
            api/iconhelper.h \
            api/app.h \
            api/appinit.h \
            api/showdatetime.h \
            frmdata.h \
            qtsoap.h \
            sensordata.h \
            frmconfig.h \
            frmmore.h \
            frmlogin.h \
            webdata.h

FORMS += frmmain.ui \
            usercontrol/frminputbox.ui \
            usercontrol/frmmessagebox.ui \
            frmdata.ui \
            sensordata.ui \
            frmconfig.ui \
            frmmore.ui \
            frmlogin.ui

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/usercontrol

MOC_DIR         = temp/moc
RCC_DIR         = temp/rcc
UI_DIR          = temp/ui
OBJECTS_DIR     = temp/obj
DESTDIR         = bin

win32:RC_FILE   = other/main.rc

RESOURCES += other/rc.qrc
