#if defined _sampyt_included
	#endinput
#endif
#define _sampyt_included

#include <omp_http>
#include <a_json>

#if !defined SAMPYT_URL
	#error "Voce precisa definir a URL do seu YT-Conversor!"
#endif

static
	bool:sampyt_wait[MAX_PLAYERS],
	JSONNode:sampyt_cache[MAX_PLAYERS];

stock SampYT_SearchTitle(id, const title[], limit = 1, const region[] = "BR")
{
	static link[128], args[128];
	json_close(sampyt_cache[id]);
	format(link, sizeof(link), "%s/search.php", SAMPYT_URL);
	format(args, sizeof(args), "title=%s&limit=%d&region=%s", title, limit, region);

	clink(link), clink(args);
	HTTP(id, HTTP_GET, link, args, "SAMPYT_SEARCH");
}

stock SampYT_ExtractAudio(id, const videoid[], quality = 5)
{
	if(!sampyt_wait[id])
	{
		static link[128], args[128];
		format(link, sizeof(link), "%s/convert.php", SAMPYT_URL);
		format(args, sizeof(args), "videoid=%s&quality=%d", videoid, quality);

		clink(link), clink(args);
		HTTP(id, HTTP_GET, link, args, "SAMPYT_EXTRACT");
		sampyt_wait[id] = true;
	}
}

stock JSONNode:SampYT_GetCache(index)
{
	return sampyt_cache[index];
}

stock SampYT_GetLink(index)
{
	static link[128];
	if(existproperty(index, "sampyt_link"))
	{
		getproperty(index, "sampyt_link", .string = link);
		deleteproperty(index, "sampyt_link");
	}
	return link;
}

static stock clink(link[])
{
	static i;
	for(i = 0; i < strlen(link); i++)
		if(link[i] == ' ') link[i] = '+';
}

forward SAMPYT_SEARCH(index, code, data[]);
public SAMPYT_SEARCH(index, code, data[])
{
	if(code == 200)
	{
		sampyt_cache[index] = json_parse_string(data);
		CallLocalFunction("SampYT_ReceiveData", "d", index);
	}
	else
	{
		CallLocalFunction("SampYT_FunctionError", "dds", index, code, "SampYT_SearchVideo");
	}
	return 1;
}

forward SAMPYT_EXTRACT(index, code, data[]);
public SAMPYT_EXTRACT(index, code, data[])
{
	if(code == 200)
	{
		sampyt_wait[index] = false;
		setproperty(index, "sampyt_link", .string = data);
		CallLocalFunction("SampYT_ReceiveLink", "d", index);
	}
	else
	{
		CallLocalFunction("SampYT_FunctionError", "dds", index, code, "SampYT_ExtractAudio");
	}
	return 1;
}

forward SampYT_ReceiveData(index);
forward SampYT_ReceiveLink(index);