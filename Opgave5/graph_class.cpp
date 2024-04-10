#include "graph_class.h"
#include <queue>
#include <climits>
#include <iomanip>

using namespace std;

void Graph::grid_add_wall(int x1, int y1, int x2, int y2)
{
	for (int x = x1; x <= x2; ++x)
	{
		for (int y = y1; y <= y2; ++y)
		{
			grid_walls.insert(GridLocation{x, y});
		}
	}
}

void Graph::grid_draw(unordered_map<GridLocation, double> *distances,
					  unordered_map<GridLocation, GridLocation> *point_to,
					  vector<GridLocation> *path,
					  GridLocation *start,
					  GridLocation *goal)
{
	const int field_width = 3;
	cout << string(field_width * width, '_') << '\n';
	for (int y = 0; y != height; ++y)
	{
		for (int x = 0; x != width; ++x)
		{
			GridLocation id{x, y};
			if (grid_walls.find(id) != grid_walls.end())
			{
				cout << string(field_width, '#');
			}
			else if (start && id == *start)
			{
				cout << " S ";
			}
			else if (goal && id == *goal)
			{
				cout << " T ";
			}
			else if (path != nullptr && find(path->begin(), path->end(), id) != path->end())
			{
				cout << " @ ";
			}
			else if (point_to != nullptr && point_to->count(id))
			{
				GridLocation next = (*point_to)[id];
				if (next.x == x + 1)
				{
					cout << " > ";
				}
				else if (next.x == x - 1)
				{
					cout << " < ";
				}
				else if (next.y == y + 1)
				{
					cout << " v ";
				}
				else if (next.y == y - 1)
				{
					cout << " ^ ";
				}
				else
				{
					cout << " * ";
				}
			}
			else if (distances != nullptr && distances->count(id))
			{
				cout << ' ' << left << setw(field_width - 1) << (*distances)[id];
			}
			else
			{
				cout << " . ";
			}
		}
		cout << '\n';
	}
	cout << string(field_width * width, '~') << '\n';
}

vector<GridLocation> Graph::grid_reconstruct_path(
	GridLocation start, GridLocation goal,
	unordered_map<GridLocation, GridLocation> came_from)
{
	vector<GridLocation> path;

	// TO BE IMPLEMENTED

	return path;
}

void Graph::a_star(GridLocation start, GridLocation goal,
				   unordered_map<GridLocation, GridLocation> &came_from,
				   unordered_map<GridLocation, double> &cost_so_far)
{
	// Priority queue for nodes to visit
	std::priority_queue<std::pair<double, GridLocation>> frontier;
	frontier.push(std::make_pair(0, start));

	// Initialize starting node
	came_from[start] = start;
	cost_so_far[start] = 0;

	while (!frontier.empty())
	{
		// Get the next node to visit
		GridLocation current = frontier.top().second;
		frontier.pop();

		// If we've reached the goal, we're done
		if (current == goal)
		{
			break;
		}

		// Otherwise, visit all neighbors
		for (auto n : grid_neighbors(current))
		{
			double new_cost = cost_so_far[current] + 1;
			if (cost_so_far.find(n) == cost_so_far.end() || new_cost < cost_so_far[n])
			{
				cost_so_far[n] = new_cost;
				double priority = new_cost + heuristic(n, goal);
				frontier.push(std::make_pair(-priority, n));
				came_from[n] = current;
			}
		}
	}
}
