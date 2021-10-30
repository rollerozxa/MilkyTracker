/*
 *  tracker/discord.h
 *
 *  Copyright 2021 ROllerozxa
 *
 *  This file is part of Milkytracker.
 *
 *  Milkytracker is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Milkytracker is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Milkytracker.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once
#include <iostream>
#include <memory>
#include "BasicTypes.h"

struct DataRichPresence;

class Discord
{
public:
	Discord();
	~Discord();

	static std::unique_ptr<Discord> createDiscordSingleton();
	void init();

	void setState(const std::string &state);
	void setDetails(const std::string &details);
	
	
	void setStatePP(const PPString &state);
	void setDetailsPP(const PPString &details);
	
	void updatePresence();

	static void handleDiscordError(int errcode, const char *message);
	static void handleDiscordReady();

private:
	static const std::string s_application_id;
	std::unique_ptr<DataRichPresence> m_data;
};

extern std::unique_ptr<Discord> g_discord;
