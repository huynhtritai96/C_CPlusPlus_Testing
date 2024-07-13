### Summary

- **Include GoogleTest Headers**:
  ```cpp
  #include <gtest/gtest.h>
  ```

- **Define a Test**:
  ```cpp
  TEST(TestSuiteName, TestName) {
    // Arrange
    // Act
    // Assert
  }
  ```

- **ASSERT_EQ(Expected, Actual)**:
  - Compare expected and actual values.
  ```cpp
  ASSERT_EQ(expected, actual);
  ```

- **Main Function to Run Tests**:
  ```cpp
  int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }
  ```

### Key Concepts and Commands

1. **GoogleMock Matchers**:
   - **ElementsAre**: Asserts that a container contains exactly the given elements in the same order.
   ```cpp
   ASSERT_THAT(v, testing::ElementsAre(0, 1, 2, 0, 1));
   ```

2. **Combining Matchers**:
   - **Each**: Asserts that each element in the container matches the given matcher.
   - **AllOf**: Combines multiple matchers with a logical AND.
   - **Ge**: Greater than or equal to.
   - **Lt**: Less than.
   ```cpp
   ASSERT_THAT(v, Each(AllOf(Ge(0), Lt(3)))); // Each element is between 0 and 3
   ```

### Detailed Cheat Sheet

#### 1. **Basic Test Structure (Review)**
   - Set up, call function, and assert results.
   ```cpp
   TEST(TestSuiteName, TestName) {
     // Arrange
     // Act
     // Assert
   }
   ```

#### 2. **Matchers in GoogleMock**:
   - **ElementsAre**: Verify the exact sequence of elements.
   ```cpp
   ASSERT_THAT(v, testing::ElementsAre(0, 1, 2, 0, 1));
   ```

#### 3. **Combining Matchers**:
   - **Each**: Apply a condition to all elements.
   - **AllOf**: Combine multiple conditions.
   - **Ge**: Greater than or equal.
   - **Lt**: Less than.
   ```cpp
   ASSERT_THAT(v, Each(AllOf(Ge(0), Lt(3))));
   ```

#### 4. **Main Function (Review)**
   - Initialize and run all tests.
   ```cpp
   int main(int argc, char **argv) {
     ::testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
   }
   ```

### Example Code
Combining everything into a comprehensive example:
```cpp
#include <vector>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "LibraryCode.hpp"

// Function to be tested (assumed to be defined in LibraryCode.hpp)
std::vector<int> generateNumbers(int size, int mod);

TEST(VectorTests, ElementsAreTest) {
  std::vector<int> v = generateNumbers(5, 3);  // Example: 0, 1, 2, 0, 1
  ASSERT_THAT(v, testing::ElementsAre(0, 1, 2, 0, 1));
}

TEST(VectorTests, RangeTest) {
  using namespace testing;
  std::vector<int> v = generateNumbers(5, 3);  // Example: 0, 1, 2, 0, 1
  ASSERT_THAT(v, Each(AllOf(Ge(0), Lt(3))));
}

// Test the toUpper function with a basic input
TEST(ToUpperTest, BasicTest) {
  // Arrange
  char inputString[] = "Hello World";

  // Act
  toUpper(inputString);

  // Assert
  ASSERT_STREQ("HELLO WORLD", inputString);
  // Alternative: ASSERT_STRCASEEQ("Hello WORLD", inputString); // Case insensitive comparison

  // Alternative using std::string
  // std::string str(inputString);
  // ASSERT_EQ("HELLO WORLD", str);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
```

### Summary of New Commands and Concepts

- **Matchers**:
  - **ElementsAre**: Verify the exact order of elements.
  - **Each**: Apply a condition to each element.
  - **AllOf**: Combine multiple conditions.
  - **Ge**: Greater than or equal.
  - **Lt**: Less than.

### Advanced Topic: ASSERT_THROW

#### **ASSERT_THROW Overview**
- **Purpose**: To verify that a specific exception is thrown by the code under test.
- **Syntax**:
  ```cpp
  ASSERT_THROW(statement, expected_exception_type);
  ```

#### **Usage Example**
- **Test Definition**:
  ```cpp
  TEST(TestSuiteName, TestName) {
    ASSERT_THROW(statement, expected_exception_type);
  }
  ```

