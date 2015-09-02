#include "XmlWriter.h"

bool XmlWriter::exists(const std::string fileName)
{
	std::fstream checkFile(fileName);
	return checkFile.is_open();
}

bool XmlWriter::open(const std::string strFile)
{
	outFile.open(strFile);
	if (outFile.is_open())
	{
		outFile << "<?xml version=\"1.0\"?>\n";
		indent = 0;
		openTags = 0;
		openElements = 0;
		return true;
	}
	if (exists(strFile))
	{
		std::cerr << "Error: File already exists.\n";
		return false;
	}
	return false;
}

void XmlWriter::close()
{
	if (outFile.is_open())
	{
		outFile.close();
	}
	else
	{
		std::cerr << "File already closed.\n";
	}
}

void XmlWriter::writeOpenTag(const std::string openTag)
{
	if (outFile.is_open())
	{
		for (int i = 0; i < indent; i++)
		{
			outFile << "\t";
		}
		tempOpenTag.resize(openTags + 1);
		outFile << "<" << openTag << ">\n";
		tempOpenTag[openTags] = openTag;
		indent += 1;
		openTags += 1;
	}
	else
	{
		std::cerr << "File is closed. Unable to write to file.\n";
	}
}

void XmlWriter::writeCloseTag()
{
	if (outFile.is_open())
	{
		indent -= 1;
		for (int i = 0; i < indent; i++)
		{
			outFile << "\t";
		}
		outFile << "</" << tempOpenTag[openTags - 1] << ">\n";
		tempOpenTag.resize(openTags - 1);
		openTags -= 1;
	}
	else
	{
		std::cerr << "File is closed. Unable to write to file.\n";
	}
}

void XmlWriter::writeStartElementTag(const std::string elementTag)
{
	if (outFile.is_open())
	{
		for (int i = 0; i < indent; i++)
		{
			outFile << "\t";
		}
		tempElementTag.resize(openElements + 1);
		tempElementTag[openElements] = elementTag;
		openElements += 1;
		outFile << "<" << elementTag;
	}
	else
	{
		std::cerr << "File is closed. Unable to write to file.\n";
	}
}

void XmlWriter::writeEndElementTag()
{
	if (outFile.is_open())
	{
		outFile << "</" << tempElementTag[openElements - 1] << ">\n";
		tempElementTag.resize(openElements - 1);
		openElements -= 1;
	}
	else
	{
		std::cerr << "File is closed. Unable to write to file.\n";
	}
}

void XmlWriter::writeAttribute(const std::string outAttribute)
{
	if (outFile.is_open())
	{
		outFile << " " << outAttribute;
	}
	else
	{
		std::cerr << "File is closed. Unable to write to file.\n";
	}
}

void XmlWriter::writeString(const std::string outString)
{
	if (outFile.is_open())
	{
		outFile << ">" << outString;
	}
	else
	{
		std::cerr << "File is closed. Unable to write to file.\n";
	}
}

std::string XmlWriter::getCurrentDateTime()
{
	time_t currentTime;
	struct tm *localTime;
	std::string currentDateTime;
	std::string lowDash = "_";
	std::string standartDash = "-";
	time(&currentTime);                   // Get the current time
	localTime = localtime(&currentTime);  // Convert the current time to the local time

	int Day = localTime->tm_mday;
	int Month = localTime->tm_mon + 1;
	int Year = localTime->tm_year + 1900;
	int Hour = localTime->tm_hour;
	int Min = localTime->tm_min;
	int Sec = localTime->tm_sec;

	std::string sDay;
	std::string sMonth;

	if (Day < 10)
	{
		sDay = std::to_string(Day);
		sDay.insert(0, "0");
	}
	else
	{
		sDay = std::to_string(Day);
	}

	if (Month < 10)
	{
		sMonth = std::to_string(Month);
		sMonth.insert(0, "0");
	}
	else
	{
		sMonth = std::to_string(Month);
	}

	currentDateTime = "(";
	currentDateTime.append(sDay);
	currentDateTime.append(lowDash);
	currentDateTime.append(sMonth);
	currentDateTime.append(lowDash);
	currentDateTime.append(std::to_string(Year));
	currentDateTime.append(")");
	currentDateTime.append(lowDash);
	currentDateTime.append("(");
	currentDateTime.append(std::to_string(Hour));
	currentDateTime.append(standartDash);
	currentDateTime.append(std::to_string(Min));
	currentDateTime.append(standartDash);
	currentDateTime.append(std::to_string(Sec));
	currentDateTime.append(")");

	return currentDateTime;
}

std::string XmlWriter::getCurrentTime(std::string input)
{
	int pos = input.find_last_of("(");
	return input.substr(pos + 1, input.size() - pos - 2);
}

void XmlWriter::writeXmlToFile(std::string startGame, std::string endGame, int time, int realTime,
	double startCredit, double playerBet, double playerWin, double coef)
{
	//Fix path -------------------------------------------------------------------------------
	std::string path = "../../XML/";
	std::string gameName = "Rally";
	std::string pcName = getenv("COMPUTERNAME");
	std::string fileFormat = ".xml";

	std::ostringstream sstream;
	std::string strToPass;

	XmlWriter xml;
	std::string lowDash = "_";
	std::string xmlNamer;

	xmlNamer = path;
	xmlNamer.append(gameName);
	xmlNamer.append(lowDash);
	xmlNamer.append(pcName);
	xmlNamer.append(lowDash);
	xmlNamer.append(getCurrentDateTime());
	xmlNamer.append(fileFormat);

	xml.open(xmlNamer);

	xml.writeOpenTag("RALLY");

	xml.writeStartElementTag("STARTGAME");
	xml.writeString(startGame);
	xml.writeEndElementTag();

	xml.writeStartElementTag("ENDGAME");
	xml.writeString(endGame);
	xml.writeEndElementTag();

	xml.writeStartElementTag("TIME");
	xml.writeString(std::to_string(time));
	xml.writeEndElementTag();

	xml.writeStartElementTag("REALTIME");
	xml.writeString(std::to_string(realTime));
	xml.writeEndElementTag();

	xml.writeStartElementTag("STARTCREDIT");
	xml.writeString(std::to_string(startCredit));
	xml.writeEndElementTag();

	xml.writeStartElementTag("PLAYERBET");
	xml.writeString(std::to_string(playerBet));
	xml.writeEndElementTag();

	xml.writeStartElementTag("PLAYERWIN");
	xml.writeString(std::to_string(playerWin));
	xml.writeEndElementTag();

	xml.writeStartElementTag("COEF");
	xml.writeString(std::to_string(coef));
	xml.writeEndElementTag();

	xml.writeCloseTag();

	xml.close();
}