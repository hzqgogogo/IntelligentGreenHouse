#include <QApplication>
#include "frmmain.h"
#include "api/appinit.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);



    AppInit *init = new AppInit;
    init->Load();

    frmMain frm;
    frm.show();

    return app.exec();
}
