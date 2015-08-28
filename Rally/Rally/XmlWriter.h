#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Globals.h"

class XmlWriter
{
public:
	bool open(const std::string);
	void close();
	bool exists(const std::string);
	void writeOpenTag(const std::string);
	void writeCloseTag();
	void writeStartElementTag(const std::string);
	void writeEndElementTag();
	void writeAttribute(const std::string);
	void writeString(const std::string);
	std::string getCurrentDateTime();
	std::string getCurrentTime(std::string);
	void XmlWriter::writeXmlToFile(std::string, std::string, int, int, double, double, double, double);
private:
	std::ofstream outFile;
	int indent;
	int openTags;
	int openElements;
	std::vector<std::string> tempOpenTag;
	std::vector<std::string> tempElementTag;
};