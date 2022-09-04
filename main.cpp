#include <QGuiApplication>
#include <QObject>
#include <QQmlComponent>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QSurfaceFormat>
#include <QThread>

#include "terminalvm.hpp"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QCoreApplication::setApplicationName("Rudiron Terminal");
    QCoreApplication::setApplicationVersion("1.1.5");

    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/icon.ico"));

    qmlRegisterType<TerminalVM>("com.VM",1, 0,"TerminalVM");
    qmlRegisterType<TransmitterVM>("com.VM",1, 0,"TransmitterVM");
    qmlRegisterType<OptionsVM>("com.VM",1, 0,"OptionsVM");
    qmlRegisterType<LogVM>("com.VM",1, 0,"LogVM");

    qmlRegisterType<UARTPackage>("com.VM", 1, 0, "UARTPackage");
    qmlRegisterType<OptionsModel>("com.VM", 1, 0, "OptionsModel");
    qmlRegisterType<OptionsOutputModel>("com.VM", 1, 0, "OptionsOutputModel");
    qmlRegisterType<IOMode>("com.VM", 1, 0, "IOMode");


    qDebug() << "Main thread ID = " << QThread::currentThreadId();
    //Баги:
    //Удаление первых приводит к визуальным ошибкам
    //Автопрокрутка срабатывает, когда сролл еще не завершился

    //Не реализовано:
    //режимы ввода текста: 2й, 8й, 16й
    //режимы вывода текста: 2й, 8й, 16й
    //открывать порт только для чтения
    //сохранять последние настройки
    //загружать последние настройки
    //кодировка отправляемого текста
    //кодировка принимаемого текста

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
