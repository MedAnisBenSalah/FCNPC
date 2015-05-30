/* =========================================
			
		FCNPC - Fully Controllable NPC
			----------------------

	- File: Main.cpp
	- Author(s): OrMisicL

  =========================================*/

#include "Main.h"

// Globals
logprintf_t			logprintf;
void				**ppPluginData;
extern void			*pAMXFunctions;
CServer				*pServer;
bool				bServerInit = false;
DWORD				dwStartTick;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) 
{
	ppPluginData = ppData;
	// Get the AMX functions pointer
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	// Get the logprintf function address
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];
	// Print the loading message
	logprintf("");
	logprintf("-------------------------------------------------");
	logprintf("     FCNPC - Fully Controllable NPC v" VERSION "");
	logprintf("");
	logprintf("- Author: OrMisicL");
	logprintf("- Build:  " __DATE__" at " __TIME__ "");
	logprintf("-------------------------------------------------");
	logprintf("");
	logprintf("Loading ...");

	/*

	*/
	/*DWORD a = CUtils::FindPattern("\x80\xB8\x67\x0C\x00\x00\x02\x74\x1D\x8B\x45\xD8\x89\x04\x24", "xx????xx?xxxxxx") + 2;
	logprintf("0x%x - 0x%x", a, *(DWORD *)a);*/
	// Install the exception handler
	CExceptionHandler::Install();
	// Initialize linux tick count
#ifndef _WIN32
	CUtils::LoadTickCount();
