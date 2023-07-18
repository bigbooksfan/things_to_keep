export module Test_module;

// add new tests in this function definition in very end of this file
export void RunAllTests();

// import tested modules here
import A;

import <iostream>;

module : private;

template <typename T, typename U>
void AssertEqualImpl(const T& t, const U& u, const std::string& t_str, const std::string& u_str, const std::string& file, const std::string& func, unsigned line, const std::string& hint) {
    if (t != u) {
        std::cerr << std::boolalpha;
        std::cerr << file << "(" << line << "): " << func << ": ";
        std::cerr << "ASSERT_EQUAL(" << t_str << ", " << u_str << ") failed: ";
        std::cerr << t << " != " << u << ".";
        if (!hint.empty()) {
            std::cerr << " Hint: " << hint;
        }
        std::cerr << std::endl;
        //abort();
    }
}

void AssertImpl(bool value, const std::string& expr_str, const std::string& file, const std::string& func, unsigned line,
    const std::string& hint) {
    if (!value) {
        std::cerr << file << "(" << line << "): " << func << ":\n";
        std::cerr << "ASSERT(" << expr_str << ") failed.\n";
        if (!hint.empty()) {
            std::cerr << "Hint: " << hint;
        }
        std::cerr << std::endl;
        //abort();
    }
}

template <typename T>
void RunTestImpl(const T& func, const std::string& func_name) {
    func();
    std::cerr << func_name << " OK\n";
}

#define ASSERT(expr) AssertImpl(!!(expr), #expr, __FILE__, __FUNCTION__, __LINE__, "")

#define ASSERT_HINT(expr, hint) AssertImpl(!!(expr), #expr, __FILE__, __FUNCTION__, __LINE__, (hint))

#define ASSERT_EQUAL(a, b) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, "")

#define ASSERT_EQUAL_HINT(a, b, hint) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, (hint))

#define RUN_TEST(func) RunTestImpl((func), #func)

// tests bodies
void TestA() {
    ASSERT(foo(5) == 10);
    ASSERT_HINT(foo(5) == 10, "foo is broken");
    ASSERT_EQUAL(foo(5), 10);
    ASSERT_EQUAL_HINT(foo(5), 10, "foo is broken");
}

void RunAllTests() {
    RUN_TEST(TestA);
}