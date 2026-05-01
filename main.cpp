// This code write for Principles of Programming Languages Homework 1
// th-Emin
import std;
import Tools;
import Thruster;
import AirControl;
import Communications;

void initilaze_vent_tree(VentNode* root);
void initialize_thrusters(std::vector<Thruster*> &thrusters);

int main() {
    double active_freq = 145.800;
    auto comms = setup_comm_channel(active_freq);
    comms("ARTEMIS-II System Initializing...");

    VentNode* root = new VentNode(0, false); 
    initilaze_vent_tree(root);

    std::vector<Thruster*> thrusters;
    initialize_thrusters(thrusters);

    auto is_valid_frequency = [&active_freq](double incoming_freq) {
        return std::abs(incoming_freq - active_freq) < 0.1;
    };

    for(auto const& packet : read_telemetry("events.txt")){
        if(!is_valid_frequency(packet.frequency)){
            continue;
        }
        try {
            switch(packet.type){
                case EventType::TELEMETRY_RX:
                    comms(packet.message);
                    if(packet.parameter1 == "THRUST"){
                        for(auto* t : thrusters) {
                            if (t->getId() == std::stoi(packet.parameter2)) {
                                t->printState();
                            }
                        }
                    }else if(packet.parameter1 == "VENT"){
                        for(auto* v : find_vent(root, std::stoi(packet.parameter2))) {
                            v->printState();
                        }
                    }
                    break;
                case EventType::VENTSET:
                    comms(packet.message);
                    for(auto* v : find_vent(root, std::stoi(packet.parameter1))) {
                        v->setOpen(packet.parameter2 == "true");
                    }
                    break;
                case EventType::THRUSTOPEN:
                    comms(packet.message);
                    for(auto* t : thrusters) {
                        if (t->getId() == std::stoi(packet.parameter1)) {
                            t->setOpen(packet.parameter2 == "true");
                        }
                    }
                    break;
                case EventType::THRUSTSET:
                    comms(packet.message);
                    for(auto* t : thrusters) {
                        if (t->getId() == std::stoi(packet.parameter1)) {
                            t->apply_thrust(std::stoi(packet.parameter2));
                        }
                    }
                    break;
                case EventType::CHANGEFREQ:
                    comms(packet.message);
                    active_freq = std::stod(packet.parameter1);
                    break;
                case EventType::AIRCHECK: {
                    comms(packet.message);
                    int open_count = 0;
                    diagnostic_vent_check(root, open_count);
                    std::println("{} vents are open", open_count);
                    break;
                }
                default:
                    comms(packet.message);
                    break;
            }
        } catch (const std::exception& e) {
            std::println("Exception caught during event processing: {}", e.what());
        }
    }

    for (auto* t : thrusters) {
        delete t;
    }
    delete root;

    comms("ARTEMIS System Shutting Down.");
    return 0;
}

void initilaze_vent_tree(VentNode* root){
    if(root->read_id()*2 >= 14) return;
    root->left = new VentNode(root->read_id()*2 + 1, random(0, 1) == 1);
    root->right = new VentNode(root->read_id()*2 + 2, random(0, 1) == 1);
    initilaze_vent_tree(root->left);
    initilaze_vent_tree(root->right);
}

void initialize_thrusters(std::vector<Thruster*> &thrusters){
    for(int i = 0; i < 5; i++)
        thrusters.push_back(new MainEngine(i, true));

    for(int i = 5; i < 9; i++)
        thrusters.push_back(new RCS_Valve(i, false));
}


