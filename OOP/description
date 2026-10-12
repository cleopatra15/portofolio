## Overview

This project simulates the core backend operations of a bookstore—including inventory management, client tracking, and order processing. It was designed specifically as a technical sandbox to implement complex C++ concepts, standard template library (STL) algorithms, and scalable software design principles.

## Technical Skills

* **Advanced OOP Architecture:** 
  * Deep inheritance hierarchies and polymorphism.
  * Virtual inheritance used to resolve the "Diamond Problem" (`AutorUniversal` inheriting from both `AutorRoman` and `AutorPoet`).
  * Dynamic casting and Run-Time Type Information (RTTI).
* **Modern Design Patterns:**
  * **Singleton Pattern (Meyers):** Implemented for centralized system logging.
  * **Abstract Factory Pattern:** Used to dynamically generate compatible Eco and Premium packaging/delivery objects.
* **Memory & Resource Management:** Strict adherence to the Rule of Three (custom copy constructors, assignment operators, and virtual destructors) to prevent memory leaks during deep copies.
* **Generic Programming:** Custom template classes (`Colectie<T, N>`) and specialized template functions for sorting and searching.
* **Modern STL Integration:** Extensive use of `std::vector`, `std::list`, `std::map`, and `<algorithm>` (`find_if`, `for_each`, `remove_if`) combined with lambda expressions.
* **Robust Error Handling:** Custom exception classes inheriting from `std::exception` to handle invalid inputs and demonstrate stack unwinding.

##  Core Features

- **Inventory Control:** Manage Standard and Special Edition books, update stock, apply discounts, and filter inventory.
- **Author Cataloging:** Differentiate between Novelists, Poets, and Universal Authors using polymorphic behavior.
- **Client Management:** Track premium vs. standard clients, newsletter subscriptions, and calculate loyalty statuses.
- **Order Processing:** Create orders, estimate delivery times, and simulate packaging/shipping using different processing families.

##  Getting Started

*(Currently a single-file implementation. To run, compile the `main.cpp` using any standard C++ compiler.)*

```bash
g++ -o bookstore main.cpp
./bookstore
