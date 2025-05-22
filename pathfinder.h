#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <QObject>
#include <QVariantList>
#include <QPoint>
#include <QList>
#include <QTimer>
#include <QRandomGenerator>

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

signals:
    void gridDataChanged();
    void isMovingChanged();

private:
    struct Character {
        QList<QPoint> path;
        int currentPathIndex = 0;  // Inicialización directa
        int type = 5;
        QPoint currentPosition;

        Character() = default;
        Character(QList<QPoint> p, int t, QPoint pos) :
            path(p), type(t), currentPosition(pos) {}
    };

    QPoint m_goalPosition;
    QVariantList m_gridData;
    QTimer m_moveTimer;
    QTimer m_spawnTimer;
    bool m_isMoving;
    QList<Character> m_activeCharacters;

    //constantes para los tipos de celdas
    static const int BLOCKED = 0;
    static const int PATH = 1;
    static const int PLAYER = 2;
    static const int GOAL = 3;
    static const int PATH_MARKER = 4;
    static const int ROWS = 10;
    static const int COLS = 10;

    bool isValid(int row, int col) const;
    bool isBlocked(int row, int col) const;
    bool isDestination(int row, int col, const QPoint &dest) const;
    double calculateHValue(int row, int col, const QPoint &dest) const;
    QList<QPoint> tracePath(const QVector<QVector<QPair<int, int>>> &parentCells, const QPoint &dest) const;
    QPoint findGoalPosition() const;
    int getIndex(int row, int col) const;
    QList<QPoint> computePath(const QPoint &src, const QPoint &dest);
    void spawnCharacter();
    void moveCharacters();
    int generateRandomType() { return QRandomGenerator::global()->bounded(5, 19); }

};

#endif // PATHFINDER_H

