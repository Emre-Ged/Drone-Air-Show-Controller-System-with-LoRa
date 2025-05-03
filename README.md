Drone Air Show Controller System with LoRa and Poisson Distribution

Project Overview

This project simulates a Drone Air Show Controller System, where drones perform synchronized aerial maneuvers (such as forming a triangle) while communicating with a central controller. The drones communicate via LoRa, a long-range, low-power communication protocol. Additionally, we simulate random events such as drone failures and orientation changes using the Poisson distribution.

Objectives:
	•	Simulate drone communication and behavior during an air show using LoRa.
	•	Model random drone failures and orientation changes based on Poisson distribution.
	•	Evaluate network performance such as packet delivery ratio (PDR), latency, and reliability.
	•	Analyze the impact of random events on drone synchronization and communication.

Implementation

Technologies Used:
	•	OMNeT++: A discrete event simulation framework used to simulate the network and drone behavior.
	•	LoRa Communication: A wireless communication protocol used for drone-controller communication.
	•	C++: Programming language used for simulation model development.
	•	Poisson Distribution: A statistical method used to simulate random events (drone failures or orientation changes).

Simulation Workflow:
	1.	Central Controller: The controller coordinates the drone movements and manages communication using LoRa.
	2.	Drones: Drones are simulated as nodes that perform specific maneuvers (e.g., forming a triangle), with random changes in orientation based on Poisson-distributed events.
	3.	LoRa Communication: Each drone communicates with the controller over a 2 km range. Communication reliability and packet delivery are measured.
	4.	Poisson Distribution: Random events like drone failures and reorientations are modeled using Poisson distribution, affecting drone movement.

Future Improvements
	•	Enhanced Drone Behavior: More complex drone movements and behaviors (e.g., adaptive maneuvers, obstacle avoidance).
	•	Multi-Gateway Communication: Extend the system to support communication with multiple controllers (gateways) for larger drone fleets.
	•	Network Optimization: Investigate optimizing the LoRa parameters (e.g., spreading factor, transmission power) for better network performance under different conditions.

Contact Information
	•	Semir Emre Gedikli
	•	Email: emre.gedikli@metu.edu.tr
	•	GitHub: Emre-Ged-github
	•	Alperen Kayhan
	•	Email: alperen.kayhan@metu.edu.tr
	•	GitHub: alperen-github

