#include "pathfinder.h"
#include <QDebug>
#include <queue>
#include <cmath>
#include <cfloat>
//El algoritmo de pathfinding esta basado a partir de: https://www.geeksforgeeks.org/a-search-algorithm/

PathFinder::PathFinder(QObject *parent) : QObject(parent), m_isMoving(false), m_selectedTowerType(0)
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
    m_oleadas = new Oleadas(this);

    // Conectar señales
    connect(m_oleadas, &Oleadas::gridActualizado, this, &PathFinder::gridDataChanged);
}

void PathFinder::iniciarOleada()
{
    if (m_path.isEmpty()) {
        findPath(); // Encontrar ruta primero
    }

    if (!m_path.isEmpty()) {
        m_oleadas->iniciarOleada(m_path, m_gridData);
    }
}

void PathFinder::detenerOleada()
{
    m_oleadas->detenerOleada();
}

bool PathFinder::hayOleadaActiva() const
{
    return m_oleadas->oleadaActiva();
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

void PathFinder::setSelectedTowerType(int type)
{
    if (m_selectedTowerType != type) {
        m_selectedTowerType = type;
        emit selectedTowerTypeChanged();
        qDebug() << "Torre seleccionada:" << type;
    }
}

bool PathFinder::upgradeTower(int row, int col)
{
    if (!isValid(row, col)) {
        qDebug() << "Posición inválida para mejorar torre:" << row << "," << col;
        return false;
    }

    int index = getIndex(row, col);
    if (index < 0 || index >= m_gridData.size()) {
        qDebug() << "Índice fuera de rango para mejorar torre:" << index;
        return false;
    }

    int cellValue = m_gridData[index].toInt();

    // Verificar si hay una torre que se pueda mejorar
    if (!canUpgradeTower(cellValue)) {
        qDebug() << "No hay una torre que se pueda mejorar en la posición:" << row << "," << col;
        return false;
    }

    // Mejorar la torre al siguiente nivel
    int newTowerType = cellValue + 1;
    m_gridData[index] = newTowerType;
    emit gridDataChanged();

    qDebug() << "Torre mejorada en posición:" << row << "," << col
             << "de nivel" << getTowerLevel(cellValue) << "a nivel" << getTowerLevel(newTowerType);

    return true;
}

bool PathFinder::placeTower(int row, int col)
{
    if (!canPlaceTower(row, col)) {
        qDebug() << "No se puede colocar torre en la posición:" << row << "," << col;
        return false;
    }

    if (m_selectedTowerType == 0) {
        qDebug() << "No hay tipo de torre seleccionado";
        return false;
    }

    int index = getIndex(row, col);
    if (index >= 0 && index < m_gridData.size()) {
        m_gridData[index] = m_selectedTowerType;
        emit gridDataChanged();
        qDebug() << "Torre colocada en posición:" << row << "," << col << "Tipo:" << m_selectedTowerType;
        return true;
    }

    return false;
}

bool PathFinder::canPlaceTower(int row, int col) const
{
    if (!isValid(row, col)) {
        return false;
    }

    int index = getIndex(row, col);
    if (index < 0 || index >= m_gridData.size()) {
        return false;
    }

    int cellValue = m_gridData[index].toInt();

    // Solo se puede colocar torre en celdas de camino (PATH = 1)
    // No se puede colocar en celdas bloqueadas, jugador, meta, o donde ya hay torres
    return (cellValue == PATH || cellValue == PATH_MARKER);
}

bool PathFinder::isTower(int cellValue) const
{
    // Verifica si el valor corresponde a cualquier tipo de torre
    return (cellValue >= ARTILLERO_1 && cellValue <= MAGO_3);
}

bool PathFinder::canUpgradeTower(int cellValue) const
{
    // Solo se pueden mejorar torres de nivel 1 y 2
    return (cellValue == ARTILLERO_1 || cellValue == ARTILLERO_2 ||
            cellValue == ARQUERO_1 || cellValue == ARQUERO_2 ||
            cellValue == MAGO_1 || cellValue == MAGO_2);
}

bool PathFinder::isValid(int row, int col) const
{
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS);
}

bool PathFinder::isBlocked(int row, int col) const
{
    int index = getIndex(row, col);
    if (index < 0 || index >= m_gridData.size()) {
        return true;
    }

    int cellValue = m_gridData[index].toInt();

    // Las celdas bloqueadas incluyen: BLOCKED y todas las torres (11-19)
    return (cellValue == BLOCKED || (cellValue >= 11 && cellValue <= 19));
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

int PathFinder::getTowerLevel(int towerType) const
{
    // Determina el nivel de la torre basado en su tipo
    if (towerType == ARTILLERO_1 || towerType == ARQUERO_1 || towerType == MAGO_1) {
        return 1;
    } else if (towerType == ARTILLERO_2 || towerType == ARQUERO_2 || towerType == MAGO_2) {
        return 2;
    } else if (towerType == ARTILLERO_3 || towerType == ARQUERO_3 || towerType == MAGO_3) {
        return 3;
    }
    return 0; // No es una torre
}

int PathFinder::getTowerType(int towerType) const
{
    // Determina el tipo base de la torre (artillero, arquero, mago)
    if (towerType >= ARTILLERO_1 && towerType <= ARTILLERO_3) {
        return ARTILLERO_1; // Tipo base: Artillero
    } else if (towerType >= ARQUERO_1 && towerType <= ARQUERO_3) {
        return ARQUERO_1; // Tipo base: Arquero
    } else if (towerType >= MAGO_1 && towerType <= MAGO_3) {
        return MAGO_1; // Tipo base: Mago
    }
    return 0; // No es una torre
}

int PathFinder::getIndex(int row, int col) const
{
    return row * COLS + col;
}

void PathFinder::findPath()
{
    // Si ya inicio la oleada, omitir
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
