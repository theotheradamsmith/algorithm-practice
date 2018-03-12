#include <stdio.h>
#include <time.h>

#include <list>

class Beast {
	public:
		Beast(const char *name) : name(name) {}
		const char *getName();
		int getET();
		void setET(int t);

	private:
		const char *name;
		int entry_time;
};

class Dog : public Beast {
	public:
		Dog(const char *name) : Beast(name) {}
};

class Cat : public Beast {
	public:
		Cat(const char *name) : Beast(name) {}
};

class AnimalShelter {
	public:
		AnimalShelter() {}
		void enqueue(Dog *d);
		void enqueue(Cat *c);
		Beast *dequeueAny();
		Dog *dequeueDog();
		Cat *dequeueCat();
		void printResidents();

	private:
		int earliest_dog = 0; // longest staying dog
		int earliest_cat = 0; // longest staying cat
		int index = 1;            // entry time tracker

		std::list<Dog *> dogs;
		std::list<Cat *> cats;
};

const char *Beast::getName() {
	return name;
}

int Beast::getET() {
	return entry_time;
}

void Beast::setET(int t) {
	entry_time = t;
}

void AnimalShelter::enqueue(Dog *d) {
	d->setET(index++);

	if (!earliest_dog) {
		earliest_dog = d->getET();
	}

	dogs.push_front(d);
}

void AnimalShelter::enqueue(Cat *c) {
	c->setET(index++);

	if (!earliest_cat) {
		earliest_cat = c->getET();
	}

	cats.push_front(c);
}

Dog *AnimalShelter::dequeueDog() {
	if (dogs.empty())
		return nullptr;

	Dog *d = dogs.back();
	dogs.pop_back();
	earliest_dog = dogs.empty() ? 0 : dogs.back()->getET();
	return d;
}

Cat *AnimalShelter::dequeueCat() {
	if (cats.empty())
		return nullptr;

	Cat *c = cats.back();
	cats.pop_back();
	earliest_cat = cats.empty() ? 0 : cats.back()->getET();
	return c;
}

Beast *AnimalShelter::dequeueAny() {
	if (!earliest_dog) {
		return dequeueCat();
	}

	if (!earliest_cat) {
		return dequeueDog();
	}

	if (earliest_dog < earliest_cat) {
		return dequeueDog();
	} else if (earliest_cat < earliest_dog) {
		return dequeueCat();
	} else {
		return nullptr;
	}
}

void AnimalShelter::printResidents() {
	printf("Earliest Dog: %d\nEarliest Cat: %d\n\n", earliest_dog, earliest_cat);

	printf("Cats:\n");
	for (auto c : cats) {
		printf("\t%s: %d\n", c->getName(), c->getET());
	}

	printf("\n");

	printf("Dogs: \n");
	for (auto d : dogs) {
		printf("\t%s: %d\n", d->getName(), d->getET());
	}

	printf("\n");
}

int main() {
	AnimalShelter my_shelter;

	const char *cats[4] = {"BeatriceCat", "SandyCat", "LilyCat", "DaintyCat"};
	const char *dogs[4] = {"RufusDog", "PetrosDog", "OliverDog", "MartinDog"};

	my_shelter.enqueue(new Dog(dogs[0]));
	my_shelter.enqueue(new Dog(dogs[1]));
	my_shelter.enqueue(new Cat(cats[0]));

	my_shelter.printResidents();

	my_shelter.enqueue(new Dog(dogs[2]));
	my_shelter.enqueue(new Cat(cats[1]));
	my_shelter.enqueue(new Dog(dogs[3]));
	my_shelter.enqueue(new Cat(cats[2]));
	my_shelter.enqueue(new Cat(cats[3]));
	my_shelter.printResidents();

	printf("Dequeuing any: %s\n", my_shelter.dequeueAny()->getName());
	printf("Dequeuing any: %s\n", my_shelter.dequeueAny()->getName());
	printf("Dequeuing any: %s\n", my_shelter.dequeueAny()->getName());
	my_shelter.printResidents();

	printf("Dequeuing cat: %s\n", my_shelter.dequeueCat()->getName());
	printf("Dequeuing dog: %s\n", my_shelter.dequeueDog()->getName());
	my_shelter.printResidents();

	my_shelter.enqueue(new Dog("ArnoldDog"));
	my_shelter.enqueue(new Cat("DonnaCat"));
	my_shelter.enqueue(new Dog("JulienDog"));

	printf("Dequeuing any: %s\n", my_shelter.dequeueAny()->getName());
	my_shelter.printResidents();

	printf("Dequeuing any: %s\n", my_shelter.dequeueAny()->getName());
	printf("Dequeuing any: %s\n", my_shelter.dequeueAny()->getName());
	my_shelter.printResidents();
	return 0;
}
