#include <iostream>
#include <optional>
#include <string>
using namespace std;

// Template function with compile-time branching
template<typename T>
optional<int> fun(T x) {
    if constexpr (is_same_v<T, int>) {
        return x;                  // T is int, return as-is
    }
    else if constexpr (is_same_v<T, double>) {
        return static_cast<int>(2 * x); // T is double, double and cast to int
    }
    else {
        return nullopt;            // For all other types
    }
}

int main() {
    // Test with int
    auto v1 = fun(5);   // optional<int>
    if (v1.has_value()) {
        cout << "fun(5) = " << v1.value() << endl;
    }

    // Test with double
    auto v2 = fun(5.5); // optional<int>
    if (v2.has_value()) {
        cout << "fun(5.5) = " << v2.value() << endl;
    }

    // Test with string
    auto v3 = fun(string("hello")); // optional<int>
    if (!v3.has_value()) {
        cout << "fun(\"hello\") returned no value" << endl;
    }

    return 0;
}
