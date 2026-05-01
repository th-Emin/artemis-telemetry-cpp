// This code write for Principles of Programming Languages Homework 1
// th-Emin
export module Communications;

import std;

export enum class EventType {
    TELEMETRY_RX,
    AIRCHECK,
    VENTSET,
    THRUSTOPEN,
    THRUSTSET,
    CHANGEFREQ,
};

export struct TelemetryPacket {
    double frequency;
    EventType type;
    std::string parameter1;
    std::string parameter2;
    std::string message;
    TelemetryPacket(double frequency, EventType type, std::string parameter1, std::string parameter2, std::string message) 
        : frequency(frequency), type(type), parameter1(parameter1), parameter2(parameter2), message(message) {}
};

export std::generator<TelemetryPacket> read_telemetry(const std::string& filepath){
    std::ifstream file(filepath);
    if(!file.is_open()){
        co_return;
    }
    std::string line;
    while(std::getline(file, line)){
        if(line.empty()) continue;
        
        std::stringstream ss(line);
        double freq;
        std::string type_str;
        ss >> freq >> type_str;
        
        EventType type;
        std::string param1 = "-1";
        std::string param2 = "-1";
        std::string message;

        if(type_str == "TELEMETRY_RX"){
            type = EventType::TELEMETRY_RX;
            ss >> param1 >> param2;
        }else if(type_str == "VENTSET"){
            type = EventType::VENTSET;
            ss >> param1 >> param2;
        }else if(type_str == "THRUSTOPEN"){
            type = EventType::THRUSTOPEN;
            ss >> param1 >> param2;
        }else if(type_str == "THRUSTSET"){
            type = EventType::THRUSTSET;
            ss >> param1 >> param2;
        }else if(type_str == "CHANGEFREQ"){
            type = EventType::CHANGEFREQ;
            ss >> param1;
        }else if(type_str == "AIRCHECK"){
            type = EventType::AIRCHECK;
        }else{
            continue;
        }
        char quote_mark;
        ss >> quote_mark;
        std::getline(ss, message, '"');
        co_yield TelemetryPacket(freq, type, param1, param2, message);
    }
}

export auto setup_comm_channel(double &frequency) {
    return [&frequency](const std::string& msg) {
        std::println("Comm Channel [{}]: {}", frequency, msg);
    };
}

