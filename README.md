```cpp
// 快速幂实现pow功能
constexpr long long quickmul(long long x, long long n){ 
    constexpr long long MOD = 1000000007;
    if(x == 0) return 0;
    if(n==0) return 1;
    long long sum = 1;
    while(n){
        if(n&1) sum = (long long)sum * x % MOD;
        n >>= 1;
        x = (long long)x * x % MOD;
    }
    return sum;
}
```
```cpp
//字符串处理

#include<vector>
#include <sstream>  
#include <iostream>  

//分割为【单词】后进行处理，这是最通用的办法。
void Split(string &line, vector<string> &words)
{
	string word;
	//这个是in string stream 需要#include<sstream>,然后就可以用类似于 cin>>的方式任意处理了。
	istringstream iss(line,istringstream::in);
    
	while (iss >> word)
	{
		words.push_back(word);
	}
}

int main()
{
	string lines ;
	//读入一行，可能会在结尾有\r，但不会包含\n，
	std::getline(cin, lines);
	//删除最后的 \r 如果要split的话，则可不调用
	lines.erase(lines.find_last_of("\r"));
	vector<string> words;
	//分割为每个单词
	Split(lines,words);

	for (int i = 0; i < words.size(); i++)
	{
		cout << words[i] << endl;
	}
}
```

### [202309-3.cpp](202309-3.cpp) 
用string来写hash就可以了