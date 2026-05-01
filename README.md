# ARTEMIS-II System Simulation

This repository contains the C++ source code for the ARTEMIS-II System, a simulation initially designed for a Principles of Programming Languages assignment. The project models a spacecraft's telemetry, environmental air control, and thruster management systems using modern C++20 features, including modules and coroutines.

## System Architecture

The project is divided into several distinct C++ modules that handle different spacecraft subsystems:

*   **Main Application (`main.cpp`)**: The entry point that initializes the "ARTEMIS-II System". It sets up the vent tree, initializes the thruster array, establishes the initial communication frequency at 145.800, and loops through the telemetry event stream. 
*   **AirControl Module**: Manages the environmental vent system using a binary tree of `VentNode` objects. It simulates reading environmental data like oxygen levels, temperature, and pressure. It also features a recursive diagnostic check function and a `find_vent` function that utilizes C++ coroutines (`std::generator`) to search for and yield specific vent nodes.
*   **Communications Module**: Defines the `EventType` enumeration and a `TelemetryPacket` data structure. It provides a coroutine-based generator called `read_telemetry` to sequentially parse incoming commands from a specified filepath. It also includes a lambda generator to print formatted communication logs.
*   **Thruster Module**: Implements an object-oriented inheritance hierarchy for propulsion control. It features a base `Thruster` class alongside two derived classes: `MainEngine` and `RCS_Valve`. Each class has virtual methods to toggle its valve state and apply specific thrust values
*   **Tools Module**: Provides a thread-safe `random` utility function. It utilizes `std::random_device` and `std::mt19937` to generate uniform integer distributions

## Telemetry Data Format

The main system reads incoming commands from an `events.txt` file. Each line in this file represents a single telemetry packet with the following structure:
*   **Frequency**: A double precision number representing the communication frequency, such as `145.800` or `120.600`.
*   **Event Type**: A string mapping to an `EventType`. Supported events include `TELEMETRY_RX`, `VENTSET`, `THRUSTOPEN`, `THRUSTSET`, `CHANGEFREQ`, and `AIRCHECK`.
*   **Parameters**: Up to two optional strings containing target IDs, boolean states (e.g., `true`/`false`), or numeric thrust levels.
*   **Message**: A descriptive log string enclosed in double quotes.

During execution, the system dynamically filters the incoming packets, completely ignoring events if their broadcast frequency does not fall within 0.1 of the spacecraft's currently active communication frequency.

## Compilation Requirements

Because this code aggressively leverages modern C++ standards, your build environment must meet the following requirements:
*   A cutting-edge C++ compiler with robust support for **C++20 and C++23 features**.
*   Full support for C++ Modules (e.g., `export module`, `import std;`).
*   Support for the `<generator>` header and coroutine keywords like `co_yield` and `co_return`.
*   Support for the modern `<print>` header (`std::println`).