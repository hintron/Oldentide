# Oldentide Style Guide

## C++

* **Files** should be named after their class/namespace using UpperCamelCase notation.
```Cpp
    Class UserContainer should be in UserContainer.cpp/h
```
* **Source Files** should be all have a matching header file (except Main.cpp) use the ".cpp" file ending.
```Cpp
    UserContainer.cpp
```
* **Header Files** should have a matching source file and use the ".h" file ending.
```Cpp
    UserContainer.h
```
* **Boilerplate** Every code-containing file should have the same boilerplate at the top of the file.  
  The boilerplate should include the file name, creation date, author's name, and purpose (in that order).
```Cpp
    // File:     UserContainer.cpp
    // Created:  January 1, 2016
    // Author:   John Smith
    // Purpose:  A simple class that contains user information.
```
* **Comments** should all be implemented using line comments ("//") when posible.
```Cpp
    // This is a description for the foo class.
    // This is the way to do a multi-line comment.
    class foo {
        private:
        int bar;    // This is a description for the bar variable.
        byte baz;   // This is a description for the baz variable.
    }
```
* **Classes** should be named using UpperCamelCase notation, and use descriptive names.
  They should have private or protected variables.
  They should use public getter and setter methods for any data member that you would need to edit.
  Other functions can be public or private as needed.
  Class declarations should go in header files, and implementation should be in source files.
```Cpp
UserContainer.h:

    Class UserContainer {
        public:
        User(int id);
        int getId();
        void setId(int id);
        
        private:
        int id;
    }

UserContainer.cpp:

    UserContainer::UserContainer(int id) {
        setId(id);
    }
    
    int UserContainer::getId() {
        return id;
    }
    
    void UserContainer::setId(int id) {
        this.id = id;
    }
```
* **Namespaces** should be named using all undercase letters.  The **"using namespace std"** directive should never be used.
```Cpp
    namespace testmode {
        bool CheckObese(int weight) {
            if (weight > 300) {
                return true;
            }
            return false;
        }
    }
    
    if (testmode::CheckObese(310)) {
        std::cout << "You should lose some weight buddy..." << std::endl;
    }
    else {
        std::cout << "Keep eating bro!" << std::endl;
    }
```
* **Functions** should be named using UpperCamelCase notation.  If a function returns nothing, please denote that it returns void.
  Functional programming is encouraged where possible, but otherwise, parameters are passed inputs first, outputs second.
```Cpp
Functional:

    int AddTwoIntegers(int x, int y) {
        return x + y;
    }

Referencial:
    
    void AddTwoInteger(int x, int y, int &z) {
        z = x + y
    }
```
* **Variables** should be named using lowerCamelCase notation.
```Cpp
    int phoneNumber = 9251234567;
    string fullHomeAddress = "123 Sesame Street, Sacramento, CA 94203";
```
* **Braces** should always open on the same line as the declaration, with a space between the declaration and the '{'.  
  Closing braces should always be on their own line, aligned with the declaration.
```Cpp
    int foo(int bar) {
        return bar;
    }
```
* **Angle Brackets** should follow directly after the container name and have no spaces touching their insides.
```Cpp
    std::Vector<std::string> names = new std::vector<std::string>();
```
* **Square Brackets** should follow directly after the array name and have no spaces touching their insides.
```Cpp
    int phoneNumbers[100];
    std::cout << "Phone Number 5 is: " << phoneNumbers[4] << std::endl;
```
* **Parenthases** should follow directly after the function name and have no spaces touching their insides.
```Cpp
    UserContainer joseph = new UserContainer(15);
    int userId = joseph.getId();
```
* **if-else statements** and other similar statements should keep declarations on their own line.
```Cpp
    if (foo) {
        return bar;
    }
    else {
        return baz;
    }
```

## C# 

* **To be implemented!**
