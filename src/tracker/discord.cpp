/*
 *  tracker/discord.cpp
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

#include "discord.h"
#include <ctime>
#include "discord_rpc.h"
#include <string>
#include <assert.h>
#include <cstring>
#include "BasicTypes.h"

std::unique_ptr<Discord> g_discord;
const std::string Discord::s_application_id = "903976700570906644";

struct DataRichPresence
{
	std::string state = "";
	std::string details = "";
	uint64_t start_timestamp;
	std::string large_image_key = "default";
	std::string small_image_key = "";
	std::string party_id = "";
	uint32_t party_size = 0;
	uint32_t party_max = 0;
};

Discord::Discord()
{
	m_data = std::unique_ptr<DataRichPresence>(new DataRichPresence);
	m_data->start_timestamp = time(0);
}

Discord::~Discord()
{
	Discord_Shutdown();
}

std::unique_ptr<Discord> Discord::createDiscordSingleton()
{
	assert(!g_discord);
	return std::unique_ptr<Discord>(new Discord());
}

void Discord::init()
{
	DiscordEventHandlers handlers{};
	/*
		Handlers list :
		ready, disconnected, errored, joinGame, spectateGame, joinRequest
	*/
	//handlers.ready = Discord::handleDiscordReady;
	//handlers.errored = Discord::handleDiscordError;
	Discord_Shutdown();
	Discord_Initialize(s_application_id.c_str(), &handlers, 1, NULL);
}

void Discord::setState(const std::string &state)
{
	m_data->state = state.substr(0, 128);
}

void Discord::setDetails(const std::string &details)
{
	m_data->details = details.substr(0, 128);
}

void Discord::setStatePP(const PPString &state)
{
	m_data->state = state.getStrBuffer();
}

void Discord::setDetailsPP(const PPString &details)
{
	m_data->details = details.getStrBuffer();
}

void Discord::updatePresence()
{
	DiscordRichPresence discord_presence;
	memset(&discord_presence, 0, sizeof(discord_presence));

	discord_presence.state = m_data->state.c_str();
	discord_presence.details = m_data->details.c_str();
	discord_presence.startTimestamp = m_data->start_timestamp;
	discord_presence.largeImageKey = m_data->large_image_key.c_str();
	discord_presence.smallImageKey = m_data->small_image_key.c_str();
	discord_presence.partyId = m_data->party_id.c_str();
	discord_presence.partySize = m_data->party_size;
	discord_presence.partyMax = m_data->party_max;
	// discord_presence.matchSecret = "4b2fdce12f639de8bfa7e3591b71a0d679d7c93f";
	// discord_presence.spectateSecret = "e7eb30d2ee025ed05c71ea495f770b76454ee4e0";
	// discord_presence.instance = 1;
	Discord_UpdatePresence(&discord_presence);
}

void Discord::handleDiscordReady()
{
}

void Discord::handleDiscordError(int errcode, const char *message)
{
}