- **Example Code**:
  ```cpp
  #include "LibraryCode.hpp"
  #include <gtest/gtest.h>
  #include <stdexcept>

  // Function to be tested (assumed to be defined in LibraryCode.hpp)
  double mySqrt(double value);

  // Test case for negative argument
  TEST(SquareRootTest, NegativeArgumentTest) {
    double inputValue = -9;
    ASSERT_THROW(mySqrt(inputValue), std::runtime_error);  // Expect runtime_error
  }

  // Test case for positive argument
  TEST(SquareRootTest, PositiveArgumentTest) {
    double inputValue = 9;
    ASSERT_NO_THROW(mySqrt(inputValue));  // Expect no exception
  }

  // Main function to run all tests
  int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }
  ```

### Google Test Order of Execution Cheat Sheet

#### Unit Test Basics (TEST)
- **Structure**: Arrange ==> Act ==> Assert

#### Test Fixtures (TEST_F)
- **Purpose**: Test with similar Setup & TearDown

#### Order of Execution in Google Test
1. **SetUpTestCase**: Called once before all tests in the test case.
   ```cpp
   static void SetUpTestCase();
   ```
2. **Fixture Constructor**: Called before each test.
   ```cpp
   AccountTestFixture();
   ```
3. **SetUp**: Called before each test.
   ```cpp
   void SetUp() override;
   ```
4. **Test Body**: The actual test code.
   ```cpp
   TEST_F(AccountTestFixture, TestName) {
     // Test code here
   }
   ```
5. **TearDown**: Called after each test.
   ```cpp
   void TearDown() override;
   ```
6. **Fixture Destructor**: Called after each test.
   ```cpp
   virtual ~AccountTestFixture();
   ```
7. **TearDownTestCase**: Called once after all tests in the test case.
   ```cpp
   static void TearDownTestCase();
   ```

#### Example Code

```cpp
#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>
#include "LibraryCode.hpp"

// Define your test fixture
class AccountTestFixture : public testing::Test {
public:
  AccountTestFixture();
  virtual ~AccountTestFixture();
  void SetUp() override;
  void TearDown() override;
  static void SetUpTestCase();
  static void TearDownTestCase();

protected:
  Account account;
};

// Implement the test fixture methods
AccountTestFixture::AccountTestFixture() {
  std::cout << "Constructor called\n";
}

AccountTestFixture::~AccountTestFixture() {
  std::cout << "Destructor called\n";
}

void AccountTestFixture::SetUpTestCase() {
  std::cout << "SetUpTestCase called\n";
}

void AccountTestFixture::TearDownTestCase() {
  std::cout << "TearDownTestCase called\n";
}

void AccountTestFixture::SetUp() {
  std::cout << "SetUp called\n";
  account.deposit(10.5);
}

void AccountTestFixture::TearDown() {
  std::cout << "TearDown called\n";
}

// Define tests using the fixture
TEST_F(AccountTestFixture, TestDeposit) {
  std::cout << "Test body\n";
  ASSERT_EQ(10.5, account.getBalance());
}

TEST_F(AccountTestFixture, TestWithdrawOK) {
  account.withdraw(3);
  ASSERT_EQ(7.5, account.getBalance());
}

TEST_F(AccountTestFixture, TestWithdrawInsufficientFunds) {
  ASSERT_THROW(account.withdraw(300), std::runtime_error);
}

TEST_F(AccountTestFixture, TestTransferOK) {
  Account to;
  account.transfer(to, 2);
  ASSERT_EQ(8.5, account.getBalance());
  ASSERT_EQ(2, to.getBalance());
}

TEST_F(AccountTestFixture, TestTransferInsufficientFunds) {
  Account to;
  ASSERT_THROW(account.transfer(to, 200), std::runtime_error);
}

// Main function to run all tests
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
```

### Summary

- **Unit Test Basics (TEST)**: Arrange ==> Act ==> Assert
- **Test Fixtures (TEST_F)**:
  - Inherit from `testing::Test`
  - Implement `SetUp()`, `TearDown()`, `SetUpTestCase()`, `TearDownTestCase()`
- **Order of Execution**:
  1. `SetUpTestCase()`
  2. **Constructor** (`AccountTestFixture()`)
  3. `SetUp()`
  4. **Test Body** (`TEST_F(...)`)
  5. `TearDown()`
  6. **Destructor** (`~AccountTestFixture()`)
  7. `TearDownTestCase()`
 
### Google Test Parameterized Tests Cheat Sheet
#### Parameterized Tests (TEST_P)
- **Purpose**: Test with multiple sets of parameters

