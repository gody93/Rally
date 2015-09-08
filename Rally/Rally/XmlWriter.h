#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Globals.h"

class XmlWriter
{
public:
	//Checks if file is open
	bool open(const std::string);
	//Closes the file
	void close();
	//Checks if the file exists;
	bool exists(const std::string);
	// Self explanatory
	void writeOpenTag(const std::string);
	void writeCloseTag();
	void writeStartElementTag(const std::string);
	void writeEndElementTag();
	void writeAttribute(const std::string);
	void writeString(const std::string);
	std::string getCurrentDateTime();
	std::string getCurrentTime(std::string);
	//Creates XML file with given values
	void XmlWriter::writeXmlToFile(std::string, std::string, int, int, double, double, double, double);
private:
	std::ofstream outFile;
	int indent;
	int openTags;
	int openElements;
	std::vector<std::string> tempOpenTag;
	std::vector<std::string> tempElementTag;
};
