SELECT DISTINCT title
FROM movies
WHERE id In (
    SELECT movie_id
    FROM stars
    JOIN people ON stars.person_id = people.id
    WHERE people.name = 'Bradley Cooper'
)
AND id IN (
    SELECT movie_id
    FROM stars
    JOIN people ON stars.person_id = people.id
    WHERE people.name = 'Jennifer Lawrence'
);
