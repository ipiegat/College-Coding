//DO NOT MODIFY THIS FILE
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include "ECSplitIntervals.cpp"

using namespace std;

void printIntervals(vector<pair<int,int>> intervals){
	//prints vector of pairs
	cout<<"[";
	for (auto i=intervals.begin();i!=intervals.end();i++){
		cout<<"("+to_string(i->first)+","+to_string(i->second)+")";
		if (intervals.size()!=1 && i!=intervals.end()-1){
			cout<<", ";
		}
	}
	cout<<"]"<<endl;
}

bool testEqual(vector<pair<int,int>> output, vector<pair<int,int>> expected){
	//tests if two vectors of pairs are equal, ignoring order
	if (output.size()!=expected.size()){
		return false;
	}
	for (pair p : expected){
		if (count(expected.begin(),expected.end(),p)!=count(output.begin(),output.end(),p)){
			return false;
		}
	}
	return true;
}

bool Test1(){
	cout<<endl<<"Test 1"<<endl;
	vector<pair<int,int>> intervals = {{1,6},{7,10},{11,12}};
	const vector<int> vals_to_remove = {3,9};
	vector<pair<int,int>> expected = {{1,2},{4,6},{7,8},{10,10},{11,12}};
	splitIntervals(intervals, vals_to_remove);
	cout<<"output:          ";
	printIntervals(intervals);
	cout<<"expected output: ";
	printIntervals(expected);
	if (testEqual(intervals,expected)){
		cout<<"TEST PASSED"<<endl;
		return true;
	}
	cout<<"TEST FAILED"<<endl;
	return false;
}

bool Test2(){
	cout<<endl<<"Test 2"<<endl;
	vector<pair<int,int>> intervals = {{1,10},{7,9},{7,9}};
	const vector<int> vals_to_remove = {4,8};
	vector<pair<int,int>> expected = {{1,3},{5,7},{9,10},{7,7},{9,9},{7,7},{9,9}};
	splitIntervals(intervals, vals_to_remove);
	cout<<"output:          ";
	printIntervals(intervals);
	cout<<"expected output: ";
	printIntervals(expected);
	if (testEqual(intervals,expected)){
		cout<<"TEST PASSED"<<endl;
		return true;
	}
	cout<<"TEST FAILED"<<endl;
	return false;
}

bool Test3(){
	cout<<endl<<"Test 3"<<endl;
	vector<pair<int,int>> intervals = {{1,3},{3,5},{6,10}};
	const vector<int> vals_to_remove = {3,6,10};
	vector<pair<int,int>> expected = {{1,2},{4,5},{7,9}};
	splitIntervals(intervals, vals_to_remove);
	cout<<"output:          ";
	printIntervals(intervals);
	cout<<"expected output: ";
	printIntervals(expected);
	if (testEqual(intervals,expected)){
		cout<<"TEST PASSED"<<endl;
		return true;
	}
	cout<<"TEST FAILED"<<endl;
	return false;
}

int main(){
	if (!Test1()){return -1;}
	if (!Test2()){return -1;}
	if (!Test3()){return -1;}
	cout<<endl<<"ALL TESTS PASS"<<endl;
	return 0;
}