#endif
	// Create the server instance
	pServer = new CServer();
	if(!pServer)
	{
		logprintf("Failed. (Cant create server instance)");
		return false;
	}
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload( )
{
	// Reset the unintizalized flag
	bServerInit = false;
	// Delete the server instance
	SAFE_DELETE(pServer);

	logprintf("FCNPC Unloaded.");
}
// Natives table
AMX_NATIVE_INFO PluginNatives[ ] =
{
	{ "FCNPC_SetUpdateRate", CNatives::FCNPC_SetUpdateRate},
	{ "FCNPC_InitZMap", CNatives::FCNPC_InitZMap},
	
	{ "FCNPC_Create", CNatives::FCNPC_Create},
	{ "FCNPC_Destroy", CNatives::FCNPC_Destroy},
	{ "FCNPC_Spawn", CNatives::FCNPC_Spawn},
	{ "FCNPC_Respawn", CNatives::FCNPC_Respawn},
	{ "FCNPC_IsSpawned", CNatives::FCNPC_IsSpawned},
	{ "FCNPC_Kill", CNatives::FCNPC_Kill},
	{ "FCNPC_IsDead", CNatives::FCNPC_IsDead},

	{ "FCNPC_SetPosition", CNatives::FCNPC_SetPosition},
	{ "FCNPC_GetPosition", CNatives::FCNPC_GetPosition},
	{ "FCNPC_SetQuaternion", CNatives::FCNPC_SetQuaternion},
	{ "FCNPC_GetQuaternion", CNatives::FCNPC_GetQuaternion},
	{ "FCNPC_SetAngle", CNatives::FCNPC_SetAngle},
	{ "FCNPC_GetAngle", CNatives::FCNPC_GetAngle},
	{ "FCNPC_SetVelocity", CNatives::FCNPC_SetVelocity},
	{ "FCNPC_GetVelocity", CNatives::FCNPC_GetVelocity},
	{ "FCNPC_SetInterior", CNatives::FCNPC_SetInterior},
	{ "FCNPC_GetInterior", CNatives::FCNPC_GetInterior},

	{ "FCNPC_SetHealth", CNatives::FCNPC_SetHealth},
	{ "FCNPC_GetHealth", CNatives::FCNPC_GetHealth},
	{ "FCNPC_SetArmour", CNatives::FCNPC_SetArmour},
	{ "FCNPC_GetArmour", CNatives::FCNPC_GetArmour},

	{ "FCNPC_SetSkin", CNatives::FCNPC_SetSkin},
	{ "FCNPC_GetSkin", CNatives::FCNPC_GetSkin},

	{ "FCNPC_SetWeapon", CNatives::FCNPC_SetWeapon},
	{ "FCNPC_GetWeapon", CNatives::FCNPC_GetWeapon},
	{ "FCNPC_SetAmmo", CNatives::FCNPC_SetAmmo},
	{ "FCNPC_GetAmmo", CNatives::FCNPC_GetAmmo},

	{ "FCNPC_SetKeys", CNatives::FCNPC_SetKeys},
	{ "FCNPC_GetKeys", CNatives::FCNPC_GetKeys},

	{ "FCNPC_SetSpecialAction", CNatives::FCNPC_SetSpecialAction},
	{ "FCNPC_GetSpecialAction", CNatives::FCNPC_GetSpecialAction},

	{ "FCNPC_GoTo", CNatives::FCNPC_GoTo},
	{ "FCNPC_Stop", CNatives::FCNPC_Stop},
	{ "FCNPC_IsMoving", CNatives::FCNPC_IsMoving},

	{ "FCNPC_AimAt", CNatives::FCNPC_AimAt},
	{ "FCNPC_StopAim", CNatives::FCNPC_StopAim},
	{ "FCNPC_MeleeAttack", CNatives::FCNPC_MeleeAttack},
	{ "FCNPC_StopAttack", CNatives::FCNPC_StopAttack},
	{ "FCNPC_IsAiming", CNatives::FCNPC_IsAiming},
	{ "FCNPC_IsShooting", CNatives::FCNPC_IsShooting},
	{ "FCNPC_IsReloading", CNatives::FCNPC_IsReloading},

	/*{ "FCNPC_EnterVehicle", CNatives::FCNPC_EnterVehicle},
	{ "FCNPC_ExitVehicle", CNatives::FCNPC_ExitVehicle},*/
	{ "FCNPC_PutInVehicle", CNatives::FCNPC_PutInVehicle},
	{ "FCNPC_RemoveFromVehicle", CNatives::FCNPC_RemoveFromVehicle},
	{ "FCNPC_GetVehicleID", CNatives::FCNPC_GetVehicleID},
	{ "FCNPC_GetVehicleSeat", CNatives::FCNPC_GetVehicleSeat},

	{ "FCNPC_StartRecordingPlayback", CNatives::FCNPC_StartRecordingPlayback},
	{ "FCNPC_StopRecordingPlayback", CNatives::FCNPC_StopRecordingPlayback},
	{ "FCNPC_PauseRecordingPlayback", CNatives::FCNPC_PauseRecordingPlayback},
	{ "FCNPC_ResumeRecordingPlayback", CNatives::FCNPC_ResumeRecordingPlayback},

	{ "FCNPC_OpenNode", CNatives::FCNPC_OpenNode},
	{ "FCNPC_CloseNode", CNatives::FCNPC_CloseNode},
	{ "FCNPC_IsNodeOpen", CNatives::FCNPC_IsNodeOpen},
	{ "FCNPC_GetNodePointPosition", CNatives::FCNPC_GetNodePointPosition},
	{ "FCNPC_GetNodeType", CNatives::FCNPC_GetNodeType},
	{ "FCNPC_SetNodePoint", CNatives::FCNPC_SetNodePoint},
	{ "FCNPC_GetNodePointCount", CNatives::FCNPC_GetNodePointCount},
	{ "FCNPC_GetNodeInfo", CNatives::FCNPC_GetNodeInfo},
	{ "FCNPC_PlayNode", CNatives::FCNPC_PlayNode},
	{ "FCNPC_StopPlayingNode", CNatives::FCNPC_StopPlayingNode},

	{ "FCNPC_GetZGround", CNatives::FCNPC_GetZGround},
	{ 0, 0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *pAMX) 
{
	if(!bServerInit)
	{
		// Initialize the server
		BYTE byteError = 0;
		if((byteError = pServer->Initialize()) != 0)
		{
			// Get the error
			char szError[64];
			CUtils::GetPluginError(byteError, szError);
			logprintf("Failed. (Error: %s)", szError);
			exit(0);
		}
		// Initialize the starting tick
		dwStartTick = GetTickCount();
		// Set the initialized flag
		bServerInit = true;
	}
	// Register the AMX
	CCallbackManager::RegisterAMX(pAMX);
	// Register the plugin natives for the amx instance
	return amx_Register(pAMX, PluginNatives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *pAMX) 
{
	// Unregister the AMX
	CCallbackManager::UnregisterAMX(pAMX);	
	return AMX_ERR_NONE;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() 
{
	// Check if we need to process
	if((GetTickCount() - dwStartTick) >= 5)
	{
		// Process the player manager
		pServer->GetPlayerManager()->Process();
		// Update the start tick 
		dwStartTick = GetTickCount();
	}
}