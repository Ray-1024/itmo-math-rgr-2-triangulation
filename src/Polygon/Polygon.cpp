#include "Polygon.h"
#include "../Utils/Utils.h"
#include <set>

void Polygon::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(arr, states);
    target.draw(lines, states);
    target.draw(points, states);
}

Polygon::Polygon() {
    arr.setPrimitiveType(sf::PrimitiveType::LineStrip);
    lines.setPrimitiveType(sf::PrimitiveType::Lines);
    points.setPrimitiveType(sf::PrimitiveType::Quads);
}

void Polygon::addVertex(float x, float y) {
    if (canAdd(x, y)) {
        arr.append(sf::Vertex(sf::Vector2f(x, y)));
        int pointSize = 4;
        points.append(sf::Vertex(sf::Vector2f(x - pointSize, y - pointSize), sf::Color::Cyan));
        points.append(sf::Vertex(sf::Vector2f(x + pointSize, y - pointSize), sf::Color::Cyan));
        points.append(sf::Vertex(sf::Vector2f(x + pointSize, y + pointSize), sf::Color::Cyan));
        points.append(sf::Vertex(sf::Vector2f(x - pointSize, y + pointSize), sf::Color::Cyan));

    }
}

void Polygon::clear() {
    arr.clear();
    lines.clear();
    points.clear();
}

void Polygon::isCircled() {
    if (arr.getVertexCount() > 2 && canAdd(arr[0].position.x, arr[0].position.y)) {
        addVertex(arr[0].position.x, arr[0].position.y);
        update();
    }
}

bool Polygon::canAdd(float x, float y) {
    if (arr.getVertexCount() < 2)return true;
    if (arr[arr.getVertexCount() - 1].position == arr[0].position)return false;

    for (int i = 0; i < arr.getVertexCount() - 1; ++i) {
        if (intersects(arr[i].position, arr[i + 1].position, arr[arr.getVertexCount() - 1].position,
                       sf::Vector2f(x, y)))
            return false;
    }
    return true;
}

void Polygon::update() {

    int n = arr.getVertexCount() - 1, currVertex = 0;
    std::vector<int> prev(n), next(n), ang(n), curr(n);

    for (int i = 0; i < n; ++i) {
        prev[i] = (i - 1 + n) % n;
        next[i] = (n + i + 1) % n;
        curr[i] = i;
        if (arr[i].position.y <= arr[currVertex].position.y)
            currVertex = i;
    }

    if (getAngle(getVert(prev[currVertex]), getVert(currVertex), getVert(next[currVertex])) >= M_PI)
        std::swap(prev, next);

    for (int i = currVertex; i > -1; i = (next[i] == currVertex) ? -1 : next[i]) {
        ang[i] = getAngle(getVert(prev[i]), getVert(i), getVert(next[i]));
        //verts.insert({ang[i], i});
    }

    while (curr.size() > 3) {
        int pos = std::find_if(curr.begin(), curr.end(), [&ang, &n, &prev, &next, this](int ind) {
            if (ang[ind] < M_PI) {
                for (int i = 0; i < n; ++i) {
                    if (inTriangle(getVert(i), getVert(prev[ind]), getVert(ind), getVert(next[ind])))return false;
                }
                return true;
            }
            return false;
        }) - curr.begin();

        if (pos == n) {
            return;
        } else {
            int v = curr[pos], pr, nx;
            pr = prev[v];
            nx = next[v];
            addLine(pr, nx);
            next[pr] = nx;
            prev[nx] = pr;
            ang[pr] = getAngle(getVert(prev[pr]), getVert(pr), getVert(next[pr]));
            ang[nx] = getAngle(getVert(prev[nx]), getVert(nx), getVert(next[nx]));
            std::swap(curr[curr.size() - 1], curr[pos]);
            curr.pop_back();
        }
    }
}

sf::Vector2f Polygon::getVert(int ind) {
    return arr[(ind >= 0) ? (ind % (arr.getVertexCount() - 1)) : (arr.getVertexCount() - 1 -
                                                                  ((-ind) % (arr.getVertexCount() - 1)))].position;
}

void Polygon::addLine(int i, int j) {
    lines.append(sf::Vertex(getVert(i), sf::Color::Red));
    lines.append(sf::Vertex(getVert(j), sf::Color::Red));
}


