#pragma once


#include <iostream>
#include <Global.h>
#include <MC/Level.hpp>
#include <MC/Player.hpp>
#include <EventAPI.h>
#include <LoggerAPI.h>
#include <MC/BlockInstance.hpp>
#include <MC/Block.hpp>
#include <MC/BlockSource.hpp>
#include <MC/Actor.hpp>
#include <MC/ItemStack.hpp>
#include "Version.h"
#include <LLAPI.h>
#include <Utils/StringHelper.h>
#include <RemoteCallAPI.h>
#include <ServerAPI.h>
#include <MC/LevelData.hpp>
#include "Setting.h"



extern Logger logger;
#define S(x) std::to_string(x)
#define JsonFile "plugins/BEPlaceholderAPI/config.json"
#define VERSION LL::Version{PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, PLUGIN_VERSION_REVISION, PLUGIN_LLVERSION_STATUS}