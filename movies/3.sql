-- Lists the titles of all movies with a release date on or after 2018, in alphabetical order
-- First find movies title(s) released on or after 2018, then order alphbetically
SELECT title FROM movies
WHERE year >= '2018'
ORDER BY title;
