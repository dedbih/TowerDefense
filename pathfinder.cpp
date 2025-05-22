#include "pathfinder.h"
#include <QDebug>
#include <queue>
#include <cmath>
#include <cfloat>

PathFinder::PathFinder(QObject *parent) : QObject(parent), m_isMoving(false)
{
    connect(&m_moveTimer, &QTimer::timeout, this, &PathFinder::moveCharacters);
    connect(&m_spawnTimer, &QTimer::timeout, this, &PathFinder::spawnCharacter);
    m_spawnTimer.start(3000); // Spawn every 3 seconds
    m_goalPosition = findGoalPosition();
}
QVariantList PathFinder::gridData() const
{
    return m_gridData;
}

void PathFinder::setGridData(const QVariantList &data)
{
    if (m_gridData != data) {
        m_gridData = data;
        m_goalPosition = findGoalPosition();
        qDebug() << "Goal position updated:" << m_goalPosition;
        emit gridDataChanged();
    }
}

bool PathFinder::isValid(int row, int col) const
{
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS);
}

bool PathFinder::isBlocked(int row, int col) const
{
    int index = getIndex(row, col);
    return (index >= 0 && index < m_gridData.size() && m_gridData[index].toInt() == BLOCKED);
}

bool PathFinder::isDestination(int row, int col, const QPoint &dest) const
{
    return (row == dest.x() && col == dest.y());
}

double PathFinder::calculateHValue(int row, int col, const QPoint &dest) const
{
    // Usamos la distancia Manhattan ya que solo permitimos movimientos horizontales y verticales
    return std::abs(row - dest.x()) + std::abs(col - dest.y());
}

QList<QPoint> PathFinder::tracePath(const QVector<QVector<QPair<int, int>>> &parentCells, const QPoint &dest) const
{
    QList<QPoint> path;

    int row = dest.x();
    int col = dest.y();

    while (!(parentCells[row][col].first == row && parentCells[row][col].second == col)) {
        path.prepend(QPoint(row, col));

        int temp_row = parentCells[row][col].first;
        int temp_col = parentCells[row][col].second;
        row = temp_row;
        col = temp_col;
    }

    return path;
}

QPoint PathFinder::findGoalPosition() const
{
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int index = getIndex(i, j);
            if (index < m_gridData.size() && m_gridData[index].toInt() == GOAL) {
                return QPoint(i, j);
            }
        }
    }
    qWarning() << "Goal not found!";
    return QPoint(-1, -1);
}

int PathFinder::getIndex(int row, int col) const
{
    return row * COLS + col;
}

QList<QPoint> PathFinder::computePath(const QPoint &src, const QPoint &dest)
{
    QList<QPoint> path;
    if (!isValid(src.x(), src.y()) || !isValid(dest.x(), dest.y())) {
        qDebug() << "Invalid source or destination";
        return path;
    }
    QVector<QVector<bool>> closedList(ROWS, QVector<bool>(COLS, false));
    QVector<QVector<QPair<int, int>>> parentCells(ROWS, QVector<QPair<int, int>>(COLS, qMakePair(-1, -1)));

    std::priority_queue<std::pair<double, QPair<int, int>>,
                        std::vector<std::pair<double, QPair<int, int>>>,
                        std::greater<std::pair<double, QPair<int, int>>>> openList;

    openList.push({0.0, {src.x(), src.y()}});
    parentCells[src.x()][src.y()] = {src.x(), src.y()};

    bool foundDest = false;

    while (!openList.empty() && !foundDest) {
        auto [f, pos] = openList.top();
        auto [i, j] = pos;
        openList.pop();
        closedList[i][j] = true;

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int dir = 0; dir < 4; ++dir) {
            int newRow = i + dx[dir];
            int newCol = j + dy[dir];

            if (isValid(newRow, newCol)) {
                if (isDestination(newRow, newCol, dest)) {
                    parentCells[newRow][newCol] = {i, j};
                    foundDest = true;
                    path = tracePath(parentCells, dest);
                    break;
                }
                else if (!closedList[newRow][newCol] && !isBlocked(newRow, newCol)) {
                    double gNew = (i == src.x() && j == src.y()) ? 0 : 1;
                    double hNew = calculateHValue(newRow, newCol, dest);
                    double fNew = gNew + hNew;

                    if (parentCells[newRow][newCol].first == -1 || fNew < f) {
                        openList.push({fNew, {newRow, newCol}});
                        parentCells[newRow][newCol] = {i, j};
                    }
                }
            }
        }
    }
    return path;
}

