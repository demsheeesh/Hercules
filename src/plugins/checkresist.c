//===== Hercules Plugin ======================================
//= race_resist() script command
//===== By ===================================================
//= Kuroe
//===== Credits===============================================
//= Wolfie of BlackoutRO (https://blackout-ro.net) (check_resist) plugin
//= http://herc.ws/board/topic/16115-check_resist-script-command/
//===== Version ==============================================
//= 1.1
//===== Description ==========================================
//= Checks how much resistance a character has to a particular
// race.
//
//= race_resist(<type>{, <account id>});
//= E.g. race_resist(RC_Player);
//= E.g. race_resist(RC_Player, getcharid(CHAR_ID_ACCOUNT));
/* Types:
	- `RC_Formless`: 0
	- `RC_Undead`: 1
	- `RC_Brute`: 2
	- `RC_Plant`: 3
	- `RC_Insect`: 4
	- `RC_Fish`: 5
	- `RC_Demon`: 6
	- `RC_DemiHuman`: 7
	- `RC_Angel`: 8
	- `RC_Dragon`: 9
	- `RC_Player`: 10
	- `RC_Boss`: 11
	- `RC_NonBoss`: 12
*/
//============================================================

#include "common/hercules.h" /* Should always be the first Hercules file included! (if you don't make it first, you won't be able to use interfaces) */

#include "map/map.h"
#include "map/pc.h"
#include "map/script.h"

#include "common/HPMDataCheck.h" /* should always be the last Hercules file included! (if you don't make it last, it'll intentionally break compile time) */

HPExport struct hplugin_info pinfo = {
	"race_resist",    // Plugin name
	SERVER_TYPE_MAP,// Which server types this plugin works with?
	"1.1",       // Plugin version
	HPM_VERSION, // HPM Version (don't change, macro is automatically updated)
};

BUILDIN(race_resist)
{
	struct map_session_data *sd = (script_hasdata(st, 3)) ? script->id2sd(st, script_getnum(st, 3)) : script->rid2sd(st);
	if (sd == NULL)
		return true;

	int type = script_getnum(st, 2);
	if (type < RC_FORMLESS || type >= RC_MAX) {
		ShowWarning("buildin_race_resist: Invalid type specified.\n");
		script_pushint(st, -1);
		return false;
	}

	script_pushint(st, sd->subrace[type]);
	return true;
}

/* run when server starts */
HPExport void plugin_init (void)
{
	addScriptCommand("race_resist", "i?", race_resist);
}