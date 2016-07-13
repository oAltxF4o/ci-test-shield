#include "mbed.h"
#include "greentea-client/test_env.h"
#include "unity.h"
#include "utest.h"
#include "rtos.h"

using namespace utest::v1;

// Template to set one Analog pin as input and then cycle through the rest as outputs.
// As you turn more pins on the voltage on the ain pin will go up.
template <PinName aout_pin, PinName ain_pin> 
void AnalogOutput_Test()
{
    AnalogIn ain(ain_pin);
    AnalogOut aout(aout_pin);
    float valueOff = 0;
    float valueOn = 0;
    aout = 0;
    valueOff = ain.read();
    aout = 0.5;
    valueOn = ain.read();
    printf("***** valueOff = %f, valueOn = %f \n",valueOff, valueOn);
    TEST_ASSERT(valueOn > valueOff);
    valueOff = ain.read();
    aout = 1.0;
    valueOn = ain.read();
    printf("***** valueOff = %f, valueOn = %f \n",valueOff, valueOn);
    TEST_ASSERT(valueOn > valueOff);
}

utest::v1::status_t test_setup(const size_t number_of_cases) {
    // Setup Greentea using a reasonable timeout in seconds
    GREENTEA_SETUP(30, "default_auto");
    return verbose_test_setup_handler(number_of_cases);
}

utest::v1::status_t greentea_failure_handler(const Case *const source, const failure_t reason) {
    greentea_case_failure_abort_handler(source, reason);
    return STATUS_CONTINUE;
}

// Test cases
// TODO: take input based on pinmap
Case cases[] = {
    Case("Test Analog Output on A5", AnalogOutput_Test<A5,A0>,greentea_failure_handler),
};

Specification specification(test_setup, cases);

// Entry point into the tests
int main() {
    return !Harness::run(specification);
}
