CREATE TABLE IF NOT EXISTS Artist(
    id INTEGER PRIMARY KEY,
    name TEXT NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS Song(
    id INTEGER PRIMARY KEY,
    title TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS Release(
    id INTEGER PRIMARY KEY,
    title TEXT NOT NULL,
    release_year INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS SongVersion(
    id INTEGER PRIMARY KEY,
    song_id INTEGER NOT NULL,
    music_id TEXT UNIQUE,
    subtitle TEXT,
    release_id INTEGER NOT NULL,
    track_no INTEGER NOT NULL CHECK (track_no >= 0),
    disk_no INTEGER,
    file_path TEXT NOT NULL,
    duration_sec INTEGER NOT NULL CHECK (duration_sec >= 0),
    FOREIGN KEY (song_id) REFERENCES Song(id),
    FOREIGN KEY (release_id) REFERENCES Release(id)
);

CREATE TABLE IF NOT EXISTS PlayHistory(
    id INTEGER PRIMARY KEY,
    version_id INTEGER NOT NULL,
    date TEXT NOT NULL,
    count INTEGER NOT NULL CHECK (count >= 0),
    FOREIGN KEY (version_id) REFERENCES SongVersion(id)
);

CREATE TABLE IF NOT EXISTS SongArtist(
    song_id INTEGER NOT NULL,
    artist_id INTEGER NOT NULL,
    PRIMARY KEY (song_id, artist_id),
    FOREIGN KEY (song_id) REFERENCES Song(id),
    FOREIGN KEY (artist_id) REFERENCES Artist(id)
);

CREATE TABLE IF NOT EXISTS ReleaseArtist(
    release_id INTEGER NOT NULL,
    artist_id INTEGER NOT NULL,
    PRIMARY KEY (release_id, artist_id),
    FOREIGN KEY (release_id) REFERENCES Release(id),
    FOREIGN KEY (artist_id) REFERENCES Artist(id)
);

INSERT OR IGNORE INTO Artist (name)
VALUES ('Various Artists');