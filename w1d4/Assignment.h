#include <iostream>
enum Payment_t {Card, Cash, Invoice};
enum Month_t {January, February, Mars, April, May, June, July, August, September, October, November, December};

class Workshop {
    Service
    Customer
    Part

};

class Record {
    CustomerID
    ServiceID
};

class Customer {
    private:
    std::string Name;
    std::string Address;

    public:
    Customer() = delete;
    int CustomerID;
    // Assign customer to customer ID?
    void addCustomer(std::string name, std::string address) {
        Name = name, Address = address;
    }
    //void printCustomerInfo()
};

/*class Vehicle {
    private:
    std::string RegNo;
    std::string Model;  
    int ModelYear;
};*/

class Part {
    std::string PartName;
    int PartNo;

};

class ServiceVisit {
    int Price;
    Payment_t Paymethod;
    int Year;
    Month_t Month;
    int Day;
    Part PartsChanged;

};