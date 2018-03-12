#include <stdio.h>
#include <vector>

typedef struct data {
	data(char c, int i) : dat(c), idx(i) {};
	char dat;
	int idx;
} data;

typedef struct dependency {
	dependency(data newer, data older) : newer(newer), older(older), next(nullptr) {};
	struct data newer;
	struct data older;
	dependency *next;
} dependency;

dependency *create_dep(data newer, data older) {
	dependency *z = new dependency(newer, older);
	return z;
}

#define MAXV 1000

typedef struct edgenode {
	edgenode(data d, edgenode *e) : y(d), next(e) {};
	data y;
	edgenode *next;
} edgenode;

typedef struct graph {
	edgenode *edges[MAXV];
	int nedges;
	int nvertices;
	bool directed;
	bool discovered[MAXV];
	bool processed[MAXV];
	bool valid_bo;
} graph;

bool find_build_order(std::vector<char> &build_order, data test1[], int items, dependency *deps);

static int count_deps(dependency *deps) {
	int num_deps = 0;

	while (deps) {
		num_deps++;
		deps = deps->next;
	}

	return num_deps;
}

static void init_graph(graph *g, bool directed) {
	g->nedges = g->nvertices = 0;
	g->directed = directed;

	g->valid_bo = true;

	for (int i = 0; i < MAXV; i++) {
		g->edges[i] = nullptr;
		g->discovered[i] = g->processed[i] = 0;
	}
}

static void insert_edge(graph *g, data newer, data older, bool directed) {
	edgenode *p = new edgenode(older, g->edges[newer.idx]);
	g->edges[newer.idx] = p;
	g->nedges++;
}


static graph *build_graph(bool directed, data datarr[], int datlen, dependency *deps) {
	graph *g = new graph;
	init_graph(g, directed);

	g->nvertices = datlen;

	int num_deps = count_deps(deps);

	while (deps) {
		insert_edge(g, deps->newer, deps->older, directed);
		deps = deps->next;
	}

	return g;
}

static void print_graph(graph *g, data datarr[], int datlen) {
	edgenode *p;

	for (int i = 0; i < g->nvertices; i++) {
		printf("%c: ", datarr[i].dat);
		p = g->edges[i];
		while (p) {
			printf(" %c", p->y.dat);
			p = p->next;
		}
		printf("\n");
	}
}

static void insert_dep(dependency **li, dependency *dep) {
	if (!(*li)) {
		*li = dep;
		return;
	} else {
		dependency *p = *li;
		while (p->next) {
			p = p->next;
		}
		p->next = dep;
	}
}

static void print_dependency(dependency *p) {
	printf("%c => %c\n", p->newer.dat, p->older.dat);
}

int main(void) {
	data test1[6] = {
		data('a', 0),
		data('b', 1),
		data('c', 2),
		data('d', 3),
		data('e', 4),
		data('f', 5),
	};

	dependency *deps = nullptr;

	insert_dep(&deps, create_dep(test1[3], test1[0])); // d->a
	insert_dep(&deps, create_dep(test1[1], test1[5])); // b->f
	//insert_dep(&deps, create_dep(test1[5], test1[2])); // f->c
	insert_dep(&deps, create_dep(test1[3], test1[1])); // d->b
	insert_dep(&deps, create_dep(test1[2], test1[3])); // c->d
	insert_dep(&deps, create_dep(test1[0], test1[5])); // a->f

	dependency *p = deps;

	std::vector<char> build_order;

	if (find_build_order(build_order, test1, 6, deps)) {
		for (auto bo : build_order) {
			printf("%c ", bo);
		}
		printf("\n");
	} else {
		printf("No valid build order.\n");
	}

	return 0;
}

static void dfs(graph *g, data v, std::vector<char> &build_order) {
	if (!(g->valid_bo))
		return;

	g->discovered[v.idx] = true;
	edgenode *p = g->edges[v.idx];

	while (p) {
		data y = p->y;
		if (!(g->discovered[y.idx])) {
			dfs(g, y, build_order);
		} else if (!(g->processed[y.idx])) {
			g->valid_bo = false;
			return;
		}
		if (!(g->valid_bo))
			return;
		p = p->next;
	}

	build_order.push_back(v.dat);

	g->processed[v.idx] = true;
}

bool find_build_order(std::vector<char> &build_order, data test1[], int items, dependency *deps) {
	graph *bog = build_graph(true, test1, items, deps);
	//print_graph(bog, test1, items);

	for (int i = 0; i < items; i++) {
		if (!(bog->valid_bo))
			return false;
		data curr_item = test1[i];
		if (!(bog->discovered[curr_item.idx])) {
			dfs(bog, curr_item, build_order);
		}
	}

	return true;
}

