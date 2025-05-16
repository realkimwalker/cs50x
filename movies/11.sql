-- Lists the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, by highest rated
SELECT title
FROM movies
JOIN ratings ON ratings.movie_id = movies.id
JOIN stars ON stars.movie_id = movies.id
JOIN people ON stars.person_id = people.id
WHERE people.name = 'Chadwick Boseman'
ORDER BY rating DESC LIMIT 5;
