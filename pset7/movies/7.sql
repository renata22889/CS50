SELECT title, rating FROM ratings

ratings JOIN movies ON ratings.movie_id = movies.id

WHERE rating != "\\N" 
AND year = 2010

GROUP BY title
ORDER BY rating DESC;