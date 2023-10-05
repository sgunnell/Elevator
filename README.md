# Elevator Dispatcher and Simulation

This repository contains an Elevator Dispatcher and Simulation system implemented in C++. The project focuses on creating a scalable elevator simulation that concurrently simulates passengers, elevators, and a dispatcher controller. It achieves this by utilizing parallel threads, multiple processes, and object-oriented programming principles.

## Features

- **Scalable Simulation:** The project implements a scalable elevator simulation that can handle multiple passengers, elevators, and concurrent requests efficiently.

- **Concurrency:** Utilizes parallel threads and multiple processes to simulate passengers, elevators, and the dispatcher controller concurrently. This ensures efficient use of system resources.

- **IPC Communication:** Implements inter-process communication (IPC) tools provided by the operating system to ensure reliable communication between input, output, and internal processes. This guarantees proper communication, data integrity, and resource allocation throughout the simulation.

- **Dispatcher Controller:** The system includes a dispatcher controller that utilizes the C SCAN algorithm to optimize elevator requests from a pipeline. This optimization is crucial for efficient elevator operations.

- **Utilizes Various Data Structures:** The implementation incorporates monitors, mailboxes, linked lists, and stacks to manage elevator requests, ensuring organized and optimized handling of commands and requests.

## License

This project is licensed under the [MIT License](LICENSE.md) - see the [LICENSE.md](LICENSE.md) file for details.

Feel free to contribute, report issues, or submit feature requests!
