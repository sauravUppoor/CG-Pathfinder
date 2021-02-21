#include<conio.h>
#include<iostream.h>
#include<graphics.h>
#include<dos.h>
#include<math.h>
#include<stdlib.h>
#include<alloc.h>
#include<stdio.h>
#include<dos.h>

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

const int MAXN = 10;
const int INF = 1000;


int adj[MAXN][MAXN];
int vis[MAXN];
int dist[MAXN], pred[MAXN];

int x[MAXN], y[MAXN];

void table(int n,int a[],int b[]){
    settextstyle(0, 0, 1);
	int i=0;
	char str[3];
	char str1[3];
	char str2[3];
    rectangle(450,20,600,40*(n + 1)+20);
    line(500,20,500,40*(n + 1)+20);
    line(550,20,550,40*(n + 1)+20);
    outtextxy(475,30,"v");
    outtextxy(515,30,"d(v)");
    outtextxy(560,30,"u");

    while(i<=n){
       sprintf(str,"%d",i+1);
       sprintf(str1,"%d",dist[i+1]);
       sprintf(str2,"%d",pred[i+1]);

      // if(str1 == "1000") str1 = "INF";
      // if(str2 == "1000") str2 = "INF";
       if(i<n){
            outtextxy(475,80+40*i,str);
            if(dist[i+1] != 1000) outtextxy(525,80+40*i,str1);
            else outtextxy(525, 80 + 40*i, "INF");
            outtextxy(575,80+40*i,str2);

       }
       line(450,20+40*(i+1),600,20+40*(i+1));
       i++;
    }
}

void nodeVal(int i) {
    char nval[3];
    sprintf(nval, "%d", i);
    settextstyle(3, 0, 2);
    setcolor(BLACK);
    outtextxy(x[i]-10, y[i]-10, nval);
    setcolor(WHITE);
}

void edgeVal(int i, int j) {
    char nval[3];
    sprintf(nval, "%d", adj[i][j]);
    settextstyle(3, 0, 2);
    //setcolor(YELLOW);
    outtextxy((x[i] + x[j])/2 + 10 , (y[i] + y[j])/2 - 30, nval);
    setcolor(WHITE);
}

void sourceDestination(int source, int dest) {
    settextstyle(6, 0, 2);
    char s[3], d[3];
    sprintf(s, "%d", source);
    sprintf(d, "%d", dest);
    outtextxy(4, 350, "SOURCE  ");
    setcolor(GREEN);
    outtextxy(75, 350, s);
    setcolor(WHITE);
    outtextxy(4, 370, "DESTINATION  ");
    setcolor(GREEN);
    outtextxy(125, 370, d);
    setcolor(WHITE);
}

void printSource(int source) {
    settextstyle(6, 0, 2);
    char s[3];
    sprintf(s, "%d", source);
    outtextxy(4, 350, "SOURCE  ");
    setcolor(GREEN);
    outtextxy(75, 350, s);
    setcolor(WHITE);
}

void boxes() {
    settextstyle(0, 0, 1);
    outtextxy(4,4,"GRAPH");
	outtextxy(430,4,"TABLE");
	outtextxy(4,330,"PRINTING SECTION");
	rectangle(2,2,420,320);
	rectangle(426,2,635,320);
	rectangle(2,325,635,475);
}

void processing(int u, int v, int status) {
    char s[3], d[3];
    sprintf(s, "%d", u);
    sprintf(d, "%d", v);
    settextstyle(6, 0, 2);
    setcolor(RED);  outtextxy(180, 400, s);
    setcolor(WHITE); outtextxy(200, 400, "-->");
    setcolor(BLUE); outtextxy(250, 400, d);
    if(status == 0) {
        setcolor(WHITE); outtextxy(270, 400, "PROCESSING");
    }
    else {
        setcolor(GREEN); outtextxy(270, 400, "RELAXED!!!");
    }
    setcolor(WHITE);
}

void printPath(int path[], int pp, int length) {
    settextstyle(6, 0, 2);
    outtextxy(4, 400, "PATH FOUND");
    int cnt = 0;
    for(int i = length - 1; i >= pp; --i, cnt += 50) {
        char s[3];
        sprintf(s, "%d", path[i]);
        setcolor(GREEN);
        outtextxy(150 + cnt, 400, s);
        setcolor(WHITE);
        if(i != pp) outtextxy(180 + cnt, 400, "-");
    }

}

