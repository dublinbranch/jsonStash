#include "decammelizer.h"
#include "rapidjson/includeMePretty.h"
#include <QDebug>

static rapidjson::Document j1;

QByteArray printJson(const rapidjson::Document& json) {
	rapidjson::StringBuffer                          buffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> WTR(buffer);
	json.Accept(WTR);
	QByteArray res;
	res = buffer.GetString();
	res.detach();
	return res;
}

std::string decammelizer(const std::string& camelCase) {
	// First place underscores between contiguous lower and upper case letters.
	// For example, `_LowerCamelCase` becomes `_Lower_Camel_Case`.
	//first char is out of iter
	std::string snake_case(1, tolower(camelCase[0]));
	for (auto it = camelCase.begin() + 1; it != camelCase.end(); ++it) {
		if (isupper(*it) && *(it - 1) != '_' && islower(*(it - 1))) {
			snake_case += "_";
		}
		snake_case += *it;
	}

	// Then convert it to lower case.
	std::transform(snake_case.begin(), snake_case.end(), snake_case.begin(), ::tolower);

	return snake_case;
}

void loop(rapidjson::GenericValue<rapidjson::UTF8<>>& vX);
void unwindObj(rapidjson::GenericObject<false, rapidjson::GenericValue<rapidjson::UTF8<>>>& obj) {
	for (auto& v : obj) {
		auto       pre     = printJson(j1);
		QByteArray oldName = v.name.GetString();
		if (oldName == "addedByGoogleAds") {
			int x = 0;
		}
		auto neu  = decammelizer(v.name.GetString());
		v.name    = rapidjson::Value(neu.c_str(), j1.GetAllocator()).Move();
		auto post = printJson(j1);
		loop(const_cast<rapidjson::GenericValue<rapidjson::UTF8<>>&>(v.value));
	}
}

void unwindArr(rapidjson::GenericArray<false, rapidjson::GenericValue<rapidjson::UTF8<>>>& arr) {
	uint i = arr.Size();
	do {
		i--;
		loop(const_cast<rapidjson::GenericValue<rapidjson::UTF8<>>&>(arr[i]));
	} while (i > 0);
}

void loop(rapidjson::GenericValue<rapidjson::UTF8<>>& vX) {
	if (vX.IsObject()) {
		auto v1 = vX.GetObject();
		unwindObj(v1);
	} else if (vX.IsArray()) {
		auto v1 = vX.GetArray();
		unwindArr(v1);
	} else {
		//nothing to be done for leaf
	}
}

QByteArray camelTo_snake_case(const QByteArray& original) {

	j1.Parse(original.constData(), original.size());
	loop(j1);
	qDebug().noquote() << printJson(j1);
	return "";
}
