#include<iostream>
#include<vector>
using namespace std;

void SplitString(string s, vector<string> &v){
	
	string temp = "";
	for(int i=0;i<s.length();++i){
		
		if(s[i]==' '){
			v.push_back(temp);
			temp = "";
		}
		else{
			temp.push_back(s[i]);
		}
		
	}
	v.push_back(temp);
	
}

template<typename T>
void PrintVector(vector<T> v){
	for(int i=0;i<v.size();++i)
		cout<<v[i]<<endl;
	cout<<"\n";
}

int main()
{
	vector<string> v;
	string s = "Hello! My name is John Smith.";
	cout<<"Input String: "<<endl<<s<<endl;
	SplitString(s, v);
	cout<<"String After Split"<<endl;
	PrintVector(v);
	
}