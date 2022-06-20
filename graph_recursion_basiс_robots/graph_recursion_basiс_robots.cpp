#include <iostream>
#include <vector>
using namespace std;

struct Robot
{
public:
    int start_point;
    int prev;
    int moves;
    vector<int> count;
    Robot()
    {
        prev = -1;
        start_point = -1;
        moves = 0;
    }
};

void traversal(Robot robots, int** graph, int n, vector<vector<int>>& roads, int start, int prev)
{
    for (int j = 0; j < n; j++)
    {
        if (robots.count[j] < 2 && graph[robots.start_point][j] == 1 && robots.start_point != j && robots.prev != j)
        {
            start = robots.start_point;
            prev = robots.prev;
            robots.prev = robots.start_point;
            robots.start_point = j;
            robots.moves++;
            robots.count[j]++;
            if (robots.moves % 2 == 0 && robots.moves < roads[j][0])
                roads[j][0] = robots.moves;
            else if (robots.moves % 2 == 1 && robots.moves < roads[j][1])
                roads[j][1] = robots.moves;
            traversal(robots, graph, n, roads, -1, -1);
            robots.start_point = start;
            robots.prev = prev;
            robots.moves--;
            robots.count[j]--;
        }
    }
    return;
}

void print(vector<vector<int>> arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < arr[i].size(); j++)
            cout << arr[i][j] << " ";
        cout << endl;
    }
}

void main()
{
    setlocale(LC_ALL, "rus");
    int n = -1, num, num_roads, time = 51;
    vector<pair <int, int>> points;

    cout << "Введите количество дорог: ";
    cin >> num_roads;

    points.resize(num_roads);

    for (int i = 0; i < num_roads; i++)
    {
        cout << "Введите 2 пункта, между которыми есть дорога: ";
        cin >> points[i].first >> points[i].second;
        points[i].first--;
        points[i].second--;
        if (points[i].first > points[i].second && points[i].first > n) n = points[i].first;
        else if (points[i].second > n) n = points[i].second;
    }

    n++;
    int** graph = new int* [n];


    for (int i = 0; i < n; i++)
        graph[i] = new int[n];


    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    for (int i = 0; i < n; i++)
        graph[i][i] = 1;

    for (int i = 0; i < num_roads; i++)
    {
        graph[points[i].first][points[i].second] = 1;
        graph[points[i].second][points[i].first] = 1;

    }


    cout << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << graph[i][j] << " ";
        cout << endl;
    }
    cout << endl;


    cout << "Введите количество роботов (2 или 3): ";
    cin >> num;
    vector<Robot> robots(num); //вектор, содержащий роботов
    vector<vector<vector<int>>> roads(num); //вектор, содержащий ходы для каждого робота

    for (int i = 0; i < num; i++)
    {
        roads[i].resize(n);
        for (int j = 0; j < n; j++)
        {
            roads[i][j].resize(2);
        }
    }

    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < n; j++)
        {
            roads[i][j][0] = 51;
            roads[i][j][1] = 51;
        }
    }


    for (int i = 0; i < num; i++)
    {
        robots[i].count.resize(n);
        cout << "Введите начальное положение робота " << i + 1 << ": ";
        cin >> robots[i].start_point;
        robots[i].start_point--;
        for (int j = 0; j < n; j++)
        {
            robots[i].count[j] = 0;
        }
        robots[i].count[robots[i].start_point] = 1;
        roads[i][robots[i].start_point][0] = 0;
    }


    for (int i = 0; i < num; i++)
        traversal(robots[i], graph, n, roads[i], -1, -1);
    for (int l = 0; l < n; l++)
    {
        if (roads[0][l][0] == roads[1][l][0] && roads[0][l][0] < time)
        {
            if (num == 2) time = roads[0][l][0];
            else if (roads[0][l][0] == roads[2][l][0]) time = roads[0][l][0];
        }
        if (roads[0][l][1] == roads[1][l][1] && roads[0][l][1] < time)
        {
            if (num == 2) time = roads[0][l][1];
            else if (roads[0][l][1] == roads[2][l][1]) time = roads[0][l][1];
        }
    }
    if (time == 51) cout << "\nРоботы не могут встретиться ни в одном пункте одновременно\n";
    else cout << "\nМинимальное время, за которое роботы одновременно могут встретиться в одном пункте, равно " << time << "\n";
    return;
}


