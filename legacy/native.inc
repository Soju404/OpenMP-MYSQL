stock CharacterSetup(playerid)
{
	PlayerData[playerid][pSkin] = 20001;
	SetSpawnInfo(playerid, PlayerData[playerid][pSkin], 0, 2495.3547, -1688.2319, 13.6774, 351.1646, 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);
	SetPlayerHealth(playerid, 100.0);
	return 1;
}

stock GetName(playerid)
{
    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));
    return name;
}

stock ReturnIP(playerid)
{
    new name[MAX_PLAYER_NAME];
    GetPlayerIp(playerid, name, sizeof(name));
    return name;
}

stock KickEx(playerid)
{
	SetTimerEx("KickTimer", 400, false, "d", playerid);
}

function KickTimer(playerid)
{
	Kick(playerid);
}

stock SendClientMessageEx(playerid, color, const text[], {Float, _}:...)
{
    static
        args,
            str[144];

    if((args = numargs()) == 3)
    {
            SendClientMessage(playerid, color, text);
    }
    else
    {
        while (--args >= 3)
        {
            #emit LCTRL 5
            #emit LOAD.alt args
            #emit SHL.C.alt 2
            #emit ADD.C 12
            #emit ADD
            #emit LOAD.I
            #emit PUSH.pri
        }
        #emit PUSH.S text
        #emit PUSH.C 144
        #emit PUSH.C str
        #emit PUSH.S 8
        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        SendClientMessage(playerid, color, str);

        #emit RETN
    }
    return 1;
}