#### Defining a Parameterized Test
1. **Define Test Fixture Class**:
   - Inherit from `testing::TestWithParam<std::tuple<...>>`
   ```cpp
   class ValidatorFixture : public testing::TestWithParam<std::tuple<int, bool>> {
   protected:
     Validator mValidator{5, 10};
   };
   ```

2. **Define Parameterized Test Case**:
   ```cpp
   TEST_P(ValidatorFixture, TestInRange) {
     auto param = GetParam();
     int value = std::get<0>(param);
     bool expected = std::get<1>(param);
     ASSERT_EQ(expected, mValidator.inRange(value));
   }
   ```

3. **Instantiate the Parameterized Test Case**:
   ```cpp
   INSTANTIATE_TEST_SUITE_P(
       InRangeTrue, ValidatorFixture,
       testing::Values(
           std::make_tuple(-50, false), std::make_tuple(4, false),
           std::make_tuple(5, true), std::make_tuple(6, true),
           std::make_tuple(7, true), std::make_tuple(9, true),
           std::make_tuple(10, true), std::make_tuple(11, false),
           std::make_tuple(100, false)
       )
   );
   ```

4. **Main Function**:
   ```cpp
   int main(int argc, char **argv) {
     testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
   }
   ```

### Example Usage

```cpp
#include <gtest/gtest.h>
#include <tuple>
#include <iostream>
#include "LibraryCode.hpp"

// Define your test fixture
class ValidatorFixture : public testing::TestWithParam<std::tuple<int, bool>> {
public:
  ValidatorFixture() {
    std::cout << "Constructor called\n";
  }
  virtual ~ValidatorFixture() {
    std::cout << "Destructor called\n";
  }
  void SetUp() override {
    std::cout << "SetUp called\n";
  }
  void TearDown() override {
    std::cout << "TearDown called\n";
  }
  static void SetUpTestCase() {
    std::cout << "SetUpTestCase called\n";
  }
  static void TearDownTestCase() {
    std::cout << "TearDownTestCase called\n";
  }

protected:
  Validator mValidator{5, 10};
};

// Parameterized test case
TEST_P(ValidatorFixture, TestInRange) {
  std::cout << "Test body called\n";
  auto param = GetParam();
  int value = std::get<0>(param);
  bool expected = std::get<1>(param);
  ASSERT_EQ(expected, mValidator.inRange(value));
}

// Instantiation of parameterized tests
INSTANTIATE_TEST_SUITE_P(
    InRangeTrue,                   // Prefix name
    ValidatorFixture,              // Test fixture class
    testing::Values(               // List of parameter values
        std::make_tuple(-50, false), std::make_tuple(4, false),
        std::make_tuple(5, true), std::make_tuple(6, true),
        std::make_tuple(7, true), std::make_tuple(9, true),
        std::make_tuple(10, true), std::make_tuple(11, false),
        std::make_tuple(100, false)
    )
);

// Main function to run all tests
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
```

### Expected Output

When you run this test, the output will include the print statements, making it clear which functions are called and in what order. Here is an example of what the output might look like:

```plaintext
[==========] Running 9 tests from 1 test suite.
[----------] Global test environment set-up.
SetUpTestCase called
[----------] 9 tests from InRangeTrue/ValidatorFixture

// TEST CASE 0:
[ RUN      ] InRangeTrue/ValidatorFixture.TestInRange/0
Constructor called
SetUp called
Test body called
TearDown called
Destructor called
[       OK ] InRangeTrue/ValidatorFixture.TestInRange/0 (0 ms)

// TEST CASE 1:
[ RUN      ] InRangeTrue/ValidatorFixture.TestInRange/1
Constructor called
SetUp called
Test body called
TearDown called
Destructor called
[       OK ] InRangeTrue/ValidatorFixture.TestInRange/1 (0 ms)


.....
.....

[----------] 9 tests from InRangeTrue/ValidatorFixture (0 ms total)
TearDownTestCase called
[----------] Global test environment tear-down
[==========] 9 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 9 tests.
```

### Explanation

- **SetUpTestCase called**: This is called once before any of the tests in the `InRangeTrue/ValidatorFixture` test suite run.
- **Constructor called**: This is called before each individual test case.
- **SetUp called**: This is called immediately after the constructor and before the test body.
- **Test body called**: This is the actual test case execution.
- **TearDown called**: This is called after each individual test case.
- **Destructor called**: This is called after each individual test case to clean up.
- **TearDownTestCase called**: This is called once after all the tests in the `InRangeTrue/ValidatorFixture` test suite have completed.

