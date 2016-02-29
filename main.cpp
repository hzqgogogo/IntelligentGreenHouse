#include <QApplication>
#include "frmmain.h"
#include "api/appinit.h"
#include "frmlogin.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    AppInit *init = new AppInit;
    init->Load();

    frmLogin frm;
    frm.show();

    return app.exec();
}
