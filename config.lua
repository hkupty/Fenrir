global_cfg = 
{ 
	_name 		= "Fenrir",
	_type 		= "basic_session_manager",
	rule_alg	= "default_rulemgr",
	session_1	= 
	{
		_name 			= "Player1",
		_type 			= "TCP_Session",
		group			= "brokers",
		buffer_1		=
		{
			_name			= "_btc",
			_type 			= "async_linked_list",
		},
		buffer_2		=
		{
			_name 			= "_aco",
			_type 			= "async_fixed",
			max_size		= "2048",
		}
	},
	session_2	=
	{
		_name			= "System1",
		_type			= "UDP_Session",
		group			= "systems",
		buffer_1		=
		{
			_name 			= "_btc",
			_type 			= "sync_linked_list",
		}
	}
}