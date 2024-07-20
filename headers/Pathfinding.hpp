#ifndef Pathfinding_hpp
#define Pathfinding_hpp

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

float stepsize = 100.0f;

class Point {
public:
    float x, y;
    Point()
        : x(0)
        , y(0)
    { }
    Point(float x, float y)
        : x(x)
        , y(y)
    { }

    bool operator ==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator !=(const Point& other) const {
        return x != other.x || y != other.y;
    }

    bool operator <(const Point& other) const {
        return std::tie(x, y) < std::tie(other.x, other.y);
    }
};

namespace std {
    template < >
    struct hash < Point > {
        size_t operator()(const Point& p) const {
            return hash < float >()(p.x) ^ hash < float >()(p.y);
        }
    };
}

float heuristic(const Point& a, const Point& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

std::vector < Point > getNeighbors(const Point& p) {
    std::vector < Point > neighbors;

    neighbors.emplace_back(p.x - stepsize, p.y);
    neighbors.emplace_back(p.x + stepsize, p.y);
    neighbors.emplace_back(p.x, p.y - stepsize);
    neighbors.emplace_back(p.x, p.y + stepsize);

    neighbors.emplace_back(p.x-stepsize, p.y - stepsize);
    neighbors.emplace_back(p.x-stepsize, p.y + stepsize);
    neighbors.emplace_back(p.x+stepsize, p.y - stepsize);
    neighbors.emplace_back(p.x+stepsize, p.y + stepsize);
 
    return neighbors;
}

std::vector < Point > aStar(const Point& start, const Point& goal) {
    std::priority_queue < std::pair < float, Point >, std::vector < std::pair < float, Point >>, std::greater < >> openSet;
    std::unordered_map < Point, Point > cameFrom;
    std::unordered_map < Point, int > costSoFar;

    openSet.emplace(0, start);
    cameFrom[start] = start;
    costSoFar[start] = 0;

    while (!openSet.empty()) {
        Point current = openSet.top().second;
        openSet.pop();

        if (current == goal) {
            std::vector < Point > path;
            while (current != start) {
                path.push_back(current);
                current = cameFrom[current];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }
        else if (abs(current.x - goal.x) < stepsize && abs(current.y - goal.y) < stepsize)
        {
            // TO-DO
            Point next = Point(goal.x, goal.y);
            float newCost = costSoFar[current] + 1;
            if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next]) {
                costSoFar[next] = newCost;
                float priority = newCost + heuristic(next, goal);
                openSet.emplace(priority, next);
                cameFrom[next] = current;
            }
        }
        else {
            for (const Point& next : getNeighbors(current)) {
                float newCost = costSoFar[current] + 1;
                if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next]) {
                    costSoFar[next] = newCost;
                    float priority = newCost + heuristic(next, goal);
                    openSet.emplace(priority, next);
                    cameFrom[next] = current;
                }
            }
        }


    }

    return { }; // No path found
}

#endif