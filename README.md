
# Scheduler Project

## Overview

This project implements an advanced job scheduler designed to optimize system performance and resource management in complex environments. The scheduler is based on the Completely Fair Scheduler (CFS) algorithm, which ensures fair CPU time allocation among tasks, and includes additional handling for real-time tasks using a dynamic Round Robin (RR) algorithm. This design provides a quick response to tasks while maintaining high fairness and efficient CPU distribution across all tasks, ensuring that no task is starved and system performance remains optimal.

## Features

-   **Real-Time Task Handling**: Prioritizes real-time tasks to ensure fast response time.
-   **Fair CPU Distribution**: Implements CFS to ensure fair CPU time allocation to all tasks based on priority.
-   **Prevention of Starvation**: Ensures no tasks are starved, regardless of their priority.
-   **Dynamic Scheduling**: The system dynamically adjusts the CPU allocation to handle varying task loads and priorities efficiently.

## Algorithms

-   **Completely Fair Scheduler (CFS)**: Provides fairness in CPU distribution and prevents starvation by using a virtual runtime mechanism.
-   **Round Robin (RR) for Real-Time Tasks**: Manages real-time tasks by assigning dynamic quantum slices based on task priority.

## Requirements

-   **Real-time tasks** should have the highest priority and fast response time.
-   **CPU time** should be distributed fairly between tasks, with high-priority tasks receiving more CPU time.
-   The scheduler must **prevent starvation** for all tasks, ensuring progress in the system.
-   A mechanism must be available for **logging runtime information** to aid in crash investigation.

## Design

The scheduler operates using two threads:

-   **Input Thread**: Receives new tasks and inserts them into the appropriate data structures.
-   **Scheduler Thread**: Executes tasks based on the scheduling algorithm.

### Task Handling

-   **Non-Real-Time Tasks**: Managed using a Red-Black Tree, where tasks are selected based on their virtual runtime.
-   **Real-Time Tasks**: Managed using a Round Robin queue with dynamic quantum based on task priority.

## Data Structures

-   **Red-Black Tree**: Stores non-real-time tasks and ensures fair CPU allocation.
-   **Queue**: Stores real-time tasks and executes them in a round-robin fashion.

## Testing

The system was tested for:

1.  **Prevention of Starvation**: Ensuring all tasks get CPU time within a reasonable period.
2.  **Fairness**: Verifying that CPU time is divided fairly based on task priority.
3.  **Handling System Load**: Ensuring the system can handle a mix of real-time and non-real-time tasks efficiently.
4.  **Random Tasks**: Ensuring tasks complete correctly when random priorities and execution times are assigned.

## design doc.

## How to Build and Run

1.  **Clone the Repository**:
       ```bash
    `git clone https://github.com/Hadassa-Buganim/Scheduler` 
2.  **Build**: Use your preferred build system or IDE (e.g., Visual Studio, GCC, etc.) to compile the project.
3.  **Run**: Run the executable to start the scheduler. Provide task input as required.

## Contributions

Authors:

-   [Bracha Goldberg](https://github.com/BrachiGoldberg)
-   [Chaya Hadad](https://github.com/chayaProg)
-   [Hadassa Buganim](https://github.com/Hadassa-Buganim)
