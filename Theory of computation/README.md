# Theory-of-computation

# Formal Languages, Automata & Graph Theory 

> A collection of algorithmic engines simulating finite state machines (DFA, NFA, PDA) and exploring advanced Graph Theory conjectures. 

## 🚀 Overview

This repository bridges the gap between theoretical computer science and practical software engineering. It contains custom-built simulation engines for deterministic and non-deterministic automata, alongside a unique implementation of a Pushdown Automaton (PDA) used as the core logic engine for a text-based adventure game. 

Additionally, it includes an algorithmic exploration of the Erdős-Gyárfás Conjecture using Python and graph theory libraries.

## 🗂️ Projects Included

### 1. The PDA Wizard Game 🧙‍♂️ (`wizard_game.py` & `pda.py`)
A creative application of a **Pushdown Automaton (PDA)**. Instead of just parsing strings, the PDA acts as a game engine:
* **The Concept:** You are escaping a wizarding school. The rooms are "States" ($q_0$ to $q_7$). Your magical inventory acts as the PDA's **LIFO Stack**.
* **The Mechanics:** To pass obstacles, you must pick up items in the correct order so they sit at the top of your stack when needed (e.g., picking up a Spellbook, then a Potion, to melt a gate before unlocking a barrier).
* **Technical Implementation:** Uses a recursive branch search (`pda_branch_search`) to evaluate valid state transitions based on player input, current state, and the top symbol of the stack.

### 2. NFA Simulator with $\epsilon$-Transitions (`nfa.py` & `main.py`)
A Non-Deterministic Finite Automaton (NFA) evaluation engine.
* Parses external `.txt` configuration files to build the automaton dynamically.
* Handles **Epsilon ($\epsilon$) transitions** (state jumps without consuming input) using a clean backtracking algorithm.
* Generates and prints a formatted transition table to the console.

### 3. DFA Simulator (C++ & Python)
* Parses strict Deterministic Finite Automaton rules from a `.dfa` file.
* Simulates state-by-state execution to accept or reject custom string inputs.
* Built using robust Object-Oriented Principles in C++.

### 4. Graph Theory: Erdős-Gyárfás Conjecture (`Referat_...pdf` & scripts)
An empirical, algorithmic exploration of the famous 1995 graph theory conjecture.
* Uses the `networkx` library to programmatically generate random graphs.
* Filters for non-planar, claw-free ($K_{1,3}$) graphs with a minimum degree of $\delta(G) \ge 3$.
* Implements a custom **Depth-First Search (DFS)** algorithm to detect cycles with lengths of $2^k$.
* Uses graph hashing (Weisfeiler-Lehman) to memorize and avoid re-testing identical graph structures.

## 🛠️ Technical Skills Demonstrated

* **Algorithmic Thinking:** Implementing recursive branch search and backtracking to simulate non-determinism in NFAs and PDAs.
* **Data Structures:** Practical application of Stacks (LIFO) and Graphs.
* **File Parsing & I/O:** Custom text parsers built to extract state rules, alphabets, and transition functions from structured `.txt` and `.dfa` files.
* **Applied Mathematics:** Translating strict mathematical definitions (Automata theory, Erdős-Gyárfás) into executable, optimized code.

## 💻 How to Run

**To play the Wizard Game (PDA):**
```bash
python wizard_game.py
  
