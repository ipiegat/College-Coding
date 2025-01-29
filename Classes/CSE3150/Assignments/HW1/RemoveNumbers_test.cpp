// this file is used to test the RemoveSpaces.cpp file
// Only submit RemoveNubers.cpp
#include <iostream>

using namespace std;

#include <string>
#include "RemoveNumbers.h"

string RemoveNumbers(string);

int main()
{
	string s1 = "998I132 4l642o356v577e4 4t81399o032 1057p1245r11o4442g747r330a887m7 761i3321n6 42C3+4+80!1";
	string s2 = "I have 2 sisters and 1 brother. They are 9, 13, and 17 years old.";
	string s3 = "1234567890";
	string s4 = "I live on 123 Main Street.";
	cout<<RemoveNumbers(s1)<<endl;
	cout<<RemoveNumbers(s2)<<endl;
	cout<<RemoveNumbers(s3)<<endl;
	cout<<RemoveNumbers(s4)<<endl;
	return 0;
}
