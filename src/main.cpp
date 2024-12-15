#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QLocale>
#include <QTranslator>

#include "hdr/columnvalvesviewmodel.h"

// Main function: Entry point of the application
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    // Enable high DPI scaling for older Qt versions
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    // Create a QGuiApplication instance
    QGuiApplication app(argc, argv);

    // Set up the QML application engine
    QQmlApplicationEngine engine;

    // Define the main QML file to load
    const QUrl url(QStringLiteral("qrc:/qml/pages/main.qml"));

    // Connect a signal to handle cases where the main QML file fails to load
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) // If the object creation fails and the URL matches
            QCoreApplication::exit(-1); // Exit the application with an error code
    }, Qt::QueuedConnection);

    // Register the `Types::ValvesState` meta-object to make it accessible in QML
    qmlRegisterUncreatableMetaObject(Types::ValvesState::staticMetaObject,
                                     "com.enums", // QML module name
                                     1, 0,        // Module version
                                     "Enums",     // Name in QML
                                     "Enum creation error"); // Error message for uncreatable meta-object

    // Register `ColumnValvesViewModel` as a QML type
    qmlRegisterType<ColumnValvesViewModel>("Vacuum", 1, 0, "ColumnValvesViewModel");

    // Load the main QML file into the application engine
    engine.load(url);

    // Execute the application event loop
    return app.exec();
}
