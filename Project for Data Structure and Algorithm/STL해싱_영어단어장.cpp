#include <map>
#include <string>
#include <iostream>
#include <cstdio>
using namespace std;

int main() {

	map<string, string> myDic;
	map<string, string>::iterator dp; //맵에 대한 반복자
	myDic["hello"] = "안녕하세요?";
	myDic["world"] = "아름다운 세상";
	myDic["data"] = "데이터";
	myDic["structure"] = "구조, 구조체";
	myDic["list"] = "리스트";
	myDic["Pain past is pleasure"] = "지나간 고통은 즐거움이다."; //천인국 교수님 감동... ㅠㅠ
	myDic["Habit is second nature"] = "습관은 제2의 천성이다.";
	myDic["No pain No gain"] = "고통 없이는 얻는 것도 없다.";

	//출력
	for (dp = myDic.begin(); dp != myDic.end(); ++dp) {
		printf("%20s = %s\n", dp->first.c_str(), dp->second.c_str());
	}

	//출력2
	dp = myDic.find("structure");
	if (dp == myDic.end()) { printf("검색 실패: 찾는 단어가 없습니다.\n"); }
	else { printf("검색 성공: %s ---> %s\n", dp->first.c_str(), dp->second.c_str()); }

	//출력3
	dp = myDic.find("algorithm");
	if (dp == myDic.end()) { printf("검색 실패: 찾는 단어가 없습니다.\n"); }

	//출력4
	myDic.erase("list");
	dp = myDic.find("structure");
	myDic.erase(dp);
	for (dp = myDic.begin(); dp != myDic.end(); ++dp) {
		printf("%20s = %s\n", dp->first.c_str(), dp->second.c_str());
	}

	return 0;
}