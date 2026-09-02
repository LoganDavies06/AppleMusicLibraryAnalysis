from python_files.play_count_helper import *

play_counts = query_play_count()

for song in play_counts[:5]:
    print(
        "Title:", song.title,
        "Artist:", song.artist,
        "Album Artist:", song.album_artist,
        "Album:", song.album,
        "Plays:", song.plays,
        "ID:", song.musicID,
        "Track Number:", song.trackNo,
        "Disk Number:", song.diskNo
    )