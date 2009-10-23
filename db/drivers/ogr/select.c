
/*****************************************************************************
*
* MODULE:       OGR driver 
*   	    	
* AUTHOR(S):    Radim Blazek
*               Some updates by Martin Landa <landa.martin gmail.com>
*
* PURPOSE:      DB driver for OGR sources     
*
* COPYRIGHT:    (C) 2004-2009 by the GRASS Development Team
*
*               This program is free software under the GNU General Public
*   	    	License (>=v2). Read the file COPYING that comes with GRASS
*   	    	for details.
*
*****************************************************************************/

#include <grass/gis.h>
#include <grass/dbmi.h>
#include <grass/glocale.h>

#include "ogr_api.h"
#include "globals.h"
#include "proto.h"

/*!
  \brief Open select cursor

  \param sel select statement (given as dbString)
  \param[out] dbc pointer to dbCursor
  \param mode open mode

  \return DB_OK on success
  \return DB_FAILED on failure
*/
int db__driver_open_select_cursor(dbString * sel, dbCursor * dbc, int mode)
{
    cursor *c;
    dbTable *table;

    init_error();

    /* allocate cursor */
    c = alloc_cursor();
    if (c == NULL)
	return DB_FAILED;

    db_set_cursor_mode(dbc, mode);
    db_set_cursor_type_readonly(dbc);

    c->hLayer = OGR_DS_ExecuteSQL(hDs, db_get_string(sel), NULL, NULL);

    if (c->hLayer == NULL) {
	append_error(_("Unable to select: \n"));
	append_error(db_get_string(sel));
	append_error("\n");
	report_error();
	return DB_FAILED;
    }

    if (describe_table(c->hLayer, &table, c) == DB_FAILED) {
	append_error(_("Unable to describe table\n"));
	report_error();
	OGR_DS_ReleaseResultSet(hDs, c->hLayer);
	return DB_FAILED;
    }

    /* record table with dbCursor */
    db_set_cursor_table(dbc, table);

    /* set dbCursor's token for my cursor */
    db_set_cursor_token(dbc, c->token);

    return DB_OK;
}
