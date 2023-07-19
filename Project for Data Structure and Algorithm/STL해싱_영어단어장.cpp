#include <map>
#include <string>
#include <iostream>
#include <cstdio>
using namespace std;

int main() {

	map<string, string> myDic;
	map<string, string>::iterator dp; //�ʿ� ���� �ݺ���
	myDic["hello"] = "�ȳ��ϼ���?";
	myDic["world"] = "�Ƹ��ٿ� ����";
	myDic["data"] = "������";
	myDic["structure"] = "����, ����ü";
	myDic["list"] = "����Ʈ";
	myDic["Pain past is pleasure"] = "������ ������ ��ſ��̴�."; //õ�α� ������ ����... �Ф�
	myDic["Habit is second nature"] = "������ ��2�� õ���̴�.";
	myDic["No pain No gain"] = "���� ���̴� ��� �͵� ����.";

	//���
	for (dp = myDic.begin(); dp != myDic.end(); ++dp) {
		printf("%20s = %s\n", dp->first.c_str(), dp->second.c_str());
	}

	//���2
	dp = myDic.find("structure");
	if (dp == myDic.end()) { printf("�˻� ����: ã�� �ܾ �����ϴ�.\n"); }
	else { printf("�˻� ����: %s ---> %s\n", dp->first.c_str(), dp->second.c_str()); }

	//���3
	dp = myDic.find("algorithm");
	if (dp == myDic.end()) { printf("�˻� ����: ã�� �ܾ �����ϴ�.\n"); }

	//���4
	myDic.erase("list");
	dp = myDic.find("structure");
	myDic.erase(dp);
	for (dp = myDic.begin(); dp != myDic.end(); ++dp) {
		printf("%20s = %s\n", dp->first.c_str(), dp->second.c_str());
	}

	return 0;
}