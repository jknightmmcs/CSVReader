#include "csvreadermainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QSettings>
#include <QDebug>

QString lang_code;

QTranslator* createTranslator(QObject* parent = nullptr) {
    QSettings settings("settings.ini", QSettings::IniFormat);
    if (settings.contains("language")) {
        lang_code = settings.value("language").toString();
    }
    else {
        lang_code = QLocale::system().bcp47Name();
    }

    QString directories[] = { "translations/", "." };
    auto translator = new QTranslator(parent);

    for (auto directory : directories) {
        if (translator->load("csv_reader_" + lang_code + ".qm", directory)) {
            return translator;
        }
    }

    delete translator;
    return nullptr;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);    

    auto translator = createTranslator();
    if (translator) {
        a.installTranslator(translator);
    }

    CSVReaderMainWindow w;

    w.show();    

    return a.exec();
}
