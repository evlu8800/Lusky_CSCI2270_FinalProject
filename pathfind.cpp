//Evan Lusky
//CSCI 2270
//Final Project

#include<iostream>
#include<vector>
#include<queue>
#include<fstream>
# define INT_MAX    2000000

using namespace std;
struct adjvertex;

struct vertex
{
    int posx;
    int posy;
    vector<adjvertex> adjacent;
    bool issolved;
    int distance;
    vertex *parent;
};

struct adjvertex
{
    vertex *v;
    int weight;
    adjvertex(vertex *x, int w)
    {
        v = x;
        weight = w;
    }
};

class graph
{
    public:
    vector<vertex*> vertices; //pointers?
    int x;
    int y;
    vertex * vstack[1000];
    int top;
    graph();
    void connect();
    void createmap();
    void dijkstra(int startx, int starty, int endx, int endy);
    void stackpush(vertex *);
    vertex * stackpop();

};

graph::graph()
{
    x = 640;
    y = 480;
    top = 0;
    vertex * fix = new vertex;
    vertices.push_back(fix);

    for (int i=1; i<=x; i++)
    {
        for (int j=1; j<=y; j++)
        {
            int coord = ((i-1)*480) + j;
            vertex * temp = new vertex;
            temp->posx = i;
            temp->posy = j;
            temp->issolved = false;
            temp->distance = INT_MAX;
            vertices.push_back(temp);
            //cout << "MADE!" << coord << endl;
        }
    }


}
void graph::stackpush(vertex * vert)
{
    if (top == 999)
    {
        cout << "Stack Full" << endl;
        return;
    }
    else
    {
        vstack[top] = vert;
        top++;
    }
}
vertex * graph::stackpop()
{
    if (top == 0)
    {
        cout << "Stack Empty" << endl;
        return nullptr;
    }
    else
    {
        vertex * temp = vstack[top-1];
        top--;
        return temp;
    }
}
void graph::connect()
{
    for (int i=1; i<=x; i++)
    {
        for (int j=1; j<=y; j++)
        {
            int coord = ((i-1)*480) + j;
            //cout << "check" << coord << endl;
            if (i==1 && j==1)
            {
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord+1], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord+480], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord+481], 1));
            }
            else if (i==1 && j==480)
            {
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord-1], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord+480], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord+479], 1));
            }
            else if (i==640 && j==1)
            {
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord+1], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord-480], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord-481], 1));
            }
            else if (i==640 && j==480)
            {
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord-1], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord-480], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord-479], 1));
            }
            else if (i==1)
            {
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord+1], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord-1], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord+480], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord+481], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord+479], 1));
            }
            else if (i==640)
            {
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord-1], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord+1], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord-480], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord-479], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord-481], 1));
            }
            else if (j==1)
            {
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord+1], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord-480], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord+480], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord+481], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord-479], 1));
            }
            else if (j==480)
            {
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord-1], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord-480], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord+480], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord-479], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord+479], 1));
            }
            else
            {
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord+1], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord-1], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord+480], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord-480], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord+479], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord-479], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord+481], 1));
                vertices[coord]->adjacent.push_back(adjvertex(vertices[coord-481], 1));
            }
        }
    }
}

void graph::createmap()
{
    for (int i=0; i<300; i++) // adjust for obstacles
    {
        for (int k=0; k<vertices[2000 + i]->adjacent.size(); k++)
        {
            //cout << "check2222" << endl;
            vertices[2000+i]->adjacent[k].weight = 500000;
        }
    }
}

void graph::dijkstra(int startx, int starty, int endx, int endy)
{
    vertex *start = vertices[((startx-1)*480)+starty];
    vertex *finish = vertices[((endx-1)*480)+endy];
    start->issolved = true;
    start->distance = 0;
    start->parent = nullptr;
    vector<vertex*> solved;
    solved.push_back(start);
    int minDistance, dist;
    vertex * solvedV = nullptr;
    vertex * s = nullptr;
    vertex * parent = nullptr;
    while (!solved.empty() && finish->issolved != true)
    {

        for (int i=0; i<solved.size(); i++)
        {
            cout << solved[i]->posx << " " << solved[i]->posy << endl;
        }
        minDistance = INT_MAX;
        solvedV = nullptr;
        for(int i=0; i<solved.size(); i++)
        {
            //cout << solved[0]->distance << flush;
            s = solved[i];
            for (int j=0; j < s->adjacent.size(); j++)
            {
                if (!s->adjacent[j].v->issolved)
                {
                    dist = s->distance + s->adjacent[j].weight;
                    if (dist < minDistance)
                    {
                        solvedV = s->adjacent[j].v;
                        minDistance = dist;
                        parent = s;
                    }
                }
            }
        }
        solvedV->distance = minDistance;
        solvedV->parent = parent;
        solvedV->issolved = true;
        solved.push_back(solvedV);
    }
    vertex * traverse = finish;
    cout << "ANSWER" << endl;
    while (traverse != nullptr)
    {
        //cout << traverse->posx << " " << traverse->posy << endl;
        stackpush(traverse);
        traverse = traverse->parent;
    }
    while (top != 0)
    {
        traverse = stackpop();
        cout << traverse->posx << " " << traverse->posy << endl;
    }

}

int main()
{
    int sx, sy, ex, ey;
    sx = 1;
    sy = 1;
    ex = 30;
    ey = 50;
    //ofstream outfile("connects.txt");
    graph level;
    level.connect();
    level.createmap();
    /*for (int i=1; i < 10000; i++)
    {
        outfile << level.vertices[i]->posx << " " << level.vertices[i]->posy << endl;
        for (int j=0; j<level.vertices[i]->adjacent.size(); j++)
            outfile << "   " << level.vertices[i]->adjacent[j].v->posx << " " << level.vertices[i]->adjacent[j].v->posy << endl;
    }*/
    level.dijkstra(sx, sy, ex, ey);
    return 0;
}

