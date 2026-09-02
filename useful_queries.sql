-- Get every song and the earliest release it appears on
SELECT song, release, release_year
FROM (
    SELECT
        s.id AS song_id,
        s.title AS song,
        r.title AS release,
        r.release_year,
        ROW_NUMBER() OVER (
            PARTITION BY s.id
            ORDER BY r.release_year ASC, r.id ASC
        ) AS rn
    FROM Song s
    JOIN SongVersion sv ON sv.song_id = s.id
    JOIN Release r ON r.id = sv.release_id
)
WHERE rn = 1
ORDER BY song;