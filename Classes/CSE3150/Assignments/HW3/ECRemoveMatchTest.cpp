//DO NOT MODIFY THIS FILE
#include <vector>
#include <string>
#include <iostream>
#include "ECRemoveMatch.cpp"

using namespace std;

int main(){
	string s1="ABC";
	string *p1=&s1;
	string *p3=p1;
	
	string s2="ABC";
	string *p2=&s2;
	string *p4=p2;
	
	vector<string *> v1={p1,p2,p3};
	vector<string *> v2={p1,p3,p2};
	
	vector<string *> v1_expected={p2};
	vector<string *> v2_expected={p1,p3};
	
	removeMatch(v1,&s1);
	removeMatch(v2,&s2);
	
	cout<<"Test 1"<<endl;
	if (v1==v1_expected){
		cout<<"PASSED"<<endl<<endl; 
	}
	else{ cout<<"FAILED"<<endl<<endl; }
	cout<<"Test 2"<<endl;
	if (v2==v2_expected){
		cout<<"PASSED"<<endl;
	}
	else{ cout<<"FAILED"<<endl; }
	
	return 0;
}