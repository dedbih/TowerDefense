#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <QObject>
#include <QVariantList>
#include <QPoint>
#include <QList>
#include <QTimer>

class PathFinder : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList gridData READ gridData WRITE setGridData NOTIFY gridDataChanged)
    Q_PROPERTY(bool isMoving READ isMoving NOTIFY isMovingChanged)

public:
    explicit PathFinder(QObject *parent = nullptr);

    QVariantList gridData() const;
    void setGridData(const QVariantList &data);

    bool isMoving() const { return m_isMoving; }

    Q_INVOKABLE void findPath();
    Q_INVOKABLE void moveCharacter();

signals:
    void gridDataChanged();
    void isMovingChanged();

private:
    QVariantList m_gridData;
    QList<QPoint> m_path;
    QTimer m_moveTimer;
    int m_currentPathIndex;
    bool m_isMoving;

    // Constantes para los tipos de celdas
    static const int BLOCKED = 0;
    static const int PATH = 1;
    static const int PLAYER = 2;
    static const int GOAL = 3;
    static const int PATH_MARKER = 4; // Para marcar la ruta encontrada

    // Tamaño del grid
    static const int ROWS = 10;
    static const int COLS = 10;

    // Métodos auxiliares para el algoritmo A*
    bool isValid(int row, int col) const;
    bool isBlocked(int row, int col) const;
    bool isDestination(int row, int col, const QPoint &dest) const;
    double calculateHValue(int row, int col, const QPoint &dest) const;
    QList<QPoint> tracePath(const QVector<QVector<QPair<int, int>>> &parentCells, const QPoint &dest) const;
    QPoint findPlayerPosition() const;
    QPoint findGoalPosition() const;
    int getIndex(int row, int col) const;
};

#endif // PATHFINDER_H
