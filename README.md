# System Design & C++ Systems Programming

Hands-on C++ systems programming and low-level design (LLD) practice: multithreading primitives, custom STL-style containers, memory management, C++17 features, and two full LLD exercises (Parking Lot, Elevator System).

### Multithreading (`multithreading/`)

Concurrency primitives built from scratch with `<mutex>`, `<condition_variable>`, and `<atomic>`:

- `ThreadPool.cpp` — a working thread pool: worker threads pulling from a shared task queue, synchronized with `std::mutex` / `std::condition_variable`.
- `RingBuffer.cpp` / `MultiUserRingBuffer.cpp` — bounded circular buffers for producer/consumer use, including a multi-producer/multi-consumer variant.
- `ProducerConsumer.cpp` — the classic producer-consumer pattern with condition variables.
- `ConsumerRateLimit.cpp` — a rate-limited consumer.
- `Atomic_flag.cpp` — lock-free signaling with `std::atomic_flag`.
- `Mutex.cpp`, `Multithreading.cpp` — mutex and thread fundamentals.
- `GenericThreadPool.cpp` — placeholder, not yet implemented.

### Custom STL (`STL/`)

Hand-rolled versions of standard library building blocks, to understand what they do under the hood:

- `unique_pointer.cpp` — a minimal `unique_ptr`.
- `shared_pointer.cpp` — a minimal `shared_ptr` with reference counting.
- `MyVector.cpp` — a dynamic array (`vector`) with manual memory management.

### Memory management (`Memory_management/`)

- `Placement_new.cpp` — placement `new` in practice.

### C++17 (`CPP17/`)

- `optional.cpp`, `variant.cpp`, `Any.cpp` — `std::optional`, `std::variant`, and `std::any` usage.

### Low-level design exercises (`System desing/`)

- **Parking Lot** (`ParkingLot/`) — a modular OOD exercise split into single-responsibility classes: `ParkingLot`, `MainGate`, `SlotManager`, `Ticket`, `PaymentManager` / `PaymentMethod` (credit card, UPI), `VehicleType`.
- **Elevator System** (`Elevator/`) — an elevator/floor request simulation: `Elevator`, `ElevatorManager`, `Floor`, `Request`, `Status`.
- Classic design patterns: `Singleton.cpp`, `Observer_pattern.cpp`, `abstract_factory.cpp`, `factory_pattern.cpp`, `Builder_pattern.cpp` (placeholder, not yet implemented).

### Other

- `data_structor/DSU.cpp` — a Disjoint Set Union (Union-Find) implementation.
- `inheritance/CRTP.cpp` — Curiously Recurring Template Pattern example.

### Note on hygiene

A few IDE/build artifacts (Visual Studio `.vs/` folders, `.sln` / `.vcxproj` files, compiled `.exe` binaries) are committed alongside the source under `System desing/`. The `.cpp`/`.h` files are the actual content worth reviewing.
