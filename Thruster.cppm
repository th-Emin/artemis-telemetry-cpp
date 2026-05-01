// This code write for Principles of Programming Languages Homework 1
// th-Emin
export module Thruster;

import std;

export class Thruster {
  protected:
    int id;
    int thrust;
    bool open_state;
  public:
    Thruster(int id, bool open_state = false, int thrust = 0) : id(id), open_state(open_state), thrust(thrust) {}
    virtual ~Thruster() = default;
    virtual void setOpen(bool state){
        open_state = state;
    }
    int getId(){
        return id;
    }
    void printState(){
        std::println("Thruster (ID: {}): State is {}", id, open_state?"OPEN":"CLOSED");
    }
    virtual void apply_thrust(int thrust){
        this->thrust = thrust;
    }
};

export class MainEngine : public Thruster {
public:
    MainEngine(int id, bool open_state = false, int thrust = 0) : Thruster(id, open_state, thrust) {}
    void setOpen(bool state) override{
        Thruster::setOpen(state);
        std::println("MainEngine (ID: {}): Valve State changed to {}!", id, state);
    }
    void apply_thrust(int thrust) override {
        Thruster::apply_thrust(thrust);
        std::println("MainEngine (ID: {}): Applying {} Newtons of main engine thrust!", id, thrust);
    }
};

export class RCS_Valve : public Thruster {
public:
    RCS_Valve(int id, bool open_state = false, int thrust = 0) : Thruster(id, open_state, thrust) {}
    void setOpen(bool state) override{
        Thruster::setOpen(state);
        std::println("RCS_Valve (ID: {}): Valve State changed to {}!", id, state);
    }
    void apply_thrust(int thrust) override {
        Thruster::apply_thrust(thrust);
        std::println("RCS_Valve (ID: {}): Applying {} Newtons of attitude control thrust.", id, thrust);
    }
};