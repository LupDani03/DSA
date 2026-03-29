#include <cstdint>
#include <iostream>

class SpecialContainer {
    std::uint32_t capacity;
    std::uint32_t size;
    int *array;

    void resize() {
        this->capacity = capacity * 2;

        // alocam dublu de memorie
        int *temp_array = new int[capacity];

        // intializam totul ca "neocupat"
        for (std::uint32_t i = 0; i < capacity; i++) {
            temp_array[i] = -1;
        }

        // parcurgem tabelul vechi
        for (std::uint32_t i = 0; i < capacity / 2; i++) {

            // daca e nealocat locul, trecem peste
            if (array[i] == -1) {
                continue; // era break.. oboseala asta
            }

            // calculam pozitia in tabelul nou
            auto y = hash(array[i]);

            // linear probing in caz de coliziune
            if (temp_array[y] != -1) {

                for (std::uint32_t j = y; j < capacity; j++) {

                    if (temp_array[j] == -1) {
                        y = j;
                        break;
                    }
                }
            }

            std::cout << "rehash " << array[i] << " " << y << "\n";

            // reatribuire
            temp_array[y] = array[i];
        }

        // dealocam memoria veche
        delete[] array;
        // pointerul intern se uita catre memoria noua
        array = temp_array;
    }

    std::uint32_t hash(int x) {
        return static_cast<std::uint32_t>(std::abs(x)) % capacity;
    }

public:
    // node-ul pentru lista inlantuita de la iterator si initializarea de friend class
    struct Node { int value; Node* next; };
    Node* head = nullptr;
    friend class Iterator;

    SpecialContainer(std::uint32_t capacity) {
        this->capacity = capacity;
        size = 0;
        array = new int[capacity];

        for (std::uint32_t i = 0; i <= capacity; i++) {
            array[i] = -1;
        }
    }

    void add(int x) {
        if (size == capacity) {
            resize();
        }

        auto y = hash(x);

        if (array[y] != -1) {
            for (std::uint32_t i = y; i < capacity; i++) {
                if (array[i] == -1) {
                    y = i;
                    break;
                }
            }
        }

        if (array[y] == -1) {
            array[y] = x;
            size++;
        } else {
            resize();
            add(x);
        }
    }

    bool remove(int x) {

        auto y = hash(x);

        if (array[y] == x) {
            array[y] = -1;
            size--;
            return true;
        } else {
            for (std::uint32_t i = y + 1; array[i] != -1; i++) {
                if (array[i] == x) {
                    array[i] = -1;
                    size--;
                    return true;
                }
            }
        }

        return false;
    }

    bool search(int x) {
        auto y = hash(x);
        if (array[y] == x) {
            return true;
        } else {
            for (std::uint32_t i = y + 1; array[i] != -1; i++) {
                if (array[i] == x) {
                    return true;
                }
            }
        }
        return false;
    }

    void display() {
        std::cout << "size: " << size << std::endl;
        std::cout << "capacity: " << capacity << std::endl;
        for (std::uint32_t i = 0; i < capacity; i++) {
            if (array[i] != -1) {
                std::cout << "index:" << i << " val " << array[i] << "  ";
            }
        }
        std::cout << std::endl;
    }
};

class Iterator {
    //initializare iterator
    SpecialContainer::Node* current;
public:
    //functiile generice
    Iterator(SpecialContainer::Node* start){
        current = start;
    }

    bool valid(){
        return current != nullptr;
    }

    int getCurrent(){
        return current->value;
    }

    void next(){
        if(current != nullptr){
            current = current->next;
        }
    }
};

int main() {
    SpecialContainer s(3);
    s.display();

    s.add(1);
    s.display();

    s.add(2);
    s.display();

    s.add(3);
    s.display();

    s.add(4);
    s.display();

    s.add(6);
    s.display();

    s.remove(6);
    s.display();

    if (s.search(3)) {
        std::cout << "SUPER" << "\n";
        s.display();
    }

    s.remove(1);
    s.display();

    s.add(5);
    s.display();

    s.add(10);
    s.display();

    return 0;
}