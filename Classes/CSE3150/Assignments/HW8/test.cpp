
#include <iostream>
#include <cassert>
#include "User.h"
#include "RentalCart.h"
#include "MediaCatalog.h"
#include "Payment.h"

using namespace std;

// g++ -std=c++17 -o DigitalLibrary test.cpp User.cpp MediaCatalog.cpp RentalCart.cpp Payment.cpp

void TestDiscount()
{
    auto& catalog = MediaCatalog::getInstance();
    catalog.addMedia("Data Structures", make_shared<Media>("Data Structures", 50));
    catalog.addMedia("AI Basics", make_shared<Media>("AI Basics", 70));
    CreditCard cc(30); // Simulate payment with some overdraft
    PayPal paypal(70);  // Sufficient funds

    StudentUser student("S123", "Alice", 90, &cc);
    FacultyUser faculty("F001", "Dr. Jane", 60, &paypal);

    student.getRentalCart()->addMedia(catalog.getMedia("Data Structures"));
    faculty.getRentalCart()->addMedia(catalog.getMedia("AI Basics"));

    double studentExpected = 50.0;
    double facultyExpected = 70.0;
    
    double studentTotal = student.getRentalCart()->calculateTotal(&student);
    double facultyTotal = faculty.getRentalCart()->calculateTotal(&faculty);

    assert(studentTotal == studentExpected);
    assert(facultyTotal == facultyExpected);

    assert(student.getPaymentMethod()->processPayment(studentTotal));  // should succeed
    assert(faculty.getPaymentMethod()->processPayment(facultyTotal));  // should succeed

    assert(student.getLoyaltyPoints() == 95);
    assert(faculty.getLoyaltyPoints() == 67);

    double studentExpectedBal = -20.0;
    double facultyExpectedBal = 0.0;

    assert(student.getPaymentMethod()->getBalance() == studentExpectedBal);
    assert(faculty.getPaymentMethod()->getBalance() == facultyExpectedBal);
}

void TestFailure()
{
    auto& catalog = MediaCatalog::getInstance();
    catalog.addMedia("Data Structures", make_shared<Media>("Data Structures", 50));
    catalog.addMedia("AI Basics", make_shared<Media>("AI Basics", 70));
    CreditCard cc(10); // Simulate payment with insufficient overdraft
    PayPal paypal(40);  // Insufficient funds

    StudentUser student("S123", "Alice", 80, &cc);
    FacultyUser faculty("F001", "Dr. Jane", 70, &paypal);

    student.getRentalCart()->addMedia(catalog.getMedia("AI Basics"));
    faculty.getRentalCart()->addMedia(catalog.getMedia("Data Structures"));

    double studentExpected = 70.0;
    double facultyExpected = 50.0;
    
    double studentTotal = student.getRentalCart()->calculateTotal(&student);
    double facultyTotal = faculty.getRentalCart()->calculateTotal(&faculty);

    assert(studentTotal == studentExpected);
    assert(facultyTotal == facultyExpected);

    assert(!student.getPaymentMethod()->processPayment(studentTotal));  // should fail
    assert(!faculty.getPaymentMethod()->processPayment(facultyTotal));  // should fail

    assert(student.getLoyaltyPoints() == 80);
    assert(faculty.getLoyaltyPoints() == 70);

    double studentExpectedBal = 10.0;
    double facultyExpectedBal = 40.0;

    assert(student.getPaymentMethod()->getBalance() == studentExpectedBal);
    assert(faculty.getPaymentMethod()->getBalance() == facultyExpectedBal);
}

int main() {
    TestDiscount();
    TestFailure();
    std::cout << "\nAll tests passed.\n";
    return 0;
}