In Google Test, there are two main levels of setup and teardown functions: the test fixture level (`SetUp` and `TearDown`) and the test suite level (`SetUpTestCase` and `TearDownTestCase`). Both levels serve different purposes and are used for different scenarios.

### `SetUp` and `TearDown` : Clear cache, files genereted after pushing config, and clear all DB
These functions are called before and after each individual test case, respectively. They are useful for setting up and cleaning up resources that are needed for a single test. Here's why you might need these functions:

1. **Isolation**: Ensures that each test runs in a clean environment, free from any side effects caused by other tests.
2. **Consistency**: Each test gets a consistent initial state, which is crucial for reliable and repeatable tests.
3. **Resource Management**: Sets up and tears down resources (e.g., memory, file handles, network connections) that are needed only for the duration of a single test.

### `SetUpTestCase` and `TearDownTestCase`
These functions are called once before and after all tests in the test suite, respectively. They are useful for setting up and cleaning up resources that are shared among all tests in a test suite. Here's why you might need these functions:

1. **Efficiency**: Avoids redundant setup and teardown operations by sharing expensive resources among multiple tests.
2. **State Sharing**: Useful when tests need to share some state or resource that should be set up once and cleaned up once.
3. **Global Initialization**: Performs initialization that is global to the test suite, such as starting a server or initializing a database.

### Example Scenario
Let's consider a database connection example to illustrate the use of both levels:

#### Using `SetUpTestCase` and `TearDownTestCase` : Start Yumapro, OAMA, MPLANE, RU-sim, rather than each test run 1 Yumapro, 1 OAMA, 1 Mplane
If the database connection is expensive to create and you want to use it across multiple tests:

```cpp
class DatabaseTest : public testing::Test {
protected:
  static void SetUpTestCase() {
    // Establish a connection to the database once for all tests in this suite
    dbConnection = new DatabaseConnection();
    dbConnection->connect();
  }

  static void TearDownTestCase() {
    // Clean up the database connection once after all tests in this suite
    dbConnection->disconnect();
    delete dbConnection;
    dbConnection = nullptr;
  }

  static DatabaseConnection* dbConnection;
};

DatabaseConnection* DatabaseTest::dbConnection = nullptr;

TEST_F(DatabaseTest, QueryTest1) {
  // Use dbConnection for this test
}

TEST_F(DatabaseTest, QueryTest2) {
  // Use dbConnection for this test
}
```

#### Using `SetUp` and `TearDown`
If you need to reset the state of the database for each test to ensure isolation:

```cpp
class DatabaseTest : public testing::Test {
protected:
  void SetUp() override {
    // Reset the database state before each test
    dbConnection->resetState();
  }

  void TearDown() override {
    // Clean up after each test if necessary
  }

  static void SetUpTestCase() {
    // Establish a connection to the database once for all tests in this suite
    dbConnection = new DatabaseConnection();
    dbConnection->connect();
  }

  static void TearDownTestCase() {
    // Clean up the database connection once after all tests in this suite
    dbConnection->disconnect();
    delete dbConnection;
    dbConnection = nullptr;
  }

  static DatabaseConnection* dbConnection;
};

DatabaseConnection* DatabaseTest::dbConnection = nullptr;

TEST_F(DatabaseTest, QueryTest1) {
  // Use dbConnection for this test
}

TEST_F(DatabaseTest, QueryTest2) {
  // Use dbConnection for this test
}
```

NOTE: 

TEST_F = TEST + SetupGlobalEnviroment + SetupTestCaseCache and TearDownTestCaseCache + TearDownGlobalEnviroment
TEST_P = loop of Test_F
TEST can be TEST_F (if setup inside body :)), too long) and can be TEST_P (by using for loop)

### Summary
- **Use `SetUp` and `TearDown`** for setting up and cleaning up resources that are needed for each individual test. This ensures that each test runs in a clean, consistent environment.
- **Use `SetUpTestCase` and `TearDownTestCase`** for setting up and cleaning up resources that are shared across all tests in a test suite. This is useful for expensive setup operations that should only be performed once.

By combining both levels, you can ensure efficient and reliable test execution, balancing between test isolation and resource management.

To run multiple test suites using Google Test, you can combine filters using a colon (`:`) to specify which tests to run. Here's how you can adjust your main function and demonstrate the expected output for both environments with multiple filters.

### Adjusted Code

