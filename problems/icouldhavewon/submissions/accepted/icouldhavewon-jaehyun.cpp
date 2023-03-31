#include<iostream>
#include<string>
#include<vector>
using namespace std;
int main()
{
	string a;
	cin >> a;
	vector<int> ans;
	for(int k=1;k<=a.size();++k)
	{
		int alice_set = 0, bob_set = 0;
		int alice_point = 0, bob_point = 0;
		for(int i=0;i<a.size();++i)
		{
			if(a[i]=='A') alice_point++;
			if(a[i]=='B') bob_point++;
			if(alice_point==k) { alice_set++; alice_point = bob_point = 0; }
			if(bob_point==k) { bob_set++; alice_point = bob_point = 0; }
		}
		if(alice_set > bob_set) ans.emplace_back(k);
	}
	cout << ans.size() << endl;
	for(auto k: ans) cout << k << " ";
	cout << endl;
	return 0;
}
