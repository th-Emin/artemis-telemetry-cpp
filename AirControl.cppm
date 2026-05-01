// This code write for Principles of Programming Languages Homework 1
// th-Emin
export module AirControl;

import std;
import Tools;

export class VentNode {
private:
    int id;
    bool open_state;

public:
    VentNode* left;
    VentNode* right;

    VentNode(int id, bool open_state = false) 
        : id(id), open_state(open_state), left(nullptr), right(nullptr) {}
    
    int read_id() const {
        return id;
    }

    bool isOpen() const {
        return open_state;
    }

    void set() {
        open_state = (get_oxygen_level() < 20 || get_pressure() < 1000 || get_temperature() > 25);
    }

    void setOpen(bool state) {
        open_state = state;
    }

    int get_oxygen_level() const {
        if(open_state) {
            return random(19, 24); 
        }
        return random(18, 21); 
    }

    int get_temperature() const {
        if(open_state) {
            return random(22, 27); 
        }
        return random(24, 29); 
    }

    int get_pressure() const {
        if(open_state) {
            return random(990, 1020); 
        }
        return random(980, 1009); 
    }

    void printState(){
        std::println("Vent Node (ID: {}): State is {}", id, open_state?"OPEN":"CLOSED");
    }

    ~VentNode(){
        delete left;
        delete right;
    }
};

export void diagnostic_vent_check(VentNode* current_node, int& open_count) {
    if (current_node == nullptr) {
        return;
    }

    current_node->set();

    if (current_node->isOpen()) {
        open_count++;
    }

    // Recursive traversal (Runtime Stack & Parameter Passing demonstration)
    diagnostic_vent_check(current_node->left, open_count);
    diagnostic_vent_check(current_node->right, open_count);
}

export std::generator<VentNode*> find_vent(VentNode* root, int target_id) {
    if (root) {
        if (root->read_id() == target_id) co_yield root;
        for (auto* v : find_vent(root->left, target_id))
            co_yield v;
        for (auto* v : find_vent(root->right, target_id))
            co_yield v;
    }
}
