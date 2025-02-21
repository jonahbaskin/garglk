/******************************************************************************
 *                                                                            *
 * This file is part of Gargoyle.                                             *
 *                                                                            *
 * Gargoyle is free software; you can redistribute it and/or modify           *
 * it under the terms of the GNU General Public License as published by       *
 * the Free Software Foundation; either version 2 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * Gargoyle is distributed in the hope that it will be useful,                *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with Gargoyle; if not, write to the Free Software                    *
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA *
 *                                                                            *
 *****************************************************************************/

/* 
 * File:   gtk_utils.h
 */

#ifndef GTK_UTILS_H
#define GTK_UTILS_H

#include <stdbool.h>
#include <gtk/gtk.h>

/*
 * If the given filename string represents a directory, append a slash ('/') if the 
 * filename string isn't already terminated by a slash.
 * 
 * Note: GtkFileSelection requires filename strings that actually represent directories
 * to end with a slash, in order to initialize its widgets properly.
 */
GString * normalizeFilename(GString * filename);

/*
 * GtkTreeSortable sort func for sorting filename (and directory) lists case-insensitively.
 * 
 * GtkListStore usually sets such a sort func automatically for string lists, however this 
 * default sort func is not provided on some platforms (like Kindle).
 */
gint filenameListSortFunc(GtkTreeModel * model,
        GtkTreeIter * a, GtkTreeIter * b, gpointer user_data);

/*
 * Activates sorting for the filename lists of a GtkFileSelection dialog and similar 
 * GtkListStore backed single column tree views (i.e. this includes the directory-name 
 * list of GtkFileSelection).
 * 
 * Note: The sort order can be reversed at runtime by clicking on the respective column 
 * header.
 */
void makeFilenameListTreeViewSortable(GtkTreeView * filenameListTreeView, GtkSortType initialSortOrder);

#ifdef _KINDLE
/*
 * Returns the value of the first environment variable set or an empty string
 * otherwise. The caller is responsible to free the returned GString object.
 */
GString * createAndInitFilenameFromOsEnvironmentVariable(
        const char * environmentVariableName1, 
        const char * environmentVariableName2);

void closeLipcInstance();
void openVirtualKeyboard(GtkWidget * widget, gpointer * callback_data);

/*
 * Creates a GtkFileSelection and sizes it for semi-fullscreen mode on K*ndle,
 * leaving approx. the bottom 1/3 of the screen for the native onscreen K*ndle 
 * keyboard.
 */
GtkWidget * createAndInitKindleFileRequestor(
        const GString * initFilename,               // Initial path and/or filename for the file requestor
        const GtkSortType directoryListSortOrder,   // Initial sort order for the directory list
        const GtkSortType filenameListSortOrder);   // Initial sort order for the file list
#endif /* _KINDLE */

#endif /* GTK_UTILS_H */
