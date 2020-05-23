search this function:

bool CClientManager::InitializeLandTable()

And look this:

	char query[4096];

Add below this:

#ifdef __ENABLE_CLEAR_OLD_GUILD_LANDS__
	CDBManager::instance().DirectQuery(
		"update land "
		"INNER JOIN guild ON land.guild_id = guild.id "
		"INNER JOIN player ON guild.`master` = player.id "
		"set guild_id=0 "
		"where guild_id > 0 and "
		"DATE_SUB(NOW(),INTERVAL 21 DAY) > last_play; "
	);

	CDBManager::instance().DirectQuery(
		"DELETE object "
		"FROM object "
		"INNER JOIN land ON land.id = object.land_id "
		"WHERE land.guild_id=0; "
	);
#endif