int main() {



    memset(vis, 0, sizeof(vis));
    memset(pred, -1, sizeof(pred));

    int n, m, gd = DETECT, gm;
    int i, j;
    initgraph(&gd,&gm,"..\\BGI");

    settextstyle(8,0,5);

	// print text at coordinate x,y;
    outtextxy(100,200,"DIJKSTRA VISUALISER");
    settextstyle(0,0,0);
    outtextxy(200,300,"PRINT ANY KEY TO CONTINUE");
    getch();
    clearviewport();

    outtextxy(100, 150, "Enter the number of cities: ");
    gotoxy(15, 11);
    cin >> n;
    outtextxy(100, 200, "Enter number of bidirectional paths between these cities: ");
    gotoxy(15, 15);
    cin >> m;

    for(i = 1; i <= n; ++i) dist[i] = INF;

    for(i = 0; i < n; ++i) {
        int xc, yc;

        outtextxy(100, 240 + 17*i, "Enter the coordinates of this city: ");
        gotoxy(50, 16 + i);
        gotoxy(50, 16 + i);
        cin >> xc >> yc;
        x[i + 1] = xc;  y[i + 1] = yc;

    }
    gotoxy(10, 10);
    clearviewport();
    //Taking in Adj Matrix. If no edge present value stored is -1
    cout << "Enter the Adjacency Matrix of weights for the cities (-1 for no edge): \n";

    for(i = 1; i <= n; ++i) {
        gotoxy(10, 12 + i);
        for(j = 1; j <= n; ++j) {
            cin >> adj[i][j];
        }
    }
    clrscr();

    //Taking input for Source
    int source;
    clearviewport();
    gotoxy(15, 10);
    cout << "Enter the source node: ";
    gotoxy(15, 12);
    cin >> source;
    clearviewport();

    printSource(source);
    //Plotting Nodes with source node as green
    for(i = 1; i <= n; ++i) {
        textcolor(BLACK);
        if(i == source) setfillstyle(SOLID_FILL, GREEN);
        else setfillstyle(SOLID_FILL, WHITE);
        circle(x[i], y[i], 20);
        floodfill(x[i] + 1, y[i] + 1, 15);

        nodeVal(i);
    }

    //Plotting edges
    for(i = 1; i <= n; ++i) {
        for(j = 1; j <= n; ++j) {
            if(adj[i][j] != -1) {
                    setlinestyle(1, 0, 3);
                line(x[i], y[i], x[j], y[j]);
                edgeVal(i, j);
            }
        }
    }
    setlinestyle(0, 0, 1);
    //table(n, dist, pred);
    boxes();
    getch();

    //********Dijkstra Algo**********

    dist[source] = 0;
    int in_queue = 0; //Keeps track of all the nodes in queue
    int queue_weight[MAXN], queue_idx[MAXN]; //Manual creation of queue of pair using to arrays.

    //One for weight and corresponding other for its idx. Initially both are -1 to show nnot filled.
    for(i = 0; i <= m; ++i) {
        queue_weight[i] = -1;
        queue_idx[i] = -1;
    }

    //Inserting in queue, here, takes linear time to search for empty position in queue
    for(i = 0; i <= m; ++i) {
        if(queue_weight[i] == -1) {
            queue_weight[i] = dist[source];
            queue_idx[i] = source;
            in_queue++;
            break;
        }
    }

    while(in_queue != 0) {
        //cout << in_queue << "\n";

        //Search for minimum weight edge from the queue and dequeue it.
        int minn = INF, idx;
        for(i = 0; i <= m; ++i) {
            if(queue_weight[i] != -1 && queue_weight[i] < minn) {
            minn = queue_weight[i];
            idx = i;
            }
        }

        int cur = queue_idx[idx];
        queue_weight[idx] = -1;
        queue_idx[idx] = -1;
        in_queue--;

        for(i = 1; i <= n; ++i) {
            if(adj[cur][i] != -1) {
                int b = i;
                int w = adj[cur][i];
                int ii, jj;

                boxes();
                printSource(source);
                //Print graph and show current edge being processed (red colour)
                for(ii = 1; ii <= n; ++ii) {
                    textcolor(BLACK);
                    if(ii == cur) setfillstyle(SOLID_FILL, RED);
                    else if(ii == b) setfillstyle(SOLID_FILL, BLUE);
                    else setfillstyle(SOLID_FILL, WHITE);
                    circle(x[ii], y[ii], 20);
                    floodfill(x[ii] + 1, y[ii] + 1, 15);
                    nodeVal(ii);
                }

                //Plotting edges
                for(ii = 1; ii <= n; ++ii) {
                    for(jj = 1; jj <= n; ++jj) {
                        if(adj[ii][jj] != -1) {
                            if((ii == cur && jj == b) || (ii == b && jj == cur)) {
                                setlinestyle(0, 0, 3);
                            }
                            else {
                                setlinestyle(1, 0, 3);
                            }
                            line(x[ii], y[ii], x[jj], y[jj]);
                            edgeVal(ii, jj);
                        }
                    }
                }
                setlinestyle(0, 0, 1);
                processing(cur, b, 0);
                table(n, dist, pred);
                getch();
                clearviewport();
                //Relaxation
                //cout << dist[cur] + w << " " << dist[b] << "\n";
                if(dist[cur] + w < dist[b]) {
                    dist[b] = dist[cur] + w;
                    pred[b] = cur;

                    //Print graph and show edge relaxation (orange colour) + Update the table(TODO)
                    boxes();
                    printSource(source);
                    for(ii = 1; ii <= n; ++ii) {
                        textcolor(BLACK);
                        if(ii == cur) setfillstyle(SOLID_FILL, RED);
                        else if(ii == b) setfillstyle(SOLID_FILL, BLUE);
                        else setfillstyle(SOLID_FILL, WHITE);
                        circle(x[ii], y[ii], 20);
                        floodfill(x[ii] + 1, y[ii] + 1, 15);
                        nodeVal(ii);
                    }

                    //Plotting edges
                    for(ii = 1; ii <= n; ++ii) {
                        for(jj = 1; jj <= n; ++jj) {
                            if(adj[ii][jj] != -1) {
                                if((ii == cur && jj == b) || (ii == b && jj == cur)) {
                                    setlinestyle(0, 0, 3);
                                    setcolor(LIGHTGREEN);
                                }
                                else {
                                    setlinestyle(1, 0, 3);
                                    setcolor(WHITE);
                                }
                                line(x[ii], y[ii], x[jj], y[jj]);
                                edgeVal(ii, jj);
                            }
                        }
                    }
                    setlinestyle(0, 0, 1);
                    processing(cur, b, 1);
                    table(n, dist, pred);
                    getch();
                    clearviewport();

                    //Insert the node b to queue
                    for(j = 0; j <= m; ++j) {
                        if(queue_weight[j] == -1) {
                            queue_weight[j] = dist[b];
                            queue_idx[j] = b;
                            in_queue++;
                            break;
                        }
                    }
                }

            }
        }
    }
    clearviewport();

    //Dijkstra Done. Now restore the path by taking input the destination node.
    int destination;
    gotoxy(15,10);
    cout << "Enter your destination node: \n";
    gotoxy(15,12);
    cin >> destination;

    clearviewport();

    //Printing the path using the predecessor (pred) array
    int path[MAXN];
    int length = 0;

    //We are considering that path always exists. Incase to check if it doesn't use a hashmap to check
    //if we would reach the same node twice which means cycle is formed and this its not the shortest path
    //and hence no path exists.
    gotoxy(0,0);

    for(i = destination; i != source; i = pred[i]) path[length++] = i;
    path[length++] = source;

    /*for(i = length-1; i >= 0; --i) cout << path[i] << " ";
    getch();*/

    //First display initial status of graph
    boxes();
    sourceDestination(source, destination);
    for(i = 1; i <= n; ++i) {
        textcolor(BLACK);
        if(i == source) setfillstyle(SOLID_FILL, GREEN);
        else setfillstyle(SOLID_FILL, WHITE);
        circle(x[i], y[i], 20);
        floodfill(x[i] + 1, y[i] + 1, 15);

        nodeVal(i);
    }

    //Plotting edges
    for(i = 1; i <= n; ++i) {
        for(j = 1; j <= n; ++j) {
            if(adj[i][j] != -1) {
                    setlinestyle(1, 0, 3);
                line(x[i], y[i], x[j], y[j]);
                edgeVal(i, j);
            }
        }
    }
    setlinestyle(0, 0, 1);
    table(n, dist, pred);
    getch();
    clearviewport();
    for(int pp = length - 2; pp >= 0; --pp) {
        boxes();
        sourceDestination(source, destination);
        setlinestyle(0, 0, 3);
        //In each iteration change the colour of the prevoious and current nodes in the path[] and edge between them to green.
        //Plotting Nodes with source node as green
        for(i = 1; i <= n; ++i) {
            textcolor(BLACK);
            int ok = 0;

            for(j = length - 1; j >= pp; --j) {
                if(path[j] == i) {
                    ok = 1;
                    break;
                }
            }
            if(ok == 1) setfillstyle(SOLID_FILL, GREEN);
            else setfillstyle(SOLID_FILL, WHITE);
            circle(x[i], y[i], 20);
            floodfill(x[i] + 1, y[i] + 1, 15);

            nodeVal(i);
        }


        //Plotting edges

        for(i = 1; i <= n; ++i) {
            for(j = 1; j <= n; ++j) {
                int first = 0;
                int second = 0;
                if(adj[i][j] != -1) {

                    for(int m = length - 2; m >= pp; --m) {
                        first = 0;
                        second = 0;
                        if((path[m + 1] == i && path[m] == j) || (path[m] == i && path[m + 1] == j)) {
                            first = 1;
                            second = 1;
                        }
                        if(first == 1 && second == 1) {
                            setlinestyle(0, 0, 3);
                            setcolor(GREEN);
                            line(x[i], y[i], x[j], y[j]);
                            edgeVal(i, j);
                            break;
                        }
                        else {
                            setlinestyle(1, 0, 3);
                            setcolor(WHITE);
                            line(x[i], y[i], x[j], y[j]);
                            edgeVal(i, j);
                        }


                    }
                }
            }
            setlinestyle(0, 0, 1);
            table(n, dist, pred);
        }
        printPath(path, pp, length);
        getch();
        clearviewport();
    }

    return 0;
}
