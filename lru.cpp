#include <map>
#include <stdio.h>

#include "general.h"

#define DEBUG 0
#define print_debug(fmt, ...) \
	do { if (DEBUG) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
							__LINE__, __func__, __VA_ARGS__); } while (0)
class Data {
	public:
		Data(int id, const char *str) : id(id), val(str) {}
		int id;
		const char *val;
};

struct ll {
	Data *d;
	struct ll *next;
	struct ll *prev;
};

struct ll *make_ll(Data *d) {
	struct ll *z = new struct ll;
	z->d = d;
	z->next = z->prev = NULL;
	return z;
}

struct ll *insert_after(struct ll *li, Data *d) {
	if (!li)
		return make_ll(d);
	else {
		li->next = make_ll(d);
		li->next->prev = li;
		return li->next;
	}
}

void delete_node(struct ll *node) {
	delete node->d;
	delete node;
}

class LRUCache {
	public:
		LRUCache(int m) : max(m) {}
		void put(Data *d);
		Data *get(int id);
		void print_cache();

	private:
		std::map<int, struct ll *> lrucache;
		struct ll *head = NULL;
		struct ll *tail = NULL;
		int size = 0;
		int max;
};

void LRUCache::put(Data *d) {
	print_debug("Inserting node %d\n", d->id);
	if (lrucache.find(d->id) != lrucache.end()) {
		print_debug("ID already exists: %d\n", d->id);
	}

	if (!head) {
		head = make_ll(d);
		tail = head;
		size++;
	} else {
		if (size < max) {
			size++;
		} else {
			struct ll *tmp = head->next;
			lrucache.erase(head->d->id);
			delete_node(head);
			head = tmp;
		}

		tail = insert_after(tail, d);
	}

	lrucache.insert({d->id, tail});
}

static void print_ll(struct ll *li) {
	while (li) {
		printf("%d ", li->d->id);
		li = li->next;
	}
	printf("\n");
}

Data *LRUCache::get(int id) {
	print_debug("Accessing node %d\n", id);

	std::map<int, struct ll *>::iterator it = lrucache.find(id);

	if (it == lrucache.end()) {
		print_debug("Node %d not found\n", it->second->d->id);
		return NULL;
	} else {
		struct ll *node = it->second;

		if (DEBUG) {
			printf("Before get: ");
			print_ll(head);
		}

		if (head == node) {
			head->next->prev = NULL;
			head = head->next;
		} else {
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}

		node->next = NULL;
		node->prev = tail;
		tail->next = node;
		tail = node;

		if (DEBUG) {
			printf("After get: ");
			print_ll(head);
		}

		return node->d;
	}
}

void LRUCache::print_cache() {
	for (auto n : lrucache) {
		printf("%d => %p", n.first, n.second);
		printf("\n");
	}
}

int main() {
	LRUCache c(5);
	c.put(new Data(1, "foo"));
	c.put(new Data(2, "bar"));
	c.get(1);
	c.put(new Data(3, "qux"));
	c.get(1);
	c.get(2);
	c.put(new Data(4, "cat"));
	c.put(new Data(5, "dog"));
	c.get(4);
	c.put(new Data(6, "yom"));
	c.get(1);
	c.put(new Data(7, "top"));

	c.print_cache();
}
