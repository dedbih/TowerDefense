#include "pathfinder.h"
#include <QDebug>
#include <queue>
#include <cmath>
#include <cfloat>

PathFinder::PathFinder(QObject *parent) : QObject(parent), m_isMoving(false)
{
    // Conectar el timer para mover el personaje
    connect(&m_moveTimer, &QTimer::timeout, this, [this]() {
        if (m_currentPathIndex < m_path.size()) {
            // Obtener la posición actual del jugador
            QPoint playerPos = findPlayerPosition();

            // Obtener la siguiente posición en la ruta
            QPoint nextPos = m_path[m_currentPathIndex];

            // Actualizar el grid: mover el jugador a la nueva posición
            int playerIndex = getIndex(playerPos.x(), playerPos.y());
            int nextIndex = getIndex(nextPos.x(), nextPos.y());

            m_gridData[playerIndex] = PATH;
            m_gridData[nextIndex] = PLAYER;

            // Avanzar al siguiente punto en la ruta
            m_currentPathIndex++;

            // Emitir señal de que los datos del grid han cambiado
            emit gridDataChanged();

            // Si hemos llegado al final de la ruta, detener el timer
            if (m_currentPathIndex >= m_path.size()) {
                m_moveTimer.stop();
                m_isMoving = false;
                emit isMovingChanged();
            }
        } else {
            m_moveTimer.stop();
            m_isMoving = false;
            emit isMovingChanged();
        }
    });
}

QVariantList PathFinder::gridData() const
{
    return m_gridData;
}

void PathFinder::setGridData(const QVariantList &data)
{
    if (m_gridData != data) {
        m_gridData = data;
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

QPoint PathFinder::findPlayerPosition() const
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int index = getIndex(i, j);
            if (index < m_gridData.size() && m_gridData[index].toInt() == PLAYER) {
                return QPoint(i, j);
            }
        }
    }

    return QPoint(-1, -1);
}

QPoint PathFinder::findGoalPosition() const
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int index = getIndex(i, j);
            if (index < m_gridData.size() && m_gridData[index].toInt() == GOAL) {
                return QPoint(i, j);
            }
        }
    }

    return QPoint(-1, -1);
}

int PathFinder::getIndex(int row, int col) const
{
    return row * COLS + col;
}

void PathFinder::findPath()
{
    // Si ya estamos en movimiento, no hacer nada
    if (m_isMoving) {
        return;
    }

    // Encontrar la posición del jugador y la meta
    QPoint src = findPlayerPosition();
    QPoint dest = findGoalPosition();

    if (src.x() == -1 || dest.x() == -1) {
        qDebug() << "No se pudo encontrar el jugador o la meta";
        return;
    }

    // Verificar si el origen o el destino están bloqueados
    if (isBlocked(src.x(), src.y()) || isBlocked(dest.x(), dest.y())) {
        qDebug() << "Origen o destino bloqueados";
        return;
    }

    // Verificar si ya estamos en el destino
    if (isDestination(src.x(), src.y(), dest)) {
        qDebug() << "Ya estamos en el destino";
        return;
    }

    // Crear una lista cerrada (celdas ya visitadas)
    QVector<QVector<bool>> closedList(ROWS, QVector<bool>(COLS, false));

    // Crear una matriz para almacenar los detalles de cada celda
    QVector<QVector<double>> fList(ROWS, QVector<double>(COLS, FLT_MAX));
    QVector<QVector<double>> gList(ROWS, QVector<double>(COLS, FLT_MAX));
    QVector<QVector<double>> hList(ROWS, QVector<double>(COLS, FLT_MAX));
    QVector<QVector<QPair<int, int>>> parentCells(ROWS, QVector<QPair<int, int>>(COLS, qMakePair(-1, -1)));

    // Inicializar la celda de origen
    int i = src.x(), j = src.y();
    fList[i][j] = 0.0;
    gList[i][j] = 0.0;
    hList[i][j] = 0.0;
    parentCells[i][j] = qMakePair(i, j);

    // Crear una lista abierta (celdas por visitar)
    // <f, <row, col>>
    std::priority_queue<std::pair<double, QPair<int, int>>,
                        std::vector<std::pair<double, QPair<int, int>>>,
                        std::greater<std::pair<double, QPair<int, int>>>> openList;

    // Añadir la celda de origen a la lista abierta
    openList.push(std::make_pair(0.0, qMakePair(i, j)));

    // Bandera para indicar si se ha encontrado el destino
    bool foundDest = false;

    // Mientras la lista abierta no esté vacía
    while (!openList.empty() && !foundDest) {
        // Obtener la celda con menor f de la lista abierta
        std::pair<double, QPair<int, int>> p = openList.top();
        openList.pop();

        // Añadir la celda a la lista cerrada
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        // Para cada dirección (arriba, abajo, izquierda, derecha)
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int dir = 0; dir < 4; ++dir) {
            int newRow = i + dx[dir];
            int newCol = j + dy[dir];

            // Verificar si la nueva celda es válida
            if (isValid(newRow, newCol)) {
                // Si hemos llegado al destino
                if (isDestination(newRow, newCol, dest)) {
                    // Establecer el padre de la celda destino
                    parentCells[newRow][newCol] = qMakePair(i, j);
                    qDebug() << "Destino encontrado";
                    foundDest = true;

                    // Trazar la ruta
                    m_path = tracePath(parentCells, dest);
                    break;
                }
                // Si la celda no está en la lista cerrada y no está bloqueada
                else if (!closedList[newRow][newCol] && !isBlocked(newRow, newCol)) {
                    // Calcular los nuevos valores de g, h y f
                    double gNew = gList[i][j] + 1.0;
                    double hNew = calculateHValue(newRow, newCol, dest);
                    double fNew = gNew + hNew;

                    // Si la celda no está en la lista abierta o tiene un f menor
                    if (fList[newRow][newCol] == FLT_MAX || fList[newRow][newCol] > fNew) {
                        // Actualizar los valores de la celda
                        fList[newRow][newCol] = fNew;
                        gList[newRow][newCol] = gNew;
                        hList[newRow][newCol] = hNew;
                        parentCells[newRow][newCol] = qMakePair(i, j);

                        // Añadir la celda a la lista abierta
                        openList.push(std::make_pair(fNew, qMakePair(newRow, newCol)));
                    }
                }
            }
        }
    }

    // Si no se ha encontrado el destino
    if (!foundDest) {
        qDebug() << "No se ha encontrado una ruta al destino";
        return;
    }

    // Marcar la ruta en el grid (opcional)
    for (const QPoint &point : m_path) {
        int index = getIndex(point.x(), point.y());
        if (m_gridData[index].toInt() == PATH) {
            m_gridData[index] = PATH_MARKER;
        }
    }

    emit gridDataChanged();
}

void PathFinder::moveCharacter()
{
    // Si ya estamos en movimiento, no hacer nada
    if (m_isMoving) {
        return;
    }

    // Encontrar la ruta si no la tenemos
    if (m_path.isEmpty()) {
        findPath();
    }

    // Si no se encontró una ruta, no hacer nada
    if (m_path.isEmpty()) {
        return;
    }

    // Iniciar el movimiento
    m_currentPathIndex = 0;
    m_isMoving = true;
    emit isMovingChanged();

    // Iniciar el timer para mover el personaje
    m_moveTimer.start(500); // Mover cada 500ms
}
