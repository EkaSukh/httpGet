#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "httpget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    HttpGet getData;

    QQmlApplicationEngine engine;
    QQmlContext* rootContext = engine.rootContext();
    rootContext->setContextProperty("classH", &getData);

    const QUrl qurl(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [qurl](QObject *obj, const QUrl & objUrl){
        if(!obj && qurl == objUrl)
                QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(qurl);

    return app.exec();
}

