global_cfg = 
{ 
	_name 		= "Fenrir",
	_type 		= "basic_session_manager",
	rule_alg	= "default_rulemgr",
	session_1	= 
	{
		_name 			= "Player1",
		_type 			= "tcp_session",
		group			= "brokers",
		buffer_1		=
		{
			_name			= "bf1",
			_type 			= "async_linked_list_buffer",
		},
		buffer_2		=
		{
			_name 			= "bf2",
			_type 			= "async_fixed_buffer",
			max_size		= "2048",
		}
	},
	session_2	=
	{
		_name			= "System1",
		_type			= "tcp_session",
		group			= "systems",
		buffer_1		=
		{
			_name 			= "bf1",
			_type 			= "sync_linked_list",
		}
	}
}