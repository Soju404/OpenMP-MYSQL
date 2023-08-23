function OnPlayerLoaded(playerid, race_check)
{
    if (race_check != g_MysqlRaceCheck[playerid]) return Kick(playerid);

    new str[256];
	if(cache_num_rows() > 0)
    {
        cache_get_value_name(0, "password", PlayerData[playerid][pPassword], 65);

    	format(str, sizeof(str), "{FFFFFF}Welcome back to Realized {FFFF00}%s\n{FFFFFF}Current IP: {FF0606}%s\n\n{FFFFFF}Kamu diberikan waktu {FFFF00}3 menit {FFFFFF}untuk memasukan password dan login atau akan dikick dari server\nSilahkan masukan password account anda pada kolom dibawah ini:\n\n{FF6347}ATTEMPT: {FFFFFF}Kesempatan login teersisa {FFFF00}%d{FFFFFF}/{FF0000}3 {FFFFFF}kali lagi.", GetName(playerid), ReturnIP(playerid));
	    ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Login to Realized", str, "Login", "Exit");
	
		SetPlayerSkin(playerid, 20001);
		SetPlayerPos(playerid, 217.8511, -98.4865, 1005.2578);
		SetPlayerFacingAngle(playerid, 113.8861);
		SetPlayerInterior(playerid, 15);
		SetPlayerCameraPos(playerid, 215.2182, -99.5546, 1006.4);
		SetPlayerCameraLookAt(playerid, 217.8511, -98.4865, 1005.2578);
		ApplyAnimation(playerid, "benchpress", "gym_bp_celebrate", 4.1, true, false, false, false, 0, SYNC_NONE);

		// from now on, the player has 30 seconds to login
		PlayerData[playerid][pLoginTimer] = SetTimerEx("OnLoginTimeout", SECONDS_TO_LOGIN * 1000, false, "d", playerid);
    }
    else
	{
	    format(str, sizeof(str), "{FFFFFF}Welcome to Realized {FFFF00}%s\n{FFFFFF}Current IP: {FF0606}%s\n\n{FFFFFF}Untuk register kamu harus membuat password account-mu terlebih dahulu\nNote: Minimal 7 huruf/angka dan Maksimal 32 huruf/angka\n\nSilahkan masukkan password untuk melanjutkan register ke kolom dibawah ini:", GetName(playerid), ReturnIP(playerid));
        ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "Register to Realized", str, "Register", "Exit");
	}
    return 1;
}

function OnPlayerDataLoaded(playerid)
{
	cache_get_value_name_int(0, "pID", PlayerData[playerid][pID]);
	cache_get_value_name(0, "username", PlayerData[playerid][pName]);
	SetSpawnInfo(playerid, 20001, 0,  2495.3547, -1688.2319, 13.6774, 351.1646, WEAPON_M4, 500, WEAPON_KNIFE, 1, WEAPON_COLT45, 100);
	SpawnPlayer(playerid);

	PlayerData[playerid][pLogged] = true;
    return 1;
}

function HashPlayerPassword(playerid, hashid)
{
	new
		query[256],
		hash[BCRYPT_HASH_LENGTH];

    bcrypt_get_hash(hash, sizeof(hash));

	GetPlayerName(playerid, PlayerData[playerid][pName], MAX_PLAYER_NAME + 1);

	mysql_format(sqlHandle, query,sizeof(query),"INSERT INTO `players` (`username`, `password`, `registered`) VALUES ('%s', '%s', '%d')", PlayerData[playerid][pName], hash, gettime());
	mysql_query(sqlHandle, query, true);

	CharacterSetup(playerid);
    SendServerMessage(playerid, "Your UCP is successfully registered!");
	return 1;
}


function OnPlayerPasswordChecked(playerid, bool:success)
{
	new str[256];
    format(str, sizeof(str), "{FFFFFF}Welcome back to Realized {FFFF00}%s\n{FFFFFF}Current IP: {FF0606}%s\n\n{FFFFFF}Kamu diberikan waktu {FFFF00}3 menit {FFFFFF}untuk memasukan password dan login atau akan dikick dari server\nSilahkan masukan password account anda pada kolom dibawah ini:\n\n{FF6347}ATTEMPT: {FFFFFF}Kesempatan login teersisa {FFFF00}%d{FFFFFF}/{FF0000}3 {FFFFFF}kali lagi.", GetName(playerid), ReturnIP(playerid));
    
	if(!success)
	{
	    if(PlayerData[playerid][pAttempt] < 5)
	    {
		    PlayerData[playerid][pAttempt]++;
	        ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Login to Realized", str, "Login", "Exit");
		}
		else
		{
		    SendServerMessage(playerid, "Kamu telah salah memasukan password sebanyak {FFFF00}3 kali!");
		    KickEx(playerid);
		}
	}
	else
	{
		new query[103];
		mysql_format(sqlHandle, query, sizeof query, "SELECT * FROM `players` WHERE `username` = '%e' LIMIT 1", PlayerData[playerid][pName]);
		mysql_tquery(sqlHandle, query, "OnPlayerDataLoaded", "d", playerid);
	}
	return 1;
}

function OnLoginTimeout(playerid)
{
	SendServerMessage(playerid, "Kamu login terlalu lama!");
	KickEx(playerid);
	return 1;
}