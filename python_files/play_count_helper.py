import subprocess
import csv

script = '''
tell application "Music"
    set output to ""
    set i to 0

    set totalTracks to count of every file track of library playlist 1
    display notification "Processing " & totalTracks & " tracks..." with title "Apple Music Query"

    repeat with t in every file track of library playlist 1
        set trackName to name of t
        set trackArtist to artist of t
        set trackAlbum to album of t
        set trackPlays to played count of t
        set musicID to persistent ID of t
        set trackNo to track number of t
        set diskNo to disc number of t

        set albumArtist to album artist of t
        if albumArtist is missing value or albumArtist is "" then
            set albumArtist to trackArtist
        end if

        set i to i + 1
        if i mod 20 = 0 then
            display notification "Processed " & i & " out of " & totalTracks & " tracks" with title "Apple Music Query"
        end if

        set output to output & trackName & tab & trackArtist & tab & albumArtist & tab & trackAlbum & tab & trackPlays & tab & musicID & tab & trackNo & tab & diskNo & return
    end repeat

    return output
end tell
'''

def query_play_count():
    result = subprocess.run(
        ["osascript", "-e", script],
        capture_output=True,
        text=True
    )

    entries = []

    if result.returncode != 0:
        print("Error:")
        print(result.stderr)
    else:
        for line in result.stdout.splitlines():
            title, artist, album_artist, album, plays, musicID, trackNo, diskNo = line.split("\t")

            entries.append(SongData(title, artist, album_artist, album, plays, musicID, trackNo, diskNo))

    with open("entries.csv", "w", newline="") as entriesFile:
        writer = csv.writer(entriesFile)

        writer.writerow([
        "title",
        "artist",
        "album_artist",
        "album",
        "plays",
        "musicID",
        "trackNo",
        "diskNo"])

        for i in entries:
            writer.writerow([i.title, i.artist, i.album_artist, i.album, i.plays, i.musicID, i.trackNo, i.diskNo])

    return entries

def query_play_count_csv():
    entries = []

    with open("entries.csv","r") as entries_file:
        reader = csv.reader(entries_file)
        header = next(reader)
        for row in reader:
            entries.append(SongData(row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7]))

    return entries


class SongData:
    title: str
    artist: str
    album_artist: str
    album: str
    plays: int
    musicID: str
    trackNo: int
    diskNo: int

    def __init__(self,title, artist, album_artist, album, plays, musicID, trackNo, diskNo):
        self.title = title
        self.artist = artist
        self.album_artist = album_artist
        self.album = album
        self.plays = int(plays)
        self.musicID = musicID
        self.trackNo = int(trackNo)
        self.diskNo = int(diskNo)

        if not album_artist:
            self.album_artist = artist

        if self.diskNo == 0:
            self.diskNo = 1
