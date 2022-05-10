#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../common/HPMi.h"
#include "../map/clif.h"
#include "../map/atcommand.h"
#include "../map/script.h"
#include "../map/pc.h"
#include "../common/nullpo.h"

#include "../common/HPMDataCheck.h"

HPExport struct hplugin_info pinfo =
{
    "@hold",		// Plugin name
    SERVER_TYPE_MAP,// Which server types this plugin works with?
    "0.1",			// Plugin version
    HPM_VERSION,	// HPM Version (don't change, macro is automatically updated)
};


/*==========================================
* @hold by Voidless
*==========================================*/
ACMD(hold)
{
	nullpo_retr(-1, sd);

	if (!sd->block_action.move)
	{
		sd->block_action.move=1;
		clif->message(fd, "Character movement turned off");
	}
	else
	{
		sd->block_action.move=0;
		clif->message(fd, "Character movement turned on");
	}
	return 1;
}


/* Server Startup */
HPExport void plugin_init (void)
{
	addAtcommand("hold",hold);
}