```cpp
#include "LibraryCode.hpp"
#include <gtest/gtest.h>
#include <iostream>

// Uncomment to simulate Windows environment
// #define __WIN32

// Unix-specific tests
TEST(UnixSuite, DummyTest1) {
  std::cout << "Dummy test 1 - Unix \n";
#ifdef __WIN32
  FAIL();
#else
  SUCCEED();
#endif
}

TEST(UnixSuite, DummyTest2) {
  std::cout << "Dummy test 2 - Unix \n";
#ifdef __WIN32
  FAIL();
#else
  SUCCEED();
#endif
}

// Windows-specific tests
TEST(WindowsSuite, DummyTest1) {
  std::cout << "Dummy test 1 - Windows \n";
#ifdef __WIN32
  SUCCEED();
#else
  FAIL();
#endif
}

TEST(WindowsSuite, DummyTest2) {
  std::cout << "Dummy test 2 - Windows \n";
#ifdef __WIN32
  SUCCEED();
#else
  FAIL();
#endif
}

// Additional tests for demonstration
TEST(CommonSuite, DummyTest1) {
  std::cout << "Dummy test 1 - Common \n";
  SUCCEED();
}

TEST(CommonSuite, DummyTest2) {
  std::cout << "Dummy test 2 - Common \n";
  SUCCEED();
}

int main(int argc, char **argv) {
#ifdef __WIN32
  testing::GTEST_FLAG(filter) = "WindowsSuite.*:CommonSuite.*";  // Run Windows and Common tests
#else
  testing::GTEST_FLAG(filter) = "UnixSuite.*:CommonSuite.*";  // Run Unix and Common tests
#endif
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
```

### Expected Output

#### Output for Unix Environment

Ensure `#define __WIN32` is commented out.

```plaintext
[==========] Running 4 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 2 tests from UnixSuite
[ RUN      ] UnixSuite.DummyTest1
Dummy test 1 - Unix 
[       OK ] UnixSuite.DummyTest1 (0 ms)
[ RUN      ] UnixSuite.DummyTest2
Dummy test 2 - Unix 
[       OK ] UnixSuite.DummyTest2 (0 ms)
[----------] 2 tests from UnixSuite (0 ms total)

[----------] 2 tests from CommonSuite
[ RUN      ] CommonSuite.DummyTest1
Dummy test 1 - Common 
[       OK ] CommonSuite.DummyTest1 (0 ms)
[ RUN      ] CommonSuite.DummyTest2
Dummy test 2 - Common 
[       OK ] CommonSuite.DummyTest2 (0 ms)
[----------] 2 tests from CommonSuite (0 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 2 test suites ran. (0 ms total)
[  PASSED  ] 4 tests.
```

#### Output for Windows Environment

Uncomment `#define __WIN32`.

```plaintext
[==========] Running 4 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 2 tests from WindowsSuite
[ RUN      ] WindowsSuite.DummyTest1
Dummy test 1 - Windows 
[       OK ] WindowsSuite.DummyTest1 (0 ms)
[ RUN      ] WindowsSuite.DummyTest2
Dummy test 2 - Windows 
[       OK ] WindowsSuite.DummyTest2 (0 ms)
[----------] 2 tests from WindowsSuite (0 ms total)

[----------] 2 tests from CommonSuite
[ RUN      ] CommonSuite.DummyTest1
Dummy test 1 - Common 
[       OK ] CommonSuite.DummyTest1 (0 ms)
[ RUN      ] CommonSuite.DummyTest2
Dummy test 2 - Common 
[       OK ] CommonSuite.DummyTest2 (0 ms)
[----------] 2 tests from CommonSuite (0 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 2 test suites ran. (0 ms total)
[  PASSED  ] 4 tests.
```

### Summary

- **Multiple Filters**: Use colons (`:`) to combine multiple test suite filters.
  ```cpp
  #ifdef __WIN32
    testing::GTEST_FLAG(filter) = "WindowsSuite.*:CommonSuite.*";
  #else
    testing::GTEST_FLAG(filter) = "UnixSuite.*:CommonSuite.*";
  #endif
  ```

- **Test Suites**:
  - `UnixSuite`: Tests specific to Unix environments.
  - `WindowsSuite`: Tests specific to Windows environments.
  - `CommonSuite`: Tests common to both environments.

- **Conditional Compilation**:
  - Use `#ifdef __WIN32` to differentiate between Windows and Unix environments.

By following this setup, you can ensure that the appropriate tests for the target environment and common tests are executed, providing clear and concise output for each scenario.


  
