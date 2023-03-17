#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <set>
#include <cassert>

namespace MyUnitTests {

    using std::string;
    using std::cerr;

    using namespace std;            // need it here to avoid massive amount of ""s errors

    template <typename T, typename U>
    void AssertEqualImpl(const T& t, const U& u, const string& t_str, const string& u_str, const string& file, const string& func, unsigned line, const string& hint) {
        if (t != u) {
            cerr << boolalpha;
            cerr << file << "(" << line << "): " << func << ": ";
            cerr << "ASSERT_EQUAL(" << t_str << ", " << u_str << ") failed: ";
            cerr << *t << " != " << *u << ".";
            if (!hint.empty()) {
                cerr << " Hint: " << hint;
            }
            cerr << std::endl;
            abort();
        }
    }

    void AssertImpl(bool value, const string& expr_str, const string& file, const string& func, unsigned line,
        const string& hint) {
        if (!value) {
            cerr << file << "(" << line << "): " << func << ": ";
            cerr << "ASSERT(" << expr_str << ") failed.";
            if (!hint.empty()) {
                cerr << " Hint: " << hint;
            }
            cerr << std::endl;
            abort();
        }
    }

    template <typename T>
    void RunTestImpl(const T& func, const string& func_name) {
        func();
        cerr << func_name << " OK\n";
    }

#define ASSERT(expr) AssertImpl(!!(expr), #expr, __FILE__, __FUNCTION__, __LINE__, "")

#define ASSERT_HINT(expr, hint) AssertImpl(!!(expr), #expr, __FILE__, __FUNCTION__, __LINE__, (hint))

#define ASSERT_EQUAL(a, b) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, "")

#define ASSERT_EQUAL_HINT(a, b, hint) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, (hint))

#define RUN_TEST(func) RunTestImpl((func), #func)

    // -------- Начало модульных тестов поисковой системы ----------

    void RequestsInStrings() {
        const vector<string> strings = { "cat", "dog", "dog", "horse" };
        const vector<string> requests = { "bear", "cat", "deer", "dog", "dogs", "horses" };
        {
            const auto a = LowerBound(strings.begin(), strings.end(), requests[0]);
            const vector<string>::const_iterator b = strings.begin() + 0;
            ASSERT_EQUAL_HINT(a, b, "bear should be [0]\n");
        }
        {
            const auto a = LowerBound(strings.begin(), strings.end(), requests[1]);
            const vector<string>::const_iterator b = strings.begin() + 0;
            ASSERT_EQUAL_HINT(a, b, "bear should be [0]\n");
        }
        {
            const auto a = LowerBound(strings.begin(), strings.end(), requests[2]);
            const vector<string>::const_iterator b = strings.begin() + 1;
            ASSERT_EQUAL_HINT(a, b, "bear should be [0]\n");
        }
        {
            const auto a = LowerBound(strings.begin(), strings.end(), requests[3]);
            const vector<string>::const_iterator b = strings.begin() + 1;
            ASSERT_EQUAL_HINT(a, b, "bear should be [0]\n");
        }
        {
            const auto a = LowerBound(strings.begin(), strings.end(), requests[4]);
            const vector<string>::const_iterator b = strings.begin() + 3;
            ASSERT_EQUAL_HINT(a, b, "bear should be [0]\n");
        }
        {
            const auto a = LowerBound(strings.begin(), strings.end(), requests[5]);
            const vector<string>::const_iterator b = strings.begin() + 4;
            ASSERT_EQUAL_HINT(a, b, "bear should be [0]\n");
        }
    }
    
    void RequestsInStringsSeq() {
        const vector<string> strings = { "cat", "dog", "dog", "horse" };
        const vector<string> requests = { "bear", "cat", "deer", "dog", "dogs", "horses" };
        {
            const auto a = LowerBound(execution::seq, strings.begin(), strings.end(), requests[0]);
            const vector<string>::const_iterator b = strings.begin() + 0;
            ASSERT_EQUAL_HINT(a, b, "bear should be [0]\n");
        }
        {
            const auto a = LowerBound(execution::seq, strings.begin(), strings.end(), requests[1]);
            const vector<string>::const_iterator b = strings.begin() + 0;
            ASSERT_EQUAL_HINT(a, b, "bear should be [0]\n");
        }
        {
            const auto a = LowerBound(execution::seq, strings.begin(), strings.end(), requests[2]);
            const vector<string>::const_iterator b = strings.begin() + 1;
            ASSERT_EQUAL_HINT(a, b, "bear should be [0]\n");
        }
        {
            const auto a = LowerBound(execution::seq, strings.begin(), strings.end(), requests[3]);
            const vector<string>::const_iterator b = strings.begin() + 1;
            ASSERT_EQUAL_HINT(a, b, "bear should be [0]\n");
        }
        {
            const auto a = LowerBound(execution::seq, strings.begin(), strings.end(), requests[4]);
            const vector<string>::const_iterator b = strings.begin() + 3;
            ASSERT_EQUAL_HINT(a, b, "bear should be [0]\n");
        }
        {
            const auto a = LowerBound(execution::seq, strings.begin(), strings.end(), requests[5]);
            const vector<string>::const_iterator b = strings.begin() + 4;
            ASSERT_EQUAL_HINT(a, b, "bear should be [0]\n");
        }
    }
    
