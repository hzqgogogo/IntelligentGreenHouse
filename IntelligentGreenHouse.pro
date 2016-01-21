QT += network sql
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
            frmdata.cpp

HEADERS += frmmain.h \
            usercontrol/frminputbox.h \
            usercontrol/frmmessagebox.h \
            usercontrol/qcustomplot.h \
            api/myhelper.h \
            api/iconhelper.h \
            api/app.h \
            api/appinit.h \
            api/showdatetime.h \
            frmdata.h

FORMS += frmmain.ui \
            usercontrol/frminputbox.ui \
            usercontrol/frmmessagebox.ui \
            frmdata.ui

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/usercontrol

win32:RC_FILE   = other/main.rc

RESOURCES += other/rc.qrc
