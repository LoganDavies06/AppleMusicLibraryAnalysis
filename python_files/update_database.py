#from mutagen.m4a import M4A
from mutagen import File
from pathlib import Path
import re
import sqlite3

from play_count_helper import *
from SQL_methods import *

def normalize_title(title):
    # Remove track/disc number
    #title = re.sub(r"^\d+(?:-\d+)?\s+", "", title)

    subtitles = []

    while True:
        match = re.match(r"^(.+?)\s*([\(\[][^)\]]*[\)\]])$", title)

        if not match:
            break

        title = match.group(1).strip()
        subtitles.insert(0, match.group(2))

    subtitle = " ".join(subtitles) if subtitles else None

    return title, subtitle

def process_artist(artist):
    artists = re.split(r"\s+(?:\+|feat\.)\s+", artist, flags=re.IGNORECASE)
    return artists

def song_into_database(database: sqlite3.Connection, full_artist: str, full_title: str, file: File, play_count: SongData, path: Path):
    title, subtitle = normalize_title(full_title)
    artists = process_artist(full_artist)
    album_artists = process_artist(play_count.album_artist)

    artist_ids = get_artists(database, artists)
    album_artist_ids = get_artists(database, album_artists)
    song_id = get_song(database, artist_ids, title)
    release_id = get_release(database, file, album_artist_ids, play_count.album, path)
    version_id = get_version(database, file, path, song_id, release_id, subtitle, play_count.musicID, play_count.fav)
    add_play_count(database, version_id, play_count.plays)

def process_song(path: Path, play_counts_map: dict[tuple[str, str, str, int, int], SongData], database: sqlite3.Connection):
    file = File(path)

    full_title = file.tags.get("\xa9nam")[0]
    full_artist = file.tags.get("\xa9ART")[0]
    album = file.tags.get("\xa9alb")[0]

    track_no = file.tags.get("trkn")[0][0]
    try:
        disk_no = file.tags.get("disk")[0][0]
    except:
        disk_no = 1

    key = (
        full_title,
        full_artist,
        album,
        track_no,
        disk_no
    )

    song = play_counts_map.get(key)

    if song:
        song_into_database(database, full_artist, full_title, file, song, path)

    database.commit()

def update_database():
    print("Retrieving play counts from Apple Music", flush=True)
    play_counts = query_play_count_csv()
    play_counts_map = {
    (song.title, song.artist, song.album, song.trackNo, song.diskNo): song
    for song in play_counts }

    print("Entering values into database")
    database = create_database()
    music_path = Path.home() / "Music" / "Music" / "Media.localized" / "Music"
    for i in music_path.rglob("*.m4a"): process_song(i, play_counts_map, database)

    print("Done!")
    database.close()

def test():
    title = "Change (In the House Of Flies)"

    title, sub = normalize_title(title)

    print(title)
    print(sub)

if __name__ == "__main__":
    update_database()