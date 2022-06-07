#include <QGuiApplication>
#include <QObject>
#include <QQmlComponent>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QSurfaceFormat>

#include "terminalvm.hpp"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    qmlRegisterType<TerminalVM>("com.VM",1, 0,"TerminalVM");
    qmlRegisterType<TransmitterVM>("com.VM",1, 0,"TransmitterVM");
    qmlRegisterType<OptionsVM>("com.VM",1, 0,"OptionsVM");
    qmlRegisterType<LogVM>("com.VM",1, 0,"LogVM");

    qmlRegisterType<UARTPackage>("com.VM", 1, 0, "UARTPackage");
    qmlRegisterType<OptionsModel>("com.VM", 1, 0, "OptionsModel");
    qmlRegisterType<OptionsOutputModel>("com.VM", 1, 0, "OptionsOutputModel");
    qmlRegisterType<IOMode>("com.VM", 1, 0, "IOMode");

    //Не реализованые фичи
    //Режим ввода текста
    //Режим вывода текста
    //Кодировка отправляемого текста
    //Кодировка читаемого текста
    //Открыть порт только для чтения

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/Components/Terminal.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
