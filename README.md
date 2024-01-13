# C_CPlusPlus_Testing
####Unit test
one unit of code

####Integration testing
Testing of integrated modules (code modules, individual appplications, client-server applications, etc...)          

####System testing
End-to-end testing              
Back-box type of testing (code not available)               
Overall specifications are checked                  

####Unit test basics (TEST)
Arrange ==> Act ==> Assert

####Test Fixtures (TEST_F)
Test with similar Setup & TearDown (YourTestFixture inherit from testing::Test)                     
In testing::Test have:                      
void SetUp();                      
void TearDown();                
static void SetUpTestCase();                    
static void TearDownTestCase();                            
SetUpTestCase ==> Fixture Constructor ==> Setup ==> Test body ==> TearDown ==> Fixture Destructor => TearDownTestCase                                                             

####Parameterized Test (TEST_P)
Generating multiple test cases but writing the test body just once                  
Inherit from testing::TestWithParam<T> not inherit from testing::Test                   
SetUpTestCase and TearDownTestCase => public                    
INSTANTIATE_TEST_SUITE_P => generate tests from params                      

####Mock Test
create a fake object to simulate the behavior of real object within a system. The primary goal of mock testing is to isolate the code being tested and verify that it interacts correctly with its dependencies.
-Fake                                             
    + working implementation                
    + take a shortcut                   
    + not suitable for production                   
    + example: in-memory database                   
-Stub                   
    + responds with pre-defined data                        
-Mock                       
    + has set expectaions: throws/doesn't throw exceptions, call the methods                        
Syntax:                     
    MOCK_METHOD(ReturnType, MethodName, (Arguments...));                    
    For example:                    
        int sum(int a, int b);                      
        MOCK_METHOD(int, sum, (int, int));              
    MOCK_METHOD(ReturnType, MethodName, (Arguments...), (Specs...));            
    Specs:              
        const                   void doSomeThing() const;                     MOCK_METHOD(void, doSomeThing, (), (const));
        override            
        noexcept                        

Legacy         
Method with n parameters:               
MOCK_METHODn(name, ReturnType(ParamType1, ParamType2...));              
For example:                    
    int sum(int a, int b);                                    
    MOCK_METHOD2(sum, int(int, int));               
    void doSomething();                  
    MOCK_METHOD0(doSomething, void());  

MOCK_CONST_METHODn
For example:                    
    int sum(int a, int b) const;                                    
    MOCK_CONST_METHOD2(sum, int(int, int));  

ON_CALL vs EXPECT_CALL              
ON_CALL: sets the behavior when a method gets called            
EXPECT_CALL: ON_CALL + expectaions   

Setting Mock behavior                          
ACTION              
Setting an action/return value
-WillOnce           
-WillRepeatedly             
-WillByDefault              
-Return             
-ReturnRef      

Expected number of calls            
-AnyNumber()                     
-AtLeast(n)                            
-AtMost(n)              
-Between(m,n)               
-Exactly(n) or n                

For exact value: EXPECT_CALL(someObject, someMethod(ParamType1, ParamType2...));                
For argument is greater/lower:  EXPECT_CALL(someObject, someMethod(Gt(T)));         
For anything: XPECT_CALL(someObject, someMethod(_)); (using ::testing::_)      



=====================install google test============================                            
unzip googletest-main.zip               
cd googletest-main.zip              
cmake CMakeLists.txt                    
make                    
cd lib                  
sudo cp * /usr/lib                  
cd googlemock/include               
sudo cp -r gmock /usr/local/include             
cd googletest/include           
sudo cp -r gtest /usr/local/include             

====================copile and run================================
cmake -S . -B target/build              
cd target/build             
make                

