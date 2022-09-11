#include "discordrpc.h"

#include <time.h>
#include <chrono>
static int64_t eptime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

DiscordRichPresence discordPresence;

void Discord::Initialize()
{
    DiscordEventHandlers Handle;
    memset(&Handle, 0, sizeof(Handle));
    Discord_Initialize("954871070555525120", &Handle, 1, NULL);
}

void Discord::State(const char* state)
{
    discordPresence.state = state;
    Discord_UpdatePresence(&discordPresence);
}

void Discord::Details(const char* details)
{
    discordPresence.details = details;
    Discord_UpdatePresence(&discordPresence);
}

void Discord::Update()
{
    memset(&discordPresence, 0, sizeof(discordPresence));
    //discordPresence.state = state;
    //discordPresence.details = details;
    discordPresence.startTimestamp = eptime;
    discordPresence.largeImageKey = "meme";
    discordPresence.largeImageText = "ANARCHY";
    discordPresence.smallImageKey = "hsh";
    discordPresence.smallImageText = "This user have big pp";
    Discord_UpdatePresence(&discordPresence);
}