void PathFinder::spawnCharacter()
{
    QPoint spawnPoint(0, 0);

    // 1. Verificar posición objetivo y spawn válidos
    if (m_goalPosition.x() == -1 || isBlocked(spawnPoint.x(), spawnPoint.y())) {
        return;
    }

    // Generar tipo de enemigo aleatorio
    int enemyType = generateRandomType();
    qDebug() << "Generando enemigo tipo:" << enemyType;

    if (isBlocked(spawnPoint.x(), spawnPoint.y())) {
        qDebug() << "Spawn bloqueado";
        return;
    }

    // 2. Calcular ruta con verificación adicional
    QList<QPoint> newPath = computePath(spawnPoint, m_goalPosition);
    if (newPath.isEmpty()) {
        qDebug() << "Ruta inválida";
        return;
    }

    // 3. Inicialización correcta del personaje
    Character newChar;
    newChar.path = newPath;
    newChar.currentPathIndex = 0;  // Inicializar explícitamente
    newChar.type = enemyType;
    newChar.currentPosition = spawnPoint;

    // 4. Verificar celda de spawn
    int spawnIndex = getIndex(spawnPoint.x(), spawnPoint.y());
    if (spawnIndex >= m_gridData.size() || m_gridData[spawnIndex].toInt() != PATH) {
        qDebug() << "Celda ocupada:" << m_gridData[spawnIndex];
        return;
    }

    // 5. Actualizar grid y lista
    m_gridData[spawnIndex] = newChar.type;
    m_activeCharacters.append(newChar);

    qDebug() << "Personaje generado. Índice inicial:" << spawnIndex
             << "Ruta:" << newPath.size();

    // 6. Iniciar movimiento si está detenido
    if (!m_moveTimer.isActive()) {
        m_moveTimer.start(500);
        m_isMoving = true;
        emit isMovingChanged();
    }
    emit gridDataChanged();
}
void PathFinder::moveCharacters()
{
    bool updated = false;

    for (int i = 0; i < m_activeCharacters.size();) {
        Character &c = m_activeCharacters[i];

        // 1. Validación completa de índices
        if (c.currentPathIndex < 0 || c.currentPathIndex >= c.path.size()) {
            qDebug() << "Índice inválido. Eliminando personaje en" << c.currentPosition;

            // Liberar celda ocupada
            int cleanupIndex = getIndex(c.currentPosition.x(), c.currentPosition.y());
            if (cleanupIndex >= 0 && cleanupIndex < m_gridData.size()) {
                m_gridData[cleanupIndex] = PATH;
            }

            m_activeCharacters.removeAt(i);
            updated = true;
            continue;
        }

        QPoint next = c.path[c.currentPathIndex];

        // 2. Validación de posición siguiente
        if (!isValid(next.x(), next.y()) || isBlocked(next.x(), next.y())) {
            qDebug() << "Movimiento inválido. Eliminando personaje";
            int cleanupIndex = getIndex(c.currentPosition.x(), c.currentPosition.y());
            m_gridData[cleanupIndex] = PATH;
            m_activeCharacters.removeAt(i);
            updated = true;
            continue;
        }

        // 3. Actualizar posiciones
        int oldIndex = getIndex(c.currentPosition.x(), c.currentPosition.y());
        int newIndex = getIndex(next.x(), next.y());

        m_gridData[oldIndex] = PATH;
        m_gridData[newIndex] = c.type;
        c.currentPosition = next;
        c.currentPathIndex++;

        // 4. Llegada al objetivo
        if (c.currentPosition == m_goalPosition) {
            qDebug() << "Personaje llegó al objetivo";
            m_gridData[newIndex] = GOAL;
            m_activeCharacters.removeAt(i);
            updated = true;
            continue;
        }

        i++;
        updated = true;
    }

    if (updated) emit gridDataChanged();

    if (m_activeCharacters.isEmpty()) {
        m_moveTimer.stop();
        m_isMoving = false;
        emit isMovingChanged();
    }
}

void PathFinder::findPath()
{
    // Limpiar marcadores de ruta previos
    for (int i = 0; i < m_gridData.size(); ++i) {
        if (m_gridData[i].toInt() == PATH_MARKER) {
            m_gridData[i] = PATH;
        }
    }

    QPoint src(0, 0); // Posición fija de spawn
    QPoint dest = findGoalPosition();

    if (src.x() == -1 || dest.x() == -1) {
        qDebug() << "Posición inicial o final inválida";
        return;
    }

    if (isBlocked(src.x(), src.y()) || isBlocked(dest.x(), dest.y())) {
        qDebug() << "Celda inicial o final bloqueada";
        return;
    }

    QVector<QVector<bool>> closedList(ROWS, QVector<bool>(COLS, false));
    QVector<QVector<QPair<int, int>>> parentCells(ROWS, QVector<QPair<int, int>>(COLS, qMakePair(-1, -1)));

    std::priority_queue<std::pair<double, QPair<int, int>>,
                        std::vector<std::pair<double, QPair<int, int>>>,
                        std::greater<std::pair<double, QPair<int, int>>>> openList;

    openList.push({0.0, {src.x(), src.y()}});
    parentCells[src.x()][src.y()] = {src.x(), src.y()};

    bool foundDest = false;

    while (!openList.empty() && !foundDest) {
        auto p = openList.top();
        openList.pop();

        int i = p.second.first;
        int j = p.second.second;
        closedList[i][j] = true;

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int dir = 0; dir < 4; ++dir) {
            int newRow = i + dx[dir];
            int newCol = j + dy[dir];

            if (isValid(newRow, newCol)) {
                if (isDestination(newRow, newCol, dest)) {
                    parentCells[newRow][newCol] = {i, j};
                    foundDest = true;
                    QList<QPoint> newPath = tracePath(parentCells, dest);

                    // Marcar la ruta en el grid
                    for (const QPoint &point : newPath) {
                        int index = getIndex(point.x(), point.y());
                        if (m_gridData[index].toInt() == PATH) {
                            m_gridData[index] = PATH_MARKER;
                        }
                    }
                    break;
                }
                else if (!closedList[newRow][newCol] && !isBlocked(newRow, newCol)) {
                    double gNew = (i == src.x() && j == src.y()) ? 0 : 1;
                    double hNew = calculateHValue(newRow, newCol, dest);
                    double fNew = gNew + hNew;

                    if (parentCells[newRow][newCol].first == -1 || fNew < p.first) {
                        openList.push({fNew, {newRow, newCol}});
                        parentCells[newRow][newCol] = {i, j};
                    }
                }
            }
        }
    }

    if (!foundDest) {
        qDebug() << "No se encontró ruta al destino";
        return;
    }

    emit gridDataChanged();
}

