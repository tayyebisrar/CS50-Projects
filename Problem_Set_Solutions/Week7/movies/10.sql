--SELECT DISTINCT name
--FROM people
--JOIN directors ON people.id = directors.person_id
--JOIN movies ON movies.id = directors.movie_id
--JOIN ratings ON movies.id = ratings.movie_id
--WHERE ratings.rating >= 9.0;
--alternative method
SELECT DISTINCT name
FROM people
WHERE id IN (
    SELECT person_id
    FROM directors
    WHERE movie_id IN (
        SELECT id
        FROM movies
        WHERE id IN (
            SELECT movie_id
            FROM ratings
            WHERE rating >= 9.0
        )
    )
);

