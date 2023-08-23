public SampYT_ReceiveData(index)
{
	new string[2048], JSONNode:json = SampYT_GetCache(index);
	json_get_string(json, string, sizeof(string), "result");
	
	json = json_parse_string(string);
	json_get_string(json, string, sizeof(string), "id");
	json_close(json);
	
	SampYT_ExtractAudio(index, string);
	return 1;
}

public SampYT_ReceiveLink(index)
{
	PlayAudioStreamForPlayer(index, SampYT_GetLink(index));
	return 1;
}

CMD:audio(playerid, params[])
{
    new audio[32];
    if(sscanf(params, "s[32]", audio)) return SendSyntaxMessage(playerid, "/audio [title]");
    SampYT_SearchTitle(playerid, audio);
    return 1;
}