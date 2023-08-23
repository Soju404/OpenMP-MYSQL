//server define

#define      mysql_host          "localhost"
#define      mysql_user          "root"
#define      mysql_password      ""
#define      mysql_database      "ompserver"

#define      function%0(%1)      forward %0(%1); public %0(%1)

#define		 SECONDS_TO_LOGIN 	 30

#if !defined BCRYPT_HASH_LENGTH
	#define BCRYPT_HASH_LENGTH 250
#endif

#if !defined BCRYPT_COST
	#define BCRYPT_COST 12
#endif

#define SendServerMessage(%0,%1) \
	SendClientMessageEx(%0, 0x62da92FF, "SERVER:{FFFFFF} "%1)

#define SendSyntaxMessage(%0,%1) \
	SendClientMessageEx(%0, COLOR_GREY, "USAGE:{FFFFFF} "%1)
	
#define SendErrorMessage(%0,%1) \
	SendClientMessageEx(%0, COLOR_GREY, "ERROR: "%1)