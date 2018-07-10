/*****************************************************************************
 * mlalbumtrack.cpp : Medialibrary's album track
 ****************************************************************************
 * Copyright (C) 2006-2011 VideoLAN and AUTHORS
 * $Id$
 *
 * Authors: Maël Kervella <dev@maelkervella.eu>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#include <cassert>
#include "mlalbumtrack.hpp"
#include "mlhelper.hpp"

MLAlbumTrack::MLAlbumTrack(const vlc_ml_media_t *_data, QObject *_parent )
    : QObject( _parent )
    , m_id         ( _data->i_id)
    , m_title      ( QString::fromUtf8( _data->psz_title ) )
    , m_trackNumber( _data->album_track.i_track_nb )
{
    assert( _data );
    assert( _data->i_type == VLC_ML_MEDIA_TYPE_AUDIO );

    int t_sec = _data->i_duration / 1000000;
    int sec = t_sec % 60;
    int min = (t_sec / 60) % 60;
    int hour = t_sec / 3600;
    if (hour == 0)
        m_duration = QString("%1:%2")
                .arg(min, 2, 10, QChar('0'))
                .arg(sec, 2, 10, QChar('0'));
    else
        m_duration = QString("%1:%2:%3")
                .arg(hour, 2, 10, QChar('0'))
                .arg(min, 2, 10, QChar('0'))
                .arg(sec, 2, 10, QChar('0'));

    for( const vlc_ml_file_t& file: ml_range_iterate<vlc_ml_file_t>( _data->p_files ) )
        if( file.i_type == VLC_ML_FILE_TYPE_MAIN )
        {
            //FIXME should we store every mrl
            m_mrl = QString::fromUtf8(file.psz_mrl);
            break;
        }
}

uint64_t MLAlbumTrack::getId() const
{
    return m_id;
}

QString MLAlbumTrack::getTitle() const
{
    return m_title;
}

QString MLAlbumTrack::getAlbumTitle() const
{
    return m_albumTitle;
}

QString MLAlbumTrack::getCover() const
{
    return m_cover;
}

unsigned int MLAlbumTrack::getTrackNumber() const
{
    return m_trackNumber;
}

QString MLAlbumTrack::getDuration() const
{
    return m_duration;
}

QString MLAlbumTrack::getMRL() const
{
    return m_mrl;
}

QString MLAlbumTrack::getPresName() const
{
    return m_title;
}

QString MLAlbumTrack::getPresImage() const
{
    return "qrc:///noart.png";
}

QString MLAlbumTrack::getPresInfo() const
{
    return "";
}