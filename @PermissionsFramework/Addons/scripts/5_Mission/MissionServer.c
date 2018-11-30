modded class MissionServer
{
    protected ref PermissionsFramework m_PermissionsFramework;

    void MissionServer()
    {        
        m_PermissionsFramework = new PermissionsFramework();
    }

    void ~MissionServer()
    {
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

        m_PermissionsFramework.OnUpdate( timeslice );
    }

	override void OnPreloadEvent(PlayerIdentity identity, out bool useDB, out vector pos, out float yaw, out int queueTime)
	{
        super.OnPreloadEvent( identity, useDB, pos, yaw, queueTime );

        GetPermissionsManager().GetPlayerByIdentity( identity );
    }

    override void InvokeOnConnect( PlayerBase player, PlayerIdentity identity)
	{
        super.InvokeOnConnect( player, identity );

        GetPermissionsManager().GetPlayerByIdentity( identity );

        GetGame().SelectPlayer( identity, player );
    } 

    override void InvokeOnDisconnect( PlayerBase player )
	{
        GetPermissionsManager().PlayerLeft( player.GetIdentity() );

        super.InvokeOnDisconnect( player );
    } 

}