    void RequestsInStringsPar1() {
        const vector<string> strings = { "cat", "dog", "dog", "horse" };
        const vector<string> requests = { "bear", "cat", "deer", "dog", "dogs", "horses" };
        {
            const auto a = LowerBound(execution::par, strings.begin(), strings.end(), requests[0]);
            const vector<string>::const_iterator b = strings.begin() + 0;
            ASSERT_EQUAL_HINT(a, b, "bear should be [0]\n");
        }
        {
            const auto a = LowerBound(execution::par, strings.begin(), strings.end(), requests[1]);
            const vector<string>::const_iterator b = strings.begin() + 0;
            ASSERT_EQUAL_HINT(a, b, "bear should be [0]\n");
        }
        {
            const auto a = LowerBound(execution::par, strings.begin(), strings.end(), requests[2]);
            const vector<string>::const_iterator b = strings.begin() + 1;
            ASSERT_EQUAL_HINT(a, b, "bear should be [0]\n");
        }
        {
            const auto a = LowerBound(execution::par, strings.begin(), strings.end(), requests[3]);
            const vector<string>::const_iterator b = strings.begin() + 1;
            ASSERT_EQUAL_HINT(a, b, "bear should be [0]\n");
        }
        {
            const auto a = LowerBound(execution::par, strings.begin(), strings.end(), requests[4]);
            const vector<string>::const_iterator b = strings.begin() + 3;
            ASSERT_EQUAL_HINT(a, b, "bear should be [0]\n");
        }
        {
            const auto a = LowerBound(execution::par, strings.begin(), strings.end(), requests[5]);
            const vector<string>::const_iterator b = strings.begin() + 4;
            ASSERT_EQUAL_HINT(a, b, "bear should be [0]\n");
        }
    }
    
    void RequestsInStringsPar() {
        const vector<int> strings = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        {
            const auto a = LowerBound(execution::par, strings.begin(), strings.end(), 0);
            const vector<int>::const_iterator b = strings.begin() + 0;
            ASSERT_EQUAL_HINT(a, b, "bear should be [0]\n");
        }
        {
            const auto a = LowerBound(execution::par, strings.begin(), strings.end(), 2);
            const vector<int>::const_iterator b = strings.begin() + 2;
            ASSERT_EQUAL_HINT(a, b, "bear should be [2]\n");
        }
        {
            const auto a = LowerBound(execution::par, strings.begin(), strings.end(), 4);
            const vector<int>::const_iterator b = strings.begin() + 4;
            ASSERT_EQUAL_HINT(a, b, "bear should be [4]\n");
        }
        {
            const auto a = LowerBound(execution::par, strings.begin(), strings.end(), 5);
            const vector<int>::const_iterator b = strings.begin() + 5;
            ASSERT_EQUAL_HINT(a, b, "bear should be [5]\n");
        }
        {
            const auto a = LowerBound(execution::par, strings.begin(), strings.end(), 6);
            const vector<int>::const_iterator b = strings.begin() + 6;
            ASSERT_EQUAL_HINT(a, b, "bear should be [6]\n");
        }
        {
            const auto a = LowerBound(execution::par, strings.begin(), strings.end(), 12);
            const vector<int>::const_iterator b = strings.end();
            ASSERT_EQUAL_HINT(a, b, "bear should be [end]\n");
        }
        {
            const auto a = LowerBound(execution::par, strings.begin(), strings.end(), 9);
            const vector<int>::const_iterator b = strings.begin() + 9;
            ASSERT_EQUAL_HINT(a, b, "bear should be [end]\n");
        }
    }

    void Tests() {
        
        RUN_TEST(RequestsInStrings);
        RUN_TEST(RequestsInStringsSeq);
        RUN_TEST(RequestsInStringsPar);
        RUN_TEST(RequestsInStringsPar1);
    }
}       // namespace MyUnitTests