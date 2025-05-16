-- Lists the titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred
-- Search for Bradley Coopers Movies with JL's movies as a subset search
SELECT title
FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON stars.person_id = people.id
WHERE people.name = 'Bradley Cooper'
AND title IN
    (SELECT title
    FROM movies
    JOIN stars ON stars.movie_id = movies.id
    JOIN people ON stars.person_id = people.id
    WHERE people.name = 'Jennifer Lawrence');
