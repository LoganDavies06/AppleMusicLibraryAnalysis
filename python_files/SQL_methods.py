import sqlite3
from mutagen import File
from pathlib import Path
from datetime import date

def create_database():
    database = sqlite3.connect("music.db")

    with open("create_tables.sql", "r") as file:
        database.executescript(file.read())

    database.commit()
    return database

def get_artists(db: sqlite3.Connection, artists: list[str]):
    artist_ids = []

    for artist in artists:
        row = db.execute("SELECT id FROM Artist WHERE name = ?", (artist,)).fetchone()

        if row: 
            artist_ids.append(row[0])
            continue

        cursor = db.execute("INSERT INTO Artist (name) VALUES (?)", (artist,))

        artist_ids.append(cursor.lastrowid)

    return artist_ids

def get_song(db: sqlite3.Connection, artist_ids: list[int], title: str):
    rows = db.execute("SELECT id FROM Song WHERE title = ?", (title,)).fetchall()

    wanted = set(artist_ids)

    for row in rows:
        song_id = row[0]

        existing = db.execute(
            "SELECT artist_id FROM SongArtist WHERE song_id = ?",
            (song_id,)
        ).fetchall()

        existing_ids = {row[0] for row in existing}

        if existing_ids == wanted:
            return song_id

    cursor = db.execute("INSERT INTO Song (title) VALUES (?)", (title,))
    song_id = cursor.lastrowid

    db.executemany("INSERT INTO SongArtist (song_id, artist_id) VALUES (?, ?)", [(song_id, artist_id) for artist_id in artist_ids])

    return song_id

def get_release(db: sqlite3.Connection, file: File, artist_ids: list[int], title: str, path: Path):
    compilation = file.tags.get("cpil", [False])
    year =  file.tags.get("\xa9day")[0]

    if compilation:
        artist_ids = db.execute("SELECT id FROM Artist WHERE name = 'Various Artists'").fetchone()

    wanted = set(artist_ids)

    rows = db.execute("SELECT id FROM Release WHERE title = ?", (title,)).fetchall()

    for row in rows:
        release_id = row[0]

        existing = db.execute(
            "SELECT artist_id FROM ReleaseArtist WHERE release_id = ?",
            (release_id,)
        ).fetchall()

        existing_ids = {row[0] for row in existing}

        if existing_ids == wanted:
            return release_id

    cursor = db.execute("INSERT INTO Release (title, release_year) VALUES (?, ?)", (title,year))
    release_id = cursor.lastrowid

    db.executemany("INSERT INTO ReleaseArtist (release_id, artist_id) VALUES (?, ?)", [(release_id, artist_id) for artist_id in artist_ids])

    return release_id

def get_version(db: sqlite3.Connection, file: File, path: Path, song_id: int, release_id: int, subtitle: str, musicID: str):
    track = file.tags.get("trkn")
    disk = file.tags.get("disk")
    duration = round(file.info.length)

    track_no = track[0][0] if track else None
    disk_no = disk[0][0] if disk else None

    row = db.execute("SELECT id FROM SongVersion WHERE music_id = ?", (musicID,)).fetchone()

    if row: 
        db.execute("UPDATE SongVersion SET song_id = ?, subtitle = ? WHERE id = ?", (song_id, subtitle, row[0]))
        return row[0]

    cursor = db.execute("INSERT INTO SongVersion (song_id, release_id, subtitle, track_no, disk_no, file_path, duration_sec, music_id) VALUES (?,?,?,?,?,?,?,?)", (song_id, release_id, subtitle, track_no, disk_no, str(path), duration, musicID))

    return cursor.lastrowid

def add_play_count(db: sqlite3.Connection, version_id: int, play_count: int):
    curr_date = date.today().isoformat()
    row = db.execute("SELECT id FROM PlayHistory WHERE version_id = ? AND date = ?", (version_id,curr_date)).fetchone()

    if row:
        db.execute("UPDATE PlayHistory SET count = ? WHERE id = ?", (play_count, row[0]))
    else:
        db.execute("INSERT INTO PlayHistory (version_id, date, count) VALUES (?, ?, ?)", (version_id, curr_date, play_count))