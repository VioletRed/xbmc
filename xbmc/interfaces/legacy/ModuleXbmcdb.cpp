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

#include "ModuleXbmcdb.h"

#include "filesystem/PluginDirectory.h"
#include "FileItem.h"

#include "AddonUtils.h"
#include "video/VideoInfoTag.h"
#include "music/tags/MusicInfoTag.h"
#include "pictures/PictureInfoTag.h"
#include "video/VideoDatabase.h"
#include "music/MusicDatabase.h"
#include "URL.h"
#include "media/MediaType.h"

namespace XBMCAddon
{

  namespace xbmcdb
  {
    using namespace std;

    int addItemtoVideoDb(const String& mediatype,
        const XBMCAddon::xbmcgui::ListItem* listItem)
    {
      CVideoDatabase videodb;
      CVideoInfoTag &movieDetails = *(listItem->item->GetVideoInfoTag());
      long lResult;
      CURL url(listItem->item->GetPath());

      if (!url.IsProtocol("plugin"))
        return -1; // Add plugins, not files

      // ensure the art map isn't completely empty by specifying an empty thumb
      map<string, string> art = listItem->item->GetArt();
      if (art.empty())
        art["thumb"] = "";

      if (mediatype != MediaTypeSong)
      {
        /* Add the video to videodatabase
         * Store the original path (i.e "plugin://...") even if the
         * playable stream has been already resolved.
         */
        videodb.Open();
        std::string Path = movieDetails.GetPath();
        std::string FileNameAndPath = movieDetails.m_strFileNameAndPath;
        if (listItem->item->HasProperty("original_listitem_url"))
        {
          movieDetails.m_strFileNameAndPath = listItem->item->GetProperty(
              "original_listitem_url").asString();
          movieDetails.m_strPath = listItem->item->GetProperty(
              "original_listitem_url").asString();
        }
        lResult = videodb.SetDetailsForItem(-1, mediatype, movieDetails, art);
        movieDetails.m_strFileNameAndPath = FileNameAndPath;
        movieDetails.m_strPath = Path;
        movieDetails.m_iDbId = lResult;
        movieDetails.m_type = mediatype;
        videodb.Close();
      }
      return lResult;
    }

    void deleteItemfromVideoDb(const String& path)
    {
      CURL url(path);
      CVideoDatabase videodb;

      if (!url.IsProtocol("plugin"))
        return;

      if (!videodb.Open())
        return;
      videodb.DeleteMovie(path);
      videodb.DeleteEpisode(path);
      videodb.DeleteMusicVideo(path);
      videodb.Close();
    }

    std::vector<XBMCAddon::xbmcgui::ListItem*> getVideoItemsByWhere(
        const String& mediaType, const String& SQLWhere, const String& SQLJoin,
        const String& SQLFields, const String& SQLOrder, const String& SQLGroup)
    {
      CVideoDatabase videodb;
      CVideoDatabase::Filter filter;
      CFileItemList videoItems;
      std::vector<XBMCAddon::xbmcgui::ListItem*> listItems;

      filter.where  = SQLWhere;
      filter.join   = SQLJoin;
      filter.order  = SQLOrder;
      filter.fields = SQLFields;
      filter.group  = SQLGroup;

      if (!MediaTypes::IsValidMediaType(mediaType))
        return listItems;

      std::ostringstream baseDbPath;
      baseDbPath << "videodb://" << MediaTypes::ToPlural(mediaType) << "/titles";

      if (!videodb.Open())
        return listItems;

      videodb.GetItems(baseDbPath.str(), videoItems, filter);
      videodb.Close();

      int i = 0;
      while (i < videoItems.Size())
      {
        /* Copy returned items into a Python-SWIG compatible structure */
        XBMCAddon::xbmcgui::ListItem* item;
        item = new XBMCAddon::xbmcgui::ListItem(videoItems.Get(i++));
        listItems.push_back(item);
      }
      return listItems;
    }

    std::vector<XBMCAddon::xbmcgui::ListItem*> getMoviesByWhere(
        const String& SQLWhere, const String& SQLJoin, const String& SQLFields,
        const String& SQLOrder, const String& SQLGroup)
    {
      return getVideoItemsByWhere(MediaTypeMovie, SQLWhere, SQLJoin, SQLFields, SQLOrder, SQLGroup);
    }

    std::vector<XBMCAddon::xbmcgui::ListItem*> getMusicVideosByWhere(
        const String& SQLWhere, const String& SQLJoin, const String& SQLFields,
        const String& SQLOrder, const String& SQLGroup)
    {
      return getVideoItemsByWhere(MediaTypeMusicVideo, SQLWhere, SQLJoin, SQLFields, SQLOrder, SQLGroup);
    }

  }
}
