#include "LibraryCode.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>

TEST(AccountTest, TestEmptyAccount) {
  Account account;

  double balance = account.getBalance();

  ASSERT_EQ(0, balance);
}

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

void AccountTestFixture::TearDown() { std::cout << "TearDown called\n"; }

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

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

/*
@huynhtritai96 ➜ .../C_CPlusPlus_Testing/GoogleTestFixtures/GoogleTest-fixtures/build (main) $ ./unitTestRunner 
[==========] Running 6 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 1 test from AccountTest
[ RUN      ] AccountTest.TestEmptyAccount
[       OK ] AccountTest.TestEmptyAccount (0 ms)
[----------] 1 test from AccountTest (0 ms total)

[----------] 5 tests from AccountTestFixture
SetUpTestCase called
[ RUN      ] AccountTestFixture.TestDeposit
Constructor called
SetUp called
Test body
TearDown called
Destructor called
[       OK ] AccountTestFixture.TestDeposit (0 ms)
[ RUN      ] AccountTestFixture.TestWithdrawOK
Constructor called
SetUp called
TearDown called
Destructor called
[       OK ] AccountTestFixture.TestWithdrawOK (0 ms)
[ RUN      ] AccountTestFixture.TestWithdrawInsufficientFunds
Constructor called
SetUp called
TearDown called
Destructor called
[       OK ] AccountTestFixture.TestWithdrawInsufficientFunds (0 ms)
[ RUN      ] AccountTestFixture.TestTransferOK
Constructor called
SetUp called
TearDown called
Destructor called
[       OK ] AccountTestFixture.TestTransferOK (0 ms)
[ RUN      ] AccountTestFixture.TestTransferInsufficientFunds
Constructor called
SetUp called
TearDown called
Destructor called
[       OK ] AccountTestFixture.TestTransferInsufficientFunds (0 ms)
TearDownTestCase called
[----------] 5 tests from AccountTestFixture (0 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 2 test suites ran. (0 ms total)
[  PASSED  ] 6 tests.
*/