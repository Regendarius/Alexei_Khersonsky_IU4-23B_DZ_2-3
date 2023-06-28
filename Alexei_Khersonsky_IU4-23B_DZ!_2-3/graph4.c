#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>


// Определение структуры для графа
typedef struct {
int **vertices; // Динамический массив смежности графа
int num_vertices; // Количество вершин в графе
} Graph;

// Функция создания графа
Graph createGraph(int num_vertices) {
Graph graph;
graph.num_vertices = num_vertices;
graph.vertices = (int **) malloc(num_vertices * sizeof(int *));
for (int i = 0; i < num_vertices; i++) {
graph.vertices[i] = (int *) calloc(num_vertices, sizeof(int));
}
return graph;
}

// Функция освобождения памяти графа
void freeGraph(Graph *graph) {
for (int i = 0; i < graph->num_vertices; i++) {
free(graph->vertices[i]);
}
free(graph->vertices);
}


// Функция вывода графа на экран
void printGraph(Graph *graph) {
// Обход всех вершин графа
for (int i = 0; i < graph->num_vertices; i++) {
// Вывод вершины и всех ее смежных вершин
printf("%d:", i);
for (int j = 0; j < graph->num_vertices; j++) {
if (graph->vertices[i][j]) {
printf(" %d", j);
}
}
printf("\n");
}
}

void visualizeGraph(Graph *graph) {
printf("  ");
for(int i=0; i < graph->num_vertices; i++) {
printf("%d ", i+1);
}
printf("\n");


for(int i=0; i < graph->num_vertices; i++) {
    printf("%d ", i+1);
    for(int j=0; j < graph->num_vertices; j++) {
        printf("%d ", graph->vertices[i][j]);
    
    }
    printf("\n");
}
}

void graph_union(Graph *graph1, Graph *graph2) {
int new_num_vertices = graph1->num_vertices + graph2->num_vertices;
Graph new_graph = createGraph(new_num_vertices);


// копируем вершины первого графа в новый граф
for (int i = 0; i < graph1->num_vertices; i++) {
    for (int j = 0; j < graph1->num_vertices; j++) {
        new_graph.vertices[i][j] = graph1->vertices[i][j];
    }
}

// копируем вершины второго графа в новый граф
for (int i = 0; i < graph2->num_vertices; i++) {
    for (int j = 0; j < graph2->num_vertices; j++) {
        new_graph.vertices[i + graph1->num_vertices][j + graph1->num_vertices] = graph2->vertices[i][j];
    }
}

// копируем рёбра первого графа в новый граф
for (int i = 0; i < graph1->num_vertices; i++) {
    for (int j = 0; j < graph1->num_vertices; j++) {
        if (graph1->vertices[i][j] != 0) {
            new_graph.vertices[i][j] = graph1->vertices[i][j];
        }
    }
}

// копируем рёбра второго графа в новый граф
for (int i = 0; i < graph2->num_vertices; i++) {
    for (int j = 0; j < graph2->num_vertices; j++) {
        if (graph2->vertices[i][j] != 0) {
            new_graph.vertices[i + graph1->num_vertices][j + graph1->num_vertices] = graph2->vertices[i][j];
        }
    }
}

// освобождаем память 
for (int i = 0; i < graph1->num_vertices; i++) {
    free(graph1->vertices[i]);
}
free(graph1->vertices);

// возвращаем новый граф
*graph1 = new_graph;
}

// Функция считывания графа из файла
Graph readGraphFromFile(const char *filename) {
FILE *file = fopen(filename, "r");
if (!file) {
printf("Error opening file %s\n", filename);
exit(EXIT_FAILURE);
}

int num_vertices;
fscanf(file, "%d", &num_vertices);

Graph graph = createGraph(num_vertices);
int from, to;
while (fscanf(file, "%d %d", &from, &to) == 2) {
graph.vertices[from][to] = 1;
graph.vertices[to][from] = 1;
}

fclose(file);
return graph;
}


// Главная функция программы
int main() {
// Создание двух графов
/*Graph graph1 = createGraph(4);
graph1.vertices[0][1] = 1;
graph1.vertices[0][2] = 1;
graph1.vertices[1][0] = 1;
graph1.vertices[1][2] = 1;
graph1.vertices[2][0] = 1;
graph1.vertices[2][1] = 1;
graph1.vertices[2][3] = 1;
graph1.vertices[3][2] = 1;

*/ 
Graph graph1 = readGraphFromFile("graph1.txt");

Graph graph2 = createGraph(3);
graph2.vertices[0][1] = 1;
graph2.vertices[1][0] = 1;
graph2.vertices[1][2] = 1;
graph2.vertices[2][1] = 1;

// Объединение графов и вывод результата
visualizeGraph(&graph1);
visualizeGraph(&graph2);

graph_union(&graph1,&graph2);
visualizeGraph(&graph1);


// Освобождение памяти
freeGraph(&graph1);
freeGraph(&graph2);

return 0;
}