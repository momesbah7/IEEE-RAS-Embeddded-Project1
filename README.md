# Smart Parking Management System 🚗⚡

An embedded-systems-oriented C application designed for efficient parking slot allocation, real-time vehicle tracking, and automated log management. Built as part of the **IEEE RAS Student Chapter** embedded systems track.

---

## 🛠️ System Features
*   **Automated Slot Assignment:** Dynamically finds and reserves the nearest available parking slot.
*   **Real-time Checkout & Billing:** Tracks vehicle exit times using `time_t` and automatically calculates durations and fees.
*   **Advanced Search & Edit:** Easily locate any vehicle inside the garage by its Plate ID or update its details on the fly.
*   **Persistent Storage:** Save/Load system state dynamically from local files (`.txt` / `.dat`) to prevent data loss on shutdown.
*   **Cross-Platform UI:** Clean Terminal-based dashboard with fully automated screen-clearing compatible with both **Windows** and **Linux (Ubuntu)**.

---

## 📁 Project Structure
*   `main.c` — Contains the core application loop, user interactive dashboard, and system menus.
*   `functions.c` — Core logic implementation (Vehicle adding, slot allocation, sorting, and file I/O operations).
*   `functions.h` — System structures, macros, external variables, and function prototypes.

---

## 🚀 Compilation and Execution

To run the verified stable version of this project, use the following commands in your terminal:

```bash
# 1. Compile all project files together
gcc main.c functions.c -o parking_system

# 2. Run the application
./parking_system
```

## Contributors

* **Mohamed Mesbah**
* **Mostafa Elramady**