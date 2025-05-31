#ifndef PATHFINDER_H
#define PATHFINDER_H
#include "oleadas.h"
#include <QObject>
#include <QVariantList>
#include <QPoint>
#include <QList>
#include <QTimer>

//El algoritmo de pathfinding esta basado a partir de: https://www.geeksforgeeks.org/a-search-algorithm/

class PathFinder : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList gridData READ gridData WRITE setGridData NOTIFY gridDataChanged)
    Q_PROPERTY(bool isMoving READ isMoving NOTIFY isMovingChanged)
    Q_PROPERTY(int selectedTowerType READ selectedTowerType WRITE setSelectedTowerType NOTIFY selectedTowerTypeChanged)
    Q_PROPERTY(Oleadas* oleadas READ oleadas CONSTANT)

public:
    explicit PathFinder(QObject *parent = nullptr);

    QVariantList gridData() const;
    void setGridData(const QVariantList &data);

    bool isMoving() const { return m_isMoving; }

    int selectedTowerType() const { return m_selectedTowerType; }
    void setSelectedTowerType(int type);

    Q_INVOKABLE void findPath();
    Q_INVOKABLE void moveCharacter();
    Q_INVOKABLE bool placeTower(int row, int col);
    Q_INVOKABLE bool upgradeTower(int row, int col);
    Q_INVOKABLE int getTowerLevel(int towerType) const;
    Q_INVOKABLE int getTowerType(int towerType) const;

    Q_INVOKABLE void iniciarOleada();
    Q_INVOKABLE void detenerOleada();
    Q_INVOKABLE bool hayOleadaActiva() const;
    Oleadas* oleadas() const { return m_oleadas; }

signals:
    void gridDataChanged();
    void isMovingChanged();
    void selectedTowerTypeChanged();

private:
    QVariantList m_gridData;
    QList<QPoint> m_path;
    QTimer m_moveTimer;
    int m_currentPathIndex;
    bool m_isMoving;
    int m_selectedTowerType;

    Oleadas *m_oleadas;

    // Constantes para los tipos de celdas
    static const int BLOCKED = 0;
    static const int PATH = 1;
    static const int PLAYER = 2;
    static const int GOAL = 3;
    static const int PATH_MARKER = 4;

    // Constantes para las torres
    static const int ARTILLERO_1 = 11;
    static const int ARTILLERO_2 = 12;
    static const int ARTILLERO_3 = 13;
    static const int ARQUERO_1 = 14;
    static const int ARQUERO_2 = 15;
    static const int ARQUERO_3 = 16;
    static const int MAGO_1 = 17;
    static const int MAGO_2 = 18;
    static const int MAGO_3 = 19;

    // Tamaño del grid
    static const int ROWS = 16;
    static const int COLS = 32;

    // Métodos auxiliares para el algoritmo A*
    bool isValid(int row, int col) const;
    bool isBlocked(int row, int col) const;
    bool isDestination(int row, int col, const QPoint &dest) const;
    double calculateHValue(int row, int col, const QPoint &dest) const;
    QList<QPoint> tracePath(const QVector<QVector<QPair<int, int>>> &parentCells, const QPoint &dest) const;
    QPoint findPlayerPosition() const;
    QPoint findGoalPosition() const;
    int getIndex(int row, int col) const;
    bool canPlaceTower(int row, int col) const;
    bool isTower(int cellValue) const;
    bool canUpgradeTower(int cellValue) const;
};

#endif // PATHFINDER_H
