/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "Tuple.h"

#include "AddonString.h"
#include "ListItem.h"

#include "utils/log.h"

#include "SortFileItem.h"
#include "swighelper.h"

namespace XBMCAddon
{
  namespace xbmcdb
  {
    /**
     * addItemtoVideoDb(database, listitem) -- Add the item to database
     * - Returns dbId for the item
     * mediatype   : string - Media type to be added
     *                        "movie"
     *                        "tvshow"
     *                        "musicvideo"
     *                        "song"
     * lititem     : ListItem - Item to be added
     *
     * example:
     *   - xbmcplugin.addItemtoDb("musicvideo", listitem)
     */
    int addItemtoVideoDb(const String& mediatype,
        const XBMCAddon::xbmcgui::ListItem* listItem);

    /**
     * deleteItemfromVideoDb(path) -- Remove all references to item from database
     * path        : string - Path to media to be removed
     *
     * example:
     *   - xbmcplugin.deleteItemfromDb("plugin://plugin.video.myplugin/path/to/item")
     */
    void deleteItemfromVideoDb(const String& path);

    /**
     * getVideoItemsByWhere(where, join, fields, order, group) -- Run a SQL query in videodb
     * where        : string - Basic SQL statement
     *
     * example:
     *   - xbmcplugin.getMoviesByWhere(MEDIA_TYPE_MOVIE, "title like '%mymovie%')
     */
    std::vector<XBMCAddon::xbmcgui::ListItem*> getVideoItemsByWhere(
        const String& mediaType, const String& SQLWhere,
        const String& SQLJoin = emptyString,
        const String& SQLFields = emptyString,
        const String& SQLOrder = emptyString,
        const String& SQLGroup = emptyString);

    /**
     * getMoviesByWhere(where, join, fields, order, group) -- Run a SQL query in videodb
     * where        : string - Basic SQL statement
     *
     * example:
     *   - xbmcplugin.getMoviesByWhere("name like '%mymovie%')
     */
    std::vector<XBMCAddon::xbmcgui::ListItem*> getMoviesByWhere(
        const String& SQLWhere, const String& SQLJoin = emptyString,
        const String& SQLFields = emptyString, const String& SQLOrder =
            emptyString, const String& SQLGroup = emptyString);

    /**
     * getMusicVideosByWhere(where, join, fields, order, group) -- Run a SQL query in videodb
     * where        : string - Basic SQL statement
     *
     * example:
     *   - xbmcplugin.getMusicVideosByWhere("name like '%mymovie%')
     */
    std::vector<XBMCAddon::xbmcgui::ListItem*> getMusicVideosByWhere(
        const String& SQLWhere, const String& SQLJoin = emptyString,
        const String& SQLFields = emptyString, const String& SQLOrder =
            emptyString, const String& SQLGroup = emptyString);

    SWIG_CONSTANT2(std::string, MEDIA_TYPE_NONE, MediaTypeNone);
    SWIG_CONSTANT2(std::string, MEDIA_TYPE_MUSIC, MediaTypeMusic);
    SWIG_CONSTANT2(std::string, MEDIA_TYPE_ARTIST, MediaTypeArtist);
    SWIG_CONSTANT2(std::string, MEDIA_TYPE_ALBUM, MediaTypeAlbum);
    SWIG_CONSTANT2(std::string, MEDIA_TYPE_SONG, MediaTypeSong);
    SWIG_CONSTANT2(std::string, MEDIA_TYPE_VIDEO, MediaTypeVideo);
    SWIG_CONSTANT2(std::string, MEDIA_TYPE_VIDEO_COLLECTION,MediaTypeVideoCollection);
    SWIG_CONSTANT2(std::string, MEDIA_TYPE_MUSIC_VIDEO, MediaTypeMusicVideo);
    SWIG_CONSTANT2(std::string, MEDIA_TYPE_MOVIE, MediaTypeMovie);
    SWIG_CONSTANT2(std::string, MEDIA_TYPE_TVSHOW, MediaTypeTvShow);
    SWIG_CONSTANT2(std::string, MEDIA_TYPE_SEASON, MediaTypeSeason);
    SWIG_CONSTANT2(std::string, MEDIA_TYPE_EPISODE, MediaTypeEpisode);
  }
}
