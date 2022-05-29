#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <Heads/shttplib.h>
#include "Helper.h"
#include <Nlohmann/json.hpp>
#include <magic_enum/magic_enum.hpp>
#include "Global.h"

using json = nlohmann::json;
using namespace std;

json getVersion() {
	httplib::SSLClient cli("api.github.com",443);
	string errorMessage = "Error";
	if (auto res = cli.Get("/repos/dreamguxiang/BEPlaceholderAPI/releases/latest")) {
		//���ʳɹ�
		if (res->status == 200) {
			json j = res->body;
			json sj;
			if (j.find("tag_name") != j.end() && j.find("name") != j.end() && j.find("body") != j.end()) {
				sj["tag_name"] = j["tag_name"];
				sj["name"] = j["name"];
				sj["body"] = j["body"];
				sj["code"] = 0;
				sj["message"] = "success.";
				return sj;
			}
			else {
				if (j.find("message") == j.end()) {
					errorMessage = "Unkown error.";
				}
				else {
					errorMessage = j["message"].get<string>();
				}
				
			}
			
		}
		else {
			errorMessage = "Access failed. HTTP error code:" + to_string(res->status);
		}
	}
	else {
		errorMessage = "The request is error in "+string(magic_enum::enum_name(res.error()));
	}
	json j;
	j["message"] = errorMessage;
	j["code"] = 1;
	return j;
}


vector<string> m_split(const string& str, const string& delim) {
	vector<string> res;
	if ("" == str) return res;
	//�Ƚ�Ҫ�и���ַ�����string����ת��Ϊchar*����
	char* strs = new char[str.length() + 1]; //��Ҫ����
	strcpy(strs, str.c_str());

	char* d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	char* p = strtok(strs, d);
	while (p) {
		string s = p; //�ָ�õ����ַ���ת��Ϊstring����
		res.push_back(s); //����������
		p = strtok(NULL, d);
	}

	return res;
}

void checkVersion() {
	json versionJson = getVersion();
	if (versionJson["code"] == 0) {
		string nowVersion = to_string(PLUGIN_VERSION_MAJOR) + "." + to_string(PLUGIN_VERSION_MINOR) + "." + to_string(PLUGIN_VERSION_REVISION);
		string tagName = versionJson["tag_name"].get<string>();
		string body = versionJson["body"].get<string>();
		if ("v" + nowVersion != tagName) {
			logger.warn(
				"A new version update has been detected. The updated content is as follows\nName:{}\nBody:{}\nTagName:{}",
				versionJson["name"].get<string>(),
				ReplaceStr(body,"\\n","\n"),
				tagName);
		}
		
	}
	else {
		logger.error(versionJson["message"].get<string>());
	}
}

