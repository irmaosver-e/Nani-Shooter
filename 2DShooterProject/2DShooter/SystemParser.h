#ifndef __SystemParser__
#define __SystemParser__

#include "Parser.h"

class SystemParser : public Parser
{
public:
	SystemParser() {}
	~SystemParser() {}
	bool parseSystem(const char* configFile);

private:
	bool parseWindow(TiXmlElement* pWindowRoot);
	bool parseInput(TiXmlElement* pInputRoot);
	bool parseSound(TiXmlElement* pSoundRoot);
	bool parseFonts(TiXmlElement* pFontsRoot);
	bool parseFiles(TiXmlElement* pFilesRoot);
};

#endif /* defined ( __SystemParser__ ) */
