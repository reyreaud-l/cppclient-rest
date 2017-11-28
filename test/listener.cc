#define CATCH_CONFIG_EXTERNAL_INTERFACES
#include "catch.hpp"
#include <iostream>

struct MyListener : Catch::TestEventListenerBase {

    using TestEventListenerBase::TestEventListenerBase; // inherit constructor
    
    // Get rid of Wweak-tables
    ~MyListener();

    // Test cases ending
    virtual void testCaseEnded( Catch::TestCaseStats const& testCaseStats ) override {
      std::cout << "test: " << testCaseStats.testInfo.name;
      if (testCaseStats.totals.testCases.failed != 0)
        std::cout << " ko.\n";
      else
        std::cout << " ok.\n";
    }
};

CATCH_REGISTER_LISTENER( MyListener )

// Get rid of Wweak-tables
MyListener::~MyListener() {}
