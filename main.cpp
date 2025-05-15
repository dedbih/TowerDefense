#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QVariantList>
#include "pathfinder.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Definir la matriz
    int grid[10][10] = {
        { 2, 0, 1, 1, 1, 0, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 1, 0, 0, 0, 1, 1 },
        { 0, 0, 1, 0, 1, 0, 0, 1, 0, 1 },
        { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 0, 1, 0, 0, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 1, 0, 0, 0, 0 },
        { 1, 0, 0, 0, 0, 1, 1, 3, 0, 1 },
        { 1, 0, 1, 1, 1, 1, 0, 0, 0, 1 },
        { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    // Convertir la matriz a QVariantList para QML
    QVariantList gridData;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            gridData.append(grid[i][j]);
        }
    }

    // Crear el objeto PathFinder
    PathFinder pathFinder;
    pathFinder.setGridData(gridData);

    // Registrar el tipo PathFinder para QML
    qmlRegisterType<PathFinder>("com.example", 1, 0, "PathFinder");

    // Exponer el objeto PathFinder al contexto QML
    engine.rootContext()->setContextProperty("pathFinder", &pathFinder);

    // Exponerla al contexto QML
    engine.rootContext()->setContextProperty("gridData", gridData);

    engine.loadFromModule("TorreDefensaJuego", "Main");

    return app.exec();
}


