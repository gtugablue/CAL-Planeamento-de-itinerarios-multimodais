#include <iostream>
#include <sstream>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;

int main()
{
	// 1. Parse a JSON string into DOM.
	ifstream infile("data/linestops/201-0.txt");
	stringstream ss;
	ss << infile.rdbuf();
	rapidjson::Document d;
	d.Parse(ss.str().c_str());
	infile.close();

	// 2. Modify it by DOM.
	rapidjson::Value& s = d["totalRecords"];
	s.SetInt(s.GetInt() + 1);

	// 3. Stringify the DOM
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	d.Accept(writer);

	// Output {"project":"rapidjson","stars":11}
	std::cout << buffer.GetString() << std::endl;
	return 0;
}
