#include "GameData.h"

DataHandler * DataHandler::GetSingleton()
{
	return *((DataHandler **)0x012B219C);
}
