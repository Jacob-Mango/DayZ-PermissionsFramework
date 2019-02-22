modded class MissionServer
{
    protected ref PermissionsFramework m_PermissionsFramework;

    void MissionServer()
    {        
        m_PermissionsFramework = new ref PermissionsFramework;
    }

    void ~MissionServer()
    {
        delete m_PermissionsFramework;
    }

    override void OnInit()
    {
        super.OnInit();
    }

    override void OnMissionStart()
    {
        super.OnMissionStart();

        m_PermissionsFramework.OnStart();
    }

    override void OnMissionFinish()
    {
        m_PermissionsFramework.OnFinish();

        super.OnMissionFinish();
    }

    override void OnUpdate( float timeslice )
    {
        super.OnUpdate( timeslice );

        m_PermissionsFramework.Update( timeslice );
    }

// TODO: Fully implement this as a better way for permissions
/*
    override void OnEvent( EventType eventTypeId, Param params ) 
	{
		super.OnEvent( eventTypeId, params );
		PlayerIdentity identity;

		switch(eventTypeId)
		{
			case ChatMessageEventTypeID:
                ChatMessageEventParams chat_params = ChatMessageEventParams.Cast( params );

                if ( chat_params.param1 == 0 && chat_params.param2 != "" )
                {
                    if ( chat_params.param3 == "/givefull" )
                    {

                    }
                }
                break;
		}
	}
*/

	override void OnPreloadEvent(PlayerIdentity identity, out bool useDB, out vector pos, out float yaw, out int queueTime)
	{
        super.OnPreloadEvent( identity, useDB, pos, yaw, queueTime );

        GetPermissionsManager().GetPlayerByIdentity( identity );
    }

    override void InvokeOnConnect( PlayerBase player, PlayerIdentity identity)
	{
        super.InvokeOnConnect( player, identity );
        
        for ( int i = 0; i < GetPermissionsManager().Roles.Count(); i++ )
        {
            ref Role role = GetPermissionsManager().Roles[i];
            role.Serialize();
            GetRPCManager().SendRPC( "PermissionsFramework", "UpdateRole", new Param2< string, ref array< string > >( role.Name, role.SerializedData ), true, identity );
        }

        GetRPCManager().SendRPC( "PermissionsFramework", "SetClientPlayer", new Param1< ref PlayerData >( SerializePlayer( GetPermissionsManager().GetPlayerByIdentity( identity ) ) ), true, identity );

        GetGame().SelectPlayer( identity, player );
    } 

    override void PlayerDisconnected( PlayerBase player, PlayerIdentity identity, string uid )
	{
        GetPermissionsManager().PlayerLeft( identity );

        super.PlayerDisconnected( player, identity, uid );
    } 

}
