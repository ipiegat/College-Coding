#include "ECVector.h"
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

void TestInit() {
    vector<int> int_coords={1, 2, 3};
    ECVector<int> vec1(int_coords);

    assert(vec1[0]==1);
    assert(vec1[1]==2);
    assert(vec1[2]==3);
	assert(vec1.getDimension()==3);
	
	vector<double> double_coords={1.0, 2.0};
    ECVector<double> vec2(double_coords);

    assert(vec2[0]==1.0);
    assert(vec2[1]==2.0);
	assert(vec2.getDimension()==2);
}

void TestCopyConstructor() {
    ECVector<int> vec1({1, 2, 3, 4});
    ECVector<int> vec2 = vec1;
	
    assert(vec2[0] == 1);
    assert(vec2[3] == 4);
}

void TestMoveConstructor() {
    ECVector<int> vec1({1, 2, 3, 4});
    ECVector<int> vec2 = std::move(vec1);

    assert(vec2[0] == 1);
    assert(vec2[3] == 4);
}

void TestElementAccess(){
    ECVector<int> vec1({1, 2, 3, 4});
    assert(vec1[0] == 1);
    vec1[0] = 5;
    assert(vec1[0] == 5);
}

void TestMagnitude(){
	ECVector<int> vec1({3, 4});
	ECVector<int> vec2({8, 4, 4, 8, 4, 4, 8});
	
	assert(vec1.getMagnitude()==5);
	assert(vec2.getMagnitude()==16);
}

void TestNormalization(){
	ECVector<double> vec1({1.0,2.0,3.0,4.0});
	ECVector<double> result(vec1.normalized());
	
	assert(result[0]==1.0/vec1.getMagnitude());
	assert(result[1]==2.0/vec1.getMagnitude());
	assert(result[2]==3.0/vec1.getMagnitude());
	assert(result[3]==4.0/vec1.getMagnitude());
}

void TestVectorAddition() {
    ECVector<int> vec1({1, 2, 3, 4});
    ECVector<int> vec2({5, 6, 7, 8});
    ECVector<int> result1 = vec1 + vec2;
	ECVector<int> vec3({1, 2});
    ECVector<int> result2 = vec1 + vec3;
	ECVector<int> result3 = vec3 + vec1;

    assert(result1[0] == 6);
    assert(result1[1] == 8);
    assert(result1[2] == 10);
    assert(result1[3] == 12);
	assert(result1.getDimension()==4);
	assert(result2[0] == 2);
    assert(result2[1] == 4);
    assert(result2[2] == 3);
    assert(result2[3] == 4);
	assert(result2.getDimension()==4);
	assert(result3[0] == 2);
    assert(result3[1] == 4);
    assert(result3[2] == 3);
    assert(result3[3] == 4);
	assert(result3.getDimension()==4);
}

void TestVectorSubtraction() {
    ECVector<int> vec1({5, 6, 7, 8});
    ECVector<int> vec2({1, 2, 3, 4});
    ECVector<int> result1 = vec1 - vec2;
	ECVector<int> vec3({1, 2});
    ECVector<int> result2 = vec1 - vec3;
	ECVector<int> result3 = vec3 - vec1;

    assert(result1[0] == 4);
    assert(result1[1] == 4);
    assert(result1[2] == 4);
    assert(result1[3] == 4);
	assert(result1.getDimension()==4);
	assert(result2[0] == 4);
    assert(result2[1] == 4);
    assert(result2[2] == 7);
    assert(result2[3] == 8);
	assert(result2.getDimension()==4);
	assert(result3[0] == -4);
    assert(result3[1] == -4);
    assert(result3[2] == -7);
    assert(result3[3] == -8);
	assert(result3.getDimension()==4);
}

void TestDotProduct() {
    ECVector<int> vec1({1, 2, 3, 4});
    ECVector<int> vec2({4, 3, -2, -1});
	ECVector<int> vec3({1, 2, 3});
    int result1 = vec1 * vec2;
	int result2 = vec1 * vec1;

    assert(result1 == 0);
	assert(result2 == 30);
	try{
		int result3=vec1 * vec3;
		assert(false);
	}
	catch(std::invalid_argument const e){
		assert(true);
	}
}

void TestScalarMultiplication() {
    ECVector<double> vec1({1.0, 2.0, 3.0, 4.0});
    ECVector<double> result1 = vec1 * 2;
	ECVector<double> result2 = 0.5 * vec1;
	
    assert(result1[0] == 2.0);
    assert(result1[1] == 4.0);
    assert(result1[2] == 6.0);
    assert(result1[3] == 8.0);
	assert(result2[0] == 0.5);
    assert(result2[1] == 1.0);
    assert(result2[2] == 1.5);
    assert(result2[3] == 2.0);
}

void TestScalarDivision() {
    ECVector<float> vec1({2.0, 3.0, 4.0});
    ECVector<float> result1 = vec1 / 2;
	ECVector<float> result2 = vec1 / 0.5;
	ECVector<float> result3 = 1.0 / vec1;
	
    assert(result1[0] == 1.0);
    assert(result1[1] == 1.5);
    assert(result1[2] == 2.0);
    assert(result2[0] == 4.0);
    assert(result2[1] == 6.0);
    assert(result2[2] == 8.0);
    assert(result3[0] == 0.5);
    assert(result3[1] == (float)(1.0/3.0));
    assert(result3[2] == 0.25);
}

int main() {
    TestInit();
    TestElementAccess();
    TestCopyConstructor();
    TestMoveConstructor();
	TestMagnitude();
	TestNormalization();
    TestVectorAddition();
    TestVectorSubtraction();
    TestDotProduct();
    TestScalarMultiplication();
    TestScalarDivision();

    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}
